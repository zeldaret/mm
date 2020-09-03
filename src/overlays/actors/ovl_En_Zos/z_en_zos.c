#include "z_en_zos.h"

#define FLAGS 0x02000009

#define THIS ((EnZos*)thisx)

void EnZos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zos_InitVars = {
    ACTOR_EN_ZOS,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZOS,
    sizeof(EnZos),
    (ActorFunc)EnZos_Init,
    (ActorFunc)EnZos_Destroy,
    (ActorFunc)EnZos_Update,
    (ActorFunc)EnZos_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/EnZos_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/EnZos_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBAE84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBAF5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBAFFC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB0D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB15C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB2C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB354.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB414.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB4CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB574.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB718.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBB8AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBBB84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBBCBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBBD5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBBDE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBBFBC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC070.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC14C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC22C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC24C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC298.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC37C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/EnZos_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC4E4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/func_80BBC500.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zos_0x80BBACA0/EnZos_Draw.asm")
