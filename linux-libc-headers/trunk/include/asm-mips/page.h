/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1994 - 1999, 2000, 03 Ralf Baechle
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#ifndef _ASM_PAGE_H
#define _ASM_PAGE_H

extern int getpagesize(void);
#define PAGE_SIZE ((unsigned long)getpagesize())
#define PAGE_SHIFT ((unsigned long[]){12,13,14,-1,15,-1,-1,-1,16}[PAGE_SIZE>>13])

#endif /* _ASM_PAGE_H */
#ifdef CONFIG_LIMITED_DMA
#define WANT_PAGE_VIRTUAL
#endif

