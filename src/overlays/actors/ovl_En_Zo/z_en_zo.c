/*
 * File: z_en_zo.c
 * Overlay: ovl_En_Zo
 * Description: Zoras (unused)
 */

#include "z_en_zo.h"
#include "objects/object_zo/object_zo.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_10)

#define THIS ((EnZo*)thisx)

void EnZo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnZo_FollowPath(EnZo* this, GlobalContext* globalCtx);
void EnZo_TreadWater(EnZo* this, GlobalContext* globalCtx);
void EnZo_DoNothing(EnZo* this, GlobalContext* globalCtx);

const ActorInit En_Zo_InitVars = {
    ACTOR_EN_ZO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZo),
    (ActorFunc)EnZo_Init,
    (ActorFunc)EnZo_Destroy,
    (ActorFunc)EnZo_Update,
    (ActorFunc)EnZo_Draw,
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

static AnimationInfoS sAnimations[] = {
    { &gZoraIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 },
    { &gZoraIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gZoraSurfacingAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gZoraHandsOnHipsTappingFootAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gZoraArmsOpenAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gZoraThrowRupeeAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
    { &gZoraWalkAnim, 1.0f, 0, -1, ANIMMODE_LOOP, -4 },
};

s8 D_8099F578[] = { -1, 1, 12, 13, 14, 9, 10, 11, 0, 6, 7, 8, 3, 4, 5, 2, -1, -1, -1, -1 };
s8 D_8099F58C[] = { 0, 0, 0, 0, 3, 4, 0, 6, 7, 0, 9, 10, 0, 12, 13 };
u8 D_8099F59C[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

s32 EnZo_SetAnimation(SkelAnime* skelAnime, s16 index) {
    s16 frameCount;
    s32 didChange = false;

    if ((index >= 0) && (index < ARRAY_COUNT(sAnimations))) {
        didChange = true;
        frameCount = sAnimations[index].frameCount;
        if (frameCount < 0) {
            frameCount = Animation_GetLastFrame(sAnimations[index].animation);
        }
        Animation_Change(skelAnime, sAnimations[index].animation, sAnimations[index].playSpeed,
                         sAnimations[index].startFrame, frameCount, sAnimations[index].mode,
                         sAnimations[index].morphFrames);
    }
    return didChange;
}

s32 EnZo_PlayWalkingSound(EnZo* this, GlobalContext* globalCtx) {
    u8 leftWasGrounded;
    u8 rightWasGrounded;
    s32 waterSfxId;
    u16 sfxId;
    u8 isFootGrounded;

    leftWasGrounded = this->isLeftFootGrounded;
    rightWasGrounded = this->isRightFootGrounded;

    if (this->actor.bgCheckFlags & 0x20) {
        if (this->actor.depthInWater < 20.0f) {
            waterSfxId = NA_SE_PL_WALK_WATER0 - SFX_FLAG;
        } else {
            waterSfxId = NA_SE_PL_WALK_WATER1 - SFX_FLAG;
        }
        sfxId = waterSfxId + SFX_FLAG;
    } else {
        sfxId = SurfaceType_GetSfx(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) + SFX_FLAG;
    }

    this->isLeftFootGrounded = isFootGrounded = SubS_IsFloorAbove(globalCtx, &this->leftFootPos, -6.0f);
    if ((this->isLeftFootGrounded) && (!leftWasGrounded) && (isFootGrounded)) {
        Actor_PlaySfxAtPos(&this->actor, sfxId);
    }

    this->isRightFootGrounded = isFootGrounded = SubS_IsFloorAbove(globalCtx, &this->rightFootPos, -6.0f);
    if ((this->isRightFootGrounded) && (!rightWasGrounded) && (isFootGrounded)) {
        Actor_PlaySfxAtPos(&this->actor, sfxId);
    }

    return 0;
}

void EnZo_Blink(EnZo* this, s32 maxEyeIndex) {
    if (DECR(this->blinkTimer) == 0) {
        this->eyeIndex++;
        if (this->eyeIndex >= maxEyeIndex) {
            this->eyeIndex = 0;
            this->blinkTimer = Rand_S16Offset(30, 30);
        }
    }
}

void EnZo_UpdateCollider(EnZo* this, GlobalContext* globalCtx) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void EnZo_LookAtPlayer(EnZo* this, GlobalContext* globalCtx) {
    static u16 D_8099F5AC[] = { 4000, 4, 1, 3, 6000, 4, 1, 6, 4000, 4, 1, 3, 6000, 4, 1, 6 };
    Player* player = GET_PLAYER(globalCtx);
    Vec3f focus;

    SkelAnime_Update(&this->skelAnime);
    if (SubS_AngleDiffLessEqual(this->actor.shape.rot.y, 0x2710, this->actor.yawTowardsPlayer)) {
        focus.x = player->actor.world.pos.x;
        focus.y = player->bodyPartsPos[7].y + 3.0f;
        focus.z = player->actor.world.pos.z;
        func_8013D2E0(&focus, &this->actor.focus.pos, &this->actor.shape.rot, &this->headRotTarget, &this->headRot,
                      &this->upperBodyRot, D_8099F5AC);
    } else {
        Math_SmoothStepToS(&this->headRotTarget.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->headRotTarget.y, 0, 4, 1000, 1);

        Math_SmoothStepToS(&this->headRot.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->headRot.y, 0, 4, 1000, 1);

        Math_SmoothStepToS(&this->upperBodyRot.x, 0, 4, 1000, 1);
        Math_SmoothStepToS(&this->upperBodyRot.y, 0, 4, 1000, 1);
    }

    EnZo_Blink(this, 3);
    SubS_FillLimbRotTables(globalCtx, this->limbRotY, this->limbRotZ, 20);
}

void EnZo_Walk(EnZo* this, GlobalContext* globalCtx) {
    if (ENZO_GET_PATH(&this->actor) != ENZO_NO_PATH) {
        EnZo_SetAnimation(&this->skelAnime, 6);
    }

    if (ENZO_GET_PATH(&this->actor) != ENZO_NO_PATH) {
        this->actionFunc = EnZo_FollowPath;
    } else {
        this->actionFunc = EnZo_DoNothing;
    }
}

void EnZo_FollowPath(EnZo* this, GlobalContext* globalCtx) {
    s16 speed;
    Vec3f pos;

    Math_SmoothStepToF(&this->actor.speedXZ, 1.0f, 0.4f, 1000.0f, 0.0f);
    speed = this->actor.speedXZ * 400.0f;
    if (SubS_CopyPointFromPath(this->path, this->waypoint, &pos) && SubS_MoveActorToPoint(&this->actor, &pos, speed)) {
        this->waypoint++;
        if (this->waypoint >= this->path->count) {
            this->waypoint = 0;
        }
    }

    if (this->actor.depthInWater > 60.0f) {
        EnZo_SetAnimation(&this->skelAnime, 1);
        this->actionFunc = EnZo_TreadWater;
        this->actor.gravity = 0.0f;
        this->actor.speedXZ = 0.0f;
    }
}

void EnZo_TreadWater(EnZo* this, GlobalContext* globalCtx) {
    f32 targetYVel;

    if (this->actor.depthInWater < (sREG(0) + 50.0f)) {
        targetYVel = -1.0f;
    } else {
        targetYVel = 1.0f;
    }
    Math_ApproachF(&this->actor.velocity.y, targetYVel, (sREG(1) + 18.0f) * 0.01f, (sREG(2) + 12.0f) * 0.01f);
}

void EnZo_DoNothing(EnZo* this, GlobalContext* globalCtx) {
}

void EnZo_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnZo* this = THIS;
    s32 pad;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &gZoraSkel, NULL, this->jointTable, this->morphTable, 20);
    EnZo_SetAnimation(&this->skelAnime, 0);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);

    this->path = SubS_GetPathByIndex(globalCtx, ENZO_GET_PATH(&this->actor), ENZO_NO_PATH);
    Actor_SetScale(&this->actor, 0.01f);

    this->actionFunc = EnZo_Walk;
    this->actor.gravity = -4.0f;
}

void EnZo_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnZo* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void EnZo_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnZo* this = THIS;

    this->actionFunc(this, globalCtx);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
    EnZo_LookAtPlayer(this, globalCtx);
    EnZo_PlayWalkingSound(this, globalCtx);
    EnZo_UpdateCollider(this, globalCtx);
}

s32 EnZo_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx,
                          Gfx** gfx) {
    EnZo* this = THIS;

    if (limbIndex == 15) {
        Matrix_InsertTranslation(1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(this->headRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->headRot.x, MTXMODE_APPLY);
        Matrix_InsertTranslation(-1500.0f, 0.0f, 0.0f, MTXMODE_APPLY);
    }

    if (limbIndex == 8) {
        Matrix_InsertXRotation_s(-this->upperBodyRot.y, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-this->upperBodyRot.x, MTXMODE_APPLY);
    }

    if ((limbIndex == 8) || (limbIndex == 9) || (limbIndex == 12)) {
        rot->y += (s16)(Math_SinS(this->limbRotY[limbIndex]) * 200.0f);
        rot->z += (s16)(Math_CosS(this->limbRotZ[limbIndex]) * 200.0f);
    }
    return false;
}

void EnZo_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx, Gfx** gfx) {
    EnZo* this = THIS;
    Vec3f sp30 = { 400.0f, 0.0f, 0.0f };
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (D_8099F578[limbIndex] >= 0) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->unk_364[D_8099F578[limbIndex]]);
    }
    if (limbIndex == 15) {
        Matrix_MultiplyVector3fByState(&sp30, &this->actor.focus.pos);
    }
    if (limbIndex == 4) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->leftFootPos);
    }
    if (limbIndex == 7) {
        Matrix_MultiplyVector3fByState(&zeroVec, &this->rightFootPos);
    }
}

static Gfx sTransparencyDlist[] = {
    gsDPSetRenderMode(AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          G_RM_FOG_SHADE_A,
                      AA_EN | Z_CMP | Z_UPD | IM_RD | CLR_ON_CVG | CVG_DST_WRAP | ZMODE_XLU | FORCE_BL |
                          GBL_c2(G_BL_CLR_IN, G_BL_A_IN, G_BL_CLR_MEM, G_BL_1MA)),
    gsDPSetAlphaCompare(G_AC_THRESHOLD),
    gsSPEndDisplayList(),
};

void EnZo_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnZo* this = THIS;
    s32 i;
    u8* shadowTex = GRAPH_ALLOC(globalCtx->state.gfxCtx, sizeof(u8) * SQ(64));
    u8* shadowTexIter;
    TexturePtr eyeTextures[] = { &gZoraEyeOpenTex, &gZoraEyeHalfTex, &gZoraEyeClosedTex };

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(eyeTextures[this->eyeIndex]));
    gSPSegment(POLY_OPA_DISP++, 0x0C, &sTransparencyDlist[2]);

    POLY_OPA_DISP =
        SkelAnime_DrawFlex(globalCtx, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                           EnZo_OverrideLimbDraw, EnZo_PostLimbDraw, &this->actor, POLY_OPA_DISP);
    Matrix_InsertXRotation_s(0, 0);

    for (i = 0, shadowTexIter = shadowTex; i < (s32)sizeof(u8) * SQ(64); i++) {
        *shadowTexIter = 0;
        shadowTexIter++;
    }
    for (i = 0; i < 5; i++) {
        func_8013CD64(this->unk_364, &this->actor.world.pos, shadowTex, i / 5.0f, 15, D_8099F59C, D_8099F58C);
    }

    func_8013CF04(&this->actor, &globalCtx->state.gfxCtx, shadowTex);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
