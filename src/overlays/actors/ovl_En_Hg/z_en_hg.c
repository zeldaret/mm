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
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HARFGIBUD,
    sizeof(EnHg),
    (ActorFunc)EnHg_Init,
    (ActorFunc)EnHg_Destroy,
    (ActorFunc)EnHg_Update,
    (ActorFunc)EnHg_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/EnHg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/EnHg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF398.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF4AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF5F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF6D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF710.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF7D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF88C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF8A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF93C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCF95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCFC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/EnHg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCFE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/func_80BCFE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hg/EnHg_Draw.s")
