/*
 * File: z_en_bom_chu.c
 * Overlay: ovl_En_Bom_Chu
 * Description: Bombchus
 */

#include "z_en_bom_chu.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS 0x00000010

#define THIS ((EnBomChu*)thisx)

void EnBomChu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808F7868(EnBomChu* this, GlobalContext* globalCtx);
void func_808F7A84(EnBomChu* this, GlobalContext* globalCtx);
void func_808F7FA0(EnBomChu* this, GlobalContext* globalCtx);
void func_808F79D4(EnBomChu* this);
void func_808F7E74(EnBomChu* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bom_Chu_InitVars = {
    ACTOR_EN_BOM_CHU,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBomChu),
    (ActorFunc)EnBomChu_Init,
    (ActorFunc)EnBomChu_Destroy,
    (ActorFunc)EnBomChu_Update,
    (ActorFunc)EnBomChu_Draw,
};

// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_808F88E0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_1 | OC1_TYPE_2, OC2_TYPE_2, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 1, { { 0, 0, 0 }, 13 }, 100 },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808F890C[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

#endif

extern ColliderSphereInit D_808F88E0;
extern InitChainEntry D_808F890C[];
extern s16 D_808F8908;
extern s16 D_808F890A;
extern EffectBlureInit1 D_808F8914;

void EnBomChu_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBomChu* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_808F890C);
    Collider_InitAndSetSphere(globalCtx, &this->unk_188, &this->actor, &D_808F88E0);
    this->unk_188.dim.worldSphere.radius = D_808F8908;
    Effect_Add(globalCtx, &this->unk_180, 2, 0, 0, &D_808F8914);
    Effect_Add(globalCtx, &this->unk_184, 2, 0, 0, &D_808F8914);
    this->unk_14A = 0x78;
    this->actor.room = -1;
    this->unk_148 = 1;
    this->unk_174 = 0.0f;
    this->actionFunc = func_808F7868;
}

void EnBomChu_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBomChu* this = THIS;

    Effect_Destroy(globalCtx, this->unk_180);
    Effect_Destroy(globalCtx, this->unk_184);
    Collider_DestroySphere(globalCtx, &this->unk_188);
}

s32 func_808F75D0(EnBomChu* this, CollisionPoly* floorPoly, GlobalContext* globalCtx) {
    Vec3f normal;
    Vec3f vec;
    f32 angle;
    f32 magnitude;
    f32 normDotUp;

    this->actor.floorPoly = floorPoly;

    if (floorPoly != NULL) {
        normal.x = COLPOLY_GET_NORMAL(floorPoly->normal.x);
        normal.y = COLPOLY_GET_NORMAL(floorPoly->normal.y);
        normal.z = COLPOLY_GET_NORMAL(floorPoly->normal.z);
    } else {
        func_808F7E74(this, globalCtx);
        return 0;
    }

    normDotUp = DOTXYZ(normal, this->unk_158);

    if (fabsf(normDotUp) >= 0.999f) {
        return 0;
    }

    angle = func_80086C48(normDotUp);
    if (angle < 0.001f) {
        return 0;
    }

    Math3D_CrossProduct(&this->unk_158, &normal, &vec);

    magnitude = Math3D_Vec3fMagnitude(&vec);

    if (magnitude < 0.001f) {
        func_808F7E74(this, globalCtx);
        return 0;
    }

    Math_Vec3f_Scale(&vec, 1.0f / magnitude);
    Matrix_InsertRotationAroundUnitVector_f(angle, &vec, 0);
    Matrix_MultiplyVector3fByState(&this->unk_164, &vec);
    Math_Vec3f_Copy(&this->unk_164, &vec);
    Math3D_CrossProduct(&this->unk_164, &normal, &this->unk_14C);

    magnitude = Math3D_Vec3fMagnitude(&this->unk_14C);
    if (magnitude < 0.001f) {
        func_808F7E74(this, globalCtx);
        return 0;
    }

    Math_Vec3f_Scale(&this->unk_14C, 1.0f / magnitude);
    Math_Vec3f_Copy(&this->unk_158, &normal);
    return 1;
}

void func_808F77E4(EnBomChu* this) {
    MtxF mf;

    mf.xx = this->unk_164.x;
    mf.xy = this->unk_164.y;
    mf.xz = this->unk_164.z;
    mf.yx = this->unk_158.x;
    mf.yy = this->unk_158.y;
    mf.yz = this->unk_158.z;
    mf.zx = this->unk_14C.x;
    mf.zy = this->unk_14C.y;
    mf.zz = this->unk_14C.z;
    func_8018219C(&mf, &this->actor.world.rot, 0);
    this->actor.world.rot.x = -this->actor.world.rot.x;
}

void func_808F7868(EnBomChu* this, GlobalContext* globalCtx) {
    Player* player;

    if (this->unk_14A == 0) {
        func_808F7E74(this, globalCtx);
    } else if (Actor_HasNoParent(&this->actor, globalCtx)) {
        player = GET_PLAYER(globalCtx);
        Math_Vec3f_Copy(&this->actor.world.pos, &player->actor.world.pos);
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
        this->actor.shape.rot.y = player->actor.shape.rot.y;
        this->actor.flags |= ACTOR_FLAG_1;
        func_800B8EF4(globalCtx, &this->actor);
        this->unk_149 = 1;
        this->actor.speedXZ = 8.0f;
        this->unk_17C = 8.0f;
        func_808F79D4(this);
    }
}

s32 func_808F7944(GlobalContext* globalCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult, CollisionPoly** poly,
                  s32* bgId) {
    if ((BgCheck_EntityLineTest1(&globalCtx->colCtx, posA, posB, posResult, poly, 1, 1, 1, 1, bgId)) &&
        ((func_800C9A4C(&globalCtx->colCtx, *poly, *bgId) & 0x30) == 0)) {
        return 1;
    }

    return 0;
}

void func_808F79D4(EnBomChu* this) {
    func_800BE3D0(&this->actor, this->actor.shape.rot.y, &this->actor.shape.rot);
    Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_GetStateTranslationAndScaledY(1.0f, &this->unk_158);
    Matrix_GetStateTranslationAndScaledZ(1.0f, &this->unk_14C);
    Matrix_GetStateTranslationAndScaledX(1.0f, &this->unk_164);
    this->actor.world.rot.x = -this->actor.shape.rot.x;
    this->actor.world.rot.y = this->actor.shape.rot.y;
    this->actor.world.rot.z = this->actor.shape.rot.z;
    this->actionFunc = func_808F7A84;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7A84.s")

void func_808F7E74(EnBomChu* this, GlobalContext* globalCtx) {
    EnBom* bomb;
    s32 i;

    bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                               this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);

    this->unk_148 = 1;
    this->unk_149 = 0;

    if (bomb != NULL) {
        bomb->timer = 0;
    }

    this->unk_14A = 1;
    this->actor.speedXZ = 0.0f;

    if (this->actor.depthInWater > 0.0f) {
        for (i = 0; i < 40; i++) {
            EffectSsBubble_Spawn(globalCtx, &this->actor.world.pos, 1.0f, 5.0f, 30.0f, 0.25f);
        }
    }

    this->actor.draw = NULL;
    this->actionFunc = func_808F7FA0;
}

void func_808F7FA0(EnBomChu* this, GlobalContext* globalCtx) {
    if (this->unk_14A == 0) {
        Actor_MarkForDeath(&this->actor);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F8080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F818C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Draw.s")
