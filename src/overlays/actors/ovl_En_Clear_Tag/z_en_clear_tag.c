/*
 * File: z_en_clear_tag.c
 * Overlay: ovl_En_Clear_Tag
 * Description: Various effects: explosions and pops, splashes, light rays
 */

#include "z_en_clear_tag.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnClearTag*)thisx)

void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Update(Actor* thisx, GlobalContext* globalCtx);
void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnClearTag_UpdateEffects(EnClearTag* this, GlobalContext* globalCtx);
void EnClearTag_DrawEffects(Actor* thisx, GlobalContext* globalCtx);

const ActorInit En_Clear_Tag_InitVars = {
    ACTOR_EN_CLEAR_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnClearTag),
    (ActorFunc)EnClearTag_Init,
    (ActorFunc)EnClearTag_Destroy,
    (ActorFunc)EnClearTag_Update,
    (ActorFunc)EnClearTag_Draw,
};

static Vec3f sZeroVector = { 0.0f, 0.0f, 0.0f };

static Vec3f sLightRayEnvColor[] = {
    { 255.0f, 255.0f, 0.0f },
    { 255.0f, 100.0f, 100.0f },
    { 100.0f, 255.0f, 100.0f },
    { 100.0f, 100.0f, 255.0f },
};

static Vec3f sLightRayPrimColor[] = {
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
    { 255.0f, 255.0f, 255.0f },
};

static f32 sFlashMaxScale[] = {
    6.0f,
    12.0f,
    9.0f,
};

static f32 sSmokeScale[] = {
    3.0f,
    6.0f,
};

static f32 sShockwaveMaxScale[] = {
    15.0f,
    30.0f,
    20.0f,
};

static f32 sDebrisScale[] = {
    0.03f,
    0.06f,
    0.04f,
};

static f32 sLightRayScale[] = {
    1000.0f, 2000.0f, 1500.0f, 800.0f, 1300.0f,
};

static f32 sLightRayMaxScaleTarget[] = {
    15.0f, 30.0f, 20.0f, 10.0f, 20.0f,
};

static f32 sLightRayMaxScale[] = {
    25.0f, 100.0f, 48.0f, 20.0f, 32.0f,
};

static TexturePtr sSplashTex[] = {
    gExplosionSplashTex1,
    gExplosionSplashTex2,
    gExplosionSplashTex3,
    gExplosionSplashTex4,
    gExplosionSplashTex5,
    gExplosionSplashTex6,
    gExplosionSplashTex7,
    gExplosionSplashTex8,
    NULL,
    NULL,
    NULL,
};

#include "overlays/ovl_En_Clear_Tag/ovl_En_Clear_Tag.c"

/**
 * Creates a debris effect.
 * Debris effects are spawned by an explosion.
 */
void EnClearTag_CreateDebrisEffect(EnClearTag* this, Vec3f* position, Vec3f* velocity, Vec3f* acceleration, f32 scale,
                                   f32 rotationZ) {
    EnClearTagEffect* effect = this->effect;
    s16 i;

    // Look for an available effect to allocate a Debris effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->type = CLEAR_TAG_EFFECT_DEBRIS;

            effect->position = *position;
            effect->velocity = *velocity;
            effect->acceleration = *acceleration;

            effect->scale = scale;

            // Set the debris effects to spawn in a circle.
            effect->rotationY = Rand_ZeroFloat(M_PI * 2);
            effect->rotationX = Rand_ZeroFloat(M_PI * 2);

            effect->effectsTimer = effect->bounces = 0;

            effect->rotationZ = rotationZ;

            effect->actionTimer = Rand_ZeroFloat(10.0f);

            break;
        }
    }
}

/**
 * Creates a smoke effect.
 * Smoke effects are spawned by an explosion.
 */
void EnClearTag_CreateSmokeEffect(EnClearTag* this, Vec3f* position, f32 scale) {
    s16 i;
    EnClearTagEffect* effect = this->effect;

    // Look for an available effect to allocate a smoke effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEAR_TAG_EFFECT_SMOKE;

            effect->position = *position;
            effect->velocity = sZeroVector;
            effect->acceleration = sZeroVector;

            effect->scale = scale;
            effect->maxScale = 2.0f * scale;
            effect->smokeScaleX = 1.0f;
            effect->smokeScaleY = 1.0f;

            effect->primColor.a = 255.0f;
            effect->envColor.r = 255.0f;
            effect->envColor.b = 255.0f;
            effect->primColor.r = 200.0f;
            effect->primColor.g = 20.0f;
            effect->primColor.b = 0.0f;
            effect->envColor.g = 215.0f;

            break;
        }
    }
}

/**
 * Creates an isolated smoke effect without an explosion.
 * Smoke effects are spawned directly.
 */
void EnClearTag_CreateIsolatedSmokeEffect(EnClearTag* this, Vec3f* position, f32 scale) {
    s16 i;
    EnClearTagEffect* effect = this->effect;

    // Look for an available effect to allocate a smoke effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEAR_TAG_EFFECT_ISOLATED_SMOKE;

            effect->position = *position;
            effect->velocity = sZeroVector;
            effect->acceleration = sZeroVector;

            effect->scale = scale;
            effect->maxScale = 2.0f * scale;
            effect->smokeScaleX = 1.0f;
            effect->smokeScaleY = 1.0f;

            if (scale <= 1.1f) {
                effect->scale = ((KREG(23) * 0.1f) + 1.0f) * scale;
                effect->primColor.a = KREG(16) + 150.0f;
                effect->primColor.r = KREG(17);
                effect->primColor.g = KREG(18);
                effect->primColor.b = KREG(19);
                effect->envColor.r = KREG(20);
                effect->envColor.g = KREG(21);
                effect->envColor.b = KREG(22);
            } else {
                effect->envColor.r = effect->envColor.g = effect->envColor.b = 0.0f;
                effect->primColor.r = effect->primColor.g = effect->primColor.b = 0.0f;
                effect->primColor.a = 255.0f;
            }

            break;
        }
    }
}

/**
 * Creates a flash effect.
 * Flash effects are spawned by an explosion or a pop.
 * Flash effects have two components: 1) a billboard flash, and 2) a light effect on the ground.
 */
void EnClearTag_CreateFlashEffect(EnClearTag* this, Vec3f* position, f32 scale, f32 floorHeight) {
    EnClearTagEffect* effect = this->effect;
    s16 i;

    // Look for an available effect to allocate a flash effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->type = CLEAR_TAG_EFFECT_FLASH;

            effect->position = *position;
            effect->velocity = sZeroVector;
            effect->acceleration = sZeroVector;

            effect->scale = 0.0f;
            effect->maxScale = scale * 3.0f;

            // rotationZ is unused for CLEAR_TAG_EFFECT_FLASH
            effect->rotationZ = floorHeight;

            effect->primColor.a = 255.0f;

            break;
        }
    }
}

/**
 * Creates a light ray effect.
 * Light ray effects are spawned by an explosion or pop.
 */
void EnClearTag_CreateLightRayEffect(EnClearTag* this, Vec3f* position, Vec3f* velocity, Vec3f* acceleration, f32 scale,
                                     f32 maxScaleTarget, s16 alphaDecrementSpeed) {
    EnClearTagEffect* effect = this->effect;
    s16 i;

    // Look for an available effect to allocate a light ray effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            s32 requiredScopeTemp;

            effect->type = CLEAR_TAG_EFFECT_LIGHT_RAYS;

            effect->position = *position;
            effect->velocity = *velocity;
            effect->acceleration = *acceleration;

            effect->scale = scale / 1000.0f;
            effect->maxScale = 1.0f;
            effect->maxScaleTarget = maxScaleTarget;

            effect->lightRayAlpha = Rand_ZeroFloat(100.0f) + 200.0f;
            effect->lightRayAlphaDecrementSpeed = alphaDecrementSpeed;

            effect->actionTimer = Rand_ZeroFloat(10.0f);

            effect->rotationY = Math_Acot2F(effect->velocity.z, effect->velocity.x);
            effect->rotationX = -Math_Acot2F(sqrtf(SQXZ(effect->velocity)), effect->velocity.y);

            effect->envColor.r = 255.0f;
            effect->envColor.g = 255.0f;
            effect->envColor.b = 0.0f;
            effect->primColor.r = 255.0f;
            effect->primColor.g = 255.0f;
            effect->primColor.b = 255.0f;

            break;
        }
    }
}

/**
 * Creates an isolated light ray effect without an explosion or pop.
 * Light ray effects are spawned directly.
 */
void EnClearTag_CreateIsolatedLightRayEffect(EnClearTag* this, Vec3f* position, Vec3f* velocity, Vec3f* acceleration,
                                             f32 scale, f32 maxScaleTarget, s16 colorIndex, s16 alphaDecrementSpeed) {
    EnClearTagEffect* effect = this->effect;
    s16 i;

    // Look for an available effect to allocate a light ray effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->type = CLEAR_TAG_EFFECT_LIGHT_RAYS;

            effect->position = *position;
            effect->velocity = *velocity;
            effect->acceleration = *acceleration;

            effect->scale = scale / 1000.0f;
            effect->maxScale = 1.0f;
            effect->maxScaleTarget = maxScaleTarget;

            effect->lightRayAlpha = Rand_ZeroFloat(100.0f) + 200.0f;
            effect->lightRayAlphaDecrementSpeed = alphaDecrementSpeed;

            effect->actionTimer = Rand_ZeroFloat(10.0f);

            effect->rotationY = Math_Acot2F(effect->velocity.z, effect->velocity.x);
            effect->rotationX = -Math_Acot2F(sqrtf(SQXZ(effect->velocity)), effect->velocity.y);

            effect->envColor.r = sLightRayEnvColor[colorIndex].x;
            effect->envColor.g = sLightRayEnvColor[colorIndex].y;
            effect->envColor.b = sLightRayEnvColor[colorIndex].z;
            effect->primColor.r = sLightRayPrimColor[colorIndex].x;
            effect->primColor.g = sLightRayPrimColor[colorIndex].y;
            effect->primColor.b = sLightRayPrimColor[colorIndex].z;

            break;
        }
    }
}

/**
 * Creates a shockwave effect
 * This effect uses concentric ring floor shadows that travel radially outward along the floor poly
 */
void EnClearTag_CreateShockwaveEffect(EnClearTag* this, Vec3f* position, f32 maxScale, s16 actionTimer) {
    EnClearTagEffect* effect = this->effect;
    s16 i;

    // Look for an available effect to allocate a shockwave effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->type = CLEAR_TAG_EFFECT_SHOCKWAVE;

            effect->position = *position;
            effect->velocity = sZeroVector;
            effect->acceleration = sZeroVector;

            effect->maxScale = maxScale;
            effect->scale = 0.0f;

            effect->actionTimer = actionTimer;

            effect->primColor.a = 200.0f;

            break;
        }
    }
}

/**
 * Creates a splash effect
 * This effect is used when EnClearTag is spawned above a waterbox
 */
void EnClearTag_CreateSplashEffect(EnClearTag* this, Vec3f* position, s16 effectsTimer) {
    s16 i;
    EnClearTagEffect* effect = this->effect;

    // Look for an available effect to allocate a splash effect to.
    for (i = 0; i < ARRAY_COUNT(this->effect) - 1; i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_AVAILABLE) {
            // Immediately overwritten and generates a lot of wasted asm (f32 to u8)
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEAR_TAG_EFFECT_SPLASH;

            effect->position = *position;
            effect->velocity = sZeroVector;
            effect->acceleration = sZeroVector;

            effect->scale = 0.0f;
            effect->maxScale = 0.0f;

            effect->actionTimer = 0;
            effect->effectsTimer = effectsTimer;

            effect->rotationX = 0.78f;

            break;
        }
    }
}

/**
 * EnClearTag destructor.
 * No Operation takes place.
 */
void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

/**
 * EnClearTag constructor.
 * This initializes effects, and sets up ClearTag instance data.
 */
void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[3];
    EnClearTag* this = THIS;
    f32 lightRayMaxScale;
    u8 i;
    Vec3f pos;
    Vec3f vel;
    Vec3f accel;

    this->actor.flags &= ~ACTOR_FLAG_1;
    if (thisx->params >= 0) {
        this->activeTimer = 70;
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);

        // Initialize isolated smoke effect
        if (thisx->params == CLEAR_TAG_SMOKE) {
            EnClearTag_CreateIsolatedSmokeEffect(this, &pos, this->actor.world.rot.z);
            return;
        }

        if (thisx->params != CLEAR_TAG_SPLASH) {
            // Initialize isolated light ray effect
            if (thisx->params == CLEAR_TAG_SMALL_LIGHT_RAYS || thisx->params == CLEAR_TAG_LARGE_LIGHT_RAYS) {
                for (i = 0; i < 54; i++) {
                    lightRayMaxScale =
                        sLightRayMaxScale[thisx->params] + Rand_ZeroFloat(sLightRayMaxScale[thisx->params]);
                    Matrix_InsertYRotation_f(Rand_ZeroFloat(M_PI * 2), MTXMODE_NEW);
                    Matrix_RotateStateAroundXAxis(Rand_ZeroFloat(M_PI * 2));
                    Matrix_GetStateTranslationAndScaledZ(lightRayMaxScale, &vel);
                    accel.x = vel.x * -0.03f;
                    accel.y = vel.y * -0.03f;
                    accel.z = vel.z * -0.03f;
                    EnClearTag_CreateIsolatedLightRayEffect(
                        this, &pos, &vel, &accel,
                        sLightRayScale[thisx->params] + Rand_ZeroFloat(sLightRayScale[thisx->params] * 0.5f),
                        sLightRayMaxScaleTarget[thisx->params], this->actor.world.rot.z, Rand_ZeroFloat(10.0f) + 20.0f);
                }
                return;
            }

            if ((this->actor.world.rot.x != 0) || (this->actor.world.rot.y != 0) || (this->actor.world.rot.z != 0)) {
                this->flashEnvColor.r = this->actor.world.rot.x;
                this->flashEnvColor.g = this->actor.world.rot.y;
                this->flashEnvColor.b = this->actor.world.rot.z;
            } else {
                this->flashEnvColor.r = 255;
                this->flashEnvColor.g = 0;
            }

            // Initialize flash effect
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 30.0f, 100.0f, 4);
            pos = this->actor.world.pos;
            EnClearTag_CreateFlashEffect(this, &pos, sFlashMaxScale[thisx->params], this->actor.floorHeight);

            // Is not underwater
            if (!(this->actor.bgCheckFlags & 0x20)) {
                if (thisx->params < 10) {
                    pos.y = this->actor.world.pos.y - 40.0f;

                    // Initialize smoke effect
                    if (thisx->params != CLEAR_TAG_POP) {
                        EnClearTag_CreateSmokeEffect(this, &pos, sSmokeScale[thisx->params]);
                    }

                    // Initialize shockwave effect
                    pos.y = this->actor.floorHeight + 3.0f;
                    EnClearTag_CreateShockwaveEffect(this, &pos, sShockwaveMaxScale[thisx->params], 0);
                    EnClearTag_CreateShockwaveEffect(this, &pos, sShockwaveMaxScale[thisx->params], 3);
                    if (thisx->params == CLEAR_TAG_LARGE_EXPLOSION) {
                        EnClearTag_CreateShockwaveEffect(this, &pos, sShockwaveMaxScale[thisx->params], 6);
                    }
                }

                // Initialize debris effect
                if (thisx->params != CLEAR_TAG_POP) {
                    pos.y = this->actor.world.pos.y;
                    for (i = 0; i < 18; i++) {
                        vel.x = __sinf(i * (33.0f / 40.0f)) * i * .5f;
                        vel.z = __cosf(i * (33.0f / 40.0f)) * i * .5f;
                        vel.y = Rand_ZeroFloat(8.0f) + 7.0f;

                        vel.x += randPlusMinusPoint5Scaled(0.5f);
                        vel.z += randPlusMinusPoint5Scaled(0.5f);

                        accel.x = 0.0f;
                        accel.y = -1.0f;
                        accel.z = 0.0f;
                        EnClearTag_CreateDebrisEffect(this, &pos, &vel, &accel,
                                                      sDebrisScale[thisx->params] +
                                                          Rand_ZeroFloat(sDebrisScale[thisx->params]),
                                                      this->actor.floorHeight);
                    }
                }
            }

            // Initialize light ray effect
            pos = this->actor.world.pos;
            for (i = 0; i < 44; i++) {
                lightRayMaxScale = sLightRayMaxScale[thisx->params] + Rand_ZeroFloat(sLightRayMaxScale[thisx->params]);
                Matrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), MTXMODE_NEW);
                Matrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                Matrix_GetStateTranslationAndScaledZ(lightRayMaxScale, &vel);
                accel.x = vel.x * -0.03f;
                accel.y = vel.y * -0.03f;
                accel.z = vel.z * -0.03f;
                EnClearTag_CreateLightRayEffect(this, &pos, &vel, &accel,
                                                sLightRayScale[thisx->params] +
                                                    Rand_ZeroFloat(sLightRayScale[thisx->params] * 0.5f),
                                                sLightRayMaxScaleTarget[thisx->params], Rand_ZeroFloat(10.0f) + 20.0f);
            }
        }

        // Initialize splash effect
        EnClearTag_CreateSplashEffect(this, &pos, 0);
        EnClearTag_CreateSplashEffect(this, &pos, 2);
    }
}

void EnClearTag_UpdateCamera(EnClearTag* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Camera* mainCam;
    s32 pad;

    switch (this->cameraState) {
        case 0:
            if (((player->actor.world.pos.z > 0.0f) && (player->actor.world.pos.z > 290.0f) &&
                 (fabsf(player->actor.world.pos.x) < 60.0f)) ||
                ((player->actor.world.pos.z < 0.0f) && (player->actor.world.pos.z < -950.0f) &&
                 (fabsf(player->actor.world.pos.x) < 103.0f))) {

                if (player->actor.world.pos.z > 0.0f) {
                    player->actor.world.pos.z = 290.0f;
                } else {
                    player->actor.world.pos.z = -950.0f;
                }

                player->actor.speedXZ = 0.0f;
                if (this->activeTimer == 0) {
                    this->cameraState = 1;
                }
            }
            break;
        case 1:
            Cutscene_Start(globalCtx, &globalCtx->csCtx);
            this->subCamId = Play_CreateSubCamera(globalCtx);
            Play_CameraChangeStatus(globalCtx, CAM_ID_MAIN, 1);
            Play_CameraChangeStatus(globalCtx, this->subCamId, 7);
            func_800B7298(globalCtx, &this->actor, 4);
            mainCam = Play_GetCamera(globalCtx, CAM_ID_MAIN);
            this->subCamEye.x = mainCam->eye.x;
            this->subCamEye.y = mainCam->eye.y;
            this->subCamEye.z = mainCam->eye.z;
            this->subCamAt.x = mainCam->at.x;
            this->subCamAt.y = mainCam->at.y;
            this->subCamAt.z = mainCam->at.z;
            Message_StartTextbox(globalCtx, 0xF, NULL);
            this->cameraState = 2;
            func_8019FDC8(&D_801DB4A4, NA_SE_VO_NA_LISTEN, 0x20);
        case 2:
            if (player->actor.world.pos.z > 0.0f) {
                player->actor.world.pos.z = 290.0f;
            } else {
                player->actor.world.pos.z = -950.0f;
            }

            player->actor.speedXZ = 0.0f;
            if (Message_GetState(&globalCtx->msgCtx) == 0) {
                mainCam = Play_GetCamera(globalCtx, CAM_ID_MAIN);
                mainCam->eye = this->subCamEye;
                mainCam->eyeNext = this->subCamEye;
                mainCam->at = this->subCamAt;
                func_80169AFC(globalCtx, this->subCamId, 0);
                Cutscene_End(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                this->cameraState = 0;
                this->subCamId = CAM_ID_MAIN;
                this->activeTimer = 20;
            }
            break;
    }

    if (this->subCamId != CAM_ID_MAIN) {
        Play_CameraSetAtEye(globalCtx, this->subCamId, &this->subCamAt, &this->subCamEye);
    }
}

/**
 * EnClear_Tag update function.
 * Decides whether to update or to mark for death
 */
void EnClearTag_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnClearTag* this = THIS;

    if (this->activeTimer != 0) {
        this->activeTimer--;
    }

    if (this->actor.params < 0) {
        EnClearTag_UpdateCamera(this, globalCtx);
    } else if (this->activeTimer != 0) {
        EnClearTag_UpdateEffects(this, globalCtx);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

/**
 * EnClearTag draw function.
 * Setups DrawEffects
 */
void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnClearTag_DrawEffects(thisx, globalCtx);
}

/**
 * Updates all effects.
 * Performs effect physics.
 * Moves and bounces debris effects.
 * Fades most effects out of view. When effects are completely faded away they are removed.
 */
void EnClearTag_UpdateEffects(EnClearTag* this, GlobalContext* globalCtx) {
    EnClearTagEffect* effect = this->effect;
    s16 i;
    f32 originalYPosition;
    Vec3f sphereCenter;
    s32 pad;

    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type != CLEAR_TAG_EFFECT_AVAILABLE) {
            effect->actionTimer++;

            // Perform effect physics.
            effect->position.x += effect->velocity.x;
            originalYPosition = effect->position.y;
            effect->position.y += effect->velocity.y;
            effect->position.z += effect->velocity.z;
            effect->velocity.x += effect->acceleration.x;
            effect->velocity.y += effect->acceleration.y;
            effect->velocity.z += effect->acceleration.z;

            if (effect->type == CLEAR_TAG_EFFECT_DEBRIS) {
                // Clamp the velocity to -5.0
                if (effect->velocity.y < -5.0f) {
                    effect->velocity.y = -5.0f;
                }

                // While the effect is falling check if it has hit the ground.
                if (effect->velocity.y < 0.0f) {
                    sphereCenter = effect->position;
                    sphereCenter.y += 5.0f;

                    // Check if the debris has hit the ground.
                    if (BgCheck_SphVsFirstPoly(&globalCtx->colCtx, &sphereCenter, 11.0f)) {
                        effect->position.y = originalYPosition;

                        // Bounce the debris effect.
                        if (effect->bounces <= 0) {
                            effect->bounces++;
                            effect->velocity.y *= -0.5f;
                            effect->effectsTimer = Rand_ZeroFloat(20.0f) + 25.0f;
                        } else {
                            // The Debris effect is done bouncing. Set its velocity and acceleration to 0.
                            effect->velocity.x = effect->velocity.z = effect->acceleration.y = effect->velocity.y =
                                0.0f;
                        }
                    }
                }

                // Rotate the debris effect.
                if (effect->acceleration.y != 0.0f) {
                    effect->rotationY += 0.5f;
                    effect->rotationX += 0.35f;
                }

                if (effect->effectsTimer == 1) {
                    effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_FIRE) {
                // Fade the fire effect.
                Math_ApproachZeroF(&effect->primColor.a, 1.0f, 15.0f);
                if (effect->primColor.a <= 0.0f) {
                    effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_SHOCKWAVE) {
                if (effect->actionTimer > 3) {
                    Math_ApproachF(&effect->scale, effect->maxScale, 0.2f, effect->maxScale * 0.6666666f);
                    Math_ApproachZeroF(&effect->primColor.a, 1.0f, 15.0f);
                    if (effect->primColor.a <= 0.0f) {
                        effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                    }
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_SMOKE) {
                // Fade the smoke effects.
                Math_ApproachZeroF(&effect->primColor.r, 1.0f, 20.0f);
                Math_ApproachZeroF(&effect->primColor.g, 1.0f, 2.0f);
                Math_ApproachZeroF(&effect->envColor.r, 1.0f, 25.5f);
                Math_ApproachZeroF(&effect->envColor.g, 1.0f, 21.5f);
                Math_ApproachZeroF(&effect->envColor.b, 1.0f, 25.5f);

                // Smooth scale the smoke effects.
                Math_ApproachF(&effect->scale, effect->maxScale, 0.05f, 0.1f);

                if (effect->primColor.r == 0.0f) {
                    Math_ApproachF(&effect->smokeScaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&effect->smokeScaleY, 3.0f, 0.1f, 0.02f);

                    // Fade the smoke effects.
                    Math_ApproachZeroF(&effect->primColor.a, 1.0f, 5.f);

                    // If the smoke effect has fully faded, unload it.
                    if (effect->primColor.a <= 0.0f) {
                        effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                    }
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_ISOLATED_SMOKE) {
                // Smooth scale the isolated smoke effects.
                Math_ApproachF(&effect->scale, effect->maxScale, 0.05f, 0.1f);
                if (effect->actionTimer > 10) {
                    Math_ApproachF(&effect->smokeScaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&effect->smokeScaleY, 3.0f, 0.1f, 0.02f);

                    // Fade the smoke effects.
                    Math_ApproachZeroF(&effect->primColor.a, 1.0f, 5.f);
                    if (effect->primColor.a <= 0.0f) {
                        effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                    }
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_FLASH) {
                // Smooth scale the flash effects.
                Math_ApproachF(&effect->scale, effect->maxScale, 0.5f, 6.0f);

                // Fade the flash effects.
                Math_ApproachZeroF(&effect->primColor.a, 1.0f, 15.0f);
                if (effect->primColor.a <= 0.0f) {
                    effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                }
            } else if (effect->type == CLEAR_TAG_EFFECT_LIGHT_RAYS) {
                // Rotate the light ray effect.
                effect->rotationZ += Rand_ZeroFloat(M_PI / 2) + (M_PI / 2);

                // Fade the light ray effects.
                effect->lightRayAlpha -= effect->lightRayAlphaDecrementSpeed;
                if (effect->lightRayAlpha <= 0) {
                    effect->lightRayAlpha = 0;
                    effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                }
                effect->primColor.a = effect->lightRayAlpha;
                if (effect->primColor.a > 255.0f) {
                    effect->primColor.a = 255.0f;
                }

                // Smooth scale the light ray effects.
                Math_ApproachF(&effect->maxScale, effect->maxScaleTarget, 1.0f,
                               (effect->maxScaleTarget / 15.0f) * 4.0f);
            } else if (effect->type == CLEAR_TAG_EFFECT_SPLASH) {
                if (effect->effectsTimer == 0) {
                    effect->scale = 7.0f;

                    // Smooth scale the splash effects.
                    Math_ApproachF(&effect->maxScale, 500.0f, 1.0f, 50.0f);
                    Math_ApproachF(&effect->rotationX, 1.5f, 1.0f, 0.12f);
                    if (effect->actionTimer > 7) {
                        effect->type = CLEAR_TAG_EFFECT_AVAILABLE;
                    }
                } else {
                    effect->actionTimer = 0;
                }
            }

            if (effect->effectsTimer != 0) {
                effect->effectsTimer--;
            }
        }
    }
}

/**
 * Draws all effects.
 * Each effect type is drawn before the next. The function will apply a material that
 * applies to all effects of that type while drawing the first effect of that type.
 */
void EnClearTag_DrawEffects(Actor* thisx, GlobalContext* globalCtx) {
    u8 isMaterialApplied = false;
    s16 i;
    s16 j;
    Vec3f vec;
    WaterBox* waterBox;
    f32 ySurface;
    MtxF mtxF;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    EnClearTag* this = THIS;
    EnClearTagEffect* effect = this->effect;
    EnClearTagEffect* firstEffect = this->effect;

    OPEN_DISPS(gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    // Draw all Debris effects.
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_DEBRIS) {
            // Apply the debris effect material if it has not already been applied.
            if (!isMaterialApplied) {
                isMaterialApplied++;
                gSPDisplayList(POLY_OPA_DISP++, gClearTagDebrisEffectMaterialDL);
            }

            // Draw the debris effect.
            Matrix_InsertTranslation(effect->position.x, effect->position.y, effect->position.z, MTXMODE_NEW);
            Matrix_Scale(effect->scale, effect->scale, effect->scale, MTXMODE_APPLY);
            Matrix_InsertYRotation_f(effect->rotationY, MTXMODE_APPLY);
            Matrix_RotateStateAroundXAxis(effect->rotationX);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gClearTagDebrisEffectDL);
        }
    }

    // Draw all Shockwave effects.
    effect = firstEffect;
    if (this->actor.floorPoly != NULL) {
        for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
            if (effect->type == CLEAR_TAG_EFFECT_SHOCKWAVE) {
                // Draw the shockwave effect.
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (s8)effect->primColor.a);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s8)effect->primColor.a);
                func_800C0094(this->actor.floorPoly, effect->position.x, effect->position.y, effect->position.z, &mtxF);
                Matrix_SetCurrentState(&mtxF);
                Matrix_Scale(effect->scale, 1.0f, effect->scale, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gameplay_keep_DL_030100);
            }
        }
    }

    // Draw all ground flash effects.
    effect = firstEffect;
    isMaterialApplied = false;
    if (this->actor.floorPoly != NULL) {
        for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
            if (effect->type == CLEAR_TAG_EFFECT_FLASH) {
                // Apply the flash ground effect material if it has not already been applied.
                if (!isMaterialApplied) {
                    gDPPipeSync(POLY_XLU_DISP++);
                    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 200, 0);
                    isMaterialApplied++;
                }

                // Draw the ground flash effect.
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)(effect->primColor.a * 0.7f));
                func_800C0094(this->actor.floorPoly, effect->position.x, this->actor.floorHeight, effect->position.z,
                              &mtxF);
                Matrix_SetCurrentState(&mtxF);
                Matrix_Scale(effect->scale * 3.0f, 1.0f, effect->scale * 3.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gClearTagFlashEffectGroundDL);
            }
        }
    }

    // Draw all smoke effects.
    effect = firstEffect;
    isMaterialApplied = false;
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if ((effect->type == CLEAR_TAG_EFFECT_SMOKE) || (effect->type == CLEAR_TAG_EFFECT_ISOLATED_SMOKE)) {
            // Apply the smoke effect material if it has not already been applied.
            if (!isMaterialApplied) {
                gSPDisplayList(POLY_XLU_DISP++, gClearTagFireEffectMaterialDL);
                isMaterialApplied++;
            }

            // Draw the smoke effect.
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, (s8)effect->envColor.r, (s8)effect->envColor.g, (s8)effect->envColor.b,
                           128);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (s8)effect->primColor.r, (s8)effect->primColor.g,
                            (s8)effect->primColor.b, (s8)effect->primColor.a);
            gSPSegment(
                POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, -effect->actionTimer * 5, 32, 64, 1, 0, 0, 32, 32));
            Matrix_InsertTranslation(effect->position.x, effect->position.y, effect->position.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(effect->smokeScaleX * effect->scale, effect->smokeScaleY * effect->scale, 1.0f, MTXMODE_APPLY);
            Matrix_InsertTranslation(0.0f, 20.0f, 0.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gClearTagFireEffectDL);
        }
    }

    // Draw all fire effects.
    effect = firstEffect;
    isMaterialApplied = false;
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_FIRE) {
            // Apply the fire effect material if it has not already been applied.
            if (!isMaterialApplied) {
                gSPDisplayList(POLY_XLU_DISP++, gClearTagFireEffectMaterialDL);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 215, 255, 128);
                isMaterialApplied++;
            }

            // Draw the fire effect.
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 20, 0, (s8)effect->primColor.a);
            gSPSegment(
                POLY_XLU_DISP++, 0x08,
                Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, -effect->actionTimer * 15, 32, 64, 1, 0, 0, 32, 32));
            Matrix_InsertTranslation(effect->position.x, effect->position.y, effect->position.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(effect->scale, effect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gClearTagFireEffectDL);
        }
    }

    // Draw all flash billboard effects.
    effect = firstEffect;
    isMaterialApplied = false;
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_FLASH) {
            // Apply the flash billboard effect material if it has not already been applied.
            if (!isMaterialApplied) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, this->flashEnvColor.r, this->flashEnvColor.g, this->flashEnvColor.b, 0);
                isMaterialApplied++;
            }

            // Draw the flash billboard effect.
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)effect->primColor.a);
            Matrix_InsertTranslation(effect->position.x, effect->position.y, effect->position.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(2.0f * effect->scale, 2.0f * effect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gClearTagFlashEffectDL);
        }
    }

    // Draw all light ray effects.
    effect = firstEffect;
    isMaterialApplied = false;
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_LIGHT_RAYS) {
            // Apply the light ray effect material if it has not already been applied.
            if (!isMaterialApplied) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, (u8)effect->envColor.r, (u8)effect->envColor.g, (u8)effect->envColor.b,
                               0);
                gSPDisplayList(POLY_XLU_DISP++, gClearTagLightRayEffectMaterialDL);
                isMaterialApplied++;
            }

            // Draw the light ray effect.
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)effect->primColor.r, (u8)effect->primColor.g,
                            (u8)effect->primColor.b, (u8)effect->primColor.a);
            Matrix_InsertTranslation(effect->position.x, effect->position.y, effect->position.z, MTXMODE_NEW);
            Matrix_InsertYRotation_f(effect->rotationY, MTXMODE_APPLY);
            Matrix_RotateStateAroundXAxis(effect->rotationX);
            Matrix_InsertZRotation_f(effect->rotationZ, MTXMODE_APPLY);
            Matrix_Scale(effect->scale * 0.5f, effect->scale * 0.5f, effect->maxScale * effect->scale, MTXMODE_APPLY);
            Matrix_RotateStateAroundXAxis(M_PI / 2);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gClearTagLightRayEffectDL);
        }
    }

    // Draw all splash effects.
    effect = firstEffect;
    for (i = 0; i < ARRAY_COUNT(this->effect); i++, effect++) {
        if (effect->type == CLEAR_TAG_EFFECT_SPLASH) {
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 200);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 200);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sSplashTex[effect->actionTimer]));
            func_8012C9BC(gfxCtx);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BACK);
            isMaterialApplied++;

            // Apply material 16 times along a circle to give the appearance of a splash
            for (j = 0; j < 16; j++) {
                Matrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_NEW);
                Matrix_GetStateTranslationAndScaledZ(effect->maxScale, &vec);
                /**
                 * Get the water surface at point (`x`, `ySurface`, `z`). `ySurface` doubles as position y input
                 * returns true if point is within the xz boundaries of an active water box, else false
                 * `ySurface` returns the water box's surface, while `outWaterBox` returns a pointer to the WaterBox
                 */
                ySurface = effect->position.y;
                if (WaterBox_GetSurface1(globalCtx, &globalCtx->colCtx, effect->position.x + vec.x,
                                         effect->position.z + vec.z, &ySurface, &waterBox)) {
                    if ((effect->position.y - ySurface) < 200.0f) {
                        // Draw the splash effect.
                        Matrix_InsertTranslation(effect->position.x + vec.x, ySurface, effect->position.z + vec.z,
                                                 MTXMODE_NEW);
                        Matrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_APPLY);
                        Matrix_RotateStateAroundXAxis(effect->rotationX);
                        Matrix_Scale(effect->scale, effect->scale, effect->scale, MTXMODE_APPLY);
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_XLU_DISP++, gExplosionSplashDL);
                    }
                }
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
