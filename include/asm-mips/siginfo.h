/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1998, 1999, 2001, 2003 Ralf Baechle
 * Copyright (C) 2000, 2001 Silicon Graphics, Inc.
 */
#ifndef _ASM_SIGINFO_H
#define _ASM_SIGINFO_H


#define SIGEV_HEAD_SIZE	(sizeof(long) + 2*sizeof(int))
#define SIGEV_PAD_SIZE	((SIGEV_MAX_SIZE-SIGEV_HEAD_SIZE) / sizeof(int))
#define SI_PAD_SIZE	((SI_MAX_SIZE/sizeof(int)) - 4)

#define HAVE_ARCH_SIGINFO_T

/*
 * We duplicate the generic versions - <linux/siginfo.h> is just borked
 * by design ...
 */
#define HAVE_ARCH_COPY_SIGINFO
struct siginfo;

#include <linux/siginfo.h>

/* This structure matches the 32/n32 ABIs for source compatibility but
   has Linux extensions.  */

typedef struct siginfo {
	int si_signo;
	int si_code;
	int si_errno;

	union {
		int _pad[SI_PAD_SIZE];

		/* kill() */
		struct {
			pid_t _pid;		/* sender's pid */
			uid_t _uid;		/* sender's uid */
		} _kill;

		/* SIGCHLD */
		struct {
			pid_t _pid;		/* which child */
			uid_t _uid;		/* sender's uid */
			int _status;		/* exit code */
			clock_t _utime;
			clock_t _stime;
		} _sigchld;

		/* IRIX SIGCHLD */
		struct {
			pid_t _pid;		/* which child */
			clock_t _utime;
			int _status;		/* exit code */
			clock_t _stime;
		} _irix_sigchld;

		/* SIGILL, SIGFPE, SIGSEGV, SIGBUS */
		struct {
			void *_addr; /* faulting insn/memory ref. */
		} _sigfault;

		/* SIGPOLL, SIGXFSZ (To do ...)  */
		struct {
#ifdef CONFIG_MIPS32
			int _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
#endif
#ifdef CONFIG_MIPS64
			long _band;	/* POLL_IN, POLL_OUT, POLL_MSG */
#endif
			int _fd;
		} _sigpoll;

		/* POSIX.1b timers */
		struct {
			timer_t _tid;		/* timer id */
			int _overrun;		/* overrun count */
			char _pad[sizeof( __ARCH_SI_UID_T) - sizeof(int)];
			sigval_t _sigval;	/* same as below */
			int _sys_private;	/* not to be passed to user */
		} _timer;

		/* POSIX.1b signals */
		struct {
			pid_t _pid;		/* sender's pid */
			uid_t _uid;		/* sender's uid */
			sigval_t _sigval;
		} _rt;

	} _sifields;
} siginfo_t;

/*
 * si_code values
 * Again these have been choosen to be IRIX compatible.
 */
#undef SI_ASYNCIO
#undef SI_TIMER
#undef SI_MESGQ
#define SI_ASYNCIO	-2	/* sent by AIO completion */
#define SI_TIMER __SI_CODE(__SI_TIMER,-3) /* sent by timer expiration */
#define SI_MESGQ __SI_CODE(__SI_MESGQ,-4) /* sent by real time mesq state change */


#endif /* _ASM_SIGINFO_H */
