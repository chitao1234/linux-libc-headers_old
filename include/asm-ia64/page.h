#ifndef _ASM_IA64_PAGE_H
#define _ASM_IA64_PAGE_H
/*
 * Pagetable related stuff.
 *
 * Copyright (C) 1998, 1999, 2002 Hewlett-Packard Co
 *	David Mosberger-Tang <davidm@hpl.hp.com>
 */


#include <asm/intrinsics.h>
#include <asm/types.h>

/*
 * PAGE_SHIFT determines the actual kernel page size.
 */
#if defined(CONFIG_IA64_PAGE_SIZE_4KB)
# define PAGE_SHIFT	12
#elif defined(CONFIG_IA64_PAGE_SIZE_8KB)
# define PAGE_SHIFT	13
#elif defined(CONFIG_IA64_PAGE_SIZE_16KB)
# define PAGE_SHIFT	14
#elif defined(CONFIG_IA64_PAGE_SIZE_64KB)
# define PAGE_SHIFT	16
#else
# error Unsupported page size!
#endif

#define PAGE_SIZE		(__IA64_UL_CONST(1) << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE - 1))
#define PAGE_ALIGN(addr)	(((addr) + PAGE_SIZE - 1) & PAGE_MASK)

#define PERCPU_PAGE_SHIFT	16	/* log2() of max. size of per-CPU area */
#define PERCPU_PAGE_SIZE	(__IA64_UL_CONST(1) << PERCPU_PAGE_SHIFT)

#define RGN_MAP_LIMIT	((1UL << (4*PAGE_SHIFT - 12)) - PAGE_SIZE)	/* per region addr limit */

#ifdef CONFIG_HUGETLB_PAGE

# if defined(CONFIG_HUGETLB_PAGE_SIZE_4GB)
#  define HPAGE_SHIFT	32
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_1GB)
#  define HPAGE_SHIFT	30
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_256MB)
#  define HPAGE_SHIFT	28
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_64MB)
#  define HPAGE_SHIFT	26
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_16MB)
#  define HPAGE_SHIFT	24
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_4MB)
#  define HPAGE_SHIFT	22
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_1MB)
#  define HPAGE_SHIFT	20
# elif defined(CONFIG_HUGETLB_PAGE_SIZE_256KB)
#  define HPAGE_SHIFT	18
# else
#  error Unsupported IA-64 HugeTLB Page Size!
# endif

# define REGION_HPAGE	(4UL)	/* note: this is hardcoded in mmu_context.h:reload_context()!*/
# define REGION_SHIFT	61
# define HPAGE_SIZE	(__IA64_UL_CONST(1) << HPAGE_SHIFT)
# define HPAGE_MASK	(~(HPAGE_SIZE - 1))
# define HAVE_ARCH_HUGETLB_UNMAPPED_AREA
# define ARCH_HAS_HUGEPAGE_ONLY_RANGE
#endif /* CONFIG_HUGETLB_PAGE */

#ifdef __ASSEMBLY__
# define __pa(x)		((x) - PAGE_OFFSET)
# define __va(x)		((x) + PAGE_OFFSET)
#endif /* !__ASSEMBLY__ */

#ifdef STRICT_MM_TYPECHECKS
  /*
   * These are used to make use of C type-checking..
   */
  typedef struct { unsigned long pte; } pte_t;
  typedef struct { unsigned long pmd; } pmd_t;
  typedef struct { unsigned long pgd; } pgd_t;
  typedef struct { unsigned long pgprot; } pgprot_t;

# define pte_val(x)	((x).pte)
# define pmd_val(x)	((x).pmd)
# define pgd_val(x)	((x).pgd)
# define pgprot_val(x)	((x).pgprot)

# define __pte(x)	((pte_t) { (x) } )
# define __pgprot(x)	((pgprot_t) { (x) } )

#else /* !STRICT_MM_TYPECHECKS */
  /*
   * .. while these make it easier on the compiler
   */
# ifndef __ASSEMBLY__
    typedef unsigned long pte_t;
    typedef unsigned long pmd_t;
    typedef unsigned long pgd_t;
    typedef unsigned long pgprot_t;
# endif

# define pte_val(x)	(x)
# define pmd_val(x)	(x)
# define pgd_val(x)	(x)
# define pgprot_val(x)	(x)

# define __pte(x)	(x)
# define __pgd(x)	(x)
# define __pgprot(x)	(x)
#endif /* !STRICT_MM_TYPECHECKS */

#define PAGE_OFFSET			0xe000000000000000

#define VM_DATA_DEFAULT_FLAGS		(VM_READ | VM_WRITE |					\
					 VM_MAYREAD | VM_MAYWRITE | VM_MAYEXEC |		\
					 (((current->thread.flags & IA64_THREAD_XSTACK) != 0)	\
					  ? VM_EXEC : 0))

#endif /* _ASM_IA64_PAGE_H */
