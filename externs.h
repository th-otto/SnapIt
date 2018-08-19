#ifndef FALSE
#  define FALSE 0
#  define TRUE  1
#endif

#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif

#ifndef _UWORD
#  ifdef UWORD
#    define _UWORD UWORD
#  else
#    define _UWORD unsigned short
#  endif
#endif

#ifndef _UBYTE
# ifdef UBYTE
#  define _UBYTE UBYTE
# else
#  define _UBYTE unsigned char
#  endif
#endif

#ifndef UNUSED
# define UNUSED(x) (void)(x)
#endif

#if defined(__PUREC__)
static unsigned long ulmul(unsigned short x, unsigned short y) 0xc0c1;
static long lmul(short x, short y) 0xc1c1;
#elif defined(__GNUC__) && defined(__mc68000__)
static __inline unsigned long ulmul(unsigned short x, unsigned short y)
{
	unsigned long z;
	
	__asm__ __volatile(
		" mulu.w %1,%0"
	: "=d"(z)
	: "d"(y), "0"(x)
	: "cc");
	return z;
}
static __inline long lmul(short x, short y)
{
	long z;
	
	__asm__ __volatile(
		" muls.w %1,%0"
	: "=d"(z)
	: "d"(y), "0"(x)
	: "cc");
	return z;
}
#else
#define ulmul(x, y) ((unsigned long)(x) * (unsigned long)(y))
#define lmul(x, y) ((long)(x) * (long)(y))
#endif

struct rgb {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};
typedef struct rgb RGBPALETTE[256];

struct converter {
	char ext[4];
	unsigned long flags;
	long (*estimate_size)(const MFDB *pic, const void *palette);
	long (*write_file)(const MFDB *pic, const void *palette, void *mem);
};

#define CONV_RGB_PALETTE 0x00010000UL


int Cookie_ReadJar(unsigned long id, long *value);
