/*
 * linux/include/asm-arm/arch-iop3xx/timex.h
 *
 * IOP3xx architecture timex specifications
 */


#if defined(CONFIG_ARCH_IQ80321) || defined(CONFIG_ARCH_IQ31244)

#define CLOCK_TICK_RATE IOP321_TICK_RATE

#elif defined(CONFIG_ARCH_IQ80331)

#define CLOCK_TICK_RATE IOP331_TICK_RATE

#else

#error "No IOP3xx timex information for this architecture"

#endif
