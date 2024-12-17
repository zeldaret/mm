#include "global.h"
#include "buffers.h"
#include "assets/audio/sequence_sizes.h"
#include "assets/audio/soundfont_sizes.h"
#define SFX_SEQ_SIZE Sequence_0_SIZE
#define AMBIENCE_SEQ_SIZE Sequence_1_SIZE
#define SFX_SOUNDFONTS_SIZE (Soundfont_0_SIZE + Soundfont_1_SIZE + Soundfont_2_SIZE)

static s32 sBssPad[36];
AudioContext gAudioCtx;
AudioCustomUpdateFunction gAudioCustomUpdateFunction;
AudioCustomSeqFunction gAudioCustomSeqFunction;
AudioCustomReverbFunction gAudioCustomReverbFunction;
AudioCustomSynthFunction gAudioCustomSynthFunction;
static s32 sBssPad2[3];

const s16 gAudioTatumInit[] = {
    0x1C00,          // unused
    TATUMS_PER_BEAT, // gTatumsPerBeat
};

// Sizes of everything on the init pool
#define AI_BUFFERS_SIZE (AIBUF_SIZE * ARRAY_COUNT(gAudioCtx.aiBuffers))
#define SOUNDFONT_LIST_SIZE (NUM_SOUNDFONTS * sizeof(SoundFont))

// 0x19BD0
#define PERMANENT_POOL_SIZE (SFX_SEQ_SIZE + AMBIENCE_SEQ_SIZE + SFX_SOUNDFONTS_SIZE + 0x430)

#ifndef AVOID_UB
// Qualifying gAudioHeapInitSizes with const appears to be required for matching, however
// gAudioHeapInitSizes.permanentPoolSize is written to (see load.c)
#define CONST const
#else
// Avoid UB: gAudioHeapInitSizes isn't really const since it is written to, so do not
// declare it as const.
#define CONST
#endif
CONST AudioHeapInitSizes gAudioHeapInitSizes = {
    ALIGN16(sizeof(gAudioHeap) - 0x100),                                         // audio heap size
    ALIGN16(PERMANENT_POOL_SIZE + AI_BUFFERS_SIZE + SOUNDFONT_LIST_SIZE + 0x40), // init pool size
    ALIGN16(PERMANENT_POOL_SIZE),                                                // permanent pool size
};

#define REVERB_INDEX_0_SETTINGS \
    { 1, 0x30, 0x3000, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x3000, 0, 0 }

ReverbSettings reverbSettings0[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x20, 0x0800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 0, 0 },
};

ReverbSettings reverbSettings1[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x1800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 11, 11 },
};

ReverbSettings reverbSettings2[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x38, 0x2800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 7, 7 },
};

ReverbSettings reverbSettings3[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x6800, 0, 0, 0x7FFF, 0x1400, 0x1400, REVERB_INDEX_NONE, 0x3000, 6, 6 },
    { 2, 0x50, 0x6000, 0, 0, 0x7FFF, 0xD000, 0x3000, REVERB_INDEX_NONE, 0x3000, 0, 0 },
};

ReverbSettings reverbSettings4[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x40, 0x5000, 0, 0, 0x7FFF, 0x1800, 0x1800, REVERB_INDEX_NONE, 0x3000, 7, 7 },
};

ReverbSettings reverbSettings5[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x40, 0x5C00, 0, 0, 0x7FFF, 0x2000, 0x2000, REVERB_INDEX_NONE, 0x3000, 4, 4 },
};

ReverbSettings reverbSettings6[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x6000, 0, 0, 0x7FFF, 0x1000, 0x1000, REVERB_INDEX_NONE, 0x3000, 10, 10 },
};

ReverbSettings reverbSettings7[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x6800, 0, 0, 0x7FFF, 0x1400, 0x1400, REVERB_INDEX_NONE, 0x3000, 6, 6 },
};

ReverbSettings reverbSettings8[2] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x50, 0x5000, 0, 0, 0x7FFF, 0xD000, 0x3000, REVERB_INDEX_NONE, 0x3000, 0, 0 },
};

ReverbSettings reverbSettings9[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x20, 0x0000, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 0, 0 },
};

ReverbSettings reverbSettingsA[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x1800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 11, 11 },
};

ReverbSettings reverbSettingsB[3] = {
    REVERB_INDEX_0_SETTINGS,
};

ReverbSettings reverbSettingsC[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x40, 0x5000, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x3000, 0, 0 },
};

ReverbSettings reverbSettingsD[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x6800, 0, 0, 0x7FFF, 0x1400, 0x1400, REVERB_INDEX_NONE, 0x3000, 6, 6 },
    { 2, 0x50, 0x6000, 0, 0, 0x7FFF, 0xD000, 0x3000, REVERB_INDEX_NONE, 0x3000, 0, 0 },
};

ReverbSettings reverbSettingsE[3] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x30, 0x1800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 11, 11 },
    { 1, 0x40, 0x5000, 0, 0, 0x7FFF, 0x1800, 0x1800, REVERB_INDEX_NONE, 0x3000, 7, 7 },
};

ReverbSettings reverbSettingsF[2] = {
    REVERB_INDEX_0_SETTINGS,
    { 1, 0x50, 0x1800, 0, 0, 0x7FFF, 0x0000, 0x0000, REVERB_INDEX_NONE, 0x0000, 11, 11 },
};

ReverbSettings* gReverbSettingsTable[] = {
    reverbSettings0, reverbSettings1, reverbSettings2, reverbSettings4, reverbSettings5,
    reverbSettings6, reverbSettings7, reverbSettings8, reverbSettings9, reverbSettings3,
};

AudioSpec gAudioSpecs[21] = {
    /* 0x0 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x1 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x2 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x3 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x4 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x5 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x6 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x7 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x8 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x9 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0xA */
    { 32000, 1, 28, 3, 0, 0, 2, reverbSettingsA, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x2800, 0x2D00, 0, 0,
      0xDC800 },
    /* 0xB */
    { 32000, 1, 28, 3, 0, 0, 2, reverbSettingsA, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0xC */
    { 32000, 1, 28, 5, 0, 0, 2, reverbSettingsA, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xCC800 },
    /* 0xD */
    { 32000, 1, 24, 5, 0, 0, 3, reverbSettingsD, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0xE */
    { 32000, 1, 24, 5, 0, 0, 3, reverbSettingsE, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0xF */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettingsF, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4000, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x10 */
    { 32000, 1, 22, 5, 0, 0, 2, reverbSettings0, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x11 */
    { 32000, 1, 22, 5, 0, 0, 2, reverbSettings8, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x12 */
    { 32000, 1, 16, 5, 0, 0, 2, reverbSettings0, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x13 */
    { 22050, 1, 24, 5, 0, 0, 2, reverbSettings0, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x4100, 0x2D00, 0, 0,
      0xDC800 },
    /* 0x14 */
    { 32000, 1, 24, 5, 0, 0, 2, reverbSettings2, 0x500, 0x200, 0x7FFF, 0xAF0, 0x2D80, 0, 0x3600, 0x2600, 0, 0,
      0xDC800 },
};
