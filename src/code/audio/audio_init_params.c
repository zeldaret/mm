#include "global.h"

const s16 gAudioTatumInit[] = {
    0x1C00, // unused
    0x30,   // gTatumsPerBeat
};

const AudioContextInitSizes gAudioContextInitSizes = {
    0x137F00, // heapSize
    0x1C480,  // mainPoolSplitSize
    0x1A000,  // permanentPoolSize
};
