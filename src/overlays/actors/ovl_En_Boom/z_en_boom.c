/*
 * File: z_en_boom.c
 * Overlay: ovl_En_Boom
 * Description: Zora boomerangs
 */

#include "z_en_boom.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnBoom*)thisx)

void EnBoom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808A2918(EnBoom* this, GlobalContext* globalCtx);

void EnBoom_SetupAction(EnBoom* this, EnBoomActionFunc actionFunc);

#if 0
const ActorInit En_Boom_InitVars = {
    ACTOR_EN_BOOM,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBoom),
    (ActorFunc)EnBoom_Init,
    (ActorFunc)EnBoom_Destroy,
    (ActorFunc)EnBoom_Update,
    (ActorFunc)EnBoom_Draw,
};

// static ColliderQuadInit sQuadInit = {
static ColliderQuadInit D_808A3010 = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_PLAYER, AC_NONE, OC1_NONE, OC2_TYPE_PLAYER, COLSHAPE_QUAD, },
    { ELEMTYPE_UNK2, { 0x00000010, 0x00, 0x02 }, { 0xF7CFFFFF, 0x00, 0x00 }, TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL, BUMP_NONE, OCELEM_NONE, },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_808A3060[] = {
    ICHAIN_S8(targetMode, 5, ICHAIN_CONTINUE),
    ICHAIN_VEC3S(shape.rot, 0, ICHAIN_STOP),
};

#endif

extern ColliderQuadInit D_808A3010;
extern InitChainEntry D_808A3060[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/EnBoom_SetupAction.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/func_808A24DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/EnBoom_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/EnBoom_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/func_808A2918.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/EnBoom_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Boom/EnBoom_Draw.s")
