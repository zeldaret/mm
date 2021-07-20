#include "z_en_cow.h"

#define FLAGS 0x00000009

#define THIS ((EnCow*)thisx)

void EnCow_Init(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Update(Actor* thisx, GlobalContext* globalCtx);
void EnCow_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit En_Cow_InitVars = {
    ACTOR_EN_COW,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_COW,
    sizeof(EnCow),
    (ActorFunc)EnCow_Init,
    (ActorFunc)EnCow_Destroy,
    (ActorFunc)EnCow_Update,
    (ActorFunc)EnCow_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_8099D610 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099C290.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099C328.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099C41C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/EnCow_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/EnCow_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099C880.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CAA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CB20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CB68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CBCC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CC68.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CCF8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CDA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099CFAC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/EnCow_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099D3C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099D4AC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099D4FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/EnCow_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Cow_0x8099C290/func_8099D59C.asm")
