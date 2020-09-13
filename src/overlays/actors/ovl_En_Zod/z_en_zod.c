#include "z_en_zod.h"

#define FLAGS 0x00000009

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Zod_InitVars = {
    ACTOR_EN_ZOD,
    ACTORTYPE_NPC,
    FLAGS,
    OBJECT_ZOD,
    sizeof(EnZod),
    (ActorFunc)EnZod_Init,
    (ActorFunc)EnZod_Destroy,
    (ActorFunc)EnZod_Update,
    (ActorFunc)EnZod_Draw
};
*/

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/EnZod_Init.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/EnZod_Destroy.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF1EC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF2B4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF338.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF3E0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF4D8.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF7CC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAF99C.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFA44.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFADC.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFB84.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFC00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFC10.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFD00.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFDB4.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFE34.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BAFF14.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/EnZod_Update.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BB0128.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BB0170.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/func_80BB01B0.asm")

GLOBAL_ASM("asm/non_matchings/ovl_En_Zod_0x80BAEF70/EnZod_Draw.asm")
