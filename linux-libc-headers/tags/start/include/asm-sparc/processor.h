/* $Id: processor.h,v 1.1 2003/12/15 18:47:00 mmazur Exp $
 * include/asm-sparc/processor.h
 *
 * Copyright (C) 1994 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef __ASM_SPARC_PROCESSOR_H
#define __ASM_SPARC_PROCESSOR_H

/*
 * Sparc32 implementation of macro that returns current
 * instruction pointer ("program counter").
 */
#define current_text_addr() ({ void *pc; __asm__("sethi %%hi(1f), %0; or %0, %%lo(1f), %0;\n1:" : "=r" (pc)); pc; })

#include <linux/a.out.h>

#include <asm/psr.h>
#include <asm/ptrace.h>
#include <asm/head.h>
#include <asm/signal.h>
#include <asm/segment.h>
#include <asm/btfixup.h>
#include <asm/page.h>
#include <asm/atomic.h>

/*
 * Bus types
 */
#define MCA_bus 0
#define MCA_bus__is_a_macro /* for versions in ksyms.c */

/*
 * The sparc has no problems with write protection
 */
#define wp_works_ok 1
#define wp_works_ok__is_a_macro /* for versions in ksyms.c */

/* Whee, this is STACK_TOP + PAGE_SIZE and the lowest kernel address too... 
 * That one page is used to protect kernel from intruders, so that
 * we can make our access_ok test faster
 */
#define TASK_SIZE	PAGE_OFFSET

struct task_struct;

struct fpq {
	unsigned long *insn_addr;
	unsigned long insn;
};

typedef struct {
	int seg;
} mm_segment_t;

/* The Sparc processor specific thread struct. */
struct thread_struct {
	struct pt_regs *kregs;

	/* Special child fork kpsr/kwim values. */
	unsigned long fork_kpsr __attribute__ ((aligned (8)));
	unsigned long fork_kwim;

	/* A place to store user windows and stack pointers
	 * when the stack needs inspection.
	 */
#define NSWINS 8
	struct reg_window reg_window[NSWINS] __attribute__ ((aligned (8)));
	unsigned long rwbuf_stkptrs[NSWINS] __attribute__ ((aligned (8)));
	unsigned long w_saved;

	/* Floating point regs */
	unsigned long   float_regs[32] __attribute__ ((aligned (8)));
	unsigned long   fsr;
	unsigned long   fpqdepth;
	struct fpq	fpqueue[16];
	unsigned long flags;
	mm_segment_t current_ds;
	struct exec core_exec;     /* just what it says. */
	int new_signal;
	atomic_t refcount;	/* used for sun4c only */
};

#define SPARC_FLAG_KTHREAD      0x1    /* task is a kernel thread */
#define SPARC_FLAG_UNALIGNED    0x2    /* is allowed to do unaligned accesses */

#define INIT_THREAD  { \
/* kregs, */ \
   0,  \
/* fork_kpsr, fork_kwim */ \
   0,         0, \
/* reg_window */  \
{ { { 0, }, { 0, } }, }, \
/* rwbuf_stkptrs */  \
{ 0, 0, 0, 0, 0, 0, 0, 0, }, \
/* w_saved */ \
   0, \
/* FPU regs */   { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
                   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }, \
/* FPU status, FPU qdepth, FPU queue */ \
   0,          0,  { { 0, 0, }, }, \
/* flags,              current_ds, */ \
   SPARC_FLAG_KTHREAD, KERNEL_DS, \
/* core_exec */ \
{ 0, }, \
/* new_signal */ \
  0, \
}

/* Return saved PC of a blocked thread. */
extern unsigned long thread_saved_pc(struct task_struct *t);

/* Do necessary setup to start up a newly executed thread. */
extern __inline__ void start_thread(struct pt_regs * regs, unsigned long pc,
				    unsigned long sp)
{
	register unsigned long zero asm("g1");

	regs->psr = (regs->psr & (PSR_CWP)) | PSR_S;
	regs->pc = ((pc & (~3)) - 4);
	regs->npc = regs->pc + 4;
	regs->y = 0;
	zero = 0;
	__asm__ __volatile__("std\t%%g0, [%0 + %3 + 0x00]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x08]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x10]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x18]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x20]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x28]\n\t"
			     "std\t%%g0, [%0 + %3 + 0x30]\n\t"
			     "st\t%1, [%0 + %3 + 0x38]\n\t"
			     "st\t%%g0, [%0 + %3 + 0x3c]"
			     : : "r" (regs), "r" (sp - sizeof(struct reg_window)), "r" (zero),
			     "i" ((const unsigned long)(&((struct pt_regs *)0)->u_regs[0])));
}

/* Free all resources held by a thread. */
#define release_thread(tsk)		do { } while(0)
extern pid_t kernel_thread(int (*fn)(void *), void * arg, unsigned long flags);

/* Prepare to copy thread state - unlazy all lazy status */
#define prepare_to_copy(tsk)	do { } while (0)

extern unsigned long get_wchan(struct task_struct *);

#define KSTK_EIP(tsk)  ((tsk)->thread.kregs->pc)
#define KSTK_ESP(tsk)  ((tsk)->thread.kregs->u_regs[UREG_FP])

#ifdef __KERNEL__

extern struct task_struct *last_task_used_math;

#define cpu_relax()	barrier()

#endif

#endif /* __ASM_SPARC_PROCESSOR_H */