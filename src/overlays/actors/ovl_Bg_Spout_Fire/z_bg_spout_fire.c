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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60C24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60C94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A60E08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/BgSpoutFire_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Spout_Fire_0x80A60B20/func_80A61040.asm")
