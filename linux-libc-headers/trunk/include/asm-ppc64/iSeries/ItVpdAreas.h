/*
 * ItVpdAreas.h
 * Copyright (C) 2001  Mike Corrigan IBM Corporation
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
#ifndef _ITVPDAREAS_H
#define _ITVPDAREAS_H

//=====================================================================================
//
//      This file defines the address and length of all of the VPD area passed to
//	the OS from PLIC (most of which start from the SP).
//

#include <asm/types.h>

// VPD Entry index is carved in stone - cannot be changed (easily).
#define ItVpdCecVpd				   0
#define ItVpdDynamicSpace			   1
#define ItVpdExtVpd				   2
#define ItVpdExtVpdOnPanel			   3
#define ItVpdFirstPaca				   4
#define ItVpdIoVpd				   5
#define ItVpdIplParms				   6
#define ItVpdMsVpd				   7
#define ItVpdPanelVpd				   8
#define ItVpdLpNaca				   9
#define ItVpdBackplaneAndMaybeClockCardVpd        10 
#define ItVpdRecoveryLogBuffer		          11
#define ItVpdSpCommArea				  12
#define ItVpdSpLogBuffer			  13
#define ItVpdSpLogBufferSave			  14
#define ItVpdSpCardVpd				  15
#define ItVpdFirstProcVpd			  16	
#define ItVpdApModelVpd				  17
#define ItVpdClockCardVpd			  18
#define ItVpdBusExtCardVpd			  19
#define ItVpdProcCapacityVpd			  20
#define ItVpdInteractiveCapacityVpd		  21
#define ItVpdFirstSlotLabel			  22
#define ItVpdFirstLpQueue			  23
#define ItVpdFirstL3CacheVpd			  24	
#define ItVpdFirstProcFruVpd			  25

#define ItVpdMaxEntries				  26


#define ItDmaMaxEntries				  10

#define ItVpdAreasMaxSlotLabels		 192 


struct SlicVpdAdrs {
	__u32	pad1;
	void *  vpdAddr;
};


struct	ItVpdAreas
{
	__u32	xSlicDesc;		// Descriptor				000-003
	__u16	xSlicSize;		// Size of this control block		004-005
	__u16	xPlicAdjustVpdLens:1;	// Flag to indicate new interface 	006-007
	__u16	xRsvd1:15;		// Reserved bits			...
	__u16	xSlicVpdEntries;	// Number of VPD entries		008-009
	__u16	xSlicDmaEntries;	// Number of DMA entries		00A-00B
	__u16	xSlicMaxLogicalProcs;	// Maximum logical processors		00C-00D
	__u16	xSlicMaxPhysicalProcs;	// Maximum physical processors		00E-00F
	__u16	xSlicDmaToksOffset;	// Offset into this of array		010-011
	__u16	xSlicVpdAdrsOffset;	// Offset into this of array		012-013
	__u16	xSlicDmaLensOffset;	// Offset into this of array		014-015
	__u16	xSlicVpdLensOffset;	// Offset into this of array		016-017
	__u16	xSlicMaxSlotLabels;	// Maximum number of slot labels	018-019
	__u16	xSlicMaxLpQueues;	// Maximum number of LP Queues		01A-01B
	__u8	xRsvd2[4];		// Reserved				01C-01F
	__u64	xRsvd3[12];		// Reserved				020-07F
	__u32	xPlicDmaLens[ItDmaMaxEntries];// Array of DMA lengths		080-0A7
	__u32	xPlicDmaToks[ItDmaMaxEntries];// Array of DMA tokens		0A8-0CF
	__u32	xSlicVpdLens[ItVpdMaxEntries];// Array of VPD lengths		0D0-12F
	void * xSlicVpdAdrs[ItVpdMaxEntries];// Array of VPD buffers	130-1EF
};

#endif /* _ITVPDAREAS_H */
