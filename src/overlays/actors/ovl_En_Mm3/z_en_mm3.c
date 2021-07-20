#include "z_en_mm3.h"

#define FLAGS 0x00000019

#define THIS ((EnMm3*)thisx)

void EnMm3_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMm3_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Mm3_InitVars = {
    ACTOR_EN_MM3,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnMm3),
    (ActorFunc)EnMm3_Init,
    (ActorFunc)EnMm3_Destroy,
    (ActorFunc)EnMm3_Update,
    (ActorFunc)EnMm3_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A703F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 63, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80A7041C = { 0, 0, 0, 0, MASS_IMMOVABLE };

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/EnMm3_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/EnMm3_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F22C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F270.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F2C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F3B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F5E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F9C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6F9DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FBA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FBFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FE1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FE30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FED8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FEEC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A6FFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A70084.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/EnMm3_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A701E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/func_80A702B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Mm3_0x80A6F0A0/EnMm3_Draw.asm")
