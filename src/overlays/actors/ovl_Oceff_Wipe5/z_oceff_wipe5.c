/*
 * File: z_oceff_wipe5.c
 * Overlay: ovl_Oceff_Wipe5
 * Description: Sonata/Lullaby/Bossa Nova/Elegy/Oath Ocarina Effect
 */

#include "z_oceff_wipe5.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_2000000)

#define THIS ((OceffWipe5*)thisx)

void OceffWipe5_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Oceff_Wipe5_InitVars = {
    ACTOR_OCEFF_WIPE5,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe5),
    (ActorFunc)OceffWipe5_Init,
    (ActorFunc)OceffWipe5_Destroy,
    (ActorFunc)OceffWipe5_Update,
    (ActorFunc)OceffWipe5_Draw,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Wipe5/OceffWipe5_Draw.s")
