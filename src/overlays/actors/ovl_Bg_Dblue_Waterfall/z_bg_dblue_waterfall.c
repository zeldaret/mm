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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_DBLUE_OBJECT,
    sizeof(BgDblueWaterfall),
    (ActorFunc)BgDblueWaterfall_Init,
    (ActorFunc)BgDblueWaterfall_Destroy,
    (ActorFunc)BgDblueWaterfall_Update,
    (ActorFunc)BgDblueWaterfall_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83C80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83D94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83E1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B83EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B841A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84348.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84610.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B8484C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84AD4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84AEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84B9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84EF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/func_80B84F20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Bg_Dblue_Waterfall_0x80B83C80/BgDblueWaterfall_Draw.asm")
