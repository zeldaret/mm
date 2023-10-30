/*
 * File: z_obj_mure2.c
 * Overlay: ovl_Obj_Mure2
 * Description: Circle of rocks spawner
 */

#include "z_obj_mure2.h"

#define FLAGS 0x00000000

#define THIS ((ObjMure2*)thisx)

void ObjMure2_Init(Actor* thisx, PlayState* play);
void ObjMure2_Update(Actor* thisx, PlayState* play);

void func_8096104C(ObjMure2* this, PlayState* play);
void func_809613C4(ObjMure2* this, PlayState* play);
void func_809613FC(ObjMure2* this, PlayState* play);
void func_80961490(ObjMure2* this, PlayState* play);
void func_809611BC(ObjMure2* this, PlayState* play);
void func_809613B0(ObjMure2* this);
void func_809613E8(ObjMure2* this);
void func_8096147C(ObjMure2* this);
void func_80961018(s16*, ObjMure2*);

void func_80960CF0(Vec3f pos[12], ObjMure2* this);
void func_80960E0C(Vec3f pos[12], ObjMure2* this);
void func_80960F0C(Vec3f pos[12], ObjMure2* this);

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

f32 D_80961590[] = {
    2560000.0,
    2560000.0,
    2560000.0,
};

f32 D_8096159C[] = {
    2907025.0,
    2907025.0,
    2907025.0,
};

static s16 sChildCounts[] = {
    9,
    12,
    8,
    0,
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

Mure2SpawnInfo D_809615B8[] = {
    { 0x0028, 0x0666 }, { 0x0028, 0x2CCC }, { 0x0028, 0x5999 }, { 0x0028, 0x8666 },
    { 0x0014, 0xC000 }, { 0x0050, 0x1333 }, { 0x0050, 0x4000 }, { 0x0050, 0x6CCC },
    { 0x0050, 0x9333 }, { 0x0050, 0xACCC }, { 0x0050, 0xC666 }, { 0x003C, 0xE000 },
};

typedef void (*ObjMure2SpawnPosFunc)(Vec3f[12], ObjMure2*);
static ObjMure2SpawnPosFunc sSpawnPosFuncs[] = {
    func_80960CF0,
    func_80960E0C,
    func_80960F0C,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 2100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

void func_80960CF0(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    Math_Vec3f_Copy(&pos[0], &this->actor.world.pos);
    for (i = 1; i < sChildCounts[this->actor.params & 3]; i++) {
        Math_Vec3f_Copy(&pos[i], &this->actor.world.pos);
        (pos + i)->x += 80.0f * Math_SinS((i - 1) * 0x2000);
        (pos + i)->z += 80.0f * Math_CosS((i - 1) * 0x2000);
    }
}

void func_80960E0C(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    for (i = 0; i < sChildCounts[this->actor.params & 3]; i++) {
        Math_Vec3f_Copy(pos + i, &this->actor.world.pos);
        (pos + i)->x += D_809615B8[i].dist * Math_CosS(D_809615B8[i].angle);
        (pos + i)->z -= D_809615B8[i].dist * Math_SinS(D_809615B8[i].angle);
    }
}

void func_80960F0C(Vec3f pos[12], ObjMure2* this) {
    s32 i;

    for (i = 0; i < sChildCounts[this->actor.params & 3]; i++) {
        Math_Vec3f_Copy(&pos[i], &this->actor.world.pos);
        (pos + i)->x += 80.0f * Math_SinS(i * 0x2000);
        (pos + i)->z += 80.0f * Math_CosS(i * 0x2000);
    }
}

void func_80961018(s16* arg0, ObjMure2* this) {
    s32 temp_v1;
    s32 temp_a2;

    temp_v1 = this->actor.params & 3;
    temp_a2 = (this->actor.params >> 8) & 0x1F;
    if (temp_v1 == 2) {
        *arg0 = temp_a2 << 4;
        return;
    }
    *arg0 = temp_a2 << 8;
}
void func_8096104C(ObjMure2* this, PlayState* play) {
    Vec3f* pos;
    s32 temp_s0;
    Vec3f spawnPos[12];
    s16 sp7E;
    s32 i;

    temp_s0 = this->actor.params & 3;
    sSpawnPosFuncs[temp_s0](spawnPos, this);
    func_80961018(&sp7E, this);
    for (i = 0; i < sChildCounts[temp_s0]; i++) {
        if (this->actors[i] != NULL) {
            continue;
        }
        if (((this->spawnFlags >> i) & 1) == 0) {
            pos = &spawnPos[i];
            this->actors[i] = Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, sActorIds[temp_s0], pos->x, pos->y,
                                                            pos->z, this->actor.world.rot.x, 0, this->actor.world.rot.z,
                                                            sp7E, this->actor.csId, this->actor.halfDaysBits, NULL);
            if (this->actors[i] != NULL) {
                this->actors[i]->room = this->actor.room;
            }
        }
    }
}

void func_809611BC(ObjMure2* this, PlayState* play) {
    s32 i;

    for (i = 0; i < sChildCounts[this->actor.params & 3]; i++) {
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

    for (i = 0; i < sChildCounts[this->actor.params & 3]; i++) {
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
    func_809613E8(this);
}

void func_809613E8(ObjMure2* this) {
    this->actionFunc = func_809613FC;
}

void func_809613FC(ObjMure2* this, PlayState* play) {
    if (Math3D_XZLengthSquared(this->actor.projectedPos.x, this->actor.projectedPos.z) <
        D_80961590[this->actor.params & 3] * this->unk_17C) {
        this->actor.flags |= 0x10;
        func_8096104C(this, play);
        func_8096147C(this);
    }
}

void func_8096147C(ObjMure2* this) {
    this->actionFunc = func_80961490;
}

void func_80961490(ObjMure2* this, PlayState* play) {
    ObjMure2_ClearChildrenList(this);
    if ((D_8096159C[this->actor.params & 3] * this->unk_17C) <=
        Math3D_XZLengthSquared(this->actor.projectedPos.x, this->actor.projectedPos.z)) {
        this->actor.flags &= ~0x10;
        func_809611BC(this, play);
        func_809613E8(this);
    }
}

void ObjMure2_Update(Actor* thisx, PlayState* play) {
    ObjMure2* this = THIS;

    if (play->csCtx.state == 0) {
        this->unk_17C = 1.0f;
    } else {
        this->unk_17C = 4.0f;
    }
    this->actionFunc(this, play);
}