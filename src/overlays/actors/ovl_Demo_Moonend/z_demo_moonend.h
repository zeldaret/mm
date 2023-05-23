#ifndef Z_DEMO_MOONEND_H
#define Z_DEMO_MOONEND_H

#include "global.h"
#include "objects/object_moonend/object_moonend.h"

struct DemoMoonend;

typedef void (*DemoMoonendActionFunc)(struct DemoMoonend*, PlayState*);

#define DEMOMOONEND_GET_PARAMS_F(thisx) (((thisx)->params) & 0xF)

typedef struct DemoMoonend {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkeletonInfo skeletonInfo;
    /* 0x0174 */ Vec3s jointTable[30];
    /* 0x0228 */ Vec3s morphTable[30];
    /* 0x02DC */ u16 cueType;
    /* 0x02DE */ u16 cueId;
    /* 0x02E0 */ DemoMoonendActionFunc actionFunc;
} DemoMoonend; // size = 0x2E4

#endif // Z_DEMO_MOONEND_H
