#include "z_oceff_storm.h"

#define FLAGS 0x02000030

#define THIS ((OceffStorm*)thisx)

void OceffStorm_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Oceff_Storm_InitVars = {
    ACTOR_OCEFF_STORM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(OceffStorm),
    (ActorFunc)OceffStorm_Init,
    (ActorFunc)OceffStorm_Destroy,
    (ActorFunc)OceffStorm_Update,
    (ActorFunc)OceffStorm_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981760.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_8098176C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Draw.s")
