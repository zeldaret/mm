#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(osGetCount)
    MFC0(   v0, C0_COUNT)
    jr      ra
END(osGetCount)
