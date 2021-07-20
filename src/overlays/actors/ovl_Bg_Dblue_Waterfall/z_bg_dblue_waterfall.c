#include "z_bg_dblue_waterfall.h"

#define FLAGS 0x00000010

#define THIS ((BgDblueWaterfall*)thisx)

void BgDblueWaterfall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDblueWaterfall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDblueWaterfall_Update(Actor* thisx, GlobalContext* globalCtx);
void BgDblueWaterfall_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Bg_Dblue_Waterfall_InitVars = {
    ACTOR_BG_DBLUE_WATERFALL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueWaterfall),
    (ActorFunc)BgDblueWaterfall_Init,
    (ActorFunc)BgDblueWaterfall_Destroy,
    (ActorFunc)BgDblueWaterfall_Update,
    (ActorFunc)BgDblueWaterfall_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B85370 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00CBFBB0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 50, 740, -740, { 0, 0, 0 } },
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B853A8[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83C80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D04.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83E1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B841A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84610.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B8484C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84AD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84AEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84B9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84EF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84F20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Draw.asm")
