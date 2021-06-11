#include "z_en_racedog.h"

#define FLAGS 0x80000010

#define THIS ((EnRacedog*)thisx)

void EnRacedog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRacedog_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Racedog_InitVars = {
    ACTOR_EN_RACEDOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DOG,
    sizeof(EnRacedog),
    (ActorFunc)EnRacedog_Init,
    (ActorFunc)EnRacedog_Destroy,
    (ActorFunc)EnRacedog_Update,
    (ActorFunc)EnRacedog_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24630.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B246F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2478C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B248B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24C14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24CB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B24F08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B251EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B252F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2538C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25448.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B255AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B256BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B2583C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B258D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25A74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/func_80B25A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Racedog/EnRacedog_Draw.s")
