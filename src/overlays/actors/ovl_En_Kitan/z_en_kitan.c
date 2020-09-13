#include "z_en_kitan.h"

#define FLAGS 0x00000009

#define THIS ((EnKitan*)thisx)

void EnKitan_Init(Actor* thisx, GlobalContext* globalCtx);
void EnKitan_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnKitan_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Kitan_InitVars = {
    ACTOR_EN_KITAN,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_KITAN,
    sizeof(EnKitan),
    (ActorFunc)EnKitan_Init,
    (ActorFunc)EnKitan_Destroy,
    (ActorFunc)EnKitan_Update,
    (ActorFunc)NULL
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/EnKitan_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/EnKitan_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C0923C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09390.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C094A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09518.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C095C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09648.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09708.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09990.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09B50.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/EnKitan_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09C74.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09C90.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Kitan_0x80C090D0/func_80C09CD0.asm")
