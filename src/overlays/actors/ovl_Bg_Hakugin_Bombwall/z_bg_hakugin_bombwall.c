#include "z_bg_hakugin_bombwall.h"

#define FLAGS 0x00000000

#define THIS ((BgHakuginBombwall*)thisx)

void BgHakuginBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgHakuginBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Hakugin_Bombwall_InitVars = {
    ACTOR_BG_HAKUGIN_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_HAKUGIN_OBJ,
    sizeof(BgHakuginBombwall),
    (ActorFunc)BgHakuginBombwall_Init,
    (ActorFunc)BgHakuginBombwall_Destroy,
    (ActorFunc)BgHakuginBombwall_Update,
    (ActorFunc)BgHakuginBombwall_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ABCF80 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 80, 80, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ABD040[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80ABCF80;
extern InitChainEntry D_80ABD040[];

extern UNK_TYPE D_06009830;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABBFC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC58C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABC7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCB5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCCE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/func_80ABCE60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Hakugin_Bombwall/BgHakuginBombwall_Draw.s")
