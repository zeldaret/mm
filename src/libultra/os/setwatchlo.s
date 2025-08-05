#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetWatchLo)
    MTC0(   a0, C0_WATCHLO)
    NOP
    jr      ra
END(__osSetWatchLo)
