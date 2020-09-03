#include "z_en_zoraegg.h"

#define FLAGS 0x00000010

#define THIS ((EnZoraegg*)thisx)

void EnZoraegg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZoraegg_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zoraegg_InitVars = {
    ACTOR_EN_ZORAEGG,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    OBJECT_ZORAEGG,
    sizeof(EnZoraegg),
    (ActorFunc)EnZoraegg_Init,
    (ActorFunc)EnZoraegg_Destroy,
    (ActorFunc)EnZoraegg_Update,
    (ActorFunc)EnZoraegg_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31590.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/EnZoraegg_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/EnZoraegg_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B319A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B319D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31A34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31C40.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31CB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31D14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31D64.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B31E00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32084.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32094.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B320E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B321D0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32228.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B322BC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32390.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B324B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32644.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B326F4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32820.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32928.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32A88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32B10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32B3C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32B70.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32BB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32C34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32D08.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/EnZoraegg_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B32F04.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B331C8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B3336C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B333DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B33480.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/func_80B33818.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zoraegg_0x80B31590/EnZoraegg_Draw.asm")
