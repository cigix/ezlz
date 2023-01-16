ESCAPE ?= 0xAA

SOURCES = lib.c
OBJECTS = $(SOURCES:.c=.o)

all: libez.a

libez.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) libez.a $(OBJECTS)

.PHONY: all clean
