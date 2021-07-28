#include "z_en_ms.h"

#define FLAGS 0x00000009

#define THIS ((EnMs*)thisx)

void EnMs_Init(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Update(Actor* thisx, GlobalContext* globalCtx);
void EnMs_Draw(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Ms_InitVars = {
    ACTOR_EN_MS,
    ACTORCAT_NPC,
    FLAGS,
    OBJECT_MS,
    sizeof(EnMs),
    (ActorFunc)EnMs_Init,
    (ActorFunc)EnMs_Destroy,
    (ActorFunc)EnMs_Update,
    (ActorFunc)EnMs_Draw,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_80952BA0 = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_HIT_PLAYER, COLSHAPE_JNTSPH, },
    { ELEMTYPE_UNK0, { 0x00000000, 0x00, 0x00 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_ON, },
    { 22, 37, 0, { 0, 0, 0 } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80952BCC[] = {
    ICHAIN_U8(targetMode, 2, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 500, ICHAIN_STOP),
};

#endif

extern ColliderCylinderInit D_80952BA0;
extern InitChainEntry D_80952BCC[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952734.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809527F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_809529AC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/func_80952A1C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Ms/EnMs_Draw.s")
