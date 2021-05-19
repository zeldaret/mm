#include "z_en_aob_01.h"

#define FLAGS 0x00000019

#define THIS ((EnAob01*)thisx)

void EnAob01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Aob_01_InitVars = {
    ACTOR_EN_AOB_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AOB,
    sizeof(EnAob01),
    (ActorFunc)EnAob01_Init,
    (ActorFunc)EnAob01_Destroy,
    (ActorFunc)EnAob01_Update,
    (ActorFunc)EnAob01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C10B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1124.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1158.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C11EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1304.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C14D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C15BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C165C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C16DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1D64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C1EC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C21E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2594.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C25E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2680.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C26E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2730.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2788.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2824.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C28B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2A64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2BE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2C9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2EC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2F34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C2FA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/EnAob01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/EnAob01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/EnAob01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C33D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C35B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/func_809C35F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Aob_01_0x809C10B0/EnAob01_Draw.asm")
