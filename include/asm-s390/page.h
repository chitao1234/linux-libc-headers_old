/*
 *  include/asm-s390/page.h
 *
 *  S390 version
 *    Copyright (C) 1999,2000 IBM Deutschland Entwicklung GmbH, IBM Corporation
 *    Author(s): Hartmut Penner (hp@de.ibm.com)
 */

#ifndef _S390_PAGE_H
#define _S390_PAGE_H

#include <asm/setup.h>
#include <asm/types.h>

/* PAGE_SHIFT determines the page size */
#define PAGE_SHIFT      12
#define PAGE_SIZE       (1UL << PAGE_SHIFT)
#define PAGE_MASK       (~(PAGE_SIZE-1))

#endif /* _S390_PAGE_H */
