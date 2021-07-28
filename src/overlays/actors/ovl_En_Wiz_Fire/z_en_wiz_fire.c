#include "z_en_wiz_fire.h"

#define FLAGS 0x08000015

#define THIS ((EnWizFire*)thisx)

void EnWizFire_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Wiz_Fire_InitVars = {
    ACTOR_EN_WIZ_FIRE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizFire),
    (ActorFunc)EnWizFire_Init,
    (ActorFunc)EnWizFire_Destroy,
    (ActorFunc)EnWizFire_Update,
    (ActorFunc)EnWizFire_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80A4C1E4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x09, 0x10 }, { 0x01001202, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 0, 0, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80A4C1E4;

extern UNK_TYPE D_06000FD8;
extern UNK_TYPE D_06002630;
extern UNK_TYPE D_06002B40;
extern UNK_TYPE D_06003120;
extern UNK_TYPE D_06005190;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/EnWizFire_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/EnWizFire_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4984C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A49A44.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A49F38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A49FD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4A11C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4A608.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/EnWizFire_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4B0C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4B33C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/EnWizFire_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4BAB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4BC74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4BDDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Wiz_Fire/func_80A4BF78.s")
