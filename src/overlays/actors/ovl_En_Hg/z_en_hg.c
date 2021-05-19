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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF398.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF5F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF634.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF6D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF710.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF778.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF7D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF88C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF8A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF93C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCF95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFC0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFE54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/func_80BCFE70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Hg_0x80BCF1D0/EnHg_Draw.asm")
