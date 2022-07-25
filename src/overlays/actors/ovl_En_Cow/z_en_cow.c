/*
 * File: z_en_cow.c
 * Overlay: ovl_En_Cow
 * Description: Cow
 */

#include "z_en_cow.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnCow*)thisx)

void EnCow_Init(Actor* thisx, PlayState* play);
void EnCow_Destroy(Actor* thisx, PlayState* play);
void EnCow_Update(Actor* thisx, PlayState* play);
void EnCow_Draw(Actor* thisx, PlayState* play);

void EnCow_TalkEnd(EnCow* this, PlayState* play);
void EnCow_GiveMilkEnd(EnCow* this, PlayState* play);
void EnCow_GiveMilkWait(EnCow* this, PlayState* play);
void EnCow_GiveMilk(EnCow* this, PlayState* play);
void EnCow_CheckForEmptyBottle(EnCow* this, PlayState* play);
void EnCow_Talk(EnCow* this, PlayState* play);
void EnCow_Idle(EnCow* this, PlayState* play);

void EnCow_DoTail(EnCow* this, PlayState* play);
void EnCow_UpdateTail(Actor* this, PlayState* play);
void EnCow_DrawTail(Actor* this, PlayState* play);

const ActorInit En_Cow_InitVars = {
    ACTOR_EN_COW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_COW,
    sizeof(EnCow),
    (ActorFunc)EnCow_Init,
    (ActorFunc)EnCow_Destroy,
    (ActorFunc)EnCow_Update,
    (ActorFunc)EnCow_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_ENEMY,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 30, 40, 0, { 0, 0, 0 } },
};

Vec3f D_8099D63C = { 0.0f, -1300.0f, 1100.0f };

void EnCow_RotatePoint(Vec3f* vec, s16 angle) {
    f32 x = (Math_CosS(angle) * vec->x) + (Math_SinS(angle) * vec->z);

    vec->z = (-Math_SinS(angle) * vec->x) + (Math_CosS(angle) * vec->z);
    vec->x = x;
}

void EnCow_SetColliderPos(EnCow* this) {
    Vec3f vec;

    vec.x = vec.y = 0.0f;
    vec.z = 30.0f;
    EnCow_RotatePoint(&vec, this->actor.shape.rot.y);
    this->colliders[0].dim.pos.x = this->actor.world.pos.x + vec.x;
    this->colliders[0].dim.pos.y = this->actor.world.pos.y;
    this->colliders[0].dim.pos.z = this->actor.world.pos.z + vec.z;

    vec.x = vec.y = 0.0f;
    vec.z = -20.0f;
    EnCow_RotatePoint(&vec, this->actor.shape.rot.y);
    this->colliders[1].dim.pos.x = this->actor.world.pos.x + vec.x;
    this->colliders[1].dim.pos.y = this->actor.world.pos.y;
    this->colliders[1].dim.pos.z = this->actor.world.pos.z + vec.z;
}

void EnCow_SetTailPos(EnCow* this) {
    Vec3f vec;

    VEC_SET(vec, 0.0f, 57.0f, -36.0f);

    EnCow_RotatePoint(&vec, this->actor.shape.rot.y);
    this->actor.world.pos.x += vec.x;
    this->actor.world.pos.y += vec.y;
    this->actor.world.pos.z += vec.z;
}

void EnCow_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnCow* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 72.0f);

    switch (EN_COW_TYPE(thisx)) {
        case EN_COW_TYPE_DEFAULT:
        case EN_COW_TYPE_ABDUCTED:
            SkelAnime_InitFlex(play, &this->skelAnime, &gCowSkel, NULL, this->jointTable, this->morphTable,
                               COW_LIMB_MAX);
            Animation_PlayLoop(&this->skelAnime, &gCowChewAnim);

            Collider_InitAndSetCylinder(play, &this->colliders[0], &this->actor, &sCylinderInit);
            Collider_InitAndSetCylinder(play, &this->colliders[1], &this->actor, &sCylinderInit);
            EnCow_SetColliderPos(this);

            this->actionFunc = EnCow_Idle;

            if (!(gSaveContext.save.weekEventReg[22] & 1) && (CURRENT_DAY != 1) &&
                (EN_COW_TYPE(thisx) == EN_COW_TYPE_ABDUCTED)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }

            Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_COW, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, this->actor.shape.rot.y, 0,
                               EN_COW_TYPE_TAIL);

            this->animationTimer = Rand_ZeroFloat(1000.0f) + 40.0f;
            this->animationCycle = 0;
            this->actor.targetMode = 6;

            D_801BDAA4 = 0;
            func_801A5080(4);
            break;
        case EN_COW_TYPE_TAIL:
            SkelAnime_InitFlex(play, &this->skelAnime, &gCowTailSkel, NULL, this->jointTable, this->morphTable,
                               COW_TAIL_LIMB_MAX);
            Animation_PlayLoop(&this->skelAnime, &gCowTailIdleAnim);

            this->actor.update = EnCow_UpdateTail;
            this->actor.draw = EnCow_DrawTail;
            this->actionFunc = EnCow_DoTail;

            EnCow_SetTailPos(this);

            this->actor.flags &= ~ACTOR_FLAG_1;
            this->animationTimer = Rand_ZeroFloat(1000.0f) + 40.0f;
            break;
    }

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Actor_SetScale(&this->actor, 0.01f);
    this->flags = 0;

    gSaveContext.save.weekEventReg[87] &= (u8)~1;
}

void EnCow_Destroy(Actor* thisx, PlayState* play) {
    EnCow* this = THIS;

    if (this->actor.params == EN_COW_TYPE_DEFAULT) { //! @bug EN_COW_TYPE_ABDUCTED do not destroy their cylinders
        Collider_DestroyCylinder(play, &this->colliders[0]);
        Collider_DestroyCylinder(play, &this->colliders[1]);
    }
}

void EnCow_UpdateAnimation(EnCow* this, PlayState* play) {
    if (this->animationTimer > 0) {
        this->animationTimer--;
    } else {
        this->animationTimer = Rand_ZeroFloat(500.0f) + 40.0f;
        Animation_Change(&this->skelAnime, &gCowChewAnim, 1.0f, this->skelAnime.curFrame,
                         Animation_GetLastFrame(&gCowChewAnim), ANIMMODE_ONCE, 1.0f);
    }
    if (this->actor.xzDistToPlayer < 150.0f) {
        if (!(this->flags & EN_COW_FLAG_PLAYER_HAS_APPROACHED)) {
            this->flags |= EN_COW_FLAG_PLAYER_HAS_APPROACHED;
            if (this->skelAnime.animation == &gCowChewAnim) {
                this->animationTimer = 0;
            }
        }
    }
    this->animationCycle++;
    if (this->animationCycle > 0x30) {
        this->animationCycle = 0;
    }

    if (this->animationCycle < 0x20) {
        this->actor.scale.x = ((Math_SinS(this->animationCycle * 0x400) * (1.0f / 100.0f)) + 1.0f) * 0.01f;
    } else {
        this->actor.scale.x = 0.01f;
    }

    if (this->animationCycle > 0x10) {
        this->actor.scale.y = ((Math_SinS((this->animationCycle * 0x400) - 0x4000) * (1.0f / 100.0f)) + 1.0f) * 0.01f;
    } else {
        this->actor.scale.y = 0.01f;
    }
}

void EnCow_TalkEnd(EnCow* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_801477B4(play);
        this->actionFunc = EnCow_Idle;
    }
}

void EnCow_GiveMilkEnd(EnCow* this, PlayState* play) {
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        this->actionFunc = EnCow_Idle;
    }
}

void EnCow_GiveMilkWait(EnCow* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = EnCow_GiveMilkEnd;
    } else {
        Actor_PickUp(&this->actor, play, GI_MILK, 10000.0f, 100.0f);
    }
}

void EnCow_GiveMilk(EnCow* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        this->actor.flags &= ~ACTOR_FLAG_10000;
        func_801477B4(play);
        this->actionFunc = EnCow_GiveMilkWait;
        Actor_PickUp(&this->actor, play, GI_MILK, 10000.0f, 100.0f);
    }
}

void EnCow_CheckForEmptyBottle(EnCow* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        if (Inventory_HasEmptyBottle()) {
            func_80151938(play, 0x32C9); // Text to give milk.
            this->actionFunc = EnCow_GiveMilk;
        } else {
            func_80151938(play, 0x32CA); // Text if you don't have an empty bottle.
            this->actionFunc = EnCow_TalkEnd;
        }
    }
}

void EnCow_Talk(EnCow* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->actor.textId == 0x32C8) { // Text to give milk after playing Epona's Song.
            this->actionFunc = EnCow_CheckForEmptyBottle;
        } else if (this->actor.textId == 0x32C9) { // Text to give milk.
            this->actionFunc = EnCow_GiveMilk;
        } else {
            this->actionFunc = EnCow_TalkEnd;
        }
    } else {
        this->actor.flags |= ACTOR_FLAG_10000;
        func_800B8614(&this->actor, play, 170.0f);
        this->actor.textId = 0x32C8; //! @bug textId is reset to this no matter the intial value
    }

    EnCow_UpdateAnimation(this, play);
}

void EnCow_Idle(EnCow* this, PlayState* play) {
    if ((play->msgCtx.ocarinaMode == 0) || (play->msgCtx.ocarinaMode == 4)) {
        if (D_801BDAA4 != 0) {
            if (this->flags & EN_COW_FLAG_WONT_GIVE_MILK) {
                this->flags &= ~EN_COW_FLAG_WONT_GIVE_MILK;
                D_801BDAA4 = 0;
            } else if ((this->actor.xzDistToPlayer < 150.0f) &&
                       ABS_ALT(BINANG_SUB(this->actor.yawTowardsPlayer, this->actor.shape.rot.y)) < 25000) {
                D_801BDAA4 = 0;
                this->actionFunc = EnCow_Talk;
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8614(&this->actor, play, 170.0f);
                this->actor.textId = 0x32C8; // Text to give milk after playing Epona's Song.

                EnCow_UpdateAnimation(this, play);
                return;
            } else {
                this->flags |= EN_COW_FLAG_WONT_GIVE_MILK;
            }
        } else {
            this->flags &= ~EN_COW_FLAG_WONT_GIVE_MILK;
        }
    }

    if (this->actor.xzDistToPlayer < 150.0f &&
        ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y)) < 25000) {
        if (func_801A5100() == 4) {
            if (!(gSaveContext.save.weekEventReg[87] & 1)) {
                gSaveContext.save.weekEventReg[87] |= 1;
                if (Inventory_HasEmptyBottle()) {
                    this->actor.textId = 0x32C9; // Text to give milk.
                } else {
                    this->actor.textId = 0x32CA; // Text if you don't have an empty bottle.
                }
                this->actor.flags |= ACTOR_FLAG_10000;
                func_800B8614(&this->actor, play, 170.0f);
                this->actionFunc = EnCow_Talk;
            }
        } else {
            gSaveContext.save.weekEventReg[87] &= (u8)~1;
        }
    }

    EnCow_UpdateAnimation(this, play);
}

void EnCow_DoTail(EnCow* this, PlayState* play) {
    if (this->animationTimer > 0) {
        this->animationTimer--;
    } else {
        this->animationTimer = Rand_ZeroFloat(200.0f) + 40.0f;
        Animation_Change(&this->skelAnime, &gCowTailIdleAnim, 1.0f, this->skelAnime.curFrame,
                         Animation_GetLastFrame(&gCowTailIdleAnim), ANIMMODE_ONCE, 1.0f);
    }

    if (this->actor.xzDistToPlayer < 150.0f &&
        ABS_ALT((s16)(this->actor.yawTowardsPlayer - this->actor.shape.rot.y)) > 25000) {
        if (!(this->flags & EN_COW_FLAG_PLAYER_HAS_APPROACHED)) {
            this->flags |= EN_COW_FLAG_PLAYER_HAS_APPROACHED;
            if (this->skelAnime.animation == &gCowTailIdleAnim) {
                this->animationTimer = 0;
            }
        }
    }
}

void EnCow_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnCow* this = THIS;
    s16 targetX;
    s16 targetY;
    Player* player = GET_PLAYER(play);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliders[0].base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->colliders[1].base);

    Actor_MoveWithGravity(&this->actor);

    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.animation == &gCowChewAnim) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_COW_CRY);
            Animation_Change(&this->skelAnime, &gCowMooAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gCowMooAnim),
                             ANIMMODE_ONCE, 1.0f);
        } else {
            Animation_Change(&this->skelAnime, &gCowChewAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gCowChewAnim),
                             ANIMMODE_LOOP, 1.0f);
        }
    }

    this->actionFunc(this, play);

    if (this->actor.xzDistToPlayer < 150.0f &&
        ABS_ALT(Math_Vec3f_Yaw(&thisx->world.pos, &player->actor.world.pos)) < 0xC000) {
        targetX = Math_Vec3f_Pitch(&thisx->focus.pos, &player->actor.focus.pos);
        targetY = Math_Vec3f_Yaw(&thisx->focus.pos, &player->actor.focus.pos) - this->actor.shape.rot.y;

        if (targetX > 0x1000) {
            targetX = 0x1000;
        } else if (targetX < -0x1000) {
            targetX = -0x1000;
        }

        if (targetY > 0x2500) {
            targetY = 0x2500;
        } else if (targetY < -0x2500) {
            targetY = -0x2500;
        }
    } else {
        targetX = targetY = 0;
    }

    Math_SmoothStepToS(&this->headTilt.x, targetX, 10, 200, 10);
    Math_SmoothStepToS(&this->headTilt.y, targetY, 10, 200, 10);
}

void EnCow_UpdateTail(Actor* thisx, PlayState* play) {
    s32 pad;
    EnCow* this = THIS;

    if (SkelAnime_Update(&this->skelAnime)) {
        if (this->skelAnime.animation == &gCowTailIdleAnim) {
            Animation_Change(&this->skelAnime, &gCowTailSwishAnim, 1.0f, 0.0f,
                             Animation_GetLastFrame(&gCowTailSwishAnim), ANIMMODE_ONCE, 1.0f);
        } else {
            Animation_Change(&this->skelAnime, &gCowTailIdleAnim, 1.0f, 0.0f, Animation_GetLastFrame(&gCowTailIdleAnim),
                             ANIMMODE_LOOP, 1.0f);
        }
    }

    this->actionFunc(this, play);
}

s32 EnCow_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnCow* this = THIS;

    if (limbIndex == COW_LIMB_HEAD) {
        rot->y += this->headTilt.y;
        rot->x += this->headTilt.x;
    }
    if (limbIndex == COW_LIMB_NOSE_RING) {
        *dList = NULL;
    }

    return false;
}

void EnCow_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCow* this = THIS;

    if (limbIndex == COW_LIMB_HEAD) {
        Matrix_MultVec3f(&D_8099D63C, &this->actor.focus.pos);
    }
}

void EnCow_Draw(Actor* thisx, PlayState* play) {
    EnCow* this = THIS;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnCow_OverrideLimbDraw, EnCow_PostLimbDraw, &this->actor);
}

void EnCow_DrawTail(Actor* thisx, PlayState* play) {
    EnCow* this = THIS;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          NULL, &this->actor);
}
