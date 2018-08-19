#include <gem.h>
#include <stddef.h>
#include <mint/mintbind.h>
#include "externs.h"
#include "s_img.h"

#define WORK_SIZE 0x3000L

#define IMG_HEADER_SIZE 16 /* sizeof(GEM_HEADER) */
#define IMG_HEADER_BUFSIZE (IMG_HEADER_SIZE + 6 + 256 * 3 * sizeof(_WORD))

static _WORD x1049a;
static _WORD rect_height; /* 1049c; */
static unsigned long planesize; /* 1049e */
static _WORD linebytes; /* x104a2; */
static _WORD linewords; /* x104a4; */
static _WORD x104a6;
static _WORD rect_planes; /* x104a8 */
static _WORD outfile; /* x104aa */
static _WORD x10408 = 1;



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


long img_safe_info(const MFDB *pic)
{
	UNUSED(pic);
	return 0;
}


long img_estimate_size(const MFDB *pic, const _WORD palette[][3])
{
	UNUSED(pic);
	UNUSED(palette);
	x104a6 = 0;
	return WORK_SIZE;
}


#define Putbyte(c) *outptr++ = ((_UBYTE)(c))
#ifdef __GNUC__
static __inline _UBYTE *__Putword(_UBYTE *ptr, _UWORD c)
{
	_UWORD *wptr = (_UWORD *)ptr;
	*wptr++ = c;
	return (_UBYTE *)wptr;
}
#define Putword(c) outptr = __Putword(outptr, (_UWORD)(c))
#else
#define Putword(c) *((_UWORD *)outptr)++ = ((_UWORD)(c))
#endif

long img_write_file(const MFDB *pic, const _WORD palette[][3], void *mem)
{
	_UBYTE *outptr = (_UBYTE *)mem;
	_UBYTE *outstart = outptr;
	_UWORD *inptr; /* a2 */
	_UWORD *instart; /* a3 */
	long out_size; /* d6 */
	_WORD w, h;
	_WORD planes;
	_UWORD *ptr; /* a4 */
	_UWORD remain;
	_UBYTE c, c2;
	
	outfile = pic->fd_r1;
	if (palette == 0)
		x104a6 = 0;
	
	Putword(1); /* version */
	Putword((IMG_HEADER_SIZE + x104a6) >> 1); /* header length */
	Putword(pic->fd_nplanes);
	Putword(2); /* pattern length */
	Putword(372); /* pixel width */
	Putword(372); /* pixel height */
	Putword(x10408 ? ((pic->fd_w + 15) & ~15) : pic->fd_w);
	Putword(pic->fd_h);
	
	out_size  = outptr - outstart;

	instart = (_UWORD *)pic->fd_addr;
	rect_height = pic->fd_h;
	
	planesize = ulmul(pic->fd_wdwidth, pic->fd_h) << 1;
	
	w = x10408 ? ((pic->fd_w + 15) & ~15) : pic->fd_w;
	
	planes = pic->fd_nplanes;
	if (planes > 8)
	{
		linewords = planes * pic->fd_wdwidth;
		linebytes = (planes >> 3) * w;
		planes = 1;
	} else
	{
		linebytes = (w + 7) >> 3;
		linewords = pic->fd_wdwidth;
	}
	rect_planes = planes;
	
	/*
	 * mask out the unused bits in the last word of every line
	 */
	if (planes <= 8 && (pic->fd_w & 0x0f) != 0)
	{
		_UWORD mask = (_UWORD)(0xffff0000UL >> (pic->fd_w & 0x0f));
		unsigned long lineend = ((linewords & 0xffffUL) << 1) - 2;
		_WORD h;
		
		inptr = instart;
		do
		{
			h = rect_height;
			ptr = inptr;
			do
			{
				*((_UWORD *)((_UBYTE *)ptr + lineend)) &= mask;
			} while (--h > 0);
			inptr = (_UWORD *)((_UBYTE *)inptr + planesize);
		} while (--planes > 0);
	}
	
	/* d0 = planesize; */
	/* d1 = linewords << 1; */
	x1049a = rect_planes;
	h = rect_height;
	
	if (h != 1)
	{
		_WORD linecount;
		_WORD maxlines = 254;
		_UWORD *ptr2; /* a5 */
		
		linecount = 0;
		inptr = instart;
	nextline:
		ptr = inptr;
		ptr2 = ptr + linewords;
		do
		{
			w = linewords;
			while (--w >= 0)
			{
				if (*ptr++ != *ptr2++)
					goto nomatch;
			}
			linecount++;
		} while (--h > 0 && linecount < maxlines);
	nomatch:
		if ((linecount >= maxlines || (maxlines = linecount) != 0) && --x1049a != 0)
		{
			inptr = (_UWORD *)((_UBYTE *)inptr + planesize);
			h = rect_height;
			linecount = 0;
			goto nextline;
		}
		x1049a = rect_planes;
		if (maxlines != 0)
		{
			++maxlines;
			Putbyte(0);
			Putbyte(0);
			Putbyte(0xff);
			Putbyte(maxlines);
			out_size += 4;
			--maxlines;
			rect_height -= maxlines;
			instart += ulmul(linewords, maxlines);
		}
	}
	
	ptr = instart;
	do
	{
		_WORD d4;
		_UBYTE *ptr2; /* a5 */

		ptr2 = (_UBYTE *)ptr;
		
		remain = linebytes;
		d4 = 0;
		do
		{
			if ((c = *ptr2) == 0x00 || c == 0xff)
			{
				_UBYTE bytecount;
				
				bytecount = 1;
				ptr2++;
				--remain;
				while (remain != 0 && bytecount != 127 && *ptr2 == c)
				{
					bytecount++;
					ptr2++;
					--remain;
				}
				if (d4 != 0 &&
					bytecount < 3 &&
					(bytecount == 1 ||
					 (remain != 0 &&
					  (remain < 2 ||
					   (((c2 = *ptr2) == 0x00 || c2 == 0xff) && ptr2[1] != c2)))))
				{
					ptr2 -= bytecount;
					remain += bytecount;
				} else
				{
					if (c == 0xff)
						bytecount |= 0x80;
					Putbyte(bytecount),
					out_size += 1;
					d4 = 0;
				}
			} else
			{
				
			}
		} while (0);
		/* 102b2 */
	} while (0);
	/* 102c2 */
	
	if (out_size > 0 && Fwrite(pic->fd_r1, out_size, outstart) != out_size)
		return -1;
	
	return 0;
}
