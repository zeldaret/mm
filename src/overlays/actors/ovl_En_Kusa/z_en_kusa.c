#include "z_en_kusa.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa*)thisx)

void EnKusa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa_Update(Actor* thisx, GlobalContext* globalCtx);

void func_809358D8(EnKusa* this, GlobalContext* globalCtx);
void func_809359AC(EnKusa* this, GlobalContext* globalCtx);
void func_80935BBC(EnKusa* this, GlobalContext* globalCtx);
void func_80935D64(EnKusa* this, GlobalContext* globalCtx);
void func_809361A4(EnKusa* this, GlobalContext* globalCtx);
void func_80936220(EnKusa* this, GlobalContext* globalCtx);
void func_809362D8(EnKusa* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Kusa_InitVars = {
    ACTOR_EN_KUSA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnKusa),
    (ActorFunc)EnKusa_Init,
    (ActorFunc)EnKusa_Destroy,
    (ActorFunc)EnKusa_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809366E0 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x0580C71C, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 6, 44, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_8093670C = { 0, 12, 30, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80936754[] = {
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -3200, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -17000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_809366E0;
extern CollisionCheckInfoInit D_8093670C;
extern InitChainEntry D_80936754[];

extern UNK_TYPE D_060002E0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809349E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934AB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934F58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80934FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809350C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809350F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_8093517C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809351A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809354F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809355A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_8093561C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809358C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809358D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935988.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809359AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935BBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935CE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80935D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809361A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809361B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936220.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936290.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809362D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/EnKusa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_80936414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kusa/func_809365CC.s")
