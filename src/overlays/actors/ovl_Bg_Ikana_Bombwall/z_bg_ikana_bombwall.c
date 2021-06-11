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
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/BgIkanaBombwall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/BgIkanaBombwall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4E44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4EAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4F2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4F9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4FF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD503C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD5118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD5134.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/BgIkanaBombwall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/BgIkanaBombwall_Draw.s")
