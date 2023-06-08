#ifndef Z64ENVIRONMENT_H
#define Z64ENVIRONMENT_H

#include "PR/ultratypes.h"
#include "z64math.h"
#include "z64light.h"
#include "z64dma.h"
#include "ultra64/message.h"

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

#define SCENESEQ_DEFAULT 0
#define SCENESEQ_MORNING 0xFE

typedef struct {
    /* 0x00 */ u16 unk_0;
    /* 0x02 */ u16 sceneTimeSpeed;
    /* 0x04 */ Vec3f sunPos;
    /* 0x10 */ u8 skybox1Index;
    /* 0x11 */ u8 skybox2Index;
    /* 0x12 */ u8 unk_12;
    /* 0x13 */ u8 skyboxBlend;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 skyboxDisabled;
    /* 0x16 */ u8 sunMoonDisabled;
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
    /* 0x36 */ LightInfo unk_36; // sun 2
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
    /* 0xE3 */ u8 unk_E3; // modified by unused func in EnWeatherTag
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

extern f32 sSandstormLerpScale;
extern s32 sSunScreenDepth;
extern s32 sEnvSkyboxNumStars;
extern u16 sTimeJump;
extern u8 sSandstormColorIndex;
extern u8 sNextSandstormColorIndex;
// extern UNK_TYPE1 D_801BDBA8;
extern u8 gWeatherMode;
extern u8 gLightConfigAfterUnderwater;
// extern UNK_TYPE1 D_801BDBB8;
// extern UNK_TYPE1 D_801BDBBC;
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
// extern UNK_TYPE1 D_801BE92C;
// extern UNK_TYPE1 D_801BE944;

#endif
