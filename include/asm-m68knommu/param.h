#ifndef _M68KNOMMU_PARAM_H
#define _M68KNOMMU_PARAM_H


#if defined(CONFIG_CLEOPATRA)
#define	HZ 1000
#endif
#ifndef HZ
#define	HZ 100
#endif


#define EXEC_PAGESIZE	4096

#ifndef NOGROUP
#define NOGROUP		(-1)
#endif

#define MAXHOSTNAMELEN	64	/* max length of hostname */

#endif /* _M68KNOMMU_PARAM_H */
