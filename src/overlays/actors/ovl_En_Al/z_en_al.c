#include "z_en_al.h"

#define FLAGS 0x00000039

#define THIS ((EnAl*)thisx)

void EnAl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Al_InitVars = {
    ACTOR_EN_AL,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AL,
    sizeof(EnAl),
    (ActorFunc)EnAl_Init,
    (ActorFunc)EnAl_Destroy,
    (ActorFunc)EnAl_Update,
    (ActorFunc)EnAl_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BDFFB8 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 14, 62, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BDFFE4 = { 0, 0, 0, 0, MASS_IMMOVABLE };

#endif

extern ColliderCylinderInit D_80BDFFB8;
extern CollisionCheckInfoInit2 D_80BDFFE4;

extern UNK_TYPE D_0600A0D8;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE1A0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE250.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE27C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE318.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE384.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE408.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE484.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE4E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE678.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE7FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDE92C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEA14.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEABC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEC2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDED20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEE5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEF3C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDEFE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF064.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF244.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF308.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF568.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF578.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF5E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF6C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/EnAl_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/EnAl_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/EnAl_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF914.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDF950.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/func_80BDFA34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Al/EnAl_Draw.s")
