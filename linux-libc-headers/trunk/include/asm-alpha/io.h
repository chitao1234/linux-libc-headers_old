#ifndef __ALPHA_IO_H
#define __ALPHA_IO_H

/* We don't use IO slowdowns on the Alpha, but.. */
#define __SLOW_DOWN_IO	do { } while (0)
#define SLOW_DOWN_IO	do { } while (0)

/*
 * Virtual -> physical identity mapping starts at this offset
 */
#ifdef USE_48_BIT_KSEG
#define IDENT_ADDR     0xffff800000000000
#else
#define IDENT_ADDR     0xfffffc0000000000
#endif

/*
 * Define actual functions in private name-space so it's easier to
 * accommodate things like XFree or svgalib that like to define their
 * own versions of inb etc.
 */
extern void __sethae (unsigned long addr);	/* syscall */
extern void _sethae (unsigned long addr);	/* cached version */


/*
 * There are different chipsets to interface the Alpha CPUs to the world.
 */

/* Control how and what gets defined within the core logic headers.  */
#define __WANT_IO_DEF

#if defined(CONFIG_ALPHA_APECS)
# include <asm/core_apecs.h>
#elif defined(CONFIG_ALPHA_CIA)
# include <asm/core_cia.h>
#elif defined(CONFIG_ALPHA_IRONGATE)
# include <asm/core_irongate.h>
#elif defined(CONFIG_ALPHA_JENSEN)
# include <asm/jensen.h>
#elif defined(CONFIG_ALPHA_LCA)
# include <asm/core_lca.h>
#elif defined(CONFIG_ALPHA_MARVEL)
# include <asm/core_marvel.h>
#elif defined(CONFIG_ALPHA_MCPCIA)
# include <asm/core_mcpcia.h>
#elif defined(CONFIG_ALPHA_POLARIS)
# include <asm/core_polaris.h>
#elif defined(CONFIG_ALPHA_T2)
# include <asm/core_t2.h>
#elif defined(CONFIG_ALPHA_TSUNAMI)
# include <asm/core_tsunami.h>
#elif defined(CONFIG_ALPHA_TITAN)
# include <asm/core_titan.h>
#elif defined(CONFIG_ALPHA_WILDFIRE)
# include <asm/core_wildfire.h>
#else
#error "What system is this?"
#endif

#undef __WANT_IO_DEF

#endif /* GENERIC */

/*
 * The convention used for inb/outb etc. is that names starting with
 * two underscores are the inline versions, names starting with a
 * single underscore are proper functions, and names starting with a
 * letter are macros that map in some way to inline or proper function
 * versions.  Not all that pretty, but before you change it, be sure
 * to convince yourself that it won't break anything (in particular
 * module support).
 */
extern u8		_inb (unsigned long port);
extern u16		_inw (unsigned long port);
extern u32		_inl (unsigned long port);
extern void		_outb (u8 b,unsigned long port);
extern void		_outw (u16 w,unsigned long port);
extern void		_outl (u32 l,unsigned long port);
extern u8		_readb(unsigned long addr);
extern u16		_readw(unsigned long addr);
extern u32		_readl(unsigned long addr);
extern u64		_readq(unsigned long addr);
extern void		_writeb(u8 b, unsigned long addr);
extern void		_writew(u16 b, unsigned long addr);
extern void		_writel(u32 b, unsigned long addr);
extern void		_writeq(u64 b, unsigned long addr);

#endif /* __ALPHA_IO_H */
