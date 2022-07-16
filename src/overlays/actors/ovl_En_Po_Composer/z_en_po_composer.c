/*
 * File: z_en_po_composer.c
 * Overlay: ovl_En_Po_Composer
 * Description: Poe Composers
 */

#include "z_en_po_composer.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((EnPoComposer*)thisx)

void EnPoComposer_Init(Actor* thisx, PlayState* play);
void EnPoComposer_Destroy(Actor* thisx, PlayState* play);
void EnPoComposer_Update(Actor* thisx, PlayState* play);
void EnPoComposer_Draw(Actor* thisx, PlayState* play);

void EnPoComposer_AwaitPlayer(EnPoComposer* this, PlayState* play);
void EnPoComposer_StartCutscene(EnPoComposer* this, PlayState* play);
void EnPoComposer_StartedCutscene(EnPoComposer* this, PlayState* play);
void EnPoComposer_PlayCurse(EnPoComposer* this, PlayState* play);
void EnPoComposer_IdleStill(EnPoComposer* this, PlayState* play);
void EnPoComposer_Appear(EnPoComposer* this, PlayState* play);
void EnPoComposer_Idle(EnPoComposer* this, PlayState* play);
void EnPoComposer_RaiseArms(EnPoComposer* this, PlayState* play);
void EnPoComposer_LowerArms(EnPoComposer* this, PlayState* play);
void EnPoComposer_CutscenePlayCurse(EnPoComposer* this, PlayState* play);
void EnPoComposer_Roll(EnPoComposer* this, PlayState* play);

void EnPoComposer_SetupAwaitPlayer(EnPoComposer* this);
void EnPoComposer_SetupStartCutscene(EnPoComposer* this);
void EnPoComposer_SetupStartedCutscene(EnPoComposer* this);
void EnPoComposer_StepLightAlpha(EnPoComposer* this);

const ActorInit En_Po_Composer_InitVars = {
    ACTOR_EN_PO_COMPOSER,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_PO_COMPOSER,
    sizeof(EnPoComposer),
    (ActorFunc)EnPoComposer_Init,
    (ActorFunc)EnPoComposer_Destroy,
    (ActorFunc)EnPoComposer_Update,
    (ActorFunc)EnPoComposer_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT3,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
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
    { 20, 40, 20, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0xF7CFFFFF, 0x00, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NORMAL,
            BUMP_NONE,
            OCELEM_ON,
        },
        { 9, { { 0, -1500, 0 }, 10 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_HIT3,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    ARRAY_COUNT(sJntSphElementsInit),
    sJntSphElementsInit,
};

static CollisionCheckInfoInit sColChkInfoInit = { 4, 25, 50, 40 };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(2, 0x0),
    /* Horse trample  */ DMG_ENTRY(1, 0x0),
    /* Explosives     */ DMG_ENTRY(2, 0x0),
    /* Zora boomerang */ DMG_ENTRY(1, 0x1),
    /* Normal arrow   */ DMG_ENTRY(2, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(2, 0x0),
    /* Hookshot       */ DMG_ENTRY(2, 0x1),
    /* Goron punch    */ DMG_ENTRY(1, 0x0),
    /* Sword          */ DMG_ENTRY(2, 0x0),
    /* Goron pound    */ DMG_ENTRY(4, 0x0),
    /* Fire arrow     */ DMG_ENTRY(2, 0x0),
    /* Ice arrow      */ DMG_ENTRY(2, 0x0),
    /* Light arrow    */ DMG_ENTRY(2, 0x0),
    /* Goron spikes   */ DMG_ENTRY(2, 0x0),
    /* Deku spin      */ DMG_ENTRY(2, 0x0),
    /* Deku bubble    */ DMG_ENTRY(2, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(1, 0x0),
    /* Zora punch     */ DMG_ENTRY(4, 0x0),
    /* Spin attack    */ DMG_ENTRY(2, 0x0),
    /* Sword beam     */ DMG_ENTRY(2, 0x0),
    /* Normal Roll    */ DMG_ENTRY(8, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(4, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(4, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

typedef enum {
    PO_COMPOSER_ANIM_IDLE_STILL,
    PO_COMPOSER_ANIM_APPEAR_DISAPPEAR,
    PO_COMPOSER_ANIM_IDLE,
    PO_COMPOSER_ANIM_RAISE_ARMS,
    PO_COMPOSER_ANIM_ARMS_RAISED,
    PO_COMPOSER_ANIM_LOWER_ARMS,
    PO_COMPOSER_ANIM_IDLE_FACING_DOWN,
    PO_COMPOSER_ANIM_BEGIN_PLAYING_CURSE,
    PO_COMPOSER_ANIM_PLAYING_CURSE,
    PO_COMPOSER_ANIM_BEGIN_ROLLING,
    PO_COMPOSER_ANIM_ROLLING,
    PO_COMPOSER_ANIM_FLEE,
    PO_COMPOSER_ANIM_ATTACK,
    PO_COMPOSER_ANIM_MAX,
} EnPoComposerAnim;

static AnimationInfo sAnimationInfo[PO_COMPOSER_ANIM_MAX] = {
    /*  0 */ { &object_po_composer_Anim_003DB0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  1 */ { &object_po_composer_Anim_003954, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, 0.0f },
    /*  2 */ { &object_po_composer_Anim_00188C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  3 */ { &object_po_composer_Anim_000570, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  4 */ { &object_po_composer_Anim_001F44, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  5 */ { &object_po_composer_Anim_0023E8, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  6 */ { &object_po_composer_Anim_002AE0, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  7 */ { &object_po_composer_Anim_000A58, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  8 */ { &object_po_composer_Anim_001420, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /*  9 */ { &object_po_composer_Anim_003024, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /* 10 */ { &object_po_composer_Anim_00334C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /* 11 */ { &object_po_composer_Anim_0015B8, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -4.0f },
    /* 12 */ { &object_po_composer_Anim_00020C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, 0.0f },
};

static Color_RGBA8 sLightColorInit = { 255, 255, 210, 0 };

static Color_RGBA8 sEnvColorInit = { 0, 0, 0, 255 };

Color_RGBA8 D_80BC6948 = { 75, 20, 25, 255 };

Color_RGBA8 D_80BC694C = { 80, 110, 90, 255 };

Color_RGBA8 D_80BC6950 = { 90, 85, 50, 255 };

Color_RGBA8 D_80BC6954 = { 100, 90, 100, 255 };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(targetArrowOffset, 3200, ICHAIN_STOP),
};

static s32 sPlayerIsPlayingOcarina = false;

void EnPoComposer_Init(Actor* thisx, PlayState* play) {
    EnPoComposer* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_po_composer_Skel_009930, &object_po_composer_Anim_00188C,
                       this->jointTable, this->morphTable, OBJECT_PO_COMPOSER_LIMB_MAX);
    Collider_InitJntSph(play, &this->lanternCollider);
    Collider_SetJntSph(play, &this->lanternCollider, &this->actor, &sJntSphInit, this->lanternColliderElements);
    Collider_InitCylinder(play, &this->bodyCollider);
    Collider_SetCylinder(play, &this->bodyCollider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->lightNode = LightContext_InsertLight(play, &play->lightCtx, &this->lightInfo);
    Lights_PointGlowSetInfo(&this->lightInfo, this->actor.home.pos.x, this->actor.home.pos.y, this->actor.home.pos.z,
                            255, 255, 255, 0);
    this->actor.flags &= ~1;
    this->lightColor = sLightColorInit;
    this->envColor = sEnvColorInit;
    this->lastCsAction = COMPOSER_CS_ACTION_NONE;

    if (PO_COMPOSER_IS_FLAT(&this->actor)) {
        this->unk290 = 0;
        this->unk330 = true;
        EnPoComposer_SetupStartedCutscene(this);
    } else if (this->actor.params & 0x4000) {
        if (gSaveContext.save.entrance != 0x20A0) {
            Actor_Kill(&this->actor);
        } else {
            this->unk290 = 0;
            this->unk330 = true;
            EnPoComposer_SetupStartedCutscene(this);
        }
    } else {
        s32 i;
        s16 csIndex = this->actor.csId;

        if (gSaveContext.save.saveInfo.weekEventReg[14] & 4) {
            Actor_Kill(&this->actor);
            return;
        }

        for (i = 0; i < ARRAY_COUNT(this->csIndices); i++) {
            if (csIndex == -1) {
                break;
            }
            this->csIndices[i] = csIndex;
            csIndex = CutsceneManager_GetAdditionalCsId(csIndex);
        }

        if (gSaveContext.save.saveInfo.weekEventReg[14] & 2) {
            this->unk290 = 1;
        } else {
            this->unk290 = 0;
        }
        this->unk330 = false;
        EnPoComposer_SetupAwaitPlayer(this);
    }
}

void EnPoComposer_Destroy(Actor* thisx, PlayState* play) {
    EnPoComposer* this = THIS;

    LightContext_RemoveLight(play, &play->lightCtx, this->lightNode);
    Collider_DestroyJntSph(play, &this->lanternCollider);
    Collider_DestroyCylinder(play, &this->bodyCollider);
}

void EnPoComposer_SetupAwaitPlayer(EnPoComposer* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_IDLE_STILL);
    this->actionFunc = EnPoComposer_AwaitPlayer;
}

void EnPoComposer_AwaitPlayer(EnPoComposer* this, PlayState* play) {
    if (this->actor.xzDistToPlayer < 200.0f) {
        EnPoComposer_SetupStartCutscene(this);
    }
}

void EnPoComposer_SetupStartCutscene(EnPoComposer* this) {
    this->unk330 = true;
    this->actionFunc = EnPoComposer_StartCutscene;
}

void EnPoComposer_StartCutscene(EnPoComposer* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->csIndices[this->unk290])) {
        CutsceneManager_Start(this->csIndices[this->unk290], &this->actor);
        EnPoComposer_SetupStartedCutscene(this);
    } else {
        if (CutsceneManager_GetCurrentCsId() == 0x7C) {
            CutsceneManager_Stop(0x7C);
        }
        CutsceneManager_Queue(this->csIndices[this->unk290]);
    }
}

void EnPoComposer_SetupStartedCutscene(EnPoComposer* this) {
    this->actionFunc = EnPoComposer_StartedCutscene;
}

void EnPoComposer_StartedCutscene(EnPoComposer* this, PlayState* play) {
}

void EnPoComposer_SetupPlayCurse(EnPoComposer* this) {
    this->actionTimer = 0;
    this->actor.flags |= ACTOR_FLAG_TARGETABLE;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_PLAYING_CURSE);
    this->actionFunc = EnPoComposer_PlayCurse;
}

void EnPoComposer_PlayCurse(EnPoComposer* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    // Damage the player every second
    if (this->actionTimer == 20) {
        func_800B8D10(play, &this->actor, 0.0f, 0, 0.0f, 1, 4);
        this->actionTimer = 0;
    } else {
        this->actionTimer++;
    }

    // Ocarina check
    if (player->stateFlags2 & PLAYER_STATE2_8000000) {
        if (!sPlayerIsPlayingOcarina) {
            // Play sound whenever the player begins playing the Ocarina
            Audio_PlaySfx(NA_SE_SY_TRE_BOX_APPEAR);
        }
        sPlayerIsPlayingOcarina = true;
    } else {
        sPlayerIsPlayingOcarina = false;
    }

    // Song check, check if player just played song of storms or song of healing to react to
    if (play->msgCtx.ocarinaMode == 3) {
        switch (play->msgCtx.lastPlayedSong) {
            case OCARINA_SONG_STORMS:
                this->unk290 = 3;
                EnPoComposer_SetupStartCutscene(this);
                break;
            case OCARINA_SONG_HEALING:
                this->unk290 = 2;
                EnPoComposer_SetupStartCutscene(this);
                break;
        }
    }

    // Play sharp's curse bgm
    func_801A1FB4(3, &this->actor.projectedPos, NA_BGM_SHARPS_CURSE, 2000.0f);
}

void EnPoComposer_SetupIdleStill(EnPoComposer* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_IDLE_STILL);
    this->actionFunc = EnPoComposer_IdleStill;
}

void EnPoComposer_IdleStill(EnPoComposer* this, PlayState* play) {
}

void EnPoComposer_SetupAppear(EnPoComposer* this) {
    this->actionTimer = 0;
    Actor_PlaySfx(&this->actor, NA_SE_EN_STALKIDS_APPEAR);
    Actor_PlaySfx(&this->actor, NA_SE_EN_PO_LAUGH);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_APPEAR_DISAPPEAR);
    this->actionFunc = EnPoComposer_Appear;
}

void EnPoComposer_Appear(EnPoComposer* this, PlayState* play) {
    this->actionTimer++;
    this->actor.shape.rot.y += 0x1000;
    if (this->actionTimer == 32) {
        EnPoComposer_SetupIdleStill(this);
    }
}

void EnPoComposer_SetupIdle(EnPoComposer* this) {
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_IDLE);
    this->actionFunc = EnPoComposer_Idle;
}

void EnPoComposer_Idle(EnPoComposer* this, PlayState* play) {
}

void EnPoComposer_SetupRaiseArms(EnPoComposer* this) {
    this->csActionTimer = 0;
    Actor_PlaySfx(&this->actor, NA_SE_EN_SHARP_REACTION);
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_RAISE_ARMS);
    this->actionFunc = EnPoComposer_RaiseArms;
}

void EnPoComposer_RaiseArms(EnPoComposer* this, PlayState* play) {
    if (this->csActionTimer == 0 && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->csActionTimer++;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_ARMS_RAISED);
    }
}

void EnPoComposer_SetupLowerArms(EnPoComposer* this) {
    this->csActionTimer = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_LOWER_ARMS);
    this->actionFunc = EnPoComposer_LowerArms;
}

void EnPoComposer_LowerArms(EnPoComposer* this, PlayState* play) {
    if (this->csActionTimer == 0 && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->csActionTimer++;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_IDLE_FACING_DOWN);
    }
}

void EnPoComposer_SetupCutscenePlayCurse(EnPoComposer* this) {
    this->csActionTimer = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_BEGIN_PLAYING_CURSE);
    this->actionFunc = EnPoComposer_CutscenePlayCurse;
}

void EnPoComposer_CutscenePlayCurse(EnPoComposer* this, PlayState* play) {
    if (this->csActionTimer == 0 && Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
        this->csActionTimer++;
        Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_PLAYING_CURSE);
    }
}

void EnPoComposer_SetupRoll(EnPoComposer* this) {
    this->csActionTimer = 0;
    Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_BEGIN_ROLLING);
    this->actionFunc = EnPoComposer_Roll;
}

void EnPoComposer_Roll(EnPoComposer* this, PlayState* play) {
    if (this->csActionTimer == 0) {
        if (Animation_OnFrame(&this->skelAnime, this->skelAnime.endFrame)) {
            this->csActionTimer++;
            Actor_PlaySfx(&this->actor, NA_SE_EN_SHARP_REACTION);
            Actor_ChangeAnimationByInfo(&this->skelAnime, sAnimationInfo, PO_COMPOSER_ANIM_ROLLING);
        }
    } else if (Animation_OnFrame(&this->skelAnime, 1.0f) && this->lightColor.a >= 33) {
        if (this->csActionTimer == 1) {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST3_DEAD_WIND2_OLD);
            this->csActionTimer = 2;
        } else {
            Actor_PlaySfx(&this->actor, NA_SE_EN_LAST3_DEAD_WIND3_OLD);
            this->csActionTimer = 1;
        }
    }
}

void EnPoComposer_SharpCutsceneDone(EnPoComposer* this) {
    gSaveContext.save.saveInfo.weekEventReg[14] |= 4;
    Actor_Kill(&this->actor);
}

s32 EnPoComposer_UpdateAction(EnPoComposer* this, PlayState* play) {
    u16 actorAction = PO_COMPOSER_IS_FLAT(&this->actor) ? 0x1E2 : 0x1E1;
    s32 actorActionIdx;

    if (!this->unk330) {
        return false;
    }

    if (Cutscene_IsCueInChannel(play, actorAction)) {
        actorActionIdx = Cutscene_GetCueChannel(play, actorAction);
        if (this->lastCsAction != play->csCtx.actorCues[actorActionIdx]->id) {
            this->lastCsAction = play->csCtx.actorCues[actorActionIdx]->id;
            switch (play->csCtx.actorCues[actorActionIdx]->id) {
                case COMPOSER_CS_ACTION_IDLE: // loop idle
                    EnPoComposer_SetupIdleStill(this);
                    break;
                case COMPOSER_CS_ACTION_APPEAR_SPIN: // appear/disappear -> loop idle
                    EnPoComposer_SetupAppear(this);
                    break;
                case COMPOSER_CS_ACTION_IDLE2: // loop sharp idle
                    EnPoComposer_SetupIdle(this);
                    break;
                case COMPOSER_CS_ACTION_RAISE_ARMS: // raise arms -> loop arms raised
                    EnPoComposer_SetupRaiseArms(this);
                    break;
                case COMPOSER_CS_ACTION_LOWER_ARMS: // lower arms -> loop idle
                    EnPoComposer_SetupLowerArms(this);
                    break;
                case COMPOSER_CS_ACTION_PLAY_CURSE: // begin playing -> loop playing
                    EnPoComposer_SetupCutscenePlayCurse(this);
                    break;
                case COMPOSER_CS_ACTION_ROLL: // begin rolling -> loop rolling
                    EnPoComposer_SetupRoll(this);
                    break;
                case COMPOSER_CS_ACTION_APPEAR: // appear
                    this->visible = true;
                    break;
                case COMPOSER_CS_ACTION_DISAPPEAR: // disappear
                    this->visible = false;
                    Actor_PlaySfx(&this->actor, NA_SE_EN_PO_DISAPPEAR);
                    break;
                case COMPOSER_CS_ACTION_DONE:
                    if (actorAction == 0x1E1) {
                        EnPoComposer_SharpCutsceneDone(this);
                    } else {
                        Actor_Kill(&this->actor);
                    }
                    break;
            }
        }
        if (this->actionFunc != EnPoComposer_Appear) {
            Cutscene_ActorTranslateAndYaw(&this->actor, play, actorActionIdx);
        } else {
            Cutscene_ActorTranslate(&this->actor, play, actorActionIdx);
        }

        EnPoComposer_StepLightAlpha(this);

        if (this->unk290 == 3 && play->csCtx.curFrame == 204) {
            Audio_PlaySfx(NA_SE_SY_DIZZY_EFFECT);
        }

        if (this->visible == true) {
            Actor_PlaySfx_Flagged(&this->actor, NA_SE_EN_SHARP_FLOAT - SFX_FLAG);
        }
        return true;
    }

    if (this->actionFunc != EnPoComposer_StartedCutscene && this->actionFunc != EnPoComposer_StartCutscene &&
        this->actionFunc != EnPoComposer_PlayCurse && play->csCtx.state == 0) {
        if (PO_COMPOSER_IS_FLAT(&this->actor)) {
            EnPoComposer_SetupStartedCutscene(this);
        } else if (this->actor.params & 0x4000) {
            EnPoComposer_SetupStartedCutscene(this);
        } else {
            this->unk330 = false;
            if (this->unk290 < 3) {
                if (!(gSaveContext.save.saveInfo.weekEventReg[14] & 2)) {
                    gSaveContext.save.saveInfo.weekEventReg[14] |= 2;
                }
                EnPoComposer_SetupPlayCurse(this);
            } else {
                EnPoComposer_SetupStartedCutscene(this);
            }
        }
    }

    this->lastCsAction = COMPOSER_CS_ACTION_NONE;
    return false;
}

void EnPoComposer_StepLightAlpha(EnPoComposer* this) {
    if (this->visible == true && this->lightColor.a != 255) {
        if (this->lightColor.a > 247) {
            this->lightColor.a = 255;
        } else {
            this->lightColor.a = this->lightColor.a + 7;
        }
    } else if (!this->visible && this->lightColor.a != 0) {
        if (this->lightColor.a < 8) {
            this->lightColor.a = 0;
        } else {
            this->lightColor.a = this->lightColor.a - 7;
        }
    }
}

void EnPoComposer_StepLightColor(EnPoComposer* this) {
    s16 color;

    color = this->lightColor.r + 5;
    this->lightColor.r = CLAMP_MAX(color, 255);

    color = this->lightColor.g + 5;
    this->lightColor.g = CLAMP_MAX(color, 255);

    if (this->lightColor.b > 210) {
        color = this->lightColor.b - 5;
        this->lightColor.b = CLAMP_MIN(color, 210);
    } else {
        color = this->lightColor.b + 5;
        this->lightColor.b = CLAMP_MAX(color, 210);
    }
}

void EnPoComposer_UpdateEnvColor(EnPoComposer* this) {
    f32 temp_fv0;
    u32 temp_v0;

    if (this->actionFunc == EnPoComposer_Appear && this->skelAnime.curFrame < 12.0f) {
        temp_v0 = 55.0f + this->skelAnime.curFrame * 16.66f;
        this->envColor.b = temp_v0;
        this->envColor.g = temp_v0;
        this->envColor.r = temp_v0;
        this->envColor.a = this->skelAnime.curFrame * 16.666666f;
    } else {
        temp_fv0 = Rand_ZeroOne();
        this->envColor.r = 225 + (s32)(temp_fv0 * 30.0f);
        this->envColor.g = 155 + (s32)(temp_fv0 * 100.0f);
        this->envColor.b = 95 + (s32)(temp_fv0 * 160.0f);
        this->envColor.a = 200;
    }
    if (this->lightColor.a == 0) {
        this->envColor.a = 0;
    }
}

void EnPoComposer_UpdateCollision(EnPoComposer* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->bodyCollider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->bodyCollider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->lanternCollider.base);
}

void EnPoComposer_Update(Actor* thisx, PlayState* play) {
    EnPoComposer* this = THIS;

    EnPoComposer_UpdateEnvColor(this);
    SkelAnime_Update(&this->skelAnime);
    Actor_SetFocus(&this->actor, 42.0f);

    this->actionFunc(this, play);

    if (!EnPoComposer_UpdateAction(this, play)) {
        EnPoComposer_UpdateCollision(this, play);
    }
}

s32 EnPoComposer_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                                  Gfx** gfx) {
    EnPoComposer* this = THIS;

    if (this->lightColor.a == 0 || limbIndex == OBJECT_PO_COMPOSER_LIMB_09) { // lantern
        *dList = NULL;
    } else if (PO_COMPOSER_IS_FLAT(&this->actor) && limbIndex == OBJECT_PO_COMPOSER_LIMB_0A) { // head
        *dList = object_po_composer_DL_006FD8;                                                 // flat head
    }

    if (limbIndex == 19) {
        //! @bug skeleton does not have a limb 19, this is leftover from OoT Poes
        gDPPipeSync((*gfx)++);
        gDPSetEnvColor((*gfx)++, this->lightColor.r, this->lightColor.g, this->lightColor.b, this->lightColor.a);
    }

    return 0;
}

void EnPoComposer_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnPoComposer* this = THIS;

    Collider_UpdateSpheres(limbIndex, &this->lanternCollider);
    if (limbIndex == OBJECT_PO_COMPOSER_LIMB_09) {
        Matrix_Get(&this->lanternMtxF);
    }
}

void EnPoComposer_Draw(Actor* thisx, PlayState* play) {
    EnPoComposer* this = THIS;
    s32 pad;
    Gfx* dl;
    Color_RGBA8* clothingColor;
    Color_RGBA8* var_t0;
    Vec3f sp88;
    Vec3s lightPos;

    OPEN_DISPS(play->state.gfxCtx);

    EnPoComposer_StepLightColor(this);

    // Select colors

    if (PO_COMPOSER_IS_FLAT(&this->actor)) {
        clothingColor = &D_80BC694C;
        var_t0 = &D_80BC6954;
    } else {
        clothingColor = &D_80BC6948;
        var_t0 = &D_80BC6950;
    }

    // Draw skeleton

    if (this->lightColor.a == 255 || this->lightColor.a == 0) {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x08,
                   Gfx_EnvColor(play->state.gfxCtx, this->lightColor.r, this->lightColor.g, this->lightColor.b,
                                this->lightColor.a));
        gSPSegment(
            POLY_OPA_DISP++, 0x0A,
            Gfx_EnvColor(play->state.gfxCtx, clothingColor->r, clothingColor->g, clothingColor->b, this->lightColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0B,
                   Gfx_EnvColor(play->state.gfxCtx, var_t0->r, var_t0->g, var_t0->b, this->lightColor.a));
        gSPSegment(POLY_OPA_DISP++, 0x0C, D_801AEFA0);

        POLY_OPA_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnPoComposer_OverrideLimbDraw, EnPoComposer_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    } else {
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        Gfx_SetupDL25_Xlu(play->state.gfxCtx);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_EnvColor(play->state.gfxCtx, this->lightColor.r, this->lightColor.g, this->lightColor.b,
                                this->lightColor.a));
        gSPSegment(
            POLY_XLU_DISP++, 0x0A,
            Gfx_EnvColor(play->state.gfxCtx, clothingColor->r, clothingColor->g, clothingColor->b, this->lightColor.a));
        gSPSegment(POLY_XLU_DISP++, 0x0B,
                   Gfx_EnvColor(play->state.gfxCtx, var_t0->r, var_t0->g, var_t0->b, this->lightColor.a));
        gSPSegment(POLY_XLU_DISP++, 0x0C, D_801AEF88);

        POLY_XLU_DISP =
            SkelAnime_DrawFlex(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                               EnPoComposer_OverrideLimbDraw, EnPoComposer_PostLimbDraw, &this->actor, POLY_XLU_DISP);
    }

    if (this->lightColor.a != 0) {
        // Draw lantern if visible

        if (this->lightColor.a == 255) {
            Scene_SetRenderModeXlu(play, 0, 1);
            dl = POLY_OPA_DISP;
        } else {
            Scene_SetRenderModeXlu(play, 1, 2);
            dl = POLY_XLU_DISP;
        }

        gDPPipeSync(&dl[0]);
        gDPSetEnvColor(&dl[1], this->envColor.r, this->envColor.g, this->envColor.b, this->lightColor.a);

        Matrix_Put(&this->lanternMtxF);
        gSPMatrix(&dl[2], Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        gSPDisplayList(&dl[3], object_po_composer_DL_006E08); // lantern base
        gSPDisplayList(&dl[4], object_po_composer_DL_006F38); // lantern enclosure

        gDPPipeSync(&dl[5]);
        gDPSetEnvColor(&dl[6], clothingColor->r, clothingColor->g, clothingColor->b, this->lightColor.a);
        gSPDisplayList(&dl[7], object_po_composer_DL_006EA8); // lantern top

        if (this->lightColor.a == 255) {
            POLY_OPA_DISP = &dl[8];
        } else {
            POLY_XLU_DISP = &dl[8];
        }
    }

    Matrix_Put(&play->billboardMtxF);
    Matrix_MultVecZ(15.0f, &sp88);
    lightPos = this->lanternCollider.elements[0].dim.worldSphere.center;
    lightPos.x += (s16)sp88.x;
    lightPos.y += (s16)sp88.y;
    lightPos.z += (s16)sp88.z;

    Lights_PointGlowSetInfo(&this->lightInfo, lightPos.x, lightPos.y, lightPos.z, this->envColor.r, this->envColor.g,
                            this->envColor.b, this->envColor.a * 0.78431374f);

    CLOSE_DISPS(play->state.gfxCtx);
}
