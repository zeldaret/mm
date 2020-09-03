#include "z_en_girla.h"

#define FLAGS 0x00000019

#define THIS ((EnGirlA*)thisx)

void EnGirlA_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGirlA_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_GirlA_InitVars = {
    ACTOR_EN_GIRLA,
    ACTORTYPE_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGirlA),
    (ActorFunc)EnGirlA_Init,
    (ActorFunc)EnGirlA_Destroy,
    (ActorFunc)EnGirlA_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863870.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086387C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808639B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863A10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863AAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863B4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863C08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863C6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863D28.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863D60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863DC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863E48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863EC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80863F94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864034.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086406C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808640A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864108.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864168.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864210.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086425C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808642D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864320.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086436C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808643B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086444C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808644A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864558.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808645A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864658.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808646F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_8086472C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864744.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_80864774.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808648F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/EnGirlA_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_GirlA_0x80863870/func_808649C8.asm")
