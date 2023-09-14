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

u8 D_801F4E30;
u8 D_801F4E31;
u8 gCustomLensFlare1On;
Vec3f gCustomLensFlare1Pos;
f32 D_801F4E44;
f32 D_801F4E48;
s16 D_801F4E4C;
u8 gCustomLensFlare2On;
Vec3f gCustomLensFlare2Pos;
f32 D_801F4E5C;
f32 D_801F4E60;
s16 D_801F4E64;
struct LightningStrike gLightningStrike;
f32 D_801F4E74;
u16 D_801F4E78;
u16 gSkyboxNumStars;
LightningBolt sLightningBolts[3];
LightNode* sNGameOverLightNode;
LightInfo sNGameOverLightInfo;
LightNode* sSGameOverLightNode;
LightInfo sSGameOverLightInfo;
f32 sSunEnvAlpha;
f32 sSunColor;
f32 sSunScale;
f32 sSunPrimAlpha;
s32 sSunDepthTestX;
s32 sSunDepthTestY;
f32 D_801F4F28;
s16 sLightningFlashAlpha;
u16 sSandstormScroll;
u8 D_801F4F30;
u8 D_801F4F31;
u8 sEnvIsTimeStopped;
u8 D_801F4F33;
u8 sGameOverLightsIntensity;
Gfx* sSkyboxStarsDList;

#include "z64environment.h"
#include "global.h"
#include "sys_cfb.h"
#include "objects/gameplay_keep/gameplay_keep.h"

// Data
f32 sSandstormLerpScale = 0.0f;
s32 sSunScreenDepth = GPACK_ZDZ(G_MAXFBZ, 0);
s32 sEnvSkyboxNumStars = 0;
u16 sTimeJump = 0;
u8 sSandstormColorIndex = 0;
u8 sNextSandstormColorIndex = 0;
u8 D_801BDBA8 = 0;
u8 D_801BDBAC = 0;
u8 gWeatherMode = WEATHER_MODE_CLEAR;
u8 gLightConfigAfterUnderwater = 0;
u8 gInterruptSongOfStorms = false;
u8 sSkyboxIsChanging = false;
u8 D_801BDBC0 = 0;
u8 D_801BDBC4 = 0;
u8 gSceneSeqState = SCENESEQ_DEFAULT;

typedef struct {
    /* 0x0 */ u16 startTime;
    /* 0x2 */ u16 endTime;
    /* 0x4 */ u8 lightSetting;
    /* 0x5 */ u8 nextLightSetting;
} TimeBasedLightEntry; // size = 0x6

TimeBasedLightEntry sTimeBasedLightConfigs[][7] = {
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 3, 3 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 3, 12 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 1 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 2 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 2, 3 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 3, 3 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 7, 7 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 7, 8 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 4, 5 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 5, 5 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 5, 6 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 6, 7 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 7, 7 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 11, 11 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 11, 8 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 8, 9 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 9, 9 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 9, 10 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 10, 11 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 11, 11 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 15, 15 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 15, 16 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 12, 13 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 13, 13 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 13, 14 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 14, 15 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 15, 15 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 19, 19 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 19, 16 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 16, 17 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 17, 17 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 17, 18 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 18, 19 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 19, 19 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 23, 23 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 23, 20 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 20, 21 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 21, 21 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 21, 22 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 22, 23 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 23, 23 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 27, 27 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(6, 0), 27, 24 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 24, 25 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 25, 25 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 25, 26 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(19, 0), 26, 27 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 27, 27 },
    },
};

TimeBasedSkyboxEntry sTimeBasedSkyboxConfigs[][9] = {
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 3, 3 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 3, 4 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 4, 4 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 0, 1 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 1, 2 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 2, 2 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 2, 3 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 3, 3 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 7, 7 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 7, 8 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 8, 8 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 0, 4, 5 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 5, 5 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 1, 5, 6 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 6, 6 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 6, 7 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 7, 7 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 11, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 8, 9 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 9, 9 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 9, 10 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 10, 10 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 10, 11 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 11, 11 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 15, 15 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 15, 16 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 16, 16 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 12, 13 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 13, 13 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 13, 14 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 14, 14 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 14, 15 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 15, 15 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 19, 19 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 19, 20 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 20, 20 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 0, 16, 17 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 17, 17 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 1, 17, 18 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 18, 18 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 0, 18, 19 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 19, 19 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 23, 23 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 23, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 20, 21 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 21, 21 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 21, 22 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 22, 22 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 22, 23 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 23, 23 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 27, 27 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 27, 28 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 28, 28 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 24, 25 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 25, 25 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 25, 26 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 26, 26 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 26, 27 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 27, 27 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 31, 31 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 31, 32 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 32, 32 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 0, 28, 29 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 29, 29 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 1, 29, 30 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 30, 30 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 0, 30, 31 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 31, 31 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 35, 35 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 35, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 32, 33 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 33, 33 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 33, 34 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 34, 34 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 34, 35 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 35, 35 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 39, 39 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 39, 40 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 40, 40 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 36, 37 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 37, 37 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 37, 38 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 38, 38 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 38, 39 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 39, 39 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 43, 43 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 43, 44 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 44, 44 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 0, 40, 41 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 41, 41 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 1, 41, 42 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 42, 42 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 0, 42, 43 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 43, 43 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 47, 47 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 47, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 44, 45 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 45, 45 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 45, 46 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 46, 46 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 46, 47 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 47, 47 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 51, 51 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 51, 48 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 48, 49 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 49, 49 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 49, 49 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 49, 50 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 50, 50 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 50, 51 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 51, 51 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 55, 55 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 55, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 52, 53 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 53, 53 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 53, 54 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 54, 54 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 54, 54 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 55, 55 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 59, 59 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 59, 56 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 56, 56 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 56, 57 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 57, 57 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 57, 58 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 58, 58 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 58, 58 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 59, 59 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 63, 63 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 63, 60 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 60, 60 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 60, 61 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 61, 61 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 61, 62 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 62, 62 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 62, 62 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 63, 63 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 67, 67 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 67, 64 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 64, 64 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 64, 65 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 65, 65 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 65, 66 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 66, 66 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 66, 66 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 67, 67 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 1, 1 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 1, 1 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 71, 71 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 71, 72 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 72, 72 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 68, 69 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 69, 69 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 69, 70 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 70, 70 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 70, 71 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 71, 71 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 75, 75 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 75, 76 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 76, 76 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 72, 73 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 73, 73 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 73, 74 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 74, 74 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 74, 75 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 75, 75 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 79, 79 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 79, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 76, 77 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 77, 77 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 77, 78 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 78, 78 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 78, 79 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 79, 79 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 83, 83 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 83, 84 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 84, 84 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 80, 81 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 81, 81 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 81, 82 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 82, 82 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 82, 83 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 83, 83 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 87, 87 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 87, 88 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 88, 88 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 84, 85 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 85, 85 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 85, 86 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 86, 86 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 86, 87 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 87, 87 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 91, 91 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 91, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 88, 89 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 89, 89 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 89, 90 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 90, 90 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 90, 91 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 91, 91 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 11, 11 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 11, 11 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 95, 95 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 95, 96 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 96, 96 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 92, 93 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 93, 93 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 93, 94 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 94, 94 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 94, 95 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 95, 95 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 1, 1, 99, 99 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 1, 1, 99, 100 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 100, 100 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 96, 97 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 97, 97 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 1, 97, 98 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 1, 1, 98, 98 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 1, 1, 98, 99 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 1, 1, 99, 99 },
    },
    {
        { CLOCK_TIME(0, 0), CLOCK_TIME(4, 0), 0, 0, 103, 103 },
        { CLOCK_TIME(4, 0), CLOCK_TIME(5, 0), 0, 1, 103, 52 },
        { CLOCK_TIME(5, 0), CLOCK_TIME(6, 0), 1, 1, 52, 52 },
        { CLOCK_TIME(6, 0), CLOCK_TIME(8, 0), 1, 1, 100, 101 },
        { CLOCK_TIME(8, 0), CLOCK_TIME(16, 0), 1, 1, 101, 101 },
        { CLOCK_TIME(16, 0), CLOCK_TIME(17, 0), 1, 0, 101, 102 },
        { CLOCK_TIME(17, 0), CLOCK_TIME(18, 0), 0, 0, 102, 102 },
        { CLOCK_TIME(18, 0), CLOCK_TIME(19, 0), 0, 0, 102, 103 },
        { CLOCK_TIME(19, 0), CLOCK_TIME(24, 0) - 1, 0, 0, 103, 103 },
    },
};

typedef struct {
    /* 0x0 */ RomFile file;
    /* 0x8 */ RomFile palette;
} SkyboxFile; // size = 0x10

SkyboxFile sNormalSkyFiles[] = {
    {
        ROM_FILE(d2_fine_static),
        ROM_FILE_UNSET,
    },
    {
        ROM_FILE(d2_cloud_static),
        ROM_FILE_UNSET,
    },
};

void Environment_GraphCallback(GraphicsContext* gfxCtx, void* arg) {
    PlayState* play = (PlayState*)arg;

    sSunScreenDepth = SysCfb_GetZBufferPixel(sSunDepthTestX, sSunDepthTestY);
    Lights_GlowCheck(play);
}

typedef struct {
    /* 0x0 */ s32 mantissa;
    /* 0x4 */ s32 exponent;
} ZBufValConversionEntry; // size = 0x8

ZBufValConversionEntry sZBufValConversionTable[1 << 3] = {
    { 6, 0x00000 }, { 5, 0x20000 }, { 4, 0x30000 }, { 3, 0x38000 },
    { 2, 0x3C000 }, { 1, 0x3E000 }, { 0, 0x3F000 }, { 0, 0x3F800 },
};

#define ZBUFVAL_EXPONENT(v) (((v) >> 15) & 7)
#define ZBUFVAL_MANTISSA(v) (((v) >> 4) & 0x7FF)

/**
 * Convert an 18-bits Z buffer value to a fixed point 15.3 value
 *
 * zBufferVal is 18 bits:
 *   3: Exponent of z value
 *  11: Mantissa of z value
 *   4: dz value (unused)
 */
s32 Environment_ZBufValToFixedPoint(s32 zBufferVal) {
    // base[exp] + mantissa << shift[exp]
    s32 ret = (ZBUFVAL_MANTISSA(zBufferVal) << sZBufValConversionTable[ZBUFVAL_EXPONENT(zBufferVal)].mantissa) +
              sZBufValConversionTable[ZBUFVAL_EXPONENT(zBufferVal)].exponent;

    return ret;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_SmoothStepToU8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpWeight.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_LerpWeightAccelDecel.s")

Color_RGBA8 sSkyboxPrimColors[] = {
    { 181, 100, 72, 0 },  { 255, 255, 255, 0 }, { 255, 164, 63, 0 },  { 70, 90, 100, 0 },   { 180, 110, 70, 0 },
    { 140, 120, 90, 0 },  { 186, 107, 70, 0 },  { 50, 90, 120, 0 },   { 160, 104, 125, 0 }, { 225, 234, 150, 0 },
    { 243, 84, 33, 0 },   { 112, 37, 55, 0 },   { 181, 100, 27, 0 },  { 255, 255, 255, 0 }, { 186, 107, 69, 0 },
    { 10, 40, 90, 0 },    { 180, 120, 100, 0 }, { 140, 120, 110, 0 }, { 186, 107, 70, 0 },  { 0, 50, 60, 0 },
    { 160, 104, 215, 0 }, { 225, 234, 150, 0 }, { 243, 84, 33, 0 },   { 100, 25, 45, 0 },   { 181, 100, 27, 0 },
    { 255, 255, 255, 0 }, { 186, 107, 69, 0 },  { 10, 10, 50, 0 },    { 165, 110, 63, 0 },  { 150, 120, 90, 0 },
    { 166, 112, 65, 0 },  { 10, 40, 60, 0 },    { 160, 104, 215, 0 }, { 225, 234, 150, 0 }, { 243, 84, 33, 0 },
    { 100, 20, 40, 0 },   { 181, 100, 27, 0 },  { 255, 255, 255, 0 }, { 186, 107, 69, 0 },  { 0, 50, 70, 0 },
    { 180, 126, 70, 0 },  { 150, 140, 120, 0 }, { 225, 164, 63, 0 },  { 0, 70, 80, 0 },     { 160, 104, 215, 0 },
    { 225, 234, 150, 0 }, { 243, 84, 33, 0 },   { 100, 40, 65, 0 },   { 105, 72, 57, 0 },   { 150, 120, 90, 0 },
    { 80, 56, 21, 0 },    { 60, 46, 40, 0 },    { 210, 120, 180, 0 }, { 210, 120, 180, 0 }, { 210, 120, 180, 0 },
    { 210, 120, 180, 0 }, { 100, 90, 110, 0 },  { 100, 90, 110, 0 },  { 100, 90, 110, 0 },  { 100, 90, 110, 0 },
    { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 255, 255, 255, 0 }, { 25, 53, 235, 0 },
    { 25, 53, 235, 0 },   { 25, 53, 235, 0 },   { 25, 53, 235, 0 },   { 198, 121, 88, 0 },  { 255, 255, 255, 0 },
    { 255, 164, 70, 0 },  { 55, 53, 91, 0 },    { 199, 126, 78, 0 },  { 159, 125, 103, 0 }, { 186, 107, 59, 0 },
    { 50, 90, 120, 0 },   { 171, 113, 131, 0 }, { 225, 234, 180, 0 }, { 237, 84, 37, 0 },   { 133, 48, 75, 0 },
    { 198, 121, 88, 0 },  { 255, 255, 255, 0 }, { 255, 164, 70, 0 },  { 55, 53, 91, 0 },    { 209, 135, 100, 0 },
    { 180, 177, 158, 0 }, { 196, 127, 79, 0 },  { 50, 90, 120, 0 },   { 171, 113, 131, 0 }, { 225, 234, 180, 0 },
    { 237, 84, 37, 0 },   { 133, 48, 75, 0 },   { 198, 121, 88, 0 },  { 235, 250, 235, 0 }, { 255, 164, 70, 0 },
    { 55, 53, 91, 0 },    { 205, 140, 110, 0 }, { 159, 125, 103, 0 }, { 186, 107, 59, 0 },  { 50, 90, 120, 0 },
    { 171, 113, 131, 0 }, { 225, 234, 180, 0 }, { 237, 84, 37, 0 },   { 133, 48, 75, 0 },
};

Color_RGBA8 sSkyboxEnvColors[] = {
    { 102, 135, 99, 0 }, { 0, 15, 69, 0 },    { 110, 55, 110, 0 }, { 0, 0, 100, 0 },   { 70, 10, 10, 0 },
    { 40, 0, 10, 0 },    { 40, 40, 40, 0 },   { 20, 20, 30, 0 },   { 60, 0, 10, 0 },   { 65, 45, 0, 0 },
    { 20, 25, 90, 0 },   { 0, 5, 25, 0 },     { 102, 135, 99, 0 }, { 0, 4, 199, 0 },   { 60, 65, 89, 0 },
    { 0, 0, 0, 0 },      { 70, 10, 10, 0 },   { 20, 0, 30, 0 },    { 40, 40, 40, 0 },  { 0, 0, 20, 0 },
    { 60, 0, 10, 0 },    { 65, 45, 0, 0 },    { 20, 25, 90, 0 },   { 0, 0, 30, 0 },    { 102, 135, 99, 0 },
    { 0, 4, 199, 0 },    { 60, 65, 89, 0 },   { 0, 0, 20, 0 },     { 66, 10, 10, 0 },  { 46, 5, 2, 0 },
    { 66, 10, 10, 0 },   { 0, 20, 50, 0 },    { 60, 0, 10, 0 },    { 65, 45, 0, 0 },   { 20, 25, 90, 0 },
    { 0, 0, 20, 0 },     { 102, 135, 99, 0 }, { 0, 4, 199, 0 },    { 60, 65, 89, 0 },  { 0, 0, 40, 0 },
    { 90, 90, 100, 0 },  { 60, 20, 30, 0 },   { 110, 55, 110, 0 }, { 0, 0, 50, 0 },    { 60, 0, 10, 0 },
    { 65, 45, 0, 0 },    { 20, 25, 90, 0 },   { 0, 0, 25, 0 },     { 10, 0, 0, 0 },    { 46, 5, 2, 0 },
    { 34, 14, 10, 0 },   { 21, 5, 13, 0 },    { 0, 0, 0, 0 },      { 0, 0, 0, 0 },     { 0, 0, 0, 0 },
    { 0, 0, 0, 0 },      { 50, 20, 10, 0 },   { 50, 20, 10, 0 },   { 50, 20, 10, 0 },  { 50, 20, 10, 0 },
    { 30, 15, 250, 0 },  { 30, 15, 250, 0 },  { 30, 15, 250, 0 },  { 30, 15, 250, 0 }, { 177, 82, 93, 0 },
    { 177, 82, 93, 0 },  { 177, 82, 93, 0 },  { 177, 82, 93, 0 },  { 90, 82, 102, 0 }, { 0, 4, 199, 0 },
    { 101, 24, 131, 0 }, { 26, 7, 0, 0 },     { 70, 9, 6, 0 },     { 49, 6, 1, 0 },    { 40, 15, 59, 0 },
    { 0, 2, 28, 0 },     { 60, 0, 10, 0 },    { 75, 45, 0, 0 },    { 20, 20, 89, 0 },  { 0, 7, 17, 0 },
    { 90, 82, 102, 0 },  { 0, 4, 199, 0 },    { 101, 24, 131, 0 }, { 26, 7, 0, 0 },    { 70, 12, 16, 0 },
    { 51, 10, 15, 0 },   { 50, 15, 58, 0 },   { 0, 2, 28, 0 },     { 60, 0, 10, 0 },   { 75, 45, 0, 0 },
    { 20, 20, 89, 0 },   { 0, 7, 17, 0 },     { 90, 82, 102, 0 },  { 0, 4, 199, 0 },   { 101, 24, 131, 0 },
    { 26, 7, 0, 0 },     { 70, 20, 45, 0 },   { 49, 6, 1, 0 },     { 40, 15, 59, 0 },  { 0, 2, 28, 0 },
    { 60, 0, 10, 0 },    { 75, 45, 0, 0 },    { 20, 20, 89, 0 },   { 0, 7, 17, 0 },
};

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

typedef enum {
    /* 0 */ LENS_FLARE_CIRCLE0,
    /* 1 */ LENS_FLARE_CIRCLE1,
    /* 2 */ LENS_FLARE_RING
} LensFlareType;

static Color_RGB8 sLensFlareColors[] = {
    { 155, 205, 255 }, // blue
    { 255, 255, 205 }, // yellow
    { 255, 255, 205 }, // yellow
    { 255, 255, 205 }, // yellow
    { 155, 255, 205 }, // green
    { 205, 255, 255 }, // light blue
    { 155, 155, 255 }, // dark blue
    { 205, 175, 255 }, // purple
    { 175, 255, 205 }, // light green
    { 255, 155, 235 }, // pink
};
static f32 sLensFlareScales[] = {
    23.0f, 12.0f, 7.0f, 5.0f, 3.0f, 10.0f, 6.0f, 2.0f, 3.0f, 1.0f,
};
static u32 sLensFlareAlphas[] = {
    50, 10, 25, 40, 70, 30, 50, 70, 50, 40,
};
static u32 sLensFlareTypes[] = {
    LENS_FLARE_RING,    LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1,
    LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1, LENS_FLARE_CIRCLE1,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLensFlare.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_RandCentered.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawRainImpl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawRain.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_ChangeLightSetting.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawSkyboxFilters.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLightningFlash.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateLightningStrike.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_AddLightningBolts.s")

static TexturePtr sLightningTextures[] = {
    gEffLightning1Tex, gEffLightning2Tex, gEffLightning3Tex, gEffLightning4Tex,
    gEffLightning5Tex, gEffLightning6Tex, gEffLightning7Tex, gEffLightning8Tex,
};

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawLightning.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_PlaySceneSequence.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateTimeBasedSequence.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_DrawCustomLensFlare.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_InitGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FadeInGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FadeOutGameOverLights.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_UpdateRain.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kankyo/Environment_FillScreen.s")

u8 sSandstormPrimColors[] = {
    255, 255, 255, //
    255, 255, 255, //
    255, 255, 255, //
    255, 255, 255, //
    210, 156, 85,  //
    255, 200, 100, //
    225, 160, 50,  //
    105, 90,  40,  //
};

u8 sSandstormEnvColors[] = {
    100, 100, 100, //
    100, 100, 100, //
    100, 100, 100, //
    100, 100, 100, //
    155, 106, 35,  //
    200, 150, 50,  //
    170, 110, 0,   //
    50,  40,  0,   //
};

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
