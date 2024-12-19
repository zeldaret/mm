#include "z64audio.h"
#include "buffers.h"
#include "assets/audio/sequence_sizes.h"
#include "assets/audio/soundfont_sizes.h"

#define SFX_SEQ_SIZE Sequence_0_SIZE
#define AMBIENCE_SEQ_SIZE Sequence_1_SIZE
#define SFX_SOUNDFONTS_SIZE (Soundfont_0_SIZE + Soundfont_1_SIZE + Soundfont_2_SIZE)

s16 gAudioTatumInit[] = {
    0x1C00,          // unused
    TATUMS_PER_BEAT, // gTatumsPerBeat
};

// Sizes of everything on the init pool
#define AI_BUFFERS_SIZE (AIBUF_SIZE * ARRAY_COUNT(gAudioCtx.aiBuffers))
#define SOUNDFONT_LIST_SIZE (NUM_SOUNDFONTS * sizeof(SoundFont))

// 0x19BD0
#define PERMANENT_POOL_SIZE (SFX_SEQ_SIZE + AMBIENCE_SEQ_SIZE + SFX_SOUNDFONTS_SIZE + 0x430)

AudioHeapInitSizes gAudioHeapInitSizes = {
    ALIGN16(sizeof(gAudioHeap) - 0x100),                                         // audio heap size
    ALIGN16(PERMANENT_POOL_SIZE + AI_BUFFERS_SIZE + SOUNDFONT_LIST_SIZE + 0x40), // init pool size
    ALIGN16(PERMANENT_POOL_SIZE),                                                // permanent pool size
};
