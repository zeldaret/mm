#include "global.h"

Gfx D_801D0D00[] = { 0xE7000000, 0x00000000, 0xEF002CF0, 0x0342524D, 0xFA0000FF,
                     0x00000001, 0xF9000000, 0x00000001, 0xDF000000, 0x00000000 };

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
    this->texture = D_801DE890;
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

void TransitionCircle_SetColor(s32* gfxp, u32 arg1) {
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

void TransitionCircle_LoadAndSetTexture(Gfx** gfxp, TexturePtr texture, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                                        f32 arg6) {
    Gfx* gfx = *gfxp;
    s32 temp1 = D_801FBBCC;
    s32 temp2 = D_801FBBCE;
    s32 width = 1 << arg4;
    s32 height = 1 << arg5;
    f32 s;
    f32 t;
    s32 dtdy;
    s32 dsdx;

    gDPLoadTextureBlock_4b(gfx++, texture, arg2, width, height, 0, G_TX_MIRROR | G_TX_CLAMP, G_TX_MIRROR | G_TX_CLAMP,
                           arg4, arg5, G_TX_NOLOD, G_TX_NOLOD);
    gDPSetTileSize(gfx++, G_TX_RENDERTILE, (0xA0 - width) << 2, (0x78 - height) << 2, (0xA0 + (width - 1)) << 2,
                   (0x78 + (height - 1)) << 2);

    s = ((1.0f - (1.0f / arg6)) * 160.0f) + 70.0f;
    t = ((1.0f - (1.0f / arg6)) * 120.0f) + 50.0f;

    if (s < -1023.0f) {
        s = -1023.0f;
    }
    if (t < -1023.0f) {
        t = -1023.0f;
    }

    if ((s <= -1023.0f) || (t <= -1023.0f)) {
        dsdx = 0;
        dtdy = 0;
    } else {
        dsdx = ((320.0f - (2.0f * s)) / gScreenWidth) * 1024.0f;
        dtdy = ((240.0f - (2.0f * t)) / gScreenHeight) * 1024.0f;
    }

    gSPTextureRectangle(gfx++, 0, 0, temp1 << 2, temp2 << 2, G_TX_RENDERTILE, (s32)(s * 32.0f), (s32)(t * 32.0f), dsdx,
                        dtdy);
    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

void TransitionCircle_Draw(void* thisx, Gfx** gfxp) {
    Gfx* gfx = *gfxp;
    TransitionCircle* this = (TransitionCircle*)thisx;

    gDPPipeSync(gfx++);
    gSPDisplayList(gfx++, &D_801D0D00);
    gDPSetPrimColor(gfx++, 0, this->lod, this->primColor.r, this->primColor.g, this->primColor.b, 1);
    if (this->unk_15 == 0) {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                          PRIM_LOD_FRAC, PRIMITIVE);
    } else {
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, 1, TEXEL0, PRIM_LOD_FRAC, PRIMITIVE, 0, 0, 0, PRIMITIVE, 1, TEXEL0,
                          PRIM_LOD_FRAC, PRIMITIVE);
    }
    TransitionCircle_LoadAndSetTexture(&gfx, this->texture, 4, 0, this->unk_1C, this->unk_1D, this->unk_04);
    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

s32 TransitionCircle_IsDone(void* thisx) {
    TransitionCircle* this = (TransitionCircle*)thisx;

    return this->isDone;
}
