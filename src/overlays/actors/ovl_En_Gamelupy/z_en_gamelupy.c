/*
 * File: z_en_gamelupy.c
 * Overlay: ovl_En_Gamelupy
 * Description: Deku Scrub Playground Rupees
 */

#include "z_en_gamelupy.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnGamelupy*)thisx)

void EnGamelupy_Init(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Update(Actor* thisx, GlobalContext* globalCtx);
void EnGamelupy_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AF6958(EnGamelupy* this, GlobalContext* globalCtx);
void func_80AF69A8(EnGamelupy* this, GlobalContext* globalCtx);
void func_80AF6A78(EnGamelupy* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Gamelupy_InitVars = {
    ACTOR_EN_GAMELUPY,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnGamelupy),
    (ActorFunc)EnGamelupy_Init,
    (ActorFunc)EnGamelupy_Destroy,
    (ActorFunc)EnGamelupy_Update,
    (ActorFunc)EnGamelupy_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AF6CF0 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_NO_PUSH | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 30, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80AF6CF0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/EnGamelupy_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/EnGamelupy_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6854.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6944.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6958.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF69A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6A38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6A78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/func_80AF6B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/EnGamelupy_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Gamelupy/EnGamelupy_Draw.s")
