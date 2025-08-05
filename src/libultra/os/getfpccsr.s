#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetFpcCsr)
    CFC1(   v0, C1_FPCSR)
    jr      ra
END(__osGetFpcCsr)
