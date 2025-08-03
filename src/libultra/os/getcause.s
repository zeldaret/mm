#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetCause)
    MFC0(   v0, C0_CAUSE)
    jr      ra
END(__osGetCause)
