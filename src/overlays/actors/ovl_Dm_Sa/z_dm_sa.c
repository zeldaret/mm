#include "z_dm_sa.h"

#define FLAGS 0x00000030

#define THIS ((DmSa*)thisx)

void DmSa_Init(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Update(Actor* thisx, GlobalContext* globalCtx);
void DmSa_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Sa_InitVars = {
    ACTOR_DM_SA,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_STK,
    sizeof(DmSa),
    (ActorFunc)DmSa_Init,
    (ActorFunc)DmSa_Destroy,
    (ActorFunc)DmSa_Update,
    (ActorFunc)DmSa_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2E960.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/DmSa_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/DmSa_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EABC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/DmSa_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EB10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EB2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EB44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EB58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/func_80A2EBB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Dm_Sa_0x80A2E960/DmSa_Draw.asm")
