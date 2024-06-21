#ifndef VARIABLES_H
#define VARIABLES_H

#include "z64.h"
#include "segment_symbols.h"
#include "macros.h"

// data

extern s32 gDbgCamEnabled;

extern s16 gLowPassFilterData[];
extern s16 gHighPassFilterData[];
extern s16 gBandStopFilterData[];
extern s16 gBandPassFilterData[];
extern s16* gWaveSamples[9];
extern f32 gBendPitchOneOctaveFrequencies[];
extern f32 gBendPitchTwoSemitonesFrequencies[];
extern f32 gPitchFrequencies[];
extern u8 gDefaultShortNoteVelocityTable[];
extern u8 gDefaultShortNoteGateTimeTable[];
extern EnvelopePoint gDefaultEnvelope[];
extern NoteSampleState gZeroedSampleState;
extern NoteSampleState gDefaultSampleState;
extern u16 gHaasEffectDelaySize[];
extern u16 gHaasEffectDelaySize[];
extern s16 gInvalidAdpcmCodeBook[];
extern f32 gHeadsetPanVolume[];
extern f32 gStereoPanVolume[];
extern f32 gDefaultPanVolume[];
extern s32 gAudioCtxInitalized;
extern u8 D_801D6200[0x400];

extern u8 gAudioSpecId;
extern u8 gAudioHeapResetState;
extern AudioSpec gAudioSpecs[21];

// rodata
extern const u16 gAudioEnvironmentalSfx[];
extern const s16 gAudioTatumInit[];
extern const AudioHeapInitSizes gAudioHeapInitSizes;
extern u8 gSoundFontTable[];
extern u8 gSequenceFontTable[];
extern u8 gSequenceTable[];
extern u8 gSampleBankTable[];

// bss

extern s32 gTransitionTileState;
extern Color_RGBA8_u32 gPlayVisMonoColor;

extern u64* gAudioSPDataPtr;
extern u32 gAudioSPDataSize;

extern s32 D_801FD120;

extern u8 sResetAudioHeapTimer;
extern u16 sResetAudioHeapFadeReverbVolume;
extern u16 sResetAudioHeapFadeReverbVolumeStep;
extern AudioContext gAudioCtx; // at 0x80200C70

// other segments
extern Mtx D_01000000;
extern u16 D_0F000000[];


#endif
