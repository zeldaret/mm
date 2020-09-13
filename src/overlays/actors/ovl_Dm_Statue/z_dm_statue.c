#include "z_dm_statue.h"

#define FLAGS 0x04000030

#define THIS ((DmStatue*)thisx)

void DmStatue_Init(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Update(Actor* thisx, GlobalContext* globalCtx);
void DmStatue_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Statue_InitVars = {
    ACTOR_DM_STATUE,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_SMTOWER,
    sizeof(DmStatue),
    (ActorFunc)DmStatue_Init,
    (ActorFunc)DmStatue_Destroy,
    (ActorFunc)DmStatue_Update,
    (ActorFunc)DmStatue_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Statue_0x80A4C9B0/DmStatue_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Statue_0x80A4C9B0/DmStatue_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Statue_0x80A4C9B0/DmStatue_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Statue_0x80A4C9B0/DmStatue_Draw.asm")
