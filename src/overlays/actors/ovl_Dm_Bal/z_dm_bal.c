#include "z_dm_bal.h"

#define FLAGS 0x02000019

#define THIS ((DmBal*)thisx)

void DmBal_Init(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Update(Actor* thisx, GlobalContext* globalCtx);
void DmBal_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Dm_Bal_InitVars = {
    ACTOR_DM_BAL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BAL,
    sizeof(DmBal),
    (ActorFunc)DmBal_Init,
    (ActorFunc)DmBal_Destroy,
    (ActorFunc)DmBal_Update,
    (ActorFunc)DmBal_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/DmBal_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/DmBal_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1EAC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1EAD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1EAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1EC60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1ED0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1ED64.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/DmBal_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1EF80.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/func_80C1F060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Dm_Bal_0x80C1E9E0/DmBal_Draw.asm")
