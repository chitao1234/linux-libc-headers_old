#ifndef _ASMARM_PAGE_H
#define _ASMARM_PAGE_H


/* PAGE_SHIFT determines the page size.  This is configurable. */
#if defined(CONFIG_PAGESIZE_16)
#define PAGE_SHIFT      14              /* 16K */
#else           /* default */
#define PAGE_SHIFT      15              /* 32K */
#endif

#define EXEC_PAGESIZE   32768

#define PAGE_SIZE		(1UL << PAGE_SHIFT)
#define PAGE_MASK		(~(PAGE_SIZE-1))

/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr)	(((addr)+PAGE_SIZE-1)&PAGE_MASK)

#endif
