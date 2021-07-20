#include "z_en_pst.h"

#define FLAGS 0x00000001

#define THIS ((EnPst*)thisx)

void EnPst_Init(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Update(Actor* thisx, GlobalContext* globalCtx);
void EnPst_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Pst_InitVars = {
    ACTOR_EN_PST,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_PST,
    sizeof(EnPst),
    (ActorFunc)EnPst_Init,
    (ActorFunc)EnPst_Destroy,
    (ActorFunc)EnPst_Update,
    (ActorFunc)EnPst_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B2C4B8 = {
    { COLTYPE_HIT1, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0x00000000, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 28, 72, 0, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit2 D_80B2C4E4 = { 1, 0, 0, 0, MASS_IMMOVABLE };

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2B830.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2B874.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2B8F4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2B974.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BAA4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BBFC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BCF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BD30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BD88.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BD98.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2BE54.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/EnPst_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/EnPst_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/EnPst_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/func_80B2C11C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Pst_0x80B2B830/EnPst_Draw.asm")
