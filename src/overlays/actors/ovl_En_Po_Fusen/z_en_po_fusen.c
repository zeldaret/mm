#include "z_en_po_fusen.h"
#include "overlays/actors/ovl_En_Ma4/z_en_ma4.h"

#define FLAGS 0x80100030

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
                               struct Actor* actor);

extern AnimationHeader D_06000040;
extern FlexSkeletonHeader D_060024F0;

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
    0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF1, 0xF1, 0xF1, 0xF1, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

void EnPoFusen_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    f32 heightTemp;

    this->actor.scale.x = this->actor.scale.y = this->actor.scale.z = 0.00700000021607;
    this->actor.targetMode = 6;
    this->actor.colChkInfo.damageTable = &sDamageTable;

    Collider_InitSphere(globalCtx, &this->collider);
    Collider_SetSphere(globalCtx, &this->collider, &this->actor, &sSphereInit);

    if (0) {}
    this->collider.dim.worldSphere.radius = 40;
    SkelAnime_InitSV(globalCtx, &this->anime, &D_060024F0, &D_06000040, this->limbDrawTbl, this->transitionDrawTbl, 10);
    ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 25.0f);
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
    struct Actor* actorPtr;

    actorPtr = globalCtx->actorCtx.actorList[ACTORCAT_NPC].first;
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
    if ((u32)this->actionFunc == (u32)EnPoFusen_IdleFuse) {
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

void EnPoFusen_IncrementMalonPop(EnPoFusen* this) {
    Actor* parent = this->actor.parent;
    EnMa4* romani;

    if ((parent != 0) && (parent->id == ACTOR_EN_MA4)) {
        romani = (EnMa4*)parent;
        romani->unk338++;
    }

    this->actor.draw = NULL;
    this->actionFunc = EnPoFusen_Pop;
}

void EnPoFusen_Pop(EnPoFusen* this, GlobalContext* globalCtx) {
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, this->actor.world.pos.x,
                this->actor.world.pos.y + 20.0f, this->actor.world.pos.z, 255, 255, 200, 2);
    Audio_PlayActorSound2(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
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
        EnPoFusen_IncrementMalonPop(this);
    }
}

void EnPoFusen_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    this->actionFunc(this, globalCtx);
    if (EnPoFusen_CheckCollision(this, globalCtx) != 0) {
        EnPoFusen_IncrementMalonPop(this);
    }
}

s32 EnPoFusen_OverrideLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                               struct Actor* actor) {
    EnPoFusen* this = (EnPoFusen*)actor;
    f32 zScale;
    f32 yScale;
    f32 xScale;
    s16 pad;
    s16 zRot;
    s16 pad2;
    s16 xRot;

    if (limbIndex == 2) {
        zScale = (Math_CosS(this->randScaleChange) * 0.0799999982119f) + 1.0f;
        xScale = zScale;
        if (!zScale) {}
        yScale = (Math_SinS(this->randScaleChange) * 0.0799999982119f) + 1.0f;
        yScale = yScale * yScale;
        xRot = ((Math_SinS(this->randXZRotChange) * 2730.0f));
        zRot = ((Math_CosS(this->randXZRotChange) * 2730.0f));
        SysMatrix_InsertRotation(xRot, 0, zRot, 1);
        Matrix_Scale(xScale, yScale, zScale, 1);
        SysMatrix_InsertZRotation_s(-zRot, 1);
        SysMatrix_InsertXRotation_s(-xRot, 1);
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
    return 0;
}

void EnPoFusen_PostLimbDraw(GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot, Actor* actor) {
}

void EnPoFusen_UnkActorDraw(GlobalContext* globalCtx, s32 limbIndex, Actor* actor) {
}

void EnPoFusen_Draw(Actor* thisx, GlobalContext* globalCtx) {
    EnPoFusen* this = THIS;
    func_8012C28C(globalCtx->state.gfxCtx);
    func_801343C0(globalCtx, this->anime.skeleton, this->anime.limbDrawTbl, this->anime.dListCount,
                  EnPoFusen_OverrideLimbDraw, EnPoFusen_PostLimbDraw, EnPoFusen_UnkActorDraw, &this->actor);
}
