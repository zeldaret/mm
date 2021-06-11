#include "z_en_rr.h"

#define FLAGS 0x00000405

#define THIS ((EnRr*)thisx)

void EnRr_Init(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Update(Actor* thisx, GlobalContext* globalCtx);
void EnRr_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Rr_InitVars = {
    ACTOR_EN_RR,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_RR,
    sizeof(EnRr),
    (ActorFunc)EnRr_Init,
    (ActorFunc)EnRr_Destroy,
    (ActorFunc)EnRr_Update,
    (ActorFunc)EnRr_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA01C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA19C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA238.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA3F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA4F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA6B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA7AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA910.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FA9CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAA94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAC80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAD1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAE50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FAF94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB1C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB2C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB42C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/func_808FB794.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Rr/EnRr_Draw.s")
