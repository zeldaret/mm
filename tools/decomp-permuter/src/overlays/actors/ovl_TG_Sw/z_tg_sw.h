#ifndef Z_TG_SW_H
#define Z_TG_SW_H

#include <global.h>

struct TGSw;
typedef void (*TGSwActionFunc)(struct TGSw*, GlobalContext*);

typedef struct TGSw {
    /* 0x000 */ Actor actor;
    /* 0x144 */ TGSwActionFunc actionFunc;
} TGSw; // size = 0x148

extern const ActorInit TG_Sw_InitVars;

#endif // Z_TG_SW_H
