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
    (ActorFunc)OceffStorm_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/func_80981760.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/func_8098176C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/OceffStorm_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/OceffStorm_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/func_80981928.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/func_80981B48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/OceffStorm_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/func_80981BB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Oceff_Storm_0x80981760/OceffStorm_Draw.asm")
