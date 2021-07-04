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
    (ActorFunc)Boss02_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA1D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA24C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA264.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA344.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DA50C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/Boss02_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/Boss02_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DAA74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DAA98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DAAA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DAB78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DBFB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DC218.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/Boss02_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DC78C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/Boss02_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DD0A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DD0CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DD2F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DD934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_02_0x809DA1D0/func_809DEAC4.asm")
