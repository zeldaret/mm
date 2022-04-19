/*
 * File: z_en_muto.c
 * Overlay: ovl_En_Muto
 * Description: Mutoh, leader of the carpenters
 */

#include "z_en_muto.h"
#include "objects/object_toryo/object_toryo.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnMuto*)thisx)

void EnMuto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnMuto_ChangeAnim(EnMuto* this, s32 arg1);
void EnMuto_SetHeadRotation(EnMuto* this);
void EnMuto_SetupIdle(EnMuto* this);
void EnMuto_Idle(EnMuto* this, GlobalContext* globalCtx);
void EnMuto_SetupDialogue(EnMuto* this, GlobalContext* globalCtx);
void EnMuto_InDialogue(EnMuto* this, GlobalContext* globalCtx);
s32 EnMuto_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);

const ActorInit En_Muto_InitVars = {
    ACTOR_EN_MUTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TORYO,
    sizeof(EnMuto),
    (ActorFunc)EnMuto_Init,
    (ActorFunc)EnMuto_Destroy,
    (ActorFunc)EnMuto_Update,
    (ActorFunc)EnMuto_Draw,
};

static u16 sTextIds[] = { 0x2ABD, 0x2ABB, 0x0624, 0x0623, 0x2AC6 };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
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

void EnMuto_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnMuto* this = THIS;

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 40.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &object_toryo_Skel_007150, &object_toryo_Anim_000E50,
                       this->jointTable, this->morphTable, 17);

    this->isInMayorsRoom = this->actor.params;
    if (!this->isInMayorsRoom) {
        this->shouldSetHeadRotation = true;
        this->textIdIndex = 2;
        if (gSaveContext.save.weekEventReg[60] & 0x80) {
            this->textIdIndex = 3;
        }

        if (gSaveContext.save.day != 3 || !gSaveContext.save.isNight) {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        this->collider.dim.radius = 30;
        this->collider.dim.height = 60;
        this->collider.dim.yShift = 0;

        if (gSaveContext.save.weekEventReg[63] & 0x80 || (gSaveContext.save.day == 3 && gSaveContext.save.isNight)) {
            Actor_MarkForDeath(&this->actor);
        }
    }

    this->actor.targetMode = 6;
    this->actor.gravity = -3.0f;
    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    EnMuto_SetupIdle(this);
}

void EnMuto_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnMuto* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnMuto_ChangeAnim(EnMuto* this, s32 animIndex) {
    static AnimationHeader* sAnimations[] = { &object_toryo_Anim_000E50, &object_toryo_Anim_000E50 };
    static u8 sAnimationModes[] = { ANIMMODE_LOOP, ANIMMODE_ONCE };

    this->animIndex = animIndex;
    this->frameIndex = Animation_GetLastFrame(&sAnimations[animIndex]->common);
    Animation_Change(&this->skelAnime, sAnimations[this->animIndex], 1.0f, 0.0f, this->frameIndex,
                     sAnimationModes[this->animIndex], -4.0f);
}

void EnMuto_SetHeadRotation(EnMuto* this) {
    s32 yawRotToTarget = ABS_ALT(BINANG_SUB(this->yawTowardsTarget, this->actor.world.rot.y));

    this->headRotTarget.y = 0;
    if (this->actor.xzDistToPlayer < 200.0f && yawRotToTarget < 0x4E20) {
        this->headRotTarget.y = BINANG_SUB(this->yawTowardsTarget, this->actor.world.rot.y);
        if (this->headRotTarget.y > 0x2710) {
            this->headRotTarget.y = 0x2710;
        } else if (this->headRotTarget.y < -0x2710) {
            this->headRotTarget.y = -0x2710;
        }
    }
}

void EnMuto_SetupIdle(EnMuto* this) {
    EnMuto_ChangeAnim(this, 0);
    this->isInDialogue = false;
    this->actionFunc = EnMuto_Idle;
}

void EnMuto_Idle(EnMuto* this, GlobalContext* globalCtx) {
    Player* player;
    this->actor.textId = sTextIds[this->textIdIndex];

    if (!this->isInMayorsRoom && (player = GET_PLAYER(globalCtx))->transformation == PLAYER_FORM_DEKU) {
        if (!(gSaveContext.save.weekEventReg[88] & 8)) {
            this->actor.textId = 0x62C;
        } else {
            this->actor.textId = 0x62B;
        }
    }

    if (1) {} // Needed to match

    if (!this->isInMayorsRoom && Player_GetMask(globalCtx) == PLAYER_MASK_KAFEIS_MASK) {
        this->actor.textId = 0x2363;
    }

    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        EnMuto_SetupDialogue(this, globalCtx);
        return;
    }

    if (!this->isInMayorsRoom) {
        s16 yawRotToPlayer = ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.world.rot.y));

        this->yawTowardsTarget = this->actor.yawTowardsPlayer;
        if (yawRotToPlayer > 0x2890) {
            return;
        }
    } else {
        this->textIdIndex = 0;
        if (gSaveContext.save.weekEventReg[60] & 8) {
            this->textIdIndex = 1;
        }
        if (Player_GetMask(globalCtx) == PLAYER_MASK_COUPLE) {
            this->textIdIndex = 4;
        }

        if (this->cutsceneState == 1) {
            EnMuto_SetupDialogue(this, globalCtx);
            return;
        }
    }

    func_800B8614(&this->actor, globalCtx, 80.0f);
}

void EnMuto_SetupDialogue(EnMuto* this, GlobalContext* globalCtx) {
    if (!this->isInMayorsRoom) {
        this->yawTowardsTarget = 0;
    }

    if (this->targetActor != NULL) {
        this->shouldSetHeadRotation = true;
        this->cutsceneState = 1;
        Actor_ChangeFocus(this->targetActor, globalCtx, this->targetActor);
    }

    this->isInDialogue = true;
    this->actionFunc = EnMuto_InDialogue;
}

void EnMuto_InDialogue(EnMuto* this, GlobalContext* globalCtx) {
    if (!this->isInMayorsRoom) {
        this->yawTowardsTarget = this->actor.yawTowardsPlayer;
        if (Message_GetState(&globalCtx->msgCtx) == 5 && Message_ShouldAdvance(globalCtx)) {
            func_801477B4(globalCtx);

            if (this->actor.textId == 0x62C) {
                gSaveContext.save.weekEventReg[88] |= 8;
            }
            if (this->actor.textId == 0x624) {
                gSaveContext.save.weekEventReg[60] |= 0x80;
            }

            this->textIdIndex = 3;

            EnMuto_SetupIdle(this);
        }
        return;
    }

    if (this->targetActor == &this->actor) {
        this->yawTowardsTarget = this->actor.world.rot.y;
        if (this->skelAnime.playSpeed == 0.0f) {
            this->skelAnime.playSpeed = 1.0f;
        }
    } else {
        f32 frameIndex = this->skelAnime.curFrame;

        this->yawTowardsTarget = Math_Vec3f_Yaw(&this->actor.world.pos, &this->targetActor->world.pos);
        if (this->frameIndex <= frameIndex) {
            this->skelAnime.playSpeed = 0.0f;
        }
    }

    if (globalCtx->msgCtx.currentTextId == 0x2AC6 || globalCtx->msgCtx.currentTextId == 0x2AC7 ||
        globalCtx->msgCtx.currentTextId == 0x2AC8) {
        this->skelAnime.playSpeed = 0.0f;
        this->yawTowardsTarget = this->actor.yawTowardsPlayer;
        this->skelAnime.curFrame = 30.0f;
    }
    if (globalCtx->msgCtx.currentTextId == 0x2ACF) {
        this->skelAnime.playSpeed = 0.0f;
    }

    if (this->cutsceneState == 2) {
        EnMuto_SetupIdle(this);
    }
}

void EnMuto_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnMuto* this = THIS;

    SkelAnime_Update(&this->skelAnime);

    if (this->shouldSetHeadRotation) {
        EnMuto_SetHeadRotation(this);
    }

    if (this->isInMayorsRoom && gSaveContext.save.day == 3 && gSaveContext.save.isNight) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->actionFunc(this, globalCtx);

    DECR(this->unusedCounter);

    Actor_SetScale(&this->actor, 0.01f);
    this->actor.shape.rot.y = this->actor.world.rot.y;
    Actor_SetFocus(&this->actor, 60.0f);
    Actor_MoveWithGravity(&this->actor);

    Math_SmoothStepToS(&this->headRot.y, this->headRotTarget.y, 1, 0xBB8, 0);
    Math_SmoothStepToS(&this->headRot.x, this->headRotTarget.x, 1, 0x3E8, 0);
    Math_SmoothStepToS(&this->waistRot.y, this->waistRotTarget.y, 1, 0xBB8, 0);

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 20.0f, 50.0f, 0x1DU);

    this->actor.uncullZoneForward = 500.0f;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

s32 EnMuto_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                            Actor* thisx) {
    EnMuto* this = THIS;

    if (limbIndex == 1) {
        rot->x += this->waistRot.y;
    }

    if (limbIndex == 15) {
        rot->x += this->headRot.y;
        rot->z += this->headRot.x;
    }

    return false;
}

void EnMuto_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnMuto* this = THIS;

    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnMuto_OverrideLimbDraw, NULL, &this->actor);
}
