/*
 * File: z_en_bombal.c
 * Overlay: ovl_En_Bombal
 * Description: Bombers - Majora Balloon
 */

#include "z_en_bombal.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnBombal*)thisx)

void EnBombal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C05B3C(EnBombal* this, GlobalContext* globalCtx);
void func_80C05C44(EnBombal* this, GlobalContext* globalCtx);
void func_80C05DE8(EnBombal* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bombal_InitVars = {
    ACTOR_EN_BOMBAL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnBombal),
    (ActorFunc)EnBombal_Init,
    (ActorFunc)EnBombal_Destroy,
    (ActorFunc)EnBombal_Update,
    (ActorFunc)EnBombal_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C06460 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x004138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 60, 90, -50, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C06460;

extern UNK_TYPE D_06000A00;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05B24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05B3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/EnBombal_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C05F90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C060B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombal/func_80C06208.s")
