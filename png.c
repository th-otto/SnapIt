#include <gem.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdint.h>
#include <mint/mintbind.h>
#include "externs.h"

struct converter const png_converter = {
	"PNG (Palette)",
	"png",
	CONV_1BPP|CONV_2BPP|CONV_4BPP|CONV_8BPP,
	0,
	0
};
