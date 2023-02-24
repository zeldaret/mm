/*
 * File: z_bg_danpei_movebg.c
 * Overlay: ovl_Bg_Danpei_Movebg
 * Description: Moving platforms beneath Dampe's house
 */

#include "z_bg_danpei_movebg.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgDanpeiMovebg*)thisx)

void BgDanpeiMovebg_Init(Actor* thisx, PlayState* play);
void BgDanpeiMovebg_Destroy(Actor* thisx, PlayState* play);
void BgDanpeiMovebg_Update(Actor* thisx, PlayState* play);

#if 0
ActorInit Bg_Danpei_Movebg_InitVars = {
    /**/ ACTOR_BG_DANPEI_MOVEBG,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(BgDanpeiMovebg),
    /**/ BgDanpeiMovebg_Init,
    /**/ BgDanpeiMovebg_Destroy,
    /**/ BgDanpeiMovebg_Update,
    /**/ NULL,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80AF753C[] = {
    ICHAIN_F32(uncullZoneScale, 1500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1000, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80AF753C[];

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF6DE0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/BgDanpeiMovebg_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF6EA8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/BgDanpeiMovebg_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/BgDanpeiMovebg_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF705C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF70FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF71FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF72F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF7354.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF746C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Danpei_Movebg/func_80AF74CC.s")
