/*
 * include/asm-v850/atomic.h -- Atomic operations
 *
 *  Copyright (C) 2001,02  NEC Corporation
 *  Copyright (C) 2001,02  Miles Bader <miles@gnu.org>
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file COPYING in the main directory of this
 * archive for more details.
 *
 * Written by Miles Bader <miles@gnu.org>
 */

#ifndef __V850_ATOMIC_H__
#define __V850_ATOMIC_H__


#include <asm/system.h>

#ifdef CONFIG_SMP
#error SMP not supported
#endif

typedef struct { int counter; } atomic_t;

#define ATOMIC_INIT(i)	{ (i) }

#define atomic_add(i, v)	atomic_add_return ((i), (v))
#define atomic_sub(i, v)	atomic_sub_return ((i), (v))

#define atomic_dec_return(v)	atomic_sub_return (1, (v))
#define atomic_inc_return(v)	atomic_add_return (1, (v))
#define atomic_inc(v) 		atomic_inc_return (v)
#define atomic_dec(v) 		atomic_dec_return (v)

#define atomic_sub_and_test(i,v)	(atomic_sub_return ((i), (v)) == 0)
#define atomic_dec_and_test(v)		(atomic_sub_return (1, (v)) == 0)
#define atomic_add_negative(i,v)	(atomic_add_return ((i), (v)) < 0)

/* Atomic operations are already serializing on ARM */
#define smp_mb__before_atomic_dec()	barrier()
#define smp_mb__after_atomic_dec()	barrier()
#define smp_mb__before_atomic_inc()	barrier()
#define smp_mb__after_atomic_inc()	barrier()

#endif /* __V850_ATOMIC_H__ */