/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1992-1997, 2000-2003 Silicon Graphics, Inc.  All Rights Reserved.
 */
#ifndef _ASM_IA64_SN_XTALK_XTALK_H
#define _ASM_IA64_SN_XTALK_XTALK_H


/*
 * xtalk.h -- platform-independent crosstalk interface
 */
/*
 * User-level device driver visible types
 */
typedef char            xwidgetnum_t;	/* xtalk widget number  (0..15) */

#define XWIDGET_NONE		(-1)

typedef int xwidget_part_num_t;	/* xtalk widget part number */

#define XWIDGET_PART_NUM_NONE	(-1)

typedef int             xwidget_rev_num_t;	/* xtalk widget revision number */

#define XWIDGET_REV_NUM_NONE	(-1)

typedef int xwidget_mfg_num_t;	/* xtalk widget manufacturing ID */

#define XWIDGET_MFG_NUM_NONE	(-1)

typedef struct xtalk_piomap_s *xtalk_piomap_t;

/* It is often convenient to fold the XIO target port
 * number into the XIO address.
 */
#define	XIO_NOWHERE	(0xFFFFFFFFFFFFFFFFull)
#define	XIO_ADDR_BITS	(0x0000FFFFFFFFFFFFull)
#define	XIO_PORT_BITS	(0xF000000000000000ull)
#define	XIO_PORT_SHIFT	(60)

#define	XIO_PACKED(x)	(((x)&XIO_PORT_BITS) != 0)
#define	XIO_ADDR(x)	((x)&XIO_ADDR_BITS)
#define	XIO_PORT(x)	((xwidgetnum_t)(((x)&XIO_PORT_BITS) >> XIO_PORT_SHIFT))
#define	XIO_PACK(p,o)	((((uint64_t)(p))<<XIO_PORT_SHIFT) | ((o)&XIO_ADDR_BITS))


#endif				/* _ASM_IA64_SN_XTALK_XTALK_H */
