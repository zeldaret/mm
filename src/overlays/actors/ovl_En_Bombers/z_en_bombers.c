#include "z_en_bombers.h"

#define FLAGS 0x00000009

#define THIS ((EnBombers*)thisx)

void EnBombers_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombers_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Bombers_InitVars = {
    ACTOR_EN_BOMBERS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_CS,
    sizeof(EnBombers),
    (ActorFunc)EnBombers_Init,
    (ActorFunc)EnBombers_Destroy,
    (ActorFunc)EnBombers_Update,
    (ActorFunc)EnBombers_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80C04770 = {
    { COLTYPE_NONE, AT_NONE, AC_NONE, OC1_ON | OC1_TYPE_PLAYER, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_ON, },
    { 10, 30, 0, { 0, 0, 0 } },
};

#endif

extern ColliderCylinderInit D_80C04770;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/EnBombers_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/EnBombers_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C03824.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C038B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C039A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C03ACC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C03AF4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C03F64.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C03FAC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C042F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C04354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C043C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/EnBombers_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/func_80C045B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Bombers/EnBombers_Draw.s")
