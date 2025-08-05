#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetConfig)
    MTC0(   a0, C0_CONFIG)
    jr      ra
END(__osSetConfig)
