#include "z_en_boom.h"

#define FLAGS 0x00000030

#define THIS ((EnBoom*)thisx)

void EnBoom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBoom_Draw(Actor* thisx, GlobalContext* globalCtx);

/*

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
    ICHAIN_VEC3S(shape, 0, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/func_808A24D0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/func_808A24DC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/EnBoom_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/EnBoom_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/func_808A2918.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/EnBoom_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Boom_0x808A24D0/EnBoom_Draw.asm")
