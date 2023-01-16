all: libez.a ezlz unezlz

libez.a:
	$(MAKE) -C lib libez.a
	cp lib/libez.a $@

ezlz: libez.a
	$(MAKE) -C compression ezlz EZLIBDIR=$(CURDIR)
	cp compression/ezlz $@

unezlz: libez.a
	$(MAKE) -C decompression unezlz EZLIBDIR=$(CURDIR)
	cp decompression/unezlz $@

clean:
	$(RM) libez.a ezlz unezlz
	$(MAKE) -C lib clean
	$(MAKE) -C compression clean
	$(MAKE) -C decompression clean

.PHONY: all clean
