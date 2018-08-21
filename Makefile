CROSS_PREFIX=m68k-atari-mint-

CC = $(CROSS_PREFIX)gcc
CFLAGS = -O2 -fomit-frame-pointer -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror
CPPFLAGS = -DPNGLIB_SLB
LDFLAGS = -s -Wl,-stack,32k

PROGRAMS = snapit.prg
LIBS = -lpng.slb -lz.slb -lgem -lm

all: $(PROGRAMS)

snapit.prg: snapit.o tga16.o tga24.o img.o gif.o png.o tab.o cookie.o nf_ops.o nf_debug.o malloc.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

snapit.o: snapit.c snapit.rsh snapit.h


clean::
	$(RM) *.o *.pdb $(PROGRAMS)
