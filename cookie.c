#include <gem.h>
#include <stddef.h>
#include <mint/mintbind.h>
#include "cookie.h"


#include "externs.h"

typedef struct {
	union {
		unsigned long id;
		long end;
	} cookie;
	long cookie_value;
} COOKIE;

static COOKIE *_get_jarptr(void)
{
	COOKIE *p;
	
	/*
	 * cookie jar ptr is longword aligned, thus
	 * we can use Setexc to fetch its value
	 */
	p = (COOKIE *)Setexc(0x5A0 / 4, (void (*)())-1);
	return p;
}



static COOKIE *SearchJar(unsigned long id)
{
	COOKIE *p;
	
	p = _get_jarptr();
	if (p != NULL)
	{
		for (;;)
		{
			if (p->cookie.end == 0)
				return NULL;
			if (p->cookie.id == id)
				break;
			p++;
		}
	}
	return p;
}


int Cookie_Find(unsigned long id, long *value)
{
	COOKIE *p;
	
	p = SearchJar(id);
	if (p != NULL)
	{
		if (value)
			*value = p->cookie_value;
		return TRUE;
	}
	return FALSE;
}


