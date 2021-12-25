/*
 * File: z_en_bigokuta.c
 * Overlay: ovl_En_Bigokuta
 * Description: Big Octo
 */

#include "z_en_bigokuta.h"
#include "assets/objects/object_bigokuta/object_bigokuta.h"

#define FLAGS 0x00000005

#define THIS ((EnBigokuta*)thisx)

void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AC2B4C(GlobalContext* globalCtx, EnBigokuta* this);
void EnBigokuta_SetupIdle(EnBigokuta* this);
void EnBigokuta_Idle(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_PlayRiseEffects(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_RiseOutOfWater(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_SetupIdleAboveWater(EnBigokuta* this);
void EnBigokuta_IdleAboveWater(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_SuckInPlayer(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC31EC(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_SetupShootPlayer(EnBigokuta* this);
void EnBigokuta_ShootPlayer(EnBigokuta* this, GlobalContext* globalCtx);
void func_80AC34A8(EnBigokuta* this, GlobalContext* globalCtx);
void EnBigokuta_SetupDeathEffects(EnBigokuta* this);
void EnBigokuta_PlayDeathEffects(EnBigokuta* this, GlobalContext* globalCtx);

const ActorInit En_Bigokuta_InitVars = {
    ACTOR_EN_BIGOKUTA,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BIGOKUTA,
    sizeof(EnBigokuta),
    (ActorFunc)EnBigokuta_Init,
    (ActorFunc)EnBigokuta_Destroy,
    (ActorFunc)EnBigokuta_Update,
    (ActorFunc)EnBigokuta_Draw,
};

static ColliderCylinderInit sCylinder1Init = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFC74F, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 75, 125, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinder2Init = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x000038B0, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 70, 125, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit sColChkInfoInit = { 4, 130, 120, MASS_HEAVY };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 89, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 33, ICHAIN_STOP),
};

void EnBigokuta_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gBigOctoSkel, &gBigOctoIdleAnim, this->jointTable,
                       this->morphTable, 0x14);

    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinder1Init);
    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinder2Init);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &sColChkInfoInit);
    this->cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);

    if ((gSaveContext.weekEventReg[20] & 2) ||
        ((this->actor.params != 0xFF) && (Flags_GetSwitch(globalCtx, this->actor.params)))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.world.pos.y -= 99.0f;
        EnBigokuta_SetupIdle(this);
    }

    this->camAt.x = ((Math_SinS(this->actor.home.rot.y) * 66.0f) + this->actor.world.pos.x);
    this->camAt.y = ((this->actor.home.pos.y - 49.5f) + 42.899998f);
    this->camAt.z = ((Math_CosS(this->actor.home.rot.y) * 66.0f) + this->actor.world.pos.z);
    this->unkFunc = func_80AC2B4C;
}

void EnBigokuta_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

void EnBigokuta_SetupCutsceneCamera(EnBigokuta* this, GlobalContext* globalCtx, Vec3f* at, Vec3f* eye) {
    s16 phi_a0;

    ActorCutscene_Start(this->actor.cutscene, &this->actor);
    this->camId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    Play_CameraSetAtEye(globalCtx, this->camId, at, eye);
    phi_a0 = BINANG_SUB(Actor_YawToPoint(&this->actor, eye), this->actor.home.rot.y);
    if (phi_a0 > 0) {
        phi_a0 = BINANG_ADD(this->actor.home.rot.y, 0x1800);
    } else {
        phi_a0 = BINANG_SUB(this->actor.home.rot.y, 0x1800);
    }
    this->camEye.x = (Math_SinS(phi_a0) * 250.0f) + this->camAt.x;
    this->camEye.y = (this->camAt.y + 100.0f);
    this->camEye.z = (Math_CosS(phi_a0) * 250.0f) + this->camAt.z;
}

void func_80AC299C(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera = Play_GetCamera(globalCtx, this->camId);

    Math_Vec3f_StepTo(&camera->eye, &this->camEye, 20.0f);
    Math_Vec3f_StepTo(&camera->at, &this->camAt, 20.0f);
    Play_CameraSetAtEye(globalCtx, this->camId, &camera->at, &camera->eye);
}

void EnBigokuta_ResetCamera(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (this->camId != 0) {
        camera = Play_GetCamera(globalCtx, this->camId);
        Play_CameraSetAtEye(globalCtx, 0, &camera->at, &camera->eye);
        this->camId = 0;
        ActorCutscene_Stop(this->actor.cutscene);
    }
}

void EnBigokuta_ReleasePlayer(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (&this->actor == player->actor.parent) {
        player->actor.parent = NULL;
        player->unk_AE8 = 100;
        player->actor.velocity.y = 0.0f;
        player->actor.world.pos.x += 20.0f * Math_SinS(this->actor.home.rot.y);
        player->actor.world.pos.z += 20.0f * Math_CosS(this->actor.home.rot.y);
        func_800B8D50(globalCtx, &this->actor, 10.0f, this->actor.home.rot.y, 10.0f, 4);
    }
    EnBigokuta_ResetCamera(this, globalCtx);
}

/*
 * Set in Init, never seen again.
 */
void func_80AC2B4C(GlobalContext* globalCtx, EnBigokuta* this) {
    func_8013A530(globalCtx, &this->actor, 3, &this->actor.focus.pos, &this->actor.shape.rot, 280.0f, 1800.0f, -1);
}

s32 func_80AC2B98(EnBigokuta* this, GlobalContext* globalCtx) {
    DynaWaterBoxList list;

    this->actor.floorHeight = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &list.unk0,
                                                          &this->actor, &this->actor.world.pos);
    if (!WaterBox_GetSurface1_2(globalCtx, &globalCtx->colCtx, this->actor.world.pos.x, this->actor.world.pos.z,
                                &this->actor.home.pos.y, &list.boxes) ||
        (this->actor.home.pos.y <= this->actor.floorHeight)) {
        return false;
    } else {
        return true;
    }
}

void EnBigokuta_SpawnRipple(EnBigokuta* this, GlobalContext* globalCtx) {
    Vec3f ripplePos;

    ripplePos.x = this->actor.world.pos.x;
    ripplePos.y = this->actor.home.pos.y;
    ripplePos.z = this->actor.world.pos.z;
    EffectSsGRipple_Spawn(globalCtx, &ripplePos, 1000, 1400, 0);
}

void EnBigokuta_SetupIdle(EnBigokuta* this) {
    Animation_Change(&this->skelAnime, &gBigOctoIdleAnim, 0.5f, 0.0f, 0.0f, 1, -3.0f);
    this->actionFunc = EnBigokuta_Idle;
}

void EnBigokuta_Idle(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 99.0f, 2.5f);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000);
    if ((this->actor.xzDistToPlayer < 300.0f) && ((player->actor.world.pos.y - this->actor.home.pos.y) < 100.0f)) {
        EnBigokuta_PlayRiseEffects(this, globalCtx);
    }
}

void EnBigokuta_PlayRiseEffects(EnBigokuta* this, GlobalContext* globalCtx) {
    Vec3f splashPos;
    s32 i;
    s16 angle = 0;

    Animation_PlayOnce(&this->skelAnime, &gBigOctoRiseOutOfWaterAnim);
    splashPos.y = this->actor.home.pos.y;
    for (i = 0; i < 8; i++) {
        splashPos.x = (Math_SinS(angle) * 70.0f) + this->actor.world.pos.x;
        splashPos.z = (Math_CosS(angle) * 70.0f) + this->actor.world.pos.z;
        EffectSsGSplash_Spawn(globalCtx, &splashPos, NULL, NULL, 0, Rand_S16Offset(1000, 200));
        angle = BINANG_ADD(angle, 0x2000);
    }
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_LAND);
    this->actionFunc = EnBigokuta_RiseOutOfWater;
}

void EnBigokuta_RiseOutOfWater(EnBigokuta* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 15.0f);
    if (SkelAnime_Update(&this->skelAnime)) {
        EnBigokuta_SetupIdleAboveWater(this);
    }
}

void EnBigokuta_SetupIdleAboveWater(EnBigokuta* this) {
    Animation_MorphToLoop(&this->skelAnime, &gBigOctoIdleAnim, -5.0f);
    this->actionFunc = EnBigokuta_IdleAboveWater;
}

void EnBigokuta_IdleAboveWater(EnBigokuta* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 2.5f);
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x1000);

    if ((this->actor.xzDistToPlayer > 400.0f) || (this->actor.playerHeightRel > 200.0f)) {
        Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_SINK);
        EnBigokuta_SetupIdle(this);
    } else if ((this->actor.xzDistToPlayer < 200.0f) &&
               globalCtx->grabPlayer(globalCtx, GET_PLAYER(globalCtx))) {
        EnBigokuta_SuckInPlayer(this, globalCtx);
    }
}

void func_80AC3054(EnBigokuta* this, GlobalContext* globalCtx) {
    Camera* camera;

    if (this->actor.cutscene != -1) {
        if (this->camId != 0) {
            func_80AC299C(this, globalCtx);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            camera = Play_GetCamera(globalCtx, 0);
            EnBigokuta_SetupCutsceneCamera(this, globalCtx, &camera->at, &camera->eye);
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void EnBigokuta_SuckInPlayer(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    player->actor.parent = &this->actor;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
    this->unk_192 = 0;
    Animation_Change(&this->skelAnime, &gBigOctoIdleAnim, 1.0f, 12.0f, 12.0f, 2, -3.0f);
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->unk_2A0.x = ((Math_SinS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.x);
    this->unk_2A0.y = ((this->actor.home.pos.y - 49.5f) + 42.899998f);
    this->unk_2A0.z = ((Math_CosS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.z);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_SLIME_DEAD);
    this->actionFunc = func_80AC31EC;
}

void func_80AC31EC(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    func_80AC3054(this, globalCtx);
    SkelAnime_Update(&this->skelAnime);
    Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 49.5f, 10.0f);
    if (this->unk_192 < 9) {
        this->unk_192++;
    }

    player->unk_AE8 = 0;
    Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_294);
    if (Math_Vec3f_StepTo(&player->actor.world.pos, &this->unk_2A0, sqrtf(this->unk_192) * 5.0f) < 0.1f) {
        s16 rotY = this->actor.shape.rot.y;

        if (Math_ScaledStepToS(&this->actor.shape.rot.y, this->actor.home.rot.y, 0x800)) {
            EnBigokuta_SetupShootPlayer(this);
        }

        this->unk_2A0.x = (Math_SinS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.x;
        this->unk_2A0.y = (this->actor.home.pos.y - 49.5f) + 42.899998f;
        this->unk_2A0.z = (Math_CosS(this->actor.shape.rot.y) * 66.0f) + this->actor.world.pos.z;
        Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_2A0);
        Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
        player->actor.shape.rot.y += BINANG_SUB(this->actor.shape.rot.y, rotY);
    } else {
        Math_Vec3f_Copy(&this->unk_294, &player->actor.world.pos);
        player->actor.velocity.y = 0.0f;
    }
}

void EnBigokuta_SetupShootPlayer(EnBigokuta* this) {
    this->unk_192 = 0xC;
    this->actionFunc = EnBigokuta_ShootPlayer;
}

void EnBigokuta_ShootPlayer(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    this->unk_192--;
    if (this->unk_192 >= 0) {
        func_80AC3054(this, globalCtx);
        Math_Vec3f_Copy(&player->actor.world.pos, &this->unk_2A0);
        if (this->unk_192 == 0) {
            EnBigokuta_ReleasePlayer(this, globalCtx);
            Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_REVERSE);
        }
    } else if (this->unk_192 == -0x18) {
        EnBigokuta_SetupIdleAboveWater(this);
    }
}

void func_80AC3460(EnBigokuta* this) {
    ActorCutscene_SetIntentToPlay(this->cutscene);
    this->unk_192 = 0;
    this->collider2.base.acFlags &= ~1;
    this->actionFunc = func_80AC34A8;
}

void func_80AC34A8(EnBigokuta* this, GlobalContext* globalCtx) {
    Player* player;

    this->actor.colorFilterTimer = Animation_GetLastFrame(&gBigOctoDeathAnim);
    if (this->unk_192 != 0) {
        this->unk_192--;
        if (this->unk_192 == 0) {
            this->unk_190 = 0;
            this->unk_288.x = 0.0f;
            func_800BF7CC(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), 2, 0.5f, 0.35f);
            EnBigokuta_SetupDeathEffects(this);
        }
    } else if (ActorCutscene_GetCanPlayNext(this->cutscene)) {
        ActorCutscene_Start(this->cutscene, &this->actor);
        if ((!(gSaveContext.eventInf[4] & 2)) && (!(gSaveContext.eventInf[3] & 0x20))) {
            func_800B724C(globalCtx, &this->actor, 7);
        } else {
            player = GET_PLAYER(globalCtx);
            player->stateFlags1 |= 0x20;
        }

        if (this->unk_190 == 0xA) {
            this->unk_192 = 3;
        } else {
            EnBigokuta_SetupDeathEffects(this);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->cutscene);
    }
}

void EnBigokuta_SetupDeathEffects(EnBigokuta* this) {
    Animation_MorphToPlayOnce(&this->skelAnime, &gBigOctoDeathAnim, -5.0f);
    Audio_PlayActorSound2(&this->actor, NA_SE_EN_DAIOCTA_DEAD2);
    this->actor.flags &= -2;
    this->unk_192 = 0xA;
    this->actionFunc = EnBigokuta_PlayDeathEffects;
}

static Vec3f D_80AC45A4 = { 0.0f, -0.5f, 0.0f };
static Color_RGBA8 D_80AC45B0 = { 255, 255, 255, 255 };
static Color_RGBA8 D_80AC45B4 = { 100, 255, 255, 255 };
static Color_RGBA8 D_80AC45B8 = { 150, 150, 150, 0 };
void EnBigokuta_PlayDeathEffects(EnBigokuta* this, GlobalContext* globalCtx) {
    if (SkelAnime_Update(&this->skelAnime)) {
        this->actor.world.pos.y -= 0.2f;
        if (this->unk_192 > 0) {
            this->unk_192--;
            if (this->unk_192 == 6) {
                Vec3f dustPos;

                dustPos.x = this->actor.world.pos.x;
                dustPos.y = this->actor.world.pos.y + 150.0f;
                dustPos.z = this->actor.world.pos.z;
                func_800B0DE0(globalCtx, &dustPos, &D_801D15B0, &D_801D15B0, &D_80AC45B0, &D_80AC45B4, 1200, 20);
                Audio_PlayActorSound2(&this->actor, NA_SE_EN_OCTAROCK_DEAD2);
            }
        } else {
            this->actor.world.pos.y -= 0.2f;
            if (Math_StepToF(&this->actor.scale.y, 0.001f, 0.001f)) {
                s32 i;
                Vec3f bubbleVel;
                Vec3f bubblePos;

                Audio_PlaySoundAtPosition(globalCtx, &this->actor.world.pos, 0x32, NA_SE_EN_COMMON_WATER_MID);
                bubblePos.y = this->actor.world.pos.y;
                for (i = 0; i < 20; i++) {
                    bubbleVel.x = randPlusMinusPoint5Scaled(10.0f);
                    bubbleVel.y = Rand_ZeroFloat(5.5f) + 5.5f;
                    bubbleVel.z = randPlusMinusPoint5Scaled(10.0f);
                    bubblePos.x = this->actor.world.pos.x + (2.0f * bubbleVel.x);
                    bubblePos.z = this->actor.world.pos.z + (2.0f * bubbleVel.z);
                    EffectSsDtBubble_SpawnCustomColor(globalCtx, &bubblePos, &bubbleVel, &D_80AC45A4, &D_80AC45B0, &D_80AC45B8,
                                                      Rand_S16Offset(150, 50), 25, 0);
                }

                if (this->actor.params != 0xFF) {
                    Actor_SetSwitchFlag(globalCtx, this->actor.params);
                }
                ActorCutscene_Stop(this->cutscene);
                Actor_MarkForDeath(&this->actor);

                if ((!(gSaveContext.eventInf[4] & 2)) && (!(gSaveContext.eventInf[3] & 0x20))) {
                    func_800B724C(globalCtx, &this->actor, 6);
                } else {
                    Player* player = GET_PLAYER(globalCtx);

                    player->stateFlags1 &= ~0x20;
                }
            }
            if (this->unk_288.x > 0.0f) {
                this->unk_288.x = this->actor.scale.y * 30.30303f;
            }
        }
    } else {
        Math_StepToF(&this->actor.world.pos.y, this->actor.home.pos.y - 16.5f, 15.0f);
    }
}

s32 EnBigokuta_IsNearSwampBoat(EnBigokuta* this, GlobalContext* globalCtx) {
    this->actor.child = func_ActorCategoryIterateById(globalCtx, NULL, ACTORCAT_BG, ACTOR_BG_INGATE);

    if ((this->actor.child != NULL) && (Actor_XZDistanceBetweenActors(&this->actor, this->actor.child) < 250.0f)) {
        return true;
    } else {
        return false;
    }
}

void EnBigokuta_TryDieToSwampBoat(EnBigokuta* this, GlobalContext* globalCtx) {
    if ((this->collider2.base.acFlags & 1) &&
        ((this->collider2.base.acFlags & 2) || (((globalCtx->sceneNum == 0x45) || (globalCtx->sceneNum == 0)) &&
                                                (EnBigokuta_IsNearSwampBoat(this, globalCtx))))) {
        Enemy_StartFinishingBlow(globalCtx, &this->actor);

        if (this->collider2.base.acFlags & 2) {
            if (this->collider2.info.acHitInfo->toucher.dmgFlags & 0x1000) {
                this->unk_190 = 0xA;
                this->unk_288.y = 1.2f;
                this->unk_288.z = 1.8000001f;
                this->unk_288.x = 1.0f;
            } else if (this->collider2.info.acHitInfo->toucher.dmgFlags & 0x2000) {
                this->unk_190 = 0x14;
                this->unk_288.y = 1.2f;
                this->unk_288.x = 4.0f;
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->collider2.info.bumper.hitPos.x,
                            this->collider2.info.bumper.hitPos.y, this->collider2.info.bumper.hitPos.z, 0, 0, 0, 4);
            }
        }

        this->collider2.base.acFlags &= ~2;
        func_800BCB70(&this->actor, 0x4000, 0xFF, 0, Animation_GetLastFrame(&gBigOctoDeathAnim));
        EnBigokuta_ReleasePlayer(this, globalCtx);
        func_80AC3460(this);
    }
}

void EnBigokuta_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;
    s32 pad;

    if (!func_80AC2B98(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    if ((globalCtx->gameplayFrames % 7) == 0) {
        EnBigokuta_SpawnRipple(this, globalCtx);
    }

    EnBigokuta_TryDieToSwampBoat(this, globalCtx);
    this->actionFunc(this, globalCtx);

    if ((this->collider2.base.acFlags & 1) != 0) {
        this->collider1.dim.pos.x = Math_SinS(this->actor.shape.rot.y) * -20.0f + this->actor.world.pos.x;
        this->collider1.dim.pos.y = this->actor.world.pos.y;
        this->collider1.dim.pos.z = Math_CosS(this->actor.shape.rot.y) * -20.0f + this->actor.world.pos.z;

        this->collider2.dim.pos.x = this->collider1.dim.pos.x;
        this->collider2.dim.pos.y = this->collider1.dim.pos.y;
        this->collider2.dim.pos.z = this->collider1.dim.pos.z;

        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        Actor_SetHeight(&this->actor, 82.5f);
    }

    if (this->unk_288.x > 0.0f) {
        if (this->unk_190 != 0xA) {
            Math_StepToF(&this->unk_288.x, 0.0f, 0.05f);
            this->unk_288.y = (this->unk_288.x + 1.0f) * 0.6f;
            this->unk_288.y = CLAMP_MAX(this->unk_288.y, 1.2f);
        } else if (Math_StepToF(&this->unk_288.z, 1.2f, 0.030000001f) == 0) {
            func_800B9010(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
        }
    }
}

s32 EnBigokuta_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                Actor* thisx, Gfx** gfx) {
    if (limbIndex == 0xA) {
        EnBigokuta* this = THIS;
        s32 envColor;
        s16 rotX;
        f32 lastFrame;

        if (this->actionFunc == EnBigokuta_PlayDeathEffects) {
            lastFrame = Animation_GetLastFrame(&gBigOctoDeathAnim);
            envColor = ((255.0f / lastFrame) * (lastFrame - this->skelAnime.curFrame));
        } else {
            envColor = 255;
        }
        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, envColor, envColor, envColor, envColor);

        if (this->actionFunc == func_80AC31EC) {
            rotX = (s16)(this->unk_192 * 6144.0f * (1.0f / 9.0f));
            rot->x -= rotX;
        } else if (this->actionFunc == EnBigokuta_ShootPlayer) {
            if (this->unk_192 == 1) {
                rotX = 0;
            } else if (this->unk_192 == 0) {
                rotX = -0xC00;
            } else if (this->unk_192 > 0) {
                rotX = 0x1800;
            } else {
                rotX = ((this->unk_192 + 0x18) * 0.041666668f * -6144.0f);
            }
            rot->x -= rotX;
        }

    } else if (limbIndex == 0x11) {
        EnBigokuta* this = THIS;
        f32 temp;

        if (this->actionFunc == EnBigokuta_PlayDeathEffects) {
            if (this->unk_192 < 5) {
                Matrix_Scale(1.0f, 1.0f, (this->unk_192 * 0.2f * 0.25f) + 1.0f, MTXMODE_APPLY);
            } else if (this->unk_192 < 8) {
                temp = (this->unk_192 - 5) * (1.0f / 12.0f);
                Matrix_Scale(1.0f + temp, 1.0f + temp, 1.25f - temp, MTXMODE_APPLY);
            } else {
                Matrix_Scale(1.25f - ((this->unk_192 - 8) * 0.125f), 1.25f - ((this->unk_192 - 8) * 0.125f), 1.0f,
                             MTXMODE_APPLY);
            }
        } else if (this->actionFunc == func_80AC31EC) {
            temp = sin_rad(this->unk_192 * (M_PI / 3.0f)) * 0.5f;
            Matrix_Scale(((this->unk_192 * (2.0f / 90.0f)) * (0.5f + temp)) + 1.0f,
                         ((this->unk_192 * (2.0f / 90.0f)) * (0.5f - temp)) + 1.0f,
                         1.0f - ((this->unk_192 * 0.3f) / 9.0f), MTXMODE_APPLY);
        } else if (this->actionFunc == EnBigokuta_ShootPlayer && this->unk_192 != 1) {
            if (this->unk_192 == 0) {
                Matrix_Scale(0.9f, 0.9f, 1.15f, MTXMODE_APPLY);
            } else if (this->unk_192 > 0) {
                temp = sin_rad(this->unk_192 * (M_PI / 3.0f)) * 0.5f;
                Matrix_Scale(((0.5f + temp) * 0.2f) + 1.0f, ((0.5f - temp) * 0.2f) + 1.0f, 0.7f, MTXMODE_APPLY);
            } else {
                Matrix_Scale(1.0f - ((this->unk_192 + 0x18) * 0.2f * 0.041666668f),
                             1.0f - ((this->unk_192 + 0x18) * 0.2f * 0.041666668f),
                             ((this->unk_192 + 0x18) * 0.3f * 0.041666668f) + 1.0f, MTXMODE_APPLY);
            }
        }
    }
    return 0;
}

static s8 D_80AC45BC[] = { -1, -1, -1, 0, -1, 1, -1, 2, -1, 3, 8, 4, -1, 5, -1, -1, -1, -1, 6, 7 };
static Vec3f D_80AC45D0[] = {
    { 0.0f, 2000.0f, 1000.0f },    { 0.0f, 2000.0f, -2000.0f }, { 1700.0f, 700.0f, -600.0f },
    { -1700.0f, 700.0f, -600.0f }, { 0.0f, 500.0f, -2500.0f },
};
void EnBigokuta_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx,
                             Gfx** gfx) {
    EnBigokuta* this = THIS;
    s32 temp_s0;
    s8 temp_v0 = D_80AC45BC[limbIndex];

    if (temp_v0 != -1) {
        if (temp_v0 < 6) {
            Matrix_GetStateTranslationAndScaledX(800.0f, &this->limbPos[temp_v0]);
        } else if (temp_v0 < 8) {
            Matrix_GetStateTranslation(&this->limbPos[temp_v0]);
        } else {
            for (temp_s0 = 0; temp_s0 < 5; temp_s0++) {
                Matrix_MultiplyVector3fByState(&D_80AC45D0[temp_s0], &this->limbPos[temp_v0 + temp_s0]);
            }
        }
    }
}

void EnBigokuta_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnBigokuta* this = THIS;
    Gfx* gfx;
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    if ((this->actionFunc != EnBigokuta_PlayDeathEffects) || (this->unk_192 != 0)) {
        Scene_SetRenderModeXlu(globalCtx, 0, 1);
        gfx = POLY_OPA_DISP;
        gSPDisplayList(&gfx[0], &sSetupDL[0x96]);
        gDPSetEnvColor(&gfx[1], 255, 255, 255, 255);
        POLY_OPA_DISP = SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                           this->skelAnime.dListCount, EnBigokuta_OverrideLimbDraw,
                                           EnBigokuta_PostLimbDraw, &this->actor, &gfx[2]);
    } else {
        Scene_SetRenderModeXlu(globalCtx, 1, 2);
        gfx = POLY_XLU_DISP;
        gSPDisplayList(&gfx[0], &sSetupDL[0x96]);
        gDPSetEnvColor(&gfx[1], 0, 0, 0, (this->actor.scale.y * 7727.273f));
        POLY_XLU_DISP =
            SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable,
                               this->skelAnime.dListCount, NULL, EnBigokuta_PostLimbDraw, &this->actor, &gfx[2]);
    }

    func_800BE680(globalCtx, &this->actor, this->limbPos, ARRAY_COUNT(this->limbPos), this->unk_288.y, this->unk_288.z,
                  this->unk_288.x, this->unk_190);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
