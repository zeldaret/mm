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
    (ActorFunc)EnDragon_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EAA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EB40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5ED90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EDF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EE3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EF88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5EFD0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F3A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F508.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F888.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5F8D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5FCC0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B5FD68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B60138.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B6043C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/func_80B60494.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Dragon_0x80B5E890/EnDragon_Draw.asm")
