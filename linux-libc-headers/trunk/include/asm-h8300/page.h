#ifndef _H8300_PAGE_H
#define _H8300_PAGE_H


/* PAGE_SHIFT determines the page size */

#define PAGE_SHIFT	(12)
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))


#endif /* _H8300_PAGE_H */
