/*
 * File: z_en_heishi.c
 * Overlay: ovl_En_Heishi
 * Description: Soldier (Mayor's Residence only)
 */

#include "z_en_heishi.h"
#include "objects/object_sdn/object_sdn.h"

#define FLAGS 0x00000009

#define THIS ((EnHeishi*)thisx)

void EnHeishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnHeishi_ChangeAnimation(EnHeishi* this, s32 animIndex);
void EnHeishi_SetHeadRotation(EnHeishi* this);
void EnHeishi_SetupIdle(EnHeishi* this);
void EnHeishi_Idle(EnHeishi* this, GlobalContext* globalCtx);
s32 EnHeishi_OverrideLimbDraw(GlobalContext* globalctx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx);

const ActorInit En_Heishi_InitVars = {
    ACTOR_EN_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnHeishi),
    (ActorFunc)EnHeishi_Init,
    (ActorFunc)EnHeishi_Destroy,
    (ActorFunc)EnHeishi_Update,
    (ActorFunc)EnHeishi_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 20, 60, 0, { 0, 0, 0 } },
};

void EnHeishi_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnHeishi* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gSoldierSkeleton, &gSoldierWave, this->jointTable,
                       this->morphTable, HEISHI_LIMB_MAX);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->paramCopy = this->actor.params;
    this->yawTowardsPlayer = this->actor.world.rot.y;

    if (this->paramCopy == 0) {
        this->unk26C = 1;
        if (!(gSaveContext.weekEventReg[63] & 0x80) && ((gSaveContext.day != 3) || !gSaveContext.isNight)) {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        this->colliderCylinder.dim.radius = 30;
        this->colliderCylinder.dim.height = 60;
        this->colliderCylinder.dim.yShift = 0;
        if ((gSaveContext.weekEventReg[63] & 0x80) || ((gSaveContext.day == 3) && gSaveContext.isNight)) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->colliderCylinder, &this->actor, &sCylinderInit);
    this->actor.flags |= 0x08000000;
    EnHeishi_SetupIdle(this);
}

void EnHeishi_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnHeishi* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
}

void EnHeishi_ChangeAnimation(EnHeishi* this, s32 animIndex) {
    static AnimationHeader* sAnimations[] = { &gSoldierStandHandOnHip, &gSoldierCheerWithSpear, &gSoldierWave,
                                              &gSoldierSitAndReach, &gSoldierStandUp };
    static u8 sAnimModes[] = { 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    this->animIndex = animIndex;
    this->frameCount = Animation_GetLastFrame(sAnimations[this->animIndex]);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.0f, this->frameCount,
                     sAnimModes[this->animIndex], -10.0f);
}

void EnHeishi_SetHeadRotation(EnHeishi* this) {
    s16 yawTemp = this->yawTowardsPlayer - this->actor.world.rot.y;
    s32 yaw = ABS_ALT(yawTemp);

    this->headRotXTarget = 0;
    if ((this->actor.xzDistToPlayer < 200.0f) && (yaw < 0x4E20)) {
        this->headRotXTarget = this->yawTowardsPlayer - this->actor.world.rot.y;
        if (this->headRotXTarget > 0x2710) {
            this->headRotXTarget = 0x2710;
        } else if (this->headRotXTarget < -0x2710) {
            this->headRotXTarget = -0x2710;
        }
    }
}

void EnHeishi_SetupIdle(EnHeishi* this) {
    s8 animIndex = 0;

    EnHeishi_ChangeAnimation(this, animIndex);
    this->unk278 = animIndex;
    this->actionFunc = EnHeishi_Idle;
}

void EnHeishi_Idle(EnHeishi* this, GlobalContext* globalCtx) {
}

void EnHeishi_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnHeishi* this = THIS;

    SkelAnime_Update(&this->skelAnime);
    if (this->timer != 0) {
        this->timer--;
    }

    this->actor.shape.rot.y = this->actor.world.rot.y;
    if ((this->paramCopy != 0) && (gSaveContext.day == 3) && gSaveContext.isNight) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actionFunc(this, globalCtx);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 29);
        Actor_SetScale(&this->actor, 0.01f);
        if (this->unk26C != 0) {
            EnHeishi_SetHeadRotation(this);
        }

        Actor_SetFocus(&this->actor, 60.0f);
        Math_SmoothStepToS(&this->headRotX, this->headRotXTarget, 1, 3000, 0);
        Math_SmoothStepToS(&this->headRotY, this->headRotYTarget, 1, 1000, 0);
        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }
}

s32 EnHeishi_OverrideLimbDraw(GlobalContext* globalctx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                              Actor* thisx) {
    EnHeishi* this = THIS;

    if (limbIndex == HEISHI_LIMB_HEAD) {
        rot->x += this->headRotX;
        rot->y += this->headRotY;
        rot->z += this->headRotZ;
    }

    return false;
}

void EnHeishi_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnHeishi* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHeishi_OverrideLimbDraw, NULL, &this->actor);
}
