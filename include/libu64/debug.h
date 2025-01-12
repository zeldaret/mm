#ifndef LIBU64_DEBUG_H
#define LIBU64_DEBUG_H

#include "../attributes.h"

NORETURN void _dbg_hungup(const char* file, int lineNum);
NORETURN void Reset(void);

#endif
