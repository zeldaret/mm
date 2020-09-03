#ifndef _Z_EN_SYATEKI_DEKUNUTS_H_
#define _Z_EN_SYATEKI_DEKUNUTS_H_

#include <global.h>

struct EnSyatekiDekunuts;

typedef struct EnSyatekiDekunuts {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x12C];
} EnSyatekiDekunuts; // size = 0x270

extern const ActorInit En_Syateki_Dekunuts_InitVars;

#endif
