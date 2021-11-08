/*
 * File: z_en_ah.c
 * Overlay: ovl_En_Ah
 * Description: Anju's Mother
 */

#include "z_en_ah.h"

#define FLAGS 0x00000039

#define THIS ((EnAh*)thisx)

void EnAh_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAh_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD36B8(EnAh* this, GlobalContext* globalCtx);
void func_80BD3768(EnAh* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ah_InitVars = {
    ACTOR_EN_AH,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AH,
    sizeof(EnAh),
    (ActorFunc)EnAh_Init,
    (ActorFunc)EnAh_Destroy,
    (ActorFunc)EnAh_Update,
    (ActorFunc)EnAh_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD3E34 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BD3E60 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80BD3E34;
extern CollisionCheckInfoInit2 D_80BD3E60;

extern UNK_TYPE D_06009E70;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2A30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2B0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2BA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2BE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2C6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2DA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2DC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD2FD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD30C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3118.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3198.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3294.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3320.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3374.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD33FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3548.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD35BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3658.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD36B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3768.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/EnAh_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/EnAh_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/EnAh_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3AA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/func_80BD3AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ah/EnAh_Draw.s")
