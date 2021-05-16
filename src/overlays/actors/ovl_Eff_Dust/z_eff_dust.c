#include "z_eff_dust.h"

#define FLAGS 0x00000030

#define THIS ((EffDust*)thisx)

void EffDust_Init(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Update(Actor* thisx, GlobalContext* globalCtx);
void EffDust_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Eff_Dust_InitVars = {
    ACTOR_EFF_DUST,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EffDust),
    (ActorFunc)EffDust_Init,
    (ActorFunc)EffDust_Destroy,
    (ActorFunc)EffDust_Update,
    (ActorFunc)EffDust_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_80918B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/EffDust_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/EffDust_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_80918D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_80918FE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_80919230.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/EffDust_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_80919768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/func_809199FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Eff_Dust/EffDust_Draw.s")
