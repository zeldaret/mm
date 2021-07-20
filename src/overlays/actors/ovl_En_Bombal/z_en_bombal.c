#include "z_en_bombal.h"

#define FLAGS 0x00000010

#define THIS ((EnBombal*)thisx)

void EnBombal_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombal_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0

const ActorInit En_Bombal_InitVars = {
    ACTOR_EN_BOMBAL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_FUSEN,
    sizeof(EnBombal),
    (ActorFunc)EnBombal_Init,
    (ActorFunc)EnBombal_Destroy,
    (ActorFunc)EnBombal_Update,
    (ActorFunc)EnBombal_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C06460 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0x004138B0, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
    { 60, 90, -50, { 0, 0, 0 } },
};

#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/EnBombal_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/EnBombal_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C05B24.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C05B3C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C05C44.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C05DE8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/EnBombal_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/EnBombal_Draw.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C05F90.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C060B8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Bombal_0x80C05A70/func_80C06208.asm")
