ver=`cat VERSION`
name="linux-libc-headers-${ver}"

all: release

install:
	mv release/${name}.tar.bz2 ~/www/linux-libc-headers/
	chmod a+r ~/www/linux-libc-headers/${name}.tar.bz2

release: VERSION
	rm -rf .tmp
	mkdir -p .tmp/${name}
	[ -d release ] || mkdir release
	cp -a include .tmp/${name}
	rm -rf .tmp/${name}/include/asm-generic
	find .tmp -name '*~'|xargs rm -f
	find .tmp -name CVS|xargs rm -rf
	tar -cf release/${name}.tar.bz2 --bzip2 -C .tmp ${name}
	rm -rf .tmp

