/*
 * File: z_bg_open_shutter.c
 * Overlay: ovl_Bg_Open_Shutter
 * Description: Sliding doors in opening dungeon
 */

#include "z_bg_open_shutter.h"
#include "objects/object_open_obj/object_open_obj.h"
#include "z64rumble.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgOpenShutter*)thisx)

void BgOpenShutter_Init(Actor* thisx, PlayState* play);
void BgOpenShutter_Destroy(Actor* thisx, PlayState* play);
void BgOpenShutter_Update(Actor* thisx, PlayState* play);
void BgOpenShutter_Draw(Actor* thisx, PlayState* play);

void func_80ACAD88(BgOpenShutter* this, PlayState* play);
void func_80ACAE5C(BgOpenShutter* this, PlayState* play);
void func_80ACAEF0(BgOpenShutter* this, PlayState* play);

typedef enum {
    /* 0x1 */ BGOPENSHUTTER_DOOR_OPEN = 1,
    /* 0x2 */ BGOPENSHUTTER_DOOR_CLOSED,
} BGOpenShutterDoorState;

const ActorInit Bg_Open_Shutter_InitVars = {
    ACTOR_BG_OPEN_SHUTTER,
    ACTORCAT_DOOR,
    FLAGS,
    OBJECT_OPEN_OBJ,
    sizeof(BgOpenShutter),
    (ActorFunc)BgOpenShutter_Init,
    (ActorFunc)BgOpenShutter_Destroy,
    (ActorFunc)BgOpenShutter_Update,
    (ActorFunc)BgOpenShutter_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 350, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 350, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

f32 func_80ACAB10(PlayState* play, Actor* actor, f32 arg2, f32 arg3, f32 arg4) {
    Player* player = GET_PLAYER(play);
    Vec3f point;
    Vec3f offset;

    point.x = player->actor.world.pos.x;
    point.y = player->actor.world.pos.y + arg2;
    point.z = player->actor.world.pos.z;

    Actor_OffsetOfPointInActorCoords(actor, &offset, &point);
    if ((arg3 < fabsf(offset.x)) || (arg4 < fabsf(offset.y))) {
        return FLT_MAX;
    } else {
        return offset.z;
    }
}

s8 func_80ACABA8(BgOpenShutter* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    f32 temp_fv0;
    s16 temp_v0;

    if (!Player_InCsMode(play) && (this->dyna.actor.xzDistToPlayer < 100.0f)) {
        temp_fv0 = func_80ACAB10(play, &this->dyna.actor, 0.0f, 65.0f, 15.0f);
        if (fabsf(temp_fv0) < 50.0f) {
            temp_v0 = player->actor.shape.rot.y - this->dyna.actor.shape.rot.y;
            if (temp_fv0 > 0.0f) {
                temp_v0 = (0x8000 - temp_v0);
            }
            if (ABS_ALT(temp_v0) < 0x3000) {
                if (temp_fv0 > 1.0f) {
                    return 1;
                }
                if (temp_fv0 < -1.0f) {
                    return -1;
                }
            }
        }
    }
    return 0;
}

void BgOpenShutter_Init(Actor* thisx, PlayState* play) {
    BgOpenShutter* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(play, &this->dyna, &object_open_obj_Colheader_001640);
    this->actionFunc = func_80ACAD88;
}

void BgOpenShutter_Destroy(Actor* thisx, PlayState* play) {
    BgOpenShutter* this = THIS;
    s32 params = BGOPENSHUTTER_GET_A(thisx);

    play->doorCtx.transitionActorList[params].id = -play->doorCtx.transitionActorList[params].id;
    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void func_80ACAD88(BgOpenShutter* this, PlayState* play) {
    s32 quake;

    if (this->unk_15C != 0) {
        Player* player = GET_PLAYER(play);

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_OPEN);
        Camera_ChangeDoorCam(play->cameraPtrs[CAM_ID_MAIN], &this->dyna.actor, player->unk_3BA, 0.0f, 12, 15, 10);
        this->unk_164 = 0;
        this->actionFunc = func_80ACAE5C;
        this->dyna.actor.velocity.y = 0.0f;
    } else {
        Player* player = GET_PLAYER(play);

        quake = func_80ACABA8(this, play);
        if (quake > 0) {
            player->doorType = 2;
            player->doorDirection = quake;
            player->doorActor = &this->dyna.actor;
            func_80122F28(player);
        }
    }
}

void func_80ACAE5C(BgOpenShutter* this, PlayState* play) {
    Math_StepToF(&this->dyna.actor.velocity.y, 15.0f, 3.0f);
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 120.0f,
                     this->dyna.actor.velocity.y)) {
        this->unk_164++;
    }
    if (this->unk_164 >= 10) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_CLOSE);
        this->actionFunc = func_80ACAEF0;
    }
}

void func_80ACAEF0(BgOpenShutter* this, PlayState* play) {
    s32 pad;
    s16 quake;

    Math_StepToF(&this->dyna.actor.velocity.y, 20.0f, 8.0f);
    if (Math_StepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y, this->dyna.actor.velocity.y)) {
        this->dyna.actor.floorHeight = this->dyna.actor.home.pos.y;
        Actor_SpawnFloorDustRing(play, &this->dyna.actor, &this->dyna.actor.world.pos, 60.0f, 10, 8.0f, 500, 10, true);
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_BIGWALL_BOUND);
        quake = Quake_Add(Play_GetCamera(play, CAM_ID_MAIN), 3);
        Quake_SetSpeed(quake, -0x7F18);
        Quake_SetQuakeValues(quake, 2, 0, 0, 0);
        Quake_SetCountdown(quake, 10);
        Rumble_Request(this->dyna.actor.xyzDistToPlayerSq, 180, 20, 100);
        this->unk_15C = 0;
        this->actionFunc = func_80ACAD88;
    }
}

void BgOpenShutter_Update(Actor* thisx, PlayState* play2) {
    BgOpenShutter* this = THIS;
    PlayState* play = play2;
    s32 index;

    if (Cutscene_CheckActorAction(play, 0x7C)) {
        index = Cutscene_GetActorActionIndex(play, 0x7C);
        if (play->csCtx.actorActions[index]->action == BGOPENSHUTTER_DOOR_OPEN) {
            if (this->actionFunc == func_80ACAD88) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_OPEN);
                this->actionFunc = func_80ACAE5C;
                this->dyna.actor.velocity.y = 0.0f;
            }
            this->unk_164 = 0;
        } else if (play->csCtx.actorActions[index]->action == BGOPENSHUTTER_DOOR_CLOSED) {
            if (this->actionFunc == func_80ACAE5C) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SLIDE_DOOR_CLOSE);
                this->actionFunc = func_80ACAEF0;
            }
        }
    }
    this->actionFunc(this, play);
}

void BgOpenShutter_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, object_open_obj_DL_0003E8);
}
