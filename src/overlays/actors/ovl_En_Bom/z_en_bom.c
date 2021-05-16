#include "z_en_bom.h"

#define FLAGS 0x00000030

#define THIS ((EnBom*)thisx)

void EnBom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bom_InitVars = {
    ACTOR_EN_BOM,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBom),
    (ActorFunc)EnBom_Init,
    (ActorFunc)EnBom_Destroy,
    (ActorFunc)EnBom_Update,
    (ActorFunc)EnBom_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/EnBom_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/EnBom_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_80871058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_808714D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_808715B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/EnBom_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/EnBom_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_80872648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_808726DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom/func_80872BC0.s")
