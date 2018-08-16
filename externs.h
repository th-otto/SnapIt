#ifndef FALSE
#  define FALSE 0
#  define TRUE  1
#endif

#ifndef _WORD
#  ifdef WORD
#    define _WORD WORD
#  else
#    define _WORD short
#  endif
#endif

#ifndef _UWORD
#  ifdef UWORD
#    define _UWORD UWORD
#  else
#    define _UWORD unsigned short
#  endif
#endif

#ifndef UNUSED
# define UNUSED(x) (void)(x)
#endif

int Cookie_ReadJar(unsigned long id, long *value);
