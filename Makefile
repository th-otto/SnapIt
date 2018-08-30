CROSS_PREFIX=m68k-atari-mint-

PNG_SHARED=1
JPEG_SHARED=1

CC = $(CROSS_PREFIX)gcc
CPU_CFLAGS =
CFLAGS = $(CPU_CFLAGS) -O2 -fomit-frame-pointer -Wall -Wstrict-prototypes -Wmissing-prototypes -Werror
CPPFLAGS =
ifeq ($(PNG_SHARED),1)
CPPFLAGS += -DPNGLIB_SLB -DZLIB_SLB
PNG_LIBS = -lpng.slb -lz.slb
else
PNG_LIBS = -lpng -lz
endif
ifeq ($(JPEG_SHARED),1)
CPPFLAGS += -DJPEG_SLB
JPEG_LIBS = -ljpeg.slb
else
JPEG_LIBS = -ljpeg
endif
LDFLAGS = -s -Wl,-stack,32k

PROGRAMS = snapit.prg
LIBS = $(PNG_LIBS) $(JPEG_LIBS) -lgem -lm

all: $(PROGRAMS)

snapit.prg: snapit.o tga16.o tga24.o img.o gif.o png.o jpeg.o tab.o cookie.o nf_ops.o nf_debug.o malloc.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

snapit.o: snapit.c snapit.rsh snapit.h


ATARI_ROOT=/windows/c/atari
SLB=$(ATARI_ROOT)/mint/slb

bindist:
	$(MAKE) DESTDIR=/tmp/t/snapit allbindist

allbindist:
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-m68020-60"
	mkdir -p $(DESTDIR)/020
	cp -a $(PROGRAMS) $(DESTDIR)/020
	cp -a $(SLB)/020/zlib.slb $(SLB)/020/pnglib16.slb $(SLB)/020/jpeg8d.slb $(DESTDIR)/020
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-mcpu=5475"
	mkdir -p $(DESTDIR)/v4e
	cp -a $(PROGRAMS) $(DESTDIR)/v4e
	cp -a $(SLB)/v4e/zlib.slb $(SLB)/v4e/pnglib16.slb $(SLB)/v4e/jpeg8d.slb $(DESTDIR)/v4e
	$(MAKE) clean
	$(MAKE) -j8 CPU_CFLAGS="-m68000"
	mkdir -p $(DESTDIR)/000
	cp -a $(PROGRAMS) $(DESTDIR)/000
	cp -a $(SLB)/000/zlib.slb $(SLB)/000/pnglib16.slb $(SLB)/000/jpeg8d.slb $(DESTDIR)/000
	cp -a $(ATARI_ROOT)/snapit.acc $(DESTDIR)/000
	$(MAKE) clean
	cp -a snapit.txt $(DESTDIR)
	cd $(DESTDIR)/..; rm -f snapit.zip; zip -r snapit.zip `basename $(DESTDIR)`

clean::
	$(RM) *.o *.pdb $(PROGRAMS)
