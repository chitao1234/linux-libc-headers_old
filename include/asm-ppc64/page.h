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


/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	12
#ifndef __ASSEMBLY__
# define PAGE_SIZE	(1UL << PAGE_SHIFT)
#else
# define PAGE_SIZE	(1 << PAGE_SHIFT)
#endif
#define PAGE_MASK	(~(PAGE_SIZE-1))
#define PAGE_OFFSET_MASK (PAGE_SIZE-1)

#ifdef CONFIG_HUGETLB_PAGE

#define HPAGE_SHIFT	24
#define HPAGE_SIZE	((1UL) << HPAGE_SHIFT)
#define HPAGE_MASK	(~(HPAGE_SIZE - 1))
#define HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

/* For 64-bit processes the hugepage range is 1T-1.5T */
#define TASK_HPAGE_BASE 	(0x0000010000000000UL)
#define TASK_HPAGE_END 	(0x0000018000000000UL)

/* For 32-bit processes the hugepage range is 2-3G */
#define TASK_HPAGE_BASE_32	(0x80000000UL)
#define TASK_HPAGE_END_32	(0xc0000000UL)

#define ARCH_HAS_HUGEPAGE_ONLY_RANGE
#define ARCH_HAS_PREPARE_HUGEPAGE_RANGE

#define is_hugepage_low_range(addr, len) \
	(((addr) > (TASK_HPAGE_BASE_32-(len))) && ((addr) < TASK_HPAGE_END_32))
#define is_hugepage_high_range(addr, len) \
	(((addr) > (TASK_HPAGE_BASE-(len))) && ((addr) < TASK_HPAGE_END))

#define is_hugepage_only_range(addr, len) \
	(is_hugepage_high_range((addr), (len)) || \
	 (current->mm->context.low_hpages \
	  && is_hugepage_low_range((addr), (len))))
#define hugetlb_free_pgtables free_pgtables
#define HAVE_ARCH_HUGETLB_UNMAPPED_AREA

#define in_hugepage_area(context, addr) \
	((cur_cpu_spec->cpu_features & CPU_FTR_16M_PAGE) && \
	 ((((addr) >= TASK_HPAGE_BASE) && ((addr) < TASK_HPAGE_END)) || \
	  ((context).low_hpages && \
	   (((addr) >= TASK_HPAGE_BASE_32) && ((addr) < TASK_HPAGE_END_32)))))

#else /* !CONFIG_HUGETLB_PAGE */

#define in_hugepage_area(mm, addr)	0

#endif /* !CONFIG_HUGETLB_PAGE */

#define SID_SHIFT       28
#define SID_MASK        0xfffffffff
#define GET_ESID(x)     (((x) >> SID_SHIFT) & SID_MASK)

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
