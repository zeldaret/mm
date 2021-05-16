#include "z_boss_02.h"

#define FLAGS 0x00000035

#define THIS ((Boss02*)thisx)

void Boss02_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss02_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_02_InitVars = {
    ACTOR_BOSS_02,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(Boss02),
    (ActorFunc)Boss02_Init,
    (ActorFunc)Boss02_Destroy,
    (ActorFunc)Boss02_Update,
    (ActorFunc)Boss02_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA1D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA264.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA344.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DA50C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAA74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAA98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAAA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DAB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DBFB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DC218.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DC78C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/Boss02_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD0A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD2F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DD934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_02/func_809DEAC4.s")
