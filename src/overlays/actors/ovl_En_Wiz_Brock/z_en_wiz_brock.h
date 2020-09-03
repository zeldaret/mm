#ifndef Z_EN_WIZ_BROCK_H
#define Z_EN_WIZ_BROCK_H

#include <global.h>

struct EnWizBrock;

typedef struct EnWizBrock {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x6C];
} EnWizBrock; // size = 0x1B0

extern const ActorInit En_Wiz_Brock_InitVars;

#endif // Z_EN_WIZ_BROCK_H
