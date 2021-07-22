#include "z_en_test2.h"

#define FLAGS 0x00000090

#define THIS ((EnTest2*)thisx)

void EnTest2_Init(Actor* thisx, GlobalContext* globalCtx);
void EnTest2_Update(Actor* thisx, GlobalContext* globalCtx);

#if(0)
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


extern InitChainEntry D_80A3E74C[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test2_0x80A3E390/EnTest2_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test2_0x80A3E390/EnTest2_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test2_0x80A3E390/func_80A3E4EC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_En_Test2_0x80A3E390/func_80A3E524.asm")
