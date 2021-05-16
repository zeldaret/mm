#include "z_bg_open_spot.h"

#define FLAGS 0x00000010

#define THIS ((BgOpenSpot*)thisx)

void BgOpenSpot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgOpenSpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgOpenSpot_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Open_Spot_InitVars = {
    ACTOR_BG_OPEN_SPOT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(BgOpenSpot),
    (ActorFunc)BgOpenSpot_Init,
    (ActorFunc)BgOpenSpot_Destroy,
    (ActorFunc)BgOpenSpot_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Spot/BgOpenSpot_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Spot/BgOpenSpot_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Spot/BgOpenSpot_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Open_Spot/func_80ACB2B0.s")
