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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOS,
    sizeof(EnZos),
    (ActorFunc)EnZos_Init,
    (ActorFunc)EnZos_Destroy,
    (ActorFunc)EnZos_Update,
    (ActorFunc)EnZos_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/EnZos_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/EnZos_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBAE84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBAF5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBAFFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB0D4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB15C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB2C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB4CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB574.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB718.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBB8AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBBB84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBBCBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBBD5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBBDE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBBFBC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC070.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC14C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC24C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC298.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC37C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/EnZos_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC4E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/func_80BBC500.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zos_0x80BBACA0/EnZos_Draw.asm")
