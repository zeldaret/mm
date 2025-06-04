#include "PR/asm.h"
#include "PR/regdef.h"

.text
.align 5

/* Copy 0x20 bytes at a1 to a0, with word alignment */
/* void func_8019AEC0(u32 dst[8], u32 src[8]) */
LEAF(func_8019AEC0)
    addi    t7, a1, 0x20
1:
.set noreorder
    lw      t0, 0x0(a1)
    lw      t1, 0x4(a1)
    lw      t2, 0x8(a1)
    lw      t3, 0xC(a1)
    addi    a1, a1, 0x10
    sw      t0, 0x0(a0)
    sw      t1, 0x4(a0)
    sw      t2, 0x8(a0)
    sw      t3, 0xC(a0)
.set reorder
    addi    a0, a0, 0x10
    bne     a1, t7, 1b
    jr      ra
END(func_8019AEC0)
