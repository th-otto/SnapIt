#include <gem.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <mint/mintbind.h>
#define JPEG_INTERNAL_OPTIONS
#undef INLINE
#undef LOCAL
#undef GLOBAL
#undef EXTERN
#ifdef JPEG_SLB
#include <slb/jpeg.h>
#else
#include <jpeglib.h>
#endif
#include <jerror.h>
#undef INLINE
#undef LOCAL
#undef GLOBAL
#undef EXTERN
#include <setjmp.h>
#include "externs.h"
#include <mint/arch/nf_ops.h>



#define OUTPUT_BUF_SIZE  4096

#ifdef C_PROGRESSIVE_SUPPORTED
static boolean progressive = FALSE;
#endif
static boolean force_baseline = FALSE;
static int quality = 75;


struct my_error_mgr {
	struct jpeg_error_mgr pub;
	jmp_buf errjmp;
};

struct my_destination_mgr {
	struct jpeg_destination_mgr pub; /* public fields */
	int outfile;		/* target stream */
	JOCTET *buffer;		/* start of buffer */
};



METHODDEF(void) my_error_exit(j_common_ptr cinfo)
{
	struct my_error_mgr *err = (struct my_error_mgr *)cinfo->err;
	err->pub.output_message(cinfo);
	longjmp(err->errjmp, 1);
}


METHODDEF(void) my_output_message(j_common_ptr cinfo)
{
	struct my_error_mgr *err = (struct my_error_mgr *)cinfo->err;
	char buffer[JMSG_LENGTH_MAX];

	err->pub.format_message(cinfo, buffer);
	safe_alert(buffer);
}


METHODDEF(void) fd_init_destination(j_compress_ptr cinfo)
{
	struct my_destination_mgr *dest = (struct my_destination_mgr *) cinfo->dest;

	/* Allocate the output buffer --- it will be released when done with image */
	dest->buffer = (JOCTET *)(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_IMAGE, OUTPUT_BUF_SIZE * sizeof(JOCTET));

	dest->pub.next_output_byte = dest->buffer;
	dest->pub.free_in_buffer = OUTPUT_BUF_SIZE;
}


METHODDEF(void) fd_term_destination(j_compress_ptr cinfo)
{
	struct my_destination_mgr *dest = (struct my_destination_mgr *) cinfo->dest;
	size_t datacount = OUTPUT_BUF_SIZE - dest->pub.free_in_buffer;

	/* Write any data remaining in the buffer */
	if (datacount > 0)
	{
		if (Fwrite(dest->outfile, datacount, dest->buffer) != datacount)
			ERREXIT(cinfo, JERR_FILE_WRITE);
	}
}


METHODDEF(boolean) fd_empty_buffer(j_compress_ptr cinfo)
{
	struct my_destination_mgr *dest = (struct my_destination_mgr *) cinfo->dest;
	dest->pub.free_in_buffer = 0;
	fd_term_destination(cinfo);
	return TRUE;
}


static void jpeg_fd_dest(j_compress_ptr cinfo, int outfile)
{
	struct my_destination_mgr *dest;

	cinfo->dest = (struct jpeg_destination_mgr *)
	(*cinfo->mem->alloc_small) ((j_common_ptr) cinfo, JPOOL_PERMANENT, sizeof(struct my_destination_mgr));

	dest = (struct my_destination_mgr *) cinfo->dest;
	dest->pub.init_destination = fd_init_destination;
	dest->pub.empty_output_buffer = fd_empty_buffer;
	dest->pub.term_destination = fd_term_destination;
	dest->outfile = outfile;
}


static void get_32bit_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w)
{
	_WORD x;
	
	for (x = w; x > 0; x--)
	{
		inptr++;
		*outptr++ = *inptr++;
		*outptr++ = *inptr++;
		*outptr++ = *inptr++;
	}
}


static void get_24bit_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w)
{
	_WORD x;
	
	for (x = w; x > 0; x--)
	{
		*outptr++ = *inptr++;
		*outptr++ = *inptr++;
		*outptr++ = *inptr++;
	}
}


static void get_16bit_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w)
{
	_WORD x;
	
	for (x = w; x > 0; x--)
	{
		/* input:  RRRRRGGG GGGBBBBB */
		/* output: RRRRR000 GGGGGG00 BBBBB000 */
		*outptr++ = rgb5tab[(inptr[0] >> 3) & 0x1f];
		*outptr++ = rgb6tab[(inptr[1] >> 5) | ((inptr[0] & 0x07) << 3)];
		*outptr++ = rgb5tab[inptr[1] & 0x1f];
		inptr += 2;
	}
}


static void get_chunky_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w, const struct rgb *pal)
{
	_WORD x;
	
	for (x = w; x > 0; x--)
	{
		unsigned char c = *inptr++;
		*outptr++ = pal[c].r;
		*outptr++ = pal[c].g;
		*outptr++ = pal[c].b;
	}
}


static void get_8planes_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w, const struct rgb *pal)
{
	_WORD x;
	const unsigned short *s;
	unsigned char pel;
	unsigned short mask;
	
	s = (const unsigned short *)inptr;
	for (x = w; x > 0; x -= 16)
	{
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
			*outptr++ = pal[pel].r;
			*outptr++ = pal[pel].g;
			*outptr++ = pal[pel].b;
		}
		s += 8;
	}
}


static void get_4planes_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w, const struct rgb *pal)
{
	_WORD x;
	const unsigned short *s;
	unsigned char pel;
	unsigned short mask;
	
	s = (const unsigned short *)inptr;
	for (x = w; x > 0; x -= 16)
	{
		for (mask = 0x8000; mask; mask >>= 1)
		{
			pel = 0;
			if (s[0] & mask) pel |= 0x01;
			if (s[1] & mask) pel |= 0x02;
			if (s[2] & mask) pel |= 0x04;
			if (s[3] & mask) pel |= 0x08;
			*outptr++ = pal[pel].r;
			*outptr++ = pal[pel].g;
			*outptr++ = pal[pel].b;
		}
		s += 4;
	}
}


static void get_2planes_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w, const struct rgb *pal)
{
	_WORD x;
	const unsigned short *s;
	unsigned char pel;
	unsigned short mask;
	
	s = (const unsigned short *)inptr;
	for (x = w; x > 0; x -= 16)
	{
		for (mask = 0x8000; mask; mask >>= 1)
		{
			pel = 0;
			if (s[0] & mask) pel |= 0x01;
			if (s[1] & mask) pel |= 0x02;
			*outptr++ = pal[pel].r;
			*outptr++ = pal[pel].g;
			*outptr++ = pal[pel].b;
		}
		s += 2;
	}
}


static void get_1planes_row(const unsigned char *inptr, JSAMPROW outptr, _WORD w)
{
	_WORD x;
	const unsigned short *s;
	
	s = (const unsigned short *)inptr;
	for (x = w; x > 0; x -= 8)
	{
		unsigned char c = *s++;
		*outptr++ = c & 0x80 ? 0 : 0xff;
		*outptr++ = c & 0x40 ? 0 : 0xff;
		*outptr++ = c & 0x20 ? 0 : 0xff;
		*outptr++ = c & 0x10 ? 0 : 0xff;
		*outptr++ = c & 0x08 ? 0 : 0xff;
		*outptr++ = c & 0x04 ? 0 : 0xff;
		*outptr++ = c & 0x02 ? 0 : 0xff;
		*outptr++ = c & 0x01 ? 0 : 0xff;
	}
}


static long jpeg_write_file(const MFDB *pic, const void *palette, void *mem)
{
	struct jpeg_compress_struct _cinfo;
	struct jpeg_compress_struct *cinfo = &_cinfo;
	struct my_error_mgr jerr;
	JSAMPROW row;
	const unsigned char *instart;
	_WORD planes;
	size_t linesize;
	const struct rgb *pal = (const struct rgb *)palette;
	
#if defined(JPEG_SLB)
	{
		long err;
		if ((err = slb_jpeglib_open(NULL)) < 0)
			return err;
	}
#endif

	/* Initialize the JPEG compression object with default error handling. */
	cinfo->err = jpeg_std_error(&jerr.pub);
	jerr.pub.error_exit = my_error_exit;
	jerr.pub.output_message = my_output_message;
	jerr.pub.trace_level = 3;
	if (setjmp(jerr.errjmp) != 0)
	{
		jpeg_destroy_compress(&_cinfo);
		return -1;
	}
	
	jpeg_create_compress(cinfo);

	cinfo->in_color_space = JCS_RGB; /* arbitrary guess */
	jpeg_set_defaults(cinfo);

	if (pic->fd_nplanes == 1)
	{
		cinfo->in_color_space = JCS_GRAYSCALE;
		cinfo->input_components = 1;
	} else
	{
		cinfo->in_color_space = JCS_RGB;
		cinfo->input_components = 3;
	}
	cinfo->data_precision = 8;
	cinfo->image_width = pic->fd_w;
	cinfo->image_height = pic->fd_h;

	jpeg_fd_dest(cinfo, OUT_FD(pic));

	jpeg_default_colorspace(cinfo);

	jpeg_set_quality(cinfo, quality, force_baseline);

#ifdef C_PROGRESSIVE_SUPPORTED
	if (progressive)	/* process -progressive; -scans can override */
	{
		jpeg_simple_progression(cinfo);
	}
#endif

	jpeg_start_compress(cinfo, TRUE);
	
	row = (JSAMPROW)mem;
	planes = pic->fd_nplanes;
	if (planes == 15)
		planes = 16;
	linesize = ulmul(pic->fd_wdwidth << 1, planes);
	instart = (const unsigned char *)pic->fd_addr;
	while (cinfo->next_scanline < cinfo->image_height)
	{
		switch (planes)
		{
		case 1:
			get_1planes_row(instart, row, pic->fd_w);
			break;
		case 2:
			get_2planes_row(instart, row, pic->fd_w, pal);
			break;
		case 4:
			get_4planes_row(instart, row, pic->fd_w, pal);
			break;
		case 8:
			if (pic->fd_stand)
				get_chunky_row(instart, row, pic->fd_w, pal);
			else
				get_8planes_row(instart, row, pic->fd_w, pal);
			break;
		case 15:
		case 16:
			get_16bit_row(instart, row, pic->fd_w);
			break;
		case 24:
			get_24bit_row(instart, row, pic->fd_w);
			break;
		case 32:
			get_32bit_row(instart, row, pic->fd_w);
			break;
		}
		jpeg_write_scanlines(cinfo, &row, 1);
		instart += linesize;
	}
	
	jpeg_finish_compress(cinfo);
	jpeg_destroy_compress(cinfo);
	
	return 0;
}


static long jpeg_estimate_size(const MFDB *pic, const void *palette)
{
	UNUSED(pic);
	UNUSED(palette);
	return pic->fd_wdwidth * (16 * 3 * sizeof(JSAMPLE));
}


static void jpeg_free_mem(void)
{
#ifdef JPEG_SLB
	slb_jpeglib_close();
#endif
}


struct converter const jpeg_converter = {
	"JPEG",
	"jpg",
	CONV_1BPP|CONV_2BPP|CONV_4BPP|CONV_8BPP|CONV_CHUNKY|CONV_15BPP|CONV_16BPP|CONV_24BPP|CONV_32BPP|CONV_RGB_PALETTE,
	CONV_24BPP,
	jpeg_estimate_size,
	jpeg_write_file,
	jpeg_free_mem
};
