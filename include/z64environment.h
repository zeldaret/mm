#ifndef Z64ENVIRONMENT_H
#define Z64ENVIRONMENT_H

#include "PR/ultratypes.h"
// #include "z64game_over.h"
#include "z64light.h"
#include "z64math.h"
// #include "z64message.h"
#include "z64dma.h"
// #include "z64view.h"
#include "ultra64/message.h"

struct PlayState;
struct MessageContext;
struct GameOverContext;
struct PauseContext;
struct SkyboxContext;
struct View;

typedef enum {
    /* 0 */ LIGHT_MODE_TIME, // environment lights use `lightConfig` and change based on time of day
    /* 1 */ LIGHT_MODE_SETTINGS // environment lights use `lightSetting`
} LightMode;

typedef enum {
    /* 0 */ LIGHTNING_MODE_OFF, // no lightning
    /* 1 */ LIGHTNING_MODE_ON, // request ligtning strikes at random intervals
    /* 2 */ LIGHTNING_MODE_LAST // request one lightning strike before turning off
} LightningMode;

typedef enum {
    /* 0 */ LIGHTNING_STRIKE_WAIT, // wait between lightning strikes. request bolts when timer hits 0
    /* 1 */ LIGHTNING_STRIKE_START, // fade in the flash. note: bolts are requested in the previous state
    /* 2 */ LIGHTNING_STRIKE_END // fade out the flash and go back to wait
} LightningStrikeState;

typedef enum {
    /* 0x00 */ LIGHTNING_BOLT_START,
    /* 0x01 */ LIGHTNING_BOLT_WAIT,
    /* 0x02 */ LIGHTNING_BOLT_DRAW,
    /* 0xFF */ LIGHTNING_BOLT_INACTIVE = 0xFF
} LightningBoltState;

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x04 */ Vec3f offset;
    /* 0x10 */ Vec3f pos;
    /* 0x1C */ s8 pitch;
    /* 0x1D */ s8 roll;
    /* 0x1E */ u8 textureIndex;
    /* 0x1F */ u8 delayTimer;
} LightningBolt; // size = 0x20

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x01 */ u8 flashRed;
    /* 0x02 */ u8 flashGreen;
    /* 0x03 */ u8 flashBlue;
    /* 0x04 */ u8 flashAlphaTarget;
    /* 0x08 */ f32 delayTimer;
} LightningStrike; // size = 0xC

typedef enum {
    /* 0x00 */ TIMESEQ_DAY_BGM,
    /* 0x01 */ TIMESEQ_FADE_DAY_BGM,
    /* 0x02 */ TIMESEQ_NIGHT_BEGIN_SFX,
    /* 0x03 */ TIMESEQ_EARLY_NIGHT_CRITTERS,
    /* 0x04 */ TIMESEQ_NIGHT_DELAY,
    /* 0x05 */ TIMESEQ_NIGHT_CRITTERS,
    /* 0x06 */ TIMESEQ_DAY_BEGIN_SFX,
    /* 0x07 */ TIMESEQ_MORNING_CRITTERS,
    /* 0x08 */ TIMESEQ_DAY_DELAY,
    /* 0xFE */ TIMESEQ_REQUEST = 0xFE,
    /* 0xFF */ TIMESEQ_DISABLED
} TimeBasedSeqState;

typedef enum {
    /* 0 */ WEATHER_MODE_CLEAR,
    /* 1 */ WEATHER_MODE_CLOUDY_CONFIG3, // scene must define settings for light config 3
    /* 2 */ WEATHER_MODE_CLOUDY_CONFIG2, // scene must define settings for light config 2
    /* 3 */ WEATHER_MODE_SNOW, // scene must define settings for light config 2
    /* 4 */ WEATHER_MODE_RAIN, // scene must define settings for light config 2
    /* 5 */ WEATHER_MODE_HEAVY_RAIN // scene must define settings for light config 4
} WeatherMode;

typedef enum {
    /* 0x0 */ SANDSTORM_OFF,
    /* 0x1 */ SANDSTORM_FILL,
    /* 0x2 */ SANDSTORM_UNFILL,
    /* 0x3 */ SANDSTORM_ACTIVE,
    /* 0x4 */ SANDSTORM_DISSIPATE,
    /* 0x5 */ SANDSTORM_UNK5,
    /* 0x6 */ SANDSTORM_UNK6,
    /* 0x7 */ SANDSTORM_UNK7,
    /* 0x8 */ SANDSTORM_UNK8,
    /* 0x9 */ SANDSTORM_UNK9,
    /* 0xA */ SANDSTORM_UNKA,
    /* 0xB */ SANDSTORM_UNKB,
    /* 0xC */ SANDSTORM_UNKC,
    /* 0xD */ SANDSTORM_UNKD
} SandstormState;

#define LIGHT_SETTING_OVERRIDE_NONE 0xFF

#define SCENESEQ_DEFAULT 0
#define SCENESEQ_MORNING 0xFE

typedef struct EnvironmentContext {
    /* 0x00 */ u16 unk_0;
    /* 0x02 */ u16 sceneTimeSpeed;
    /* 0x04 */ Vec3f sunPos;
    /* 0x10 */ u8 skybox1Index;
    /* 0x11 */ u8 skybox2Index;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 skyboxBlend;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 skyboxDisabled;
    /* 0x16 */ u8 sunDisabled;
    /* 0x17 */ u8 skyboxConfig;
    /* 0x18 */ u8 changeSkyboxNextConfig;
    /* 0x19 */ u8 changeSkyboxState;
    /* 0x1A */ u16 changeSkyboxTimer;
    /* 0x1C */ u16 unk_1C;
    /* 0x1E */ u8 lightMode;
    /* 0x1F */ u8 lightConfig;
    /* 0x20 */ u8 changeLightNextConfig;
    /* 0x21 */ u8 changeLightEnabled;
    /* 0x22 */ u16 changeLightTimer;
    /* 0x24 */ u16 changeDuration;
    /* 0x26 */ u8 unk_26;
    /* 0x28 */ LightInfo dirLight1; // sun 1
    /* 0x36 */ LightInfo dirLight2; // sun 2
    /* 0x44 */ s8 skyboxDmaState;
    /* 0x48 */ DmaRequest dmaRequest;
    /* 0x68 */ OSMesgQueue loadQueue;
    /* 0x80 */ OSMesg loadMsg;
    /* 0x84 */ f32 glareAlpha;
    /* 0x88 */ f32 lensFlareAlphaScale;
    /* 0x8C */ EnvLightSettings lightSettings;
    /* 0xA8 */ f32 unk_A8;
    /* 0xAC */ Vec3s windDir;
    /* 0xB4 */ f32 windSpeed;
    /* 0xB8 */ u8 numLightSettings;
    /* 0xBC */ LightSettings* lightSettingsList;
    /* 0xC0 */ u8 lightBlendEnabled;
    /* 0xC1 */ u8 lightSetting;
    /* 0xC2 */ u8 prevLightSetting;
    /* 0xC3 */ u8 lightSettingOverride;
    /* 0xC4 */ LightSettings unk_C4;
    /* 0xDA */ u16 lightBlendRateOverride;
    /* 0xDC */ f32 lightBlend;
    /* 0xE0 */ u8 unk_E0;
    /* 0xE1 */ u8 unk_E1;
    /* 0xE2 */ u8 unk_E2;
    /* 0xE3 */ u8 lightningState; // modified by unused func in EnWeatherTag
    /* 0xE4 */ u8 timeSeqState;
    /* 0xE5 */ u8 fillScreen;
    /* 0xE6 */ u8 screenFillColor[4];
    /* 0xEA */ u8 sandstormState;
    /* 0xEB */ u8 sandstormPrimA;
    /* 0xEC */ u8 sandstormEnvA;
    /* 0xED */ u8 customSkyboxFilter;
    /* 0xEE */ u8 skyboxFilterColor[4];
    /* 0xF2 */ u8 precipitation[8]; // [3] is used by both DemoKankyo and ObjectKankyo effect count
    /* 0xFA */ u8 unk_FA[4];
} EnvironmentContext; // size = 0x100

// void Environment_GraphCallback(void);
s32 Environment_ZBufValToFixedPoint(s32 zBufferVal);
void Environment_Init(struct PlayState* play, EnvironmentContext* envCtx, s32 arg2);
u8 Environment_SmoothStepToU8(u8* pvalue, u8 target, u8 scale, u8 step, u8 minStep);
f32 Environment_LerpWeight(u16 max, u16 min, u16 val);
f32 Environment_LerpWeightAccelDecel(u16 endFrame, u16 startFrame, u16 curFrame, u16 accelDuration, u16 decelDuration);
void Environment_UpdateSkybox(u8 skyboxId, EnvironmentContext* envCtx, struct SkyboxContext* skyboxCtx);
void Environment_EnableUnderwaterLights(struct PlayState* play, s32 waterLightsIndex);
void Environment_DisableUnderwaterLights(struct PlayState* play);
void func_800F6A04(void);
void func_800F6A40(struct PlayState* play);
void func_800F6AB8(void);
void Environment_UpdateTime(struct PlayState* play, EnvironmentContext* envCtx, struct PauseContext* pauseCtx, struct MessageContext* msgCtx, struct GameOverContext* gameOverCtx);
// void func_800F6CEC(void);
u8 func_800F6EA4(f32 arg0, f32 arg1, f32 arg2);
s32 Environment_IsSceneUpsideDown(struct PlayState* play);
void Environment_UpdateLights(struct PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx);
void Environment_UpdateSun(struct PlayState* play);
void func_800F88C4(u16 arg0);
void func_800F8970(void);
// void func_800F8A9C(void);
void Environment_Update(struct PlayState* play, EnvironmentContext* envCtx, LightContext* lightCtx,
                        struct PauseContext* pauseCtx, struct MessageContext* msgCtx, struct GameOverContext* gameOverCtx,
                        GraphicsContext* gfxCtx);
void Environment_DrawSun(struct PlayState* play);
void Environment_DrawSunLensFlare(struct PlayState* play, EnvironmentContext* envCtx, struct View* view, GraphicsContext* gfxCtx, Vec3f vec);
void Environment_DrawLensFlare(struct PlayState* play, EnvironmentContext* envCtx, struct View* view, GraphicsContext* gfxCtx, Vec3f vec, f32 arg5, f32 arg6, s16 arg7, s8 arg8);
f32 Environment_RandCentered(void);
void Environment_DrawRainImpl(struct PlayState* play, struct View* view, GraphicsContext* gfxCtx);
void Environment_DrawRain(struct PlayState* play, struct View* view, GraphicsContext* gfxCtx);
void Environment_ChangeLightSetting(struct PlayState* play, u8 lightConfig);
void Environment_DrawSkyboxFilters(struct PlayState* play);
void Environment_DrawLightningFlash(struct PlayState* play, u8 red, u8 green, u8 blue, u8 alpha);
void Environment_UpdateLightningStrike(struct PlayState* play);
void Environment_AddLightningBolts(struct PlayState* play, u8 num);
void Environment_DrawLightning(struct PlayState* play, s32 unused);
void Environment_PlaySceneSequence(struct PlayState* play);
void Environment_DrawCustomLensFlare(struct PlayState* play);
void Kankyo_InitGameOverLights(struct PlayState* play);
void Environment_FadeInGameOverLights(struct PlayState* play);
void Environment_FadeOutGameOverLights(struct PlayState* play);
void Environment_FillScreen(GraphicsContext* gfxCtx, u8 red, u8 green, u8 blue, u8 alpha, u8 drawFlags);
void Environment_DrawSandstorm(struct PlayState* play, u8 sandstormState);
s32 Environment_AdjustLights(struct PlayState* play, f32 arg1, f32 arg2, f32 arg3, f32 arg4);
void Environment_LerpRGB8(Color_RGB8* from, Color_RGB8* to, f32 lerp, Vec3s* dst);
void Environment_LerpAmbientColor(struct PlayState* play, Color_RGB8* to, f32 lerp);
void Environment_LerpDiffuseColor(struct PlayState* play, Color_RGB8* to, f32 lerp);
void Environment_LerpFogColor(struct PlayState* play, Color_RGB8* to, f32 lerp);
void Environment_LerpFog(struct PlayState* play, s16 fogNearTarget, s16 fogFarTarget, f32 lerp);
u32 Environment_GetBgsDayCount(void);
void Environment_ClearBgsDayCount(void);
u32 Environment_GetTotalDays(void);
void Environment_ForcePlaySequence(u16 seqId);
s32 Environment_IsForcedSequenceDisabled(void);
void Environment_PlayStormNatureAmbience(struct PlayState* play);
void Environment_StopStormNatureAmbience(struct PlayState* play);
void Environment_WarpSongLeave(struct PlayState* play);
void func_800FD980(struct PlayState* play);
void Environment_DrawSkyboxStar(Gfx** gfxp, f32 x, f32 y, s32 width, s32 height);
// void Environment_DrawSkyboxStars(void);
void Environment_Draw(struct PlayState* play);
void func_800FE3E0(struct PlayState* play);
void Environment_StopTime(void);
void Environment_StartTime(void);
u8 Environment_IsTimeStopped(void);
u32 func_800FE4B8(struct PlayState* play);
u8 Environment_IsFinalHours(struct PlayState* play);
u8 func_800FE5D0(struct PlayState* play);
u32 func_800FE610(struct PlayState* play);
u16 Environment_GetTimeSpeed(struct PlayState* play);
void Environment_SetTimeJump(f32 minutes);
u8 func_800FE6F8(struct PlayState* play, s16 arg1, s16 arg2);
u8 func_800FE778();
u8 func_800FE788();
f32 func_800FE798();
void func_800FE7A8(Color_RGBA8* arg0, Color_RGBA8* arg1);
u8 func_800FE9B4(struct PlayState* play);
void func_800FEA50(struct PlayState* play);
void func_800FEAB0(void);
void Environment_JumpForwardInTime(void);
void func_800FEAF4(EnvironmentContext* envCtx);

// Data to import
extern f32 sSandstormLerpScale;
extern s32 sSunScreenDepth;
extern s32 sEnvSkyboxNumStars;
extern u16 sTimeJump;
extern u8 sSandstormColorIndex;
extern u8 sNextSandstormColorIndex;
// extern UNK_TYPE1 D_801BDBA8;
extern u8 gWeatherMode;
extern u8 gLightConfigAfterUnderwater;
extern u8 gInterruptSongOfStorms;
// extern UNK_TYPE1 gSkyboxIsChanging;
extern u8 D_801BDBC0;
extern u8 D_801BDBC4;
extern u8 sSceneSeqState;
// extern UNK_TYPE1 D_801BDBCC;
// extern UNK_TYPE1 D_801BDCF4;
// extern UNK_TYPE1 D_801BE38E;
// extern UNK_TYPE1 D_801BE38F;
// extern UNK_TYPE1 D_801BE390;
// extern UNK_TYPE1 D_801BE4D4;
// extern UNK_TYPE1 D_801BE534;
// extern UNK_TYPE1 D_801BE6D4;
// extern UNK_TYPE1 D_801BE874;
// extern UNK_TYPE4 D_801BE894;
// extern UNK_TYPE4 D_801BE8BC;
// extern UNK_TYPE4 D_801BE8E4;
// extern UNK_TYPE1 sSandstormPrimColors;
// extern UNK_TYPE1 sSandstormEnvColors;


// bss to import
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

extern LightningStrike gLightningStrike;
//extern f32 D_801F4E70; gLightningStrike.delayTimer
extern f32 D_801F4E74;
extern u16 D_801F4E78;
extern u16 gSkyboxNumStars;
extern LightningBolt sLightningBolts[3];

// structs?
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
// extern UNK_TYPE1 sSandstormScroll;
extern u8 D_801F4F30;
extern u8 D_801F4F31;
extern u8 sEnvIsTimeStopped;
extern u8 D_801F4F33;
extern u8 sGameOverLightsIntensity;
extern Gfx* D_801F4F38;

#endif
