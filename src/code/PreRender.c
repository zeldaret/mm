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

// #pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170730.asm")
void func_80170730(PreRender* this, Gfx** dList) {
    func_801705EC(this, dList);

    if (this->cvgSave != NULL) {
        func_8017023C(this, dList, this->fbuf, this->cvgSave);
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170774.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170798.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170B28.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170B4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017160C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801716C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801717F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80171F4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80171FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80172078.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801720FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80172758.asm")
