#include "z_en_ja.h"

#define FLAGS 0x00000019

#define THIS ((EnJa*)thisx)

void EnJa_Init(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Update(Actor* thisx, GlobalContext* globalCtx);
void EnJa_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ja_InitVars = {
    ACTOR_EN_JA,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnJa),
    (ActorFunc)EnJa_Init,
    (ActorFunc)EnJa_Destroy,
    (ActorFunc)EnJa_Update,
    (ActorFunc)EnJa_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1900.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC192C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1984.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC19FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1A68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1AE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1B60.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1D70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1E40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC1FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC203C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC20D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC213C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC2150.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC21A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC2274.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC22F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/EnJa_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/EnJa_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/EnJa_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC25E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC2620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC2B30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/EnJa_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC2EA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC3154.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC32D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC33C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Ja_0x80BC1900/func_80BC3594.asm")
