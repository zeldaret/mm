#ifndef Z64_DOOR_H
#define Z64_DOOR_H

#include "ultra64.h"
#include "z64actor.h"

typedef struct KnobDoorActor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ SkelAnime skelAnime;
    /* 0x1A0 */ u8 animIndex;
    /* 0x1A1 */ u8 playOpenAnim;
    /* 0x1A2 */ s8 objectSlot;
    /* 0x1A3 */ s8 dlIndex;
} KnobDoorActor; // size = 0x1A4

typedef struct SlidingDoorActor {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x15C */ s16 unk_15C;
    /* 0x15E */ s16 unk_15E;
} SlidingDoorActor; // size = 0x160

#define DOOR_GET_TRANSITION_ID(thisx) ((u16)(thisx)->params >> 10)

#endif
