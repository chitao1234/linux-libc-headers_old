/* $Id: param.h,v 1.1 2003/12/15 18:47:00 mmazur Exp $ */
#ifndef _ASMSPARC_PARAM_H
#define _ASMSPARC_PARAM_H

#ifdef __KERNEL__
# define HZ		100	/* Internal kernel timer frequency */
# define USER_HZ	100	/* .. some user interfaces are in "ticks" */
# define CLOCKS_PER_SEC (USER_HZ)
#endif

#ifndef HZ
#define HZ 100
#endif

#define EXEC_PAGESIZE	8192    /* Thanks for sun4's we carry baggage... */

#ifndef NGROUPS
#define NGROUPS		32
#endif

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

#endif