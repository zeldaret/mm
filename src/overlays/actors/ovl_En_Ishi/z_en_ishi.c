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

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D6E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D758.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095D804.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DDA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DE9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DF90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095DFF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E204.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E2B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E5C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E64C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095E95C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095EA70.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095EBDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F0A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F180.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F194.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/EnIshi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F210.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F36C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F61C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ishi/func_8095F654.s")
