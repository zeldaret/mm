#include "z_en_onpuman.h"

#define FLAGS 0x00000009

#define THIS ((EnOnpuman*)thisx)

void EnOnpuman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Onpuman_InitVars = {
    ACTOR_EN_ONPUMAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOnpuman),
    (ActorFunc)EnOnpuman_Init,
    (ActorFunc)EnOnpuman_Destroy,
    (ActorFunc)EnOnpuman_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1202C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B121D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Update.s")
