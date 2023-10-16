#ifndef Z64MAP_H
#define Z64MAP_H
#include "ultra64.h"
#include "z64scene.h"

struct PlayState;

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
    /* 0x0 */ u8 texWidth;
    /* 0x1 */ u8 texHeight;
    /* 0x2 */ s16 offsetX;
    /* 0x4 */ s16 offsetY;
    /* 0x6 */ u8 drawType;
    /* 0x7 */ u8 colorIndex;
    /* 0x8 */ s16 scale;
} MapSpriteInfo; // size = 0xA

typedef struct {
    /* 0x0 */ TexturePtr lmapTex; //minimap texture
    /* 0x4 */ u8 width;
    /* 0x5 */ u8 height;
    /* 0x6 */ u8 offsetX;
    /* 0x7 */ u8 offsetY;
    /* 0x8 */ u8 drawType;
    /* 0x9 */ u8 colorIndex;
    /* 0xA */ s16 scale;
} MapSpriteInfo2; // size = 0xC

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
} struct_801BEBB8; // size = 0x5C

typedef struct {
    /* 0x0 */ s16 unk0; //scene
    /* 0x2 */ s16 unk2;
} struct_801BEC5C; // size = 0x4

typedef struct {
    /* 0x00 */ s32 unk0[5];
} struct_801BEC70; // size = 0x14

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x4 */ s32 unk4;
    /* 0x8 */ s32 unk8;
} struct_801BED24; // size = 0xC

typedef struct {
    /* 0x000 */ s32 rooms;
    /* 0x004 */ s32 unk4[32];
    /* 0x084 */ void* unk84[32];
    /* 0x104 */ void* unk104[32];
    /* 0x184 */ s32 unk184;
} struct_801F56B0; // size = 0x188

/* z_map_disp */
void func_80102EB4(u32 param_1);
void func_80102ED0(u32 param_1);
s32 func_80102EF0(struct PlayState* play);
void MapDisp_Init(struct PlayState* play);
s32 func_80105294(void);
s16 func_80105318(void);
void func_8010549C(struct PlayState* play, void* segmentAddress);
void func_8010565C(struct PlayState* play, s32 num, void* segmentAddress);
void func_80105818(struct PlayState* play, s32 num, TransitionActorEntry* transitionActorList);
void MapDisp_Destroy(struct PlayState* play);
void func_80105B34(struct PlayState* play);
void MapDisp_SwapRooms(s16 nextRoom);
s32 func_80106530(struct PlayState* play);
void func_80106644(struct PlayState* play, s32 x, s32 z, s32 rot);
void* func_801068FC(struct PlayState* play, void* heap);
void func_80108AF8(struct PlayState* play);
s32 func_801090B0(s32 arg0);
s32 func_80109124(s16 arg0);
void func_801091F0(struct PlayState* play);

/* z_map_data */
void MapData_GetMapColor(s32 colorIndex, Color_RGBA8* color);
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

/* z_map_exp */
s32 Map_GetDungeonOrBossAreaIndex(struct PlayState* play);
s32 Map_IsInDungeonOrBossArea(struct PlayState* play);
s32 func_8010A0A4(struct PlayState* play);
s32 Map_IsInBossArea(struct PlayState* play);
void Minimap_SavePlayerRoomInitInfo(struct PlayState* play);
void Map_InitRoomData(struct PlayState* play, s16 room);
void Map_Destroy(struct PlayState* play);
void Map_Init(struct PlayState* play);
void Minimap_Draw(struct PlayState* play);
void Map_Update(struct PlayState* play);

#endif
