ver=`cat VERSION`
name="linux-libc-headers-${ver}"

tarball_install:
	mv release/${name}.tar.bz2 ~/www/linux-libc-headers/
	chmod a+r ~/www/linux-libc-headers/${name}.tar.bz2
	cp ChangeLog LICENSE README AUTHORS FAQ ~/www/linux-libc-headers/doc
	chmod a+r ~/www/linux-libc-headers/doc/*

release: VERSION
	rm -rf .tmp
	mkdir -p .tmp/${name}/doc
	[ -d release ] || mkdir release
	cp -a include .tmp/${name}
	rm -rf .tmp/${name}/include/asm-generic
	find .tmp -name '*~'|xargs rm -f
	find .tmp -name CVS|xargs rm -rf
	find .tmp -type d -empty|xargs rmdir
	cp ChangeLog LICENSE README AUTHORS FAQ .tmp/${name}/doc
	tar -cf release/${name}.tar.bz2 --bzip2 -C .tmp ${name}
	rm -rf .tmp

