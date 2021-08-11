#include "z_obj_makeoshihiki.h"

#define FLAGS 0x00000010

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

s32 ObjMakeoshihiki_GetPathIndex(ObjMakeoshihiki* this, GlobalContext* globalCtx) {
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
        Actor_SetSwitchFlag(globalCtx, switchFlag2);
    } else {
        Actor_UnsetSwitchFlag(globalCtx, switchFlag2);
    }

    if (pathIndex & 1) {
        Actor_SetSwitchFlag(globalCtx, switchFlag1);
    } else {
        Actor_UnsetSwitchFlag(globalCtx, switchFlag1);
    }
}

void ObjMakeoshihiki_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMakeoshihiki* this = THIS;
    Vec3s* childPoint;
    Path* path;
    s32 pathIndex;

    path = &globalCtx->setupPathList[OBJMAKEOSHIHIKI_GET_PATHLISTINDEX(this)];
    this->pathPoints = Lib_SegmentedToVirtual(path->points);
    this->pathCount = path->count;
    pathIndex = ObjMakeoshihiki_GetPathIndex(this, globalCtx);
    childPoint = &this->pathPoints[pathIndex];
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
                if (Math3D_DistanceSquared(&this->actor.child->world.pos, &pathPointF) < 0.25f) {
                    ObjMakeoshihiki_SetSwitchFlags(this, globalCtx, loopPathIndex);
                    return;
                }
            }
        }
    }
}
