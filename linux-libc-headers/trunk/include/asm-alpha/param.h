#ifndef _ASM_ALPHA_PARAM_H
#define _ASM_ALPHA_PARAM_H

/* ??? Gross.  I don't want to parameterize this, and supposedly the
   hardware ignores reprogramming.  We also need userland buy-in to the 
   change in HZ, since this is visible in the wait4 resources etc.  */

#ifdef __KERNEL__
/* Debian doesn't define CONFIG_ALPHA_RAWHIDE, and including
   <linux/config.h> pollutes the namespace.  */
#include <linux/config.h>
#endif

#ifndef HZ
# ifndef CONFIG_ALPHA_RAWHIDE
#  define HZ	1024
# else
#  define HZ	1200
# endif
#endif

#define USER_HZ		HZ

#define EXEC_PAGESIZE	8192

#ifndef NGROUPS
#define NGROUPS		32
#endif

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

#ifdef __KERNEL__
# define CLOCKS_PER_SEC	HZ	/* frequency at which times() counts */
#endif

#endif /* _ASM_ALPHA_PARAM_H */
