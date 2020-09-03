#include "z_en_minideath.h"

#define FLAGS 0x00000015

#define THIS ((EnMinideath*)thisx)

void EnMinideath_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMinideath_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Minideath_InitVars = {
    ACTOR_EN_MINIDEATH,
    ACTORTYPE_ENEMY,
    FLAGS,
    OBJECT_DEATH,
    sizeof(EnMinideath),
    (ActorFunc)EnMinideath_Init,
    (ActorFunc)EnMinideath_Destroy,
    (ActorFunc)EnMinideath_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/EnMinideath_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/EnMinideath_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA268.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA308.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA34C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA458.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA7D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA860.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA8E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CA8F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAAC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAAEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAB90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CABB0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAC54.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CACD8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAE00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAE18.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAF08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CAF68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB07C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB0C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB22C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB454.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB524.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB59C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB6A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB6D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB7B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB7CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB810.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/func_808CB8F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Minideath_0x808CA0B0/EnMinideath_Update.asm")
