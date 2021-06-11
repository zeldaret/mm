#include "z_en_knight.h"

#define FLAGS 0x00000035

#define THIS ((EnKnight*)thisx)

void EnKnight_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Update(Actor* thisx, GlobalContext* globalCtx);
void EnKnight_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Knight_InitVars = {
    ACTOR_EN_KNIGHT,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(EnKnight),
    (ActorFunc)EnKnight_Init,
    (ActorFunc)EnKnight_Destroy,
    (ActorFunc)EnKnight_Update,
    (ActorFunc)EnKnight_Draw,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B20F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B21F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B22CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B2DD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B2F54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B316C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B31E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B329C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B331C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B33F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B35BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3618.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B37C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3834.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B389C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3B94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3E9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B3F0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B40E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B41D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B41F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B42B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B47EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4BFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4C58.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4E84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4ED8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B4F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B51DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B52E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5634.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B58D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B592C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B59FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5B08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5D54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5E90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5ED0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B5FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B601C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B631C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B638C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6528.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6C04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6C54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6D38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6D94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B6F40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7190.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B71DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7778.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B78A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B7950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B842C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B8458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9A18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9D24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9E00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809B9F8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA058.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA0CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA940.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BA978.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC67C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC720.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BC8B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCA80.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCAD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCB54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BCB78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/EnKnight_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD1AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD260.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD29C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD490.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Knight/func_809BD858.s")
