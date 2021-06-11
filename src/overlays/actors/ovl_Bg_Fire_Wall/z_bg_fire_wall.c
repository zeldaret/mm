#include "z_bg_fire_wall.h"

#define FLAGS 0x00000000

#define THIS ((BgFireWall*)thisx)

void BgFireWall_Init(Actor* thisx, GlobalContext* globalCtx);
void BgFireWall_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgFireWall_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Bg_Fire_Wall_InitVars = {
    ACTOR_BG_FIRE_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FWALL,
    sizeof(BgFireWall),
    (ActorFunc)BgFireWall_Init,
    (ActorFunc)BgFireWall_Destroy,
    (ActorFunc)BgFireWall_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC638.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC68C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC6C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC7F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809AC970.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/BgFireWall_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Fire_Wall/func_809ACB28.s")
