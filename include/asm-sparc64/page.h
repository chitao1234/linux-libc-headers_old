
#ifndef _SPARC64_PAGE_H
#define _SPARC64_PAGE_H

#include <asm/const.h>

#define PAGE_SHIFT   13
#define PAGE_SIZE    (_AC(1,UL) << PAGE_SHIFT)
#define PAGE_MASK    (~(PAGE_SIZE-1))

#endif /* !(_SPARC64_PAGE_H) */
