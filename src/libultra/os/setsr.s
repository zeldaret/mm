#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetSR)
    MTC0(   a0, C0_SR)
    NOP
    jr      ra
END(__osSetSR)
