#include "z_en_bombal.h"

#define FLAGS 0x00000010

#define THIS ((EnBombal*)thisx)

void EnBombal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bombal_InitVars = {
    ACTOR_EN_BOMBAL,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnBombal),
    (ActorFunc)EnBombal_Init,
    (ActorFunc)EnBombal_Destroy,
    (ActorFunc)EnBombal_Update,
    (ActorFunc)EnBombal_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/EnBombal_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/EnBombal_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C05B24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C05B3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C05C44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C05DE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/EnBombal_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/EnBombal_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C05F90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C060B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Bombal_0x80C05A70/func_80C06208.asm")
