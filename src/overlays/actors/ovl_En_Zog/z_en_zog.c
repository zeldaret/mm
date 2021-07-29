#include "z_en_zog.h"

#define FLAGS 0x00000009

#define THIS ((EnZog*)thisx)

void EnZog_Init(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Update(Actor* thisx, GlobalContext* globalCtx);
void EnZog_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Zog_InitVars = {
    ACTOR_EN_ZOG,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_ZOG,
    sizeof(EnZog),
    (ActorFunc)EnZog_Init,
    (ActorFunc)EnZog_Destroy,
    (ActorFunc)EnZog_Update,
    (ActorFunc)EnZog_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B95880 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_80B95880;
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93468.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/EnZog_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/EnZog_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B939C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93A48.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93B44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93BA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93BE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93D2C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B93EA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B943A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B943C0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B943EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B94470.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B9451C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B9461C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B946B4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B946FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B948A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B94A00.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B94C5C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B94D0C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B94E34.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B95128.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B95240.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/EnZog_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B954C4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/func_80B95598.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Zog_0x80B93310/EnZog_Draw.asm")
