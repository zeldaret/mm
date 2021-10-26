#include "z_en_goroiwa.h"

#define FLAGS 0x80000010

#define THIS ((EnGoroiwa*)thisx)

void EnGoroiwa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGoroiwa_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Goroiwa_InitVars = {
    ACTOR_EN_GOROIWA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(EnGoroiwa),
    (ActorFunc)EnGoroiwa_Init,
    (ActorFunc)EnGoroiwa_Destroy,
    (ActorFunc)EnGoroiwa_Update,
    (ActorFunc)EnGoroiwa_Draw,
};

// static ColliderJntSphElementInit sJntSphElementsInit[1] = {
static ColliderJntSphElementInit D_80942DC0[1] = {
    {
        { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x04 }, { 0x01C37BB6, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
        { 0, { { 0, 0, 0 }, 58 }, 100 },
    },
};

// static ColliderJntSphInit sJntSphInit = {
static ColliderJntSphInit D_80942DE4 = {
    { COLTYPE_METAL, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_JNTSPH, },
    1, D_80942DC0, // sJntSphElementsInit,
};

// sColChkInfoInit
static CollisionCheckInfoInit D_80942DF4 = { 0, 12, 60, MASS_HEAVY };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80942E78[] = {
    ICHAIN_F32_DIV1000(gravity, -900, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -26000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 160, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_STOP),
};

#endif

extern ColliderJntSphElementInit D_80942DC0[1];
extern ColliderJntSphInit D_80942DE4;
extern CollisionCheckInfoInit D_80942DF4;
extern InitChainEntry D_80942E78[];

extern UNK_TYPE D_060032E0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093E8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093E91C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093E938.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093E9B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EAD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EB58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EB74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EC50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093ECD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093ED80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EDB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EDD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EE64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EEBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EEDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093EF54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093F198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093F34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093F498.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093F5EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093F6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093FAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093FC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8093FC6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80940090.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80940588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80940A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80940E38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/EnGoroiwa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/EnGoroiwa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8094156C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_809419D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941E28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941EB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941F10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941F54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80941FA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80942084.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_809420F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_809421E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_8094220C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_809425CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80942604.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/EnGoroiwa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/func_80942B1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Goroiwa/EnGoroiwa_Draw.s")
