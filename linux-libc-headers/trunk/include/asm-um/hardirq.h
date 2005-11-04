/* (c) 2004 cw@f00f.org, GPLv2 blah blah */

#ifndef __ASM_UM_HARDIRQ_H
#define __ASM_UM_HARDIRQ_H

#include <linux/threads.h>
#include <linux/irq.h>

/* NOTE: When SMP works again we might want to make this
 * ____cacheline_aligned or maybe use per_cpu state? --cw */
typedef struct {
	unsigned int __softirq_pending;
} irq_cpustat_t;

#include <linux/irq_cpustat.h>

#endif /* __ASM_UM_HARDIRQ_H */
