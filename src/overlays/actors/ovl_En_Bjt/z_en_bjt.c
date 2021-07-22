#include "z_en_bjt.h"

#define FLAGS 0x00000009

#define THIS ((EnBjt*)thisx)

void EnBjt_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBjt_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bjt_InitVars = {
    ACTOR_EN_BJT,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_BJT,
    sizeof(EnBjt),
    (ActorFunc)EnBjt_Init,
    (ActorFunc)EnBjt_Destroy,
    (ActorFunc)EnBjt_Update,
    (ActorFunc)EnBjt_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BFDF48 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 68, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80BFDF74 = { 0, 0, 0, 0, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80BFDF48;
extern CollisionCheckInfoInit2 D_80BFDF74;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD2E0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD30C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD3A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD434.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD5E4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD6BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD8F0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFD984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFDA48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/func_80BFDAE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/EnBjt_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/EnBjt_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/EnBjt_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bjt_0x80BFD2E0/EnBjt_Draw.asm")
