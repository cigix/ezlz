override CPPFLAGS += -I$(EZLIBDIR)
override LDFLAGS += -L$(EZLIBDIR)
override LDLIBS += -lez

SOURCES = unezlz.c decompress.c state.c
OBJECTS = $(SOURCES:.c=.o)

all: unezlz

unezlz: $(OBJECTS)

clean:
	$(RM) unezlz $(OBJECTS)

.PHONY: all clean
