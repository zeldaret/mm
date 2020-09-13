#include "z_en_twig.h"

#define FLAGS 0x00000010

#define THIS ((EnTwig*)thisx)

void EnTwig_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTwig_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Twig_InitVars = {
    ACTOR_EN_TWIG,
    ACTORTYPE_MISC,
    FLAGS,
    OBJECT_TWIG,
    sizeof(EnTwig),
    (ActorFunc)EnTwig_Init,
    (ActorFunc)EnTwig_Destroy,
    (ActorFunc)EnTwig_Update,
    (ActorFunc)EnTwig_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/EnTwig_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/EnTwig_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0A54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0A6C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0A7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0AC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0CC4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/func_80AC0D2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/EnTwig_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Twig_0x80AC0830/EnTwig_Draw.asm")
