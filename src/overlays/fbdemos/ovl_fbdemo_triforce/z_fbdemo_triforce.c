/*
 * File: z_fbdemo_triforce.c
 * Overlay: ovl_fbdemo_triforce
 * Description:
 */

#include "z_fbdemo_triforce.h"

void* TransitionTriforce_Init(void* thisx);
void TransitionTriforce_Destroy(void* thisx);
void TransitionTriforce_Update(void* thisx, s32 updateRate);
void TransitionTriforce_Draw(void* thisx, Gfx** gfxP);
void TransitionTriforce_Start(void* thisx);
void TransitionTriforce_SetType(void* thisx, s32 type);
void TransitionTriforce_SetColor(void* thisx, u32 color);
s32 TransitionTriforce_IsDone(void* thisx);

#if 0
const TransitionInit TransitionTriforce_InitVars = {
    TransitionTriforce_Init,
    TransitionTriforce_Destroy,
    TransitionTriforce_Update,
    TransitionTriforce_Draw,
    TransitionTriforce_Start,
    TransitionTriforce_SetType,
    TransitionTriforce_SetColor,
    NULL,
    TransitionTriforce_IsDone,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Start.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_SetType.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/func_80AC5280.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_triforce/TransitionTriforce_IsDone.s")
