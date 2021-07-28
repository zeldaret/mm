#include "z_en_muto.h"

#define FLAGS 0x00000009

#define THIS ((EnMuto*)thisx)

void EnMuto_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMuto_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Muto_InitVars = {
    ACTOR_EN_MUTO,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_TORYO,
    sizeof(EnMuto),
    (ActorFunc)EnMuto_Init,
    (ActorFunc)EnMuto_Destroy,
    (ActorFunc)EnMuto_Update,
    (ActorFunc)EnMuto_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80BE841C = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 20, 60, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80BE841C;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/EnMuto_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/EnMuto_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7C94.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7D20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7DB4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7DEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7F88.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE7FEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/EnMuto_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/func_80BE8328.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Muto/EnMuto_Draw.s")
