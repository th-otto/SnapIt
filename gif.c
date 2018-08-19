#include <gem.h>
#include <stddef.h>
#include <mint/mintbind.h>
#include "externs.h"
#include "s_gif.h"

#define WORK_SIZE 0x3000L


long gif_estimate_size(const MFDB *pic, const _WORD palette[][3])
{
	UNUSED(pic);
	UNUSED(palette);
	return WORK_SIZE;
}

