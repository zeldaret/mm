#include "z_oceff_wipe3.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe3*)thisx)

void OceffWipe3_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe3_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Oceff_Wipe3_InitVars = {
    ACTOR_OCEFF_WIPE3,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe3),
    (ActorFunc)OceffWipe3_Init,
    (ActorFunc)OceffWipe3_Destroy,
    (ActorFunc)OceffWipe3_Update,
    (ActorFunc)OceffWipe3_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe3_0x809879E0/OceffWipe3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe3_0x809879E0/OceffWipe3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe3_0x809879E0/OceffWipe3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Wipe3_0x809879E0/OceffWipe3_Draw.asm")
