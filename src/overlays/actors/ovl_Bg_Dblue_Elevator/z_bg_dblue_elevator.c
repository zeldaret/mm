/*
 * File: z_bg_dblue_elevator.c
 * Overlay: ovl_Bg_Dblue_Elevator
 * Description: Great Bay Temple - Elevator
 */

#include "z_bg_dblue_elevator.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgDblueElevator*)thisx)

void BgDblueElevator_Init(Actor* thisx, PlayState* play);
void BgDblueElevator_Destroy(Actor* thisx, PlayState* play);
void BgDblueElevator_Update(Actor* thisx, PlayState* play);
void BgDblueElevator_Draw(Actor* thisx, PlayState* play);

#if 0
ActorInit Bg_Dblue_Elevator_InitVars = {
    /**/ ACTOR_BG_DBLUE_ELEVATOR,
    /**/ ACTORCAT_BG,
    /**/ FLAGS,
    /**/ OBJECT_DBLUE_OBJECT,
    /**/ sizeof(BgDblueElevator),
    /**/ BgDblueElevator_Init,
    /**/ BgDblueElevator_Destroy,
    /**/ BgDblueElevator_Update,
    /**/ BgDblueElevator_Draw,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B929EC[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 250, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 250, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_80B929EC[];

extern UNK_TYPE D_060002C8;
extern UNK_TYPE D_060005C4;

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B91F20.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B91F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B922C0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B922FC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/BgDblueElevator_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/BgDblueElevator_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B924DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B924F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B9257C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B925B8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B92644.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/func_80B92660.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/BgDblueElevator_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Dblue_Elevator/BgDblueElevator_Draw.s")
