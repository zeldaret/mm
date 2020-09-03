#ifndef _Z_OBJ_KENDO_KANBAN_H_
#define _Z_OBJ_KENDO_KANBAN_H_

#include <global.h>

struct ObjKendoKanban;

typedef struct ObjKendoKanban {
    /* 0x000 */ Actor actor;
    /* 0x144 */ char unk_144[0x1CC];
} ObjKendoKanban; // size = 0x310

extern const ActorInit Obj_Kendo_Kanban_InitVars;

#endif
