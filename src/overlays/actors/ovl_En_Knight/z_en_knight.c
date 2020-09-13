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
    ACTORTYPE_BOSS,
    FLAGS,
    OBJECT_KNIGHT,
    sizeof(EnKnight),
    (ActorFunc)EnKnight_Init,
    (ActorFunc)EnKnight_Destroy,
    (ActorFunc)EnKnight_Update,
    (ActorFunc)EnKnight_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B20F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B21F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B22CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/EnKnight_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/EnKnight_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B2DD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B2F54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B316C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B31E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B329C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B331C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3394.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B33F0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B35BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3618.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B37C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3834.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B389C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3958.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3A7C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3B94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3CD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3DAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3E9C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B3F0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B40E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B41D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B41F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B42B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B47EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4BFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4C58.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4E84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4ED8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B4F90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5058.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B51DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B52E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5634.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B58D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B592C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B59FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5B08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5D54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5E90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5ED0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B5FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B601C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B631C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B638C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6528.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6C04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6C54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6D38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6D94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6EC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B6F40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B7190.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B71DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B7708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B7778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B78A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B7950.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B842C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B8458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B9A18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B9D24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B9E00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809B9F8C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BA058.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BA0CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BA940.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BA978.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/EnKnight_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BC2C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BC67C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BC720.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BC8B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BCA80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BCAD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BCB54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BCB78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/EnKnight_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BD1AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BD260.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BD29C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BD490.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Knight_0x809B20F0/func_809BD858.asm")
