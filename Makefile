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
	TZ=UTC svn log -v --xml | aux/svn2log.py -x ChangeLog -u aux/users -F
	cp ChangeLog LICENSE README AUTHORS FAQ .tmp/${name}/doc
	find .tmp -name '*~'|xargs rm -f
	find .tmp -name .svn|xargs rm -rf
	find .tmp -type d|xargs chmod a+rx
	chmod a+r -R .tmp
	tar -cf release/${name}.tar.bz2 --bzip2 -C .tmp ${name}
	rm -rf .tmp

