#include "z_dm_nb.h"

#define FLAGS 0x00000009

#define THIS ((DmNb*)thisx)

void DmNb_Init(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Update(Actor* thisx, GlobalContext* globalCtx);
void DmNb_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Nb_InitVars = {
    ACTOR_DM_NB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(DmNb),
    (ActorFunc)DmNb_Init,
    (ActorFunc)DmNb_Destroy,
    (ActorFunc)DmNb_Update,
    (ActorFunc)DmNb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/func_80C1DED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/func_80C1DF18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/DmNb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/DmNb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/DmNb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/func_80C1E168.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Dm_Nb/DmNb_Draw.s")
