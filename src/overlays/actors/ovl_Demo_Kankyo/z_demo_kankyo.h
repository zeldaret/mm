#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include "global.h"

struct DemoKankyo;

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);

typedef struct {
  /* 0x000 */ u8 state;
  /* 0x004 */ Vec3f posOffset;
  /* 0x010 */ Vec3f posOffsetPrev;
  /* 0x01C */ Vec3f posBase;
  /* 0x028 */ Vec3f speedClock; // cycles in radians
  /* 0x034 */ f32 speed;
  /* 0x038 */ f32 speedTarget;
  /* 0x03C */ u16 alphaClock;
  /* 0x03E */ u16 LostWoodsSkyFishSpeedXZClock;
  /* 0x040 */ u8 alpha;
  /* 0x044 */ f32 scale; // size of the particle
  /* 0x048 */ u16 LostWoodsSkyFishSpeedXZ; // the x-z speed (angular velocity) the lost woods skyfish oscillates around player. pos or neg 200-400 
  /* 0x04A */ u16 LostWoodsSkyFishPosOffsetMax; // The x-z range the lost woods skyfish oscillates around player. random value between 15-65
  /* 0x04C */ f32 LostWoodsSkyFishSpeedY; // the y speed (angular velocity) the lost woods skyfish oscillates around player.
  /* 0x050 */ u16 pad50; // unused, always assigned to 0, nothing else in this actor uses it
} DemoKankyoParticle; // size = 0x54

#define DEMOKANKYO_PARTICLE_COUNT 64

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DemoKankyoParticle particles[DEMOKANKYO_PARTICLE_COUNT];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ s32 objectId;
    /* 0x164C */ u8 isSafeToDrawGiants;
} DemoKankyo; // size = 0x1650

typedef enum {
    /* 0 */ DEMO_KANKYO_TYPE_LOSTWOODS,
    /* 1 */ DEMO_KANKYO_TYPE_GIANTS,
    /* 2 */ DEMO_KANKYO_TYPE_MOON,
} DemoKankyoType;

typedef enum {
    /* 0 */ DEMO_KANKYO_STATE_INIT,
    /* 1 */ DEMO_KANKYO_STATE_SINGLE,
    /* 2 */ DEMO_KANKYO_STATE_SKYFISH,
    /* 3 */ DEMO_KANKYO_STATE_DISABLED,
} DemoKankyoStateType;

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
