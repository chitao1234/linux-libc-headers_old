#ifndef _M68K_PAGE_H
#define _M68K_PAGE_H


/* PAGE_SHIFT determines the page size */
#ifndef CONFIG_SUN3
#define PAGE_SHIFT	(12)
#else
#define PAGE_SHIFT	(13)
#endif
#ifdef __ASSEMBLY__
#define PAGE_SIZE	(1 << PAGE_SHIFT)
#else
#define PAGE_SIZE	(1UL << PAGE_SHIFT)
#endif
#define PAGE_MASK	(~(PAGE_SIZE-1))


#endif /* _M68K_PAGE_H */
