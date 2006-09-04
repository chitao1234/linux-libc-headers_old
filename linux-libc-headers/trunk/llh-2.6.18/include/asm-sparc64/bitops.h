/* $Id: bitops.h,v 1.39 2002/01/30 01:40:00 davem Exp $
 * bitops.h: Bit string operations on the V9.
 *
 * Copyright 1996, 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _SPARC64_BITOPS_H
#define _SPARC64_BITOPS_H

#include <linux/compiler.h>
#include <asm/byteorder.h>

extern int test_and_set_bit(unsigned long nr, volatile unsigned long *addr);
extern int test_and_clear_bit(unsigned long nr, volatile unsigned long *addr);
extern int test_and_change_bit(unsigned long nr, volatile unsigned long *addr);
extern void set_bit(unsigned long nr, volatile unsigned long *addr);
extern void clear_bit(unsigned long nr, volatile unsigned long *addr);
extern void change_bit(unsigned long nr, volatile unsigned long *addr);

#include <asm-generic/bitops/non-atomic.h>

#ifdef CONFIG_SMP
#define smp_mb__before_clear_bit()	membar_storeload_loadload()
#define smp_mb__after_clear_bit()	membar_storeload_storestore()
#else
#define smp_mb__before_clear_bit()	barrier()
#define smp_mb__after_clear_bit()	barrier()
#endif

#include <asm-generic/bitops/ffz.h>
#include <asm-generic/bitops/__ffs.h>
#include <asm-generic/bitops/fls.h>
#include <asm-generic/bitops/fls64.h>

#include <asm-generic/bitops/find.h>

#endif /* defined(_SPARC64_BITOPS_H) */
