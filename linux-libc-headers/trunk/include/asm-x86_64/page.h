#ifndef _X86_64_PAGE_H
#define _X86_64_PAGE_H

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	12
#ifdef __ASSEMBLY__
#define PAGE_SIZE	(0x1 << PAGE_SHIFT)
#else
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#endif
#define PAGE_MASK	(~(PAGE_SIZE-1))
#define PHYSICAL_PAGE_MASK	(~(PAGE_SIZE-1) & (__PHYSICAL_MASK << PAGE_SHIFT))

#define THREAD_ORDER 1 
#ifdef __ASSEMBLY__
#define THREAD_SIZE  (1 << (PAGE_SHIFT + THREAD_ORDER))
#else
#define THREAD_SIZE  (1UL << (PAGE_SHIFT + THREAD_ORDER))
#endif
#define CURRENT_MASK (~(THREAD_SIZE-1))

#define LARGE_PAGE_MASK (~(LARGE_PAGE_SIZE-1))
#define LARGE_PAGE_SIZE (1UL << PMD_SHIFT)

#define HPAGE_SHIFT PMD_SHIFT
#define HPAGE_SIZE	((1UL) << HPAGE_SHIFT)
#define HPAGE_MASK	(~(HPAGE_SIZE - 1))
#define HUGETLB_PAGE_ORDER	(HPAGE_SHIFT - PAGE_SHIFT)

#endif /* _X86_64_PAGE_H */
