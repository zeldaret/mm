#include "z_boss_03.h"

#define FLAGS 0x00000035

#define THIS ((Boss03*)thisx)

void Boss03_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss03_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_03_InitVars = {
    ACTOR_BOSS_03,
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_BOSS03,
    sizeof(Boss03),
    (ActorFunc)Boss03_Init,
    (ActorFunc)Boss03_Destroy,
    (ActorFunc)Boss03_Update,
    (ActorFunc)Boss03_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2760.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2788.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E299C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2AB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2B8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2C1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2C3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E2DA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/Boss03_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/Boss03_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E344C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E34B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E38EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E3968.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E3D34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E3D98.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4180.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E421C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4674.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E475C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4910.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E497C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4C34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4C90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E4E80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E5ADC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E5B64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E65F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E6640.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E69A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E6A38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E6B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E6BC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E6CB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/Boss03_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E7920.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E79C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E7AA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/Boss03_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E7D00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E81E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E8810.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Boss_03_0x809E2760/func_809E8BEC.asm")
