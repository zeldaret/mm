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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_RD,
    sizeof(EnRd),
    (ActorFunc)EnRd_Init,
    (ActorFunc)EnRd_Destroy,
    (ActorFunc)EnRd_Update,
    (ActorFunc)EnRd_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/EnRd_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/EnRd_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D41FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D43AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D45D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D47DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4868.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D49E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4A90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4B20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4CA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4DC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4E60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D4FE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D506C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D53C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5660.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D56E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D586C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D58CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5CCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5D88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5DF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5E98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D5F18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6008.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6054.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D60B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6130.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D616C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6200.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6388.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D64D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D65BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D66A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6814.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6A94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6B64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/EnRd_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/func_808D6DFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Rd_0x808D3E20/EnRd_Draw.asm")
