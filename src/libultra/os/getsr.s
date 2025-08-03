#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetSR)
    MFC0(   v0, C0_SR)
    jr      ra
END(__osGetSR)
