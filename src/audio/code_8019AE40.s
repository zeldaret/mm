#include "PR/asm.h"
#include "PR/regdef.h"

.text

/* void func_8019AE40(UNK* a0, UNK* a1, u16 a2, s32 a3) */
LEAF(func_8019AE40)
    andi    a2, a2, 0xFFFF
    srl     a2, a2, 1
    lw      t0, 0x28(a0)
    lw      t1, 0x2C(a0)
    lw      t2, 0xC(a1)
    bnez    a3, 1f
    sll     t2, t2, 1
    add     t0, t0, t2
    add     t1, t1, t2
1:
    lw      t2, 0x4(a1)
    lw      t3, 0x8(a1)
    lbu     t4, 0x4(a0)
    sll     a3, a3, 1
    add     t2, t2, a3
    add     t3, t3, a3
    sll     t4, t4, 1
2:
.set noreorder
    lh      t5, (t2)
    lh      t6, (t3)
    add     t2, t2, t4
    add     t3, t3, t4
    addi    a2, a2, -1
    sh      t5, (t0)
    addi    t0, t0, 2
    sh      t6, (t1)
.set reorder
    addi    t1, t1, 2
    bgtz    a2, 2b
    jr      ra
END(func_8019AE40)
