ver=`cat VERSION`
name="glibc-kernel-headers-${ver}"

all: release

install:
	mv release/${name} ~/www/glibc-kernel-headers/
	chmod a+r ~/www/glibc-kernel-headers/${name}

release: VERSION
	rm -rf .tmp
	mkdir -p .tmp/${name}
	mkdir release
	cp -a include .tmp/${name}
	find .tmp -name '*~'|xargs rm -f
	find .tmp -name CVS|xargs rm -rf
	tar -cf release/${name}.tar.bz2 --bzip2 -C .tmp ${name}
	rm -rf .tmp

