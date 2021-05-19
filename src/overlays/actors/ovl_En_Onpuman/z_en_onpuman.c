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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/EnOnpuman_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/EnOnpuman_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/func_80B11F44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/func_80B11F78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/func_80B1202C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/func_80B1217C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/func_80B121D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Onpuman_0x80B11E60/EnOnpuman_Update.asm")
