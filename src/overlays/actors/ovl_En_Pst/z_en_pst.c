/*
 * File: z_en_pst.c
 * Overlay: ovl_En_Pst
 * Description: Postbox
 */

#include "z_en_pst.h"

#define FLAGS (ACTOR_FLAG_1)

#define THIS ((EnPst*)thisx)

void EnPst_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B2BD98(EnPst* this, GlobalContext* globalCtx);
void func_80B2BE54(EnPst* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Pst_InitVars = {
    ACTOR_EN_PST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B2C4B8 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 28, 72, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B2C4E4 = { 1, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80B2C4B8;
extern CollisionCheckInfoInit2 D_80B2C4E4;

extern UNK_TYPE D_06001A80;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B830.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B874.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B8F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2B974.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BAA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BBFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BCF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BD98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2BE54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/func_80B2C11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pst/EnPst_Draw.s")
