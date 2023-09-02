/*
 * File: z_en_cne_01.c
 * Overlay: ovl_En_Cne_01
 * Description: Unused Market NPC
 */

#include "z_en_cne_01.h"
#include "objects/object_cne/object_cne.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY | ACTOR_FLAG_10)

#define THIS ((EnCne01*)thisx)

void EnCne01_Init(Actor* thisx, PlayState* play);
void EnCne01_Destroy(Actor* thisx, PlayState* play);
void EnCne01_Update(Actor* thisx, PlayState* play);
void EnCne01_Draw(Actor* thisx, PlayState* play);

void EnCne01_Walk(EnHy* this, PlayState* play);
void EnCne01_FaceForward(EnHy* this, PlayState* play);
void EnCne01_Talk(EnHy* this, PlayState* play);

ActorInit En_Cne_01_InitVars = {
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

static TrackOptionsSet sTrackOptions = {
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
    { 0xFA0, 4, 1, 3 },
    { 0x1770, 4, 1, 6 },
};

void EnCne01_UpdateModel(EnCne01* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f point;

    EnHy_UpdateSkelAnime(&this->enHy, play);
    if (SubS_AngleDiffLessEqual(this->enHy.actor.shape.rot.y, 0x36B0, this->enHy.actor.yawTowardsPlayer)) {
        point.x = player->actor.world.pos.x;
        point.y = player->bodyPartsPos[PLAYER_BODYPART_HEAD].y + 3.0f;
        point.z = player->actor.world.pos.z;
        SubS_TrackPoint(&point, &this->enHy.actor.focus.pos, &this->enHy.actor.shape.rot, &this->enHy.trackTarget,
                        &this->enHy.headRot, &this->enHy.torsoRot, &sTrackOptions);
    } else {
        Math_SmoothStepToS(&this->enHy.trackTarget.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.trackTarget.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.headRot.y, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.x, 0, 4, 0x3E8, 1);
        Math_SmoothStepToS(&this->enHy.torsoRot.y, 0, 4, 0x3E8, 1);
    }
    SubS_UpdateFidgetTables(play, this->enHy.fidgetTableY, this->enHy.fidgetTableZ, ENHY_LIMB_MAX);
    EnHy_UpdateCollider(&this->enHy, play);
}

s32 EnCne01_TestIsTalking(EnCne01* this, PlayState* play) {
    s32 isTalking = false;

    if (Actor_ProcessTalkRequest(&this->enHy.actor, &play->state)) {
        isTalking = true;
        this->enHy.textId = 0x10B9; // Invalid textId, produces empty textbox
        this->enHy.prevTrackTarget = this->enHy.trackTarget;
        this->enHy.prevHeadRot = this->enHy.headRot;
        this->enHy.prevTorsoRot = this->enHy.torsoRot;
        this->enHy.prevActionFunc = this->enHy.actionFunc;
        this->enHy.actionFunc = EnCne01_Talk;
    }
    return isTalking;
}

s32 func_809CB4A0(EnCne01* this, PlayState* play) {
    s16 x;
    s16 y;

    Actor_GetScreenPos(play, &this->enHy.actor, &x, &y);
    //! @bug: Both x and y conditionals are always true, || should be an &&
    if (!this->enHy.waitingOnInit && ((x >= 0) || (x < SCREEN_WIDTH)) && ((y >= 0) || (y < SCREEN_HEIGHT))) {
        Actor_OfferTalkExchangeEquiCylinder(&this->enHy.actor, play, 30.0f, PLAYER_IA_MAGIC_BEANS);
    }
    return true;
}

void EnCne01_FinishInit(EnHy* this, PlayState* play) {
    if (EnHy_Init(this, play, &gCneSkel, ENHY_ANIM_OS_ANIME_11)) {
        this->actor.flags |= ACTOR_FLAG_TARGETABLE;
        this->actor.draw = EnCne01_Draw;
        this->waitingOnInit = false;
        if (ENCNE01_GET_PATH_INDEX(&this->actor) == ENCNE01_PATH_INDEX_NONE) {
            this->actionFunc = EnCne01_FaceForward;
        } else {
            this->actionFunc = EnCne01_Walk;
        }
    }
}

void EnCne01_Walk(EnHy* this, PlayState* play) {
    if (EnHy_MoveForwards(this, 1.0f)) {
        this->curPoint = 0;
    }
}

void EnCne01_FaceForward(EnHy* this, PlayState* play) {
    this->actor.shape.rot = this->actor.world.rot;
}

void EnCne01_Talk(EnHy* this, PlayState* play) {
    s16 yaw;
    u8 talkState;

    Math_SmoothStepToS(&this->actor.shape.rot.y, this->actor.yawTowardsPlayer, 4, 0xFA0, 1);

    talkState = Message_GetState(&play->msgCtx);
    this->inMsgState3 = (talkState == TEXT_STATE_3) ? true : false;

    switch (talkState) {
        case TEXT_STATE_NONE:
            yaw = ABS_ALT(this->actor.shape.rot.y - this->actor.yawTowardsPlayer);
            if (yaw < 0x64) {
                Message_StartTextbox(play, this->textId, NULL);
            }
            break;

        case TEXT_STATE_CLOSING:
            this->actor.textId = 0;
            this->trackTarget = this->prevTrackTarget;
            this->headRot = this->prevHeadRot;
            this->torsoRot = this->prevTorsoRot;
            this->actor.shape.rot.y = this->actor.world.rot.y;
            this->actionFunc = this->prevActionFunc;
            this->prevActionFunc = NULL;
            break;

        default:
            break;
    }
}

void EnCne01_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    EnCne01* this = THIS;

    this->enHy.animObjIndex = SubS_GetObjectIndex(OBJECT_OS_ANIME, play);
    this->enHy.headObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);
    this->enHy.skelUpperObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);
    this->enHy.skelLowerObjIndex = SubS_GetObjectIndex(OBJECT_CNE, play);

    if ((this->enHy.animObjIndex < 0) || (this->enHy.headObjIndex < 0) || (this->enHy.skelUpperObjIndex < 0) ||
        (this->enHy.skelLowerObjIndex < 0)) {
        Actor_Kill(&this->enHy.actor);
    }
    this->enHy.actor.draw = NULL;
    Collider_InitCylinder(play, &this->enHy.collider);
    Collider_SetCylinder(play, &this->enHy.collider, &this->enHy.actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->enHy.actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    this->enHy.actor.flags &= ~ACTOR_FLAG_TARGETABLE;
    this->enHy.path = SubS_GetPathByIndex(play, ENCNE01_GET_PATH_INDEX(&this->enHy.actor), ENCNE01_PATH_INDEX_NONE);
    this->enHy.waitingOnInit = true;
    Actor_SetScale(&this->enHy.actor, 0.01f);
    this->enHy.actionFunc = EnCne01_FinishInit;
}

void EnCne01_Destroy(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;

    Collider_DestroyCylinder(play, &this->enHy.collider);
}

void EnCne01_Update(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;

    EnCne01_TestIsTalking(this, play);
    this->enHy.actionFunc(&this->enHy, play);
    Actor_UpdateBgCheckInfo(play, &this->enHy.actor, 0.0f, 0.0f, 0.0f, UPDBGCHECKINFO_FLAG_4);
    EnCne01_UpdateModel(this, play);
    func_809CB4A0(this, play);
}

s32 EnCne01_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnCne01* this = THIS;
    s8 bodyPartIndex;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    bodyPartIndex = gEnHyLimbToBodyParts[limbIndex];
    if (bodyPartIndex > BODYPART_NONE) {
        Matrix_MultVec3f(&zeroVec, &this->enHy.bodyPartsPos[bodyPartIndex]);
    }

    if (limbIndex == CNE_LIMB_HEAD) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->enHy.headObjIndex].segment);
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->enHy.headObjIndex].segment);
        *dList = gCneHeadBrownHairDL;
        gSegments[6] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->enHy.skelLowerObjIndex].segment);

        CLOSE_DISPS(play->state.gfxCtx);
    }
    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_Translate(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_RotateXS(this->enHy.headRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->enHy.headRot.x, MTXMODE_APPLY);
        Matrix_Translate(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == CNE_LIMB_TORSO) {
        Matrix_RotateXS(-this->enHy.torsoRot.y, MTXMODE_APPLY);
        Matrix_RotateZS(-this->enHy.torsoRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_HEAD) && this->enHy.inMsgState3 && ((play->state.frames % 2) == 0)) {
        Matrix_Translate(40.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if ((limbIndex == CNE_LIMB_TORSO) || (limbIndex == CNE_LIMB_LEFT_UPPER_ARM) ||
        (limbIndex == CNE_LIMB_RIGHT_UPPER_ARM)) {
        rot->y += (s16)(Math_SinS(this->enHy.fidgetTableY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->enHy.fidgetTableZ[limbIndex]) * 200.0f);
    }

    return false;
}

void EnCne01_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnCne01* this = THIS;
    GraphicsContext* gfxCtx = play->state.gfxCtx;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == CNE_LIMB_RIGHT_FOOT) {
        OPEN_DISPS(play->state.gfxCtx);

        gSPSegment(POLY_OPA_DISP++, 0x06, play->objectCtx.status[this->enHy.skelUpperObjIndex].segment);
        gSegments[0x06] = VIRTUAL_TO_PHYSICAL(play->objectCtx.status[this->enHy.skelUpperObjIndex].segment);

        CLOSE_DISPS(play->state.gfxCtx);
    }

    if (limbIndex == CNE_LIMB_HEAD) {
        Matrix_MultVec3f(&zeroVec, &this->enHy.actor.focus.pos);
    }
}

void EnCne01_TransformLimbDraw(PlayState* play, s32 limbIndex, Actor* thisx) {
}

void EnCne01_Draw(Actor* thisx, PlayState* play) {
    EnCne01* this = THIS;
    s32 i;
    u8* shadowTex = GRAPH_ALLOC(play->state.gfxCtx, SUBS_SHADOW_TEX_SIZE);
    u8* shadowTexIter;

    OPEN_DISPS(play->state.gfxCtx);

    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 160, 180, 255, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 160, 180, 255, 0));
    gSPSegment(POLY_OPA_DISP++, 0x0A, Gfx_EnvColor(play->state.gfxCtx, 160, 180, 255, 0));
    gDPPipeSync(POLY_OPA_DISP++);
    SkelAnime_DrawTransformFlexOpa(play, this->enHy.skelAnime.skeleton, this->enHy.skelAnime.jointTable,
                                   this->enHy.skelAnime.dListCount, EnCne01_OverrideLimbDraw, EnCne01_PostLimbDraw,
                                   EnCne01_TransformLimbDraw, &this->enHy.actor);
    Matrix_RotateXS(0, MTXMODE_NEW);

    for (i = 0, shadowTexIter = shadowTex; i < SUBS_SHADOW_TEX_SIZE; i++) {
        *shadowTexIter++ = 0;
    }
    for (i = 0; i < 5; i++) {
        SubS_GenShadowTex(this->enHy.bodyPartsPos, &this->enHy.actor.world.pos, shadowTex, i / 5.0f, ENHY_BODYPART_MAX,
                          gEnHyShadowSizes, gEnHyParentShadowBodyParts);
    }
    SubS_DrawShadowTex(&this->enHy.actor, &play->state, shadowTex);

    CLOSE_DISPS(play->state.gfxCtx);
}
