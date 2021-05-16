#include "z_en_dragon.h"

#define FLAGS 0x00000035

#define THIS ((EnDragon*)thisx)

void EnDragon_Init(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Update(Actor* thisx, GlobalContext* globalCtx);
void EnDragon_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Dragon_InitVars = {
    ACTOR_EN_DRAGON,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_UTUBO,
    sizeof(EnDragon),
    (ActorFunc)EnDragon_Init,
    (ActorFunc)EnDragon_Destroy,
    (ActorFunc)EnDragon_Update,
    (ActorFunc)EnDragon_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/EnDragon_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/EnDragon_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EAA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EB40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5ED90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EE3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EF88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5EFD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5F3A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5F418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5F508.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5F888.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5F8D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5FCC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B5FD68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B60138.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/EnDragon_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B6043C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/func_80B60494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Dragon/EnDragon_Draw.s")
