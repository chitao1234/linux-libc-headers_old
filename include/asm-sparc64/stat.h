/* $Id: stat.h,v 1.2 2004/01/21 19:59:58 mmazur Exp $ */
#ifndef _SPARC64_STAT_H
#define _SPARC64_STAT_H

#include <linux/types.h>

struct stat {
	unsigned   st_dev;
	ino_t   st_ino;
	mode_t  st_mode;
	short   st_nlink;
	uid_t   st_uid;
	gid_t   st_gid;
	unsigned   st_rdev;
	off_t   st_size;
	time_t  st_atime;
	time_t  st_mtime;
	time_t  st_ctime;
	off_t   st_blksize;
	off_t   st_blocks;
	unsigned long  __unused4[2];
};

#endif
