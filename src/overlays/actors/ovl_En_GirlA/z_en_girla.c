#include "z_en_girla.h"

#define FLAGS 0x00000019

#define THIS ((EnGirlA*)thisx)

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_GirlA_InitVars = {
    ACTOR_EN_GIRLA,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGirlA),
    (ActorFunc)EnGirlA_Init,
    (ActorFunc)EnGirlA_Destroy,
    (ActorFunc)EnGirlA_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086387C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/EnGirlA_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/EnGirlA_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808639B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863A10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863AAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863B4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863C08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863D28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863E48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80863F94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864034.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086406C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808640A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086425C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808642D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086436C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808643B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086444C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808644A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864558.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808645A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808646A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808646E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808646F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_8086472C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_80864774.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808648F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/EnGirlA_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_GirlA/func_808649C8.s")
