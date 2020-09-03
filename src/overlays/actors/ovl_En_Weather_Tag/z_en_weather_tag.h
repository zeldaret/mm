#ifndef _Z_EN_WEATHER_TAG_H_
#define _Z_EN_WEATHER_TAG_H_

#include <global.h>

struct EnWeatherTag;

typedef struct EnWeatherTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} EnWeatherTag; // size = 0x15C

extern const ActorInit En_Weather_Tag_InitVars;

#endif
