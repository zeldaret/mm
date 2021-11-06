/*
 * File: z_oceff_wipe6.c
 * Overlay: ovl_Oceff_Wipe6
 * Description:
 */

#include "z_oceff_wipe6.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe6*)thisx)

void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Oceff_Wipe6_InitVars = {
    ACTOR_OCEFF_WIPE6,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe6),
    (ActorFunc)OceffWipe6_Init,
    (ActorFunc)OceffWipe6_Destroy,
    (ActorFunc)OceffWipe6_Update,
    (ActorFunc)OceffWipe6_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe6/OceffWipe6_Draw.s")
