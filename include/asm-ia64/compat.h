#ifndef _ASM_IA64_COMPAT_H
#define _ASM_IA64_COMPAT_H
/*
 * Architecture specific compatibility types
 */
#include <linux/types.h>

#define COMPAT_USER_HZ	100

typedef __u32		compat_size_t;
typedef __s32		compat_ssize_t;
typedef __s32		compat_time_t;
typedef __s32		compat_clock_t;
typedef __s32		compat_key_t;
typedef __s32		compat_pid_t;
typedef __u16		compat_uid_t;
typedef __u16		compat_gid_t;
typedef __u32		compat_uid32_t;
typedef __u32		compat_gid32_t;
typedef __u16		compat_mode_t;
typedef __u32		compat_ino_t;
typedef __u16		compat_dev_t;
typedef __s32		compat_off_t;
typedef __s64		compat_loff_t;
typedef __u16		compat_nlink_t;
typedef __u16		compat_ipc_pid_t;
typedef __s32		compat_daddr_t;
typedef __u32		compat_caddr_t;
typedef __kernel_fsid_t	compat_fsid_t;

typedef __s32		compat_int_t;
typedef __s32		compat_long_t;
typedef __u32		compat_uint_t;
typedef __u32		compat_ulong_t;

struct compat_timespec {
	compat_time_t	tv_sec;
	__s32		tv_nsec;
};

struct compat_timeval {
	compat_time_t	tv_sec;
	__s32		tv_usec;
};

struct compat_stat {
	compat_dev_t	st_dev;
	__u16		__pad1;
	compat_ino_t	st_ino;
	compat_mode_t	st_mode;
	compat_nlink_t	st_nlink;
	compat_uid_t	st_uid;
	compat_gid_t	st_gid;
	compat_dev_t	st_rdev;
	__u16		__pad2;
	__u32		st_size;
	__u32		st_blksize;
	__u32		st_blocks;
	__u32		st_atime;
	__u32		st_atime_nsec;
	__u32		st_mtime;
	__u32		st_mtime_nsec;
	__u32		st_ctime;
	__u32		st_ctime_nsec;
	__u32		__unused4;
	__u32		__unused5;
};

struct compat_flock {
	short		l_type;
	short		l_whence;
	compat_off_t	l_start;
	compat_off_t	l_len;
	compat_pid_t	l_pid;
};

#define F_GETLK64	12
#define F_SETLK64	13
#define F_SETLKW64	14

/*
 * IA32 uses 4 byte alignment for 64 bit quantities,
 * so we need to pack this structure.
 */
struct compat_flock64 {
	short		l_type;
	short		l_whence;
	compat_loff_t	l_start;
	compat_loff_t	l_len;
	compat_pid_t	l_pid;
} __attribute__((packed));

struct compat_statfs {
	int		f_type;
	int		f_bsize;
	int		f_blocks;
	int		f_bfree;
	int		f_bavail;
	int		f_files;
	int		f_ffree;
	compat_fsid_t	f_fsid;
	int		f_namelen;	/* SunOS ignores this field. */
	int		f_frsize;
	int		f_spare[5];
};

#define COMPAT_RLIM_OLD_INFINITY       0x7fffffff
#define COMPAT_RLIM_INFINITY           0xffffffff

typedef __u32		compat_old_sigset_t;	/* at least 32 bits */

#define _COMPAT_NSIG		64
#define _COMPAT_NSIG_BPW	32

typedef __u32		compat_sigset_word;

#define COMPAT_OFF_T_MAX	0x7fffffff
#define COMPAT_LOFF_T_MAX	0x7fffffffffffffffL

struct compat_ipc64_perm {
	compat_key_t key;
	compat_uid32_t uid;
	compat_gid32_t gid;
	compat_uid32_t cuid;
	compat_gid32_t cgid;
	unsigned short mode;
	unsigned short __pad1;
	unsigned short seq;
	unsigned short __pad2;
	compat_ulong_t unused1;
	compat_ulong_t unused2;
};

struct compat_semid64_ds {
	struct compat_ipc64_perm sem_perm;
	compat_time_t  sem_otime;
	compat_ulong_t __unused1;
	compat_time_t  sem_ctime;
	compat_ulong_t __unused2;
	compat_ulong_t sem_nsems;
	compat_ulong_t __unused3;
	compat_ulong_t __unused4;
};

struct compat_msqid64_ds {
	struct compat_ipc64_perm msg_perm;
	compat_time_t  msg_stime;
	compat_ulong_t __unused1;
	compat_time_t  msg_rtime;
	compat_ulong_t __unused2;
	compat_time_t  msg_ctime;
	compat_ulong_t __unused3;
	compat_ulong_t msg_cbytes;
	compat_ulong_t msg_qnum;
	compat_ulong_t msg_qbytes;
	compat_pid_t   msg_lspid;
	compat_pid_t   msg_lrpid;
	compat_ulong_t __unused4;
	compat_ulong_t __unused5;
};

struct compat_shmid64_ds {
	struct compat_ipc64_perm shm_perm;
	compat_size_t  shm_segsz;
	compat_time_t  shm_atime;
	compat_ulong_t __unused1;
	compat_time_t  shm_dtime;
	compat_ulong_t __unused2;
	compat_time_t  shm_ctime;
	compat_ulong_t __unused3;
	compat_pid_t   shm_cpid;
	compat_pid_t   shm_lpid;
	compat_ulong_t shm_nattch;
	compat_ulong_t __unused4;
	compat_ulong_t __unused5;
};

/*
 * A pointer passed in from user mode. This should not be used for syscall parameters,
 * just declare them as pointers because the syscall entry code will have appropriately
 * comverted them already.
 */
typedef	__u32		compat_uptr_t;

static inline void *
compat_ptr (compat_uptr_t uptr)
{
	return (void *) (unsigned long) uptr;
}

static __inline__ void *
compat_alloc_user_space (long len)
{
	struct pt_regs *regs = ia64_task_regs(current);
	return (void *) (((regs->r12 & 0xffffffff) & -16) - len);
}

#endif /* _ASM_IA64_COMPAT_H */
