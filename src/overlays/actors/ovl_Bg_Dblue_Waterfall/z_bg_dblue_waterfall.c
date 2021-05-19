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
