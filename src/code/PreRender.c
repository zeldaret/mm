#include <ultra64.h>
#include <global.h>

void func_8016FCF0(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg) {
    this->widthSave = width;
    this->heightSave = height;
    this->fbufSave = fbuf;
    this->cvgSave = cvg;
    this->zbufSave = zbuf;
    this->ulxSave = 0;
    this->ulySave = 0;
    this->lrxSave = width - 1;
    this->lrySave = height - 1;
}

void func_8016FD2C(PreRender* this) {
    bzero(this, sizeof(PreRender));
    func_80174AA0(&this->alloc);
}

void func_8016FD60(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf) {
    this->width = width;
    this->height = height;
    this->fbuf = fbuf;
    this->zbuf = zbuf;
    this->ulx = 0;
    this->uly = 0;
    this->lrx = width - 1;
    this->lry = height - 1;
}

void func_8016FD94(PreRender* this) {
    func_80174BA0(&this->alloc);
}

void func_8016FDB8(PreRender* this, Gfx** dList, void* srcBuf, void* destBuf, u32 arg4) {
    Gfx* dList2 = *dList;
    u32 flags;

    gDPPipeSync(dList2++);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, destBuf);

    gDPSetScissor(dList2++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    flags = 0x18;
    if (arg4 == true) {
        flags = 0x1C;
    }

    func_80172758(&dList2, srcBuf, NULL, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0.0f, 0.0f, 1.0f,
                  1.0f, flags);
    gDPPipeSync(dList2++);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *dList = dList2;
}

void func_8016FF70(PreRender* this, Gfx** dList, void* srcBuf, void* destBuf) {
    func_8016FDB8(this, dList, srcBuf, destBuf, false);
}

void func_8016FF90(PreRender* this, Gfx** dList, void* srcBuf, void* destBuf, s32 envR, s32 envG, s32 envB, s32 envA) {
    Gfx* dList2 = *dList;

    gDPPipeSync(dList2++);

    if (envA == 255) {
        gDPSetOtherMode(dList2++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    } else {
        gDPSetOtherMode(dList2++,
                        G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2);
    }

    gDPSetEnvColor(dList2++, envR, envG, envB, envA);
    gDPSetCombineLERP(dList2++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0,
                      ENVIRONMENT);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, destBuf);

    gDPSetScissor(dList2++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    func_80172758(&dList2, srcBuf, 0, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0.0f, 0.0f, 1.0f,
                  1.0f, 0xB);
    gDPPipeSync(dList2++);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *dList = dList2;
}

void func_80170200(PreRender* this, Gfx** dList, void* srcBuf, void* destBuf) {
    func_8016FF90(this, dList, srcBuf, destBuf, 255, 255, 255, 255);
}

#ifdef NON_MATCHING
// just regalloc
void func_8017023C(PreRender* this, Gfx** dList, void* srcBuf, void* dstBuf) {
    Gfx* dList2 = *dList;
    s32 x;
    s32 x2;
    s32 dx;

    gDPPipeSync(dList2++);
    gDPSetOtherMode(dList2++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_PASS | G_RM_OPA_CI2);
    gDPSetCombineLERP(dList2++, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0);
    gDPSetColorImage(dList2++, G_IM_FMT_I, G_IM_SIZ_8b, this->width, dstBuf);
    gDPSetScissor(dList2++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    dx = 0x1000 / (this->width * 2);
    x = this->height;
    x2 = 0;

    while (x > 0) {
        s32 uls = 0;
        s32 lrs = this->width - 1;
        s32 ult;
        s32 lrt;

        dx = CLAMP_MAX(dx, x);
        ult = x2;
        lrt = x2 + dx - 1;

        gDPLoadTextureTile(dList2++, srcBuf, G_IM_FMT_IA, G_IM_SIZ_16b, this->width, this->height, uls, ult, lrs, lrt,
                           0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                           G_TX_NOLOD, G_TX_NOLOD);

        gSPTextureRectangle(dList2++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                            ult << 5, 1 << 10, 1 << 10);

        x2 += dx;
        x -= dx;
    }

    gDPPipeSync(dList2++);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *dList = dList2;
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017023C.asm")
#endif

void func_8017057C(PreRender* this, Gfx** dList) {
    if ((this->zbufSave != NULL) && (this->zbuf != NULL)) {
        func_8016FF70(this, dList, this->zbuf, this->zbufSave);
    }
}

void func_801705B4(PreRender* this, Gfx** dList) {
    if ((this->fbufSave != NULL) && (this->fbuf != NULL)) {
        func_80170200(this, dList, this->fbuf, this->fbufSave);
    }
}

void func_801705EC(PreRender* this, Gfx** dList) {
    Gfx* dList2 = *dList;

    gDPPipeSync(dList2++);
    gDPSetBlendColor(dList2++, 255, 255, 255, 8);
    gDPSetPrimDepth(dList2++, -1, -1);
    gDPSetOtherMode(dList2++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_VISCVG | G_RM_VISCVG2);
    gDPSetScissor(dList2++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);
    gDPFillRectangle(dList2++, 0, 0, this->width, this->height);
    gDPPipeSync(dList2++);

    *dList = dList2;
}

void func_80170730(PreRender* this, Gfx** dList) {
    func_801705EC(this, dList);

    if (this->cvgSave != NULL) {
        func_8017023C(this, dList, this->fbuf, this->cvgSave);
    }
}

void func_80170774(PreRender* this, Gfx** dList) {
    func_8016FF70(this, dList, this->zbufSave, this->zbuf);
}

#ifdef NON_MATCHING
// just regalloc
void func_80170798(PreRender* this, Gfx** dList) {
    Gfx* gfx;
    s32 y;
    s32 y2;
    s32 dy;
    s32 rtile = 1;

    if (this->cvgSave != NULL) {
        gfx = *dList;

        gDPPipeSync(gfx++);
        gDPSetEnvColor(gfx++, 255, 255, 255, 32);
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA |
                            GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1) |
                            GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1));
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 1, 0, TEXEL1, ENVIRONMENT, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

        dy = (this->width > 320) ? 2 : 4;
        y = this->height;
        y2 = 0;

        while (y > 0) {
            s32 uls = 0;
            s32 lrs = this->width - 1;
            s32 ult;
            s32 lrt;

            dy = CLAMP_MAX(dy, y);

            ult = y2;
            lrt = (y2 + dy - 1);

            gDPLoadMultiTile(gfx++, this->fbufSave, 0x0000, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width,
                             this->height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                             G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            if (1) {}
            gDPLoadMultiTile(gfx++, this->cvgSave, 0x0160, rtile, G_IM_FMT_I, G_IM_SIZ_8b, this->width, this->height,
                             uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                             G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            if (1) {}
            gSPTextureRectangle(gfx++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                                ult << 5, 1 << 10, 1 << 10);

            y2 += dy;
            y -= dy;
        }

        gDPPipeSync(gfx++);
        *dList = gfx;
    }
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170798.asm")
#endif

void func_80170AE0(PreRender* this, Gfx** dList, s32 alpha) {
    func_8016FF90(this, dList, this->fbufSave, this->fbuf, 255, 255, 255, alpha);
}

void func_80170B28(PreRender* this, Gfx** dList) {
    func_8016FF70(this, dList, this->fbufSave, this->fbuf);
}

void func_80170B4C(PreRender* this, s32 x, s32 y) {
    s32 i;
    s32 j;
    s32 buffA[3 * 5];
    s32 buffR[3 * 5];
    s32 buffG[3 * 5];
    s32 buffB[3 * 5];
    s32 x1;
    s32 y1;
    s32 pad;
    s32 pxR;
    s32 pxG;
    s32 pxB;
    s32 pxR2;
    s32 pxG2;
    s32 pxB2;
    Color_RGB5A1 pxIn;
    Color_RGB5A1 pxOut;
    u32 pxR3;
    u32 pxG3;
    u32 pxB3;

    /*
    Picture this as a 3x5 rectangle where the middle pixel (index 7) correspond to (x, y)
      _ _ _ _ _
    | 0 1 2 3 4 |
    | 5 6 7 8 9 |
    | A B C D E |
      ‾ ‾ ‾ ‾ ‾
    */
    for (i = 0; i < 3 * 5; i++) {
        x1 = (i % 5) + x - 2;
        y1 = (i / 5) + y - 1;

        if (x1 < 0) {
            x1 = 0;
        } else if (x1 > (this->width - 1)) {
            x1 = this->width - 1;
        }
        if (y1 < 0) {
            y1 = 0;
        } else if (y1 > (this->height - 1)) {
            y1 = this->height - 1;
        }

        pxIn.rgba = this->fbufSave[x1 + y1 * this->width];
        buffR[i] = (pxIn.r << 3) | (pxIn.r >> 2);
        buffG[i] = (pxIn.g << 3) | (pxIn.g >> 2);
        buffB[i] = (pxIn.b << 3) | (pxIn.b >> 2);
        buffA[i] = this->cvgSave[x1 + y1 * this->width] >> 5; // A
    }

    pxR = pxR2 = buffR[7];
    pxG = pxG2 = buffG[7];
    pxB = pxB2 = buffB[7];

    for (i = 1; i < 3 * 5; i += 2) {
        if (buffA[i] == 7) {
            if (pxR < buffR[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffR[j] >= buffR[i]) && (buffA[j] == 7)) {
                        pxR = buffR[i];
                    }
                }
            }
            if (pxG < buffG[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffG[j] >= buffG[i]) && (buffA[j] == 7)) {
                        pxG = buffG[i];
                    }
                }
            }
            if (pxB < buffB[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffB[j] >= buffB[i]) && (buffA[j] == 7)) {
                        pxB = buffB[i];
                    }
                }
            }
            if (1) {}
            if (pxR2 > buffR[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffR[j] <= buffR[i]) && (buffA[j] == 7)) {
                        pxR2 = buffR[i];
                    }
                }
            }
            if (pxG2 > buffG[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffG[j] <= buffG[i]) && (buffA[j] == 7)) {
                        pxG2 = buffG[i];
                    }
                }
            }
            if (pxB2 > buffB[i]) {
                for (j = 1; j < 15; j += 2) {
                    if ((i != j) && (buffB[j] <= buffB[i]) && (buffA[j] == 7)) {
                        pxB2 = buffB[i];
                    }
                }
            }
        }
    }

    pad = 7 - buffA[7];
    pxR3 = buffR[7] + (((s32)((pad * ((pxR + pxR2) - (buffR[7] << 1))) + 4)) >> 3);
    pxG3 = buffG[7] + (((s32)((pad * ((pxG + pxG2) - (buffG[7] << 1))) + 4)) >> 3);
    pxB3 = buffB[7] + (((s32)((pad * ((pxB + pxB2) - (buffB[7] << 1))) + 4)) >> 3);

    pxOut.r = pxR3 >> 3;
    pxOut.g = pxG3 >> 3;
    pxOut.b = pxB3 >> 3;
    pxOut.a = 1;
    this->fbufSave[x + y * this->width] = pxOut.rgba;
}

void func_8017160C(PreRender* this) {
    s32 x;
    s32 y;
    s32 cvg;

    for (y = 0; y < this->height; y++) {
        for (x = 0; x < this->width; x++) {
            cvg = this->cvgSave[x + y * this->width];
            cvg >>= 5;
            cvg++;

            if (cvg != 8) {
                func_80170B4C(this, x, y);
            }
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801716C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801717F8.asm")

void func_80171F4C(PreRender* this) {
    if (this->cvgSave == NULL || this->fbufSave == NULL) {
        this->unk_4D = 0;
    } else {
        this->unk_4D = 1;
        func_8017160C(this);
        func_801717F8(this);
        this->unk_4D = 2;
    }
}

void func_80171FA8(PreRender* this) {
    if ((this->cvgSave != NULL) && (this->fbufSave != NULL)) {
        if (D_801F6FC0) {
            StackCheck_Cleanup(&slowlyStackEntry);
            func_801857A0(&D_801F6E00);
        }

        this->unk_4D = 1;
        StackCheck_Init(&slowlyStackEntry, slowlyStack, &slowlyStack[4096], 0, 0x100, D_801DFC60);
        Slowly_Start(&D_801F6E00, &D_801F7FE8, func_80171F4C, this, 0);
        D_801F6FC0 = true;
    }
}

void func_80172078(PreRender *this) {
    if (D_801F6FC0) {
        StackCheck_Cleanup(&slowlyStackEntry);
        func_801857A0(&D_801F6E00);
        D_801F6FC0 = false;
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80172758.asm")
