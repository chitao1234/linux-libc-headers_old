#ifndef _LINUX_BYTEORDER_SWAB_H
#define _LINUX_BYTEORDER_SWAB_H

/*
 * linux/byteorder/swab.h
 * Byte-swapping, independently from CPU endianness
 *	swabXX[ps]?(foo)
 *
 * Francois-Rene Rideau <fare@tunes.org> 19971205
 *    separated swab functions from cpu_to_XX,
 *    to clean up support for bizarre-endian architectures.
 *
 * See asm-i386/byteorder.h and suches for examples of how to provide
 * architecture-dependent optimized versions
 *
 */

/* for userspace, just use glibc macros */

#include <byteswap.h>

#define ___constant_swab16(x) __bswap_constant_16(x)
#define ___constant_swab32(x) __bswap_constant_32(x)
#define ___constant_swab64(x) __bswap_constant_64(x)

#define __swab16(x) bswap_16(x)
#define __swab32(x) bswap_32(x)
#define __swab64(x) bswap_64(x)

/* ...p() and ...s() variants not defined yet - to be if they appear needed */

#endif /* _LINUX_BYTEORDER_SWAB_H */
