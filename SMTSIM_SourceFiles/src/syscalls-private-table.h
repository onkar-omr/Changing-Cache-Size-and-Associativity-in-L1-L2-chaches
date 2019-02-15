/* SMTSIM simulator.
   
   Copyright (C) 1994-1999 by Dean Tullsen (tullsen@cs.ucsd.edu)
   ALL RIGHTS RESERVED.

   SMTSIM is distributed under the following conditions:

     You may make copies of SMTSIM for your own use and modify those copies.

     All copies of SMTSIM must retain all copyright notices contained within.

     You may not sell SMTSIM or distribute SMTSIM in conjunction with a
     commerical product or service without the express written consent of
     Dean Tullsen.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.

Significant parts of the SMTSIM simulator were written by Gun Sirer
(before it became the SMTSIM simulator) and by Jack Lo (after it became
the SMTSIM simulator).  Therefore the following copyrights may also apply:

Copyright (C) Jack Lo
Copyright (C) E. Gun Sirer

Pieces of this code may have been derived from Jim Larus\' SPIM simulator,
which contains the following copyright:

==============================================================
   Copyright (C) 1990-1998 by James Larus (larus@cs.wisc.edu).
   ALL RIGHTS RESERVED.

   SPIM is distributed under the following conditions:

     You may make copies of SPIM for your own use and modify those copies.

     All copies of SPIM must retain my name and copyright notice.

     You may not sell SPIM or distributed SPIM in conjunction with a
     commerical product or service without the expressed written consent of
     James Larus.

   THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
   IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
   PURPOSE.
===============================================================
 */


{ a_SYS_syscall,        SPC_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG}, "syscall"},
{ a_SYS_exit,   SPC_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "exit"},
{ a_SYS_fork,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "fork"},
{ a_SYS_read,   UNIX_SYSCALL, { FD_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "read"},
{ a_SYS_write,  UNIX_SYSCALL, { FD_ARG, ADDR_R_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "write"},
{ a_SYS_old_open,       SPC_SYSCALL, { PATH_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_open"},
{ a_SYS_close,  UNIX_SYSCALL, { FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "close"},
{ 7,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_old_creat,      SPC_SYSCALL, { PATH_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_creat"},
{ a_SYS_link,   UNIX_SYSCALL, { PATH_ARG, PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "link"},
{ a_SYS_unlink, UNIX_SYSCALL, { PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "unlink"},
{ a_SYS_execv,  BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "execv"},
{ a_SYS_chdir,  UNIX_SYSCALL, { PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "chdir"},
{ 13,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_mknod,  UNIX_SYSCALL, { PATH_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "mknod"},
{ a_SYS_chmod,  UNIX_SYSCALL, { PATH_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "chmod"},
{ a_SYS_chown,  UNIX_SYSCALL, { PATH_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "chown"},
{ a_SYS_obreak, SPC_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "obreak"},
{ 18,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_lseek,  UNIX_SYSCALL, { FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "lseek"},
{ a_SYS_getpid, UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getpid"},
{ a_SYS_mount,  BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "mount"},
{ 22,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 23,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getuid, UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getuid"},
{ 25,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_ptrace, UNIX_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG}, "ptrace"},
{ 27,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 28,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 29,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 30,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 31,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 32,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_access, UNIX_SYSCALL, { PATH_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "access"},
{ 34,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 35,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_sync,   UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sync"},
{ a_SYS_kill,   UNIX_SYSCALL, { INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "kill"},
{ a_SYS_old_stat,       SPC_SYSCALL, { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_stat"},
{ 39,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_old_lstat,      SPC_SYSCALL, { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_lstat"},
{ a_SYS_dup,    SPC_SYSCALL, { FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "dup"},
{ a_SYS_pipe,   UNIX_SYSCALL, { ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "pipe"},
{ 43,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_profil, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "profil"},
{ a_SYS_open,   UNIX_SYSCALL, { PATH_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "open"},
{ 46,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getgid, UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getgid"},
{ a_SYS_sigprocmask,    SPC_SYSCALL, { INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sigprocmask"},
{ 49,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 50,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_acct,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "acct"},
{ a_SYS_sigpending,     BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "sigpending"},
{ 53,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_ioctl,  SPC_SYSCALL, { FD_ARG, INT_ARG, ADDR_RW_ARG, NO_ARG, NO_ARG, NO_ARG}, "ioctl"},
{ a_SYS_reboot, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "reboot"},
{ 56,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_symlink,        UNIX_SYSCALL, { PATH_ARG, PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "symlink"},
{ a_SYS_readlink,       UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "readlink"},
{ a_SYS_execve, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "execve"},
{ a_SYS_umask,  UNIX_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "umask"},
{ a_SYS_chroot, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "chroot"},
{ a_SYS_old_fstat,      SPC_SYSCALL, { FD_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_fstat"},
{ 63,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getpagesize,    SPC_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getpagesize"},
{ a_SYS_mremap, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "mremap"},
{ a_SYS_vfork,  BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "vfork"},
{ a_SYS_stat,   UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "stat"},
{ a_SYS_lstat,  UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "lstat"},
{ a_SYS_sbrk,   SPC_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sbrk"},
{ a_SYS_sstk,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sstk"},
{ a_SYS_mmap,   UNIX_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG}, "mmap"},
{ 72,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_munmap, UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "munmap"},
{ a_SYS_mprotect,       UNIX_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "mprotect"},
{ a_SYS_madvise,        BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "madvise"},
{ a_SYS_old_vhangup,    BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_vhangup"},
{ 77,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_mincore,        BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "mincore"},
{ a_SYS_getgroups,      UNIX_SYSCALL, { INT_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getgroups"},
{ a_SYS_setgroups,      BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setgroups"},
{ a_SYS_old_getpgrp,    UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_getpgrp"},
{ a_SYS_setpgrp,        UNIX_SYSCALL, { INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setpgrp"},
{ a_SYS_setitimer,      SPC_SYSCALL, { INT_ARG, ADDR_R_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "setitimer"},
{ a_SYS_old_wait,       BAD_SYSCALL, { ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_wait"},
{ a_SYS_table,          SPC_SYSCALL, { INT_ARG, INT_ARG, ADDR_RW_ARG, INT_ARG, INT_ARG, NO_ARG}, "table"},
{ a_SYS_getitimer,      UNIX_SYSCALL, { INT_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getitimer"},
{ a_SYS_gethostname,    UNIX_SYSCALL, { ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "gethostname"},
{ a_SYS_sethostname,    BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sethostname"},
{ a_SYS_getdtablesize,  UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getdtablesize"},
{ a_SYS_dup2,   SPC_SYSCALL, { FD_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "dup2"},
{ a_SYS_fstat,  UNIX_SYSCALL, { FD_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "fstat"},
{ a_SYS_fcntl,  UNIX_SYSCALL, { FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "fcntl"},
{ a_SYS_select, SPC_SYSCALL, { INT_ARG, ADDR_RW_ARG, ADDR_RW_ARG, ADDR_RW_ARG, ADDR_RW_ARG, NO_ARG}, "select"},
{ 94,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_fsync,  UNIX_SYSCALL, { FD_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "fsync"},
{ a_SYS_setpriority,    BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setpriority"},
{ a_SYS_socket, SPC_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "socket"},
{ a_SYS_connect,        BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "connect"},
{ a_SYS_old_accept,     BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_accept"},
{ a_SYS_getpriority,    BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getpriority"},
{ a_SYS_old_send,       BAD_SYSCALL, { INT_ARG, ADDR_R_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG}, "old_send"},
{ a_SYS_old_recv,       BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG}, "old_recv"},
{ a_SYS_sigreturn,      SPC_SYSCALL, { ADDR_RW_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sigreturn"},
{ a_SYS_bind,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "bind"},
{ a_SYS_setsockopt,     BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setsockopt"},
{ a_SYS_listen, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "listen"},
{ a_SYS_plock,  BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "plock"},
{ a_SYS_old_sigvec,     SPC_SYSCALL, { INT_ARG, ADDR_R_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_sigvec"},
{ a_SYS_old_sigblock,   SPC_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_sigblock"},
{ a_SYS_old_sigsetmask, SPC_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_sigsetmask"},
{ 111,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_sigstack,       SPC_SYSCALL, { ADDR_R_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sigstack"},
{ a_SYS_old_recvmsg,    BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_recvmsg"},
{ a_SYS_old_sendmsg,    BAD_SYSCALL, { INT_ARG, ADDR_R_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_sendmsg"},
{ 115,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_gettimeofday,   UNIX_SYSCALL, { ADDR_W_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "gettimeofday"},
{ a_SYS_getrusage,      UNIX_SYSCALL, { INT_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getrusage"},
{ a_SYS_getsockopt,     BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getsockopt"},
{ 119,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_readv,  UNIX_SYSCALL, { FD_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "readv"},
{ a_SYS_writev, UNIX_SYSCALL, { FD_ARG, ADDR_R_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "writev"},
{ a_SYS_settimeofday,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "settimeofday"},
{ a_SYS_fchown, UNIX_SYSCALL, { FD_ARG, INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "fchown"},
{ a_SYS_fchmod, UNIX_SYSCALL, { FD_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "fchmod"},
{ a_SYS_old_recvfrom,   BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, INT_ARG, INT_ARG, ADDR_W_ARG, ADDR_W_ARG}, "old_recvfrom"},
{ a_SYS_setreuid,       BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setreuid"},
{ a_SYS_setregid,       BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setregid"},
{ a_SYS_rename, UNIX_SYSCALL, { PATH_ARG, PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "rename"},
{ a_SYS_truncate,       UNIX_SYSCALL, { PATH_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "truncate"},
{ a_SYS_ftruncate,      UNIX_SYSCALL, { FD_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "ftruncate"},
{ a_SYS_flock,  BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "flock"},
{ 132,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_sendto, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sendto"},
{ a_SYS_shutdown,       BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "shutdown"},
{ a_SYS_socketpair,     BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "socketpair"},
{ a_SYS_mkdir,  UNIX_SYSCALL, { PATH_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "mkdir"},
{ a_SYS_rmdir,  UNIX_SYSCALL, { PATH_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "rmdir"},
{ a_SYS_utimes, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "utimes"},
{ 139,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_adjtime,        BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "adjtime"},
{ a_SYS_old_getpeername,        BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_getpeername"},
{ a_SYS_gethostid,      BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "gethostid"},
{ a_SYS_sethostid,      BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "sethostid"},
{ a_SYS_getrlimit,      SPC_SYSCALL, { INT_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getrlimit"},
{ a_SYS_setrlimit,      SPC_SYSCALL, { INT_ARG, ADDR_R_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setrlimit"},
{ a_SYS_old_killpg,     UNIX_SYSCALL, { INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_killpg"},
{ a_SYS_setsid, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "setsid"},
{ 148,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_oldquota,       BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "oldquota"},
{ a_SYS_old_getsockname,        BAD_SYSCALL, { INT_ARG, ADDR_W_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "old_getsockname"},
{ 151,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 152,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 153,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 154,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 155,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_sigaction,      SPC_SYSCALL, { INT_ARG, ADDR_R_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG}, "sigaction"},
{ 157,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 158,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getdirentries,  UNIX_SYSCALL, { FD_ARG, ADDR_W_ARG, INT_ARG, ADDR_RW_ARG, NO_ARG, NO_ARG}, "getdirentries"},
{ a_SYS_statfs,   UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "statfs"},
{ 161,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 162,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 163,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 164,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getdomainname,  UNIX_SYSCALL, { ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getdomainname"},
{ a_SYS_setdomainname,  BAD_SYSCALL, { ADDR_R_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "setdomainname"},
{ 167,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 168,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_exportfs,       BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "exportfs"},
{ 170,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 171,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 172,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 173,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 174,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 175,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 176,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 177,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 178,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 179,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 180,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 181,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 182,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 183,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getmnt, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "getmnt"},
{ 185,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 186,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 187,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 188,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 189,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 190,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 191,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 192,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 193,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 194,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 195,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 196,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 197,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 198,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_swapon, BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "swapon"},
{ a_SYS_msgctl, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "msgctl"},
{ a_SYS_msgget, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "msgget"},
{ a_SYS_msgrcv, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "msgrcv"},
{ a_SYS_msgsnd, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "msgsnd"},
{ a_SYS_semctl, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "semctl"},
{ a_SYS_semget, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "semget"},
{ a_SYS_semop,  BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "semop"},
{ a_SYS_uname,  UNIX_SYSCALL, { ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "uname"},
{ 208,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 209,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 210,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 211,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 212,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 213,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 214,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 215,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 216,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 217,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 218,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_utc_gettime,    BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "utc_gettime"},
{ a_SYS_utc_adjtime,    BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "utc_adjtime"},
{ 221,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 222,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 223,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_new_stat,   UNIX_SYSCALL,  { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG},  "stat"},
{ a_SYS_new_lstat,  UNIX_SYSCALL,  { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG},  "lstat"},
{ a_SYS_new_fstat,  UNIX_SYSCALL,  { FD_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG},    "fstat"},
{ a_SYS_new_statfs, UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG}, "statfs"},
{ 228,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 229,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 230,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 231,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 232,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 233,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 234,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 235,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 236,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 237,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 238,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 239,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 240,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 241,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 242,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 243,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 244,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 245,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 246,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 247,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 248,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 249,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_uswitch,        UNIX_SYSCALL, { INT_ARG, INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "uswitch"},
{ 251,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_audcntl,        BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "audcntl"},
{ a_SYS_audgen, BAD_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, NO_ARG}, "audgen"},
{ 254,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 255,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ a_SYS_getsysinfo,     UNIX_SYSCALL, { INT_ARG, ADDR_W_ARG, INT_ARG, ADDR_RW_ARG, ADDR_RW_ARG, ADDR_RW_ARG}, "getsysinfo"},
{ a_SYS_setsysinfo,     UNIX_SYSCALL, { INT_ARG, ADDR_R_ARG, INT_ARG, ADDR_RW_ARG, ADDR_RW_ARG, NO_ARG}, "setsysinfo"},
{ 258,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 259,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 260,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 261,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 262,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 263,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 264,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 265,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 266,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 267,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 268,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 269,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 270,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 271,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 272,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 273,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 274,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 275,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 276,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 277,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 278,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 279,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 280,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 281,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 282,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 283,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 284,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 285,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 286,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 287,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 288,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 289,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 290,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 291,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 292,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 293,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 294,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 295,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 296,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 297,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 298,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 299,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 300,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 301,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 302,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 303,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 304,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 305,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 306,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 307,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 308,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 309,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 310,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 311,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 312,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 313,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 314,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 315,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 316,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 317,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 318,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 319,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 320,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 321,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 322,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_times,   UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "linux_times"},
{ 324,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 325,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 326,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 327,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 328,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 329,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 330,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 331,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 332,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 333,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 334,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 335,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 336,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 337,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 338,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_alpha_uname,  UNIX_SYSCALL, { ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "uname"},
{ 340,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_mremap,       UNIX_SYSCALL, { INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG, INT_ARG}, "linux_mremap"},
{ 342,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 343,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 344,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 345,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 346,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 347,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 348,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 349,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 350,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 351,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ rt_sigaction,   UNIX_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "rt_sigaction"},
{ 353,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 354,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 355,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 356,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 357,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 358,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_gettimeofday,   UNIX_SYSCALL,{ ADDR_W_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "linux_gettimeofday"},
{ 360,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 361,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 362,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 363,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_getrusage,   UNIX_SYSCALL, { INT_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "getrusage"},
{ 365,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 366,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 367,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 368,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 369,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 370,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 371,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 372,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 373,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 374,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 375,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 376,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 377,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 378,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 379,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 380,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 381,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 382,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 383,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 384,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 385,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 386,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 387,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 388,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 389,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 390,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 391,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 392,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 393,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 394,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 395,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 396,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 397,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 398,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 399,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 400,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 401,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 402,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 403,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 404,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_exit_group,   UNIX_SYSCALL, { INT_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "exit"},
{ 406,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 407,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 408,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 409,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 410,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 411,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 412,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 413,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 414,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 415,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 416,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 417,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 418,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 419,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 420,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 421,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 422,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 423,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 424,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_alpha_stat64,   UNIX_SYSCALL, { PATH_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "stat64"},
{ 426,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ linux_alpha_fstat64, UNIX_SYSCALL,{ FD_ARG, ADDR_W_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, "fstat64"},
{ 428,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 429,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 430,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 431,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 432,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 433,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 434,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 435,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 436,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 437,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},
{ 438,   BAD_SYSCALL, { NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG, NO_ARG}, ""},