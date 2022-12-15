#include "global.h"
#include "system_malloc.h"

Gfx sTransitionUnkSetupDL[] = {
    gsDPPipeSync(),
    gsSPTexture(0x8000, 0x8000, 0, G_TX_RENDERTILE, G_ON),
    gsSPLoadGeometryMode(G_TEXTURE_ENABLE),
    gsDPSetCombineMode(G_CC_DECALRGB, G_CC_DECALRGB),
    gsDPSetOtherMode(G_AD_DISABLE | G_CD_MAGICSQ | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                         G_TD_CLAMP | G_TP_PERSP | G_CYC_1CYCLE | G_PM_1PRIMITIVE,
                     G_AC_NONE | G_ZS_PIXEL | G_RM_AA_OPA_SURF | G_RM_AA_OPA_SURF2),
    gsSPEndDisplayList(),
};

void TransitionUnk_InitGraphics(TransitionUnk* this) {
    s32 row2;
    s32 pad2;
    s32 pad3;
    s32 frame;
    s32 rowTex;
    s32 row;
    Gfx* gfx;
    Vtx* vtx;
    s32 col;
    s32 colTex;

    guMtxIdent(&this->modelView);
    guMtxIdent(&this->unk_98);
    guOrtho(&this->projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, -1000.0f, 1000.0f, 1.0f);

    for (frame = 0; frame < 2; frame++) {
        this->frame = frame;
        vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
        for (colTex = 0, col = 0; col < (this->col + 1); col++, colTex += 0x20) {
            for (rowTex = 0, row = 0; row < (this->row + 1); row++, rowTex += 0x20) {
                Vtx_t* vtx2 = &vtx->v;

                // clang-format on
                vtx++;   \
                vtx2->tc[0] = rowTex << 6; \
                vtx2->ob[0] = row * 0x20; \
                vtx2->ob[1] = col * 0x20; \
                vtx2->ob[2] = -5; \
                vtx2->flag = 0; \
                vtx2->tc[1] = colTex << 6; \
                vtx2->cn[0] = 0; \
                vtx2->cn[1] = 0; \
                vtx2->cn[2] = 120; \
                vtx2->cn[3] = 255;
                // clang-format on
            }
        }
    }

    gfx = this->gfx;
    for (colTex = 0, col = 0; col < this->col; col++, colTex += 0x20) {

        gSPVertex(gfx++, SEGMENT_ADDR(0xA, (u32)col * (this->row + 1) * sizeof(Vtx)), 2 * (this->row + 1), 0);

        for (rowTex = 0, row = 0, row2 = 0; row < this->row;) {
            gDPPipeSync(gfx++);

            gDPLoadTextureTile(gfx++, SEGMENT_ADDR(0xB, 0), G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WIDTH, SCREEN_HEIGHT,
                               rowTex, colTex, rowTex + 0x20, colTex + 0x20, 0, G_TX_NOMIRROR | G_TX_WRAP,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            gSP1Quadrangle(gfx++, row, row + 1, row2 + this->row + 2, this->row + row2 + 1, 0);

            rowTex += 0x20;
            row2++;
            row++;
        }
    }

    gDPPipeSync(gfx++);
    gSPEndDisplayList(gfx++);
}

void TransitionUnk_InitData(TransitionUnk* this) {
    s32 col;
    s32 row;

    for (col = 0; col < this->col + 1; col++) {
        for (row = 0; row < this->row + 1; row++) {
            (this->unk_0C + row + col * (this->row + 1))->unk_0 = row * 32;
            (this->unk_0C + row + col * (this->row + 1))->unk_4 = col * 32;
        }
    }
}

void TransitionUnk_Destroy(TransitionUnk* this) {
    Sleep_Msec(100);

    if (this->unk_0C != NULL) {
        SystemArena_Free(this->unk_0C);
        this->unk_0C = NULL;
    }
    if (this->vtxFrame1 != NULL) {
        SystemArena_Free(this->vtxFrame1);
        this->vtxFrame1 = NULL;
    }
    if (this->vtxFrame2 != NULL) {
        SystemArena_Free(this->vtxFrame2);
        this->vtxFrame2 = NULL;
    }
    if (this->gfx != NULL) {
        SystemArena_Free(this->gfx);
        this->gfx = NULL;
    }
}

TransitionUnk* TransitionUnk_Init(TransitionUnk* this, s32 row, s32 col) {
    s32 tmp;

    bzero(this, sizeof(TransitionUnk));
    this->frame = 0;
    this->row = row;
    this->col = col;
    tmp = (row + 1) * (col + 1);
    this->unk_0C = SystemArena_Malloc(tmp * sizeof(TransitionUnkData));
    this->vtxFrame1 = SystemArena_Malloc(tmp * sizeof(Vtx));
    this->vtxFrame2 = SystemArena_Malloc(tmp * sizeof(Vtx));
    this->gfx = SystemArena_Malloc(((row * 9 + 1) * col + 2) * sizeof(Gfx));

    if (this->unk_0C == NULL || this->vtxFrame1 == NULL || this->vtxFrame2 == NULL || this->gfx == NULL) {
        if (this->unk_0C != NULL) {
            SystemArena_Free(this->unk_0C);
            this->unk_0C = NULL;
        }
        if (this->vtxFrame1 != NULL) {
            SystemArena_Free(this->vtxFrame1);
            this->vtxFrame1 = NULL;
        }
        if (this->vtxFrame2 != NULL) {
            SystemArena_Free(this->vtxFrame2);
            this->vtxFrame2 = NULL;
        }
        if (this->gfx != NULL) {
            SystemArena_Free(this->gfx);
            this->gfx = NULL;
        }
        return NULL;
    }
    TransitionUnk_InitGraphics(this);
    TransitionUnk_InitData(this);
    this->frame = 0;

    return this;
}

void TransitionUnk_SetData(TransitionUnk* this) {
    s32 col;
    Vtx* vtx;
    s32 row;

    for (col = 0; col < this->col + 1; col++) {
        for (row = 0; row < this->row + 1; row++) {
            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + row + col * (this->row + 1))->v.ob[0] = (this->unk_0C + row + col * (this->row + 1))->unk_0;
            vtx = (this->frame == 0) ? this->vtxFrame1 : this->vtxFrame2;
            (vtx + row + col * (this->row + 1))->v.ob[1] = (this->unk_0C + row + col * (this->row + 1))->unk_4;
        }
    }
}

void TransitionUnk_Draw(TransitionUnk* this, Gfx** gfxP) {
    Gfx* gfx = *gfxP;

    gSPDisplayList(gfx++, sTransitionUnkSetupDL);
    TransitionUnk_SetData(this);
    gSPMatrix(gfx++, &this->projection, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_PROJECTION);
    gSPMatrix(gfx++, &this->modelView, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPSegment(gfx++, 0xA, this->frame == 0 ? this->vtxFrame1 : this->vtxFrame2);
    gSPSegment(gfx++, 0xB, this->zBuffer);
    gSPDisplayList(gfx++, sTransitionUnkSetupDL);
    gSPDisplayList(gfx++, this->gfx);
    gDPPipeSync(gfx++);
    this->frame ^= 1;
    *gfxP = gfx;
}

void TransitionUnk_Update(TransitionUnk* this) {
    f32 temp_f00;
    f32 temp_f12;
    s32 col;
    f32 phi_f14;
    s32 row;

    for (col = 0; col < this->col + 1; col++) {
        for (row = 0; row < this->row + 1; row++) {
            temp_f00 =
                (this->unk_0C + row + col * (this->row + 1))->unk_0 - (this->unk_0C + 5 + 4 * (this->row + 1))->unk_0;
            temp_f12 =
                (this->unk_0C + row + col * (this->row + 1))->unk_4 - (this->unk_0C + 5 + 4 * (this->row + 1))->unk_4;
            phi_f14 = (SQ(temp_f00) + SQ(temp_f12)) / 100.0f;
            if (phi_f14 != 0.0f) {
                if (phi_f14 < 1.0f) {
                    phi_f14 = 1.0f;
                }
                (this->unk_0C + row + col * (this->row + 1))->unk_0 -= temp_f00 / phi_f14;
                (this->unk_0C + row + col * (this->row + 1))->unk_4 -= temp_f12 / phi_f14;
            }
        }
    }
}

void func_801647AC(TransitionUnk* this) {
}

s32 func_801647B8(TransitionUnk* this) {
    return 0;
}
