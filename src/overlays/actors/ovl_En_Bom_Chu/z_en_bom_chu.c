#include "z_en_bom_chu.h"

#define FLAGS 0x00000010

#define THIS ((EnBomChu*)thisx)

void EnBomChu_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomChu_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Bom_Chu_InitVars = {
    ACTOR_EN_BOM_CHU,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBomChu),
    (ActorFunc)EnBomChu_Init,
    (ActorFunc)EnBomChu_Destroy,
    (ActorFunc)EnBomChu_Update,
    (ActorFunc)EnBomChu_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F75D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F77E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7868.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F79D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F7FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F8080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/func_808F818C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bom_Chu/EnBomChu_Draw.s")
