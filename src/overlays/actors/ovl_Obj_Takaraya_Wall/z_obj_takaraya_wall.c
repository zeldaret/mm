/*
 * File: z_obj_takaraya_wall.c
 * Overlay: ovl_Obj_Takaraya_Wall
 * Description: Treasure Chest Shop board manager
 */

#include "z_obj_takaraya_wall.h"
#include "objects/object_takaraya_objects/object_takaraya_objects.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjTakarayaWall*)thisx)

void ObjTakarayaWall_Init(Actor* thisx, PlayState* play);
void ObjTakarayaWall_Destroy(Actor* thisx, PlayState* play);
void ObjTakarayaWall_Update(Actor* thisx, PlayState* play2);
void ObjTakarayaWall_Draw(Actor* thisx, PlayState* play);

void func_80AD9B04(ObjTakarayaWall* this, PlayState* play);

ActorInit Obj_Takaraya_Wall_InitVars = {
    ACTOR_OBJ_TAKARAYA_WALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_TAKARAYA_OBJECTS,
    sizeof(ObjTakarayaWall),
    (ActorFunc)ObjTakarayaWall_Init,
    (ActorFunc)ObjTakarayaWall_Destroy,
    (ActorFunc)ObjTakarayaWall_Update,
    (ActorFunc)ObjTakarayaWall_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 40, 120, 0, { 0, 0, 0 } },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

typedef struct ObjTakarayaWallSpace {
    /* 0 */ u8 row;
    /* 1 */ u8 column;
} ObjTakarayaWallSpace; // size = 0x2

typedef enum ObjTakarayaWallSpaceState {
    /* 0 */ TAKARAYA_WALL_INACTIVE,
    /* 1 */ TAKARAYA_WALL_RISING,
    /* 2 */ TAKARAYA_WALL_FALLING,
} ObjTakarayaWallSpaceState;

s32 sPathBuilderIndex;
ObjTakarayaWallSpace sPathBuilder[88];
s32 D_80ADA508; // Set but never used
s32 sPathBuilderReachedStart;
Vec3f sAudioPositions[11][8];
u8 sSpaceStates[11][8];
f32 sWallHeights[11][8]; // -10.0f means the wall does not raise (the space is open)

s32 ObjTakarayaWall_PosToSpace(Vec3f* pos, s32* row, s32* column) {
    *row = ((s32)pos->x + (14 * 120)) / 120;
    *column = (s32)pos->z / 120;

    if ((*row < 0) || (*row >= ARRAY_COUNT(sWallHeights)) || (*column < 0) ||
        (*column >= ARRAY_COUNT(sWallHeights[0]))) {
        return false;
    }
    return true;
}

/*
 * Checks if the given row and coulmn is valid and is open, i.e does not raise up.
 */
s32 ObjTakarayaWall_SpaceOpen(s32 row, s32 column) {
    if ((row < 0) || (row >= ARRAY_COUNT(sWallHeights)) || (column < 0) || (column >= ARRAY_COUNT(sWallHeights[0])) ||
        (sWallHeights[row][column] == 0.0f)) {
        return false;
    }

    return true;
}

/*
 * Checks nearby spaces if the adjacent space (which depends on the mode) or any of the three adjacent spaces to that
 * space are closed (i.e the wall rises up).
 * The modes check for the adjacent space towards the
 *  0: Back (towards the spawned chest)
 *  1: Right
 *  2: Front
 *  3: Left
 * of the supplied space.
 */
s32 ObjTakarayaWall_NearbySpacesClosed(s32 row, s32 column, s32 mode) {
    s32 row1;
    s32 column1;
    s32 adjacentSpaceRow;
    s32 adjacentSpaceColumn;
    s32 row2;
    s32 column2;
    s32 row3;
    s32 column3;

    if ((mode == 2) || (mode == 0)) {
        if (mode == 0) {
            adjacentSpaceRow = row - 1;
            row3 = row - 2;
        } else {
            adjacentSpaceRow = row + 1;
            row3 = row + 2;
        }
        adjacentSpaceColumn = column;
        column3 = column;
        row1 = adjacentSpaceRow;
        column1 = column + 1;
        row2 = adjacentSpaceRow;
        column2 = column - 1;
    } else {
        if (mode == 1) {
            adjacentSpaceColumn = column - 1;
            column3 = column - 2;
        } else {
            adjacentSpaceColumn = column + 1;
            column3 = column + 2;
        }
        adjacentSpaceRow = row;
        row3 = row;
        row1 = row + 1;
        column1 = adjacentSpaceColumn;
        row2 = row - 1;
        column2 = adjacentSpaceColumn;
    }

    if ((adjacentSpaceRow < 0) || (adjacentSpaceRow >= ARRAY_COUNT(sWallHeights)) || (adjacentSpaceColumn < 0) ||
        (adjacentSpaceColumn >= ARRAY_COUNT(sWallHeights[0])) ||
        (sWallHeights[adjacentSpaceRow][adjacentSpaceColumn] == -10.0f) || ObjTakarayaWall_SpaceOpen(row1, column1) ||
        ObjTakarayaWall_SpaceOpen(row2, column2) || ObjTakarayaWall_SpaceOpen(row3, column3)) {
        return false;
    }

    return true;
}

void ObjTakarayaWall_BuildPath(s32 row, s32 column) {
    s32 closedFlags = 0;
    s32 closedCount = 0;
    s32 mode;
    s32 shift;

    if (ObjTakarayaWall_NearbySpacesClosed(row, column, 0)) {
        closedCount++;
        closedFlags |= 1;
    }

    if (ObjTakarayaWall_NearbySpacesClosed(row, column, 1)) {
        closedCount++;
        closedFlags |= 2;
    }

    if (ObjTakarayaWall_NearbySpacesClosed(row, column, 2)) {
        closedCount++;
        closedFlags |= 4;
    }

    if (ObjTakarayaWall_NearbySpacesClosed(row, column, 3)) {
        closedCount++;
        closedFlags |= 8;
    }

    if (closedCount == 0) {
        sPathBuilderIndex--;
        if (!sPathBuilderReachedStart) {
            D_80ADA508--;
        }
    } else {
        mode = (s32)Rand_ZeroFloat(closedCount) % closedCount;
        if (mode == 0) {
            shift = 0;
            while (!((1 << shift) & closedFlags)) {
                shift++;
            }
        } else if (mode == 1) {
            shift = 3;
            while (!((1 << shift) & closedFlags)) {
                shift--;
            }
        } else if (mode == 2) {
            shift = 0;
            while (!((1 << shift) & closedFlags)) {
                shift++;
            }
            shift++;
            while (!((1 << shift) & closedFlags)) {
                shift++;
            }
        } else {
            shift = 3;
            while (!((1 << shift) & closedFlags)) {
                shift--;
            }
            shift--;
            while (!((1 << shift) & closedFlags)) {
                shift--;
            }
        }

        if (shift == 0) {
            row--;
        } else if (shift == 2) {
            row++;
        } else if (shift == 1) {
            column--;
        } else {
            column++;
        }

        sWallHeights[row][column] = -10.0f;
        sPathBuilder[sPathBuilderIndex].row = row;
        sPathBuilder[sPathBuilderIndex].column = column;
        sPathBuilderIndex++;
        if (!sPathBuilderReachedStart) {
            D_80ADA508++;
            if (row == 10) {
                sPathBuilderReachedStart = true;
            }
        }
    }
}

void ObjTakarayaWall_Init(Actor* thisx, PlayState* play) {
    ObjTakarayaWall* this = THIS;
    Actor* chest;
    s32 column;
    s32 i;
    s32 j;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    for (i = 0; i < ARRAY_COUNT(sWallHeights); i++) {
        for (j = 0; j < ARRAY_COUNT(sWallHeights[0]); j++) {
            sWallHeights[i][j] = 0.0f;
        }
    }

    Collider_InitAndSetCylinder(play, &this->columnCollider, &this->actor, &sCylinderInit);
    Collider_InitAndSetCylinder(play, &this->rowCollider, &this->actor, &sCylinderInit);
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;

    column = (s32)Rand_ZeroFloat(8.0f) % 8;
    chest = Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_EN_BOX, -1635.0f, 0.0f, (column * 120) + 60, 0,
                                          0x4000, this->actor.shape.rot.z, this->actor.params, this->actor.csId,
                                          HALFDAYBIT_ALL, NULL);
    Flags_SetSwitch(play, this->actor.shape.rot.z);
    this->actor.shape.rot.z = 0;

    if (chest != NULL) {
        chest->uncullZoneForward = 2000.0f;
    }

    sWallHeights[0][column] = -10.0f;
    sPathBuilder[sPathBuilderIndex].row = 0;
    sPathBuilder[sPathBuilderIndex].column = column;
    sPathBuilderIndex++;
    D_80ADA508++;

    do {
        ObjTakarayaWall_BuildPath(sPathBuilder[sPathBuilderIndex - 1].row, sPathBuilder[sPathBuilderIndex - 1].column);
    } while (sPathBuilderIndex >= 2);

    for (j = 1; j < ARRAY_COUNT(sWallHeights[0]) - 1; j++) {
        if (sWallHeights[10][j] == -10.0f) {
            break;
        }
    }

    if (j == 7) {
        if (sWallHeights[10][0] == -10.0f) {
            sWallHeights[10][1] = -10.0f;
        } else {
            sWallHeights[10][6] = -10.0f;
        }
    }

    this->actionFunc = func_80AD9B04;
}

void ObjTakarayaWall_Destroy(Actor* thisx, PlayState* play) {
    ObjTakarayaWall* this = THIS;
    s32 i;
    s32 j;

    Collider_DestroyCylinder(play, &this->columnCollider);
    Collider_DestroyCylinder(play, &this->rowCollider);

    for (i = 0; i < ARRAY_COUNT(sAudioPositions); i++) {
        for (j = 0; j < ARRAY_COUNT(sAudioPositions[0]); j++) {
            AudioSfx_StopByPos(&sAudioPositions[i][j]);
        }
    }
}

void func_80AD9B04(ObjTakarayaWall* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    ColliderCylinder* collider;
    s32 playerRowBehind;
    s32 playerRow;
    s32 playerColumn;
    s32 columnColliderActive;
    s32 rowColliderActive;
    s32 playerSpaceXPos;
    s32 playerSpaceZPos;
    s32 i;
    s32 j;
    s32 playerColumnRight;
    s32 playerColumnLeft;
    s32 playerRowInFront;

    rowColliderActive = false;
    columnColliderActive = false;
    playerRowBehind = playerRowInFront = -1;
    playerColumnLeft = playerColumnRight = -1;

    ObjTakarayaWall_PosToSpace(&player->actor.world.pos, &playerRow, &playerColumn);
    playerSpaceXPos = (((s32)player->actor.world.pos.x + (15 * 120)) % 120) - 60;
    playerSpaceZPos = (((s32)player->actor.world.pos.z + (1 * 120)) % 120) - 60;

    if (playerSpaceXPos > 20) {
        playerRowBehind = playerRow + 1;
    } else if (playerSpaceXPos < -20) {
        playerRowInFront = playerRow - 1;
    }

    if (playerSpaceZPos > 20) {
        playerColumnLeft = playerColumn + 1;
    } else if (playerSpaceZPos < -20) {
        playerColumnRight = playerColumn - 1;
    }

    for (i = 0; i < ARRAY_COUNT(sWallHeights); i++) {
        for (j = 0; j < ARRAY_COUNT(sWallHeights[0]); j++) {
            if (sWallHeights[i][j] >= 0.0f) {
                if (((j == playerColumn) && ((i == playerRowInFront) || (i == playerRowBehind))) ||
                    ((i == playerRow) && ((j == playerColumnRight) || (j == playerColumnLeft)))) {
                    if (Math_StepToF(&sWallHeights[i][j], 120.0f, 15.0f)) {
                        sSpaceStates[i][j] = TAKARAYA_WALL_INACTIVE;
                    } else {
                        sSpaceStates[i][j] = TAKARAYA_WALL_RISING;
                    }
                    if (j == playerColumn) {
                        columnColliderActive = true;
                    } else if (i == playerRow) {
                        rowColliderActive = true;
                    }
                } else if ((i != playerRow) || (j != playerColumn)) {
                    Math_SmoothStepToF(&sWallHeights[i][j], 0.0f, 0.2f, 5.0f, 1.0f);
                    sSpaceStates[i][j] = TAKARAYA_WALL_FALLING;
                }
            }
        }
    }

    collider = &this->columnCollider;
    collider->dim.radius = 200;
    if (!columnColliderActive) {
        collider->dim.pos.y = (s32)this->actor.world.pos.y - 240;
    } else {
        collider->dim.pos.y = (s32)this->actor.world.pos.y;
        collider->dim.pos.z = (s32)player->actor.world.pos.z;
        if (playerSpaceXPos > 0) {
            collider->dim.pos.x = ((((s32)player->actor.world.pos.x + (14 * 120)) / 120) * 120) - 1380;
        } else {
            collider->dim.pos.x = ((((s32)player->actor.world.pos.x + (14 * 120)) / 120) * 120) - 1860;
        }
    }

    collider = &this->rowCollider;
    collider->dim.radius = 200;
    if (!rowColliderActive) {
        collider->dim.pos.y = (s32)this->actor.world.pos.y - 240;
    } else {
        collider->dim.pos.y = (s32)this->actor.world.pos.y;
        collider->dim.pos.x = (s32)player->actor.world.pos.x;
        if (playerSpaceZPos > 0) {
            collider->dim.pos.z = (((s32)player->actor.world.pos.z / 120) * 120) + 300;
        } else {
            collider->dim.pos.z = (((s32)player->actor.world.pos.z / 120) * 120) - 180;
        }
    }
}

void ObjTakarayaWall_Update(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    ObjTakarayaWall* this = THIS;

    this->actionFunc(this, play);

    CollisionCheck_SetOC(play, &play->colChkCtx, &this->columnCollider.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->rowCollider.base);
}

void ObjTakarayaWall_Draw(Actor* thisx, PlayState* play) {
    Vec3f audioPos;
    ObjTakarayaWall* this = THIS;
    MtxF* mtx;
    Gfx* gfx;
    s32 i;
    s32 j;

    OPEN_DISPS(play->state.gfxCtx);

    mtx = Matrix_GetCurrent();
    gfx = POLY_OPA_DISP;
    gSPDisplayList(gfx++, gSetupDLs[SETUPDL_25]);
    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 255);

    for (i = 0; i < ARRAY_COUNT(sWallHeights); i++) {
        for (j = 0; j < ARRAY_COUNT(sWallHeights[0]); j++) {
            if (sWallHeights[i][j] > 0.0f) {
                mtx->xw = (i * 120) - 1620;
                mtx->yw = sWallHeights[i][j] + (this->actor.world.pos.y - 120.0f);
                mtx->zw = (j * 120) + 60;

                gSPMatrix(gfx++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

                if (((i + j) % 2) != 0) {
                    gSPDisplayList(gfx++, object_takaraya_objects_DL_000D60);
                } else {
                    gSPDisplayList(gfx++, object_takaraya_objects_DL_000B70);
                }

                if (sSpaceStates[i][j] != TAKARAYA_WALL_INACTIVE) {
                    audioPos.x = mtx->xw;
                    audioPos.y = mtx->yw;
                    audioPos.z = mtx->zw;

                    SkinMatrix_Vec3fMtxFMultXYZ(&play->viewProjectionMtxF, &audioPos, &sAudioPositions[i][j]);

                    if (sSpaceStates[i][j] == TAKARAYA_WALL_RISING) {
                        Audio_PlaySfx_AtPos(&sAudioPositions[i][j], NA_SE_EV_ROCK_CUBE_RISING - SFX_FLAG);
                    } else { // TAKARAYA_WALL_FALLING
                        Audio_PlaySfx_AtPos(&sAudioPositions[i][j], NA_SE_EV_ROCK_CUBE_FALL - SFX_FLAG);
                    }
                }
            }
        }
    }

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(play->state.gfxCtx);
}
