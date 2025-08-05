#include "PR/asm.h"
#include "PR/regdef.h"

.text

LEAF(sqrtf)
    sqrt.s  fv0, fa0
    j       ra
END(sqrtf)
