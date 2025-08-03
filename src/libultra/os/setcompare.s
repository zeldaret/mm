#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetCompare)
    MTC0(   a0, C0_COMPARE)
    jr      ra
END(__osSetCompare)
