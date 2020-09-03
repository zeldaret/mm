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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(Boss06),
    (ActorFunc)Boss06_Init,
    (ActorFunc)Boss06_Destroy,
    (ActorFunc)Boss06_Update,
    (ActorFunc)Boss06_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2120.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2140.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/Boss06_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/Boss06_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F23CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F24A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F24C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2B64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2C44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2E14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2ED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/func_809F2EE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/Boss06_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_06_0x809F2120/Boss06_Draw.asm")
