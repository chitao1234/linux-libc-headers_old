#ifndef _ASM_M32R_PGALLOC_H
#define _ASM_M32R_PGALLOC_H

/* $Id: pgalloc.h,v 1.1 2004/10/21 15:15:37 mmazur Exp $ */

#include <linux/config.h>
#include <linux/mm.h>

#include <asm/io.h>
#include <asm/pgtable.h>

#define pmd_populate_kernel(mm, pmd, pte)	\
	set_pmd(pmd, __pmd(_PAGE_TABLE + __pa(pte)))

static __inline__ void pmd_populate(struct mm_struct *mm, pmd_t *pmd,
	struct page *pte)
{
	set_pmd(pmd, __pmd(_PAGE_TABLE + page_to_phys(pte)));
}

/*
 * Allocate and free page tables.
 */
static __inline__ pgd_t *pgd_alloc(struct mm_struct *mm)
{
	pgd_t *pgd = (pgd_t *)__get_free_page(GFP_KERNEL);

	if (pgd)
		clear_page(pgd);

	return pgd;
}

static __inline__ void pgd_free(pgd_t *pgd)
{
	free_page((unsigned long)pgd);
}

static __inline__ pte_t *pte_alloc_one_kernel(struct mm_struct *mm,
	unsigned long address)
{
	pte_t *pte = (pte_t *)__get_free_page(GFP_KERNEL);

	if (pte)
		clear_page(pte);

	return pte;
}

static __inline__ struct page *pte_alloc_one(struct mm_struct *mm,
	unsigned long address)
{
	struct page *pte = alloc_page(GFP_KERNEL);

	if (pte)
		clear_page(page_address(pte));

	return pte;
}

static __inline__ void pte_free_kernel(pte_t *pte)
{
	free_page((unsigned long)pte);
}

static __inline__ void pte_free(struct page *pte)
{
	__free_page(pte);
}

#define __pte_free_tlb(tlb, pte)	pte_free((pte))

/*
 * allocating and freeing a pmd is trivial: the 1-entry pmd is
 * inside the pgd, so has no extra memory associated with it.
 * (In the PAE case we free the pmds as part of the pgd.)
 */

#define pmd_alloc_one(mm, addr)		({ BUG(); ((pmd_t *)2); })
#define pmd_free(x)			do { } while (0)
#define __pmd_free_tlb(tlb, x)		do { } while (0)
#define pgd_populate(mm, pmd, pte)	BUG()

#define check_pgt_cache()	do { } while (0)

#endif /* _ASM_M32R_PGALLOC_H */

