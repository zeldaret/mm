/*
 * File: z_en_ssh.c
 * Overlay: ovl_En_Ssh
 * Description: Cursed Man (Swamp Spider House)
 */

#include "z_en_ssh.h"
#include "objects/object_ssh/object_ssh.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnSsh*)thisx)

void EnSsh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSsh_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnSsh_Wait(EnSsh* this, GlobalContext* globalCtx);
void EnSsh_Idle(EnSsh* this, GlobalContext* globalCtx);
void EnSsh_Land(EnSsh* this, GlobalContext* globalCtx);
void EnSsh_Drop(EnSsh* this, GlobalContext* globalCtx);
void EnSsh_Return(EnSsh* this, GlobalContext* globalCtx);
void EnSsh_Start(EnSsh* this, GlobalContext* globalCtx);

extern AnimationHeader D_06000304;

const ActorInit En_Ssh_InitVars = {
    ACTOR_EN_SSH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SSH,
    sizeof(EnSsh),
    (ActorFunc)EnSsh_Init,
    (ActorFunc)EnSsh_Destroy,
    (ActorFunc)EnSsh_Update,
    (ActorFunc)EnSsh_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 32, 50, -24, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 1, 0, 0, 0, MASS_IMMOVABLE };

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 60, -30, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x04 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 1, { { 0, -240, 0 }, 28 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT6,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

void EnSsh_SetupAction(EnSsh* this, EnSshActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnSsh_SpawnShockwave(EnSsh* this, GlobalContext* globalCtx) {
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.floorHeight;
    pos.z = this->actor.world.pos.z;
    EffectSsBlast_SpawnWhiteCustomScale(globalCtx, &pos, &zeroVec, &zeroVec, 100, 220, 8);
}

s32 EnSsh_CreateBlureEffect(GlobalContext* globalCtx) {
    EffectBlureInit1 blureInit;
    u8 sP1StartColor[4] = { 255, 255, 255, 75 };
    u8 sP2StartColor[4] = { 255, 255, 255, 75 };
    u8 sP1EndColor[4] = { 255, 255, 255, 0 };
    u8 sP2EndColor[4] = { 255, 255, 255, 0 };
    s32 i;
    s32 blureIdx;

    for (i = 0; i < ARRAY_COUNT(blureInit.p1StartColor); i++) {
        blureInit.p1StartColor[i] = sP1StartColor[i];
        blureInit.p2StartColor[i] = sP2StartColor[i];
        blureInit.p1EndColor[i] = sP1EndColor[i];
        blureInit.p2EndColor[i] = sP2EndColor[i];
    }
    blureInit.elemDuration = 6;
    blureInit.unkFlag = false;
    blureInit.calcMode = 3;

    Effect_Add(globalCtx, &blureIdx, 1, 0, 0, &blureInit);
    return blureIdx;
}

s32 EnSsh_CheckCeilingPos(EnSsh* this, GlobalContext* globalCtx) {
    CollisionPoly* poly;
    s32 bgId;
    Vec3f posB;

    posB.x = this->actor.world.pos.x;
    posB.y = this->actor.world.pos.y + 1000.0f;
    posB.z = this->actor.world.pos.z;
    if (!BgCheck_EntityLineTest1(&globalCtx->colCtx, &this->actor.world.pos, &posB, &this->ceilingPos, &poly, false,
                                 false, true, true, &bgId)) {
        return false;
    }
    return true;
}

void EnSsh_AddBlureVertex(EnSsh* this) {
    Vec3f p1Base = { 834.0f, 834.0f, 0.0f };
    Vec3f p2Base = { 834.0f, -584.0f, 0.0f };
    Vec3f p1;
    Vec3f p2;

    p1Base.x *= this->colliderScale;
    p1Base.y *= this->colliderScale;
    p1Base.z *= this->colliderScale;

    p2Base.x *= this->colliderScale;
    p2Base.y *= this->colliderScale;
    p2Base.z *= this->colliderScale;

    Matrix_StatePush();
    Matrix_MultiplyVector3fByState(&p1Base, &p1);
    Matrix_MultiplyVector3fByState(&p2Base, &p2);
    Matrix_StatePop();
    EffectBlure_AddVertex(Effect_GetByIndex(this->blureIdx), &p1, &p2);
}

void EnSsh_AddBlureSpace(EnSsh* this) {
    EffectBlure_AddSpace(Effect_GetByIndex(this->blureIdx));
}

void EnSsh_InitColliders(EnSsh* this, GlobalContext* globalCtx) {
    ColliderCylinderInit* cylinders[] = {
        &sCylinderInit1, &sCylinderInit1, &sCylinderInit1, &sCylinderInit2, &sCylinderInit2, &sCylinderInit2,
    };
    s32 i;
    s32 pad;

    for (i = 0; i < ARRAY_COUNT(this->collider1); i++) {
        Collider_InitAndSetCylinder(globalCtx, &this->collider1[i], &this->actor, cylinders[i]);
    }

    this->collider1[0].info.bumper.dmgFlags = 0x38A9;
    this->collider1[1].info.bumper.dmgFlags = ~0x83038A9;
    this->collider1[2].base.colType = COLTYPE_METAL;
    this->collider1[2].info.bumperFlags = (BUMP_NO_AT_INFO | BUMP_HOOKABLE | BUMP_ON);
    this->collider1[2].info.elemType = ELEMTYPE_UNK2;
    this->collider1[2].info.bumper.dmgFlags = ~0x83038A9;

    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(2), &sColChkInfoInit);
    Collider_InitJntSph(globalCtx, &this->collider2);
    Collider_SetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit, this->collider2Elements);
}

f32 EnSsh_SetAnimation(EnSsh* this, s32 arg0) {
    AnimationHeader* animation[] = { &object_ssh_Anim_006D78, &object_ssh_Anim_001494, &object_ssh_Anim_001494,
                                     &object_ssh_Anim_006788, &object_ssh_Anim_001494, &object_ssh_Anim_001494,
                                     &object_ssh_Anim_006D78 };
    f32 playerbackSpeed[] = { 1.0f, 4.0f, 1.0f, 1.0f, 8.0f, 6.0f, 2.0f };
    u8 mode[] = {
        ANIMMODE_ONCE_INTERP, ANIMMODE_ONCE_INTERP, ANIMMODE_LOOP_INTERP, ANIMMODE_ONCE_INTERP,
        ANIMMODE_LOOP_INTERP, ANIMMODE_LOOP_INTERP, ANIMMODE_LOOP_INTERP,
    };
    f32 frameCount = Animation_GetLastFrame(animation[arg0]);
    s32 pad;

    Animation_Change(&this->skelAnime, animation[arg0], playerbackSpeed[arg0], 0.0f, frameCount, mode[arg0], -6.0f);
    return frameCount;
}

void EnSsh_SetWaitAnimation(EnSsh* this) {
    EnSsh_SetAnimation(this, SSH_ANIM_WAIT);
}

void EnSsh_SetReturnAnimation(EnSsh* this) {
    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALTU_UP);
    EnSsh_SetAnimation(this, SSH_ANIM_UP);
}

void EnSsh_SetLandAnimation(EnSsh* this) {
    this->actor.world.pos.y = this->floorHeightOffset + this->actor.floorHeight;
    this->animTimer = EnSsh_SetAnimation(this, SSH_ANIM_LAND);
}

void EnSsh_SetDropAnimation(EnSsh* this) {
    if (this->unkTimer == 0) {
        this->animTimer = EnSsh_SetAnimation(this, SSH_ANIM_DROP);
    }
    this->actor.velocity.y = -10.0f;
}

void EnSsh_SetStunned(EnSsh* this) {
    if (this->stunTimer == 0) {
        this->stateFlags |= SSH_STATE_ATTACKED;
        this->stunTimer = 120;
        this->actor.colorFilterTimer = 0;
    }
}

void EnSsh_SetColliderScale(EnSsh* this, f32 arg1, f32 arg2) {
    s32 i;
    f32 radius = this->collider2.elements[0].dim.modelSphere.radius;
    f32 height;
    f32 yShift;

    radius *= arg1;
    this->collider2.elements[0].dim.modelSphere.radius = radius;

    for (i = 0; i < ARRAY_COUNT(this->collider1); i++) {
        yShift = this->collider1[i].dim.yShift;
        radius = this->collider1[i].dim.radius;
        height = this->collider1[i].dim.height;

        height *= arg1;
        yShift *= arg1;
        radius *= arg1 * arg2;

        this->collider1[i].dim.yShift = yShift;
        this->collider1[i].dim.radius = radius;
        this->collider1[i].dim.height = height;
    }

    Actor_SetScale(&this->actor, 0.04f * arg1);
    this->floorHeightOffset = 60.0f * arg1;
    this->colliderScale = arg1 * 1.5f;
}

s32 EnSsh_Damaged(EnSsh* this) {
    if ((this->stunTimer == 120) && (this->stateFlags & SSH_STATE_STUNNED)) {
        Actor_SetColorFilter(&this->actor, 0, 200, 0, this->stunTimer);
    }

    if (DECR(this->stunTimer) != 0) {
        Math_SmoothStepToS(&this->maxTurnRate, 10000, 10, 1000, 1);
        return false;
    }

    this->stunTimer = 0;
    this->stateFlags &= ~SSH_STATE_STUNNED;
    this->spinTimer = 0;
    if (this->swayTimer == 0) {
        this->spinTimer = 30;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALTU_ROLL);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_ST_ATTACK);

    return true;
}

void EnSsh_Turn(EnSsh* this, GlobalContext* globalCtx) {
    if (this->hitTimer != 0) {
        this->hitTimer--;
    }

    if (DECR(this->spinTimer) != 0) {
        this->actor.world.rot.y += (s16)(10000.0f * (this->spinTimer / 30.0f));
    } else if ((this->swayTimer == 0) && (this->stunTimer == 0)) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 4, 10000, 1);
    }
    this->actor.shape.rot.y = this->actor.world.rot.y;
}

void EnSsh_Stunned(EnSsh* this, GlobalContext* globalCtx) {
    if ((this->swayTimer == 0) && (this->stunTimer == 0)) {
        Math_SmoothStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer ^ 0x8000, 4, this->maxTurnRate, 1);
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;

    if (this->stunTimer < 30) {
        if (this->stunTimer & 1) {
            this->actor.shape.rot.y += 2000;
        } else {
            this->actor.shape.rot.y -= 2000;
        }
    }
}

void EnSsh_UpdateYaw(EnSsh* this, GlobalContext* globalCtx) {
    if (this->stunTimer != 0) {
        EnSsh_Stunned(this, globalCtx);
    } else {
        EnSsh_Turn(this, globalCtx);
    }
}

void EnSsh_Bob(EnSsh* this, GlobalContext* globalCtx) {
    f32 bobVel = 0.5f;

    if (globalCtx->state.frames & 8) {
        bobVel *= -1.0f;
    }
    Math_SmoothStepToF(&this->actor.velocity.y, bobVel, 0.4f, 1000.0f, 0.0f);
}

s32 EnSsh_IsCloseToLink(EnSsh* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    f32 yDist;

    if (this->stateFlags & SSH_STATE_GROUND_START) {
        return true;
    }

    if (this->unkTimer != 0) {
        return true;
    }

    if (this->swayTimer != 0) {
        return true;
    }

    if (this->animTimer != 0) {
        return true;
    }

    if (this->actor.xzDistToPlayer > 160.0f) {
        return false;
    }

    yDist = this->actor.world.pos.y - player->actor.world.pos.y;
    if ((yDist < 0.0f) || (yDist > 400.0f)) {
        return false;
    }

    if (player->actor.world.pos.y < this->actor.floorHeight) {
        return false;
    }

    return true;
}

s32 EnSsh_IsCloseToHome(EnSsh* this) {
    f32 vel = this->actor.velocity.y;
    f32 nextY = this->actor.world.pos.y + vel * 2.0f;

    if (this->actor.home.pos.y <= nextY) {
        return true;
    }
    return false;
}

s32 EnSsh_IsCloseToGround(EnSsh* this) {
    f32 vel = this->actor.velocity.y;
    f32 nextY = this->actor.world.pos.y + vel * 2.0f;

    if ((nextY - this->actor.floorHeight) <= this->floorHeightOffset) {
        return true;
    }
    return false;
}

void EnSsh_Sway(EnSsh* this) {
    Vec3f swayVecBase;
    Vec3f swayVec;
    f32 temp_f20;
    s16 swayAngle;

    if (this->swayTimer != 0) {
        this->swayAngle += 1600;
        this->swayTimer--;
        if (this->swayTimer == 0) {
            this->swayAngle = 0;
        }

        temp_f20 = (this->swayTimer * (1.0f / 6));
        swayAngle = Math_SinS(this->swayAngle) * (temp_f20 * (0x10000 / 360.0f));
        temp_f20 = this->actor.world.pos.y - this->ceilingPos.y;

        swayVecBase.x = Math_SinS(swayAngle) * temp_f20;
        swayVecBase.y = Math_CosS(swayAngle) * temp_f20;
        swayVecBase.z = 0.0f;

        Matrix_StatePush();
        Matrix_InsertTranslation(this->ceilingPos.x, this->ceilingPos.y, this->ceilingPos.z, MTXMODE_NEW);
        Matrix_InsertYRotation_f(this->actor.world.rot.y * (M_PI / 0x8000), MTXMODE_APPLY);
        Matrix_MultiplyVector3fByState(&swayVecBase, &swayVec);
        Matrix_StatePop();

        this->actor.shape.rot.z = -(swayAngle * 2);
        this->actor.world.pos.x = swayVec.x;
        this->actor.world.pos.z = swayVec.z;
    }
}

void EnSsh_CheckBodyStickHit(EnSsh* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    ColliderInfo* colliderInfo = &this->collider1[0].info;

    if (player->unk_B28 != 0) {
        colliderInfo->bumper.dmgFlags |= 2;
        this->collider1[1].info.bumper.dmgFlags &= ~2;
        this->collider1[2].info.bumper.dmgFlags &= ~2;
    } else {
        colliderInfo->bumper.dmgFlags &= ~2;
        this->collider1[1].info.bumper.dmgFlags |= 2;
        this->collider1[2].info.bumper.dmgFlags |= 2;
    }
}

s32 EnSsh_CheckHitPlayer(EnSsh* this, GlobalContext* globalCtx) {
    s32 i;
    s32 hit = false;

    if ((this->hitCount == 0) && (this->spinTimer == 0)) {
        return false;
    }

    for (i = 0; i < ARRAY_COUNT(this->collider1) / 2; i++) {
        if (this->collider1[3 + i].base.ocFlags2 & OC2_HIT_PLAYER) {
            this->collider1[3 + i].base.ocFlags2 &= ~OC2_HIT_PLAYER;
            hit = true;
        }
    }

    if (!hit) {
        return false;
    }

    this->hitTimer = 30;
    if (this->swayTimer == 0) {
        this->spinTimer = this->hitTimer;
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALTU_ROLL);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_ST_ATTACK);

    globalCtx->damagePlayer(globalCtx, -8);

    func_800B8D98(globalCtx, &this->actor, 4.0f, this->actor.yawTowardsPlayer, 6.0f);
    this->hitCount--;
    return true;
}

s32 EnSsh_CheckHitFront(EnSsh* this) {
    u32 acFlags;

    if (this->collider1[2].base.acFlags) {}
    acFlags = this->collider1[2].base.acFlags;

    if (!!(acFlags & AC_HIT) == 0) {
        return false;
    }

    this->collider1[2].base.acFlags &= ~AC_HIT;
    this->invincibilityTimer = 8;

    if ((this->swayTimer == 0) && (this->hitTimer == 0) && (this->stunTimer == 0)) {
        this->swayTimer = 60;
    }

    return true;
}

s32 EnSsh_CheckHitBack(EnSsh* this, GlobalContext* globalCtx) {
    ColliderCylinder* collider = &this->collider1[0];
    s32 hit = false;

    if (collider->base.acFlags & AC_HIT) {
        collider->base.acFlags &= ~AC_HIT;
        hit = true;
    }

    collider = &this->collider1[1];
    if (collider->base.acFlags & AC_HIT) {
        collider->base.acFlags &= ~AC_HIT;
        hit = true;
    }

    if (!hit) {
        return false;
    }

    this->invincibilityTimer = 8;
    if (this->hitCount <= 0) {
        this->hitCount++;
    }

    if (this->stunTimer == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_ST_DAMAGE);
    }

    EnSsh_SetStunned(this);
    this->stateFlags |= SSH_STATE_STUNNED;
    return false;
}

s32 EnSsh_CollisionCheck(EnSsh* this, GlobalContext* globalCtx) {
    if (this->stunTimer == 0) {
        EnSsh_CheckHitPlayer(this, globalCtx);
    }

    if (EnSsh_CheckHitFront(this)) {
        return false;
    }

    if (globalCtx->actorCtx.unk2 != 0) {
        this->invincibilityTimer = 8;
        if (this->stunTimer == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_COMMON_FREEZE);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_VO_ST_DAMAGE);
        }
        EnSsh_SetStunned(this);
        this->stateFlags |= SSH_STATE_STUNNED;
        return false;
    }

    return EnSsh_CheckHitBack(this, globalCtx);
}

void EnSsh_SetBodyCylinderAC(EnSsh* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider1[0]);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1[0].base);
}

void EnSsh_SetLegsCylinderAC(EnSsh* this, GlobalContext* globalCtx) {
    s16 angleTowardsLink = ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y));

    if (angleTowardsLink < (90 * (0x10000 / 360))) {
        Collider_UpdateCylinder(&this->actor, &this->collider1[2]);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1[2].base);
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider1[1]);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1[1].base);
    }
}

s32 EnSsh_SetCylinderOC(EnSsh* this, GlobalContext* globalCtx) {
    Vec3f colliderOffsets[] = { { 40.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { -40.0f, 0.0f, 0.0f } };
    Vec3f colliderPos;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->collider1) / 2; i++) {
        colliderPos = this->actor.world.pos;

        colliderOffsets[i].x *= this->colliderScale;
        colliderOffsets[i].y *= this->colliderScale;
        colliderOffsets[i].z *= this->colliderScale;

        Matrix_StatePush();
        Matrix_InsertTranslation(colliderPos.x, colliderPos.y, colliderPos.z, MTXMODE_NEW);
        Matrix_InsertYRotation_f(BINANG_TO_RAD(this->initialYaw), MTXMODE_APPLY);
        Matrix_MultiplyVector3fByState(&colliderOffsets[i], &colliderPos);
        Matrix_StatePop();

        this->collider1[3 + i].dim.pos.x = colliderPos.x;
        this->collider1[3 + i].dim.pos.y = colliderPos.y;
        this->collider1[3 + i].dim.pos.z = colliderPos.z;

        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1[3 + i].base);
    }

    return true;
}

void EnSsh_SetColliders(EnSsh* this, GlobalContext* globalCtx) {
    if (this->actor.colChkInfo.health == 0) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
        return;
    }

    if (this->hitTimer == 0) {
        EnSsh_SetCylinderOC(this, globalCtx);
    }

    if (DECR(this->invincibilityTimer) == 0) {
        EnSsh_SetBodyCylinderAC(this, globalCtx);
        EnSsh_SetLegsCylinderAC(this, globalCtx);
    }
}

void EnSsh_Init(Actor* thisx, GlobalContext* globalCtx) {
    // @bug - this symbol no longer exists, reads from a random place in object_ssh_Tex_000190 instead
    f32 frameCount = Animation_GetLastFrame(&D_06000304);
    s32 pad;
    EnSsh* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &object_ssh_Skel_006470, NULL, this->jointTable, this->morphtable, 30);
    Animation_Change(&this->skelAnime, &object_ssh_Anim_001494, 1.0f, 0.0f, frameCount, ANIMMODE_LOOP_INTERP, 0.0f);
    this->blureIdx = EnSsh_CreateBlureEffect(globalCtx);
    EnSsh_InitColliders(this, globalCtx);
    this->stateFlags = 0;
    this->hitCount = 0;
    EnSsh_CheckCeilingPos(this, globalCtx);

    if (!ENSSH_IS_CHILD(&this->actor)) {
        this->stateFlags |= SSH_STATE_FATHER;
    }

    if (!(this->stateFlags & SSH_STATE_FATHER)) {
        EnSsh_SetColliderScale(this, 0.5f, 1.0f);
    } else {
        EnSsh_SetColliderScale(this, 0.75f, 1.0f);
    }

    this->actor.gravity = 0.0f;
    this->initialYaw = this->actor.world.rot.y;
    EnSsh_SetupAction(this, EnSsh_Start);
    if (Inventory_GetSkullTokenCount(globalCtx->sceneNum) >= 30) {
        Actor_MarkForDeath(&this->actor);
    }
}

void EnSsh_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSsh* this = THIS;
    s32 i;

    Effect_Destroy(globalCtx, this->blureIdx);

    for (i = 0; i < ARRAY_COUNT(this->collider1); i++) {
        Collider_DestroyCylinder(globalCtx, &this->collider1[i]);
    }

    Collider_DestroyJntSph(globalCtx, &this->collider2);
}

void EnSsh_Wait(EnSsh* this, GlobalContext* globalCtx) {
    if (EnSsh_IsCloseToLink(this, globalCtx)) {
        EnSsh_SetDropAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Drop);
    } else {
        EnSsh_Bob(this, globalCtx);
    }
}

void EnSsh_Talk(EnSsh* this, GlobalContext* globalCtx) {
    EnSsh_Bob(this, globalCtx);

    if ((Message_GetState(&globalCtx->msgCtx) == 5) && Message_ShouldAdvance(globalCtx)) {
        switch (globalCtx->msgCtx.currentTextId) {
            case 0x904:
            case 0x905:
            case 0x906:
            case 0x908:
            case 0x910:
            case 0x911:
            case 0x912:
            case 0x914:
                func_80151938(globalCtx, globalCtx->msgCtx.currentTextId + 1);
                break;

            default:
                func_801477B4(globalCtx);
                this->actionFunc = EnSsh_Idle;
                break;
        }
    }
}

void func_809756D0(EnSsh* this, GlobalContext* globalCtx) {
    u16 phi_a1;

    if (gSaveContext.save.weekEventReg[34] & 8) {
        phi_a1 = 0x914;
    } else {
        phi_a1 = 0x910;
        gSaveContext.save.weekEventReg[34] |= 8;
    }
    Message_StartTextbox(globalCtx, phi_a1, &this->actor);
}

void EnSsh_Idle(EnSsh* this, GlobalContext* globalCtx) {
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actionFunc = EnSsh_Talk;
        func_809756D0(this, globalCtx);
        return;
    }

    if ((this->unkTimer != 0) && (DECR(this->unkTimer) == 0)) {
        EnSsh_SetAnimation(this, SSH_ANIM_WAIT);
    }

    if ((this->animTimer != 0) && (DECR(this->animTimer) == 0)) {
        EnSsh_SetAnimation(this, SSH_ANIM_WAIT);
    }

    if (!EnSsh_IsCloseToLink(this, globalCtx)) {
        EnSsh_SetReturnAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Return);
        return;
    }

    if (DECR(this->sfxTimer) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALTU_LAUGH);
        this->sfxTimer = 64;
    }

    EnSsh_Bob(this, globalCtx);

    if ((this->unkTimer == 0) && (this->animTimer == 0) && (this->actor.xzDistToPlayer < 100.0f) &&
        Player_IsFacingActor(&this->actor, 0x3000, globalCtx)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }
}

void EnSsh_Land(EnSsh* this, GlobalContext* globalCtx) {
    if ((this->unkTimer != 0) && (DECR(this->unkTimer) == 0)) {
        EnSsh_SetAnimation(this, SSH_ANIM_WAIT);
    }

    if ((this->animTimer != 0) && (DECR(this->animTimer) == 0)) {
        EnSsh_SetAnimation(this, SSH_ANIM_WAIT);
    }

    if ((this->actor.floorHeight + this->floorHeightOffset) <= this->actor.world.pos.y) {
        EnSsh_SetupAction(this, EnSsh_Idle);
    } else {
        Math_SmoothStepToF(&this->actor.velocity.y, 2.0f, 0.6f, 1000.0f, 0.0f);
    }
}

void EnSsh_Drop(EnSsh* this, GlobalContext* globalCtx) {
    if ((this->unkTimer != 0) && (DECR(this->unkTimer) == 0)) {
        EnSsh_SetAnimation(this, SSH_ANIM_DROP);
    }

    if (!EnSsh_IsCloseToLink(this, globalCtx)) {
        EnSsh_SetReturnAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Return);
    } else if (EnSsh_IsCloseToGround(this)) {
        EnSsh_SpawnShockwave(this, globalCtx);
        EnSsh_SetLandAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Land);
    } else if (DECR(this->sfxTimer) == 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_STALTU_DOWN);
        this->sfxTimer = 3;
    }
}

void EnSsh_Return(EnSsh* this, GlobalContext* globalCtx) {
    f32 frameRatio = this->skelAnime.curFrame / (this->skelAnime.animLength - 1.0f);

    if (frameRatio == 1.0f) {
        EnSsh_SetReturnAnimation(this);
    }

    if (EnSsh_IsCloseToLink(this, globalCtx)) {
        EnSsh_SetDropAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Drop);
    } else if (EnSsh_IsCloseToHome(this)) {
        EnSsh_SetWaitAnimation(this);
        EnSsh_SetupAction(this, EnSsh_Wait);
    } else {
        this->actor.velocity.y = 4.0f * frameRatio;
    }
}

void EnSsh_UpdateColliderScale(EnSsh* this) {
    if (this->stateFlags & SSH_STATE_SPIN) {
        if (this->spinTimer == 0) {
            this->stateFlags &= ~SSH_STATE_SPIN;
            if (!(this->stateFlags & SSH_STATE_FATHER)) {
                EnSsh_SetColliderScale(this, 0.5f, 1.0f);
            } else {
                EnSsh_SetColliderScale(this, 0.75f, 1.0f);
            }
        }
    } else if (this->spinTimer != 0) {
        this->stateFlags |= SSH_STATE_SPIN;
        if (!(this->stateFlags & SSH_STATE_FATHER)) {
            EnSsh_SetColliderScale(this, 0.5f, 2.0f);
        } else {
            EnSsh_SetColliderScale(this, 0.75f, 2.0f);
        }
    }
}

void EnSsh_Start(EnSsh* this, GlobalContext* globalCtx) {
    if (!EnSsh_IsCloseToGround(this)) {
        EnSsh_SetupAction(this, EnSsh_Wait);
        EnSsh_Wait(this, globalCtx);
    } else {
        EnSsh_SetLandAnimation(this);
        this->stateFlags |= SSH_STATE_GROUND_START;
        EnSsh_SetupAction(this, EnSsh_Land);
        EnSsh_Land(this, globalCtx);
    }
}

void EnSsh_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnSsh* this = THIS;

    EnSsh_UpdateColliderScale(this);

    if (EnSsh_CollisionCheck(this, globalCtx)) {
        return;
    }

    if (this->stunTimer != 0) {
        EnSsh_Damaged(this);
    } else {
        SkelAnime_Update(&this->skelAnime);
        Actor_UpdatePos(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
        this->actionFunc(this, globalCtx);
    }

    EnSsh_UpdateYaw(this, globalCtx);

    if (DECR(this->blinkTimer) == 0) {
        this->blinkTimer = Rand_S16Offset(60, 60);
    }

    this->blinkState = this->blinkTimer;
    if (this->blinkState >= 3) {
        this->blinkState = 0;
    }

    EnSsh_SetColliders(this, globalCtx);
    Actor_SetFocus(&this->actor, 0.0f);
}

s32 EnSsh_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnSsh* this = THIS;

    switch (limbIndex) {
        case 1:
            if ((this->spinTimer != 0) && (this->swayTimer == 0)) {
                if (this->spinTimer >= 2) {
                    EnSsh_AddBlureVertex(this);
                } else {
                    EnSsh_AddBlureSpace(this);
                }
            }
            break;

        case 4:
            if (this->stateFlags & SSH_STATE_FATHER) {
                *dList = object_ssh_DL_005850;
            }
            break;

        case 5:
            if (this->stateFlags & SSH_STATE_FATHER) {
                *dList = object_ssh_DL_005210;
            }
            break;

        case 8:
            if (this->stateFlags & SSH_STATE_FATHER) {
                *dList = object_ssh_DL_005F78;
            }
            break;
    }
    return false;
}

void EnSsh_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnSsh* this = THIS;

    if ((limbIndex == 5) && (this->stateFlags & SSH_STATE_FATHER)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        gSPDisplayList(POLY_OPA_DISP++, object_ssh_DL_0000D8);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    Collider_UpdateSpheres(limbIndex, &this->collider2);
}

void EnSsh_Draw(Actor* thisx, GlobalContext* globalCtx) {
    static TexturePtr D_80976178[] = { object_ssh_Tex_001970, object_ssh_Tex_001DF0, object_ssh_Tex_0021F0 };
    s32 pad;
    EnSsh* this = THIS;

    EnSsh_CheckBodyStickHit(this, globalCtx);
    EnSsh_Sway(this);

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPSegment(POLY_OPA_DISP++, 0x08, SEGMENTED_TO_VIRTUAL(D_80976178[this->blinkState]));

    SkelAnime_DrawOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, EnSsh_OverrideLimbDraw,
                      EnSsh_PostLimbDraw, &this->actor);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
