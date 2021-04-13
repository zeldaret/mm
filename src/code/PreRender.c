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

    func_80172758(&dList2, srcBuf, NULL, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, flags);
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

    func_80172758(&dList2, srcBuf, 0, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, 0, 0, 0.0f, 0.0f, 1.0f, 1.0f, 0xB);
    gDPPipeSync(dList2++);
    gDPSetColorImage(dList2++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *dList = dList2;
}

void func_80170200(PreRender* this, Gfx** dList, void* srcBuf, void* destBuf) {
    func_8016FF90(this, dList, srcBuf, destBuf, 255, 255, 255, 255);
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017023C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_8017057C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801705B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_801705EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/PreRender/func_80170730.asm")

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
