#ifndef _ALPHA_ERRNO_H
#define _ALPHA_ERRNO_H

#ifndef _LINUX_ERRNO_H
 #include <linux/errno.h>
#endif

#undef	EAGAIN
#undef	EDEADLK
#undef	ENAMETOOLONG
#undef	ENOLCK
#undef	ENOSYS
#undef	ENOTEMPTY
#undef	ELOOP
#undef	EWOULDBLOCK
#undef	ENOMSG
#undef	EIDRM
#undef	ECHRNG
#undef	EL2NSYNC
#undef	EL3HLT
#undef	EL3RST
#undef	ELNRNG
#undef	EUNATCH
#undef	ENOCSI
#undef	EL2HLT
#undef	EBADE
#undef	EBADR
#undef	EXFULL
#undef	ENOANO
#undef	EBADRQC
#undef	EBADSLT
#undef	EDEADLOCK
#undef	EBFONT
#undef	ENOSTR
#undef	ENODATA
#undef	ETIME
#undef	ENOSR
#undef	ENONET
#undef	ENOPKG
#undef	EREMOTE
#undef	ENOLINK
#undef	EADV
#undef	ESRMNT
#undef	ECOMM
#undef	EPROTO
#undef	EMULTIHOP
#undef	EDOTDOT
#undef	EBADMSG
#undef	EOVERFLOW
#undef	ENOTUNIQ
#undef	EBADFD
#undef	EREMCHG
#undef	ELIBACC
#undef	ELIBBAD
#undef	ELIBSCN
#undef	ELIBMAX
#undef	ELIBEXEC
#undef	EILSEQ
#undef	ERESTART
#undef	ESTRPIPE
#undef	EUSERS
#undef	ENOTSOCK
#undef	EDESTADDRREQ
#undef	EMSGSIZE
#undef	EPROTOTYPE
#undef	ENOPROTOOPT
#undef	EPROTONOSUPPORT
#undef	ESOCKTNOSUPPORT
#undef	EOPNOTSUPP
#undef	EPFNOSUPPORT
#undef	EAFNOSUPPORT
#undef	EADDRINUSE
#undef	EADDRNOTAVAIL
#undef	ENETDOWN
#undef	ENETUNREACH
#undef	ENETRESET
#undef	ECONNABORTED
#undef	ECONNRESET
#undef	ENOBUFS
#undef	EISCONN
#undef	ENOTCONN
#undef	ESHUTDOWN
#undef	ETOOMANYREFS
#undef	ETIMEDOUT
#undef	ECONNREFUSED
#undef	EHOSTDOWN
#undef	EHOSTUNREACH
#undef	EALREADY
#undef	EINPROGRESS
#undef	ESTALE
#undef	EUCLEAN
#undef	ENOTNAM
#undef	ENAVAIL
#undef	EISNAM
#undef	EREMOTEIO
#undef	EDQUOT
#undef	ENOMEDIUM
#undef	EMEDIUMTYPE

#define	EDEADLK		11	/* Resource deadlock would occur */
#define	EAGAIN		35	/* Try again */
#define	EWOULDBLOCK	EAGAIN	/* Operation would block */
#define	EINPROGRESS	36	/* Operation now in progress */
#define	EALREADY	37	/* Operation already in progress */
#define	ENOTSOCK	38	/* Socket operation on non-socket */
#define	EDESTADDRREQ	39	/* Destination address required */
#define	EMSGSIZE	40	/* Message too long */
#define	EPROTOTYPE	41	/* Protocol wrong type for socket */
#define	ENOPROTOOPT	42	/* Protocol not available */
#define	EPROTONOSUPPORT	43	/* Protocol not supported */
#define	ESOCKTNOSUPPORT	44	/* Socket type not supported */
#define	EOPNOTSUPP	45	/* Operation not supported on transport endpoint */
#define	EPFNOSUPPORT	46	/* Protocol family not supported */
#define	EAFNOSUPPORT	47	/* Address family not supported by protocol */
#define	EADDRINUSE	48	/* Address already in use */
#define	EADDRNOTAVAIL	49	/* Cannot assign requested address */
#define	ENETDOWN	50	/* Network is down */
#define	ENETUNREACH	51	/* Network is unreachable */
#define	ENETRESET	52	/* Network dropped connection because of reset */
#define	ECONNABORTED	53	/* Software caused connection abort */
#define	ECONNRESET	54	/* Connection reset by peer */
#define	ENOBUFS		55	/* No buffer space available */
#define	EISCONN		56	/* Transport endpoint is already connected */
#define	ENOTCONN	57	/* Transport endpoint is not connected */
#define	ESHUTDOWN	58	/* Cannot send after transport endpoint shutdown */
#define	ETOOMANYREFS	59	/* Too many references: cannot splice */
#define	ETIMEDOUT	60	/* Connection timed out */
#define	ECONNREFUSED	61	/* Connection refused */
#define	ELOOP		62	/* Too many symbolic links encountered */
#define	ENAMETOOLONG	63	/* File name too long */
#define	EHOSTDOWN	64	/* Host is down */
#define	EHOSTUNREACH	65	/* No route to host */
#define	ENOTEMPTY	66	/* Directory not empty */

#define	EUSERS		68	/* Too many users */
#define	EDQUOT		69	/* Quota exceeded */
#define	ESTALE		70	/* Stale NFS file handle */
#define	EREMOTE		71	/* Object is remote */

#define	ENOLCK		77	/* No record locks available */
#define	ENOSYS		78	/* Function not implemented */

#define	ENOMSG		80	/* No message of desired type */
#define	EIDRM		81	/* Identifier removed */
#define	ENOSR		82	/* Out of streams resources */
#define	ETIME		83	/* Timer expired */
#define	EBADMSG		84	/* Not a data message */
#define	EPROTO		85	/* Protocol error */
#define	ENODATA		86	/* No data available */
#define	ENOSTR		87	/* Device not a stream */

#define	ENOPKG		92	/* Package not installed */

#define	EILSEQ		116	/* Illegal byte sequence */

/* The following are just random noise.. */
#define	ECHRNG		88	/* Channel number out of range */
#define	EL2NSYNC	89	/* Level 2 not synchronized */
#define	EL3HLT		90	/* Level 3 halted */
#define	EL3RST		91	/* Level 3 reset */

#define	ELNRNG		93	/* Link number out of range */
#define	EUNATCH		94	/* Protocol driver not attached */
#define	ENOCSI		95	/* No CSI structure available */
#define	EL2HLT		96	/* Level 2 halted */
#define	EBADE		97	/* Invalid exchange */
#define	EBADR		98	/* Invalid request descriptor */
#define	EXFULL		99	/* Exchange full */
#define	ENOANO		100	/* No anode */
#define	EBADRQC		101	/* Invalid request code */
#define	EBADSLT		102	/* Invalid slot */

#define	EDEADLOCK	EDEADLK

#define	EBFONT		104	/* Bad font file format */
#define	ENONET		105	/* Machine is not on the network */
#define	ENOLINK		106	/* Link has been severed */
#define	EADV		107	/* Advertise error */
#define	ESRMNT		108	/* Srmount error */
#define	ECOMM		109	/* Communication error on send */
#define	EMULTIHOP	110	/* Multihop attempted */
#define	EDOTDOT		111	/* RFS specific error */
#define	EOVERFLOW	112	/* Value too large for defined data type */
#define	ENOTUNIQ	113	/* Name not unique on network */
#define	EBADFD		114	/* File descriptor in bad state */
#define	EREMCHG		115	/* Remote address changed */

#define	EUCLEAN		117	/* Structure needs cleaning */
#define	ENOTNAM		118	/* Not a XENIX named type file */
#define	ENAVAIL		119	/* No XENIX semaphores available */
#define	EISNAM		120	/* Is a named type file */
#define	EREMOTEIO	121	/* Remote I/O error */

#define	ELIBACC		122	/* Can not access a needed shared library */
#define	ELIBBAD		123	/* Accessing a corrupted shared library */
#define	ELIBSCN		124	/* .lib section in a.out corrupted */
#define	ELIBMAX		125	/* Attempting to link in too many shared libraries */
#define	ELIBEXEC	126	/* Cannot exec a shared library directly */
#define	ERESTART	127	/* Interrupted system call should be restarted */
#define	ESTRPIPE	128	/* Streams pipe error */

#define ENOMEDIUM	129	/* No medium found */
#define EMEDIUMTYPE	130	/* Wrong medium type */

#endif
