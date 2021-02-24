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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_NB,
    sizeof(DmNb),
    (ActorFunc)DmNb_Init,
    (ActorFunc)DmNb_Destroy,
    (ActorFunc)DmNb_Update,
    (ActorFunc)DmNb_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/func_80C1DED0.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/func_80C1DF18.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/DmNb_Init.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/DmNb_Destroy.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/DmNb_Update.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/func_80C1E168.asm")

#pragma GLOBAL_ASM("asm/non_matchings/ovl_Dm_Nb_0x80C1DED0/DmNb_Draw.asm")
