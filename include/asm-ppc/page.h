#ifndef _PPC_PAGE_H
#define _PPC_PAGE_H

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	12
#define PAGE_SIZE	(1UL << PAGE_SHIFT)

/*
 * Subtle: this is an int (not an unsigned long) and so it
 * gets extended to 64 bits the way want (i.e. with 1s).  -- paulus
 */
#define PAGE_MASK	(~((1 << PAGE_SHIFT) - 1))

#endif /* _PPC_PAGE_H */
