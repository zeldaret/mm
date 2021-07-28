#include "z_bg_haka_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgHakaBombwall*)thisx)

void BgHakaBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakaBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakaBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakaBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Haka_Bombwall_InitVars = {
    ACTOR_BG_HAKA_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKA_OBJ,
    sizeof(BgHakaBombwall),
    (ActorFunc)BgHakaBombwall_Init,
    (ActorFunc)BgHakaBombwall_Destroy,
    (ActorFunc)BgHakaBombwall_Update,
    (ActorFunc)BgHakaBombwall_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD64A0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 80, 80, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BD64D4[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80BD64A0;
extern InitChainEntry D_80BD64D4[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD5E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD5E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD62D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD6314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD63B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/func_80BD63D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Haka_Bombwall/BgHakaBombwall_Draw.s")
