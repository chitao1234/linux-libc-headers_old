#ifndef _ALPHA_PAGE_H
#define _ALPHA_PAGE_H

#include <asm/pal.h>

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	13
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#define PAGE_MASK	(~(PAGE_SIZE-1))


#endif /* _ALPHA_PAGE_H */
