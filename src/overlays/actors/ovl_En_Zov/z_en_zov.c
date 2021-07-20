#include "z_en_zov.h"

#define FLAGS 0x00000009

#define THIS ((EnZov*)thisx)

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Zov_InitVars = {
    ACTOR_EN_ZOV,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOV,
    sizeof(EnZov),
    (ActorFunc)EnZov_Init,
    (ActorFunc)EnZov_Destroy,
    (ActorFunc)EnZov_Update,
    (ActorFunc)EnZov_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BD26E0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 20, 40, 0, { 0, 0, 0 } },
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD13DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1440.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1570.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD15A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD160C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1764.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD187C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD19FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1AE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1BF0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1C38.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1C84.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1D30.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1D94.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1DB8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1F1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD1FC8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD2380.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/func_80BD2404.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zov_0x80BD11E0/EnZov_Draw.asm")
