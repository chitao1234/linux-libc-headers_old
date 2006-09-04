#ifndef _ASM_GENERIC_BITOPS_H_
#define _ASM_GENERIC_BITOPS_H_

/*
 * For the benefit of those who are trying to port Linux to another
 * architecture, here are some C-language equivalents.  You should
 * recode these in the native assembly language, if at all possible.
 * 
 * C language equivalents written by Theodore Ts'o, 9/26/92
 */

#include <asm-generic/bitops/atomic.h>
#include <asm-generic/bitops/non-atomic.h>
#include <asm-generic/bitops/__ffs.h>
#include <asm-generic/bitops/ffz.h>
#include <asm-generic/bitops/fls.h>
#include <asm-generic/bitops/fls64.h>
#include <asm-generic/bitops/find.h>

#endif /* _ASM_GENERIC_BITOPS_H */
