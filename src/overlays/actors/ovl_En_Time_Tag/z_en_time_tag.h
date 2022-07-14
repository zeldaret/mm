#ifndef Z_EN_TIME_TAG_H
#define Z_EN_TIME_TAG_H

#include "global.h"

struct EnTimeTag;

typedef void (*EnTimeTagActionFunc)(struct EnTimeTag*, PlayState*);

#define ENTIMETAG_GET_1F(thisx) ((thisx)->params & 0x1F)
#define ENTIMETAG_GET_SWITCHFLAG(thisx) ((thisx)->params & 0x7F)
#define ENTIMETAG_GET_1FE0(thisx) (((thisx)->params & 0x1FE0) >> 0x5)
#define ENTIMETAG_GET_E000(thisx) (((thisx)->params & 0xE000) >> 0xD)

typedef struct EnTimeTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTimeTagActionFunc actionFunc;
} EnTimeTag; // size = 0x148

extern const ActorInit En_Time_Tag_InitVars;

#endif // Z_EN_TIME_TAG_H
