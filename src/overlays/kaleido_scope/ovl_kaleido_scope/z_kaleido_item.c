/*
 * File: z_kaleido_item.c
 * Overlay: ovl_kaleido_scope
 * Description:
 */

#include "z_kaleido_scope.h"

extern UNK_TYPE D_02001360;
extern UNK_TYPE D_020044A0;
extern UNK_TYPE D_02004AA0;
extern UNK_TYPE D_0200B998;
extern UNK_TYPE D_08062000;
extern UNK_TYPE D_08064340;
extern UNK_TYPE D_0B000000;
extern UNK_TYPE D_0C000000;
extern UNK_TYPE D_0C006C00;

s32 D_8082B3C0 = 0;

s32 D_8082B3C4 = 0;

s16 D_8082B3C8 = 10;

u8 D_8082B3CC[5][24] = {
    {
        false, false, false, false, false, false, false, false, false, false, false, false,
        false, false, false, false, false, false, true,  true,  true,  true,  true,  true,
    },
    {
        true, false, false, false, false, true, false, false, false, false, false, true,
        true, true,  true,  false, false, true, true,  true,  true,  true,  true,  true,
    },
    {
        true,  false, false, false, false, true, false, false, false, false, false, true,
        false, true,  true,  false, false, true, true,  true,  true,  true,  true,  true,
    },
    {
        true,  false, false, false, false, true, false, false, false, true, false, true,
        false, true,  true,  false, false, true, true,  true,  true,  true, true,  true,
    },
    {
        true,  true, true, true, true, true, true, true, true, true, true, true,
        false, true, true, true, true, true, true, true, true, true, true, true,
    },
};

s16 D_8082B444[] = {
    0x005F, 0x003E, 0x005F, 0x0080, 0x00A1, 0x00C2, 0x003E, 0x005F,
};

s16 D_8082B454[] = {
    0x0055, 0x0075, 0x0075, 0x0075, 0x0075, 0x0075, 0x0096, 0x0096, 0x00FF, 0x0064,
    0x00FF, 0x0000, 0x0000, 0x0064, 0x00FF, 0x0000, 0x0000, 0x00FF, 0x0064, 0x0000,
};

u8 D_8082B47C[] = {
    0x35, 0x33, 0x34, 0x32, 0xFF,
};

s16 D_8082B484[] = {
    0x0294,
    0x0384,
    0x0474,
    0x0000,
};

s16 D_8082B48C[] = {
    0x044C,
    0x0398,
    0x044C,
    0x0000,
};

s32 D_8082B494[] = { 0, 0, 0 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081B240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081B6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081B6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081BCA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081C684.s")
