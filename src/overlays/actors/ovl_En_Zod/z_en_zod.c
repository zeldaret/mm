/*
 * File: z_en_zod.c
 * Overlay: ovl_En_Zod
 * Description: Zora Drummer Tijo
 */

#include "z_en_zod.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnZod*)thisx)

void EnZod_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZod_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
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

#endif

extern ColliderCylinderInit D_80BB0540;

extern UNK_TYPE D_06000D94;
extern UNK_TYPE D_06007650;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF1EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF2B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF338.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF3E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF4D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF7CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAF99C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFADC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFB84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFC10.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFD00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFDB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFE34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BAFF14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB0170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/func_80BB01B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zod/EnZod_Draw.s")
