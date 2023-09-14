#include "ultra64.h"
#include "z64light.h"
#include "z64math.h"

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x04 */ Vec3f offset;
    /* 0x10 */ Vec3f pos;
    /* 0x1C */ s8 pitch;
    /* 0x1D */ s8 roll;
    /* 0x1E */ u8 textureIndex;
    /* 0x1F */ u8 delayTimer;
} LightningBolt; // size = 0x20

// Variables are put before most headers as a hacky way to bypass bss reordering
struct LightningStrike;

extern u8 D_801F4E30;
extern u8 D_801F4E31;
extern u8 gCustomLensFlare1On;
extern Vec3f gCustomLensFlare1Pos;
extern f32 D_801F4E44;
extern f32 D_801F4E48;
extern s16 D_801F4E4C;
extern u8 gCustomLensFlare2On;
extern Vec3f gCustomLensFlare2Pos;
extern f32 D_801F4E5C;
extern f32 D_801F4E60;
extern s16 D_801F4E64;
extern struct LightningStrike gLightningStrike;
extern f32 D_801F4E74;
extern u16 D_801F4E78;
extern u16 gSkyboxNumStars;
extern LightningBolt sLightningBolts[3];
extern LightNode* sNGameOverLightNode;
extern LightInfo sNGameOverLightInfo;
extern LightNode* sSGameOverLightNode;
extern LightInfo sSGameOverLightInfo;
extern f32 sSunEnvAlpha;
extern f32 sSunColor;
extern f32 sSunScale;
extern f32 sSunPrimAlpha;
extern s32 sSunDepthTestX;
extern s32 sSunDepthTestY;
extern f32 D_801F4F28;
extern s16 sLightningFlashAlpha;
extern u16 sSandstormScroll;
extern u8 D_801F4F30;
extern u8 D_801F4F31;
extern u8 sEnvIsTimeStopped;
extern u8 D_801F4F33;
extern u8 sGameOverLightsIntensity;
extern Gfx* sSkyboxStarsDList;

#include "global.h"
#include "z64environment.h"

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GraphCallback.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_ZBufValToFixedPoint.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_SmoothStepToU8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpWeight.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpWeightAccelDecel.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateSkybox.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_EnableUnderwaterLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DisableUnderwaterLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6A04.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateSkyboxRotY.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateNextDayTime.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateTime.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6CEC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F6EA4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_IsSceneUpsideDown.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateSun.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F88C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800F8970.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdatePostmanEvents.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Update.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSun.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSunLensFlare.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLensFlare.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_RandCentered.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawRainImpl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawRain.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_ChangeLightSetting.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxFilters.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLightningFlash.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateLightningStrike.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_AddLightningBolts.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLightning.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_PlaySceneSequence.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateTimeBasedSequence.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawCustomLensFlare.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_InitGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FadeInGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FadeOutGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateRain.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FillScreen.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSandstorm.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_AdjustLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpRGB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpAmbientColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpDiffuseColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpFogColor.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpFog.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetBgsDayCount.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_ClearBgsDayCount.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetTotalDays.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_ForcePlaySequence.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_IsForcedSequenceDisabled.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_PlayStormNatureAmbience.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_StopStormNatureAmbience.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_WarpSongLeave.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_SetupSkyboxStars.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxStar.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxStarsImpl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxStars.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_StopTime.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_StartTime.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_IsTimeStopped.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetStormState.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_IsFinalHours.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FE5D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FE610.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetTimeSpeed.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_SetTimeJump.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FE6F8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetSandstormColorIndex.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetNextSandstormColorIndex.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_GetSandstormLerpScale.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpSandstormColors.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FE9B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FEA50.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FEAB0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_JumpForwardInTime.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/func_800FEAF4.s")
