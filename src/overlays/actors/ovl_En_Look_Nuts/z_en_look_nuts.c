#include "z_en_look_nuts.h"

#define FLAGS 0x80000000

#define THIS ((EnLookNuts*)thisx)

void EnLookNuts_Init(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Update(Actor* thisx, GlobalContext* globalCtx);
void EnLookNuts_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Look_Nuts_InitVars = {
    ACTOR_EN_LOOK_NUTS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DNK,
    sizeof(EnLookNuts),
    (ActorFunc)EnLookNuts_Init,
    (ActorFunc)EnLookNuts_Destroy,
    (ActorFunc)EnLookNuts_Update,
    (ActorFunc)EnLookNuts_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67A34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67C48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67F30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A67FC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A68080.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/func_80A680FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Look_Nuts/EnLookNuts_Draw.s")
