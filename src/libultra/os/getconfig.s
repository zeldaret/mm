#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osGetConfig)
    MFC0(   v0, C0_CONFIG)
    jr      ra
END(__osGetConfig)
