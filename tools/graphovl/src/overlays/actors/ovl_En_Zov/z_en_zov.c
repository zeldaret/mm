#include "z_en_zov.h"

#define FLAGS 0x00000009

#define THIS ((EnZov*)thisx)

void EnZov_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZov_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD187C(EnZov* this, GlobalContext* globalCtx);
void func_80BD19FC(EnZov* this, GlobalContext* globalCtx);
void func_80BD1BF0(EnZov* this, GlobalContext* globalCtx);
void func_80BD1C38(EnZov* this, GlobalContext* globalCtx);
void func_80BD1C84(EnZov* this, GlobalContext* globalCtx);
void func_80BD1D94(EnZov* this, GlobalContext* globalCtx);
void func_80BD1DB8(EnZov* this, GlobalContext* globalCtx);
void func_80BD1F1C(EnZov* this, GlobalContext* globalCtx);

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

extern ColliderCylinderInit D_80BD26E0;

extern UNK_TYPE D_0600D3EC;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/EnZov_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/EnZov_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD13DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1440.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1470.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1570.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD15A4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD160C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1764.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD187C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD19FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1AE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1BF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1C38.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1C84.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1D30.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1D94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1DB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1F1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD1FC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/EnZov_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD2380.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/func_80BD2404.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Zov/EnZov_Draw.s")
