/*
 * File: z_title.c
 * Overlay: ovl_title
 * Description:
 */

#include "z_title.h"

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_UpdateCounters.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_RenderView.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_Draw.s")

void Title_Main(GameState* thisx);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_Main.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_title/Title_Init.s")
