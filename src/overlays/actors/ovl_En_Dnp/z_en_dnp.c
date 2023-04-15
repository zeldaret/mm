/*
 * File: z_en_dnp.c
 * Overlay: ovl_En_Dnp
 * Description: Deku Princess
 *
 * This actor's name is probably short for "Dekunuts Princess". It uses assets from object_dnq,
 * which is probably short for "Dekunuts Queen".
 */

#include "z_en_dnp.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnDnp*)thisx)

void EnDnp_Init(Actor* thisx, PlayState* play);
void EnDnp_Destroy(Actor* thisx, PlayState* play);
void EnDnp_Update(Actor* thisx, PlayState* play);
void EnDnp_Draw(Actor* thisx, PlayState* play);

void func_80B3D11C(EnDnp* this, PlayState* play);
void func_80B3D2D4(EnDnp* this, PlayState* play);
void func_80B3D338(EnDnp* this, PlayState* play);
void func_80B3D3F8(EnDnp* this, PlayState* play);
void func_80B3D558(EnDnp* this, PlayState* play);

typedef enum {
    /* 0 */ EN_DNP_EYE_OPEN,
    /* 1 */ EN_DNP_EYE_HALF,
    /* 2 */ EN_DNP_EYE_CLOSED,
    /* 3 */ EN_DNP_EYE_ANGRY,
    /* 4 */ EN_DNP_EYE_MAX,
} EnDnpEyeIndex;

ActorInit En_Dnp_InitVars = {
    /**/ ACTOR_EN_DNP,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DNQ,
    /**/ sizeof(EnDnp),
    /**/ EnDnp_Init,
    /**/ EnDnp_Destroy,
    /**/ EnDnp_Update,
    /**/ EnDnp_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT1,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 14, 38, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

typedef enum {
    /* -1 */ EN_DNP_ANIM_NONE = -1,
    /*  0 */ EN_DNP_ANIM_JUMP_KICK, // Can be triggered by a cutscene, but no cutscene in the final game does so
    /*  1 */ EN_DNP_ANIM_HURRY,
    /*  2 */ EN_DNP_ANIM_CUTSCENE_HURRY,
    /*  3 */ EN_DNP_ANIM_HURRY_END,
    /*  4 */ EN_DNP_ANIM_SCOLD, // Unused
    /*  5 */ EN_DNP_ANIM_LAUGH_START,
    /*  6 */ EN_DNP_ANIM_LAUGH_LOOP,
    /*  7 */ EN_DNP_ANIM_TURN_AROUND,
    /*  8 */ EN_DNP_ANIM_BOW,
    /*  9 */ EN_DNP_ANIM_RUN, // Unused
    /* 10 */ EN_DNP_ANIM_THINK_START,
    /* 11 */ EN_DNP_ANIM_THINK_LOOP,
    /* 12 */ EN_DNP_ANIM_ARMS_TOGETHER_START,
    /* 13 */ EN_DNP_ANIM_ARMS_TOGETHER_LOOP,
    /* 14 */ EN_DNP_ANIM_GREETING,
    /* 15 */ EN_DNP_ANIM_IDLE,
    /* 16 */ EN_DNP_ANIM_CUTSCENE_IDLE,
    /* 17 */ EN_DNP_ANIM_UNUSED_WALK, // Unused
    /* 18 */ EN_DNP_ANIM_WALK,        // Can be triggered by a cutscene, but no cutscene in the final game does so
    /* 19 */ EN_DNP_ANIM_ANGRY_START,
    /* 20 */ EN_DNP_ANIM_ANGRY_LOOP,
    /* 21 */ EN_DNP_ANIM_JUMP,
    /* 22 */ EN_DNP_ANIM_BOUNCE_START,
    /* 23 */ EN_DNP_ANIM_BOUNCE_LOOP,
    /* 24 */ EN_DNP_ANIM_GLARE_START,
    /* 25 */ EN_DNP_ANIM_GLARE_LOOP
} EnDnpAnimation;

static AnimationInfoS sAnimationInfo[] = {
    { &gDekuPrincessJumpKickAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessHurryAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gDekuPrincessHurryAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessHurryEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessScoldAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessLaughStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessLaughLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessTurnAroundAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuPrincessBowAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessRunAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessThinkStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessThinkLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessArmsTogetherStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessArmsTogetherLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessGreetingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gDekuPrincessIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gDekuPrincessAngryStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessAngryLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessJumpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, -4 },
    { &gDekuPrincessBounceStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuPrincessBounceLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gDekuPrincessGlareStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gDekuPrincessGlareLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

static s32 D_80B3DE58[] = {
    0x00172000, 0x0D040005, 0x0E09670C, 0x100E0968, 0x0C100E09, 0x6F0C0F09, 0x700C1000,
};

s32 func_80B3CA20(EnDnp* this) {
    if ((this->animIndex == EN_DNP_ANIM_CUTSCENE_HURRY) || (this->animIndex == EN_DNP_ANIM_RUN)) {
        if (Animation_OnFrame(&this->skelAnime, 1.0f) || Animation_OnFrame(&this->skelAnime, 5.0f) ||
            Animation_OnFrame(&this->skelAnime, 9.0f) || Animation_OnFrame(&this->skelAnime, 13.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_TURN);
        }
    } else if ((this->animIndex == EN_DNP_ANIM_GLARE_START) || (this->animIndex == EN_DNP_ANIM_TURN_AROUND)) {
        if (Animation_OnFrame(&this->skelAnime, 1.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_TURN);
        }
    } else if (this->animIndex == EN_DNP_ANIM_GREETING) {
        if (Animation_OnFrame(&this->skelAnime, 7.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_GREET);
        }
        if (Animation_OnFrame(&this->skelAnime, 22.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_GREET2);
        }
    } else if (this->animIndex == EN_DNP_ANIM_BOW) {
        if (Animation_OnFrame(&this->skelAnime, 9.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_GREET);
        }
        if (Animation_OnFrame(&this->skelAnime, 18.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_GREET2);
        }
    } else if ((this->animIndex == EN_DNP_ANIM_UNUSED_WALK) && (this->animIndex == EN_DNP_ANIM_WALK)) {
        //! @bug: Impossible to reach, && should be an ||
        if (Animation_OnFrame(&this->skelAnime, 7.0f) || Animation_OnFrame(&this->skelAnime, 15.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    } else if (this->animIndex == EN_DNP_ANIM_JUMP) {
        if (Animation_OnFrame(&this->skelAnime, 17.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    } else if (this->animIndex == EN_DNP_ANIM_BOUNCE_LOOP) {
        if (Animation_OnFrame(&this->skelAnime, 3.0f)) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_DEKUHIME_WALK);
        }
    }

    return 0;
}

s32 EnDnp_ChangeAnim(EnDnp* this, s32 animIndex) {
    s32 ret = false;

    if (animIndex != this->animIndex) {
        this->animIndex = animIndex;
        ret = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
    }

    return ret;
}

void func_80B3CC80(EnDnp* this, PlayState* play) {
    f32 temp_f0 = this->actor.scale.x / 0.0085f;

    Collider_UpdateCylinder(&this->actor, &this->collider);
    this->collider.dim.radius = 14.0f * temp_f0;
    this->collider.dim.height = 38.0f * temp_f0;
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void func_80B3CD1C(EnDnp* this) {
    if ((this->unk_322 & 0x80) && (DECR(this->blinkTimer) == 0)) {
        this->eyeIndex++;
        if (this->eyeIndex >= EN_DNP_EYE_MAX) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeIndex = EN_DNP_EYE_OPEN;
        }
    }
}

s32 func_80B3CDA4(EnDnp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 temp_s0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
    Vec3f sp3C;
    Vec3f sp30;
    s16 pitch;

    temp_s0 = CLAMP(temp_s0, -0x3FFC, 0x3FFC);

    Math_SmoothStepToS(&this->unk_332, temp_s0, 3, 0x2AA8, 0x1);
    sp30 = player->actor.world.pos;
    sp30.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    sp3C = this->actor.world.pos;
    sp3C.y += 10.0f;
    pitch = Math_Vec3f_Pitch(&sp3C, &sp30);

    //! FAKE
    if (1) {}

    Math_SmoothStepToS(&this->unk_330, pitch, 3, 0x2AA8, 0x1);

    return 1;
}

s32 func_80B3CEC0(EnDnp* this, PlayState* play) {
    if (this->unk_322 & 8) {
        func_80B3CDA4(this, play);
        this->unk_322 &= ~0x10;
        this->unk_322 |= 64;
    } else if (this->unk_322 & 0x40) {
        this->unk_322 &= ~0x40;
        this->unk_330 = 0;
        this->unk_332 = 0;
        this->unk_338 = 20;
    } else if (DECR(this->unk_338) == 0) {
        this->unk_322 |= 0x10;
    }

    return 1;
}

s32 func_80B3CF60(EnDnp* this, PlayState* play) {
    s32 ret = false;

    if ((this->unk_322 & 7) && Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        SubS_UpdateFlags(&this->unk_322, 0, 7);
        this->unk_322 |= 8;
        this->actionFunc = func_80B3D3F8;
        ret = true;
    } else if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20) && Actor_HasParent(&this->actor, play)) {
        SubS_UpdateFlags(&this->unk_322, 0, 7);
        this->unk_322 &= ~0x500;
        this->actor.parent = NULL;
        this->unk_32E = 0;
        this->actionFunc = func_80B3D338;
        ret = true;
    }

    return ret;
}

s32 func_80B3D044(EnDnp* this, PlayState* play) {
    s32 ret = false;

    if (play->csCtx.state != 0) {
        if (!(this->unk_322 & 0x200)) {
            this->unk_322 |= (0x200 | 0x10);
            this->actor.flags &= ~ACTOR_FLAG_1;
            this->unk_324 = 0xFF;
        }
        SubS_UpdateFlags(&this->unk_322, 0, 7);
        this->actionFunc = func_80B3D11C;
        ret = true;
    } else if (this->unk_322 & 0x200) {
        this->actor.flags |= ACTOR_FLAG_1;
        SubS_UpdateFlags(&this->unk_322, 3, 7);
        this->unk_322 &= ~(0x200 | 0x10);
        this->actionFunc = func_80B3D2D4;
    }

    return ret;
}

void func_80B3D11C(EnDnp* this, PlayState* play) {
    static s32 sCsAnimations[] = {
        EN_DNP_ANIM_JUMP_KICK,   EN_DNP_ANIM_CUTSCENE_IDLE, EN_DNP_ANIM_GREETING,
        EN_DNP_ANIM_THINK_START, EN_DNP_ANIM_WALK,          EN_DNP_ANIM_ARMS_TOGETHER_START,
        EN_DNP_ANIM_LAUGH_START, EN_DNP_ANIM_TURN_AROUND,   EN_DNP_ANIM_CUTSCENE_HURRY,
        EN_DNP_ANIM_ANGRY_START, EN_DNP_ANIM_JUMP,          EN_DNP_ANIM_BOUNCE_START,
        EN_DNP_ANIM_GLARE_START, EN_DNP_ANIM_BOW,
    };
    s32 temp_v0;
    s32 val;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_29_40) && (play->sceneId == SCENE_MITURIN) &&
        (play->csCtx.currentCsIndex == 0)) {
        this->unk_322 |= 0x20;
        SET_WEEKEVENTREG(WEEKEVENTREG_29_40);
    }

    if (Cutscene_CheckActorAction(play, 101)) {
        temp_v0 = Cutscene_GetActorActionIndex(play, 101);
        val = play->csCtx.actorActions[temp_v0]->action;
        if (this->unk_324 != (u8)val) {
            EnDnp_ChangeAnim(this, sCsAnimations[val]);
            if (this->animIndex == EN_DNP_ANIM_CUTSCENE_IDLE) {
                this->unk_322 |= 8;
            } else {
                this->unk_322 &= ~8;
            }

            if (this->animIndex == EN_DNP_ANIM_ANGRY_START) {
                Actor_PlaySfx(&this->actor, NA_SE_VO_DHVO04);
            }

            if (this->animIndex == EN_DNP_ANIM_GLARE_START) {
                this->unk_322 &= ~0x80;
                this->eyeIndex = EN_DNP_EYE_ANGRY;
                this->blinkTimer = 0;
            }
        }

        this->unk_324 = val;
        if (((this->animIndex == EN_DNP_ANIM_THINK_START) || (this->animIndex == EN_DNP_ANIM_ARMS_TOGETHER_START) ||
             (this->animIndex == EN_DNP_ANIM_LAUGH_START) || (this->animIndex == EN_DNP_ANIM_ANGRY_START) ||
             (this->animIndex == EN_DNP_ANIM_BOUNCE_START) || (this->animIndex == EN_DNP_ANIM_GLARE_START)) &&
            Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            EnDnp_ChangeAnim(this, this->animIndex + 1);
        }
        Cutscene_ActorTranslateAndYaw(&this->actor, play, temp_v0);
    }
}

void func_80B3D2D4(EnDnp* this, PlayState* play) {
    if (this->unk_322 & 0x20) {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x3, 0x2AA8);
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 0x3, 0x2AA8);
    }
}

void func_80B3D338(EnDnp* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->unk_32E != 0) && (Message_GetState(&play->msgCtx) == TEXT_STATE_CLOSING)) {
        Actor_Kill(&this->actor);
        return;
    }

    if (this->unk_32E == 0) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            this->unk_32E = 1;
        } else {
            this->actor.textId = 0x971;
            player->actor.textId = this->actor.textId;
            func_800B8500(&this->actor, play, 9999.9f, 9999.9f, PLAYER_IA_MINUS1);
        }
    }
}

void func_80B3D3F8(EnDnp* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, D_80B3DE58, NULL, &this->unk_328)) {
        SubS_UpdateFlags(&this->unk_322, 3, 7);
        this->unk_322 &= ~8;
        this->actionFunc = func_80B3D2D4;
    } else {
        Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 0x3, 0x2AA8);
    }
}

void func_80B3D47C(EnDnp* this, PlayState* play) {
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        Math_SmoothStepToF(&this->actor.scale.x, 0.0085f, 0.1f, 0.01f, 0.001f);
        if ((s32)(this->actor.scale.x * 10000.0f) >= 85) {
            this->actor.flags |= ACTOR_FLAG_1;
            SubS_UpdateFlags(&this->unk_322, 3, 7);
            this->unk_322 &= ~0x10;
            this->unk_322 |= 0x400;
            this->actor.scale.x = 0.0085f;
            this->actionFunc = func_80B3D558;
        }
    }
    Actor_SetScale(&this->actor, this->actor.scale.x);
}

void func_80B3D558(EnDnp* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        SET_WEEKEVENTREG(WEEKEVENTREG_23_20);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnDnp_Init(Actor* thisx, PlayState* play) {
    EnDnp* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 16.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gDekuPrincessSkel, NULL, this->jointTable, this->morphTable,
                       DEKU_PRINCESS_LIMB_MAX);
    this->animIndex = EN_DNP_ANIM_NONE;
    EnDnp_ChangeAnim(this, EN_DNP_ANIM_IDLE);
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
    this->unk_322 = 0;
    this->actor.targetMode = 0;
    this->unk_322 |= (0x100 | 0x80 | 0x10);
    this->actor.gravity = -1.0f;
    if (EN_DNP_GET_TYPE(&this->actor) == EN_DNP_TYPE_RELEASED_FROM_BOTTLE) {
        this->actor.flags &= ~ACTOR_FLAG_1;
        Actor_SetScale(&this->actor, 0.00085000007f);
        SubS_UpdateFlags(&this->unk_322, 0, 7);
        this->actor.shape.rot.x = 0;
        this->actor.world.rot.x = this->actor.shape.rot.x;
        this->actor.cutscene = 0x10;
        this->actionFunc = func_80B3D47C;
    } else if (((EN_DNP_GET_TYPE(&this->actor) == EN_DNP_TYPE_WOODFALL_TEMPLE) &&
                !Inventory_HasItemInBottle(ITEM_DEKU_PRINCESS) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20)) ||
               ((EN_DNP_GET_TYPE(&this->actor) == EN_DNP_TYPE_DEKU_KINGS_CHAMBER) &&
                CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20))) {
        Actor_SetScale(&this->actor, 0.0085f);
        SubS_UpdateFlags(&this->unk_322, 3, 7);
        this->unk_322 |= 0x400;
        if ((play->sceneId == SCENE_MITURIN) && CHECK_WEEKEVENTREG(WEEKEVENTREG_29_40)) {
            this->unk_322 |= 0x20;
            EnDnp_ChangeAnim(this, EN_DNP_ANIM_HURRY);
        }
        this->actionFunc = func_80B3D2D4;
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnDnp_Destroy(Actor* thisx, PlayState* play) {
    EnDnp* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnDnp_Update(Actor* thisx, PlayState* play) {
    EnDnp* this = THIS;
    s32 pad;
    f32 sp2C;
    f32 sp28;

    if (!func_80B3CF60(this, play) && func_80B3D044(this, play)) {
        func_80B3D11C(this, play);
        SkelAnime_Update(&this->skelAnime);
        func_80B3CD1C(this);
        func_80B3CEC0(this, play);
    } else {
        this->actionFunc(this, play);
        SkelAnime_Update(&this->skelAnime);
        func_80B3CD1C(this);
        func_80B3CEC0(this, play);
        Actor_MoveWithGravity(&this->actor);
        Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 12.0f, 0.0f, 4);
        sp2C = this->collider.dim.radius + 50;
        sp28 = this->collider.dim.height + 30;
        if ((this->unk_322 & 0x400) && !CHECK_WEEKEVENTREG(WEEKEVENTREG_23_20)) {
            Actor_OfferGetItem(&this->actor, play, GI_MAX, sp2C, sp28);
        }
        func_8013C964(&this->actor, play, sp2C, sp28, PLAYER_IA_NONE, this->unk_322 & 7);
        Actor_SetFocus(&this->actor, 30.0f);
        func_80B3CC80(this, play);
    }

    if (this->unk_322 & 0x100) {
        func_80B3CA20(this);
    }
}

s32 func_80B3D974(s16 arg0, s16 arg1, Vec3f* arg2, Vec3s* arg3, s32 arg4, s32 arg5) {
    Vec3f sp74;
    Vec3s sp6C;
    MtxF sp2C;

    Matrix_MultVec3f(&gZeroVec3f, &sp74);
    Matrix_Get(&sp2C);
    Matrix_MtxFToYXZRot(&sp2C, &sp6C, false);
    *arg2 = sp74;
    if (arg4 == 0) {
        if (arg5 != 0) {
            sp6C.z = arg0;
            sp6C.y = arg1;
        }
        Math_SmoothStepToS(&arg3->x, sp6C.x, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->y, sp6C.y, 3, 0x2AA8, 0xB6);
        Math_SmoothStepToS(&arg3->z, sp6C.z, 3, 0x2AA8, 0xB6);
    } else {
        arg3->x = sp6C.x;
        arg3->y = sp6C.y;
        arg3->z = sp6C.z;
    }

    return 1;
}

void EnDnp_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnDnp_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnDnp* this = THIS;
    s32 phi_v1 = 1;
    s32 phi_v0;

    if (this->unk_322 & 0x10) {
        phi_v0 = 0;
    } else {
        phi_v1 = 0;
        if (this->unk_322 & 0x40) {
            phi_v0 = 1;
        } else {
            phi_v0 = 0;
        }
    }

    if (limbIndex == DEKU_PRINCESS_LIMB_HEAD) {
        func_80B3D974(this->unk_330 + 0x4000, this->unk_332 + this->actor.shape.rot.y + 0x4000, &this->unk_1D8,
                      &this->unk_1E4, phi_v1, phi_v0);
        Matrix_Pop();
        Matrix_Translate(this->unk_1D8.x, this->unk_1D8.y, this->unk_1D8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_1E4.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_1E4.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_1E4.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnDnp_Draw(Actor* thisx, PlayState* play) {
    static TexturePtr sEyeTextures[] = {
        gDekuPrincessEyeOpenTex,
        gDekuPrincessEyeHalfTex,
        gDekuPrincessEyeClosedTex,
        gDekuPrincessEyeAngryTex,
    };
    EnDnp* this = THIS;

    if (this->unk_322 & 0x100) {
        OPEN_DISPS(play->state.gfxCtx);

        func_8012C28C(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeIndex]));

        SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                       this->skelAnime.dListCount, NULL, EnDnp_PostLimbDraw, EnDnp_TransformLimbDraw,
                                       &this->actor);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
