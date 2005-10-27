#!/bin/sh

testheader()
{
	header=$1
	cat test.orig|sed -e "s,BLE,$header," >test.c
	gcc -I$LLHDIR/linux-libc-headers/include $CFLAGS test.c
}

cd $LLHDIR/skrypty/.tmp

(cd $LLHDIR/linux-libc-headers/include
rm -f asm
ln -s $1 asm)

if [ "$1" == "asm-i386" ]; then
	CFLAGS=""
	testheader $2
	if [ -f a.out ]; then
		echo "------------------- Doing i386 ANSI test -----------------------"
		CFLAGS="-ansi -pedantic -pedantic-errors"
		testheader $2
	fi
else
	CFLAGS=""
	testheader $2
fi


rm -f a.out test.c
rm -f $LLHDIR/linux-libc-headers/include/asm



