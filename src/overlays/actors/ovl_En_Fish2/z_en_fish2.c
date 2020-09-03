#include "z_en_fish2.h"

#define FLAGS 0x00000019

#define THIS ((EnFish2*)thisx)

void EnFish2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFish2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Fish2_InitVars = {
    ACTOR_EN_FISH2,
    ACTORTYPE_PROP,
    FLAGS,
    OBJECT_FB,
    sizeof(EnFish2),
    (ActorFunc)EnFish2_Init,
    (ActorFunc)EnFish2_Destroy,
    (ActorFunc)EnFish2_Update,
    (ActorFunc)EnFish2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B28370.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B28478.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/EnFish2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/EnFish2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B287F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B288E8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2899C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B289DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B28B5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B28C14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2913C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29194.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29250.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2938C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B293C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2951C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B295A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29778.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B297FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29E5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B29EE4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2A01C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2A094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2A23C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2A448.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2A498.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/EnFish2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2ABF4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2AC20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/EnFish2_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2ADB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2AF80.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Fish2_0x80B28370/func_80B2B180.asm")
