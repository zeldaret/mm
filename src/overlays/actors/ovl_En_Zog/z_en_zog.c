/*
 * File: z_en_zog.c
 * Overlay: ovl_En_Zog
 * Description: Mikau
 */

#include "z_en_zog.h"

#define FLAGS 0x00000009

#define THIS ((EnZog*)thisx)

void EnZog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B943A0(EnZog* this, GlobalContext* globalCtx);
void func_80B943C0(EnZog* this, GlobalContext* globalCtx);
void func_80B94470(EnZog* this, GlobalContext* globalCtx);
void func_80B9451C(EnZog* this, GlobalContext* globalCtx);
void func_80B9461C(EnZog* this, GlobalContext* globalCtx);
void func_80B946B4(EnZog* this, GlobalContext* globalCtx);
void func_80B946FC(EnZog* this, GlobalContext* globalCtx);
void func_80B948A8(EnZog* this, GlobalContext* globalCtx);
void func_80B94A00(EnZog* this, GlobalContext* globalCtx);
void func_80B94C5C(EnZog* this, GlobalContext* globalCtx);
void func_80B94D0C(EnZog* this, GlobalContext* globalCtx);
void func_80B94E34(EnZog* this, GlobalContext* globalCtx);
void func_80B95128(EnZog* this, GlobalContext* globalCtx);
void func_80B95240(EnZog* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zog_InitVars = {
    ACTOR_EN_ZOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOG,
    sizeof(EnZog),
    (ActorFunc)EnZog_Init,
    (ActorFunc)EnZog_Destroy,
    (ActorFunc)EnZog_Update,
    (ActorFunc)EnZog_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B95880 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80B95880;

extern UNK_TYPE D_0600FC0C;
extern UNK_TYPE D_060280A8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93310.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93468.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/EnZog_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/EnZog_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B939C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93A48.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93B44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93D2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93DE8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B93EA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B943A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B943C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B943EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B94470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B9451C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B9461C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B946B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B946FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B948A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B94A00.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B94C5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B94D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B94E34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B95128.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B95240.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/EnZog_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B954C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/func_80B95598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zog/EnZog_Draw.s")
