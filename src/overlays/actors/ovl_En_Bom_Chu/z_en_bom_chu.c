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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F75D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F77E4.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7944.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F8080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F818C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Draw.s")
