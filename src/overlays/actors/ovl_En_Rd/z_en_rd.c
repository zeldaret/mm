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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4190.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D41FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4260.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D43AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D45D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D47DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4868.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D49E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4A90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4B20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4CA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4DC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4E60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D4FE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D506C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D53C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D56E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D586C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D58CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5C54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5CCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5D88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5E98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D5F18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6008.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6054.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D60B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6130.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D616C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6200.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6388.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D64D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D65BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D66A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6814.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6A94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6B64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/func_808D6DFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Rd_0x808D3E20/EnRd_Draw.asm")
