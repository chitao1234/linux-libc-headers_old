#ifndef _PPC64_PAGE_H
#define _PPC64_PAGE_H

/*
 * Copyright (C) 2001 PPC64 Team, IBM Corp
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */


#ifdef __ASSEMBLY__
  #define ASM_CONST(x) x
#else
  #define __ASM_CONST(x) x##UL
  #define ASM_CONST(x) __ASM_CONST(x)
#endif

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	12
#define PAGE_SIZE	(ASM_CONST(1) << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))
#define PAGE_OFFSET_MASK (PAGE_SIZE-1)

#define SID_SHIFT       28
#define SID_MASK        0xfffffffffUL
#define ESID_MASK	0xfffffffff0000000UL
#define GET_ESID(x)     (((x) >> SID_SHIFT) & SID_MASK)

#ifdef CONFIG_HUGETLB_PAGE

#define HPAGE_SHIFT	24
#define HPAGE_SIZE	((1UL) << HPAGE_SHIFT)
#define HPAGE_MASK	(~(HPAGE_SIZE - 1))
#define HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

/* For 64-bit processes the hugepage range is 1T-1.5T */
#define TASK_HPAGE_BASE ASM_CONST(0x0000010000000000)
#define TASK_HPAGE_END 	ASM_CONST(0x0000018000000000)

#define LOW_ESID_MASK(addr, len)	(((1U << (GET_ESID(addr+len-1)+1)) \
	   	                	- (1U << GET_ESID(addr))) & 0xffff)

#define ARCH_HAS_HUGEPAGE_ONLY_RANGE
#define ARCH_HAS_PREPARE_HUGEPAGE_RANGE

#define touches_hugepage_low_range(addr, len) \
	(LOW_ESID_MASK((addr), (len)) & current->mm->context.htlb_segs)
#define touches_hugepage_high_range(addr, len) \
	(((addr) > (TASK_HPAGE_BASE-(len))) && ((addr) < TASK_HPAGE_END))

#define __within_hugepage_low_range(addr, len, segmask) \
	((LOW_ESID_MASK((addr), (len)) | (segmask)) == (segmask))
#define within_hugepage_low_range(addr, len) \
	__within_hugepage_low_range((addr), (len), \
				    current->mm->context.htlb_segs)
#define within_hugepage_high_range(addr, len) (((addr) >= TASK_HPAGE_BASE) \
	  && ((addr)+(len) <= TASK_HPAGE_END) && ((addr)+(len) >= (addr)))

#define is_hugepage_only_range(addr, len) \
	(touches_hugepage_high_range((addr), (len)) || \
	  touches_hugepage_low_range((addr), (len)))
#define hugetlb_free_pgtables free_pgtables
#define HAVE_ARCH_HUGETLB_UNMAPPED_AREA

#define in_hugepage_area(context, addr) \
	((cur_cpu_spec->cpu_features & CPU_FTR_16M_PAGE) && \
	 ( (((addr) >= TASK_HPAGE_BASE) && ((addr) < TASK_HPAGE_END)) || \
	   ( ((addr) < 0x100000000L) && \
	     ((1 << GET_ESID(addr)) & (context).htlb_segs) ) ) )

#else /* !CONFIG_HUGETLB_PAGE */

#define in_hugepage_area(mm, addr)	0

#endif /* !CONFIG_HUGETLB_PAGE */

/* align addr on a size boundary - adjust address up/down if needed */
#define _ALIGN_UP(addr,size)	(((addr)+((size)-1))&(~((size)-1)))
#define _ALIGN_DOWN(addr,size)	((addr)&(~((size)-1)))

/* align addr on a size boundary - adjust address up if needed */
#define _ALIGN(addr,size)     _ALIGN_UP(addr,size)

/* to align the pointer to the (next) double word boundary */
#define DOUBLEWORD_ALIGN(addr)	_ALIGN(addr,sizeof(unsigned long))

/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr)	_ALIGN(addr, PAGE_SIZE)

#endif /* _PPC64_PAGE_H */
