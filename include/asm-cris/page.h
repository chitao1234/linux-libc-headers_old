#ifndef _CRIS_PAGE_H
#define _CRIS_PAGE_H

#include <asm/arch/page.h>

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT	13
#ifndef __ASSEMBLY__
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#else
#define PAGE_SIZE	(1 << PAGE_SHIFT)
#endif
#define PAGE_MASK	(~(PAGE_SIZE-1))


#endif /* _CRIS_PAGE_H */

