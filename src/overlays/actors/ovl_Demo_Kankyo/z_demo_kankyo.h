#ifndef Z_DEMO_KANKYO_H
#define Z_DEMO_KANKYO_H

#include "global.h"

struct DemoKankyo;

typedef void (*DemoKankyoActionFunc)(struct DemoKankyo*, GlobalContext*);

typedef struct {
  /* 0x000 */ u8 unk_00;
  /* 0x004 */ Vec3f unk_04;
  /* 0x010 */ Vec3f unk_10;
  /* 0x01C */ Vec3f unk_1C;
  /* 0x028 */ Vec3f unk_28;
  /* 0x034 */ f32 unk_34;
  /* 0x038 */ f32 unk_38;
  /* 0x03C */ u16 unk_3C;
  /* 0x03E */ u16 unk_3E;
  /* 0x040 */ u8 unk_40;
  /* 0x044 */ f32 unk_44;
  /* 0x048 */ u16 unk_48;
  /* 0x04A */ u16 unk_4A;
  /* 0x04C */ f32 unk_4C;
  /* 0x050 */ u16 unk_50;
  /* 0x052 */ UNK_TYPE1 unk52[0x2];
} DemoKankyoParticle; // size = 0x54

#define DEMOKANKYO_PARTICLE_COUNT 64

typedef struct DemoKankyo {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ DemoKankyoParticle particles[64];
    /* 0x1644 */ DemoKankyoActionFunc actionFunc;
    /* 0x1648 */ s32 unk_1648;
    /* 0x164C */ u8 unk_164C;
} DemoKankyo; // size = 0x1650

extern const ActorInit Demo_Kankyo_InitVars;

#endif // Z_DEMO_KANKYO_H
