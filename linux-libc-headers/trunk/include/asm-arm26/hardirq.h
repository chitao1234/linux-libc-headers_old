#ifndef __ASM_HARDIRQ_H
#define __ASM_HARDIRQ_H

#include <linux/cache.h>
#include <linux/threads.h>

typedef struct {
	unsigned int __softirq_pending;
	unsigned int __local_irq_count;
	unsigned int __local_bh_count;
	unsigned int __syscall_count;
	struct task_struct * __ksoftirqd_task; /* waitqueue is too large */
} ____cacheline_aligned irq_cpustat_t;

#include <linux/irq_cpustat.h>	/* Standard mappings for irq_cpustat_t above */

#define HARDIRQ_BITS	8

/*
 * The hardirq mask has to be large enough to have space
 * for potentially all IRQ sources in the system nesting
 * on a single CPU:
 */
#if (1 << HARDIRQ_BITS) < NR_IRQS
# error HARDIRQ_BITS is too low!
#endif

#define irq_enter()		(preempt_count() += HARDIRQ_OFFSET)

#ifndef CONFIG_SMP
#define irq_exit()							\
	do {								\
		preempt_count() -= HARDIRQ_OFFSET;			\
		if (!in_interrupt() && softirq_pending(smp_processor_id())) \
			__asm__("bl%? __do_softirq": : : "lr");/* out of line */\
		preempt_enable_no_resched();				\
	} while (0)

#endif

#endif /* __ASM_HARDIRQ_H */
