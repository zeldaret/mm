/*
 * File: z_en_shn.c
 * Overlay: ovl_En_Shn
 * Description: Swamp Tourist Center Guide
 * Shashin(Shn) ~ Photo
 */

#include "z_en_shn.h"
#include "z64snap.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnShn*)thisx)

void EnShn_Init(Actor* thisx, PlayState* play);
void EnShn_Destroy(Actor* thisx, PlayState* play);
void EnShn_Update(Actor* thisx, PlayState* play);
void EnShn_Draw(Actor* thisx, PlayState* play);

void func_80AE6A64(EnShn* this, PlayState* play);

// Could be something related to text/dialogue?
static UNK_TYPE D_80AE6F00[] = {
    0x00170800, 0x0B0E09C4, 0x0C0F09C5, 0x0C111708, 0x03018C04, 0x018E1901, 0x860F00FF, 0x1E001300, 0x00011501,
    0x47280012, 0x28001928, 0x002D2800, 0x5D280093, 0x28003319, 0x00472C09, 0xE70C2F00, 0x000C1210, 0x2C09CB0C,
    0x2F00000C, 0x0F09CC0C, 0x0F09CD0C, 0x0500A500, 0xCB00CB2C, 0x09D10C2F, 0x00000C0F, 0x09D20C19, 0xFFE62C09,
    0xD30C2F00, 0x000C0F09, 0xD40C0F09, 0xD50C0500, 0x9200B200, 0xB22C09D9, 0x0C2F0000, 0x0C0F09DA, 0x0C102C09,
    0xE80C2F00, 0x000C0F09, 0xE90C0F09, 0xEA0C0057, 0x04001712, 0x06000C00, 0x0013000C, 0x0C115704, 0x0700000E,
    0x09EB0C12, 0x16101206, 0x00060000, 0x1300060C, 0x07FFEC2C, 0x09EC0C2F, 0x00000C0F, 0x09ED0C0F, 0x09EE0C00,
    0x57040017, 0x1206000C, 0x00001300, 0x0C0C1157, 0x04070000, 0x0E09EF0C, 0x12161012, 0x06000600, 0x00130006,
    0x0C07FFEC, 0x12060004, 0x00001300, 0x040C0700, 0x000E09CE, 0x0C161012, 0x06000200, 0x00130002, 0x0C070000,
    0x0E09D80C, 0x16100C0F, 0x09CF0C1C, 0x05011509, 0x0000100E, 0x09D60C19, 0xFFF10037, 0x40001C2C, 0x09DB0C2F,
    0x00000C0F, 0x09DC0C0F, 0x09DD0C0F, 0x09DE0C0F, 0x09DF0C11, 0x3740102C, 0x09E00C2F, 0x00000C0F, 0x09E10C0F,
    0x09E20C10, 0x00374000, 0x180E09DB, 0x0C0F09DC, 0x0C0F09DD, 0x0C0F09DE, 0x0C0F09DF, 0x0C113740, 0x100E09E0,
    0x0C0F09E1, 0x0C0F09E2, 0x0C100E09, 0xC90C0F09, 0xCA0C100E, 0x09C60C10, 0x001402FF, 0xED0E09C8, 0x0C19FE69
};

static UNK_TYPE D_80AE70B0[] = { 0x0E09D00C, 0x16100000 };

static UNK_TYPE D_80AE70B8[] = {
    0x28001228, 0x00152800, 0x28280055, 0x28008A28, 0x002D1900, 0x402C09E7, 0x0C12102C, 0x09CB2F00, 0x000C0F09,
    0xCC0C0F09, 0xCD0C0500, 0xA000C600, 0xC62C09D1, 0x2F00000C, 0x0F09D20C, 0x19FFE72C, 0x09D32F00, 0x000C0F09,
    0xD40C0F09, 0xD50C0500, 0x8F00AF00, 0xAF2C09D9, 0x2F00000C, 0x0F09DA0C, 0x102C09E8, 0x2F00000C, 0x0F09E90C,
    0x0F09EA0C, 0x00570400, 0x17120600, 0x0C000013, 0x000C0C11, 0x57040700, 0x000E09EB, 0x0C121610, 0x12060006,
    0x00001300, 0x060C07FF, 0xEC2C09EC, 0x2F00000C, 0x0F09ED0C, 0x0F09EE0C, 0x00570800, 0x17120600, 0x0C000013,
    0x000C0C11, 0x57080700, 0x000E09EF, 0x0C121610, 0x12060006, 0x00001300, 0x060C07FF, 0xEC120600, 0x04000013,
    0x00040C07, 0x00000E09, 0xCE0C1610, 0x12060002, 0x00001300, 0x020C0700, 0x000E09D8, 0x0C16100C, 0x0F09CF0C,
    0x1C050115, 0x09000010, 0x0E09D60C, 0x19FFF100,
};

static UNK_TYPE D_80AE71C4[] = { 0x00374000, 0x1C2C09DB, 0x0C2F0000, 0x0C0F09DC, 0x0C0F09DD, 0x0C0F09DE, 0x0C0F09DF,
                                 0x0C113740, 0x102C09E0, 0x0C2F0000, 0x0C0F09E1, 0x0C0F09E2, 0x0C100000 };

ActorInit En_Shn_InitVars = {
    /**/ ACTOR_EN_SHN,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_SHN,
    /**/ sizeof(EnShn),
    /**/ EnShn_Init,
    /**/ EnShn_Destroy,
    /**/ EnShn_Update,
    /**/ EnShn_Draw,
};

void func_80AE6130(EnShn* this) {
    this->skelAnime.playSpeed = this->playSpeed;
    SkelAnime_Update(&this->skelAnime);
}

s32 func_80AE615C(EnShn* this, s32 animIndex) {
    static AnimationInfoS sAnimationInfo[] = {
        { &gBurlyGuyHandsOnTableAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
        { &gBurlyGuyHandsOnTableAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
        { &gBurlyGuyChinScratchAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
        { &gBurlyGuyChinScratchAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    };
    s32 phi_v0 = 0;
    s32 phi_v1 = 0;

    if (animIndex != this->unk_2E8) {
        phi_v0 = 1;
    }
    if (phi_v0 != 0) {
        this->unk_2E8 = animIndex;
        phi_v1 = SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, animIndex);
        this->playSpeed = this->skelAnime.playSpeed;
    }
    return phi_v1;
}

s32 EnShn_IsFacingPlayer(EnShn* this) {
    s16 phi_v1;
    f32 range;

    if (this->unk_2C8 == 0) {
        phi_v1 = 0;
    } else {
        this->unk_2C8--;
        phi_v1 = this->unk_2C8;
    }
    if (phi_v1 == 0) {
        this->unk_2EC ^= 1;
        this->unk_2C8 = Rand_S16Offset(30, 30);
    }
    if (this->unk_2EC != 0) {
        range = 120.0f;
    } else {
        range = 80.0f;
    }
    return Actor_IsFacingAndNearPlayer(&this->actor, range, 0x238C);
}

Player* EnShn_GetPlayer(EnShn* this, PlayState* play) {
    return GET_PLAYER(play);
}

void func_80AE626C(EnShn* this) {
    s32 topPad;
    Vec3f playerPos;
    Vec3f shnPos;
    s32 bottomPad;

    Math_Vec3f_Copy(&playerPos, &this->shnPlayerRef->actor.world.pos);
    Math_Vec3f_Copy(&shnPos, &this->actor.world.pos);
    Math_ApproachS(&this->unk_2BC, (Math_Vec3f_Yaw(&shnPos, &playerPos) - this->actor.shape.rot.y), 4, 0x2AA8);
    this->unk_2BC = CLAMP(this->unk_2BC, -0x1FFE, 0x1FFE);
    Math_Vec3f_Copy(&shnPos, &this->actor.focus.pos);
    if (this->shnPlayerRef->actor.id == ACTOR_PLAYER) {
        playerPos.y = this->shnPlayerRef->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
    } else {
        Math_Vec3f_Copy(&playerPos, &this->shnPlayerRef->actor.focus.pos);
    }
    Math_ApproachS(&this->unk_2BA, Math_Vec3f_Pitch(&shnPos, &playerPos), 4, 0x2AA8);
    this->unk_2BA = CLAMP(this->unk_2BA, -0x1554, 0x1554);
}

void func_80AE63A8(EnShn* this, PlayState* play) {
    s16 phi_v1;
    s16 phi_v1_2;

    this->shnPlayerRef = EnShn_GetPlayer(this, play);
    if ((this->unk_1D8 & 8) && (this->shnPlayerRef != NULL)) {
        if (this->unk_2CA == 0) {
            phi_v1 = 0;
        } else {
            this->unk_2CA--;
            phi_v1 = this->unk_2CA;
        }
        if (phi_v1 == 0) {
            func_80AE626C(this);
            this->unk_1D8 &= ~0x20;
            this->unk_1D8 |= 0x10;
            return;
        }
    }
    if (this->unk_1D8 & 0x10) {
        this->unk_1D8 &= ~0x10;
        this->unk_2BA = 0;
        this->unk_2BC = 0;
        this->unk_2CA = 20;
        return;
    }
    if (this->unk_2CA == 0) {
        phi_v1_2 = 0;
    } else {
        this->unk_2CA--;
        phi_v1_2 = this->unk_2CA;
    }
    if (phi_v1_2 == 0) {
        this->unk_1D8 |= 0x20;
    }
}

void func_80AE6488(EnShn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 talkState = Message_GetState(&play->msgCtx);
    f32 phi_f0_2;
    f32 phi_f0;

    this->unk_2D4 += (this->unk_2D0 != 0.0f) ? 40.0f : -40.0f;
    this->unk_2D4 = CLAMP(this->unk_2D4, 0.0f, 80.0f);
    Matrix_Translate(this->unk_2D4, 0.0f, 0.0f, MTXMODE_APPLY);
    if ((&this->actor == player->talkActor) &&
        ((play->msgCtx.currentTextId < 0xFF) || (play->msgCtx.currentTextId >= 0x201)) && (talkState == TEXT_STATE_3) &&
        (this->prevTalkState == TEXT_STATE_3)) {
        if (play->state.frames % 2 == 0) {
            if (this->unk_2D0 != 0.0f) {
                this->unk_2D0 = 0.0f;
            } else {
                this->unk_2D0 = 1.0f;
            }
        }
    } else {
        this->unk_2D0 = 0.0f;
    }
    this->prevTalkState = talkState;
}

s32 func_80AE65F4(EnShn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u16 temp = play->msgCtx.currentTextId;

    if (player->stateFlags1 & PLAYER_STATE1_40) {
        if (this->unk_1DA != temp) {
            if ((this->unk_1D8 & 0x80) || (this->unk_1D8 & 0x100)) {
                this->unk_1D8 |= 8;
                func_80AE615C(this, 1);
            }
            if (temp == 0x9C5) {
                if (1) {}
                this->unk_1D8 |= 8;
                func_80AE615C(this, 1);
            }
        }
        this->unk_1DA = temp;
        this->unk_1D8 |= 0x40;
    } else if (this->unk_1D8 & 0x40) {
        if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_23_08)) {
            func_80AE615C(this, 3);
        }
        this->unk_1DA = 0;
        this->unk_1D8 &= ~0x40;
    }
    return false;
}

s32 func_80AE6704(Actor* thisx, PlayState* play) {
    static s32 sPictographFlags[] = {
        PICTO_VALID_0,      PICTO_VALID_MONKEY,    PICTO_VALID_BIG_OCTO,
        PICTO_VALID_TINGLE, PICTO_VALID_DEKU_KING, PICTO_VALID_IN_SWAMP,
    };
    EnShn* this = THIS;
    s32 ret = 0;

    switch (this->unk_2C6) {
        case 0:
            if (!CHECK_QUEST_ITEM(QUEST_PICTOGRAPH)) {
                this->unk_2C6 = 6;
                ret = 1;
            } else {
                this->unk_2C6++;
            }
            break;

        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            if (Snap_CheckFlag(sPictographFlags[this->unk_2C6])) {
                this->unk_2C6 = 6;
                ret = 1;
                REMOVE_QUEST_ITEM(QUEST_PICTOGRAPH);
            } else {
                this->unk_2C6++;
            }
            break;

        case 6:
            CLEAR_WEEKEVENTREG(WEEKEVENTREG_90_40);
            func_800B7298(play, &this->actor, PLAYER_CSACTION_WAIT);
            play->nextEntrance = ENTRANCE(SOUTHERN_SWAMP_POISONED, 6);
            gSaveContext.nextCutsceneIndex = 0;
            play->transitionTrigger = TRANS_TRIGGER_START;
            play->transitionType = TRANS_TYPE_FADE_WHITE;
            gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE_SLOW;
            this->unk_2C6++;
            break;
    }
    return ret;
}

UNK_TYPE* func_80AE6880(EnShn* this, PlayState* play) {
    if (this->unk_2BE != 0) {
        return D_80AE70B0;
    }
    if (this->unk_1D8 & 0x80) {
        this->unk_2D8 = func_80AE6704;
        return D_80AE70B8;
    }
    if (this->unk_1D8 & 0x100) {
        return D_80AE71C4;
    }
    this->unk_2D8 = func_80AE6704;
    return D_80AE6F00;
}

s32 func_80AE68F0(EnShn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s32 ret = false;

    if (((this->unk_1D8 & SUBS_OFFER_MODE_MASK) != SUBS_OFFER_MODE_NONE) &&
        Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        this->unk_1D8 &= ~0x180;
        if (player->exchangeItemAction == PLAYER_IA_PICTOGRAPH_BOX) {
            this->unk_1D8 |= 0x80;
            this->unk_2E4 = player->exchangeItemAction;
        } else if (player->exchangeItemAction != PLAYER_IA_NONE) {
            this->unk_1D8 |= 0x100;
            this->unk_2E4 = player->exchangeItemAction;
        }
        SubS_SetOfferMode(&this->unk_1D8, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
        this->unk_1DC = func_80AE6880(this, play);
        this->unk_2C6 = 0;
        if (CHECK_WEEKEVENTREG(WEEKEVENTREG_23_08)) {
            this->unk_1D8 |= 8;
        }
        this->actionFunc = func_80AE6A64;
        ret = true;
    }
    return ret;
}

void func_80AE69E8(EnShn* this, PlayState* play) {
    Math_ApproachS(&this->actor.shape.rot.y, this->actor.world.rot.y, 3, 0x2AA8);
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_23_08) && EnShn_IsFacingPlayer(this)) {
        this->unk_1D8 |= 8;
    } else {
        this->unk_1D8 &= ~0x8;
    }
}

void func_80AE6A64(EnShn* this, PlayState* play) {
    s16 yawBetweenActors;
    Vec3f playerPos;
    Vec3f shnPos;

    if (func_8010BF58(&this->actor, play, this->unk_1DC, this->unk_2D8, &this->unk_1E0)) {
        SubS_SetOfferMode(&this->unk_1D8, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_1D8 &= ~8;
        this->unk_1D8 |= 0x20;
        this->unk_2CA = 20;
        this->unk_1E0 = 0;
        this->unk_2BE = 0;
        this->actionFunc = func_80AE69E8;
    } else if (this->shnPlayerRef != 0) {
        Math_Vec3f_Copy(&playerPos, &this->shnPlayerRef->actor.world.pos);
        Math_Vec3f_Copy(&shnPos, &this->actor.world.pos);
        yawBetweenActors = Math_Vec3f_Yaw(&shnPos, &playerPos);
        Math_ApproachS(&this->actor.shape.rot.y, yawBetweenActors, 4, 0x2AA8);
    }
}

void EnShn_Init(Actor* thisx, PlayState* play) {
    EnShn* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gBurlyGuySkel, NULL, this->jointTable, this->morphTable,
                       BURLY_GUY_LIMB_MAX);
    this->unk_2E8 = -1;
    if (CHECK_WEEKEVENTREG(WEEKEVENTREG_23_08)) {
        func_80AE615C(this, 0);
    } else {
        func_80AE615C(this, 2);
    }
    this->actor.targetMode = TARGET_MODE_6;
    Actor_SetScale(&this->actor, 0.01f);
    this->unk_2E0 = 0;
    this->unk_2D8 = 0;
    this->unk_1D8 = 0;
    if (gSaveContext.save.entrance != ENTRANCE(TOURIST_INFORMATION, 2)) {
        SubS_SetOfferMode(&this->unk_1D8, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk_2BE = 0;
    } else {
        SubS_SetOfferMode(&this->unk_1D8, SUBS_OFFER_MODE_AUTO, SUBS_OFFER_MODE_MASK);
        this->unk_2BE = 1;
    }
    this->actionFunc = func_80AE69E8;
}

void EnShn_Destroy(Actor* thisx, PlayState* play) {
}

void EnShn_Update(Actor* thisx, PlayState* play) {
    EnShn* this = THIS;

    func_80AE68F0(this, play);
    this->actionFunc(this, play);
    func_80AE65F4(this, play);
    func_80AE6130(this);
    func_80AE63A8(this, play);
    this->unk_2E0 = 0;
    SubS_Offer(&this->actor, play, 120.0f, 40.0f, PLAYER_IA_NONE, this->unk_1D8 & SUBS_OFFER_MODE_MASK);
}

s32 EnShn_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnShn* this = THIS;

    if (limbIndex == BURLY_GUY_LIMB_HEAD) {
        func_80AE6488(this, play);
        *dList = gSwampGuideHeadDL;
    }
    return false;
}

Vec3f D_80AE7270 = { 1200.0f, 0.0f, 0.0f };
void EnShn_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    if (limbIndex == BURLY_GUY_LIMB_HEAD) {
        Matrix_MultVec3f(&D_80AE7270, &thisx->focus.pos);
        Math_Vec3s_Copy(&thisx->focus.rot, &thisx->world.rot);
    }
}

void EnShn_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
    EnShn* this = THIS;
    s32 stepRot;
    s32 overrideRot;

    if (!(this->unk_1D8 & 0x20)) {
        if (this->unk_1D8 & 0x10) {
            overrideRot = true;
        } else {
            overrideRot = false;
        }
        stepRot = true;
    } else {
        overrideRot = false;
        stepRot = false;
    }

    if (limbIndex == BURLY_GUY_LIMB_HEAD) {
        SubS_UpdateLimb(this->unk_2BA + 0x4000, this->unk_2BC + this->actor.shape.rot.y + 0x4000, &this->unk_1E8,
                        &this->unk_1F4, stepRot, overrideRot);
        Matrix_Pop();
        Matrix_Translate(this->unk_1E8.x, this->unk_1E8.y, this->unk_1E8.z, MTXMODE_NEW);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Matrix_RotateYS(this->unk_1F4.y, MTXMODE_APPLY);
        Matrix_RotateXS(this->unk_1F4.x, MTXMODE_APPLY);
        Matrix_RotateZS(this->unk_1F4.z, MTXMODE_APPLY);
        Matrix_Push();
    }
}

void EnShn_Draw(Actor* thisx, PlayState* play) {
    EnShn* this = THIS;

    Gfx_SetupDL37_Opa(play->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable,
                                   this->skelAnime.dListCount, EnShn_OverrideLimbDraw, EnShn_PostLimbDraw,
                                   EnShn_TransformLimbDraw, &this->actor);
}
