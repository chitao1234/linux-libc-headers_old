#ifndef _M68K_BITOPS_H
#define _M68K_BITOPS_H
/*
 * Copyright 1992, Linus Torvalds.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the main directory of this archive
 * for more details.
 */


/*
 * Require 68020 or better.
 *
 * They use the standard big-endian m680x0 bit ordering.
 */

#define test_and_set_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_test_and_set_bit(nr, vaddr) : \
   __generic_test_and_set_bit(nr, vaddr))

extern __inline__ int __constant_test_and_set_bit(int nr,volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bset %2,%1; sne %0"
	     : "=d" (retval), "+m" (((volatile char *)vaddr)[(nr^31) >> 3])
	     : "di" (nr & 7));

	return retval;
}

extern __inline__ int __generic_test_and_set_bit(int nr,volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bfset %2@{%1:#1}; sne %0"
	     : "=d" (retval) : "d" (nr^31), "a" (vaddr) : "memory");

	return retval;
}

#define set_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_set_bit(nr, vaddr) : \
   __generic_set_bit(nr, vaddr))

#define __set_bit(nr,vaddr) set_bit(nr,vaddr) 

extern __inline__ void __constant_set_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bset %1,%0"
	     : "+m" (((volatile char *)vaddr)[(nr^31) >> 3]) : "di" (nr & 7));
}

extern __inline__ void __generic_set_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bfset %1@{%0:#1}"
	     : : "d" (nr^31), "a" (vaddr) : "memory");
}

#define test_and_clear_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_test_and_clear_bit(nr, vaddr) : \
   __generic_test_and_clear_bit(nr, vaddr))

#define __test_and_clear_bit(nr,vaddr) test_and_clear_bit(nr,vaddr)

extern __inline__ int __constant_test_and_clear_bit(int nr, volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bclr %2,%1; sne %0"
	     : "=d" (retval), "+m" (((volatile char *)vaddr)[(nr^31) >> 3])
	     : "di" (nr & 7));

	return retval;
}

extern __inline__ int __generic_test_and_clear_bit(int nr, volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bfclr %2@{%1:#1}; sne %0"
	     : "=d" (retval) : "d" (nr^31), "a" (vaddr) : "memory");

	return retval;
}

#define clear_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_clear_bit(nr, vaddr) : \
   __generic_clear_bit(nr, vaddr))
#define __clear_bit(nr,vaddr) clear_bit(nr,vaddr)

extern __inline__ void __constant_clear_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bclr %1,%0"
	     : "+m" (((volatile char *)vaddr)[(nr^31) >> 3]) : "di" (nr & 7));
}

extern __inline__ void __generic_clear_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bfclr %1@{%0:#1}"
	     : : "d" (nr^31), "a" (vaddr) : "memory");
}

#define test_and_change_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_test_and_change_bit(nr, vaddr) : \
   __generic_test_and_change_bit(nr, vaddr))

#define __test_and_change_bit(nr,vaddr) test_and_change_bit(nr,vaddr)
#define __change_bit(nr,vaddr) change_bit(nr,vaddr)

extern __inline__ int __constant_test_and_change_bit(int nr, volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bchg %2,%1; sne %0"
	     : "=d" (retval), "+m" (((volatile char *)vaddr)[(nr^31) >> 3])
	     : "di" (nr & 7));

	return retval;
}

extern __inline__ int __generic_test_and_change_bit(int nr, volatile unsigned long * vaddr)
{
	char retval;

	__asm__ __volatile__ ("bfchg %2@{%1:#1}; sne %0"
	     : "=d" (retval) : "d" (nr^31), "a" (vaddr) : "memory");

	return retval;
}

#define change_bit(nr,vaddr) \
  (__builtin_constant_p(nr) ? \
   __constant_change_bit(nr, vaddr) : \
   __generic_change_bit(nr, vaddr))

extern __inline__ void __constant_change_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bchg %1,%0"
	     : "+m" (((volatile char *)vaddr)[(nr^31) >> 3]) : "di" (nr & 7));
}

extern __inline__ void __generic_change_bit(int nr, volatile unsigned long * vaddr)
{
	__asm__ __volatile__ ("bfchg %1@{%0:#1}"
	     : : "d" (nr^31), "a" (vaddr) : "memory");
}

extern __inline__ int test_bit(int nr, const volatile unsigned long * vaddr)
{
	return ((1UL << (nr & 31)) & (((const volatile unsigned long *) vaddr)[nr >> 5])) != 0;
}

extern __inline__ int find_first_zero_bit(const unsigned long *vaddr,
					  unsigned size)
{
	const unsigned long *p = vaddr, *addr = vaddr;
	unsigned long allones = ~0UL;
	int res;
	unsigned long num;

	if (!size)
		return 0;

	size = (size >> 5) + ((size & 31) > 0);
	while (*p++ == allones)
	{
		if (--size == 0)
			return (p - addr) << 5;
	}

	num = ~*--p;
	__asm__ __volatile__ ("bfffo %1{#0,#0},%0"
			      : "=d" (res) : "d" (num & -num));
	return ((p - addr) << 5) + (res ^ 31);
}

extern __inline__ int find_next_zero_bit (const unsigned long *vaddr, int size,
				      int offset)
{
	const unsigned long *addr = vaddr;
	const unsigned long *p = addr + (offset >> 5);
	int set = 0, bit = offset & 31UL, res;

	if (offset >= size)
		return size;

	if (bit) {
		unsigned long num = ~*p & (~0UL << bit);

		/* Look for zero in first longword */
		__asm__ __volatile__ ("bfffo %1{#0,#0},%0"
				      : "=d" (res) : "d" (num & -num));
		if (res < 32)
			return (offset & ~31UL) + (res ^ 31);
                set = 32 - bit;
		p++;
	}
	/* No zero yet, search remaining full bytes for a zero */
	res = find_first_zero_bit (p, size - 32 * (p - addr));
	return (offset + set + res);
}

/*
 * ffz = Find First Zero in word. Undefined if no zero exists,
 * so code should check against ~0UL first..
 */
extern __inline__ unsigned long ffz(unsigned long word)
{
	int res;

	__asm__ __volatile__ ("bfffo %1{#0,#0},%0"
			      : "=d" (res) : "d" (~word & -~word));
	return res ^ 31;
}

#endif /* _M68K_BITOPS_H */