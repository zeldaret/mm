#include "global.h"

// ucode.h
#define SP_UCODE_DATA_SIZE 0x800

// macros.h
#define CLAMP_ALT(x, min, max) ((x) > (max) ? (max) : (x) < (min) ? (min) : (x))

typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 lodProportion;
    /* 0x0C */ Color_RGBA8_u32 primColor;
    /* 0x10*/ Color_RGBA8_u32 envColor;
} Struct_80140E80; // size = 0x14

// Init
void func_80140E80(Struct_80140E80* this) {
    bzero(this, sizeof(Struct_80140E80));
}

// Destroy
void func_80140EA0(Struct_80140E80* this) {
}

// internal, only used in func_80141008
void func_80140EAC(Gfx** gfxP, uObjBg* bg, void* img, s32 width, s32 height, s32 flag) {
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, img);
    gDPSetScissor(gfx++, 0, 0, 0, width, height);
    gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);

    if (!!(flag & 1) != 0) {
        gSPBgRectCopy(gfx++, bg);
    } else {
        gSPBgRect1Cyc(gfx++, bg);
    }
    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, D_0F000000);
    gSPDisplayList(gfx++, &D_0E000000.setScissor[0]);

    *gfxP = gfx;
}

// internal
void func_80141008(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 frameX, f32 frameY, f32 arg7,
                   f32 arg8, s32 flag) {
    Gfx* gfx;
    Gfx* gfxTemp;
    uObjBg* bg;

    gfxTemp = gfx = *gfxP;
    bg = Graph_DlistAlloc(&gfxTemp, sizeof(uObjBg));
    gfx = gfxTemp;

    bg->b.imageX = 0;
    bg->b.imageW = width * 4;
    bg->b.frameX = frameX * 4.0f;
    bg->b.frameW = width * 4;
    bg->b.imageY = 0;
    bg->b.imageH = height * 4;
    bg->b.frameY = frameY * 4.0f;
    bg->b.frameH = height * 4;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = G_IM_FMT_RGBA;
    bg->b.imageSiz = G_IM_SIZ_16b;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;
    bg->b.imagePtr = source;

    // so flag is to do with whether it is scalable
    if (!!(flag & 1) != 0) {
        guS2DInitBg(bg);
    } else {
        bg->s.scaleW = (s32)(0x400 / arg7);
        bg->s.scaleH = (s32)(0x400 / arg8);
        bg->s.imageYorig = bg->b.imageY;
    }

    func_80140EAC(&gfx, bg, img, width, height, flag);
    *gfxP = gfx;
}

// used in FbdemoWipe5 and internally
// "default settings" wrapper for func_80141008
void func_8014116C(Gfx** gfxP, void* source, void* img, s32 width, s32 height, s32 flag) {
    func_80141008(gfxP, source, img, width, height, 0.0f, 0.0f, 1.0f, 1.0f, flag);
}

// wrapper for func_80141008, used in func_80141200
void func_801411B4(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 frameX, f32 frameY, f32 arg7,
                   f32 arg8, s32 flag) {
    func_80141008(gfxP, source, img, width, height, frameX, frameY, arg7, arg8, flag);
}

#define gDPSetPrimColor_u32(pkt, m, l, d)                                                       \
    _DW({                                                                                      \
        Gfx* _g = (Gfx*)(pkt);                                                                 \
                                                                                               \
        _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
        _g->words.w1 = (unsigned int)(d);                                                      \
    })

// internal
void func_80141200(Struct_80140E80* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height) {
    Gfx* gfx = *gfxP;
    s32 pad[3];

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);

    func_8014116C(&gfx, source, img, width, height, 1);

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);

    {
        s32 color = GPACK_RGBA5551(this->primColor.r, this->primColor.g, (u32)this->primColor.b, 1);

        gDPSetFillColor(gfx++, (color << 0x10) | color);
    }

    gDPFillRectangle(gfx++, 0, 0, width - 1, height - 1);

    gDPPipeSync(gfx++);

    {
        s32 lodFrac = (s32)(this->lodProportion * 255.0f);

        gDPSetPrimColor_u32(gfx++, 0, lodFrac, this->primColor.rgba);
    }

    if (this->envColor.a == 0) {
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PIXEL | AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL |
                            GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                            GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA));
        gDPSetCombineLERP(gfx++, PRIMITIVE, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, 1, PRIMITIVE, TEXEL0, PRIM_LOD_FRAC,
                          TEXEL0, 0, 0, 0, 1);
    } else {
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_NOOP2);
        gDPSetColor(gfx++, G_SETENVCOLOR, this->envColor.rgba);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                          ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                          ENVIRONMENT);
    }

    {
        f32 var_fv1 = CLAMP_ALT(this->unk04, 0.032f, 1.0f);

        func_801411B4(&gfx, img, source, width, height, width * 0.5f * (1.0f - var_fv1),
                      height * 0.5f * (1.0f - var_fv1), var_fv1, var_fv1, 0);
    }

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

// internal, used in func_80141778
void func_8014151C(Struct_80140E80* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height) {
    if (this->unk04 < 1.0f) {
        Gfx* gfx = *gfxP;
        u32 color;

        if (this->unk04 > 0.032f) {
            func_80141200(this, &gfx, source, img, width, height);
        } else {
            gDPPipeSync(gfx++);

            gDPSetOtherMode(gfx++,
                            G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                                G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                            G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
            color = GPACK_RGBA5551(this->primColor.r, this->primColor.g, (u32)this->primColor.b, 1);
            gDPSetFillColor(gfx++, (color << 0x10) | color);
            gDPFillRectangle(gfx++, 0, 0, width - 1, height - 1);

            gDPPipeSync(gfx++);
        }

        *gfxP = gfx;
    }
}

// internal, used in func_80141778
void func_80141678(Struct_80140E80* this, Gfx** gfxP, void* img, s32 width, s32 height) {
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);

    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_NOOP2);
    gDPSetColor(gfx++, G_SETPRIMCOLOR, this->primColor.rgba);
    gDPSetColor(gfx++, G_SETENVCOLOR, this->envColor.rgba);
    gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT,
                      PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT);
    func_8014116C(&gfx, img, img, width, height, 0);

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

// main 2D drawing function in this file, used in Play and FbdemoWipe4
void func_80141778(Struct_80140E80* this, Gfx** gfxP, void* img) {
    Gfx* gfx = *gfxP;

    gSPLoadUcodeL(gfx++, gspS2DEX2_fifo);

    switch (this->unk00) {
        case 1:
            func_8014151C(this, &gfx, D_0F000000, img, gScreenWidth, gScreenHeight);
            break;

        case 2:
            func_80141678(this, &gfx, D_0F000000, gScreenWidth, gScreenHeight);
            break;

        default:
            break;
    }

    gSPLoadUcode(gfx++, SysUcode_GetUCode(), SysUcode_GetUCodeData());

    *gfxP = gfx;
}
