#!/bin/sh

OUT=`date +%F_%T`
OUT="$LLHDIR/zepsute/$OUT"
touch $OUT

cd $LLHDIR/skrypty/.tmp

for arch in asm-alpha asm-arm asm-arm26 asm-cris asm-h8300 \
	asm-i386 asm-ia64 asm-m32r asm-m68k asm-mips asm-parisc asm-ppc \
   	asm-ppc64 asm-s390 asm-sh asm-sh64 asm-sparc asm-sparc64 asm-um \
	asm-v850 asm-x86_64; do 
	
	(cd $LLHDIR/linux-libc-headers/include
	rm -f asm
	ln -s $arch asm)

	for file in `cd ../../linux-libc-headers/include; find sound scsi asm linux -name '*.h'`; do
		cat test.orig|sed -e "s,BLE,$file," >test.c
		(gcc -I$LLHDIR/linux-libc-headers/include -Wall test.c) >/dev/null 2>&1
		if [ ! -f a.out ]; then
			echo $arch:$file >>$OUT
		fi
		rm -f a.out test.c
	done
done

cat $OUT|sort> $OUT.tmp
mv $OUT.tmp $OUT

rm -f $LLHDIR/linux-libc-headers/include/asm



