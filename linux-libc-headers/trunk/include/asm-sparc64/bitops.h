/*
 * bitops.h: Bit string operations on the V9.
 *
 * Copyright 1996, 1997 David S. Miller (davem@caip.rutgers.edu)
 */

#ifndef _SPARC64_BITOPS_H
#define _SPARC64_BITOPS_H

#include <asm/byteorder.h>

extern long ___test_and_set_bit(unsigned long nr, volatile unsigned long *addr);
extern long ___test_and_clear_bit(unsigned long nr, volatile unsigned long *addr);
extern long ___test_and_change_bit(unsigned long nr, volatile unsigned long *addr);

#define test_and_set_bit(nr,addr)	({___test_and_set_bit(nr,addr)!=0;})
#define test_and_clear_bit(nr,addr)	({___test_and_clear_bit(nr,addr)!=0;})
#define test_and_change_bit(nr,addr)	({___test_and_change_bit(nr,addr)!=0;})
#define set_bit(nr,addr)		((void)___test_and_set_bit(nr,addr))
#define clear_bit(nr,addr)		((void)___test_and_clear_bit(nr,addr))
#define change_bit(nr,addr)		((void)___test_and_change_bit(nr,addr))

/* "non-atomic" versions... */

static __inline__ void __set_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);

	*m |= (1UL << (nr & 63));
}

static __inline__ void __clear_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);

	*m &= ~(1UL << (nr & 63));
}

static __inline__ void __change_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);

	*m ^= (1UL << (nr & 63));
}

static __inline__ int __test_and_set_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);
	long old = *m;
	long mask = (1UL << (nr & 63));

	*m = (old | mask);
	return ((old & mask) != 0);
}

static __inline__ int __test_and_clear_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);
	long old = *m;
	long mask = (1UL << (nr & 63));

	*m = (old & ~mask);
	return ((old & mask) != 0);
}

static __inline__ int __test_and_change_bit(int nr, volatile unsigned long *addr)
{
	volatile unsigned long *m = addr + (nr >> 6);
	long old = *m;
	long mask = (1UL << (nr & 63));

	*m = (old ^ mask);
	return ((old & mask) != 0);
}

#define smp_mb__before_clear_bit()	do { } while(0)
#define smp_mb__after_clear_bit()	do { } while(0)

static __inline__ int test_bit(int nr, __const__ volatile unsigned long *addr)
{
	return (1UL & ((addr)[nr >> 6] >> (nr & 63))) != 0UL;
}

/* The easy/cheese version for now. */
static __inline__ unsigned long ffz(unsigned long word)
{
	unsigned long result;

	result = 0;
	while(word & 1) {
		result++;
		word >>= 1;
	}
	return result;
}

/**
 * __ffs - find first bit in word.
 * @word: The word to search
 *
 * Undefined if no bit exists, so code should check against 0 first.
 */
static __inline__ unsigned long __ffs(unsigned long word)
{
	unsigned long result = 0;

	while (!(word & 1UL)) {
		result++;
		word >>= 1;
	}
	return result;
}

/*
 * fls: find last bit set.
 */

#define fls(x) generic_fls(x)

/**
 * find_next_bit - find the next set bit in a memory region
 * @addr: The address to base the search on
 * @offset: The bitnumber to start searching at
 * @size: The maximum size to search
 */
static __inline__ unsigned long find_next_bit(unsigned long *addr, unsigned long size, unsigned long offset)
{
	unsigned long *p = addr + (offset >> 6);
	unsigned long result = offset & ~63UL;
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset &= 63UL;
	if (offset) {
		tmp = *(p++);
		tmp &= (~0UL << offset);
		if (size < 64)
			goto found_first;
		if (tmp)
			goto found_middle;
		size -= 64;
		result += 64;
	}
	while (size & ~63UL) {
		if ((tmp = *(p++)))
			goto found_middle;
		result += 64;
		size -= 64;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp &= (~0UL >> (64 - size));
	if (tmp == 0UL)        /* Are any bits set? */
		return result + size; /* Nope. */
found_middle:
	return result + __ffs(tmp);
}

/**
 * find_first_bit - find the first set bit in a memory region
 * @addr: The address to start the search at
 * @size: The maximum size to search
 *
 * Returns the bit-number of the first set bit, not the number of the byte
 * containing a bit.
 */
#define find_first_bit(addr, size) \
	find_next_bit((addr), (size), 0)

/* find_next_zero_bit() finds the first zero bit in a bit string of length
 * 'size' bits, starting the search at bit 'offset'. This is largely based
 * on Linus's ALPHA routines, which are pretty portable BTW.
 */

static __inline__ unsigned long find_next_zero_bit(unsigned long *addr, unsigned long size, unsigned long offset)
{
	unsigned long *p = addr + (offset >> 6);
	unsigned long result = offset & ~63UL;
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset &= 63UL;
	if (offset) {
		tmp = *(p++);
		tmp |= ~0UL >> (64-offset);
		if (size < 64)
			goto found_first;
		if (~tmp)
			goto found_middle;
		size -= 64;
		result += 64;
	}
	while (size & ~63UL) {
		if (~(tmp = *(p++)))
			goto found_middle;
		result += 64;
		size -= 64;
	}
	if (!size)
		return result;
	tmp = *p;

found_first:
	tmp |= ~0UL << size;
	if (tmp == ~0UL)        /* Are any bits zero? */
		return result + size; /* Nope. */
found_middle:
	return result + ffz(tmp);
}

#define find_first_zero_bit(addr, size) \
        find_next_zero_bit((addr), (size), 0)

extern long ___test_and_set_le_bit(int nr, volatile unsigned long *addr);
extern long ___test_and_clear_le_bit(int nr, volatile unsigned long *addr);

#define test_and_set_le_bit(nr,addr)	({___test_and_set_le_bit(nr,addr)!=0;})
#define test_and_clear_le_bit(nr,addr)	({___test_and_clear_le_bit(nr,addr)!=0;})
#define set_le_bit(nr,addr)		((void)___test_and_set_le_bit(nr,addr))
#define clear_le_bit(nr,addr)		((void)___test_and_clear_le_bit(nr,addr))

static __inline__ int test_le_bit(int nr, __const__ unsigned long * addr)
{
	int			mask;
	__const__ unsigned char	*ADDR = (__const__ unsigned char *) addr;

	ADDR += nr >> 3;
	mask = 1 << (nr & 0x07);
	return ((mask & *ADDR) != 0);
}

#define find_first_zero_le_bit(addr, size) \
        find_next_zero_le_bit((addr), (size), 0)

static __inline__ unsigned long find_next_zero_le_bit(unsigned long *addr, unsigned long size, unsigned long offset)
{
	unsigned long *p = addr + (offset >> 6);
	unsigned long result = offset & ~63UL;
	unsigned long tmp;

	if (offset >= size)
		return size;
	size -= result;
	offset &= 63UL;
	if(offset) {
		tmp = __swab64p(p++);
		tmp |= (~0UL >> (64-offset));
		if(size < 64)
			goto found_first;
		if(~tmp)
			goto found_middle;
		size -= 64;
		result += 64;
	}
	while(size & ~63) {
		if(~(tmp = __swab64p(p++)))
			goto found_middle;
		result += 64;
		size -= 64;
	}
	if(!size)
		return result;
	tmp = __swab64p(p);
found_first:
	tmp |= (~0UL << size);
	if (tmp == ~0UL)        /* Are any bits zero? */
		return result + size; /* Nope. */
found_middle:
	return result + ffz(tmp);
}

#endif /* defined(_SPARC64_BITOPS_H) */