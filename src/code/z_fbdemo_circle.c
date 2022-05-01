#include "global.h"

// s32 D_801D0D00[] = { 0xE7000000, 0x00000000, 0xEF002CF0, 0x0342524D, 0xFA0000FF,
//                      0x00000001, 0xF9000000, 0x00000001, 0xDF000000, 0x00000000 };

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

void TransitionCircle_SetColor(s32* arg0, s32 arg1) {
    *arg0 = arg1;
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/func_80164C14.s")

// OK, but can't figure out the data in display list
#pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/TransitionCircle_Draw.s")
// void TransitionCircle_Draw(void* thisx, Gfx** gfxp) {
//     Gfx* gfx = *gfxp;
//     TransitionCircle* this = (TransitionCircle*)thisx;

//     gDPPipeSync(gfx++);
//     gSPDisplayList(gfx++, &D_801D0D00);
//     gDPSetPrimColor(gfx++, 0, this->unk_03, this->unk_00, this->unk_01, this->unk_02, 1);
//     if (this->unk_15 == 0) {
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
//                           PRIM_LOD_FRAC, PRIMITIVE);
//     } else {
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 1, TEXEL0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, 1, TEXEL0,
//                           PRIM_LOD_FRAC, PRIMITIVE);
//     }
//     func_80164C14(&gfx, this->unk_18, 4, 0, this->unk_1C, this->unk_1D, this->unk_04);
//     gDPPipeSync(gfx++);

//     *gfxp = gfx;
// }

// #pragma GLOBAL_ASM("asm/non_matchings/code/z_fbdemo_circle/TransitionCircle_IsDone.s")
u8 TransitionCircle_IsDone(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    return this->isDone;
}
