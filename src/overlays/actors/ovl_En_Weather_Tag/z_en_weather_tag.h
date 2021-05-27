#ifndef Z_EN_WEATHER_TAG_H
#define Z_EN_WEATHER_TAG_H

#include <global.h>

struct EnWeatherTag;

typedef void (*EnWeatherTagActionFunc)(struct EnWeatherTag*, GlobalContext*);

typedef struct EnWeatherTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnWeatherTagActionFunc actionFunc;
    /* 0x148 */ char unk148[0x4];
    /* 0x14C */ u8 unk14C; // path count 
    /* 0x150 */ UNK_PTR unk150;
    /* 0x154 */ u16 unk154;
    /* 0x156 */ s16 unk156;
    /* 0x158 */ u16 unk158;
    /* 0x15A */ s16 unk15A; // pad?
} EnWeatherTag; // size = 0x15C

extern const ActorInit En_Weather_Tag_InitVars;

extern s8 D_801BDBB8;
extern s8 D_801BDBB4;
extern u8 D_801BDBB0;

#endif // Z_EN_WEATHER_TAG_H
