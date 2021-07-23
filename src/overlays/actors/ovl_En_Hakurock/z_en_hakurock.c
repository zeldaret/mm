#include "z_en_hakurock.h"

#define FLAGS 0x00000030

#define THIS ((EnHakurock*)thisx)

void EnHakurock_Init(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnHakurock_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Hakurock_InitVars = {
    ACTOR_EN_HAKUROCK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    OBJECT_BOSS_HAKUGIN,
    sizeof(EnHakurock),
    (ActorFunc)EnHakurock_Init,
    (ActorFunc)EnHakurock_Destroy,
    (ActorFunc)EnHakurock_Update,
    (ActorFunc)NULL,
};


// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80B22A80 = {
    { COLTYPE_HARD, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_HARD | AC_TYPE_PLAYER, OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL, OC2_TYPE_1, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0x20000000, 0x00, 0x00 }, { 0xF3CFBBFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_HARD, BUMP_ON, OCELEM_ON, },
    { 60, 60, -30, { 0, 0, 0 } },
};


// sColChkInfoInit
static CollisionCheckInfoInit D_80B22AAC = { 0, 60, 60, MASS_IMMOVABLE };


extern ColliderCylinderInit D_80B22A80;
extern CollisionCheckInfoInit D_80B22AAC;
#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21BE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B21FFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22040.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B220A8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B221E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B222AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B2242C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B224C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22500.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B226AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B22750.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/EnHakurock_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B228F4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Hakurock/func_80B229A4.s")
