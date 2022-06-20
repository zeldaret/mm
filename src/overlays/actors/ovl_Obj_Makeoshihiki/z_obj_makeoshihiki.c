/*
 * File: z_obj_makeoshihiki.c
 * Overlay: ovl_Obj_Makeoshihiki
 * Description: Pushable Block Switch Flags Handler
 */

#include "z_obj_makeoshihiki.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjMakeoshihiki*)thisx)

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMakeoshihiki_Update(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Makeoshihiki_InitVars = {
    ACTOR_OBJ_MAKEOSHIHIKI,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMakeoshihiki),
    (ActorFunc)ObjMakeoshihiki_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjMakeoshihiki_Update,
    (ActorFunc)NULL,
};

s32 ObjMakeoshihiki_GetChildSpawnPointIndex(ObjMakeoshihiki* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pathIndexOffset1 = Flags_GetSwitch(globalCtx, OBJMAKEOSHIHIKI_GET_SWITCHFLAG_1(this)) ? 1 : 0;
    s32 pathIndexOffset2 = Flags_GetSwitch(globalCtx, OBJMAKEOSHIHIKI_GET_SWITCHFLAG_2(this)) ? 2 : 0;

    return pathIndexOffset1 + pathIndexOffset2;
}

void ObjMakeoshihiki_SetSwitchFlags(ObjMakeoshihiki* this, GlobalContext* globalCtx, s32 pathIndex) {
    s32 pad;
    s32 pad2;
    s32 switchFlag1;
    s32 switchFlag2;

    switchFlag2 = OBJMAKEOSHIHIKI_GET_SWITCHFLAG_2(this);
    switchFlag1 = OBJMAKEOSHIHIKI_GET_SWITCHFLAG_1(this);

    if (pathIndex & 2) {
        Flags_SetSwitch(globalCtx, switchFlag2);
    } else {
        Flags_UnsetSwitch(globalCtx, switchFlag2);
    }

    if (pathIndex & 1) {
        Flags_SetSwitch(globalCtx, switchFlag1);
    } else {
        Flags_UnsetSwitch(globalCtx, switchFlag1);
    }
}

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMakeoshihiki* this = THIS;
    Vec3s* childPoint;
    Path* path;
    s32 childPointIndex;

    path = &globalCtx->setupPathList[OBJMAKEOSHIHIKI_GET_PATHLISTINDEX(this)];
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
    this->pathCount = path->count;
    childPointIndex = ObjMakeoshihiki_GetChildSpawnPointIndex(this, globalCtx);
    childPoint = &this->pathPoints[childPointIndex];
    if (Actor_SpawnAsChild(&globalCtx->actorCtx, &this->actor, globalCtx, ACTOR_OBJ_OSHIHIKI, childPoint->x,
                           childPoint->y, childPoint->z, 0, 0, 0, 0xFFF1) == NULL) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMakeoshihiki_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMakeoshihiki* this = THIS;
    Actor* child;
    s32 loopPathIndex;
    Vec3f pathPointF;

    child = this->actor.child;
    if (child != NULL) {
        if (child->update == NULL) {
            this->actor.child = NULL;
        } else {
            for (loopPathIndex = 0; loopPathIndex < this->pathCount; loopPathIndex++) {
                Math_Vec3s_ToVec3f(&pathPointF, &this->pathPoints[loopPathIndex]);
                if (Math3D_Vec3fDistSq(&this->actor.child->world.pos, &pathPointF) < SQ(0.5f)) {
                    ObjMakeoshihiki_SetSwitchFlags(this, globalCtx, loopPathIndex);
                    return;
                }
            }
        }
    }
}
