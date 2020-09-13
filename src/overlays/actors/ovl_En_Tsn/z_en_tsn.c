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
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TSN,
    sizeof(EnTsn),
    (ActorFunc)EnTsn_Init,
    (ActorFunc)EnTsn_Destroy,
    (ActorFunc)EnTsn_Update,
    (ActorFunc)EnTsn_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80ADFCA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80ADFCEC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/EnTsn_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/EnTsn_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80ADFF84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0010.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0304.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0418.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE04C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE04FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0704.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0C88.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0D10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0D78.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/EnTsn_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0F84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE0FA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/func_80AE1024.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tsn_0x80ADFCA0/EnTsn_Draw.asm")
