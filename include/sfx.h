#ifndef SFX_H
#define SFX_H

#include "PR/ultratypes.h"
#include "libc/assert.h"
#include "z64math.h"

/**
 * With `SFX_FLAG` on, play the entire sfx audio clip.
 * Requesting the sfx while playing will restart the sfx from the beginning.
 * i.e. sfx only needs to be requested once.
 * 
 * With `SFX_FLAG` off, play the sfx for only one frame.
 * Requesting the sfx while playing will allow the sfx to continue to the next frame.
 * i.e. sfx needs to be requested every frame.
 * 
 * By default, `SFX_FLAG` is on.
 * Use `- SFX_FLAG` to turn `SFX_FLAG` off.
 */
#define SFX_FLAG_MASK 0xC00
#define SFX_FLAG 0x800

#define DEFINE_SFX(_0, enum, _2, _3, _4, _5, _6) enum,

typedef enum SfxId {
    NA_SE_NONE, // Requesting a sfx with this id will play no sound

    NA_SE_PL_BASE = 0x7FF,
    #include "tables/sfx/playerbank_table.h"
    NA_SE_PL_END,

    NA_SE_IT_BASE = 0x17FF,
    #include "tables/sfx/itembank_table.h"
    NA_SE_IT_END,

    NA_SE_EV_BASE = 0x27FF,
    #include "tables/sfx/environmentbank_table.h"
    NA_SE_EV_END,

    NA_SE_EN_BASE = 0x37FF,
    #include "tables/sfx/enemybank_table.h"
    NA_SE_EN_END,

    NA_SE_SY_BASE = 0x47FF,
    #include "tables/sfx/systembank_table.h"
    NA_SE_SY_END,

    NA_SE_OC_BASE = 0x57FF,
    #include "tables/sfx/ocarinabank_table.h"
    NA_SE_OC_END,

    NA_SE_VO_BASE = 0x67FF,
    #include "tables/sfx/voicebank_table.h"
    NA_SE_VO_END,

    NA_SE_MAX
} SfxId;

#undef DEFINE_SFX

// These limits are due to the way Sequence 0 is programmed. There is also a global limit of 1024 entries for every bank
// enforced in Audio_PlayActiveSfx in sfx.c
static_assert(NA_SE_PL_END - (NA_SE_PL_BASE + 1) <= 512, "Player Bank SFX Table is limited to 512 entries due to Sequence 0");
static_assert(NA_SE_IT_END - (NA_SE_IT_BASE + 1) <= 128, "Item Bank SFX Table is limited to 128 entries due to Sequence 0");
static_assert(NA_SE_EV_END - (NA_SE_EV_BASE + 1) <= 512, "Environment Bank SFX Table is limited to 512 entries due to Sequence 0");
static_assert(NA_SE_EN_END - (NA_SE_EN_BASE + 1) <= 768, "Enemy Bank SFX Table is limited to 768 entries due to Sequence 0");
static_assert(NA_SE_SY_END - (NA_SE_SY_BASE + 1) <= 128, "System Bank SFX Table is limited to 128 entries due to Sequence 0");
static_assert(NA_SE_OC_END - (NA_SE_OC_BASE + 1) <= 128, "Ocarina Bank SFX Table is limited to 128 entries due to Sequence 0");
static_assert(NA_SE_VO_END - (NA_SE_VO_BASE + 1) <= 512, "Voice Bank SFX Table is limited to 512 entries due to Sequence 0");

typedef enum SfxPauseMenu {
    /* 0 */ SFX_PAUSE_MENU_CLOSE,
    /* 1 */ SFX_PAUSE_MENU_OPEN
} SfxPauseMenu;

typedef enum SfxBankType {
    /* 0 */ BANK_PLAYER,
    /* 1 */ BANK_ITEM,
    /* 2 */ BANK_ENV,
    /* 3 */ BANK_ENEMY,
    /* 4 */ BANK_SYSTEM,
    /* 5 */ BANK_OCARINA,
    /* 6 */ BANK_VOICE
} SfxBankType;

typedef enum SfxState {
    /* 0 */ SFX_STATE_EMPTY,
    /* 1 */ SFX_STATE_QUEUED,
    /* 2 */ SFX_STATE_READY,
    /* 3 */ SFX_STATE_PLAYING_REFRESH,
    /* 4 */ SFX_STATE_PLAYING,
    /* 5 */ SFX_STATE_PLAYING_ONE_FRAME
} SfxState;

typedef struct {
    /* 0x00 */ f32* posX;
    /* 0x04 */ f32* posY;
    /* 0x08 */ f32* posZ;
    /* 0x0C */ f32* freqScale;
    /* 0x10 */ f32* volume;
    /* 0x14 */ s8* reverbAdd;
    /* 0x18 */ f32 dist;
    /* 0x1C */ u32 priority; // lower is more prioritized
    /* 0x20 */ u16 sfxParams;
    /* 0x22 */ u16 sfxId;
    /* 0x25 */ u8 sfxFlags;
    /* 0x24 */ u8 sfxImportance;
    /* 0x26 */ u8 state; // uses SfxState enum
    /* 0x27 */ u8 freshness;
    /* 0x28 */ u8 prev;
    /* 0x29 */ u8 next;
    /* 0x2A */ u8 channelIndex;
    /* 0x2B */ u8 randFreq;
    /* 0x2C */ u8 token;
} SfxBankEntry; // size = 0x30

#define SFX_BANK_SHIFT(sfxId)   (((sfxId) >> 12) & 0xFF)

#define SFX_BANK_MASK(sfxId)    ((sfxId) & 0xF000)

#define SFX_INDEX(sfxId)    ((sfxId) & 0x3FF)
#define SFX_BANK(sfxId)     SFX_BANK_SHIFT(SFX_BANK_MASK(sfxId))

typedef struct {
    /* 0x0 */ u32 priority; // lower is more prioritized
    /* 0x4 */ u8 entryIndex;
} ActiveSfx; // size = 0x8

// SfxParams bit-packing

// Slows the decay of volume with distance (a 3-bit number ranging from 0-7)
#define SFX_PARAM_DIST_RANGE_SHIFT 0
#define SFX_PARAM_DIST_RANGE_MASK_UPPER (4 << SFX_PARAM_DIST_RANGE_SHIFT)
#define SFX_PARAM_DIST_RANGE_MASK (7 << SFX_PARAM_DIST_RANGE_SHIFT)

// Lower SEQ_PLAYER_BGM_MAIN and SEQ_PLAYER_BGM_SUB while the sfx is playing
#define SFX_FLAG_LOWER_VOLUME_BGM (1 << 3)

// Sfx priority is not raised with distance (making it more likely to be ejected)
#define SFX_FLAG_PRIORITY_NO_DIST (1 << 4)

// If a new sfx is requested at both the same position with the same importance,
// Block that new sfx from replacing the current sfx
// Note: Only 1 sfx can be played at a specific position at once
#define SFX_FLAG_BLOCK_EQUAL_IMPORTANCE (1 << 5)

// Applies increasingly random offsets to frequency (a 2-bit number ranging from 0-3)
#define SFX_PARAM_RAND_FREQ_RAISE_SHIFT 6
#define SFX_PARAM_RAND_FREQ_RAISE_MASK (3 << SFX_PARAM_RAND_FREQ_RAISE_SHIFT)

// Sets a flag to ioPort 5
#define SFX_FLAG_8 (1 << 8)

// Use lowpass filter on surround sound
#define SFX_FLAG_SURROUND_LOWPASS_FILTER (1 << 9)

// Unused remnant of OoT
#define SFX_FLAG_BEHIND_SCREEN_Z_INDEX_SHIFT 10
#define SFX_FLAG_BEHIND_SCREEN_Z_INDEX (1 << SFX_FLAG_BEHIND_SCREEN_Z_INDEX_SHIFT)

// Randomly scale base frequency each frame through mutiplicative offset
#define SFX_PARAM_RAND_FREQ_SCALE (1 << 11)

// Sfx reverb is not raised with distance
#define SFX_FLAG_REVERB_NO_DIST (1 << 12)

// Sfx volume is not lowered with distance
#define SFX_FLAG_VOLUME_NO_DIST (1 << 13)

// SFX_FLAG_VIBRATO 
// Randomly lower base frequency each frame through additive offset
#define SFX_PARAM_RAND_FREQ_LOWER (1 << 14)

// Sfx frequency is not raised with distance
#define SFX_FLAG_FREQ_NO_DIST (1 << 15)

// Force the sfx to reset from the beginning when requested again
#define SFX_FLAG2_FORCE_RESET (1 << 0)

// Unused
#define SFX_FLAG2_UNUSED2 (1 << 2)
#define SFX_FLAG2_UNUSED4 (1 << 4)

// Do not use highpass filter on surround sound
#define SFX_FLAG2_SURROUND_NO_HIGHPASS_FILTER (1 << 5)

// Unused
#define SFX_FLAG2_UNUSED6 (1 << 6)

// Apply a low-pass filter with a lowPassCutoff of 4
#define SFX_FLAG2_APPLY_LOWPASS_FILTER (1 << 7)

typedef struct {
    /* 0x0 */ u8 importance;
    /* 0x1 */ u8 flags;
    /* 0x2 */ u16 params;
} SfxParams; // size = 0x4

// functions in sfx.c

void AudioSfx_MuteBanks(u16 muteMask);
void AudioSfx_LowerBgmVolume(u8 channelIndex);
void AudioSfx_RestoreBgmVolume(u8 channelIndex);
void AudioSfx_PlaySfx(u16 sfxId, Vec3f* pos, u8 token, f32* freqScale, f32* volume, s8* reverbAdd);
void AudioSfx_ProcessRequest(void);
void AudioSfx_StopByBank(u8 bankId);
void AudioSfx_StopByPosAndBank(u8 bankId, Vec3f* pos);
void AudioSfx_StopByPos(Vec3f* pos);
void AudioSfx_StopByPosAndId(Vec3f* pos, u16 sfxId);
void AudioSfx_StopByTokenAndId(u8 token, u16 sfxId);
void AudioSfx_StopById(u32 sfxId);
void AudioSfx_ProcessRequests(void);
void AudioSfx_ProcessActiveSfx(void);
u8 AudioSfx_IsPlaying(u32 sfxId);
void AudioSfx_Reset(void);

// functions in code_8019AF00.c

void AudioSfx_SetProperties(u8 bankId, u8 entryIndex, u8 channelIndex);
void AudioSfx_LowerSfxSettingsReverb(Vec3f* pos, s8 isReverbLowered);
void AudioSfx_SetChannelIO(Vec3f* pos, u16 sfxId, u8 ioData);

// Various wrappers to AudioSfx_PlaySfx
void Audio_PlaySfx(u16 sfxId);
void Audio_PlaySfx_2(u16 sfxId);
void Audio_PlaySfx_AtPosWithPresetLowFreqAndHighReverb(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_AtPos(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_MessageDecide(void);
void Audio_PlaySfx_MessageCancel(void);
void Audio_PlaySfx_Underwater(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_WithSfxSettingsReverb(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_AtPosForMetalEffectsWithSyncedFreqAndVolume(Vec3f* pos, u16 sfxId, f32 freqVolParam);
void Audio_PlaySfx_AtPosWithSyncedFreqAndVolume(Vec3f* pos, u16 sfxId, f32 freqVolParam);
void Audio_PlaySfx_GiantsMask(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_Randomized(Vec3f* pos, u16 baseSfxId, u8 randLim);
void Audio_PlaySfx_SwordCharge(Vec3f* pos, u8 chargeLevel);
void Audio_PlaySfx_AtPosWithFreq(Vec3f* pos, u16 sfxId, f32 freqScale);
void Audio_PlaySfx_AtPosWithFreqAndChannelIO(Vec3f* pos, u16 sfxId, f32 freqScale, u8 arg3);
void Audio_PlaySfx_WaterWheel(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_AtPosWithTimer(Vec3f* pos, u16 sfxId, f32 timerShiftedLerp);
void Audio_PlaySfx_AtPosWithReverb(Vec3f* pos, u16 sfxId, s8 reverbAdd);
void Audio_PlaySfx_AtPosWithVolume(Vec3f* pos, u16 sfxId, f32 volume);
void Audio_PlaySfx_River(Vec3f* pos, f32 freqScale);
void Audio_PlaySfx_BigBells(Vec3f* pos, u8 volumeIndex);
void Audio_PlaySfx_AtPosWithChannelIO(Vec3f* pos, u16 sfxId, u8 ioData);
void Audio_PlaySfx_AtPosWithAllChannelsIO(Vec3f* pos, u16 sfxId, u8 ioData);
void Audio_PlaySfx_PauseMenuOpenOrClose(u8 pauseMenuOpenOrClose);
void Audio_PlaySfx_IfNotInCutscene(u16 sfxId);
void Audio_PlaySfx_AtFixedPos(Vec3f* pos, u16 sfxId);
void Audio_PlaySfx_AtPosWithVolumeTransition(Vec3f* pos, u16 sfxId, u16 duration);

// Sfx helper functions
void Audio_SetSfxUnderwaterReverb(s8 isUnderwaterReverbActivated);
void Audio_SetSfxTimerLerpInterval(s8 timerLerpRange1, s8 timerLerpRange2);
void Audio_SetSfxVolumeTransition(f32* volume, f32 volumeTarget, u16 duration);
void Audio_SetSfxReverbIndexExceptOcarinaBank(u8 reverbIndex);

extern ActiveSfx gActiveSfx[7][3];

extern u8 gIsLargeSfxBank[7];
extern u8 D_801D6608[7];
extern u8 gChannelsPerBank[4][7];
extern u8 gUsedChannelsPerBank[4][7];
extern f32 gSfxVolume;
extern SfxParams* gSfxParams[7];
extern SfxBankEntry* gSfxBanks[7];
extern u8 gSfxChannelLayout;
extern Vec3f gSfxDefaultPos;
extern f32 gSfxDefaultFreqAndVolScale;
extern s8 gSfxDefaultReverb;

#endif
