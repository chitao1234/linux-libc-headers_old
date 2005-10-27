#ifndef __ASM_SH64_IO_H
#define __ASM_SH64_IO_H

/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the main directory of this archive
 * for more details.
 *
 * include/asm-sh64/io.h
 *
 * Copyright (C) 2000, 2001  Paolo Alberelli
 * Copyright (C) 2003  Paul Mundt
 *
 */

/*
 * Convention:
 *    read{b,w,l}/write{b,w,l} are for PCI,
 *    while in{b,w,l}/out{b,w,l} are for ISA
 * These may (will) be platform specific function.
 *
 * In addition, we have
 *   ctrl_in{b,w,l}/ctrl_out{b,w,l} for SuperH specific I/O.
 * which are processor specific. Address should be the result of
 * onchip_remap();
 */

#include <asm/cache.h>
#include <asm/system.h>
#include <asm/page.h>

#define virt_to_bus virt_to_phys
#define bus_to_virt phys_to_virt
#define page_to_bus page_to_phys

/*
 * Nothing overly special here.. instead of doing the same thing
 * over and over again, we just define a set of sh64_in/out functions
 * with an implicit size. The traditional read{b,w,l}/write{b,w,l}
 * mess is wrapped to this, as are the SH-specific ctrl_in/out routines.
 */
static inline unsigned char sh64_in8(const volatile void *addr)
{
	return *(volatile unsigned char *)addr;
}

static inline unsigned short sh64_in16(const volatile void *addr)
{
	return *(volatile unsigned short *)addr;
}

static inline unsigned int sh64_in32(const volatile void *addr)
{
	return *(volatile unsigned int *)addr;
}

static inline unsigned long long sh64_in64(const volatile void *addr)
{
	return *(volatile unsigned long long *)addr;
}

static inline void sh64_out8(unsigned char b, volatile void *addr)
{
	*(volatile unsigned char *)addr = b;
	wmb();
}

static inline void sh64_out16(unsigned short b, volatile void *addr)
{
	*(volatile unsigned short *)addr = b;
	wmb();
}

static inline void sh64_out32(unsigned int b, volatile void *addr)
{
	*(volatile unsigned int *)addr = b;
	wmb();
}

static inline void sh64_out64(unsigned long long b, volatile void *addr)
{
	*(volatile unsigned long long *)addr = b;
	wmb();
}

#define readb(addr)		sh64_in8(addr)
#define readw(addr)		sh64_in16(addr)
#define readl(addr)		sh64_in32(addr)
#define readb_relaxed(addr)	sh64_in8(addr)
#define readw_relaxed(addr)	sh64_in16(addr)
#define readl_relaxed(addr)	sh64_in32(addr)

#define writeb(b, addr)		sh64_out8(b, addr)
#define writew(b, addr)		sh64_out16(b, addr)
#define writel(b, addr)		sh64_out32(b, addr)

#define ctrl_inb(addr)		sh64_in8(ioport_map(addr, 1))
#define ctrl_inw(addr)		sh64_in16(ioport_map(addr, 2))
#define ctrl_inl(addr)		sh64_in32(ioport_map(addr, 4))

#define ctrl_outb(b, addr)	sh64_out8(b, ioport_map(addr, 1))
#define ctrl_outw(b, addr)	sh64_out16(b, ioport_map(addr, 2))
#define ctrl_outl(b, addr)	sh64_out32(b, ioport_map(addr, 4))

#define ioread8(addr)		sh64_in8(addr)
#define ioread16(addr)		sh64_in16(addr)
#define ioread32(addr)		sh64_in32(addr)
#define iowrite8(b, addr)	sh64_out8(b, addr)
#define iowrite16(b, addr)	sh64_out16(b, addr)
#define iowrite32(b, addr)	sh64_out32(b, addr)

#define inb(addr)		ctrl_inb(addr)
#define inw(addr)		ctrl_inw(addr)
#define inl(addr)		ctrl_inl(addr)
#define outb(b, addr)		ctrl_outb(b, addr)
#define outw(b, addr)		ctrl_outw(b, addr)
#define outl(b, addr)		ctrl_outl(b, addr)

void outsw(unsigned long port, const void *addr, unsigned long count);
void insw(unsigned long port, void *addr, unsigned long count);
void outsl(unsigned long port, const void *addr, unsigned long count);
void insl(unsigned long port, void *addr, unsigned long count);

void memcpy_toio(void *to, const void *from, long count);
void memcpy_fromio(void *to, void *from, long count);

#define mmiowb()

#endif /* __ASM_SH64_IO_H */
