/*
 * File: z_daytelop.c
 * Overlay: ovl_daytelop
 * Description:
 */

#include "z_daytelop.h"

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Draw.s")

void Daytelop_Main(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Main.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_nop80815770.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_LoadGraphics.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_daytelop/Daytelop_Init.s")
