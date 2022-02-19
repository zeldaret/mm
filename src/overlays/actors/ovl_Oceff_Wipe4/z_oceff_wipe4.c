/*
 * File: z_oceff_wipe4.c
 * Overlay: ovl_Oceff_Wipe4
 * Description: Scarecrow's Song Ocarina Effect
 */

#include "z_oceff_wipe4.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe4*)thisx)

void OceffWipe4_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Oceff_Wipe4_InitVars = {
    ACTOR_OCEFF_WIPE4,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe4),
    (ActorFunc)OceffWipe4_Init,
    (ActorFunc)OceffWipe4_Destroy,
    (ActorFunc)OceffWipe4_Update,
    (ActorFunc)OceffWipe4_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe4/OceffWipe4_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe4/OceffWipe4_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe4/OceffWipe4_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe4/OceffWipe4_Draw.s")
