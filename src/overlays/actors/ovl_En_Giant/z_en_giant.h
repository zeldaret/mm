#ifndef Z_EN_GIANT_H
#define Z_EN_GIANT_H

#include "global.h"

#define GIANT_TYPE(thisx) ((thisx)->params & 0xF)

/**
 * The giants are divided into types based on where in the game they appear.
 * - TERMINA_FIELD: These appear in all non-ending cutscenes that take place in Termina Field.
 * - CLOCK_TOWER_SUCCESS: These appear in the Clock Tower when the Oath to Order is played and all giants are freed.
 * - GIANTS_CHAMBER_AND_ENDING: These giants appear in the Giant's Chamber or in all cutscenes that play after defeating Majora.
 * - CLOCK_TOWER_FAILURE: These appear in the Clock Tower when the Oath to Order is played and all giants are NOT freed.
 */
typedef enum {
    /*  0 */ GIANT_TYPE_MOUNTAIN_TERMINA_FIELD,
    /*  1 */ GIANT_TYPE_CANYON_TERMINA_FIELD,
    /*  2 */ GIANT_TYPE_SWAMP_TERMINA_FIELD,
    /*  3 */ GIANT_TYPE_OCEAN_TERMINA_FIELD,
    /*  4 */ GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_SUCCESS,
    /*  5 */ GIANT_TYPE_CANYON_CLOCK_TOWER_SUCCESS,
    /*  6 */ GIANT_TYPE_SWAMP_CLOCK_TOWER_SUCCESS,
    /*  7 */ GIANT_TYPE_OCEAN_CLOCK_TOWER_SUCCESS,
    /*  8 */ GIANT_TYPE_MOUNTAIN_GIANTS_CHAMBER_AND_ENDING,
    /*  9 */ GIANT_TYPE_CANYON_GIANTS_CHAMBER_AND_ENDING,
    /* 10 */ GIANT_TYPE_SWAMP_GIANTS_CHAMBER_AND_ENDING,
    /* 11 */ GIANT_TYPE_OCEAN_GIANTS_CHAMBER_AND_ENDING,
    /* 12 */ GIANT_TYPE_MOUNTAIN_CLOCK_TOWER_FAILURE,
    /* 13 */ GIANT_TYPE_CANYON_CLOCK_TOWER_FAILURE,
    /* 14 */ GIANT_TYPE_SWAMP_CLOCK_TOWER_FAILURE,
    /* 15 */ GIANT_TYPE_OCEAN_CLOCK_TOWER_FAILURE,
    /* 16 */ GIANT_TYPE_MAX
} GiantType;

/**
 * These values are used to index into sAnimationTable to pick the appropriate animation.
 */
typedef enum {
    /*  0 */ GIANT_ANIMATION_LOOK_UP_START,
    /*  1 */ GIANT_ANIMATION_LOOK_UP_LOOP,
    /*  2 */ GIANT_ANIMATION_FALLING_OVER,
    /*  3 */ GIANT_ANIMATION_RAISED_ARMS_START,
    /*  4 */ GIANT_ANIMATION_RAISED_ARMS_LOOP,
    /*  5 */ GIANT_ANIMATION_STRUGGLE_START,
    /*  6 */ GIANT_ANIMATION_STRUGGLE_LOOP,
    /*  7 */ GIANT_ANIMATION_IDLE_LOOP,
    /*  8 */ GIANT_ANIMATION_WALKING_LOOP,
    /*  9 */ GIANT_ANIMATION_BIG_CALL_START,
    /* 10 */ GIANT_ANIMATION_BIG_CALL_LOOP,
    /* 11 */ GIANT_ANIMATION_BIG_CALL_END,
    /* 12 */ GIANT_ANIMATION_SMALL_CALL_START,
    /* 13 */ GIANT_ANIMATION_SMALL_CALL_LOOP,
    /* 14 */ GIANT_ANIMATION_SMALL_CALL_END,
    /* 15 */ GIANT_ANIMATION_MAX
} GiantAnimationIndex;

struct EnGiant;

typedef void (*EnGiantActionFunc)(struct EnGiant*, GlobalContext*);

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ s16 animationId;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u16 action;
    /* 0x24E */ s16 alpha;
    /* 0x250 */ u16 sfxId;
    /* 0x254 */ MtxF unk_254;
    /* 0x294 */ s16 faceIndex;
    /* 0x296 */ s16 blinkTimer;
    /* 0x298 */ EnGiantActionFunc actionFunc;
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
