#include <ultra64.h>
#include <global.h>

void SceneProc_DrawCurrentSceneAnimatedTextures(GlobalContext* ctxt) {
    gSceneProcSceneDrawFuncs[ctxt->sceneConfig](ctxt);
}

void SceneProc_DrawSceneConfig0(GlobalContext* ctxt) {
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;

    gSPDisplayList(gfxCtx->polyOpa.p++, gSceneProcDefaultDl);
    gSPDisplayList(gfxCtx->polyXlu.p++, gSceneProcDefaultDl);
}

Gfx* SceneProc_SetTile1Layer(GlobalContext* ctxt, ScrollingTextureParams* params) {
    return Rcp_GenerateSetTileSizeDl((ctxt->state).gfxCtx,
                                     params->xStep * gSceneProcStep,
                                     -(params->yStep * gSceneProcStep),
                                     params->width,
                                     params->height);
}

void SceneProc_DrawType0Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params) {
    Gfx* dl = SceneProc_SetTile1Layer(ctxt, params);

    {
        GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
        if (gSceneProcFlags & 1) {
            gSPSegment(gfxCtx->polyOpa.p++, segment, dl);
        }

        if (gSceneProcFlags & 2) {
            gSPSegment(gfxCtx->polyXlu.p++, segment, dl);
        }
    }
}

Gfx* SceneProc_SetTile2Layers(GlobalContext* ctxt, ScrollingTextureParams* params) {
    return Rcp_GenerateSetTileSize2Dl((ctxt->state).gfxCtx,
                                      0,
                                      params[0].xStep * gSceneProcStep,
                                      -(params[0].yStep * gSceneProcStep),
                                      params[0].width,
                                      params[0].height,
                                      1,
                                      params[1].xStep * gSceneProcStep,
                                      -(params[1].yStep * gSceneProcStep),
                                      params[1].width,
                                      params[1].height);
}

void SceneProc_DrawType1Texture(GlobalContext* ctxt, u32 segment, ScrollingTextureParams* params) {
    Gfx* dl = SceneProc_SetTile2Layers(ctxt, params);

    {
        GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
        if (gSceneProcFlags & 1) {
            gSPSegment(gfxCtx->polyOpa.p++, segment, dl);
        }

        if (gSceneProcFlags & 2) {
            gSPSegment(gfxCtx->polyXlu.p++, segment, dl);
        }
    }
}

#ifdef NON_MATCHING
// Slight ordering differences at the beginning
void SceneProc_DrawFlashingTexture(GlobalContext* ctxt, u32 segment, FlashingTexturePrimColor* primColor, RGBA8* envColor) {
    GraphicsContext* gfxCtx;
    Gfx* dl;

    {
        Gfx* _g = (Gfx*)ctxt->state.gfxCtx->polyOpa.d - 4;
        dl = _g;
        ctxt->state.gfxCtx->polyOpa.d = _g;
    }

    gfxCtx = ctxt->state.gfxCtx;
    if (gSceneProcFlags & 1) {
        gSPSegment(gfxCtx->polyOpa.p++, segment, dl);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(gfxCtx->polyXlu.p++, segment, dl);
    }

    gDPSetPrimColor(dl++,
                    0,
                    primColor->lodFrac,
                    primColor->red,
                    primColor->green,
                    primColor->blue,
                    (u8)(primColor->alpha * gSceneProcFlashingAlpha));

    if (envColor != NULL) {
        gDPSetEnvColor(dl++,
                       envColor->red,
                       envColor->green,
                       envColor->blue,
                       envColor->alpha);
    }

    gSPEndDisplayList(dl++);
}
#else
GLOBAL_ASM("./asm/non_matchings/z_scene_proc/SceneProc_DrawFlashingTexture.asm")
#endif

void SceneProc_DrawType2Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params) {
    RGBA8* envColor;
    FlashingTexturePrimColor* primColor = (FlashingTexturePrimColor *)Lib_PtrSegToVirt(params->primColors);
    u32 pad;
    u32 index = gSceneProcStep % params->cycleLength;

    primColor += index;

    if (params->envColors) {
        envColor = (RGBA8*)Lib_PtrSegToVirt(params->envColors) + index;
    } else {
        envColor = NULL;
    }

    SceneProc_DrawFlashingTexture(ctxt, segment, primColor, envColor);
}

s32 SceneProc_Lerp(s32 a, s32 b, f32 t) {
    return (s32)((b - a) * t) + a;
}

#ifdef NON_MATCHING
// Slight ordering and regalloc differences around t = ...
void SceneProc_DrawType3Texture(GlobalContext* ctxt, u32 segment, FlashingTextureParams* params) {
    FlashingTextureParams* params2 = params;
    RGBA8* envColorTo;
    FlashingTexturePrimColor* primColorTo = (FlashingTexturePrimColor *)Lib_PtrSegToVirt(params2->primColors);
    u16* keyFrames = (u16*)Lib_PtrSegToVirt(params2->keyFrames);
    s32 index = gSceneProcStep % params2->cycleLength;
    s32 pad1;
    s32 keyFrameIndex;
    RGBA8* envColorPtrIn;
    f32 t;
    s32 pad2;
    FlashingTexturePrimColor primColorIn;
    RGBA8* envColorFrom;
    RGBA8 envColorIn;
    s32 pad3;
    FlashingTexturePrimColor* primColorFrom;

    keyFrameIndex = 1;
    keyFrames += 1;
    while (params2->numKeyFrames > keyFrameIndex) {
        if (index < *keyFrames) break;
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
        envColorTo = (RGBA8*)Lib_PtrSegToVirt(params2->envColors) + keyFrameIndex;
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

    SceneProc_DrawFlashingTexture(ctxt, segment, &primColorIn, envColorPtrIn);
}
#else
GLOBAL_ASM("./asm/non_matchings/z_scene_proc/SceneProc_DrawType3Texture.asm")
#endif

GLOBAL_ASM("./asm/non_matchings/z_scene_proc/SceneProc_Interpolate.asm")

u8 SceneProc_InterpolateClamped(u32 numKeyFrames, f32* keyFrames, f32* values, f32 frame) {
    s32 ret = SceneProc_Interpolate(numKeyFrames, keyFrames, values, frame);

    return (ret < 0)   ? 0    :
           (ret > 0xFF)? 0xFF :
                         ret;
}

GLOBAL_ASM("./asm/non_matchings/z_scene_proc/SceneProc_DrawType4Texture.asm")

void SceneProc_DrawType5Texture(GlobalContext* ctxt, u32 segment, CyclingTextureParams* params) {
    u8* offsets;
    Gfx** dls;
    Gfx* dl;
    GraphicsContext* gfxCtx;
    s32 step;

    dls = (Gfx**)Lib_PtrSegToVirt(params->textureDls);
    offsets = (u8*)Lib_PtrSegToVirt(params->textureDlOffsets);
    step = gSceneProcStep % params->cycleLength;
    dl = (Gfx*)Lib_PtrSegToVirt(dls[offsets[step]]);

    gfxCtx = ctxt->state.gfxCtx;
    if (gSceneProcFlags & 1) {
        gSPSegment(gfxCtx->polyOpa.p++, segment, dl);
    }

    if (gSceneProcFlags & 2) {
        gSPSegment(gfxCtx->polyXlu.p++, segment, dl);
    }
}


void SceneProc_DrawAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, f32 flashingAlpha, u32 step, u32 flags) {
    s32 segmentAbs;
    s32 segment;

    gSceneProcFlashingAlpha = flashingAlpha;
    gSceneProcStep = step;
    gSceneProcFlags = flags;

    if ((textures != NULL) && (textures->segment != 0)) {
        do {
            segment = textures->segment;
            segmentAbs = ((segment < 0)? -segment : segment) + 7;

            gSceneProcDrawFuncs[textures->type](ctxt, segmentAbs, (void*)Lib_PtrSegToVirt(textures->params));

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

void SceneProc_DrawTranslucentSceneAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha) {
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
void SceneProc_DrawOpaqueAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 1);
}
void SceneProc_DrawTranslucentAnimatedTexturesWithAlpha(GlobalContext* ctxt, AnimatedTexture* textures, f32 alpha, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, alpha, step, 2);
}

void SceneProc_DrawSceneConfig1(GlobalContext* ctxt) {
  SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);
}

#ifdef NON_MATCHING
// This function still needs a lot of work
void SceneProc_DrawSceneConfig3(GlobalContext* ctxt) {
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
    u32 frames = ctxt->unk18840;

    if (0);

    gSPSegment(gfxCtx->polyXlu.p++, 8,
               Rcp_GenerateSetTileSizeDl(ctxt->state.gfxCtx, 0, frames & 0x3f, 0x100, 0x10));
    gSPSegment(gfxCtx->polyXlu.p++, 9,
               Rcp_GenerateSetTileSize2Dl(ctxt->state.gfxCtx,
                                          0, 0x7F - (frames & 0x7F), frames & 0x7F, 0x20, 0x20,
                                          1, frames & 0x7F, frames & 0x7F, 0x20, 0x20));
    gSPSegment(gfxCtx->polyOpa.p++, 10,
               Rcp_GenerateSetTileSize2Dl(ctxt->state.gfxCtx,
                                          0, 0, 0, 0x20, 0x20,
                                          1, 0, 0x7F - (frames & 0x7F), 0x20, 0x20));
    gSPSegment(gfxCtx->polyOpa.p++, 11,
               Rcp_GenerateSetTileSizeDl(ctxt->state.gfxCtx, 0, frames & 0x7F, 0x20, 0x20));
    gSPSegment(gfxCtx->polyXlu.p++, 12,
               Rcp_GenerateSetTileSize2Dl(ctxt->state.gfxCtx,
                                          0, 0, frames * 0x32 & 0x7Ff, 8, 0x200,
                                          1, 0, frames * 0x3c & 0x7Ff, 8, 0x200));
    gSPSegment(gfxCtx->polyOpa.p++, 13,
               Rcp_GenerateSetTileSize2Dl(ctxt->state.gfxCtx,
                                          0, 0, 0, 0x20, 0x40,
                                          1, 0, frames & 0x7F, 0x20, 0x20));

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x80, 0x80, 0x80, 0x80);

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x80, 0x80, 0x80, 0x80);
}
#else
GLOBAL_ASM("./asm/non_matchings/z_scene_proc/SceneProc_DrawSceneConfig3.asm")
#endif

void SceneProc_DrawSceneConfig4(GlobalContext* ctxt) {
    u32 frames;
    GraphicsContext* gfxCtx = ctxt->state.gfxCtx;
    u32 frames2;

    frames = ctxt->unk18840;
    frames2 = frames * 1;

    gSPSegment(gfxCtx->polyXlu.p++, 8,
               Rcp_GenerateSetTileSize2Dl(ctxt->state.gfxCtx,
                                          0, 0x7F - (frames & 0x7F), frames2 & 0x7F, 0x20, 0x20,
                                          1, (frames & 0x7F), frames2 & 0x7F, 0x20, 0x20));

    gDPPipeSync(gfxCtx->polyOpa.p++);
    gDPSetEnvColor(gfxCtx->polyOpa.p++, 0x80, 0x80, 0x80, 0x80);

    gDPPipeSync(gfxCtx->polyXlu.p++);
    gDPSetEnvColor(gfxCtx->polyXlu.p++, 0x80, 0x80, 0x80, 0x80);
}

void SceneProc_DrawSceneConfig2(GlobalContext* ctxt){}

void func_80131DF0(GlobalContext* ctxt, u32 param_2, u32 flags) {
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

void func_80131E58(GlobalContext* ctxt, u32 param_2, u32 flags) {
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

void SceneProc_DrawSceneConfig5(GlobalContext* ctxt) {
    u32 dlIndex;
    u32 alpha;
    GraphicsContext* gfxCtx;

    if (ctxt->roomContext.unk7A[0] != 0) {
        dlIndex = 1;
        alpha = ctxt->roomContext.unk7A[1];
    } else {
        dlIndex = 0;
        alpha = 0xff;
    }

    if (alpha == 0) {
        ctxt->roomContext.unk78 = 0;
    } else {
        gfxCtx = ctxt->state.gfxCtx;

        ctxt->roomContext.unk78 = 1;

        SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);

        func_80131DF0(ctxt, dlIndex, 3);

        gDPSetEnvColor(gfxCtx->polyOpa.p++, 0xFF, 0xFF, 0xFF, alpha);
        gDPSetEnvColor(gfxCtx->polyXlu.p++, 0xFF, 0xFF, 0xFF, alpha);
    }
}

void SceneProc_DrawSceneConfig7(GlobalContext* ctxt) {
      SceneProc_DrawAllAnimatedTextures(ctxt, ctxt->sceneTextureAnimations, ctxt->roomContext.unk7A[0]);
}

void SceneProc_DrawSceneConfig6(GlobalContext* ctxt) {
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

    if (Actor_GetSwitchFlag(ctxt,0x33) &&
        Actor_GetSwitchFlag(ctxt,0x34) &&
        Actor_GetSwitchFlag(ctxt,0x35) &&
        Actor_GetSwitchFlag(ctxt,0x36)) {
        func_800C3C00(&ctxt->colCtx, 1);
    } else {
        func_800C3C14(&ctxt->colCtx, 1);
    }

    {
        dl = (Gfx*)ctxt->state.gfxCtx->polyOpa.d - 18;
        //dl = _g;
        ctxt->state.gfxCtx->polyOpa.d = dl;
    }

    SceneProc_DrawAllSceneAnimatedTextures(ctxt, ctxt->sceneTextureAnimations);

    gfxCtx = ctxt->state.gfxCtx;
    dlHead = dl;
    for (i = 0; i < 9; i++, dlHead += 2) {
        u32 lodFrac = 0;

        _bcopy(D_801C3C88, dlHead, sizeof(Gfx[2]));

        switch(i) {
        case 0:
            if (Actor_GetSwitchFlag(ctxt,0x33) &&
                Actor_GetSwitchFlag(ctxt,0x34) &&
                Actor_GetSwitchFlag(ctxt,0x35) &&
                Actor_GetSwitchFlag(ctxt,0x36)) {
                lodFrac = 0xFF;
            }
            break;
        case 1:
            if (Actor_GetSwitchFlag(ctxt,0x37)) {
                lodFrac = 0x44;
            }
            break;
        case 2:
            if (Actor_GetSwitchFlag(ctxt,0x37) &&
                Actor_GetSwitchFlag(ctxt,0x38)) {
                lodFrac = 0x44;
            }
            break;
        case 3:
            if (Actor_GetSwitchFlag(ctxt,0x37) &&
                Actor_GetSwitchFlag(ctxt,0x38) &&
                Actor_GetSwitchFlag(ctxt,0x39)) {
                lodFrac = 0x44;
            }
            break;
        case 4:
            if (!Actor_GetSwitchFlag(ctxt,0x33)) {
                lodFrac = 0x44;
            }
            break;
        case 5:
            if (Actor_GetSwitchFlag(ctxt,0x34)) {
                lodFrac = 0x44;
            }
            break;
        case 6:
            if (Actor_GetSwitchFlag(ctxt,0x34) &&
                Actor_GetSwitchFlag(ctxt,0x35)) {
                lodFrac = 0x44;
            }
            break;
        case 7:
            if (Actor_GetSwitchFlag(ctxt,0x34) &&
                Actor_GetSwitchFlag(ctxt,0x35) &&
                Actor_GetSwitchFlag(ctxt,0x36)) {
                lodFrac = 0x44;
            }
            break;
        case 8:
            if (Actor_GetSwitchFlag(ctxt,0x3A)) {
                lodFrac = 0x44;
            }
            break;
        }

        gDPSetPrimColor(dlHead, 0, lodFrac, 0xFF, 0xFF, 0xFF, 0xFF);
    }

    gSPSegment(gfxCtx->polyOpa.p++, 6, dl);
    gSPSegment(gfxCtx->polyXlu.p++, 6, dl);
}
