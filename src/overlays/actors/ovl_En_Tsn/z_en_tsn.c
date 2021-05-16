#include "z_en_tsn.h"

#define FLAGS 0x02000019

#define THIS ((EnTsn*)thisx)

void EnTsn_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTsn_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tsn_InitVars = {
    ACTOR_EN_TSN,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnTsn),
    (ActorFunc)EnTsn_Init,
    (ActorFunc)EnTsn_Destroy,
    (ActorFunc)EnTsn_Update,
    (ActorFunc)EnTsn_Draw
};
*/

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFCA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80ADFF84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0010.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0460.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE04C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE04FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0698.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0C88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0D10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0F84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE0FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/func_80AE1024.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tsn/EnTsn_Draw.s")
