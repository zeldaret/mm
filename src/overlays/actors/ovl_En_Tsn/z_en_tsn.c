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
    (ActorFunc)EnTsn_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80ADFCA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80ADFCEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/EnTsn_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/EnTsn_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80ADFF84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0010.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0304.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0418.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0460.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE04C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE04FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0698.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0704.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0C88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0D10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/EnTsn_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0F84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE0FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/func_80AE1024.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Tsn_0x80ADFCA0/EnTsn_Draw.asm")
