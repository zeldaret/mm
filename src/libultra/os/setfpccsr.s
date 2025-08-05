#include "PR/asm.h"
#include "PR/regdef.h"
#include "PR/R4300.h"

.text

LEAF(__osSetFpcCsr)
    CFC1(   v0, fcr31)
    CTC1(   a0, fcr31)
    jr      ra
END(__osSetFpcCsr)
