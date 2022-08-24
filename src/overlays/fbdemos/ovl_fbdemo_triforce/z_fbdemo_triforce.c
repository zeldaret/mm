/*
 * File: z_fbdemo_triforce.c
 * Overlay: ovl_fbdemo_triforce
 * Description:
 */

#include "z_fbdemo_triforce.h"

void* TransitionTriforce_Init(void* thisx);
void TransitionTriforce_Destroy(void* thisx);
void TransitionTriforce_Update(void* thisx, s32 updateRate);
void TransitionTriforce_Draw(void* thisx, Gfx** gfxP);
void TransitionTriforce_Start(void* thisx);
void TransitionTriforce_SetType(void* thisx, s32 type);
void TransitionTriforce_SetColor(void* thisx, u32 color);
s32 TransitionTriforce_IsDone(void* thisx);

Gfx D_80AC5630[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPClearGeometryMode(G_ZBUFFER | G_SHADE | G_CULL_BOTH | G_FOG | G_LIGHTING | G_TEXTURE_GEN | G_TEXTURE_GEN_LINEAR
                          | G_LOD | G_SHADING_SMOOTH),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                     G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE, G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF
                     | G_RM_AA_OPA_SURF2),
    gsSPEndDisplayList(),
};

Gfx D_80AC5660[] =
{
    gsDPNoOp(),
    gsDPNoOpTag(0xFFFFFFFF),
    gsSPCullDisplayList(32191, 0),
    gsDPNoOpTag(0xFFFFFFFF),
    gsDPSetCombineLERP(TEXEL0, COMBINED, 0, COMBINED, 0, COMBINED, ENVIRONMENT, COMBINED, 0, COMBINED, 0, COMBINED, COMBINED, COMBINED, LOD_FRACTION, COMBINED),
    gsDPNoOpTag(0xFFFFFFFF),
    gsDPNoOp(),
    gsDPNoOpTag(0xFFFFFFFF),
    gsSPVertex(0x00000000, 79, 33),
    gsDPNoOpTag(0xFFFFFFFF),
    gsDPSetDepthImage(0x00000000),
    gsDPNoOpTag(0xFFFFFFFF),
};

const TransitionInit TransitionTriforce_InitVars = {
    TransitionTriforce_Init,
    TransitionTriforce_Destroy,
    TransitionTriforce_Update,
    TransitionTriforce_Draw,
    TransitionTriforce_Start,
    TransitionTriforce_SetType,
    TransitionTriforce_SetColor,
    NULL,
    TransitionTriforce_IsDone,
};

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Start.s")
void TransitionTriforce_Start(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    switch (this->state) {
        case 1:
        case 2:
            this->transPos = 1.0f;
            return;
    }
    this->transPos = 0.03f;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Init.s")
void* TransitionTriforce_Init(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    bzero(this, sizeof(*this));
    guOrtho(&this->projection, -160.0f, 160.0f, -120.0f, 120.0f, -1000.0f, 1000.0f, 1.0f);
    this->transPos = 1.0f;
    this->state = 2;
    this->step = 0.015f;
    this->fadeDirection = 1;
    return this;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Destroy.s")
void TransitionTriforce_Destroy(void* thisx) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Update.s")
void TransitionTriforce_Update(void* thisx, s32 updateRate) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;
    f32 temp_f0;
    s32 i;

    for (i = updateRate; i > 0; i--) {
        if (this->state == 1) {
            this->transPos = CLAMP_MIN(this->transPos * (1.0f - this->step), 0.03f);
        } else if (this->state == 2) {
            this->transPos = CLAMP_MIN(this->transPos - this->step, 0.03f);
        } else if (this->state == 3) {
            this->transPos = CLAMP_MAX(this->transPos / (1.0f - this->step), 1.0f);
        } else if (this->state == 4) {
            this->transPos = CLAMP_MAX(this->transPos + this->step, 1.0f);
        }
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_SetColor.s")
void TransitionTriforce_SetColor(void* thisx, u32 color) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->color.rgba = color;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_SetType.s")
void TransitionTriforce_SetType(void* thisx, s32 type) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->fadeDirection = type;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/func_80AC5280.s")
void func_80AC5280(void* thisx, s32 state) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    this->state = state;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Draw.s")
// void TransitionTriforce_Draw(void* thisx, Gfx** gfxP) {
//     Gfx* gfx = *gfxP;
//     Mtx* modelView;
//     TransitionTriforce* this = (TransitionTriforce*)thisx;
//     f32 scale;
//     s32 pad;
//     f32 rotation = this->transPos * 360.0f;

//     modelView = this->modelView[this->frame];
//     scale = this->transPos * 0.625f;
//     this->frame ^= 1;
//     // osSyncPrintf("rate=%f tx=%f ty=%f rotate=%f\n", this->transPos, 0.0f, 0.0f, rotation);
//     guScale(&modelView[0], scale, scale, 1.0f);
//     guRotate(&modelView[1], rotation, 0.0f, 0.0f, 1.0f);
//     guTranslate(&modelView[2], 0.0f, 0.0f, 0.0f);

//     gDPPipeSync(gfx++);
//     gSPDisplayList(gfx++, &D_80AC5630);
//     gDPSetColor(gfx++, G_SETPRIMCOLOR, this->color.rgba);
//     gDPSetCombineMode(gfx++, G_CC_PRIMITIVE, G_CC_PRIMITIVE);
//     gSPMatrix(gfx++, &this->projection, G_MTX_LOAD | G_MTX_PROJECTION);
//     gSPMatrix(gfx++, &modelView[0], G_MTX_LOAD);
//     gSPMatrix(gfx++, &modelView[1], G_MTX_NOPUSH | G_MTX_MODELVIEW | G_MTX_MUL);
//     gSPMatrix(gfx++, &modelView[2], G_MTX_NOPUSH | G_MTX_MODELVIEW | G_MTX_MUL);
//     gSPVertex(gfx++, &D_80AC5660, 10, 0);
//     if (!TransitionTriforce_IsDone(this)) {
//         switch (this->fadeDirection) {
//             case 1:
//                 // gSP2Triangles(gfx++, 0, 4, 5, 0, 64, 16, 3, 0);
//                 gSP2Triangles(gfx++, 0, 4, 5, 0, 16, 48, 0, 0);
//                 gSP1Triangle(gfx++, 5, 3, 2, 0);
//                 break;
//             case 2:
//                 gSP2Triangles(gfx++, 3, 4, 5, 0, 0, 2, 6, 0);
//                 gSP2Triangles(gfx++, 0, 6, 7, 0, 1, 0, 7, 0);
//                 gSP2Triangles(gfx++, 1, 7, 8, 0, 1, 8, 9, 0);
//                 gSP2Triangles(gfx++, 1, 9, 2, 0, 2, 9, 6, 0);
//                 break;
//         }
//     } else {
//         switch (this->fadeDirection) {
//             case 1:
//                 break;
//             case 2:
//                 gSP1Quadrangle(gfx++, 6, 7, 8, 9, 0);
//                 break;
//         }
//     }
//     gDPPipeSync(gfx++);
//     *gfxP = gfx;
// }

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_IsDone.s")
s32 TransitionTriforce_IsDone(void* thisx) {
    TransitionTriforce* this = (TransitionTriforce*)thisx;

    s32 ret = 0;

    if (this->state == 1 || this->state == 2) {
        return this->transPos <= 0.03f;

    } else if (this->state == 3 || this->state == 4) {
        return this->transPos >= 1.0f;
    }
    return ret;
}
