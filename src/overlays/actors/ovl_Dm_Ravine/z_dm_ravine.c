#include "z_dm_ravine.h"

#define FLAGS 0x00000030

#define THIS ((DmRavine*)thisx)

void DmRavine_Init(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Update(Actor* thisx, GlobalContext* globalCtx);
void DmRavine_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Ravine_InitVars = {
    ACTOR_DM_RAVINE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmRavine),
    (ActorFunc)DmRavine_Init,
    (ActorFunc)DmRavine_Destroy,
    (ActorFunc)DmRavine_Update,
    (ActorFunc)DmRavine_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ravine/DmRavine_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ravine/DmRavine_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ravine/func_80A2E838.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ravine/DmRavine_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Ravine/DmRavine_Draw.s")
