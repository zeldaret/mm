/*
 * File: z_door_spiral.c
 * Overlay: ovl_Door_Spiral
 * Description: Staircase
 */

#include "z_door_spiral.h"
#include "objects/gameplay_dangeon_keep/gameplay_dangeon_keep.h"
#include "objects/object_numa_obj/object_numa_obj.h"
#include "objects/object_hakugin_obj/object_hakugin_obj.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"
#include "objects/object_ikninside_obj/object_ikninside_obj.h"
#include "objects/object_danpei_object/object_danpei_object.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((DoorSpiral*)thisx)

void DoorSpiral_Init(Actor* thisx, PlayState* play);
void DoorSpiral_Destroy(Actor* thisx, PlayState* play);
void DoorSpiral_Update(Actor* thisx, PlayState* play);
void DoorSpiral_Draw(Actor* thisx, PlayState* play);

void func_809A2B60(DoorSpiral* this, DoorSpiralActionFunc actionFunc);
s32 func_809A2B70(DoorSpiral* this, PlayState* play);
u8 func_809A2BF8(PlayState* play);
f32 func_809A2E08(PlayState* play, DoorSpiral* this, f32 arg2, f32 arg3, f32 arg4);
void func_809A2DB0(DoorSpiral* this, PlayState* play);
void func_809A2FF8(DoorSpiral* this, PlayState* play);
void func_809A2DB0(DoorSpiral* this, PlayState* play);
void func_809A3098(DoorSpiral* this, PlayState* play);
s32 func_809A2EA0(DoorSpiral* this, PlayState* play);

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

UNK_TYPE D_809A3250[] = {
    0x00000000, 0x00000000, 0x00000000, 0x820C320F, 0x050219E0, 0x0501D980, 0x00000000, 0x820C320F,
    0x06004448, 0x060007A8, 0x00000000, 0x820C320F, 0x060051B8, 0x060014C8, 0x00000000, 0x820C320F,
    0x06009278, 0x06006128, 0x00000000, 0x820C320F, 0x06013EA8, 0x06012B70, 0x00000000, 0x820C320F,
    0x06000EA0, 0x06000590, 0x00000000, 0x820C320F, 0x06002110, 0x060012C0, 0x00000000, 0x820C320F,
};

typedef struct {
    /* 0x0 */ s16 objectId;
    /* 0x2 */ u8 index;
} SpiralObjectInfo; // size = 0x4

SpiralObjectInfo D_809A32D0[] = {
    { GAMEPLAY_KEEP, 0 },    { GAMEPLAY_DANGEON_KEEP, 1 }, { OBJECT_NUMA_OBJ, 2 },      { OBJECT_HAKUGIN_OBJ, 4 },
    { OBJECT_IKANA_OBJ, 5 }, { OBJECT_DANPEI_OBJECT, 7 },  { OBJECT_IKNINSIDE_OBJ, 6 },
};

UNK_TYPE D_809A32EC[] = {
    0x001B0200, 0x00210300, 0x00160400, 0x00180400, 0x00300500, 0x00560600, 0x001D0600,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2B60.s")
void func_809A2B60(DoorSpiral* this, DoorSpiralActionFunc actionFunc) {
    this->actionFunc = actionFunc;
    this->unk14A = 0;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2B70.s")
s32 func_809A2B70(DoorSpiral* this, PlayState* play) {
    SpiralObjectInfo* z = &D_809A32D0[this->unk147];
    this->unk148 = z->index;
    if ((this->unk148 == 7) || ((this->unk148 == 2) && (play->roomCtx.curRoom.enablePosLights != 0))) {
        if (this->unk148 == 2) {
            this->unk148 = 3;
        }
        this->actor.flags |= 0x10000000;
    }
    func_809A2B60(this, func_809A2FF8);
    return 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2BF8.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Init.s")
void DoorSpiral_Init(Actor* thisx, PlayState* play) {
    DoorSpiral* this = THIS;
    s32 transitionActorId = DOORSPIRAL_GET_FC00(thisx);
    s8 temp_v0_2;

    if (this->actor.room != play->doorCtx.transitionActorList[transitionActorId].sides[0].room) {
        Actor_Kill(&this->actor);
    } else {
        Actor_ProcessInitChain(&this->actor, sInitChain);
        this->unk145 = DOORSPIRAL_GET_SOME_FLAG(thisx);
        this->unk146 = DOORSPIRAL_GET_SOME_FLAG_2(thisx);
        this->unk147 = func_809A2BF8(play);
        temp_v0_2 = Object_GetIndex(&play->objectCtx, D_809A32D0[this->unk147].objectId);
        this->objIndex = temp_v0_2;
        if (temp_v0_2 < 0) {
            Actor_Kill(&this->actor);
        } else {
            func_809A2B60(this, func_809A2DB0);
            Actor_SetFocus(&this->actor, 60.0f);
        }
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Destroy.s")
void DoorSpiral_Destroy(Actor* thisx, PlayState* play) {
    s32 transitionActorId = DOORSPIRAL_GET_FC00(thisx);
    play->doorCtx.transitionActorList[transitionActorId].id = -play->doorCtx.transitionActorList[transitionActorId].id;
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2DB0.s")
void func_809A2DB0(DoorSpiral* this, PlayState* play) {
    if (Object_IsLoaded(&play->objectCtx, this->objIndex) != 0) {
        this->actor.objBankIndex = this->objIndex;
        func_809A2B70(this, play);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2E08.s")
f32 func_809A2E08(PlayState* play, DoorSpiral* this, f32 arg2, f32 arg3, f32 arg4) {
    Player* player = GET_PLAYER(play);
    Vec3f point;
    Vec3f offset;

    point.x = player->actor.world.pos.x;
    point.y = player->actor.world.pos.y + arg2;
    point.z = player->actor.world.pos.z;

    Actor_OffsetOfPointInActorCoords(&this->actor, &offset, &point);

    if ((arg3 < fabsf(offset.x)) || (arg4 < fabsf(offset.y))) {
        return FLT_MAX;
    } else {
        return offset.z;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2EA0.s")

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A2FF8.s")
void func_809A2FF8(DoorSpiral* this, PlayState* play) {
    Player* player;
    u32 index;

    if (this->unk144) {
        func_809A2B60(this, func_809A3098);
    } else if (func_809A2EA0(this, play) != 0) {
        player = GET_PLAYER(play);
        player->doorType = PLAYER_DOORTYPE_STAIRCASE;
        player->doorDirection = this->unk146;
        player->doorActor = &this->actor;
        index = DOORSPIRAL_GET_FC00(&this->actor);
        player->doorNext = (play->doorCtx.transitionActorList[index].params >> 0xA);
        func_80122F28(player);
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/func_809A3098.s")
void func_809A3098(DoorSpiral* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & 0x20000000)) {
        func_809A2B60(this, func_809A2DB0);
        this->unk144 = 0;
    }
}

//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Update.s")
void DoorSpiral_Update(Actor* thisx, PlayState* play) {
    DoorSpiral* this = THIS;
    Player* player = GET_PLAYER(play);

    if (!(player->stateFlags1 & 0x100004C0) || (this->actionFunc == func_809A2DB0)) {
        this->actionFunc(this, play);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Door_Spiral/DoorSpiral_Draw.s")
