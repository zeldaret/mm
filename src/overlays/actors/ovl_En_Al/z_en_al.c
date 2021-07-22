#include "z_en_al.h"

#define FLAGS 0x00000039

#define THIS ((EnAl*)thisx)

void EnAl_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAl_Draw(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


extern ColliderCylinderInit D_80BDFFB8;
extern CollisionCheckInfoInit2 D_80BDFFE4;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE1A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE250.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE27C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE318.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE384.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE408.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE484.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE4E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE678.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE7FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDE92C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEA14.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEABC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEC2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDED20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEE5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEF3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDEFE4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF064.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF244.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF308.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF390.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF414.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF568.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF578.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF5E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF6C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/EnAl_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/EnAl_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/EnAl_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF914.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDF950.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/func_80BDFA34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Al_0x80BDE1A0/EnAl_Draw.asm")
