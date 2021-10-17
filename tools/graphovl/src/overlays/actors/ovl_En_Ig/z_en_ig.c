#include "z_en_ig.h"

#define FLAGS 0x00000019

#define THIS ((EnIg*)thisx)

void EnIg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnIg_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BF2AF8(EnIg* this, GlobalContext* globalCtx);
void func_80BF2BD4(EnIg* this, GlobalContext* globalCtx);

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

extern ColliderCylinderInit D_80BF3418;
extern ColliderSphereInit D_80BF3444;
extern CollisionCheckInfoInit2 D_80BF3470;

extern UNK_TYPE D_06008710;
extern UNK_TYPE D_0600C538;
extern UNK_TYPE D_060130D0;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1150.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1200.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1258.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1284.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF13E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF146C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF14B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF15EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF16C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1744.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF17BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1920.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF19A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1A60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1C44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1D78.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1DF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF1FA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF219C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2368.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2400.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF25E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF293C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2A50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2AF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2BD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/EnIg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/EnIg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/EnIg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2EDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF2EFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/func_80BF302C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ig/EnIg_Draw.s")
