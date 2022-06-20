/*
 * File: z_en_onpuman.c
 * Overlay: ovl_En_Onpuman
 * Description: Monkey Instrument Prompt (unused)
 */

#include "z_en_onpuman.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((EnOnpuman*)thisx)

void EnOnpuman_Init(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnOnpuman_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Onpuman_InitVars = {
    ACTOR_EN_ONPUMAN,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnOnpuman),
    (ActorFunc)EnOnpuman_Init,
    (ActorFunc)EnOnpuman_Destroy,
    (ActorFunc)EnOnpuman_Update,
    (ActorFunc)NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B12390 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80B12390;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B11F78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1202C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B1217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/func_80B121D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Onpuman/EnOnpuman_Update.s")
