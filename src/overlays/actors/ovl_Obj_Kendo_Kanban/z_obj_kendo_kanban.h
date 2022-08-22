#ifndef Z_OBJ_KENDO_KANBAN_H
#define Z_OBJ_KENDO_KANBAN_H

#include "global.h"

struct ObjKendoKanban;

typedef void (*ObjKendoKanbanActionFunc)(struct ObjKendoKanban*, PlayState*);

#define OBJKENDOKANBAN_GET_F(thisx) ((thisx)->params & 0xF)

typedef struct ObjKendoKanban {
    /* 0x000 */ Actor actor;
    /* 0x144 */ ColliderCylinder colliderCylinder;
    /* 0x190 */ ColliderTris colliderTris;
    /* 0x1B0 */ ColliderTrisElement colliderTrisElements[2];
    /* 0x268 */ ObjKendoKanbanActionFunc actionFunc;
    /* 0x26C */ Vec3f unk_26C_4ElemDrawMultDest[4];
    /* 0x29C */ Vec3f fourPoints[4];
    /* 0x2CC */ Vec3f unk_2CC_DrawMultSrc;
    /* 0x2D8 */ Vec3f deltaActorPosition;
    /* 0x2E4 */ Vec3f vectLowestPoint;
    /* 0x2F0 */ Vec3f rotationalAxis;
    /* 0x2FC */ s32 idxLastLowestPoint;
    /* 0x300 */ s16 bHasNewLowestPoint;
    /* 0x302 */ s16 rotationalVelocity;
    /* 0x304 */ s16 rotationalAcceleration;
    /* 0x306 */ UNK_TYPE1 pad306[2];
    /* 0x308 */ s16 framesSinceGrounded;
    /* 0x30A */ s16 unk_30A;
    /* 0x30C */ u8 boardFragments;
} ObjKendoKanban; // size = 0x310

extern const ActorInit Obj_Kendo_Kanban_InitVars;

#endif // Z_OBJ_KENDO_KANBAN_H
