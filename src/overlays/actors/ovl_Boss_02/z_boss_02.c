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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(Boss02),
    (ActorFunc)Boss02_Init,
    (ActorFunc)Boss02_Destroy,
    (ActorFunc)Boss02_Update,
    (ActorFunc)Boss02_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA1D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA22C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA24C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA264.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA344.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DA50C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/Boss02_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/Boss02_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DAA74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DAA98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DAAA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DAB78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DBFB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DC218.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/Boss02_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DC78C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/Boss02_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DD0A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DD0CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DD2F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DD934.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_02_0x809DA1D0/func_809DEAC4.asm")
