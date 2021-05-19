#include "z_oceff_wipe6.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe6*)thisx)

void OceffWipe6_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe6_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe6_0x80BCA5A0/OceffWipe6_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe6_0x80BCA5A0/OceffWipe6_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe6_0x80BCA5A0/OceffWipe6_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe6_0x80BCA5A0/OceffWipe6_Draw.asm")
