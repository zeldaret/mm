#include "z_en_syateki_wf.h"

#define FLAGS 0x08000030

#define THIS ((EnSyatekiWf*)thisx)

void EnSyatekiWf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnSyatekiWf_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A20284(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20320(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A203DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A206DC(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A2075C(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A20800(EnSyatekiWf* this, GlobalContext* globalCtx);
void func_80A208F8(EnSyatekiWf* this, GlobalContext* globalCtx);

#if 0
// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A20E74 = {
    { COLTYPE_HIT5, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 40, 60, 0, { 0, 0, 0 } },
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80A20E50[1] = {
    {
        { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
        { 17, { { 800, 0, 0 }, 25 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80A20EA0 = {
    { COLTYPE_HIT5, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_JNTSPH, },
    1, D_80A20E50, // sJntSphElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A20EB0 = {
    { COLTYPE_HIT5, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 15, 20, -15, { 0, 0, 0 } },
};

const ActorInit En_Syateki_Wf_InitVars = {
    ACTOR_EN_SYATEKI_WF,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WF,
    sizeof(EnSyatekiWf),
    (ActorFunc)EnSyatekiWf_Init,
    (ActorFunc)EnSyatekiWf_Destroy,
    (ActorFunc)EnSyatekiWf_Update,
    (ActorFunc)EnSyatekiWf_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A20FBC[] = {
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A20E74;
extern ColliderJntSphElementInit D_80A20E50[1];
extern ColliderJntSphInit D_80A20EA0;
extern ColliderCylinderInit D_80A20EB0;
extern InitChainEntry D_80A20FBC[];

extern UNK_TYPE D_0600A3CC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A200E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A201CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2030C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20378.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A203DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20670.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A206DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2075C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A2079C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20800.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A208F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20CF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/func_80A20D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Syateki_Wf/EnSyatekiWf_Draw.s")
