#ifndef Z_EN_KANBAN_H
#define Z_EN_KANBAN_H

#include <global.h>

struct EnKanban;

typedef struct EnKanban {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0xAC];
} EnKanban; // size = 0x1F0

extern const ActorInit En_Kanban_InitVars;

#endif // Z_EN_KANBAN_H
