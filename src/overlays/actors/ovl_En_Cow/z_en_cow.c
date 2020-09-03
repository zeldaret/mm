#include "z_en_cow.h"

#define FLAGS 0x00000009

#define THIS ((EnCow*)thisx)

void EnCow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Cow_InitVars = {
    ACTOR_EN_COW,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_COW,
    sizeof(EnCow),
    (ActorFunc)EnCow_Init,
    (ActorFunc)EnCow_Destroy,
    (ActorFunc)EnCow_Update,
    (ActorFunc)EnCow_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099C290.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099C328.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099C41C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/EnCow_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/EnCow_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099C880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CAA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CB20.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CB68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CBCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CC68.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CCF8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CDA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099CFAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/EnCow_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099D3C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099D4AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099D4FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/EnCow_Draw.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Cow_0x8099C290/func_8099D59C.asm")
