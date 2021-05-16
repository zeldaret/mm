#include "z_en_pst.h"

#define FLAGS 0x00000001

#define THIS ((EnPst*)thisx)

void EnPst_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Pst_InitVars = {
    ACTOR_EN_PST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BBFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BCF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2C11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Draw.s")
