/*
 * resource set indices for snapit
 *
 * created by ORCS 2.16
 */

/*
 * Number of Strings:        33
 * Number of Bitblks:        0
 * Number of Iconblks:       0
 * Number of Color Iconblks: 0
 * Number of Color Icons:    0
 * Number of Tedinfos:       2
 * Number of Free Strings:   5
 * Number of Free Images:    0
 * Number of Objects:        28
 * Number of Trees:          2
 * Number of Userblks:       0
 * Number of Images:         0
 * Total file size:          1258
 */

#undef RSC_NAME
#ifndef __ALCYON__
#define RSC_NAME "snapit"
#endif
#undef RSC_ID
#ifdef snapit
#define RSC_ID snapit
#else
#define RSC_ID 0
#endif

#ifndef RSC_STATIC_FILE
# define RSC_STATIC_FILE 0
#endif
#if !RSC_STATIC_FILE
#define NUM_STRINGS 33
#define NUM_FRSTR 5
#define NUM_UD 0
#define NUM_IMAGES 0
#define NUM_BB 0
#define NUM_FRIMG 0
#define NUM_IB 0
#define NUM_CIB 0
#define NUM_TI 2
#define NUM_OBS 28
#define NUM_TREE 2
#endif



#define ABOUT_DIALOG                       0 /* form/dialog */

#define SNAP_DIALOG                        1 /* form/dialog */
#define SNAP_SCREEN                        4 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_TOP_CURR                      5 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_TOP_WORK                      6 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_RUBBER                        7 /* BUTTON in tree SNAP_DIALOG */
#define O_IMG                              9 /* BUTTON in tree SNAP_DIALOG */
#define O_GIF                             10 /* BUTTON in tree SNAP_DIALOG */
#define O_TGA16                           11 /* BUTTON in tree SNAP_DIALOG */
#define O_TGA24                           12 /* BUTTON in tree SNAP_DIALOG */
#define O_PNG                             13 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_DELAY                        14 /* FTEXT in tree SNAP_DIALOG */ /* max len 1 */
#define FORCE_TRUECOLOR                   15 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_HELP                         16 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_OK                           17 /* BUTTON in tree SNAP_DIALOG */
#define SNAP_CANCEL                       18 /* BUTTON in tree SNAP_DIALOG */

#define AL_NOMEM                           0 /* Alert string */
/* [1][Not enough memory!][Cancel] */

#define AL_WRITEFILE                       1 /* Alert string */
/* [1][Error writing file!][Cancel] */

#define FS_CHOOSEFILE                      2 /* Free string */
/* Choose image filename */

#define AL_OVERWRITE                       3 /* Alert string */
/* [2][Overwrite existing file?][Yes|No] */

#define AL_NO_RESOLUTION                   4 /* Alert string */
/* [1][Unsupported Resolution][Cancel] */




#ifdef __STDC__
#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif
extern _WORD snapit_rsc_load(_WORD wchar, _WORD hchar);
extern _WORD snapit_rsc_gaddr(_WORD type, _WORD idx, void *gaddr);
extern _WORD snapit_rsc_free(void);
#endif
