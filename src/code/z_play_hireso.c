#include "global.h"

// Segment 0x07 schedule_dma_static_test
// Segment 0x08 schedule_static
extern TexturePtr D_08001340;
extern TexturePtr D_080013D8;
extern TexturePtr D_080017D8;
extern TexturePtr D_08001F70;

extern u16 D_801D0D80[][30];
extern TexturePtr D_801D1238[];
extern Color_RGB16 D_801D1330[];
extern s16 D_801D1344[][6];
extern u16 D_801D146C[];

void func_8016AC10(Gfx** gfxP, s32 rxl, s32 ryl, s32 rxh, s32 ryh, s32 tile, s32 s, s32 t, s32 dsdx, s32 dtdy) {
    s32 xl = rxl - (D_801FBBD0 << 2);
    s32 yl = ryl - (D_801FBBD2 << 2);
    s32 xh = rxh - (D_801FBBD0 << 2);
    s32 yh = ryh - (D_801FBBD2 << 2);
    Gfx* gfx = *gfxP;

    gSPScisTextureRectangle(gfx++, xl, yl, xh, yh, tile, s, t, dsdx, dtdy);

    *gfxP = gfx;
}

#ifdef NON_MATCHING
void func_8016AE1C(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s32 i;
    s32 xl;
    s32 xh;

    gDPLoadTextureBlock(gfx++, &D_080017D8, G_IM_FMT_I, G_IM_SIZ_8b, 8, 24, 0, G_TX_NOMIRROR | G_TX_WRAP,
                        G_TX_NOMIRROR | G_TX_WRAP, 3, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    xl = 263 << 2;
    xh = 120 << 2;
    for (i = 0; i < 2; i++) {
        gDPSetPrimColor(gfx++, 0, 0, D_801D1330[i].r, D_801D1330[i].g, D_801D1330[i].b, 192);
        func_8016AC10(&gfx, xl, 74 << 2, xh, 98 << 2, 0, 0, 0, 0x400, 0x400);
        xl += 150 << 2;
        xh += 150 << 2;
    }

    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

    xl = 124 << 2;
    xh = 172 << 2;
    for (i = 0; i < 3; i++) {
        gDPLoadTextureBlock(gfx++, D_801D1238[i], G_IM_FMT_IA, G_IM_SIZ_8b, 48, 22, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        func_8016AC10(&gfx, xl, 77 << 2, xh, 99 << 2, 0, 0, 0, 0x400, 0x400);
        xl += 150 << 2;
        xh += 150 << 2;
    }

    gDPLoadTextureBlock_4b(gfx++, &D_08001F70, G_IM_FMT_IA, 48, 11, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    xl = 172 << 2;
    xh = xl + (48 << 2);
    for (i = 0; i < 3; i++) {
        func_8016AC10(&gfx, xl, 86 << 2, xh, 97 << 2, 0, 0, 0, 0x400, 0x400);
        xh += 150 << 2;
        xl += 150 << 2;
    }

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}
#else
void func_8016AE1C(Gfx**);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016AE1C.s")
#endif

void func_8016B278(Gfx** gfxP) {
    Gfx* gfx = *gfxP;
    s16* color;
    s32 i;
    s32 j;
    s32 k;
    s32 tmp;
    s32 xl;
    s32 yl;
    s32 xh;
    s32 yh;

    gDPLoadTextureBlock_4b(gfx++, &D_08001340, G_IM_FMT_I, 48, 1, 0, G_TX_NOMIRROR | G_TX_WRAP,
                           G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

    color = D_801D1344[0];
    for (i = 0, tmp = 120; i < 3; tmp += 150, i++) {
        xl = tmp << 2;
        yl = 104 << 2;
        xh = xl + (48 << 2);
        yh = 480 << 2;
        for (j = 0; j < 2; j++) {
            gDPSetPrimColor(gfx++, 0, 0, color[0], color[1], color[2], 192);
            for (k = 0; k < 2; k++) {
                func_8016AC10(&gfx, xl, yl, xh, yh, 0, 0, 0, 0x400, 0x400);
                xl += 36 << 2;
                xh += 36 << 2;
            }
            color += 3;
        }
    }
    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

void func_8016B4B0(Gfx** gfxP, s32 arg0, s32 arg1);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016B4B0.s")

void func_8016C344(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016C344.s")

void func_8016CD4C(Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016CD4C.s")

void func_8016E40C(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016E40C.s")

void func_8016EA90(BombersNotebook* this, Gfx** gfxP);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/func_8016EA90.s")

void BombersNotebook_Draw(BombersNotebook* this, GraphicsContext* gfxCtx) {
    Gfx* gfx;
    s32 pad[2];

    func_8012CF0C(gfxCtx, this->unk_00 != 2, false, 0, 0, 0);

    OPEN_DISPS(gfxCtx);

    gfx = POLY_OPA_DISP;

    if (this->unk_00 == 2) {
        gSPSegment(gfx++, 0x07, this->unk_40);
        gSPSegment(gfx++, 0x08, this->unk_88);
        gfx = func_8012C600(gfx);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0, PRIMITIVE,
                          ENVIRONMENT, TEXEL0, ENVIRONMENT, TEXEL0, 0, PRIMITIVE, 0);
        gDPSetRenderMode(gfx++, G_RM_OPA_SURF, G_RM_OPA_SURF2);
        gDPSetPrimColor(gfx++, 0, 0, 255, 255, 215, 255);
        gDPSetEnvColor(gfx++, 100, 100, 100, 255);
        gDPLoadTextureBlock(gfx++, &D_080013D8, G_IM_FMT_I, G_IM_SIZ_8b, 32, 32, 0, G_TX_NOMIRROR | G_TX_WRAP,
                            G_TX_NOMIRROR | G_TX_WRAP, 5, 5, G_TX_NOLOD, G_TX_NOLOD);

        func_8016AC10(&gfx, 0, 0, 0xA00, 0x780, 0, 0, 0, 0x200, 0x200);

        gDPPipeSync(gfx++);
        gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
        gDPSetRenderMode(gfx++, G_RM_XLU_SURF, G_RM_XLU_SURF2);

        func_8016AE1C(&gfx);
        func_8016B278(&gfx);

        gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 86, 600, 450);
        func_8016C344(this, &gfx);

        gDPPipeSync(gfx++);
        gSPDisplayList(gfx++, D_0E000000.setScissor);

        func_8016CD4C(&gfx);

        if (this->unk_A4 == 0) {
            func_8016E40C(this, &gfx);
        }
        func_8016EA90(this, &gfx);
    }
    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(gfxCtx);
}

void func_8016F4EC(BombersNotebook* this, s32 flag) {
    switch (this->unk_00) {
        case 0:
            if (this->unk_40 == NULL) {
                break;
            }
            CmpDma_LoadAllFiles(this->unk_44, this->unk_40, this->unk_48);
            osCreateMesgQueue(&this->unk_6C, this->unk_84, ARRAY_COUNT(this->unk_84));
            DmaMgr_SendRequestImpl(&this->unk_4C, this->unk_88, this->unk_8C, this->unk_90, 0, &this->unk_6C, NULL);
            this->unk_00 = 1;
            // fall-through
        case 1:
            if (osRecvMesg(&this->unk_6C, NULL, flag) == 0) {
                this->unk_00 = 2;
            }
    }
}

#ifdef NON_MATCHING
void BombersNotebook_Update(PlayState* play, BombersNotebook* this, Input* input) {
    static s16 D_801D14DC = 0;
    static s16 D_801D14E0 = 0;
    static s16 D_801D14E4 = 0;
    static s16 D_801D14E8 = 0;
    s32 sp2C = input->rel.stick_x;
    s32 sp28 = input->rel.stick_y;
    s32 sp24;

    this->unk_44 = SEGMENT_ROM_START(schedule_dma_static_test);
    this->unk_48 = SEGMENT_ROM_SIZE(schedule_dma_static_old);
    this->unk_8C = SEGMENT_ROM_START(schedule_static);
    this->unk_90 = SEGMENT_ROM_SIZE(schedule_static);

    if (this->unk_40 == NULL) {
        this->unk_40 = ZeldaArena_Malloc(this->unk_48);
    }

    if (this->unk_88 == NULL) {
        this->unk_88 = ZeldaArena_Malloc(this->unk_90);
    }

    func_8016F4EC(this, 0);

    if (this->unk_00 == 2) {
        if (sp2C < -30) {
            if (D_801D14E4 == -1) {
                D_801D14DC--;
                if (D_801D14DC < 0) {
                    D_801D14DC = 2;
                } else {
                    sp2C = 0;
                }
            } else {
                D_801D14DC = 10;
                D_801D14E4 = -1;
            }
        } else if (sp2C > 30) {
            if (D_801D14E4 == 1) {
                D_801D14DC--;
                if (D_801D14DC < 0) {
                    D_801D14DC = 2;
                } else {
                    sp2C = 0;
                }
            } else {
                D_801D14DC = 10;
                D_801D14E4 = 1;
            }
        } else {
            D_801D14E4 = 0;
        }

        if (sp28 < -30) {
            if (D_801D14E8 == -1) {
                D_801D14E0--;
                if (D_801D14E0 < 0) {
                    D_801D14E0 = 2;
                } else {
                    sp28 = 0;
                }
            } else {
                D_801D14E0 = 10;
                D_801D14E8 = -1;
            }
        } else if (sp28 > 30) {
            if (D_801D14E8 == 1) {
                D_801D14E0--;
                if (D_801D14E0 < 0) {
                    D_801D14E0 = 2;
                } else {
                    sp28 = 0;
                }
            } else {
                D_801D14E0 = 10;
                D_801D14E8 = 1;
            }
        } else {
            D_801D14E8 = 0;
        }
        if (this->unk_A4 == 0) {
            if (CHECK_WEEKEVENTREG(D_801C6B28[this->unk_94 + this->unk_9C])) {
                sp24 = this->unk_98;
                if (sp2C > 30) {
                    while (true) {
                        sp24 += 3;
                        if (D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] == 0x9999) {
                            while (true) {
                                sp24 -= 3;
                                if (sp24 == 0) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                                if (CHECK_WEEKEVENTREG(
                                        D_801C6B28[D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] & 0xFF])) {
                                    play_sound(NA_SE_SY_ERROR);
                                    break;
                                }
                            }
                            break;
                        }
                        if (CHECK_WEEKEVENTREG(D_801C6B28[D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] & 0xFF])) {
                            play_sound(NA_SE_SY_CURSOR);
                            break;
                        }
                    }
                } else if (sp2C < -30) {
                    while (sp24 != 0) {
                        sp24 -= 3;
                        if (CHECK_WEEKEVENTREG(D_801C6B28[D_801D0D80[this->unk_94 + this->unk_9C][sp24 - 3] & 0xFF])) {
                            play_sound(NA_SE_SY_CURSOR);
                            break;
                        }
                    }
                }
                this->unk_98 = sp24;
                if (this->unk_98 != 0) {
                    if (play->msgCtx.currentTextId !=
                        D_801D146C[D_801D0D80[this->unk_94 + this->unk_9C][this->unk_98 - 3] & 0xFF]) {
                        Message_ContinueTextbox(play,
                                      D_801D146C[D_801D0D80[this->unk_94 + this->unk_9C][this->unk_98 - 3] & 0xFF]);
                    }
                } else {
                    if (play->msgCtx.currentTextId != D_801D146C[this->unk_94 + this->unk_9C]) {
                        Message_ContinueTextbox(play, D_801D146C[this->unk_94 + this->unk_9C]);
                    }
                }
            } else {
                Message_CloseTextbox(play);
            }

            if (sp28 < -30) {
                if (this->unk_94 < 3) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_98 = 0;
                    this->unk_94++;
                } else if (this->unk_9C < 0x10) {
                    if (D_801D14E8 == -1) {
                        this->unk_A4 = -0x18;
                    } else {
                        this->unk_A4 = -0xC;
                    }
                    this->unk_A8 = 0;
                    this->unk_98 = 0;
                }
            } else if (sp28 > 30) {
                if (this->unk_94 > 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_98 = 0;
                    this->unk_94--;
                } else if (this->unk_9C != 0) {
                    play_sound(NA_SE_SY_CURSOR);
                    this->unk_9C--;
                    if (D_801D14E8 == 1) {
                        this->unk_A4 = 0x18;
                    } else {
                        this->unk_A4 = 0xC;
                    }
                    this->unk_A8 = -0x30;
                    this->unk_98 = 0;
                }
            }
        } else if (this->unk_A4 < 0) {
            this->unk_A8 += this->unk_A4;
            if (ABS_ALT(this->unk_A8) >= 0x30) {
                play_sound(NA_SE_SY_CURSOR);
                this->unk_A8 = 0;
                this->unk_A4 = 0;
                this->unk_9C++;
            }
        } else {
            this->unk_A8 += this->unk_A4;
            if (this->unk_A8 == 0) {
                this->unk_A8 = 0;
                this->unk_A4 = 0;
            }
        }
    }
}
#else
void BombersNotebook_Update(PlayState* play, BombersNotebook* this, Input* input);
#pragma GLOBAL_ASM("asm/non_matchings/code/z_play_hireso/BombersNotebook_Update.s")
#endif

void BombersNotebook_Init(BombersNotebook* this) {
    bzero(this, sizeof(BombersNotebook));
}

void BombersNotebook_Destroy(BombersNotebook* this) {
    if (this->unk_00 == 1) {
        func_8016F4EC(this, true);
    }
    if (this->unk_40 != NULL) {
        ZeldaArena_Free(this->unk_40);
        this->unk_40 = NULL;
    }
}
