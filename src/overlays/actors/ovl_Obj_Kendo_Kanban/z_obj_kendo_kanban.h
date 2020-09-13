#ifndef Z_OBJ_KENDO_KANBAN_H
#define Z_OBJ_KENDO_KANBAN_H

#include <global.h>

struct ObjKendoKanban;

typedef struct ObjKendoKanban {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1CC];
} ObjKendoKanban; // size = 0x310

extern const ActorInit Obj_Kendo_Kanban_InitVars;

#endif // Z_OBJ_KENDO_KANBAN_H
