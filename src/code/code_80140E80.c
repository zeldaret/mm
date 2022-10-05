/**
 * @file code_80140E80.c
 * @brief Copies images between color images (generally framebuffers), possibly with filling, scaling, and colour
 * interpolation.
 *
 * Used for several transition effects, and in z_play to shrink the screen at the end of the First and Second Days.
 *
 *
 *
 * @note to use the functions in this file, with the exception of func_80141778(), it is necessary to load the S2DEX2
 * microcode first, and then re-load the 3D microcode afterwards for the rest of the drawing in the frame; see
 * func_80141778() for how to do this.
 */
#include "global.h"

// z64.h once named properly
typedef enum {
    /* 0 */ BG_CYC_1CYC, // Enable rescaling
    /* 1 */ BG_CYC_COPY  // Direct copy, no scaling
} BgMode;

typedef enum {
    /* 0 */ FB_MODE_DO_NOTHING, // Do nothing but waste time loading microcode
    /* 1 */ FB_MODE_GENERAL,    // Interpolation, filling and scaling
    /* 2 */ FB_MODE_INTERPOLATE
} FbMode;

#define SCALE_MIN 0.032f
#define SCALE_MAX 1.0f //!< also unchanged scale

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
 * @param[in,out] gfxP      Pointer to current displaylist
 * @param[in]     bg        BG object to draw
 * @param[out]    img       Pointer to beginning of destination color image
 * @param[in]     width     Output width in pixels
 * @param[in]     height    Output height in pixels
 * @param[in]     cycleFlag Which BG mode to use
 */
void func_80140EAC(Gfx** gfxP, uObjBg* bg, void* img, s32 width, s32 height, s32 cycleFlag) {
    Gfx* gfx = *gfxP;

    gDPPipeSync(gfx++);
    // Set up color image to draw bg to
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, img);
    gDPSetScissor(gfx++, 0, 0, 0, width, height);

    // Draw bg in appropriate type
    gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
    if (!!(cycleFlag & BG_CYC_COPY) != 0) { //! FAKE: may possibly be a better way
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
 * BG's settings. Use func_8014116C() or func_801411B4()
 *
 * @param[out] gfxP     Pointer to current displaylist
 * @param[in] source    Pointer to beginning of source color image
 * @param[out] img      Pointer to beginning of destination color image
 * @param[in] width     Output width in pixels
 * @param[in] height    Output height in pixels
 * @param[in] x         Left of drawn output
 * @param[in] y         Top of drawn output
 * @param[in] scaleX    Amount to rescale the image, (dsdx). No effect if `cycleFlag` is `BG_CYC_COPY`.
 * @param[in] scaleY    Amount to rescale the image, (dtdy). No effect if `cycleFlag` is `BG_CYC_COPY`.
 * @param[in] cycleFlag Which BG mode to use
 */
void func_80141008(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY,
                   s32 cycleFlag) {
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

    if (!!(cycleFlag & BG_CYC_COPY) != 0) { //! TODO possibly fake, may be a better way
        guS2DInitBg(bg);
    } else {
        bg->s.scaleW = (s32)((1 << 10) / scaleX);
        bg->s.scaleH = (s32)((1 << 10) / scaleY);
        bg->s.imageYorig = bg->b.imageY;
    }

    // draw BG to `img`
    func_80140EAC(&gfx, bg, img, width, height, cycleFlag);

    *gfxP = gfx;
}

// used in FbdemoWipe5 and internally
// "default settings" wrapper for func_80141008
/**
 * Set up a BG from a specified source image and draw it to the specified color image with func_80140EAC(), using the
 * BG's settings. Position uses the default (0,0), and no rescaling is done even if 1-cycle mode is enabled.
 *
 * @see func_80141008() for arguments.
 */
void func_8014116C(Gfx** gfxP, void* source, void* img, s32 width, s32 height, s32 cycleFlag) {
    func_80141008(gfxP, source, img, width, height, 0.0f, 0.0f, SCALE_MAX, SCALE_MAX, cycleFlag);
}

// wrapper for func_80141008 with general arguments, used in func_80141200
/**
 * Set up a BG from a specified source image and draw it to the specified color image with func_80140EAC(). Fully
 * general settings are available.
 *
 * @see func_80141008() for arguments.
 */
void func_801411B4(Gfx** gfxP, void* source, void* img, s32 width, s32 height, f32 x, f32 y, f32 scaleX, f32 scaleY,
                   s32 cycleFlag) {
    func_80141008(gfxP, source, img, width, height, x, y, scaleX, scaleY, cycleFlag);
}

// TODO work out what to do with this.
#define gDPSetPrimColor_u32(pkt, m, l, d)                                                      \
    _DW({                                                                                      \
        Gfx* _g = (Gfx*)(pkt);                                                                 \
                                                                                               \
        _g->words.w0 = (_SHIFTL(G_SETPRIMCOLOR, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
        _g->words.w1 = (unsigned int)(d);                                                      \
    })

#define gDPSetLODColor(pkt, c, m, l, d)                                          \
    _DW({                                                                        \
        Gfx* _g = (Gfx*)(pkt);                                                   \
                                                                                 \
        _g->words.w0 = _SHIFTL(c, 24, 8) | _SHIFTL(m, 8, 8) | _SHIFTL(l, 0, 8)); \
        _g->words.w1 = (unsigned int)(d);                                        \
    })

// internal, used in func_8014151C
/**
 * Most general redrawing function.
 *
 *  - Copies `source` to `img`,
 *  - fills the current framebuffer with `this->primColor`,
 *  - applies colour interpolation to `img`,
 *  - copies `img` back to `source`, with rescaling.
 *
 * @param[in]     this
 * @param[in,out] gfxP   Pointer to current displaylist
 * @param[in,out] source Pointer to beginning of in/out color image
 * @param[out]    img    Pointer to beginning of destination color image
 * @param[in]     width  Output width in pixels
 * @param[in]     height Output height in pixels
 */
void func_80141200(Struct_80140E80* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height) {
    Gfx* gfx = *gfxP;
    s32 pad[3];

    gDPPipeSync(gfx++);
    // copy source to img
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_COPY | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    func_8014116C(&gfx, source, img, width, height, BG_CYC_COPY);

    gDPPipeSync(gfx++);
    // fill framebuffer with primColor
    gDPSetOtherMode(gfx++,
                    G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
    {
        s32 color = GPACK_RGBA5551(this->primColor.r, this->primColor.g, (u32)this->primColor.b, 1);

        gDPSetFillColor(gfx++, (color << 0x10) | color);
    }
    //! @bug func_8014116C() sets the current color image back to the frame's default framebuffer at the end, so this
    //! will always fill in the default framebuffer, whatever are used as `source` and `img`. This does not arise
    //! in-game since this function is always used with `source = D_0F000000`.
    gDPFillRectangle(gfx++, 0, 0, width - 1, height - 1);

    gDPPipeSync(gfx++);
    // Set lod and primColor from struct, perform interpolation, draw image with scaling (this is the most general
    // alteration this system can carry out).
    {
        s32 lodFrac = this->lodProportion * 255;

        gDPSetPrimColor_u32(gfx++, 0, lodFrac, this->primColor.rgba);
    }
    if (this->envColor.a == 0) {
        // Interpolate between primColor and texel color using lod (but with max alpha)
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_BILERP | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_THRESHOLD | G_ZS_PIXEL | AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA | ALPHA_CVG_SEL |
                            GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                            GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA));
        gDPSetCombineLERP(gfx++, PRIMITIVE, TEXEL0, PRIM_LOD_FRAC, TEXEL0, 0, 0, 0, 1, PRIMITIVE, TEXEL0, PRIM_LOD_FRAC,
                          TEXEL0, 0, 0, 0, 1);
    } else {
        // Interpolate between envColor (the new black) and primColor (the new white)
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PIXEL | G_RM_CLD_SURF | G_RM_NOOP2);
        gDPSetColor(gfx++, G_SETENVCOLOR, this->envColor.rgba);
        gDPSetCombineLERP(gfx++, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                          ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0, ENVIRONMENT, PRIMITIVE, ENVIRONMENT, TEXEL0,
                          ENVIRONMENT);
    }
    // Draw scaled image in centre of width x height rectangle in `source`
    {
        f32 scale = CLAMP_ALT(this->scale, SCALE_MIN, SCALE_MAX);

        func_801411B4(&gfx, img, source, width, height, width * 0.5f * (1.0f - scale), height * 0.5f * (1.0f - scale),
                      scale, scale, BG_CYC_1CYC);
    }

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

// internal, used in func_80141778, mode 1
/**
 * If scale is within `(SCALE_MIN, SCALE_MAX)`, apply func_80141200().
 * If it is smaller than `SCALE_MIN`, fill the framebuffer with `this->primColor`
 *
 * @param[in]     this
 * @param[in,out] gfxP   Pointer to current displaylist
 * @param[in,out] source Pointer to beginning of source color image
 * @param[in,out] img    Pointer to beginning of destination color image
 * @param[in]     width  Output width in pixels
 * @param[in]     height Output height in pixels
 */
void func_8014151C(Struct_80140E80* this, Gfx** gfxP, void* source, void* img, s32 width, s32 height) {
    if (this->scale < SCALE_MAX) {
        Gfx* gfx = *gfxP;
        u32 color;

        if (this->scale > SCALE_MIN) {
            func_80141200(this, &gfx, source, img, width, height);
        } else {
            gDPPipeSync(gfx++);
            // fill the framebuffer with this->primColor
            gDPSetOtherMode(gfx++,
                            G_AD_PATTERN | G_CD_MAGICSQ | G_CK_NONE | G_TC_CONV | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                                G_TD_CLAMP | G_TP_NONE | G_CYC_FILL | G_PM_NPRIMITIVE,
                            G_AC_NONE | G_ZS_PIXEL | G_RM_NOOP | G_RM_NOOP2);
            color = GPACK_RGBA5551(this->primColor.r, this->primColor.g, (u32)this->primColor.b, 1);
            gDPSetFillColor(gfx++, (color << 0x10) | color);
            //! @bug See corresponding note in func_80141200()
            gDPFillRectangle(gfx++, 0, 0, width - 1, height - 1);

            gDPPipeSync(gfx++);
        }

        *gfxP = gfx;
    }
}

// internal, used in func_80141778, mode 2
/**
 * Redraw `img` in-place, using texel color to interpolate between envColor (the new black) and primColor (the new
 * white)
 *
 * @param[in]     this
 * @param[in,out] gfxP   Pointer to current displaylist
 * @param[in,out] img    Pointer to beginning of color image to modify in-place
 * @param[in]     width  width of img
 * @param[in]     height height of img
 */
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
    func_8014116C(&gfx, img, img, width, height, BG_CYC_1CYC);

    gDPPipeSync(gfx++);

    *gfxP = gfx;
}

// main 2D drawing function in this file, used in Play and FbdemoWipe4
/**
 *
 *
 * @param[in]     this
 * @param[in,out] gfxP Pointer to current displaylist
 * @param[in,out] img  Pointer to beginning of destination color image
 */
void func_80141778(Struct_80140E80* this, Gfx** gfxP, void* img) {
    Gfx* gfx = *gfxP;

    gSPLoadUcodeL(gfx++, gspS2DEX2_fifo);

    switch (this->mode) {
        case FB_MODE_GENERAL:
            func_8014151C(this, &gfx, D_0F000000, img, gScreenWidth, gScreenHeight);
            break;

        case FB_MODE_INTERPOLATE:
            func_80141678(this, &gfx, D_0F000000, gScreenWidth, gScreenHeight);
            break;

        default:
            break;
    }

    gSPLoadUcode(gfx++, SysUcode_GetUCode(), SysUcode_GetUCodeData());

    *gfxP = gfx;
}
