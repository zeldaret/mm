#include "z_en_wiz_fire.h"

#define FLAGS 0x08000015

#define THIS ((EnWizFire*)thisx)

void EnWizFire_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit En_Wiz_Fire_InitVars = {
    ACTOR_EN_WIZ_FIRE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizFire),
    (ActorFunc)EnWizFire_Init,
    (ActorFunc)EnWizFire_Destroy,
    (ActorFunc)EnWizFire_Update,
    (ActorFunc)EnWizFire_Draw
};
*/

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
