#!/bin/sh

cd $LLHDIR/skrypty/.tmp

(cd $LLHDIR/linux-libc-headers/include
rm -f asm
ln -s $1 asm)

if [ "$1" == "asm-i386" ]; then
	CFLAGS="-ansi -pedantic -pedantic-errors"
else
	CFLAGS=""
fi

cat test.orig|sed -e "s,BLE,$2," >test.c
gcc -I$LLHDIR/linux-libc-headers/include $CFLAGS -Wall test.c
rm -f a.out test.c

rm -f $LLHDIR/linux-libc-headers/include/asm



