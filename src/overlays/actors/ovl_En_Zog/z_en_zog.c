#include "z_en_zog.h"

#define FLAGS 0x00000009

#define THIS ((EnZog*)thisx)

void EnZog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zog_InitVars = {
    ACTOR_EN_ZOG,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZOG,
    sizeof(EnZog),
    (ActorFunc)EnZog_Init,
    (ActorFunc)EnZog_Destroy,
    (ActorFunc)EnZog_Update,
    (ActorFunc)EnZog_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93310.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93468.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/EnZog_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/EnZog_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B939C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93A48.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93B44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93BA8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93BE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93D2C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93DE8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B93EA0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B943A0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B943C0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B943EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B94470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B9451C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B9461C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B946B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B946FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B948A8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B94A00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B94C5C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B94D0C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B94E34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B95128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B95240.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/EnZog_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B954C4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/func_80B95598.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zog_0x80B93310/EnZog_Draw.asm")
