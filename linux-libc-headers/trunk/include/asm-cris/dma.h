/* $Id: dma.h,v 1.1 2003/12/15 18:47:01 mmazur Exp $ */

#ifndef _ASM_DMA_H
#define _ASM_DMA_H

#include <asm/arch/dma.h>

/* it's useless on the Etrax, but unfortunately needed by the new
   bootmem allocator (but this should do it for this) */

#define MAX_DMA_ADDRESS PAGE_OFFSET

#endif /* _ASM_DMA_H */
