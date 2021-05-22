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
    (ActorFunc)EnBom_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80871058.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808714D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808715B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/EnBom_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80872648.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_808726DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bom_0x80870DB0/func_80872BC0.asm")
