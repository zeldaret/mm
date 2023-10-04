/*
 * File: z_en_drs.c
 * Overlay: ovl_En_Drs
 * Description: Anju's Wedding Dress Mannequin
 */

#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, PlayState* play);
void EnDrs_Destroy(Actor* thisx, PlayState* play);
void EnDrs_Update(Actor* thisx, PlayState* play);
void EnDrs_Draw(Actor* thisx, PlayState* play);

void EnDrs_Idle(EnDrs* this, PlayState* play);

ActorInit En_Drs_InitVars = {
    ACTOR_EN_DRS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DRS,
    sizeof(EnDrs),
    (ActorFunc)EnDrs_Init,
    (ActorFunc)EnDrs_Destroy,
    (ActorFunc)EnDrs_Update,
    (ActorFunc)NULL,
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
    { 16, 62, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

typedef enum {
    /* 0 */ WEDDING_DRESS_MANNEQUIN_ANIM_IDLE,
    /* 1 */ WEDDING_DRESS_MANNEQUIN_ANIM_MAX
} WeddingDressMannequinAnimation;

static AnimationInfoS sAnimationInfo[WEDDING_DRESS_MANNEQUIN_ANIM_MAX] = {
    { &gWeddingDressMannequinIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 }, // WEDDING_DRESS_MANNEQUIN_ANIM_IDLE
};

void EnDrs_CollisionUpdate(EnDrs* this, PlayState* play) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnDrs_Setup(EnDrs* this, PlayState* play) {
    s32 pad[2];

    if ((this->moonMaskObjectSlot > OBJECT_SLOT_NONE) && SubS_IsObjectLoaded(this->moonMaskObjectSlot, play)) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        SkelAnime_InitFlex(play, &this->skelAnime, &gWeddingDressMannequinSkel, NULL, this->jointTable,
                           this->morphTable, WEDDING_DRESS_MANNEQUIN_LIMB_MAX);
        SubS_ChangeAnimationByInfoS(&this->skelAnime, sAnimationInfo, WEDDING_DRESS_MANNEQUIN_ANIM_IDLE);
        Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = EnDrs_Draw;
        this->actionFunc = EnDrs_Idle;
    }
}

void EnDrs_Idle(EnDrs* this, PlayState* play) {
}

void EnDrs_Init(Actor* thisx, PlayState* play) {
    EnDrs* this = THIS;

    this->moonMaskObjectSlot = SubS_GetObjectSlot(OBJECT_MSMO, play);
    this->actionFunc = EnDrs_Setup;
}

void EnDrs_Destroy(Actor* thisx, PlayState* play) {
    EnDrs* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void EnDrs_Update(Actor* thisx, PlayState* play) {
    EnDrs* this = THIS;

    this->actionFunc(this, play);
    if (this->actor.draw != NULL) {
        SkelAnime_Update(&this->skelAnime);
        EnDrs_CollisionUpdate(this, play);
    }
}

void EnDrs_PostLimbDraw(PlayState* play2, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDrs* this = THIS;
    PlayState* play = play2;
    s8 temp = this->moonMaskObjectSlot;
    s8 temp2 = this->actor.objectSlot;

    // Anju removes the Moon Mask at the start of the Couple's Mask cutscene
    // after that it will no longer be rendered.
    if (!CHECK_WEEKEVENTREG(WEEKEVENTREG_87_02) && (limbIndex == WEDDING_DRESS_MANNEQUIN_LIMB_MASK)) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[temp].segment);
        gSPDisplayList(POLY_OPA_DISP++, &gMoonMaskDL);
        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.slots[temp2].segment);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}

void EnDrs_Draw(Actor* thisx, PlayState* play) {
    EnDrs* this = THIS;

    Gfx_SetupDL37_Opa(play->state.gfxCtx);
    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount, NULL,
                          EnDrs_PostLimbDraw, &this->actor);
}
