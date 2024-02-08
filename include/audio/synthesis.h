#ifndef AUDIO_SYNTHESIS_H
#define AUDIO_SYNTHESIS_H

#include "PR/ultratypes.h"
#include "PR/abi.h"
#include "unk.h"

// size of a single sample point
#define SAMPLE_SIZE sizeof(s16)

// Samples are processed in groups of 16 called a "frame"
#define SAMPLES_PER_FRAME ADPCMFSIZE

// The length of one left/right channel is 13 frames
#define DMEM_1CH_SIZE (13 * SAMPLES_PER_FRAME * SAMPLE_SIZE)
// Both left and right channels
#define DMEM_2CH_SIZE (2 * DMEM_1CH_SIZE)

// Must be the same amount of samples as copied by aDuplicate() (audio microcode)
#define WAVE_SAMPLE_COUNT 64

typedef struct NoteSynthesisBuffers {
    /* 0x000 */ s16 adpcmState[16];
    /* 0x020 */ s16 finalResampleState[16];
    /* 0x040 */ s16 filterState[32];
    /* 0x080 */ s16 unusedState[16];
    /* 0x0A0 */ s16 haasEffectDelayState[32];
    /* 0x0E0 */ s16 combFilterState[128];
    /* 0x1E0 */ s16 surroundEffectState[128];
} NoteSynthesisBuffers; // size = 0x2E0

typedef struct NoteSynthesisState {
    /* 0x00 */ u8 atLoopPoint : 1;
    /* 0x00 */ u8 stopLoop : 1;
    /* 0x01 */ u8 sampleDmaIndex;
    /* 0x02 */ u8 prevHaasEffectLeftDelaySize;
    /* 0x03 */ u8 prevHaasEffectRightDelaySize;
    /* 0x04 */ u8 curReverbVol;
    /* 0x05 */ u8 numParts;
    /* 0x06 */ u16 samplePosFrac; // Fractional part of the sample position
    /* 0x08 */ u16 surroundEffectGain;
    /* 0x0C */ s32 samplePosInt; // Integer part of the sample position
    /* 0x10 */ NoteSynthesisBuffers* synthesisBuffers;
    /* 0x14 */ s16 curVolLeft;
    /* 0x16 */ s16 curVolRight;
    /* 0x18 */ UNK_TYPE1 unk_18[0x6];
    /* 0x1E */ u8 combFilterNeedsInit;
    /* 0x1F */ u8 unk_1F;
    /* 0x20 */ UNK_TYPE1 unk_20[0x4];
} NoteSynthesisState; // size = 0x24

Acmd* AudioSynth_Update(Acmd* abiCmdStart, s32* numAbiCmds, s16* aiBufStart, s32 numSamplesPerFrame);

#endif
