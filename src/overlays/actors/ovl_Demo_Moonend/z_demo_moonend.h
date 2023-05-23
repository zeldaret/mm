#ifndef Z_DEMO_MOONEND_H
#define Z_DEMO_MOONEND_H

#include "global.h"
#include "objects/object_moonend/object_moonend.h"

struct DemoMoonend;

typedef void (*DemoMoonendActionFunc)(struct DemoMoonend*, PlayState*);

#define DEMOMOONEND_GET_PARAMS_F(thisx) (((thisx)->params) & 0xF)

typedef struct DemoMoonend {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkeletonInfo skelInfo;
    /* 0x0174 */ Vec3s unk_174[30];
    /* 0x0228 */ Vec3s unk_228[30];
    /* 0x02DC */ u16 actorActionCmd;
    /* 0x02DE */ u16 actorAction;
    /* 0x02E0 */ DemoMoonendActionFunc actionFunc;
} DemoMoonend; // size = 0x2E4

#endif // Z_DEMO_MOONEND_H
