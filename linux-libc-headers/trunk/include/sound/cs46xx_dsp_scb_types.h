/*
 *  The driver for the Cirrus Logic's Sound Fusion CS46XX based soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@suse.cz>
 *
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 *
 * NOTE: comments are copy/paste from cwcemb80.lst 
 * provided by Tom Woller at Cirrus (my only
 * documentation about the SP OS running inside
 * the DSP) 
 */

#ifndef __CS46XX_DSP_SCB_TYPES_H__
#define __CS46XX_DSP_SCB_TYPES_H__

#include <asm/byteorder.h>

#ifndef ___DSP_DUAL_16BIT_ALLOC
#if   defined(__LITTLE_ENDIAN)
#define ___DSP_DUAL_16BIT_ALLOC(a,b) __u16 a; __u16 b;
#elif defined(__BIG_ENDIAN)
#define ___DSP_DUAL_16BIT_ALLOC(a,b) __u16 b; __u16 a;
#else
#error Not __LITTLE_ENDIAN and not __BIG_ENDIAN, then what ???
#endif
#endif

/* This structs are used internally by the SP */

typedef struct _basic_dma_req_t {
	/* DMA Requestor Word 0 (DCW)  fields:

	   31 [30-28]27  [26:24] 23 22 21 20 [19:18] [17:16] 15 14 13  12  11 10 9 8 7 6  [5:0]
	   _______________________________________________________________________________________	
	   |S| SBT  |D|  DBT    |wb|wb|  |  |  LS  |  SS   |Opt|Do|SSG|DSG|  |  | | | | | Dword   |
	   |H|_____ |H|_________|S_|D |__|__|______|_______|___|ne|__ |__ |__|__|_|_|_|_|_Count -1|
	*/
	__u32 dcw;                 /* DMA Control Word */
	__u32 dmw;                 /* DMA Mode Word */
	__u32 saw;                 /* Source Address Word */
	__u32 daw;                 /* Destination Address Word  */
} basic_dma_req_t;

typedef struct _scatter_gather_ext_t {
	__u32 npaw;                /* Next-Page Address Word */

	/* DMA Requestor Word 5 (NPCW)  fields:
     
	   31-30 29 28          [27:16]              [15:12]             [11:3]                [2:0] 				
	   _________________________________________________________________________________________	
	   |SV  |LE|SE|   Sample-end byte offset   |         | Page-map entry offset for next  |    | 
	   |page|__|__| ___________________________|_________|__page, if !sample-end___________|____|
	*/
	__u32 npcw;                /* Next-Page Control Word */
	__u32 lbaw;                /* Loop-Begin Address Word */
	__u32 nplbaw;              /* Next-Page after Loop-Begin Address Word */
	__u32 sgaw;                /* Scatter/Gather Address Word */
} scatter_gather_ext_t;

typedef struct _volume_control_t {
	___DSP_DUAL_16BIT_ALLOC(
	   rightTarg,  /* Target volume for left & right channels */
	   leftTarg
	)
	___DSP_DUAL_16BIT_ALLOC(
	   rightVol,   /* Current left & right channel volumes */
	   leftVol
	)
} volume_control_t;

/* Generic stream control block (SCB) structure definition */
typedef struct _generic_scb_t {
	/* For streaming I/O, the DSP should never alter any words in the DMA
	   requestor or the scatter/gather extension.  Only ad hoc DMA request
	   streams are free to alter the requestor (currently only occur in the
	   DOS-based MIDI controller and in debugger-inserted code).
    
	   If an SCB does not have any associated DMA requestor, these 9 ints
	   may be freed for use by other tasks, but the pointer to the SCB must
	   still be such that the insOrd:nextSCB appear at offset 9 from the
	   SCB pointer.
     
	   Basic (non scatter/gather) DMA requestor (4 ints)
	*/
  
	/* Initialized by the host, only modified by DMA 
	   R/O for the DSP task */
	basic_dma_req_t  basic_req;  /* Optional */

	/* Scatter/gather DMA requestor extension   (5 ints) 
	   Initialized by the host, only modified by DMA
	   DSP task never needs to even read these.
	*/
	scatter_gather_ext_t sg_ext;  /* Optional */

	/* Sublist pointer & next stream control block (SCB) link.
	   Initialized & modified by the host R/O for the DSP task
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,     /* REQUIRED */
	    sub_list_ptr  /* REQUIRED */
	)
  
	/* Pointer to this tasks parameter block & stream function pointer 
	   Initialized by the host  R/O for the DSP task */
	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,  /* REQUIRED */
	    this_spb      /* REQUIRED */
	)

	/* rsConfig register for stream buffer (rsDMA reg. 
	   is loaded from basicReq.daw for incoming streams, or 
	   basicReq.saw, for outgoing streams) 

	   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]
	   ______________________________________________________________________________
	   |DMA  |D|maxDMAsize| streamNum|dir|p|  |  |  |  | | |ds |shr 1|rev Cy | mod   |
	   |prio |_|__________|__________|___|_|__|__|__|__|_|_|___|_____|_______|_______|
	   31 30 29  [28:24]     [23:16] 15 14 13 12 11 10 9 8 7 6  5      4      [3:0]


	   Initialized by the host R/O for the DSP task
	*/
	__u32  strm_rs_config; /* REQUIRED */
               // 
	/* On mixer input streams: indicates mixer input stream configuration
	   On Tees, this is copied from the stream being snooped

	   Stream sample pointer & MAC-unit mode for this stream 
     
	   Initialized by the host Updated by the DSP task
	*/
	__u32  strm_buf_ptr; /* REQUIRED  */

	/* On mixer input streams: points to next mixer input and is updated by the
                                   mixer subroutine in the "parent" DSP task
				   (least-significant 16 bits are preserved, unused)
    
           On Tees, the pointer is copied from the stream being snooped on
	   initialization, and, subsequently, it is copied into the
	   stream being snooped.

	   On wavetable/3D voices: the strmBufPtr will use all 32 bits to allow for
                                   fractional phase accumulation

	   Fractional increment per output sample in the input sample buffer

	   (Not used on mixer input streams & redefined on Tees)
	   On wavetable/3D voices: this 32-bit word specifies the integer.fractional 
	   increment per output sample.
	*/
	__u32  strmPhiIncr;


	/* Standard stereo volume control
	   Initialized by the host (host updates target volumes) 

	   Current volumes update by the DSP task
	   On mixer input streams: required & updated by the mixer subroutine in the
                                   "parent" DSP task

	   On Tees, both current & target volumes are copied up on initialization,
	   and, subsequently, the target volume is copied up while the current
	   volume is copied down.
     
	   These two 32-bit words are redefined for wavetable & 3-D voices.    
	*/
	volume_control_t vol_ctrl_t;   /* Optional */
} generic_scb_t;


typedef struct _spos_control_block_t {
	/* WARNING: Certain items in this structure are modified by the host
	            Any dword that can be modified by the host, must not be
		    modified by the SP as the host can only do atomic dword
		    writes, and to do otherwise, even a read modify write, 
		    may lead to corrupted data on the SP.
  
		    This rule does not apply to one off boot time initialisation prior to starting the SP
	*/


	___DSP_DUAL_16BIT_ALLOC( 
	/* First element on the Hyper forground task tree */
	    hfg_tree_root_ptr,  /* HOST */			    
	/* First 3 dwords are written by the host and read-only on the DSP */
	    hfg_stack_base      /* HOST */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Point to this data structure to enable easy access */
	    spos_cb_ptr,	 /* SP */
	    prev_task_tree_ptr   /* SP && HOST */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Currently Unused */
	    xxinterval_timer_period,
	/* Enable extension of SPOS data structure */
	    HFGSPB_ptr
	)


	___DSP_DUAL_16BIT_ALLOC(
	    xxnum_HFG_ticks_thisInterval,
	/* Modified by the DSP */
	    xxnum_tntervals
	)


	/* Set by DSP upon encountering a trap (breakpoint) or a spurious
	   interrupt.  The host must clear this dword after reading it
	   upon receiving spInt1. */
	___DSP_DUAL_16BIT_ALLOC(
	    spurious_int_flag,	 /* (Host & SP) Nature of the spurious interrupt */
	    trap_flag            /* (Host & SP) Nature of detected Trap */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused2,					
	    invalid_IP_flag        /* (Host & SP ) Indicate detection of invalid instruction pointer */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* pointer to forground task tree header for use in next task search */
	    fg_task_tree_hdr_ptr,	  /* HOST */		
	/* Data structure for controlling synchronous link update */
	    hfg_sync_update_ptr           /* HOST */
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	     begin_foreground_FCNT,  /* SP */
	/* Place holder for holding sleep timing */
	     last_FCNT_before_sleep  /* SP */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused7,           /* SP */
	    next_task_treePtr  /* SP */
	)

	__u32 unused5;        

	___DSP_DUAL_16BIT_ALLOC(
	    active_flags,   /* SP */
	/* State flags, used to assist control of execution of Hyper Forground */
	    HFG_flags       /* SP */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused9,
	    unused8
	)
                              
	/* Space for saving enough context so that we can set up enough 
	   to save some more context.
	*/
	__u32 rFE_save_for_invalid_IP;
	__u32 r32_save_for_spurious_int;
	__u32 r32_save_for_trap;
	__u32 r32_save_for_HFG;
} spos_control_block_t;

/* SPB for MIX_TO_OSTREAM algorithm family */
typedef struct _mix2_ostream_spb_t
{
	/* 16b.16b integer.frac approximation to the
	   number of 3 sample triplets to output each
	   frame. (approximation must be floor, to
	   insure that the fractional error is always
	   positive)
	*/
	__u32 outTripletsPerFrame;

	/* 16b.16b integer.frac accumulated number of
	   output triplets since the start of group 
	*/
	__u32 accumOutTriplets;  
} mix2_ostream_spb_t;

/* SCB for Timing master algorithm */
typedef struct _timing_master_scb_t {
	/* First 12 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,     /* REQUIRED */
	    sub_list_ptr  /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,  /* REQUIRED */
	    this_spb      /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	/* Initial values are 0000:xxxx */
 	    reserved,
	    extra_sample_accum
	)

  
	/* Initial values are xxxx:0000
	   hi: Current CODEC output FIFO pointer
	       (0 to 0x0f)
           lo: Flag indicating that the CODEC
	       FIFO is sync'd (host clears to
	       resynchronize the FIFO pointer
	       upon start/restart) 
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    codec_FIFO_syncd, 
	    codec_FIFO_ptr
	)
  
	/* Init. 8000:0005 for 44.1k
                 8000:0001 for 48k
	   hi: Fractional sample accumulator 0.16b
	   lo: Number of frames remaining to be
	       processed in the current group of
	       frames
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frac_samp_accum_qm1,
	    TM_frms_left_in_group
	) 

	/* Init. 0001:0005 for 44.1k
                 0000:0001 for 48k
	   hi: Fractional sample correction factor 0.16b
	       to be added every frameGroupLength frames
	       to correct for truncation error in
	       nsamp_per_frm_q15
	   lo: Number of frames in the group
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frac_samp_correction_qm1,
	    TM_frm_group_length  
	)

	/* Init. 44.1k*65536/8k = 0x00058333 for 44.1k
                 48k*65536/8k = 0x00060000 for 48k
	   16b.16b integer.frac approximation to the
	   number of samples to output each frame.
	   (approximation must be floor, to insure */
	__u32 nsamp_per_frm_q15;
} timing_master_scb_t;

/* SCB for CODEC output algorithm */
typedef struct _codec_output_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_rs_config; /* REQUIRED */

	__u32 strm_buf_ptr;   /* REQUIRED */

	/* NOTE: The CODEC output task reads samples from the first task on its
                 sublist at the stream buffer pointer (init. to lag DMA destination
		 address word).  After the required number of samples is transferred,
		 the CODEC output task advances sub_list_ptr->strm_buf_ptr past the samples
		 consumed.
	*/

	/* Init. 0000:0010 for SDout
                 0060:0010 for SDout2
		 0080:0010 for SDout3
	   hi: Base IO address of FIFO to which
	       the left-channel samples are to
	       be written.
	   lo: Displacement for the base IO
	       address for left-channel to obtain
	       the base IO address for the FIFO
	       to which the right-channel samples
	       are to be written.
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    left_chan_base_IO_addr,
	    right_chan_IO_disp
	)


	/* Init: 0x0080:0004 for non-AC-97
	   Init: 0x0080:0000 for AC-97
	   hi: Exponential volume change rate
	       for input stream
	   lo: Positive shift count to shift the
	       16-bit input sample to obtain the
	       32-bit output word
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    CO_scale_shift_count, 
	    CO_exp_vol_change_rate
	)

	/* Pointer to SCB at end of input chain */
	___DSP_DUAL_16BIT_ALLOC(
	    reserved,
	    last_sub_ptr
	)
} codec_output_scb_t;

/* SCB for CODEC input algorithm */
typedef struct _codec_input_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_rs_config; /* REQUIRED */
	__u32 strm_buf_ptr;   /* REQUIRED */

	/* NOTE: The CODEC input task reads samples from the hardware FIFO 
                 sublist at the DMA source address word (sub_list_ptr->basic_req.saw).
                 After the required number of samples is transferred, the CODEC
                 output task advances sub_list_ptr->basic_req.saw past the samples
                 consumed.  SPuD must initialize the sub_list_ptr->basic_req.saw
                 to point half-way around from the initial sub_list_ptr->strm_nuf_ptr
                 to allow for lag/lead.
	*/

	/* Init. 0000:0010 for SDout
                 0060:0010 for SDout2
		 0080:0010 for SDout3
	   hi: Base IO address of FIFO to which
	       the left-channel samples are to
	       be written.
	   lo: Displacement for the base IO
	       address for left-channel to obtain
	       the base IO address for the FIFO
	       to which the right-channel samples
	       are to be written.
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    rightChanINdisp, 
	    left_chan_base_IN_addr
	)
	/* Init. ?:fffc
	   lo: Negative shift count to shift the
	       32-bit input dword to obtain the
	       16-bit sample msb-aligned (count
	       is negative to shift left)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    scaleShiftCount, 
	    reserver1
	)

	__u32  reserved2;
} codec_input_scb_t;


typedef struct _pcm_serial_input_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_buf_ptr;   /* REQUIRED */
	__u32 strm_rs_config; /* REQUIRED */
  
	/* Init. Ptr to CODEC input SCB
	   hi: Pointer to the SCB containing the
	       input buffer to which CODEC input
	       samples are written
	   lo: Flag indicating the link to the CODEC
	       input task is to be initialized
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    init_codec_input_link,
	    codec_input_buf_scb
	)

	/* Initialized by the host (host updates target volumes) */
	volume_control_t psi_vol_ctrl;   
  
} pcm_serial_input_scb_t;

typedef struct _src_task_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    frames_left_in_gof,
	    gofs_left_in_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    const2_thirds,
	    num_extra_tnput_samples
	)

	___DSP_DUAL_16BIT_ALLOC(
	    cor_per_gof,
	    correction_per_sec 
	)

	___DSP_DUAL_16BIT_ALLOC(
	    output_buf_producer_ptr,  
	    junk_DMA_MID
	)

	___DSP_DUAL_16BIT_ALLOC(
	    gof_length,  
	    gofs_per_sec
	)

	__u32 input_buf_strm_config;

	___DSP_DUAL_16BIT_ALLOC(
	    reserved_for_SRC_use,
	    input_buf_consumer_ptr
	)

	__u32 accum_phi;

	___DSP_DUAL_16BIT_ALLOC(
	    exp_src_vol_change_rate,
	    input_buf_producer_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    src_next_scb,
	    src_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    src_entry_point,
	    src_this_sbp
	)

	__u32  src_strm_rs_config;
	__u32  src_strm_buf_ptr;
  
	__u32   phiIncr6int_26frac;
  
	volume_control_t src_vol_ctrl;
} src_task_scb_t;

typedef struct _decimate_by_pow2_scb_t {
	/* decimationFactor = 2, 4, or 8 (larger factors waste too much memory
	                                  when compared to cascading decimators)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    dec2_coef_base_ptr,
	    dec2_coef_increment
	)

	/* coefIncrement = 128 / decimationFactor (for our ROM filter)
	   coefBasePtr = 0x8000 (for our ROM filter)
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    dec2_in_samples_per_out_triplet,
	    dec2_extra_in_samples
	)
	/* extraInSamples: # of accumulated, unused input samples (init. to 0)
	   inSamplesPerOutTriplet = 3 * decimationFactor
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_const2_thirds,
	    dec2_half_num_taps_mp5
	)
	/* halfNumTapsM5: (1/2 number of taps in decimation filter) minus 5
	   const2thirds: constant 2/3 in 16Q0 format (sign.15)
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_output_buf_producer_ptr,
	    dec2_junkdma_mid
	)

	__u32  dec2_reserved2;

	__u32  dec2_input_nuf_strm_config;
	/* inputBufStrmConfig: rsConfig for the input buffer to the decimator
	   (buffer size = decimationFactor * 32 dwords)
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_phi_incr,
	    dec2_input_buf_consumer_ptr
	)
	/* inputBufConsumerPtr: Input buffer read pointer (into SRC filter)
	   phiIncr = decimationFactor * 4
	*/

	__u32 dec2_reserved3;

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_exp_vol_change_rate,
	    dec2_input_buf_producer_ptr
	)
	/* inputBufProducerPtr: Input buffer write pointer
	   expVolChangeRate: Exponential volume change rate for possible
	                     future mixer on input streams
	*/

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_next_scb,
	    dec2_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    dec2_entry_point,
	    dec2_this_spb
	)

	__u32  dec2_strm_rs_config;
	__u32  dec2_strm_buf_ptr;

	__u32  dec2_reserved4;

	volume_control_t dec2_vol_ctrl; /* Not used! */
} decimate_by_pow2_scb_t;

typedef struct _vari_decimate_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    vdec_frames_left_in_gof,
	    vdec_gofs_left_in_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_const2_thirds,
	    vdec_extra_in_samples
	)
	/* extraInSamples: # of accumulated, unused input samples (init. to 0)
	   const2thirds: constant 2/3 in 16Q0 format (sign.15) */

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_cor_per_gof,
	    vdec_correction_per_sec
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_output_buf_producer_ptr,
	    vdec_input_buf_consumer_ptr
	)
	/* inputBufConsumerPtr: Input buffer read pointer (into SRC filter) */
	___DSP_DUAL_16BIT_ALLOC(
	    vdec_gof_length,
	    vdec_gofs_per_sec
	)

	__u32  vdec_input_buf_strm_config;
	/* inputBufStrmConfig: rsConfig for the input buffer to the decimator
	   (buffer size = 64 dwords) */
	__u32  vdec_coef_increment;
	/* coefIncrement = - 128.0 / decimationFactor (as a 32Q15 number) */

	__u32  vdec_accumphi;
	/* accumPhi: accumulated fractional phase increment (6.26) */

	___DSP_DUAL_16BIT_ALLOC(
 	    vdec_exp_vol_change_rate,
	    vdec_input_buf_producer_ptr
	)
	/* inputBufProducerPtr: Input buffer write pointer
	   expVolChangeRate: Exponential volume change rate for possible
	   future mixer on input streams */

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_next_scb,
	    vdec_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    vdec_entry_point,
	    vdec_this_spb
	)

	__u32 vdec_strm_rs_config;
	__u32 vdec_strm_buf_ptr;

	__u32 vdec_phi_incr_6int_26frac;

	volume_control_t vdec_vol_ctrl;
} vari_decimate_scb_t;


/* SCB for MIX_TO_OSTREAM algorithm family */
typedef struct _mix2_ostream_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_rs_config; /* REQUIRED */
	__u32 strm_buf_ptr;   /* REQUIRED */


	/* hi: Number of mixed-down input triplets
	       computed since start of group
	   lo: Number of frames remaining to be
	       processed in the current group of
	       frames
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frames_left_in_group,
	    accum_input_triplets
	)

	/* hi: Exponential volume change rate
	       for mixer on input streams
	   lo: Number of frames in the group
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    frame_group_length,
	    exp_vol_change_rate
	)
  
	___DSP_DUAL_16BIT_ALLOC(
	    const_FFFF,
	    const_zero
	)
} mix2_ostream_scb_t;


/* SCB for S16_MIX algorithm */
typedef struct _mix_only_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_rs_config; /* REQUIRED */
	__u32 strm_buf_ptr;   /* REQUIRED */

	__u32 reserved;
	volume_control_t vol_ctrl;
} mix_only_scb_t;

/* SCB for the async. CODEC input algorithm */
typedef struct _async_codec_input_scb_t {		 
	__u32 io_free2;     
  
	__u32 io_current_total;
	__u32 io_previous_total;
  
	__u16 io_count;
	__u16 io_count_limit;
  
	__u16 o_fifo_base_addr;            
	__u16 ost_mo_format;
	/* 1 = stereo; 0 = mono 
	   xxx for ASER 1 (not allowed); 118 for ASER2 */

	__u32  ostrm_rs_config;
	__u32  ostrm_buf_ptr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    io_sclks_per_lr_clk,
	    io_io_enable
	)

	__u32  io_free4;

	___DSP_DUAL_16BIT_ALLOC(  
	    io_next_scb,
	    io_sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    io_entry_point,
	    io_this_spb
	)

	__u32 istrm_rs_config;
	__u32 istrm_buf_ptr;

	/* Init. 0000:8042: for ASER1
                 0000:8044: for ASER2  */
	___DSP_DUAL_16BIT_ALLOC(
	    io_stat_reg_addr,
	    iofifo_pointer
	)

	/* Init 1 stero:100 ASER1
	   Init 0 mono:110 ASER2 
	*/
	___DSP_DUAL_16BIT_ALLOC(
	    ififo_base_addr,            
	    ist_mo_format
	)

	__u32 i_free;
} async_codec_input_scb_t;


/* SCB for the SP/DIF CODEC input and output */
typedef struct _spdifiscb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    status_ptr,     
	    status_start_ptr
	)

	__u32 current_total;
	__u32 previous_total;

	___DSP_DUAL_16BIT_ALLOC(
	    count,
	    count_limit
	)

	__u32 status_data;

	___DSP_DUAL_16BIT_ALLOC(  
	    status,
	    free4
	)

	__u32 free3;

	___DSP_DUAL_16BIT_ALLOC(  
	    free2,
	    bit_count
	)

	__u32  temp_status;
  
	___DSP_DUAL_16BIT_ALLOC(
	    next_SCB,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,
	    this_spb
	)

	__u32  strm_rs_config;
	__u32  strm_buf_ptr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    stat_reg_addr, 
	    fifo_pointer
	)

	___DSP_DUAL_16BIT_ALLOC(
	    fifo_base_addr, 
	    st_mo_format
	)

	__u32  free1;
} spdifiscb_t;


/* SCB for the SP/DIF CODEC input and output  */
typedef struct _spdifoscb_t {		 


	__u32 free2;     

	__u32 free3[4];             

	/* Need to be here for compatibility with AsynchFGTxCode */
	__u32 strm_rs_config;
                               
	__u32 strm_buf_ptr;

	___DSP_DUAL_16BIT_ALLOC(  
	    status,
	    free5
	)

	__u32 free4;

	___DSP_DUAL_16BIT_ALLOC(  
	    next_scb,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,
	    this_spb
	)

	__u32 free6[2];
  
	___DSP_DUAL_16BIT_ALLOC(
	    stat_reg_addr, 
	    fifo_pointer
	)

	___DSP_DUAL_16BIT_ALLOC(
	    fifo_base_addr,
	    st_mo_format
	)

	__u32  free1;                                         
} spdifoscb_t;



typedef struct _asynch_fg_rx_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    bot_buf_mask,
	    buf_Mask
	)

	___DSP_DUAL_16BIT_ALLOC(
	    max,
	    min
	)

	___DSP_DUAL_16BIT_ALLOC(
	    old_producer_pointer,
	    hfg_scb_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    delta,
	    adjust_count
	)

	__u32 unused2[5];  

	___DSP_DUAL_16BIT_ALLOC(  
	    sibling_ptr,  
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    code_ptr,
	    this_ptr
	)

	__u32 strm_rs_config; 

	__u32 strm_buf_ptr;
  
	__u32 unused_phi_incr;
  
	___DSP_DUAL_16BIT_ALLOC(
	    right_targ,   
	    left_targ
	)

	___DSP_DUAL_16BIT_ALLOC(
	    right_vol,
	    left_vol
	)
} asynch_fg_rx_scb_t;



typedef struct _asynch_fg_tx_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    not_buf_mask,
	    buf_mask
	)

	___DSP_DUAL_16BIT_ALLOC(
	    max,
	    min
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused1,
	    hfg_scb_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    delta,
	    adjust_count
	)

	__u32 accum_phi;

	___DSP_DUAL_16BIT_ALLOC(
	    unused2,
	    const_one_third
	)

	__u32 unused3[3];

	___DSP_DUAL_16BIT_ALLOC(
	    sibling_ptr,
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    codePtr,
	    this_ptr
	)

	__u32 strm_rs_config;

	__u32 strm_buf_ptr;

	__u32 phi_incr;

	___DSP_DUAL_16BIT_ALLOC(
	    unused_right_targ,
	    unused_left_targ
	)

	___DSP_DUAL_16BIT_ALLOC(
	    unused_right_vol,
	    unused_left_vol
	)
} asynch_fg_tx_scb_t;


typedef struct _output_snoop_scb_t {
	/* First 13 dwords from generic_scb_t */
	basic_dma_req_t  basic_req;  /* Optional */
	scatter_gather_ext_t sg_ext;  /* Optional */
	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,       /* REQUIRED */
	    sub_list_ptr    /* REQUIRED */
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,    /* REQUIRED */
	    this_spb        /* REQUIRED */
	)

	__u32 strm_rs_config; /* REQUIRED */
	__u32 strm_buf_ptr;   /* REQUIRED */

	___DSP_DUAL_16BIT_ALLOC(
	    init_snoop_input_link,
	    snoop_child_input_scb
	)

	__u32 snoop_input_buf_ptr;

	___DSP_DUAL_16BIT_ALLOC(
	    reserved,
	    input_scb
	)
} output_snoop_scb_t;

typedef struct _spio_write_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	    address1,
	    address2
	)

	__u32 data1;

	__u32 data2;

	___DSP_DUAL_16BIT_ALLOC(
	    address3,
	    address4
	)

	__u32 data3;

	__u32 data4;

	___DSP_DUAL_16BIT_ALLOC(
	    unused1,
	    data_ptr
	)

	__u32 unused2[2];

	___DSP_DUAL_16BIT_ALLOC(
	    sibling_ptr,
	    child_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,
	    this_ptr
	)

	__u32 unused3[5];
} spio_write_scb_t;

typedef struct _magic_snoop_task_t {
	__u32 i0;
	__u32 i1;

	__u32 strm_buf_ptr1;
  
	__u16 i2;
	__u16 snoop_scb;

	__u32 i3;
	__u32 i4;
	__u32 i5;
	__u32 i6;

	__u32 i7;

	___DSP_DUAL_16BIT_ALLOC(
	    next_scb,
	    sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	    entry_point,
	    this_ptr
	)

	__u32 strm_buf_config;
	__u32 strm_buf_ptr2;

	__u32 i8;

	volume_control_t vdec_vol_ctrl;
} magic_snoop_task_t;


typedef struct _filter_scb_t {
	___DSP_DUAL_16BIT_ALLOC(
	      a0_right,          /* 0x00 */
	      a0_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      a1_right,          /* 0x01 */
	      a1_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      a2_right,          /* 0x02 */
	      a2_left
	)
	___DSP_DUAL_16BIT_ALLOC(
	      output_buf_ptr,    /* 0x03 */
	      init
	)

	___DSP_DUAL_16BIT_ALLOC(
	      filter_unused3,    /* 0x04 */
	      filter_unused2
	)

	__u32 prev_sample_output1; /* 0x05 */
	__u32 prev_sample_output2; /* 0x06 */
	__u32 prev_sample_input1;  /* 0x07 */
	__u32 prev_sample_input2;  /* 0x08 */

	___DSP_DUAL_16BIT_ALLOC(
	      next_scb_ptr,      /* 0x09 */
	      sub_list_ptr
	)

	___DSP_DUAL_16BIT_ALLOC(
	      entry_point,       /* 0x0A */
	      spb_ptr
	)

	__u32  strm_rs_config;     /* 0x0B */
	__u32  strm_buf_ptr;       /* 0x0C */

	___DSP_DUAL_16BIT_ALLOC(
              b0_right,          /* 0x0D */
	      b0_left
	)
	___DSP_DUAL_16BIT_ALLOC(
              b1_right,          /* 0x0E */
	      b1_left
	)
	___DSP_DUAL_16BIT_ALLOC(
              b2_right,          /* 0x0F */
	      b2_left
	)
} filter_scb_t;
#endif /* __DSP_SCB_TYPES_H__ */