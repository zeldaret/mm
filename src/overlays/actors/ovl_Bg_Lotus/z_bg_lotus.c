#include "z_bg_lotus.h"
#include "objects/object_lotus/object_lotus.h"

#define FLAGS 0x00000000

#define THIS ((BgLotus*)thisx)

void BgLotus_Init(Actor* thisx, PlayState* play);
void BgLotus_Destroy(Actor* thisx, PlayState* play);
void BgLotus_Update(Actor* thisx, PlayState* play);
void BgLotus_Draw(Actor* thisx, PlayState* play);

/*
const ActorInit Bg_Lotus_InitVars = {
    ACTOR_BG_LOTUS,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_LOTUS,
    sizeof(BgLotus),
    (ActorFunc)BgLotus_Init,
    (ActorFunc)BgLotus_Destroy,
    (ActorFunc)BgLotus_Update,
    (ActorFunc)BgLotus_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/BgLotus_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/BgLotus_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/func_80AD6830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/func_80AD68DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/func_80AD6A88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/func_80AD6B68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/BgLotus_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Lotus/BgLotus_Draw.s")
