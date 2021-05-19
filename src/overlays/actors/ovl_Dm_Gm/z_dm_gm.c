#include "z_dm_gm.h"

#define FLAGS 0x00000009

#define THIS ((DmGm*)thisx)

void DmGm_Init(Actor* thisx, GlobalContext* globalCtx);
void DmGm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmGm_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Gm_InitVars = {
    ACTOR_DM_GM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AN1,
    sizeof(DmGm),
    (ActorFunc)DmGm_Init,
    (ActorFunc)DmGm_Destroy,
    (ActorFunc)DmGm_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24360.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24428.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24504.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C2457C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C2478C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C248A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24BD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/DmGm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/DmGm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/DmGm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C24E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Gm_0x80C24360/func_80C25000.asm")
