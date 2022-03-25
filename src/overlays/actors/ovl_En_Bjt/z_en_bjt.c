/*
 * File: z_en_bjt.c
 * Overlay: ovl_En_Bjt
 * Description: ??? (Hand in toilet)
 */

#include "z_en_bjt.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnBjt*)thisx)

void EnBjt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BFDA48(EnBjt* this, GlobalContext* globalCtx);
void func_80BFDAE8(EnBjt* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bjt_InitVars = {
    ACTOR_EN_BJT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJT,
    sizeof(EnBjt),
    (ActorFunc)EnBjt_Init,
    (ActorFunc)EnBjt_Destroy,
    (ActorFunc)EnBjt_Update,
    (ActorFunc)EnBjt_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFDF48 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BFDF74 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80BFDF48;
extern CollisionCheckInfoInit2 D_80BFDF74;

extern UNK_TYPE D_06002390;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD2E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD30C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD3A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD434.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD4FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD5E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD6BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD8F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFD984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFDA48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/func_80BFDAE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bjt/EnBjt_Draw.s")
