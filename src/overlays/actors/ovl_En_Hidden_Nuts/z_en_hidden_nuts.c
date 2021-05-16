#include "z_en_hidden_nuts.h"

#define FLAGS 0x02000009

#define THIS ((EnHiddenNuts*)thisx)

void EnHiddenNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHiddenNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Hidden_Nuts_InitVars = {
    ACTOR_EN_HIDDEN_NUTS,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HINTNUTS,
    sizeof(EnHiddenNuts),
    (ActorFunc)EnHiddenNuts_Init,
    (ActorFunc)EnHiddenNuts_Destroy,
    (ActorFunc)EnHiddenNuts_Update,
    (ActorFunc)EnHiddenNuts_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/EnHiddenNuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/EnHiddenNuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB1B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB2B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB580.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB7E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDB978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDBA28.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDBB48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDBE70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/func_80BDBED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/EnHiddenNuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hidden_Nuts/EnHiddenNuts_Draw.s")
