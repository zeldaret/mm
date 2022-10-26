/*
 * File: z_door_spiral.c
 * Overlay: ovl_Door_Spiral
 * Description: Floor-changing spiral staircase
 */

#include "z_door_spiral.h"
#include "assets/objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "assets/objects/object_numa_obj/object_numa_obj.h"
#include "assets/objects/object_hakugin_obj/object_hakugin_obj.h"
#include "assets/objects/object_ikana_obj/object_ikana_obj.h"
#include "assets/objects/object_danpei_object/object_danpei_object.h"
#include "assets/objects/object_ikninside_obj/object_ikninside_obj.h"

#define FLAGS 0x00000010

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, PlayState* play2);
void DoorSpiral_Destroy(Actor* thisx, PlayState* play2);
void DoorSpiral_Update(Actor* thisx, PlayState* play2);
void DoorSpiral_Draw(Actor* thisx, PlayState* play2);

void func_809A2DB0(DoorSpiral* this, PlayState* play);
void func_809A2FF8(DoorSpiral* this, PlayState* play);
void func_809A3098(DoorSpiral* this, PlayState* play);

ActorInit Door_Spiral_InitVars = {
    ACTOR_DOOR_SPIRAL,
    ACTORCAT_DOOR,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(DoorSpiral),
    (ActorFunc)DoorSpiral_Init,
    (ActorFunc)DoorSpiral_Destroy,
    (ActorFunc)DoorSpiral_Update,
    (ActorFunc)DoorSpiral_Draw,
};

typedef struct {
    Gfx* unk_0[3];
    char unk_C[2];
    u8 unk_E;
    u8 unk_F;
} DoorSpiralUnkStruct1;

DoorSpiralUnkStruct1 D_809A3250[] = {
    { NULL, NULL, NULL, { 0x82, 0x0C }, 50, 15 },
    { gameplay_dangeon_keep_DL_0219E0, gameplay_dangeon_keep_DL_01D980, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_numa_obj_DL_004448, object_numa_obj_DL_0007A8, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_numa_obj_DL_0051B8, object_numa_obj_DL_0014C8, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_hakugin_obj_DL_009278, object_hakugin_obj_DL_006128, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_ikana_obj_DL_013EA8, object_ikana_obj_DL_012B70, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_ikninside_obj_DL_000EA0, object_ikninside_obj_DL_000590, NULL, { 0x82, 0x0C }, 50, 15 },
    { object_danpei_object_DL_002110, object_danpei_object_DL_0012C0, NULL, { 0x82, 0x0C }, 50, 15 },
};

typedef struct {
    s16 id;
    u8 unk_2;
} DoorSpiralUnkStruct2;

DoorSpiralUnkStruct2 D_809A32D0[7] = {
    { GAMEPLAY_KEEP, 0 },    { GAMEPLAY_DANGEON_KEEP, 1 }, { OBJECT_NUMA_OBJ, 2 },      { OBJECT_HAKUGIN_OBJ, 4 },
    { OBJECT_IKANA_OBJ, 5 }, { OBJECT_DANPEI_OBJECT, 7 },  { OBJECT_IKNINSIDE_OBJ, 6 },
};
DoorSpiralUnkStruct2 D_809A32EC[7] = {
    { SCENE_MITURIN, 2 },     { SCENE_HAKUGIN, 3 },   { SCENE_INISIE_N, 4 }, { SCENE_INISIE_R, 4 },
    { SCENE_DANPEI2TEST, 5 }, { SCENE_IKNINSIDE, 6 }, { SCENE_CASTLE, 6 },
};

InitChainEntry D_809A3308[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

void func_809A2B60(DoorSpiral* this, DoorSpiralActionFunc actionFunc) {
    this->actionFunc = actionFunc;
    this->unk_14A = 0;
}

s32 func_809A2B70(DoorSpiral* this, PlayState* play) {
    DoorSpiralUnkStruct2* temp = &D_809A32D0[this->unk_147];

    this->unk_148 = temp->unk_2;
    if ((this->unk_148 == 7) || ((this->unk_148 == 2) && play->roomCtx.curRoom.enablePosLights)) {
        if (this->unk_148 == 2) {
            this->unk_148 = 3;
        }
        this->actor.flags |= ACTOR_FLAG_10000000;
    }
    func_809A2B60(this, func_809A2FF8);
    return 0;
}

s32 func_809A2BF8(PlayState* play) {
    DoorSpiralUnkStruct2* temp = D_809A32EC;
    s32 i;
    s32 var_v1;

    for (i = 0; i < ARRAY_COUNT(D_809A32EC); i++, temp++) {
        if (play->sceneId == temp->id) {
            break;
        }
    }
    if (i < ARRAY_COUNT(D_809A32EC)) {
        var_v1 = temp->unk_2;
    } else if (Object_GetIndex(&play->objectCtx, GAMEPLAY_DANGEON_KEEP) >= 0) {
        var_v1 = 1;
    } else {
        var_v1 = 0;
    }
    return var_v1;
}

void DoorSpiral_Init(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    DoorSpiral* this = (DoorSpiral*)thisx;
    s32 temp1 = DOORSPIRAL_GET_PARAM_FC00(thisx);

    if (thisx->room != play->doorCtx.transitionActorList[temp1].sides[0].room) {
        Actor_Kill(thisx);
        return;
    }
    Actor_ProcessInitChain(thisx, D_809A3308);
    this->unk_145 = DOORSPIRAL_GET_PARAM_0300(thisx);
    this->unk_146 = DOORSPIRAL_GET_PARAM_0080(thisx);
    this->unk_147 = func_809A2BF8(play);
    if ((this->unk_149 = Object_GetIndex(&play->objectCtx, D_809A32D0[this->unk_147].id)) < 0) {
        Actor_Kill(thisx);
        return;
    }
    func_809A2B60(this, func_809A2DB0);
    Actor_SetFocus(thisx, 60.0f);
}

void DoorSpiral_Destroy(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    DoorSpiral* this = (DoorSpiral*)thisx;
    s32 temp1 = DOORSPIRAL_GET_PARAM_FC00(&this->actor);

    play->doorCtx.transitionActorList[temp1].id = -play->doorCtx.transitionActorList[temp1].id;
}

void func_809A2DB0(DoorSpiral* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->unk_149)) {
        this->actor.objBankIndex = this->unk_149;
        func_809A2B70(this, play);
    }
}

f32 func_809A2E08(PlayState* play, DoorSpiral* this, f32 arg2, f32 arg3, f32 arg4) {
    Player* player = GET_PLAYER(play);
    Vec3f sp28;
    Vec3f sp1C;

    sp28.x = player->actor.world.pos.x;
    sp28.y = player->actor.world.pos.y + arg2;
    sp28.z = player->actor.world.pos.z;
    Actor_OffsetOfPointInActorCoords(&this->actor, &sp1C, &sp28);
    if ((arg3 < fabsf(sp1C.x)) || (arg4 < fabsf(sp1C.y))) {
        return FLT_MAX;
    } else {
        return sp1C.z;
    }
}

s32 func_809A2EA0(DoorSpiral* this, PlayState* play) {
    Player* sp24 = GET_PLAYER(play);
    f32 temp_fv0;
    s16 var_v0;

    if (Player_InCsMode(play) == 0) {
        temp_fv0 = func_809A2E08(play, this, 0.0f, D_809A3250[this->unk_148].unk_E, D_809A3250[this->unk_148].unk_F);
        if (fabsf(temp_fv0) < 64.0f) {
            var_v0 = sp24->actor.shape.rot.y - this->actor.shape.rot.y;
            if (temp_fv0 > 0.0f) {
                var_v0 = 0x8000 - var_v0;
            }
            if (ABS_ALT(var_v0) < 0x3000) {
                return (temp_fv0 >= 0.0f) ? 1.0f : -1.0f;
            }
        }
    }
    return 0;
}

void func_809A2FF8(DoorSpiral* this, PlayState* play) {
    if (this->unk_144) {
        func_809A2B60(this, func_809A3098);
    } else if (func_809A2EA0(this, play) != 0) {
        Player* player = GET_PLAYER(play);
        s32 temp1;

        player->doorType = 4;
        player->doorDirection = this->unk_146;
        player->doorActor = &this->actor;
        temp1 = DOORSPIRAL_GET_PARAM_FC00(&this->actor);
        player->doorNext = DOORSPIRAL_GET_PARAM_FC00(&play->doorCtx.transitionActorList[temp1]);
        func_80122F28(player);
    }
}

void func_809A3098(DoorSpiral* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & PLAYER_STATE1_20000000)) {
        func_809A2B60(this, func_809A2DB0);
        this->unk_144 = false;
    }
}

void DoorSpiral_Update(Actor* thisx, PlayState* play) {
    DoorSpiral* this = (DoorSpiral*)thisx;
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & (PLAYER_STATE1_10000000 | PLAYER_STATE1_400 | PLAYER_STATE1_80 | PLAYER_STATE1_40)) ||
        (this->actionFunc == func_809A2DB0)) {
        this->actionFunc(this, play);
    }
}

void DoorSpiral_Draw(Actor* thisx, PlayState* play) {
    s32 pad; // can be playstate recast
    DoorSpiral* this = (DoorSpiral*)thisx;

    if (this->actor.objBankIndex == this->unk_149) {
        DoorSpiralUnkStruct1* sp2C = &D_809A3250[this->unk_148];
        Gfx* sp28 = sp2C->unk_0[this->unk_146];

        if (sp28 != NULL) {
            OPEN_DISPS(play->state.gfxCtx);

            func_8012C28C(play->state.gfxCtx);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, sp2C->unk_0[this->unk_146]);

            CLOSE_DISPS(play->state.gfxCtx);
        }
    }
}
