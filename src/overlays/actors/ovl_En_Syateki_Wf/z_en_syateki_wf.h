#ifndef Z_EN_SYATEKI_WF_H
#define Z_EN_SYATEKI_WF_H

#include <global.h>

struct EnSyatekiWf;

typedef struct EnSyatekiWf {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x288];
} EnSyatekiWf; // size = 0x3CC

extern const ActorInit En_Syateki_Wf_InitVars;

#endif // Z_EN_SYATEKI_WF_H
