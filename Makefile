override CFLAGS += -Wall -Wextra -Werror

all: libez.a ezlz unezlz

libez.a:
	$(MAKE) -C lib libez.a CFLAGS="$(CFLAGS)"
	cp lib/libez.a $@

ezlz: libez.a
	$(MAKE) -C compression ezlz CFLAGS="$(CFLAGS)" EZLIBDIR="$(CURDIR)"
	cp compression/ezlz $@

unezlz: libez.a
	$(MAKE) -C decompression unezlz CFLAGS="$(CFLAGS)" EZLIBDIR="$(CURDIR)"
	cp decompression/unezlz $@

check: ezlz unezlz
	$(MAKE) -C tests check EZLZ="$(CURDIR)/ezlz" UNEZLZ="$(CURDIR)/unezlz"

clean:
	$(RM) libez.a ezlz unezlz
	$(MAKE) -C lib clean
	$(MAKE) -C compression clean
	$(MAKE) -C decompression clean
	$(MAKE) -C tests clean

.PHONY: all clean
