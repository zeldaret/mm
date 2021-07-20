#include "z_bg_danpei_movebg.h"

#define FLAGS 0x00000010

#define THIS ((BgDanpeiMovebg*)thisx)

void BgDanpeiMovebg_Init(Actor* thisx, GlobalContext* globalCtx);
void BgDanpeiMovebg_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgDanpeiMovebg_Update(Actor* thisx, GlobalContext* globalCtx);

/*

const ActorInit Bg_Danpei_Movebg_InitVars = {
    ACTOR_BG_DANPEI_MOVEBG,
    ACTORCAT_BG,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(BgDanpeiMovebg),
    (ActorFunc)BgDanpeiMovebg_Init,
    (ActorFunc)BgDanpeiMovebg_Destroy,
    (ActorFunc)BgDanpeiMovebg_Update,
    (ActorFunc)NULL,
};


// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AF753C[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

*/

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF6DE0.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/BgDanpeiMovebg_Init.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF6EA8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/BgDanpeiMovebg_Destroy.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/BgDanpeiMovebg_Update.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF705C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF70FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF71FC.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF72F8.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF7354.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF746C.asm")

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg_0x80AF6DE0/func_80AF74CC.asm")
