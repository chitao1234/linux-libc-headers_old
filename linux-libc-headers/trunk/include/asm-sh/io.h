#ifndef __ASM_SH_IO_H
#define __ASM_SH_IO_H

/*
 * Convention:
 *    read{b,w,l}/write{b,w,l} are for PCI,
 *    while in{b,w,l}/out{b,w,l} are for ISA
 * These may (will) be platform specific function.
 * In addition we have 'pausing' versions: in{b,w,l}_p/out{b,w,l}_p
 * and 'string' versions: ins{b,w,l}/outs{b,w,l}
 * For read{b,w,l} and write{b,w,l} there are also __raw versions, which
 * do not have a memory barrier after them.
 *
 * In addition, we have 
 *   ctrl_in{b,w,l}/ctrl_out{b,w,l} for SuperH specific I/O.
 *   which are processor specific.
 */

/*
 * We follow the Alpha convention here:
 *  __inb expands to an inline function call (which either calls via the
 *        mach_vec if generic, or a machine specific implementation)
 *  _inb  is a real function call (note ___raw fns are _ version of __raw)
 *  inb   by default expands to _inb, but the machine specific code may
 *        define it to __inb if it chooses.
 */

#include <asm/cache.h>
#include <asm/system.h>

/* These are always function calls, in both kernel and user space */
extern unsigned char	_inb (unsigned long port);
extern unsigned short	_inw (unsigned long port);
extern unsigned int	_inl (unsigned long port);
extern void		_outb (unsigned char b, unsigned long port);
extern void		_outw (unsigned short w, unsigned long port);
extern void		_outl (unsigned int l, unsigned long port);
extern unsigned char	_inb_p (unsigned long port);
extern unsigned short	_inw_p (unsigned long port);
extern unsigned int	_inl_p (unsigned long port);
extern void		_outb_p (unsigned char b, unsigned long port);
extern void		_outw_p (unsigned short w, unsigned long port);
extern void		_outl_p (unsigned int l, unsigned long port);
extern void		_insb (unsigned long port, void *dst, unsigned long count);
extern void		_insw (unsigned long port, void *dst, unsigned long count);
extern void		_insl (unsigned long port, void *dst, unsigned long count);
extern void		_outsb (unsigned long port, const void *src, unsigned long count);
extern void		_outsw (unsigned long port, const void *src, unsigned long count);
extern void		_outsl (unsigned long port, const void *src, unsigned long count);
extern unsigned char	_readb(unsigned long addr);
extern unsigned short	_readw(unsigned long addr);
extern unsigned int	_readl(unsigned long addr);
extern void		_writeb(unsigned char b, unsigned long addr);
extern void		_writew(unsigned short b, unsigned long addr);
extern void		_writel(unsigned int b, unsigned long addr);

#endif /* __ASM_SH_IO_H */
