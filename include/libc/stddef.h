#ifndef STDDEF_H
#define STDDEF_H

#include "PR/ultratypes.h"

typedef u32 size_t;

typedef s32 ptrdiff_t;

#ifndef NULL
#define NULL (void*)0
#endif

#ifdef __GNUC__
#define offsetof(structure, member) __builtin_offsetof (structure, member)
#else
#define offsetof(structure, member) ((size_t)&(((structure*)0)->member))
#endif

#endif /* STDDEF_H */
