/*
 * File: z_oceff_storm.c
 * Overlay: ovl_Oceff_Storm
 * Description: Song of Storms Ocarina Effect
 */

#include "z_oceff_storm.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20 | ACTOR_FLAG_2000000)

#define THIS ((OceffStorm*)thisx)

void OceffStorm_Init(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Update(Actor* thisx, GlobalContext* globalCtx);
void OceffStorm_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80981928(OceffStorm* this, GlobalContext* globalCtx);
void func_80981B48(OceffStorm* this, GlobalContext* globalCtx);

void OceffStorm_SetupAction(OceffStorm* this, OceffStormActionFunc actionFunc);

#if 0
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

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_8098176C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981928.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981B48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/func_80981BB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Oceff_Storm/OceffStorm_Draw.s")
