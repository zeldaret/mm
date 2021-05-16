#include "z_boss_01.h"

#define FLAGS 0x00000035

#define THIS ((Boss01*)thisx)

void Boss01_Init(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Update(Actor* thisx, GlobalContext* globalCtx);
void Boss01_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Boss_01_InitVars = {
    ACTOR_BOSS_01,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS01,
    sizeof(Boss01),
    (ActorFunc)Boss01_Init,
    (ActorFunc)Boss01_Destroy,
    (ActorFunc)Boss01_Update,
    (ActorFunc)Boss01_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0550.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D082C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D089C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D092C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D0AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D119C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D12B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1AB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1B2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1E5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1E74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D1EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D20D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D25E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D26B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2780.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D27D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2858.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2AA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2CDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D2E4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3074.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D30D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D32B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D345C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D34D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3530.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D35A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D365C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D370C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3ADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3C10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D3CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D441C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D4464.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D44C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D4668.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D519C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5584.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D55CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/Boss01_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5BC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D5FB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D606C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D62D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6314.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6488.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D64E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6588.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D65E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D670C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D694C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6BB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6C98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D6E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Boss_01/func_809D73D4.s")
