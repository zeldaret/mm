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
        SceneProc_SceneDrawConfigAnimatedMaterial,
        SceneProc_SceneDrawConfigDoNothing,
        SceneProc_DrawSceneConfig3, // unused
        SceneProc_DrawSceneConfig4, // unused
        SceneProc_SceneDrawConfig5, // unused
        SceneProc_SceneDrawConfigGreatBayTemple,
        SceneProc_SceneDrawConfigAnimatedMaterialManualStep,
    };

    sceneDrawConfigFuncs[globalCtx->sceneConfig](globalCtx);
}

/**
 * Scene Draw Config 0:
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
Gfx* SceneProc_SingleLayerTexScroll(GlobalContext* globalCtx, TextureScrollAnimParams* params) {
    return Gfx_TexScroll(globalCtx->state.gfxCtx, params->xStep * gSceneProcStep, -(params->yStep * gSceneProcStep),
                         params->width, params->height);
}

/**
 * Animated material type 0 : single layer texture scroll
 */
void SceneProc_DrawAnimatedMaterialTexScroll(GlobalContext* globalCtx, u32 segment, TextureScrollAnimParams* params) {
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
Gfx* SceneProc_TwoLayerTexScroll(GlobalContext* globalCtx, TextureScrollAnimParams* params) {
    return Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, params[0].xStep * gSceneProcStep,
                            -(params[0].yStep * gSceneProcStep), params[0].width, params[0].height, 1,
                            params[1].xStep * gSceneProcStep, -(params[1].yStep * gSceneProcStep), params[1].width,
                            params[1].height);
}

/**
 * Animated material type 1 : two layer texture scroll
 */
void SceneProc_DrawAnimatedMaterialTwoTexScroll(GlobalContext* globalCtx, u32 segment,
                                                TextureScrollAnimParams* params) {
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
    Gfx* colorDList = (Gfx*)GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(Gfx) * 4);

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

void SceneProc_DrawType2Texture(GlobalContext* ctxt, u32 segment, TextureColorAnimParams* params) {
    Color_RGBA8* envColor;
    SceneDrawPrimColor* primColor = (SceneDrawPrimColor*)Lib_SegmentedToVirtual(params->primColors);
    u32 pad;
    u32 index = gSceneProcStep % params->keyFrameLength;

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

void SceneProc_DrawType3Texture(GlobalContext* ctxt, u32 segment, TextureColorAnimParams* params);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawType3Texture.asm")

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

void SceneProc_DrawAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures, f32 flashingAlpha, u32 step,
                                    u32 flags) {
    static AnimatedTextureDrawFunc gSceneProcDrawFuncs[] = {
        SceneProc_DrawAnimatedMaterialTexScroll,
        SceneProc_DrawAnimatedMaterialTwoTexScroll,
        SceneProc_DrawType2Texture,
        SceneProc_DrawType3Texture,
        SceneProc_DrawType4Texture,
        SceneProc_DrawType5Texture,
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

void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 3);
}

void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 1);
}

void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 2);
}

void SceneProc_DrawAllSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures, f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 3);
}

void SceneProc_DrawOpaqueSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures, f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 1);
}

void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures,
                                                             f32 alpha) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, ctxt->unk18840, 2);
}

void SceneProc_DrawAllAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 3);
}

void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 1);
}

void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* ctxt, AnimatedMaterial* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 2);
}

void SceneProc_DrawAllAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures, f32 alpha, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 3);
}
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures, f32 alpha,
                                                   u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 1);
}
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedMaterial* textures, f32 alpha,
                                                        u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 2);
}

/**
 * Scene Draw Config 1:
 * Allows the usage of the animated material system in scenes
 */
void SceneProc_SceneDrawConfigAnimatedMaterial(GlobalContext* ctxt) {
    SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);
}

/**
 * Scene Draw Config 3:
 * Unused
 */
void SceneProc_DrawSceneConfig3(GlobalContext* ctxt);
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_scene_proc/SceneProc_DrawSceneConfig3.asm")

/**
 * Scene Draw Config 3:
 * Unused
 */
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

/**
 * Scene Draw Config 2:
 * Has no effect, and is only used in SPOT00 (cutscene map)
 */
void SceneProc_SceneDrawConfigDoNothing(GlobalContext* ctxt) {
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
 * rather than always animating like `SceneProc_SceneDrawConfigAnimatedMaterial`.
 */
void SceneProc_SceneDrawConfigAnimatedMaterialManualStep(GlobalContext* globalCtx) {
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
                    lodFrac = 0xFF;
                }
                break;
            case 1:
                if (Flags_GetSwitch(globalCtx, 0x37)) {
                    lodFrac = 0x44;
                }
                break;
            case 2:
                if (Flags_GetSwitch(globalCtx, 0x37) && Flags_GetSwitch(globalCtx, 0x38)) {
                    lodFrac = 0x44;
                }
                break;
            case 3:
                if (Flags_GetSwitch(globalCtx, 0x37) && Flags_GetSwitch(globalCtx, 0x38) &&
                    Flags_GetSwitch(globalCtx, 0x39)) {
                    lodFrac = 0x44;
                }
                break;
            case 4:
                if (!(Flags_GetSwitch(globalCtx, 0x33))) {
                    lodFrac = 0x44;
                }
                break;
            case 5:
                if (Flags_GetSwitch(globalCtx, 0x34)) {
                    lodFrac = 0x44;
                }
                break;
            case 6:
                if (Flags_GetSwitch(globalCtx, 0x34) && Flags_GetSwitch(globalCtx, 0x35)) {
                    lodFrac = 0x44;
                }
                break;
            case 7:
                if (Flags_GetSwitch(globalCtx, 0x34) && Flags_GetSwitch(globalCtx, 0x35) &&
                    Flags_GetSwitch(globalCtx, 0x36)) {
                    lodFrac = 0x44;
                }
                break;
            case 8:
                if (Flags_GetSwitch(globalCtx, 0x3A)) {
                    lodFrac = 0x44;
                }
                break;
        }

        gDPSetPrimColor(dListHead, 0, lodFrac, 255, 255, 255, 255);
    }

    gSPSegment(POLY_OPA_DISP++, 0x06, dList);
    gSPSegment(POLY_XLU_DISP++, 0x06, dList);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
