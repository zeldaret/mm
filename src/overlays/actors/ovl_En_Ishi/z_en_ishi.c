#include "z_en_ishi.h"

#define FLAGS 0x00800010

#define THIS ((EnIshi*)thisx)

void EnIshi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_Update(Actor* thisx, GlobalContext* globalCtx);

void func_8095E5C0(EnIshi* this, GlobalContext* globalCtx);
void func_8095E660(EnIshi* this, GlobalContext* globalCtx);
void func_8095E95C(EnIshi* this, GlobalContext* globalCtx);
void func_8095EBDC(EnIshi* this, GlobalContext* globalCtx);
void func_8095F0A4(EnIshi* this, GlobalContext* globalCtx);
void func_8095F194(EnIshi* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ishi_InitVars = {
    ACTOR_EN_ISHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnIshi),
    (ActorFunc)EnIshi_Init,
    (ActorFunc)EnIshi_Destroy,
    (ActorFunc)EnIshi_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8095F6EC = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x01C37FBE, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 10, 18, -2, { 0, 0, 0 } },
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8095F718 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_PLAYER, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00400000, 0x00, 0x02 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 55, 70, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_8095F744 = { 0, 12, 60, MASS_IMMOVABLE };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8095F784[] = {
    ICHAIN_F32_DIV1000(gravity, -1200, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_8095F798[] = {
    ICHAIN_F32_DIV1000(gravity, -2500, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_8095F6EC;
extern ColliderCylinderInit D_8095F718;
extern CollisionCheckInfoInit D_8095F744;
extern InitChainEntry D_8095F784[];
extern InitChainEntry D_8095F798[];

extern UNK_TYPE D_060009B0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DE9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E2B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E64C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095EA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F36C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F654.s")
