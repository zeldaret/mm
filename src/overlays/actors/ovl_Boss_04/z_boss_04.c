#include "z_boss_04.h"

#define FLAGS 0x00000035

#define THIS ((Boss04*)thisx)

void Boss04_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss04_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_04_InitVars = {
    ACTOR_BOSS_04,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(Boss04),
    (ActorFunc)Boss04_Init,
    (ActorFunc)Boss04_Destroy,
    (ActorFunc)Boss04_Update,
    (ActorFunc)Boss04_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809EC040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/Boss04_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/Boss04_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809EC544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809EC568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ECD00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ECD18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ECEF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ECF58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ED224.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ED2A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ED45C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809ED50C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/Boss04_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809EDCCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/func_809EDECC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_04/Boss04_Draw.s")
