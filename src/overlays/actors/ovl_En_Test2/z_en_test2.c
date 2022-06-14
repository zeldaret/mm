/*
 * File: z_en_test2.c
 * Overlay: ovl_En_Test2
 * Description: Objects affected by the Lens of Truth
 */

#include "z_en_test2.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_80)

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest2_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit En_Test2_InitVars = {
    ACTOR_EN_TEST2,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTest2),
    (ActorFunc)EnTest2_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)EnTest2_Update,
    (ActorFunc)NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80A3E74C[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 8000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 800, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 2500, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80A3E74C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/EnTest2_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E4EC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Test2/func_80A3E524.s")
