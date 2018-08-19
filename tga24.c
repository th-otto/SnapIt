#include <gem.h>
#include <stddef.h>
#include <mint/mintbind.h>
#include "externs.h"
#include "s_tga24.h"

#define TGA_HEAD_SIZE 18
#define WORK_SIZE 16000L


long tga24_estimate_size(const MFDB *pic, const _WORD palette[][3])
{
	UNUSED(pic);
	UNUSED(palette);
	return WORK_SIZE;
}


long tga24_write_file(const MFDB *pic, const _WORD palette[][3], void *mem)
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
	*outptr++ = 24; /* bits per pixel */
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
				/* output: BBBBB000 GGGGGG00 RRRRR000 */
				outptr[2] = inptr[0] & 0xf8;
				outptr[0] = (inptr[1] & 0x1f) << 3;
				outptr[1] = (inptr[1] >> 3) | ((inptr[0] & 0x07) << 5);
				outptr += 3;
				break;
			case 32:
				inptr++;
				/* fall through */
			case 24:
				outptr[2] = *inptr++;
				outptr[1] = *inptr++;
				outptr[0] = *inptr++;
				outptr += 3;
				break;
			default:
				return -1;
			}
			out_size += 3;
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
