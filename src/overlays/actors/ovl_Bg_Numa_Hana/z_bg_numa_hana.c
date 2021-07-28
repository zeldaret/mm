#include "z_bg_numa_hana.h"

#define FLAGS 0x00000410

#define THIS ((BgNumaHana*)thisx)

void BgNumaHana_Init(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Update(Actor* thisx, GlobalContext* globalCtx);
void BgNumaHana_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Numa_Hana_InitVars = {
    ACTOR_BG_NUMA_HANA,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_NUMA_OBJ,
    sizeof(BgNumaHana),
    (ActorFunc)BgNumaHana_Init,
    (ActorFunc)BgNumaHana_Destroy,
    (ActorFunc)BgNumaHana_Update,
    (ActorFunc)BgNumaHana_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A1B260 = {
    { COLTYPE_METAL, AT_NONE, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0x00000000, 0x00, 0x00 }, { 0x01CBFBB6, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON | BUMP_HOOKABLE, OCELEM_ON, },
    { 18, 16, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A1B2A8[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 600, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80A1B260;
extern InitChainEntry D_80A1B2A8[];

extern UNK_TYPE D_06009FE0;
extern UNK_TYPE D_0600B928;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A56C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1A750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AB00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ABD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ABF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ACCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1ACE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/func_80A1AE1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Numa_Hana/BgNumaHana_Draw.s")
