/*
 * File: z_kaleido_scope_NES.c
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

void func_80178E3C(u8*, s32, s32, s32);

void func_80821900(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), arg1, arg0, 0x400);
}

void func_8082192C(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(map_name_static), arg1, arg0, 0xA00);
}

void func_80821958(s32 arg0, s32 arg1) {
    func_80178E3C(SEGMENT_ROM_START(item_name_static), arg1, arg0, 0x400);
}

void func_80821984(PlayState* play, s16 arg1) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->unk_268[pauseCtx->pageIndex] = 0;
    pauseCtx->unk_258 = arg1;
    pauseCtx->unk_25A = 0;

    play_sound(NA_SE_SY_DECIDE);

    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = 0xFF;
    gSaveContext.buttonStatus[2] = 0xFF;
    gSaveContext.buttonStatus[3] = 0xFF;
    gSaveContext.buttonStatus[4] = 0xFF;

    gSaveContext.unk_3F22 = 0;
    Interface_ChangeAlpha(50);
}

extern u8 D_801C6A98[5][5];

void func_80821A04(PlayState* play) {
    PauseContext* pauseCtx = &play->pauseCtx;

    pauseCtx->unk_280 = 0;
    pauseCtx->unk_258 = 0;

    play_sound(NA_SE_SY_CURSOR);

    pauseCtx->unk_298 = 4.0f;

    // TODO: indexing of D_801C6A98 is likely wrong
    gSaveContext.buttonStatus[0] = 0;
    gSaveContext.buttonStatus[1] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[2] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[3] = D_801C6A98[pauseCtx->pageIndex + 1][1];
    gSaveContext.buttonStatus[4] = 0;

    gSaveContext.unk_3F22 = 0;

    Interface_ChangeAlpha(50);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821AD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821CC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80821F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808221DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80823350.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824738.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808248D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80824B90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808256E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_8082585C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808259D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80825E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808274DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827A8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80827E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Draw.s")

#ifdef NON_MATCHING
void func_808286D8(u32* arg0, u16 arg1) {
    u8 temp_t1;
    u32 var_a1;
    u16 i;
    u32 temp_a1_2;
    s32 j;

    if (!arg0) {}

    for (i = 0; i < arg1; i++) {
        j = i;
        if (arg0[j] & ~0xFF) {
            var_a1 = arg0[j];
            temp_a1_2 = var_a1 >> 8;
            if (j) {}
            temp_t1 = ((((temp_a1_2 & 0xFF0000) >> 0x10) + ((temp_a1_2 & 0xFF00) >> 7) + (temp_a1_2 & 0xFF)) / 7) & 0xFF;
            arg0[j] = (arg0[j] & 0xFF) | (((((temp_t1 << 8) | temp_t1) << 8) | temp_t1) << 8);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_808286D8.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/func_80828788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_kaleido_scope/KaleidoScope_Update.s")
