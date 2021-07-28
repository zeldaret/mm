/*
 * File: z_fbdemo_wipe3.c
 * Overlay: ovl_fbdemo_wipe3
 * Description:
 */

#include "z_fbdemo_wipe3.h"

void* TransitionWipe3_Init(void* thisx);
void TransitionWipe3_Destroy(void* thisx);
void TransitionWipe3_Update(void* thisx, s32 updateRate);
void TransitionWipe3_Draw(void* thisx, Gfx** gfxP);
void TransitionWipe3_Start(void* thisx);
void TransitionWipe3_SetType(void* thisx, s32 type);
void TransitionWipe3_SetColor(void* thisx, u32 color);
void TransitionWipe3_SetEnvColor(void* thisx, u32 color);
s32 TransitionWipe3_IsDone(void* thisx);

#if 0
const TransitionInit TransitionWipe3_InitVars = {
    TransitionWipe3_Init,
    TransitionWipe3_Destroy,
    TransitionWipe3_Update,
    TransitionWipe3_Draw,
    TransitionWipe3_Start,
    TransitionWipe3_SetType,
    TransitionWipe3_SetColor,
    TransitionWipe3_SetEnvColor,
    TransitionWipe3_IsDone,
};

#endif

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_Start.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/func_80AC68B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_IsDone.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_SetType.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_SetColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_fbdemo_wipe3/TransitionWipe3_SetEnvColor.s")
