/*
 * File: z_en_po_fusen.c
 * Overlay: ovl_En_Po_Fusen
 * Description: Romani Ranch - Poe Balloon
 */

#include "z_en_po_fusen.h"
#include "overlays/actors/ovl_En_Ma4/z_en_ma4.h"
#include "objects/object_po_fusen/object_po_fusen.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_100000 | ACTOR_FLAG_80000000)

#define THIS ((EnPoFusen*)thisx)

#define GET_FUSE_LEN_PARAM(this) (((Actor*)(this))->params & 0x3FF)
#define GET_IS_FUSE_TYPE_PARAM(this) (((Actor*)(this))->params & 0x8000)

void EnPoFusen_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPoFusen_Draw(Actor* thisx, GlobalContext* globalCtx);

u16 EnPoFusen_CheckParent(EnPoFusen* this, GlobalContext* globalCtx);
void EnPoFusen_InitNoFuse(EnPoFusen* this);
void EnPoFusen_InitFuse(EnPoFusen* this);
void EnPoFusen_Pop(EnPoFusen* this, GlobalContext* globalCtx);
void EnPoFusen_Idle(EnPoFusen* this, GlobalContext* globalCtx);
void EnPoFusen_IdleFuse(EnPoFusen* this, GlobalContext* globalCtx);
s32 EnPoFusen_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx);

const ActorInit En_Po_Fusen_InitVars = {
    ACTOR_EN_PO_FUSEN,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PO_FUSEN,
    sizeof(EnPoFusen),
    (ActorFunc)EnPoFusen_Init,
    (ActorFunc)EnPoFusen_Destroy,
    (ActorFunc)EnPoFusen_Update,
    (ActorFunc)EnPoFusen_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1 | OC2_UNK1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 200 }, 100 },
};

static DamageTable sDamageTable = {
    /* Deku Nut       */ DMG_ENTRY(0, 0x0),
    /* Deku Stick     */ DMG_ENTRY(0, 0x0),
    /* Horse trample  */ DMG_ENTRY(0, 0x0),
    /* Explosives     */ DMG_ENTRY(0, 0x0),
    /* Zora boomerang */ DMG_ENTRY(0, 0x0),
    /* Normal arrow   */ DMG_ENTRY(1, 0xF),
    /* UNK_DMG_0x06   */ DMG_ENTRY(0, 0x0),
    /* Hookshot       */ DMG_ENTRY(0, 0x0),
    /* Goron punch    */ DMG_ENTRY(0, 0x0),
    /* Sword          */ DMG_ENTRY(0, 0x0),
    /* Goron pound    */ DMG_ENTRY(0, 0x0),
    /* Fire arrow     */ DMG_ENTRY(1, 0xF),
    /* Ice arrow      */ DMG_ENTRY(1, 0xF),
    /* Light arrow    */ DMG_ENTRY(1, 0xF),
    /* Goron spikes   */ DMG_ENTRY(1, 0xF),
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

void EnPoFusen_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    f32 heightTemp;

    this->actor.scale.x = this->actor.scale.y = this->actor.scale.z = 0.007f;
    this->actor.targetMode = 6;
    this->actor.colChkInfo.damageTable = &sDamageTable;

    Collider_InitSphere(globalCtx, &this->collider);
    Collider_SetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);

    if (0) {}
    this->collider.dim.worldSphere.radius = 40;
    SkelAnime_InitFlex(globalCtx, &this->anime, &object_po_fusen_Skel_0024F0, &object_po_fusen_Anim_000040,
                       this->jointTable, this->morphTable, 10);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 25.0f);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 0x4);

    if (EnPoFusen_CheckParent(this, globalCtx) == 0) {
        Actor_MarkForDeath(&this->actor);
    }

    heightTemp = this->actor.floorHeight + 90.0f;
    if (this->actor.home.pos.y < heightTemp) {
        this->actor.home.pos.y = heightTemp;
    }

    this->randScaleChange = ((Rand_Next() % 0xFFFEU) - 0x7FFF);
    this->randYRotChange = ((Rand_Next() % 0x4B0U) - 0x258);
    this->avgBaseRotation = 0x1555;
    this->limb3Rot = 0;
    this->limb46Rot = 0;
    this->limb57Rot = 0;
    this->limb8Rot = 0;
    this->limb9Rot = 0x71C;
    this->randBaseRotChange = 0;

    if (GET_IS_FUSE_TYPE_PARAM(this)) {
        EnPoFusen_InitFuse(this);
        return;
    }

    EnPoFusen_InitNoFuse(this);
}

void EnPoFusen_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    Collider_DestroySphere(globalCtx, &this->collider);
}

u16 EnPoFusen_CheckParent(EnPoFusen* this, GlobalContext* globalCtx) {
    Actor* actorPtr;

    actorPtr = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;
    if (GET_IS_FUSE_TYPE_PARAM(this)) {
        return 1;
    }

    if (actorPtr != 0) {
        do {
            if (actorPtr->id == ACTOR_EN_MA4) {
                this->actor.parent = actorPtr;
                return 1;
            }
            actorPtr = actorPtr->next;
        } while (actorPtr != 0);
    }

    return 0;
}

u16 EnPoFusen_CheckCollision(EnPoFusen* this, GlobalContext* globalCtx) {
    if (this->actionFunc == EnPoFusen_IdleFuse) {
        return 0;
    }

    this->collider.dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = (this->actor.world.pos.y + 20.0f);
    this->collider.dim.worldSphere.center.z = this->actor.world.pos.z;

    if ((this->collider.base.acFlags & AC_HIT) && (this->actor.colChkInfo.damageEffect == 0xF)) {
        this->collider.base.acFlags &= ~AC_HIT;
        return 1;
    }

    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);

    return 0;
}

void EnPoFusen_InitNoFuse(EnPoFusen* this) {
    this->actor.shape.rot.z = 0;
    this->actionFunc = EnPoFusen_Idle;
}

void EnPoFusen_Idle(EnPoFusen* this, GlobalContext* globalCtx) {
    f32 shadowScaleTmp;
    f32 shadowAlphaTmp;
    f32 heightOffset;
    f32 f255 = 255.0f;

    this->actor.world.pos = this->actor.home.pos;
    this->randScaleChange += 0x190;
    this->randXZRotChange += 0x5DC;
    this->randBaseRotChange += 0x9C4;
    heightOffset = Math_SinS(this->randScaleChange);
    heightOffset = 50.0f * heightOffset;
    this->actor.shape.rot.y += this->randYRotChange;
    this->actor.world.pos.y += heightOffset;
    this->actor.shape.rot.z = (Math_SinS(this->randBaseRotChange) * 910.0f);

    if ((this->randScaleChange < 0x4000) && (this->randScaleChange >= -0x3FFF)) {
        Math_SmoothStepToS(&this->limb9Rot, 0x38E, 0x14, 0xBB8, 0x64);
    } else {
        Math_SmoothStepToS(&this->limb9Rot, 0x71C, 0x8, 0xBB8, 0x64);
    }

    this->avgBaseRotation = this->limb9Rot * 3;
    this->limb3Rot = (Math_SinS(this->randBaseRotChange + 0x38E3) * this->avgBaseRotation);
    this->limb46Rot = (Math_SinS(this->randBaseRotChange) * this->avgBaseRotation);
    this->limb57Rot = (Math_SinS(this->randBaseRotChange - 0x38E3) * this->avgBaseRotation);
    this->limb8Rot = (Math_SinS(this->randBaseRotChange - 0x71C6) * this->avgBaseRotation);

    shadowScaleTmp = ((1.0f - Math_SinS(this->randScaleChange)) * 10.0f) + 50.0f;
    shadowAlphaTmp = ((1.0f - Math_SinS(this->randScaleChange)) * 75.0f) + 100.0f;
    this->actor.shape.shadowScale = shadowScaleTmp;
    this->actor.shape.shadowAlpha = (shadowAlphaTmp > f255) ? (u8)f255 : (u8)shadowAlphaTmp;
}

void EnPoFusen_IncrementRomaniPop(EnPoFusen* this) {
    Actor* parent = this->actor.parent;
    EnMa4* romani;

    if ((parent != NULL) && (parent->id == ACTOR_EN_MA4)) {
        romani = (EnMa4*)parent;
        romani->poppedBalloonCounter++;
    }

    this->actor.draw = NULL;
    this->actionFunc = EnPoFusen_Pop;
}

void EnPoFusen_Pop(EnPoFusen* this, GlobalContext* globalCtx) {
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                this->actor.world.pos.y + 20.0f, this->actor.world.pos.z, 255, 255, 200, CLEAR_TAG_POP);
    Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
    Actor_MarkForDeath(&this->actor);
}

void EnPoFusen_InitFuse(EnPoFusen* this) {
    s16 rotZ = this->actor.shape.rot.z;
    this->fuse = GET_FUSE_LEN_PARAM(this);
    this->actor.shape.rot.z = 0;
    this->randScaleChange = rotZ & 0xFFFFu;
    this->actionFunc = EnPoFusen_IdleFuse;
}

void EnPoFusen_IdleFuse(EnPoFusen* this, GlobalContext* globalCtx) {
    EnPoFusen_Idle(this, globalCtx);
    if (this->fuse-- == 0) {
        EnPoFusen_IncrementRomaniPop(this);
    }
}

void EnPoFusen_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    this->actionFunc(this, globalCtx);
    if (EnPoFusen_CheckCollision(this, globalCtx) != 0) {
        EnPoFusen_IncrementRomaniPop(this);
    }
}

s32 EnPoFusen_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               Actor* thisx) {
    EnPoFusen* this = THIS;
    f32 zScale;
    f32 yScale;
    f32 xScale;
    s16 pad;
    s16 zRot;
    s16 pad2;
    s16 xRot;

    if (limbIndex == 2) {
        zScale = (Math_CosS(this->randScaleChange) * 0.08f) + 1.0f;
        xScale = zScale;
        if (!zScale) {}
        yScale = (Math_SinS(this->randScaleChange) * 0.08f) + 1.0f;
        yScale = yScale * yScale;
        xRot = ((Math_SinS(this->randXZRotChange) * 2730.0f));
        zRot = ((Math_CosS(this->randXZRotChange) * 2730.0f));
        Matrix_InsertRotation(xRot, 0, zRot, MTXMODE_APPLY);
        Matrix_Scale(xScale, yScale, zScale, MTXMODE_APPLY);
        Matrix_InsertZRotation_s(-zRot, MTXMODE_APPLY);
        Matrix_InsertXRotation_s(-xRot, MTXMODE_APPLY);
    } else if (limbIndex == 3) {
        rot->y += this->limb3Rot;
    } else if (limbIndex == 6) {
        rot->y += this->limb46Rot;
    } else if (limbIndex == 4) {
        rot->z += this->limb46Rot;
    } else if ((limbIndex == 5) || (limbIndex == 7)) {
        rot->z += this->limb57Rot;
    } else if (limbIndex == 8) {
        rot->z += this->limb8Rot;
    } else if (limbIndex == 9) {
        rot->y += (s16)(this->limb9Rot * Math_SinS(this->randBaseRotChange));
        rot->z += (s16)(this->limb9Rot * Math_CosS(this->randBaseRotChange));
    }
    return false;
}

void EnPoFusen_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* thisx) {
}

void EnPoFusen_TransformLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* thisx) {
}

void EnPoFusen_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    func_8012C28C(globalCtx->state.gfxCtx);
    SkelAnime_DrawTransformFlexOpa(globalCtx, this->anime.skeleton, this->anime.jointTable, this->anime.dListCount,
                                   EnPoFusen_OverrideLimbDraw, EnPoFusen_PostLimbDraw, EnPoFusen_TransformLimbDraw,
                                   &this->actor);
}
