#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetCause)
    MTC0(   a0, C0_CAUSE)
    jr      ra
END(__osSetCause)
