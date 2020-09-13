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
    ACTORTYPE_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EffDust),
    (ActorFunc)EffDust_Init,
    (ActorFunc)EffDust_Destroy,
    (ActorFunc)EffDust_Update,
    (ActorFunc)EffDust_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_80918B40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/EffDust_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/EffDust_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_80918D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_80918FE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_80919230.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/EffDust_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_80919768.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/func_809199FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Eff_Dust_0x80918B40/EffDust_Draw.asm")
