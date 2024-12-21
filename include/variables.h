#ifndef VARIABLES_H
#define VARIABLES_H

#include "z64.h"
#include "segment_symbols.h"
#include "stack.h"
#include "macros.h"

// data

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
extern s32 gAudioCtxInitialized;
extern STACK(aspMainStack, 0x400);

extern u8 gAudioSpecId;
extern u8 gAudioHeapResetState;
extern AudioSpec gAudioSpecs[21];

// rodata
extern const u16 gAudioEnvironmentalSfx[];
extern s16 gAudioTatumInit[];
extern AudioHeapInitSizes gAudioHeapInitSizes;
extern AudioTable gSoundFontTable;
extern u8 gSequenceFontTable[];
extern u8 gSequenceTable[];
extern AudioTable gSampleBankTable;

// bss

extern u64* gAudioSPDataPtr;
extern u32 gAudioSPDataSize;

// other segments
extern Mtx D_01000000;
extern Gfx D_08000000[];
extern u16 D_0F000000[];

#endif
