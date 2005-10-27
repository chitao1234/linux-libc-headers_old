#!/bin/sh

cd $LLHDIR/linux-libc-headers/include

FILES=`find asm-* linux sound scsi mtd -name '*.h'`

cd $LLHDIR/2.6

diff -urN $1 $2 > $LLHDIR/diffy/full.diff

for i in $FILES; do
	diff -u $1/include/$i $2/include/$i >>$LLHDIR/diffy/specific.diff
done

diff -u $1/include/asm-generic/errno.h $2/include/asm-generic/errno.h >>$LLHDIR/diffy/specific.diff
diff -u $1/include/asm-generic/hdreg.h $2/include/asm-generic/hdreg.h >>$LLHDIR/diffy/specific.diff

cd $LLHDIR/diffy

cat full.diff|grep -B1 '^@@ -0,0'|grep '^+++'|awk '{print $2};'>add
cat full.diff|grep -B1 '^@@.*+0,0'|grep '^+++'|awk '{print $2};'>del

