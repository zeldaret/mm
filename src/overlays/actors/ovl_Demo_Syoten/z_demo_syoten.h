#ifndef Z_DEMO_SYOTEN_H
#define Z_DEMO_SYOTEN_H

#include "global.h"

struct DemoSyoten;

typedef void (*DemoSyotenActionFunc)(struct DemoSyoten*, GlobalContext*);

#define DEMOSYOTEN_GET_F(thisx) ((thisx)->params & 0xF)
#define DEMOSYOTEN_GET_7E00(thisx) (((thisx)->params & 0x7E00) >> 9)

#define DEMOSYOTEN_7E00_3F 0x3F

enum {
    /* 0 */ DEMOSYOTEN_F_0,
    /* 1 */ DEMOSYOTEN_F_1,
    /* 2 */ DEMOSYOTEN_F_2,
    /* 3 */ DEMOSYOTEN_F_3,
    /* 4 */ DEMOSYOTEN_F_4
};

typedef struct {
    /* 0x00 */ UNK_TYPE1 unk00[0x1];
    /* 0x01 */ u8 count;
    /* 0x02 */ UNK_TYPE1 unk2[0x16];
} DemoSyotenStruct2; // almost certainly wrong, just filling space

typedef struct DemoSyoten {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ UNK_TYPE1 unk_144[0x18];
    /* 0x015C */ DemoSyotenStruct2* unk_15C;
    /* 0x0160 */ UNK_TYPE1 unk160[0x14];
    /* 0x0174 */ Vec3s unk_174[51];
    /* 0x02A6 */ Vec3s unk_2A6[51];
    /* 0x03D8 */ f32 unk_3D8;
    /* 0x03DC */ Gfx* unk_3DC;
    /* 0x03E0 */ AnimatedMaterial* unk_3E0;
    /* 0x03E4 */ u16 unk_3E4;
    /* 0x03E6 */ s16 unk_3E6;
    /* 0x03E8 */ Path* unk_3E8;
    /* 0x03EC */ s32 unk_3EC;
    /* 0x03F0 */ u16 unk_3F0;
    /* 0x03F2 */ u16 unk_3F2;
    /* 0x03F4 */ DemoSyotenActionFunc actionFunc;
} DemoSyoten; // size = 0x3F8

extern const ActorInit Demo_Syoten_InitVars;

#endif // Z_DEMO_SYOTEN_H
