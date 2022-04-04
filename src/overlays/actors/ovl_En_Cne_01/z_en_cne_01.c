/*
 * File: z_en_cne_01.c
 * Overlay: ovl_En_Cne_01
 * Description: Unused Market NPC
 */

#include "z_en_cne_01.h"
#include "objects/object_cne/object_cne.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnCne01*)thisx)

void EnCne01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCne01_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnCne01_Walk(EnHy* this, GlobalContext* globalCtx);
void EnCne01_FaceForward(EnHy* this, GlobalContext* globalCtx);
void EnCne01_Talk(EnHy* this, GlobalContext* globalCtx);

const ActorInit En_Cne_01_InitVars = {
    ACTOR_EN_CNE_01,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnCne01),
    (ActorFunc)EnCne01_Init,
    (ActorFunc)EnCne01_Destroy,
    (ActorFunc)EnCne01_Update,
    (ActorFunc)EnCne01_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK1,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 64, 0, { 0, 0, 0 } },
};

static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0),
    /* Deku Stick     */ DMG_ENTRY(0, 0),
    /* Horse trample  */ DMG_ENTRY(0, 0),
    /* Explosives     */ DMG_ENTRY(0, 0),
    /* Zora boomerang */ DMG_ENTRY(0, 0),
    /* Normal arrow   */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0),
    /* Hookshot       */ DMG_ENTRY(0, 0),
    /* Goron punch    */ DMG_ENTRY(0, 0),
    /* Sword          */ DMG_ENTRY(0, 0),
    /* Goron pound    */ DMG_ENTRY(0, 0),
    /* Fire arrow     */ DMG_ENTRY(0, 0),
    /* Ice arrow      */ DMG_ENTRY(0, 0),
    /* Light arrow    */ DMG_ENTRY(0, 0),
    /* Goron spikes   */ DMG_ENTRY(0, 0),
    /* Deku spin      */ DMG_ENTRY(0, 0),
    /* Deku bubble    */ DMG_ENTRY(0, 0),
    /* Deku launch    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0),
    /* Zora barrier   */ DMG_ENTRY(0, 0),
    /* Normal shield  */ DMG_ENTRY(0, 0),
    /* Light ray      */ DMG_ENTRY(0, 0),
    /* Thrown object  */ DMG_ENTRY(0, 0),
    /* Zora punch     */ DMG_ENTRY(0, 0),
    /* Spin attack    */ DMG_ENTRY(0, 0),
    /* Sword beam     */ DMG_ENTRY(0, 0),
    /* Normal Roll    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0),
    /* Unblockable    */ DMG_ENTRY(0, 0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0),
    /* Powder Keg     */ DMG_ENTRY(0, 0),
};

u16 D_809CBF58[] = { 4000, 4, 1, 3, 6000, 4, 1, 6, 4000, 4, 1, 3, 6000, 4, 1, 6 };

void EnCne01_UpdateModel(EnCne01* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f focus;

    EnHy_UpdateSkelAnime(&this->enHy, globalCtx);
    if (SubS_AngleDiffLessEqual(this->enHy.actor.shape.rot.y, 0x36B0, this->enHy.actor.yawTowardsPlayer)) {
        focus.x = player->actor.world.pos.x;
        focus.y = player->bodyPartsPos[7].y + 3.0f;
        focus.z = player->actor.world.pos.z;
        func_8013D2E0(&focus, &this->enHy.actor.focus.pos, &this->enHy.actor.shape.rot, &this->enHy.focusTarget,
                      &this->enHy.headRot, &this->enHy.torsoRot, D_809CBF58);
    } else {
        Math_SmoothStepToS(&this->enHy.focusTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.focusTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.y, 0, 4, 0x3E8, 1);
    }
    SubS_FillLimbRotTables(globalCtx, this->enHy.limbRotTableY, this->enHy.limbRotTableZ,
                           ARRAY_COUNT(this->enHy.limbRotTableY));
    EnHy_UpdateCollider(&this->enHy, globalCtx);
}

s32 EnCne01_TestIsTalking(EnCne01* this, GlobalContext* globalCtx) {
    s32 isTalking = false;

    if (Actor_ProcessTalkRequest(&this->enHy.actor, &globalCtx->state)) {
        isTalking = true;
        this->enHy.textId = 0x10B9; // Invalid textId, produces empty textbox
        this->enHy.tmpFocusTarget = this->enHy.focusTarget;
        this->enHy.tmpHeadRot = this->enHy.headRot;
        this->enHy.tmpTorsoRot = this->enHy.torsoRot;
        this->enHy.tmpActionFunc = this->enHy.actionFunc;
        this->enHy.actionFunc = EnCne01_Talk;
    }
    return isTalking;
}

s32 func_809CB4A0(EnCne01* this, GlobalContext* globalCtx) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(globalCtx, &this->enHy.actor, &x, &y);
    //! @bug: Both x and y conditionals are always true, || should be an &&
    if (!this->enHy.waitingOnInit && ((x >= 0) || (x < SCREEN_WIDTH)) && ((y >= 0) || (y < SCREEN_HEIGHT))) {
        func_800B85E0(&this->enHy.actor, globalCtx, 30.0f, EXCH_ITEM_2E);
    }
    return true;
}

void EnCne01_FinishInit(EnHy* this, GlobalContext* globalCtx) {
    if (EnHy_Init(this, globalCtx, &gCneSkel, ENHY_ANIMATION_OS_ANIME_11)) {
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.draw = EnCne01_Draw;
        this->waitingOnInit = false;
        if (ENCNE01_GET_PATH(&this->actor) == ENCNE01_NO_PATH) {
            this->actionFunc = EnCne01_FaceForward;
        } else {
            this->actionFunc = EnCne01_Walk;
        }
    }
}

void EnCne01_Walk(EnHy* this, GlobalContext* globalCtx) {
    if (EnHy_MoveForwards(this, 1.0f)) {
        this->curPoint = 0;
    }
}

void EnCne01_FaceForward(EnHy* this, GlobalContext* globalCtx) {
    this->actor.shape.rot = this->actor.world.rot;
}

void EnCne01_Talk(EnHy* this, GlobalContext* globalCtx) {
    s16 yaw;
    u8 talkState;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 1);
    talkState = Message_GetState(&globalCtx->msgCtx);
    this->inMsgState3 = (talkState == 3) ? true : false;

    switch (talkState) {
        case 0:
            yaw = ABS_ALT(this->actor.shape.rot.y - this->actor.yawTowardsPlayer);
            if (yaw < 0x64) {
                Message_StartTextbox(globalCtx, this->textId, NULL);
            }
            break;
        case 2:
            this->actor.textId = 0;
            this->focusTarget = this->tmpFocusTarget;
            this->headRot = this->tmpHeadRot;
            this->torsoRot = this->tmpTorsoRot;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actionFunc = this->tmpActionFunc;
            this->tmpActionFunc = NULL;
            break;
    }
}

void EnCne01_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnCne01* this = THIS;

    this->enHy.animObjIndex = SubS_GetObjectIndex(OBJECT_OS_ANIME, globalCtx);
    this->enHy.headObjIndex = SubS_GetObjectIndex(OBJECT_CNE, globalCtx);
    this->enHy.skelUpperObjIndex = SubS_GetObjectIndex(OBJECT_CNE, globalCtx);
    this->enHy.skelLowerObjIndex = SubS_GetObjectIndex(OBJECT_CNE, globalCtx);

    if ((this->enHy.animObjIndex < 0) || (this->enHy.headObjIndex < 0) || (this->enHy.skelUpperObjIndex < 0) ||
        (this->enHy.skelLowerObjIndex < 0)) {
        Actor_MarkForDeath(&this->enHy.actor);
    }
    this->enHy.actor.draw = NULL;
    Collider_InitCylinder(globalCtx, &this->enHy.collider);
    Collider_SetCylinder(globalCtx, &this->enHy.collider, &this->enHy.actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->enHy.actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->enHy.actor.flags &= ~ACTOR_FLAG_1;
    this->enHy.path = SubS_GetPathByIndex(globalCtx, ENCNE01_GET_PATH(&this->enHy.actor), ENCNE01_NO_PATH);
    this->enHy.waitingOnInit = true;
    Actor_SetScale(&this->enHy.actor, 0.01f);
    this->enHy.actionFunc = EnCne01_FinishInit;
}

void EnCne01_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnCne01* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->enHy.collider);
}

void EnCne01_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnCne01* this = THIS;

    EnCne01_TestIsTalking(this, globalCtx);
    this->enHy.actionFunc(&this->enHy, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->enHy.actor, 0.0f, 0.0f, 0.0f, 4);
    EnCne01_UpdateModel(this, globalCtx);
    func_809CB4A0(this, globalCtx);
}

s32 EnCne01_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                             Actor* thisx) {
    EnCne01* this = THIS;
    s8 bodyPart;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    bodyPart = gEnHyBodyParts[limbIndex];
    if (bodyPart >= 0) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->enHy.bodyPartsPos[bodyPart]);
    }

    if (limbIndex == CNE_LIMB_HEAD) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->enHy.headObjIndex].segment);
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.headObjIndex].segment);
        *dList = gCneHeadBrownHairDL;
        gSegments[6] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.skelLowerObjIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }
    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->enHy.headRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->enHy.headRot.x, MTXMODE_APPLY);
        Matrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == CNE_LIMB_TORSO) {
        Matrix_InsertXRotation_s(-this->enHy.torsoRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->enHy.torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_HEAD) && this->enHy.inMsgState3 && ((globalCtx->state.frames % 2) == 0)) {
        Matrix_InsertTranslation(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_TORSO) || (limbIndex == CNE_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == CNE_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)(Math_SinS(this->enHy.limbRotTableY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->enHy.limbRotTableZ[limbIndex]) * 200.0f);
    }

    return false;
}

void EnCne01_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCne01* this = THIS;
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == CNE_LIMB_RIGHT_FOOT) {
        OPEN_DISPS(globalCtx->state.gfxCtx);
        gSPSegment(POLY_OPA_DISP++, 0x06, globalCtx->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        gSegments[0x06] = PHYSICAL_TO_VIRTUAL(globalCtx->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        CLOSE_DISPS(globalCtx->state.gfxCtx);
    }

    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->enHy.actor.focus.pos);
    }
}

void EnCne01_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnCne01_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnCne01* this = THIS;
    s32 i;
    u8* shadowTex = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(u8[64][64]));
    u8* shadowTexIter;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(globalCtx->state.gfxCtx, 160, 180, 255, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(globalCtx->state.gfxCtx, 160, 180, 255, 0));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(globalCtx->state.gfxCtx, 160, 180, 255, 0));
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->enHy.skelAnime.skeleton, this->enHy.skelAnime.jointTable,
                                   this->enHy.skelAnime.dListCount, EnCne01_OverrideLimbDraw, EnCne01_PostLimbDraw,
                                   EnCne01_TransformLimbDraw, &this->enHy.actor);
    Matrix_InsertXRotation_s(0, MTXMODE_NEW);

    for (i = 0, shadowTexIter = shadowTex; i < (s32)sizeof(u8[64][64]); i++) {
        *shadowTexIter++ = 0;
    }
    for (i = 0; i < 5; i++) {
        func_8013CD64(this->enHy.bodyPartsPos, &this->enHy.actor.world.pos, shadowTex, i / 5.0f,
                      ARRAY_COUNT(this->enHy.bodyPartsPos), gEnHyShadowSize, gEnHyBodyPartsIndex);
    }
    func_8013CF04(&this->enHy.actor, &globalCtx->state.gfxCtx, shadowTex);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
