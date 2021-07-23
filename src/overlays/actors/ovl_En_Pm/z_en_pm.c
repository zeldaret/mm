#include "z_en_pm.h"

#define FLAGS 0x00000039

#define THIS ((EnPm*)thisx)

void EnPm_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPm_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Pm_InitVars = {
    ACTOR_EN_PM,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MM,
    sizeof(EnPm),
    (ActorFunc)EnPm_Init,
    (ActorFunc)EnPm_Destroy,
    (ActorFunc)EnPm_Update,
    (ActorFunc)EnPm_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80AFB790 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};


// static ColliderSphereInit sSphereInit = {
static ColliderSphereInit D_80AFB7BC = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_SPHERE, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 0, { { 0, 0, 0 }, 26 }, 100 },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80AFB7E8 = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80AFB790;
extern ColliderSphereInit D_80AFB7BC;
extern CollisionCheckInfoInit2 D_80AFB7E8;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7B40.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7BAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7CB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7D60.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7DC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7E6C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7E98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF7F68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF80F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF81E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8348.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8478.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8540.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF86F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF87C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8890.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF898C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8AC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8BA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8C68.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8D84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8DD4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF8ED4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9008.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF91E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF94AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF95E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF98A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF992C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9A0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9AB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9B54.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9BF8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9D04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AF9E7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA170.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA334.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA438.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA4D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA5FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFA724.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/EnPm_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/EnPm_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/EnPm_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFAA04.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFAA44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/func_80AFABAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Pm/EnPm_Draw.s")
