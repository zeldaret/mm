/*
 * File: z_en_scopenuts.c
 * Overlay: ovl_En_Scopenuts
 * Description: Business Scrub that sells you a Heart Piece
 */

#include "z_en_scopenuts.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_dnt/object_dnt.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnScopenuts*)thisx)

void EnScopenuts_Init(Actor* thisx, PlayState* play);
void EnScopenuts_Destroy(Actor* thisx, PlayState* play);
void EnScopenuts_Update(Actor* thisx, PlayState* play);
void EnScopenuts_Draw(Actor* thisx, PlayState* play);

void func_80BCB078(EnScopenuts* this, PlayState* play);
void func_80BCB1C8(EnScopenuts* this, PlayState* play);
void func_80BCB4DC(EnScopenuts* this, PlayState* play);
void func_80BCB52C(EnScopenuts* this, PlayState* play);
void func_80BCB6D0(EnScopenuts* this, PlayState* play);
void func_80BCB90C(EnScopenuts* this, PlayState* play);
void func_80BCB980(EnScopenuts* this, PlayState* play);
void func_80BCBA00(EnScopenuts* this, PlayState* play);
void func_80BCBC60(EnScopenuts* this, PlayState* play);
void func_80BCBD28(EnScopenuts* this, PlayState* play);
void func_80BCBF0C(EnScopenuts* this, PlayState* play);
void func_80BCBFFC(EnScopenuts* this, PlayState* play);
void func_80BCC288(EnScopenuts* this, PlayState* play);
s32 func_80BCC2AC(EnScopenuts* this, Path* path, s32 arg2_);
f32 func_80BCC448(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3);

ActorInit En_Scopenuts_InitVars = {
    /**/ ACTOR_EN_SCOPENUTS,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_DNT,
    /**/ sizeof(EnScopenuts),
    /**/ EnScopenuts_Init,
    /**/ EnScopenuts_Destroy,
    /**/ EnScopenuts_Update,
    /**/ EnScopenuts_Draw,
};

static ColliderCylinderInitType1 sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
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
    { 27, 32, 0, { 0, 0, 0 } },
};

static AnimationInfoS sAnimationInfo[] = {
    { &gBusinessScrubStandingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubRiseUpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubJumpAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubBurrowAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubExcitedStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubExcitedLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubExcitedEndAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubTakeOffHatAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubFlyStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubFlyLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubShockedStartAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubShockedShakeHeadAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubShockedPoundAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubShockedEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubThinkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubBobAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gBusinessScrubBurrowAnim, 1.0f, 8, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubBurrowAnim, 1.0f, 4, -1, ANIMMODE_ONCE, -4 },
    { &gBusinessScrubBurrowAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubFlyLoopAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gBusinessScrubTakeOffHatAnim, -1.0f, 0, -1, ANIMMODE_ONCE, 0 },
    { &gBusinessScrubFlyEndAnim, 1.0f, 0, -1, ANIMMODE_ONCE, 0 },
};

Gfx* D_80BCCCDC[] = { gKakeraLeafMiddleDL, gKakeraLeafTipDL };

Vec3f D_80BCCCE4 = { 0.0f, -0.5f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_U8(targetMode, TARGET_MODE_0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

s16 func_80BCABF0(Path* path) {
    Vec3s* sp34 = Lib_SegmentedToVirtual(path->points);
    Vec3f sp28;
    Vec3f sp1C;

    Math_Vec3s_ToVec3f(&sp28, &sp34[0]);
    Math_Vec3s_ToVec3f(&sp1C, &sp34[1]);
    return Math_Vec3f_Yaw(&sp28, &sp1C);
}

void func_80BCAC40(EnScopenuts* this, PlayState* play) {
    s16 i;
    Vec3f sp60;
    Vec3f sp54;

    sp60 = this->actor.world.pos;
    sp60.y += 100.0f;

    for (i = 0; i < 36; i++) {
        sp54.x = Rand_Centered() * 10.0f;
        sp54.y = 2.0f * Rand_Centered();
        sp54.z = Rand_Centered() * 10.0f;
        EffectSsHahen_Spawn(play, &sp60, &sp54, &D_80BCCCE4, 0, 150, GAMEPLAY_KEEP, 16, D_80BCCCDC[i & 1]);
    }
}

void func_80BCAD64(EnScopenuts* this, s16 arg1) {
    f32 sp24 = Math_CosS(this->actor.world.rot.x) * this->actor.speed;

    switch (arg1) {
        case 1:
            this->actor.velocity.y = this->actor.speed;
            this->actor.velocity.x = 0.0f;
            this->actor.velocity.z = 0.0f;
            break;

        case 2:
            this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * this->actor.speed;
            this->actor.velocity.y = 0.0f;
            this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * this->actor.speed;
            break;

        case 3:
            this->actor.velocity.x = 0.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.velocity.z = 0.0f;
            break;

        default:
            this->actor.velocity.x = Math_SinS(this->actor.world.rot.y) * sp24;
            this->actor.velocity.y = Math_SinS(this->actor.world.rot.x) * this->actor.speed;
            this->actor.velocity.z = Math_CosS(this->actor.world.rot.y) * sp24;
            break;
    }
    Actor_UpdatePos(&this->actor);
}

void func_80BCAE78(EnScopenuts* this, PlayState* play) {
    if (this->unk_328 & 4) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }

    if (this->unk_328 & 2) {
        Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 20.0f, 20.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    }
}

s16 func_80BCAF0C(EnScopenuts* this) {
    switch (this->unk_33C) {
        case 0x0:
            if (CHECK_WEEKEVENTREG(WEEKEVENTREG_53_02)) {
                this->unk_328 |= 1;
                return 0x1638;
            }
            return 0x162F;
        case 0x162F:
            return 0x1630;
        case 0x1630:
            return 0x1631;
        case 0x1631:
            this->unk_358 = 150;
            return 0x1632;
        case 0x1633:
            this->unk_358 = 100;
            return 0x1634;
    }
    return 0;
}

void func_80BCAFA8(EnScopenuts* this, PlayState* play) {
    Vec3f screenPos;

    Play_GetScreenPos(play, &this->actor.world.pos, &screenPos);
    if ((screenPos.x >= 130.0f) && (screenPos.x < (SCREEN_WIDTH - 130.0f)) && (screenPos.y >= 90.0f)) {
        if (screenPos.y < (SCREEN_HEIGHT - 90.0f)) {
            this->actor.draw = EnScopenuts_Draw;
            this->unk_348 = 10;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 10);
            this->actionFunc = func_80BCB078;
        }
    }
}

void func_80BCB078(EnScopenuts* this, PlayState* play) {
    Vec3s sp30;

    if (this->path != NULL) {
        func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp30);
        if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            sp30.y = this->actor.wallYaw;
        }
        Math_SmoothStepToS(&this->actor.world.rot.y, sp30.y, 10, 300, 0);
        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_33E = 0x1000;
        this->unk_340 += 0x1C71;
        this->actor.world.rot.x = -sp30.x;
        if (func_80BCC2AC(this, this->path, this->unk_334)) {
            if (this->unk_334 >= (this->path->count - 1)) {
                this->actionFunc = func_80BCB1C8;
                this->actor.speed = 0.0f;
                this->actor.gravity = -1.0f;
                return;
            }
            this->unk_334++;
        }
    }

    if (this->unk_334 >= (this->path->count - 2)) {
        Math_ApproachF(&this->actor.speed, 1.5f, 0.2f, 1.0f);
    } else {
        Math_ApproachF(&this->actor.speed, 5.0f, 0.2f, 1.0f);
    }
    Actor_MoveWithoutGravity(&this->actor);
}

void func_80BCB1C8(EnScopenuts* this, PlayState* play) {
    this->unk_350 *= 0.92f;
    Actor_SetScale(&this->actor, this->unk_350);
    if (this->actor.bgCheckFlags & BGCHECKFLAG_GROUND) {
        SET_WEEKEVENTREG(WEEKEVENTREG_52_40);
        Actor_Kill(&this->actor);
    }
}

void func_80BCB230(EnScopenuts* this, PlayState* play) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 sp24 = Animation_GetLastFrame(sAnimationInfo[this->unk_348].animation);

    Math_ApproachS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 2, 0xE38);

    if ((((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false) &&
        ((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        Actor_PlaySfx(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        this->actionFunc = func_80BCB4DC;
        this->unk_348 = 3;
        this->collider.dim.height = 64;
        func_80BCAC40(this, play);
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 3);
    } else if (sp26 == sp24) {
        if ((this->unk_348 == 4) || (this->unk_348 == 18)) {
            this->unk_348 = 17;
            this->collider.dim.height = 0;
            Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_DOWN);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 17);
        } else if (this->unk_348 == 2) {
            this->unk_348 = 16;
            this->collider.dim.height = 32;
            Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_UP);
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 16);
        } else if (this->unk_348 == 17) {
            if (DECR(this->unk_34E) == 0) {
                this->unk_34E = Rand_ZeroOne() * 10.0f;
                this->unk_348 = 2;
                this->collider.dim.height = 32;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 2);
            }
        } else if ((this->unk_348 == 16) && (DECR(this->unk_34E) == 0)) {
            this->unk_34E = Rand_S16Offset(40, 40);
            this->unk_348 = 18;
            this->collider.dim.height = 32;
            SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 18);
        }
    }
}

void func_80BCB4DC(EnScopenuts* this, PlayState* play) {
    if (this->skelAnime.curFrame == this->skelAnime.endFrame) {
        this->actionFunc = func_80BCB52C;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 0);
    }
}

void func_80BCB52C(EnScopenuts* this, PlayState* play) {
    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 3, 2000, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_33C = func_80BCAF0C(this);
        Message_StartTextbox(play, this->unk_33C, &this->actor);
        this->actionFunc = func_80BCB6D0;
    } else if (((this->actor.xzDistToPlayer < 100.0f) &&
                (((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false)) ||
               this->actor.isLockedOn) {
        Actor_OfferTalk(&this->actor, play, 100.0f);
    } else if (!(((this->actor.playerHeightRel < 50.0f) && (this->actor.playerHeightRel > -50.0f)) ? true : false) ||
               !((this->actor.xzDistToPlayer < 200.0f) ? true : false)) {
        this->unk_348 = 4;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 4);
        this->actionFunc = func_80BCB230;
    }
}

void func_80BCB6D0(EnScopenuts* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (talkState == TEXT_STATE_5) {
        if (Message_ShouldAdvance(play)) {
            if (this->unk_328 & 1) {
                this->unk_328 &= ~1;
                play->msgCtx.msgMode = MSGMODE_TEXT_CLOSING;
                play->msgCtx.stateTimer = 4;
                this->actor.flags &= ~ACTOR_FLAG_TARGETABLE;
                this->unk_328 &= ~4;
                this->unk_348 = 8;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 8);
                this->actionFunc = func_80BCBA00;
            } else {
                this->unk_33C = func_80BCAF0C(this);
                Message_StartTextbox(play, this->unk_33C, &this->actor);
            }
        }
    } else if (talkState == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            switch (play->msgCtx.choiceIndex) {
                case 0:
                    if (gSaveContext.save.saveInfo.playerData.rupees < this->unk_358) {
                        Audio_PlaySfx(NA_SE_SY_ERROR);
                        this->unk_33C = 0x1636;
                        this->unk_328 |= 1;
                        Message_StartTextbox(play, this->unk_33C, &this->actor);
                    } else {
                        Audio_PlaySfx_MessageDecide();
                        play->msgCtx.msgMode = MSGMODE_TEXT_CLOSING;
                        play->msgCtx.stateTimer = 4;
                        Rupees_ChangeBy(-this->unk_358);
                        this->actionFunc = func_80BCB90C;
                    }
                    break;
                case 1:
                    Audio_PlaySfx_MessageCancel();
                    if (this->unk_358 == 150) {
                        this->unk_33C = 0x1633;
                    } else {
                        this->unk_33C = 0x1635;
                        this->unk_328 |= 1;
                    }
                    Message_StartTextbox(play, this->unk_33C, &this->actor);
                    break;
            }
        }
    } else if (talkState == TEXT_STATE_DONE) {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 400.0f, PLAYER_IA_MINUS1);
        this->actionFunc = func_80BCB980;
    }
}

void func_80BCB90C(EnScopenuts* this, PlayState* play) {
    if (Actor_HasParent(&this->actor, play)) {
        this->actor.parent = NULL;
        SET_WEEKEVENTREG(WEEKEVENTREG_53_02);
        this->actionFunc = func_80BCB6D0;
    } else {
        Actor_OfferGetItem(&this->actor, play, GI_HEART_PIECE, 300.0f, 300.0f);
    }
}

void func_80BCB980(EnScopenuts* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_33C = 0x1637;
        this->unk_328 |= 1;
        Message_StartTextbox(play, this->unk_33C, &this->actor);
        this->actionFunc = func_80BCB6D0;
    } else {
        Actor_OfferTalkExchangeEquiCylinder(&this->actor, play, 400.0f, PLAYER_IA_MINUS1);
    }
}

void func_80BCBA00(EnScopenuts* this, PlayState* play) {
    s16 sp26 = this->skelAnime.curFrame;
    s16 sp24 = Animation_GetLastFrame(sAnimationInfo[this->unk_348].animation);

    switch (sp26) {
        case 10:
            this->unk_35A = 1;
            this->unk_35C = 0.1f;
            this->unk_360 = 0.1f;
            this->unk_364 = 0.1f;
            break;

        case 11:
        case 12:
            this->unk_35C += 0.15f;
            this->unk_360 += 0.32f;
            this->unk_364 += 0.15f;
            break;

        case 13:
            this->unk_35C = 0.55f;
            this->unk_360 = 1.05f;
            this->unk_364 = 0.55f;
            break;

        case 14:
            this->unk_35C = 1.0f;
            this->unk_360 = 2.0f;
            this->unk_364 = 1.0f;
            break;

        case 15:
        case 16:
            this->unk_360 -= 0.33f;
            break;

        case 17:
            this->unk_360 = 1.0f;
            break;

        case 18:
        case 19:
            this->unk_360 += 0.27f;
            break;

        case 20:
            this->unk_35A = 2;
            this->unk_360 = 1.8f;
            break;

        case 21:
        case 22:
        case 23:
            this->unk_360 -= 0.2f;
            break;

        case 24:
            this->unk_360 = 1.0f;
            break;
    }

    if (this->unk_36C == 0) {
        if (CutsceneManager_IsNext(this->csId)) {
            CutsceneManager_StartWithPlayerCs(this->csId, &this->actor);
            this->unk_36C = 1;
        } else {
            if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
                CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
            }
            CutsceneManager_Queue(this->csId);
            return;
        }
    }

    if (sp26 == sp24) {
        this->unk_35A = 3;
        this->unk_348 = 19;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 19);
        Actor_PlaySfx(&this->actor, NA_SE_EN_NUTS_DOWN);
        this->unk_328 &= ~2;
        this->unk_34E = 50;
        this->unk_328 |= 8;
        this->unk_32C = this->actor.world.pos.y;
        this->actionFunc = func_80BCBC60;
    }
}

void func_80BCBC60(EnScopenuts* this, PlayState* play) {
    f32 sp24;
    Vec3f sp18;

    this->unk_340 += this->unk_34C;
    sp24 = this->unk_32C - this->actor.world.pos.y;

    if (!(this->unk_370 & 3)) {
        sp18.x = this->actor.world.pos.x;
        sp18.y = this->unk_32C;
        sp18.z = this->actor.world.pos.z;
        func_800B14D4(play, 20.0f, &sp18);
    }

    if (sp24 > 5.0f) {
        this->actor.velocity.y = 0.0f;
        this->actor.gravity = 0.0f;
        this->unk_372 = func_80BCABF0(this->path);
        this->actionFunc = func_80BCBD28;
    }
}

void func_80BCBD28(EnScopenuts* this, PlayState* play) {
    Vec3f sp44;
    s16 sp42 = this->skelAnime.curFrame;
    s16 sp40 = Animation_GetLastFrame(sAnimationInfo[this->unk_348].animation);
    Vec3s sp38;

    func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp38);
    if (sp42 == sp40) {
        Math_SmoothStepToS(&this->unk_34C, 0x1C71, 3, 0x100, 0);
        this->unk_340 += this->unk_34C;
        this->actor.shape.yOffset = 1500.0f;
    }

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->unk_372, 3, 2000, 0);
    this->actor.world.rot.y = this->actor.shape.rot.y;

    if (DECR(this->unk_34E) == 0) {
        if (!(this->unk_370 & 3)) {
            sp44 = this->actor.world.pos;
            func_800B14D4(play, 20.0f, &sp44);
        }
        this->actor.velocity.y = 5.0f;
    } else if (!(this->unk_370 & 3)) {
        sp44.x = this->actor.world.pos.x;
        sp44.y = this->unk_32C;
        sp44.z = this->actor.world.pos.z;
        func_800B14D4(play, 20.0f, &sp44);
    }

    if ((this->actor.home.pos.y + 22.5f) < this->actor.world.pos.y) {
        this->unk_368 = 0.3f;
        this->unk_348 = 9;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 9);
        Actor_PlaySfx(&this->actor, NA_SE_EN_AKINDONUTS_HIDE);
        func_80BCAC40(this, play);
        this->actionFunc = func_80BCBF0C;
    }
}

void func_80BCBF0C(EnScopenuts* this, PlayState* play) {
    this->unk_340 += this->unk_34C;
    if (this->unk_368 >= 1.0f) {
        this->unk_368 = 1.0f;
        this->actor.velocity.y = 5.0f;
    } else {
        this->actor.velocity.y = 5.0f;
        this->unk_368 += 0.1f;
    }

    if ((this->actor.home.pos.y + 50.0f) < this->actor.world.pos.y) {
        Math_ApproachF(&this->actor.velocity.y, 0.0f, 0.2f, 1.0f);
        this->unk_348 = 10;
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 10);
        this->unk_328 |= 2;
        this->unk_36E = 0;
        this->actionFunc = func_80BCBFFC;
    }
}

void func_80BCBFFC(EnScopenuts* this, PlayState* play) {
    Vec3s sp38;
    f32 sp34;
    s16 sp32 = 0;

    this->actor.velocity.y = 0.0f;
    this->actor.gravity = 0.0f;

    if (this->path != NULL) {
        sp34 = func_80BCC448(this->path, this->unk_334, &this->actor.world.pos, &sp38);
        if (this->actor.bgCheckFlags & BGCHECKFLAG_WALL) {
            sp38.y = this->actor.wallYaw;
        }

        if (this->unk_334 < 6) {
            Math_SmoothStepToS(&this->actor.world.rot.y, sp38.y, 10, 300, 0);
        } else {
            Math_SmoothStepToS(&this->actor.world.rot.y, sp38.y, 10, 1500, 0);
        }

        this->actor.shape.rot.y = this->actor.world.rot.y;
        this->unk_33E = 0x1000;
        this->unk_340 += this->unk_34C;
        this->actor.world.rot.x = -sp38.x;

        if (func_80BCC2AC(this, this->path, this->unk_334)) {
            sp32 = 1;
        }

        if (sp34 < 10.0f) {
            if (sp32 == 1) {
                sp32 = 3;
            } else {
                sp32 = 2;
            }
        }

        if (sp32 == 3) {
            if (this->unk_334 >= (this->path->count - 1)) {
                CutsceneManager_Stop(this->csId);
                CLEAR_WEEKEVENTREG(WEEKEVENTREG_52_40);
                this->actionFunc = func_80BCC288;
            } else {
                this->unk_334++;
            }
        }
    } else if (this->actor.playerHeightRel > 500.0f) {
        CutsceneManager_Stop(this->csId);
        this->actionFunc = func_80BCC288;
    }

    Math_ApproachF(&this->actor.speed, 1.0f, 0.2f, 1.0f);
    func_80BCAD64(this, sp32);

    if (this->unk_36C == 2) {
        if (CutsceneManager_IsNext(this->csId)) {
            CutsceneManager_StartWithPlayerCs(this->csId, &this->actor);
            this->unk_36C = 3;
        } else {
            CutsceneManager_Queue(this->csId);
            return;
        }
    } else if ((this->unk_36C == 1) && (this->unk_36E == 20)) {
        CutsceneManager_Stop(this->csId);
        this->csId = CutsceneManager_GetAdditionalCsId(this->csId);
        CutsceneManager_Queue(this->csId);
        this->unk_36C = 2;
    }
    this->unk_36E++;
}

void func_80BCC288(EnScopenuts* this, PlayState* play) {
    Actor_Kill(&this->actor);
}

s32 func_80BCC2AC(EnScopenuts* this, Path* path, s32 arg2_) {
    Vec3s* sp5C = Lib_SegmentedToVirtual(path->points);
    s32 sp58 = path->count;
    s32 arg2 = arg2_;
    s32 sp50 = false;
    f32 phi_f12;
    f32 phi_f14;
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    Vec3f sp30;

    Math_Vec3s_ToVec3f(&sp30, &sp5C[arg2]);

    if (arg2 == 0) {
        phi_f12 = sp5C[1].x - sp5C[0].x;
        phi_f14 = sp5C[1].z - sp5C[0].z;
    } else if ((sp58 - 1) == arg2) {
        phi_f12 = sp5C[sp58 - 1].x - sp5C[sp58 - 2].x;
        phi_f14 = sp5C[sp58 - 1].z - sp5C[sp58 - 2].z;
    } else {
        phi_f12 = sp5C[arg2 + 1].x - sp5C[arg2 - 1].x;
        phi_f14 = sp5C[arg2 + 1].z - sp5C[arg2 - 1].z;
    }

    func_8017B7F8(&sp30, RAD_TO_BINANG(Math_FAtan2F(phi_f12, phi_f14)), &sp44, &sp40, &sp3C);

    if (((this->actor.world.pos.x * sp44) + (sp40 * this->actor.world.pos.z) + sp3C) > 0.0f) {
        sp50 = true;
    }
    return sp50;
}

f32 func_80BCC448(Path* path, s32 arg1, Vec3f* arg2, Vec3s* arg3) {
    Vec3s* temp_v1;
    Vec3f sp20;

    if (path != NULL) {
        temp_v1 = Lib_SegmentedToVirtual(path->points);
        temp_v1 = &temp_v1[arg1];
        sp20.x = temp_v1[0].x;
        sp20.y = temp_v1[0].y;
        sp20.z = temp_v1[0].z;
    }

    arg3->y = Math_Vec3f_Yaw(arg2, &sp20);
    arg3->x = Math_Vec3f_Pitch(arg2, &sp20);

    return sp20.y - arg2->y;
}

void EnScopenuts_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnScopenuts* this = THIS;

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_74_40) &&
        (gSaveContext.save.saveInfo.inventory.items[ITEM_OCARINA_OF_TIME] == ITEM_NONE)) {
        Actor_Kill(&this->actor);
        return;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    SkelAnime_InitFlex(play, &this->skelAnime, &gBusinessScrubSkel, &gBusinessScrubStandingAnim, this->jointTable,
                       this->morphTable, 28);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinderType1(play, &this->collider, &this->actor, &sCylinderInit);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    this->unk_350 = 0.01f;
    Actor_SetScale(&this->actor, 0.01f);
    this->actor.colChkInfo.cylRadius = 0;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_328 |= 2;
    this->unk_328 |= 4;
    this->actor.speed = 0.0f;

    if (ENSCOPENUTS_GET_3E0(&this->actor) == ENSCOPENUTS_3E0_0) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_52_40)) {
            Actor_Kill(&this->actor);
        } else if (play->actorCtx.flags & ACTORCTX_FLAG_1) {
            this->path =
                SubS_GetPathByIndex(play, ENSCOPENUTS_GET_PATH_INDEX(&this->actor), ENSCOPENUTS_PATH_INDEX_NONE);
            this->actor.draw = NULL;
            this->actionFunc = func_80BCAFA8;
            this->actor.gravity = 0.0f;
        } else {
            Actor_Kill(&this->actor);
        }
    } else if (ENSCOPENUTS_GET_3E0(&this->actor) == ENSCOPENUTS_3E0_1) {
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_52_40)) {
            this->path =
                SubS_GetPathByIndex(play, ENSCOPENUTS_GET_PATH_INDEX(&this->actor), ENSCOPENUTS_PATH_INDEX_NONE);
            if (this->path == NULL) {
                Actor_Kill(&this->actor);
            } else {
                this->actor.gravity = -1.0f;
                this->actor.draw = EnScopenuts_Draw;
                this->csId = this->actor.csId;
                this->unk_33C = 0;
                this->unk_358 = 150;
                this->unk_348 = 4;
                this->unk_35A = 0;
                SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, 4);
                this->actionFunc = func_80BCB230;
            }
        } else {
            Actor_Kill(&this->actor);
        }
    } else {
        Actor_Kill(&this->actor);
    }
}

void EnScopenuts_Destroy(Actor* thisx, PlayState* play) {
    EnScopenuts* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnScopenuts_Update(Actor* thisx, PlayState* play) {
    EnScopenuts* this = THIS;

    Actor_SetFocus(&this->actor, 60.0f);
    SkelAnime_Update(&this->skelAnime);
    Actor_MoveWithGravity(&this->actor);

    this->actionFunc(this, play);

    if (this->unk_328 & 8) {
        Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_AKINDO_FLY - SFX_FLAG);
    }
    func_80BCAE78(this, play);
}

s32 EnScopenuts_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnScopenuts* this = THIS;

    if (((this->unk_348 == 4) && (this->unk_35A == 0)) || ((this->unk_348 == 8) && (this->unk_35A == 0)) ||
        (this->unk_348 == 18) || (this->unk_348 == 2) || (this->unk_348 == 3) || (this->unk_348 == 17) ||
        (this->unk_348 == 16)) {
        if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 23) || (limbIndex == 24) ||
            (limbIndex == 15)) {
            *dList = NULL;
        }
    } else if ((this->unk_348 == 8) || (this->unk_348 == 19)) {
        switch (this->unk_35A) {
            case 1:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;

            case 2:
            case 3:
                if ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27) || (limbIndex == 15) ||
                    (limbIndex == 25)) {
                    *dList = NULL;
                }
                break;
        }
    } else if (((this->unk_348 == 9) || (this->unk_348 == 10)) && ((limbIndex == 15) || (limbIndex == 25))) {
        *dList = NULL;
    }

    if (limbIndex == 26) {
        if ((this->unk_33C == 0x162F) || (this->unk_33C == 0x1630)) {
            *dList = gBusinessScrubEyesSquintDL;
        } else {
            *dList = gBusinessScrubEyesDL;
        }
    }

    return false;
}

void EnScopenuts_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnScopenuts_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnScopenuts* this = THIS;

    if (((this->unk_35A == 1) || (this->unk_35A == 2)) && ((limbIndex == 23) || (limbIndex == 24))) {
        Matrix_Scale(this->unk_35C, this->unk_360, this->unk_364, MTXMODE_APPLY);
    }

    if ((this->unk_348 == 9) && ((limbIndex == 16) || (limbIndex == 21) || (limbIndex == 27))) {
        Matrix_Scale(this->unk_368, this->unk_368, this->unk_368, MTXMODE_APPLY);
    }

    if (limbIndex == 24) {
        Matrix_RotateYS(this->unk_340, MTXMODE_APPLY);
    }
}

void EnScopenuts_Draw(Actor* thisx, PlayState* play) {
    EnScopenuts* this = THIS;

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnScopenuts_OverrideLimbDraw, EnScopenuts_PostLimbDraw,
                                   EnScopenuts_TransformLimbDraw, &this->actor);
}
