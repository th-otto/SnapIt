#include <gem.h>
#include <stddef.h>
#include <mint/mintbind.h>
#include "externs.h"

#define TGA_HEAD_SIZE 18
#define WORK_SIZE 16000L


static long tga16_estimate_size(const MFDB *pic, const void *palette)
{
	UNUSED(pic);
	UNUSED(palette);
	return WORK_SIZE;
}


static long tga16_write_file(const MFDB *pic, const void *palette, void *mem)
{
	unsigned char *outptr = (unsigned char *)mem;
	unsigned char *outstart;
	size_t out_size;
	size_t linesize;
	const unsigned char *inptr, *instart;
	_WORD x, y;
	_WORD planes;
	
	UNUSED(palette);
	
	outstart = outptr;
	
	*outptr++ = 0; /* length of image ID field - we don't have one */
	*outptr++ = 0; /* color map type - none */
	*outptr++ = 2; /* image type - uncompressed true color */
	*outptr++ = 0; /* color map specification */
	*outptr++ = 0;
	*outptr++ = 0;
	*outptr++ = 0;
	*outptr++ = 0;
	*outptr++ = 0; /* X-origin */
	*outptr++ = 0;
	*outptr++ = 0; /* Y-origin */
	*outptr++ = 0;
	*outptr++ = pic->fd_w; /* image width */
	*outptr++ = pic->fd_w >> 8;
	*outptr++ = pic->fd_h; /* image height */
	*outptr++ = pic->fd_h >> 8;
	*outptr++ = 16; /* bits per pixel */
	*outptr++ = 0x20; /* image descriptor: origin in upper left, no alpha */

	out_size = TGA_HEAD_SIZE;
	
	planes = pic->fd_nplanes;
	if (planes == 15)
		planes = 16;
	linesize = ((size_t)pic->fd_wdwidth * planes) << 1;
	
	instart = (const unsigned char *)pic->fd_addr;
	for (y = 0; y < pic->fd_h; y++)
	{
		inptr = instart;
		for (x = 0; x < pic->fd_w; x++)
		{
			switch (pic->fd_nplanes)
			{
			case 15:
			case 16:
				/* input:  RRRRRGGG GGGBBBBB */
				/* output: ARRRRRGG GGGBBBBB */
				*outptr++ = (inptr[1] & 0x1f) | ((inptr[1] >> 1) & 0x60) | ((inptr[0] & 1) << 7);
				*outptr++ = inptr[0] >> 1;
				inptr += 2;
				break;
			case 32:
				inptr++;
				/* fall through */
			case 24:
				/* input:  RRRRR000 GGGGGG00 BBBBB000 */
				/* output: ARRRRRGG GGGBBBBB */
				outptr[0] = ((inptr[2] & 0xf8) >> 3) | ((inptr[1] & 0x38) << 2);
				outptr[1] = ((inptr[0] & 0xf8) >> 1) | ((inptr[1] & 0xc0) >> 6);
				break;
			default:
				return -1;
			}
			out_size += 2;
			if (out_size >= (WORK_SIZE - 100))
			{
				if (Fwrite(pic->fd_r1, out_size, outstart) != out_size)
					return -1;
				outptr = outstart;
				out_size = 0;
			}
		}
		instart += linesize;
	}
	
	if (out_size > 0 && Fwrite(pic->fd_r1, out_size, outstart) != out_size)
		return -1;
	
	return 0;
}

struct converter const tga16_converter = { "tga", 0, tga16_estimate_size, tga16_write_file };
