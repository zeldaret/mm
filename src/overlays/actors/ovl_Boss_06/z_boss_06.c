#include "z_boss_06.h"

#define FLAGS 0x00000035

#define THIS ((Boss06*)thisx)

void Boss06_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss06_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_06_InitVars = {
    ACTOR_BOSS_06,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(Boss06),
    (ActorFunc)Boss06_Init,
    (ActorFunc)Boss06_Destroy,
    (ActorFunc)Boss06_Update,
    (ActorFunc)Boss06_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2120.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2140.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F23CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F24A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F24C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2B64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2E14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/func_809F2EE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_06/Boss06_Draw.s")
