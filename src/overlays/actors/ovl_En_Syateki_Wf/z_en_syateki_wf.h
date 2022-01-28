#ifndef Z_EN_SYATEKI_WF_H
#define Z_EN_SYATEKI_WF_H

#include "global.h"

struct EnSyatekiWf;

typedef void (*EnSyatekiWfActionFunc)(struct EnSyatekiWf*, GlobalContext*);

typedef struct EnSyatekiWf {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x150];
    /* 0x0294 */ EnSyatekiWfActionFunc actionFunc;
    /* 0x0298 */ char unk_298[0x134];
} EnSyatekiWf; // size = 0x3CC

extern const ActorInit En_Syateki_Wf_InitVars;

#endif // Z_EN_SYATEKI_WF_H
