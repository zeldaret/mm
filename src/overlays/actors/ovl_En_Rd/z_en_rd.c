#include "z_en_rd.h"

#define FLAGS 0x00000415

#define THIS ((EnRd*)thisx)

void EnRd_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRd_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rd_InitVars = {
    ACTOR_EN_RD,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRd),
    (ActorFunc)EnRd_Init,
    (ActorFunc)EnRd_Destroy,
    (ActorFunc)EnRd_Update,
    (ActorFunc)EnRd_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/EnRd_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/EnRd_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D41FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D43AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D45D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D47DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D49E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4A90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4B20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4CA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4E60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D4FE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D506C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D53C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D56E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D586C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D58CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5CCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5D88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D5F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6054.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D60B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6130.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D616C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6200.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6388.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D64D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D65BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D66A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6814.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6A94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/EnRd_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/func_808D6DFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rd/EnRd_Draw.s")
