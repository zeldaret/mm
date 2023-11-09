/*
 * File: z_en_hg.c
 * Overlay: ovl_En_Hg
 * Description: Pamela's Father (Gibdo)
 */

#include "z_en_hg.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnHg*)thisx)

void EnHg_Init(Actor* thisx, PlayState* play);
void EnHg_Destroy(Actor* thisx, PlayState* play);
void EnHg_Update(Actor* thisx, PlayState* play);
void EnHg_Draw(Actor* thisx, PlayState* play);

void EnHg_SetupWait(EnHg* this);
void EnHg_Wait(EnHg* this, PlayState* play);
void EnHg_SetupChasePlayer(EnHg* this);
void EnHg_ChasePlayer(EnHg* this, PlayState* play);
void EnHg_SetupChasePlayerWait(EnHg* this);
void EnHg_ChasePlayerWait(EnHg* this, PlayState* play);
void EnHg_SetupReactToHit(EnHg* this);
void EnHg_ReactToHit(EnHg* this, PlayState* play);
void EnHg_PlayCutscene(EnHg* this, PlayState* play);
void EnHg_SetupCsAction(EnHg* this);
void EnHg_HandleCsAction(EnHg* this, PlayState* play);
s32 EnHg_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx);
void EnHg_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx);

typedef enum {
    /* 0 */ HG_CS_FIRST_ENCOUNTER,
    /* 1 */ HG_CS_GET_MASK,
    /* 2 */ HG_CS_SUBSEQUENT_ENCOUNTER,
    /* 3 */ HG_CS_SONG_OF_HEALING
} HgCsIndex;

ActorInit En_Hg_InitVars = {
    /**/ ACTOR_EN_HG,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_HARFGIBUD,
    /**/ sizeof(EnHg),
    /**/ EnHg_Init,
    /**/ EnHg_Destroy,
    /**/ EnHg_Update,
    /**/ EnHg_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
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
    { 18, 46, 0, { 0, 0, 0 } },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x1),
    /* Deku Stick     */ DMG_ENTRY(1, 0xD),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(1, 0xF),
    /* Zora boomerang */ DMG_ENTRY(3, 0xC),
    /* Normal arrow   */ DMG_ENTRY(3, 0xC),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0xF),
    /* Hookshot       */ DMG_ENTRY(0, 0x1),
    /* Goron punch    */ DMG_ENTRY(2, 0xF),
    /* Sword          */ DMG_ENTRY(1, 0xF),
    /* Goron pound    */ DMG_ENTRY(1, 0xF),
    /* Fire arrow     */ DMG_ENTRY(3, 0x2),
    /* Ice arrow      */ DMG_ENTRY(3, 0x3),
    /* Light arrow    */ DMG_ENTRY(1, 0x4),
    /* Goron spikes   */ DMG_ENTRY(2, 0xF),
    /* Deku spin      */ DMG_ENTRY(0, 0x1),
    /* Deku bubble    */ DMG_ENTRY(1, 0xD),
    /* Deku launch    */ DMG_ENTRY(2, 0xF),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x1),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0xF),
    /* Zora punch     */ DMG_ENTRY(1, 0xF),
    /* Spin attack    */ DMG_ENTRY(1, 0xF),
    /* Sword beam     */ DMG_ENTRY(2, 0x0),
    /* Normal Roll    */ DMG_ENTRY(4, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(1, 0xF),
};

static CollisionCheckInfoInit2 sColChkInfoInit2 = {
    0, 0, 0, 0, 0x80,
};

typedef enum {
    /* 0 */ HG_ANIM_IDLE,
    /* 1 */ HG_ANIM_LURCH_FORWARD,
    /* 2 */ HG_ANIM_RECOIL,
    /* 3 */ HG_ANIM_LEAN_FORWARD,
    /* 4 */ HG_ANIM_REACH_FORWARD,
    /* 5 */ HG_ANIM_CURL_UP,
    /* 6 */ HG_ANIM_CROUCHED_PANIC,
    /* 7 */ HG_ANIM_PANIC,
    /* 8 */ HG_ANIM_MAX
} HgAnimation;

static AnimationInfo sAnimationInfo[HG_ANIM_MAX] = {
    { &gPamelasFatherIdleAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },          // HG_ANIM_IDLE
    { &gPamelasFatherLurchForwardAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },  // HG_ANIM_LURCH_FORWARD
    { &gPamelasFatherRecoilFromHitAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f }, // HG_ANIM_RECOIL
    { &gPamelasFatherLeanForwardAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },    // HG_ANIM_LEAN_FORWARD
    { &gPamelasFatherReachForwardAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },   // HG_ANIM_REACH_FORWARD
    { &gPamelasFatherCurlUpAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },         // HG_ANIM_CURL_UP
    { &gPamelasFatherCrouchedPanicAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },  // HG_ANIM_CROUCHED_PANIC
    { &gPamelasFatherPanicAnim, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },          // HG_ANIM_PANIC
};

static u32 sHasSoundPlayed = false;

void EnHg_Init(Actor* thisx, PlayState* play) {
    EnHg* this = THIS;
    s16 csId = this->actor.csId;
    s32 i;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 36.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gPamelasFatherGibdoSkel, &gPamelasFatherIdleAnim, this->jointTable,
                       this->morphTable, PAMELAS_FATHER_GIBDO_LIMB_MAX);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit2);
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_75_20) || CHECK_WEEKEVENTREG(WEEKEVENTREG_CLEARED_STONE_TOWER_TEMPLE)) {
        Actor_Kill(&this->actor);
    }
    this->actor.targetMode = TARGET_MODE_1;
    this->actor.colChkInfo.health = 0;
    this->actor.gravity = -1.0f;
    for (i = 0; i < ARRAY_COUNT(this->csIdList); i++) {
        if (csId == CS_ID_NONE) {
            break;
        }
        this->csIdList[i] = csId;
        csId = CutsceneManager_GetAdditionalCsId(csId);
    }
    EnHg_SetupWait(this);
}

void EnHg_Destroy(Actor* thisx, PlayState* play) {
    EnHg* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnHg_SetupWait(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_IDLE);
    this->actionFunc = EnHg_Wait;
}

void EnHg_Wait(EnHg* this, PlayState* play) {
    if (this->actor.colChkInfo.health == 1) {
        if (((this->actor.xzDistToPlayer < 200.0f) && (this->actor.playerHeightRel < 40.0f)) &&
            !Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_483)) {
            EnHg_SetupChasePlayer(this);
        }
        if ((gSaveContext.sceneLayer == 0) && (play->csCtx.scriptIndex == 0) &&
            ((play->csCtx.curFrame == 20) || (play->csCtx.curFrame == 60))) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_HALF_REDEAD_SURPRISE);
        }
    }
}

void EnHg_SetupChasePlayer(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_LURCH_FORWARD);
    this->actionFunc = EnHg_ChasePlayer;
}

void EnHg_ChasePlayer(EnHg* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 pad;

    this->actor.speed = 1.6f;
    if (!(player->stateFlags2 & PLAYER_STATE2_8000000) && (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE)) {
        if (((this->skelAnime.curFrame > 9.0f) && (this->skelAnime.curFrame < 16.0f)) ||
            ((this->skelAnime.curFrame > 44.0f) && (this->skelAnime.curFrame < 51.0f))) {
            Actor_MoveWithGravity(&this->actor);
            Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 5, 0x3E8, 0x14);
            this->actor.world.rot.y = this->actor.shape.rot.y;
        }
        if ((Math_Vec3f_DistXZ(&this->actor.world.pos, &this->actor.home.pos) > 200.0f) &&
            (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) > 200.0f)) {
            EnHg_SetupChasePlayerWait(this);
        }
    }
}

void EnHg_SetupChasePlayerWait(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_IDLE);
    this->actionFunc = EnHg_ChasePlayerWait;
}

void EnHg_ChasePlayerWait(EnHg* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (Math_Vec3f_DistXZ(&player->actor.world.pos, &this->actor.home.pos) < 200.0f) {
        EnHg_SetupChasePlayer(this);
    }
}

void EnHg_SetupReactToHit(EnHg* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_RECOIL);
    this->actionFunc = EnHg_ReactToHit;
}

void EnHg_ReactToHit(EnHg* this, PlayState* play) {
    if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        EnHg_SetupChasePlayerWait(this);
    }
}

void EnHg_HandleTatlDialog(EnHg* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_NONE) {
        if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
            Message_StartTextbox(play, 0x24F, &this->actor);
        } else {
            Actor_OfferTalk(&this->actor, play, 80.0f);
        }
    }
}

void EnHg_PlayRedeadSfx(EnHg* this, PlayState* play) {
    if (this->actor.colChkInfo.health == 1) {
        if ((this->actionFunc == EnHg_ChasePlayer) || (this->actionFunc == EnHg_ReactToHit) ||
            (this->actionFunc == EnHg_ChasePlayerWait)) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_HALF_REDEAD_LOOP - SFX_FLAG);
        }
    }
}

void EnHg_UpdateCollision(EnHg* this, PlayState* play) {
    if (this->actor.colChkInfo.health != 0) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            EnHg_SetupReactToHit(this);
        }
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
        if ((this->actionFunc != EnHg_ReactToHit) && (this->actionFunc != EnHg_PlayCutscene) &&
            (this->actionFunc != EnHg_HandleCsAction)) {
            CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

void EnHg_SetupCutscene(EnHg* this) {
    this->actionFunc = EnHg_PlayCutscene;
}

void EnHg_PlayCutscene(EnHg* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->csIdList[this->csIdIndex])) {
        CutsceneManager_Start(this->csIdList[this->csIdIndex], &this->actor);
        EnHg_SetupCsAction(this);
    } else {
        if (CutsceneManager_GetCurrentCsId() == CS_ID_GLOBAL_TALK) {
            CutsceneManager_Stop(CS_ID_GLOBAL_TALK);
        }
        CutsceneManager_Queue(this->csIdList[this->csIdIndex]);
    }
}

void EnHg_SetupCsAction(EnHg* this) {
    this->csIdList[3] = 99;
    this->csIdList[2] = 0;
    this->actionFunc = EnHg_HandleCsAction;
}

void EnHg_HandleCsAction(EnHg* this, PlayState* play) {
    if (Cutscene_IsCueInChannel(play, CS_CMD_ACTOR_CUE_484)) {
        s32 cueChannel = Cutscene_GetCueChannel(play, CS_CMD_ACTOR_CUE_484);

        if (this->csIdList[3] != play->csCtx.actorCues[cueChannel]->id) {
            this->csIdList[3] = play->csCtx.actorCues[cueChannel]->id;
            switch (play->csCtx.actorCues[cueChannel]->id) {
                case 1:
                    this->animIndex = HG_ANIM_IDLE;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_IDLE);
                    break;

                case 2:
                    this->csIdList[2] = 0;
                    this->animIndex = HG_ANIM_LEAN_FORWARD;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_LEAN_FORWARD);
                    break;

                case 3:
                    this->csIdList[2] = 0;
                    this->animIndex = HG_ANIM_CURL_UP;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_CURL_UP);
                    break;

                case 4:
                    this->csIdList[2] = 0;
                    this->animIndex = HG_ANIM_PANIC;
                    if ((this->csIdIndex == HG_CS_GET_MASK) || (this->csIdIndex == HG_CS_SONG_OF_HEALING)) {
                        Audio_PlaySfx_2(NA_SE_EN_HALF_REDEAD_TRANS);
                    }
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_PANIC);
                    break;

                case 5:
                    this->animIndex = HG_ANIM_LURCH_FORWARD;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_LURCH_FORWARD);
                    break;

                case 6:
                    SET_WEEKEVENTREG(WEEKEVENTREG_75_20);
                    Actor_Kill(&this->actor);
                    break;

                default:
                    break;
            }
        } else if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            switch (this->animIndex) {
                case HG_ANIM_LEAN_FORWARD:
                    this->animIndex = HG_ANIM_REACH_FORWARD;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_REACH_FORWARD);
                    break;

                case HG_ANIM_CURL_UP:
                    this->animIndex = HG_ANIM_CROUCHED_PANIC;
                    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, HG_ANIM_CROUCHED_PANIC);
                    break;

                default:
                    break;
            }
        }

        switch (this->animIndex) {
            case HG_ANIM_LEAN_FORWARD:
            case HG_ANIM_REACH_FORWARD:
                Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_HALF_REDEAD_LOOP - SFX_FLAG);
                break;

            case HG_ANIM_CURL_UP:
            case HG_ANIM_CROUCHED_PANIC:
                Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_HALF_REDEAD_SCREAME - SFX_FLAG);
                break;

            case HG_ANIM_PANIC:
                if ((this->csIdIndex == HG_CS_FIRST_ENCOUNTER) || (this->csIdIndex == HG_CS_SUBSEQUENT_ENCOUNTER)) {
                    Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_HALF_REDEAD_SCREAME - SFX_FLAG);
                }
                break;

            default:
                break;
        }

        Cutscene_ActorTranslateAndYaw(&this->actor, play, cueChannel);
        return;

    } else if (play->csCtx.state == CS_STATE_IDLE) {
        EnHg_SetupWait(this);
    }

    this->csIdList[3] = 99;
}

void EnHg_WaitForPlayerAction(EnHg* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    // If the player has gone upstairs this interaction will not trigger
    if ((this->actor.colChkInfo.health != 1) || (fabsf(this->actor.playerHeightRel) >= 80.0f)) {
        return;
    }

    if (player->stateFlags2 & PLAYER_STATE2_8000000) {
        if (!sHasSoundPlayed) {
            Audio_PlaySfx(NA_SE_SY_TRE_BOX_APPEAR);
        }
        sHasSoundPlayed = true;
    } else {
        sHasSoundPlayed = false;
    }

    if (play->msgCtx.ocarinaMode == OCARINA_MODE_EVENT) {
        if ((play->msgCtx.lastPlayedSong == OCARINA_SONG_HEALING) && (GET_PLAYER_FORM == PLAYER_FORM_HUMAN)) {
            if (INV_CONTENT(ITEM_MASK_GIBDO) == ITEM_MASK_GIBDO) {
                this->csIdIndex = HG_CS_SONG_OF_HEALING;
            } else {
                this->csIdIndex = HG_CS_GET_MASK;
            }

            EnHg_SetupCutscene(this);
        }

    } else {
        if ((this->actor.xzDistToPlayer < 60.0f) && (fabsf(this->actor.playerHeightRel) < 40.0f)) {
            if ((this->actionFunc != EnHg_PlayCutscene) && (this->actionFunc != EnHg_HandleCsAction)) {
                if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_61_02)) {
                    SET_WEEKEVENTREG(WEEKEVENTREG_61_02);
                    this->csIdIndex = HG_CS_FIRST_ENCOUNTER;
                } else {
                    this->csIdIndex = HG_CS_SUBSEQUENT_ENCOUNTER;
                }

                EnHg_SetupCutscene(this);
                return;
            }
        }

        EnHg_HandleTatlDialog(this, play);
    }
}

void EnHg_Update(Actor* thisx, PlayState* play) {
    EnHg* this = THIS;

    this->actionFunc(this, play);
    SkelAnime_Update(&this->skelAnime);
    EnHg_UpdateCollision(this, play);
    EnHg_WaitForPlayerAction(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 30.0f, 25.0f, 0.0f, UPDBGCHECKINFO_FLAG_1 | UPDBGCHECKINFO_FLAG_4);
    EnHg_PlayRedeadSfx(this, play);
}

s32 EnHg_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return false;
}

void EnHg_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnHg* this = THIS;
    if (limbIndex == PAMELAS_FATHER_GIBDO_LIMB_EYEBROWS) {
        Matrix_Get(&this->mf);
    } else if (limbIndex == PAMELAS_FATHER_GIBDO_LIMB_HEAD) {
        Matrix_MultZero(&this->actor.focus.pos);
    }
}

void EnHg_Draw(Actor* thisx, PlayState* play) {
    EnHg* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnHg_OverrideLimbDraw, EnHg_PostLimbDraw, &this->actor);
    Matrix_Put(&this->mf);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, gPamelasFatherGibdoEyebrowsDL);

    CLOSE_DISPS(play->state.gfxCtx);
}
