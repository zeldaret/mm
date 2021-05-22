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

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC638.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC68C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC6C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC7F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809AC970.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/BgFireWall_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Fire_Wall_0x809AC4B0/func_809ACB28.asm")
