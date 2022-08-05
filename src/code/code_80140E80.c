/**
 * @file code_80140E80.c
 * @brief Copies images between color images (generally framebuffers), possibly with scaling. Used for several
 * transition effects, and in z_play to shrink the screen at the end of the First and Second Days.
 *
 * 
 *
 * @note to use the functions in this file, with the exception of the general-purpose func_80141778(), you must load the
 * S2DEX2 microcode first, and re-load the 3D microcode afterwards for the rest of the drawing in the frame.
 */
#include "global.h"

// ucode.h
#define SP_UCODE_DATA_SIZE 0x800

// macros.h
#define CLAMP_ALT(x, min, max) ((x) > (max) ? (max) : (x) < (min) ? (min) : (x))

// Init
void func_80140E80(Struct_80140E80* this) {
    bzero(this, sizeof(Struct_80140E80));
}

// Destroy
void func_80140EA0(Struct_80140E80* this) {
}

// internal, only used in func_80141008
/**
 * Draw a bg to the specified color image.
 *
 * @param gfxP Pointer to current displaylist
 * @param bg BG object to draw
 * @param img Pointer to topleft of destination color image
 * @param width Output width in pixels
 * @param height Output height in pixels
 * @param scalable Whether to use the scalable BG mode
 */
void func_80140EAC(Gfx** gfxP, uObjBg* bg, void* img, s32 width, s32 height, s32 scalable) {
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);
    // Set up color image to draw bg to
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, img);
    gDPSetScissor(gfx++, 0, 0, 0, width, height);

    // Draw bg in appropriate type
    gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
    if (!!(scalable & 1) != 0) {
        gSPBgRectCopy(gfx++, bg);
    } else {
        gSPBgRect1Cyc(gfx++, bg);
    }

    gDPPipeSync(gfx++);
    // Reset the color image and scissor to frame's defaults
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_801FBBCC, D_0F000000);
    gSPDisplayList(gfx++, &D_0E000000.setScissor[0]);

    *gfxP = gfx;
}

// internal
/**
 * Set up a BG from a specified source image and draw it to the specified color image with func_80140EAC(), using the
 * BG's settings
 *
 * @param gfxP Pointer to current displaylist
 * @param source Beginning of texture to draw
 * @param img  Pointer to topleft of destination color image
 * @param width Output width in pixels
 * @param height Output height in pixels
 * @param x left of image drawn
 * @param y top of image drawn
 * @param scaleX Amount to rescale the image, (dsdx). No effect if `scalable` is off.
 * @param scaleY Amount to rescale the image, (dtdy). No effect if `scalable` is off.
 * @param scalable Whether to use the scalable BG mode
 */
void func_80141008(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY,
                   s32 scalable) {
    Gfx* gfx = *gfxP;
    Gfx* gfxTemp;
    uObjBg* bg;

    // Allocate for BG
    gfxTemp = gfx;
    bg = Graph_DlistAlloc(&gfxTemp, sizeof(uObjBg));
    gfx = gfxTemp;

    // Set up BG
    bg->b.imageX = 0;
    bg->b.imageW = width << 2;
    bg->b.frameX = x * 4;
    bg->b.frameW = width << 2;
    bg->b.imageY = 0;
    bg->b.imageH = height << 2;
    bg->b.frameY = y * 4;
    bg->b.frameH = height << 2;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = G_IM_FMT_RGBA;
    bg->b.imageSiz = G_IM_SIZ_16b;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;
    bg->b.imagePtr = source;

    if (!!(scalable & 1) != 0) {
        guS2DInitBg(bg);
    } else {
        bg->s.scaleW = (s32)((1 << 10) / scaleX);
        bg->s.scaleH = (s32)((1 << 10) / scaleY);
        bg->s.imageYorig = bg->b.imageY;
    }

    // draw BG to `img`
    func_80140EAC(&gfx, bg, img, width, height, scalable);

    *gfxP = gfx;
}

// used in FbdemoWipe5 and internally
// "default settings" wrapper for func_80141008
/**
 * Set up a BG from a specified source image and draw it to the specified color image with func_80140EAC(), using the
 * BG's settings. Position uses the default (0,0), and no rescaling is done.
 *
 * @see func_80141008() for arguments.
 */
void func_8014116C(Gfx** gfxP, void* source, void* img, s32 width, s32 height, s32 scalable) {
    func_80141008(gfxP, source, img, width, height, 0.0f, 0.0f, 1.0f, 1.0f, scalable);
}

// wrapper for func_80141008 with general arguments, used in func_80141200
/**
 * Set up a BG from a specified source image and draw it to the specified color image with func_80140EAC(). Fully
 * general settings are available.
 *
 * @see func_80141008() for arguments.
 */
void func_801411B4(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY,
                   s32 scalable) {
    func_80141008(gfxP, source, img, width, height, x, y, scaleX, scaleY, scalable);
}

#define gDPSetPrimColor_u32(pkt, m, l, d)                                                      \
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
        s32 lodFrac = this->lodProportion * 255.0f;

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
        f32 var_fv1 = CLAMP_ALT(this->unk_04, 0.032f, 1.0f);

        func_801411B4(&gfx, img, source, width, height, width * 0.5f * (1.0f - var_fv1),
                      height * 0.5f * (1.0f - var_fv1), var_fv1, var_fv1, 0);
    }

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

// internal, used in func_80141778
void func_8014151C(Struct_80140E80* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height) {
    if (this->unk_04 < 1.0f) {
        Gfx* gfx = *gfxP;
        u32 color;

        if (this->unk_04 > 0.032f) {
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

    switch (this->unk_00) {
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
