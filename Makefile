CFLAGS := $(shell pkg-config --cflags libutouch-geis)
LDFLAGS := $(shell pkg-config --libs libutouch-geis)

geis2: geis2.o 
geis2.o: geis2.c
