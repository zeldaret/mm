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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnBombal),
    (ActorFunc)EnBombal_Init,
    (ActorFunc)EnBombal_Destroy,
    (ActorFunc)EnBombal_Update,
    (ActorFunc)EnBombal_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05B24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C060B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C06208.s")
