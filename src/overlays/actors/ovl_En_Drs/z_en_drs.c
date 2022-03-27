/*
 * File: z_en_drs.c
 * Overlay: ovl_En_Drs
 * Description: Anju's Wedding Dress Mannequin
 */

#include "z_en_drs.h"

#define FLAGS 0x00000000

#define THIS ((EnDrs*)thisx)

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDrs_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnDrs_Idle(EnDrs* this, GlobalContext* globalCtx);

const ActorInit En_Drs_InitVars = {
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

static AnimationInfoS sAnimations = { &gWeddingDressMannequinIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 };

void EnDrs_CollisionUpdate(EnDrs* this, GlobalContext* globalCtx) {
    Collider_UpdateCylinder(&this->actor, &this->collider);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnDrs_Setup(EnDrs* this, GlobalContext* globalCtx) {
    s32 pad[2];

    if ((this->moonMaskObjBankIndex >= 0) && SubS_IsObjectLoaded(this->moonMaskObjBankIndex, globalCtx)) {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
        SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gWeddingDressMannequinSkel, NULL, this->jointTable,
                           this->morphTable, WEDDING_DRESS_MANNEQUIN_LIMB_MAX);
        SubS_ChangeAnimationByInfoS(&this->skelAnime, &sAnimations, 0);
        Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
        CollisionCheck_SetInfo2(&this->actor.colChkInfo, DamageTable_Get(0x16), &sColChkInfoInit);
        Actor_SetScale(&this->actor, 0.01f);
        this->actor.draw = EnDrs_Draw;
        this->actionFunc = EnDrs_Idle;
    }
}

void EnDrs_Idle(EnDrs* this, GlobalContext* globalCtx) {
}

void EnDrs_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;

    this->moonMaskObjBankIndex = SubS_GetObjectIndex(OBJECT_MSMO, globalCtx);
    this->actionFunc = EnDrs_Setup;
}

void EnDrs_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnDrs_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;

    this->actionFunc(this, globalCtx);
    if (this->actor.draw != NULL) {
        SkelAnime_Update(&this->skelAnime);
        EnDrs_CollisionUpdate(this, globalCtx);
    }
}

void EnDrs_PostLimbDraw(GlobalContext* globalCtx2, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnDrs* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s8 temp = this->moonMaskObjBankIndex;
    s8 temp2 = this->actor.objBankIndex;

    // Anju removes the Moon Mask at the start of the Couple's Mask cutscene
    // after that it will no longer be rendered.
    if (!(gSaveContext.save.weekEventReg[87] & 2) && (limbIndex == WEDDING_DRESS_MANNEQUIN_LIMB_MASK)) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[temp].segment);
        gSPDisplayList(POLY_OPA_DISP++, &gMoonMaskDL);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[temp2].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
}

void EnDrs_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnDrs* this = THIS;

    func_8012C5B0(globalCtx->state.gfxCtx);
    SkelAnime_DrawFlexOpa(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          NULL, EnDrs_PostLimbDraw, &this->actor);
}
