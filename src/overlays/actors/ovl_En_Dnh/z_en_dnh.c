/*
 * File: z_en_dnh.c
 * Overlay: ovl_En_Dnh
 * Description: Koume in boat house
 */

#include "z_en_dnh.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnDnh*)thisx)

void EnDnh_Init(Actor* thisx, PlayState* play);
void EnDnh_Destroy(Actor* thisx, PlayState* play);
void EnDnh_Update(Actor* thisx, PlayState* play);
void EnDnh_Draw(Actor* thisx, PlayState* play);

void func_80A50F38(EnDnh* this, PlayState* play);
void EnDnh_DoNothing(EnDnh* this, PlayState* play);

UNK_TYPE D_80A51250[] = {
    0x000C0800, 0x080E0862, 0x0C111101, 0x10040005, 0x0E08670C, 0x10001402, 0x007A0019, 0x1000300E, 0x08590C25,
    0x000D0018, 0x0F08630C, 0x12060043, 0x00001300, 0x430C0700, 0x000E088D, 0x0C190007, 0x0F088D0C, 0x19000012,
    0x11191009, 0x00001000, 0x1A100016, 0x0E085A11, 0x1A100C0F, 0x085B0C0F, 0x085C0C05, 0x00060024, 0x00060E08,
    0x5B19FFEE, 0x300F085E, 0x0C08000A, 0x00050F08, 0x750C1014, 0xFFF60F08, 0x600C1211, 0x19100900, 0x0010310F,
    0x085F0C10, 0x00192000, 0x49001A10, 0x003D0E08, 0x68111A10, 0x0C0F0869, 0x0C0F086A, 0x0C0F086B, 0x0C0F086C,
    0x0C050000, 0x00190000, 0x300E086E, 0x1119201C, 0x03201D03, 0x401D0380, 0x1D04010C, 0x12090000, 0x10310E08,
    0x6D0C100E, 0x08700C19, 0xFFCB0019, 0x2000070E, 0x08710C19, 0xFFBB0E08, 0x720C0F08, 0x730C0500, 0x00001700,
    0x0008000A, 0x0006320F, 0x08750C10, 0x3014FFF6, 0x001A4000, 0x0919FFA8, 0x310E0874, 0x0C100E08, 0x76111920,
    0x1C03201D, 0x03401D03, 0x801D0401, 0x0C120900, 0x00100000,
};

UNK_TYPE D_80A51384[] = {
    0x0E08610C,
    0x16100000,
};

UNK_TYPE D_80A5138C[] = {
    0x1B034000, 0x67001A40, 0x003A1B03, 0x80001A0E, 0x087C0C00, 0x5B20000A, 0x0F087E0C, 0x115B2019,
    0x004E0F08, 0x7B0C1900, 0x470E087D, 0x0C120600, 0x0C000013, 0x000C0C07, 0x00000E08, 0x7E0C111A,
    0x4019002C, 0x1B038000, 0x0B0E087A, 0x0C0F087B, 0x0C19001C, 0x0E08780C, 0x12060005, 0x00001300,
    0x050C0700, 0x000E0879, 0x0C190004, 0x0E08770C, 0x1D03201D, 0x03401D03, 0x801D0401, 0x16100000,
};

ActorInit En_Dnh_InitVars = {
    ACTOR_EN_DNH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TRO,
    sizeof(EnDnh),
    (ActorFunc)EnDnh_Init,
    (ActorFunc)EnDnh_Destroy,
    (ActorFunc)EnDnh_Update,
    (ActorFunc)EnDnh_Draw,
};

typedef enum {
    /* 0 */ ENDNH_ANIM_HEAD_MOVING,
    /* 1 */ ENDNH_ANIM_MAX
} EnDnhAnimation;

static AnimationInfoS sAnimationInfo[ENDNH_ANIM_MAX] = {
    { &gKoumeKioskHeadMoving, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // ENDNH_ANIM_HEAD_MOVING
};

static TexturePtr sEyeTextures[] = {
    gKoumeKioskEyeOpenTex,
    gKoumeKioskEyeHalfTex,
    gKoumeKioskEyeClosedTex,
    gKoumeKioskEyeHalfTex,
};

s32 func_80A50D40(Actor* actor, PlayState* play) {
    func_800B7298(play, actor, PLAYER_CSMODE_WAIT);
    if (CHECK_EVENTINF(EVENTINF_35)) {
        play->nextEntrance = ENTRANCE(SOUTHERN_SWAMP_CLEARED, 6);
    } else {
        play->nextEntrance = ENTRANCE(SOUTHERN_SWAMP_POISONED, 6);
    }
    gSaveContext.nextCutsceneIndex = 0;
    play->transitionTrigger = TRANS_TRIGGER_START;
    play->transitionType = TRANS_TYPE_FADE_WHITE;
    gSaveContext.nextTransitionType = TRANS_TYPE_FADE_WHITE_SLOW;
    CLEAR_WEEKEVENTREG(WEEKEVENTREG_90_40);
    CLEAR_EVENTINF(EVENTINF_50);
    return 1;
}

void* func_80A50DF8(EnDnh* this, PlayState* play) {
    switch (this->unk198) {
        case 1:
            return D_80A51384;

        case 2:
            return D_80A5138C;

        default:
            return D_80A51250;
    }
}

s32 func_80A50E40(EnDnh* this, PlayState* play) {
    if (((this->unk18C & SUBS_OFFER_MODE_MASK) == SUBS_OFFER_MODE_NONE) ||
        !Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        return 0;
    }
    SubS_SetOfferMode(&this->unk18C, SUBS_OFFER_MODE_NONE, SUBS_OFFER_MODE_MASK);
    this->msgEventScript = func_80A50DF8(this, play);
    this->actionFunc = func_80A50F38;
    return 1;
}

s32 func_80A50EC0(EnDnh* this) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeTexIndex++;
        if (this->eyeTexIndex >= ARRAY_COUNT(sEyeTextures)) {
            this->blinkTimer = Rand_S16Offset(30, 30);
            this->eyeTexIndex = 0;
        }
    }
}

void func_80A50F38(EnDnh* this, PlayState* play) {
    if (func_8010BF58(&this->actor, play, this->msgEventScript, this->msgEventCallback, &this->unk194)) {
        SubS_SetOfferMode(&this->unk18C, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk194 = 0;
        this->unk198 = 0;
        this->actionFunc = EnDnh_DoNothing;
    }
}

void EnDnh_DoNothing(EnDnh* this, PlayState* play) {
}

void EnDnh_Init(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_Init(play, &this->skelAnime, &gKoumeKioskSkeleton, NULL, this->jointTable, this->morphTable,
                   KOUME_KIOSK_LIMB_MAX);
    SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, ENDNH_ANIM_HEAD_MOVING);
    this->actor.shape.yOffset = 1100.0f;

    if (gSaveContext.save.entrance != ENTRANCE(TOURIST_INFORMATION, 1)) {
        SubS_SetOfferMode(&this->unk18C, SUBS_OFFER_MODE_ONSCREEN, SUBS_OFFER_MODE_MASK);
        this->unk198 = 0;
    } else {
        SubS_SetOfferMode(&this->unk18C, SUBS_OFFER_MODE_AUTO, SUBS_OFFER_MODE_MASK);
        this->unk198 = CHECK_EVENTINF(EVENTINF_35) ? 2 : 1;
    }

    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_SAVED_KOUME)) {
        this->actor.draw = NULL;
    }

    this->msgEventCallback = func_80A50D40;
    this->unk194 = 0;
    this->actionFunc = EnDnh_DoNothing;
}

void EnDnh_Destroy(Actor* thisx, PlayState* play) {
}

void EnDnh_Update(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    func_80A50E40(this, play);
    this->actionFunc(this, play);
    func_80A50EC0(this);
    SkelAnime_Update(&this->skelAnime);
    SubS_Offer(&this->actor, play, 60.0f, 30.0f, PLAYER_IA_NONE, this->unk18C & SUBS_OFFER_MODE_MASK);
    Actor_SetFocus(&this->actor, 26.0f);
}

s32 EnDnh_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnDnh* this = THIS;

    if (limbIndex == KOUME_KIOSK_LIMB_HEAD) {
        Matrix_Translate(0.0f, this->actor.shape.yOffset, 0.0f, MTXMODE_APPLY);
    }
    return false;
}

void EnDnh_Draw(Actor* thisx, PlayState* play) {
    EnDnh* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(sEyeTextures[this->eyeTexIndex]));
    SkelAnime_DrawOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, EnDnh_OverrideLimbDraw, NULL,
                      &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}
