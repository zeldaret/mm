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

void func_80960CF0(Vec3f*, ObjMure2*);
void func_80960E0C(Vec3f*, ObjMure2*);
void func_80960F0C(Vec3f*, ObjMure2*);

#if 1
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

s16 D_809615A8[] = {
    9,
    12,
    8,
    0,
};

s16 D_809615B0[] = {
    0x0090,
    0x0090,
    0x00B0,
    0x0000,
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

typedef void (*ObjMure2UnkFunc)(Vec3f*, ObjMure2*);
ObjMure2UnkFunc D_809615E8[] = {
    func_80960CF0,
    func_80960E0C,
    func_80960F0C,
};

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809615F4[] = {
    ICHAIN_F32(uncullZoneForward, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 2100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif

extern InitChainEntry D_809615F4[];

void func_80960CF0(Vec3f* arg0, ObjMure2* arg1) {
    s32 i;

    Math_Vec3f_Copy(&arg0[0], &arg1->actor.world.pos);
    for (i = 1; i < D_809615A8[arg1->actor.params & 3]; i++) {
        Math_Vec3f_Copy(&arg0[i], &arg1->actor.world.pos);
        (arg0 + i)->x += 80.0f * Math_SinS((i - 1) * 0x2000);
        (arg0 + i)->z += 80.0f * Math_CosS((i - 1) * 0x2000);
    }
}

void func_80960E0C(Vec3f* arg0, ObjMure2* arg1) {
    s32 i;

    for (i = 0; i < D_809615A8[arg1->actor.params & 3]; i++) {
        Math_Vec3f_Copy(arg0 + i, &arg1->actor.world.pos);
        (arg0 + i)->x += D_809615B8[i].dist * Math_CosS(D_809615B8[i].angle);
        (arg0 + i)->z -= D_809615B8[i].dist * Math_SinS(D_809615B8[i].angle);
    }
}

void func_80960F0C(Vec3f* arg0, ObjMure2* arg1) {
    s32 i;

    for (i = 0; i < D_809615A8[arg1->actor.params & 3]; i++) {
        Math_Vec3f_Copy(&arg0[i], &arg1->actor.world.pos);
        (arg0 + i)->x += 80.0f * Math_SinS(i * 0x2000);
        (arg0 + i)->z += 80.0f * Math_CosS(i * 0x2000);
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
    Vec3f* temp_v0;
    s32 temp_s0;
    Vec3f sp80[12];
    s16 sp7E;
    s32 i;

    temp_s0 = this->actor.params & 3;
    D_809615E8[temp_s0](&sp80, this);
    func_80961018(&sp7E, this);
    for (i = 0; i < D_809615A8[temp_s0]; i++) {
        if (this->unk_148[i] != NULL) {
            continue;
        }
        if (((this->unk_178 >> i) & 1) == 0) {
            temp_v0 = &sp80[i];
            this->unk_148[i] = Actor_SpawnAsChildAndCutscene(
                &play->actorCtx, play, D_809615B0[temp_s0], temp_v0->x, temp_v0->y, temp_v0->z, this->actor.world.rot.x,
                0, this->actor.world.rot.z, sp7E, this->actor.csId, this->actor.halfDaysBits, NULL);
            if (this->unk_148[i] != NULL) {
                this->unk_148[i]->room = this->actor.room;
            }
        }
    }
}

void func_809611BC(ObjMure2* this, PlayState* play) {
    s32 i;

    for (i = 0; i < D_809615A8[this->actor.params & 3]; i++) {
        if (((this->unk_178 >> i) & 1) == 0) {
            if (this->unk_148[i] != NULL) {
                if (Actor_HasParent(this->unk_148[i], play)) {
                    this->unk_178 |= 1 << i;
                } else {
                    Actor_Kill(this->unk_148[i]);
                }
                this->unk_148[i] = NULL;
            }
        } else {
            this->unk_148[i] = NULL;
        }
    }
}

void func_809612BC(ObjMure2* this) {
    s32 i;

    for (i = 0; i < D_809615A8[this->actor.params & 3]; i++) {
        if (this->unk_148[i] == NULL) {
            continue;
        }
        if ((((this->unk_178 >> i) & 1) == 0) && (this->unk_148[i]->update == NULL)) {
            this->unk_178 |= (1 << i);
            this->unk_148[i] = NULL;
        }
    }
}

void ObjMure2_Init(Actor* thisx, PlayState* play) {
    ObjMure2* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_809615F4);
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
    func_809612BC(this);
    if ((D_8096159C[this->actor.params & 3] * this->unk_17C) <= Math3D_XZLengthSquared(this->actor.projectedPos.x, this->actor.projectedPos.z)) {
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