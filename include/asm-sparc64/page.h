
#ifndef _SPARC64_PAGE_H
#define _SPARC64_PAGE_H


#define PAGE_SHIFT   13
#ifndef __ASSEMBLY__
/* I have my suspicions... -DaveM */
#define PAGE_SIZE    (1UL << PAGE_SHIFT)
#else
#define PAGE_SIZE    (1 << PAGE_SHIFT)
#endif

#define PAGE_MASK    (~(PAGE_SIZE-1))

#endif /* !(_SPARC64_PAGE_H) */
