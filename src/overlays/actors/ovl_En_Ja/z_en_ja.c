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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BOJ,
    sizeof(EnJa),
    (ActorFunc)EnJa_Init,
    (ActorFunc)EnJa_Destroy,
    (ActorFunc)EnJa_Update,
    (ActorFunc)EnJa_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1900.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC192C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC19FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1A68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1B60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1D70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1E40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC1FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC203C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC20D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC213C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC2150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC21A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC2274.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC22F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/EnJa_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/EnJa_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/EnJa_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC25E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC2620.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC2B30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/EnJa_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC2EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC3154.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC32D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC33C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ja/func_80BC3594.s")
