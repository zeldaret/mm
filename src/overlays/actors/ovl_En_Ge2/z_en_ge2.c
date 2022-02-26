/*
 * File: z_en_ge2.c
 * Overlay: ovl_En_Ge2
 * Description: Purple-clad Gerudo Pirate
 */

#include "z_en_ge2.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_80000000)

#define THIS ((EnGe2*)thisx)

void EnGe2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGe2_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B8BCEC(EnGe2* this, GlobalContext* globalCtx);
void func_80B8BD38(EnGe2* this, GlobalContext* globalCtx);
void func_80B8BE08(EnGe2* this, GlobalContext* globalCtx);
void func_80B8BF04(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C048(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C0B0(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C45C(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C59C(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C644(EnGe2* this, GlobalContext* globalCtx);
void func_80B8C9B8(EnGe2* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ge2_InitVars = {
    ACTOR_EN_GE2,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_GLA,
    sizeof(EnGe2),
    (ActorFunc)EnGe2_Init,
    (ActorFunc)EnGe2_Destroy,
    (ActorFunc)EnGe2_Update,
    (ActorFunc)EnGe2_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B8CE40 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x038BFBB3, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80B8CE40;

extern UNK_TYPE D_06008DD8;
extern UNK_TYPE D_060091D0;
extern UNK_TYPE D_06009D1C;
extern UNK_TYPE D_0600A344;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B514.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B5AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B6B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B7A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B848.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8B90C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BA40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BB3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BC1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BC78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BCEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BD38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BD90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BE08.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BF04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8BFC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C048.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C0B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C13C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C45C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8C9B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CC0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CCB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/func_80B8CCFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ge2/EnGe2_Draw.s")
