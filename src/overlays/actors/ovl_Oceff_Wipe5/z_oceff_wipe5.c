#include "z_oceff_wipe5.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe5*)thisx)

void OceffWipe5_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe5_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
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
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe5_0x80BC7AD0/OceffWipe5_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe5_0x80BC7AD0/OceffWipe5_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe5_0x80BC7AD0/OceffWipe5_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe5_0x80BC7AD0/OceffWipe5_Draw.asm")
