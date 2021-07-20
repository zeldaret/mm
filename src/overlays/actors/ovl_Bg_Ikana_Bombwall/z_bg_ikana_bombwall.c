#include "z_bg_ikana_bombwall.h"

#define FLAGS 0x10000000

#define THIS ((BgIkanaBombwall*)thisx)

void BgIkanaBombwall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBombwall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBombwall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaBombwall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Bg_Ikana_Bombwall_InitVars = {
    ACTOR_BG_IKANA_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaBombwall),
    (ActorFunc)BgIkanaBombwall_Init,
    (ActorFunc)BgIkanaBombwall_Destroy,
    (ActorFunc)BgIkanaBombwall_Update,
    (ActorFunc)BgIkanaBombwall_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD5270 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 80, 80, 0, { 0, 0, 0 } },
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD529C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000008, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 50, 20, 0, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80BD52D0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4720.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4A14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/BgIkanaBombwall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/BgIkanaBombwall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4E44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4EAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4F2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4F88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4F9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD4FF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD503C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD5118.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/func_80BD5134.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/BgIkanaBombwall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall_0x80BD4720/BgIkanaBombwall_Draw.asm")
