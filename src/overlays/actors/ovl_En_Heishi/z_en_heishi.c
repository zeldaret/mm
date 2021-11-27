/*
 * File: z_en_heishi.c
 * Overlay: ovl_En_Heishi
 * Description: Soldier
 */

#include "z_en_heishi.h"

#define FLAGS 0x00000009

#define THIS ((EnHeishi*)thisx)

void EnHeishi_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Update(Actor* thisx, GlobalContext* globalCtx);
void EnHeishi_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BE9214(EnHeishi* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Heishi_InitVars = {
    ACTOR_EN_HEISHI,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_SDN,
    sizeof(EnHeishi),
    (ActorFunc)EnHeishi_Init,
    (ActorFunc)EnHeishi_Destroy,
    (ActorFunc)EnHeishi_Update,
    (ActorFunc)EnHeishi_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE9450 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BE9450;

extern UNK_TYPE D_06003BFC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE90BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9148.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE91DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9214.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/func_80BE9380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Heishi/EnHeishi_Draw.s")
