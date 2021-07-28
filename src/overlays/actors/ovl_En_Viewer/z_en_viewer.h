#ifndef Z_EN_VIEWER_H
#define Z_EN_VIEWER_H

#include "global.h"

struct EnViewer;

typedef struct EnViewer {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x14];
} EnViewer; // size = 0x158

extern const ActorInit En_Viewer_InitVars;

#endif // Z_EN_VIEWER_H
