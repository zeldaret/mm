#include "z_door_spiral.h"

#define FLAGS 0x00000010

#define THIS ((DoorSpiral*)thisx)

typedef struct {
    /* 0x00 */ Gfx* spiralDL[2]; // one displaylist for downward spiral, and one for upward
    /* 0x08 */ s32 unk8;         // unused
    /* 0x0C */ u8 unkC;          // unused
    /* 0x0D */ u8 unkD;          // unused
    /* 0x0E */ u8 spiralWidth;
    /* 0x0F */ u8 spiralHeight;
} SpiralInfo;

typedef struct {
    /* 0x00 */ s16 objectBankId;
    /* 0x02 */ u8 spiralType;
} SpiralObjectInfo;

typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 objectType; // index to SpiralObjectInfo
} SpiralSceneInfo;

typedef enum {
    /* 0 */ SPIRAL_NONE,
    /* 1 */ SPIRAL_GENERIC,
    /* 2 */ SPIRAL_WOODFALL_TEMPLE,
    /* 3 */ SPIRAL_WOODFAL_TEMPLE_ALT,
    /* 4 */ SPIRAL_SNOWHEAD_TEMPLE,
    /* 5 */ SPIRAL_STONE_TOWER,
    /* 6 */ SPIRAL_IKANA_CASTLE,
    /* 7 */ SPIRAL_DAMPES_HOUSE
} SpiralType;

void DoorSpiral_Init(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Destroy(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Update(Actor* thisx, GlobalContext* globalCtx);
void DoorSpiral_Draw(Actor* thisx, GlobalContext* globalCtx);

void DoorSpiral_WaitForObject(DoorSpiral* this, GlobalContext* globalCtx);
void DoorSpiral_Wait(DoorSpiral* this, GlobalContext* globalCtx);
void DoorSpiral_PlayerClimb(DoorSpiral* this, GlobalContext* globalCtx);

const ActorInit Door_Spiral_InitVars = {
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

// Parameters for each staircase
static SpiralInfo sSpiralInfo[] = {
    { { NULL, NULL }, 0, 130, 12, 50, 15 }, // blank
    { { 0x050219E0, 0x0501D980 }, 0, 130, 12, 50, 15 },
    { { 0x06004448, 0x060007A8 }, 0, 130, 12, 50, 15 },
    { { 0x060051B8, 0x060014C8 }, 0, 130, 12, 50, 15 },
    { { 0x06009278, 0x06006128 }, 0, 130, 12, 50, 15 },
    { { 0x06013EA8, 0x06012B70 }, 0, 130, 12, 50, 15 },
    { { 0x06000EA0, 0x06000590 }, 0, 130, 12, 50, 15 },
    { { 0x06002110, 0x060012C0 }, 0, 130, 12, 50, 15 },
};

// Defines which object bank a staircase should use, and its index to `sSpiralInfo`
static SpiralObjectInfo sSpiralObjectInfo[] = {
    { GAMEPLAY_KEEP, 0 },    { GAMEPLAY_DANGEON_KEEP, 1 }, { OBJECT_NUMA_OBJ, 2 },      { OBJECT_HAKUGIN_OBJ, 4 },
    { OBJECT_IKANA_OBJ, 5 }, { OBJECT_DANPEI_OBJECT, 7 },  { OBJECT_IKNINSIDE_OBJ, 6 },
};

/**
 * Sets the actor's action function
 */
void DoorSpiral_SetupAction(DoorSpiral* this, DoorSpiralActionFunc* actionFunc) {
    this->actionFunc = actionFunc;
    this->unk14A = 0; // set but never used
}

/**
 * Sets this->spiralType, which is derived from `sSpiralObjectInfo`, and is used as an index to `sSpiralInfo`.
 */
s32 DoorSpiral_SetSpiralType(DoorSpiral* this, GlobalContext* globalCtx) {
    SpiralObjectInfo* doorObjectInfo = &sSpiralObjectInfo[this->objectType];

    this->spiralType = doorObjectInfo->spiralType;

    if ((this->spiralType == SPIRAL_DAMPES_HOUSE) ||
        ((this->spiralType == SPIRAL_WOODFALL_TEMPLE) && globalCtx->roomContext.currRoom.enablePosLights)) {
        if (this->spiralType == SPIRAL_WOODFALL_TEMPLE) {
            this->spiralType = SPIRAL_WOODFAL_TEMPLE_ALT;
        }

        this->actor.flags |= 0x10000000;
    }

    DoorSpiral_SetupAction(this, DoorSpiral_Wait);

    return 0;
}

/**
 * Gets the object type to be used as an index to `sSpiralObjectInfo`.
 * It first checks `sSpiralSceneInfo`, but if the current scene is not found it will fall back to the default spiral.
 */
s32 DoorSpiral_GetObjectType(GlobalContext* globalCtx) {
    // Defines which object type should be used for specific scenes
    static SpiralSceneInfo spiralSceneInfo[] = {
        { SCENE_MITURIN, 2 },     { SCENE_HAKUGIN, 3 },   { SCENE_INISIE_N, 4 }, { SCENE_INISIE_R, 4 },
        { SCENE_DANPEI2TEST, 5 }, { SCENE_IKNINSIDE, 6 }, { SCENE_CASTLE, 6 },
    };
    SpiralSceneInfo* sceneInfo = spiralSceneInfo;
    s32 i;
    s32 type;

    for (i = 0; i < 7; sceneInfo++, i++) {
        if (globalCtx->sceneNum == sceneInfo->sceneNum) {
            break;
        }
    }

    type = i;

    if (type < 7) {
        type = sceneInfo->objectType;
    } else {
        type = (Scene_FindSceneObjectIndex(&globalCtx->sceneContext, 3) >= 0) ? 1 : 0;
    }

    return type;
}

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 1, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 400, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_STOP),
};

void DoorSpiral_Init(Actor* thisx, GlobalContext* globalCtx) {
    DoorSpiral* this = THIS;
    s32 pad;
    s32 transition = (u16)thisx->params >> 10;
    s8 objBankId;

    if (thisx->room != globalCtx->transitionActorList[transition].sides[0].room) {
        Actor_MarkForDeath(thisx);
        return;
    }

    Actor_ProcessInitChain(thisx, &sInitChain);
    this->unk145 = (thisx->params >> 8) & 3; // set but never used
    this->orientation = (thisx->params >> 7) & 1;
    this->objectType = DoorSpiral_GetObjectType(globalCtx);
    objBankId = Scene_FindSceneObjectIndex(&globalCtx->sceneContext, sSpiralObjectInfo[this->objectType].objectBankId);
    this->bankIndex = objBankId;

    if (objBankId < 0) {
        Actor_MarkForDeath(thisx);
        return;
    }

    DoorSpiral_SetupAction(this, DoorSpiral_WaitForObject);
    Actor_SetHeight(thisx, 60.0f);
}

void DoorSpiral_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 transition = (u16)thisx->params >> 10;

    globalCtx->transitionActorList[transition].id *= -1;
}

/**
 * Waits for the required object to be loaded.
 */
void DoorSpiral_WaitForObject(DoorSpiral* this, GlobalContext* globalCtx) {
    if (Scene_IsObjectLoaded(&globalCtx->sceneContext, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        DoorSpiral_SetSpiralType(this, globalCtx);
    }
}

/**
 * Finds the distance between the spiral and the player.
 */
f32 DoorSpiral_GetDistFromPlayer(GlobalContext* globalCtx, DoorSpiral* this, f32 yOffset, f32 spiralWidth,
                                 f32 spiralHeight) {
    ActorPlayer* player = PLAYER;
    Vec3f target;
    Vec3f offset;

    target.x = player->base.world.pos.x;
    target.y = player->base.world.pos.y + yOffset;
    target.z = player->base.world.pos.z;

    Actor_CalcOffsetOrientedToDrawRotation(&this->actor, &offset, &target);

    if ((spiralWidth < fabsf(offset.x)) || (spiralHeight < fabsf(offset.y))) {
        return 3.4028235e38f;
    }

    return offset.z;
}

/**
 * Checks if the player should climb the stairs.
 */
s32 DoorSpiral_PlayerShouldClimb(DoorSpiral* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;

    if (!(func_801233E4(globalCtx))) {
        SpiralInfo* spiralInfo = &sSpiralInfo[this->spiralType];
        f32 dist =
            DoorSpiral_GetDistFromPlayer(globalCtx, this, 0.0f, spiralInfo->spiralWidth, spiralInfo->spiralHeight);

        if (fabsf(dist) < 64.0f) {
            s16 angle = player->base.shape.rot.y - this->actor.shape.rot.y;

            if (dist > 0.0f) {
                angle = 0x8000 - angle;
            }

            if (ABS_ALT(angle) < 0x3000) {
                return (dist >= 0.0f) ? 1.0f : -1.0f;
            }
        }
    }

    return 0;
}

/**
 * Wait for the player to interact with the spiral.
 */
void DoorSpiral_Wait(DoorSpiral* this, GlobalContext* globalCtx) {
    ActorPlayer* player;
    s32 transition;

    if (this->shouldClimb) {
        DoorSpiral_SetupAction(this, DoorSpiral_PlayerClimb);
    } else if (DoorSpiral_PlayerShouldClimb(this, globalCtx)) {
        player = PLAYER;

        player->doorType = 4;
        player->doorDirection = this->orientation;
        player->doorActor = &this->actor;
        transition = (u16)this->actor.params >> 10;
        player->unk37F = ((u16)globalCtx->transitionActorList[transition].params) >> 10;

        func_80122F28(player, globalCtx, &this->actor);
    }
}

/**
 * Player is climbing the stairs.
 */
void DoorSpiral_PlayerClimb(DoorSpiral* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;

    if (!(player->stateFlags1 & 0x20000000)) {
        DoorSpiral_SetupAction(this, DoorSpiral_WaitForObject);
        this->shouldClimb = 0;
    }
}

void DoorSpiral_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorSpiral* this = THIS;
    s32 pad;
    ActorPlayer* player = PLAYER;

    if ((!(player->stateFlags1 & 0x100004C0)) || (this->actionFunc == DoorSpiral_WaitForObject)) {
        this->actionFunc(this, globalCtx);
    }
}

void DoorSpiral_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    DoorSpiral* this = THIS;

    if (this->actor.objBankIndex == this->bankIndex) {
        SpiralInfo* spiralInfo = &sSpiralInfo[this->spiralType];
        Gfx* dList;

        // Set the model to render based on the orientation of the stairs (upward or downward)
        dList = spiralInfo->spiralDL[this->orientation];

        if (dList != NULL) {
            OPEN_DISPS(globalCtx->state.gfxCtx);

            func_8012C28C(globalCtx->state.gfxCtx);

            gSPMatrix(POLY_OPA_DISP++, SysMatrix_AppendStateToPolyOpaDisp(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, spiralInfo->spiralDL[this->orientation]);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
