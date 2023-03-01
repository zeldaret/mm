/**
 * @file PreRender.c
 *
 * This file implements various routines important to framebuffer effects, such as RDP accelerated color and depth
 * buffer copies and coverage drawing. Also contains software implementations of the Video Interface anti-aliasing and
 * divot filters.
 */
#include "global.h"

/**
 * Assigns the "save" values in PreRender
 */
void PreRender_SetValuesSave(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf, void* cvg) {
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

void PreRender_Init(PreRender* this) {
    bzero(this, sizeof(PreRender));
    ListAlloc_Init(&this->alloc);
}

/**
 * Assigns the current values in PreRender
 */
void PreRender_SetValues(PreRender* this, u32 width, u32 height, void* fbuf, void* zbuf) {
    this->width = width;
    this->height = height;
    this->fbuf = fbuf;
    this->zbuf = zbuf;
    this->ulx = 0;
    this->uly = 0;
    this->lrx = width - 1;
    this->lry = height - 1;
}

void PreRender_Destroy(PreRender* this) {
    ListAlloc_FreeAll(&this->alloc);
}

void func_8016FDB8(PreRender* this, Gfx** gfxp, void* buf, void* bufSave, u32 arg4) {
    Gfx* gfx = *gfxp;
    u32 flags;

    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, bufSave);
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    flags = 0x18;
    if (arg4 == true) {
        flags = 0x1C;
    }

    Prerender_DrawBackground2D(&gfx, buf, NULL, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0,
                               0.0f, 0.0f, 1.0f, 1.0f, flags);
    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *gfxp = gfx;
}

void func_8016FF70(PreRender* this, Gfx** gfxp, void* buf, void* bufSave) {
    func_8016FDB8(this, gfxp, buf, bufSave, false);
}

void func_8016FF90(PreRender* this, Gfx** gfxp, void* buf, void* bufSave, s32 envR, s32 envG, s32 envB, s32 envA) {
    Gfx* gfx = *gfxp;

    gDPPipeSync(gfx++);

    if (envA == 255) {
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_OPA_SURF | G_RM_OPA_SURF2);
    } else {
        gDPSetOtherMode(gfx++,
                        G_AD_NOISE | G_CD_NOISE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | G_RM_CLD_SURF | G_RM_CLD_SURF2);
    }

    gDPSetEnvColor(gfx++, envR, envG, envB, envA);
    gDPSetCombineLERP(gfx++, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0, ENVIRONMENT, TEXEL0, 0, ENVIRONMENT, 0, 0, 0, 0,
                      ENVIRONMENT);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, bufSave);

    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    Prerender_DrawBackground2D(&gfx, buf, 0, this->width, this->height, G_IM_FMT_RGBA, G_IM_SIZ_16b, G_TT_NONE, 0, 0.0f,
                               0.0f, 1.0f, 1.0f, 0xB);
    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *gfxp = gfx;
}

/**
 * Copies `fbuf` to `fbufSave`, discarding the alpha channel and leaving the rgb channel unchanged
 */
void func_80170200(PreRender* this, Gfx** gfxp, void* fbuf, void* fbufSave) {
    func_8016FF90(this, gfxp, fbuf, fbufSave, 255, 255, 255, 255);
}

//! FAKE: Same definition as `gSPTextureRectangle` but without the `_DW()` wrapper (do-while 0)
#define gSPTextureRectangle_Alt(pkt, xl, yl, xh, yh, tile, s, t, dsdx, dtdy)                   \
    {                                                                                          \
        Gfx* _g = (Gfx*)(pkt);                                                                 \
                                                                                               \
        _g->words.w0 = (_SHIFTL(G_TEXRECT, 24, 8) | _SHIFTL(xh, 12, 12) | _SHIFTL(yh, 0, 12)); \
        _g->words.w1 = (_SHIFTL(tile, 24, 3) | _SHIFTL(xl, 12, 12) | _SHIFTL(yl, 0, 12));      \
        gImmp1(pkt, G_RDPHALF_1, (_SHIFTL(s, 16, 16) | _SHIFTL(t, 0, 16)));                    \
        gImmp1(pkt, G_RDPHALF_2, (_SHIFTL(dsdx, 16, 16) | _SHIFTL(dtdy, 0, 16)));              \
    }

//! FAKE: Same definition as `gDPLoadTextureTile` but without the `_DW()` wrapper (do-while 0)
#define gDPLoadTextureTile_Alt(pkt, timg, fmt, siz, width, height, uls, ult, lrs, lrt, pal, cms, cmt, masks, maskt,    \
                               shifts, shiftt)                                                                         \
    {                                                                                                                  \
        gDPSetTextureImage(pkt, fmt, siz, width, timg);                                                                \
        gDPSetTile(pkt, fmt, siz, (((((lrs) - (uls) + 1) * siz##_TILE_BYTES) + 7) >> 3), 0, G_TX_LOADTILE, 0, cmt,     \
                   maskt, shiftt, cms, masks, shifts);                                                                 \
        gDPLoadSync(pkt);                                                                                              \
        gDPLoadTile(pkt, G_TX_LOADTILE, (uls) << G_TEXTURE_IMAGE_FRAC, (ult) << G_TEXTURE_IMAGE_FRAC,                  \
                    (lrs) << G_TEXTURE_IMAGE_FRAC, (lrt) << G_TEXTURE_IMAGE_FRAC);                                     \
        gDPPipeSync(pkt);                                                                                              \
        gDPSetTile(pkt, fmt, siz, (((((lrs) - (uls) + 1) * siz##_LINE_BYTES) + 7) >> 3), 0, G_TX_RENDERTILE, pal, cmt, \
                   maskt, shiftt, cms, masks, shifts);                                                                 \
        gDPSetTileSize(pkt, G_TX_RENDERTILE, (uls) << G_TEXTURE_IMAGE_FRAC, (ult) << G_TEXTURE_IMAGE_FRAC,             \
                       (lrs) << G_TEXTURE_IMAGE_FRAC, (lrt) << G_TEXTURE_IMAGE_FRAC);                                  \
    }

/**
 * Reads the coverage values stored in the RGBA16 format `img` with dimensions `this->width`, `this->height` and
 * converts it to an 8-bpp intensity image.
 *
 * @param gfxp      Display list pointer
 * @param img       Image to read coverage from
 * @param cvgDst    Buffer to store coverage into
 */
void PreRender_CoverageRgba16ToI8(PreRender* this, Gfx** gfxp, void* img, void* cvgDst) {
    Gfx* gfx = *gfxp;
    s32 rowsRemaining;
    s32 curRow;
    s32 nRows;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_PASS | G_RM_OPA_CI2);

    // Set the combiner to draw the texture as-is, discarding alpha channel
    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 0, 0, 0, 0, TEXEL0, 0, 0, 0, 0);
    // Set the destination color image to the provided address
    gDPSetColorImage(gfx++, G_IM_FMT_I, G_IM_SIZ_8b, this->width, cvgDst);
    // Set up a scissor based on the source image
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);

    // Calculate the max number of rows that can fit into TMEM at once
    nRows = TMEM_SIZE / (this->width * G_IM_SIZ_16b_BYTES);

    // Set up the number of remaining rows
    rowsRemaining = this->height;
    curRow = 0;
    while (rowsRemaining > 0) {
        s32 uls = 0;
        s32 lrs = this->width - 1;
        s32 ult;
        s32 lrt;

        // Make sure that we don't load past the end of the source image
        nRows = MIN(rowsRemaining, nRows);

        // Determine the upper and lower bounds of the rect to draw
        ult = curRow;
        lrt = curRow + nRows - 1;

        // Load a horizontal strip of the source image in IA16 format. Since the source image is stored in memory as
        // RGBA16, the bits are reinterpreted into IA16:
        //
        // r     g      b     a
        // 11111 111 11 11111 1
        // i         a
        // 11111 111 11 11111 1
        //
        // I = (r << 3) | (g >> 2)
        // A = (g << 6) | (b << 1) | a
        //
        // Since it is expected that r = g = b = cvg in the source image, this results in
        //  I = (cvg << 3) | (cvg >> 2)
        // This expands the 5-bit coverage into an 8-bit value
        gDPLoadTextureTile_Alt(gfx++, img, G_IM_FMT_IA, G_IM_SIZ_16b, this->width, this->height, uls, ult, lrs, lrt, 0,
                               G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);

        if (1) {}

        // Draw that horizontal strip to the destination image. With the combiner and blender configuration set above,
        // the intensity (I) channel of the loaded IA16 texture will be written as-is to the I8 color image, each pixel
        // in the final image is
        //  I = (cvg << 3) | (cvg >> 2)
        // FAKE: See Alt definition above
        gSPTextureRectangle_Alt(gfx++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                                ult << 5, 1 << 10, 1 << 10);

        // Update the number of rows remaining and index of the row being drawn
        curRow += nRows;
        rowsRemaining -= nRows;
    }

    // Reset the color image to the current framebuffer
    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width, this->fbuf);

    *gfxp = gfx;
}

/**
 * Saves zbuf to zbufSave
 */
void PreRender_SaveZBuffer(PreRender* this, Gfx** gfxp) {
    if ((this->zbufSave != NULL) && (this->zbuf != NULL)) {
        func_8016FF70(this, gfxp, this->zbuf, this->zbufSave);
    }
}

/**
 * Saves fbuf to fbufSave
 */
void PreRender_SaveFramebuffer(PreRender* this, Gfx** gfxp) {
    if ((this->fbufSave != NULL) && (this->fbuf != NULL)) {
        func_80170200(this, gfxp, this->fbuf, this->fbufSave);
    }
}

/**
 * Fetches the coverage of the current framebuffer into an image of the same format as the current color image, storing
 * it over the framebuffer in memory.
 */
void PreRender_FetchFbufCoverage(PreRender* this, Gfx** gfxp) {
    Gfx* gfx = *gfxp;

    gDPPipeSync(gfx++);
    // Set the blend color to full white and set maximum depth
    gDPSetBlendColor(gfx++, 255, 255, 255, 8);
    gDPSetPrimDepth(gfx++, 0xFFFF, 0xFFFF);

    // Uses G_RM_VISCVG to blit the coverage values to the framebuffer
    //
    // G_RM_VISCVG is the following special render mode:
    //  IM_RD    : Allow read-modify-write operations on the framebuffer
    //  FORCE_BL : Apply the blender to all pixels rather than just edges
    //  (G_BL_CLR_IN * G_BL_0 + G_BL_CLR_BL * G_BL_A_MEM) / (G_BL_0 + G_BL_CLR_BL) = G_BL_A_MEM
    //
    // G_BL_A_MEM ("memory alpha") is coverage, therefore this blender configuration emits only the coverage
    // and discards any pixel colors. For an RGBA16 framebuffer, each of the three color channels r,g,b will
    // receive the coverage value individually.
    //
    // Also disables other modes such as alpha compare and texture perspective correction
    gDPSetOtherMode(gfx++,
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_VISCVG | G_RM_VISCVG2);
    // Set up a scissor with the same dimensions as the framebuffer
    gDPSetScissor(gfx++, G_SC_NON_INTERLACE, 0, 0, this->width, this->height);
    // Fill rectangle to obtain the coverage values as an RGBA16 image
    gDPFillRectangle(gfx++, 0, 0, this->width, this->height);
    gDPPipeSync(gfx++);

    *gfxp = gfx;
}

/**
 * Draws the coverage of the current framebuffer `this->fbuf` to an I8 image at `this->cvgSave`. Overwrites
 * `this->fbuf` in the process.
 */
void PreRender_DrawCoverage(PreRender* this, Gfx** gfxp) {
    PreRender_FetchFbufCoverage(this, gfxp);

    if (this->cvgSave != NULL) {
        PreRender_CoverageRgba16ToI8(this, gfxp, this->fbuf, this->cvgSave);
    }
}

/**
 * Restores zbufSave to zbuf
 */
void PreRender_RestoreZBuffer(PreRender* this, Gfx** gfxp) {
    func_8016FF70(this, gfxp, this->zbufSave, this->zbuf);
}

/**
 * Draws a full-screen image to the current framebuffer, that sources the rgb channel from `this->fbufSave` and
 * the alpha channel from `this->cvgSave` modulated by environment color.
 */
void func_80170798(PreRender* this, Gfx** gfxp) {
    Gfx* gfx;
    s32 rowsRemaining;
    s32 curRow;
    s32 nRows;
    s32 rtile = 1;

    if (this->cvgSave != NULL) {
        gfx = *gfxp;

        gDPPipeSync(gfx++);
        gDPSetEnvColor(gfx++, 255, 255, 255, 32);
        // Effectively disable blending in both cycles. It's 2-cycle so that TEXEL1 can be used to point to a different
        // texture tile.
        gDPSetOtherMode(gfx++,
                        G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                            G_TD_CLAMP | G_TP_NONE | G_CYC_2CYCLE | G_PM_NPRIMITIVE,
                        G_AC_NONE | G_ZS_PRIM | AA_EN | CVG_DST_CLAMP | ZMODE_OPA | CVG_X_ALPHA |
                            GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1) |
                            GBL_c2(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1));

        // Set up the color combiner: first cycle: TEXEL0, TEXEL1 + ENVIRONMENT; second cycle: G_CC_PASS2
        gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 1, 0, TEXEL1, ENVIRONMENT, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);

        nRows = (this->width > SCREEN_WIDTH) ? 2 : 4;

        rowsRemaining = this->height;
        curRow = 0;

        while (rowsRemaining > 0) {
            s32 uls = 0;
            s32 lrs = this->width - 1;
            s32 ult;
            s32 lrt;

            // Make sure that we don't load past the end of the source image
            nRows = MIN(rowsRemaining, nRows);

            // Determine the upper and lower bounds of the rect to draw
            ult = curRow;
            lrt = curRow + nRows - 1;

            // Load the frame buffer line
            gDPLoadMultiTile(gfx++, this->fbufSave, 0x0000, G_TX_RENDERTILE, G_IM_FMT_RGBA, G_IM_SIZ_16b, this->width,
                             this->height, uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP,
                             G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

            // Load the coverage line
            gDPLoadMultiTile(gfx++, this->cvgSave, 0x0160, rtile, G_IM_FMT_I, G_IM_SIZ_8b, this->width, this->height,
                             uls, ult, lrs, lrt, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK,
                             G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
            //! FAKE
            if (1) {}
            if (1) {}

            // Draw a texture for which the rgb channels come from the framebuffer and the alpha channel comes from
            // coverage, modulated by env color
            gSPTextureRectangle(gfx++, uls << 2, ult << 2, (lrs + 1) << 2, (lrt + 1) << 2, G_TX_RENDERTILE, uls << 5,
                                ult << 5, 1 << 10, 1 << 10);

            curRow += nRows;
            rowsRemaining -= nRows;
        }

        gDPPipeSync(gfx++);
        *gfxp = gfx;
    }
}

void func_80170AE0(PreRender* this, Gfx** gfxp, s32 alpha) {
    func_8016FF90(this, gfxp, this->fbufSave, this->fbuf, 255, 255, 255, alpha);
}

/**
 * Copies fbufSave to fbuf
 */
void PreRender_RestoreFramebuffer(PreRender* this, Gfx** gfxp) {
    func_8016FF70(this, gfxp, this->fbufSave, this->fbuf);
}

/**
 * Applies the Video Interface anti-aliasing of silhouette edges to an image.
 *
 * This filter performs a linear interpolation on partially covered pixels between the current pixel color (called
 * foreground color) and a "background" pixel color obtained by sampling fully covered pixels at the six highlighted
 * points in the following 5x3 neighborhood:
 *    _ _ _ _ _
 *  |   o   o   |
 *  | o   X   o |
 *  |   o   o   |
 *    ‾ ‾ ‾ ‾ ‾
 * Whether a pixel is partially covered is determined by reading the coverage values associated with the image.
 * Coverage is a measure of how many subpixels the last drawn primitive covered. A fully covered pixel is one with a
 * full coverage value, the entire pixel was covered by the primitive.
 * The background color is calculated as the average of the "penultimate" minimum and maximum colors in the 5x3
 * neighborhood.
 *
 * The final color is calculated by interpolating the foreground and background color weighted by the coverage:
 *      OutputColor = cvg * ForeGround + (1.0 - cvg) * BackGround
 *
 * This is a software implementation of the same algorithm used in the Video Interface hardware when Anti-Aliasing is
 * enabled in the VI Control Register.
 *
 * Patent describing the algorithm:
 *
 * Gossett, C. P., & van Hook, T. J. (Filed 1995, Published 1998)
 * Antialiasing of silhouette edges (USOO5742277A)
 * U.S. Patent and Trademark Office
 * Expired 2015-10-06
 * https://patents.google.com/patent/US5742277A/en
 *
 * @param this  PreRender instance
 * @param x     Center pixel x
 * @param y     Center pixel y
 */
void PreRender_AntiAliasFilter(PreRender* this, s32 x, s32 y) {
    s32 i;
    s32 j;
    s32 buffCvg[3 * 5];
    s32 buffR[3 * 5];
    s32 buffG[3 * 5];
    s32 buffB[3 * 5];
    s32 xi;
    s32 yi;
    s32 temp;
    s32 pmaxR;
    s32 pmaxG;
    s32 pmaxB;
    s32 pminR;
    s32 pminG;
    s32 pminB;
    Color_RGBA16 pxIn;
    Color_RGBA16 pxOut;
    u32 outR;
    u32 outG;
    u32 outB;

    // Extract pixels in the 5x3 neighborhood
    for (i = 0; i < 5 * 3; i++) {
        xi = x + (i % 5) - 2;
        yi = y + (i / 5) - 1;

        // Clamp coordinates to the edges of the image
        if (xi < 0) {
            xi = 0;
        } else if (xi > (this->width - 1)) {
            xi = this->width - 1;
        }
        if (yi < 0) {
            yi = 0;
        } else if (yi > (this->height - 1)) {
            yi = this->height - 1;
        }

        // Extract color channels for each pixel, convert 5-bit color channels to 8-bit
        pxIn.rgba = this->fbufSave[xi + yi * this->width];
        buffR[i] = (pxIn.r << 3) | (pxIn.r >> 2);
        buffG[i] = (pxIn.g << 3) | (pxIn.g >> 2);
        buffB[i] = (pxIn.b << 3) | (pxIn.b >> 2);
        buffCvg[i] = this->cvgSave[xi + yi * this->width] >> 5;
    }

    pmaxR = pminR = buffR[7];
    pmaxG = pminG = buffG[7];
    pmaxB = pminB = buffB[7];

    // For each neighbor
    for (i = 1; i < 5 * 3; i += 2) {
        // Only sample fully covered pixels
        if (buffCvg[i] == 7) {
            // Determine "Penultimate Maximum" Value

            // If current maximum is less than this neighbor
            if (pmaxR < buffR[i]) {
                // For each neighbor (again)
                for (j = 1; j < 5 * 3; j += 2) {
                    // If not the neighbor we were at before, and this neighbor has a larger value and this pixel is
                    // fully covered, that means the neighbor at `i` is the "penultimate maximum"
                    if ((i != j) && (buffR[j] >= buffR[i]) && (buffCvg[j] == 7)) {
                        pmaxR = buffR[i];
                    }
                }
            }
            if (pmaxG < buffG[i]) {
                for (j = 1; j < 5 * 3; j += 2) {
                    if ((i != j) && (buffG[j] >= buffG[i]) && (buffCvg[j] == 7)) {
                        pmaxG = buffG[i];
                    }
                }
            }
            if (pmaxB < buffB[i]) {
                for (j = 1; j < 5 * 3; j += 2) {
                    if ((i != j) && (buffB[j] >= buffB[i]) && (buffCvg[j] == 7)) {
                        pmaxB = buffB[i];
                    }
                }
            }

            if (1) {}

            // Determine "Penultimate Minimum" Value

            // Same as above with inverted conditions
            if (pminR > buffR[i]) {
                for (j = 1; j < 5 * 3; j += 2) {
                    if ((i != j) && (buffR[j] <= buffR[i]) && (buffCvg[j] == 7)) {
                        pminR = buffR[i];
                    }
                }
            }
            if (pminG > buffG[i]) {
                for (j = 1; j < 5 * 3; j += 2) {
                    if ((i != j) && (buffG[j] <= buffG[i]) && (buffCvg[j] == 7)) {
                        pminG = buffG[i];
                    }
                }
            }
            if (pminB > buffB[i]) {
                for (j = 1; j < 5 * 3; j += 2) {
                    if ((i != j) && (buffB[j] <= buffB[i]) && (buffCvg[j] == 7)) {
                        pminB = buffB[i];
                    }
                }
            }
        }
    }

    // The background color is determined by averaging the penultimate minimum and maximum pixels, and subtracting the
    // ForeGround color:
    //      BackGround = (pMax + pMin) - (ForeGround) * 2

    // OutputColor = cvg * ForeGround + (1.0 - cvg) * BackGround
    temp = 7 - buffCvg[7];
    outR = buffR[7] + ((s32)(temp * (pmaxR + pminR - (buffR[7] * 2)) + 4) >> 3);
    outG = buffG[7] + ((s32)(temp * (pmaxG + pminG - (buffG[7] * 2)) + 4) >> 3);
    outB = buffB[7] + ((s32)(temp * (pmaxB + pminB - (buffB[7] * 2)) + 4) >> 3);

    pxOut.r = outR >> 3;
    pxOut.g = outG >> 3;
    pxOut.b = outB >> 3;
    pxOut.a = 1;
    this->fbufSave[x + y * this->width] = pxOut.rgba;
}

/**
 * Applies the Video Interface anti-aliasing filter to `this->fbufSave` using `this->cvgSave`
 */
void PreRender_ApplyAntiAliasingFilter(PreRender* this) {
    s32 x;
    s32 y;
    s32 cvg;

    // Apply AA filter
    for (y = 0; y < this->height; y++) {
        for (x = 0; x < this->width; x++) {
            cvg = this->cvgSave[x + y * this->width];
            cvg >>= 5;
            cvg++;

            if (cvg != 8) {
                // If this pixel has only partial coverage, perform the Video Filter interpolation on it
                PreRender_AntiAliasFilter(this, x, y);
            }
        }
    }
}

// TODO: Could args be `windowR`,`windowG`,`windowB` from OoT's PreRender_DivotFilter()
u32 func_801716C4(u8* arg0, u8* arg1, u8* arg2) {
    u8 sp28[8 * 4];
    u32 var_s0;
    u32 var_s1;

    *(s32*)(&sp28[0 * 4]) = 0;
    *(s32*)(&sp28[1 * 4]) = 0;
    *(s32*)(&sp28[2 * 4]) = 0;
    *(s32*)(&sp28[3 * 4]) = 0;
    *(s32*)(&sp28[4 * 4]) = 0;
    *(s32*)(&sp28[5 * 4]) = 0;
    *(s32*)(&sp28[6 * 4]) = 0;
    *(s32*)(&sp28[7 * 4]) = 0;

    sp28[arg0[0]]++;
    sp28[arg0[1]]++;
    sp28[arg0[2]]++;

    sp28[arg1[0]]++;
    sp28[arg1[1]]++;
    sp28[arg1[2]]++;

    sp28[arg2[0]]++;
    sp28[arg2[1]]++;
    sp28[arg2[2]]++;

    var_s0 = 0;
    var_s1 = 0;
    while (true) {
        var_s0 += sp28[var_s1];
        if (var_s0 >= 5) {
            break;
        }
        var_s1++;
    }

    return var_s1;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/PreRender/func_801717F8.s")

/**
 * Applies filters to the framebuffer prerender to make it look smoother
 */
void PreRender_ApplyFilters(PreRender* this) {
    if ((this->cvgSave == NULL) || (this->fbufSave == NULL)) {
        this->unk_4D = 0;
    } else {
        this->unk_4D = 1;
        PreRender_ApplyAntiAliasingFilter(this);
        func_801717F8(this);
        this->unk_4D = 2;
    }
}

/**
 * Initializes `PreRender_ApplyFilters` onto a new "slowly" thread
 */
void PreRender_ApplyFiltersSlowlyInit(PreRender* this) {
    if ((this->cvgSave != NULL) && (this->fbufSave != NULL)) {
        if (D_801F6FC0) {
            StackCheck_Cleanup(&slowlyStackEntry);
            Slowly_Stop(&D_801F6E00);
        }

        this->unk_4D = 1;
        StackCheck_Init(&slowlyStackEntry, slowlyStack, &slowlyStack[4096], 0, 0x100, "slowly");
        Slowly_Start(&D_801F6E00, &D_801F7FE8, PreRender_ApplyFilters, this, NULL);
        D_801F6FC0 = true;
    }
}

/**
 * Destroys the "slowly" thread
 */
void PreRender_ApplyFiltersSlowlyDestroy(PreRender* this) {
    if (D_801F6FC0) {
        StackCheck_Cleanup(&slowlyStackEntry);
        Slowly_Stop(&D_801F6E00);
        D_801F6FC0 = false;
    }
}

// Unused, likely since `PreRender_ApplyFilters` already handles NULL checks
void func_801720C4(PreRender* this) {
    if ((this->cvgSave != NULL) && (this->fbufSave != NULL)) {
        PreRender_ApplyFilters(this);
    }
}

// TODO: ucode.h
#define SP_UCODE_DATA_SIZE 0x800

typedef struct {
    /* 0x00 */ void* timg;
    /* 0x04 */ void* tlut;
    /* 0x08 */ u16 width;
    /* 0x0A */ u16 height;
    /* 0x0C */ u8 fmt;
    /* 0x0D */ u8 siz;
    /* 0x0E */ u16 tt;
    /* 0x10 */ u16 tlutCount;
    /* 0x14 */ f32 x;
    /* 0x18 */ f32 y;
    /* 0x1C */ f32 xScale;
    /* 0x20 */ f32 yScale;
    /* 0x24 */ u32 flags;
} PreRenderBackground2DParams; // size = 0x28

void Prerender_DrawBackground2DImpl(PreRenderBackground2DParams* bg2D, Gfx** gfxp) {
    Gfx* gfx;
    uObjBg* bg;
    u32 sp64;
    Gfx* gfxTemp;
    u32 sp5C;

    sp5C = (bg2D->flags & 8) != 0;
    sp64 = (bg2D->flags & 4) ? G_AC_THRESHOLD : G_AC_NONE;

    gfxTemp = *gfxp;
    bg = Graph_DlistAlloc(&gfxTemp, sizeof(uObjBg));
    gfx = gfxTemp;

    bg->b.imageX = 0;
    bg->b.imageW = (bg2D->width * (1 << 2)) + 1;
    bg->b.frameX = bg2D->x * (1 << 2);

    bg->b.imageY = 0;
    bg->b.imageH = (bg2D->height * (1 << 2)) + 1;
    bg->b.frameY = bg2D->y * (1 << 2);

    bg->b.imagePtr = bg2D->timg;
    bg->b.imageLoad = G_BGLT_LOADTILE;
    bg->b.imageFmt = bg2D->fmt;
    bg->b.imageSiz = bg2D->siz;
    bg->b.imagePal = 0;
    bg->b.imageFlip = 0;

    if (sp5C) {
        gSPLoadUcodeL(gfx++, gspS2DEX2_fifo);
    }

    if ((bg2D->fmt == G_IM_FMT_CI) && (bg2D->tlut != NULL)) {
        gDPLoadTLUT(gfx++, bg2D->tlutCount, 256, bg2D->tlut);
    } else {
        gDPPipeSync(gfx++);
    }

    if (bg2D->flags & 0x10) {
        bg->b.frameW = bg2D->width * (1 << 2);
        bg->b.frameH = bg2D->height * (1 << 2);

        guS2DInitBg(bg);

        if (!(bg2D->flags & 1)) {
            gDPSetOtherMode(gfx++, bg2D->tt | G_CYC_COPY, sp64);
        }

        gSPBgRectCopy(gfx++, bg);
    } else {
        bg->b.frameW = (u32)(bg2D->width * (1 << 2)) * bg2D->xScale;
        bg->b.frameH = (u32)(bg2D->height * (1 << 2)) * bg2D->yScale;
        bg->b.tmemW = (1 << 10) / bg2D->xScale;
        bg->b.tmemH = (1 << 10) / bg2D->yScale;
        bg->s.imageYorig = bg->b.imageY;

        if (!(bg2D->flags & 1)) {
            gDPSetOtherMode(gfx++, bg2D->tt | G_AD_DISABLE | G_CD_DISABLE | G_TC_FILT,
                            AA_EN | CVG_X_ALPHA | ALPHA_CVG_SEL |
                                GBL_c1(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) |
                                GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_BL, G_BL_1MA) | sp64);
        }

        if (!(bg2D->flags & 2)) {
            gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, 1, 0, 0, 0, TEXEL0, 0, 0, 0, 1);
        }

        gSPObjRenderMode(gfx++, G_OBJRM_ANTIALIAS | G_OBJRM_BILERP);
        gSPBgRect1Cyc(gfx++, bg);
    }

    gDPPipeSync(gfx++);

    if (sp5C) {
        gSPLoadUcode(gfx++, SysUcode_GetUCode(), SysUcode_GetUCodeData());
    }

    *gfxp = gfx;
}

void Prerender_DrawBackground2D(Gfx** gfxp, void* timg, void* tlut, u16 width, u16 height, u8 fmt, u8 siz, u16 tt,
                                u16 tlutCount, f32 x, f32 y, f32 xScale, f32 yScale, u32 flags) {
    PreRenderBackground2DParams bg2D;
    PreRenderBackground2DParams* bg2DPtr = &bg2D;

    bg2D.timg = timg;
    bg2D.tlut = tlut;
    bg2D.width = width;
    bg2D.height = height;
    bg2D.fmt = fmt;
    bg2D.siz = siz;
    bg2D.tt = tt;
    bg2D.tlutCount = tlutCount;
    bg2D.x = x;
    bg2D.y = y;
    bg2D.xScale = xScale;
    bg2D.yScale = yScale;
    bg2D.flags = flags;

    Prerender_DrawBackground2DImpl(bg2DPtr, gfxp);
}
