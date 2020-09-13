#include "z_oceff_wipe2.h"

#define FLAGS 0x02000010

#define THIS ((OceffWipe2*)thisx)

void OceffWipe2_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe2_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffWipe2_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Oceff_Wipe2_InitVars = {
    ACTOR_OCEFF_WIPE2,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffWipe2),
    (ActorFunc)OceffWipe2_Init,
    (ActorFunc)OceffWipe2_Destroy,
    (ActorFunc)OceffWipe2_Update,
    (ActorFunc)OceffWipe2_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Wipe2_0x80986270/OceffWipe2_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Wipe2_0x80986270/OceffWipe2_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Wipe2_0x80986270/OceffWipe2_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_Oceff_Wipe2_0x80986270/OceffWipe2_Draw.asm")
