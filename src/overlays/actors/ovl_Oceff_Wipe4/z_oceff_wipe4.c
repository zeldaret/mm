#include "z_oceff_wipe4.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe4*)thisx)

void OceffWipe4_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe4_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe4_0x8099D780/OceffWipe4_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe4_0x8099D780/OceffWipe4_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe4_0x8099D780/OceffWipe4_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe4_0x8099D780/OceffWipe4_Draw.asm")
