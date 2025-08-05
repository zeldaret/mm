#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetCompare)
    MFC0(   v0, C0_COMPARE)
    jr      ra
END(__osGetCompare)
