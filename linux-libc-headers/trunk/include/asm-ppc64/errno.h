#ifndef _PPC64_ERRNO_H
#define _PPC64_ERRNO_H

/* 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef _LINUX_ERRNO_H
 #error "Do not include this header directly. Include linux/errno.h instead."
#endif

#undef	EDEADLOCK
#define	EDEADLOCK	58	/* File locking deadlock error */

#define _LAST_ERRNO	516

#endif
