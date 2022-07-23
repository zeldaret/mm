/*
 * File: z_kaleido_mask.c
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

s32 D_8082B600 = 0;

s32 D_8082B604 = 0;

s16 D_8082B608 = 10;

s32 D_8082B60C[] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000001, 0x00000000, 0x00010000,
    0x00000001, 0x00000000, 0x00010000, 0x00000001, 0x00000000, 0x00010000, 0x00000001, 0x00000000,
    0x00010000, 0x00000001, 0x00000000, 0x00010000, 0x00000001, 0x00000000, 0x00010000, 0x00000001,
    0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101, 0x01010101,
};

s32 D_8082B684[] = {
    0x01010004, 0x02020180, 0x01040210, 0x00100201, 0x00080110, 0x02040220, 0x00400080, 0x00020102, 0x00010240,
    0x01200108, 0x00200140, 0x02080280, 0x00FF0064, 0x00FF0000, 0x00000064, 0x00FF0000, 0x000000FF, 0x00640000,
};

u8 D_8082B6CC[] = { 0x35, 0x33, 0x34, 0x32, 0xFF };

s16 D_8082B6D4[] = {
    0x0294,
    0x0384,
    0x0474,
    0x0000,
};

s16 D_8082B6DC[] = {
    0x044C,
    0x0398,
    0x044C,
    0x0000,
};

s32 D_8082B6E4[] = { 0, 0, 0 };

s16 D_8082B6F0[] = { 100, 255 };

s32 D_8082B6F4 = 0;

s16 D_8082B6F8[] = { 10, 0, 0, 0 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8081FF80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808204AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80820FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821730.s")
