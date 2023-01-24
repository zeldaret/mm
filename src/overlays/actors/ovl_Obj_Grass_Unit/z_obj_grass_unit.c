/*
 * File: z_obj_grass_unit.c
 * Overlay: ovl_Obj_Grass_Unit
 * Description: Spawner for circular patch of grass
 */

#include "z_obj_grass_unit.h"
#include "overlays/actors/ovl_Obj_Grass/z_obj_grass.h"
#include "overlays/actors/ovl_Obj_Grass_Carry/z_obj_grass_carry.h"

#define FLAGS 0x00000000

#define THIS ((ObjGrassUnit*)thisx)

void ObjGrassUnit_Init(Actor* this, PlayState* play2);

ActorInit Obj_Grass_Unit_InitVars = {
    ACTOR_OBJ_GRASS_UNIT,  ACTORCAT_BG,           FLAGS,
    GAMEPLAY_FIELD_KEEP,   sizeof(ObjGrassUnit),  (ActorFunc)ObjGrassUnit_Init,
    (ActorFunc)Actor_Noop, (ActorFunc)Actor_Noop, (ActorFunc)NULL,
};

typedef struct {
    f32 x;
    s16 z;
} Test;

Test D_809AC360[] = {
    { 0.0f, 0x0000 },  { 80.0f, 0x0000 }, { 80.0f, 0x2000 }, { 80.0f, 0x4000 }, { 80.0f, 0x6000 },
    { 80.0f, 0x8000 }, { 80.0f, 0xA000 }, { 80.0f, 0xC000 }, { 80.0f, 0xE000 },
};

Test D_809AC3A8[] = {
    { 40.0f, 0x0666 }, { 40.0f, 0x2CCC }, { 40.0f, 0x5999 }, { 40.0f, 0x8667 }, { 20.0f, 0xC000 }, { 80.0f, 0x1333 },
    { 80.0f, 0x4000 }, { 80.0f, 0x6CCC }, { 80.0f, 0x9334 }, { 80.0f, 0xACCD }, { 80.0f, 0xC667 }, { 60.0f, 0xE000 },
};

typedef struct {
    s32 count;
    Test* positions;
} T_809AC408;

T_809AC408 D_809AC408[2] = { { 9, D_809AC360 }, { 12, D_809AC3A8 }, };

ObjGrass* D_809AC418 = NULL;
ObjGrassCarry* D_809AC41C = NULL;
ObjGrassCarry* D_809AC420 = NULL;
s32 D_809AC424 = 0;

s32 func_809ABDE0(Actor* this, PlayState* play) {

    D_809AC418 = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_GRASS, 0.0f, 0.0f, 0.0f, 0, 0, 0, -1);
    if (D_809AC418 != NULL) {
        D_809AC418->actor.room = this->room;
        return true;
    }
    return false;
}

s32 func_809ABE54(Actor* this, PlayState* play) {

    D_809AC41C = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_GRASS_CARRY, 0.0f, 0.0f, 0.0f, 0, 0, 0, 0);
    if (D_809AC41C != NULL) {
        D_809AC41C->actor.room = this->room;
        return true;
    }
    return false;
}

s32 func_809ABEC4(Actor* this, PlayState* play) {

    D_809AC420 = Actor_Spawn(&play->actorCtx, play, ACTOR_OBJ_GRASS_CARRY, 0.0f, 0.0f, 0.0f, 0, 0, 0, 1);
    if (D_809AC420 != NULL) {
        D_809AC420->actor.room = this->room;
        return true;
    }
    return false;
}

s32 func_809ABF38(PlayState* play, Vec3f* arg1) {
    WaterBox* sp34;
    f32 sp30;
    s32 sp2C;

    if ((WaterBox_GetSurfaceImpl(play, &play->colCtx, arg1->x, arg1->z, &sp30, &sp34, &sp2C) != 0) &&
        (arg1->y < sp30)) {
        return true;
    }
    return false;
}

void ObjGrassUnit_Init(Actor* this, PlayState* play2) {
    PlayState* play = play2;
    ObjGrassStruct1_1* temp_s0;
    ObjGrass* sp94;
    f32 var_fs0;
    f32 tmp;
    s32 var_s4; // i
    Test* temp_s1;
    CollisionPoly* sp80;
    s32 sp7C;
    ObjGrassStruct1* temp_s2_2;
    T_809AC408* temp_s6;
    s8 sp73;

    sp73 = ((s16)this->params >> 8) & 0x1F;
    if ((D_809AC418 == NULL) && (func_809ABDE0(this, play) == 0)) { // obj_grass
        Actor_Kill(this);
        return;
    }
    if ((D_809AC41C == NULL) && (func_809ABE54(this, play) != 0)) { // obj_grass_carry
        D_809AC41C->unk_190 = D_809AC418;
    }
    if ((D_809AC420 == NULL) && (func_809ABEC4(this, play) != 0)) { // obj_grass_carry
        D_809AC420->unk_190 = D_809AC418;
    }
    if ((D_809AC424 == 0) && (D_809AC418 != NULL) && (D_809AC41C != NULL) && (D_809AC420 != NULL)) {
        D_809AC424 = 1;
        D_809AC418->unk_3298[0] = D_809AC41C;
        D_809AC418->unk_3298[1] = D_809AC420;
        D_809AC41C->unk_190 = D_809AC418;
        D_809AC420->unk_190 = D_809AC418;
    }

    sp94 = D_809AC418;
    if (D_809AC418->unk_2944 >= 0x28) {
        Actor_Kill(this);
        return;
    }

    var_fs0 = 0.0f;
    temp_s2_2 = &sp94->unk_144[D_809AC418->unk_2944];
    temp_s2_2->unk_FC = 0;
    temp_s6 = &D_809AC408[(this->params & 1)];

    for (var_s4 = 0; var_s4 < temp_s6->count; var_s4++) {
        temp_s0 = &temp_s2_2->unk_0C[temp_s2_2->unk_FC];
        temp_s1 = &temp_s6->positions[var_s4];

        temp_s0->unk_00.x = (Math_CosS((this->home.rot.y + temp_s1->z)) * temp_s1->x) + this->home.pos.x;
        temp_s0->unk_00.y = this->home.pos.y + 100.0f;
        temp_s0->unk_00.z = (Math_SinS((this->home.rot.y + temp_s1->z)) * temp_s1->x) + this->home.pos.z;

        temp_s0->unk_00.y = BgCheck_EntityRaycastFloor5(&play->colCtx, &sp80, &sp7C, this, &temp_s0->unk_00);
        tmp = temp_s0->unk_00.y - this->home.pos.y;
        if ((fabsf(tmp) < 80.0f) && (temp_s0->unk_00.y > -32000.0f)) {
            temp_s2_2->unk_FC++;
            temp_s0->unk_0C = (s16)(Rand_Next() >> 0x10);
            temp_s0->unk_0E = sp73;
            if (func_809ABF38(play, &temp_s0->unk_00) != 0) {
                temp_s0->unk_0F |= 8;
            }
            var_fs0 += temp_s0->unk_00.y;
        }
    }
    if (temp_s2_2->unk_FC > 0) {
        sp94->unk_2944++;
        temp_s2_2->unk_00.x = this->home.pos.x;
        temp_s2_2->unk_00.y = (var_fs0 / temp_s2_2->unk_FC);
        temp_s2_2->unk_00.z = this->home.pos.z;
    }
    Actor_Kill(this);
}
