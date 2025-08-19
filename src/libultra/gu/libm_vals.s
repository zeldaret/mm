#include "PR/asm.h"
#include "PR/regdef.h"

.rdata

DATA(__libm_qnan_f)
    .word 0x7F810000
ENDDATA(__libm_qnan_f)
