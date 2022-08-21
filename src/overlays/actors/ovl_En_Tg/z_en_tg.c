/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling) - End Credits Scene
 */

#include "z_en_tg.h"
#include "objects/object_mu/object_mu.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnTg*)thisx)

void EnTg_Init(Actor* thisx, PlayState* play);
void EnTg_Destroy(Actor* thisx, PlayState* play);
void EnTg_Update(Actor* thisx, PlayState* play);
void EnTg_Draw(Actor* thisx, PlayState* play);

void EnTg_Idle(EnTg* this, PlayState* play);
void EnTg_UpdateHearts(PlayState* play, EnTgHeartEffect* enTgHeartEffect, s32 len);
void EnTg_DrawHeart(PlayState* play, EnTgHeartEffect* enTgHeartEffect, s32 len);
void EnTg_SpawnFirstHeart(EnTg* this, EnTgHeartEffect* enTgHeartEffect, Vec3f* heartStartPos, s32 len);

const ActorInit En_Tg_InitVars = {
    ACTOR_EN_TG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MU,
    sizeof(EnTg),
    (ActorFunc)EnTg_Init,
    (ActorFunc)EnTg_Destroy,
    (ActorFunc)EnTg_Update,
    (ActorFunc)EnTg_Draw,
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
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(0, 0x0),
    /* Ice arrow      */ DMG_ENTRY(0, 0x0),
    /* Light arrow    */ DMG_ENTRY(0, 0x0),
    /* Goron spikes   */ DMG_ENTRY(0, 0x0),
    /* Deku spin      */ DMG_ENTRY(0, 0x0),
    /* Deku bubble    */ DMG_ENTRY(0, 0x0),
    /* Deku launch    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x12   */ DMG_ENTRY(0, 0x0),
    /* Zora barrier   */ DMG_ENTRY(0, 0x0),
    /* Normal shield  */ DMG_ENTRY(0, 0x0),
    /* Light ray      */ DMG_ENTRY(0, 0x0),
    /* Thrown object  */ DMG_ENTRY(0, 0x0),
    /* Zora punch     */ DMG_ENTRY(0, 0x0),
    /* Spin attack    */ DMG_ENTRY(0, 0x0),
    /* Sword beam     */ DMG_ENTRY(0, 0x0),
    /* Normal Roll    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1B   */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1C   */ DMG_ENTRY(0, 0x0),
    /* Unblockable    */ DMG_ENTRY(0, 0x0),
    /* UNK_DMG_0x1E   */ DMG_ENTRY(0, 0x0),
    /* Powder Keg     */ DMG_ENTRY(0, 0x0),
};

static AnimationInfoS sAnimationInfo = { &gHoneyAndDarlingIdleAnim, 1.0f, 0, -1, ANIMMODE_LOOP, 0 };

void EnTg_ChangeAnim(SkelAnime* skelAnime, AnimationInfoS* animationInfo, s16 animIndex) {
    f32 endFrame;

    animationInfo += animIndex;

    if (animationInfo->frameCount < 0) {
        endFrame = Animation_GetLastFrame(animationInfo->animation);
    } else {
        endFrame = animationInfo->frameCount;
    }
    Animation_Change(skelAnime, animationInfo->animation, animationInfo->playSpeed, animationInfo->startFrame, endFrame,
                     animationInfo->mode, animationInfo->morphFrames);
}

void EnTg_UpdateCollider(EnTg* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

void EnTg_UpdateSkelAnime(EnTg* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

void EnTg_Init(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &gHoneyAndDarlingSkel, NULL, this->jointTable, this->morphTable,
                       HONEY_AND_DARLING_LIMB_MAX);
    EnTg_ChangeAnim(&this->skelAnime, &sAnimationInfo, 0);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = EnTg_Idle;
    this->actor.gravity = -4.0f;
}

void EnTg_Destroy(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

/**
 * The actor spins, and a heart is spawned above the actor every 12 frames.
 */
void EnTg_Idle(EnTg* this, PlayState* play) {
    Vec3f heartStartPos;

    this->actor.shape.rot.y += sREG(0) + 0x258;
    this->actor.world.rot = this->actor.shape.rot;

    if (DECR(this->spawnHeartTimer) == 0) {
        this->spawnHeartTimer = 12;
        heartStartPos = this->actor.world.pos;
        heartStartPos.y += 62.0f;
        EnTg_SpawnFirstHeart(this, this->enTgHeartEffect, &heartStartPos, 10);
    }
}

void EnTg_Update(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4U);
    EnTg_UpdateSkelAnime(this, play);
    EnTg_UpdateHearts(play, this->enTgHeartEffect, 10);
    EnTg_UpdateCollider(this, play);
}

s32 EnTg_OverrideLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    return 0;
}

void EnTg_PostLimbDraw(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };

    if (limbIndex == HONEY_AND_DARLING_LIMB_MAN_HEAD) {
        Matrix_MultVec3f(&zeroVec, &this->actor.focus.pos);
    }
}

void EnTg_Draw(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;
    GraphicsContext* gfxCtx;

    Matrix_Push();
    EnTg_DrawHeart(play, this->enTgHeartEffect, 10);
    Matrix_Pop();

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 0, 50, 160, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 255, 255, 255, 0));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, this->skelAnime.dListCount,
                          EnTg_OverrideLimbDraw, EnTg_PostLimbDraw, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

/**
 * This function is always called with the same heartStartPos and len = 10.
 * Sets all the flags and a path for when the first heart (of two) is spawned.
 */
void EnTg_SpawnFirstHeart(EnTg* this, EnTgHeartEffect* enTgHeartEffect, Vec3f* heartStartPos, s32 len) {
    Vec3f heartVelocityVec = { 0.0f, 1.5f, 0.0f };
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    s32 i;

    for (i = 0; i < len && enTgHeartEffect->isEnabled; i++, enTgHeartEffect++) {}

    if (i < len) {
        enTgHeartEffect->isEnabled = true;
        enTgHeartEffect->pos = *heartStartPos;
        enTgHeartEffect->velocity = heartVelocityVec;
        enTgHeartEffect->unusedZeroVec20 = zeroVec;
        enTgHeartEffect->scale = 0.01f;
        enTgHeartEffect->pos.x += 4.0f * Math_SinS(this->actor.shape.rot.y);
        enTgHeartEffect->pos.z += 4.0f * Math_CosS(this->actor.shape.rot.y);
        enTgHeartEffect->timer = 16;
    }
}

/**
 * This function is always called with the same len = 10.
 * The heart path is curvy as it floats up because of the use of Math_SinS and Math_CosS.
 * The first heart spawned sets the path, the second heart spawned follows it.
 */
void EnTg_UpdateHearts(PlayState* play, EnTgHeartEffect* enTgHeartEffect, s32 len) {
    Vec3f zeroVec = { 0.0f, 0.0f, 0.0f };
    s16 yaw = Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
    s32 i;

    for (i = 0; i < len; i++, enTgHeartEffect++) {
        if (enTgHeartEffect->isEnabled == 1) {
            if (DECR(enTgHeartEffect->timer) == 0) {
                enTgHeartEffect->isEnabled = false;
            }
            enTgHeartEffect->pos.y += enTgHeartEffect->velocity.y; // always increased by 1.5f
            enTgHeartEffect->pos.x += 2.0f * Math_SinS(enTgHeartEffect->angle);
            enTgHeartEffect->pos.z += 2.0f * Math_CosS(enTgHeartEffect->angle);

            Matrix_Push();
            Matrix_Translate(enTgHeartEffect->pos.x, enTgHeartEffect->pos.y,
                             enTgHeartEffect->pos.z, MTXMODE_NEW);
            Matrix_RotateYS(yaw, MTXMODE_APPLY);
            Matrix_MultVec3f(&zeroVec, &enTgHeartEffect->pos);
            Matrix_Pop();

            enTgHeartEffect->angle += 0x1770;
        }
    }
}

void EnTg_DrawHeart(PlayState* play, EnTgHeartEffect* enTgHeartEffect, s32 len) {
    s32 i;
    s32 flag = false;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < len; i++, enTgHeartEffect++) {
        if (enTgHeartEffect->isEnabled == 1) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, gHoneyAndDarlingHeartMaterialDL);
                flag = true;
            }
            Matrix_Translate(enTgHeartEffect->pos.x, enTgHeartEffect->pos.y,
                             enTgHeartEffect->pos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(enTgHeartEffect->scale, enTgHeartEffect->scale, enTgHeartEffect->scale, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gHoneyAndDarlingHeartModelDL);
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
