#include <gem.h>
#include <stddef.h>
#include <stdlib.h>
#include <mint/mintbind.h>
#include "externs.h"

typedef struct {                /* Header fuer GEM-Bilder */
    _UBYTE version[2];          /* Versionsnummer */
    _UBYTE head_len[2];         /* Laenge des Headers in words */
    _UBYTE plane_num[2];        /* Anzahl der planes */
    _UBYTE pat_len[2];          /* Laenge der verwendeten Muster in bytes */
    _UBYTE pix_wid[2];          /* Pixelbreite des verwendeten Geraetes in um */
    _UBYTE pix_hght[2];         /* Pixelhoehe des verwendeten Geraetes in um */
    _UBYTE pix_num[2];          /* Pixel-breite einer Zeile */
    _UBYTE scan_num[2];         /* Anzahl der Zeilen */
} GEM_HEADER;

#define IMG_HEADER_SIZE 16 /* sizeof(GEM_HEADER) */
#define IMG_HEADER_BUFSIZE (IMG_HEADER_SIZE + 6 + 256 * 3 * sizeof(_WORD))


#define XIMG_MAGIC 0x58494d47l

typedef struct ximg_header {
	_UBYTE magic[4];
	_WORD model;
	_WORD palette[256][3];
} XIMG_HEADER;
#define SIZEOF_XIMG_HEADER(planes) (4 + 2 + (1 << (planes)) * 3 * 2)

#define tobyte(pixels) (((pixels) + 7) >> 3)
#define toword(pixels) ((((pixels) + 15) >> 4) << 1)


#define put_long(l) \
	*outptr++ = (_UBYTE)((l) >> 24); \
	*outptr++ = (_UBYTE)((l) >> 16); \
	*outptr++ = (_UBYTE)((l) >>  8); \
	*outptr++ = (_UBYTE)((l)      )
#define put_word(w) \
	*outptr++ = (_UBYTE)((w) >>  8); \
	*outptr++ = (_UBYTE)((w)      )
#define put_byte(b) \
	*outptr++ = (_UBYTE)(b)




static _WORD img_header_len(const MFDB *pic, const void *palette)
{
	_WORD planes = pic->fd_nplanes;
	_WORD headlen;

	headlen = IMG_HEADER_SIZE;
	if (planes > 1 && planes <= 8 && palette)
		headlen += SIZEOF_XIMG_HEADER(planes);
	
	return headlen;
}


static long img_estimate_size(const MFDB *pic, const void *palette)
{
	_WORD width = pic->fd_w;
	_WORD height = pic->fd_h;
	_WORD planes = pic->fd_nplanes;
	unsigned long size;
	_WORD headlen;

	headlen = img_header_len(pic, palette);
	size = toword(width);
	/*
	 * worst (uncompressed) case is 2 additional bytes
	 * for every 128 bytes in a line
	 */
	size += ((size + 127) / 128) * 2;
	size = size * ulmul(planes, height);
	size += headlen;
	
	return size;
}


static _WORD do_compress(const _UBYTE *start, const _UBYTE *end)
{
	_WORD i;
	_UBYTE c;

	for (i = 0, c = *start; &start[i] < end; i++)
	{
		if (start[i] != start[i & 1])
			break;
	}
	if (i < 3)
	{
		i = 0;
	} else
	{
		if ((c != 0 && c != 0xff) || start[1] != c)
		{
	 		i &= -2;
			if (i < 6)
				i = 0;
		}
	}
	return i;
}


static _UBYTE *put_uncompressed(_UBYTE *outptr, const _UBYTE *start, const _UBYTE *end)
{
	size_t n = end - start;
	
	if (n != 0)
	{
		while (n > 127)
		{
			_UBYTE c = 127;
			
			put_byte(0x80);
			c = 127;
			put_byte(c);
			while (c)
			{
				put_byte(*start);
				start++;
				c--;
			}
			n -= 127;
		}
		put_byte(0x80);
		put_byte(n);
		while (start != end)
		{
			put_byte(*start);
			start++;
		}
	}
	return outptr;
}


static _UBYTE *put_compressed(_UBYTE *outptr, const _UBYTE *start, _WORD n)
{
	_UBYTE c1;
	_UBYTE c2;

	c1 = *start++;
	c2 = *start;
	if (c1 == 0 && c2 == 0)
	{
		while (n > 127)
		{
			put_byte(127);
			n -= 127;
		}
		put_byte(n);
	} else if (c1 == 0xff && c2 == 0xff)
	{
		while (n > 127)
		{
			put_byte(0xff);
			n -= 127;
		}
		put_byte(n + 0x80);
	} else
	{
		n >>= 1;
		while (n > 127)
		{
			put_byte(0x00);
			put_byte(127);
			put_byte(c1);
			put_byte(c2);
			n -= 127;
		}
		put_byte(0x00);
		put_byte(n);
		put_byte(c1);
		put_byte(c2);
	}
	return outptr;
}


static _UBYTE *compress_line(_UBYTE *outptr, const _UBYTE *buf, _WORD rect_bytes)
{
	const _UBYTE *pend;
	const _UBYTE *start;
	const _UBYTE *lastend;
	_WORD x;

	pend = buf + rect_bytes;
	start = buf;
	lastend = buf;
	while (lastend != pend)
	{
		if ((x = do_compress(lastend, pend)) != 0)
		{
			outptr = put_uncompressed(outptr, start, lastend);
			outptr = put_compressed(outptr, lastend, x);
			lastend += x;
			start = lastend;
		} else
		{
			lastend++;
		}
	}
	outptr = put_uncompressed(outptr, start, lastend);
	return outptr;
}


static _WORD cmp_lines_standard(const _UBYTE *buf, _UWORD line_bytes, _WORD height, _WORD num_planes)
{
	_UWORD j;
	_WORD i;
	const _UBYTE *p1;
	const _UBYTE *p2;
	unsigned long plane_size;
	_WORD p;
	
	if (height > 255)
		height = 255;
	/*
	 * height - 1, because loop below already increments by 1 line
	 */
	plane_size = ulmul(line_bytes, height - 1);
	for (i = 0; i < height; i++)
	{
		p1 = buf;
		p2 = p1 + ulmul(i, line_bytes);
		for (p = 0; p < num_planes; p++)
		{
			for (j = line_bytes; j-- != 0; )
			{
				if (*p1++ != *p2++)
					return i;
			}
			p1 += plane_size;
			p2 += plane_size;
		}
	}
	return i;
}


static _WORD cmp_lines_interleaved(const _UBYTE *buf, _UWORD line_bytes, _WORD height, _WORD num_planes)
{
	_UWORD j;
	_WORD i;
	const _UBYTE *p1;
	const _UBYTE *p2;
	unsigned long plane_size;
	_WORD p;
	
	if (height > 255)
		height = 255;
	/*
	 * height - 1, because loop below already increments by 1 line
	 */
	plane_size = ulmul(line_bytes, height - 1);
	for (i = 0; i < height; i++)
	{
		p1 = buf;
		p2 = p1 + ulmul(i, line_bytes);
		for (p = 0; p < num_planes; p++)
		{
			for (j = line_bytes; j-- != 0; )
			{
				if (*p1++ != *p2++)
					return i;
			}
			p1 += plane_size;
			p2 += plane_size;
		}
	}
	return i;
}


/*
 * input is assumed to be in separate planes (standard format)
 */
static _UBYTE *img_pack_standard(
	_UBYTE *outptr,
	const _UBYTE *buf,
	_WORD rect_width,
	_WORD rect_height,
	_WORD num_planes)
{
	_WORD i;
	_WORD linecount;
	_UWORD line_size;
	unsigned long plane_size;
	const _UBYTE *line;
	
	line_size = toword(rect_width);
	plane_size = ulmul(line_size, rect_height);
	while (rect_height > 0)
	{
		linecount = cmp_lines_standard(buf, line_size, rect_height, num_planes);
		if (linecount > 1)
		{
			put_byte(0);
			put_byte(0);
			put_byte(0xff);
			put_byte(linecount);
		}
		line = buf;
		for (i = 0; i < num_planes; i++)
		{
			outptr = compress_line(outptr, line, tobyte(rect_width));
			line += plane_size;
		}
		buf += ulmul(line_size, linecount);
		rect_height -= linecount;
	}
	return outptr;
}


/*
 * input is assumed to be in interleaved planes (screen format)
 */
static _UBYTE *img_pack_interleaved(
	_UBYTE *outptr,
	const _UBYTE *buf,
	_WORD rect_width,
	_WORD rect_height,
	_WORD num_planes)
{
	_WORD i;
	_WORD linecount;
	_UWORD line_size;
	const _UBYTE *line;
	_WORD *linebuf = NULL;
	
	line_size = toword(rect_width);
	if (num_planes != 1)
	{
		linebuf = (_WORD *)malloc(line_size);
		if (linebuf == NULL)
			return outptr;
	}
	while (rect_height > 0)
	{
		linecount = cmp_lines_interleaved(buf, line_size, rect_height, num_planes);
		if (linecount > 1)
		{
			put_byte(0);
			put_byte(0);
			put_byte(0xff);
			put_byte(linecount);
		}
		line = buf;
		if (num_planes == 1)
		{
			outptr = compress_line(outptr, line, tobyte(rect_width));
			buf += ulmul(line_size, linecount);
		} else
		{
			for (i = 0; i < num_planes; i++)
			{
				const _WORD *p1;
				_WORD *p2;
				_WORD j;
				
				p2 = (_WORD *)linebuf;
				p1 = (const _WORD *)line;
				for (j = line_size >> 1; j != 0; j--)
				{
					*p2 = *p1;
					p2++;
					p1 += num_planes;
				}
				outptr = compress_line(outptr, (const _UBYTE *)linebuf, tobyte(rect_width));
				line += 2;
			}
			buf += ulmul(line_size, linecount) * num_planes;
		}
		rect_height -= linecount;
	}
	free(linebuf);
	return outptr;
}


static long img_write_file(const MFDB *pic, const void *palette, void *mem)
{
	_WORD width = pic->fd_w;
	_WORD height = pic->fd_h;
	_WORD planes = pic->fd_nplanes;
	_UBYTE *buf, *outptr;
	_WORD headlen;
	size_t size;
	
	headlen = img_header_len(pic, palette);
	
	buf = (_UBYTE *)mem;
	outptr = buf;
	
	put_word(1);			/* version */
	headlen >>= 1;
	put_word(headlen);
	put_word(planes);
	put_word(2);			/* pat_len */
	put_word(372);
	put_word(372);
	put_word(width);
	put_word(height);
	if (planes > 1 && planes <= 8 && palette)
	{
		_WORD ncolors, i;
		_WORD color;
		const _WORD *pal = (const _WORD *)palette;
		
		ncolors = (1 << planes);
		put_long(XIMG_MAGIC);
		put_word(0); /* model */
		
		for (i = 0; i < ncolors; i++)
		{
			color = pal[i * 3 + 0];
			put_word(color);
			color = pal[i * 3 + 1];
			put_word(color);
			color = pal[i * 3 + 2];
			put_word(color);
		}
	}

	if (pic->fd_stand)
		outptr = img_pack_standard(outptr, (const _UBYTE *)pic->fd_addr, width, height, planes);
	else
		outptr = img_pack_interleaved(outptr, (const _UBYTE *)pic->fd_addr, width, height, planes);
	size = outptr - buf;
	
	if (size > 0 && Fwrite(pic->fd_r1, size, buf) != size)
		return -1;
	
	return 0;
}

struct converter const img_converter = { "img", 0, img_estimate_size, img_write_file };
