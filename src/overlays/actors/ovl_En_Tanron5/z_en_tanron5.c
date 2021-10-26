#include "z_en_tanron5.h"

#define FLAGS 0x00000030

#define THIS ((EnTanron5*)thisx)

void EnTanron5_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Update(Actor* thisx, GlobalContext* globalCtx);
void EnTanron5_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Tanron5_InitVars = {
    ACTOR_EN_TANRON5,
    ACTORCAT_BOSS,
    FLAGS,
    OBJECT_BOSS02,
    sizeof(EnTanron5),
    (ActorFunc)EnTanron5_Init,
    (ActorFunc)EnTanron5_Destroy,
    (ActorFunc)EnTanron5_Update,
    (ActorFunc)EnTanron5_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE5DA4 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ALL, AC_ON | AC_TYPE_PLAYER | AC_TYPE_ENEMY | AC_TYPE_OTHER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK2, { 0xF7CFFFFF, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 70, 450, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BE5DA4;

extern UNK_TYPE D_06007A88;
extern UNK_TYPE D_06007D18;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE4930.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE4A2C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE5818.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/EnTanron5_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Tanron5/func_80BE5C10.s")
