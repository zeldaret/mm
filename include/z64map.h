#ifndef Z64MAP_H
#define Z64MAP_H
#include "ultra64.h"
#include "z64scene.h"

/*
Handles L-minimap and pause screen dungeon minimap system.

z_map_data.c stores MapSpriteInfo and helper functions to "simplify" accessing this data

Two separate Id systems are used to access data

mapId
0x000-0x004 fetches L-minimap data from gameplay_dangeon_keep
0x005-0x039 fetches dungeon minimap data from map_i_static
0x100-0x161 fetches L-minimap data from map_grand_static

mapCompactId
0x000-0x039 fetches dungeon minimap data from map_i_static
0x03A-0x09B fetches L-minimap data from map_grand_static
*/

#define FLOOR_INDEX_MAX 4

/* z_map_data */
#define MAPDATA_MAP_I_MAX 0x3A
#define MAPDATA_MAP_GRAND 0x100
#define MAPDATA_GET_MAP_GRAND_ID_FROM_COMPACT_ID(id) (id + (MAPDATA_MAP_GRAND - MAPDATA_MAP_I_MAX))
#define MAPDATA_GET_MAP_GRAND_ID_FROM_MAP_ID(mapId) (mapId - MAPDATA_MAP_GRAND)

#define MAPDATA_MID_GAMEPLAY_DANGEON_KEEP 0
#define MAPDATA_MID_MAP_GRAND_STATIC 1
#define MAPDATA_MID_MAP_I_STATIC 2

#define MAPDATA_CPID_MAP_GRAND_STATIC 0
#define MAPDATA_CPID_MAP_I_STATIC 1
#define MAPDATA_CPID_2 2

#define MAPDATA_DRAW_0 0
#define MAPDATA_DRAW_1 1
#define MAPDATA_DRAW_2 2
#define MAPDATA_DRAW_3 3

typedef struct {
    u8 texWidth;
    u8 texHeight;
    s16 offsetX;
    s16 offsetY;
    u8 drawType;
    u8 colorIndex;
    s16 scale;
} MapSpriteInfo; // size 0x0A

typedef struct {
    /* 0x00 */ TexturePtr lmapTex; //minimap texture
    /* 0x04 */ u8 width;
    /* 0x05 */ u8 height;
    /* 0x06 */ u8 offsetX;
    /* 0x07 */ u8 offsetY;
    /* 0x08 */ u8 drawType;
    /* 0x09 */ u8 colorIndex;
    /* 0x0A */ s16 scale;
} MapSpriteInfo2; // size 0x0C

/* z_map_disp */

typedef struct {
    /* 0x00 */ MinimapList* minimapList;
    /* 0x04 */ s32 curRoom;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ TexturePtr lMapCurTex; // gameplay cur minimap room
    /* 0x14 */ s32 prevRoom;
    /* 0x18 */ TexturePtr lMapPrevTex;
    /* 0x1C */ s16 unk1C; //same as 0C
    /* 0x1E */ s16 unk1E; //same as 0E
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 swapAnimTimer;
    /* 0x28 */ void* texBuff0;
    /* 0x2C */ void* texBuff1;
    /* 0x30 */ s16 sceneMinX; //scene minBounds.x
    /* 0x32 */ s16 sceneMinZ; //scene minBounds.z
    /* 0x34 */ s16 sceneWidth; //scene boundsWidth.x
    /* 0x36 */ s16 sceneHeight; //scene boundsWidth.z
    /* 0x38 */ s16 sceneMidX; //scene boundsMidpoint.x
    /* 0x3A */ s16 sceneMidZ; //scene boundsMidpoint.z
    /* 0x3C */ s16* unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ s16 unk42;
    /* 0x44 */ s16 unk44;
    /* 0x48 */ s16* unk48;
    /* 0x4C */ s16 unk4C;
    /* 0x50 */ s32 numChests;
    /* 0x54 */ MinimapChest* unk54;
    /* 0x58 */ s16 unk58;
    /* 0x5A */ s16 unk5A;
} T_801BEBB8;

typedef struct {
    /* 0x00 */ s16 unk0; //scene
    /* 0x02 */ s16 unk2;
} T_801BEC5C;

typedef struct {
    /* 0x00 */ s32 unk0[5];
} T_801BEC70;

typedef struct {
    s16 unk0;
    s32 unk4;
    s32 unk8;
} T_801BED24; // size 0x0C

typedef struct {
    /* 0x000 */ s32 rooms;
    /* 0x004 */ s32 unk4[32];
    /* 0x084 */ void* unk84[32];
    /* 0x104 */ void* unk104[32];
    /* 0x184 */ s32 unk184;
} T_801F56B0;

/* z_map_data */
TexturePtr MapData_GetMapTexGameplayDangeonKeep(s32);
s32 MapData_GetMapCompactId(s32);
s32 MapData_MID_GetType(s32);
s32 MapData_CPID_GetSizeOfMapTex(s32);
void MapData_GetDrawType(s32, s32*);
s32 MapData_GetMapColorIndex(s32);
s32 MapDisp_GetSizeOfMapITex(s32);
s32 MapData_GetMapIId(s32);
s32 MapData_GetSizeOfMapGrandTex(s32 mapId);
void MapData_GetMapTexDim(s32 mapId, s32* width, s32* height);
void MapData_GetMapTexOffset(s32 mapId, s32* offsetX, s32* offsetY);
void MapData_GetMapScale(s32 mapId, s32 *scale);
void MapData_CPID_GetTexDim(s32 mapCompactId, s32* width, s32* height);
void MapData_CPID_GetTexOffset(s32 mapCompactId, s32* offsetX, s32* offsetY);
s16 MapData_CPID_GetMapScale(s32 mapCompactId);
#endif
