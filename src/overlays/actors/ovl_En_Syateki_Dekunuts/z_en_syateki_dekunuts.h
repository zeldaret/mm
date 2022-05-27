#ifndef Z_EN_SYATEKI_DEKUNUTS_H
#define Z_EN_SYATEKI_DEKUNUTS_H

#include "global.h"

struct EnSyatekiDekunuts;

typedef void (*EnSyatekiDekunutsActionFunc)(struct EnSyatekiDekunuts*, GlobalContext*);

typedef struct EnSyatekiDekunuts {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x44];
    /* 0x0188 */ EnSyatekiDekunutsActionFunc actionFunc;
    /* 0x018C */ char unk_18C[0xE4];
} EnSyatekiDekunuts; // size = 0x270

extern const ActorInit En_Syateki_Dekunuts_InitVars;

#endif // Z_EN_SYATEKI_DEKUNUTS_H
