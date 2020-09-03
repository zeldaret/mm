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
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2B830.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2B874.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2B8F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2B974.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BAA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BBFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BCF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BD30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BD88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BD98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2BE54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/EnPst_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/EnPst_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/EnPst_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/func_80B2C11C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Pst_0x80B2B830/EnPst_Draw.asm")
