ESCAPE ?= 0xAA

SOURCES = dict.c bytes.c bits.c io.c
OBJECTS = $(SOURCES:.c=.o)

override CPPFLAGS += -DESCAPE=$(ESCAPE)

all: libez.a

libez.a: $(OBJECTS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	$(RM) libez.a $(OBJECTS)

.PHONY: all clean
