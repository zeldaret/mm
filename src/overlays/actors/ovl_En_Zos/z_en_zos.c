#include "z_en_zos.h"

#define FLAGS 0x02000009

#define THIS ((EnZos*)thisx)

void EnZos_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZos_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zos_InitVars = {
    ACTOR_EN_ZOS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOS,
    sizeof(EnZos),
    (ActorFunc)EnZos_Init,
    (ActorFunc)EnZos_Destroy,
    (ActorFunc)EnZos_Update,
    (ActorFunc)EnZos_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BBC6F0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 60, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80BBC6F0;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/EnZos_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/EnZos_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBAE84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBAF5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBAFFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB0D4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB15C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB2C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB414.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB4CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB574.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB718.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBB8AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBBB84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBBCBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBBD5C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBBDE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBBFBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC070.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC14C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC22C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC24C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC298.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC37C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/EnZos_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC4E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/func_80BBC500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zos/EnZos_Draw.s")
