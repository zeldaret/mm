#include "z_en_sth.h"

#define FLAGS 0x00000009

#define THIS ((EnSth*)thisx)

void EnSth_Init(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnSth_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Sth_InitVars = {
    ACTOR_EN_STH,
    ACTORCAT_NPC,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnSth),
    (ActorFunc)EnSth_Init,
    (ActorFunc)EnSth_Destroy,
    (ActorFunc)EnSth_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B6D19C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_ENEMY, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 30, 40, 0, { 0, 0, 0 } },
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B6703C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B670A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67148.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B671A0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67208.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B672A4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67348.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67458.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67540.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B677BC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67838.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B678A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67958.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67984.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67AB4.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67B50.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67C1C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67DA0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B67E20.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/EnSth_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B680A8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B681E8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B68310.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Sth_0x80B66D30/func_80B6849C.asm")
