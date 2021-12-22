/*
 * File: z_en_mag.c
 * Overlay: ovl_En_Mag
 * Description: Title Logo
 */

#include "z_en_mag.h"

#define FLAGS 0x00000030

#define THIS ((EnMag*)thisx)

void EnMag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx);

static s16 D_8096E910 = 0;
static s16 D_8096E914 = 30; // Timer used in update helper
static s16 D_8096E918 = 0;  // Array index used in update helper, always 0 or 1
static s16 D_8096E91C = 0;
static s16 D_8096E920 = 20;

const ActorInit En_Mag_InitVars = {
    ACTOR_EN_MAG,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_MAG,
    sizeof(EnMag),
    (ActorFunc)EnMag_Init,
    (ActorFunc)EnMag_Destroy,
    (ActorFunc)EnMag_Update,
    (ActorFunc)EnMag_Draw,
};

// Used in update helper
static s16 D_8096E944[] = { 155, 255 };
static s16 D_8096E948[] = { 255, 155 };
static s16 D_8096E94C[] = { 55, 255 };
static s16 D_8096E950[] = { 255, 0 };
static s16 D_8096E954[] = { 255, 155 };

static s16 D_8096E958[] = { 255, 155 };
static s16 D_8096E95C[] = { 255, 0 };
static s16 D_8096E960[] = { 0, 155 };

// // PRESS START character indices
// static u8 D_8096E964[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };

// static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
// static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
// static TexturePtr D_8096E9A0[] = { 0x600FF40, 0x6010340, 0x6010340, 0x6010740, 0x6010B40, 0x6010B40 };

// static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
// static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
// static s16 D_8096E9D0 = 0;
// static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };

// extern UNK_TYPE D_06011E48;

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Init.s")
void EnMag_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMag* this = (EnMag*)thisx;
    u16 i;

    this->unk11F54 = 6;
    this->unk11F56 = 10;

    for (i = 0; i < 6; i++) {
        this->unk11F36[i] = 0;
        this->unk11F44[i] = 0;
    }

    this->unk11F08[0] = 255;
    this->unk11F08[1] = 155;
    this->unk11F08[2] = 255;
    this->unk11F08[3] = 0;
    this->unk11F08[4] = 255;
    this->unk11F08[5] = 155;

    this->unk11F06 = 20;
    this->unk11F14 = 0;

    this->unk11F18[0] = 255;
    this->unk11F18[1] = 155;
    this->unk11F18[2] = 255;
    this->unk11F18[3] = 0;
    this->unk11F18[4] = 255;
    this->unk11F18[5] = 155;

    this->unk11F16 = 55;

    this->unk11F24 = 0;
    this->unk11F26 = 0;
    this->unk11F28[0] = this->unk11F28[1] = this->unk11F28[2] = 255;

    this->unk11F2E = this->unk11F30 = this->unk11F32 = this->unk11F34 = 0;

    this->unk11F02 = 30;
    this->unk11F00 = this->unk11F04 = 0;

    if (gSaveContext.unk_3F1E != 0) {
        this->unk11F2E = 210;
        this->unk11F32 = 255;
        this->unk11F34 = 255;
        this->unk11F06 = 100;
        this->unk11F14 = 255;
        this->unk11F08[0] = 255;
        this->unk11F08[1] = 255;
        this->unk11F08[2] = 255;
        this->unk11F08[3] = 0;
        this->unk11F08[4] = 255;
        this->unk11F08[5] = 155;
        this->unk11F16 = 100;
        this->unk11F24 = 255;
        this->unk11F18[0] = 255;
        this->unk11F18[1] = 255;
        this->unk11F18[2] = 255;
        this->unk11F18[3] = 0;
        this->unk11F18[4] = 255;
        this->unk11F18[5] = 155;
        gSaveContext.unk_3F1E = 0;
        this->unk11F04 = 2;
        D_8096E910 = 20;
        gSaveContext.fadeDuration = 1;
        gSaveContext.unk_3F51 = 255;
    }

    Font_LoadOrderedFont(&this->unk170);
    this->unk11F58 = 0;
    this->unk11F5A = 0;
    this->unk11F5C = 0;
    this->unk11F60 = 0;
    this->unk11F64 = 25;
    this->unk11F66 = 25;
    this->unk11F68 = 20;
    this->unk11F6A = 40;
    this->unk11F6C = 10;
    this->unk11F6E = 10;
    this->unk11F70 = 15;
    D_8096E914 = 30;
    D_8096E918 = 0;
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Destroy.s")
void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096B604.s")
void func_8096B604(Actor* thisx) {
    EnMag* this = THIS;
    s16 temp_lo;

    temp_lo = ABS_ALT(this->unk11F18[0] - D_8096E944[D_8096E918]) / D_8096E914;
    if (this->unk11F18[0] >= D_8096E944[D_8096E918]) {
        this->unk11F18[0] -= temp_lo;
    } else {
        this->unk11F18[0] += temp_lo;
    }

    temp_lo = ABS_ALT(this->unk11F18[1] - D_8096E948[D_8096E918]) / D_8096E914;
    if (this->unk11F18[1] >= D_8096E948[D_8096E918]) {
        this->unk11F18[1] -= temp_lo;
    } else {
        this->unk11F18[1] += temp_lo;
    }

    temp_lo = ABS_ALT(this->unk11F18[2] - D_8096E94C[D_8096E918]) / D_8096E914;
    if (this->unk11F18[2] >= D_8096E94C[D_8096E918]) {
        this->unk11F18[2] -= temp_lo;
    } else {
        this->unk11F18[2] += temp_lo;
    }

    temp_lo = ABS_ALT(this->unk11F18[3] - D_8096E950[D_8096E918]) / D_8096E914;
    if (this->unk11F18[3] >= D_8096E950[D_8096E918]) {
        this->unk11F18[3] -= temp_lo;
    } else {
        this->unk11F18[3] += temp_lo;
    }

    // Skips 4

    temp_lo = ABS_ALT(this->unk11F18[5] - D_8096E954[D_8096E918]) / D_8096E914;
    if (this->unk11F18[5] >= D_8096E954[D_8096E918]) {
        this->unk11F18[5] -= temp_lo;
    } else {
        this->unk11F18[5] += temp_lo;
    }

    D_8096E914--;
    if (D_8096E914 == 0) {
        this->unk11F18[0] = D_8096E944[D_8096E918];
        this->unk11F18[1] = D_8096E948[D_8096E918];
        this->unk11F18[2] = D_8096E94C[D_8096E918];
        this->unk11F18[3] = D_8096E950[D_8096E918];
        // Skips 4
        this->unk11F18[5] = D_8096E954[D_8096E918];
        D_8096E914 = 30;
        D_8096E918 ^= 1;
    }
}

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Update.s")
void EnMag_Update(Actor* thisx, GlobalContext* globalCtx) {
    s16 temp_lo;
    s32 pad[2];
    EnMag* this = (EnMag*)thisx;

    if (gSaveContext.fileNum != 0xFEDC) {
        if (this->unk11F04 == 0) {
            if (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_START) ||
                CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
                CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B)) {

                if (!EnvFlags_Get(globalCtx, 4)) {
                    play_sound(0x4823U);
                    this->unk11F04 = 0xA;
                    this->unk11F00 = 0;
                    this->unk11F02 = 0x1E;
                    D_8096E910 = 0x14;
                    gSaveContext.fadeDuration = 1;
                    gSaveContext.unk_3F51 = 0xFF;
                }
            }
        } else {
            switch (this->unk11F04) {
                case 1:
                    temp_lo = ABS_ALT(this->unk11F08[1] - D_8096E958[0]) / this->unk11F64;
                    if (this->unk11F08[1] >= D_8096E958[0]) {
                        this->unk11F08[1] -= temp_lo;
                    } else {
                        this->unk11F08[1] += temp_lo;
                    }

                    temp_lo = ABS_ALT(this->unk11F0E[0] - D_8096E95C[0]) / this->unk11F64;
                    if (this->unk11F0E[0] >= D_8096E95C[0]) {
                        this->unk11F0E[0] -= temp_lo;
                    } else {
                        this->unk11F0E[0] += temp_lo;
                    }

                    temp_lo = ABS_ALT(this->unk11F0E[2] - D_8096E960[0]) / this->unk11F64;
                    if (this->unk11F0E[2] >= D_8096E960[0]) {
                        this->unk11F0E[2] -= temp_lo;
                    } else {
                        this->unk11F0E[2] += temp_lo;
                    }

                    temp_lo = ABS_ALT(this->unk11F14 - 0xFF) / this->unk11F64;
                    this->unk11F14 += temp_lo;

                    temp_lo = ABS_ALT(this->unk11F06 - 0x20) / this->unk11F64;
                    this->unk11F06 += temp_lo;

                    this->unk11F64--;
                    if (this->unk11F64 == 0) {
                        this->unk11F08[1] = D_8096E958[0];
                        this->unk11F0E[0] = D_8096E95C[0];
                        this->unk11F0E[2] = D_8096E960[0];
                        this->unk11F14 = 0xFF;
                        this->unk11F04 = 2;
                        this->unk11F72 = 5;
                    }
                    break;

                case 2:
                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->unk11F08[1] - D_8096E958[1]) / this->unk11F66;
                        if (this->unk11F08[1] >= D_8096E958[1]) {
                            this->unk11F08[1] -= temp_lo;
                        } else {
                            this->unk11F08[1] += temp_lo;
                        }

                        temp_lo = ABS_ALT(this->unk11F0E[0] - D_8096E95C[1]) / this->unk11F66;
                        if (this->unk11F0E[0] >= D_8096E95C[1]) {
                            this->unk11F0E[0] -= temp_lo;
                        } else {
                            this->unk11F0E[0] += temp_lo;
                        }

                        temp_lo = ABS_ALT(this->unk11F0E[2] - D_8096E960[1]) / this->unk11F66;
                        if (this->unk11F0E[2] >= D_8096E960[1]) {
                            this->unk11F0E[2] -= temp_lo;
                        } else {
                            this->unk11F0E[2] += temp_lo;
                        }

                        temp_lo = ABS_ALT(this->unk11F06 - 0x80) / this->unk11F66;
                        this->unk11F06 += temp_lo;

                        temp_lo = ABS_ALT(this->unk11F26 - 0xFF) / this->unk11F66;
                        this->unk11F26 += temp_lo;

                        this->unk11F66--;
                        if (this->unk11F66 == 0) {
                            this->unk11F08[1] = D_8096E958[1];
                            this->unk11F0E[0] = D_8096E95C[1];
                            this->unk11F0E[2] = D_8096E960[1];
                            this->unk11F06 = 0x80;
                            this->unk11F26 = 0xFF;
                            this->unk11F04 = 3;
                            this->unk11F72 = 5;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 3:
                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->unk11F2E - 0xFF) / this->unk11F68;
                        this->unk11F2E += temp_lo;

                        this->unk11F68--;
                        if (this->unk11F68 == 0) {
                            this->unk11F68 = 1;
                            this->unk11F2E = 0xFF;
                        }

                        temp_lo = ABS_ALT(this->unk11F14 - 0x3C) / this->unk11F6A;
                        this->unk11F14 -= temp_lo;

                        temp_lo = ABS_ALT(this->unk11F24 - 0xFF) / this->unk11F6A;
                        this->unk11F24 += temp_lo;

                        temp_lo = ABS_ALT(this->unk11F16 - 0x80) / this->unk11F6A;
                        this->unk11F16 += temp_lo;

                        this->unk11F6A--;
                        if (this->unk11F6A == 0) {
                            this->unk11F14 = 0x3C;
                            this->unk11F24 = 0xFF;
                            this->unk11F16 = 0x80;
                            this->unk11F04 = 5;
                            this->unk11F72 = 0x14;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 5:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->unk11F30 - 0xFF) / this->unk11F6C;
                        this->unk11F30 += temp_lo;

                        this->unk11F6C--;
                        if (this->unk11F6C == 0) {
                            this->unk11F24 = 0xFF;
                            this->unk11F04 = 6;
                            this->unk11F72 = 0x14;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 6:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->unk11F34 - 0xFF) / this->unk11F6E;
                        this->unk11F34 += temp_lo;

                        this->unk11F6E--;
                        if (this->unk11F6E == 0) {
                            this->unk11F34 = 0xFF;
                            this->unk11F04 = 0xD;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 10:
                    this->unk11F08[1] = D_8096E958[0];
                    this->unk11F0E[0] = D_8096E95C[0];
                    this->unk11F0E[2] = D_8096E960[0];
                    this->unk11F14 = 0x3C;
                    this->unk11F06 = 0x80;
                    this->unk11F26 = 0xFF;
                    this->unk11F2E = 0xFF;
                    this->unk11F24 = 0xFF;
                    this->unk11F16 = 0x80;
                    this->unk11F30 = 0xFF;
                    this->unk11F34 = 0xFF;
                    this->unk11F04 = 0xD;
                    break;

                case 13:
                    func_8096B604(&this->actor);

                    if (D_8096E910 == 0) {
                        if (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_START) ||
                            CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
                            CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B)) {
                            if (globalCtx->sceneLoadFlag != 0x14) {
                                func_801A3F54(0);
                                D_801BB12C++;
                                if (D_801BB12C >= 2) {
                                    D_801BB12C = 0;
                                }
                                play_sound(0x4823U);
                                gSaveContext.gameMode = 2;
                                globalCtx->sceneLoadFlag = 0x14;
                                globalCtx->unk_1887F = 2;
                                globalCtx->nextEntranceIndex = 0x1C00;
                                gSaveContext.cutscene = 0;
                                gSaveContext.sceneSetupIndex = 0;
                            }
                            this->unk11F54 = 0xF;
                            this->unk11F56 = 0x19;
                            this->unk11F04 = 0x14;
                        }
                    } else {
                        D_8096E910--;
                    }
                    break;

                case 20:
                    temp_lo = ABS_ALT(this->unk11F14) / this->unk11F70;
                    this->unk11F14 -= temp_lo;

                    temp_lo = ABS_ALT(this->unk11F26) / this->unk11F70;
                    this->unk11F26 -= temp_lo;

                    temp_lo = ABS_ALT(this->unk11F24) / this->unk11F70;
                    this->unk11F24 -= temp_lo;

                    temp_lo = ABS_ALT(this->unk11F2E) / this->unk11F70;
                    this->unk11F2E -= temp_lo;

                    temp_lo = ABS_ALT(this->unk11F30) / this->unk11F70;
                    this->unk11F30 -= temp_lo;

                    temp_lo = ABS_ALT(this->unk11F34) / this->unk11F70;
                    this->unk11F34 -= temp_lo;

                    this->unk11F70--;
                    if (this->unk11F70 == 0) {
                        this->unk11F14 = 0;
                        this->unk11F26 = 0;
                        this->unk11F2E = 0;
                        this->unk11F30 = 0;
                        this->unk11F24 = 0;
                        this->unk11F34 = 0;
                        this->unk11F04 = 0x15;
                    }
                    break;
            }

            if ((this->unk11F04 > 0) && (this->unk11F04 < 0xA)) {
                if (CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_START) ||
                    CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_A) ||
                    CHECK_BTN_ALL(globalCtx->state.input[0].press.button, BTN_B)) {
                    play_sound(0x4823U);
                    this->unk11F04 = 0xA;
                }
            }
        }
    }

    if (this->unk11F04 == 0) {
        if (EnvFlags_Get(globalCtx, 3)) {
            this->unk11F02 = 0x28;
            this->unk11F04 = 1;
        }
    } else if (this->unk11F04 < 0x14) {
        if (EnvFlags_Get(globalCtx, 4)) {
            this->unk11F04 = 0x14;
        }
    }
}

// EnMag_DrawTextureI8
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096C998.s")
void func_8096C998(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_I, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1024, 1024);

    *gfxp = gfx;
}

// EnMag_DrawTextureIA8
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096CBB0.s")
void func_8096CBB0(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1024, 1024);

    *gfxp = gfx;
}

// argB is an index into the scrolling arrays
// EnMag_DrawEffectTextures
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096CDC8.s")
void func_8096CDC8(Gfx** gfxp, void* maskTex, void* effectTex, s16 maskWidth, s16 maskHeight, s16 effectWidth,
                   s16 effectHeight, s16 rectLeft, s16 rectTop, u16 shifts, u16 shiftt, u16 argB, EnMag* this) {
    Gfx* gfx = *gfxp;

    gDPLoadMultiBlock_4b(gfx++, maskTex, 0x0000, G_TX_RENDERTILE, G_IM_FMT_I, maskWidth, maskHeight, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                         G_TX_NOLOD);

    gDPLoadMultiBlock(gfx++, effectTex, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, effectWidth, effectHeight, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, shifts, shiftt);

    gDPSetTileSize(gfx++, 1, this->unk11F36[argB] & 0x7F, this->unk11F44[argB] & 0x7F,
                   (this->unk11F36[argB] & 0x7F) + 0xF, (this->unk11F44[argB] & 0x7F) + 0xF);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + maskWidth) << 2, (rectTop + maskHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1024, 1024);

    *gfxp = gfx;
}

#define gDPSetTileCustom(pkt, fmt, siz, width, height, pal, cms, cmt, masks, maskt, shifts, shiftt)                    \
    {                                                                                                                  \
        gDPPipeSync(pkt);                                                                                              \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_LOADTILE, 0, cmt, maskt, shiftt, cms, \
                   masks, shifts);                                                                                     \
        gDPTileSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((width)*siz##_TILE_BYTES) + 7) >> 3, 0, G_TX_RENDERTILE, pal, cmt, maskt, shiftt,  \
                   cms, masks, shifts);                                                                                \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, 0, 0, ((width)-1) << G_TEXTURE_IMAGE_FRAC,                                \
                       ((height)-1) << G_TEXTURE_IMAGE_FRAC);                                                          \
    }

// EnMag_DrawImageRGBA32
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D230.s")
void func_8096D230(Gfx** gfxp, s16 centerX, s16 centerY, void* source, u32 width, u32 height) {
    Gfx* gfx = *gfxp;
    u8* curTexture;
    s32 textureCount;
    u32 rectLeft;
    u32 rectTop;
    u32 textureHeight;
    s32 remainingSize;
    s32 textureSize;
    s32 pad;
    s32 i;

    func_8012CA0C(&gfx);

    curTexture = source;
    rectLeft = centerX - (width / 2);
    rectTop = centerY - (height / 2);
    textureHeight = 4096 / (width << 2);
    remainingSize = (width * height) << 2;
    textureSize = (width * textureHeight) << 2;
    textureCount = remainingSize / textureSize;
    if ((remainingSize % textureSize) != 0) {
        textureCount += 1;
    }

    gDPSetTileCustom(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, textureHeight, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                     G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    remainingSize -= textureSize;

    for (i = 0; i < textureCount; i++) {
        gDPSetTextureImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, curTexture);

        gDPLoadSync(gfx++);
        gDPLoadTile(gfx++, G_TX_LOADTILE, 0, 0, (width - 1) << 2, (textureHeight - 1) << 2);

        gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + (s32)width) << 2,
                            (rectTop + textureHeight) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

        curTexture += textureSize;
        rectTop += textureHeight;

        if ((remainingSize - textureSize) < 0) {
            if (remainingSize > 0) {
                textureHeight = remainingSize / (s32)(width << 2);
                remainingSize -= textureSize;

                gDPSetTileCustom(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_32b, width, textureHeight, 0,
                                 G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK,
                                 G_TX_NOLOD, G_TX_NOLOD);
            }
        } else {
            remainingSize -= textureSize;
        }
    }

    *gfxp = gfx;
}

// EnMag_DrawCharTexture
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D60C.s")
void func_8096D60C(Gfx** gfxp, void* texture, s32 rectLeft, s32 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + 10) << 2, (rectTop + 10) << 2, G_TX_RENDERTILE,
                        0, 0, 1625, 1625);

    *gfxp = gfx;
}

extern TexturePtr D_06000000;
extern TexturePtr D_06009000;
extern TexturePtr D_06009680;
extern TexturePtr D_06009D00;
extern TexturePtr D_06010F40;
extern TexturePtr D_06011740;
extern TexturePtr D_06011BC0;
extern TexturePtr D_06011E48;

// EnMag_DrawInner
// #ifdef NON_MATCHING
// void func_8096D74C(Actor* thisx, GlobalContext* globalCtx, Gfx** gfxp) {

//     // PRESS START character indices
//     static u8 D_8096E964[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };

//     static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
//     static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
//     static TexturePtr D_8096E9A0[] = { 0x600FF40, 0x6010340, 0x6010340, 0x6010740, 0x6010B40, 0x6010B40 };

//     static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
//     static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
//     static s16 D_8096E9D0 = 0;
//     static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };

//     // s16 temp_a1;
//     // s16 temp_a1_3;
//     // s16 temp_v1_3;
//     // s16 temp_v1_5;
//     // s16 temp_a1_2;
//     // s16 temp_a1_4;
//     // s16 temp_lo;
//     // s16 temp_lo_2;
//     // s32 temp_v0_13;
//     // s32 temp_v0_15;
//     // s32 phi_a1;
//     // s32 phi_a1_2;
//     // s32 phi_s2_3;
//     // s32 phi_s2_4;
//     // s32 phi_a0;
//     // s32 phi_a0_2;
//     s32 pad;
//     EnMag* this = THIS;
//     Font* font = &this->unk170;
//     Gfx* gfx = *gfxp;
//     u16 i;
//     u16 j;
//     u16 k;
//     s32 sp1B8;
//     s32 phi_s2;

//     gSPSegment(gfx++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);

//     func_8012C680(&gfx);

//     gDPPipeSync(gfx++);
//     gDPSetCycleType(gfx++, G_CYC_2CYCLE);
//     gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
//     gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
//     gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
//                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

//     gDPSetPrimColor(gfx++, 0, this->unk11F06, this->unk11F08[0], this->unk11F08[1], this->unk11F08[2], this->unk11F14);
//     gDPSetEnvColor(gfx++, this->unk11F0E[0], this->unk11F0E[1], this->unk11F0E[2], 255);

//     // Glowy effects behind Mask
//     if (this->unk11F06 != 0) { // effectPrimLodFrac
//         for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
//             for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
//                 this->unk11F36[k] += D_8096E9B8[k];
//                 this->unk11F44[k] += D_8096E9C4[k];
//                 func_8096CDC8(&gfx, D_8096E970[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k, this);
//             }
//         }
//     }

//     func_8012C680(&gfx);
//     if (this->unk11F26 != 0) { // mainAlpha
//         gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
//                           ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

//         gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->unk11F26);
//         gDPSetEnvColor(gfx++, this->unk11F28[0], this->unk11F28[1], this->unk11F28[2], 255);

//         func_8096D230(&gfx, 0x7C, 0x67, &D_06011E48, 0x80, 0x70); // Majora's Mask image
//     }

//     gDPPipeSync(gfx++);

//     gDPSetCycleType(gfx++, G_CYC_2CYCLE);
//     gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
//     gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
//     gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
//                       ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

//     gDPSetPrimColor(gfx++, 0, this->unk11F16, this->unk11F18[0], this->unk11F18[1], this->unk11F18[2], this->unk11F24);
//     gDPSetEnvColor(gfx++, this->unk11F1E[0], this->unk11F1E[1], this->unk11F1E[2], 255);

//     // Glowy effects behind "ZELDA"
//     // phi_v1 = sp74;
//     if (this->unk11F16 != 0) {
//         for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
//             for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
//                 func_8096CDC8(&gfx, D_8096E988[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k, this);
//             }
//         }
//     }

//     if (this->unk11F30 != 0) {
//         func_8012C680(&gfx);

//         gDPSetAlphaCompare(gfx++, G_AC_NONE);
//         gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//         if (this->unk11F2E < 0x64) {
//             gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//         } else {
//             gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//         }

//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->unk11F30);
//         gDPSetEnvColor(gfx++, 100, 0, 100, 255);
//         func_8096C998(&gfx, &D_06009680, 0x68, 0x10, 0x97, 0x7C); // Flame effect mask
//     }

//     func_8012C680(&gfx);

//     gDPSetAlphaCompare(gfx++, G_AC_NONE);
//     gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//     if (this->unk11F2E < 0x64) {
//         gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//     } else {
//         gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//     }

//     gDPSetPrimColor(gfx++, 0, 0x78, 208, 102, 222, this->unk11F30);

//     func_8096C998(&gfx, &D_06009000, 0x68, 0x10, 0x97, 0x7C); // Subtitle

//     func_8012C680(&gfx);

//     gDPSetAlphaCompare(gfx++, G_AC_NONE);
//     gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//     if (this->unk11F2E != 0) {
//         gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->unk11F2E);

//         func_8096D230(&gfx, 0xB1, 0x69, &D_06000000, 0x90, 0x40); // ZELDA

//         gDPPipeSync(gfx++);

//         if (this->unk11F2E < 0x64) {
//             gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//         } else {
//             gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//         }

//         gDPSetPrimColor(gfx++, 0, 0, 208, 102, 222, this->unk11F2E);

//         func_8096C998(&gfx, &D_06009D00, 0x48, 8, 0x9E, 0x47); // "The Legend of"
//     }
//     func_8012C680(&gfx);

//     if (this->unk11F34 != 0) {
//         gDPSetAlphaCompare(gfx++, G_AC_NONE);
//         gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
//         gDPSetPrimColor(gfx++, 0, 0, this->unk11F34, this->unk11F34, this->unk11F34, this->unk11F34);

//         func_8096CBB0(&gfx, &D_06010F40, 0x80, 0x10, 0x5E, 0xC6); // Copyright
//     }

//     if (gSaveContext.fileNum == 0xFEDC) {
//         s16 temp_a1_2;

//         s16 temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
//         if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
//             temp_a1_2 = D_8096E9D0 - temp_lo;
//         } else {
//             temp_a1_2 = D_8096E9D0 + temp_lo;
//         }

//         gDPPipeSync(gfx++);
//         gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
//                           0);

//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_2);

//         D_8096E9D0 = temp_a1_2;

//         gDPLoadTextureBlock_4b(gfx++, &D_06011740, G_IM_FMT_I, 256, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         gSPTextureRectangle(gfx++, 0x0090, 0x02C0, 0x0490, 0x02E4, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, temp_a1_2);
//         gSPTextureRectangle(gfx++, 0x008C, 0x02BC, 0x048C, 0x02E0, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_2);
//         gDPLoadTextureBlock_4b(gfx++, &D_06011BC0, G_IM_FMT_I, 144, 9, 0, G_TX_NOMIRROR | G_TX_WRAP,
//                                G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         gSPTextureRectangle(gfx++, 0x0170, 0x02F4, 0x03B0, 0x0318, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, temp_a1_2);
//         gSPTextureRectangle(gfx++, 0x016C, 0x02F0, 0x03AC, 0x0314, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         D_8096E920--;
//         if (D_8096E920 == 0) {
//             // temp_v0_14 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[D_8096E91C];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C ^= 1;
//         }
//     } else if (this->unk11F34 != 0) {
//         s16 temp_a1_4;
//         s16 temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
//         if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
//             temp_a1_4 = D_8096E9D0 - temp_lo;
//         } else {
//             temp_a1_4 = D_8096E9D0 + temp_lo;
//         }

//         gDPPipeSync(gfx++);
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
//                           0);
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_4);
//         D_8096E9D0 = temp_a1_4;

//         phi_s2 = 0x78;
//         for (i = 0; i < 10; i++) {
//             // func_8096D60C(&gfx, &this->unk170.fontBuf[D_8096E964[i] * FONT_CHAR_TEX_SIZE ], phi_s2, 0xAF);
//             func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2, 0xAF);

//             phi_s2 += 7;
//             if (i == 4) {
//                 phi_s2 += 5;
//             }
//         }

//         gDPPipeSync(gfx++);
//         gDPSetPrimColor(gfx++, 0, 0, 255, 30, 30, temp_a1_4);

//         phi_s2 = 0x77;
//         for (i = 0; i < 10; i++) {
//             // func_8096D60C(&gfx, &font->fontBuf[D_8096E964[i] * FONT_CHAR_TEX_SIZE], phi_s2_4, 0xAE);
//             func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2, 0xAE);
//             phi_s2 += 7;
//             if (i == 4) {
//                 phi_s2 += 5;
//             }
//         }

//         D_8096E920--;
//         if (D_8096E920 == 0) {
//             // temp_v0_16 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[D_8096E91C];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C ^= 1;
//         }
//     }
//     *gfxp = gfx;
// }
// #else
// // PRESS START character indices
// static u8 D_8096E964[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };

// static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
// static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
// static TexturePtr D_8096E9A0[] = { 0x600FF40, 0x6010340, 0x6010340, 0x6010740, 0x6010B40, 0x6010B40 };

// static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
// static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
// static s16 D_8096E9D0 = 0;
// static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };
// void func_8096D74C(Actor* thisx, GlobalContext* globalCtx, Gfx** gfxp);
// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/func_8096D74C.s")
// #endif
void func_8096D74C(Actor* thisx, GlobalContext* globalCtx, Gfx** gfxp) {
    static u8 D_8096E964[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };
    static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
    static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
    static TexturePtr D_8096E9A0[] = { 0x600FF40, 0x6010340, 0x6010340, 0x6010740, 0x6010B40, 0x6010B40 };
    static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
    static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
    static s16 D_8096E9D0 = 0;
    static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };
    s32 pad;
    EnMag* this = (EnMag*)thisx;
    Font* font = &this->unk170;
    Gfx* gfx = *gfxp;
    u16 i;
    u16 j;
    u16 k;
    s32 phi_s2;
    s32 sp1B8;
    s16 temp_lo;

    gSPSegment(gfx++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);
    func_8012C680(&gfx);
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, 1 << 20);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, (((0 << 30) | (3 << 26)) | (0 << 22)) | (2 << 18),
                     ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, this->unk11F06, this->unk11F08[0], this->unk11F08[1], this->unk11F08[2], this->unk11F14);
    gDPSetEnvColor(gfx++, this->unk11F0E[0], this->unk11F0E[1], this->unk11F0E[2], 255);
    if (this->unk11F06 != 0) {
        for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
            for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
                this->unk11F36[k] += D_8096E9B8[k];
                this->unk11F44[k] += D_8096E9C4[k];
                func_8096CDC8(&gfx, D_8096E970[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k, this);
            }
        }
    }
    func_8012C680(&gfx);
    if (this->unk11F26 != 0) {
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, this->unk11F26);
        gDPSetEnvColor(gfx++, this->unk11F28[0], this->unk11F28[1], this->unk11F28[2], 255);
        func_8096D230(&gfx, 0x7C, 0x67, &D_06011E48, 0x80, 0x70);
    }
    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, 1 << 20);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, (((0 << 30) | (3 << 26)) | (0 << 22)) | (2 << 18),
                     ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);
    gDPSetPrimColor(gfx++, 0, this->unk11F16, this->unk11F18[0], this->unk11F18[1], this->unk11F18[2], this->unk11F24);
    gDPSetEnvColor(gfx++, this->unk11F1E[0], this->unk11F1E[1], this->unk11F1E[2], 255);
    if (this->unk11F16 != 0) {
        for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
            for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
                func_8096CDC8(&gfx, D_8096E988[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k, this);
            }
        }
    }
    if (this->unk11F30 != 0) {
        func_8012C680(&gfx);
        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        if (this->unk11F2E < 0x64) {
            gDPSetRenderMode(gfx++,
                             ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                             ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
        } else {
            gDPSetRenderMode(gfx++,
                             ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                             ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
        }
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->unk11F30);
        gDPSetEnvColor(gfx++, 100, 0, 100, 255);
        func_8096C998(&gfx, &D_06009680, 0x68, 0x10, 0x97, 0x7C);
    }
    func_8012C680(&gfx);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    if (this->unk11F2E < 0x64) {
        gDPSetRenderMode(gfx++, ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                         ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
    } else {
        gDPSetRenderMode(gfx++, ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                         ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
    }
    gDPSetPrimColor(gfx++, 0, 0x78, 208, 102, 222, this->unk11F30);
    func_8096C998(&gfx, &D_06009000, 0x68, 0x10, 0x97, 0x7C);
    func_8012C680(&gfx);
    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
    if (this->unk11F2E != 0) {
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->unk11F2E);
        func_8096D230(&gfx, 0xB1, 0x69, &D_06000000, 0x90, 0x40);
        gDPPipeSync(gfx++);
        if (this->unk11F2E < 0x64) {
            gDPSetRenderMode(gfx++,
                             ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                             ((((((0x40 | 0x300) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
        } else {
            gDPSetRenderMode(gfx++,
                             ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 30)) | (0 << 26)) | (1 << 22)) | (0 << 18),
                             ((((((0x40 | 0x200) | 0x4000) | 0) | (0 << 28)) | (0 << 24)) | (1 << 20)) | (0 << 16));
        }
        gDPSetPrimColor(gfx++, 0, 0, 208, 102, 222, this->unk11F2E);
        func_8096C998(&gfx, &D_06009D00, 0x48, 8, 0x9E, 0x47);
    }
    func_8012C680(&gfx);
    if (this->unk11F34 != 0) {
        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gfx++, 0, 0, this->unk11F34, this->unk11F34, this->unk11F34, this->unk11F34);
        func_8096CBB0(&gfx, &D_06010F40, 0x80, 0x10, 0x5E, 0xC6);
    }
    if (gSaveContext.fileNum == 0xFEDC) {
        // temp_a1 = D_8096E9D0;
        // v0 = temp_a1 - D_8096E9D4[D_8096E91C];
        temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
        // temp_lo = temp_lo;
        // if (((D_8096E9D0 - D_8096E9D4[D_8096E91C]) < 0)) {
        //   temp_lo = (-(D_8096E9D0 - D_8096E9D4[D_8096E91C]));
        // } else {
        //   temp_lo = (D_8096E9D0 - D_8096E9D4[D_8096E91C]);
        // }
        // temp_a1 = temp_lo / D_8096E920;

        // temp_lo = (((temp_a1 - D_8096E9D4[D_8096E91C]) < 0) ? (-(temp_a1 - D_8096E9D4[D_8096E91C])) : (temp_a1 -
        // D_8096E9D4[D_8096E91C])) / D_8096E920; temp_a1 = (temp_a1 >= D_8096E9D4[D_8096E91C]) ? temp_a1 - temp_lo :
        // temp_a1 + temp_lo;
        if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
            D_8096E9D0 -= temp_lo;
        } else {
            D_8096E9D0 += temp_lo;
        }
        gDPPipeSync(gfx++);
        gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_8096E9D0);
        // D_8096E9D0 = D_8096E9D0;

        gDPLoadTextureBlock_4b(gfx++, &D_06011740, 4, 256, 9, 0, 0 | 0, 0 | 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx++, 0x0090, 0x02C0, 0x0490, 0x02E4, 0, 0, 0, 0x0400, 0x0400);
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, D_8096E9D0);
        gSPTextureRectangle(gfx++, 0x008C, 0x02BC, 0x048C, 0x02E0, 0, 0, 0, 0x0400, 0x0400);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_8096E9D0);
        gDPLoadTextureBlock_4b(gfx++, &D_06011BC0, 4, 144, 9, 0, 0 | 0, 0 | 0, 0, 0, 0, 0);
        gSPTextureRectangle(gfx++, 0x0170, 0x02F4, 0x03B0, 0x0318, 0, 0, 0, 0x0400, 0x0400);
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, D_8096E9D0);
        gSPTextureRectangle(gfx++, 0x016C, 0x02F0, 0x03AC, 0x0314, 0, 0, 0, 0x0400, 0x0400);
        D_8096E920--;
        if (D_8096E920 == 0) {
            D_8096E9D0 = D_8096E9D4[D_8096E91C];
            if (gSaveContext.fileNum == 0xFEDC) {
                D_8096E920 = 0x28;
            } else {
                D_8096E920 = 0x14;
            }
            D_8096E91C ^= 1;
        }
    } else if (this->unk11F34 != 0) {
        // if (((D_8096E9D0 - D_8096E9D4[D_8096E91C]) < 0)) {
        //   temp_lo = (-(D_8096E9D0 - D_8096E9D4[D_8096E91C]));
        // } else {
        //   temp_lo = (D_8096E9D0 - D_8096E9D4[D_8096E91C]);
        // }
        // temp_a1 = temp_lo / D_8096E920;
        // temp_a1 = D_8096E9D0;
        // v0 = temp_a1 - D_8096E9D4[D_8096E91C];
        temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
        // temp_lo = (((temp_a1 - D_8096E9D4[D_8096E91C]) < 0) ? (-(temp_a1 - D_8096E9D4[D_8096E91C])) : (temp_a1 -
        // D_8096E9D4[D_8096E91C])) / D_8096E920;
        if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
            D_8096E9D0 -= temp_lo;
            // temp_a1 = (s16) temp_a1;
        } else {
            D_8096E9D0 += temp_lo;
            // temp_a1 = (s16) temp_a1;
        }
        // temp_a1 = (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) ? D_8096E9D0 - temp_a1 : D_8096E9D0 + temp_a1;

        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_8096E9D0);
        // D_8096E9D0 = D_8096E9D0;
        if (1) {}
        
        phi_s2 = 0x78;
        for (i = 0; i < 10; i++) {
            func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2, 0xAF);
            phi_s2 += 7;
            if (i == 4) {
                phi_s2 += 5;
            }
        }

        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 255, 30, 30, D_8096E9D0);
        phi_s2 = 0x77;
        for (i = 0; i < 10; i++) {
            func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2, 0xAE);
            phi_s2 += 7;
            if (i == 4) {
                phi_s2 += 5;
            }
        }

        D_8096E920--;
        if (D_8096E920 == 0) {
            D_8096E9D0 = D_8096E9D4[D_8096E91C];
            if (gSaveContext.fileNum == 0xFEDC) {
                D_8096E920 = 0x28;
            } else {
                D_8096E920 = 0x14;
            }
            D_8096E91C ^= 1;
        }
    }
    *gfxp = gfx;
}

// void func_8096D74C(Actor *thisx, GlobalContext *globalCtx, Gfx **gfxp) {

//     // PRESS START character indices
// static u8 D_8096E964[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };

// static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
// static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
// static TexturePtr D_8096E9A0[] = { 0x600FF40, 0x6010340, 0x6010340, 0x6010740, 0x6010B40, 0x6010B40 };

// static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
// static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
// static s16 D_8096E9D0 = 0;
// static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };

//     // Gfx *gfx;
//     // s32 sp1B8;
//     // EnMag *sp74;
//     // Gfx **temp_a0;
//     // Gfx **temp_a0_2;
//     // Gfx **temp_a0_3;
//     // Gfx **temp_a0_4;
//     // Gfx **temp_a0_5;
//     // Gfx **temp_a0_6;
//     // Gfx *temp_t5;
//     // Gfx *temp_t5_10;
//     // Gfx *temp_t5_11;
//     // Gfx *temp_t5_12;
//     // Gfx *temp_t5_13;
//     // Gfx *temp_t5_14;
//     // Gfx *temp_t5_2;
//     // Gfx *temp_t5_3;
//     // Gfx *temp_t5_4;
//     // Gfx *temp_t5_5;
//     // Gfx *temp_t5_6;
//     // Gfx *temp_t5_7;
//     // Gfx *temp_t5_8;
//     // Gfx *temp_t5_9;
//     // Gfx *temp_t6;
//     // Gfx *temp_t6_10;
//     // Gfx *temp_t6_11;
//     // Gfx *temp_t6_12;
//     // Gfx *temp_t6_13;
//     // Gfx *temp_t6_2;
//     // Gfx *temp_t6_3;
//     // Gfx *temp_t6_4;
//     // Gfx *temp_t6_5;
//     // Gfx *temp_t6_6;
//     // Gfx *temp_t6_7;
//     // Gfx *temp_t6_8;
//     // Gfx *temp_t6_9;
//     // Gfx *temp_t7;
//     // Gfx *temp_t7_10;
//     // Gfx *temp_t7_11;
//     // Gfx *temp_t7_12;
//     // Gfx *temp_t7_13;
//     // Gfx *temp_t7_14;
//     // Gfx *temp_t7_2;
//     // Gfx *temp_t7_3;
//     // Gfx *temp_t7_4;
//     // Gfx *temp_t7_5;
//     // Gfx *temp_t7_6;
//     // Gfx *temp_t7_7;
//     // Gfx *temp_t7_8;
//     // Gfx *temp_t7_9;
//     // Gfx *temp_t8;
//     // Gfx *temp_t8_10;
//     // Gfx *temp_t8_11;
//     // Gfx *temp_t8_12;
//     // Gfx *temp_t8_13;
//     // Gfx *temp_t8_14;
//     // Gfx *temp_t8_15;
//     // Gfx *temp_t8_16;
//     // Gfx *temp_t8_17;
//     // Gfx *temp_t8_2;
//     // Gfx *temp_t8_3;
//     // Gfx *temp_t8_4;
//     // Gfx *temp_t8_5;
//     // Gfx *temp_t8_6;
//     // Gfx *temp_t8_7;
//     // Gfx *temp_t8_8;
//     // Gfx *temp_t8_9;
//     // Gfx *temp_t9;
//     // Gfx *temp_t9_2;
//     // Gfx *temp_t9_3;
//     // Gfx *temp_t9_4;
//     // Gfx *temp_t9_5;
//     // Gfx *temp_t9_6;
//     // Gfx *temp_t9_7;
//     // Gfx *temp_t9_8;
//     // Gfx *temp_v0;
//     // Gfx *temp_v0_10;
//     // Gfx *temp_v0_11;
//     // Gfx *temp_v0_2;
//     // Gfx *temp_v0_3;
//     // Gfx *temp_v0_5;
//     // Gfx *temp_v0_6;
//     // Gfx *temp_v0_7;
//     // Gfx *temp_v0_8;
//     // Gfx *temp_v0_9;
//     // Gfx *temp_v1_2;
//     s16 temp_a1;
//     s16 temp_a1_3;
//     // s16 temp_v0_14;
//     // s16 temp_v0_16;
//     s16 temp_v1_3;
//     s16 temp_v1_5;
//     s16 temp_a1_2;
//     s16 temp_a1_4;
//     s16 temp_lo;
//     s16 temp_lo_2;
//     // s32 temp_s0;
//     // s32 temp_s0_2;
//     // s32 temp_s1;
//     // s32 temp_s1_2;
//     // s32 temp_s2;
//     // s32 temp_s2_2;
//     // s32 temp_s7;
//     // s32 temp_s7_2;
//     // s32 temp_s7_3;
//     // s32 temp_s7_4;
//     // s32 temp_v0_12;
//     s32 temp_v0_13;
//     s32 temp_v0_15;
//     // u32 temp_s5;
//     // u32 temp_s5_2;
//     // u32 temp_v1_4;
//     // void *temp_s1_3;
//     // void *temp_v0_4;
//     // void *temp_v1;
//     // s32 phi_s0;
//     // s32 phi_s2;
//     // s32 phi_s1;
//     // s32 phi_s7;
//     // s32 phi_s0_2;
//     // s32 phi_s2_2;
//     // s32 phi_s1_2;
//     // s32 phi_s7_2;
//     // void *phi_v1;
//     s32 phi_a1;
//     s32 phi_a1_2;
//     // s32 phi_s7_3;
//     s32 phi_s2_3;
//     // s32 phi_s0_3;
//     // s32 phi_s7_4;
//     s32 phi_s2_4;
//     // s32 phi_s0_4;
//     s32 phi_a0;
//     s32 phi_a0_2;

//     EnMag* this = THIS;
//     Font* font = &this->unk170;
//     Gfx* gfx = *gfxp;
//     u16 i;
//     u16 j;
//     u16 k;
//     s32 sp1B8;
//     s32 phi_s2;

//     // temp_v0 = gfx;
//     // gfx = temp_v0 + 8;
//     // temp_v0->words.w0 = 0xDB060018;
//     // temp_v0->words.w1 = (u32) globalCtx->objectCtx.status[thisx->objBankIndex].segment;
//     gSPSegment(gfx++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);

//     func_8012C680(&gfx);

//     // temp_t6 = gfx;
//     // gfx = temp_t6 + 8;
//     // temp_t6->words.w1 = 0;
//     // temp_t6->words.w0 = 0xE7000000;
//     gDPPipeSync(gfx++);

//     // temp_t9 = gfx;
//     // gfx = temp_t9 + 8;
//     // temp_t9->words.w1 = 0x100000;
//     // temp_t9->words.w0 = 0xE3000A01;
//     gDPSetCycleType(gfx++, G_CYC_2CYCLE);

//     // temp_t8 = gfx;
//     // gfx = temp_t8 + 8;
//     // temp_t8->words.w1 = 1;
//     // temp_t8->words.w0 = 0xE2001E01;
//     gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);

//     // temp_t7 = gfx;
//     // gfx = temp_t7 + 8;
//     // temp_t7->words.w0 = 0xE200001C;
//     // temp_t7->words.w1 = 0xC184340;
//     gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);

//     // temp_t6_2 = gfx;
//     // gfx = temp_t6_2 + 8;
//     // temp_t6_2->words.w0 = 0xFC272C60;
//     // temp_t6_2->words.w1 = 0x350CE37F;
//     gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
//     ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

//     // temp_v0_2 = gfx;
//     // temp_v1 = thisx + 0x10000;
//     // gfx = temp_v0_2 + 8;
//     // temp_v0_2->words.w0 = (thisx->unk11F06 & 0xFF) | 0xFA000000;
//     // temp_v0_2->words.w1 = ((thisx->unk11F0C & 0xFF) << 8) | (thisx->unk11F08 << 0x18) | ((thisx->unk11F0A & 0xFF)
//     << 0x10) | (thisx->unk11F14 & 0xFF); gDPSetPrimColor(gfx++, 0, this->unk11F06, this->unk11F08[0],
//     this->unk11F08[1], this->unk11F08[2], this->unk11F14);

//     // temp_v0_3 = gfx;
//     // gfx = temp_v0_3 + 8;
//     // temp_v0_3->words.w0 = 0xFB000000;
//     // temp_v0_3->words.w1 = ((thisx->unk11F12 & 0xFF) << 8) | (thisx->unk11F0E << 0x18) | ((thisx->unk11F10 & 0xFF)
//     << 0x10) | 0xFF; gDPSetEnvColor(gfx++, this->unk11F0E[0], this->unk11F0E[1], this->unk11F0E[2], 255);

//     // sp74 = temp_v1;
//     if (this->unk11F06 != 0) { // effectPrimLodFrac
// //         sp1B8 = 0x26;
// //         sp74 = temp_v1;
// //         phi_s7 = 0;
// //         phi_s0 = 0;
// //         do {
// //             phi_s2 = 0x39;
// //             phi_s1 = 0;
// // loop_3:
// //             // temp_v0_4 = thisx + (phi_s0 * 2);
// //             this->unk11F36[phi_s0] += D_8096E9B8[phi_s0];
// //             this->unk11F44[phi_s0] += D_8096E9C4[phi_s0];
// //             func_8096CDC8(&gfx, D_8096E970[phi_s0], D_8096E9A0[phi_s0], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1,
// 1, phi_s0, this);
// //             temp_s1 = (phi_s1 + 1) & 0xFFFF;
// //             temp_s0 = (phi_s0 + 1) & 0xFFFF;
// //             phi_s0 = temp_s0;
// //             phi_s2 += 0x40;
// //             phi_s1 = temp_s1;
// //             phi_s0 = temp_s0;
// //             if (temp_s1 < 3) {
// //                 goto loop_3;
// //             }
// //             temp_s7 = (phi_s7 + 1) & 0xFFFF;
// //             sp1B8 += 0x40;
// //             phi_s7 = temp_s7;
// //         } while (temp_s7 < 2);

//         // Taken from OoT, may have to rejig the loop
//         // u16 i;
//         // u16 j;
//         // u16 k;
//         // u16 sp1B8;
//         // u16 phi_s2;

//         for (k = 0, i = 0, sp1B8 = 38; i < 3; i++, sp1B8 += 64) {
//             for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
//                 this->unk11F36[k] += D_8096E9B8[k];
//                 this->unk11F44[k] += D_8096E9C4[k];
//                 func_8096CDC8(&gfx, D_8096E970[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k,
//                 this);
//             }
//         }
//     }

//     func_8012C680(&gfx);
//     if (this->unk11F26 != 0) { // mainAlpha
//         // temp_t8_2 = gfx;
//         // gfx = temp_t8_2 + 8;
//         // temp_t8_2->words.w0 = 0xFC309661;
//         // temp_t8_2->words.w1 = 0x552EFF7F;
//         gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
//         ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

//         // temp_v0_5 = gfx;
//         // gfx = temp_v0_5 + 8;
//         // temp_v0_5->words.w0 = 0xFA000000;
//         // temp_v0_5->words.w1 = (sp74->unk1F26 & 0xFF) | ~0xFF;
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->unk11F26);

//         // temp_a0 = &gfx;
//         // temp_v0_6 = gfx;
//         // gfx = temp_v0_6 + 8;
//         // temp_v0_6->words.w0 = 0xFB000000;
//         // temp_v0_6->words.w1 = ((sp74->unk1F2C & 0xFF) << 8) | (sp74->unk1F28 << 0x18) | ((sp74->unk1F2A & 0xFF) <<
//         0x10) | 0xFF; gDPSetEnvColor(gfx++, this->unk11F28[0], this->unk11F28[1], this->unk11F28[2], 255);

//         func_8096D230(&gfx, 0x7C, 0x67, &D_06011E48, 0x80, 0x70); // Majora's Mask image
//     }

//     // temp_t8_3 = gfx;
//     // gfx = temp_t8_3 + 8;
//     // temp_t8_3->words.w1 = 0;
//     // temp_t8_3->words.w0 = 0xE7000000;
//     gDPPipeSync(gfx++);

//     // temp_t5 = gfx;
//     // gfx = temp_t5 + 8;
//     // temp_t5->words.w1 = 0x100000;
//     // temp_t5->words.w0 = 0xE3000A01;
//     gDPSetCycleType(gfx++, G_CYC_2CYCLE);

//     // temp_t7_2 = gfx;
//     // gfx = temp_t7_2 + 8;
//     // temp_t7_2->words.w1 = 1;
//     // temp_t7_2->words.w0 = 0xE2001E01;
//     gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);

//     // temp_t6_3 = gfx;
//     // gfx = temp_t6_3 + 8;
//     // temp_t6_3->words.w0 = 0xE200001C;
//     // temp_t6_3->words.w1 = 0xC184340;
//     gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);

//     // temp_t8_4 = gfx;
//     // gfx = temp_t8_4 + 8;
//     // temp_t8_4->words.w0 = 0xFC272C60;
//     // temp_t8_4->words.w1 = 0x350CE37F;
//     gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
//     ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

//     // temp_v0_7 = gfx;
//     // gfx = temp_v0_7 + 8;
//     // temp_v0_7->words.w0 = (sp74->unk1F16 & 0xFF) | 0xFA000000;
//     // temp_v0_7->words.w1 = ((sp74->unk1F1C & 0xFF) << 8) | (sp74->unk1F18 << 0x18) | ((sp74->unk1F1A & 0xFF) <<
//     0x10) | (sp74->unk1F24 & 0xFF); gDPSetPrimColor(gfx++, 0, this->unk11F16, this->unk11F18[0], this->unk11F18[1],
//     this->unk11F18[2], this->unk11F24);

//     // temp_v0_8 = gfx;
//     // gfx = temp_v0_8 + 8;
//     // temp_v0_8->words.w0 = 0xFB000000;
//     // temp_v0_8->words.w1 = ((sp74->unk1F22 & 0xFF) << 8) | (sp74->unk1F1E << 0x18) | ((sp74->unk1F20 & 0xFF) <<
//     0x10) | 0xFF; gDPSetEnvColor(gfx++, this->unk11F1E[0], this->unk11F1E[1], this->unk11F1E[2], 255);

//     // phi_v1 = sp74;
//     if (this->unk11F16 != 0) {
// //         sp1B8 = 0x26;
// //         phi_s7_2 = 0;
// //         phi_s0_2 = 0;
// //         do {
// //             phi_s2_2 = 0x39;
// //             phi_s1_2 = 0;
// // loop_10:
// //             func_8096CDC8(&gfx, D_8096E988[phi_s0_2], D_8096E9A0[phi_s0_2], 0x40, 0x40, 0x20, 0x20, phi_s2_2,
// sp1BA, 1, 1, phi_s0_2, this);
// //             temp_s1_2 = (phi_s1_2 + 1) & 0xFFFF;
// //             temp_s0_2 = (phi_s0_2 + 1) & 0xFFFF;
// //             phi_s0_2 = temp_s0_2;
// //             phi_s2_2 += 0x40;
// //             phi_s1_2 = temp_s1_2;
// //             phi_s0_2 = temp_s0_2;
// //             if (temp_s1_2 < 3) {
// //                 goto loop_10;
// //             }
// //             temp_s7_2 = (phi_s7_2 + 1) & 0xFFFF;
// //             sp1B8 += 0x40;
// //             phi_s7_2 = temp_s7_2;
// //         } while (temp_s7_2 < 2);
// //         phi_v1 = sp74;

//         // Taken from OoT, may have to rejig the loop
//         // May also be different temps
//         // u16 i;
//         // u16 j;
//         // u16 k;
//         // s32 sp1B8;
//         // s32 phi_s2;

//         for (k = 0, i = 0, sp1B8 = 38; i < 3; i++, sp1B8 += 64) {
//             for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
//                 func_8096CDC8(&gfx, D_8096E988[k], D_8096E9A0[k], 0x40, 0x40, 0x20, 0x20, phi_s2, sp1B8, 1, 1, k,
//                 this);
//             }
//         }
//     }

//     if (this->unk11F30 != 0) {
//         func_8012C680(&gfx);
//         // temp_t5_2 = gfx;
//         // gfx = temp_t5_2 + 8;
//         // temp_t5_2->words.w1 = 0;
//         // temp_t5_2->words.w0 = 0xE2001E01;
//         gDPSetAlphaCompare(gfx++, G_AC_NONE);

//         // temp_t8_5 = gfx;
//         // temp_a0_2 = &gfx;
//         // gfx = temp_t8_5 + 8;
//         // temp_t8_5->words.w1 = 0xFF2FFFFF;
//         // temp_t8_5->words.w0 = 0xFC119623;
//         gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//         if (this->unk11F2E < 0x64) {
//             // temp_t7_3 = gfx;
//             // gfx = temp_t7_3 + 8;
//             // temp_t7_3->words.w0 = 0xE200001C;
//             // temp_t7_3->words.w1 = 0x504340;
//             gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//         } else {
//             // temp_t5_3 = gfx;
//             // gfx = temp_t5_3 + 8;
//             // temp_t5_3->words.w0 = 0xE200001C;
//             // temp_t5_3->words.w1 = 0x504240;
//             gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//         }
//         // temp_t6_4 = gfx;
//         // gfx = temp_t6_4 + 8;
//         // temp_t6_4->words.w0 = 0xFA000000;
//         // temp_t6_4->words.w1 = sp74->unk1F30 & 0xFF;
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->unk11F30);

//         // temp_t6_5 = gfx;
//         // gfx = temp_t6_5 + 8;
//         // temp_t6_5->words.w1 = 0x640064FF;
//         // temp_t6_5->words.w0 = 0xFB000000;
//         gDPSetEnvColor(gfx++, 100, 0, 100, 255);
//         func_8096C998(&gfx, &D_06009680, 0x68, 0x10, 0x97, 0x7C); // Flame effect mask
//     }

//     func_8012C680(&gfx);
//     // temp_t5_4 = gfx;
//     // gfx = temp_t5_4 + 8;
//     // temp_t5_4->words.w1 = 0;
//     // temp_t5_4->words.w0 = 0xE2001E01;
//     gDPSetAlphaCompare(gfx++, G_AC_NONE);

//     // temp_t8_6 = gfx;
//     // gfx = temp_t8_6 + 8;
//     // temp_t8_6->words.w1 = 0xFF2FFFFF;
//     // temp_t8_6->words.w0 = 0xFC119623;
//     gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//     // temp_a0_3 = &gfx;
//     if (this->unk11F2E < 0x64) {
//         // temp_t7_4 = gfx;
//         // gfx = temp_t7_4 + 8;
//         // temp_t7_4->words.w0 = 0xE200001C;
//         // temp_t7_4->words.w1 = 0x504340;
//         gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//     } else {
//         // temp_t5_5 = gfx;
//         // gfx = temp_t5_5 + 8;
//         // temp_t5_5->words.w0 = 0xE200001C;
//         // temp_t5_5->words.w1 = 0x504240;
//         gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//     }

//     // temp_v0_9 = gfx;
//     // gfx = temp_v0_9 + 8;
//     // temp_v0_9->words.w0 = 0xFA000078;
//     // temp_v0_9->words.w1 = (sp74->unk1F30 & 0xFF) | 0xD066DE00;
//     gDPSetPrimColor(gfx++, 0, 0x78, 208, 102, 222, this->unk11F30);

//     func_8096C998(&gfx, &D_06009000, 0x68, 0x10, 0x97, 0x7C); // Subtitle

//     func_8012C680(&gfx);
//     // temp_t9_2 = gfx;
//     // gfx = temp_t9_2 + 8;
//     // temp_t9_2->words.w1 = 0;
//     // temp_t9_2->words.w0 = 0xE2001E01;
//     gDPSetAlphaCompare(gfx++, G_AC_NONE);

//     // temp_t5_6 = gfx;
//     // temp_a0_4 = &gfx;
//     // gfx = temp_t5_6 + 8;
//     // temp_t5_6->words.w1 = 0xFF2FFFFF;
//     // temp_t5_6->words.w0 = 0xFC119623;
//     gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//     // temp_v0_10 = gfx;
//     if (this->unk11F2E != 0) {
//         // gfx = temp_v0_10 + 8;
//         // temp_v0_10->words.w0 = 0xFA000000;
//         // temp_v0_10->words.w1 = (sp74->unk1F2E & 0xFF) | ~0xFF;
//         gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->unk11F2E);

//         func_8096D230(&gfx, 0xB1, 0x69, &D_06000000, 0x90, 0x40); // ZELDA

//         // temp_t8_7 = gfx;
//         // temp_a0_5 = &gfx;
//         // gfx = temp_t8_7 + 8;
//         // temp_t8_7->words.w1 = 0;
//         // temp_t8_7->words.w0 = 0xE7000000;
//         gDPPipeSync(gfx++);

//         if (this->unk11F2E < 0x64) {
//             // temp_t8_8 = gfx;
//             // gfx = temp_t8_8 + 8;
//             // temp_t8_8->words.w0 = 0xE200001C;
//             // temp_t8_8->words.w1 = 0x504340;
//             gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
//         } else {
//             // temp_t9_3 = gfx;
//             // gfx = temp_t9_3 + 8;
//             // temp_t9_3->words.w0 = 0xE200001C;
//             // temp_t9_3->words.w1 = 0x504240;
//             gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
//         }
//         // temp_v0_11 = gfx;
//         // gfx = temp_v0_11 + 8;
//         // temp_v0_11->words.w0 = 0xFA000000;
//         // temp_v0_11->words.w1 = (sp74->unk1F2E & 0xFF) | 0xD066DE00;
//         gDPSetPrimColor(gfx++, 0, 0, 208, 102, 222, this->unk11F2E);

//         func_8096C998(&gfx, &D_06009D00, 0x48, 8, 0x9E, 0x47); // "The Legend of"
//     }
//     func_8012C680(&gfx);
//     // temp_t9_4 = gfx;
//     // temp_a0_6 = &gfx;
//     if (this->unk11F34 != 0) {
//         // gfx = temp_t9_4 + 8;
//         // temp_t9_4->words.w1 = 0;
//         // temp_t9_4->words.w0 = 0xE2001E01;
//         gDPSetAlphaCompare(gfx++, G_AC_NONE);

//         // temp_t5_7 = gfx;
//         // gfx = temp_t5_7 + 8;
//         // temp_t5_7->words.w1 = 0xFF2FFFFF;
//         // temp_t5_7->words.w0 = 0xFC119623;
//         gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

//         // temp_v1_2 = gfx;
//         // gfx = temp_v1_2 + 8;
//         // temp_v1_2->words.w0 = 0xFA000000;
//         // temp_v0_12 = sp74->unk1F34 & 0xFF;
//         // temp_v1_2->words.w1 = (temp_v0_12 << 0x18) | (temp_v0_12 << 0x10) | (temp_v0_12 << 8) | temp_v0_12;
//         gDPSetPrimColor(gfx++, 0, 0, this->unk11F34, this->unk11F34, this->unk11F34, this->unk11F34);

//         func_8096CBB0(&gfx, &D_06010F40, 0x80, 0x10, 0x5E, 0xC6); // Copyright
//     }

//     if (gSaveContext.fileNum == 0xFEDC) {
//         // temp_a1 = D_8096E9D0;
//         // temp_v1_3 = D_8096E9D4[D_8096E91C];
//         // temp_v0_13 = temp_a1 - temp_v1_3;
//         // // temp_t8_9 = gfx;
//         // if (temp_v0_13 < 0) {
//         //     phi_a0 = -temp_v0_13;
//         // } else {
//         //     phi_a0 = temp_v0_13;
//         // }
//         // temp_lo = phi_a0 / (s32) D_8096E920;
//         // if ((s32) temp_a1 >= (s32) temp_v1_3) {
//         //     phi_a1 = (temp_a1 - (s16) temp_lo) << 0x10;
//         // } else {
//         //     phi_a1 = (temp_a1 + (s16) temp_lo) << 0x10;
//         // }
//         // temp_a1_2 = phi_a1 >> 0x10;

//         temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
//         if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
//             temp_a1_2 = D_8096E9D0 - temp_lo;
//         } else {
//             temp_a1_2 = D_8096E9D0 + temp_lo;
//         }

//         // gfx = temp_t8_9 + 8;
//         // temp_t8_9->words.w1 = 0;
//         // temp_t8_9->words.w0 = 0xE7000000;
//         gDPPipeSync(gfx++);

//         // temp_t5_8 = gfx;
//         // gfx = temp_t5_8 + 8;
//         // temp_t5_8->words.w1 = 1;
//         // temp_t5_8->words.w0 = 0xE2001E01;
//         gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);

//         // temp_t6_6 = gfx;
//         // gfx = temp_t6_6 + 8;
//         // temp_t6_6->words.w0 = 0xFCFF97FF;
//         // temp_t6_6->words.w1 = 0xFF2DFEFF;
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
//         PRIMITIVE, 0);

//         // temp_t8_10 = gfx;
//         // temp_s5 = temp_a1_2 & 0xFF;
//         // gfx = temp_t8_10 + 8;
//         // temp_t8_10->words.w1 = temp_s5;
//         // temp_t8_10->words.w0 = 0xFA000000;
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_2);

//         D_8096E9D0 = temp_a1_2;
//         // // temp_t7_5 = gfx;
//         // // gfx = temp_t7_5 + 8;
//         // // temp_t7_5->words.w1 = (u32) &D_06011740;
//         // // temp_t7_5->words.w0 = 0xFD900000;
//         // gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, D_06011740); // Controller not connected

//         // // temp_t6_7 = gfx;
//         // // gfx = temp_t6_7 + 8;
//         // // temp_t6_7->words.w1 = 0x7000000;
//         // // temp_t6_7->words.w0 = 0xF5900000;
//         // gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 0, 0x0000, G_TX_LOADTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
//         G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

//         // // temp_t7_6 = gfx;
//         // // gfx = temp_t7_6 + 8;
//         // // temp_t7_6->words.w1 = 0;
//         // // temp_t7_6->words.w0 = 0xE6000000;
//         // gDPLoadSync(gfx++);

//         // // temp_t8_11 = gfx;
//         // // gfx = temp_t8_11 + 8;
//         // // temp_t8_11->words.w1 = 0x723F080;
//         // // temp_t8_11->words.w0 = 0xF3000000;
//         // gDPLoadBlock(gfx++, G_TX_LOADTILE, 0, 0, 575, 128);

//         // // temp_t7_7 = gfx;
//         // // gfx = temp_t7_7 + 8;
//         // // temp_t7_7->words.w1 = 0;
//         // // temp_t7_7->words.w0 = 0xE7000000;
//         // gDPPipeSync(gfx++);

//         // // temp_t8_12 = gfx;
//         // // gfx = temp_t8_12 + 8;
//         // // temp_t8_12->words.w1 = 0;
//         // // temp_t8_12->words.w0 = 0xF5802000;
//         // gDPSetTile(gfx++, G_IM_FMT_I, G_IM_SIZ_4b, 16, 0x0000, G_TX_RENDERTILE, 0, G_TX_NOMIRROR | G_TX_WRAP,
//         G_TX_NOMASK, G_TX_NOLOD, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOLOD);

//         // // temp_t7_8 = gfx;
//         // // gfx = temp_t7_8 + 8;
//         // // temp_t7_8->words.w1 = 0x3FC020;
//         // // temp_t7_8->words.w0 = 0xF2000000;
//         // gDPSetTileSize(gfx++, G_TX_RENDERTILE, 0, 0, 0x03FC, 0x0020);
//         gDPLoadTextureBlock_4b(gfx++, &D_06011740, G_IM_FMT_I, 256, 9, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR |
//         G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         // // temp_t6_8 = gfx;
//         // // gfx = temp_t6_8 + 8;
//         // // temp_t6_8->words.w0 = 0xE44902E4;
//         // // temp_t6_8->words.w1 = 0x902C0;
//         // gTexRect(gfx++, 0x0090, 0x02C0, 0x0490, 0x02E4, G_TX_RENDERTILE);

//         // temp_t8_13 = gfx;
//         // gfx = temp_t8_13 + 8;
//         // temp_t8_13->words.w1 = 0;
//         // temp_t8_13->words.w0 = 0xE1000000;

//         // temp_t5_9 = gfx;
//         // gfx = temp_t5_9 + 8;
//         // temp_t5_9->words.w1 = 0x4000400;
//         // temp_t5_9->words.w0 = 0xF1000000;

//         gSPTextureRectangle(gfx++, 0x0090, 0x02C0, 0x0490, 0x02E4, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         // temp_t9_5 = gfx;
//         // temp_v1_4 = temp_s5 | 0xCDFFFF00;
//         // gfx = temp_t9_5 + 8;
//         // temp_t9_5->words.w1 = temp_v1_4;
//         // temp_t9_5->words.w0 = 0xFA000000;
//         gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, temp_a1_2);

//         // temp_t5_10 = gfx;
//         // gfx = temp_t5_10 + 8;
//         // temp_t5_10->words.w0 = 0xE448C2E0;
//         // temp_t5_10->words.w1 = 0x8C2BC;
//         // temp_t6_9 = gfx;
//         // gfx = temp_t6_9 + 8;
//         // temp_t6_9->words.w1 = 0;
//         // temp_t6_9->words.w0 = 0xE1000000;
//         // temp_t7_9 = gfx;
//         // gfx = temp_t7_9 + 8;
//         // temp_t7_9->words.w1 = 0x4000400;
//         // temp_t7_9->words.w0 = 0xF1000000;
//         gSPTextureRectangle(gfx++, 0x008C, 0x02BC, 0x048C, 0x02E0, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         // temp_t8_14 = gfx;
//         // gfx = temp_t8_14 + 8;
//         // temp_t8_14->words.w1 = temp_s5;
//         // temp_t8_14->words.w0 = 0xFA000000;
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_2);

//         // temp_t7_10 = gfx;
//         // gfx = temp_t7_10 + 8;
//         // temp_t7_10->words.w1 = (u32) &D_06011BC0;
//         // temp_t7_10->words.w0 = 0xFD900000;
//         // temp_t6_10 = gfx;
//         // gfx = temp_t6_10 + 8;
//         // temp_t6_10->words.w1 = 0x7000000;
//         // temp_t6_10->words.w0 = 0xF5900000;
//         // temp_t7_11 = gfx;
//         // gfx = temp_t7_11 + 8;
//         // temp_t7_11->words.w1 = 0;
//         // temp_t7_11->words.w0 = 0xE6000000;
//         // temp_t8_15 = gfx;
//         // gfx = temp_t8_15 + 8;
//         // temp_t8_15->words.w1 = 0x71430E4;
//         // temp_t8_15->words.w0 = 0xF3000000;
//         // temp_t7_12 = gfx;
//         // gfx = temp_t7_12 + 8;
//         // temp_t7_12->words.w1 = 0;
//         // temp_t7_12->words.w0 = 0xE7000000;
//         // temp_t6_11 = gfx;
//         // gfx = temp_t6_11 + 8;
//         // temp_t6_11->words.w1 = 0;
//         // temp_t6_11->words.w0 = 0xF5801200;
//         // temp_t9_6 = gfx;
//         // gfx = temp_t9_6 + 8;
//         // temp_t9_6->words.w1 = 0x23C020;
//         // temp_t9_6->words.w0 = 0xF2000000;
//         gDPLoadTextureBlock_4b(gfx++, &D_06011BC0, G_IM_FMT_I, 144, 9, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR |
//         G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

//         // temp_t5_11 = gfx;
//         // gfx = temp_t5_11 + 8;
//         // temp_t5_11->words.w0 = 0xE43B0318;
//         // temp_t5_11->words.w1 = 0x1702F4;
//         // temp_t6_12 = gfx;
//         // gfx = temp_t6_12 + 8;
//         // temp_t6_12->words.w1 = 0;
//         // temp_t6_12->words.w0 = 0xE1000000;
//         // temp_t7_13 = gfx;
//         // gfx = temp_t7_13 + 8;
//         // temp_t7_13->words.w1 = 0x4000400;
//         // temp_t7_13->words.w0 = 0xF1000000;
//         gSPTextureRectangle(gfx++, 0x0170, 0x02F4, 0x03B0, 0x0318, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         // temp_t8_16 = gfx;
//         // gfx = temp_t8_16 + 8;
//         // temp_t8_16->words.w1 = temp_v1_4;
//         // temp_t8_16->words.w0 = 0xFA000000;
//         gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, temp_a1_2);

//         // temp_t7_14 = gfx;
//         // gfx = temp_t7_14 + 8;
//         // temp_t7_14->words.w0 = 0xE43AC314;
//         // temp_t7_14->words.w1 = 0x16C2F0;
//         // temp_t5_12 = gfx;
//         // gfx = temp_t5_12 + 8;
//         // temp_t5_12->words.w1 = 0;
//         // temp_t5_12->words.w0 = 0xE1000000;
//         // temp_t9_7 = gfx;
//         // gfx = temp_t9_7 + 8;
//         // temp_t9_7->words.w1 = 0x4000400;
//         // temp_t9_7->words.w0 = 0xF1000000;
//         gSPTextureRectangle(gfx++, 0x016C, 0x02F0, 0x03AC, 0x0314, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

//         D_8096E920--;
//         if (D_8096E920 == 0) {
//             // temp_v0_14 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[D_8096E91C];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C ^= 1;
//         }
//     } else if (this->unk11F34 != 0) {
//         // temp_a1_3 = D_8096E9D0;
//         // temp_v1_5 = D_8096E9D4[D_8096E91C];
//         // temp_v0_15 = temp_a1_3 - temp_v1_5;
//         // // temp_t9_8 = gfx;
//         // if (temp_v0_15 < 0) {
//         //     phi_a0_2 = -temp_v0_15;
//         // } else {
//         //     phi_a0_2 = temp_v0_15;
//         // }
//         // temp_lo_2 = phi_a0_2 / (s32) D_8096E920;
//         // if ((s32) temp_a1_3 >= (s32) temp_v1_5) {
//         //     phi_a1_2 = (temp_a1_3 - (s16) temp_lo_2) << 0x10;
//         // } else {
//         //     phi_a1_2 = (temp_a1_3 + (s16) temp_lo_2) << 0x10;
//         // }
//         // temp_a1_4 = phi_a1_2 >> 0x10;

//         temp_lo_2 = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
//         if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
//             temp_a1_4 = D_8096E9D0 - temp_lo_2;
//         } else {
//             temp_a1_4 = D_8096E9D0 + temp_lo_2;
//         }

//         // gfx = temp_t9_8 + 8;
//         // temp_t9_8->words.w1 = 0;
//         // temp_t9_8->words.w0 = 0xE7000000;
//         gDPPipeSync(gfx++);

//         // temp_t5_13 = gfx;
//         // gfx = temp_t5_13 + 8;
//         // temp_t5_13->words.w0 = 0xFCFF97FF;
//         // temp_t5_13->words.w1 = 0xFF2DFEFF;
//         gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
//         PRIMITIVE, 0);

//         // temp_t6_13 = gfx;
//         // temp_s5_2 = temp_a1_4 & 0xFF;
//         // gfx = temp_t6_13 + 8;
//         // temp_t6_13->words.w1 = temp_s5_2;
//         // temp_t6_13->words.w0 = 0xFA000000;
//         gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, temp_a1_4);
//         D_8096E9D0 = temp_a1_4;

//         // phi_s7_3 = 0;
//         // phi_s2_3 = 0x78;
//         // phi_s0_3 = 0;
//         // phi_s7_4 = 0;
//         // phi_s0_4 = 0;
//         // do {
//         //     func_8096D60C(&gfx, &this->unk170.fontBuf[D_8096E964[phi_s7_3]], phi_s2_3, 0xAF);
//         //     temp_s2 = phi_s2_3 + 7;
//         //     phi_s2_3 = temp_s2;
//         //     if (phi_s0_3 == 4) {
//         //         phi_s2_3 = temp_s2 + 5;
//         //     }
//         //     temp_s7_3 = (phi_s7_3 + 1) & 0xFFFF;
//         //     phi_s7_3 = temp_s7_3;
//         //     phi_s0_3 = temp_s7_3;
//         // } while (temp_s7_3 < 0xA);

//         phi_s2 = 0x78;
//         // i and phi_s2_3 are u16
//         for (i = 0; i < 10; i++) {
//             // May also need a font temp
//             // func_8096D60C(&gfx, &this->unk170.fontBuf[D_8096E964[i] * FONT_CHAR_TEX_SIZE ], phi_s2_3, 0xAF);
//             func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2, 0xAF);

//             // May be an if-else?
//             phi_s2 += 7;
//             if (i == 4) {
//                 phi_s2 += 5;
//             }
//         }

//         // temp_t5_14 = gfx;
//         // gfx = temp_t5_14 + 8;
//         // temp_t5_14->words.w1 = 0;
//         // temp_t5_14->words.w0 = 0xE7000000;
//         gDPPipeSync(gfx++);

//         // temp_t8_17 = gfx;
//         // gfx = temp_t8_17 + 8;
//         // temp_t8_17->words.w0 = 0xFA000000;
//         // temp_t8_17->words.w1 = temp_s5_2 | 0xFF1E1E00;
//         gDPSetPrimColor(gfx++, 0, 0, 255, 30, 30, temp_a1_4);

//         // phi_s2_4 = 0x77;
//         // do {
//         //     func_8096D60C(&gfx, &this->unk170.fontBuf[D_8096E964[phi_s7_4]], phi_s2_4, 0xAE);
//         //     temp_s2_2 = phi_s2_4 + 7;
//         //     phi_s2_4 = temp_s2_2;
//         //     if (phi_s0_4 == 4) {
//         //         phi_s2_4 = temp_s2_2 + 5;
//         //     }
//         //     temp_s7_4 = (phi_s7_4 + 1) & 0xFFFF;
//         //     phi_s7_4 = temp_s7_4;
//         //     phi_s0_4 = temp_s7_4;
//         // } while (temp_s7_4 < 0xA);

//         phi_s2_4 = 0x77;
//         for (i = 0; i < 10; i++) {
//             // func_8096D60C(&gfx, &this->unk170.fontBuf[D_8096E964[i] * FONT_CHAR_TEX_SIZE], phi_s2_4, 0xAE);
//             func_8096D60C(&gfx, font->fontBuf + D_8096E964[i] * FONT_CHAR_TEX_SIZE, phi_s2_4, 0xAE);
//             phi_s2_4 += 7;
//             if (i == 4) {
//                 phi_s2_4 += 5;
//             }
//         }

//         D_8096E920--;
//         if (D_8096E920 == 0) {
//             // temp_v0_16 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[D_8096E91C];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C ^= 1;
//         }
//     }
//     *gfxp = gfx;
// }

// #pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Mag/EnMag_Draw.s")
void EnMag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    Gfx* gfx;
    Gfx* gfxRef;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    gfxRef = POLY_OPA_DISP;
    gfx = Graph_GfxPlusOne(gfxRef);
    gSPDisplayList(OVERLAY_DISP++, gfx);

    func_8096D74C(thisx, globalCtx, &gfx);

    gSPEndDisplayList(gfx++);
    Graph_BranchDlist(gfxRef, gfx);
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// void func_8096D74C(Actor *thisx, GlobalContext *globalCtx, Gfx **gfxp) {
//     Gfx *sp1C8;
//     s32 sp1B8;
//     void *sp74;
//     Gfx **temp_a0;
//     Gfx **temp_a0_2;
//     Gfx **temp_a0_3;
//     Gfx **temp_a0_4;
//     Gfx **temp_a0_5;
//     Gfx **temp_a0_6;
//     Gfx *temp_t5;
//     Gfx *temp_t5_10;
//     Gfx *temp_t5_11;
//     Gfx *temp_t5_12;
//     Gfx *temp_t5_13;
//     Gfx *temp_t5_14;
//     Gfx *temp_t5_2;
//     Gfx *temp_t5_3;
//     Gfx *temp_t5_4;
//     Gfx *temp_t5_5;
//     Gfx *temp_t5_6;
//     Gfx *temp_t5_7;
//     Gfx *temp_t5_8;
//     Gfx *temp_t5_9;
//     Gfx *temp_t6;
//     Gfx *temp_t6_10;
//     Gfx *temp_t6_11;
//     Gfx *temp_t6_12;
//     Gfx *temp_t6_13;
//     Gfx *temp_t6_2;
//     Gfx *temp_t6_3;
//     Gfx *temp_t6_4;
//     Gfx *temp_t6_5;
//     Gfx *temp_t6_6;
//     Gfx *temp_t6_7;
//     Gfx *temp_t6_8;
//     Gfx *temp_t6_9;
//     Gfx *temp_t7;
//     Gfx *temp_t7_10;
//     Gfx *temp_t7_11;
//     Gfx *temp_t7_12;
//     Gfx *temp_t7_13;
//     Gfx *temp_t7_14;
//     Gfx *temp_t7_2;
//     Gfx *temp_t7_3;
//     Gfx *temp_t7_4;
//     Gfx *temp_t7_5;
//     Gfx *temp_t7_6;
//     Gfx *temp_t7_7;
//     Gfx *temp_t7_8;
//     Gfx *temp_t7_9;
//     Gfx *temp_t8;
//     Gfx *temp_t8_10;
//     Gfx *temp_t8_11;
//     Gfx *temp_t8_12;
//     Gfx *temp_t8_13;
//     Gfx *temp_t8_14;
//     Gfx *temp_t8_15;
//     Gfx *temp_t8_16;
//     Gfx *temp_t8_17;
//     Gfx *temp_t8_2;
//     Gfx *temp_t8_3;
//     Gfx *temp_t8_4;
//     Gfx *temp_t8_5;
//     Gfx *temp_t8_6;
//     Gfx *temp_t8_7;
//     Gfx *temp_t8_8;
//     Gfx *temp_t8_9;
//     Gfx *temp_t9;
//     Gfx *temp_t9_2;
//     Gfx *temp_t9_3;
//     Gfx *temp_t9_4;
//     Gfx *temp_t9_5;
//     Gfx *temp_t9_6;
//     Gfx *temp_t9_7;
//     Gfx *temp_t9_8;
//     Gfx *temp_v0;
//     Gfx *temp_v0_10;
//     Gfx *temp_v0_11;
//     Gfx *temp_v0_2;
//     Gfx *temp_v0_3;
//     Gfx *temp_v0_5;
//     Gfx *temp_v0_6;
//     Gfx *temp_v0_7;
//     Gfx *temp_v0_8;
//     Gfx *temp_v0_9;
//     Gfx *temp_v1_2;
//     s16 temp_a1;
//     s16 temp_a1_3;
//     s16 temp_v0_14;
//     s16 temp_v0_16;
//     s16 temp_v1_3;
//     s16 temp_v1_5;
//     s32 temp_a1_2;
//     s32 temp_a1_4;
//     s32 temp_lo;
//     s32 temp_lo_2;
//     s32 temp_s0;
//     s32 temp_s0_2;
//     s32 temp_s1;
//     s32 temp_s1_2;
//     s32 temp_s2;
//     s32 temp_s2_2;
//     s32 temp_s7;
//     s32 temp_s7_2;
//     s32 temp_s7_3;
//     s32 temp_s7_4;
//     s32 temp_v0_12;
//     s32 temp_v0_13;
//     s32 temp_v0_15;
//     u32 temp_s5;
//     u32 temp_s5_2;
//     u32 temp_v1_4;
//     void *temp_s1_3;
//     void *temp_v0_4;
//     void *temp_v1;
//     s32 phi_s0;
//     s32 phi_s2;
//     s32 phi_s1;
//     s32 phi_s7;
//     s32 phi_s0_2;
//     s32 phi_s2_2;
//     s32 phi_s1_2;
//     s32 phi_s7_2;
//     void *phi_v1;
//     s32 phi_a1;
//     s32 phi_a1_2;
//     s32 phi_s7_3;
//     s32 phi_s2_3;
//     s32 phi_s0_3;
//     s32 phi_s7_4;
//     s32 phi_s2_4;
//     s32 phi_s0_4;
//     s32 phi_a0;
//     s32 phi_a0_2;

//     sp1C8 = *gfxp;
//     temp_v0 = sp1C8;
//     sp1C8 = temp_v0 + 8;
//     temp_v0->words.w0 = 0xDB060018;
//     temp_v0->words.w1 = (u32) globalCtx->objectCtx.status[thisx->objBankIndex].segment;
//     func_8012C680(&sp1C8);
//     temp_t6 = sp1C8;
//     sp1C8 = temp_t6 + 8;
//     temp_t6->words.w1 = 0;
//     temp_t6->words.w0 = 0xE7000000;
//     temp_t9 = sp1C8;
//     sp1C8 = temp_t9 + 8;
//     temp_t9->words.w1 = 0x100000;
//     temp_t9->words.w0 = 0xE3000A01;
//     temp_t8 = sp1C8;
//     sp1C8 = temp_t8 + 8;
//     temp_t8->words.w1 = 1;
//     temp_t8->words.w0 = 0xE2001E01;
//     temp_t7 = sp1C8;
//     sp1C8 = temp_t7 + 8;
//     temp_t7->words.w0 = 0xE200001C;
//     temp_t7->words.w1 = 0xC184340;
//     temp_t6_2 = sp1C8;
//     sp1C8 = temp_t6_2 + 8;
//     temp_t6_2->words.w0 = 0xFC272C60;
//     temp_t6_2->words.w1 = 0x350CE37F;
//     temp_v0_2 = sp1C8;
//     temp_v1 = thisx + 0x10000;
//     sp1C8 = temp_v0_2 + 8;
//     temp_v0_2->words.w0 = (thisx->unk11F06 & 0xFF) | 0xFA000000;
//     temp_v0_2->words.w1 = ((thisx->unk11F0C & 0xFF) << 8) | (thisx->unk11F08 << 0x18) | ((thisx->unk11F0A & 0xFF) <<
//     0x10) | (thisx->unk11F14 & 0xFF); temp_v0_3 = sp1C8; sp1C8 = temp_v0_3 + 8; temp_v0_3->words.w0 = 0xFB000000;
//     temp_v0_3->words.w1 = ((thisx->unk11F12 & 0xFF) << 8) | (thisx->unk11F0E << 0x18) | ((thisx->unk11F10 & 0xFF) <<
//     0x10) | 0xFF; sp74 = temp_v1; if (thisx->unk11F06 != 0) {
//         sp1B8 = 0x26;
//         sp74 = temp_v1;
//         phi_s7 = 0;
//         phi_s0 = 0;
//         do {
//             phi_s2 = 0x39;
//             phi_s1 = 0;
// loop_3:
//             temp_v0_4 = thisx + (phi_s0 * 2);
//             temp_v0_4->unk11F36 = (s16) (temp_v0_4->unk11F36 + D_8096E9B8[phi_s0]);
//             temp_v0_4->unk11F44 = (s16) (temp_v0_4->unk11F44 + D_8096E9C4[phi_s0]);
//             func_8096CDC8(&sp1C8, D_8096E970[phi_s0], D_8096E9A0[phi_s0], 0x40, (s16) 0x40, (s16) 0x20, (s16) 0x20,
//             (s16) phi_s2, (s16) (s32) (s16) sp1B8, (u16) 1, (u16) 1, (u16) phi_s0, (EnMag *) thisx); temp_s1 =
//             (phi_s1 + 1) & 0xFFFF; temp_s0 = (phi_s0 + 1) & 0xFFFF; phi_s0 = temp_s0; phi_s2 += 0x40; phi_s1 =
//             temp_s1; phi_s0 = temp_s0; if (temp_s1 < 3) {
//                 goto loop_3;
//             }
//             temp_s7 = (phi_s7 + 1) & 0xFFFF;
//             sp1B8 += 0x40;
//             phi_s7 = temp_s7;
//         } while (temp_s7 < 2);
//     }
//     func_8012C680(&sp1C8);
//     if (sp74->unk1F26 != 0) {
//         temp_t8_2 = sp1C8;
//         sp1C8 = temp_t8_2 + 8;
//         temp_t8_2->words.w0 = 0xFC309661;
//         temp_t8_2->words.w1 = 0x552EFF7F;
//         temp_v0_5 = sp1C8;
//         sp1C8 = temp_v0_5 + 8;
//         temp_v0_5->words.w0 = 0xFA000000;
//         temp_a0 = &sp1C8;
//         temp_v0_5->words.w1 = (sp74->unk1F26 & 0xFF) | ~0xFF;
//         temp_v0_6 = sp1C8;
//         sp1C8 = temp_v0_6 + 8;
//         temp_v0_6->words.w0 = 0xFB000000;
//         temp_v0_6->words.w1 = ((sp74->unk1F2C & 0xFF) << 8) | (sp74->unk1F28 << 0x18) | ((sp74->unk1F2A & 0xFF) <<
//         0x10) | 0xFF; func_8096D230(temp_a0, 0x7C, 0x67, (u8 *) &D_06011E48, 0x80U, 0x70U);
//     }
//     temp_t8_3 = sp1C8;
//     sp1C8 = temp_t8_3 + 8;
//     temp_t8_3->words.w1 = 0;
//     temp_t8_3->words.w0 = 0xE7000000;
//     temp_t5 = sp1C8;
//     sp1C8 = temp_t5 + 8;
//     temp_t5->words.w1 = 0x100000;
//     temp_t5->words.w0 = 0xE3000A01;
//     temp_t7_2 = sp1C8;
//     sp1C8 = temp_t7_2 + 8;
//     temp_t7_2->words.w1 = 1;
//     temp_t7_2->words.w0 = 0xE2001E01;
//     temp_t6_3 = sp1C8;
//     sp1C8 = temp_t6_3 + 8;
//     temp_t6_3->words.w0 = 0xE200001C;
//     temp_t6_3->words.w1 = 0xC184340;
//     temp_t8_4 = sp1C8;
//     sp1C8 = temp_t8_4 + 8;
//     temp_t8_4->words.w0 = 0xFC272C60;
//     temp_t8_4->words.w1 = 0x350CE37F;
//     temp_v0_7 = sp1C8;
//     sp1C8 = temp_v0_7 + 8;
//     temp_v0_7->words.w0 = (sp74->unk1F16 & 0xFF) | 0xFA000000;
//     temp_v0_7->words.w1 = ((sp74->unk1F1C & 0xFF) << 8) | (sp74->unk1F18 << 0x18) | ((sp74->unk1F1A & 0xFF) << 0x10)
//     | (sp74->unk1F24 & 0xFF); temp_v0_8 = sp1C8; sp1C8 = temp_v0_8 + 8; temp_v0_8->words.w0 = 0xFB000000;
//     temp_v0_8->words.w1 = ((sp74->unk1F22 & 0xFF) << 8) | (sp74->unk1F1E << 0x18) | ((sp74->unk1F20 & 0xFF) << 0x10)
//     | 0xFF; phi_v1 = sp74; if (sp74->unk1F16 != 0) {
//         sp1B8 = 0x26;
//         phi_s7_2 = 0;
//         phi_s0_2 = 0;
//         do {
//             phi_s2_2 = 0x39;
//             phi_s1_2 = 0;
// loop_10:
//             func_8096CDC8(&sp1C8, D_8096E988[phi_s0_2], D_8096E9A0[phi_s0_2], 0x40, (s16) 0x40, (s16) 0x20, (s16)
//             0x20, (s16) phi_s2_2, (s16) (s32) unksp1BA, (u16) 1, (u16) 1, (u16) phi_s0_2, (EnMag *) thisx); temp_s1_2
//             = (phi_s1_2 + 1) & 0xFFFF; temp_s0_2 = (phi_s0_2 + 1) & 0xFFFF; phi_s0_2 = temp_s0_2; phi_s2_2 += 0x40;
//             phi_s1_2 = temp_s1_2;
//             phi_s0_2 = temp_s0_2;
//             if (temp_s1_2 < 3) {
//                 goto loop_10;
//             }
//             temp_s7_2 = (phi_s7_2 + 1) & 0xFFFF;
//             sp1B8 += 0x40;
//             phi_s7_2 = temp_s7_2;
//         } while (temp_s7_2 < 2);
//         phi_v1 = sp74;
//     }
//     if (phi_v1->unk1F30 != 0) {
//         func_8012C680(&sp1C8);
//         temp_t5_2 = sp1C8;
//         sp1C8 = temp_t5_2 + 8;
//         temp_t5_2->words.w1 = 0;
//         temp_t5_2->words.w0 = 0xE2001E01;
//         temp_t8_5 = sp1C8;
//         temp_a0_2 = &sp1C8;
//         sp1C8 = temp_t8_5 + 8;
//         temp_t8_5->words.w1 = 0xFF2FFFFF;
//         temp_t8_5->words.w0 = 0xFC119623;
//         if ((s32) sp74->unk1F2E < 0x64) {
//             temp_t7_3 = sp1C8;
//             sp1C8 = temp_t7_3 + 8;
//             temp_t7_3->words.w0 = 0xE200001C;
//             temp_t7_3->words.w1 = 0x504340;
//         } else {
//             temp_t5_3 = sp1C8;
//             sp1C8 = temp_t5_3 + 8;
//             temp_t5_3->words.w0 = 0xE200001C;
//             temp_t5_3->words.w1 = 0x504240;
//         }
//         temp_t6_4 = sp1C8;
//         sp1C8 = temp_t6_4 + 8;
//         temp_t6_4->words.w0 = 0xFA000000;
//         temp_t6_4->words.w1 = sp74->unk1F30 & 0xFF;
//         temp_t6_5 = sp1C8;
//         sp1C8 = temp_t6_5 + 8;
//         temp_t6_5->words.w1 = 0x640064FF;
//         temp_t6_5->words.w0 = 0xFB000000;
//         func_8096C998(temp_a0_2, &D_06009680, 0x68, 0x10, (s16) 0x97, (s16) 0x7C);
//     }
//     func_8012C680(&sp1C8);
//     temp_t5_4 = sp1C8;
//     sp1C8 = temp_t5_4 + 8;
//     temp_t5_4->words.w1 = 0;
//     temp_t5_4->words.w0 = 0xE2001E01;
//     temp_t8_6 = sp1C8;
//     sp1C8 = temp_t8_6 + 8;
//     temp_t8_6->words.w1 = 0xFF2FFFFF;
//     temp_t8_6->words.w0 = 0xFC119623;
//     temp_a0_3 = &sp1C8;
//     if ((s32) sp74->unk1F2E < 0x64) {
//         temp_t7_4 = sp1C8;
//         sp1C8 = temp_t7_4 + 8;
//         temp_t7_4->words.w0 = 0xE200001C;
//         temp_t7_4->words.w1 = 0x504340;
//     } else {
//         temp_t5_5 = sp1C8;
//         sp1C8 = temp_t5_5 + 8;
//         temp_t5_5->words.w0 = 0xE200001C;
//         temp_t5_5->words.w1 = 0x504240;
//     }
//     temp_v0_9 = sp1C8;
//     sp1C8 = temp_v0_9 + 8;
//     temp_v0_9->words.w0 = 0xFA000078;
//     temp_v0_9->words.w1 = (sp74->unk1F30 & 0xFF) | 0xD066DE00;
//     func_8096C998(temp_a0_3, &D_06009000, 0x68, 0x10, (s16) 0x97, (s16) 0x7C);
//     func_8012C680(&sp1C8);
//     temp_t9_2 = sp1C8;
//     sp1C8 = temp_t9_2 + 8;
//     temp_t9_2->words.w1 = 0;
//     temp_t9_2->words.w0 = 0xE2001E01;
//     temp_t5_6 = sp1C8;
//     temp_a0_4 = &sp1C8;
//     sp1C8 = temp_t5_6 + 8;
//     temp_t5_6->words.w1 = 0xFF2FFFFF;
//     temp_t5_6->words.w0 = 0xFC119623;
//     temp_v0_10 = sp1C8;
//     if (sp74->unk1F2E != 0) {
//         sp1C8 = temp_v0_10 + 8;
//         temp_v0_10->words.w0 = 0xFA000000;
//         temp_v0_10->words.w1 = (sp74->unk1F2E & 0xFF) | ~0xFF;
//         func_8096D230(temp_a0_4, 0xB1, 0x69, &D_06000000, 0x90U, 0x40U);
//         temp_t8_7 = sp1C8;
//         temp_a0_5 = &sp1C8;
//         sp1C8 = temp_t8_7 + 8;
//         temp_t8_7->words.w1 = 0;
//         temp_t8_7->words.w0 = 0xE7000000;
//         if ((s32) sp74->unk1F2E < 0x64) {
//             temp_t8_8 = sp1C8;
//             sp1C8 = temp_t8_8 + 8;
//             temp_t8_8->words.w0 = 0xE200001C;
//             temp_t8_8->words.w1 = 0x504340;
//         } else {
//             temp_t9_3 = sp1C8;
//             sp1C8 = temp_t9_3 + 8;
//             temp_t9_3->words.w0 = 0xE200001C;
//             temp_t9_3->words.w1 = 0x504240;
//         }
//         temp_v0_11 = sp1C8;
//         sp1C8 = temp_v0_11 + 8;
//         temp_v0_11->words.w0 = 0xFA000000;
//         temp_v0_11->words.w1 = (sp74->unk1F2E & 0xFF) | 0xD066DE00;
//         func_8096C998(temp_a0_5, &D_06009D00, 0x48, 8, (s16) 0x9E, (s16) 0x47);
//     }
//     func_8012C680(&sp1C8);
//     temp_t9_4 = sp1C8;
//     temp_a0_6 = &sp1C8;
//     if (sp74->unk1F34 != 0) {
//         sp1C8 = temp_t9_4 + 8;
//         temp_t9_4->words.w1 = 0;
//         temp_t9_4->words.w0 = 0xE2001E01;
//         temp_t5_7 = sp1C8;
//         sp1C8 = temp_t5_7 + 8;
//         temp_t5_7->words.w1 = 0xFF2FFFFF;
//         temp_t5_7->words.w0 = 0xFC119623;
//         temp_v1_2 = sp1C8;
//         sp1C8 = temp_v1_2 + 8;
//         temp_v1_2->words.w0 = 0xFA000000;
//         temp_v0_12 = sp74->unk1F34 & 0xFF;
//         temp_v1_2->words.w1 = (temp_v0_12 << 0x18) | (temp_v0_12 << 0x10) | (temp_v0_12 << 8) | temp_v0_12;
//         func_8096CBB0(temp_a0_6, &D_06010F40, 0x80, 0x10, (s16) 0x5E, (s16) 0xC6);
//     }
//     if (gSaveContext.fileNum == 0xFEDC) {
//         temp_a1 = D_8096E9D0;
//         temp_v1_3 = D_8096E9D4[D_8096E91C];
//         temp_v0_13 = temp_a1 - temp_v1_3;
//         temp_t8_9 = sp1C8;
//         if (temp_v0_13 < 0) {
//             phi_a0 = -temp_v0_13;
//         } else {
//             phi_a0 = temp_v0_13;
//         }
//         temp_lo = phi_a0 / (s32) D_8096E920;
//         if ((s32) temp_a1 >= (s32) temp_v1_3) {
//             phi_a1 = (temp_a1 - (s16) temp_lo) << 0x10;
//         } else {
//             phi_a1 = (temp_a1 + (s16) temp_lo) << 0x10;
//         }
//         temp_a1_2 = phi_a1 >> 0x10;
//         sp1C8 = temp_t8_9 + 8;
//         temp_t8_9->words.w1 = 0;
//         temp_t8_9->words.w0 = 0xE7000000;
//         temp_t5_8 = sp1C8;
//         sp1C8 = temp_t5_8 + 8;
//         temp_t5_8->words.w1 = 1;
//         temp_t5_8->words.w0 = 0xE2001E01;
//         temp_t6_6 = sp1C8;
//         sp1C8 = temp_t6_6 + 8;
//         temp_t6_6->words.w0 = 0xFCFF97FF;
//         temp_t6_6->words.w1 = 0xFF2DFEFF;
//         temp_t8_10 = sp1C8;
//         temp_s5 = temp_a1_2 & 0xFF;
//         sp1C8 = temp_t8_10 + 8;
//         temp_t8_10->words.w1 = temp_s5;
//         temp_t8_10->words.w0 = 0xFA000000;
//         D_8096E9D0 = (s16) temp_a1_2;
//         temp_t7_5 = sp1C8;
//         sp1C8 = temp_t7_5 + 8;
//         temp_t7_5->words.w1 = (u32) &D_06011740;
//         temp_t7_5->words.w0 = 0xFD900000;
//         temp_t6_7 = sp1C8;
//         sp1C8 = temp_t6_7 + 8;
//         temp_t6_7->words.w1 = 0x7000000;
//         temp_t6_7->words.w0 = 0xF5900000;
//         temp_t7_6 = sp1C8;
//         sp1C8 = temp_t7_6 + 8;
//         temp_t7_6->words.w1 = 0;
//         temp_t7_6->words.w0 = 0xE6000000;
//         temp_t8_11 = sp1C8;
//         sp1C8 = temp_t8_11 + 8;
//         temp_t8_11->words.w1 = 0x723F080;
//         temp_t8_11->words.w0 = 0xF3000000;
//         temp_t7_7 = sp1C8;
//         sp1C8 = temp_t7_7 + 8;
//         temp_t7_7->words.w1 = 0;
//         temp_t7_7->words.w0 = 0xE7000000;
//         temp_t8_12 = sp1C8;
//         sp1C8 = temp_t8_12 + 8;
//         temp_t8_12->words.w1 = 0;
//         temp_t8_12->words.w0 = 0xF5802000;
//         temp_t7_8 = sp1C8;
//         sp1C8 = temp_t7_8 + 8;
//         temp_t7_8->words.w1 = 0x3FC020;
//         temp_t7_8->words.w0 = 0xF2000000;
//         temp_t6_8 = sp1C8;
//         sp1C8 = temp_t6_8 + 8;
//         temp_t6_8->words.w0 = 0xE44902E4;
//         temp_t6_8->words.w1 = 0x902C0;
//         temp_t8_13 = sp1C8;
//         sp1C8 = temp_t8_13 + 8;
//         temp_t8_13->words.w1 = 0;
//         temp_t8_13->words.w0 = 0xE1000000;
//         temp_t5_9 = sp1C8;
//         sp1C8 = temp_t5_9 + 8;
//         temp_t5_9->words.w1 = 0x4000400;
//         temp_t5_9->words.w0 = 0xF1000000;
//         temp_t9_5 = sp1C8;
//         temp_v1_4 = temp_s5 | 0xCDFFFF00;
//         sp1C8 = temp_t9_5 + 8;
//         temp_t9_5->words.w1 = temp_v1_4;
//         temp_t9_5->words.w0 = 0xFA000000;
//         temp_t5_10 = sp1C8;
//         sp1C8 = temp_t5_10 + 8;
//         temp_t5_10->words.w0 = 0xE448C2E0;
//         temp_t5_10->words.w1 = 0x8C2BC;
//         temp_t6_9 = sp1C8;
//         sp1C8 = temp_t6_9 + 8;
//         temp_t6_9->words.w1 = 0;
//         temp_t6_9->words.w0 = 0xE1000000;
//         temp_t7_9 = sp1C8;
//         sp1C8 = temp_t7_9 + 8;
//         temp_t7_9->words.w1 = 0x4000400;
//         temp_t7_9->words.w0 = 0xF1000000;
//         temp_t8_14 = sp1C8;
//         sp1C8 = temp_t8_14 + 8;
//         temp_t8_14->words.w1 = temp_s5;
//         temp_t8_14->words.w0 = 0xFA000000;
//         temp_t7_10 = sp1C8;
//         sp1C8 = temp_t7_10 + 8;
//         temp_t7_10->words.w1 = (u32) &D_06011BC0;
//         temp_t7_10->words.w0 = 0xFD900000;
//         temp_t6_10 = sp1C8;
//         sp1C8 = temp_t6_10 + 8;
//         temp_t6_10->words.w1 = 0x7000000;
//         temp_t6_10->words.w0 = 0xF5900000;
//         temp_t7_11 = sp1C8;
//         sp1C8 = temp_t7_11 + 8;
//         temp_t7_11->words.w1 = 0;
//         temp_t7_11->words.w0 = 0xE6000000;
//         temp_t8_15 = sp1C8;
//         sp1C8 = temp_t8_15 + 8;
//         temp_t8_15->words.w1 = 0x71430E4;
//         temp_t8_15->words.w0 = 0xF3000000;
//         temp_t7_12 = sp1C8;
//         sp1C8 = temp_t7_12 + 8;
//         temp_t7_12->words.w1 = 0;
//         temp_t7_12->words.w0 = 0xE7000000;
//         temp_t6_11 = sp1C8;
//         sp1C8 = temp_t6_11 + 8;
//         temp_t6_11->words.w1 = 0;
//         temp_t6_11->words.w0 = 0xF5801200;
//         temp_t9_6 = sp1C8;
//         sp1C8 = temp_t9_6 + 8;
//         temp_t9_6->words.w1 = 0x23C020;
//         temp_t9_6->words.w0 = 0xF2000000;
//         temp_t5_11 = sp1C8;
//         sp1C8 = temp_t5_11 + 8;
//         temp_t5_11->words.w0 = 0xE43B0318;
//         temp_t5_11->words.w1 = 0x1702F4;
//         temp_t6_12 = sp1C8;
//         sp1C8 = temp_t6_12 + 8;
//         temp_t6_12->words.w1 = 0;
//         temp_t6_12->words.w0 = 0xE1000000;
//         temp_t7_13 = sp1C8;
//         sp1C8 = temp_t7_13 + 8;
//         temp_t7_13->words.w1 = 0x4000400;
//         temp_t7_13->words.w0 = 0xF1000000;
//         temp_t8_16 = sp1C8;
//         sp1C8 = temp_t8_16 + 8;
//         temp_t8_16->words.w1 = temp_v1_4;
//         temp_t8_16->words.w0 = 0xFA000000;
//         temp_t7_14 = sp1C8;
//         sp1C8 = temp_t7_14 + 8;
//         temp_t7_14->words.w0 = 0xE43AC314;
//         temp_t7_14->words.w1 = 0x16C2F0;
//         temp_t5_12 = sp1C8;
//         sp1C8 = temp_t5_12 + 8;
//         temp_t5_12->words.w1 = 0;
//         temp_t5_12->words.w0 = 0xE1000000;
//         temp_t9_7 = sp1C8;
//         sp1C8 = temp_t9_7 + 8;
//         temp_t9_7->words.w1 = 0x4000400;
//         temp_t9_7->words.w0 = 0xF1000000;
//         D_8096E920 += -1;
//         if (D_8096E920 == 0) {
//             temp_v0_14 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[temp_v0_14];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C = temp_v0_14 ^ 1;
//         }
//     } else if (sp74->unk1F34 != 0) {
//         temp_a1_3 = D_8096E9D0;
//         temp_v1_5 = D_8096E9D4[D_8096E91C];
//         temp_v0_15 = temp_a1_3 - temp_v1_5;
//         temp_t9_8 = sp1C8;
//         if (temp_v0_15 < 0) {
//             phi_a0_2 = -temp_v0_15;
//         } else {
//             phi_a0_2 = temp_v0_15;
//         }
//         temp_lo_2 = phi_a0_2 / (s32) D_8096E920;
//         if ((s32) temp_a1_3 >= (s32) temp_v1_5) {
//             phi_a1_2 = (temp_a1_3 - (s16) temp_lo_2) << 0x10;
//         } else {
//             phi_a1_2 = (temp_a1_3 + (s16) temp_lo_2) << 0x10;
//         }
//         temp_a1_4 = phi_a1_2 >> 0x10;
//         sp1C8 = temp_t9_8 + 8;
//         temp_t9_8->words.w1 = 0;
//         temp_t9_8->words.w0 = 0xE7000000;
//         temp_t5_13 = sp1C8;
//         sp1C8 = temp_t5_13 + 8;
//         temp_t5_13->words.w0 = 0xFCFF97FF;
//         temp_t5_13->words.w1 = 0xFF2DFEFF;
//         temp_t6_13 = sp1C8;
//         temp_s5_2 = temp_a1_4 & 0xFF;
//         sp1C8 = temp_t6_13 + 8;
//         temp_t6_13->words.w1 = temp_s5_2;
//         temp_t6_13->words.w0 = 0xFA000000;
//         D_8096E9D0 = (s16) temp_a1_4;
//         temp_s1_3 = thisx + 0x170;
//         phi_s7_3 = 0;
//         phi_s2_3 = 0x78;
//         phi_s0_3 = 0;
//         phi_s7_4 = 0;
//         phi_s0_4 = 0;
//         do {
//             func_8096D60C(&sp1C8, (D_8096E964[phi_s7_3] << 7) + temp_s1_3 + 0x7880, phi_s2_3, 0xAF);
//             temp_s2 = phi_s2_3 + 7;
//             phi_s2_3 = temp_s2;
//             if (phi_s0_3 == 4) {
//                 phi_s2_3 = temp_s2 + 5;
//             }
//             temp_s7_3 = (phi_s7_3 + 1) & 0xFFFF;
//             phi_s7_3 = temp_s7_3;
//             phi_s0_3 = temp_s7_3;
//         } while (temp_s7_3 < 0xA);
//         temp_t5_14 = sp1C8;
//         sp1C8 = temp_t5_14 + 8;
//         temp_t5_14->words.w1 = 0;
//         temp_t5_14->words.w0 = 0xE7000000;
//         temp_t8_17 = sp1C8;
//         sp1C8 = temp_t8_17 + 8;
//         temp_t8_17->words.w0 = 0xFA000000;
//         temp_t8_17->words.w1 = temp_s5_2 | 0xFF1E1E00;
//         phi_s2_4 = 0x77;
//         do {
//             func_8096D60C(&sp1C8, (D_8096E964[phi_s7_4] << 7) + temp_s1_3 + 0x7880, phi_s2_4, 0xAE);
//             temp_s2_2 = phi_s2_4 + 7;
//             phi_s2_4 = temp_s2_2;
//             if (phi_s0_4 == 4) {
//                 phi_s2_4 = temp_s2_2 + 5;
//             }
//             temp_s7_4 = (phi_s7_4 + 1) & 0xFFFF;
//             phi_s7_4 = temp_s7_4;
//             phi_s0_4 = temp_s7_4;
//         } while (temp_s7_4 < 0xA);
//         D_8096E920 += -1;
//         if (D_8096E920 == 0) {
//             temp_v0_16 = D_8096E91C;
//             D_8096E9D0 = D_8096E9D4[temp_v0_16];
//             if (gSaveContext.fileNum == 0xFEDC) {
//                 D_8096E920 = 0x28;
//             } else {
//                 D_8096E920 = 0x14;
//             }
//             D_8096E91C = temp_v0_16 ^ 1;
//         }
//     }
//     *gfxp = sp1C8;
// }
