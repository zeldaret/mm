#include "z_en_ig.h"

#define FLAGS 0x00000019

#define THIS ((EnIg*)thisx)

void EnIg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Ig_InitVars = {
    ACTOR_EN_IG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_DAI,
    sizeof(EnIg),
    (ActorFunc)EnIg_Init,
    (ActorFunc)EnIg_Destroy,
    (ActorFunc)EnIg_Update,
    (ActorFunc)EnIg_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BF3418 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 28, 62, 0, { 0, 0, 0 } },
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80BF3444 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 20 }, 100 },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BF3470 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1150.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1200.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1258.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1284.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF13E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF146C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF14B0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF15EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF16C8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1744.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF17BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1920.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF19A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1A60.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1B40.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1C44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1D78.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1DF4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF1FA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF219C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2368.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2400.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF25E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2890.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF293C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2A50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2AF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2BD4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/EnIg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/EnIg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/EnIg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2EDC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF2EFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/func_80BF302C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Ig_0x80BF1150/EnIg_Draw.asm")
