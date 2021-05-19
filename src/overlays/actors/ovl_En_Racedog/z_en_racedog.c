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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B24630.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B246F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B2478C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B248B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/EnRacedog_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/EnRacedog_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B24C14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B24CB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B24E14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B24F08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B251EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B252F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B2538C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B25448.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B25490.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B255AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B256BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/EnRacedog_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B2583C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B258D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B25A74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/func_80B25A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Racedog_0x80B24630/EnRacedog_Draw.asm")
