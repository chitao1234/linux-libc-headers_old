#ifndef _ASMi386_PARAM_H
#define _ASMi386_PARAM_H

#ifdef __KERNEL__
# define HZ		1000		/* Internal kernel timer frequency */
# define USER_HZ	100		/* .. some user interfaces are in "ticks" */
# define CLOCKS_PER_SEC	(USER_HZ)	/* like times() */
#endif

#ifndef HZ
#define HZ sysconf(_SC_CLK_TCK)
#endif

#define EXEC_PAGESIZE	4096

#ifndef NGROUPS
#define NGROUPS		32
#endif

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

#endif