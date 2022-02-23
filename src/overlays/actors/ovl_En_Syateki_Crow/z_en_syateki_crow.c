/*
 * File: z_en_syateki_crow.c
 * Overlay: ovl_En_Syateki_Crow
 * Description: Shooting Gallery Guay
 */

#include "z_en_syateki_crow.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiCrow*)thisx)

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiCrow_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_809CA5D4(EnSyatekiCrow* this);
void func_809CA67C(EnSyatekiCrow* this, GlobalContext* globalCtx);
void func_809CA71C(EnSyatekiCrow* this);
void func_809CA840(EnSyatekiCrow* this, GlobalContext* globalCtx);
void func_809CA8E4(EnSyatekiCrow* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Syateki_Crow_InitVars = {
    ACTOR_EN_SYATEKI_CROW,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_CROW,
    sizeof(EnSyatekiCrow),
    (ActorFunc)EnSyatekiCrow_Init,
    (ActorFunc)EnSyatekiCrow_Destroy,
    (ActorFunc)EnSyatekiCrow_Update,
    (ActorFunc)EnSyatekiCrow_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_809CB07C[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 1, { { 0, 60, 0 }, 50 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_809CB0A0 = {
    { COLTYPE_HIT3, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_809CB07C, // sJntSphElementsInit,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809CB0B0[] = {
    ICHAIN_F32(uncullZoneScale, 3000, ICHAIN_CONTINUE),
    ICHAIN_S8(hintId, 88, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -500, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_809CB07C[1];
extern ColliderJntSphInit D_809CB0A0;
extern InitChainEntry D_809CB0B0[];

extern FlexSkeletonHeader D_060010C0;
extern AnimationHeader D_060000F0;

void EnSyatekiCrow_Init(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnSyatekiCrow* this = THIS;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 temp;

    path = syatekiMan->path;
    while (path->unk2 != 0) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    temp = 0;
    while (temp < EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor)) {
        temp++;
        path = &globalCtx->setupPathList[path->unk1];
    }

    Actor_ProcessInitChain(&this->actor, D_809CB0B0);
    SkelAnime_InitFlex(globalCtx, &this->skelAnime, &D_060010C0, &D_060000F0, this->jointTable, this->morphTable, 9);
    Collider_InitJntSph(globalCtx, &this->unk_23C);
    Collider_SetJntSph(globalCtx, &this->unk_23C, &this->actor, &D_809CB0A0, &this->unk_25C);
    this->unk_23C.elements->dim.worldSphere.radius = D_809CB0A0.elements[0].dim.modelSphere.radius;
    ActorShape_Init(&this->actor.shape, 2000.0f, ActorShadow_DrawCircle, 20.0f);

    if ((path == NULL) || (EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor) >= 0x80)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_1C8 = Lib_SegmentedToVirtual(path->points);
    this->unk_1CC = 1;
    this->unk_1CE = path->count;
    this->unk_1C4 = 0x14;
    this->unk_1BC = 0;
    func_809CA5D4(this);
}

void EnSyatekiCrow_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnSyatekiCrow* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->unk_23C);
}

void func_809CA5D4(EnSyatekiCrow* this) {
    Actor_SetScale(&this->actor, 0.03f);
    this->actor.speedXZ = 0.0f;
    this->actor.gravity = 0.0f;
    this->actor.world = this->actor.home;
    this->actor.prevPos = this->actor.home.pos;
    this->actor.shape.rot = this->actor.world.rot;
    this->unk_1CC = 1;
    this->actor.draw = NULL;
    this->actionFunc = func_809CA67C;
}

void func_809CA67C(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;

    if ((syatekiMan->unk_26A == 1) && (this->unk_1C2 == 1) &&
        (syatekiMan->unk_274 & (1 << EN_SYATEKI_CROW_GET_PARAM_FF00(&this->actor)))) {
        func_809CA71C(this);
    } else if (syatekiMan->unk_26A != 1) {
        this->unk_1C2 = 1;
    }

    if ((syatekiMan->unk_274 == 0) && (syatekiMan->unk_274 == 0)) {
        this->unk_1C2 = 1;
    }
}

void func_809CA71C(EnSyatekiCrow* this) {
    Vec3f sp24;
    s16 temp;

    this->actor.world.pos.x = this->unk_1C8[0].x;
    this->actor.world.pos.y = this->unk_1C8[0].y;
    this->actor.world.pos.z = this->unk_1C8[0].z;
    sp24.x = this->unk_1C8[this->unk_1CC].x;
    sp24.y = this->unk_1C8[this->unk_1CC].y;
    sp24.z = this->unk_1C8[this->unk_1CC].z;
    temp = Math_Vec3f_Yaw(&this->actor.world.pos, &sp24);
    this->actor.world.rot.y = temp;
    this->actor.shape.rot.y = temp;
    temp = Math_Vec3f_Pitch(&this->actor.world.pos, &sp24);
    this->actor.shape.rot.x = temp;
    this->actor.world.rot.x = temp;
    this->actor.draw = EnSyatekiCrow_Draw;
    this->actionFunc = func_809CA840;
}

void func_809CA840(EnSyatekiCrow* this, GlobalContext* globalCtx) {
    if (((EN_SYATEKI_CROW_GET_PARAM_F(&this->actor) * 20) + 20) < this->unk_1BC) {
        Actor_PlaySfxAtPos(this->actor.parent, NA_SE_EN_KAICHO_CRY);
        this->unk_1BC = 0;
        this->actor.speedXZ = EN_SYATEKI_CROW_GET_PARAM_F0(&this->actor) + 6.0f;
        this->actor.gravity = -0.5f;
        this->actionFunc = func_809CA8E4;
    } else {
        this->unk_1BC++;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CA8E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAAF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CABC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CACD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/func_809CAF2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Crow/EnSyatekiCrow_Draw.s")
