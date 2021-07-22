#include "z_en_zod.h"

#define FLAGS 0x00000009

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BB0540 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 60, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BB0540;
#endif

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
