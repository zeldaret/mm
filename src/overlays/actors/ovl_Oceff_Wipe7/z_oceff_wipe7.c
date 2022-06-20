/*
 * File: z_oceff_wipe7.c
 * Overlay: ovl_Oceff_Wipe7
 * Description: Song of Healing Ocarina Effect
 */

#include "z_oceff_wipe7.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe7*)thisx)

void OceffWipe7_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe7_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe7_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe7_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Oceff_Wipe7_InitVars = {
    ACTOR_OCEFF_WIPE7,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe7),
    (ActorFunc)OceffWipe7_Init,
    (ActorFunc)OceffWipe7_Destroy,
    (ActorFunc)OceffWipe7_Update,
    (ActorFunc)OceffWipe7_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe7/OceffWipe7_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe7/OceffWipe7_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe7/OceffWipe7_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe7/OceffWipe7_Draw.s")
