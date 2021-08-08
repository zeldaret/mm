#ifndef Z_OBJ_KENDO_KANBAN_H
#define Z_OBJ_KENDO_KANBAN_H

#include "global.h"

struct ObjKendoKanban;

typedef void (*ObjKendoKanbanActionFunc)(struct ObjKendoKanban* this, GlobalContext* globalCtx);

typedef struct ObjKendoKanban {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ char unk_144[0x124];
    /* 0x0268 */ ObjKendoKanbanActionFunc actionFunc;
    /* 0x026C */ char unk_26C[0xA4];
} ObjKendoKanban; // size = 0x310

extern const ActorInit Obj_Kendo_Kanban_InitVars;

#endif // Z_OBJ_KENDO_KANBAN_H
