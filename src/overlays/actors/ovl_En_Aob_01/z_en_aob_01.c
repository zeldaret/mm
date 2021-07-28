#include "z_en_aob_01.h"

#define FLAGS 0x00000019

#define THIS ((EnAob01*)thisx)

void EnAob01_Init(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Update(Actor* thisx, GlobalContext* globalCtx);
void EnAob01_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Aob_01_InitVars = {
    ACTOR_EN_AOB_01,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_AOB,
    sizeof(EnAob01),
    (ActorFunc)EnAob01_Init,
    (ActorFunc)EnAob01_Destroy,
    (ActorFunc)EnAob01_Update,
    (ActorFunc)EnAob01_Draw,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809C3820 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK1, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 18, 64, 0, { 0, 0, 0 } },
};


extern ColliderCylinderInit D_809C3820;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C10B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1124.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1158.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C11EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1304.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1424.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C14D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C15BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C165C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C16DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C1EC8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2060.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C21E0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2504.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2594.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C25E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2680.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C26E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2730.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2788.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2824.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C28B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2A64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2BE4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2C9C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2EC4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2F34.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C2FA0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/EnAob01_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/EnAob01_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/EnAob01_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C33D8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C35B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/func_809C35F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Aob_01/EnAob01_Draw.s")
