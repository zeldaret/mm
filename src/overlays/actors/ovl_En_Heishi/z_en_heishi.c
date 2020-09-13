#include "z_en_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnHeishi*)thisx)

void EnHeishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Heishi_InitVars = {
    ACTOR_EN_HEISHI,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnHeishi),
    (ActorFunc)EnHeishi_Init,
    (ActorFunc)EnHeishi_Destroy,
    (ActorFunc)EnHeishi_Update,
    (ActorFunc)EnHeishi_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/EnHeishi_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/EnHeishi_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/func_80BE90BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/func_80BE9148.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/func_80BE91DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/func_80BE9214.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/EnHeishi_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/func_80BE9380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Heishi_0x80BE8F20/EnHeishi_Draw.asm")
