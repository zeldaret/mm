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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS04,
    sizeof(Boss04),
    (ActorFunc)Boss04_Init,
    (ActorFunc)Boss04_Destroy,
    (ActorFunc)Boss04_Update,
    (ActorFunc)Boss04_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809EC040.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/Boss04_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/Boss04_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809EC544.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809EC568.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ECD00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ECD18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ECEF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ECF58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ED224.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ED2A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ED45C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809ED50C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/Boss04_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809EDCCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/func_809EDECC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_04_0x809EC040/Boss04_Draw.asm")
