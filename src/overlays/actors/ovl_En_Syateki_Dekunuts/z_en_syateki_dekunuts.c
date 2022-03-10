/*
 * File: z_en_syateki_dekunuts.c
 * Overlay: ovl_En_Syateki_Dekunuts
 * Description: Shooting Gallery Deku Scrub
 */

#include "z_en_syateki_dekunuts.h"
#include "overlays/actors/ovl_En_Syateki_Man/z_en_syateki_man.h"
#include "objects/object_dekunuts/object_dekunuts.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_8000000)

#define THIS ((EnSyatekiDekunuts*)thisx)

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A2BF18(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C0F8(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C168(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C208(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C2E0(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C3F0(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C48C(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2C5DC(EnSyatekiDekunuts* this, GlobalContext* globalCtx);
void func_80A2BE54(EnSyatekiDekunuts* this);

extern UNK_TYPE D_06001E50;
extern SkeletonHeader D_06002468;
extern AnimationHeader D_06002A5C;

const ActorInit En_Syateki_Dekunuts_InitVars = {
    ACTOR_EN_SYATEKI_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnSyatekiDekunuts),
    (ActorFunc)EnSyatekiDekunuts_Init,
    (ActorFunc)EnSyatekiDekunuts_Destroy,
    (ActorFunc)EnSyatekiDekunuts_Update,
    (ActorFunc)EnSyatekiDekunuts_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A2CAB0 = {
    {
        COLTYPE_HIT6,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 48, 80, 0, { 0, 0, 0 } },
};

static Cylinder16 D_80A2CADC[] = { { 24, 40, 0, { 0, 0, 0 } } };

static AnimationInfo D_80A2CAE8[] = {
    { &object_dekunuts_Anim_003180, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002A5C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_00326C, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &object_dekunuts_Anim_002FA4, 1.0f, 0.0f, 0.0f, ANIMMODE_LOOP, -1.0f },
    { &object_dekunuts_Anim_00259C, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002BD4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
    { &object_dekunuts_Anim_002DD4, 1.0f, 0.0f, 0.0f, ANIMMODE_ONCE, -1.0f },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A2CB90[] = {
    ICHAIN_S8(hintId, 77, ICHAIN_CONTINUE),
    ICHAIN_F32(gravity, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2600, ICHAIN_STOP),
};

void EnSyatekiDekunuts_Init(Actor* thisx, GlobalContext* globalCtx2) {
    static s32 D_80A2CB9C = 1;
    EnSyatekiDekunuts* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    s32 phi_v0;
    Path* path;
    EnSyatekiMan* syatekiMan = (EnSyatekiMan*)this->actor.parent;
    s32 temp;

    path = syatekiMan->path;
    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->actor, &D_80A2CAB0);

    if (EN_SYATEKI_DEKUNUTS_GET_PARAM_F(&this->actor) == 1) {
        Actor_SetScale(&this->actor, 0.01f);
        this->collider.dim = D_80A2CADC[0];
        phi_v0 = 3;
    } else {
        Actor_SetScale(&this->actor, 0.02f);
        phi_v0 = 1;
    }

    while (path->unk2 != phi_v0) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    for (temp = 0; temp < EN_SYATEKI_DEKUNUTS_GET_PARAM_FF00(&this->actor); temp++) {
        path = &globalCtx->setupPathList[path->unk1];
    }

    if (D_80A2CB9C == 1) {
        this->unk_1EC = 1;
        D_80A2CB9C = 0;
    } else {
        this->unk_1EC = 0;
    }

    Actor_ProcessInitChain(&this->actor, D_80A2CB90);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 35.0f);
    SkelAnime_Init(globalCtx, &this->skelAnime, &D_06002468, &D_06002A5C, this->jointTable, this->morphTable, 10);
    if (path == NULL) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_1E4 = Lib_SegmentedToVirtual(path->points);
    this->unk_1E8 = EN_SYATEKI_DEKUNUTS_GET_PARAM_F0(&this->actor);
    this->unk_1EA = path->count;
    this->unk_1D8 = 0;
    this->unk_1DC = 0;
    this->unk_1DA = 0;
    func_80A2BE54(this);
}

static Vec3f D_80A2CBA0 = { 0.0f, 20.0f, 0.0f };
static Vec3f D_80A2CBAC = { 0.0f, 0.0f, 0.0f };
static Color_RGBA8 D_80A2CBB8 = { 255, 255, 255, 255 };
static Color_RGBA8 D_80A2CBBC = { 150, 150, 150, 0 };

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2BFC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C0F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C208.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C3AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C3F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C48C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C5DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/func_80A2C8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Dekunuts/EnSyatekiDekunuts_Draw.s")
