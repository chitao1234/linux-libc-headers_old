/*
 * ItLpNaca.h
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
#ifndef _ITLPNACA_H
#define _ITLPNACA_H

//=============================================================================
//
//	This control block contains the data that is shared between the
//	hypervisor (PLIC) and the OS.
//
//=============================================================================

struct ItLpNaca
{
//=============================================================================
// CACHE_LINE_1 0x0000 - 0x007F Contains read-only data
//=============================================================================
	__u32	xDesc;			// Eye catcher			x00-x03
	__u16	xSize;			// Size of this class		x04-x05
	__u16	xIntHdlrOffset;		// Offset to IntHdlr array	x06-x07
	__u8	xMaxIntHdlrEntries;	// Number of entries in array	x08-x08
	__u8	xPrimaryLpIndex;	// LP Index of Primary		x09-x09
	__u8	xServiceLpIndex;	// LP Ind of Service Focal Pointx0A-x0A
	__u8	xLpIndex;		// LP Index			x0B-x0B
	__u16	xMaxLpQueues;		// Number of allocated queues	x0C-x0D
	__u16	xLpQueueOffset;		// Offset to start of LP queues	x0E-x0F
	__u8	xPirEnvironMode:8;	// Piranha or hardware		x10-x10
	__u8	xPirConsoleMode:8;	// Piranha console indicator	x11-x11
	__u8	xPirDasdMode:8;		// Piranha dasd indicator	x12-x12
	__u8	xRsvd1_0[5];		// Reserved for Piranha related	x13-x17
	__u8	xLparInstalled:1;	// Is LPAR installed on system	x18-x1F
	__u8	xSysPartitioned:1;	// Is the system partitioned	...
	__u8	xHwSyncedTBs:1;		// Hardware synced TBs		...
	__u8	xIntProcUtilHmt:1;	// Utilize HMT for interrupts	...
	__u8	xRsvd1_1:4;		// Reserved			...
	__u8	xSpVpdFormat:8;		// VPD areas are in CSP format	...
	__u8	xIntProcRatio:8;	// Ratio of int procs to procs	...
	__u8	xRsvd1_2[5];		// Reserved			...
	__u16	xRsvd1_3;		// Reserved			x20-x21
	__u16	xPlicVrmIndex;		// VRM index of PLIC		x22-x23
	__u16	xMinSupportedSlicVrmInd;// Min supported OS VRM index	x24-x25
	__u16	xMinCompatableSlicVrmInd;// Min compatible OS VRM index x26-x27
	__u64	xLoadAreaAddr;		// ER address of load area	x28-x2F
	__u32	xLoadAreaChunks;	// Chunks for the load area	x30-x33
	__u32	xPaseSysCallCRMask;	// Mask used to test CR before  x34-x37
	// doing an ASR switch on PASE
	// system call.
	__u64	xSlicSegmentTablePtr;   // Pointer to Slic seg table.   x38-x3f
	__u8	xRsvd1_4[64];		//         			x40-x7F 
   
//=============================================================================
// CACHE_LINE_2 0x0080 - 0x00FF Contains local read-write data
//=============================================================================
	__u8	xRsvd2_0[128];		// Reserved			x00-x7F

//=============================================================================
// CACHE_LINE_3-6 0x0100 - 0x02FF Contains LP Queue indicators
// NB: Padding required to keep xInterrruptHdlr at x300 which is required 
// for v4r4 PLIC.
//=============================================================================
	__u8	xOldLpQueue[128];	// LP Queue needed for v4r4	100-17F
	__u8	xRsvd3_0[384];		// Reserved			180-2FF
//=============================================================================
// CACHE_LINE_7-8 0x0300 - 0x03FF Contains the address of the OS interrupt
//  handlers
//=============================================================================
	__u64	xInterruptHdlr[32];	// Interrupt handlers		300-x3FF
};

//=============================================================================

#endif /* _ITLPNACA_H */
