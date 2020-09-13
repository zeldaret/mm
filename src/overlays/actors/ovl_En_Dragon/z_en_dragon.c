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
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_UTUBO,
    sizeof(EnDragon),
    (ActorFunc)EnDragon_Init,
    (ActorFunc)EnDragon_Destroy,
    (ActorFunc)EnDragon_Update,
    (ActorFunc)EnDragon_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/EnDragon_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/EnDragon_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EAA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EB40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5ED90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EDF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EE3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EF88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5EFD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5F3A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5F418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5F508.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5F888.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5F8D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5FCC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B5FD68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B60138.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/EnDragon_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B6043C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/func_80B60494.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Dragon_0x80B5E890/EnDragon_Draw.asm")
