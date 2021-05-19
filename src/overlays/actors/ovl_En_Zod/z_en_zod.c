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
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOD,
    sizeof(EnZod),
    (ActorFunc)EnZod_Init,
    (ActorFunc)EnZod_Destroy,
    (ActorFunc)EnZod_Update,
    (ActorFunc)EnZod_Draw,
};
*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/EnZod_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/EnZod_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF1EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF2B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF338.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF3E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF4D8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF7CC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAF99C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFA44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFADC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFB84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFC00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFC10.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFD00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFDB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFE34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BAFF14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/EnZod_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BB0128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BB0170.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/func_80BB01B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zod_0x80BAEF70/EnZod_Draw.asm")
