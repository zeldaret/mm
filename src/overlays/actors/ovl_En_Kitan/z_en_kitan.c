#include "z_en_kitan.h"

#define FLAGS 0x00000009

#define THIS ((EnKitan*)thisx)

void EnKitan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKitan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKitan_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kitan_InitVars = {
    ACTOR_EN_KITAN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_KITAN,
    sizeof(EnKitan),
    (ActorFunc)EnKitan_Init,
    (ActorFunc)EnKitan_Destroy,
    (ActorFunc)EnKitan_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C0923C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C094A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C095C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09CD0.s")
