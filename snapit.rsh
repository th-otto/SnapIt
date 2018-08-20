/*
 * GEM resource C output of snapit
 *
 * created by ORCS 2.16
 */

#if !defined(__GNUC__) || !defined(__mc68000__)
#include <portab.h>
#endif

#ifdef OS_WINDOWS
#  include <portaes.h>
#  define SHORT _WORD
#  ifdef __WIN32__
#    define _WORD signed short
#  else
#    define _WORD signed int
 #   pragma option -zE_FARDATA
#  endif
#else
#  ifdef __TURBOC__
#    include <portaes.h>
#    define CP (_WORD *)
#  endif
#endif

#ifdef OS_UNIX
#  include <portaes.h>
#  define SHORT _WORD
#else
#  ifdef __GNUC__
#    ifndef __PORTAES_H__
#      if __GNUC__ < 4
#        include <aesbind.h>
#        ifndef _WORD
#          define _WORD int
#        endif
#        define CP (char *)
#      else
#        include <mt_gem.h>
#        ifndef _WORD
#          define _WORD short
#        endif
#        define CP (short *)
#      endif
#      define CW (short *)
#    endif
#  endif
#endif


#ifdef __SOZOBONX__
#  include <xgemfast.h>
#else
#  ifdef SOZOBON
#    include <aes.h>
#  endif
#endif

#ifdef MEGAMAX
#  include <gembind.h>
#  include <gemdefs.h>
#  include <obdefs.h>
#  define _WORD int
#  define SHORT int
#endif

#ifndef _VOID
#  define _VOID void
#endif

#ifndef OS_NORMAL
#  define OS_NORMAL 0x0000
#endif
#ifndef OS_SELECTED
#  define OS_SELECTED 0x0001
#endif
#ifndef OS_CROSSED
#  define OS_CROSSED 0x0002
#endif
#ifndef OS_CHECKED
#  define OS_CHECKED 0x0004
#endif
#ifndef OS_DISABLED
#  define OS_DISABLED 0x0008
#endif
#ifndef OS_OUTLINED
#  define OS_OUTLINED 0x0010
#endif
#ifndef OS_SHADOWED
#  define OS_SHADOWED 0x0020
#endif
#ifndef OS_WHITEBAK
#  define OS_WHITEBAK 0x0040
#endif
#ifndef OS_DRAW3D
#  define OS_DRAW3D 0x0080
#endif

#ifndef OF_NONE
#  define OF_NONE 0x0000
#endif
#ifndef OF_SELECTABLE
#  define OF_SELECTABLE 0x0001
#endif
#ifndef OF_DEFAULT
#  define OF_DEFAULT 0x0002
#endif
#ifndef OF_EXIT
#  define OF_EXIT 0x0004
#endif
#ifndef OF_EDITABLE
#  define OF_EDITABLE 0x0008
#endif
#ifndef OF_RBUTTON
#  define OF_RBUTTON 0x0010
#endif
#ifndef OF_LASTOB
#  define OF_LASTOB 0x0020
#endif
#ifndef OF_TOUCHEXIT
#  define OF_TOUCHEXIT 0x0040
#endif
#ifndef OF_HIDETREE
#  define OF_HIDETREE 0x0080
#endif
#ifndef OF_INDIRECT
#  define OF_INDIRECT 0x0100
#endif
#ifndef OF_FL3DIND
#  define OF_FL3DIND 0x0200
#endif
#ifndef OF_FL3DBAK
#  define OF_FL3DBAK 0x0400
#endif
#ifndef OF_FL3DACT
#  define OF_FL3DACT 0x0600
#endif
#ifndef OF_MOVEABLE
#  define OF_MOVEABLE 0x0800
#endif
#ifndef OF_POPUP
#  define OF_POPUP 0x1000
#endif

#ifndef R_CICONBLK
#  define R_CICONBLK 17
#endif
#ifndef R_CICON
#  define R_CICON 18
#endif

#ifndef G_SWBUTTON
#  define G_SWBUTTON 34
#endif
#ifndef G_POPUP
#  define G_POPUP 35
#endif
#ifndef G_EDIT
#  define G_EDIT 37
#endif
#ifndef G_SHORTCUT
#  define G_SHORTCUT 38
#endif
#ifndef G_SLIST
#  define G_SLIST 39
#endif
#ifndef G_EXTBOX
#  define G_EXTBOX 40
#endif
#ifndef G_OBLINK
#  define G_OBLINK 41
#endif

#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif

#ifndef _UBYTE
#  define _UBYTE char
#endif

#ifndef _BOOL
#  define _BOOL int
#endif

#ifndef _LONG
#  ifdef LONG
#    define _LONG LONG
#  else
#    define _LONG long
#  endif
#endif

#ifndef _ULONG
#  ifdef ULONG
#    define _ULONG ULONG
#  else
#    define _ULONG unsigned long
#  endif
#endif

#ifndef _LONG_PTR
#  define _LONG_PTR _LONG
#endif

#ifndef C_UNION
#ifdef __PORTAES_H__
#  define C_UNION(x) { (_LONG_PTR)(x) }
#endif
#ifdef __GEMLIB__
#  define C_UNION(x) { (_LONG_PTR)(x) }
#endif
#ifdef __PUREC__
#  define C_UNION(x) { (_LONG_PTR)(x) }
#endif
#ifdef __ALCYON__
#  define C_UNION(x) x
#endif
#endif
#ifndef C_UNION
#  define C_UNION(x) (_LONG_PTR)(x)
#endif

#ifndef SHORT
#  define SHORT short
#endif

#ifndef CP
#  define CP (SHORT *)
#endif

#ifndef CW
#  define CW (_WORD *)
#endif


#undef RSC_STATIC_FILE
#define RSC_STATIC_FILE 1

#include "snapit.h"

#ifndef RSC_NAMED_FUNCTIONS
#  define RSC_NAMED_FUNCTIONS 0
#endif

#ifndef __ALCYON__
#undef defRSHInit
#undef defRSHInitBit
#undef defRSHInitStr
#ifndef RsArraySize
#define RsArraySize(array) (_WORD)(sizeof(array)/sizeof(array[0]))
#define RsPtrArraySize(type, array) (type *)array, RsArraySize(array)
#endif
#define defRSHInit( aa, bb ) RSHInit( aa, bb, RsPtrArraySize(OBJECT *, rs_trindex), RsArraySize(rs_object) )
#define defRSHInitBit( aa, bb ) RSHInitBit( aa, bb, RsPtrArraySize(BITBLK *, rs_frimg) )
#define defRSHInitStr( aa, bb ) RSHInitStr( aa, bb, RsPtrArraySize(_UBYTE *, rs_frstr) )
#endif

#ifdef __STDC__
#ifndef W_Cicon_Setpalette
extern _BOOL W_Cicon_Setpalette(_WORD *_palette);
#endif
#ifndef hrelease_objs
extern _VOID hrelease_objs(OBJECT *_ob, _WORD _num_objs);
#endif
#ifndef hfix_objs
extern _VOID *hfix_objs(RSHDR *_hdr, OBJECT *_ob, _WORD _num_objs);
#endif
#endif

#ifndef RLOCAL
#  if RSC_STATIC_FILE
#    ifdef LOCAL
#      define RLOCAL LOCAL
#    else
#      define RLOCAL static
#    endif
#  else
#    define RLOCAL
#  endif
#endif


#ifndef N_
#  define N_(x)
#endif


#if RSC_STATIC_FILE
#undef NUM_STRINGS
#undef NUM_BB
#undef NUM_IB
#undef NUM_CIB
#undef NUM_CIC
#undef NUM_TI
#undef NUM_FRSTR
#undef NUM_FRIMG
#undef NUM_OBS
#undef NUM_TREE
#undef NUM_UD
#define NUM_STRINGS 33
#define NUM_BB		0
#define NUM_IB		0
#define NUM_CIB     0
#define NUM_CIC     0
#define NUM_TI		2
#define NUM_FRSTR	5
#define NUM_FRIMG	0
#define NUM_OBS     28
#define NUM_TREE	2
#define NUM_UD		0
#endif


static char snapit_string_0[] = "GEM SnapShot Tool";
static char snapit_string_1[] = "";
static char snapit_string_2[] = "";
static char snapit_string_3[] = "Freeware by Thorsten Otto";
static char snapit_string_4[] = "August 2018";
static char snapit_string_5[] = "Written with Pure-C";
static char snapit_string_6[] = "& modules using GCC";
static char snapit_string_7[] = "\275 2018 Thorsten Otto";
static char snapit_string_8[] = "Ok";
static char snapit_string_9[] = "Version 1.0";
static char snapit_string_10[] = "Snap Area:";
static char snapit_string_11[] = "Output:";
static char snapit_string_12[] = "Whole screen";
static char snapit_string_13[] = "Window with frame";
static char snapit_string_14[] = "Window w/o frame";
static char snapit_string_15[] = "Rectangle selection";
static char snapit_string_16[] = "IMG";
static char snapit_string_17[] = "GIF";
static char snapit_string_18[] = "TGA 16";
static char snapit_string_19[] = "TGA 24";
static char snapit_string_20[] = "PNG";
static char snapit_string_21[] = "0";
static char snapit_string_22[] = "Delay: _ second(s)";
static char snapit_string_23[] = "9";
static char snapit_string_24[] = "Output TrueColor";
static char snapit_string_25[] = "Help";
static char snapit_string_26[] = "Catch";
static char snapit_string_27[] = "Cancel";
static char snapit_string_28[] = "[1][Not enough memory!][Cancel]";
static char snapit_string_29[] = "[1][Error writing file!][Cancel]";
static char snapit_string_30[] = "Choose image filename";
static char snapit_string_31[] = "[2][Overwrite existing file?][Yes|No]";
static char snapit_string_32[] = "[1][Unsupported Resolution][Cancel]";


static char *rs_frstr[NUM_FRSTR] = {
	snapit_string_28,
	snapit_string_29,
	snapit_string_30,
	snapit_string_31,
	snapit_string_32
};


static TEDINFO rs_tedinfo[NUM_TI] = {
	{ snapit_string_0, snapit_string_1, snapit_string_2, IBM, 0, TE_CNTR, 0x1180, 0x0, 0, 18,1 },
	{ snapit_string_21, snapit_string_22, snapit_string_23, IBM, 6, TE_CNTR, 0x1180, 0x0, -2, 2,19 } /* SNAP_DELAY */
};


static OBJECT rs_object[NUM_OBS] = {
/* ABOUT_DIALOG */

	{ -1, 1, 8, G_BOX, OF_FL3DBAK, OS_OUTLINED, C_UNION(0x21180L), 0,0, 47,14 },
	{ 2, -1, -1, G_BOXTEXT, OF_FL3DACT, OS_NORMAL, C_UNION(&rs_tedinfo[0]), 14,1, 20,1 },
	{ 3, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_3), 11,4, 25,1 },
	{ 4, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_4), 18,5, 11,1 },
	{ 5, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_5), 14,8, 19,1 },
	{ 6, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_6), 14,9, 19,1 },
	{ 7, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_7), 14,10, 20,1 },
	{ 8, -1, -1, G_BUTTON, 0x607, OS_WHITEBAK, C_UNION(snapit_string_8), 20,12, 8,1 },
	{ 0, -1, -1, G_STRING, 0x620, OS_NORMAL, C_UNION(snapit_string_9), 18,2, 11,1 },

/* SNAP_DIALOG */

	{ -1, 1, 18, G_BOX, OF_FL3DBAK, OS_OUTLINED, C_UNION(0x21100L), 0,0, 39,12 },
	{ 2, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_10), 1,1, 10,1 },
	{ 3, -1, -1, G_STRING, OF_NONE, OS_NORMAL, C_UNION(snapit_string_11), 28,1, 7,1 },
	{ 8, 4, 7, G_IBOX, OF_NONE, OS_NORMAL, C_UNION(0x1100L), 1,2, 25,5 },
	{ 5, -1, -1, G_BUTTON, 0x411, 0xFC41, C_UNION(snapit_string_12), 0,0, 25,1 }, /* SNAP_SCREEN */
	{ 6, -1, -1, G_BUTTON, 0x411, 0xFC40, C_UNION(snapit_string_13), 0,1, 25,1 }, /* SNAP_TOP_CURR */
	{ 7, -1, -1, G_BUTTON, 0x411, 0xFC40, C_UNION(snapit_string_14), 0,2, 25,1 }, /* SNAP_TOP_WORK */
	{ 3, -1, -1, G_BUTTON, 0x411, 0xFC40, C_UNION(snapit_string_15), 0,3, 25,1 }, /* SNAP_RUBBER */
	{ 14, 9, 13, G_IBOX, OF_NONE, OS_NORMAL, C_UNION(0x1100L), 28,2, 10,6 },
	{ 10, -1, -1, G_BUTTON, 0x451, 0xFC40, C_UNION(snapit_string_16), 0,0, 10,1 }, /* O_IMG */
	{ 11, -1, -1, G_BUTTON, 0x451, 0xFC40, C_UNION(snapit_string_17), 0,1, 10,1 }, /* O_GIF */
	{ 12, -1, -1, G_BUTTON, 0x451, 0xFC40, C_UNION(snapit_string_18), 0,2, 10,1 }, /* O_TGA16 */
	{ 13, -1, -1, G_BUTTON, 0x451, 0xFC40, C_UNION(snapit_string_19), 0,3, 10,1 }, /* O_TGA24 */
	{ 8, -1, -1, G_BUTTON, 0x451, 0xFC40, C_UNION(snapit_string_20), 0,4, 10,1 }, /* O_PNG */
	{ 15, -1, -1, G_FTEXT, 0x408, OS_NORMAL, C_UNION(&rs_tedinfo[1]), 1,8, 18,1 }, /* SNAP_DELAY */
	{ 16, -1, -1, G_BUTTON, 0x441, 0xFC40, C_UNION(snapit_string_24), 21,8, 17,1 }, /* FORCE_TRUECOLOR */
	{ 17, -1, -1, G_BUTTON, 0x605, OS_NORMAL, C_UNION(snapit_string_25), 1,10, 8,1 }, /* SNAP_HELP */
	{ 18, -1, -1, G_BUTTON, 0x607, OS_WHITEBAK, C_UNION(snapit_string_26), 16,10, 8,1 }, /* SNAP_OK */
	{ 0, -1, -1, G_BUTTON, 0x625, OS_WHITEBAK, C_UNION(snapit_string_27), 30,10, 8,1 } /* SNAP_CANCEL */
};


static OBJECT *rs_trindex[NUM_TREE] = {
	&rs_object[0], /* ABOUT_DIALOG */
	&rs_object[9] /* SNAP_DIALOG */
};





#if RSC_STATIC_FILE

#if RSC_NAMED_FUNCTIONS
#ifdef __STDC__
_WORD snapit_rsc_load(_WORD wchar, _WORD hchar)
#else
_WORD snapit_rsc_load(wchar, hchar)
_WORD wchar;
_WORD wchar;
#endif
{
#ifndef RSC_HAS_PALETTE
#  define RSC_HAS_PALETTE 0
#endif
#ifndef RSC_USE_PALETTE
#  define RSC_USE_PALETTE 0
#endif
#if RSC_HAS_PALETTE || RSC_USE_PALETTE
	W_Cicon_Setpalette(&rgb_palette[0][0]);
#endif
#if NUM_OBS != 0
	{
		_WORD Obj;
		OBJECT *tree;
		for (Obj = 0, tree = rs_object; Obj < NUM_OBS; Obj++, tree++)
		{
			tree->ob_x = wchar * (tree->ob_x & 0xff) + (tree->ob_x >> 8);
			tree->ob_y = hchar * (tree->ob_y & 0xff) + (tree->ob_y >> 8);
			tree->ob_width = wchar * (tree->ob_width & 0xff) + (tree->ob_width >> 8);
			tree->ob_height = hchar * (tree->ob_height & 0xff) + (tree->ob_height >> 8);
		}
		hfix_objs(NULL, rs_object, NUM_OBS);
	}
#endif
	return 1;
}


#ifdef __STDC__
_WORD snapit_rsc_gaddr(_WORD type, _WORD idx, void *gaddr)
#else
_WORD snapit_rsc_gaddr(type, idx, gaddr)
_WORD type;
_WORD idx;
void *gaddr;
#endif
{
	switch (type)
	{
#if NUM_TREE != 0
	case R_TREE:
		if (idx < 0 || idx >= NUM_TREE)
			return 0;
		*((OBJECT **)gaddr) = rs_trindex[idx];
		break;
#endif
#if NUM_OBS != 0
	case R_OBJECT:
		if (idx < 0 || idx >= NUM_OBS)
			return 0;
		*((OBJECT **)gaddr) = &rs_object[idx];
		break;
#endif
#if NUM_TI != 0
	case R_TEDINFO:
		if (idx < 0 || idx >= NUM_TI)
			return 0;
		*((TEDINFO **)gaddr) = &rs_tedinfo[idx];
		break;
#endif
#if NUM_IB != 0
	case R_ICONBLK:
		if (idx < 0 || idx >= NUM_IB)
			return 0;
		*((ICONBLK **)gaddr) = &rs_iconblk[idx];
		break;
#endif
#if NUM_BB != 0
	case R_BITBLK:
		if (idx < 0 || idx >= NUM_BB)
			return 0;
		*((BITBLK **)gaddr) = &rs_bitblk[idx];
		break;
#endif
#if NUM_FRSTR != 0
	case R_STRING:
		if (idx < 0 || idx >= NUM_FRSTR)
			return 0;
		*((char **)gaddr) = (char *)(rs_frstr[idx]);
		break;
#endif
#if NUM_FRIMG != 0
	case R_IMAGEDATA:
		if (idx < 0 || idx >= NUM_FRIMG)
			return 0;
		*((BITBLK **)gaddr) = rs_frimg[idx];
		break;
#endif
#if NUM_OBS != 0
	case R_OBSPEC:
		if (idx < 0 || idx >= NUM_OBS)
			return 0;
		*((_LONG **)gaddr) = &rs_object[idx].ob_spec.index;
		break;
#endif
#if NUM_TI != 0
	case R_TEPTEXT:
		if (idx < 0 || idx >= NUM_TI)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_tedinfo[idx].te_ptext);
		break;
#endif
#if NUM_TI != 0
	case R_TEPTMPLT:
		if (idx < 0 || idx >= NUM_TI)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_tedinfo[idx].te_ptmplt);
		break;
#endif
#if NUM_TI != 0
	case R_TEPVALID:
		if (idx < 0 || idx >= NUM_TI)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_tedinfo[idx].te_pvalid);
		break;
#endif
#if NUM_IB != 0
	case R_IBPMASK:
		if (idx < 0 || idx >= NUM_IB)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_iconblk[idx].ib_pmask);
		break;
#endif
#if NUM_IB != 0
	case R_IBPDATA:
		if (idx < 0 || idx >= NUM_IB)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_iconblk[idx].ib_pdata);
		break;
#endif
#if NUM_IB != 0
	case R_IBPTEXT:
		if (idx < 0 || idx >= NUM_IB)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_iconblk[idx].ib_ptext);
		break;
#endif
#if NUM_BB != 0
	case R_BIPDATA:
		if (idx < 0 || idx >= NUM_BB)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_bitblk[idx].bi_pdata);
		break;
#endif
#if NUM_FRSTR != 0
	case R_FRSTR:
		if (idx < 0 || idx >= NUM_FRSTR)
			return 0;
		*((char ***)gaddr) = (char **)(&rs_frstr[idx]);
		break;
#endif
#if NUM_FRIMG != 0
	case R_FRIMG:
		if (idx < 0 || idx >= NUM_FRIMG)
			return 0;
		*((BITBLK ***)gaddr) = &rs_frimg[idx];
		break;
#endif
	default:
		return 0;
	}
	return 1;
}


#ifdef __STDC__
_WORD snapit_rsc_free(void)
#else
_WORD snapit_rsc_free()
#endif
{
#if NUM_OBS != 0
	hrelease_objs(rs_object, NUM_OBS);
#endif
	return 1;
}

#endif /* RSC_NAMED_FUNCTIONS */

#else /* !RSC_STATIC_FILE */
int rs_numstrings = 33;
int rs_numfrstr = 5;

int rs_nuser = 0;
int rs_numimages = 0;
int rs_numbb = 0;
int rs_numfrimg = 0;
int rs_numib = 0;
int rs_numcib = 0;
int rs_numti = 2;
int rs_numobs = 28;
int rs_numtree = 2;

char rs_name[] = "snapit.rsc";

int _rsc_format = 2; /* RSC_FORM_SOURCE2 */
#endif /* RSC_STATIC_FILE */
