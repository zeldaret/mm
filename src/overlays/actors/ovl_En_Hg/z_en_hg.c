#include "z_en_hg.h"

#define FLAGS 0x02100019

#define THIS ((EnHg*)thisx)

void EnHg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hg_InitVars = {
    ACTOR_EN_HG,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHg),
    (ActorFunc)EnHg_Init,
    (ActorFunc)EnHg_Destroy,
    (ActorFunc)EnHg_Update,
    (ActorFunc)EnHg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/EnHg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/EnHg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF398.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF4AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF5F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF68C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF6D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF710.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF7D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF88C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF8A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF93C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCF95C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCFC0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/EnHg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCFE54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/func_80BCFE70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Hg_0x80BCF1D0/EnHg_Draw.asm")
