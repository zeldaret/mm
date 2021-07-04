#include "z_dm_tsg.h"

#define FLAGS 0x00000030

#define THIS ((DmTsg*)thisx)

void DmTsg_Init(Actor* thisx, GlobalContext* globalCtx);
void DmTsg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmTsg_Update(Actor* thisx, GlobalContext* globalCtx);
void DmTsg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Tsg_InitVars = {
    ACTOR_DM_TSG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(DmTsg),
    (ActorFunc)DmTsg_Init,
    (ActorFunc)DmTsg_Destroy,
    (ActorFunc)DmTsg_Update,
    (ActorFunc)DmTsg_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Tsg_0x80A3AC60/DmTsg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Tsg_0x80A3AC60/DmTsg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Tsg_0x80A3AC60/DmTsg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Tsg_0x80A3AC60/DmTsg_Draw.asm")
