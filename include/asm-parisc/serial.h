/*
 * include/asm-parisc/serial.h
 */


/*
 * This assumes you have a 7.272727 MHz clock for your UART.
 * The documentation implies a 40Mhz clock, and elsewhere a 7Mhz clock
 * Clarified: 7.2727MHz on LASI. Not yet clarified for DINO
 */

#define LASI_BASE_BAUD ( 7272727 / 16 )
#define BASE_BAUD  LASI_BASE_BAUD

/*
 * We don't use the ISA probing code, so these entries are just to reserve
 * space.  Some example (maximal) configurations:
 * - 712 w/ additional Lasi & RJ16 ports: 4
 * - J5k w/ PCI serial cards: 2 + 4 * card ~= 34
 * A500 w/ PCI serial cards: 5 + 4 * card ~= 17
 */
 
#define STD_SERIAL_PORT_DEFNS			\
	{ 0, },		/* ttyS0 */	\
	{ 0, },		/* ttyS1 */	\
	{ 0, },		/* ttyS2 */	\
	{ 0, },		/* ttyS3 */	\
	{ 0, },		/* ttyS4 */	\
	{ 0, },		/* ttyS5 */	\
	{ 0, },		/* ttyS6 */	\
	{ 0, },		/* ttyS7 */	\
	{ 0, },		/* ttyS8 */


#define SERIAL_PORT_DFNS		\
	STD_SERIAL_PORT_DEFNS

