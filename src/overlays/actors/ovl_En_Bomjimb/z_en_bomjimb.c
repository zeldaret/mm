/*
 * File z_en_bomjimb.c
 * Overlay: ovl_En_Bomjimb
 * Description: Bombers when chasing them
 */

#include "z_en_bomjimb.h"

#define FLAGS 0x00000009

#define THIS ((EnBomjimb*)thisx)

void EnBomjimb_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBomjimb_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C014E4(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01A24(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01B74(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C01CD0(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C0201C(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C0217C(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02570(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02704(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02A14(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02BCC(EnBomjimb* this, GlobalContext* globalCtx);
void func_80C02DAC(EnBomjimb* this, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bomjimb_InitVars = {
    ACTOR_EN_BOMJIMB,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBomjimb),
    (ActorFunc)EnBomjimb_Init,
    (ActorFunc)EnBomjimb_Destroy,
    (ActorFunc)EnBomjimb_Update,
    (ActorFunc)EnBomjimb_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C03194 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 30, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C03194;

extern UNK_TYPE D_060064B8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/EnBomjimb_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/EnBomjimb_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C0113C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C011CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C012E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C012FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C013B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C013F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01494.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C014E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01984.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01A24.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01B74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01C18.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01CD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C01FD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C0201C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02108.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C0217C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C0250C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C0267C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02704.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02740.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02A14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02BCC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02CA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02DAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/EnBomjimb_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/func_80C02FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bomjimb/EnBomjimb_Draw.s")
