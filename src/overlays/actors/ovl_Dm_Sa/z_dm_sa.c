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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2E960.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EB58.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/func_80A2EBB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Sa_0x80A2E960/DmSa_Draw.asm")
