#ifndef Z_EN_WEATHER_TAG_H
#define Z_EN_WEATHER_TAG_H

#include <global.h>

struct EnWeatherTag;

typedef struct EnWeatherTag {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x18];
} EnWeatherTag; // size = 0x15C

extern const ActorInit En_Weather_Tag_InitVars;

#endif // Z_EN_WEATHER_TAG_H
