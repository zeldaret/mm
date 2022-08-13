/*
 * File: z_en_tg.c
 * Overlay: ovl_En_Tg
 * Description: Target Game (Honey & Darling) - End Credits
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

void func_8098FA70(EnTg* this, PlayState* play);
void func_8098FEA8(PlayState* play, EnTgUnkStruct* enTgUnkStruct, s32 len);
void func_8099000C(PlayState* play, EnTgUnkStruct* enTgUnkStruct, s32 len);
void func_8098FD50(EnTg* this, EnTgUnkStruct* enTgUnkStruct, Vec3f* heartStartPos, s32 len);

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

// sColChkInfoInit
static CollisionCheckInfoInit2 sColChkInfoInit = { 0, 0, 0, 0, MASS_IMMOVABLE };

// static DamageTable sDamageTable = {
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

static AnimationInfoS sAnimations = { &object_mu_Anim_0053E0, 1.0f, 0, -1, 0, 0 };
static Vec3f D_80990228 = { 0.0f, 0.0f, 0.0f }; // TODO: rename sZeroVec0?
static Vec3f D_80990234 = { 0.0f, 1.5f, 0.0f };
static Vec3f D_80990240 = { 0.0f, 0.0f, 0.0f }; // TODO: rename sZeroVec1?
static Vec3f D_8099024C = { 0.0f, 0.0f, 0.0f }; // TODO: rename sZeroVec2?

// EnTg_ChangeAnimation - func_8098F800
void EnTg_ChangeAnimation(SkelAnime* skelAnime, AnimationInfoS* animation, s16 unusedExtraOffset) {
    f32 endFrame;

    animation += unusedExtraOffset;

    if (animation->frameCount < 0) {
        endFrame = (f32)Animation_GetLastFrame(animation->animation);
    } else {
        endFrame = animation->frameCount;
    }
    Animation_Change(skelAnime, animation->animation, animation->playSpeed, animation->startFrame, endFrame,
                     animation->mode, animation->morphFrames);
}

void EnTg_UpdateCollider(EnTg* this, PlayState* play) {
    this->collider.dim.pos.x = this->actor.world.pos.x;
    this->collider.dim.pos.y = this->actor.world.pos.y;
    this->collider.dim.pos.z = this->actor.world.pos.z;
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
}

// Called in Update
// Maybe UpdateSkelAnime? or is some kind of animation playing?
// also could be Idle?
void func_8098F928(EnTg* this, PlayState* play) {
    SkelAnime_Update(&this->skelAnime);
}

void EnTg_Init(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    ActorShape_Init(&this->actor.shape, 0.0f, NULL, 0.0f);
    SkelAnime_InitFlex(play, &this->skelAnime, &object_mu_Skel_00B2B0, NULL, this->jointTable, this->morphTable, 21);
    EnTg_ChangeAnimation(&this->skelAnime, &sAnimations, 0);
    Collider_InitCylinder(play, &this->collider);
    Collider_SetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    CollisionCheck_SetInfo2(&this->actor.colChkInfo, &sDamageTable, &sColChkInfoInit);
    Actor_SetScale(&this->actor, 0.01f);
    this->actionFunc = func_8098FA70;
    this->actor.gravity = -4.0f;
}

void EnTg_Destroy(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

// TODO: Maybe EnTg_IdleSpin ?
void func_8098FA70(EnTg* this, PlayState* play) {
    Vec3f heartStartPos;

    this->actor.shape.rot.y += sREG(0) + 0x258; // -256
    this->actor.world.rot = this->actor.shape.rot;

    // A new heart is spawned every 12 frames
    if (DECR(this->spawnHeartTimer) == 0) {
        this->spawnHeartTimer = 12;
        heartStartPos = this->actor.world.pos; // -119.0, -8.0, -38.0
        heartStartPos.y += 62.0f;              // 54, the starting height for where the hearts spawn
        func_8098FD50(this, &this->enTgUnkStruct, &heartStartPos, 10);
    }
}

void EnTg_Update(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    this->actionFunc(this, play);
    Actor_UpdateBgCheckInfo(play, &this->actor, 0.0f, 0.0f, 0.0f, 4U);
    func_8098F928(this, play);
    func_8098FEA8(play, &this->enTgUnkStruct, 10);
    EnTg_UpdateCollider(this, play);
}

// EnTg_OverrideLimbDraw
// func_8098FBB4
s32 func_8098FBB4(PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;
    return 0;
}

// EnTg_PostLimbDraw
// func_8098FBD0
void func_8098FBD0(PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
    EnTg* this = THIS;

    Vec3f zeroVec = D_80990228; // { 0.0f, 0.0f, 0.0f };

    if (limbIndex == 9) {
        Matrix_MultVec3f(&zeroVec, &this->actor.focus.pos);
    }
}

void EnTg_Draw(Actor* thisx, PlayState* play) {
    EnTg* this = THIS;

    GraphicsContext* gfxCtx;

    Matrix_Push();
    func_8099000C(play, &this->enTgUnkStruct, 10);
    Matrix_Pop();

    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);

    gDPPipeSync(POLY_OPA_DISP++);
    gSPSegment(POLY_OPA_DISP++, 0x08, Gfx_EnvColor(play->state.gfxCtx, 0, 0x32, 0xA0, 0));
    gSPSegment(POLY_OPA_DISP++, 0x09, Gfx_EnvColor(play->state.gfxCtx, 0xFF, 0xFF, 0xFF, 0));

    SkelAnime_DrawFlexOpa(play, this->skelAnime.skeleton, this->skelAnime.jointTable, (s32)this->skelAnime.dListCount,
                          func_8098FBB4, func_8098FBD0, &this->actor);

    CLOSE_DISPS(play->state.gfxCtx);
}

// TODO: called in action function
// EnTg_SpawnHeart
// func_8098FD50
void func_8098FD50(EnTg* this, EnTgUnkStruct* enTgUnkStruct, Vec3f* heartStartPos, s32 len) {
    Vec3f heartVelocityVec = D_80990234; // { 0.0f, 1.5f, 0.0f };
    Vec3f zeroVec = D_80990240;          // { 0.0f, 0.0f, 0.0f };
    s32 i = 0;

    while ((i < len) && enTgUnkStruct->isSecondHeartSpawned) {
        i++;
        enTgUnkStruct++;
    }

    if (i < len) {
        enTgUnkStruct->isSecondHeartSpawned = true;
        enTgUnkStruct->secondHeartPos = *heartStartPos; // actor->world.pos + 62
        enTgUnkStruct->heartVelocity = heartVelocityVec;
        enTgUnkStruct->unusedZeroVec20 = zeroVec;
        enTgUnkStruct->scale = 0.01f;

        // TODO: maybe affects the heart wiggly path? watch actor shape rot
        enTgUnkStruct->secondHeartPos.x += 4.0f * Math_SinS(this->actor.shape.rot.y);
        enTgUnkStruct->secondHeartPos.z += 4.0f * Math_CosS(this->actor.shape.rot.y);
        enTgUnkStruct->secondHeartTimer = 16;
    }
}

// Looks just like func_809647EC in z_en_fu.c
// Called in Update... Updates heart positions?
void func_8098FEA8(PlayState* play, EnTgUnkStruct* enTgUnkStruct, s32 len) {
    Vec3f zeroVec = D_8099024C;
    s16 yaw = Camera_GetInputDirYaw(GET_ACTIVE_CAM(play));
    s32 i;

    // Every len frames, update heart position(s)?
    for (i = 0; i < len; i++, enTgUnkStruct++) {
        if (enTgUnkStruct->isSecondHeartSpawned == 1) {
            if (DECR(enTgUnkStruct->secondHeartTimer) == 0) {
                enTgUnkStruct->isSecondHeartSpawned = false;
            }
            enTgUnkStruct->secondHeartPos.y += enTgUnkStruct->heartVelocity.y; // is always increased by 1.5f
            enTgUnkStruct->secondHeartPos.x += 2.0f * Math_SinS(enTgUnkStruct->unk38);
            enTgUnkStruct->secondHeartPos.z += 2.0f * Math_CosS(enTgUnkStruct->unk38);
            Matrix_Push();
            Matrix_Translate(enTgUnkStruct->secondHeartPos.x, enTgUnkStruct->secondHeartPos.y,
                             enTgUnkStruct->secondHeartPos.z, MTXMODE_NEW);
            Matrix_RotateYS(yaw, MTXMODE_APPLY);
            Matrix_MultVec3f(&zeroVec, &enTgUnkStruct->secondHeartPos);
            Matrix_Pop();
            enTgUnkStruct->unk38 += 6000;
        }
    }
}

// Called in Draw... draws the heart(s)?
void func_8099000C(PlayState* play, EnTgUnkStruct* enTgUnkStruct, s32 len) {
    s32 i;
    s32 flag = false;

    OPEN_DISPS(play->state.gfxCtx);

    POLY_OPA_DISP = func_801660B8(play, POLY_OPA_DISP);
    POLY_OPA_DISP = func_8012C724(POLY_OPA_DISP);

    for (i = 0; i < len; i++, enTgUnkStruct++) {
        if (enTgUnkStruct->isSecondHeartSpawned == 1) {
            if (!flag) {
                gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0A0); // TODO: figure out what this thing is in Z64Uils
                flag = true;
            }
            Matrix_Translate(enTgUnkStruct->secondHeartPos.x, enTgUnkStruct->secondHeartPos.y,
                             enTgUnkStruct->secondHeartPos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(enTgUnkStruct->scale, enTgUnkStruct->scale, enTgUnkStruct->scale, MTXMODE_APPLY);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gameplay_keep_Tex_05E6F0));
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_mu_DL_00B0E0); // TODO: figure out what this thing is in Z64Uils
        }
    }

    CLOSE_DISPS(play->state.gfxCtx);
}
