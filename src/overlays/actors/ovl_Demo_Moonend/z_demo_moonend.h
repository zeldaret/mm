    #ifndef Z_DEMO_MOONEND_H
#define Z_DEMO_MOONEND_H

#include "global.h"

struct DemoMoonend;

typedef void (*DemoMoonendActionFunc)(struct DemoMoonend*, PlayState*);

typedef struct DemoMoonend {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkeletonInfo skelInfo;
    /* 0x0174 */ Vec3s unk_174[30];
    /* 0x0228 */ Vec3s unk_228[30];
    /* 0x02DC */ u16 unk_2DC;
    /* 0x02DE */ u16 unk_2DE;
    /* 0x02E0 */ DemoMoonendActionFunc actionFunc;
} DemoMoonend; // size = 0x2E4

extern const ActorInit Demo_Moonend_InitVars;

#endif // Z_DEMO_MOONEND_H
