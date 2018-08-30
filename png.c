#include <gem.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <mint/mintbind.h>
#ifdef PNGLIB_SLB
#include <slb/png.h>
#include <slb/zlib.h>
#else
#include <png.h>
#include <zlib.h>
#endif
#include <setjmp.h>
#include "externs.h"

#define USE_STDIO 0

typedef struct _writepng_info {
	png_structp png_ptr;
	png_infop info_ptr;
	unsigned char *image_data;
#if USE_STDIO
	FILE *outfile;
#else
	int outfile;
#endif
	jmp_buf jmpbuf;
	png_color palette[PNG_MAX_PALETTE_LENGTH];
	_UBYTE *rowbuf;
} writepng_info;


#if defined(__PUREC__) && !defined(_MINTLIB_SOURCE) && USE_STDIO
FILE *fdopen(int sfd, const char *mode)
{
	FILE *newfd;

	newfd = fopen("CON:", mode);
	if (newfd)
	{
		newfd->Handle = sfd;
		newfd->Flags |= 8; /* _FIOBUF */
	}
	return newfd;
}
#endif


static void __CDECL writepng_error_handler(png_structp png_ptr, png_const_charp msg)
{
	writepng_info *wpnginfo;

	(void) msg;
	
	/* This function, aside from the extra step of retrieving the "error
	 * pointer" (below) and the fact that it exists within the application
	 * rather than within libpng, is essentially identical to libpng's
	 * default error handler.  The second point is critical:  since both
	 * setjmp() and longjmp() are called from the same code, they are
	 * guaranteed to have compatible notions of how big a jmp_buf is,
	 * regardless of whether _BSD_SOURCE or anything else has (or has not)
	 * been defined. */

	wpnginfo = (writepng_info *)png_get_error_ptr(png_ptr);
	if (wpnginfo == NULL)
	{									/* we are completely hosed now */
#if 0
		fprintf(stderr, "writepng severe error:  jmpbuf not recoverable; terminating.\n");
		fflush(stderr);
#endif
		exit(99);
	}

	/* Now we have our data structure we can use the information in it
	 * to return control to our own higher level code (all the points
	 * where 'setjmp' is called in this file.)  This will work with other
	 * error handling mechanisms as well - libpng always calls png_error
	 * when it can proceed no further, thus, so long as the error handler
	 * is intercepted, application code can do its own error recovery.
	 */
	longjmp(wpnginfo->jmpbuf, 1);
}



static void __CDECL writepng_warning_handler(png_structp png_ptr, png_const_charp msg)
{
	/*
	 * Silently ignore any warning messages from libpng.
	 * They stupidly tend to introduce new warnings with every release,
	 * with the default warning handler writing to stdout and/or stderr,
	 * messing up the output.
	 */
	(void) png_ptr;
	(void) msg;
}



static void writepng_exit(writepng_info *wpnginfo)
{
	if (wpnginfo)
	{
		if (wpnginfo->png_ptr && wpnginfo->info_ptr)
			png_destroy_write_struct(&wpnginfo->png_ptr, &wpnginfo->info_ptr);
		free(wpnginfo->rowbuf);
		free(wpnginfo);
	}
}


#if !USE_STDIO
/*
 * needed even if it does nothing,
 * because otherwise the default routine,
 * using FILE structure, will be used
 */
static void __CDECL writepng_flushdata(png_struct *png_ptr)
{
	UNUSED(png_ptr);
}


static void __CDECL writepng_writedata(png_struct *png_ptr, png_bytep data, png_size_t size)
{
	writepng_info *wpnginfo = (writepng_info *)png_get_io_ptr(png_ptr);
	long ret = Fwrite(wpnginfo->outfile, size, data);
	if (ret != size)
		png_error(png_ptr, "Write error");
}
#endif


static long png_write_file(const MFDB *pic, const void *palette, void *mem)
{
	png_structp png_ptr;				/* note:  temporary variables! */
	png_infop info_ptr;
	int color_type, interlace_type;
	writepng_info *wpnginfo;
	unsigned long srcrowbytes;
	const struct rgb *pal = (const struct rgb *)palette;
	int num_palette = 0;
	
	UNUSED(mem);

#if defined(PNGLIB_SLB)
	{
		long err;
		if ((err = slb_pnglib_open(NULL)) < 0)
			return err;
	}
#endif

	wpnginfo = (writepng_info *)malloc(sizeof(*wpnginfo));
	if (wpnginfo == NULL)
		return -ENOMEM;
	memset(wpnginfo, 0, sizeof(*wpnginfo));

	wpnginfo->image_data = (unsigned char *)pic->fd_addr;

	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, wpnginfo, writepng_error_handler, writepng_warning_handler);
	if (!png_ptr)
	{
		free(wpnginfo);
		return -ENOMEM;						/* out of memory */
	}
	
	info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_write_struct(&png_ptr, NULL);
		free(wpnginfo);
		return -ENOMEM;						/* out of memory */
	}

	/* make sure we save our pointers for use in writepng_encode_image() */

	wpnginfo->png_ptr = png_ptr;
	wpnginfo->info_ptr = info_ptr;


	/* setjmp() must be called in every function that calls a PNG-writing
	 * libpng function, unless an alternate error handler was installed--
	 * but compatible error handlers must either use longjmp() themselves
	 * (as in this program) or some other method to return control to
	 * application code, so here we go: */

	if (setjmp(wpnginfo->jmpbuf))
	{
		writepng_exit(wpnginfo);
		return -1;
	}

#if USE_STDIO
	wpnginfo->outfile = fdopen(OUT_FD(pic), "wb");
	png_init_io(png_ptr, wpnginfo->outfile);
#else
	wpnginfo->outfile = OUT_FD(pic);
	png_set_write_fn(png_ptr, wpnginfo, writepng_writedata, writepng_flushdata);
#endif

	png_set_compression_level(png_ptr, Z_BEST_COMPRESSION);

	if (pic->fd_nplanes <= 8)
	{
		int i;
		
		color_type = pic->fd_nplanes > 1 ? PNG_COLOR_TYPE_PALETTE : PNG_COLOR_TYPE_GRAY;
		srcrowbytes = ulmul(pic->fd_wdwidth << 1, pic->fd_nplanes);
		num_palette = 1 << pic->fd_nplanes;
		for (i = 0; i < num_palette; i++)
		{
			wpnginfo->palette[i].red = pal[i].r;
			wpnginfo->palette[i].green = pal[i].g;
			wpnginfo->palette[i].blue = pal[i].b;
		}
		if (pic->fd_nplanes != 8 || !pic->fd_stand || OUT_FORCE_TRUECOLOR(pic))
		{
			unsigned long linebufsize = (unsigned long)(pic->fd_wdwidth) << 4;
			
			if (OUT_FORCE_TRUECOLOR(pic))
			{
				linebufsize *= 3;
				color_type = PNG_COLOR_TYPE_RGB;
			}
			wpnginfo->rowbuf = malloc(linebufsize);
			if (wpnginfo->rowbuf == NULL)
			{
				writepng_exit(wpnginfo);
				return -ENOMEM;
			}
		}
	} else if (pic->fd_nplanes == 15 || pic->fd_nplanes == 16 || pic->fd_nplanes == 24)
	{
		color_type = PNG_COLOR_TYPE_RGB;
		if (pic->fd_nplanes == 24)
		{
			srcrowbytes = ulmul(pic->fd_wdwidth << 1, 24);
		} else
		{
			unsigned long linebufsize;
			
			srcrowbytes = ulmul(pic->fd_wdwidth << 1, 16);
			linebufsize = (srcrowbytes >> 1) * 3;
			wpnginfo->rowbuf = malloc(linebufsize);
			if (wpnginfo->rowbuf == NULL)
			{
				writepng_exit(wpnginfo);
				return -ENOMEM;
			}
		}
	} else if (pic->fd_nplanes == 32)
	{
		unsigned long linebufsize;
		
		color_type = PNG_COLOR_TYPE_RGB;
		srcrowbytes = ulmul(pic->fd_wdwidth << 1, 32);
		linebufsize = (srcrowbytes >> 1) * 3;
		wpnginfo->rowbuf = malloc(linebufsize);
		if (wpnginfo->rowbuf == NULL)
		{
			writepng_exit(wpnginfo);
			return -ENOMEM;
		}
	} else
	{
		writepng_exit(wpnginfo);
		return -EINVAL;
	}

	interlace_type = FALSE ? PNG_INTERLACE_ADAM7 : PNG_INTERLACE_NONE;

	png_set_IHDR(png_ptr, info_ptr, pic->fd_w, pic->fd_h,
				 8, color_type, interlace_type,
				 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

	if (num_palette && color_type == PNG_COLOR_TYPE_PALETTE)
	{
		png_set_PLTE(png_ptr, info_ptr, wpnginfo->palette, num_palette);
	}
	
	{
		png_time modtime;
		time_t t;
		
		time(&t);
		png_convert_from_time_t(&modtime, t);
		png_set_tIME(png_ptr, info_ptr, &modtime);
	}

	png_write_info(png_ptr, info_ptr);

	png_set_packing(png_ptr);

	{
		_WORD x, y;
		unsigned char *image_data = wpnginfo->image_data;
		
		for (y = pic->fd_h; y > 0; --y)
		{
			unsigned char *p;
			unsigned char *s;
			
			if (pic->fd_nplanes <= 8 && OUT_FORCE_TRUECOLOR(pic))
			{
				s = image_data;
				p = wpnginfo->rowbuf;
				for (x = pic->fd_w; x > 0; x--)
				{
					unsigned char c = *s++;
					*p++ = pal[c].r;
					*p++ = pal[c].g;
					*p++ = pal[c].b;
				}
				image_data += srcrowbytes;
				png_write_row(png_ptr, wpnginfo->rowbuf);
			} else
			{
				switch (pic->fd_nplanes)
				{
				case 1:
					{
						const unsigned char *s;
						
						p = wpnginfo->rowbuf;
						s = image_data;
						for (x = pic->fd_w; x > 0; x -= 8)
						{
							unsigned char c = *s++;
							*p++ = c & 0x80 ? 0 : 0xff;
							*p++ = c & 0x40 ? 0 : 0xff;
							*p++ = c & 0x20 ? 0 : 0xff;
							*p++ = c & 0x10 ? 0 : 0xff;
							*p++ = c & 0x08 ? 0 : 0xff;
							*p++ = c & 0x04 ? 0 : 0xff;
							*p++ = c & 0x02 ? 0 : 0xff;
							*p++ = c & 0x01 ? 0 : 0xff;
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				case 2:
					{
						const unsigned short *s;
						
						p = wpnginfo->rowbuf;
						s = (const unsigned short *)image_data;
						for (x = pic->fd_w; x > 0; x -= 16)
						{
							unsigned char pel;
							unsigned short mask;
							
							for (mask = 0x8000; mask; mask >>= 1)
							{
								pel = 0;
								if (s[ 0] & mask) pel |= 0x01;
								if (s[ 1] & mask) pel |= 0x02;
								*p++ = pel;
							}
							s += 2;
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				case 4:
					{
						const unsigned short *s;
						
						p = wpnginfo->rowbuf;
						s = (const unsigned short *)image_data;
						for (x = pic->fd_w; x > 0; x -= 16)
						{
							unsigned char pel;
							unsigned short mask;
							
							for (mask = 0x8000; mask; mask >>= 1)
							{
								pel = 0;
								if (s[ 0] & mask) pel |= 0x01;
								if (s[ 1] & mask) pel |= 0x02;
								if (s[ 2] & mask) pel |= 0x04;
								if (s[ 3] & mask) pel |= 0x08;
								*p++ = pel;
							}
							s += 4;
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				case 8:
					if (pic->fd_stand)
					{
						/* input already in chunky format */
						png_write_row(png_ptr, image_data);
					} else
					{
						const unsigned short *s;
	
						p = wpnginfo->rowbuf;
						s = (const unsigned short *)image_data;
						for (x = pic->fd_w; x > 0; x -= 16)
						{
							unsigned char pel;
							unsigned short mask;
							
							for (mask = 0x8000; mask; mask >>= 1)
							{
								pel = 0;
								if (s[0] & mask) pel |= 0x01;
								if (s[1] & mask) pel |= 0x02;
								if (s[2] & mask) pel |= 0x04;
								if (s[3] & mask) pel |= 0x08;
								if (s[4] & mask) pel |= 0x10;
								if (s[5] & mask) pel |= 0x20;
								if (s[6] & mask) pel |= 0x40;
								if (s[7] & mask) pel |= 0x80;
								*p++ = pel;
							}
							s += 8;
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				case 15:
				case 16:
					{
						const unsigned short *s;
	
						p = wpnginfo->rowbuf;
						s = (const unsigned short *)image_data;
						for (x = pic->fd_w; x > 0; x--)
						{
							unsigned short pel;
							
							/* input:  RRRRRGGG GGGBBBBB */
							/* output: RRRRR000 GGGGGG00 BBBBB000 */
							pel = *s++;
							*p++ = rgb5tab[(pel >> 11) & 0x1f];
							*p++ = rgb6tab[(pel >>  5) & 0x3f];
							*p++ = rgb5tab[(pel      ) & 0x1f];
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				case 24:
					png_write_row(png_ptr, image_data);
					break;
				case 32:
					{
						const unsigned char *s;
	
						p = wpnginfo->rowbuf;
						s = image_data;
						for (x = pic->fd_w; x > 0; x--)
						{
							s++;
							*p++ = *s++;
							*p++ = *s++;
							*p++ = *s++;
						}
						png_write_row(png_ptr, wpnginfo->rowbuf);
					}
					break;
				}
				image_data += srcrowbytes;
			}
		}
	}

	png_write_end(png_ptr, NULL);
	writepng_exit(wpnginfo);

	return 0;
}



static long png_estimate_size(const MFDB *pic, const void *palette)
{
	UNUSED(pic);
	UNUSED(palette);
	return 0;
}


static void png_free_mem(void)
{
#ifdef PNGLIB_SLB
	slb_pnglib_close();
#endif
}


struct converter const png_converter = {
	"PNG",
	"png",
	CONV_1BPP|CONV_2BPP|CONV_4BPP|CONV_8BPP|CONV_CHUNKY|CONV_15BPP|CONV_16BPP|CONV_24BPP|CONV_32BPP|CONV_RGB_PALETTE,
	CONV_CHUNKY|CONV_15BPP|CONV_16BPP|CONV_24BPP|CONV_32BPP,
	png_estimate_size,
	png_write_file,
	png_free_mem
};
