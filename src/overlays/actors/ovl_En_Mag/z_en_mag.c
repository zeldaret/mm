/*
 * File: z_en_mag.c
 * Overlay: ovl_En_Mag
 * Description: Title Logo
 */

#include "z_en_mag.h"
#include "objects/object_mag/object_mag.h"

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

// Used in Update
static s16 D_8096E958[] = { 255, 155 };
static s16 D_8096E95C[] = { 255, 0 };
static s16 D_8096E960[] = { 0, 155 };

typedef struct {
    /* 0 */ s16 r;
    /* 2 */ s16 g;
    /* 4 */ s16 b;
} Color_RGB16; // size = 0x6

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
    this->unk11F0E[0] = 0;
    this->unk11F0E[1] = 255;
    this->unk11F0E[2] = 155;

    this->unk11F06 = 20;
    this->unk11F14 = 0;

    this->unk11F18[0] = 255;
    this->unk11F18[1] = 155;
    this->unk11F18[2] = 255;
    this->unk11F1E[0] = 0;
    this->unk11F1E[1] = 255;
    this->unk11F1E[2] = 155;

    this->unk11F16 = 55;

    this->unk11F24 = 0;
    this->unk11F26 = 0;
    this->unk11F28[0] = this->unk11F28[1] = this->unk11F28[2] = 255;

    this->mainTitleAlpha = this->subtitleAlpha = this->unk11F32 = this->copyrightAlpha = 0;

    this->unk11F02 = 30;
    this->unk11F00 = this->unk11F04 = 0;

    if (gSaveContext.unk_3F1E != 0) {
        this->mainTitleAlpha = 210;
        this->unk11F32 = 255;
        this->copyrightAlpha = 255;
        this->unk11F06 = 100;
        this->unk11F14 = 255;
        this->unk11F08[0] = 255;
        this->unk11F08[1] = 255;
        this->unk11F08[2] = 255;
        this->unk11F0E[0] = 0;
        this->unk11F0E[1] = 255;
        this->unk11F0E[2] = 155;
        this->unk11F16 = 100;
        this->unk11F24 = 255;
        this->unk11F18[0] = 255;
        this->unk11F18[1] = 255;
        this->unk11F18[2] = 255;
        this->unk11F1E[0] = 0;
        this->unk11F1E[1] = 255;
        this->unk11F1E[2] = 155;
        gSaveContext.unk_3F1E = 0;
        this->unk11F04 = 2;
        D_8096E910 = 20;
        gSaveContext.fadeDuration = 1;
        gSaveContext.unk_3F51 = 255;
    }

    Font_LoadOrderedFont(&this->font);
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

void EnMag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

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

    temp_lo = ABS_ALT(this->unk11F1E[0] - D_8096E950[D_8096E918]) / D_8096E914;
    if (this->unk11F1E[0] >= D_8096E950[D_8096E918]) {
        this->unk11F1E[0] -= temp_lo;
    } else {
        this->unk11F1E[0] += temp_lo;
    }

    // Skips 4

    temp_lo = ABS_ALT(this->unk11F1E[2] - D_8096E954[D_8096E918]) / D_8096E914;
    if (this->unk11F1E[2] >= D_8096E954[D_8096E918]) {
        this->unk11F1E[2] -= temp_lo;
    } else {
        this->unk11F1E[2] += temp_lo;
    }

    D_8096E914--;
    if (D_8096E914 == 0) {
        this->unk11F18[0] = D_8096E944[D_8096E918];
        this->unk11F18[1] = D_8096E948[D_8096E918];
        this->unk11F18[2] = D_8096E94C[D_8096E918];
        this->unk11F1E[0] = D_8096E950[D_8096E918];
        // Skips 4
        this->unk11F1E[2] = D_8096E954[D_8096E918];
        D_8096E914 = 30;
        D_8096E918 ^= 1;
    }
}

void EnMag_Update(Actor* thisx, GlobalContext* globalCtx) {
    s16 temp_lo;
    s32 pad[2];
    EnMag* this = (EnMag*)thisx;

    if (gSaveContext.fileNum != 0xFEDC) {
        if (this->unk11F04 == 0) {
            if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {

                if (!EnvFlags_Get(globalCtx, 4)) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    this->unk11F04 = 10;
                    this->unk11F00 = 0;
                    this->unk11F02 = 30;
                    D_8096E910 = 20;
                    gSaveContext.fadeDuration = 1;
                    gSaveContext.unk_3F51 = 255;
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

                    temp_lo = ABS_ALT(this->unk11F14 - 255) / this->unk11F64;
                    this->unk11F14 += temp_lo;

                    temp_lo = ABS_ALT(this->unk11F06 - 32) / this->unk11F64;
                    this->unk11F06 += temp_lo;

                    this->unk11F64--;
                    if (this->unk11F64 == 0) {
                        this->unk11F08[1] = D_8096E958[0];
                        this->unk11F0E[0] = D_8096E95C[0];
                        this->unk11F0E[2] = D_8096E960[0];
                        this->unk11F14 = 255;
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

                        temp_lo = ABS_ALT(this->unk11F06 - 128) / this->unk11F66;
                        this->unk11F06 += temp_lo;

                        temp_lo = ABS_ALT(this->unk11F26 - 255) / this->unk11F66;
                        this->unk11F26 += temp_lo;

                        this->unk11F66--;
                        if (this->unk11F66 == 0) {
                            this->unk11F08[1] = D_8096E958[1];
                            this->unk11F0E[0] = D_8096E95C[1];
                            this->unk11F0E[2] = D_8096E960[1];
                            this->unk11F06 = 128;
                            this->unk11F26 = 255;
                            this->unk11F04 = 3;
                            this->unk11F72 = 5;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 3:
                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->mainTitleAlpha - 255) / this->unk11F68;
                        this->mainTitleAlpha += temp_lo;

                        this->unk11F68--;
                        if (this->unk11F68 == 0) {
                            this->unk11F68 = 1;
                            this->mainTitleAlpha = 255;
                        }

                        temp_lo = ABS_ALT(this->unk11F14 - 60) / this->unk11F6A;
                        this->unk11F14 -= temp_lo;

                        temp_lo = ABS_ALT(this->unk11F24 - 255) / this->unk11F6A;
                        this->unk11F24 += temp_lo;

                        temp_lo = ABS_ALT(this->unk11F16 - 128) / this->unk11F6A;
                        this->unk11F16 += temp_lo;

                        this->unk11F6A--;
                        // Reset everything?
                        if (this->unk11F6A == 0) {
                            this->unk11F14 = 60;
                            this->unk11F24 = 255;
                            this->unk11F16 = 128;
                            this->unk11F04 = 5;
                            this->unk11F72 = 20;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 5:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->subtitleAlpha - 255) / this->unk11F6C;
                        this->subtitleAlpha += temp_lo;

                        this->unk11F6C--;
                        if (this->unk11F6C == 0) {
                            this->unk11F24 = 255;
                            this->unk11F04 = 6;
                            this->unk11F72 = 20;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 6:
                    func_8096B604(&this->actor);

                    if (this->unk11F72 == 0) {
                        temp_lo = ABS_ALT(this->copyrightAlpha - 255) / this->unk11F6E;
                        this->copyrightAlpha += temp_lo;

                        this->unk11F6E--;
                        if (this->unk11F6E == 0) {
                            this->copyrightAlpha = 255;
                            this->unk11F04 = 13;
                        }
                    } else {
                        this->unk11F72--;
                    }
                    break;

                case 10:
                    this->unk11F08[1] = D_8096E958[0];
                    this->unk11F0E[0] = D_8096E95C[0];
                    this->unk11F0E[2] = D_8096E960[0];
                    this->unk11F14 = 60;
                    this->unk11F06 = 128;
                    this->unk11F26 = 255;
                    this->mainTitleAlpha = 255;
                    this->unk11F24 = 255;
                    this->unk11F16 = 128;
                    this->subtitleAlpha = 255;
                    this->copyrightAlpha = 255;
                    this->unk11F04 = 13;
                    break;

                case 13:
                    func_8096B604(&this->actor);

                    if (D_8096E910 == 0) {
                        if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                            CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                            CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {
                            if (globalCtx->sceneLoadFlag != 0x14) {
                                func_801A3F54(0);
                                D_801BB12C++;
                                if (D_801BB12C >= 2) {
                                    D_801BB12C = 0;
                                }
                                play_sound(NA_SE_SY_PIECE_OF_HEART);
                                gSaveContext.gameMode = 2;
                                globalCtx->sceneLoadFlag = 20;
                                globalCtx->unk_1887F = 2;
                                globalCtx->nextEntranceIndex = 0x1C00;
                                gSaveContext.cutscene = 0;
                                gSaveContext.sceneSetupIndex = 0;
                            }
                            this->unk11F54 = 15;
                            this->unk11F56 = 25;
                            this->unk11F04 = 20;
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

                    temp_lo = ABS_ALT(this->mainTitleAlpha) / this->unk11F70;
                    this->mainTitleAlpha -= temp_lo;

                    temp_lo = ABS_ALT(this->subtitleAlpha) / this->unk11F70;
                    this->subtitleAlpha -= temp_lo;

                    temp_lo = ABS_ALT(this->copyrightAlpha) / this->unk11F70;
                    this->copyrightAlpha -= temp_lo;

                    this->unk11F70--;
                    if (this->unk11F70 == 0) {
                        this->unk11F14 = 0;
                        this->unk11F26 = 0;
                        this->mainTitleAlpha = 0;
                        this->subtitleAlpha = 0;
                        this->unk11F24 = 0;
                        this->copyrightAlpha = 0;
                        this->unk11F04 = 21;
                    }
                    break;
            }

            if ((this->unk11F04 > 0) && (this->unk11F04 < 10)) {
                if (CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_START) ||
                    CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_A) ||
                    CHECK_BTN_ALL(CONTROLLER1(globalCtx)->press.button, BTN_B)) {
                    play_sound(NA_SE_SY_PIECE_OF_HEART);
                    this->unk11F04 = 10;
                }
            }
        }
    }

    if (this->unk11F04 == 0) {
        if (EnvFlags_Get(globalCtx, 3)) {
            this->unk11F02 = 40;
            this->unk11F04 = 1;
        }
    } else if (this->unk11F04 < 20) {
        if (EnvFlags_Get(globalCtx, 4)) {
            this->unk11F04 = 20;
        }
    }
}

#define EnMag_DrawTextureI8 func_8096C998
/**
 * Draws an i8 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param texWidth Width of the texture.
 * @param texHeight Height of the texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
void EnMag_DrawTextureI8(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_I, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    *gfxp = gfx;
}

#define EnMag_DrawTextureIA8 func_8096CBB0
/**
 * Draws an ia8 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param texWidth Width of the texture.
 * @param texHeight Height of the texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
void EnMag_DrawTextureIA8(Gfx** gfxp, void* texture, s16 texWidth, s16 texHeight, s16 rectLeft, s16 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock(gfx++, texture, G_IM_FMT_IA, G_IM_SIZ_8b, texWidth, texHeight, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + texWidth) << 2, (rectTop + texHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

    *gfxp = gfx;
}

// index is an index into the scrolling arrays
#define EnMag_DrawEffectTextures func_8096CDC8

/**
 * Draws an i8 effect texture, masking it with an i4 mask, with shifting
 *
 * @param gfxp Pointer to current displaylist.
 * @param maskTex Texture with which to mask.
 * @param effectTex Effect texture to draw.
 * @param maskWidth Width of masking texture.
 * @param maskHeight Height of masking texture.
 * @param effectWidth Width of effect texture.
 * @param effectHeight Height of effect texture.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 * @param shifts
 * @param shiftt
 * @param index Index into the ??? arrays to use for tile size.
 * @param this Pointer to EnMag instance.
 */
void EnMag_DrawEffectTextures(Gfx** gfxp, void* maskTex, void* effectTex, s16 maskWidth, s16 maskHeight,
                              s16 effectWidth, s16 effectHeight, s16 rectLeft, s16 rectTop, u16 shifts, u16 shiftt,
                              u16 index, EnMag* this) {
    Gfx* gfx = *gfxp;

    gDPLoadMultiBlock_4b(gfx++, maskTex, 0x0000, G_TX_RENDERTILE, G_IM_FMT_I, maskWidth, maskHeight, 0,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD,
                         G_TX_NOLOD);

    gDPLoadMultiBlock(gfx++, effectTex, 0x0100, 1, G_IM_FMT_I, G_IM_SIZ_8b, effectWidth, effectHeight, 0,
                      G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, 5, 5, shifts, shiftt);

    gDPSetTileSize(gfx++, 1, this->unk11F36[index] & 0x7F, this->unk11F44[index] & 0x7F,
                   (this->unk11F36[index] & 0x7F) + 0xF, (this->unk11F44[index] & 0x7F) + 0xF);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + maskWidth) << 2, (rectTop + maskHeight) << 2,
                        G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

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

#define TMEM_SIZE (1 << 12)

// EnMag_DrawImageRGBA32
#define EnMag_DrawImageRGBA32 func_8096D230
/**
 * Draws an rgba32 texture. Because these are so large, this will draw the texture in horizontal stripes, each narrow
 * enough that that part of the texture will fit into TMEM's 4kB.
 *
 * @param gfxp Pointer to current displaylist.
 * @param centerX X coordinate of the center of the draw position.
 * @param centerY Y coordinate of the center of the draw position.
 * @param source Texture to draw.
 * @param width Width of the texture.
 * @param height Height of the texture.
 */
void EnMag_DrawImageRGBA32(Gfx** gfxp, s16 centerX, s16 centerY, void* source, u32 width, u32 height) {
    Gfx* gfx = *gfxp;
    uintptr_t curTexture;
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
    textureHeight = TMEM_SIZE / (width << 2);
    remainingSize = (width * height) << 2;
    textureSize = (width * textureHeight) << 2;
    textureCount = remainingSize / textureSize;
    if ((remainingSize % textureSize) != 0) {
        textureCount++;
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

#define EnMag_DrawCharTexture func_8096D60C
/**
 * Draws one character, expected to be a 16 by 16 i4 texture.
 *
 * @param gfxp Pointer to current displaylist.
 * @param texture Texture to draw.
 * @param rectLeft X coordinate of the top-left of the draw position.
 * @param rectTop Y coordinate of the top-left of the draw position.
 */
void EnMag_DrawCharTexture(Gfx** gfxp, void* texture, s32 rectLeft, s32 rectTop) {
    Gfx* gfx = *gfxp;

    gDPLoadTextureBlock_4b(gfx++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    gSPTextureRectangle(gfx++, rectLeft << 2, rectTop << 2, (rectLeft + 10) << 2, (rectTop + 10) << 2, G_TX_RENDERTILE,
                        0, 0, 1625, 1625);

    *gfxp = gfx;
}

#define MAJORA_MASK_TEX_CENTER_X
#define MAJORAS_MASK_TEX_CENTER_Y
#define ZELDA_TEX_CENTER_X
#define ZELDA_TEX_CENTER_Y

// EnMag_DrawInner
/**
 * Loads title, PRESS START text, etc. graphics into the displaylist array specified by gfxp, which lives on
 * POLY_OPA_DISP, but is used by OVERLAY_DISP.
 */
void func_8096D74C(Actor* thisx, GlobalContext* globalCtx, Gfx** gfxp) {
    // PRESS START character indices
    static u8 pressStartFontIndices[] = { 0x19, 0x1B, 0x0E, 0x1C, 0x1C, 0x1C, 0x1D, 0x0A, 0x1B, 0x1D };
    static TexturePtr D_8096E970[] = { 0x600CF40, 0x600D740, 0x600EF40, 0x600DF40, 0x600E740, 0x600F740 };
    static TexturePtr D_8096E988[] = { 0x6009F40, 0x600A740, 0x600BF40, 0x600AF40, 0x600B740, 0x600C740 };
    static TexturePtr D_8096E9A0[] = {
        gTitleScreenFlame0Tex, gTitleScreenFlame1Tex, gTitleScreenFlame1Tex,
        gTitleScreenFlame2Tex, gTitleScreenFlame3Tex, gTitleScreenFlame3Tex,
    };
    static s16 D_8096E9B8[] = { -1, 1, 1, -1, 1, 1 };
    static s16 D_8096E9C4[] = { -2, -2, -2, 2, 2, 2 };
    static s16 D_8096E9D0 = 0;
    static s16 D_8096E9D4[] = { 0xFF, 0, 0, 0, 0, 0 };
    s32 pad;
    EnMag* this = THIS;
    Font* font = &this->font;
    Gfx* gfx = *gfxp;
    u16 i;
    u16 j;
    u16 k;
    s32 phi_s2;
    s32 sp1B8;
    s16 temp_lo;

    // Set segment 6 to the object, since this will be read by OVERLAY_DISP which does not have that set.
    gSPSegment(gfx++, 0x06, globalCtx->objectCtx.status[this->actor.objBankIndex].segment);

    func_8012C680(&gfx);

    gDPPipeSync(gfx++);
    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(gfx++, 0, this->unk11F06, this->unk11F08[0], this->unk11F08[1], this->unk11F08[2], this->unk11F14);
    gDPSetEnvColor(gfx++, this->unk11F0E[0], this->unk11F0E[1], this->unk11F0E[2], 255);

    // Glowy effects behind Mask
    if (this->unk11F06 != 0) { // majorasMaskEffectPrimLodFrac
        for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
            for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
                this->unk11F36[k] += D_8096E9B8[k];
                this->unk11F44[k] += D_8096E9C4[k];
                EnMag_DrawEffectTextures(&gfx, D_8096E970[k], D_8096E9A0[k], 64, 64, 32, 32, phi_s2, sp1B8, 1, 1, k,
                                         this);
            }
        }
    }

    func_8012C680(&gfx);

    if (this->unk11F26 != 0) { // majorasMaskAlpha
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);

        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->unk11F26);
        gDPSetEnvColor(gfx++, this->unk11F28[0], this->unk11F28[1], this->unk11F28[2], 255);

        EnMag_DrawImageRGBA32(&gfx, 124, 103, gTitleScreenMajorasMaskTex, 128, 112); // Majora's Mask image
    }

    gDPPipeSync(gfx++);

    gDPSetCycleType(gfx++, G_CYC_2CYCLE);
    gDPSetAlphaCompare(gfx++, G_AC_THRESHOLD);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_CLD_SURF2);
    gDPSetCombineLERP(gfx++, TEXEL1, PRIMITIVE, PRIM_LOD_FRAC, TEXEL0, TEXEL1, 1, PRIM_LOD_FRAC, TEXEL0, PRIMITIVE,
                      ENVIRONMENT, COMBINED, ENVIRONMENT, COMBINED, 0, PRIMITIVE, 0);

    gDPSetPrimColor(gfx++, 0, this->unk11F16, this->unk11F18[0], this->unk11F18[1], this->unk11F18[2], this->unk11F24);
    gDPSetEnvColor(gfx++, this->unk11F1E[0], this->unk11F1E[1], this->unk11F1E[2], 255);

    // Glowy effects behind "ZELDA"
    if (this->unk11F16 != 0) {
        for (k = 0, i = 0, sp1B8 = 38; i < 2; i++, sp1B8 += 64) {
            for (j = 0, phi_s2 = 57; j < 3; j++, k++, phi_s2 += 64) {
                EnMag_DrawEffectTextures(&gfx, D_8096E988[k], D_8096E9A0[k], 64, 64, 32, 32, phi_s2, sp1B8, 1, 1, k,
                                         this);
            }
        }
    }

    if (this->subtitleAlpha != 0) {
        func_8012C680(&gfx);

        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

        if (this->mainTitleAlpha < 100) {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, this->subtitleAlpha);
        gDPSetEnvColor(gfx++, 100, 0, 100, 255);

        EnMag_DrawTextureI8(&gfx, gTitleScreenMajorasMaskSubtitleMaskTex, 104, 16, 151, 124);
    }

    func_8012C680(&gfx);

    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (this->mainTitleAlpha < 100) {
        gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
    } else {
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
    }

    gDPSetPrimColor(gfx++, 0, 120, 208, 102, 222, this->subtitleAlpha);

    EnMag_DrawTextureI8(&gfx, gTitleScreenMajorasMaskSubtitleTex, 104, 16, 151, 124); // Subtitle

    func_8012C680(&gfx);

    gDPSetAlphaCompare(gfx++, G_AC_NONE);
    gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

    if (this->mainTitleAlpha != 0) { // zeldaAlpha
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, this->mainTitleAlpha);

        EnMag_DrawImageRGBA32(&gfx, 177, 105, gTitleScreenZeldaLogoTex, 144, 64); // ZELDA

        gDPPipeSync(gfx++);

        if (this->mainTitleAlpha < 100) {
            gDPSetRenderMode(gfx++, G_RM_CLD_SURF, G_RM_CLD_SURF2);
        } else {
            gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);
        }

        gDPSetPrimColor(gfx++, 0, 0, 208, 102, 222, this->mainTitleAlpha);

        EnMag_DrawTextureI8(&gfx, gTitleScreenTheLegendOfTextTex, 72, 8, 158, 71); // "The Legend of"
    }

    func_8012C680(&gfx);

    if (this->copyrightAlpha != 0) { // copyrightAlpha
        gDPSetAlphaCompare(gfx++, G_AC_NONE);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetPrimColor(gfx++, 0, 0, this->copyrightAlpha, this->copyrightAlpha, this->copyrightAlpha,
                        this->copyrightAlpha);

        EnMag_DrawTextureIA8(&gfx, gTitleScreenCopyright2000NintendoTex, 128, 16, 94, 198); // Copyright
    }

    if (gSaveContext.fileNum == 0xFEDC) {
        // Draw No controller message
        temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
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
        gDPLoadTextureBlock_4b(gfx++, gTitleScreenControllerNotConnectedTextTex, G_IM_FMT_I, 256, 9, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
        // Texture shadow
        gSPTextureRectangle(gfx++, 36 << 2, 176 << 2, (36 + 256) << 2, (176 + 9) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);

        // Actual texture
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, D_8096E9D0);
        gSPTextureRectangle(gfx++, 35 << 2, 175 << 2, (35 + 256) << 2, (175 + 9) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);

        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_8096E9D0);
        gDPLoadTextureBlock_4b(gfx++, gTitleScreenInsertControllerTextTex, G_IM_FMT_I, 144, 9, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
        // Texture shadow
        gSPTextureRectangle(gfx++, 92 << 2, 189 << 2, (92 + 144) << 2, (189 + 9) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);

        // Actual texture
        gDPSetPrimColor(gfx++, 0, 0, 205, 255, 255, D_8096E9D0);
        gSPTextureRectangle(gfx++, 91 << 2, 188 << 2, (91 + 144) << 2, (188 + 9) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10,
                            1 << 10);

        D_8096E920--;
        if (D_8096E920 == 0) {
            D_8096E9D0 = D_8096E9D4[D_8096E91C];
            if (gSaveContext.fileNum == 0xFEDC) {
                D_8096E920 = 40;
            } else {
                D_8096E920 = 20;
            }
            D_8096E91C ^= 1;
        }
    } else if (this->copyrightAlpha != 0) {
        // Draw "PRESS START" characters

        temp_lo = ABS_ALT(D_8096E9D0 - D_8096E9D4[D_8096E91C]) / D_8096E920;
        if (D_8096E9D0 >= D_8096E9D4[D_8096E91C]) {
            D_8096E9D0 -= temp_lo;
        } else {
            D_8096E9D0 += temp_lo;
        }

        // Text shadow
        gDPPipeSync(gfx++);
        gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE,
                          0);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, D_8096E9D0);

        phi_s2 = 120;
        for (i = 0; i < 10; i++) {
            EnMag_DrawCharTexture(&gfx, font->fontBuf + pressStartFontIndices[i] * FONT_CHAR_TEX_SIZE, phi_s2, 175);

            phi_s2 += 7;
            if (i == 4) {
                phi_s2 += 5;
            }
        }

        // Actual text
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 255, 30, 30, D_8096E9D0);

        phi_s2 = 120 - 1;
        for (i = 0; i < 10; i++) {
            EnMag_DrawCharTexture(&gfx, font->fontBuf + pressStartFontIndices[i] * FONT_CHAR_TEX_SIZE, phi_s2, 175 - 1);
            phi_s2 += 7;
            if (i == 4) {
                phi_s2 += 5;
            }
        }

        D_8096E920--;
        if (D_8096E920 == 0) {
            D_8096E9D0 = D_8096E9D4[D_8096E91C];
            if (gSaveContext.fileNum == 0xFEDC) {
                D_8096E920 = 40;
            } else {
                D_8096E920 = 20;
            }
            D_8096E91C ^= 1;
        }
    }
    *gfxp = gfx;
}

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
