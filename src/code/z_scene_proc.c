#include <ultra64.h>
#include <global.h>

// Default displaylist that sets a valid displaylist into all of the segments
static Gfx sSceneDrawDefaultDl[] = {
    gsSPSegment(0x08, gEmptyDL),
    gsSPSegment(0x09, gEmptyDL),
    gsSPSegment(0x0A, gEmptyDL),
    gsSPSegment(0x0B, gEmptyDL),
    gsSPSegment(0x0C, gEmptyDL),
    gsSPSegment(0x0D, gEmptyDL),
    gsSPSegment(0x06, gEmptyDL),
    gsDPPipeSync(),
    gsDPSetPrimColor(0, 0, 128, 128, 128, 128),
    gsDPSetEnvColor(128, 128, 128, 128),
    gsSPEndDisplayList(),
};

/**
 * Executes the current scene draw config function
 */
void SceneProc_ExecuteSceneDrawFunc(GlobalContext* globalCtx) {
    static SceneDrawConfigFunc sceneDrawConfigFuncs[] = {
        SceneProc_SceneDrawConfigDefault,
        SceneProc_SceneDrawConfigAnimatedTexture,
        SceneProc_SceneDrawConfigDoNothing,
        SceneProc_DrawSceneConfig3, // unused
        SceneProc_DrawSceneConfig4, // unused
        SceneProc_SceneDrawConfig5, // unused
        SceneProc_SceneDrawConfigGreatBayTemple,
        SceneProc_SceneDrawConfigSakonsHideout,
    };

    sceneDrawConfigFuncs[globalCtx->sceneConfig](globalCtx);
}

/**
 * Default scene draw config function. This will only execute `sSceneDrawDefaultDl` on both POLY_OPA_DISP and
 * POLY_XLU_DISP
 */
void SceneProc_SceneDrawConfigDefault(GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    gSPDisplayList(gfxCtx->polyOpa.p++, sSceneDrawDefaultDl);
    gSPDisplayList(gfxCtx->polyXlu.p++, sSceneDrawDefaultDl);
}

/**
 * Returns a pointer to a single layer texture scroll displaylist
 */
Gfx* SceneProc_SingleLayerTexScroll(GlobalContext* globalCtx, TextureAnimParams* params) {
    return Gfx_TexScroll(globalCtx->state.gfxCtx, params->xStep * gSceneProcStep, -(params->yStep * gSceneProcStep),
                         params->width, params->height);
}

// TODO: name
void SceneProc_DrawType0Texture(GlobalContext* globalCtx, u32 segment, TextureAnimParams* params) {
    Gfx* texScrollDList = SceneProc_SingleLayerTexScroll(globalCtx, params);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (gSceneProcFlags & 1) {
        gSPSegment(POLY_OPA_DISP++, segment, texScrollDList);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(POLY_XLU_DISP++, segment, texScrollDList);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Returns a pointer to a two layer texture scroll displaylist
 */
Gfx* SceneProc_TwoLayerTexScroll(GlobalContext* globalCtx, TextureAnimParams* params) {
    return Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, params[0].xStep * gSceneProcStep,
                            -(params[0].yStep * gSceneProcStep), params[0].width, params[0].height, 1,
                            params[1].xStep * gSceneProcStep, -(params[1].yStep * gSceneProcStep), params[1].width,
                            params[1].height);
}

// TODO: name
void SceneProc_DrawType1Texture(GlobalContext* globalCtx, u32 segment, TextureAnimParams* params) {
    Gfx* texScrollDList = SceneProc_TwoLayerTexScroll(globalCtx, params);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (gSceneProcFlags & 1) {
        gSPSegment(POLY_OPA_DISP++, segment, texScrollDList);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(POLY_XLU_DISP++, segment, texScrollDList);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Generates a displaylist that sets the prim and env color, and stores it in the provided segment ID
 */
void SceneProc_SetColorInSegment(GlobalContext* globalCtx, u32 segment, SceneDrawPrimColor* primColor,
                                 SceneDrawEnvColor* envColor) {
    Gfx* colorDList;
    Gfx* _g;

    // TODO allocation should be a macro
    _g = (Gfx*)(((u32)globalCtx->state.gfxCtx->polyOpa.d) - sizeof(Gfx) * 4); // Allocate enough space for 4 Gfx
    colorDList = _g;
    globalCtx->state.gfxCtx->polyOpa.d = _g;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    // clang-format off
    if (gSceneProcFlags & 1) { gSPSegment(POLY_OPA_DISP++, segment, colorDList); }
    if (gSceneProcFlags & 2) { gSPSegment(POLY_XLU_DISP++, segment, colorDList); }
    // clang-format on

    gDPSetPrimColor(colorDList++, 0, primColor->lodFrac, primColor->r, primColor->g, primColor->b,
                    (u8)(primColor->a * gSceneProcFlashingAlpha));

    if (envColor != NULL) {
        gDPSetEnvColor(colorDList++, envColor->r, envColor->g, envColor->b, envColor->a);
    }

    gSPEndDisplayList(colorDList++);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void SceneProc_DrawType2Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params) {
    Color_RGBA8* envColor;
    SceneDrawPrimColor* primColor = (SceneDrawPrimColor*)Lib_SegmentedToVirtual(params->primColors);
    u32 pad;
    u32 index = gSceneProcStep % params->cycleLength;

    primColor += index;

    if (params->envColors) {
        envColor = (Color_RGBA8*)Lib_SegmentedToVirtual(params->envColors) + index;
    } else {
        envColor = NULL;
    }

    SceneProc_SetColorInSegment(ctxt, segment, primColor, envColor);
}

s32 SceneProc_Lerp(s32 a, s32 b, f32 t) {
    return (s32)((b - a) * t) + a;
}

#ifdef NON_MATCHING
// Slight ordering and regalloc differences around t = ...
void SceneProc_DrawType3Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params) {
    FlashingTextureParams* params2 = params;
    Color_RGBA8* envColorTo;
    SceneDrawPrimColor* primColorTo = (SceneDrawPrimColor*)Lib_SegmentedToVirtual(params2->primColors);
    u16* keyFrames = (u16*)Lib_SegmentedToVirtual(params2->keyFrames);
    s32 index = gSceneProcStep % params2->cycleLength;
    s32 pad1;
    s32 keyFrameIndex;
    Color_RGBA8* envColorPtrIn;
    f32 t;
    s32 pad2;
    SceneDrawPrimColor primColorIn;
    Color_RGBA8* envColorFrom;
    Color_RGBA8 envColorIn;
    s32 pad3;
    SceneDrawPrimColor* primColorFrom;

    keyFrameIndex = 1;
    keyFrames += 1;
    while (params2->numKeyFrames > keyFrameIndex) {
        if (index < *keyFrames)
            break;
        keyFrameIndex++;
        keyFrames++;
    }

    primColorTo += keyFrameIndex;
    pad1 = keyFrames[0] - keyFrames[-1];
    pad2 = index - keyFrames[-1];

    t = (f32)pad2 / (f32)pad1;

    primColorFrom = primColorTo - 1;
    primColorIn.red = SceneProc_Lerp(primColorFrom->red, primColorTo->red, t);
    primColorIn.green = SceneProc_Lerp(primColorFrom->green, primColorTo->green, t);
    primColorIn.blue = SceneProc_Lerp(primColorFrom->blue, primColorTo->blue, t);
    primColorIn.alpha = SceneProc_Lerp(primColorFrom->alpha, primColorTo->alpha, t);
    primColorIn.lodFrac = SceneProc_Lerp(primColorFrom->lodFrac, primColorTo->lodFrac, t);

    if (params2->envColors) {
        envColorTo = (Color_RGBA8*)Lib_SegmentedToVirtual(params2->envColors) + keyFrameIndex;
        envColorFrom = envColorTo - 1;
        envColorIn.red = SceneProc_Lerp(envColorFrom->red, envColorTo->red, t);
        envColorIn.green = SceneProc_Lerp(envColorFrom->green, envColorTo->green, t);
        envColorIn.blue = SceneProc_Lerp(envColorFrom->blue, envColorTo->blue, t);
        envColorIn.alpha = SceneProc_Lerp(envColorFrom->alpha, envColorTo->alpha, t);
    } else {
        envColorTo = NULL;
    }

    if (envColorTo) {
        envColorPtrIn = &envColorIn;
    } else {
        envColorPtrIn = NULL;
    }

    SceneProc_SetColorInSegment(ctxt, segment, &primColorIn, envColorPtrIn);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawType3Texture.asm")
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_Interpolate.asm")

u8 SceneProc_InterpolateClamped(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame) {
    s32 ret = SceneProc_Interpolate(numKeyFrames, keyFrames, values, frame);

    return (ret < 0) ? 0 : (ret > 0xFF) ? 0xFF : ret;
}

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawType4Texture.asm")

void SceneProc_DrawType5Texture(GlobalContext* ctxt, u32 segment, CyclingTextureParams* params) {
    u8* offsets;
    Gfx** dls;
    Gfx* dl;
    GraphicsContext* gfxCtx;
    s32 step;

    dls = (Gfx**)Lib_SegmentedToVirtual(params->textureDls);
    offsets = (u8*)Lib_SegmentedToVirtual(params->textureDlOffsets);
    step = gSceneProcStep % params->cycleLength;
    dl = (Gfx*)Lib_SegmentedToVirtual(dls[offsets[step]]);

    gfxCtx = ctxt->state.gfxCtx;
    if (gSceneProcFlags & 1) {
        gSPSegment(gfxCtx->polyOpa.p++, segment, dl);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(gfxCtx->polyXlu.p++, segment, dl);
    }
}

void SceneProc_DrawAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, f32 flashingAlpha, u32 step,
                                    u32 flags) {
    static scene_proc_draw_func gSceneProcDrawFuncs[] = {
        SceneProc_DrawType0Texture, SceneProc_DrawType1Texture, SceneProc_DrawType2Texture,
        SceneProc_DrawType3Texture, SceneProc_DrawType4Texture, SceneProc_DrawType5Texture,
    };
    s32 segmentAbs;
    s32 segment;

    gSceneProcFlashingAlpha = flashingAlpha;
    gSceneProcStep = step;
    gSceneProcFlags = flags;

    if ((textures != NULL) && (textures->segment != 0)) {
        do {
            segment = textures->segment;
            segmentAbs = ((segment < 0) ? -segment : segment) + 7;

            gSceneProcDrawFuncs[textures->type](ctxt, segmentAbs, (void*)Lib_SegmentedToVirtual(textures->params));

            textures++;
        } while (segment > -1);
    }
}

void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 3);
}

void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 1);
}

void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 2);
}

void SceneProc_DrawAllSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 3);
}

void SceneProc_DrawOpaqueSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 1);
}

void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures,
                                                             f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 2);
}

void SceneProc_DrawAllAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 3);
}

void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 1);
}

void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 2);
}

void SceneProc_DrawAllAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 3);
}
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha,
                                                   u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 1);
}
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha,
                                                        u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 2);
}

void SceneProc_SceneDrawConfigAnimatedTexture(GlobalContext* ctxt) {
    SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);
}

#ifdef NON_MATCHING
// This function still needs a lot of work
void SceneProc_DrawSceneConfig3(GlobalContext* ctxt) {
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
    u32 frames = ctxt->unk18840;

    if (0)
        ;

    gSPSegment(gfxCtx->polyXlu.p++, 8, Rcp_GenerateSetTileSizeDl(ctxt->state.gfxCtx, 0, frames & 0x3f, 0x100, 0x10));
    gSPSegment(gfxCtx->polyXlu.p++, 9,
               Gfx_TwoTexScroll(ctxt->state.gfxCtx, 0, 0x7F - (frames & 0x7F), frames & 0x7F, 0x20, 0x20, 1,
                                frames & 0x7F, frames & 0x7F, 0x20, 0x20));
    gSPSegment(gfxCtx->polyOpa.p++, 10,
               Gfx_TwoTexScroll(ctxt->state.gfxCtx, 0, 0, 0, 0x20, 0x20, 1, 0, 0x7F - (frames & 0x7F), 0x20, 0x20));
    gSPSegment(gfxCtx->polyOpa.p++, 11, Rcp_GenerateSetTileSizeDl(ctxt->state.gfxCtx, 0, frames & 0x7F, 0x20, 0x20));
    gSPSegment(gfxCtx->polyXlu.p++, 12,
               Gfx_TwoTexScroll(ctxt->state.gfxCtx, 0, 0, frames * 0x32 & 0x7Ff, 8, 0x200, 1, 0, frames * 0x3c & 0x7Ff,
                                8, 0x200));
    gSPSegment(gfxCtx->polyOpa.p++, 13,
               Gfx_TwoTexScroll(ctxt->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, frames & 0x7F, 0x20, 0x20));

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x80, 0x80, 0x80, 0x80);

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x80, 0x80, 0x80, 0x80);
}
#else
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawSceneConfig3.asm")
#endif

void SceneProc_DrawSceneConfig4(GlobalContext* ctxt) {
    u32 frames;
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
    u32 frames2;

    frames = ctxt->unk18840;
    frames2 = frames * 1;

    gSPSegment(gfxCtx->polyXlu.p++, 8,
               Gfx_TwoTexScroll(ctxt->state.gfxCtx, 0, 0x7F - (frames & 0x7F), frames2 & 0x7F, 0x20, 0x20, 1,
                                (frames & 0x7F), frames2 & 0x7F, 0x20, 0x20));

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 128, 128, 128, 128);

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 128, 128, 128, 128);
}

void SceneProc_SceneDrawConfigDoNothing(GlobalContext* ctxt) {
}

Gfx D_801C3BF0[] = {
    gsSPEndDisplayList(),
    //! @bug These instructions will never get executed
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),
    gsSPEndDisplayList(),
};

static Gfx D_801C3C10[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1),
                      G_RM_AA_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
    //! @bug These instructions will never get executed
    gsDPSetRenderMode(AA_EN | Z_CMP | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA),
                      G_RM_AA_ZB_XLU_SURF2),
    gsSPEndDisplayList(),
};

static Gfx D_801C3C30[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c1(G_BL_CLR_IN, G_BL_0, G_BL_CLR_IN, G_BL_1),
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPEndDisplayList(),
    //! @bug These instructions will never get executed
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c1(G_BL_CLR_FOG, G_BL_A_SHADE, G_BL_CLR_IN, G_BL_1MA),
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsSPEndDisplayList(),
};

void func_80131DF0(GlobalContext* ctxt, u32 param_2, u32 flags) {
    static Gfx* D_801C3C50[] = {
        D_801C3BF0,
        D_801C3C10,
        D_801C3C30,
    };
    Gfx* dl = D_801C3C50[param_2];

    {
        GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
        if (flags & 1) {
            gSPSegment(gfxCtx->polyOpa.p++, 12, dl);
        }

        if (flags & 2) {
            gSPSegment(gfxCtx->polyXlu.p++, 12, dl);
        }
    }
}
static Gfx D_801C3C60[] = {
    gsSPSetGeometryMode(G_CULL_BACK),
    gsSPEndDisplayList(),
};
static Gfx D_801C3C70[] = {
    gsSPSetGeometryMode(G_CULL_FRONT),
    gsSPEndDisplayList(),
};
void func_80131E58(GlobalContext* ctxt, u32 param_2, u32 flags) {

    static Gfx* D_801C3C80[] = {
        D_801C3C60,
        D_801C3C70,
    };
    Gfx* dl = D_801C3C80[param_2];

    {
        GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
        if (flags & 1) {
            gSPSegment(gfxCtx->polyOpa.p++, 12, dl);
        }

        if (flags & 2) {
            gSPSegment(gfxCtx->polyXlu.p++, 12, dl);
        }
    }
}

void SceneProc_SceneDrawConfig5(GlobalContext* ctxt) {
    u32 dlIndex;
    u32 alpha;
    GraphicsContext* gfxCtx;

    if (ctxt->roomContext.unk7A[0] != 0) {
        dlIndex = 1;
        alpha = ctxt->roomContext.unk7A[1];
    } else {
        dlIndex = 0;
        alpha = 255;
    }

    if (alpha == 0) {
        ctxt->roomContext.unk78 = 0;
    } else {
        gfxCtx = ctxt->state.gfxCtx;

        ctxt->roomContext.unk78 = 1;

        SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);

        func_80131DF0(ctxt, dlIndex, 3);

        gDPSetEnvColor(gfxCtx->polyOpa.p++, 255, 255, 255, alpha);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 255, 255, 255, alpha);
    }
}

void SceneProc_SceneDrawConfigSakonsHideout(GlobalContext* ctxt) {
    SceneProc_DrawAllAnimatedTextures(ctxt, ctxt->sceneTextureAnimations, ctxt->roomContext.unk7A[0]);
}

void SceneProc_SceneDrawConfigGreatBayTemple(GlobalContext* ctxt) {
    static Gfx D_801C3C88[] = {
        gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
        gsSPEndDisplayList(),
    };
    s32 i;
    Gfx* dlHead;
    u32 pad1;
    u32 pad2;
    GraphicsContext* gfxCtx;
    u32 pad3;
    u32 pad4;
    u32 pad5;
    u32 pad6;
    Gfx* dl;

    if (Actor_GetSwitchFlag(ctxt, 0x33) && Actor_GetSwitchFlag(ctxt, 0x34) && Actor_GetSwitchFlag(ctxt, 0x35) &&
        Actor_GetSwitchFlag(ctxt, 0x36)) {
        func_800C3C00(&ctxt->colCtx, 1);
    } else {
        func_800C3C14(&ctxt->colCtx, 1);
    }

    {
        dl = (Gfx*)ctxt->state.gfxCtx->polyOpa.d - 18;
        // dl = _g;
        ctxt->state.gfxCtx->polyOpa.d = dl;
    }

    SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);

    gfxCtx = ctxt->state.gfxCtx;
    dlHead = dl;
    for (i = 0; i < 9; i++, dlHead += 2) {
        u32 lodFrac = 0;

        bcopy(D_801C3C88, dlHead, sizeof(Gfx[2]));

        switch (i) {
            case 0:
                if (Actor_GetSwitchFlag(ctxt, 0x33) && Actor_GetSwitchFlag(ctxt, 0x34) &&
                    Actor_GetSwitchFlag(ctxt, 0x35) && Actor_GetSwitchFlag(ctxt, 0x36)) {
                    lodFrac = 0xFF;
                }
                break;
            case 1:
                if (Actor_GetSwitchFlag(ctxt, 0x37)) {
                    lodFrac = 0x44;
                }
                break;
            case 2:
                if (Actor_GetSwitchFlag(ctxt, 0x37) && Actor_GetSwitchFlag(ctxt, 0x38)) {
                    lodFrac = 0x44;
                }
                break;
            case 3:
                if (Actor_GetSwitchFlag(ctxt, 0x37) && Actor_GetSwitchFlag(ctxt, 0x38) &&
                    Actor_GetSwitchFlag(ctxt, 0x39)) {
                    lodFrac = 0x44;
                }
                break;
            case 4:
                if (!Actor_GetSwitchFlag(ctxt, 0x33)) {
                    lodFrac = 0x44;
                }
                break;
            case 5:
                if (Actor_GetSwitchFlag(ctxt, 0x34)) {
                    lodFrac = 0x44;
                }
                break;
            case 6:
                if (Actor_GetSwitchFlag(ctxt, 0x34) && Actor_GetSwitchFlag(ctxt, 0x35)) {
                    lodFrac = 0x44;
                }
                break;
            case 7:
                if (Actor_GetSwitchFlag(ctxt, 0x34) && Actor_GetSwitchFlag(ctxt, 0x35) &&
                    Actor_GetSwitchFlag(ctxt, 0x36)) {
                    lodFrac = 0x44;
                }
                break;
            case 8:
                if (Actor_GetSwitchFlag(ctxt, 0x3A)) {
                    lodFrac = 0x44;
                }
                break;
        }

        gDPSetPrimColor(dlHead, 0, lodFrac, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    gSPSegment(gfxCtx->polyOpa.p++, 6, dl);
    gSPSegment(gfxCtx->polyXlu.p++, 6, dl);
}
