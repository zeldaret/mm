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

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863870.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086387C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863950.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808639B0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863A10.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863AAC.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863B4C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863C08.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863C6C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863D28.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863D60.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863DC8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863E48.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863EC8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863F94.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864034.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086406C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808640A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864108.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864168.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864210.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086425C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808642D4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864320.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086436C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808643B8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086444C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808644A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864558.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808645A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864658.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646A4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646E4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646F4.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086472C.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864744.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864760.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864774.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808648F8.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808649C8.asm")
