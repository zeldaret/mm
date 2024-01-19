/*
 * File: z_en_kitan.c
 * Overlay: ovl_En_Kitan
 * Description:
 */

#include "z_en_kitan.h"

#define FLAGS (ACTOR_FLAG_TARGETABLE | ACTOR_FLAG_FRIENDLY)

#define THIS ((EnKitan*)thisx)

void EnKitan_Init(Actor* thisx, PlayState* play);
void EnKitan_Destroy(Actor* thisx, PlayState* play);
void EnKitan_Update(Actor* thisx, PlayState* play);

#if 0
ActorInit En_Kitan_InitVars = {
    /**/ ACTOR_EN_KITAN,
    /**/ ACTORCAT_NPC,
    /**/ FLAGS,
    /**/ OBJECT_KITAN,
    /**/ sizeof(EnKitan),
    /**/ EnKitan_Init,
    /**/ EnKitan_Destroy,
    /**/ EnKitan_Update,
    /**/ NULL,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C09D50 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C09D50;

extern UNK_TYPE D_06000CE8;
extern UNK_TYPE D_06002770;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C0923C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09390.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09418.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C094A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09518.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C095C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09648.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09708.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09990.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09AA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09B50.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/EnKitan_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09C74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09C90.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Kitan/func_80C09CD0.s")
