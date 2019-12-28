#include <ultra64.h>
#include <global.h>

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_801307C0.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_801307F4.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80130834.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType0Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80130940.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType1Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80130A94.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType2Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80130D0C.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType3Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80130F58.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_8013115C.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType4Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawType5Texture.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/SceneProc_DrawAnimatedTextures.asm")

void SceneProc_DrawAllSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 3);
}

void SceneProc_DrawOpaqueSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 1);
}

void SceneProc_DrawTranslucentSceneAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, ctxt->unk18840, 2);
}

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_801317F4.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_8013182C.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131864.asm")

void SceneProc_DrawAllAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 3);
}

void SceneProc_DrawOpaqueAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 1);
}

void SceneProc_DrawTranslucentAnimatedTextures(GlobalContext* ctxt, AnimatedTexture* textures, u32 step) {
    SceneProc_DrawAnimatedTextures(ctxt, textures, 1, step, 2);
}

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131920.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_8013194C.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131978.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_801319A4.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_801319CC.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131CDC.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131DE4.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131DF0.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131E58.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131EC0.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131F90.asm")

GLOBAL_ASM("./asm/nonmatching/z_scene_proc/func_80131FC0.asm")

