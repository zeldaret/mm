#include "z_en_ishi.h"

#define FLAGS 0x00800010

#define THIS ((EnIshi*)thisx)

void EnIshi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIshi_Update(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Ishi_InitVars = {
    ACTOR_EN_ISHI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnIshi),
    (ActorFunc)EnIshi_Init,
    (ActorFunc)EnIshi_Destroy,
    (ActorFunc)EnIshi_Update,
    (ActorFunc)NULL,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095D6E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095D758.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095D804.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095DABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095DDA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095DE9C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095DF90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095DFF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E14C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E204.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E2B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/EnIshi_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/EnIshi_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E5AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E5C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E64C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E660.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E934.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095E95C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095EA70.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095EBDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F060.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F0A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F180.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F194.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/EnIshi_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F210.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F36C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F61C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ishi_0x8095D6E0/func_8095F654.asm")
