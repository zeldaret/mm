#include "z_bg_spout_fire.h"

#define FLAGS 0x00000000

#define THIS ((BgSpoutFire*)thisx)

void BgSpoutFire_Init(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgSpoutFire_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Spout_Fire_InitVars = {
    ACTOR_BG_SPOUT_FIRE,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgSpoutFire),
    (ActorFunc)BgSpoutFire_Init,
    (ActorFunc)BgSpoutFire_Destroy,
    (ActorFunc)BgSpoutFire_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/BgSpoutFire_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/BgSpoutFire_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60C24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A60E08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/BgSpoutFire_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Spout_Fire/func_80A61040.s")
