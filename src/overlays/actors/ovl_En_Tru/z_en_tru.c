#include "z_en_tru.h"

#define FLAGS 0x00000039

#define THIS ((EnTru*)thisx)

void EnTru_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTru_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Tru_InitVars = {
    ACTOR_EN_TRU,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_TRU,
    sizeof(EnTru),
    (ActorFunc)EnTru_Init,
    (ActorFunc)EnTru_Destroy,
    (ActorFunc)EnTru_Update,
    (ActorFunc)EnTru_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85620.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85788.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85AA4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85BCC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85E2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A85F84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86384.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86460.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86674.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86770.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A868F8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86924.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A8697C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A869DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86B0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86BAC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A86DB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A871E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A872AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A873B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A87400.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A875AC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A8777C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A87880.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A87B48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A87DC0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A87FD0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A881E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/EnTru_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/EnTru_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/EnTru_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A885B8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A88698.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/func_80A886D4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Tru_0x80A85620/EnTru_Draw.asm")
