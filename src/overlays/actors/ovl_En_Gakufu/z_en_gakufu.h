#ifndef Z_EN_GAKUFU_H
#define Z_EN_GAKUFU_H

#include "global.h"

struct EnGakufu;

typedef void (*EnGakufuActionFunc)(struct EnGakufu*, GlobalContext*);

#define GAKUFU_GET_TYPE(thisx) ((thisx)->params & 0xF)

typedef enum {
    /* 0x00 */ GAKUFU_TERMINA_FIELD,   
    /* 0x01 */ GAKUFU_MILK_BAR
} GakufuType;

typedef struct EnGakufu {
    /* 0x000 */ Actor actor;
    /* 0x144 */ s32 songIndex;
    /* 0x148 */ u8 buttonIndex[8];
    /* 0x150 */ EnGakufuActionFunc actionFunc;
} EnGakufu; // size = 0x154

extern const ActorInit En_Gakufu_InitVars;

#endif // Z_EN_GAKUFU_H
