#include "global.h"

void func_801A5680(u16 arg0);
void func_801A54D0(u16 arg0);

void func_801A4EB0(void) {
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A4EB0/func_801A4EB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A4EB0/func_801A4FD8.s")

void func_801A5080(u16 arg0) {
    if ((D_801D8E3C != 0) && (arg0 < 6)) {
        func_801A5680(arg0);
    }
}

void func_801A50C0(u16 arg0) {
    if ((D_801D8E3C != 0) && (arg0 < 6)) {
        func_801A54D0(arg0);
    }
}

u16 func_801A5100(void) {
    return D_801D8E44;
}

u8 func_801A510C(void) {
    return D_801D8E3C;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A4EB0/func_801A5118.s")
