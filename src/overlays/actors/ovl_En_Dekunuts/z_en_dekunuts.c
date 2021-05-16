#include "z_en_dekunuts.h"

#define FLAGS 0x00000005

#define THIS ((EnDekunuts*)thisx)

void EnDekunuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDekunuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dekunuts_InitVars = {
    ACTOR_EN_DEKUNUTS,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEKUNUTS,
    sizeof(EnDekunuts),
    (ActorFunc)EnDekunuts_Init,
    (ActorFunc)EnDekunuts_Destroy,
    (ActorFunc)EnDekunuts_Update,
    (ActorFunc)EnDekunuts_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/EnDekunuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/EnDekunuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD3B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD428.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD49C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD870.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BD8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDA08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDA4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDC9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDCF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDD54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDE7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDEF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDF60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BDFB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE1CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE358.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE3A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE3FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE4D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BE73C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/EnDekunuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BEBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/func_808BED30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dekunuts/EnDekunuts_Draw.s")
