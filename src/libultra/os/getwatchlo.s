#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetWatchLo)
    MFC0(   v0, C0_WATCHLO)
    jr      ra
END(__osGetWatchLo)
