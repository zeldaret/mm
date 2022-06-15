/*
 * File: z_obj_mure.c
 * Overlay: ovl_Obj_Mure
 * Description: Bugs, Insects, Butterfly spawner and behavior
 */

#include "z_obj_mure.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure*)thisx)

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx);

void ObjMure_InitialAction(ObjMure* this, GlobalContext* globalCtx);
void ObjMure_CulledState(ObjMure* this, GlobalContext* globalCtx);
void ObjMure_ActiveState(ObjMure* this, GlobalContext* globalCtx);
void ObjMure_KillActors(ObjMure* this, GlobalContext* globalCtx);
void ObjMure_CheckChildren(ObjMure* this, GlobalContext* globalCtx);

const ActorInit Obj_Mure_InitVars = {
    ACTOR_OBJ_MURE,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMure),
    (ActorFunc)ObjMure_Init,
    (ActorFunc)ObjMure_Destroy,
    (ActorFunc)ObjMure_Update,
    (ActorFunc)NULL,
};

static f32 sZClip[] = {
    1600.0f, 1600.0f, 1000.0f, 1000.0f, 1000.0f,
};

static s32 sMaxChildSpawns[] = {
    12,
    9,
    8,
    0,
};

static s16 sSpawnActorIds[] = {
    ACTOR_EN_KUSA, 0, ACTOR_EN_FISH, ACTOR_EN_INSECT, ACTOR_EN_BUTTE,
};

static s16 sSpawnParams[] = {
    0, 2, -1, 0, -1,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1200, ICHAIN_STOP),
};

typedef enum {
    /* 0 */ OBJMURE_TYPE_GRASS,
    /* 1 */ OBJMURE_TYPE_UNDEFINED,
    /* 2 */ OBJMURE_TYPE_FISH,
    /* 3 */ OBJMURE_TYPE_BUGS,
    /* 4 */ OBJMURE_TYPE_BUTTERFLY,
    /* 5 */ OBJMURE_TYPE_MAX
} ObjMureType;

typedef enum {
    /* 0 */ OBJMURE_CHILD_STATE_0,
    /* 1 */ OBJMURE_CHILD_STATE_DEAD,
    /* 2 */ OBJMURE_CHILD_STATE_2
} ObjMureChildState;

s32 func_808D78D0(ObjMure* this, GlobalContext* globalCtx) {
    if (this->type == OBJMURE_TYPE_FISH || this->type == OBJMURE_TYPE_BUGS || this->type == OBJMURE_TYPE_BUTTERFLY) {
        Actor_ProcessInitChain(&this->actor, sInitChain);
    } else {
        return false;
    }
    return true;
}

s32 func_808D7928(ObjMure* this, GlobalContext* globalCtx) {
    if (!func_808D78D0(this, globalCtx)) {
        return false;
    }
    return true;
}

void ObjMure_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure* this = THIS;

    this->chNum = OBJ_MURE_GET_CHNUM(this->actor.params);
    this->ptn = OBJ_MURE_GET_PTN(this->actor.params);
    this->svNum = OBJ_MURE_GET_SVNUM(this->actor.params);
    this->type = OBJ_MURE_GET_TYPE(this->actor.params);
    if (this->ptn >= 4) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (this->type >= OBJMURE_TYPE_MAX) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (!func_808D7928(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc = ObjMure_InitialAction;
}

void ObjMure_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

s32 ObjMure_GetMaxChildSpawns(ObjMure* this) {
    if (this->chNum == 0) {
        return sMaxChildSpawns[this->ptn];
    }
    return this->chNum;
}

void ObjMure_GetSpawnPos(Vec3f* outPos, Vec3f* inPos, s32 ptn, s32 idx) {
    *outPos = *inPos;
}

void ObjMure_SpawnActors0(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure* this = THIS;
    s32 i;
    Vec3f pos;
    s32 pad;
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);

    for (i = 0; i < maxChildren; i++) {
        switch (this->childrenStates[i]) {
            case OBJMURE_CHILD_STATE_DEAD:
                break;
            case OBJMURE_CHILD_STATE_2:
                ObjMure_GetSpawnPos(&pos, &this->actor.world.pos, this->ptn, i);
                this->children[i] = Actor_SpawnAsChildAndCutscene(
                    &globalCtx->actorCtx, globalCtx, sSpawnActorIds[this->type], pos.x, pos.y, pos.z,
                    this->actor.world.rot.x, this->actor.world.rot.y, this->actor.world.rot.z, sSpawnParams[this->type],
                    this->actor.cutscene, this->actor.unk20, NULL);
                if (this->children[i] != NULL) {
                    if (this->type == 0x90) {
                        ((ObjMureChild*)this->children[i])->unk_197 = 1;
                    }
                    this->children[i]->room = this->actor.room;
                }
                break;
            default:
                ObjMure_GetSpawnPos(&pos, &this->actor.world.pos, this->ptn, i);
                this->children[i] = Actor_SpawnAsChildAndCutscene(
                    &globalCtx->actorCtx, globalCtx, sSpawnActorIds[this->type], pos.x, pos.y, pos.z,
                    this->actor.world.rot.x, this->actor.world.rot.y, this->actor.world.rot.z, sSpawnParams[this->type],
                    this->actor.cutscene, this->actor.unk20, NULL);
                if (this->children[i] != NULL) {
                    this->children[i]->room = this->actor.room;
                }
                break;
        }
    }
}

void ObjMure_SpawnActors1(ObjMure* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    Actor* actor = &this->actor;
    Vec3f spawnPos;
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        ObjMure_GetSpawnPos(&spawnPos, &actor->world.pos, this->ptn, i);
        this->children[i] = Actor_SpawnAsChildAndCutscene(
            &globalCtx2->actorCtx, globalCtx, sSpawnActorIds[this->type], spawnPos.x, spawnPos.y, spawnPos.z,
            actor->world.rot.x, actor->world.rot.y, actor->world.rot.z,
            (this->type == OBJMURE_TYPE_BUTTERFLY && i == 0) ? 1 : sSpawnParams[this->type], this->actor.cutscene,
            this->actor.unk20, NULL);
        if (this->children[i] != NULL) {
            this->childrenStates[i] = OBJMURE_CHILD_STATE_0;
            this->children[i]->room = actor->room;
        } else {
            this->childrenStates[i] = OBJMURE_CHILD_STATE_DEAD;
        }
    }
}

void ObjMure_SpawnActors(ObjMure* this, GlobalContext* globalCtx) {
    switch (this->svNum) {
        case 0:
            ObjMure_SpawnActors0(&this->actor, globalCtx);
            break;
        case 1:
            ObjMure_SpawnActors1(this, globalCtx);
            break;
    }
}

void ObjMure_KillActorsImpl(ObjMure* this, GlobalContext* globalCtx) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        switch (this->childrenStates[i]) {
            case OBJMURE_CHILD_STATE_DEAD:
                this->children[i] = NULL;
                break;
            case OBJMURE_CHILD_STATE_2:
                if (this->children[i] != NULL) {
                    Actor_MarkForDeath(this->children[i]);
                    this->children[i] = NULL;
                }
                break;
            default:
                if (this->children[i] != NULL) {
                    if (Actor_HasParent(this->children[i], globalCtx)) {
                        this->children[i] = NULL;
                    } else {
                        Actor_MarkForDeath(this->children[i]);
                        this->children[i] = NULL;
                    }
                }
                break;
        }
    }
}

void ObjMure_KillActors(ObjMure* this, GlobalContext* globalCtx) {
    ObjMure_KillActorsImpl(this, globalCtx);
}

void ObjMure_CheckChildren(ObjMure* this, GlobalContext* globalCtx) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            if (this->childrenStates[i] == OBJMURE_CHILD_STATE_0) {
                if (this->children[i]->update != NULL) {
                    if ((this->type == 0x90) && (((ObjMureChild*)this->children[i])->unk_197 != 0)) {
                        this->childrenStates[i] = OBJMURE_CHILD_STATE_2;
                    }
                } else {
                    this->childrenStates[i] = OBJMURE_CHILD_STATE_DEAD;
                    this->children[i] = NULL;
                }
            } else if (this->childrenStates[i] == OBJMURE_CHILD_STATE_2 && this->children[i]->update == NULL) {
                this->childrenStates[i] = OBJMURE_CHILD_STATE_DEAD;
                this->children[i] = NULL;
            }
        }
    }
}

void ObjMure_InitialAction(ObjMure* this, GlobalContext* globalCtx) {
    this->actionFunc = ObjMure_CulledState;
}

void ObjMure_CulledState(ObjMure* this, GlobalContext* globalCtx) {
    if (fabsf(this->actor.projectedPos.z) < sZClip[this->type]) {
        this->actionFunc = ObjMure_ActiveState;
        this->actor.flags |= ACTOR_FLAG_10;
        ObjMure_SpawnActors(this, globalCtx);
    }
}

void ObjMure_SetFollowTargets(ObjMure* this, f32 randMax) {
    s32 index;
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;

    for (i = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            this->children[i]->child = NULL;
            if (Rand_ZeroOne() <= randMax) {
                index = Rand_ZeroOne() * (maxChildren - 0.5f);
                if (i != index) {
                    this->children[i]->child = this->children[index];
                }
            }
        }
    }
}

/**
 * Selects a child that will follow after the player
 * `idx1` is the index + 1 of the child that will follow the player. If `idx1` is zero, no actor will follow the player
 */
void ObjMure_SetChildToFollowPlayer(ObjMure* this, s32 idx1) {
    s32 maxChildren = ObjMure_GetMaxChildSpawns(this);
    s32 i;
    s32 i2;
    s32 j;

    for (i = 0, i2 = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            if (i2 < idx1) {
                i2++;
                this->children[i]->child = this->children[i];
                for (j = 0; j < maxChildren; j++) {
                    if (i != j && this->children[j]->child == this->children[i]) {
                        this->children[j]->child = NULL;
                    }
                }
            } else if (this->children[i]->child == this->children[i]) {
                this->children[i]->child = NULL;
            }
        }
    }
}

// Fish, Bugs
void ObjMure_GroupBehavior0(ObjMure* this, GlobalContext* globalCtx) {
    if (this->unk_19C <= 0) {
        if (this->unk_19E) {
            this->unk_19E = false;
            ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.5f) + 0.1f);
            if (this->actor.xzDistToPlayer < 60.0f) {
                this->unk_19C = (s32)(Rand_ZeroOne() * 5.5f) + 4;
            } else {
                this->unk_19C = (s32)(Rand_ZeroOne() * 40.5f) + 4;
            }
        } else {
            this->unk_19E = true;
            if (this->actor.xzDistToPlayer < 60.0f) {
                this->unk_19C = (s32)(Rand_ZeroOne() * 10.5f) + 4;
                ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.2f) + 0.8f);
            } else {
                this->unk_19C = (s32)(Rand_ZeroOne() * 10.5f) + 4;
                ObjMure_SetFollowTargets(this, (Rand_ZeroOne() * 0.2f) + 0.6f);
            }
        }
    }
    if (this->actor.xzDistToPlayer < 120.0f) {
        this->unk_1A0++;
    } else {
        this->unk_1A0 = 0;
    }
    if (this->unk_1A0 >= 80) {
        ObjMure_SetChildToFollowPlayer(this, 1);
    } else {
        ObjMure_SetChildToFollowPlayer(this, 0);
    }
}

// Butterflies
void ObjMure_GroupBehavior1(ObjMure* this, GlobalContext* globalCtx) {
    s32 maxChildren;
    s32 i;

    if (this->unk_19C <= 0) {
        if (this->unk_19E) {
            this->unk_19E = false;
            ObjMure_SetFollowTargets(this, Rand_ZeroOne() * 0.2f);
            if (this->actor.xzDistToPlayer < 60.0f) {
                this->unk_19C = (s32)(Rand_ZeroOne() * 5.5f) + 4;
            } else {
                this->unk_19C = (s32)(Rand_ZeroOne() * 40.5f) + 4;
            }
        } else {
            this->unk_19E = true;
            ObjMure_SetFollowTargets(this, Rand_ZeroOne() * 0.7f);
            this->unk_19C = (s32)(Rand_ZeroOne() * 10.5f) + 4;
        }
    }

    maxChildren = ObjMure_GetMaxChildSpawns(this);
    for (i = 0; i < maxChildren; i++) {
        if (this->children[i] != NULL) {
            if (this->children[i]->child != NULL && this->children[i]->child->update == NULL) {
                this->children[i]->child = NULL;
            }
        }
    }
}

static ObjMureActionFunc sTypeGroupBehaviorFunc[] = {
    NULL, NULL, ObjMure_GroupBehavior0, ObjMure_GroupBehavior0, ObjMure_GroupBehavior1,
};

void ObjMure_ActiveState(ObjMure* this, GlobalContext* globalCtx) {
    ObjMure_CheckChildren(this, globalCtx);
    if (sZClip[this->type] + 40.0f <= fabsf(this->actor.projectedPos.z)) {
        this->actionFunc = ObjMure_CulledState;
        this->actor.flags &= ~ACTOR_FLAG_10;
        ObjMure_KillActors(this, globalCtx);
    } else if (sTypeGroupBehaviorFunc[this->type] != NULL) {
        sTypeGroupBehaviorFunc[this->type](this, globalCtx);
    }
}

void ObjMure_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMure* this = THIS;

    if (this->unk_19C > 0) {
        this->unk_19C--;
    }
    this->actionFunc(this, globalCtx);
}
