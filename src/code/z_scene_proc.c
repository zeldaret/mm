#include <ultra64.h>
#include <global.h>

// Default displaylist that sets a valid displaylist into all of the segments.
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
 * Executes the current scene draw config function.
 */
void SceneProc_ExecuteSceneDrawConfig(GlobalContext* globalCtx) {
    static SceneDrawConfigFunc sceneDrawConfigFuncs[] = {
        SceneProc_SceneDrawConfigDefault,
        SceneProc_SceneDrawConfigMatAnim,
        SceneProc_SceneDrawConfigDoNothing,
        SceneProc_DrawSceneConfig3, // unused
        SceneProc_DrawSceneConfig4, // unused
        SceneProc_SceneDrawConfig5, // unused
        SceneProc_SceneDrawConfigGreatBayTemple,
        SceneProc_SceneDrawConfigMatAnimManualStep,
    };

    sceneDrawConfigFuncs[globalCtx->sceneConfig](globalCtx);
}

/**
 * Scene Draw Config 0:
 * Default scene draw config function. This just executes `sSceneDrawDefaultDl`.
 */
void SceneProc_SceneDrawConfigDefault(GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);

    gSPDisplayList(POLY_OPA_DISP++, sSceneDrawDefaultDl);
    gSPDisplayList(POLY_XLU_DISP++, sSceneDrawDefaultDl);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Returns a pointer to a single layer texture scroll displaylist.
 */
Gfx* SceneProc_SingleLayerTexScroll(GlobalContext* globalCtx, MaterialTexScrollAnimParams* params) {
    return Gfx_TexScroll(globalCtx->state.gfxCtx, params->xStep * gSceneProcStep, -(params->yStep * gSceneProcStep),
                         params->width, params->height);
}

/**
 * Animated Material Type 0:
 * Scrolls a single layer texture using the provided `MaterialTexScrollAnimParams`.
 */
void SceneProc_DrawMatAnimTexScroll(GlobalContext* globalCtx, u32 segment, MaterialTexScrollAnimParams* params) {
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
 * Returns a pointer to a two layer texture scroll displaylist.
 */
Gfx* SceneProc_TwoLayerTexScroll(GlobalContext* globalCtx, MaterialTexScrollAnimParams* params) {
    return Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, params[0].xStep * gSceneProcStep,
                            -(params[0].yStep * gSceneProcStep), params[0].width, params[0].height, 1,
                            params[1].xStep * gSceneProcStep, -(params[1].yStep * gSceneProcStep), params[1].width,
                            params[1].height);
}

/**
 * Animated Material Type 1:
 * Scrolls a two layer texture using the provided `MaterialTexScrollAnimParams`.
 */
void SceneProc_DrawMatAnimTwoTexScroll(GlobalContext* globalCtx, u32 segment, MaterialTexScrollAnimParams* params) {
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
 * Generates a displaylist that sets the prim and env color, and stores it in the provided segment ID.
 */
void SceneProc_SetColor(GlobalContext* globalCtx, u32 segment, F3DPrimColor* primColorResult, F3DEnvColor* envColor) {
    Gfx* colorDList = (Gfx*)GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 4);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    // clang-format off
    if (gSceneProcFlags & 1) { gSPSegment(POLY_OPA_DISP++, segment, colorDList); }
    if (gSceneProcFlags & 2) { gSPSegment(POLY_XLU_DISP++, segment, colorDList); }
    // clang-format on

    gDPSetPrimColor(colorDList++, 0, primColorResult->lodFrac, primColorResult->r, primColorResult->g,
                    primColorResult->b, (u8)(primColorResult->a * gSceneProcFlashingAlpha));

    if (envColor != NULL) {
        gDPSetEnvColor(colorDList++, envColor->r, envColor->g, envColor->b, envColor->a);
    }

    gSPEndDisplayList(colorDList++);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * Animated Material Type 2:
 * Color key frame animation without linear interpolation.
 */
void SceneProc_DrawMatAnimColor(GlobalContext* globalCtx, u32 segment, void* params) {
    MaterialColorAnimParams* colorAnimParams = (MaterialColorAnimParams*)params;
    F3DPrimColor* primColor;
    F3DEnvColor* envColor;
    s32 curFrame;

    primColor = (F3DPrimColor*)Lib_SegmentedToVirtual(colorAnimParams->primColors);

    curFrame = gSceneProcStep % colorAnimParams->keyFrameLength;
    primColor += curFrame;
    envColor = (colorAnimParams->envColors != NULL)
                   ? (F3DEnvColor*)Lib_SegmentedToVirtual(colorAnimParams->envColors) + curFrame
                   : NULL;

    SceneProc_SetColor(globalCtx, segment, primColor, envColor);
}

/**
 * Linear Interpolation
 */
s32 SceneProc_Lerp(s32 min, s32 max, f32 norm) {
    return (s32)((max - min) * norm) + min;
}

/**
 * Animated Material Type 3:
 * Color key frame animation with linear interpolation.
 */
void SceneProc_DrawMatAnimColorLerp(GlobalContext* globalCtx, u32 segment, void* params) {
    MaterialColorAnimParams* colorAnimParams = (MaterialColorAnimParams*)params;
    F3DPrimColor* primColorMax;
    F3DEnvColor* envColorMax;
    u16* keyFrames;
    s32 curFrame;
    s32 endFrame;
    s32 relativeFrame; // relative to the start frame
    s32 startFrame;
    f32 norm;
    F3DPrimColor* primColorMin;
    F3DPrimColor primColorResult;
    F3DEnvColor* envColorMin;
    F3DEnvColor envColorResult;
    s32 i;

    primColorMax = (F3DPrimColor*)Lib_SegmentedToVirtual(colorAnimParams->primColors);
    keyFrames = (u16*)Lib_SegmentedToVirtual(colorAnimParams->keyFrames);
    curFrame = gSceneProcStep % colorAnimParams->keyFrameLength;
    keyFrames++;
    i = 1;

    while (colorAnimParams->keyFrameCount > i) {
        if (curFrame < *keyFrames) {
            break;
        }
        i++;
        keyFrames++;
    }

    startFrame = keyFrames[-1];
    endFrame = keyFrames[0] - startFrame;
    relativeFrame = curFrame - startFrame;
    norm = (f32)relativeFrame / (f32)endFrame;

    primColorMax += i;
    primColorMin = primColorMax - 1;
    primColorResult.r = SceneProc_Lerp(primColorMin->r, primColorMax->r, norm);
    primColorResult.g = SceneProc_Lerp(primColorMin->g, primColorMax->g, norm);
    primColorResult.b = SceneProc_Lerp(primColorMin->b, primColorMax->b, norm);
    primColorResult.a = SceneProc_Lerp(primColorMin->a, primColorMax->a, norm);
    primColorResult.lodFrac = SceneProc_Lerp(primColorMin->lodFrac, primColorMax->lodFrac, norm);

    if (colorAnimParams->envColors) {
        envColorMax = (F3DEnvColor*)Lib_SegmentedToVirtual(colorAnimParams->envColors);
        envColorMax += i;
        envColorMin = envColorMax - 1;
        envColorResult.r = SceneProc_Lerp(envColorMin->r, envColorMax->r, norm);
        envColorResult.g = SceneProc_Lerp(envColorMin->g, envColorMax->g, norm);
        envColorResult.b = SceneProc_Lerp(envColorMin->b, envColorMax->b, norm);
        envColorResult.a = SceneProc_Lerp(envColorMin->a, envColorMax->a, norm);
    } else {
        envColorMax = NULL;
    }

    SceneProc_SetColor(globalCtx, segment, &primColorResult, (envColorMax != NULL) ? &envColorResult : NULL);
}

/**
 * Lagrange interpolation
 */
f32 SceneProc_LagrangeInterp(s32 n, f32 x[], f32 fx[], f32 xp) {
    f32 weights[50];
    f32 xVal;
    f32 m;
    f32 intp;
    f32* xPtr1;
    f32* fxPtr;
    f32* weightsPtr;
    f32* xPtr2;
    s32 i;
    s32 j;

    for (i = 0, weightsPtr = weights, xPtr1 = x, fxPtr = fx, weightsPtr = weightsPtr; i < n; i++) {
        for (xVal = *xPtr1, m = 1.0f, j = 0, xPtr2 = x; j < n; j++) {
            if (j != i) {
                m *= xVal - (*xPtr2);
            }
            xPtr2++;
        }

        xPtr1++;
        *weightsPtr = (*fxPtr) / m;
        fxPtr++;
        weightsPtr++;
    }

    for (intp = 0.0f, i = 0, weightsPtr = weights; i < n; i++) {
        for (m = 1.0f, j = 0, xPtr2 = x; j < n; j++) {
            if (j != i) {
                m *= xp - (*xPtr2);
            }
            xPtr2++;
        }

        intp += (*weightsPtr) * m;
        weightsPtr++;
    }

    return intp;
}

/**
 * Lagrange interpolation specifically for colors
 */
u8 SceneProc_LagrangeInterpColor(s32 n, f32 x[], f32 fx[], f32 xp) {
    s32 intp = SceneProc_LagrangeInterp(n, x, fx, xp);

    return (intp < 0) ? 0 : (intp > 255) ? 255 : intp;
}

//! @TODO
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawType4Texture.asm")

/**
 * Animated Material Type 5:
 * Cycles between a list of textures (imagine like a GIF)
 */
void SceneProc_DrawMatAnimTexCycle(GlobalContext* globalCtx, u32 segment, void* params) {
    MaterialTexCycleAnimParams* texAnimParams = params;
    void** texList = (void**)Lib_SegmentedToVirtual(texAnimParams->textureList);
    u8* texId = (u8*)Lib_SegmentedToVirtual(texAnimParams->textureIndexList);
    s32 curFrame = gSceneProcStep % texAnimParams->keyFrameLength;
    void* tex = Lib_SegmentedToVirtual(texList[texId[curFrame]]);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (gSceneProcFlags & 1) {
        gSPSegment(POLY_OPA_DISP++, segment, tex);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(POLY_XLU_DISP++, segment, tex);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

/**
 * This is the main function that handles the animated material system.
 * There are six different animated material types, which should be set in the provided `MaterialAnimation`.
 */
void SceneProc_DrawMaterialAnimation(GlobalContext* globalCtx, MaterialAnimation* animatedMat, f32 flashingAlpha,
                                     u32 step, u32 flags) {
    static MaterialAnimationDrawFunc gSceneProcDrawFuncs[] = {
        SceneProc_DrawMatAnimTexScroll, SceneProc_DrawMatAnimTwoTexScroll, SceneProc_DrawMatAnimColor,
        SceneProc_DrawMatAnimColorLerp, SceneProc_DrawType4Texture,        SceneProc_DrawMatAnimTexCycle,
    };
    s32 segmentAbs;
    s32 segment;

    gSceneProcFlashingAlpha = flashingAlpha;
    gSceneProcStep = step;
    gSceneProcFlags = flags;

    if ((animatedMat != NULL) && (animatedMat->segment != 0)) {
        do {
            segment = animatedMat->segment;
            segmentAbs = ((segment < 0) ? -segment : segment) + 7;
            gSceneProcDrawFuncs[animatedMat->type](globalCtx, segmentAbs,
                                                   (void*)Lib_SegmentedToVirtual(animatedMat->params));
            animatedMat++;
        } while (segment > -1);
    }
}

//! @TODO
void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, globalCtx->unk18840, 3);
}

//! @TODO
void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, globalCtx->unk18840, 1);
}

//! @TODO
void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, globalCtx->unk18840, 2);
}

//! @TODO
void SceneProc_DrawAllSceneAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures, f32 alpha) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, globalCtx->unk18840, 3);
}

//! @TODO
void SceneProc_DrawOpaqueSceneAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures,
                                                        f32 alpha) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, globalCtx->unk18840, 1);
}

//! @TODO
void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures,
                                                             f32 alpha) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, globalCtx->unk18840, 2);
}

//! @TODO
void SceneProc_DrawAllAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures, u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, step, 3);
}

//! @TODO
void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures, u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, step, 1);
}

//! @TODO
void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* globalCtx, MaterialAnimation* textures, u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, 1, step, 2);
}

//! @TODO
void SceneProc_DrawAllAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures, f32 alpha,
                                                u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, step, 3);
}

//! @TODO
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures, f32 alpha,
                                                   u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, step, 1);
}

//! @TODO
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* globalCtx, MaterialAnimation* textures,
                                                        f32 alpha, u32 step) {
    SceneProc_DrawMaterialAnimation(globalCtx, textures, alpha, step, 2);
}

/**
 * Scene Draw Config 1:
 * Allows the usage of the animated material system in scenes.
 */
void SceneProc_SceneDrawConfigMatAnim(GlobalContext* globalCtx) {
    SceneProc_DrawAllSceneAnimatedTextures(globalCtx, globalCtx->sceneTextureAnimations);
}

//! @TODO
/**
 * Scene Draw Config 3:
 * Unused.
 */
void SceneProc_DrawSceneConfig3(GlobalContext* globalCtx);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawSceneConfig3.asm")

//! @TODO use DISP macros for this!
/**
 * Scene Draw Config 4:
 * This config is unused and just has a single TwoTexScroll intended for two 32x32 textures, possibly a carryover from
 * Ocarina of Time.
 */
void SceneProc_DrawSceneConfig4(GlobalContext* globalCtx) {
    u32 frames;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    u32 frames2;

    frames = globalCtx->unk18840;
    frames2 = frames * 1;

    gSPSegment(gfxCtx->polyXlu.p++, 8,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0x7F - (frames & 0x7F), frames2 & 0x7F, 32, 32, 1,
                                (frames & 0x7F), frames2 & 0x7F, 32, 32));

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 128, 128, 128, 128);

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 128, 128, 128, 128);
}

/**
 * Scene Draw Config 2:
 * Has no effect, and is only used in SPOT00 (cutscene map).
 */
void SceneProc_SceneDrawConfigDoNothing(GlobalContext* globalCtx) {
}

static Gfx D_801C3BF0[] = {
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

//! @TODO
void func_80131DF0(GlobalContext* globalCtx, u32 param_2, u32 flags) {
    static Gfx* D_801C3C50[] = {
        D_801C3BF0,
        D_801C3C10,
        D_801C3C30,
    };
    Gfx* dl = D_801C3C50[param_2];

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
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

//! @TODO
void func_80131E58(GlobalContext* globalCtx, u32 param_2, u32 flags) {
    static Gfx* D_801C3C80[] = {
        D_801C3C60,
        D_801C3C70,
    };
    Gfx* dl = D_801C3C80[param_2];

    {
        GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
        if (flags & 1) {
            gSPSegment(gfxCtx->polyOpa.p++, 12, dl);
        }

        if (flags & 2) {
            gSPSegment(gfxCtx->polyXlu.p++, 12, dl);
        }
    }
}

/**
 * Scene Draw Config 5:
 * This config is unused, and its purpose is unknown.
 */
void SceneProc_SceneDrawConfig5(GlobalContext* globalCtx) {
    u32 dListIndex;
    u32 alpha;

    if (globalCtx->roomContext.unk7A[0] != 0) {
        dListIndex = 1;
        alpha = globalCtx->roomContext.unk7A[1];
    } else {
        dListIndex = 0;
        alpha = 255;
    }

    if (alpha == 0) {
        globalCtx->roomContext.unk78 = 0;
    } else {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        globalCtx->roomContext.unk78 = 1;
        SceneProc_DrawAllSceneAnimatedTextures(globalCtx, globalCtx->sceneTextureAnimations);
        func_80131DF0(globalCtx, dListIndex, 3);
        gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, alpha);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

/**
 * Scene Draw Config 7:
 * This is a special draw config for Sakon's Hideout, as well as the Music Box House. Its step value is set manually
 * rather than always animating like `SceneProc_SceneDrawConfigMatAnim`.
 */
void SceneProc_SceneDrawConfigMatAnimManualStep(GlobalContext* globalCtx) {
    SceneProc_DrawAllAnimatedTextures(globalCtx, globalCtx->sceneTextureAnimations, globalCtx->roomContext.unk7A[0]);
}

/**
 * Scene Draw Config 6:
 * This is a special draw config for Great Bay Temple, which handles both material animations as well as setting the lod
 * fraction to a certain value when certain flags are set, which are likely used for the pipes whenever they are
 * activated.
 */
void SceneProc_SceneDrawConfigGreatBayTemple(GlobalContext* globalCtx) {
    static Gfx greatBayTempleColorSetDL[] = {
        gsDPSetPrimColor(0, 255, 255, 255, 255, 255),
        gsSPEndDisplayList(),
    };
    s32 lodFrac;
    s32 i;
    Gfx* dListHead;
    Gfx* dList;

    if (Flags_GetSwitch(globalCtx, 0x33) && Flags_GetSwitch(globalCtx, 0x34) && Flags_GetSwitch(globalCtx, 0x35) &&
        Flags_GetSwitch(globalCtx, 0x36)) {
        func_800C3C00(&globalCtx->colCtx, 1);
    } else {
        func_800C3C14(&globalCtx->colCtx, 1);
    }

    dList = (Gfx*)GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 18);

    SceneProc_DrawAllSceneAnimatedTextures(globalCtx, globalCtx->sceneTextureAnimations);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    for (dListHead = dList, i = 0; i < 9; i++, dListHead += 2) {
        lodFrac = 0;

        bcopy(greatBayTempleColorSetDL, dListHead, sizeof(greatBayTempleColorSetDL));

        switch (i) {
            case 0:
                if (Flags_GetSwitch(globalCtx, 0x33) && Flags_GetSwitch(globalCtx, 0x34) &&
                    Flags_GetSwitch(globalCtx, 0x35) && Flags_GetSwitch(globalCtx, 0x36)) {
                    lodFrac = 255;
                }
                break;
            case 1:
                if (Flags_GetSwitch(globalCtx, 0x37)) {
                    lodFrac = 68;
                }
                break;
            case 2:
                if (Flags_GetSwitch(globalCtx, 0x37) && Flags_GetSwitch(globalCtx, 0x38)) {
                    lodFrac = 68;
                }
                break;
            case 3:
                if (Flags_GetSwitch(globalCtx, 0x37) && Flags_GetSwitch(globalCtx, 0x38) &&
                    Flags_GetSwitch(globalCtx, 0x39)) {
                    lodFrac = 68;
                }
                break;
            case 4:
                if (!(Flags_GetSwitch(globalCtx, 0x33))) {
                    lodFrac = 68;
                }
                break;
            case 5:
                if (Flags_GetSwitch(globalCtx, 0x34)) {
                    lodFrac = 68;
                }
                break;
            case 6:
                if (Flags_GetSwitch(globalCtx, 0x34) && Flags_GetSwitch(globalCtx, 0x35)) {
                    lodFrac = 68;
                }
                break;
            case 7:
                if (Flags_GetSwitch(globalCtx, 0x34) && Flags_GetSwitch(globalCtx, 0x35) &&
                    Flags_GetSwitch(globalCtx, 0x36)) {
                    lodFrac = 68;
                }
                break;
            case 8:
                if (Flags_GetSwitch(globalCtx, 0x3A)) {
                    lodFrac = 68;
                }
                break;
        }

        gDPSetPrimColor(dListHead, 0, lodFrac, 255, 255, 255, 255);
    }

    gSPSegment(POLY_OPA_DISP++, 0x06, dList);
    gSPSegment(POLY_XLU_DISP++, 0x06, dList);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
