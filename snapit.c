#include <gem.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <limits.h>
#include <mint/mintbind.h>
#include <mint/cookie.h>
#include <mint/arch/nf_ops.h>

#define RSC_NAMED_FUNCTIONS 1
#define RSC_STATIC_FILE 1
#define hfix_objs(a, b, c)
#define hrelease_objs(a, b)
#include "snapit.rsh"

#include "externs.h"

extern short _app;

static _WORD gl_wchar, gl_hchar, gl_wbox, gl_hbox;
static _WORD aes_handle;
static _WORD vdi_handle;
static _WORD vdi_planes;
static _BOOL chunky_mode;
static _BOOL force_24bit;
static GRECT desk;
static GRECT screen;
static GRECT snap;
static _WORD menu_id;
static _WORD __magix;
#if 0 /* currently unused */
static _WORD __mint;
#endif


static RGBPALETTE rgb_palette;
static _WORD vdi_palette[256][4];


enum filetype {
	FT_NONE,
	FT_IMG,
	FT_GIF,
	FT_TGA16,
	FT_TGA24,
	FT_PNG
};

extern struct converter const img_converter;
extern struct converter const gif_converter;
extern struct converter const tga16_converter;
extern struct converter const tga24_converter;
extern struct converter const png_converter;

static struct {
	const struct converter *converter;
	_WORD obj;
} const converters[] = {
	{ NULL, 0 },
	{ &img_converter, O_IMG },
	{ &gif_converter, O_GIF },
	{ &tga16_converter, O_TGA16 },
	{ &tga24_converter, O_TGA24 },
	{ &png_converter, O_PNG }
};

/*
 * Map from ST standard pixel values to VDI colors, 2 planes
 */
static unsigned char const vdi_revtab4[4] = { 0, 2, 3, 1 };
/*
 * Map from ST standard pixel values to VDI colors, 4 planes
 */
static unsigned char const vdi_revtab16[16] = { 0,  2, 3, 6, 4, 7, 5, 8, 9, 10, 11, 14, 12, 15, 13,  1 };
/*
 * Map from ST standard pixel values to VDI colors, 8 planes
 */
static unsigned char const vdi_revtab256[256] = {
    0,   2,   3,   6,   4,   7,   5,   8,   9,  10,  11,  14,  12,  15,  13, 255,
   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,
   32 , 33 , 34 , 35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
   48 , 49 , 50 , 51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,
   64 , 65 , 66 , 67,  68,  69,  70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
   80 , 81 , 82 , 83,  84,  85,  86,  87,  88,  89,  90,  91,  92,  93,  94,  95,
   96,  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
  112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
  128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143,
  144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
  160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175,
  176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191,
  192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207,
  208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223,
  224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239,
  240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254,   1
};

static _UWORD snap_delay = 0;
static enum filetype file_type = FT_NONE;
static _WORD snap_type = SNAP_SCREEN;
static int snap_num = 1;
static char snap_dir[PATH_MAX - 20];
static char snap_filename[PATH_MAX];


static char const gl_menu_name[] = "  SnapIt";

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

#if 0 /* unused */
static unsigned short Mxmask(void)
{
	static unsigned short mxmask = 1;

	if (mxmask == 1)
	{
		if ((long)Mxalloc(-1, MX_STRAM) == -32L)
			mxmask = 0x0000;  /* Mxalloc is not implemented */
		else if (Sysconf(-1) == -32L)
			mxmask = MX_PREFTTRAM;  /* oldfashion Mxalloc() */
		else
			mxmask = -1;
	}

	return mxmask;
}

/*** ---------------------------------------------------------------------- ***/

static void *mxalloc(long amount, unsigned short mode)
{
	void *p = Mxalloc(amount, mode & Mxmask());
	if (p == (void *)-32)
		p = Malloc(amount);
	return p;
}
#endif

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static _BOOL acc_exit(void)
{
	_WORD msg[8];
	
	if (!_app && _AESnumapps == 1)
	{
		for (;;)
			evnt_mesag(msg);
	}
	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL test_chunky(_WORD planes)
{
	int a;
	unsigned char pls[64];
	unsigned char pld[64];
	MFDB src, dst;

	if (planes != 8)
		return FALSE;

	src.fd_addr = pls;
	src.fd_w = 16;
	src.fd_h = 1;
	src.fd_wdwidth = 1;
	src.fd_stand = 0;
	src.fd_nplanes = planes;

	dst.fd_addr = pld;
	dst.fd_w = 16;
	dst.fd_h = 1;
	dst.fd_wdwidth = 1;
	dst.fd_stand = 1;
	dst.fd_nplanes = planes;

	for (a = 0; a < 8; ++a)
		pls[a] = 1;
	for (; a < 64; ++a)
		pls[a] = 0;

	vr_trnfm(vdi_handle, &src, &dst);

	if (pld[0] == 0xff)
		return TRUE;

	return FALSE;
}

/*** ---------------------------------------------------------------------- ***/

static void draw_dialog(OBJECT *tree, GRECT *gr)
{
	_WORD x, y;
	
	x = tree[ROOT].ob_x;
	y = tree[ROOT].ob_y;
	form_center_grect(tree, gr);
	if (x != 0 && y != 0)
	{
		gr->g_x = x + gr->g_x - tree[ROOT].ob_x;
		gr->g_y = y + gr->g_y - tree[ROOT].ob_y;
		tree[ROOT].ob_x = x;
		tree[ROOT].ob_y = y;
	}
	form_dial_grect(FMD_START, gr, gr);
	objc_draw_grect(tree, ROOT, MAX_DEPTH, gr);
}

/*** ---------------------------------------------------------------------- ***/

static void undraw_dialog(OBJECT *tree, GRECT *gr)
{
	(void)tree;
	form_dial_grect(FMD_FINISH, gr, gr);
}

/*** ---------------------------------------------------------------------- ***/

static void default_file_type(void)
{
	if (force_24bit || chunky_mode)
	{
		file_type = FT_TGA24;
	} else
	{
		switch (vdi_planes)
		{
		case 1:
			file_type = FT_IMG;
			break;
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			file_type = FT_GIF;
			break;
		case 15:
		case 16:
			file_type = FT_TGA16;
			break;
		case 24:
		case 32:
			file_type = FT_TGA24;
			break;
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL open_vwork(void)
{
	int i;
	_WORD workin[15];
	_WORD workout[57];
	_WORD xworkout[57];

	for (i = 0; i < 10; i++)
		workin[i] = 1;
	workin[10] = 2;
	vdi_handle = aes_handle;
	v_opnvwk(workin, &vdi_handle, workout);
	if (vdi_handle <= 0)
		return FALSE;
	
	screen.g_w = workout[0] + 1;
	screen.g_h = workout[1] + 1;
	
	vq_extnd(vdi_handle, 1, xworkout);
	vdi_planes = xworkout[4];
	chunky_mode = test_chunky(vdi_planes);
	
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void close_vwork(void)
{
	if (vdi_handle > 0)
	{
		v_clsvwk(vdi_handle);
		vdi_handle = 0;
	}
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL win_init(void)
{
	_LONG l;
	_WORD dummy;
	_WORD level;
	
	gl_apid = appl_init();
	if (gl_apid < 0)
		return FALSE;
	Pdomain(1);
	aes_handle = graf_handle(&gl_wchar, &gl_hchar, &gl_wbox, &gl_hbox);
	
#if 0
	if (Cookie_ReadJar(C_MiNT, &l) != FALSE)
		__mint = (_WORD)l;
#endif
	if (Cookie_ReadJar(C_MagX, &l) != FALSE)
		__magix = ((short **)l)[2][24];

	if (!_app)
		menu_id = menu_register(gl_apid, gl_menu_name);
	else if (_AESnumapps != 1 && (!__magix || __magix >= 0x300))
		menu_register(gl_apid, gl_menu_name);
		
	if (((appl_xgetinfo(AES_SHELL, &level, &dummy, &dummy, &dummy)) && ((level & 0x00FF) >= SWM_NEWMSG))
		 || (__magix >= 0x400))
		shel_write(SWM_NEWMSG, 1, 1, "", "");			/* wir koennen AP_TERM! */

	if (open_vwork() == FALSE)
		return acc_exit();

	wind_get_grect(0, WF_WORKXYWH, &desk);

	default_file_type();
	
	return TRUE;
}

/*** ---------------------------------------------------------------------- ***/

static void free_mem(void)
{
}

/*** ---------------------------------------------------------------------- ***/

static void win_exit(void)
{
	close_vwork();
	free_mem();
	if (gl_apid >= 0)
	{
		appl_exit();
		gl_apid = -1;
	}
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void control(void)
{
	wind_update(BEG_UPDATE);
	wind_update(BEG_MCTRL);
}

/*** ---------------------------------------------------------------------- ***/

static void uncontrol(void)
{
	wind_update(END_MCTRL);
	wind_update(END_UPDATE);
}

/*** ---------------------------------------------------------------------- ***/

static void select_snaptype(OBJECT *tree, _WORD type)
{
	tree[SNAP_SCREEN].ob_state &= ~OS_SELECTED;
	tree[SNAP_TOP_CURR].ob_state &= ~OS_SELECTED;
	tree[SNAP_TOP_WORK].ob_state &= ~OS_SELECTED;
	tree[SNAP_RUBBER].ob_state &= ~OS_SELECTED;
	tree[type].ob_state |= OS_SELECTED;
}

/*** ---------------------------------------------------------------------- ***/

static void enable_truecolor(OBJECT *tree, _WORD type)
{
	tree[FORCE_TRUECOLOR].ob_state |= OS_DISABLED;
	if (vdi_planes == 8 &&
		(converters[type].converter->input_flags & (CONV_24BPP)))
		tree[FORCE_TRUECOLOR].ob_state &= ~OS_DISABLED;
}

static void select_truecolor(OBJECT *tree)
{
	tree[FORCE_TRUECOLOR].ob_state &= ~OS_SELECTED;
	if (force_24bit)
		tree[FORCE_TRUECOLOR].ob_state |= OS_SELECTED;
}

static void select_filetype(OBJECT *tree, _WORD type)
{
	_WORD i;
	
	for (i = 0; i < ArraySize(converters); i++)
	{
		if (converters[i].obj > 0)
		{
			tree[converters[i].obj].ob_state &= ~OS_SELECTED;
			tree[converters[i].obj].ob_state |= OS_DISABLED;
			switch (vdi_planes)
			{
			case 1:
				if (converters[i].converter->input_flags & CONV_1BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 2:
				if (converters[i].converter->input_flags & CONV_2BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 3:
			case 4:
				if (converters[i].converter->input_flags & CONV_4BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 5:
			case 6:
			case 7:
			case 8:
				if ((converters[i].converter->input_flags & (CONV_8BPP|CONV_CHUNKY)) ||
					(force_24bit && (converters[i].converter->input_flags & CONV_24BPP)))
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 15:
				if (converters[i].converter->input_flags & CONV_15BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 16:
				if (converters[i].converter->input_flags & CONV_16BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 24:
				if (converters[i].converter->input_flags & CONV_24BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			case 32:
				if (converters[i].converter->input_flags & CONV_32BPP)
					tree[converters[i].obj].ob_state &= ~OS_DISABLED;
				break;
			}
		}
	}
	tree[converters[type].obj].ob_state |= OS_SELECTED;

	enable_truecolor(tree, type);
	select_truecolor(tree);
}

/*** ---------------------------------------------------------------------- ***/

static void get_filetype(OBJECT *tree)
{
	_WORD i;
	
	file_type = FT_NONE;
	for (i = 0; i < ArraySize(converters); i++)
	{
		if (converters[i].obj > 0)
		{
			if ((tree[converters[i].obj].ob_state & OS_SELECTED) &&
				!(tree[converters[i].obj].ob_state & OS_DISABLED))
			{
				file_type = i;
				return;
			}
		}
	}
	force_24bit = (tree[FORCE_TRUECOLOR].ob_state & OS_SELECTED) &&
		!(tree[FORCE_TRUECOLOR].ob_state & OS_DISABLED);
}

/*** ---------------------------------------------------------------------- ***/

static void get_snaptype(OBJECT *tree)
{
	if (tree[SNAP_SCREEN].ob_state & OS_SELECTED)
	{
		snap_type = SNAP_SCREEN;
		snap = screen;
	} else if (tree[SNAP_TOP_CURR].ob_state & OS_SELECTED)
	{
		snap_type = SNAP_TOP_CURR;
		snap = desk;
	} else if (tree[SNAP_TOP_WORK].ob_state & OS_SELECTED)
	{
		snap_type = SNAP_TOP_WORK;
		snap = desk;
	} else if (tree[SNAP_RUBBER].ob_state & OS_SELECTED)
	{
		snap_type = SNAP_RUBBER;
		snap = desk;
	}
}

/*** ---------------------------------------------------------------------- ***/

static _WORD run_dialog(OBJECT *tree, void (*check)(OBJECT *tree, _WORD obj, GRECT *gr))
{
	GRECT gr;
	_WORD obj, ret;
	
	draw_dialog(tree, &gr);
	do {
		ret = form_do(tree, ROOT);
		obj = ret & 0x7fff;
		if ((tree[obj].ob_flags & (OF_TOUCHEXIT|OF_EXIT)) && check)
			check(tree, obj, &gr);
	} while (!(tree[obj].ob_flags & OF_EXIT));
	undraw_dialog(tree, &gr);
	tree[obj].ob_state &= ~OS_SELECTED;
	return obj;
}

/*** ---------------------------------------------------------------------- ***/

static void show_about(void)
{
	OBJECT *tree = rs_trindex[ABOUT_DIALOG];
	
	run_dialog(tree, 0);
}

/*** ---------------------------------------------------------------------- ***/

static void get_snapdir(void)
{
	int drv = Dgetdrv();
	size_t len;
	
	snap_dir[0] = drv >= 26 ? (drv - 26) + '1' : ('A' + drv);
	snap_dir[1] = ':';
	Dgetpath(&snap_dir[2], drv + 1);
	len = strlen(snap_dir);
	if (snap_dir[len - 1] != '/' && snap_dir[len - 1] != '\\')
		strcat(snap_dir, "\\");
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static unsigned char vdi_to_rgb(_WORD col)
{
	unsigned long color;
	
	if (col < 0)
		col = 0;
	else if (col > 1000)
		col = 1000;
	color = col;
	return (unsigned char)((color * 25599u) / 100000lu);
}


static void get_colors(void)
{
	_WORD i, colors;
	_WORD color[3];
	_WORD idx;
	
	if (vdi_planes > 8)
		return;
	colors = 1 << vdi_planes;
	for (i = 0; i < colors; i++)
	{
		switch (vdi_planes)
		{
		case 2:
			idx = vdi_revtab4[i];
			break;
		case 4:
			idx = vdi_revtab16[i];
			break;
		case 8:
			idx = vdi_revtab256[i];
			break;
		default:
			idx = i;
			break;
		}
		vq_color(vdi_handle, idx, 0, color);
		vdi_palette[i][0] = color[0];
		vdi_palette[i][1] = color[1];
		vdi_palette[i][2] = color[2];
		vdi_palette[i][3] = idx;
		rgb_palette[i].r = vdi_to_rgb(color[0]);
		rgb_palette[i].g = vdi_to_rgb(color[1]);
		rgb_palette[i].b = vdi_to_rgb(color[2]);
	}
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL f_exists(const char *filename)
{
	_DTA *olddta;
	_DTA dta;
	_BOOL ret;
	
	olddta = Fgetdta();
	Fsetdta(&dta);
	ret = Fsfirst(filename, FA_RDONLY|FA_HIDDEN|FA_SYSTEM) == 0;
	Fsetdta(olddta);
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

static _BOOL next_snap_num(void)
{
	int start = snap_num;
	const char *ext;
	char *end;
	char *end2;
	char name[PATH_MAX];
	_WORD button, ret;
	
	if (file_type == FT_NONE)
		return FALSE;
	ext = converters[file_type].converter->ext;
	
	for (;;)
	{
		sprintf(snap_filename, "%ssnap%03d.%s", snap_dir, snap_num, ext);
		if (!f_exists(snap_filename))
			break;
		++snap_num;
		if (snap_num >= 1000)
			snap_num = 0;
		if (snap_num == start)
			break;
	}
	
	end = (strrchr(snap_filename, '\\') + 1);
	strcpy(name, end);
	strcpy(end, "*.");
	strcat(end, ext);
	if (_AESnumapps == 1)
	{
		strupr(name);
		strupr(end);
	}
	
	if (Sversion() >= 0x1500)
		ret = fsel_exinput(snap_filename, name, &button, rs_frstr[FS_CHOOSEFILE]);
	else
		ret = fsel_input(snap_filename, name, &button);
	if (ret == 0 || button != 1)
	{
		ret = FALSE;
	} else
	{
		end = strrchr(snap_filename, '\\');
		end2 = strrchr(snap_filename, '/');
		if (end == NULL || end2 > end)
			end = end2;
		if (end == NULL)
		{
			get_snapdir();
			strcpy(snap_filename, snap_dir);
			end = snap_filename + strlen(snap_filename);
		} else
		{
			end++;
		}
		*end = '\0';
		strcpy(snap_dir, snap_filename);
		strcpy(end, name);
		if (f_exists(snap_filename))
		{
			if (form_alert(2, rs_frstr[AL_OVERWRITE]) != 1)
				ret = FALSE;
		}
	}
	return ret;
}

/*** ---------------------------------------------------------------------- ***/

static void write_snapshot(void)
{
	MFDB mem_fdb;
	MFDB screen_fdb;
	long line_len, snap_size;
	unsigned char *snap_mem;
	unsigned char *snap_ptr;
	_WORD x, y;
	long work_size;
	void *work_mem;
	_WORD fd;
	_WORD pxy[8];
	const void *pal;
	_BOOL force_conv = FALSE;
	
	mem_fdb.fd_w = snap.g_w;
	mem_fdb.fd_h = snap.g_h;
	mem_fdb.fd_wdwidth = (mem_fdb.fd_w + 15) >> 4;
	
	if (force_24bit || (chunky_mode && !(converters[file_type].converter->input_flags & CONV_8BPP)))
	{
		mem_fdb.fd_stand = 1;
		force_conv = TRUE;
		if (vdi_planes == 8 && (converters[file_type].converter->input_flags & CONV_CHUNKY))
		{
			mem_fdb.fd_nplanes = 8;
			line_len = ulmul(mem_fdb.fd_wdwidth << 1, 8);
		} else
		{
			mem_fdb.fd_nplanes = 24;
			line_len = ulmul(mem_fdb.fd_wdwidth << 1, 24);
		}
	} else
	{
		mem_fdb.fd_stand = 0;
		mem_fdb.fd_nplanes = vdi_planes;
		line_len = ulmul(mem_fdb.fd_wdwidth << 1, vdi_planes);
	}
	snap_size = line_len * snap.g_h;
	
	get_colors();
	
	snap_mem = Malloc(snap_size);
	if (snap_mem == NULL)
	{
		form_alert(1, rs_frstr[AL_NOMEM]);
		return;
	}
	mem_fdb.fd_addr = snap_mem;
	
	screen_fdb.fd_addr = 0;
	screen_fdb.fd_w = screen.g_w;
	screen_fdb.fd_h = screen.g_h;
	screen_fdb.fd_wdwidth = (screen.g_w + 15) >> 4;
	screen_fdb.fd_nplanes = vdi_planes;
	screen_fdb.fd_stand = 0;
	
	v_hide_c(vdi_handle);
	
	if (force_conv)
	{
		_WORD pel, idx;
		
		snap_ptr = snap_mem;
		for (y = 0; y < snap.g_h; y++)
		{
			snap_ptr = snap_mem + line_len * y;
			for (x = 0; x < snap.g_w; x++)
			{
				v_get_pixel(vdi_handle, snap.g_x + x, snap.g_y + y, &pel, &idx);
				pel &= 0xff;
				if (mem_fdb.fd_nplanes == 8)
				{
					*snap_ptr++ = pel;
				} else
				{
					*snap_ptr++ = rgb_palette[pel].r;
					*snap_ptr++ = rgb_palette[pel].g;
					*snap_ptr++ = rgb_palette[pel].b;
				}
			}
		}
	} else
	{
		for (y = 0; y < snap.g_h; y++)
		{
			pxy[0] = snap.g_x;
			pxy[1] = snap.g_y + y;
			pxy[2] = snap.g_x + snap.g_w - 1;
			pxy[3] = snap.g_y + y;
			pxy[4] = 0;
			pxy[5] = y;
			pxy[6] = snap.g_w - 1;
			pxy[7] = y;
			vro_cpyfm(vdi_handle, S_ONLY, pxy, &screen_fdb, &mem_fdb);
		}
	}

	pxy[0] = snap.g_x;
	pxy[1] = snap.g_y;
	pxy[2] = snap.g_x + snap.g_w - 1;
	pxy[3] = snap.g_y + snap.g_h - 1;
	vsf_color(vdi_handle, G_BLACK);
	vsf_perimeter(vdi_handle, FALSE);
	vsf_interior(vdi_handle, FIS_SOLID);
	vsf_style(vdi_handle, 0);
	vs_clip(vdi_handle, 0, pxy);
	vswr_mode(vdi_handle, MD_XOR);
	v_bar(vdi_handle, pxy);
	evnt_timer(500L);
	v_bar(vdi_handle, pxy);
	
	v_show_c(vdi_handle, 1);
	
	if (next_snap_num() == FALSE)
	{
		Mfree(snap_mem);
		return;
	}
	
	graf_mouse(BUSY_BEE, NULL);

	pal = converters[file_type].converter->input_flags & CONV_RGB_PALETTE ? (const void *)rgb_palette : (const void *)vdi_palette;
	work_size = converters[file_type].converter->estimate_size(&mem_fdb, pal);
	work_mem = NULL;
	if (work_size > 0)
	{
		work_mem = Malloc(work_size);
		if (work_mem == NULL)
		{
			Mfree(snap_mem);
			graf_mouse(ARROW, NULL);
			form_alert(1, rs_frstr[AL_NOMEM]);
			return;
		}
	}
	
	fd = (_WORD)Fcreate(snap_filename, 0);
	if (fd < 0)
	{
		graf_mouse(ARROW, NULL);
		form_alert(1, rs_frstr[AL_WRITEFILE]);
	} else
	{
		OUT_FD(&mem_fdb) = fd;
		work_size = converters[file_type].converter->write_file(&mem_fdb, pal, work_mem);
		if (work_size < 0)
		{
			graf_mouse(ARROW, NULL);
			form_alert(1, rs_frstr[AL_WRITEFILE]);
		}
		Fclose(fd);
	}
	
	Mfree(work_mem);
	Mfree(snap_mem);

	graf_mouse(ARROW, NULL);
}

/******************************************************************************/
/*** ---------------------------------------------------------------------- ***/
/******************************************************************************/

static void objc_grect(OBJECT *tree, _WORD obj, GRECT *gr)
{
	GRECT o;
	_WORD x, y;
	_WORD xdiff, ydiff;
	
	x = tree[obj].ob_x;
	y = tree[obj].ob_y;
	objc_offset(tree, obj, &gr->g_x, &gr->g_y);
	form_center_grect(&tree[obj], &o);
	xdiff = o.g_x - tree[obj].ob_x;
	ydiff = o.g_y - tree[obj].ob_y;
	gr->g_x += xdiff;
	gr->g_y += ydiff;
	gr->g_w = o.g_w;
	gr->g_h = o.g_h;
	tree[obj].ob_x = x;
	tree[obj].ob_y = y;
}

static void check_filetype(OBJECT *tree, _WORD obj, GRECT *gr)
{
	GRECT redraw;
	
	UNUSED(gr);
	
	switch (obj)
	{
	case O_IMG:
	case O_GIF:
	case O_TGA16:
	case O_TGA24:
	case O_PNG:
		get_filetype(tree);
		enable_truecolor(tree, file_type);
		force_24bit =
			(!(tree[FORCE_TRUECOLOR].ob_state & OS_DISABLED)) &&
			(vdi_planes == 8 &&
			 !(converters[file_type].converter->output_flags & (CONV_8BPP|CONV_CHUNKY)));
		select_truecolor(tree);
		objc_grect(tree, FORCE_TRUECOLOR, &redraw);
		objc_draw_grect(tree, ROOT, MAX_DEPTH, &redraw);
		break;
	case FORCE_TRUECOLOR:
		force_24bit =
			(!(tree[FORCE_TRUECOLOR].ob_state & OS_DISABLED)) &&
			((tree[FORCE_TRUECOLOR].ob_state & OS_SELECTED) ||
			 (vdi_planes == 8 &&
			  !(converters[file_type].converter->output_flags & (CONV_8BPP|CONV_CHUNKY))));
		select_truecolor(tree);
		objc_grect(tree, FORCE_TRUECOLOR, &redraw);
		objc_draw_grect(tree, ROOT, MAX_DEPTH, &redraw);
		break;
	}
}


static void run_snapit(void)
{
	OBJECT *tree = rs_trindex[SNAP_DIALOG];
	_WORD obj;
	char *delaystr;
	_WORD prevtop;
	
	wind_get_int(DESK, WF_TOP, &prevtop);
	delaystr = tree[SNAP_DELAY].ob_spec.tedinfo->te_ptext;
	sprintf(delaystr, "%u", snap_delay);
	select_snaptype(tree, snap_type);
	select_filetype(tree, file_type);
	obj = run_dialog(tree, check_filetype);
	
	if (obj == SNAP_HELP)
	{
		show_about();
	} else if (obj == SNAP_OK)
	{
		_WORD top;
		_WORD button, state;
		
		snap_delay = (_UWORD)strtoul(delaystr, NULL, 0);
		get_snaptype(tree);
		get_filetype(tree);
		switch (snap_type)
		{
		case SNAP_SCREEN:
			/*
			 * give other programs time to process WM_REDRAW
			 * messages resulting from FMD_FINISH
			 */
			uncontrol();
			evnt_timer(snap_delay * 1000L);
			control();
			break;
		case SNAP_TOP_CURR:
			/*
			 * some MultiTask AES (like XaAES)
			 * untop the current application when an ACC
			 * is invoked.
			 * FIXME: does not work, either: prevtop is already 0
			 */
			wind_get_int(DESK, WF_TOP, &top);
			if (top == 0 && prevtop != 0)
			{
				wind_set_int(prevtop, WF_TOP, 0);
				top = prevtop;
			}
			/*
			 * give other programs time to process WM_REDRAW
			 * messages resulting from FMD_FINISH,
			 * and the user the chance to select a window
			 */
			uncontrol();
			evnt_timer(snap_delay * 1000L);
			control();
			wind_get_int(DESK, WF_TOP, &top);
			wind_get_grect(top, WF_CURRXYWH, &snap);
			break;
		case SNAP_TOP_WORK:
			/*
			 * some MultiTask AES (like XaAES)
			 * untop the current application when an ACC
			 * is invoked.
			 * FIXME: does not work, either: prevtop is already 0
			 */
			wind_get_int(DESK, WF_TOP, &top);
			if (top == 0 && prevtop != 0)
			{
				wind_set_int(prevtop, WF_TOP, 0);
				top = prevtop;
			}
			/*
			 * give other programs time to process WM_REDRAW
			 * messages resulting from FMD_FINISH,
			 * and the user the chance to select a window
			 */
			uncontrol();
			evnt_timer(snap_delay * 1000L);
			control();
			wind_get_int(DESK, WF_TOP, &top);
			wind_get_grect(top, WF_WORKXYWH, &snap);
			break;
		case SNAP_RUBBER:
			graf_mouse(OUTLN_CROSS, NULL);
			do
			{
				evnt_button(1, 1, 0, &snap.g_x, &snap.g_y, &button, &state);
				graf_mkstate(&snap.g_x, &snap.g_y, &button, &state);
			} while ((button & 1));
			do
			{
				evnt_button(1, 1, 1, &snap.g_x, &snap.g_y, &button, &state);
				graf_mkstate(&snap.g_x, &snap.g_y, &button, &state);
			} while (!(button & 1));
			graf_mouse(POINT_HAND, NULL);
			graf_rubberbox(snap.g_x, snap.g_y, -snap.g_x, -snap.g_y, &snap.g_w, &snap.g_h);
			graf_mouse(ARROW, NULL);
			if (snap.g_w < 0)
			{
				snap.g_x += snap.g_w;
				snap.g_w = -snap.g_w;
			}
			if (snap.g_h < 0)
			{
				snap.g_y += snap.g_h;
				snap.g_h = -snap.g_h;
			}
			break;
		}
		
		if (rc_intersect(&screen, &snap))
		{
			write_snapshot();
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

static void snapit(void)
{
	graf_mouse(ARROW, NULL);
	
	control();
	if (file_type == FT_NONE)
	{
		form_alert(1, rs_frstr[AL_NO_RESOLUTION]);
	} else
	{
		run_snapit();
	}
	uncontrol();
}

/*** ---------------------------------------------------------------------- ***/

static void event_loop(void)
{
	_WORD msg[8];
	
	for (;;)
	{
		evnt_mesag(msg);
		switch (msg[0])
		{
		case AC_OPEN:
			if (!_app && msg[4] == menu_id)
				snapit();
			break;
		case AC_CLOSE:
			free_mem();
			/*
			 * Assumes that we normally won't get AC_CLOSE
			 * from multi-tasking AES; if we do,
			 * assume that we can safely terminate
			 */
			if (!_app && msg[4] == menu_id && _AESnumapps != 1)
				return;
			break;
		case AP_TERM:
			free_mem();
			/*
			 * Assumes that we can safely terminate an ACC
			 * in multi-tasking AES
			 */
			if (_app || _AESnumapps != 1)
				return;
			break;
		}
	}
}

/*** ---------------------------------------------------------------------- ***/

int main(void)
{
	if (win_init())
	{
		snapit_rsc_load(gl_wchar, gl_hchar);
		get_snapdir();
		if (_app)
		{
			snapit();
		} else
		{
			event_loop();
		}
	}
	win_exit();
	return 0;
}
