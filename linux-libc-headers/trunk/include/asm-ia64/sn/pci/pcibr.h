/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * Copyright (C) 1992-1997,2000-2003 Silicon Graphics, Inc. All rights reserved.
 */
#ifndef _ASM_IA64_SN_PCI_PCIBR_H
#define _ASM_IA64_SN_PCI_PCIBR_H

/* 
 * Some useful ioctls into the pcibr driver
 */
#define PCIBR			'p'
#define _PCIBR(x)		((PCIBR << 8) | (x))

/*
 * Bit defintions for variable slot_status in struct
 * pcibr_soft_slot_s.  They are here so that the user
 * hot-plug utility can interpret the slot's power
 * status.
 */
#ifdef CONFIG_HOTPLUG_PCI_SGI
#define PCI_SLOT_ENABLE_CMPLT       0x01    
#define PCI_SLOT_ENABLE_INCMPLT     0x02    
#define PCI_SLOT_DISABLE_CMPLT      0x04    
#define PCI_SLOT_DISABLE_INCMPLT    0x08    
#define PCI_SLOT_POWER_ON           0x10    
#define PCI_SLOT_POWER_OFF          0x20    
#define PCI_SLOT_IS_SYS_CRITICAL    0x40    
#define PCI_SLOT_PCIBA_LOADED       0x80    

#define PCI_SLOT_STATUS_MASK        (PCI_SLOT_ENABLE_CMPLT | \
				     PCI_SLOT_ENABLE_INCMPLT | \
                                     PCI_SLOT_DISABLE_CMPLT | \
				     PCI_SLOT_DISABLE_INCMPLT)
#define PCI_SLOT_POWER_MASK         (PCI_SLOT_POWER_ON | PCI_SLOT_POWER_OFF)

/*
 * Bit defintions for variable slot_status in struct
 * pcibr_soft_slot_s.  They are here so that both
 * the pcibr driver and the pciconfig command can
 * reference them.
 */
#define SLOT_STARTUP_CMPLT      0x01
#define SLOT_STARTUP_INCMPLT    0x02
#define SLOT_SHUTDOWN_CMPLT     0x04
#define SLOT_SHUTDOWN_INCMPLT   0x08
#define SLOT_POWER_UP           0x10
#define SLOT_POWER_DOWN         0x20
#define SLOT_IS_SYS_CRITICAL    0x40

#define SLOT_STATUS_MASK        (SLOT_STARTUP_CMPLT | SLOT_STARTUP_INCMPLT | \
                                 SLOT_SHUTDOWN_CMPLT | SLOT_SHUTDOWN_INCMPLT)
#define SLOT_POWER_MASK         (SLOT_POWER_UP | SLOT_POWER_DOWN)

/*
 * Bit definitions for variable resp_f_staus.
 * They are here so that both the pcibr driver
 * and the pciconfig command can reference them.
 */
#define FUNC_IS_VALID           0x01
#define FUNC_IS_SYS_CRITICAL    0x02

/*
 * L1 slot power operations for PCI hot-plug
 */
#define PCI_REQ_SLOT_POWER_ON       1
#define PCI_L1_QSIZE                128      /* our L1 message buffer size */


#define L1_QSIZE                128      /* our L1 message buffer size */

enum pcibr_slot_disable_action_e {
    PCI_REQ_SLOT_ELIGIBLE,
    PCI_REQ_SLOT_DISABLE
};


struct pcibr_slot_up_resp_s {
    int                     resp_sub_errno;
    char                    resp_l1_msg[L1_QSIZE + 1];
};

struct pcibr_slot_down_resp_s {
    int                     resp_sub_errno;
    char                    resp_l1_msg[L1_QSIZE + 1];
};

struct pcibr_slot_info_resp_s {
    short		    resp_bs_bridge_type;
    short		    resp_bs_bridge_mode;
    int                     resp_has_host;
    char                    resp_host_slot;
    vertex_hdl_t            resp_slot_conn;
    char                    resp_slot_conn_name[MAXDEVNAME];
    int                     resp_slot_status;
    int                     resp_l1_bus_num;
    int                     resp_bss_ninfo;
    char                    resp_bss_devio_bssd_space[16];
    iopaddr_t               resp_bss_devio_bssd_base; 
    uint64_t		    resp_bss_device;
    int                     resp_bss_pmu_uctr;
    int                     resp_bss_d32_uctr;
    int                     resp_bss_d64_uctr;
    iopaddr_t               resp_bss_d64_base;
    unsigned                resp_bss_d64_flags;
    iopaddr_t               resp_bss_d32_base;
    unsigned                resp_bss_d32_flags;
    atomic_t		    resp_bss_ext_ates_active;
    volatile unsigned      *resp_bss_cmd_pointer;
    unsigned                resp_bss_cmd_shadow;
    int                     resp_bs_rrb_valid;
    int                     resp_bs_rrb_valid_v1;
    int                     resp_bs_rrb_valid_v2;
    int                     resp_bs_rrb_valid_v3;
    int                     resp_bs_rrb_res;
    uint64_t		    resp_b_resp;
    uint64_t		    resp_b_int_device;
    uint64_t		    resp_b_int_enable;
    uint64_t		    resp_b_int_host;
    picreg_t		    resp_p_int_enable;
    picreg_t		    resp_p_int_host;
    struct pcibr_slot_func_info_resp_s {
        int                     resp_f_status;
        char                    resp_f_slot_name[MAXDEVNAME];
        char                    resp_f_bus;
        char                    resp_f_slot;
        char                    resp_f_func;
        char                    resp_f_master_name[MAXDEVNAME];
        void                   *resp_f_pops;
        error_handler_f        *resp_f_efunc;
        error_handler_arg_t     resp_f_einfo;
        int                     resp_f_vendor;
        int                     resp_f_device;

        struct {
            char                    resp_w_space[16];
            iopaddr_t               resp_w_base;
            size_t                  resp_w_size;
        } resp_f_window[6];

        unsigned                resp_f_rbase;
        unsigned                resp_f_rsize;
        int                     resp_f_ibit[4];
        int                     resp_f_att_det_error;

    } resp_func[8];
};

struct pcibr_slot_req_s {
    int                      req_slot;
    union {
        enum pcibr_slot_disable_action_e up;
        struct pcibr_slot_down_resp_s *down;
        struct pcibr_slot_info_resp_s *query;
        void                    *any;
    }                       req_respp;
    int                     req_size;
};

struct pcibr_slot_enable_resp_s {
    int                     resp_sub_errno;
    char                    resp_l1_msg[PCI_L1_QSIZE + 1];
};

struct pcibr_slot_disable_resp_s {
    int                     resp_sub_errno;
    char                    resp_l1_msg[PCI_L1_QSIZE + 1];
};

struct pcibr_slot_enable_req_s {
    pciio_slot_t              	     req_device;
    struct pcibr_slot_enable_resp_s  req_resp;
};

struct pcibr_slot_disable_req_s {
    pciio_slot_t                     req_device;
    enum pcibr_slot_disable_action_e req_action;
    struct pcibr_slot_disable_resp_s req_resp;
};

struct pcibr_slot_info_req_s {
    pciio_slot_t              	     req_device;
    struct pcibr_slot_info_resp_s    req_resp;
};

#endif	/* CONFIG_HOTPLUG_PCI_SGI */


/*
 * PCI specific errors, interpreted by pciconfig command
 */

/* EPERM                          1    */
#define PCI_SLOT_ALREADY_UP       2     /* slot already up */
#define PCI_SLOT_ALREADY_DOWN     3     /* slot already down */
#define PCI_IS_SYS_CRITICAL       4     /* slot is system critical */
/* EIO                            5    */
/* ENXIO                          6    */
#define PCI_L1_ERR                7     /* L1 console command error */
#define PCI_NOT_A_BRIDGE          8     /* device is not a bridge */
#define PCI_SLOT_IN_SHOEHORN      9     /* slot is in a shorhorn */
#define PCI_NOT_A_SLOT           10     /* slot is invalid */
#define PCI_RESP_AREA_TOO_SMALL  11     /* slot is invalid */
/* ENOMEM                        12    */
#define PCI_NO_DRIVER            13     /* no driver for device */
/* EFAULT                        14    */
#define PCI_EMPTY_33MHZ          15     /* empty 33 MHz bus */
/* EBUSY                         16    */
#define PCI_SLOT_RESET_ERR       17     /* slot reset error */
#define PCI_SLOT_INFO_INIT_ERR   18     /* slot info init error */
/* ENODEV                        19    */
#define PCI_SLOT_ADDR_INIT_ERR   20     /* slot addr space init error */
#define PCI_SLOT_DEV_INIT_ERR    21     /* slot device init error */
/* EINVAL                        22    */
#define PCI_SLOT_GUEST_INIT_ERR  23     /* slot guest info init error */
#define PCI_SLOT_RRB_ALLOC_ERR   24     /* slot initial rrb alloc error */
#define PCI_SLOT_DRV_ATTACH_ERR  25     /* driver attach error */
#define PCI_SLOT_DRV_DETACH_ERR  26     /* driver detach error */
/* EFBIG                         27    */
#define PCI_MULTI_FUNC_ERR       28     /* multi-function card error */
#define PCI_SLOT_RBAR_ALLOC_ERR  29     /* slot PCI-X RBAR alloc error */
/* ERANGE                        34    */
/* EUNATCH                       42    */

#endif				/* _ASM_IA64_SN_PCI_PCIBR_H */
