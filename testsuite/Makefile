# This testsuite originally written by Daniel Jacobowitz for Debian.

TESTS = $(patsubst %.c,%.o,$(wildcard *.c))
TESTS_295 = $(patsubst %,295-%,$(TESTS))

NON_C99ANSI = cdrom.o atomic.o
TESTS_C99ANSI = $(patsubst %,c99ansi-%,$(filter-out $(NON_C99ANSI),$(TESTS)))

# Filter out tests which no one tries to use -ansi; not worth fixing.
NON_ANSI = videodev.o videodev-time.o cdrom.o rtnetlink.o atomic.o
TESTS_ANSI = $(patsubst %,ansi-%,$(filter-out $(NON_ANSI),$(TESTS)))

# Similarly for C++.
NON_CXX = netlink.o
TESTS_CXX = $(patsubst %,cc-%,$(filter-out $(NON_CXX),$(TESTS)))

NON_CXX_ANSI = $(filter-out cdrom.o,$(NON_CXX) $(NON_ANSI))
TESTS_CXX_ANSI = $(patsubst %,cc-ansi-%,$(filter-out $(NON_CXX_ANSI),$(TESTS)))

ALL_TESTS = $(TESTS) $(TESTS_295) $(TESTS_ANSI) $(TESTS_C99ANSI) $(TESTS_CXX) $(TESTS_CXX_ANSI)

TESTDIR = $(shell pwd)/../include
LOCAL_CFLAGS = -I $(TESTDIR)

WARN = -Wall -Werror -W -Wno-unused
THIS_CFLAGS =
TEST_CFLAGS = $(WARN) $(LOCAL_CFLAGS) $(THIS_CFLAGS) $(CFLAGS)

all: asm-check $(ALL_TESTS)

asm-check:
	if [ ! -e $(TESTDIR)/asm ]; then \
	  echo "You need to set an asm symlink for this arch"; \
	  exit 1; \
	fi

clean:
	rm -f $(ALL_TESTS)

%.o: %.c
	$(CC) $(TEST_CFLAGS) -o $@ -c $<

cc-%.o: %.c
	$(CXX) $(TEST_CFLAGS) -o $@ -c -x c++ $<

cc-ansi-%.o: %.c
	$(CXX) $(TEST_CFLAGS) -ansi -pedantic -o $@ -c -x c++ $<

295-%.o: %.c
	if test -x /usr/bin/gcc-2.95; then \
	  gcc-2.95 $(TEST_CFLAGS) -o $@ -c $<; \
	fi

ansi-%.o: %.c
	$(CC) $(TEST_CFLAGS) -ansi -pedantic -o $@ -c $<

c99ansi-%.o: %.c
	$(CC) $(TEST_CFLAGS) -std=c99 -pedantic -o $@ -c $<
