CROSS_PREFIX=m68k-atari-mint-

CC = $(CROSS_PREFIX)gcc
CFLAGS = -O2 -fomit-frame-pointer -Wall -Wstrict-prototypes -Wmissing-prototypes
CPPFLAGS =
LDFLAGS = -s

PROGRAMS = snapit.prg
LIBS = -lgem

all: $(PROGRAMS)

snapit.prg: snapit.o tga16.o tga24.o cookie.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

snapit.o: snapit.c snapit.rsh snapit.h


clean::
	$(RM) *.o *.pdb $(PROGRAMS)
