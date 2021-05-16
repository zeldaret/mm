#include "z_en_minideath.h"

#define FLAGS 0x00000015

#define THIS ((EnMinideath*)thisx)

void EnMinideath_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Minideath_InitVars = {
    ACTOR_EN_MINIDEATH,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnMinideath),
    (ActorFunc)EnMinideath_Init,
    (ActorFunc)EnMinideath_Destroy,
    (ActorFunc)EnMinideath_Update,
    (ActorFunc)NULL
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA268.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA34C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA458.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA7D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA860.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA8E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CA8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAAC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAAEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAB90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CABB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAC54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CACD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAE00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAE18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAF08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CAF68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB07C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB094.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB454.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB524.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB6D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB7B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB810.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/func_808CB8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Minideath/EnMinideath_Update.s")
