#include <gem.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <mint/mintbind.h>
#include "externs.h"


#define GIFMAXVAL 255
#define MAXCMAPSIZE 256

static unsigned char const bmp_coltab8[256] = {
 255,	0,	 1,   2,   4,	6,	 3,   5,   7,	8,	 9,  10,  12,  14,	11,  13,
  16,  17,	18,  19,  20,  21,	22,  23,  24,  25,	26,  27,  28,  29,	30,  31,
  32,  33,	34,  35,  36,  37,	38,  39,  40,  41,	42,  43,  44,  45,	46,  47,
  48,  49,	50,  51,  52,  53,	54,  55,  56,  57,	58,  59,  60,  61,	62,  63,
  64,  65,	66,  67,  68,  69,	70,  71,  72,  73,	74,  75,  76,  77,	78,  79,
  80,  81,	82,  83,  84,  85,	86,  87,  88,  89,	90,  91,  92,  93,	94,  95,
  96,  97,	98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,  15
};
static unsigned char const bmp_revtab8[256] = {
   1,   2,   3,   6,   4,   7,   5,   8,   9,  10,  11,  14,  12,  15,  13, 255,
  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
  96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,   0
};

	/* FF 88 99 BB	AA EE CC DD  00 77 11 33  22 66 44 55 */
#if 0
static unsigned char const bmp_coltab4[16] = { 15,  9, 10, 11, 12, 13, 14, 8, 7, 1,  2,  3,  4,  5,  6,  0 };
static unsigned char const bmp_revtab4[16] = { 15,  9, 10, 11, 12, 13, 14, 8, 7, 1,  2,  3,  4,  5,  6,  0 };
#elif 0
static unsigned char const bmp_coltab4[16] = { 15,  1,  2,  3, 12,  5,  6, 7, 8, 9, 10, 11,  4, 13, 14,  0 };
static unsigned char const bmp_revtab4[16] = { 15,  1,  2,  3, 12,  5,  6, 7, 8, 9, 10, 11,  4, 13, 14,  0 };
#else
static unsigned char const bmp_coltab4[16] = {  0,  1,  2,  3,  4,  5,  6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
static unsigned char const bmp_revtab4[16] = {  0,  1,  2,  3,  4,  5,  6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
#endif


/*
 * a code_int must be able to hold 2**BITS values of type int, and also -1
 */
typedef int code_int;

typedef int_fast32_t count_int;

typedef int gboolean;
#define g_new0(t, n) (t *)calloc(sizeof(t), n)
#define g_renew(t, ptr, n) (t *)realloc(ptr, sizeof(t) * (n))
#define g_free(p) free(p)


struct cmap
{
	/* This is the information for the GIF colormap (aka palette). */

	int red[MAXCMAPSIZE];
	int green[MAXCMAPSIZE];
	int blue[MAXCMAPSIZE];
	/* These arrays arrays map a color index, as is found in
	   the raster part of the GIF, to an intensity value for the indicated
	   RGB component.
	 */
	int perm[MAXCMAPSIZE];
	int cmapsize;
	/* Number of entries in the GIF colormap.  I.e. number of colors
	   in the image, plus possibly one fake transparency color.
	 */
	int transparent;
	/* color index number in GIF palette of the color that is to be
	   transparent.  -1 if no color is transparent.
	 */
};


/*
 * General DEFINEs
 */

#define MAX_LZW_BITS   12

#define HSIZE  5003						/* 80% occupancy */

#define INTERLACE      0x40
#define LOCALCOLORMAP  0x80


/* should NEVER generate this code */
#define MAXCODE(n_bits)        (((code_int) 1 << (n_bits)) - 1)

#define maxmaxcode (((code_int) 1) << (MAX_LZW_BITS))


#define BitIsSet(byte, bit)      (((byte) & (bit)) != 0)

#define LM_to_uint(a,b)                        (((b)<<8)|(a))


struct byteBuffer
{
	/* Number of bytes so far in the current data block */
	unsigned int count;
	/* The current data block, under construction */
	unsigned char buffer[256];
};


struct codeBuffer
{
	unsigned int initBits;				/* user settable max # bits/code */
	unsigned int n_bits;				/* number of bits/code */
	code_int maxcode;					/* maximum code, given n_bits */

	uint_fast32_t curAccum;
	int curBits;

	int_fast32_t htab[HSIZE];
	unsigned short codetab[HSIZE];
#define HashTabOf(i)       gif->codeBuffer.htab[i]
#define CodeTabOf(i)    gif->codeBuffer.codetab[i]
};


enum pass { MULT8PLUS0, MULT8PLUS4, MULT4PLUS2, MULT2PLUS1 };


struct pixelCursor
{
	/* Width of the image, in columns */
	unsigned int width;
	/* Height of the image, in rows */
	unsigned int height;
	/* We're accessing the image in interlace fashion */
	int interlace;
	/* Number of pixels left to be read */
	uint_fast32_t nPixelsLeft;
	/* Location of pointed-to pixel, column */
	unsigned int curCol;
	/* Location of pointed-to pixel, row */
	unsigned int curRow;
	/* The interlace pass.  Undefined if !interlace */
	enum pass pass;
};



struct gif_dest
{
	/* This structure controls output of uncompressed GIF raster */
	unsigned char *outbuf;				/* The file to which to output */
	size_t outbuf_len;
	size_t outbuf_size;
	gboolean alloc_error;
	struct byteBuffer byteBuffer;		/* Where the full bytes go */
	struct codeBuffer codeBuffer;
	int width, height;
	struct pixelCursor pixelCursor;
	
	/* State for GIF code assignment */
	code_int ClearCode;					/* clear code (doesn't change) */
	code_int EOFCode;					/* EOF code (ditto) */
	code_int code_counter;				/* counts output symbols */
	code_int free_ent;					/* first unused entry */

	/*
	 * block compression parameters -- after all codes are used up,
	 * and compression rate changes, start over.
	 */
	short clear_flg;

	long int in_count;					/* length of input */
	long int out_count;					/* # of codes output (for debugging) */

	const MFDB *pic;
	short chunky;
	const struct rgb *pi_palette;
	const unsigned char *coltab;
	const unsigned char *revtab;
	const unsigned char *pixels;
};



struct stack
{
	/* Stack grows from low addresses to high addresses */
	int stack[maxmaxcode * 2];		/* array */
	int *sp;						/* stack pointer */
	int *top;						/* next word above top of stack */
};


struct gifScreen
{
	unsigned int Width;
	unsigned int Height;
	RGBPALETTE ColorMap;
	unsigned int ColorMapSize;
	/* Number of colors in the color map. */
	unsigned int ColorResolution;
	unsigned int Background;
	/* Aspect ratio of each pixel, times 64, minus 15.  (i.e. 1 => 1:4).
	   But Zero means 1:1.
	 */
	unsigned int AspectRatio;
	/* Boolean: global colormap has at least one gray color
	   (not counting black and white) 
	 */
	int hasGray;
	/* Boolean: global colormap has at least one non-gray,
	   non-black, non-white color 
	 */
	int hasColor;
};


#define WRITE_OUTTXT 0

#if WRITE_OUTTXT
static FILE *outf;
#endif



/*********************************************************************************/
/* GIF output                                                                    */
/*********************************************************************************/

static gboolean gif_enlarge(struct gif_dest *gif, size_t len)
{
	if ((gif->outbuf_len + len) > gif->outbuf_size)
	{
		size_t newsize;
		unsigned char *newbuf;

		if (gif->alloc_error)
			return FALSE;
		newsize = gif->outbuf_size + (gif->outbuf_size >> 1) + len + 1024;
		newbuf = g_renew(unsigned char, gif->outbuf, newsize);
		if (newbuf == NULL)
		{
			gif->alloc_error = TRUE;
			return FALSE;
		}
		gif->outbuf = newbuf;
		gif->outbuf_size = newsize;
	}
	return TRUE;
}

static void gif_putc(struct gif_dest *gif, unsigned char c)
{
	if (gif_enlarge(gif, 1))
		gif->outbuf[gif->outbuf_len++] = c;
}

/*
 * Write out a word to the GIF file
 */
static void Putword(struct gif_dest *gif, int w)
{
	gif_putc(gif, w & 0xff);
	gif_putc(gif, (w >> 8) & 0xff);
}


/*
 * Current location in the input pixels.
 */
static void initPixelCursor(struct pixelCursor *pixelCursor, unsigned int width, unsigned int height, int interlace)
{
	pixelCursor->width = width;
	pixelCursor->height = height;
	pixelCursor->interlace = interlace;
	pixelCursor->pass = MULT8PLUS0;
	pixelCursor->curCol = 0;
	pixelCursor->curRow = 0;
	pixelCursor->nPixelsLeft = (uint_fast32_t) width * (uint_fast32_t) height;
}


/*** ---------------------------------------------------------------------- ***/

#define toword(pixels) (((pixels) + 15) >> 4)
#define tobyte(pixels) (toword(pixels) << 1)


static unsigned long pic_rowsize(const MFDB *pic)
{
	return ulmul(tobyte(pic->fd_w), pic->fd_nplanes);
}


/*----------------------------------------------------------------------------
   Return the colormap index of the pixel at location (x,y)
-----------------------------------------------------------------------------*/
static __inline int GifGetPixel(struct gif_dest *gif, int x, int y)
{
	size_t bytes = pic_rowsize(gif->pic);
	const unsigned char *pos = gif->pixels + bytes * y;
	unsigned char mask;
	unsigned char color = 0;
	
	mask = 0x80 >> (x & 7);
	switch (gif->pic->fd_nplanes)
	{
	case 1:
		pos += (x >> 3);
		if (!(*pos & mask))
			color = 1;
		break;
	case 2:
		pos += (x >> 4) << 2;
		if (x & 0x08)
			pos++;
		if (pos[0] & mask) color |= 0x01;
		if (pos[2] & mask) color |= 0x02;
		color = gif->revtab[color];
		break;
	case 4:
		pos += (x >> 4) << 3;
		if (x & 0x08)
			pos++;
		if (pos[0] & mask) color |= 0x01;
		if (pos[2] & mask) color |= 0x02;
		if (pos[4] & mask) color |= 0x04;
		if (pos[6] & mask) color |= 0x08;
		color = gif->revtab[color];
		break;
	case 8:
		if (gif->chunky)
		{
			pos += x;
			color = *pos;
		} else
		{
			pos += (x >> 4) << 4;
			if (x & 0x08)
				pos++;
			if (pos[ 0] & mask) color |= 0x01;
			if (pos[ 2] & mask) color |= 0x02;
			if (pos[ 4] & mask) color |= 0x04;
			if (pos[ 6] & mask) color |= 0x08;
			if (pos[ 8] & mask) color |= 0x10;
			if (pos[10] & mask) color |= 0x20;
			if (pos[12] & mask) color |= 0x40;
			if (pos[14] & mask) color |= 0x80;
		}
		color = gif->revtab[color];
		break;
	}
	
	return color;
}



/*----------------------------------------------------------------------------
   Move *pixelCursorP to the next row in the interlace pattern.
-----------------------------------------------------------------------------*/
static void bumpRowInterlace(struct pixelCursor *pixelCursorP)
{
	/* There are 4 passes:
	   MULT8PLUS0: Rows 8, 16, 24, 32, etc.
	   MULT8PLUS4: Rows 4, 12, 20, 28, etc.
	   MULT4PLUS2: Rows 2, 6, 10, 14, etc.
	   MULT2PLUS1: Rows 1, 3, 5, 7, 9, etc.
	 */

	switch (pixelCursorP->pass)
	{
	case MULT8PLUS0:
		pixelCursorP->curRow += 8;
		break;
	case MULT8PLUS4:
		pixelCursorP->curRow += 8;
		break;
	case MULT4PLUS2:
		pixelCursorP->curRow += 4;
		break;
	case MULT2PLUS1:
		pixelCursorP->curRow += 2;
		break;
	}
	/* Set the proper pass for the next read.  Note that if there are
	   more than 4 rows, the sequence of passes is sequential, but
	   when there are fewer than 4, we may skip e.g. from MULT8PLUS0
	   to MULT4PLUS2.
	 */
	while (pixelCursorP->curRow >= pixelCursorP->height)
	{
		switch (pixelCursorP->pass)
		{
		case MULT8PLUS0:
			pixelCursorP->pass = MULT8PLUS4;
			pixelCursorP->curRow = 4;
			break;
		case MULT8PLUS4:
			pixelCursorP->pass = MULT4PLUS2;
			pixelCursorP->curRow = 2;
			break;
		case MULT4PLUS2:
			pixelCursorP->pass = MULT2PLUS1;
			pixelCursorP->curRow = 1;
			break;
		case MULT2PLUS1:
			/* We've read the entire image; pass and current row are
			   now undefined.
			 */
			pixelCursorP->curRow = 0;
			break;
		}
	}
}



/*----------------------------------------------------------------------------
   Bump *pixelCursorP to point to the next pixel to go into the GIF

   Must not call when there are no pixels left.
-----------------------------------------------------------------------------*/
static void bumpPixel(struct gif_dest *gif)
{
	/* Move one column to the right */
	++gif->pixelCursor.curCol;

	if (gif->pixelCursor.curCol >= gif->pixelCursor.width)
	{
		/* That pushed us past the end of a row. */
		/* Reset to the left edge ... */
		gif->pixelCursor.curCol = 0;

		/* ... of the next row */
		if (!gif->pixelCursor.interlace)
			/* Go to the following row */
			++gif->pixelCursor.curRow;
		else
			bumpRowInterlace(&gif->pixelCursor);
	}
	--gif->pixelCursor.nPixelsLeft;
}



/*----------------------------------------------------------------------------
   Return the pre-sort color index (index into the unsorted GIF color map)
   of the next pixel to be processed from the input image.

   'alpha_threshold' is the gray level such that a pixel in the alpha
   map whose value is less that that represents a transparent pixel
   in the output.
-----------------------------------------------------------------------------*/
static __inline int GIFNextPixel(struct gif_dest *gif)
{
	int r;

	if (gif->pixelCursor.nPixelsLeft == 0)
		return EOF;

	r = GifGetPixel(gif, gif->pixelCursor.curCol, gif->pixelCursor.curRow);

	bumpPixel(gif);

	return r;
}


/*----------------------------------------------------------------------------
   Write out extension for transparent color index.
-----------------------------------------------------------------------------*/
static void write_transparent_color_index_extension(struct gif_dest *gif, int Transparent)
{
	gif_putc(gif, '!');
	gif_putc(gif, 0xf9);
	gif_putc(gif, 4);
	gif_putc(gif, 1);
	gif_putc(gif, 0);
	gif_putc(gif, 0);
	gif_putc(gif, Transparent);
	gif_putc(gif, 0);
}



/*----------------------------------------------------------------------------
   Write out extension for a comment
-----------------------------------------------------------------------------*/
static void write_comment_extension(struct gif_dest *gif, const char comment[])
{
	const char *segment;

	gif_putc(gif, '!');						/* Identifies an extension */
	gif_putc(gif, 0xfe);					/* Identifies a comment */

	/* Write it out in segments no longer than 255 characters */
	for (segment = comment; segment < comment + strlen(comment); segment += 255)
	{
		int length_this_segment = (int) strlen(segment);
		if (length_this_segment > 255)
			length_this_segment = 255;
		gif_putc(gif, length_this_segment);
		if (gif_enlarge(gif, length_this_segment))
		{
			memcpy(gif->outbuf + gif->outbuf_len, segment, length_this_segment);
			gif->outbuf_len += length_this_segment;
		}
	}

	gif_putc(gif, 0);						/* No more comment blocks in this extension */
}



/***************************************************************************
 *
 *  GIFCOMPR.C       - GIF Image compression routines
 *
 *  Lempel-Ziv compression based on 'compress'.  GIF modifications by
 *  David Rowley (mgardi@watdcsu.waterloo.edu)
 *
 ***************************************************************************/

/*
 *
 * GIF Image compression - modified 'compress'
 *
 * Based on: compress.c - File compression ala IEEE Computer, June 1984.
 *
 * By Authors:  Spencer W. Thomas       (decvax!harpo!utah-cs!utah-gr!thomas)
 *              Jim McKie               (decvax!mcvax!jim)
 *              Steve Davies            (decvax!vax135!petsd!peora!srd)
 *              Ken Turkowski           (decvax!decwrl!turtlevax!ken)
 *              James A. Woods          (decvax!ihnp4!ames!jaw)
 *              Joe Orost               (decvax!vax135!petsd!joe)
 *
 */


/*
 * compress stdin to stdout
 *
 * Algorithm:  use open addressing double hashing (no chaining) on the
 * prefix code / next character combination.  We do a variant of Knuth's
 * algorithm D (vol. 3, sec. 6.4) along with G. Knott's relatively-prime
 * secondary probe.  Here, the modular division first probe is gives way
 * to a faster exclusive-or manipulation.  Also do block compression with
 * an adaptive reset, whereby the code table is cleared when the compression
 * ratio decreases, but after the table fills.  The variable-length output
 * codes are re-sized at this point, and a special CLEAR code is generated
 * for the decompressor.  Late addition:  construct the table according to
 * file size for noticeable speed improvement on small files.  Please direct
 * questions about this implementation to ames!jaw.
 */

/***************************************************************************
*                          BYTE OUTPUTTER                 
***************************************************************************/

static void byteBuffer_init(struct byteBuffer *byteBufferP)
{
	byteBufferP->count = 0;
}



/*----------------------------------------------------------------------------
   Write the current data block to the output file, then reset the current 
   data block to empty.
-----------------------------------------------------------------------------*/
static void byteBuffer_flush(struct gif_dest *gif)
{
	if (gif->byteBuffer.count > 0)
	{
		gif_putc(gif, gif->byteBuffer.count);
		if (gif_enlarge(gif, gif->byteBuffer.count))
		{
			memcpy(gif->outbuf + gif->outbuf_len, gif->byteBuffer.buffer, gif->byteBuffer.count);
			gif->outbuf_len += gif->byteBuffer.count;
		}		
		gif->byteBuffer.count = 0;
	}
}



/*----------------------------------------------------------------------------
  Add a byte to the end of the current data block, and if it is now 254
  characters, flush the data block to the output file.
-----------------------------------------------------------------------------*/
static void byteBuffer_out(struct gif_dest *gif, unsigned char c)
{
	gif->byteBuffer.buffer[gif->byteBuffer.count++] = c;
	if (gif->byteBuffer.count >= 254)
		byteBuffer_flush(gif);
}



static uint_fast32_t const masks[] = {
	0x0000, 0x0001, 0x0003, 0x0007,
	0x000F, 0x001F, 0x003F, 0x007F,
	0x00FF, 0x01FF, 0x03FF, 0x07FF,
	0x0FFF, 0x1FFF, 0x3FFF, 0x7FFF,
	0xFFFF
};


static void codeBuffer_init(struct gif_dest *gif, unsigned int initBits)
{
	gif->codeBuffer.initBits = initBits;
	gif->codeBuffer.n_bits = initBits;
	gif->codeBuffer.maxcode = MAXCODE(initBits);
	gif->codeBuffer.curAccum = 0;
	gif->codeBuffer.curBits = 0;
	gif->ClearCode = (1 << (initBits - 1));
	gif->EOFCode = gif->ClearCode + 1;
	gif->free_ent = gif->ClearCode + 2;
	gif->code_counter = gif->ClearCode + 2;
	gif->clear_flg = 0;
	gif->in_count = 1;
	gif->out_count = 0;
}



/*----------------------------------------------------------------------------
   Output one GIF code to the file, through the code buffer.

   The code is represented as n_bits bits in the file -- the lower
   n_bits bits of 'code'.

   If the code is EOF, flush the code buffer to the file.

   In some cases, change n_bits and recalculate maxcode to go with it.
-----------------------------------------------------------------------------*/
static void codeBuffer_output(struct gif_dest *gif, code_int code)
{
	/*
	   Algorithm:
	   Maintain a BITS character long buffer (so that 8 codes will
	   fit in it exactly).  Use the VAX insv instruction to insert each
	   code in turn.  When the buffer fills up empty it and start over.
	 */

	gif->codeBuffer.curAccum &= masks[gif->codeBuffer.curBits];

	if (gif->codeBuffer.curBits > 0)
		gif->codeBuffer.curAccum |= ((int_fast32_t) code << gif->codeBuffer.curBits);
	else
		gif->codeBuffer.curAccum = code;

	gif->codeBuffer.curBits += gif->codeBuffer.n_bits;

	while (gif->codeBuffer.curBits >= 8)
	{
		byteBuffer_out(gif, (unsigned int)(gif->codeBuffer.curAccum & 0xff));
		gif->codeBuffer.curAccum >>= 8;
		gif->codeBuffer.curBits -= 8;
	}

	if (gif->clear_flg)
	{
		gif->codeBuffer.n_bits = gif->codeBuffer.initBits;
		gif->codeBuffer.maxcode = MAXCODE(gif->codeBuffer.n_bits);
		gif->clear_flg = 0;
	} else if (gif->free_ent > gif->codeBuffer.maxcode)
	{
		/* The next entry is going to be too big for the code size, so
		   increase it, if possible.
		 */
		++gif->codeBuffer.n_bits;
		if (gif->codeBuffer.n_bits == MAX_LZW_BITS)
			gif->codeBuffer.maxcode = maxmaxcode;
		else
			gif->codeBuffer.maxcode = MAXCODE(gif->codeBuffer.n_bits);
	}

	if (code == gif->EOFCode)
	{
		/* We're at EOF.  Output the possible partial byte in the buffer */
		if (gif->codeBuffer.curBits > 0)
		{
			byteBuffer_out(gif, gif->codeBuffer.curAccum & 0xff);
			gif->codeBuffer.curBits = 0;
		}
		byteBuffer_flush(gif);
	}
}



/*
 * reset code table
 */
static void cl_hash(struct gif_dest *gif, int hsize)
{
	register int_fast32_t *htab_p = gif->codeBuffer.htab + hsize;
	register int_fast32_t m1 = -1;
	register int i;

	i = hsize - 16;
	do
	{
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
		*--htab_p = m1;
	} while ((i -= 16) >= 0);

	for (i += 16; i > 0; --i)
		*--htab_p = m1;
}



/*----------------------------------------------------------------------------
  Clear out the hash table
-----------------------------------------------------------------------------*/
static void cl_block(struct gif_dest *gif)
{
	cl_hash(gif, HSIZE);
	gif->free_ent = gif->ClearCode + 2;
	gif->clear_flg = 1;

	codeBuffer_output(gif, gif->ClearCode);
}



/*----------------------------------------------------------------------------
   Write the raster to file 'outfile'.

   The raster to write is 'pixels'

   Use the colormap 'cmapP' to generate the raster ('pixels' is 
   composed of RGB samples; the GIF raster is colormap indices).

   Write the raster using LZW compression.
-----------------------------------------------------------------------------*/
static void write_raster_LZW(struct gif_dest *gif)
{
	code_int ent;
	code_int disp;
	int hshift;
	int eof;

	ent = GIFNextPixel(gif);

	{
		int_fast32_t fcode;

		hshift = 0;
		for (fcode = HSIZE; fcode < 65536L; fcode *= 2L)
			++hshift;
		hshift = 8 - hshift;			/* set hash code range bound */
	}
	cl_hash(gif, HSIZE);				/* clear hash table */

	codeBuffer_output(gif, gif->ClearCode);

	eof = FALSE;
	while (!eof)
	{
		int gifpixel;

		/* The value for the pixel in the GIF image.  I.e. the colormap
		   index.  Or -1 to indicate "no more pixels."
		 */
		gifpixel = GIFNextPixel(gif);
		if (gifpixel == EOF)
			eof = TRUE;
		if (!eof)
		{
			int_fast32_t fcode = (int_fast32_t) (((int_fast32_t) gifpixel << MAX_LZW_BITS) + ent);
			code_int i;

			/* xor hashing */

			++gif->in_count;

			i = (((code_int) gifpixel << hshift) ^ ent);

			if (HashTabOf(i) == fcode)
			{
				ent = CodeTabOf(i);
				continue;
			} else if (HashTabOf(i) < 0)	/* empty slot */
				goto nomatch;
			disp = HSIZE - i;			/* secondary hash (after G. Knott) */
			if (i == 0)
				disp = 1;
		  probe:
			if ((i -= disp) < 0)
				i += HSIZE;

			if (HashTabOf(i) == fcode)
			{
				ent = CodeTabOf(i);
				continue;
			}
			if (HashTabOf(i) > 0)
				goto probe;
		  nomatch:
			codeBuffer_output(gif, ent);
			++gif->out_count;
			ent = gifpixel;
			if (gif->free_ent < maxmaxcode)
			{
				CodeTabOf(i) = gif->free_ent++;	/* code -> hashtable */
				HashTabOf(i) = fcode;
			} else
			{
				cl_block(gif);
			}
		}
	}
	/*
	 * Put out the final code.
	 */
	codeBuffer_output(gif, ent);
	++gif->out_count;
	codeBuffer_output(gif, gif->EOFCode);
}



/* Routine to convert variable-width codes into a byte stream */

static void output_uncompressed(struct gif_dest *gif, int code)
{
	/* Emit a code of n_bits bits */
	/* Uses curAccum and curBits to reblock into 8-bit bytes */
	gif->codeBuffer.curAccum |= ((int_fast32_t) code) << gif->codeBuffer.curBits;
	gif->codeBuffer.curBits += gif->codeBuffer.n_bits;

	while (gif->codeBuffer.curBits >= 8)
	{
		byteBuffer_out(gif, (unsigned int)(gif->codeBuffer.curAccum & 0xFF));
		gif->codeBuffer.curAccum >>= 8;
		gif->codeBuffer.curBits -= 8;
	}
}


/*----------------------------------------------------------------------------
   Initialize pseudo-compressor
-----------------------------------------------------------------------------*/
static void write_raster_uncompressed_init(struct gif_dest *gif)
{
	/* GIF specifies an initial Clear code */
	output_uncompressed(gif, gif->ClearCode);
}



/*----------------------------------------------------------------------------
   "Compress" one pixel value and output it as a symbol.

   'colormapIndex' must be less than gif->n_bits wide.
-----------------------------------------------------------------------------*/
static void write_raster_uncompressed_pixel(struct gif_dest *gif, unsigned int colormapIndex)
{
	output_uncompressed(gif, colormapIndex);
	/* Issue Clear codes often enough to keep the reader from ratcheting up
	 * its symbol size.
	 */
	if (gif->code_counter < gif->codeBuffer.maxcode)
	{
		++gif->code_counter;
	} else
	{
		output_uncompressed(gif, gif->ClearCode);
		gif->code_counter = gif->ClearCode + 2;	/* reset the counter */
	}
}


/* Clean up at end */
static void write_raster_uncompressed_term(struct gif_dest *gif)
{
	/* Send an EOF code */
	output_uncompressed(gif, gif->EOFCode);

	/* Flush the bit-packing buffer */
	if (gif->codeBuffer.curBits > 0)
		byteBuffer_out(gif, gif->codeBuffer.curAccum & 0xFF);

	/* Flush the packet buffer */
	byteBuffer_flush(gif);
}



/*----------------------------------------------------------------------------
   Write the raster to file 'gif'.
   
   Same as write_raster_LZW(), except written out one code per
   pixel (plus some clear codes), so no compression.  And no use
   of the LZW patent.
-----------------------------------------------------------------------------*/
static void write_raster_uncompressed(struct gif_dest *gif)
{
	/* gray levels below this in the alpha mask indicate transparent
	   pixels in the output image.
	 */
	int eof;

	write_raster_uncompressed_init(gif);

	eof = FALSE;
	while (!eof)
	{
		int gifpixel;

		/* The value for the pixel in the GIF image.  I.e. the colormap
		   index.  Or -1 to indicate "no more pixels."
		 */
		gifpixel = GIFNextPixel(gif);
		if (gifpixel == EOF)
			eof = TRUE;
		else
			write_raster_uncompressed_pixel(gif, gifpixel);
	}
	write_raster_uncompressed_term(gif);
}



/******************************************************************************
 *
 * GIF Specific routines
 *
 *****************************************************************************/

static void
writeGifHeader(struct gif_dest *gif,
	int Background,
	int BitsPerPixel, int transparent, const char comment[])
{
	int B;
	int Resolution = BitsPerPixel;
	int ColorMapSize = 1 << BitsPerPixel;

	/* Write the Magic header */
	gif_putc(gif, 'G');
	gif_putc(gif, 'I');
	gif_putc(gif, 'F');
	gif_putc(gif, '8');
	if (transparent >= 0 || comment)
		gif_putc(gif, '9');
	else
		gif_putc(gif, '7');
	gif_putc(gif, 'a');

	/* Write out the screen width and height */
	Putword(gif, gif->width);
	Putword(gif, gif->height);

	/* Indicate that there is a global color map */
	B = LOCALCOLORMAP;							/* Yes, there is a color map */

	/* OR in the resolution */
	B |= (Resolution - 1) << 4;

	/* OR in the Bits per Pixel */
	B |= (BitsPerPixel - 1);

	/* Write it out */
	gif_putc(gif, B);

	/* Write out the Background color */
	gif_putc(gif, Background);

	/* Byte of 0's (future expansion) */
	gif_putc(gif, 0);

	{
		/* Write out the Global Color Map */
		int i;

		if (Resolution == 1)
		{
			gif_putc(gif, 0);
			gif_putc(gif, 0);
			gif_putc(gif, 0);
			gif_putc(gif, GIFMAXVAL);
			gif_putc(gif, GIFMAXVAL);
			gif_putc(gif, GIFMAXVAL);
		} else
		{
			for (i = 0; i < ColorMapSize; ++i)
			{
				gif_putc(gif, gif->pi_palette[gif->coltab[i]].r);
				gif_putc(gif, gif->pi_palette[gif->coltab[i]].g);
				gif_putc(gif, gif->pi_palette[gif->coltab[i]].b);
			}
		}
	}

	if (transparent >= 0)
	{
		transparent = gif->coltab[transparent] & ((1u << gif->pic->fd_nplanes) - 1);
		write_transparent_color_index_extension(gif, transparent);
	}
	
	if (comment)
		write_comment_extension(gif, comment);
}


static void writeImageHeader(struct gif_dest *gif,
	unsigned int leftOffset,
	unsigned int topOffset,
	unsigned int initCodeSize)
{
	Putword(gif, leftOffset);
	Putword(gif, topOffset);
	Putword(gif, gif->width);
	Putword(gif, gif->height);

	/* Write out whether or not the image is interlaced */
	if (gif->pixelCursor.interlace)
		gif_putc(gif, INTERLACE);
	else
		gif_putc(gif, 0x00);

	/* Write out the initial code size */
	gif_putc(gif, initCodeSize);
}



static gboolean GIFEncode(struct gif_dest *gif, int background, const char *comment, int transparent, gboolean compressed)
{
	unsigned int leftOffset = 0;
	unsigned int topOffset = 0;

	int bitsPerPixel = gif->pic->fd_nplanes;
	/* The initial code size */
	unsigned int initCodeSize = bitsPerPixel <= 1 ? 2 : bitsPerPixel;
	
	codeBuffer_init(gif, initCodeSize + 1);
	byteBuffer_init(&gif->byteBuffer);

	writeGifHeader(gif, background, bitsPerPixel, transparent, comment);

	/* Write an Image separator */
	gif_putc(gif, ',');

	/* Write the Image header */
	writeImageHeader(gif, leftOffset, topOffset, initCodeSize);

	/* Write the actual raster */
	if (!compressed)
		write_raster_uncompressed(gif);
	else
		write_raster_LZW(gif);

	/* Write out a zero length data block (to end the series) */
	gif_putc(gif, 0);

	/* Write the GIF file terminator */
	gif_putc(gif, ';');

	return TRUE;
}


static long gif_write_file(const MFDB *pic, const void *palette, void *mem)
{
	const char *comment = NULL;
	struct gif_dest *gif;
	long ret;
	
	UNUSED(mem);
	gif = g_new0(struct gif_dest, 1);
	if (gif == NULL)
		return FALSE;
	gif->pic = pic;
	gif->width = pic->fd_w;
	gif->height = pic->fd_h;
	gif->pixels = (const unsigned char *)pic->fd_addr;
	gif->coltab =
		pic->fd_nplanes == 2 ? bmp_coltab4 :
		pic->fd_nplanes == 4 ? bmp_coltab4 :
		bmp_coltab8;
	gif->revtab =
		pic->fd_nplanes == 2 ? bmp_revtab4 :
		pic->fd_nplanes == 4 ? bmp_revtab4 :
		bmp_revtab8;
	gif->pi_palette = palette;
	gif->chunky = pic->fd_stand;
	
	/* Set some global variables for bumpPixel() */
	initPixelCursor(&gif->pixelCursor, gif->width, gif->height, FALSE);
	
	/* All set, let's do it. */
	ret = GIFEncode(gif, 0, comment, -1 , TRUE);
	if (gif->alloc_error ||
		(size_t)Fwrite(OUT_FD(pic), gif->outbuf_len, gif->outbuf) != gif->outbuf_len)
	{
		ret = -1;
	} else
	{
		ret = 0;
	}
	g_free(gif->outbuf);
	g_free(gif);
	return ret;
}


static long gif_estimate_size(const MFDB *pic, const void *palette)
{
	UNUSED(pic);
	UNUSED(palette);
	return 0;
}

struct converter const gif_converter = {
	"GIF",
	"gif",
	CONV_1BPP|CONV_2BPP|CONV_4BPP|CONV_8BPP|CONV_CHUNKY|CONV_RGB_PALETTE,
	CONV_CHUNKY,
	gif_estimate_size,
	gif_write_file,
	0
};
