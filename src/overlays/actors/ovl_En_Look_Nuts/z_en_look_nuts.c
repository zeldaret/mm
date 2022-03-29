/*
 * File: z_en_look_nuts.c
 * Overlay: ovl_En_Look_Nuts
 * Description: Deku Palace - Patrolling Deku Guard
 */

#include "z_en_look_nuts.h"

#define FLAGS (ACTOR_FLAG_80000000)

#define THIS ((EnLookNuts*)thisx)

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnLookNuts_SetupPatrol(EnLookNuts* this);
void EnLookNuts_Patrol(EnLookNuts* this, GlobalContext* globalCtx);
void EnLookNuts_SetupStandAndWait(EnLookNuts* this);
void EnLookNuts_StandAndWait(EnLookNuts* this, GlobalContext* globalCtx);
void EnLookNuts_RunToPlayer(EnLookNuts* this, GlobalContext* globalCtx);
void EnLookNuts_SetupSendPlayerToSpawn(EnLookNuts* this);
void EnLookNuts_SendPlayerToSpawn(EnLookNuts* this, GlobalContext* globalCtx);

const ActorInit En_Look_Nuts_InitVars = {
    ACTOR_EN_LOOK_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnLookNuts),
    (ActorFunc)EnLookNuts_Init,
    (ActorFunc)EnLookNuts_Destroy,
    (ActorFunc)EnLookNuts_Update,
    (ActorFunc)EnLookNuts_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 20, 50, 0, { 0, 0, 0 } },
};

s32 D_80A6862C = 0;

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(1, 0xF),
    /* Deku Stick     */ DMG_ENTRY(1, 0xF),
    /* Horse trample  */ DMG_ENTRY(1, 0xF),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(1, 0xF),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(1, 0xF),
    /* Hookshot       */ DMG_ENTRY(1, 0xE),
    /* Goron punch    */ DMG_ENTRY(1, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
    /* Deku spin      */ DMG_ENTRY(1, 0xF),
    /* Deku bubble    */ DMG_ENTRY(1, 0xF),
    /* Deku launch    */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(1, 0xF),
    /* Zora barrier   */ DMG_ENTRY(1, 0xF),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(1, 0xF),
    /* Normal Roll    */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0xF),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0xF),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(1, 0xF),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

typedef enum {
    /* 0x01 */ PALACE_GUARD_PATROLLING,
    /* 0x01 */ PALACE_GUARD_WAITING,
    /* 0x02 */ PALACE_GUARD_RUNNING_TO_PLAYER,
    /* 0x03 */ PALACE_GUARD_CAUGHT_PLAYER
} PalaceGuardState;

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnLookNuts* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 20.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &gDekuPalaceGuardSkel, &gDekuPalaceGuardDigAnim, this->jointTable,
                   this->morphTable, OBJECT_DNK_LIMB_MAX);
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.damageTable = &sDamageTable;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->actor.targetMode = 1;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->actor.flags |= ACTOR_FLAG_8000000;
    this->pathLocation = LOOKNUTS_GET_PATROL_LOCATION(&this->actor);
    this->switchFlag = LOOKNUTS_GET_SCENE_FLAG(&this->actor);
    this->spawnIndex = LOOKNUTS_GET_SPAWN_INDEX(&this->actor);

    if (this->switchFlag == 0x7F) {
        this->switchFlag = -1;
    }
    if ((this->switchFlag >= 0) && (Flags_GetSwitch(globalCtx, this->switchFlag))) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (this->pathLocation == 0x1F) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->state = PALACE_GUARD_PATROLLING;
    EnLookNuts_SetupPatrol(this);
}

void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnLookNuts* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnLookNuts_SetupPatrol(EnLookNuts* this) {
    Animation_Change(&this->skelAnime, &gDekuPalaceGuardWalkAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gDekuPalaceGuardWalkAnim), 0, -10.0f);
    this->state = PALACE_GUARD_PATROLLING;
    this->actionFunc = EnLookNuts_Patrol;
}

void EnLookNuts_Patrol(EnLookNuts* this, GlobalContext* globalCtx) {
    f32 sp34 = 0.0f;
    f32 sp30;

    SkelAnime_Update(&this->skelAnime);
    if (Play_InCsMode(globalCtx)) {
        this->actor.speedXZ = 0.0f;
        return;
    }

    this->actor.speedXZ = 2.0f;
    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }

    if (D_80A6862C != 0) {
        Math_ApproachZeroF(&this->actor.speedXZ, 0.3f, 1.0f);
        return;
    }

    this->path = SubS_GetPathByIndex(globalCtx, this->pathLocation, 0x1F);
    if (this->path != NULL) {
        sp34 = SubS_GetDistSqAndOrientPath(this->path, this->currentPathIndex, &this->actor.world.pos, &sp30);
    }

    if (sp30 < 10.0f) {
        if (this->path != NULL) {
            this->currentPathIndex++;
            if (this->currentPathIndex >= this->path->count) {
                this->currentPathIndex = 0;
            }
            if (Rand_ZeroOne() < 0.6f) {
                EnLookNuts_SetupStandAndWait(this);
                return;
            }
        }
    }
    Math_SmoothStepToS(&this->actor.shape.rot.y, sp34, 1, 0x1388, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnLookNuts_SetupStandAndWait(EnLookNuts* this) {
    Animation_Change(&this->skelAnime, &gDekuPalaceGuardWalkAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gDekuPalaceGuardWalkAnim), 2, -10.0f);
    this->waitTimer = Rand_S16Offset(1, 3);
    this->headRotTarget.y = 10000.0f;

    if (Rand_ZeroOne() < 0.5f) {
        this->headRotTarget.y = -10000.0f;
    }
    this->eventTimer = 10;
    this->state = PALACE_GUARD_WAITING;
    this->actionFunc = EnLookNuts_StandAndWait;
}

// Patrol Guards will stand in place and wait for a maximum of ~12 frames.
void EnLookNuts_StandAndWait(EnLookNuts* this, GlobalContext* globalCtx) {
    s16 randOffset;

    SkelAnime_Update(&this->skelAnime);
    Math_ApproachZeroF(&this->actor.speedXZ, 0.3f, 1.0f);
    if (!Play_InCsMode(globalCtx) && (D_80A6862C == 0) && (this->eventTimer == 0)) {
        this->eventTimer = 10;
        switch (this->waitTimer) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
                this->waitTimer++;
                this->headRotTarget.y *= -1.0f;
                break;
            case 5:
                this->headRotTarget.y = 0.0f;
                randOffset = Rand_S16Offset(1, 2);
                this->eventTimer = 0;
                this->waitTimer += randOffset;
                break;
            case 6:
                if (fabsf(this->headRotTarget.y - this->headRotation.y) < 10.0f) {
                    this->waitTimer = 10;
                    this->headRotTarget.x = 4000.0f;
                    this->eventTimer = 5;
                }
                break;
            case 7:
                if (fabsf(this->headRotTarget.y - this->headRotation.y) < 10.0f) {
                    this->headRotTarget.z = 4000.0f;
                    this->waitTimer++;
                }
                break;
            case 8:
                this->waitTimer = 10;
                this->eventTimer = 20;
                this->headRotTarget.z = -8000.0f;
                break;
            case 10:
                Math_Vec3f_Copy(&this->headRotTarget, &gZeroVec3f);
                this->waitTimer = 11;
                break;
            case 11:
                if ((fabsf(this->headRotation.x) < 30.0f) && (fabsf(this->headRotation.y) < 30.0f) &&
                    (fabsf(this->headRotation.z) < 30.0f)) {
                    this->waitTimer = 12;
                }
                break;
        }
        if (this->waitTimer == 12) {
            this->waitTimer = 0;
            EnLookNuts_SetupPatrol(this);
        }
    }
}

void EnLookNuts_DetectedPlayer(EnLookNuts* this, GlobalContext* globalCtx) {
    Animation_Change(&this->skelAnime, &gDekuPalaceGuardWalkAnim, 2.0f, 0.0f,
                     Animation_GetLastFrame(&gDekuPalaceGuardWalkAnim), 0, -10.0f);
    this->state = PALACE_GUARD_RUNNING_TO_PLAYER;
    this->eventTimer = 300;
    Message_StartTextbox(globalCtx, 0x833, &this->actor);
    this->actionFunc = EnLookNuts_RunToPlayer;
}

void EnLookNuts_RunToPlayer(EnLookNuts* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 5.0f)) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_NUTS_WALK);
    }

    this->actor.speedXZ = 4.0f;
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 0xBB8, 0);
    if ((this->actor.xzDistToPlayer < 70.0f) || (this->eventTimer == 0)) {
        this->actor.speedXZ = 0.0f;
        EnLookNuts_SetupSendPlayerToSpawn(this);
    }
}

void EnLookNuts_SetupSendPlayerToSpawn(EnLookNuts* this) {
    Animation_Change(&this->skelAnime, &gDekuPalaceGuardWalkAnim, 1.0f, 0.0f,
                     Animation_GetLastFrame(&gDekuPalaceGuardWalkAnim), 2, -10.0f);
    this->state = PALACE_GUARD_CAUGHT_PLAYER;
    this->actionFunc = EnLookNuts_SendPlayerToSpawn;
}

void EnLookNuts_SendPlayerToSpawn(EnLookNuts* this, GlobalContext* globalCtx) {
    SkelAnime_Update(&this->skelAnime);
    Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 1, 0xBB8, 0);
    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        func_801477B4(globalCtx);
        globalCtx->nextEntranceIndex = Entrance_CreateIndexFromSpawn(this->spawnIndex);
        gSaveContext.nextCutsceneIndex = 0;
        Scene_SetExitFade(globalCtx);
        globalCtx->sceneLoadFlag = 0x14;
        gSaveContext.save.weekEventReg[17] |= 4;
    }
}

static Vec3f effectVecInitialize = { 0.0f, 0.0f, 0.0f };

void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnLookNuts* this = THIS;
    Vec3f effectVelOffset;
    Vec3f effectPos;
    Vec3f effectVel;

    if (this->blinkTimer == 0) {
        this->eyeState++;
        if (this->eyeState >= 3) {
            this->eyeState = 0;
            this->blinkTimer = (s16)Rand_ZeroFloat(60.0f) + 20;
        }
    }
    this->actionFunc(this, globalCtx);
    if (this->blinkTimer != 0) {
        this->blinkTimer--;
    }
    if (this->eventTimer != 0) {
        this->eventTimer--;
    }
    Actor_MoveWithGravity(&this->actor);
    if (D_80A6862C == 0) {
        if ((this->state < 2) && (this->actor.xzDistToPlayer < 320.0f) && (this->actor.playerHeightRel < 80.0f)) {
            effectVelOffset = effectVecInitialize;
            Math_Vec3f_Copy(&effectPos, &this->actor.world.pos);
            effectPos.x += Math_SinS((this->actor.world.rot.y + (s16)this->headRotation.y)) * 10.0f;
            effectPos.y += 30.0f;
            effectPos.z += Math_CosS((this->actor.world.rot.y + (s16)this->headRotation.y)) * 10.0f;
            Matrix_StatePush();
            Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
            effectVelOffset.z = 20.0f;
            Matrix_MultiplyVector3fByState(&effectVelOffset, &effectVel);
            Matrix_StatePop();
            if (!this->isPlayerDetected) {
                s16 drawFlag = 1;
                if (gSaveContext.save.isNight) {
                    drawFlag = 0;
                }
                if (Player_GetMask(globalCtx) != PLAYER_MASK_STONE) {
                    EffectSsSolderSrchBall_Spawn(globalCtx, &effectPos, &effectVel, &gZeroVec3f, 50,
                                                 &this->isPlayerDetected, drawFlag);
                }
            }

            if ((this->isPlayerDetected == true) || (this->actor.xzDistToPlayer < 20.0f)) {
                Player* player = GET_PLAYER(globalCtx);

                if (!(player->stateFlags3 & 0x100) && !Play_InCsMode(globalCtx)) {
                    Math_Vec3f_Copy(&this->headRotTarget, &gZeroVec3f);
                    this->state = PALACE_GUARD_RUNNING_TO_PLAYER;
                    play_sound(NA_SE_SY_FOUND);
                    func_800B7298(globalCtx, &this->actor, 0x1A);
                    D_80A6862C = 1;
                    this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_10);
                    this->actor.gravity = 0.0f;
                    EnLookNuts_DetectedPlayer(this, globalCtx);
                } else {
                    this->isPlayerDetected = false;
                }
            }
        }
        Math_ApproachF(&this->headRotation.x, this->headRotTarget.x, 1.0f, 3000.0f);
        Math_ApproachF(&this->headRotation.y, this->headRotTarget.y, 1.0f, 6000.0f);
        Math_ApproachF(&this->headRotation.z, this->headRotTarget.z, 1.0f, 2000.0f);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

static TexturePtr sEyeTextures[] = {
    gDekuPalaceGuardEyeOpenTex,
    gDekuPalaceGuardEyeHalfTex,
    gDekuPalaceGuardEyeClosedTex,
};

void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnLookNuts* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeState]));
    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, NULL, NULL, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
