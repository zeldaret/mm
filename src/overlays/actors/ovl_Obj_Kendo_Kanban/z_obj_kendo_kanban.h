#ifndef Z_OBJ_KENDO_KANBAN_H
#define Z_OBJ_KENDO_KANBAN_H

#include "global.h"

struct ObjKendoKanban;

typedef void (*ObjKendoKanbanActionFunc)(struct ObjKendoKanban*, GlobalContext*);

#define OBJKENDOKANBAN_GET_F(thisx) ((thisx)->params & 0xF)

#define OBJKENDOKANBAN_F_0 0
#define OBJKENDOKANBAN_F_1 (1 << 0)
#define OBJKENDOKANBAN_F_2 (1 << 1)
#define OBJKENDOKANBAN_F_4 (1 << 2)
#define OBJKENDOKANBAN_F_8 (1 << 3)

typedef struct ObjKendoKanban {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderCylinder colliderCylinder;
    /* 0x0190 */ ColliderTris colliderTris;
    /* 0x01B0 */ ColliderTrisElement colliderTrisElements[2];
    /* 0x0268 */ ObjKendoKanbanActionFunc actionFunc;
    /* 0x026C */ Vec3f unk_26C[4];
    /* 0x029C */ Vec3f unk_29C[4];
    /* 0x02CC */ Vec3f unk_2CC;
    /* 0x02D8 */ Vec3f unk_2D8;
    /* 0x02E4 */ Vec3f unk_2E4;
    /* 0x02F0 */ Vec3f unk_2F0;
    /* 0x02FC */ s32 unk_2FC;
    /* 0x0300 */ s16 unk_300;
    /* 0x0302 */ s16 unk_302;
    /* 0x0304 */ s16 unk_304;
    /* 0x0306 */ UNK_TYPE1 pad306[2];
    /* 0x0308 */ s16 unk_308;
    /* 0x030A */ s16 unk_30A;
    /* 0x030C */ u8 unk_30C;
} ObjKendoKanban; // size = 0x310

extern const ActorInit Obj_Kendo_Kanban_InitVars;

#endif // Z_OBJ_KENDO_KANBAN_H
