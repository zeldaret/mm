/*
 * File: z_en_kitan.c
 * Overlay: ovl_En_Kitan
 * Description: Keaton
 */

#include "z_en_kitan.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnKitan*)thisx)

void EnKitan_Init(Actor* thisx, PlayState* play);
void EnKitan_Destroy(Actor* thisx, PlayState* play);
void EnKitan_Update(Actor* thisx, PlayState* play);
void EnKitan_Draw(Actor* thisx, PlayState* play);

void func_80C09708(EnKitan*, PlayState*);
void func_80C09B50(EnKitan*, PlayState*);

ActorInit En_Kitan_InitVars = {
    /**/ ACTOR_EN_KITAN,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_KITAN,
    /**/ sizeof(EnKitan),
    /**/ EnKitan_Init,
    /**/ EnKitan_Destroy,
    /**/ EnKitan_Update,
    /**/ NULL,
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
    { 20, 40, 0, { 0, 0, 0 } },
};

#define ENKITAN_GET_9(thisx) (((thisx)->params & 0xFE00) >> 9)

void EnKitan_Init(Actor* thisx, PlayState* play) {
    EnKitan* this = THIS;
    s32 pad;

    Actor_SetScale(&this->actor, 0.0f);
    this->actionFunc = func_80C09B50;
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 12.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_kitan_Skel_007FA8, &object_kitan_Anim_002770, this->jointTable,
                       this->morphTable, OBJECT_KITAN_LIMB_MAX);
    Animation_PlayLoop(&this->skelAnime, &object_kitan_Anim_002770);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->actor.velocity.y = -9.0f;
    this->actor.terminalVelocity = -9.0f;
    this->actor.gravity = -1.0f;
    if (Player_GetMask(play) != PLAYER_MASK_KEATON || Flags_GetCollectible(play, ENKITAN_GET_9(&this->actor))) {
        Actor_Kill(&this->actor);
        return;
    }
    this->timer = 120;
    this->actor.flags &= ~1;
}

void EnKitan_Destroy(Actor* thisx, PlayState* play) {
    EnKitan* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80C0923C(EnKitan* this, PlayState* play, s32 arg2) {
    static Color_RGBA8 sEffPrimColor = { 255, 255, 255, 255 };
    static Color_RGBA8 sEffEnvColor = { 255, 255, 200, 255 };
    s32 i;
    Vec3f accel;
    Vec3f vel;
    Vec3f pos;

    pos.x = this->actor.world.pos.x;
    pos.y = this->actor.world.pos.y;
    pos.z = this->actor.world.pos.z;

    for (i = 0; i < arg2; i++) {
        vel.x = randPlusMinusPoint5Scaled(10.0f);
        vel.y = Rand_ZeroFloat(6.0f);
        vel.z = randPlusMinusPoint5Scaled(10.0f);
        accel.x = -vel.x * 0.05f;
        accel.y = 0.1f;
        accel.z = -vel.x * 0.05f;
        func_800B0F18(play, &pos, &vel, &accel, &sEffPrimColor, &sEffEnvColor, 400, 20, 20);
    }
}

s32 func_80C09390(EnKitan* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (player->stateFlags1 & PLAYER_STATE1_800000) {
        return false;
    }
    if (Player_IsFacingActor(&this->actor, 0x3000, play) && Actor_IsFacingPlayer(&this->actor, 0x3000) &&
        this->actor.xzDistToPlayer < 120.0f) {
        return true;
    }
    return false;
}

u16 func_80C09418(EnKitan* this) {
    s32 i = 0;

    //! @bug This loop was likely meant to have a cap of 1000?
    while (true) {
        s32 rand = Rand_ZeroFloat(30.0f);

        if (!(this->textBitSet & (1 << rand))) {
            this->textBitSet |= (1 << rand);
            return 0x04B6 + 2 * rand;
        }

        i++;
        if (i > 1000) {
            continue;
        }
    }
}

void func_80C094A8(EnKitan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (this->timer > 0) {
        this->timer--;
        this->actor.scale.x *= 0.7f;
        Actor_SetScale(&this->actor, this->actor.scale.x);
    } else {
        Actor_Kill(&this->actor);
    }
}

void func_80C09518(EnKitan* this, PlayState* play) {
    s32 pad;

    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80C09708;
        Message_ContinueTextbox(play, 0x04B5);
        this->actor.flags &= ~ACTOR_FLAG_10000;
        Animation_MorphToLoop(&this->skelAnime, &object_kitan_Anim_000CE8, -5.0f);
    } else {
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void func_80C095C8(EnKitan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
    if (Actor_TextboxIsClosing(&this->actor, play)) {
        this->actor.flags |= ACTOR_FLAG_10000;
        this->actionFunc = func_80C09518;
        func_800B8500(&this->actor, play, 1000.0f, 1000.0f, PLAYER_IA_MINUS1);
    }
}

void func_80C09648(EnKitan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        this->actionFunc = func_80C095C8;
        gSaveContext.save.saveInfo.weekEventReg[0x4F] |= 0x80;
    } else if (gSaveContext.save.saveInfo.weekEventReg[0x4F] & 0x80) {
        Actor_OfferGetItem(&this->actor, play, GI_RUPEE_RED, 2000.0f, 1000.0f);
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 2000.0f, 1000.0f);
    }
}

void func_80C09708(EnKitan* this, PlayState* play) {
    if (SkelAnime_Update(&this->skelAnime)) {
        Animation_MorphToLoop(&this->skelAnime, &object_kitan_Anim_002770, -10.0f);
        if (play->msgCtx.currentTextId != 0x04B4) {
            Message_ContinueTextbox(play, func_80C09418(this));
        }
    }

    switch (Message_GetState(&play->msgCtx)) {
        case 4:
            if (Message_ShouldAdvance(play)) {
                if (play->msgCtx.choiceIndex + 1 == play->msgCtx.unk1206C) {
                    play_sound(NA_SE_SY_QUIZ_CORRECT);
                    this->timer++;
                    if (this->timer < 5) {
                        play->msgCtx.msgLength = 0;
                    } else {
                        this->timer = 0;
                        this->textBitSet = 0;
                        Message_ContinueTextbox(play, 0x04B4);
                    }
                    Animation_MorphToPlayOnce(&this->skelAnime, &object_kitan_Anim_00190C, -5.0f);
                } else {
                    play_sound(NA_SE_SY_QUIZ_INCORRECT);
                    Animation_MorphToLoop(&this->skelAnime, &object_kitan_Anim_000CE8, -5.0f);
                    Message_ContinueTextbox(play, 0x04B3);
                    this->timer = 0;
                    this->textBitSet = 0;
                }
            }
            break;
        case 5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x04B0:
                    case 0x04B1:
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;
                    case 0x04B2:
                        Animation_MorphToLoop(&this->skelAnime, &object_kitan_Anim_002770, -5.0f);
                        Message_ContinueTextbox(play, func_80C09418(this));
                        break;
                    case 0x04B4:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80C09648;
                        func_80C09648(this, play);
                        break;
                    case 0x04B3:
                        AudioSeq_QueueSeqCmd(0x110000FF);
                        /* fallthrough */
                    case 0x04B5:
                        Message_CloseTextbox(play);
                        this->actionFunc = func_80C094A8;
                        this->timer = 4;
                        func_80C0923C(this, play, 30);
                        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EN_NPC_FADEAWAY);
                        Flags_SetCollectible(play, ENKITAN_GET_9(&this->actor));
                        break;
                    default:
                        if (!(play->msgCtx.currentTextId & 1)) {
                            Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        }
                        break;
                }
            }
            break;
    }
}

void func_80C09990(EnKitan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->actionFunc = func_80C09708;
        Message_StartTextbox(play, 0x04B0, &this->actor);
        this->timer = 0;
        Animation_MorphToLoop(&this->skelAnime, &object_kitan_Anim_000CE8, -5.0f);
        Audio_PlayFanfare(NA_BGM_KEATON_QUIZ);
    } else if (this->timer <= 0 || Player_GetMask(play) != PLAYER_MASK_KEATON) {
        this->actionFunc = func_80C094A8;
        this->timer = 4;
        func_80C0923C(this, play, 30);
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 30, NA_SE_EN_NPC_FADEAWAY);
    } else if (func_80C09390(this, play)) {
        func_800B8614(&this->actor, play, 130.0f);
        this->timer--;
    }
}

void func_80C09AA4(EnKitan* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);

    if (this->timer > 0) {
        this->timer--;
        this->actor.scale.x = this->actor.scale.x * 0.3f + 0.0105f;
        Actor_SetScale(&this->actor, this->actor.scale.x);
    } else {
        Actor_SetScale(&this->actor, 0.015f);
        this->actionFunc = func_80C09990;
        this->actor.flags |= ACTOR_FLAG_1;
        this->timer = 600;
    }
}

void func_80C09B50(EnKitan* this, PlayState* play) {
    if (this->timer > 0) {
        this->timer--;
        return;
    }
    func_80C0923C(this, play, 30);
    Actor_PlaySfx(&this->actor, NA_SE_EN_NPC_APPEAR);
    this->actor.draw = EnKitan_Draw;
    this->actionFunc = func_80C09AA4;
    this->timer = 20;
    this->actor.shape.rot.y = this->actor.yawTowardsPlayer;
    this->actor.world.rot.y = this->actor.shape.rot.y;
}

void EnKitan_Update(Actor* thisx, PlayState* play) {
    EnKitan* this = THIS;

    if (this->actor.draw != NULL) {
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 40.0f, 25.0f, 40.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0x1000, 0x200);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actionFunc(this, play);
}

s32 EnKitan_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

void EnKitan_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    static Vec3f sFocusOffset = { 0.0f, 0.0f, 0.0f };
    EnKitan* this = THIS;

    if (limbIndex == 6) {
        Matrix_MultVec3f(&sFocusOffset, &this->actor.focus.pos);
    }
}

void EnKitan_Draw(Actor* thisx, PlayState* play) {
    EnKitan* this = THIS;

    func_8012C5B0(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnKitan_OverrideLimbDraw, EnKitan_PostLimbDraw, &this->actor);
}
