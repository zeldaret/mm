#include <ultra64.h>
#include <global.h>

void EffectSs_DrawGEffect(GlobalContext* globalCtx, EffectSs* this, void* texture) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    f32 scale;
    MtxF mfTrans;
    MtxF mfScale;
    MtxF mfResult;
    MtxF mfTrans11DA0;
    s32 pad1;
    Mtx* mtx;
    void* object = globalCtx->sceneContext.objects[this->rgObjBankIdx].segment;

    OPEN_DISPS(gfxCtx);

    scale = this->rgScale * D_801DC100;
    SkinMatrix_SetTranslate(&mfTrans, this->pos.x, this->pos.y, this->pos.z);
    Matrix_MakeScale(&mfScale, scale, scale, scale);
    SkinMatrix_MtxFMtxFMult(&mfTrans, &globalCtx->mf_187FC, &mfTrans11DA0);
    SkinMatrix_MtxFMtxFMult(&mfTrans11DA0, &mfScale, &mfResult);
    gSegments[6] = PHYSICAL_TO_VIRTUAL(object);
    gSPSegment(POLY_XLU_DISP++, 0x06, object);

    mtx = SkinMatrix_MtxFToNewMtx(gfxCtx, &mfResult);

    if (mtx != NULL) {
        gSPMatrix(POLY_XLU_DISP++, mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPSegment(POLY_XLU_DISP++, 0x08, Lib_PtrSegToVirt(texture));
        func_8012C9BC(gfxCtx);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, this->rgPrimColorR, this->rgPrimColorG, this->rgPrimColorB,
                        this->rgPrimColorA);
        gDPSetEnvColor(POLY_XLU_DISP++, this->rgEnvColorR, this->rgEnvColorG, this->rgEnvColorB, this->rgEnvColorA);
        gSPDisplayList(POLY_XLU_DISP++, this->gfx);
    }

    CLOSE_DISPS(gfxCtx);
}

// EffectSsDust Spawn Functions

void EffectSsDust_Spawn(GlobalContext* globalCtx, u16 drawFlags, Vec3f* pos, Vec3f* velocity, Vec3f* accel,
                        ColorRGBA8* primColor, ColorRGBA8* envColor, s16 scale, s16 scaleStep, s16 life,
                        u8 updateMode) {
    EffectSsDustInitParams initParams;

    Math_Vec3f_Copy(&initParams.pos, pos);
    Math_Vec3f_Copy(&initParams.velocity, velocity);
    Math_Vec3f_Copy(&initParams.accel, accel);
    initParams.primColor = *primColor;
    initParams.envColor = *envColor;
    initParams.drawFlags = drawFlags;
    initParams.scale = scale;
    initParams.scaleStep = scaleStep;
    initParams.life = life;
    initParams.updateMode = updateMode;

    EffectSs_Spawn(globalCtx, EFFECT_SS2_TYPE_DUST, 128, &initParams);
}

void func_800B0DE0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep) {
    EffectSsDust_Spawn(globalCtx, 0, pos, velocity, accel, primColor, envColor, scale, scaleStep, 10, 0);
}

void func_800B0E48(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep) {
    EffectSsDust_Spawn(globalCtx, 1, pos, velocity, accel, primColor, envColor, scale, scaleStep, 10, 0);
}

void func_800B0EB0(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep, s16 life) {
    EffectSsDust_Spawn(globalCtx, 0, pos, velocity, accel, primColor, envColor, scale, scaleStep, life, 0);
}

void func_800B0F18(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep, s16 life) {
    EffectSsDust_Spawn(globalCtx, 1, pos, velocity, accel, primColor, envColor, scale, scaleStep, life, 0);
}

void func_800B0F80(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep, s16 life) {
    EffectSsDust_Spawn(globalCtx, 2, pos, velocity, accel, primColor, envColor, scale, scaleStep, life, 0);
}

void func_800B0FE8(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep) {
    EffectSsDust_Spawn(globalCtx, 0, pos, velocity, accel, primColor, envColor, scale, scaleStep, 10, 1);
}

void func_800B1054(GlobalContext* globalCtx, Vec3f* pos, Vec3f* velocity, Vec3f* accel, ColorRGBA8* primColor,
                   ColorRGBA8* envColor, s16 scale, s16 scaleStep) {
    EffectSsDust_Spawn(globalCtx, 1, pos, velocity, accel, primColor, envColor, scale, scaleStep, 10, 1);
}
#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B10C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B11A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1280.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B12F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B139C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B13D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B14D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B165C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B16B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnSparkle.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnBomb2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnBlast.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1A70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1AC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1B10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnGSpark.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1BDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1C70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1CC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B1DC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnDodongoFire.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnBubble.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnGRipple.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnGSplash.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnGFire.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnLightning.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2090.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnBigOctoBubble2.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnFragment.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B221C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2364.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnStick.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnSplash.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B249C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnStone1.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnHitMark.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2684.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B26A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnPhantomGanonFlash.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnKakarikoFire.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnSoldierSearchBall.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnShard.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnIcePiece.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2930.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnEnemyIce.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2B7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2BC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnFireTail.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2CE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2DA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnEnemyFire.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B2E6C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnExtra.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnDeadDekuBaba.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B3030.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnDeadDodongo.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnDeadDekuScrub.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/func_800B31BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnIceSmoke.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/code/z_effect_soft_sprite_old_init/EffectSS_SpawnIceBlock.asm")
