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
    (ActorFunc)Boss01_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0550.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D082C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D089C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D092C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D0AA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D119C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D12B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1AB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1B2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1E5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1E74.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D1EA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D20D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D25E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2664.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D26B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2780.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D27D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2858.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2A44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2AA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2BCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2CDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D2E4C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3074.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D30D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D32B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3374.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D345C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D34D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3530.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D35A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D365C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D370C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3A7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3ADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3C10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D3CD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D441C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D4464.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D44C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D4668.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D519C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5584.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D55CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/Boss01_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5B0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5BC4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D5FB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D606C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D62D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6314.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6424.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6488.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D64E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6588.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D65E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D670C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D694C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6B08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6BB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6C98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D6E7C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Boss_01_0x809D0530/func_809D73D4.asm")
