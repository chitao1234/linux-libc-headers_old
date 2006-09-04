/* $Id: termios.h,v 1.11 2001/06/01 08:12:11 davem Exp $ */
#ifndef _SPARC64_TERMIOS_H
#define _SPARC64_TERMIOS_H

#include <asm/ioctls.h>
#include <asm/termbits.h>

struct sunos_ttysize {
	int st_lines;   /* Lines on the terminal */
	int st_columns; /* Columns on the terminal */
};

struct winsize {
	unsigned short ws_row;
	unsigned short ws_col;
	unsigned short ws_xpixel;
	unsigned short ws_ypixel;
};

/* line disciplines */
#define N_TTY		0
#define N_SLIP		1
#define N_MOUSE		2
#define N_PPP		3
#define N_STRIP		4
#define N_AX25		5
#define N_X25		6
#define N_6PACK		7
#define N_MASC		8	/* Reserved for Mobitex module <kaz@cafe.net> */
#define N_R3964		9	/* Reserved for Simatic R3964 module */
#define N_PROFIBUS_FDL	10	/* Reserved for Profibus <Dave@mvhi.com> */
#define N_IRDA		11	/* Linux IrDa - http://irda.sourceforge.net/ */
#define N_SMSBLOCK	12	/* SMS block mode - for talking to GSM data cards about SMS messages */
#define N_HDLC		13	/* synchronous HDLC */
#define N_SYNC_PPP	14	/* synchronous PPP */
#define N_HCI		15  /* Bluetooth HCI UART */

#endif /* _SPARC64_TERMIOS_H */
