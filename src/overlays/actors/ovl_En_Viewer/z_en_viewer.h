#ifndef Z_EN_VIEWER_H
#define Z_EN_VIEWER_H

#include "global.h"

struct EnViewer;

typedef void (*EnViewerActionFunc)(struct EnViewer*, PlayState*);

typedef struct EnViewer {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnViewerActionFunc actionFunc;
    /* 0x148 */ char unk_148[0x10];
} EnViewer; // size = 0x158

extern const ActorInit En_Viewer_InitVars;

#endif // Z_EN_VIEWER_H
