/*
 * File: z_obj_mure2.c
 * Overlay: ovl_Obj_Mure2
 * Description: Circle of rocks spawner
 */

#include "z_obj_mure2.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure2*)thisx)

#define OBJMURE2_GET_CHILD_TYPE(thisx) ((thisx)->params & 3)

typedef enum Mure2ChildType {
    OBJMURE2_CHILDTYPE_BUSH_RING,
    OBJMURE2_CHILDTYPE_BUSH_SCATTERED,
    OBJMURE2_CHILDTYPE_ROCK_RING
} Mre2ChildType;

void ObjMure2_Init(Actor* thisx, PlayState* play);
void ObjMure2_Update(Actor* thisx, PlayState* play);

void ObjMure2_SpawnChildren(ObjMure2* this, PlayState* play);
void func_809613C4(ObjMure2* this, PlayState* play);
void ObjMure2_WaitForPlayerInRange(ObjMure2* this, PlayState* play);
void ObjMure2_WaitForPlayerOutOfRange(ObjMure2* this, PlayState* play);
void ObjMure2_KillChildren(ObjMure2* this, PlayState* play);
void func_809613B0(ObjMure2* this);
void ObjMure2_SetupWaitForPlayerInRange(ObjMure2* this);
void ObjMure2_SetupWaitForPlayerOutOfRange(ObjMure2* this);
void ObjMure2_GetChildParams(s16*, ObjMure2*);

void ObjMure2_GetBushCircleSpawnPos(Vec3f pos[12], ObjMure2* this);
void ObjMure2_GetBushScatteredPos(Vec3f pos[12], ObjMure2* this);
void ObjMure2_GetRocksSpawnPos(Vec3f pos[12], ObjMure2* this);

ActorInit Obj_Mure2_InitVars = {
    /**/ ACTOR_OBJ_MURE2,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ObjMure2),
    /**/ ObjMure2_Init,
    /**/ Actor_Noop,
    /**/ ObjMure2_Update,
    /**/ NULL,
};

static f32 sActivationRangesSq[] = {
    SQ(1600.0f), // OBJMURE2_CHILDTYPE_BUSH_RING
    SQ(1600.0f), // OBJMURE2_CHILDTYPE_BUSH_SCATTERED
    SQ(1600.0f), // OBJMURE2_CHILDTYPE_ROCK_RING
};

static f32 sDeactivationRangesSq[] = {
    SQ(1705.0f), // OBJMURE2_CHILDTYPE_BUSH_RING
    SQ(1705.0f), // OBJMURE2_CHILDTYPE_BUSH_SCATTERED
    SQ(1705.0f), // OBJMURE2_CHILDTYPE_ROCK_RING
};

static s16 sChildCounts[] = {
    9,  // OBJMURE2_CHILDTYPE_BUSH_RING
    12, // OBJMURE2_CHILDTYPE_BUSH_SCATTERED
    8,  // OBJMURE2_CHILDTYPE_ROCK_RING
};

static s16 sActorIds[] = {
    ACTOR_EN_KUSA,
    ACTOR_EN_KUSA,
    ACTOR_EN_ISHI,
};
typedef struct Mure2SpawnInfo {
    s16 dist;
    s16 angle;
} Mure2SpawnInfo;

static Mure2SpawnInfo sScatteredBushSpawnInfo[] = {
    { 0x0028, 0x0666 }, { 0x0028, 0x2CCC }, { 0x0028, 0x5999 }, { 0x0028, 0x8666 },
    { 0x0014, 0xC000 }, { 0x0050, 0x1333 }, { 0x0050, 0x4000 }, { 0x0050, 0x6CCC },
    { 0x0050, 0x9333 }, { 0x0050, 0xACCC }, { 0x0050, 0xC666 }, { 0x003C, 0xE000 },
};

typedef void (*ObjMure2SpawnPosFunc)(Vec3f[12], ObjMure2*);
static ObjMure2SpawnPosFunc sSpawnPosFuncs[] = {
    ObjMure2_GetBushCircleSpawnPos, // OBJMURE2_CHILDTYPE_BUSH_RING
    ObjMure2_GetBushScatteredPos,   // OBJMURE2_CHILDTYPE_BUSH_SCATTERED
    ObjMure2_GetRocksSpawnPos,      // OBJMURE2_CHILDTYPE_ROCK_RING
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 2100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

void ObjMure2_GetBushCircleSpawnPos(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    Math_Vec3f_Copy(&pos[0], &this->actor.world.pos);
    for (i = 1; i < sChildCounts[OBJMURE2_GET_CHILD_TYPE(&this->actor)]; i++) {
        Math_Vec3f_Copy(&pos[i], &this->actor.world.pos);
        (pos + i)->x += 80.0f * Math_SinS((i - 1) * 0x2000);
        (pos + i)->z += 80.0f * Math_CosS((i - 1) * 0x2000);
    }
}

void ObjMure2_GetBushScatteredPos(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    for (i = 0; i < sChildCounts[OBJMURE2_GET_CHILD_TYPE(&this->actor)]; i++) {
        Math_Vec3f_Copy(pos + i, &this->actor.world.pos);
        (pos + i)->x += sScatteredBushSpawnInfo[i].dist * Math_CosS(sScatteredBushSpawnInfo[i].angle);
        (pos + i)->z -= sScatteredBushSpawnInfo[i].dist * Math_SinS(sScatteredBushSpawnInfo[i].angle);
    }
}

void ObjMure2_GetRocksSpawnPos(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    for (i = 0; i < sChildCounts[OBJMURE2_GET_CHILD_TYPE(&this->actor)]; i++) {
        Math_Vec3f_Copy(&pos[i], &this->actor.world.pos);
        (pos + i)->x += 80.0f * Math_SinS(i * 0x2000);
        (pos + i)->z += 80.0f * Math_CosS(i * 0x2000);
    }
}

void ObjMure2_GetChildParams(s16* childParams, ObjMure2* this) {
    s32 childType;
    s32 temp_a2;

    childType = OBJMURE2_GET_CHILD_TYPE(&this->actor);
    temp_a2 = (this->actor.params >> 8) & 0x1F;
    if (childType == OBJMURE2_CHILDTYPE_ROCK_RING) {
        *childParams = temp_a2 << 4;
        return;
    }
    *childParams = temp_a2 << 8;
}
void ObjMure2_SpawnChildren(ObjMure2* this, PlayState* play) {
    Vec3f* pos;
    s32 childType;
    Vec3f spawnPos[12];
    s16 childParams;
    s32 i;

    childType = OBJMURE2_GET_CHILD_TYPE(&this->actor);
    sSpawnPosFuncs[childType](spawnPos, this);
    ObjMure2_GetChildParams(&childParams, this);
    for (i = 0; i < sChildCounts[childType]; i++) {
        if (this->actors[i] != NULL) {
            continue;
        }
        if (((this->spawnFlags >> i) & 1) == 0) {
            pos = &spawnPos[i];
            this->actors[i] = Actor_SpawnAsChildAndCutscene(
                &play->actorCtx, play, sActorIds[childType], pos->x, pos->y, pos->z, this->actor.world.rot.x, 0,
                this->actor.world.rot.z, childParams, this->actor.csId, this->actor.halfDaysBits, NULL);
            if (this->actors[i] != NULL) {
                this->actors[i]->room = this->actor.room;
            }
        }
    }
}

void ObjMure2_KillChildren(ObjMure2* this, PlayState* play) {
    s32 i;

    for (i = 0; i < sChildCounts[OBJMURE2_GET_CHILD_TYPE(&this->actor)]; i++) {
        if (((this->spawnFlags >> i) & 1) == 0) {
            if (this->actors[i] != NULL) {
                if (Actor_HasParent(this->actors[i], play)) {
                    this->spawnFlags |= 1 << i;
                } else {
                    Actor_Kill(this->actors[i]);
                }
                this->actors[i] = NULL;
            }
        } else {
            this->actors[i] = NULL;
        }
    }
}

void ObjMure2_ClearChildrenList(ObjMure2* this) {
    s32 i;

    for (i = 0; i < sChildCounts[OBJMURE2_GET_CHILD_TYPE(&this->actor)]; i++) {
        if (this->actors[i] == NULL) {
            continue;
        }
        if ((((this->spawnFlags >> i) & 1) == 0) && (this->actors[i]->update == NULL)) {
            this->spawnFlags |= (1 << i);
            this->actors[i] = NULL;
        }
    }
}

void ObjMure2_Init(Actor* thisx, PlayState* play) {
    ObjMure2* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    if (play->csCtx.state != 0) {
        this->actor.uncullZoneForward += 1200.0f;
    }
    func_809613B0(this);
}

void func_809613B0(ObjMure2* this) {
    this->actionFunc = func_809613C4;
}

void func_809613C4(ObjMure2* this, PlayState* play) {
    ObjMure2_SetupWaitForPlayerInRange(this);
}

void ObjMure2_SetupWaitForPlayerInRange(ObjMure2* this) {
    this->actionFunc = ObjMure2_WaitForPlayerInRange;
}

void ObjMure2_WaitForPlayerInRange(ObjMure2* this, PlayState* play) {
    if (Math3D_XZLengthSquared(this->actor.projectedPos.x, this->actor.projectedPos.z) <
        sActivationRangesSq[OBJMURE2_GET_CHILD_TYPE(&this->actor)] * this->rangeMultiplier) {
        this->actor.flags |= ACTOR_FLAG_10;
        ObjMure2_SpawnChildren(this, play);
        ObjMure2_SetupWaitForPlayerOutOfRange(this);
    }
}

void ObjMure2_SetupWaitForPlayerOutOfRange(ObjMure2* this) {
    this->actionFunc = ObjMure2_WaitForPlayerOutOfRange;
}

void ObjMure2_WaitForPlayerOutOfRange(ObjMure2* this, PlayState* play) {
    ObjMure2_ClearChildrenList(this);

    if ((sDeactivationRangesSq[OBJMURE2_GET_CHILD_TYPE(&this->actor)] * this->rangeMultiplier) <=
        Math3D_XZLengthSquared(this->actor.projectedPos.x, this->actor.projectedPos.z)) {
        this->actor.flags &= ~ACTOR_FLAG_10;
        ObjMure2_KillChildren(this, play);
        ObjMure2_SetupWaitForPlayerInRange(this);
    }
}

void ObjMure2_Update(Actor* thisx, PlayState* play) {
    ObjMure2* this = THIS;

    if (play->csCtx.state == 0) {
        this->rangeMultiplier = 1.0f;
    } else {
        this->rangeMultiplier = 4.0f;
    }
    this->actionFunc(this, play);
}
