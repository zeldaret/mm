/*
 * File: z_opening.c
 * Overlay: ovl_opening
 * Description:
 */

#include "z_opening.h"

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_opening/Opening_SetupForTitleCutscene.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_opening/func_80803EA0.s")

void Opening_Main(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_opening/Opening_Main.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_opening/Opening_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_opening/Opening_Init.s")
