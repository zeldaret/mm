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
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_KEIKOKU_DEMO,
    sizeof(DmRavine),
    (ActorFunc)DmRavine_Init,
    (ActorFunc)DmRavine_Destroy,
    (ActorFunc)DmRavine_Update,
    (ActorFunc)DmRavine_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ravine_0x80A2E7A0/DmRavine_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ravine_0x80A2E7A0/DmRavine_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ravine_0x80A2E7A0/func_80A2E838.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ravine_0x80A2E7A0/DmRavine_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Ravine_0x80A2E7A0/DmRavine_Draw.asm")
