/*
 * File: z_file_choose_80807940.c
 * Overlay: ovl_file_choose
 * Description:
 */

#include "z_file_choose.h"
#include "z64rumble.h"

extern UNK_TYPE D_01002800;
extern UNK_TYPE D_01007980;
extern UNK_TYPE D_0102A6B0;
extern UNK_TYPE D_0102B170;
extern UNK_TYPE D_010310F0;
extern UNK_TYPE D_010311F0;

// there are uses of D_0E000000.fillRect (appearing as D_0E0002E0) in this file
extern GfxMasterList D_0E000000;

extern s16 D_80814304[];
extern s16 D_80814404[];
extern s16 D_80814410[];
extern s16 D_8081441C[];

s32 D_80813DF0[] = {
    0xFFA20048, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00220048, 0x00000000, 0x10000000, 0xFFFFFFFF, 0xFFA20038,
    0x00000000, 0x00000200, 0xFFFFFFFF, 0x00220038, 0x00000000, 0x10000200, 0xFFFFFFFF, 0xFF9C002C, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0xFFDC002C, 0x00000000, 0x08000000, 0xFFFFFFFF, 0xFF9C001C, 0x00000000, 0x00000200,
    0xFFFFFFFF, 0xFFDC001C, 0x00000000, 0x08000200, 0xFFFFFFFF, 0xFF9C0004, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0xFFDC0004, 0x00000000, 0x08000000, 0xFFFFFFFF, 0xFF9CFFF4, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFDCFFF4,
    0x00000000, 0x08000200, 0xFFFFFFFF, 0xFF9CFFDC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFFCFFDC, 0x00000000,
    0x0C000000, 0xFFFFFFFF, 0xFF9CFFCC, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFFCFFCC, 0x00000000, 0x0C000200,
    0xFFFFFFFF, 0x00390009, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x00690009, 0x00000000, 0x06000000, 0xFFFFFFFF,
    0x0039FFF8, 0x00000000, 0x00000220, 0xFFFFFFFF, 0x0069FFF8, 0x00000000, 0x06000220, 0xFFFFFFFF,
};

s32 D_80813F30[] = {
    0xFF9C001A, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFCC001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFF9C000A,
    0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFCC000A, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFFD0001A, 0x00000000,
    0x00000000, 0xFFFFFFFF, 0x0000001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFFD0000A, 0x00000000, 0x00000200,
    0xFFFFFFFF, 0x0000000A, 0x00000000, 0x06000200, 0xFFFFFFFF, 0x0004001A, 0x00000000, 0x00000000, 0xFFFFFFFF,
    0x0034001A, 0x00000000, 0x06000000, 0xFFFFFFFF, 0x0004000A, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x0034000A,
    0x00000000, 0x06000200, 0xFFFFFFFF, 0x0038001A, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x0068001A, 0x00000000,
    0x06000000, 0xFFFFFFFF, 0x0038000A, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x0068000A, 0x00000000, 0x06000200,
    0xFFFFFFFF, 0xFF9CFFF2, 0x00000000, 0x00000000, 0xFFFFFFFF, 0xFFCCFFF2, 0x00000000, 0x06000000, 0xFFFFFFFF,
    0xFF9CFFE2, 0x00000000, 0x00000200, 0xFFFFFFFF, 0xFFCCFFE2, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFFD0FFF2,
    0x00000000, 0x00000000, 0xFFFFFFFF, 0x0000FFF2, 0x00000000, 0x06000000, 0xFFFFFFFF, 0xFFD0FFE2, 0x00000000,
    0x00000200, 0xFFFFFFFF, 0x0000FFE2, 0x00000000, 0x06000200, 0xFFFFFFFF, 0xFF9CFFCA, 0x00000000, 0x00000000,
    0xFFFFFFFF, 0xFFFCFFCA, 0x00000000, 0x0C000000, 0xFFFFFFFF, 0xFF9CFFBA, 0x00000000, 0x00000200, 0xFFFFFFFF,
    0xFFFCFFBA, 0x00000000, 0x0C000200, 0xFFFFFFFF, 0xFFFCFFCA, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x005CFFCA,
    0x00000000, 0x0C000000, 0xFFFFFFFF, 0xFFFCFFBA, 0x00000000, 0x00000200, 0xFFFFFFFF, 0x005CFFBA, 0x00000000,
    0x0C000200, 0xFFFFFFFF,
};

s32 D_80814130[] = {
    0xFF9C001C, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009C001C, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9C001A, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009C001A, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

s32 D_80814170[] = {
    0xFF9CFFF4, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009CFFF4, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9CFFF2, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009CFFF2, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

s32 D_808141B0[] = {
    0xFF9CFFCC, 0x00000000, 0x00000000, 0xFFFFFFFF, 0x009CFFCC, 0x00000000, 0x20000000, 0xFFFFFFFF,
    0xFF9CFFCA, 0x00000000, 0x00000040, 0xFFFFFFFF, 0x009CFFCA, 0x00000000, 0x20000040, 0xFFFFFFFF,
};

u8 D_808141F0[] = {
    0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19,
    0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29,
    0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    0x3A, 0x3B, 0x3C, 0x3D, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x00, 0x40, 0x3F,
    0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

s16 sChooseFileYOffsets[] = { -48, -48, -48, -24, -24, 0 };

s16 D_8081424C[3][3] = {
    { 0x0000, 0xFFD0, 0xFFD0 },
    { 0xFFC0, 0x0010, 0xFFD0 },
    { 0xFFC0, 0xFFC0, 0x0020 },
};

s16 sEraseDelayTimer = 0xF;

s16 D_80814264[] = { -56, -40, -24, 0 };

s16 D_8081426C[] = { 0, 16, 32 };

s32 D_80814274[] = { 0x00000000, 0x00000000, 0x00000000 };

void FileSelect_DrawTexQuadI4(GraphicsContext* gfxCtx, TexturePtr texture, s16 vtx) {
    OPEN_DISPS(gfxCtx);

    gDPLoadTextureBlock_4b(POLY_OPA_DISP++, texture, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_CLAMP,
                           G_TX_NOMIRROR | G_TX_CLAMP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);

    CLOSE_DISPS(gfxCtx);
}

void FileSelect_DrawMultiTexQuadI4(GraphicsContext* gfxCtx, TexturePtr texture1, TexturePtr texture2, s16 vtx) {
    OPEN_DISPS(gfxCtx);

    gDPLoadTextureBlock_4b(POLY_OPA_DISP++, texture1, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gDPLoadMultiBlock_4b(POLY_OPA_DISP++, texture2, 0x0080, 1, G_IM_FMT_I, 16, 16, 0, G_TX_NOMIRROR | G_TX_WRAP,
                         G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
    gSP1Quadrangle(POLY_OPA_DISP++, vtx, vtx + 2, vtx + 3, vtx + 1, 0);

    CLOSE_DISPS(gfxCtx);
}

void FileSelect_SetKeyboardVtx(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 phi_t2;
    s16 phi_t0;
    s16 phi_t3;
    s16 phi_s1;
    s16 phi_t1;
    s16 phi_s2;

    this->keyboardVtx = GRAPH_ALLOC(this->state.gfxCtx, sizeof(Vtx) * 4 * 5 * 13);

    phi_s1 = 0x26;

    for (phi_t2 = 0, phi_s2 = 0, phi_t3 = 0; phi_s2 < 5; phi_s2++) {
        phi_t0 = -0x60;

        for (phi_t1 = 0; phi_t1 < 13; phi_t1++, phi_t3 += 4, phi_t2++) {
            //! @bug D_80814304 is accessed out of bounds when drawing the empty space character (value of 64). Under
            //! normal circumstances it reads a halfword from sNameLabelTextures.
            this->keyboardVtx[phi_t3].v.ob[0] = this->keyboardVtx[phi_t3 + 2].v.ob[0] = D_80814304[phi_t2] + phi_t0;

            this->keyboardVtx[phi_t3 + 1].v.ob[0] = this->keyboardVtx[phi_t3 + 3].v.ob[0] =
                D_80814304[phi_t2] + phi_t0 + 12;

            this->keyboardVtx[phi_t3].v.ob[1] = this->keyboardVtx[phi_t3 + 1].v.ob[1] = phi_s1;

            this->keyboardVtx[phi_t3 + 2].v.ob[1] = this->keyboardVtx[phi_t3 + 3].v.ob[1] = phi_s1 - 12;

            this->keyboardVtx[phi_t3].v.ob[2] = this->keyboardVtx[phi_t3 + 1].v.ob[2] =
                this->keyboardVtx[phi_t3 + 2].v.ob[2] = this->keyboardVtx[phi_t3 + 3].v.ob[2] = 0;

            this->keyboardVtx[phi_t3].v.flag = this->keyboardVtx[phi_t3 + 1].v.flag =
                this->keyboardVtx[phi_t3 + 2].v.flag = this->keyboardVtx[phi_t3 + 3].v.flag = 0;

            this->keyboardVtx[phi_t3].v.tc[0] = this->keyboardVtx[phi_t3].v.tc[1] =
                this->keyboardVtx[phi_t3 + 1].v.tc[1] = this->keyboardVtx[phi_t3 + 2].v.tc[0] = 0;

            this->keyboardVtx[phi_t3 + 1].v.tc[0] = this->keyboardVtx[phi_t3 + 2].v.tc[1] =
                this->keyboardVtx[phi_t3 + 3].v.tc[0] = this->keyboardVtx[phi_t3 + 3].v.tc[1] = 0x200;

            this->keyboardVtx[phi_t3].v.cn[0] = this->keyboardVtx[phi_t3 + 1].v.cn[0] =
                this->keyboardVtx[phi_t3 + 2].v.cn[0] = this->keyboardVtx[phi_t3 + 3].v.cn[0] =
                    this->keyboardVtx[phi_t3].v.cn[1] = this->keyboardVtx[phi_t3 + 1].v.cn[1] =
                        this->keyboardVtx[phi_t3 + 2].v.cn[1] = this->keyboardVtx[phi_t3 + 3].v.cn[1] =
                            this->keyboardVtx[phi_t3].v.cn[2] = this->keyboardVtx[phi_t3 + 1].v.cn[2] =
                                this->keyboardVtx[phi_t3 + 2].v.cn[2] = this->keyboardVtx[phi_t3 + 3].v.cn[2] =
                                    this->keyboardVtx[phi_t3].v.cn[3] = this->keyboardVtx[phi_t3 + 1].v.cn[3] =
                                        this->keyboardVtx[phi_t3 + 2].v.cn[3] = this->keyboardVtx[phi_t3 + 3].v.cn[3] =
                                            255;

            phi_t0 += 0x10;
        }

        phi_s1 -= 0x10;
    }

    this->keyboard2Vtx = GRAPH_ALLOC(this->state.gfxCtx, sizeof(Vtx) * 24);

    for (phi_t1 = 0, phi_t3 = 0; phi_t3 < 6; phi_t3++, phi_t1 += 4) {

        this->keyboard2Vtx[phi_t1 + 0].v.ob[0] = this->keyboard2Vtx[phi_t1 + 2].v.ob[0] = D_80814404[phi_t3] + 1;

        this->keyboard2Vtx[phi_t1 + 1].v.ob[0] = this->keyboard2Vtx[phi_t1 + 3].v.ob[0] =
            this->keyboard2Vtx[phi_t1 + 0].v.ob[0] + D_80814410[phi_t3] - 2;

        this->keyboard2Vtx[phi_t1 + 0].v.ob[1] = this->keyboard2Vtx[phi_t1 + 1].v.ob[1] = D_8081441C[phi_t3] - 1;

        this->keyboard2Vtx[phi_t1 + 2].v.ob[1] = this->keyboard2Vtx[phi_t1 + 3].v.ob[1] =
            this->keyboard2Vtx[phi_t1 + 0].v.ob[1] - 0xE;

        this->keyboard2Vtx[phi_t1 + 0].v.ob[2] = this->keyboard2Vtx[phi_t1 + 1].v.ob[2] =
            this->keyboard2Vtx[phi_t1 + 2].v.ob[2] = this->keyboard2Vtx[phi_t1 + 3].v.ob[2] = 0;

        this->keyboard2Vtx[phi_t1 + 0].v.flag = this->keyboard2Vtx[phi_t1 + 1].v.flag =
            this->keyboard2Vtx[phi_t1 + 2].v.flag = this->keyboard2Vtx[phi_t1 + 3].v.flag = 0;

        this->keyboard2Vtx[phi_t1 + 0].v.tc[0] = this->keyboard2Vtx[phi_t1 + 0].v.tc[1] =
            this->keyboard2Vtx[phi_t1 + 1].v.tc[1] = this->keyboard2Vtx[phi_t1 + 2].v.tc[0] = 0;

        this->keyboard2Vtx[phi_t1 + 1].v.tc[0] = this->keyboard2Vtx[phi_t1 + 3].v.tc[0] = D_80814410[phi_t3] << 5;

        this->keyboard2Vtx[phi_t1 + 2].v.tc[1] = this->keyboard2Vtx[phi_t1 + 3].v.tc[1] = 0x200;

        this->keyboard2Vtx[phi_t1 + 0].v.cn[0] = this->keyboard2Vtx[phi_t1 + 1].v.cn[0] =
            this->keyboard2Vtx[phi_t1 + 2].v.cn[0] = this->keyboard2Vtx[phi_t1 + 3].v.cn[0] =
                this->keyboard2Vtx[phi_t1 + 0].v.cn[1] = this->keyboard2Vtx[phi_t1 + 1].v.cn[1] =
                    this->keyboard2Vtx[phi_t1 + 2].v.cn[1] = this->keyboard2Vtx[phi_t1 + 3].v.cn[1] =
                        this->keyboard2Vtx[phi_t1 + 0].v.cn[2] = this->keyboard2Vtx[phi_t1 + 1].v.cn[2] =
                            this->keyboard2Vtx[phi_t1 + 2].v.cn[2] = this->keyboard2Vtx[phi_t1 + 3].v.cn[2] =
                                this->keyboard2Vtx[phi_t1 + 0].v.cn[3] = this->keyboard2Vtx[phi_t1 + 1].v.cn[3] =
                                    this->keyboard2Vtx[phi_t1 + 2].v.cn[3] = this->keyboard2Vtx[phi_t1 + 3].v.cn[3] =
                                        255;
    }
}

/**
 * Set vertices used by all elements of the name entry screen that are NOT the keyboard.
 * This includes the cursor highlight, the name entry plate and characters, and the buttons.
 */
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_SetNameEntryVtx.s")

void FileSelect_DrawKeyboard(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    Font* font = &this->font;
    s16 i;
    s16 tmp;
    s16 vtx;

    OPEN_DISPS(this->state.gfxCtx);

    func_8012C8AC(this->state.gfxCtx);
    gDPSetCycleType(POLY_OPA_DISP++, G_CYC_2CYCLE);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_XLU_SURF2);
    gDPSetCombineLERP(POLY_OPA_DISP++, 0, 0, 0, PRIMITIVE, TEXEL1, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, COMBINED, 0,
                      0, 0, COMBINED);
    gDPSetPrimColor(POLY_OPA_DISP++, 0, this->unk_24514, 255, 255, 255, 255);

    for (i = 0, vtx = 0; vtx < 0x100; vtx += 32) {
        gSPVertex(POLY_OPA_DISP++, &this->keyboardVtx[vtx], 32, 0);

        for (tmp = 0; tmp < 32; i++, tmp += 4) {
            FileSelect_DrawTexQuadI4(this->state.gfxCtx, font->fontBuf + D_808141F0[i] * FONT_CHAR_TEX_SIZE, tmp);
        }
    }

    gSPVertex(POLY_OPA_DISP++, &this->keyboardVtx[0x100], 4, 0);
    FileSelect_DrawTexQuadI4(this->state.gfxCtx, font->fontBuf + D_808141F0[i] * FONT_CHAR_TEX_SIZE, 0);

    CLOSE_DISPS(this->state.gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_DrawNameEntry.s")

/**
 * Fade in the name entry box and slide it to the center of the screen from the right side.
 * After the name entry box is in place, init the keyboard/cursor and change modes.
 * Update function for `CM_START_NAME_ENTRY`
 */
void FileSelect_StartNameEntry(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->kbdX = 0;
        this->kbdY = 0;
        this->kbdButton = 99;
        this->configMode = CM_NAME_ENTRY;
    }
}

/**
 * Update the keyboard cursor and play sound effects at the appropriate times.
 * There are many special cases for warping the cursor depending on where
 * the cursor currently is.
 * Update function for `CM_NAME_ENTRY`
 */
void FileSelect_UpdateKeyboardCursor(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    s16 prevKbdX;

    this->kbdButton = 99;

    if (this->kbdY != 5) {
        if (this->stickAdjX < -30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            this->charIndex--;
            this->kbdX--;
            if (this->kbdX < 0) {
                this->kbdX = 12;
                this->charIndex = (this->kbdY * 13) + this->kbdX;
            }
        } else if (this->stickAdjX > 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            this->charIndex++;
            this->kbdX++;
            if (this->kbdX > 12) {
                this->kbdX = 0;
                this->charIndex = (this->kbdY * 13) + this->kbdX;
            }
        }
    } else {
        if (this->stickAdjX < -30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            this->kbdX--;
            if (this->kbdX < 3) {
                this->kbdX = 4;
            }
        } else if (this->stickAdjX > 30) {
            play_sound(NA_SE_SY_FSEL_CURSOR);
            this->kbdX++;
            if (this->kbdX > 4) {
                this->kbdX = 3;
            }
        }
    }

    if (this->stickAdjY > 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);

        this->kbdY--;

        if (this->kbdY < 0) {
            // dont go to bottom row
            if (this->kbdX < 8) {
                this->kbdY = 4;
                this->charIndex = (s32)(this->kbdX + 52);
            } else {
                this->kbdY = 5;
                this->charIndex += 52;
                prevKbdX = this->kbdX;

                if (this->kbdX < 10) {
                    this->kbdX = 3;
                } else if (this->kbdX < 13) {
                    this->kbdX = 4;
                }
                this->unk_2451E[this->kbdX] = prevKbdX;
            }
        } else {
            this->charIndex -= 13;

            if (this->kbdY == 4) {
                this->charIndex = 52;
                this->kbdX = this->unk_2451E[this->kbdX];
                this->charIndex += this->kbdX;
            }
        }
    } else if (this->stickAdjY < -30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        this->kbdY++;

        if (this->kbdY > 5) {
            this->kbdY = 0;
            this->kbdX = this->unk_2451E[this->kbdX];
            this->charIndex = this->kbdX;
        } else {
            this->charIndex += 13;

            if (this->kbdY == 5) {
                if (this->kbdX < 8) {
                    this->kbdY = 0;
                    this->charIndex = this->kbdX;
                } else {
                    prevKbdX = this->kbdX;

                    if (this->kbdX < 3) {
                        this->kbdX = 0;
                    } else if (this->kbdX < 6) {
                        this->kbdX = 1;
                    } else if (this->kbdX < 8) {
                        this->kbdX = 2;
                    } else if (this->kbdX < 10) {
                        this->kbdX = 3;
                    } else if (this->kbdX < 13) {
                        this->kbdX = 4;
                    }
                    this->unk_2451E[this->kbdX] = prevKbdX;
                }
            }
        }
    }
    if (this->kbdY == 5) {
        this->kbdButton = this->kbdX;
    }
}

void func_8080A3CC(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;

    func_80147068(sramCtx);

    if (sramCtx->status == 0) {
        this->configMode = 0x26;
    }
}

/**
 * This function is mostly a copy paste of `FileSelect_StartNameEntry`.
 * The name entry box fades and slides in even though it is not visible.
 * After this is complete, change to the options config mode.
 * Update function for `CM_START_OPTIONS`
 */
void FileSelect_StartOptions(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;

    this->nameEntryBoxAlpha += 25;

    if (this->nameEntryBoxAlpha >= 255) {
        this->nameEntryBoxAlpha = 255;
    }

    this->nameEntryBoxPosX -= 30;

    if (this->nameEntryBoxPosX <= 0) {
        this->nameEntryBoxPosX = 0;
        this->nameEntryBoxAlpha = 255;
        this->configMode = CM_OPTIONS_MENU;
    }
}

u8 sSelectedSetting;

/**
 * Update the cursor and appropriate settings for the options menu.
 * If the player presses B, write the selected options to the SRAM header
 * and set config mode to rotate back to the main menu.
 * Update function for `CM_OPTIONS_MENU`
 */
void FileSelect_UpdateOptionsMenu(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;
    Input* input = CONTROLLER1(&this->state);

    if (CHECK_BTN_ALL(input->press.button, BTN_B)) {
        play_sound(NA_SE_SY_FSEL_DECIDE_L);
        func_80146DF8(sramCtx);
        if (!gSaveContext.unk_3F3F) {
            this->configMode = 0x2B;
        } else {
            func_80147008(sramCtx, D_801C67E8[0], D_801C6838[0]);
            func_80147020(sramCtx);
            this->configMode = 0x2A;
        }
        func_801A3D98(gSaveContext.options.audioSetting);
        return;
    }

    if (this->stickAdjX < -30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);

        if (sSelectedSetting == 0) {
            gSaveContext.options.audioSetting--;
            if (gSaveContext.options.audioSetting > 0xF0) {
                gSaveContext.options.audioSetting = 3;
            }
        } else {
            gSaveContext.options.zTargetSetting ^= 1;
        }
    } else if (this->stickAdjX > 30) {
        play_sound(NA_SE_SY_FSEL_CURSOR);

        if (sSelectedSetting == 0) {
            gSaveContext.options.audioSetting++;
            if (gSaveContext.options.audioSetting > 3) {
                gSaveContext.options.audioSetting = 0;
            }
        } else {
            gSaveContext.options.zTargetSetting ^= 1;
        }
    }

    if ((this->stickAdjY < -30) || (this->stickAdjY > 30)) {
        play_sound(NA_SE_SY_FSEL_CURSOR);
        sSelectedSetting ^= 1;
        return;
    }
    if (CHECK_BTN_ALL(input->press.button, BTN_A)) {
        play_sound(NA_SE_SY_FSEL_DECIDE_L);
        sSelectedSetting ^= 1;
    }
}

void func_8080A6BC(GameState* thisx) {
    FileSelectState* this = (FileSelectState*)thisx;
    SramContext* sramCtx = &this->sramCtx;

    func_80147068(sramCtx);

    if (sramCtx->status == 0) {
        this->configMode = 0x2B;
    }
}

void FileSelect_DrawOptionsImpl(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_file_choose/FileSelect_DrawOptionsImpl.s")

void FileSelect_DrawOptions(GameState* thisx) {
    FileSelect_DrawOptionsImpl(thisx);
}

// bss padding
s32 D_80814E94;
s32 D_80814E98;
s32 D_80814E9C;
s32 D_80814EA0;
