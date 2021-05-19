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
    (ActorFunc)EnDekunuts_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD3B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD49C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD870.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BD8D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDA08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDA4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDC9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDCF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDD54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDE7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDEF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDF60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BDFB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE1CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE294.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE358.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE3A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE3FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE4D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BE73C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BEBD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/func_808BED30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dekunuts_0x808BD1E0/EnDekunuts_Draw.asm")
