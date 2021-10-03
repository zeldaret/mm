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
 **/
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
} EnGiantType;

struct EnGiant;

typedef void (*EnGiantActionFunc)(struct EnGiant*, GlobalContext*);

typedef struct EnGiant {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[16];
    /* 0x1E8 */ Vec3s morphTable[16];
    /* 0x248 */ s16 animationId;
    /* 0x24A */ u16 unk_24A;
    /* 0x24C */ u16 unk_24C;
    /* 0x24E */ s16 alpha;
    /* 0x250 */ u16 sfxId;
    /* 0x254 */ MtxF unk_254;
    /* 0x294 */ s16 unk_294;
    /* 0x296 */ s16 unk_296;
    /* 0x298 */ EnGiantActionFunc actionFunc;
} EnGiant; // size = 0x29C

extern const ActorInit En_Giant_InitVars;

#endif // Z_EN_GIANT_H
