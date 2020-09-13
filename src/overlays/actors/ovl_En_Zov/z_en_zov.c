#include "z_en_zov.h"

#define FLAGS 0x00000009

#define THIS ((EnZov*)thisx)

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zov_InitVars = {
    ACTOR_EN_ZOV,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZOV,
    sizeof(EnZov),
    (ActorFunc)EnZov_Init,
    (ActorFunc)EnZov_Destroy,
    (ActorFunc)EnZov_Update,
    (ActorFunc)EnZov_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/EnZov_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/EnZov_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD13DC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1440.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1470.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1570.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD15A4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD160C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1764.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD187C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD19FC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1AE0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1BF0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1C38.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1C84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1D30.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1D94.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1DB8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1F1C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD1FC8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/EnZov_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD2380.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/func_80BD2404.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zov_0x80BD11E0/EnZov_Draw.asm")
