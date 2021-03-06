//
// Cache (N-way-associative array with replacement) object
//
// Jeff Brown
// $Id: cache-array.cc,v 1.1.2.18.2.4.2.14.6.1 2009/12/25 06:31:47 jbrown Exp $
//

const char RCSid_1034634457[] = 
"$Id: cache-array.cc,v 1.1.2.18.2.4.2.14.6.1 2009/12/25 06:31:47 jbrown Exp $";

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "sim-assert.h"
#include "sys-types.h"
#include "cache-array.h"
#include "assoc-array.h"
#include "coherence-mgr.h"
#include "sim-cfg.h"
#include "utils.h"
#include "sim-params.h"


using std::string;
using std::vector;


const char *CacheAccessType_names[] = {
    "Read", "ReadExcl", "Upgrade", "Write", NULL
};
const char *CacheLOutcome_names[] = {
    "Hit", "Miss", "UpgradeMiss", "CoherBusy", NULL
};
const char *CacheFillOutcome_names[] = { "NoEvict", "EvictClean", "EvictDirty",
                                         NULL };


// hack to help WritebackRec get time for debugging, without pushing "cyc"
// through all of the fill/writeback interfaces
static i64
read_global_cyc_hack()
{
    extern i64 cyc;
    return cyc;
}


namespace {

enum CacheEntryState { 
    CE_NotPresent,      // Tag match on a "not present" entry => coher. miss
    CE_SharedClean,
    CE_ExclClean,
    CE_Dirty,
    CacheEntryState_last,
    CacheEntryState_bits = 3    // #bits needed to hold values; is checked
};
const char *CacheEntryState_names[] = {
    "NotPresent", "SharedClean", "ExclClean", "Dirty", NULL
};


// Cache entry (one block)
class CacheEntry {
    CacheEntryState state : CacheEntryState_bits;      // top-level state
    bool coher_locked_out : 1;  // lookups locked out for pending coherence
    bool referenced : 1 ;       // referenced AFTER fill        

public:
    CacheEntry() { reset(); }

    void reset() {
        state = CE_NotPresent;
        coher_locked_out = false;
        referenced = false;
    }

    void set_state(CacheEntryState new_state) {
        // unconditional state assignment
        sim_assert(new_state != CE_NotPresent);     // should use reset()
        state = new_state;
    }

    CacheEntryState g_state() const { return state; }
    bool data_present() const { return (state != CE_NotPresent); }
    bool is_dirty() const { return (state == CE_Dirty); }
    bool write_perm() const {
        return (state == CE_ExclClean) || (state == CE_Dirty);
    }
    void set_dirty() {
        // writeable -> dirty upgrade
        sim_assert(write_perm());
        set_state(CE_Dirty);
    }
    void coher_lockout() {
        sim_assert(!coher_locked_out);
        sim_assert(data_present());
        coher_locked_out = true;
    }
    void coher_lockout_done() {
        // maybe not locked out, e.g. for L1 cache
        sim_assert(data_present());     // if not present, should have reset()
        coher_locked_out = false;
    }
    bool is_coher_locked_out() const { return coher_locked_out; }
    bool is_referenced() const {
        sim_assert(data_present());
        return referenced;
    }
    void set_referenced() {
        sim_assert(data_present());
        referenced = true;
    }
};


// Accounting info for each cache bank.
//
// Note that this cartoon model of cache ports doesn't account for concurrent
// operations on the same address by different ports.
class CacheBank {
    enum CachePortType { // Bit flags
        CP_Read=1,
        CP_Write=2,
        CP_ReadWrite = CP_Read | CP_Write
    };
    struct CachePort {
        CachePortType type;
        // Cycle# one past the completion of the most recent request completes:
        // the cycle that the result is available, and in which a new request
        // may begin.
        i64 avail_cyc;          // Cycle when next operation can begin
        i64 done_cyc;           // Cycle after all ops complete
        CachePort(CachePortType type_) : type(type_) {
            sim_assert((type == CP_Read) || (type == CP_Write) ||
                   (type == CP_ReadWrite));
        }
        void reset() { avail_cyc = done_cyc = 0; }
    };

    vector<CachePort> ports;    // order: read, write, read+write
    CacheBankStats stats;

    int choose_port(i64 now, bool for_write) const {
        int n_ports = static_cast<int>(ports.size());
        if (n_ports == 1)
            return 0;
        int choose_mask = (for_write) ? CP_Write : CP_Read;
        int chosen_pnum = -1;
        i64 min_time = I64_MAX;
        for (int pnum = 0; pnum < n_ports; pnum++) {
            const CachePort& port = ports[pnum];
            if (((port.type & choose_mask) == choose_mask)
                && (port.avail_cyc < min_time)) {
                chosen_pnum = pnum;
                min_time = port.avail_cyc;
                if (min_time <= now) {
                    // Don't bother chasing the global minimum time, if we've
                    // found one that's ready now; rather, prefer the
                    // lower-numbered (less-capable) port that can do the job.
                    break;
                }
            }
        }
        sim_assert(chosen_pnum >= 0);
        return chosen_pnum;
    }

public:
    CacheBank(int ports_r, int ports_w, int ports_rw) {
        for (int i = 0; i < ports_r; i++)
            ports.push_back(CachePort(CP_Read));
        for (int i = 0; i < ports_w; i++)
            ports.push_back(CachePort(CP_Write));
        for (int i = 0; i < ports_rw; i++)
            ports.push_back(CachePort(CP_ReadWrite));
    }
    void reset() {
        for (size_t pnum = 0; pnum < ports.size(); pnum++)
            ports[pnum].reset();
    }
    void reset_stats() { 
        stats.lookups_r = 0;
        stats.lookups_rex = 0;
        stats.lookups_upgrade = 0;
        stats.lookups_w = 0;
        stats.fills = 0;
        stats.fillconts = 0;
        stats.wbs = 0;  
        stats.coher_syncs = 0;
        stats.coher_pulls = 0;
    }
    i64 bill_time(i64 now, OpTime op_time, bool for_write) {
        int chosen_pnum = choose_port(now, for_write);
        CachePort& chosen_port = ports[chosen_pnum];
        i64 req_done_time;
        bill_resource_time(req_done_time, chosen_port.avail_cyc, now,
                           op_time);
        if (req_done_time > chosen_port.done_cyc)
            chosen_port.done_cyc = req_done_time;
        return req_done_time;
    }
    void inc_stats(CacheBankOp bank_op) {
        // Warning: interacts with utilization calc in get_bankstats()
        switch (bank_op) {
        case CacheBank_LookupR: stats.lookups_r++; break;
        case CacheBank_LookupREx: stats.lookups_rex++; break;
        case CacheBank_LookupUpgrade: stats.lookups_upgrade++; break;
        case CacheBank_LookupW: stats.lookups_w++; break;
        case CacheBank_Fill:    stats.fills++; break;
        case CacheBank_FillCont: stats.fillconts++; break;
        case CacheBank_WB:      stats.wbs++; break;
        case CacheBank_CoherSync: stats.coher_syncs++; break;
        case CacheBank_CoherPull: stats.coher_pulls++; break;
        default: sim_abort();
        }
    }
    void get_stats(CacheBankStats *dest) const {
        // Leaves "util" undefined, for caller to fill in
        *dest = stats;
    }
    bool port_avail(i64 now, bool for_write) const {
        int chosen_pnum = choose_port(now, for_write);
        const CachePort& chosen_port = ports[chosen_pnum];
        return chosen_port.avail_cyc <= now;
    }
    void sync_all_ports(i64 now) {
        // Prepare for an operation which must be ordered after any
        // outstanding operations.  This is conservative, but we don't have
        // much choice since we don't track addresses in this simplification.
        // (We include "done_cyc", since we need to order the _delivery_
        // (done-cyc) of smaller coherence invalidates/etc. with respect to
        // larger data fills, not just the start times.  A proper interconnect
        // model would address this.)
        i64 post_sync_time = now;
        for (vector<CachePort>::const_iterator iter = ports.begin();
             iter != ports.end(); ++iter) {
            if (iter->avail_cyc > post_sync_time)
                post_sync_time = iter->avail_cyc;
            if (iter->done_cyc > post_sync_time)
                post_sync_time = iter->done_cyc;
        }
        for (vector<CachePort>::iterator iter = ports.begin();
             iter != ports.end(); ++iter) {
            iter->avail_cyc = post_sync_time;
        }
    }
};

#if HAVE_HASHMAP
    typedef hash_map<u32,int> PopCountMap;
#else
    typedef std::map<u32,int> PopCountMap;
#endif


struct WritebackRec {
    LongAddr base_addr;
    i64 enq_time;               // for debugging
    bool for_coher;
    WritebackRec(const LongAddr& base_addr_, bool for_coher_)
        : base_addr(base_addr_), for_coher(for_coher_) {
        enq_time = read_global_cyc_hack();
    }
    string fmt() const {
        string out;
        out += "base_addr ";
        out += fmt_laddr(base_addr);
        out += ", enq_time ";
        out += fmt_i64(enq_time);
        out += ", for_coher ";
        out += (for_coher) ? "t" : "f";            
        return out;
    }
};

typedef std::list<WritebackRec> WritebackQueue;


} // Anonymous namespace close


struct CacheArray {
private:
    int cache_id;
    CacheGeometry geom;
    CacheTiming timing;
    CoherenceMgr *coher;
    // (parent_core arguably doesn't belong here, but it will likely prove
    // useful in the future)
    CoreResources *parent_core;         // NULL <=> not assoc. with ==1 core
    bool track_coher_misses;            // keep coher-invl tags for counting
    OpTime zero_op_time;

    string config_base;
    int block_bytes_lg, n_banks_lg;
    int n_lines_lg, n_lines;
    int n_blocks;

    AssocArray *cam;
    vector<CacheEntry> entries;         // 2D array [n_lines][assoc]
    vector<CacheBank> banks;            // 1D array [n_banks]
    WritebackQueue wb_fifo;             // pending writebacks
    int wb_fifo_used;
    CacheStats stats;
    PopCountMap pop_count;              // Population count (masterid -> count)
    int pop_total;                      // sum{i}(pop_count[i])
    i64 stats_reset_cyc;

    inline void gen_aa_key(AssocArrayKey& key, const LongAddr& addr) const {
        mem_addr tagidx = addr.a >> block_bytes_lg;
        key.lookup = tagidx;
        key.match = addr.id;
    }
    inline void reverse_aa_key(LongAddr& addr, const AssocArrayKey& key)
        const {
        addr.set(key.lookup << block_bytes_lg, key.match);
    }

    inline mem_addr block_base_addr(mem_addr addr) const {
        return addr & ~(geom.block_bytes - 1);
    }

    inline int block_bank_num(const LongAddr& addr) const {
        return static_cast<int>((addr.a >> block_bytes_lg)
                                & (geom.n_banks - 1));
    }

    inline CacheEntry& ent_ref(long line_num, int way_num) {
        sim_assert(line_num >= 0);
        sim_assert(way_num >= 0);
#ifdef DEBUG
        return entries.at(geom.assoc * line_num + way_num);
#else
        return entries[geom.assoc * line_num + way_num];
#endif
    }

    inline const CacheEntry& ent_ref(long line_num, int way_num) const {
        sim_assert(line_num >= 0);
        sim_assert(way_num >= 0);
#ifdef DEBUG
        return entries.at(geom.assoc * line_num + way_num);
#else
        return entries[geom.assoc * line_num + way_num];
#endif
    }

    void get_op_time(OpTime& ret, CacheBankOp bank_op) const {
        // Warning: interacts with utilization calc in get_bankstats()
        switch (bank_op) {
        case CacheBank_LookupR:
        case CacheBank_LookupREx:
        case CacheBank_LookupUpgrade:
        case CacheBank_LookupW:
            ret = timing.access_time;
            break;
        case CacheBank_Fill:
            ret = timing.fill_time;
            break;
        case CacheBank_FillCont:
            ret = timing.access_time;
            break;
        case CacheBank_WB:
        case CacheBank_CoherPull:
            ret = timing.access_time_wb;
            break;
        case CacheBank_CoherSync:
            ret = zero_op_time;
            break;
        default: 
            ret = timing.access_time;   // Avoid warnings
            sim_abort();
        }
    }

    bool coher_ok(const LongAddr& addr, const CacheEntry& entry) const {
        LongAddr base_addr(block_base_addr(addr.a), addr.id);
        return !coher ||
            cm_holder_okay(coher, base_addr, cache_id,
                           entry.is_dirty(), entry.write_perm());
    }

    void pop_reset() {
        pop_total = 0;
        pop_count.clear();
    }
    void pop_increment(const LongAddr& base_addr) {
        sim_assert(pop_total < n_blocks);
        sim_assert(pop_count[base_addr.id] <= pop_total);
        ++pop_count[base_addr.id];
        ++pop_total;
    }
    void pop_decrement(const LongAddr& base_addr) {
        sim_assert(pop_count[base_addr.id] > 0);
        sim_assert(pop_total > 0);
        --pop_count[base_addr.id];
        --pop_total;
    }

    void wb_enqueue(const LongAddr& base_addr, bool for_coher) {
        if (wb_fifo_used >= geom.wb_buffer_size) {
            abort_printf("cache %d WB buffer overflow, enqueue %s\n",
                         cache_id, fmt_laddr(base_addr));
        }
        wb_fifo.push_back(WritebackRec(base_addr, for_coher));
        wb_fifo_used++;
    }
    void wb_dump() const {      // for debugging
        printf("cache_id %d WB buffer (n=%d):\n", cache_id,
               (int) wb_fifo.size());
        int idx = 0;
        for (WritebackQueue::const_iterator iter = wb_fifo.begin();
             iter != wb_fifo.end(); ++iter, ++idx) {
            printf("  [%d]: %s\n", idx, (*iter).fmt().c_str());
        }
    }

public:
    CacheArray(int cache_id_, const CacheGeometry *geom_,
               const CacheTiming *timing_,
               CoherenceMgr *coher_, CoreResources *parent_core_, i64 now);
    ~CacheArray();
    void reset(i64 now);
    void reset_stats(i64 now);

    CacheLOutcome lookup(const LongAddr& addr,
                         CacheAccessType access_type, int *first_access_ret) {
        CacheLOutcome result = Cache_Miss;
        switch (access_type) {
        case Cache_Read:        stats.reads++; break;
        case Cache_ReadExcl:    stats.reads_ex++; break;
        case Cache_Upgrade:     stats.upgrades++; break;
        case Cache_Write:       stats.writes++; break;
        default:
            ENUM_ABORT(CacheAccessType, access_type);
        }
        AssocArrayKey lookup_key;
        gen_aa_key(lookup_key, addr);
        long line_num; int way_num;
        bool first_access = false;
        if (aarray_lookup(cam, &lookup_key, &line_num, &way_num)) {
            CacheEntry& entry = ent_ref(line_num, way_num);
            if (!entry.data_present()) {
                // tag match, data missing => coher. miss for stats purposes
                stats.misses++;
                stats.coher_misses++;
            } else if (entry.is_coher_locked_out()) {
                result = Cache_CoherBusy;
                stats.coher_busy++;
            } else if ((access_type != Cache_Read) && !entry.write_perm()) {
                // tag match, data present, but no write perm => upgrade miss
                result = Cache_UpgradeMiss;
                stats.upgrade_misses++;
                if (!entry.is_referenced()) {
                    entry.set_referenced();
                    first_access = true;
                }
            } else {
                result = Cache_Hit;
                stats.hits++;
                if (!entry.is_referenced()) {
                    entry.set_referenced();
                    first_access = true;
                }
                if (access_type == Cache_Write) {
                    entry.set_dirty();
                }
                sim_assert(coher_ok(addr, entry));
            }
        } else {
            stats.misses++;
        }
        if (first_access_ret)
            *first_access_ret = first_access;
        return result;
    }

    bool access_ok(const LongAddr& addr, CacheAccessType access_type)
        const {
        AssocArrayKey lookup_key;
        gen_aa_key(lookup_key, addr);
        long line_num; int way_num;
        bool result = false;
        if (aarray_probe(cam, &lookup_key, &line_num, &way_num)) {
            const CacheEntry& entry = ent_ref(line_num, way_num);
            switch (access_type) {
            case Cache_Read:
                result = entry.data_present(); break;
            case Cache_ReadExcl:
            case Cache_Upgrade:
            case Cache_Write:
                result = entry.write_perm(); break;
            default:
                ENUM_ABORT(CacheAccessType, access_type);
            }
        }
        return result;
    }

    bool touch(const LongAddr& addr) {
        bool data_present = false;
        AssocArrayKey lookup_key;
        gen_aa_key(lookup_key, addr);
        long line_num; int way_num;
        if (aarray_lookup(cam, &lookup_key, &line_num, &way_num)) {
            CacheEntry& entry = ent_ref(line_num, way_num);
            if (entry.data_present()) {
                data_present = true;
            }
        }
        return data_present;
    }

    bool wb_buffer_full() const {
        return wb_fifo_used >= geom.wb_buffer_size;
    }
    void log_wbfull_conflict() {
        stats.wbfull_confs++;
    }

    CacheFillOutcome
    fill(const LongAddr& addr, CacheAccessType access_type,
         CacheEvicted *evicted_ret) {
        AssocArrayKey fill_key;
        AssocArrayKey evicted_key;
        long line_num; int way_num;
        bool already_present = false;
        bool evicted_valid = false;
        bool evicted_dirty = false;
        sim_assert(!wb_buffer_full());
        gen_aa_key(fill_key, addr);
        if (aarray_lookup(cam, &fill_key, &line_num, &way_num)) {
            // line_num / way_num set for later; data may be missing, though
            already_present = true;
        } else {
            evicted_valid = aarray_replace(cam, &fill_key, &line_num,
                                           &way_num, &evicted_key);
            // line_num / way_num set to victim
        }
        CacheEntry& entry = ent_ref(line_num, way_num);
        // "cam" contains the new key, now; we need to take care of the old
        // contents of "entry" (if any), then set it up for the new resident
        if (!entry.data_present()) {
            // If already_present, then this is a tag match with missing data.
            // If evicted_valid, we're evicting a tag which has no
            // corresponding data.  In either case, we'll treat the block as
            // totally absent; we only kept the tags for statistics purposes.
            already_present = false;
            evicted_valid = false;
        }
        if (already_present) {
            // Fill on an already-present block: only valid for upgrade misses.
            // (A block may have been granted exclusive access even if it
            // wasn't requested, but there still shouldn't be a later fill
            // to that block; request merging and ordering must cause any
            // later requests to use the unexpected exclusive access, rather
            // than emit newer requests.  Allowing additional miss traffic for
            // already-held ExclClean blocks will lead to problems later,
            // as it's just a matter of luck until an intervening store hit
            // dirties the block before the later fill comes in, a 
            // conflict we should prevent.)
            if (GlobalParams.mem.use_coherence &&
                (entry.g_state() != CE_SharedClean)) {
                abort_printf("cache: id %d fill of addr %s for %s "
                             "found present block, but in state %s\n",
                             cache_id, fmt_laddr(addr),
                             CacheAccessType_names[access_type],
                             CacheEntryState_names[entry.g_state()]);
            }
        }
        if (evicted_valid) {
            LongAddr e_base_addr;
            reverse_aa_key(e_base_addr, evicted_key);
            // evict-notify stuff moved into cache.c, to account for multiple
            // levels of private cache, outstanding WB requests, etc.
            //if (coher)
            //    cm_evict_notify(coher, e_base_addr, cache_id);
            if (entry.is_dirty()) {
                evicted_dirty = true;
                stats.dirty_evicts++;
                wb_enqueue(e_base_addr, false);
            }
            evicted_ret->base_addr = e_base_addr;
            pop_decrement(e_base_addr);
        }

        entry.reset();
        switch (access_type) {
        case Cache_Read:
            entry.set_state(CE_SharedClean); break;
        case Cache_ReadExcl:
            entry.set_state(CE_ExclClean); break;
        case Cache_Upgrade:
            // Sketchy: we magically insert data here if it was not present.
            // See process_coher_reply() comments about full_block_transfer.
            if (false)
                sim_assert(already_present);// fill is just an ack, no data
            entry.set_state(CE_ExclClean); break;
        case Cache_Write:
            entry.set_state(CE_Dirty); break;
        default:
            ENUM_ABORT(CacheAccessType, access_type);

        }
        sim_assert(coher_ok(addr, entry));
        if (!already_present)           // (don't double-count upgrades)
            pop_increment(addr);

        CacheFillOutcome outcome = CacheFill_NoEvict;
        if (evicted_valid) {
            outcome = (evicted_dirty) ? CacheFill_EvictDirty :
                CacheFill_EvictClean;
        }
        return outcome;
    }

    bool writeback(const LongAddr& addr) {
        // (write-back from a cache above, into this cache)
        sim_assert(!wb_buffer_full());
        AssocArrayKey wb_key;
        gen_aa_key(wb_key, addr);
        long line_num = 0; int way_num = 0;
        bool block_in_cache = aarray_lookup(cam, &wb_key, &line_num, &way_num);
        CacheEntry& entry = ent_ref(line_num, way_num);
        stats.writes++;
        if (block_in_cache && !entry.data_present())
            block_in_cache = false;
        if (block_in_cache) {
            entry.set_dirty();
            sim_assert(coher_ok(addr, entry));
        } else {
            // write-around, using a WB buffer entry to hold the outbound data
            LongAddr base_addr(addr);
            align_addr(base_addr);
            wb_enqueue(base_addr, false);
        }
        return block_in_cache;
    }

    void mark_dirty(const LongAddr& addr) {
        AssocArrayKey lookup_key;
        gen_aa_key(lookup_key, addr);
        long line_num; int way_num;
        bool tag_found = aarray_probe(cam, &lookup_key, &line_num, &way_num);
        if (tag_found) {
            CacheEntry& entry = ent_ref(line_num, way_num);
            entry.set_dirty();
            sim_assert(coher_ok(addr, entry));
        } else {
            abort_printf("mark_dirty: block %s not found\n", fmt_laddr(addr));
        }
    }

    void mark_writeable(const LongAddr& addr) {
        AssocArrayKey lookup_key;
        gen_aa_key(lookup_key, addr);
        long line_num = 0; int way_num = 0;
        bool tag_found = aarray_probe(cam, &lookup_key, &line_num, &way_num);
        CacheEntry& entry = ent_ref(line_num, way_num);
        if (tag_found && entry.data_present()) {
            if (!entry.write_perm())
                entry.set_state(CE_ExclClean);
            sim_assert(coher_ok(addr, entry));
        } else {
            abort_printf("mark_writeable: block %s not present (%sfound)\n",
                         fmt_laddr(addr), ((tag_found) ? "" : "not "));
        }
    }

    bool wb_accepted(const LongAddr& base_addr) {
        // Writebacks are enqueued as fill/yield messages arrive at the cache,
        // and this function is called as they are accepted for delivery.
        //
        // Acceptance order need not match wb_enqueue() order across banks,
        // since enqueue occurs at fill-time, but the acceptance may occur
        // after a bank-dependent delay.
        sim_assert(wb_fifo_used > 0);
        sim_assert(!wb_fifo.empty());
        bool was_full = wb_buffer_full();

        // Inefficient linear scan :( We expect the buffer to be small,
        // though.
        WritebackQueue::iterator iter(wb_fifo.begin());
        for (; iter != wb_fifo.end(); ++iter) {
            if (iter->base_addr == base_addr)
                break;
        }
        if (iter == wb_fifo.end()) {
            abort_printf("CacheArray::wb_accepted: id %d, base_addr %s: "
                         "matching writeback not found!\n", cache_id,
                         fmt_laddr(base_addr));
        }
        // (We don't actually use the wb_fifo entries for anything beyond
        // consistency checks)
        wb_fifo.erase(iter);
        wb_fifo_used--;
        return was_full;
    }

    void coher_lockout(const LongAddr& base_addr) {
        AssocArrayKey lookup_key;
        long line_num = 0; int way_num = 0;
        gen_aa_key(lookup_key, base_addr);
        if (aarray_probe(cam, &lookup_key, &line_num, &way_num)) {
            CacheEntry& entry = ent_ref(line_num, way_num);
            if (entry.data_present()) {
                entry.coher_lockout();
            }
        }
    }

    CacheFillOutcome
    coher_yield(const LongAddr& base_addr, bool invalidate,
                bool bypass_wb_alloc) {
        AssocArrayKey lookup_key;
        long line_num = 0; int way_num = 0;
        bool block_dirty = false;
        assert_ifthen(!bypass_wb_alloc, !wb_buffer_full());
        if (!bypass_wb_alloc)
            wb_enqueue(base_addr, true);  // consume space to send an ack or WB
        gen_aa_key(lookup_key, base_addr);
        bool data_present = aarray_probe(cam, &lookup_key,
                                         &line_num, &way_num);
        CacheEntry& entry = ent_ref(line_num, way_num);
        // Note: even if the tag is present, the data may still be absent
        // (particularly if track_coher_misses is enabled)
        if (data_present && !entry.data_present())
            data_present = false;
        if (data_present) {
            if (entry.is_dirty()) {
                stats.coher_writebacks++;
                block_dirty = true;
            }
            if (invalidate) {
                stats.coher_invalidates++;
                // Optionally leave tag in place, for coher. miss detection;
                // provides some additional miss characterization, at the
                // cost of holding/matching a cache entry.
                if (!track_coher_misses)
                    aarray_invalidate(cam, line_num, way_num);
                entry.reset();
                pop_decrement(base_addr);
            } else {
                entry.set_state(CE_SharedClean);
                entry.coher_lockout_done();
            }
        }

        CacheFillOutcome outcome = CacheFill_NoEvict;
        if (data_present) {
            outcome = (block_dirty) ? CacheFill_EvictDirty :
                CacheFill_EvictClean;
        }
        return outcome;
    }

    i64 update_bank(const LongAddr& addr, i64 now, CacheBankOp bank_op) {
        int bank_num = block_bank_num(addr);
        CacheBank& bank = banks[bank_num];
        // is_write for port-selection purposes
        bool is_write = (bank_op != CacheBank_LookupR) &&
            (bank_op != CacheBank_LookupREx) &&
            (bank_op != CacheBank_LookupUpgrade) &&
            (bank_op != CacheBank_FillCont);
        bank.inc_stats(bank_op);
        OpTime op_time;
        get_op_time(op_time, bank_op);
        if ((bank_op == CacheBank_CoherPull) ||
            (bank_op == CacheBank_CoherSync)) {
            bank.sync_all_ports(now);
        }
        i64 ready_time = bank.bill_time(now, op_time, is_write);
        return ready_time;
    }

    void get_stats(CacheStats *dest) const {
        *dest = stats;
        dest->lookups = stats.hits + stats.misses +
            stats.upgrade_misses + stats.coher_busy;
    }

    void get_bankstats(i64 now, int bank_num, CacheBankStats *dest) const {
        // Utilization calc. doesn't account for R+W ports all that well
        const int read_ports = geom.ports.r + geom.ports.rw;
        const int write_ports = geom.ports.w + geom.ports.rw;
        const CacheBank& bank = banks.at(bank_num);
        bank.get_stats(dest);
        dest->util =
            ((double) timing.access_time.interval * dest->lookups_r +
             (double) timing.access_time.interval * dest->lookups_rex +
             (double) timing.access_time.interval * dest->lookups_upgrade +
             (double) timing.access_time.interval * dest->fillconts) 
            / read_ports +
            ((double) timing.access_time.interval * dest->lookups_w +
             (double) timing.access_time_wb.interval * dest->wbs +
             (double) timing.fill_time.interval * dest->fills +
             (double) timing.access_time_wb.interval * dest->coher_pulls)
            / write_ports;
        dest->util /= (now - stats_reset_cyc);
    }

    void align_addr(LongAddr& addr) const {
        addr.a = block_base_addr(addr.a);
    }

    int probebank_avail(const LongAddr& addr, i64 now, bool for_write)
        const {
        int bank_num = block_bank_num(addr);
        const CacheBank& bank = banks[bank_num];
        bool port_avail = bank.port_avail(now, for_write);
        return port_avail;
    }

    int get_population(int master_id) const {
        int result = 0;
        PopCountMap::const_iterator found = pop_count.find(master_id);
        if (found != pop_count.end())
            result = found->second;
        sim_assert(result >= 0);
        return result;
    }

    LongAddr *get_tags(int master_id, int *n_tags_ret) const;

    int get_id() const { return cache_id; }
    const CacheGeometry *get_geom(int *n_lines_ret, int *n_blocks_ret) const {
        if (n_lines_ret)
            *n_lines_ret = n_lines;
        if (n_blocks_ret)
            *n_blocks_ret = n_blocks;
        return &geom;
    }
};


CacheArray::CacheArray(int cache_id_, const CacheGeometry *geom_,
                       const CacheTiming *timing_,
                       CoherenceMgr *coher_, CoreResources *parent_core_,
                       i64 now)
    : cache_id(cache_id_), geom(*geom_), timing(*timing_), coher(coher_),
      parent_core(parent_core_),
      track_coher_misses(false), cam(0), wb_fifo_used(0), pop_total(0)
{
    int log_inexact;

    sim_assert(CacheEntryState_last <= (1 << CacheEntryState_bits));

    if ((geom.size_kb <= 0) || (geom.assoc <= 0) || (geom.block_bytes <= 0)
        || (geom.n_banks <= 0) || (geom.wb_buffer_size <= 0) ||
        (geom.ports.r < 0) || (geom.ports.w < 0) || (geom.ports.rw < 0)) {
        fprintf(stderr, "(%s:%i): bad geometry creating cache\n",
                __FILE__, __LINE__);
        goto fail;
    }

    if (((geom.ports.r + geom.ports.rw) <= 0) ||
        ((geom.ports.w + geom.ports.rw) <= 0)) {
        fprintf(stderr, "(%s:%i): bad port count, creating cache; "
                "need at least one readable and one writeable port.\n",
                __FILE__, __LINE__);
        goto fail;
    }

    config_base = string(geom.config_path);

    block_bytes_lg = floor_log2(geom.block_bytes, &log_inexact);
    if (log_inexact) {
        fprintf(stderr, "(%s:%i): block_bytes (%i) not a power of 2\n",
                __FILE__, __LINE__, geom.block_bytes);
        goto fail;
    }

    n_banks_lg = floor_log2(geom.n_banks, &log_inexact);
    if (log_inexact) {
        fprintf(stderr, "(%s:%i): n_banks (%i) not a power of 2\n",
                __FILE__, __LINE__, geom.n_banks);
        goto fail;
    }

    // #lines = bytes / (block size * assoc)
    // lg(#lines) = lg(bytes / assoc) - lg(block size)
    {
        long cache_bytes = geom.size_kb * 1024;
        long way_bytes = cache_bytes / geom.assoc;
        int way_bytes_lg;

        if (cache_bytes % geom.assoc != 0) {
            fprintf(stderr, "(%s:%i): assoc (%i) doesn't divide "
                    "cache size (%li)\n", __FILE__, __LINE__, geom.assoc,
                    cache_bytes);
            goto fail;
        }
        way_bytes_lg = floor_log2(way_bytes, &log_inexact);
        if (log_inexact) {
            fprintf(stderr, "(%s:%i): cache bytes / assoc (%li) not a "
                    "power of 2\n", __FILE__, __LINE__, way_bytes);
            goto fail;
        }
        if (way_bytes_lg < block_bytes_lg) {
            fprintf(stderr, "(%s:%i): total cache way size (%li) < "
                    "a single cache block (%i)\n", __FILE__,
                    __LINE__, way_bytes, geom.block_bytes);
            goto fail;
        }
        n_lines_lg = way_bytes_lg - block_bytes_lg;
        n_lines = 1 << n_lines_lg;
        n_blocks = n_lines * geom.assoc;
    }

    if (!(cam = aarray_create_simcfg(n_lines, geom.assoc, geom.config_path))) {
        fprintf(stderr, "(%s:%i): couldn't create AssocArray\n",
                __FILE__, __LINE__);
        goto fail;
    }

    entries.resize(n_lines * geom.assoc);
    
    for (int bnum = 0; bnum < geom.n_banks; bnum++)
        banks.push_back(CacheBank(geom.ports.r, geom.ports.w, geom.ports.rw));

    {
        string key = config_base + "/" + "track_coher_misses";
        if (simcfg_have_val(key.c_str()))
            track_coher_misses = simcfg_get_bool(key.c_str());
    }

    if (coher)
        cm_add_cache(coher, this, cache_id, parent_core_);

    zero_op_time.latency = 0;
    zero_op_time.interval = 0;

    reset(now);
    return;

fail:
    fprintf(stderr, "(%s:%i): ugh, CacheArray created failed, and we don't "
            "have exceptions.  :(\n", __FILE__, __LINE__);
    sim_abort();
}


CacheArray::~CacheArray()
{
    if (cam)
        aarray_destroy(cam);
}


void
CacheArray::reset(i64 now)
{
    if (coher)
        cm_reset_cache(coher, cache_id);
    aarray_reset(cam);
    {
        vector<CacheEntry>::iterator iter = entries.begin(),
            end = entries.end();
        for (; iter != end; ++iter)
            iter->reset();
    }
    {
        vector<CacheBank>::iterator iter = banks.begin(), end = banks.end();
        for (; iter != end; ++iter)
            iter->reset();
    }
    pop_reset();
    reset_stats(now);
}


void
CacheArray::reset_stats(i64 now)
{
    stats_reset_cyc = now;
    {
        vector<CacheBank>::iterator iter = banks.begin(), end = banks.end();
        for (; iter != end; ++iter)
            iter->reset_stats();
    }
    stats.lookups = 0;
    stats.hits = stats.misses = stats.upgrade_misses = stats.coher_busy = 0;
    stats.coher_misses = 0;
    stats.reads = stats.reads_ex = stats.writes = 0;
    stats.dirty_evicts = 0;
    stats.coher_writebacks = stats.coher_invalidates = 0;
    stats.wbfull_confs = 0;
}


LongAddr *
CacheArray::get_tags(int master_id, int *n_tags_ret) const
{
    vector<LongAddr> matches;
    for (long line_num = 0; line_num < n_lines; line_num++) {
        for (int way_num = 0; way_num < geom.assoc; way_num++) {
            AssocArrayKey ent_key;
            if (aarray_readkey(cam, line_num, way_num, &ent_key)) {
                const CacheEntry& entry = ent_ref(line_num, way_num);
                if (entry.data_present()) {
                    LongAddr ent_addr;
                    reverse_aa_key(ent_addr, ent_key);
                    if ((master_id == -1) || (master_id == int(ent_addr.id))) {
                        matches.push_back(ent_addr);
                    }
                }
            }
        }
    }

    LongAddr *result = NULL;
    int n_tags = int(matches.size());
    if (!matches.empty()) {
        result = static_cast<LongAddr *>(emalloc(n_tags * sizeof(result[0])));
        for (int i = 0; i < n_tags; i++) {
            result[i] = matches[i];
        }
    }
    *n_tags_ret = n_tags;
    return result;
}



//
// C interface
//

CacheArray *
cache_create(int cache_id, const CacheGeometry *geom,
             const CacheTiming *timing,
             struct CoherenceMgr *cm, struct CoreResources *parent_core,
             i64 now)
{
    return new CacheArray(cache_id, geom, timing, cm, parent_core, now);
}

void
cache_destroy(CacheArray *cache)
{
    if (cache)
        delete cache;
}

void
cache_reset(CacheArray *cache, i64 now)
{
    cache->reset(now);
}

void
cache_reset_stats(CacheArray *cache, i64 now)
{
    cache->reset_stats(now);
}

CacheLOutcome
cache_lookup(CacheArray *cache, LongAddr addr,
             CacheAccessType access_type, int *first_access_ret)
{
    return cache->lookup(addr, access_type, first_access_ret);
}

int
cache_access_ok(const CacheArray *cache, LongAddr addr,
                CacheAccessType access_type)
{
    return cache->access_ok(addr, access_type);
}

int
cache_touch(CacheArray *cache, LongAddr addr)
{
    return cache->touch(addr);
}

int
cache_wb_buffer_full(const CacheArray *cache)
{
    return cache->wb_buffer_full();
}

void
cache_log_wbfull_conflict(CacheArray *cache)
{
    cache->log_wbfull_conflict();
}

CacheFillOutcome
cache_fill(CacheArray *cache, LongAddr addr,
           CacheAccessType access_type, CacheEvicted *evicted_ret)
{
    return cache->fill(addr, access_type, evicted_ret);
}

int
cache_writeback(CacheArray *cache, LongAddr addr)
{
    return cache->writeback(addr);
}   

void 
cache_mark_dirty(CacheArray *cache, LongAddr addr)
{
    return cache->mark_dirty(addr);
}

void
cache_mark_writeable(CacheArray *cache, LongAddr addr)
{
    return cache->mark_writeable(addr);
}

int
cache_wb_accepted(CacheArray *cache, LongAddr base_addr)
{
    return cache->wb_accepted(base_addr);
}

void
cache_coher_lockout(CacheArray *cache, LongAddr base_addr)
{
    cache->coher_lockout(base_addr);
}

CacheFillOutcome
cache_coher_yield(CacheArray *cache, LongAddr base_addr,
                  int invalidate, int bypass_wb_alloc)
{
    return cache->coher_yield(base_addr, invalidate, bypass_wb_alloc);
}

i64
cache_update_bank(CacheArray *cache, LongAddr addr, i64 now,
                  CacheBankOp bank_op)
{
    return cache->update_bank(addr, now, bank_op);
}

void 
cache_get_stats(const CacheArray *cache, CacheStats *dest)
{
    cache->get_stats(dest);
}

void 
cache_get_bankstats(const CacheArray *cache, i64 now, int bank,
                    CacheBankStats *dest)
{
    cache->get_bankstats(now, bank, dest);
}

void
cache_align_addr(const CacheArray *cache, LongAddr *addr)
{
    return cache->align_addr(*addr);
}

int
cache_probebank_avail(const CacheArray *cache, LongAddr addr,
                  i64 now, int for_write)
{
    return cache->probebank_avail(addr, now, for_write);
}

int
cache_get_population(const CacheArray *cache, int master_id)
{
    return cache->get_population(master_id);
}

LongAddr *
cache_get_tags(const CacheArray *cache, int master_id,
               int *n_tags_ret)
{
    return cache->get_tags(master_id, n_tags_ret);
}

int
cache_get_id(const CacheArray *cache)
{
    return cache->get_id();
}

const CacheGeometry *
cache_get_geom(const CacheArray *cache,
               int *n_lines_ret, int *n_blocks_ret)
{
    return cache->get_geom(n_lines_ret, n_blocks_ret);
}



//
// CacheGeometry helper functions
//
CacheGeometry *
cachegeom_create(void)
{
    CacheGeometry *result = new CacheGeometry;
    memset(result, 0, sizeof(*result));
    return result;
}

CacheGeometry *
cachegeom_copy(const CacheGeometry *cg)
{
    CacheGeometry *result = new CacheGeometry;
    *result = *cg;
    if (cg->config_path)
        result->config_path = e_strdup(cg->config_path);
    return result;    
}

void
cachegeom_destroy(CacheGeometry *cg)
{
    if (cg) {
        free(cg->config_path);
        free(cg);
    }
}
