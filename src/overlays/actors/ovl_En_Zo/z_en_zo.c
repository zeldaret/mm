#include "z_en_zo.h"

#define FLAGS 0x00000019

#define THIS ((EnZo*)thisx)

void EnZo_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZo_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zo_InitVars = {
    ACTOR_EN_ZO,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZO,
    sizeof(EnZo),
    (ActorFunc)EnZo_Init,
    (ActorFunc)EnZo_Destroy,
    (ActorFunc)EnZo_Update,
    (ActorFunc)EnZo_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099E790.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099E858.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099E96C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099E9E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099EA60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099EBD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099EC50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099ED4C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099EE24.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/EnZo_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/EnZo_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/EnZo_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099EFF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/func_8099F15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zo_0x8099E790/EnZo_Draw.asm")
