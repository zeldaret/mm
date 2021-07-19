#include "z_en_clear_tag.h"

#define FLAGS 0x00000035

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

extern Gfx D_04030100[]; // Floor shockwave ring
extern Gfx D_040378F0[]; // gExplosionSplashTex1
extern Gfx D_04037DF0[]; // gExplosionSplashTex2
extern Gfx D_040382F0[]; // gExplosionSplashTex3
extern Gfx D_040387F0[]; // gExplosionSplashTex4
extern Gfx D_04038CF0[]; // gExplosionSplashTex5
extern Gfx D_040391F0[]; // gExplosionSplashTex6
extern Gfx D_040396F0[]; // gExplosionSplashTex7
extern Gfx D_04039BF0[]; // gExplosionSplashTex8
extern Gfx D_0403A0F0[]; // gExplosionSplashDL

static Vec3f sZeroVec = { 0.0f, 0.0f, 0.0f };

static Vec3f sLightRaysEnvColor[] = {
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

static f32 sOuterCloudScaleZ[] = {
    6.0f,
    12.0f,
    9.0f,
};

static f32 sBlackSmokeScale[] = {
    3.0f,
    6.0f,
};

static f32 sFloorShockwaveScaleZ[] = {
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

static f32 sLightRayScaleZTarget[] = {
    15.0f, 30.0f, 20.0f, 10.0f, 20.0f,
};

static f32 sLightRayScaleZ[] = {
    25.0f, 100.0f, 48.0f, 20.0f, 32.0f,
};

static Gfx* sExplosionSplashTex[] = {
    D_040378F0, D_04037DF0, D_040382F0, D_040387F0, D_04038CF0, D_040391F0, D_040396F0, D_04039BF0, NULL, NULL, NULL,
};

#include "overlays/ovl_En_Clear_Tag/ovl_En_Clear_Tag.c"

void EnClearTag_AddExplosionDebrisEffect(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale, f32 rotZ) {
    f32 rotX;
    EnClearTagEffects* effect = this->effects;
    s16 i;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->type = CLEARTAG_EXPLOSION_DEBRIS;
            effect->pos = *pos;
            effect->vel = *vel;
            effect->accel = *accel;
            effect->scale = scale;
            effect->rotY = Rand_ZeroFloat(2 * M_PI);
            rotX = Rand_ZeroFloat(2 * M_PI);
            effect->isDebreeActive = 0;
            effect->rotX = rotX;
            effect->effectsTimer = effect->isDebreeActive;
            effect->rotZ = rotZ;
            effect->actionTimer = Rand_ZeroFloat(10.0f);
            break;
        }
    }
}

void EnClearTag_AddExplosionBlackSmokeEffect(EnClearTag* this, Vec3f* pos, f32 scale) {
    s16 i;
    EnClearTagEffects* effect = this->effects;

    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEARTAG_EXPLOSION_BLACK_SMOKE;
            effect->pos = *pos;
            effect->vel = sZeroVec;
            effect->accel = sZeroVec;
            effect->scale = scale;
            effect->scaleZ = 2.0f * scale;
            effect->scaleX = 1.0f;
            effect->scaleY = 1.0f;
            effect->primColorAlpha = 255.0f;
            effect->envColorR = 255.0f;
            effect->envColorB = 255.0f;
            effect->primColorR = 200.0f;
            effect->primColorG = 20.0f;
            effect->primColorB = 0.0f;
            effect->envColorG = 215.0f;
            break;
        }
    }
}

void EnClearTag_AddNoExplosionBlackSmokeEffect(EnClearTag* this, Vec3f* pos, f32 scale) {
    s16 i;
    EnClearTagEffects* effect = this->effects;

    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEARTAG_NO_EXPLOSION_BLACK_SMOKE;
            effect->pos = *pos;
            effect->vel = sZeroVec;
            effect->accel = sZeroVec;
            effect->scale = scale;
            effect->scaleZ = 2.0f * scale;
            effect->scaleX = 1.0f;
            effect->scaleY = 1.0f;

            if (scale <= 1.1f) {
                effect->scale = ((KREG(23) * 0.1f) + 1.0f) * scale;
                effect->primColorAlpha = KREG(16) + 150.0f;
                effect->primColorR = KREG(17);
                effect->primColorG = KREG(18);
                effect->primColorB = KREG(19);
                effect->envColorR = KREG(20);
                effect->envColorG = KREG(21);
                effect->envColorB = KREG(22);
            } else {
                effect->envColorB = 0.0f;
                effect->envColorG = 0.0f;
                effect->envColorR = 0.0f;
                effect->primColorB = 0.0f;
                effect->primColorG = 0.0f;
                effect->primColorR = 0.0f;
                effect->primColorAlpha = 255.0f;
            }
            break;
        }
    }
}

void EnClearTag_AddExplosionOuterCloudEffect(EnClearTag* this, Vec3f* pos, f32 scaleZ, f32 floorHeight) {
    EnClearTagEffects* effect = this->effects;
    s16 i;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->type = CLEARTAG_EXPLOSION_OUTER_CLOUD;
            effect->pos = *pos;
            effect->vel = sZeroVec;
            effect->accel = sZeroVec;
            effect->scale = 0.0f;
            effect->scaleZ = scaleZ * 3.0f;
            // rotZ is unused for CLEARTAG_EXPLOSION_OUTER_CLOUD
            effect->rotZ = floorHeight;
            effect->primColorAlpha = 255.0f;
            break;
        }
    }
}

void EnClearTag_AddLightRayFromExplosionEffect(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale,
                                               f32 scaleZTarget, s16 alphaDecrementSpeed) {
    EnClearTagEffects* effect = this->effects;
    s16 i;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->type = CLEARTAG_LIGHT_RAY;
            effect->pos = *pos;
            effect->vel = *vel;
            effect->accel = *accel;
            effect->scale = scale / 1000.0f;
            effect->scaleZ = 1.0f;
            effect->scaleZTarget = scaleZTarget;
            effect->lightRayAlpha = Rand_ZeroFloat(100.0f) + 200.0f;
            effect->lightRayAlphaDecrementSpeed = alphaDecrementSpeed;
            effect->actionTimer = Rand_ZeroFloat(10.0f);
            effect->rotY = Math_Acot2F(effect->vel.z, effect->vel.x);
            effect->rotX = -Math_Acot2F(sqrtf(SQXZ(effect->vel)), effect->vel.y);
            effect->envColorR = 255.0f;
            effect->envColorG = 255.0f;
            effect->primColorR = 255.0f;
            effect->primColorG = 255.0f;
            effect->primColorB = 255.0f;
            effect->envColorB = 0.0f;
            break;
        }
    dummy:;
    }
}

void EnClearTag_AddLightRayFromLightArrowsEffect(EnClearTag* this, Vec3f* pos, Vec3f* vel, Vec3f* accel, f32 scale,
                                                 f32 scaleZTarget, s16 colorIndex, s16 alphaDecrementSpeed) {
    EnClearTagEffects* effect = this->effects;
    s16 i;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->type = CLEARTAG_LIGHT_RAY;
            effect->pos = *pos;
            effect->vel = *vel;
            effect->accel = *accel;
            effect->scale = scale / 1000.0f;
            effect->scaleZ = 1.0f;
            effect->scaleZTarget = scaleZTarget;
            effect->lightRayAlpha = Rand_ZeroFloat(100.0f) + 200.0f;
            effect->lightRayAlphaDecrementSpeed = alphaDecrementSpeed;
            effect->actionTimer = Rand_ZeroFloat(10.0f);
            effect->rotY = Math_Acot2F(effect->vel.z, effect->vel.x);
            effect->rotX = -Math_Acot2F(sqrtf(SQXZ(effect->vel)), effect->vel.y);
            effect->envColorR = sLightRaysEnvColor[colorIndex].x;
            effect->envColorG = sLightRaysEnvColor[colorIndex].y;
            effect->envColorB = sLightRaysEnvColor[colorIndex].z;
            effect->primColorR = sLightRayPrimColor[colorIndex].x;
            effect->primColorG = sLightRayPrimColor[colorIndex].y;
            effect->primColorB = sLightRayPrimColor[colorIndex].z;
            break;
        }
    }
}

void EnClearTag_AddFloorShockwaveEffect(EnClearTag* this, Vec3f* pos, f32 scaleZ, s16 actionTimer) {
    EnClearTagEffects* effect = this->effects;
    s16 i;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            effect->type = CLEARTAG_EXPLOSION_FLOOR_SHOCKWAVE;
            effect->pos = *pos;
            effect->vel = sZeroVec;
            effect->accel = sZeroVec;
            effect->scaleZ = scaleZ;
            effect->actionTimer = actionTimer;
            effect->scale = 0.0f;
            effect->primColorAlpha = 200.0f;
            break;
        }
    }
}

void EnClearTag_AddExplosionSplashEffect(EnClearTag* this, Vec3f* pos, s16 effectsTimer) {
    s16 i;
    EnClearTagEffects* effect = this->effects;

    for (i = 0; i < 102; i++, effect++) {
        if (effect->type == CLEARTAG_NO_EFFECT) {
            // Immediately overwritten and generates a lot of wasted asm (f32 to u8)
            effect->actionTimer = Rand_ZeroFloat(100.0f);
            effect->type = CLEARTAG_EXPLOSION_SPLASH;
            effect->pos = *pos;
            effect->vel = sZeroVec;
            effect->accel = sZeroVec;
            effect->scale = 0.0f;
            effect->scaleZ = 0.0f;
            effect->actionTimer = 0;
            effect->effectsTimer = effectsTimer;
            effect->rotX = 0.78f;
            break;
        }
    }
}

void EnClearTag_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void EnClearTag_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[3];
    EnClearTag* this = THIS;
    f32 lightRayScaleZ;
    u8 i;
    Vec3f pos;
    Vec3f vel;
    Vec3f accel;

    this->actor.flags &= -2;
    if (thisx->params >= 0) {
        this->activeTimer = 70;
        Math_Vec3f_Copy(&pos, &this->actor.world.pos);
        if (thisx->params == 200) {
            EnClearTag_AddNoExplosionBlackSmokeEffect(this, &pos, this->actor.world.rot.z);
            return;
        }

        if (thisx->params != 35) {
            if (thisx->params == 3 || thisx->params == 4) {
                for (i = 0; i < 54; i++) {
                    lightRayScaleZ = sLightRayScaleZ[thisx->params] + Rand_ZeroFloat(sLightRayScaleZ[thisx->params]);
                    SysMatrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), 0);
                    SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    SysMatrix_GetStateTranslationAndScaledZ(lightRayScaleZ, &vel);
                    accel.x = vel.x * -0.03f;
                    accel.y = vel.y * -0.03f;
                    accel.z = vel.z * -0.03f;
                    EnClearTag_AddLightRayFromLightArrowsEffect(
                        this, &pos, &vel, &accel,
                        sLightRayScale[thisx->params] + Rand_ZeroFloat(sLightRayScale[thisx->params] * 0.5f),
                        sLightRayScaleZTarget[thisx->params], this->actor.world.rot.z, Rand_ZeroFloat(10.0f) + 20.0f);
                }
                return;
            } else {
                if (!((this->actor.world.rot.x == 0) && (this->actor.world.rot.y == 0) &&
                      (this->actor.world.rot.z == 0))) {
                    this->explosionOuterCloudEnvColor.r = this->actor.world.rot.x;
                    this->explosionOuterCloudEnvColor.g = this->actor.world.rot.y;
                    this->explosionOuterCloudEnvColor.b = this->actor.world.rot.z;
                } else {
                    this->explosionOuterCloudEnvColor.r = 255;
                    this->explosionOuterCloudEnvColor.g = 0;
                }

                Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 50.0f, 30.0f, 100.0f, 4);
                pos = this->actor.world.pos;
                EnClearTag_AddExplosionOuterCloudEffect(this, &pos, sOuterCloudScaleZ[thisx->params],
                                                        this->actor.floorHeight);
                if (!(this->actor.bgCheckFlags & 0x20)) {
                    if (thisx->params < 10) {
                        pos.y = this->actor.world.pos.y - 40.0f;
                        if (thisx->params != 2) {
                            EnClearTag_AddExplosionBlackSmokeEffect(this, &pos, sBlackSmokeScale[thisx->params]);
                        }
                        pos.y = this->actor.floorHeight + 3.0f;
                        EnClearTag_AddFloorShockwaveEffect(this, &pos, sFloorShockwaveScaleZ[thisx->params], 0);
                        EnClearTag_AddFloorShockwaveEffect(this, &pos, sFloorShockwaveScaleZ[thisx->params], 3);
                        if (thisx->params == 1) {
                            EnClearTag_AddFloorShockwaveEffect(this, &pos, sFloorShockwaveScaleZ[thisx->params], 6);
                        }
                    }

                    if (thisx->params != 2) {
                        pos.y = this->actor.world.pos.y;
                        for (i = 0; i < 18; i++) {
                            vel.x = __sinf(i * 0.825f) * i * .5f;
                            vel.z = __cosf(i * 0.825f) * i * .5f;
                            vel.y = Rand_ZeroFloat(8.0f) + 7.0f;
                            vel.x += randPlusMinusPoint5Scaled(0.5f);
                            vel.z += randPlusMinusPoint5Scaled(0.5f);
                            accel.x = 0.0f;
                            accel.y = -1.0f;
                            accel.z = 0.0f;
                            EnClearTag_AddExplosionDebrisEffect(this, &pos, &vel, &accel,
                                                                sDebrisScale[thisx->params] +
                                                                    Rand_ZeroFloat(sDebrisScale[thisx->params]),
                                                                this->actor.floorHeight);
                        }
                    }
                }

                pos = this->actor.world.pos;
                for (i = 0; i < 44; i++) {
                    lightRayScaleZ = sLightRayScaleZ[thisx->params] + Rand_ZeroFloat(sLightRayScaleZ[thisx->params]);
                    SysMatrix_InsertYRotation_f(Rand_ZeroFloat(2 * M_PI), 0);
                    SysMatrix_RotateStateAroundXAxis(Rand_ZeroFloat(2 * M_PI));
                    SysMatrix_GetStateTranslationAndScaledZ(lightRayScaleZ, &vel);
                    accel.x = vel.x * -0.03f;
                    accel.y = vel.y * -0.03f;
                    accel.z = vel.z * -0.03f;
                    EnClearTag_AddLightRayFromExplosionEffect(
                        this, &pos, &vel, &accel,
                        sLightRayScale[thisx->params] + Rand_ZeroFloat(sLightRayScale[thisx->params] * 0.5f),
                        sLightRayScaleZTarget[thisx->params], Rand_ZeroFloat(10.0f) + 20.0f);
                }
            }
        }
        EnClearTag_AddExplosionSplashEffect(this, &pos, 0);
        EnClearTag_AddExplosionSplashEffect(this, &pos, 2);
    }
}

void EnClearTag_UpdateCamera(EnClearTag* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Camera* camera;
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
            func_800EA0D4(globalCtx, &globalCtx->csCtx);
            this->camID = func_801694DC(globalCtx);
            func_80169590(globalCtx, 0, 1);
            func_80169590(globalCtx, this->camID, 7);
            func_800B7298(globalCtx, &this->actor, 4);
            camera = Play_GetCamera(globalCtx, 0);
            this->eye.x = camera->eye.x;
            this->eye.y = camera->eye.y;
            this->eye.z = camera->eye.z;
            this->at.x = camera->focalPoint.x;
            this->at.y = camera->focalPoint.y;
            this->at.z = camera->focalPoint.z;
            func_801518B0(globalCtx, 0xF, NULL);
            this->cameraState = 2;
            func_8019FDC8(&D_801DB4A4, NA_SE_VO_NA_LISTEN, 0x20);
        case 2:
            if (player->actor.world.pos.z > 0.0f) {
                player->actor.world.pos.z = 290.0f;
            } else {
                player->actor.world.pos.z = -950.0f;
            }

            player->actor.speedXZ = 0.0f;
            if (func_80152498(&globalCtx->msgCtx) == 0) {
                camera = Play_GetCamera(globalCtx, 0);
                camera->eye = this->eye;
                camera->unk74 = this->eye;
                camera->focalPoint = this->at;
                func_80169AFC(globalCtx, this->camID, 0);
                func_800EA0EC(globalCtx, &globalCtx->csCtx);
                func_800B7298(globalCtx, &this->actor, 6);
                this->cameraState = 0;
                this->camID = 0;
                this->activeTimer = 20;
            }
            break;
    }

    if (this->camID != 0) {
        func_8016970C(globalCtx, this->camID, &this->at, &this->eye);
    }
}

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

void EnClearTag_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnClearTag_DrawEffects(thisx, globalCtx);
}

void EnClearTag_UpdateEffects(EnClearTag* this, GlobalContext* globalCtx) {
    EnClearTagEffects* effect = this->effects;
    s32 pad;
    f32 prevPosY;
    Vec3f pos;
    s16 i;

    for (i = 0; i < 103; i++, effect++) {
        if (effect->type != CLEARTAG_NO_EFFECT) {
            effect->actionTimer++;
            effect->pos.x += effect->vel.x;
            prevPosY = effect->pos.y;
            effect->pos.y += effect->vel.y;
            effect->pos.z += effect->vel.z;
            effect->vel.x += effect->accel.x;
            effect->vel.y += effect->accel.y;
            effect->vel.z += effect->accel.z;
            if (effect->type == CLEARTAG_EXPLOSION_DEBRIS) {
                if (effect->vel.y < -5.0f) {
                    effect->vel.y = -5.0f;
                }

                if (effect->vel.y < 0.0f) {
                    pos = effect->pos;
                    pos.y += 5.0f;
                    if (func_800C5A20(&globalCtx->colCtx, &pos, 11.0f) != 0) {
                        effect->pos.y = prevPosY;
                        if (effect->isDebreeActive <= 0) {
                            effect->isDebreeActive++;
                            effect->vel.y *= -0.5f;
                            effect->effectsTimer = Rand_ZeroFloat(20.0f) + 25.0f;
                        } else {
                            effect->vel.y = 0.0f;
                            effect->accel.y = 0.0f;
                            effect->vel.z = 0.0f;
                            effect->vel.x = 0.0f;
                        }
                    }
                }

                if (effect->accel.y != 0.0f) {
                    effect->rotY += 0.5f;
                    effect->rotX += 0.35f;
                }

                if (effect->effectsTimer == 1) {
                    effect->type = CLEARTAG_NO_EFFECT;
                }
            } else if (effect->type == CLEARTAG_UNUSED_BLACK_SMOKE) {
                // effect->type never set to 2
                Math_ApproachZeroF(&effect->primColorAlpha, 1.0f, 15.0f);
                if (effect->primColorAlpha <= 0.0f) {
                    effect->type = CLEARTAG_NO_EFFECT;
                }
            } else if (effect->type == CLEARTAG_EXPLOSION_FLOOR_SHOCKWAVE) {
                if (effect->actionTimer > 3) {
                    Math_ApproachF(&effect->scale, effect->scaleZ, 0.2f, effect->scaleZ * 0.6666666f);
                    Math_ApproachZeroF(&effect->primColorAlpha, 1.0f, 15.0f);
                    if (effect->primColorAlpha <= 0.0f) {
                        effect->type = CLEARTAG_NO_EFFECT;
                    }
                }
            } else if (effect->type == CLEARTAG_EXPLOSION_BLACK_SMOKE) {
                Math_ApproachZeroF(&effect->primColorR, 1.0f, 20.0f);
                Math_ApproachZeroF(&effect->primColorG, 1.0f, 2.0f);
                Math_ApproachZeroF(&effect->envColorR, 1.0f, 25.5f);
                Math_ApproachZeroF(&effect->envColorG, 1.0f, 21.5f);
                Math_ApproachZeroF(&effect->envColorB, 1.0f, 25.5f);
                Math_ApproachF(&effect->scale, effect->scaleZ, 0.05f, 0.1f);
                if (effect->primColorR == 0.0f) {
                    Math_ApproachF(&effect->scaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&effect->scaleY, 3.0f, 0.1f, 0.02f);
                    Math_ApproachZeroF(&effect->primColorAlpha, 1.0f, 5.f);
                    if (effect->primColorAlpha <= 0.0f) {
                        effect->type = CLEARTAG_NO_EFFECT;
                    }
                }
            } else if (effect->type == CLEARTAG_NO_EXPLOSION_BLACK_SMOKE) {
                Math_ApproachF(&effect->scale, effect->scaleZ, 0.05f, 0.1f);
                if (effect->actionTimer > 10) {
                    Math_ApproachF(&effect->scaleX, 3.0f, 0.1f, 0.01f);
                    Math_ApproachF(&effect->scaleY, 3.0f, 0.1f, 0.02f);
                    Math_ApproachZeroF(&effect->primColorAlpha, 1.0f, 5.f);
                    if (effect->primColorAlpha <= 0.0f) {
                        effect->type = CLEARTAG_NO_EFFECT;
                    }
                }
            } else if (effect->type == CLEARTAG_EXPLOSION_OUTER_CLOUD) {
                Math_ApproachF(&effect->scale, effect->scaleZ, 0.5f, 6.0f);
                Math_ApproachZeroF(&effect->primColorAlpha, 1.0f, 15.0f);
                if (effect->primColorAlpha <= 0.0f) {
                    effect->type = CLEARTAG_NO_EFFECT;
                }
            } else if (effect->type == CLEARTAG_LIGHT_RAY) {
                effect->rotZ += Rand_ZeroFloat(M_PI / 2) + (M_PI / 2);
                effect->lightRayAlpha -= effect->lightRayAlphaDecrementSpeed;
                if (effect->lightRayAlpha <= 0) {
                    effect->lightRayAlpha = 0;
                    effect->type = CLEARTAG_NO_EFFECT;
                }
                effect->primColorAlpha = effect->lightRayAlpha;
                if (effect->primColorAlpha > 255.0f) {
                    effect->primColorAlpha = 255.0f;
                }
                Math_ApproachF(&effect->scaleZ, effect->scaleZTarget, 1.0f, (effect->scaleZTarget / 15.0f) * 4.0f);
            } else if (effect->type == CLEARTAG_EXPLOSION_SPLASH) {
                if (effect->effectsTimer == 0) {
                    effect->scale = 7.0f;
                    Math_ApproachF(&effect->scaleZ, 500.0f, 1.0f, 50.0f);
                    Math_ApproachF(&effect->rotX, 1.5f, 1.0f, 0.12f);
                    if (effect->actionTimer > 7) {
                        effect->type = CLEARTAG_NO_EFFECT;
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

void EnClearTag_DrawEffects(Actor* thisx, GlobalContext* globalCtx) {
    u8 isSetup = 0;
    s16 i;
    s16 j;
    Vec3f vec;
    WaterBox* waterBox;
    f32 ySurface;
    MtxF mtxF;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    EnClearTag* this = THIS;
    EnClearTagEffects* effect = this->effects;
    EnClearTagEffects* effectRef = this->effects;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_EXPLOSION_DEBRIS) {
            if (isSetup == 0) {
                isSetup++;
                gSPDisplayList(POLY_OPA_DISP++, sExplosionDebrisSetupDL);
            }
            SysMatrix_InsertTranslation(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            Matrix_Scale(effect->scale, effect->scale, effect->scale, MTXMODE_APPLY);
            SysMatrix_InsertYRotation_f(effect->rotY, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(effect->rotX);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, sExplosionDebrisVtxDL);
        }
    }

    effect = effectRef;
    if (this->actor.floorPoly != NULL) {
        for (i = 0; i < 103; i++, effect++) {
            if (effect->type == CLEARTAG_EXPLOSION_FLOOR_SHOCKWAVE) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, (s8)effect->primColorAlpha);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s8)effect->primColorAlpha);
                func_800C0094(this->actor.floorPoly, effect->pos.x, effect->pos.y, effect->pos.z, &mtxF);
                SysMatrix_SetCurrentState(&mtxF);
                Matrix_Scale(effect->scale, 1.0f, effect->scale, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, D_04030100);
            }
        }
    }

    isSetup = 0;
    effect = effectRef;
    if (this->actor.floorPoly != NULL) {
        for (i = 0; i < 103; i++, effect++) {
            if (effect->type == CLEARTAG_EXPLOSION_OUTER_CLOUD) {
                if (isSetup == 0) {
                    gDPPipeSync(POLY_XLU_DISP++);
                    gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 200, 0);
                    isSetup++;
                }
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)(effect->primColorAlpha * 0.7f));
                func_800C0094(this->actor.floorPoly, effect->pos.x, this->actor.floorHeight, effect->pos.z, &mtxF);
                SysMatrix_SetCurrentState(&mtxF);
                Matrix_Scale(effect->scale * 3.0f, 1.0f, effect->scale * 3.0f, MTXMODE_APPLY);
                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, sExplosionOuterCloudFloorDL);
            }
        }
    }

    isSetup = 0;
    effect = effectRef;
    for (i = 0; i < 103; i++, effect++) {
        if ((effect->type == CLEARTAG_EXPLOSION_BLACK_SMOKE) || (effect->type == CLEARTAG_NO_EXPLOSION_BLACK_SMOKE)) {
            if (isSetup == 0) {
                gSPDisplayList(POLY_XLU_DISP++, sExplosionBlackSmokeSetupDL);
                isSetup++;
            }
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, (s8)effect->envColorR, (s8)effect->envColorG, (s8)effect->envColorB, 128);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (s8)effect->primColorR, (s8)effect->primColorG,
                            (s8)effect->primColorB, (s8)effect->primColorAlpha);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, -effect->actionTimer * 5, 0x20, 0x40, 1, 0, 0,
                                        0x20, 0x20));
            SysMatrix_InsertTranslation(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(effect->scaleX * effect->scale, effect->scaleY * effect->scale, 1.0f, MTXMODE_APPLY);
            SysMatrix_InsertTranslation(0.0f, 20.0f, 0.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, sExplosionBlackSmokeVtxDL);
        }
    }

    // effect->type never set to 2
    isSetup = 0;
    effect = effectRef;
    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_UNUSED_BLACK_SMOKE) {
            if (isSetup == 0) {
                gSPDisplayList(POLY_XLU_DISP++, sExplosionBlackSmokeSetupDL);
                gDPSetEnvColor(POLY_XLU_DISP++, 255, 215, 255, 128);
                isSetup++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 200, 20, 0, (s8)effect->primColorAlpha);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, -effect->actionTimer * 15, 0x20, 0x40, 1, 0, 0,
                                        0x20, 0x20));
            SysMatrix_InsertTranslation(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(effect->scale, effect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, sExplosionBlackSmokeVtxDL);
        }
    }

    isSetup = 0;
    effect = effectRef;
    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_EXPLOSION_OUTER_CLOUD) {
            if (isSetup == 0) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, this->explosionOuterCloudEnvColor.r,
                               this->explosionOuterCloudEnvColor.g, this->explosionOuterCloudEnvColor.b, 0);
                isSetup++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 200, (s8)effect->primColorAlpha);
            SysMatrix_InsertTranslation(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
            Matrix_Scale(2.0f * effect->scale, 2.0f * effect->scale, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, sExplosionOuterCloudDL);
        }
    }

    isSetup = 0;
    effect = effectRef;
    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_LIGHT_RAY) {
            if (isSetup == 0) {
                gDPPipeSync(POLY_XLU_DISP++);
                gDPSetEnvColor(POLY_XLU_DISP++, (u8)effect->envColorR, (u8)effect->envColorG, (u8)effect->envColorB, 0);
                gSPDisplayList(POLY_XLU_DISP++, sLightRaySetupDL);
                isSetup++;
            }
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, (u8)effect->primColorR, (u8)effect->primColorG,
                            (u8)effect->primColorB, (u8)effect->primColorAlpha);
            SysMatrix_InsertTranslation(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            SysMatrix_InsertYRotation_f(effect->rotY, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(effect->rotX);
            SysMatrix_InsertZRotation_f(effect->rotZ, MTXMODE_APPLY);
            Matrix_Scale(effect->scale * 0.5f, effect->scale * 0.5f, effect->scaleZ * effect->scale, MTXMODE_APPLY);
            SysMatrix_RotateStateAroundXAxis(M_PI / 2);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, sLightRayVtxDL);
        }
    }

    effect = effectRef;
    for (i = 0; i < 103; i++, effect++) {
        if (effect->type == CLEARTAG_EXPLOSION_SPLASH) {
            gDPPipeSync(POLY_XLU_DISP++);
            gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 200);
            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, 200);
            gSPSegment(POLY_XLU_DISP++, 0x08, Lib_SegmentedToVirtual(sExplosionSplashTex[effect->actionTimer]));
            func_8012C9BC(gfxCtx);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BACK);
            isSetup++;
            for (j = 0; j < 16; j++) {
                SysMatrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_NEW);
                SysMatrix_GetStateTranslationAndScaledZ(effect->scaleZ, &vec);
                ySurface = effect->pos.y;
                if (func_800CA1AC(globalCtx, &globalCtx->colCtx, effect->pos.x + vec.x, effect->pos.z + vec.z,
                                  &ySurface, &waterBox)) {
                    if ((effect->pos.y - ySurface) < 200.0f) {
                        SysMatrix_InsertTranslation(effect->pos.x + vec.x, ySurface, effect->pos.z + vec.z,
                                                    MTXMODE_NEW);
                        SysMatrix_InsertYRotation_f(2.0f * (j * M_PI) * (1.0f / 16.0f), MTXMODE_APPLY);
                        SysMatrix_RotateStateAroundXAxis(effect->rotX);
                        Matrix_Scale(effect->scale, effect->scale, effect->scale, MTXMODE_APPLY);
                        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                        gSPDisplayList(POLY_XLU_DISP++, D_0403A0F0);
                    }
                }
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
