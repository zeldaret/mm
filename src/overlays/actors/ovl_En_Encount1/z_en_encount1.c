/*
 * File: z_en_encount1.c
 * Overlay: ovl_En_Encount1
 * Description: Spawner for Dragonflies, Skullfish, and Wallmasters
 */

#include "z_en_encount1.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_8000000)

#define THIS ((EnEncount1*)thisx)

void EnEncount1_Init(Actor* thisx, GlobalContext* globalCtx);
void EnEncount1_Update(Actor* thisx, GlobalContext* globalCtx);

void func_808E0954(EnEncount1* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Encount1_InitVars = {
    ACTOR_EN_ENCOUNT1,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnEncount1),
    (ActorFunc)EnEncount1_Init,
    (ActorFunc)NULL,
    (ActorFunc)EnEncount1_Update,
    (ActorFunc)NULL,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/EnEncount1_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/func_808E0954.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Encount1/EnEncount1_Update.s")
