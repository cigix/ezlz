override CPPFLAGS += -I$(EZLIBDIR)
override LDFLAGS += -L$(EZLIBDIR)
override LDLIBS += -lez

SOURCES = ezlz.c compress.c state.c
OBJECTS = $(SOURCES:.c=.o)

all: ezlz

ezlz: $(OBJECTS)

clean:
	$(RM) ezlz $(OBJECTS)

.PHONY: all clean
