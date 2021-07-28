#include "z_en_elforg.h"

#define FLAGS 0x00000010

#define THIS ((EnElforg*)thisx)

void EnElforg_Init(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Update(Actor* thisx, GlobalContext* globalCtx);
void EnElforg_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Elforg_InitVars = {
    ACTOR_EN_ELFORG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnElforg),
    (ActorFunc)EnElforg_Init,
    (ActorFunc)EnElforg_Destroy,
    (ActorFunc)EnElforg_Update,
    (ActorFunc)EnElforg_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80ACDA30 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 16, 32, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80ACDA30;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/EnElforg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/EnElforg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC7E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC8D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC934.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACC994.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCAC0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCBB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCBD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCC98.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCE4C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACCEB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD088.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD164.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD1F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD2E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD59C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD610.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD6A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD6EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/EnElforg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/func_80ACD878.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Elforg/EnElforg_Draw.s")
