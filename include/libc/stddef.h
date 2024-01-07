#ifndef LIBC_STDDEF_H
#define LIBC_STDDEF_H

#if !defined(_SIZE_T)
#define _SIZE_T
#if defined(_MIPS_SZLONG) && (_MIPS_SZLONG == 64)
typedef unsigned long size_t;
#else
typedef unsigned int  size_t;
#endif
#endif

typedef signed long ptrdiff_t;

#ifdef __GNUC__
#define offsetof(structure, member) __builtin_offsetof (structure, member)
#else
#define offsetof(structure, member) ((size_t)&(((structure*)0)->member))
#endif

#endif /* STDDEF_H */
