#ifndef _ASMARM_PAGE_H
#define _ASMARM_PAGE_H


#define EXEC_PAGESIZE   32768

extern int getpagesize(void);
#define PAGE_SIZE ((unsigned long)getpagesize())
#define PAGE_SHIFT ((unsigned long[]){12,13,14,-1,15,-1,-1,-1,16}[PAGE_SIZE>>13])
#define PAGE_MASK		(~(PAGE_SIZE-1))

/* to align the pointer to the (next) page boundary */
#define PAGE_ALIGN(addr)	(((addr)+PAGE_SIZE-1)&PAGE_MASK)

#endif
