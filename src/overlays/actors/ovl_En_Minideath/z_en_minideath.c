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
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/EnMinideath_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/EnMinideath_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA268.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA34C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA7D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA860.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA8E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CA8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAAC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAAEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAB90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CABB0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAC54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CACD8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAE00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAE18.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAF08.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CAF68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB07C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB094.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB0C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB454.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB524.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB59C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB6A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB6D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB7B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB7CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB810.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/func_808CB8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Minideath_0x808CA0B0/EnMinideath_Update.asm")
