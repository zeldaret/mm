#include "z_bg_open_spot.h"

#define FLAGS 0x00000010

#define THIS ((BgOpenSpot*)thisx)

void BgOpenSpot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgOpenSpot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgOpenSpot_Update(Actor* thisx, GlobalContext* globalCtx);

#if 0
const ActorInit Bg_Open_Spot_InitVars = {
    ACTOR_BG_OPEN_SPOT,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(BgOpenSpot),
    (ActorFunc)BgOpenSpot_Init,
    (ActorFunc)BgOpenSpot_Destroy,
    (ActorFunc)BgOpenSpot_Update,
    (ActorFunc)NULL,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80ACB3B0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 560, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 800, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};


extern InitChainEntry D_80ACB3B0[];
#endif

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Spot_0x80ACB1E0/BgOpenSpot_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Spot_0x80ACB1E0/BgOpenSpot_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Spot_0x80ACB1E0/BgOpenSpot_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Open_Spot_0x80ACB1E0/func_80ACB2B0.asm")
