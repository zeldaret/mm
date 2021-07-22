#include "z_en_kusa2.h"

#define FLAGS 0x00800010

#define THIS ((EnKusa2*)thisx)

void EnKusa2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKusa2_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Kusa2_InitVars = {
    ACTOR_EN_KUSA2,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(EnKusa2),
    (ActorFunc)EnKusa2_Init,
    (ActorFunc)EnKusa2_Destroy,
    (ActorFunc)EnKusa2_Update,
    (ActorFunc)EnKusa2_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A5EAC0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x0580C71C, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 6, 44, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A5EB50[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(minVelocityY, -17000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};


extern ColliderCylinderInit D_80A5EAC0;
extern InitChainEntry D_80A5EB50[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B160.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B334.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B3BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5B954.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BA58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BAFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BD14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BD94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BDB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BF38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BF84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5BFD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C0B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C104.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C2FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C410.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C70C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C7F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5C918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CAD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CAF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CB74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CCD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CD0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5CF44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D178.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/EnKusa2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/EnKusa2_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D5E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D5F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D618.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D62C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D6B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D754.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D794.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D7A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D7C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D964.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5D9C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5DC70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5DC98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5DE18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5DEB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E1D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E4BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E604.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/EnKusa2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E6F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E80C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/EnKusa2_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5E9B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Kusa2_0x80A5B160/func_80A5EA48.asm")
