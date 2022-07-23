#include "global.h"

Gfx D_801D0D00[] = { 0xE7000000, 0x00000000, 0xEF002CF0, 0x0342524D, 0xFA0000FF,
                     0x00000001, 0xF9000000, 0x00000001, 0xDF000000 };

const TransitionInit TransitionCircle_InitVars = {
    TransitionCircle_Init,   TransitionCircle_Destroy, TransitionCircle_Update,   TransitionCircle_Draw,
    TransitionCircle_Start,  TransitionCircle_SetType, TransitionCircle_SetColor, NULL,
    TransitionCircle_IsDone,
};

void TransitionCircle_Start(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    this->stepValue = 0.1f;
    if (this->unk_14 == 0) {
        this->unk_10 = 0.0f;
        this->unk_0C = 1.0f;
    } else {
        this->unk_0C = 0.0f;
        this->unk_10 = 1.0f;
    }
    this->unk_04 = this->unk_0C;
}

void* TransitionCircle_Init(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    bzero(this, sizeof(TransitionCircle));
    this->unk_15 = 1;
    this->unk_18 = D_801DE890;
    this->unk_1C = 6;
    this->unk_1D = 6;
    this->unk_1E = 4;
    this->unk_1F = 0;

    return this;
}

void TransitionCircle_Destroy(void* thisx) {
}

void TransitionCircle_Update(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    this->isDone = Math_StepToF(&this->unk_04, this->unk_10, this->stepValue);
}

void TransitionCircle_SetColor(s32* gfxp, s32 arg1) {
    *gfxp = arg1;
}

void TransitionCircle_SetType(void* thisx, s32 type) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    if (type & 0x80) {
        this->unk_15 = type & 1;
    } else if (type == 1) {
        this->unk_14 = 1;
    } else {
        this->unk_14 = 0;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/func_80164C14.s")
void func_80164C14(Gfx** gfxp, void** arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6) {
    s32 sp0;
    Gfx* gfx = *gfxp;
    Gfx* temp_v0;
    Gfx* temp_v0_10;
    Gfx* temp_v0_11;
    Gfx* temp_v0_12;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    Gfx* temp_v0_4;
    Gfx* temp_v0_5;
    Gfx* temp_v0_6;
    Gfx* temp_v0_7;
    Gfx* temp_v0_8;
    Gfx* temp_v0_9;
    f32 temp_fa0;
    f32 temp_ft4;
    f32 var_fv0;
    f32 var_fv1;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t5;
    s32 temp_t9;
    s32 temp_v1;
    s32 var_a0;
    s32 var_t2;
    s32 var_t3;
    s32 var_t5;
    s32 var_v1;

    gfx = *gfxp;
    // temp_a0 = (arg2 & 7) << 0x15;
    // temp_v0->words.w0 = temp_a0 | 0xFD000000 | 0x100000;
    // temp_v0->words.w1 = (u32) arg1;
    gDPSetTextureImage(POLY_OPA_DISP++, G_IM_FMT_YUV, G_IM_SIZ_4b, 1, arg1);

    // temp_v0_2 = temp_v0 + 8;
    // temp_a1 = temp_a0 | 0xF5000000;
    // temp_a2 = (arg5 & 0xF) << 0xE;
    // temp_a3 = (arg4 & 0xF) * 0x10;
    // temp_v0_2->words.w0 = temp_a1 | 0x100000;
    // temp_v0_2->words.w1 = temp_a2 | 0x070C0000 | 0x300 | temp_a3;
    // temp_v0_3 = temp_v0_2 + 8;
    gDPSetTile(gfx++, arg2, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_MIRROR | G_TX_CLAMP, arg5, G_TX_NOLOD,
               G_TX_MIRROR | G_TX_CLAMP, arg4, G_TX_NOLOD);

    // temp_v0_3->words.w0 = 0xE6000000;
    // temp_v0_3->words.w1 = 0;
    gDPLoadSync(gfx++);

    temp_v0_4 = temp_v0_3 + 8;
    temp_a0_2 = 1 << arg5;
    temp_v1 = 1 << arg4;
    temp_v0_4->words.w0 = 0xF3000000;

    temp_v0_5 = temp_v0_4 + 8;
    temp_t5 = ((s32)((temp_v1 * temp_a0_2) + 3) >> 2) - 1;
    gDPLoadBlock(gfx++, 2, 0, 0, 837, 1656);

    if (temp_t5 < 0x7FF) {
        var_t2 = temp_t5;
    } else {
        var_t2 = 0x7FF;
    }
    temp_t9 = temp_v1 / 16;
    sp0 = temp_t9;
    if (temp_t9 <= 0) {
        var_t3 = 1;
    } else {
        var_t3 = sp0;
    }
    temp_v0_6 = temp_v0_5 + 8;
    if (sp0 <= 0) {
        var_t5 = 1;
    } else {
        var_t5 = sp0;
    }
    temp_v0_4->words.w1 = (((s32)(var_t3 + 0x7FF) / var_t5) & 0xFFF) | 0x07000000 | ((var_t2 & 0xFFF) << 0xC);

    // temp_v0_5->words.w0 = 0xE7000000;
    // temp_v0_5->words.w1 = 0;
    gDPPipeSync(gfx++);

    temp_v0_6->words.w1 = temp_a2 | 0xC0000 | 0x300 | temp_a3;
    temp_v0_6->words.w0 = temp_a1 | ((((s32)((temp_v1 >> 1) + 7) >> 3) & 0x1FF) << 9);
    temp_v0_7 = temp_v0_6 + 8;
    temp_v0_7->words.w1 = ((((temp_v1 - 1) * 4) & 0xFFF) << 0xC) | (((temp_a0_2 - 1) * 4) & 0xFFF);
    temp_v0_7->words.w0 = 0xF2000000;
    temp_v0_8 = temp_v0_7 + 8;
    temp_v0_8->words.w0 = ((((0xA0 - temp_v1) * 4) & 0xFFF) << 0xC) | 0xF2000000U | (((0x78 - temp_a0_2) * 4) & 0xFFF);
    temp_v0_8->words.w1 = ((((temp_v1 + 0x9F) * 4) & 0xFFF) << 0xC) | (((temp_a0_2 + 0x77) * 4) & 0xFFF);
    temp_v0_9 = temp_v0_8 + 8;
    temp_v0_10 = temp_v0_9 + 8;
    temp_fa0 = 1.0f - (1.0f / arg6);
    var_fv0 = (temp_fa0 * 160.0f) + 70.0f;
    temp_ft4 = (temp_fa0 * 120.0f) + 50.0f;
    var_fv1 = temp_ft4;
    if (var_fv0 < -1023.0f) {
        var_fv0 = -1023.0f;
    }
    var_v1 = 0;
    if (temp_ft4 < -1023.0f) {
        var_fv1 = -1023.0f;
    }
    if ((var_fv0 <= -1023.0f) || (var_fv1 <= -1023.0f)) {
        var_a0 = 0;
    } else {
        var_v1 = (s32)(((320.0f - (2.0f * var_fv0)) / (f32)gScreenWidth) * 1024.0f);
        var_a0 = (s32)(((240.0f - (2.0f * var_fv1)) / (f32)gScreenHeight) * 1024.0f);
    }

    // gSPTextureRectangle(gfx++, D_801FBBCC << 0xC, D_801FBBCE, 0, 0, (s32)(var_fv0 * 32.0f) << 0x10, (s32)(var_fv1 * 32.0f), G_TX_RENDERTILE, var_v1 << 0x10, var_a0);
    gSPTextureRectangle(gfx++, 0, 0, D_801FBBCC * 4, D_801FBBCC * 4, 0, (s32)(var_fv0 * 32.0f), (s32)(var_fv1 * 32.0f), var_v1, var_a0)
    // gsTexRect
    temp_v0_9->words.w0 = (((D_801FBBCC * 4) & 0xFFF) << 0xC) | 0xE4000000 | ((D_801FBBCE * 4) & 0xFFF);
    temp_v0_9->words.w1 = 0;

    // Half1
    temp_v0_10->words.w0 = 0xE1000000;
    temp_v0_11 = temp_v0_10 + 8;
    temp_v0_10->words.w1 = ((s32)(var_fv0 * 32.0f) << 0x10) | ((s32)(var_fv1 * 32.0f) & 0xFFFF);

    // Half2
    temp_v0_11->words.w0 = 0xF1000000;
    temp_v0_11->words.w1 = (var_v1 << 0x10) | (var_a0 & 0xFFFF);
    temp_v0_12 = temp_v0_11 + 8;

    // temp_v0_12->words.w0 = 0xE7000000;
    // temp_v0_12->words.w1 = 0;
    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

// OK, but can't figure out the data in display list
// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/TransitionCircle_Draw.s")
void TransitionCircle_Draw(void* thisx, Gfx** gfxp) {
    Gfx* gfx = *gfxp;
    TransitionCircle* this = (TransitionCircle*)thisx;

    gDPPipeSync(gfx++);
    gSPDisplayList(gfx++, &D_801D0D00);
    gDPSetPrimColor(gfx++, 0, this->unk_03, this->unk_00, this->unk_01, this->unk_02, 1);
    if (this->unk_15 == 0) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                          PRIM_LOD_FRAC, PRIMITIVE);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 1, TEXEL0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, 1, TEXEL0,
                          PRIM_LOD_FRAC, PRIMITIVE);
    }
    func_80164C14(&gfx, this->unk_18, 4, 0, this->unk_1C, this->unk_1D, this->unk_04);
    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/TransitionCircle_IsDone.s")
u8 TransitionCircle_IsDone(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    return this->isDone;
}
