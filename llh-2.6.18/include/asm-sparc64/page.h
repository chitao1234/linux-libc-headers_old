/* $Id: page.h,v 1.39 2002/02/09 19:49:31 davem Exp $ */

#ifndef _SPARC64_PAGE_H
#define _SPARC64_PAGE_H

#include <asm/const.h>

#if defined(CONFIG_SPARC64_PAGE_SIZE_8KB)
#define PAGE_SHIFT   13
#elif defined(CONFIG_SPARC64_PAGE_SIZE_64KB)
#define PAGE_SHIFT   16
#elif defined(CONFIG_SPARC64_PAGE_SIZE_512KB)
#define PAGE_SHIFT   19
#elif defined(CONFIG_SPARC64_PAGE_SIZE_4MB)
#define PAGE_SHIFT   22
#else
#error No page size specified in kernel configuration
#endif

#define PAGE_SIZE    (_AC(1,UL) << PAGE_SHIFT)
#define PAGE_MASK    (~(PAGE_SIZE-1))

/* Flushing for D-cache alias handling is only needed if
 * the page size is smaller than 16K.
 */
#if PAGE_SHIFT < 14
#define DCACHE_ALIASING_POSSIBLE
#endif

#include <asm-generic/page.h>

#endif /* !(_SPARC64_PAGE_H) */
