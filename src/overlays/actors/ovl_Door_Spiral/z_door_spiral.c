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

#define GET_ORIENTATION_PARAM(this) ((((Actor*)(this))->params >> 7) & 0x1)
#define GET_UNK145_PARAM(this) ((((Actor*)(this))->params >> 8) & 0x3)
#define GET_TRANSITION_ID_PARAM(this) ((u16)((Actor*)(this))->params >> 10)

typedef enum {
    /* 0 */ SPIRAL_OVERWORLD, // does not display anything as there is not a DL in GAMEPLAY_KEEP for it
    /* 1 */ SPIRAL_DUNGEON,
    /* 2 */ SPIRAL_WOODFALL_TEMPLE,
    /* 3 */ SPIRAL_WOODFALL_TEMPLE_ALT, // SPIRAL_WOODFALL_TEMPLE but with positional lights enabled?
    /* 4 */ SPIRAL_SNOWHEAD_TEMPLE,
    /* 5 */ SPIRAL_STONE_TOWER,
    /* 6 */ SPIRAL_IKANA_CASTLE,
    /* 7 */ SPIRAL_DAMPES_HOUSE
} SpiralType;

typedef enum {
    /* 0 */ SPIRAL_OBJECT_OVERWORLD,
    /* 1 */ SPIRAL_OBJECT_DUNGEON,
    /* 2 */ SPIRAL_OBJECT_WOODFALL,
    /* 3 */ SPIRAL_OBJECT_SNOWHEAD,
    /* 4 */ SPIRAL_OBJECT_STONE_TOWER,
    /* 5 */ SPIRAL_OBJECT_DAMPES_HOUSE,
    /* 6 */ SPIRAL_OBJECT_IKANA_CASTLE
} SpiralObjectType;

typedef struct {
    /* 0x00 */ Gfx* spiralDL[2]; // one displaylist for downward spiral, and one for upward
    /* 0x08 */ s32 unk8;         // unused
    /* 0x0C */ u8 unkC;          // unused
    /* 0x0D */ u8 unkD;          // unused
    /* 0x0E */ u8 spiralWidth;
    /* 0x0F */ u8 spiralHeight;
} SpiralInfo;

// Maps SpiralObjectType to SpiralType
typedef struct {
    /* 0x00 */ s16 objectBankId;
    /* 0x02 */ u8 spiralType;
} SpiralObjectInfo;

// Maps scenes to SpiralObjectType
typedef struct {
    /* 0x00 */ s16 sceneNum;
    /* 0x02 */ u8 objectType;
} SpiralSceneInfo;

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

// Parameters for each staircase, indexed with SpiralType
static SpiralInfo sSpiralInfo[] = {
    { { NULL, NULL }, 0, 130, 12, 50, 15 },                                                       // SPIRAL_OVERWORLD
    { { gameplay_dangeon_keep_DL_0219E0, gameplay_dangeon_keep_DL_01D980 }, 0, 130, 12, 50, 15 }, // SPIRAL_DUNGEON
    { { object_numa_obj_DL_004448, object_numa_obj_DL_0007A8 }, 0, 130, 12, 50, 15 }, // SPIRAL_WOODFALL_TEMPLE
    { { object_numa_obj_DL_0051B8, object_numa_obj_DL_0014C8 }, 0, 130, 12, 50, 15 }, // SPIRAL_WOODFALL_TEMPLE_ALT
    { { object_hakugin_obj_DL_009278, object_hakugin_obj_DL_006128 }, 0, 130, 12, 50, 15 }, // SPIRAL_SNOWHEAD_TEMPLE
    { { object_ikana_obj_DL_013EA8, object_ikana_obj_DL_012B70 }, 0, 130, 12, 50, 15 },     // SPIRAL_STONE_TOWER
    { { object_ikninside_obj_DL_000EA0, object_ikninside_obj_DL_000590 }, 0, 130, 12, 50, 15 }, // SPIRAL_IKANA_CASTLE
    { { object_danpei_object_DL_002110, object_danpei_object_DL_0012C0 }, 0, 130, 12, 50, 15 }, // SPIRAL_DAMPES_HOUSE
};

// Defines which object bank a staircase should use, and its index to `sSpiralInfo`
static SpiralObjectInfo sSpiralObjectInfo[] = {
    { GAMEPLAY_KEEP, SPIRAL_OVERWORLD },           { GAMEPLAY_DANGEON_KEEP, SPIRAL_DUNGEON },
    { OBJECT_NUMA_OBJ, SPIRAL_WOODFALL_TEMPLE },   { OBJECT_HAKUGIN_OBJ, SPIRAL_SNOWHEAD_TEMPLE },
    { OBJECT_IKANA_OBJ, SPIRAL_STONE_TOWER },      { OBJECT_DANPEI_OBJECT, SPIRAL_DAMPES_HOUSE },
    { OBJECT_IKNINSIDE_OBJ, SPIRAL_IKANA_CASTLE },
};

/**
 * Sets the actor's action function
 */
void DoorSpiral_SetupAction(DoorSpiral* this, DoorSpiralActionFunc actionFunc) {
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
        ((this->spiralType == SPIRAL_WOODFALL_TEMPLE) && globalCtx->roomCtx.currRoom.enablePosLights)) {
        if (this->spiralType == SPIRAL_WOODFALL_TEMPLE) {
            this->spiralType = SPIRAL_WOODFALL_TEMPLE_ALT;
        }

        this->actor.flags |= ACTOR_FLAG_10000000;
    }

    DoorSpiral_SetupAction(this, DoorSpiral_Wait);

    return 0;
}

/**
 * Gets the object type to be used as an index to `sSpiralObjectInfo`.
 * It first checks `sSpiralSceneInfo`, but if the current scene is not found it will fall back to the default spiral
 * (overworld or dungeon).
 */
s32 DoorSpiral_GetObjectType(GlobalContext* globalCtx) {
    // Defines which object type should be used for specific scenes
    static SpiralSceneInfo spiralSceneInfo[] = {
        { SCENE_MITURIN, SPIRAL_OBJECT_WOODFALL },         { SCENE_HAKUGIN, SPIRAL_OBJECT_SNOWHEAD },
        { SCENE_INISIE_N, SPIRAL_OBJECT_STONE_TOWER },     { SCENE_INISIE_R, SPIRAL_OBJECT_STONE_TOWER },
        { SCENE_DANPEI2TEST, SPIRAL_OBJECT_DAMPES_HOUSE }, { SCENE_IKNINSIDE, SPIRAL_OBJECT_IKANA_CASTLE },
        { SCENE_CASTLE, SPIRAL_OBJECT_IKANA_CASTLE },
    };
    SpiralSceneInfo* sceneInfo = spiralSceneInfo;
    s32 i;
    s32 type;

    for (i = 0; i < ARRAY_COUNT(spiralSceneInfo); sceneInfo++, i++) {
        if (globalCtx->sceneNum == sceneInfo->sceneNum) {
            break;
        }
    }

    type = i;

    if (type < ARRAY_COUNT(spiralSceneInfo)) {
        type = sceneInfo->objectType;
    } else {
        // Set the type based on if link is in a dungeon scene, or the overworld
        type = (Object_GetIndex(&globalCtx->objectCtx, GAMEPLAY_DANGEON_KEEP) >= 0) ? SPIRAL_OBJECT_DUNGEON
                                                                                    : SPIRAL_OBJECT_OVERWORLD;
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
    s32 transition = GET_TRANSITION_ID_PARAM(thisx);
    s8 objBankId;

    if (this->actor.room != globalCtx->doorCtx.transitionActorList[transition].sides[0].room) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->unk145 = GET_UNK145_PARAM(thisx); // set but never used
    this->orientation = GET_ORIENTATION_PARAM(thisx);
    this->objectType = DoorSpiral_GetObjectType(globalCtx);
    objBankId = Object_GetIndex(&globalCtx->objectCtx, sSpiralObjectInfo[this->objectType].objectBankId);
    this->bankIndex = objBankId;

    if (objBankId < 0) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    DoorSpiral_SetupAction(this, DoorSpiral_WaitForObject);
    Actor_SetFocus(&this->actor, 60.0f);
}

void DoorSpiral_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    s32 transition = GET_TRANSITION_ID_PARAM(thisx);

    globalCtx->doorCtx.transitionActorList[transition].id *= -1;
}

/**
 * Waits for the required object to be loaded.
 */
void DoorSpiral_WaitForObject(DoorSpiral* this, GlobalContext* globalCtx) {
    if (Object_IsLoaded(&globalCtx->objectCtx, this->bankIndex)) {
        this->actor.objBankIndex = this->bankIndex;
        DoorSpiral_SetSpiralType(this, globalCtx);
    }
}

/**
 * Finds the distance between the stairs and the player.
 */
f32 DoorSpiral_GetDistFromPlayer(GlobalContext* globalCtx, DoorSpiral* this, f32 yOffset, f32 spiralWidth,
                                 f32 spiralHeight) {
    Player* player = GET_PLAYER(globalCtx);
    Vec3f target;
    Vec3f offset;

    target.x = player->actor.world.pos.x;
    target.y = player->actor.world.pos.y + yOffset;
    target.z = player->actor.world.pos.z;

    Actor_OffsetOfPointInActorCoords(&this->actor, &offset, &target);

    if ((spiralWidth < fabsf(offset.x)) || (spiralHeight < fabsf(offset.y))) {
        return FLT_MAX;
    }

    return offset.z;
}

/**
 * Checks if the player should climb the stairs.
 */
s32 DoorSpiral_PlayerShouldClimb(DoorSpiral* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!Player_InCsMode(&globalCtx->state)) {
        SpiralInfo* spiralInfo = &sSpiralInfo[this->spiralType];
        f32 dist =
            DoorSpiral_GetDistFromPlayer(globalCtx, this, 0.0f, spiralInfo->spiralWidth, spiralInfo->spiralHeight);

        if (fabsf(dist) < 64.0f) {
            s16 angle = player->actor.shape.rot.y - this->actor.shape.rot.y;

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
 * Wait for the player to interact with the stairs.
 */
void DoorSpiral_Wait(DoorSpiral* this, GlobalContext* globalCtx) {
    Player* player;
    s32 transition;

    if (this->shouldClimb) {
        DoorSpiral_SetupAction(this, DoorSpiral_PlayerClimb);
    } else if (DoorSpiral_PlayerShouldClimb(this, globalCtx)) {
        player = GET_PLAYER(globalCtx);

        player->doorType = 4;
        player->doorDirection = this->orientation;
        player->doorActor = &this->actor;
        transition = GET_TRANSITION_ID_PARAM(this);
        player->doorNext = ((u16)globalCtx->doorCtx.transitionActorList[transition].params) >> 10;

        func_80122F28(player);
    }
}

/**
 * Player is climbing the stairs.
 */
void DoorSpiral_PlayerClimb(DoorSpiral* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x20000000)) {
        DoorSpiral_SetupAction(this, DoorSpiral_WaitForObject);
        this->shouldClimb = 0;
    }
}

void DoorSpiral_Update(Actor* thisx, GlobalContext* globalCtx) {
    DoorSpiral* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

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

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, spiralInfo->spiralDL[this->orientation]);

            CLOSE_DISPS(globalCtx->state.gfxCtx);
        }
    }
}
