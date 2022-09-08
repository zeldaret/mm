#include "global.h"
#include "z64map.h"

static Color_RGBA8 D_801BED40[3] = {
    { 255, 255, 255, 255 },
    { 0, 255, 255, 160 },
    { 100, 255, 255, 255 },
};
static T_801BED4C D_801BED4C[5] = {
    { 0x050022C8, 96, 85, 48, 42, 0x00, 0x00, 20 }, { 0x050042C8, 96, 85, 48, 62, 0x00, 0x00, 20 },
    { 0x050052C8, 96, 85, 68, 42, 0x00, 0x00, 20 }, { 0x050032C8, 96, 85, 48, 62, 0x00, 0x00, 20 },
    { 0x050062C8, 96, 85, 68, 62, 0x00, 0x00, 20 },
};
static T_801BF170 D_801BED88[98] = {
    { 96, 85, 48, 42, 0x00, 0x00, 20 },   { 96, 85, 48, 62, 0x00, 0x00, 20 },  { 96, 85, 68, 42, 0x00, 0x00, 20 },
    { 96, 85, 48, 62, 0x00, 0x00, 20 },   { 96, 85, 68, 62, 0x00, 0x00, 20 },  { 80, 72, 40, 35, 0x01, 0x01, 52 },
    { 96, 85, 49, 43, 0x03, 0x02, 20 },   { 96, 85, 49, 43, 0x03, 0x02, 20 },  { 96, 85, 49, 43, 0x03, 0x02, 20 },
    { 96, 85, 49, 49, 0x03, 0x02, 20 },   { 48, 44, 25, 23, 0x03, 0x02, 20 },  { 96, 85, 49, 43, 0x03, 0x02, 20 },
    { 48, 46, 25, 24, 0x03, 0x02, 20 },   { 64, 61, 32, 31, 0x03, 0x02, 20 },  { 96, 85, 49, 50, 0x03, 0x02, 20 },
    { 96, 85, 49, 62, 0x03, 0x02, 20 },   { 96, 85, 49, 43, 0x03, 0x02, 20 },  { 48, 80, 21, 41, 0x01, 0x01, 198 },
    { 32, 128, 17, 87, 0x01, 0x01, 138 }, { 80, 53, 40, 27, 0x01, 0x01, 54 },  { 32, 81, 16, 15, 0x03, 0x02, 20 },
    { 80, 45, 35, 23, 0x03, 0x02, 20 },   { 64, 87, 36, 44, 0x03, 0x02, 20 },  { 64, 51, 31, 23, 0x03, 0x02, 20 },
    { 80, 79, 40, 40, 0x03, 0x02, 20 },   { 96, 75, 36, 26, 0x03, 0x02, 20 },  { 48, 41, 24, 20, 0x03, 0x02, 20 },
    { 64, 45, 31, 20, 0x03, 0x02, 20 },   { 80, 52, 38, 28, 0x03, 0x02, 20 },  { 48, 45, 23, 20, 0x03, 0x02, 20 },
    { 48, 59, 25, 37, 0x03, 0x02, 20 },   { 48, 60, 21, 38, 0x03, 0x02, 20 },  { 48, 81, 24, 40, 0x03, 0x02, 20 },
    { 48, 81, 24, 40, 0x03, 0x02, 20 },   { 80, 89, 41, 26, 0x03, 0x02, 20 },  { 80, 53, 39, 26, 0x03, 0x02, 20 },
    { 64, 78, 37, 36, 0x03, 0x02, 20 },   { 64, 68, 33, 33, 0x03, 0x02, 20 },  { 48, 68, 23, 35, 0x03, 0x02, 20 },
    { 48, 36, 25, 17, 0x03, 0x02, 20 },   { 48, 25, 24, 12, 0x03, 0x02, 20 },  { 64, 75, 24, 37, 0x03, 0x02, 20 },
    { 32, 53, 17, 26, 0x03, 0x02, 20 },   { 80, 62, 35, 27, 0x01, 0x01, 105 }, { 64, 76, 31, 31, 0x01, 0x01, 133 },
    { 96, 85, 47, 43, 0x03, 0x02, 20 },   { 80, 71, 48, 33, 0x01, 0x01, 180 }, { 80, 87, 44, 44, 0x01, 0x01, 72 },
    { 64, 65, 31, 36, 0x01, 0x01, 57 },   { 48, 41, 28, 20, 0x01, 0x01, 60 },  { 64, 76, 17, 36, 0x01, 0x01, 58 },
    { 80, 60, 27, 22, 0x01, 0x01, 83 },   { 80, 47, 38, 23, 0x01, 0x01, 69 },  { 80, 60, 40, 38, 0x01, 0x01, 29 },
    { 48, 19, 17, 8, 0x01, 0x01, 25 },    { 32, 99, 17, 16, 0x01, 0x01, 88 },  { 48, 69, 19, 28, 0x01, 0x01, 76 },
    { 48, 83, 34, 47, 0x01, 0x01, 104 },  { 80, 54, 45, 27, 0x01, 0x01, 61 },  { 80, 92, 35, 50, 0x01, 0x01, 60 },
    { 48, 75, 24, 37, 0x03, 0x02, 20 },   { 64, 49, 32, 23, 0x03, 0x02, 20 },  { 64, 49, 25, 24, 0x03, 0x02, 20 },
    { 64, 52, 32, 24, 0x03, 0x02, 34 },   { 64, 49, 31, 24, 0x03, 0x02, 34 },  { 32, 33, 18, 14, 0x03, 0x02, 34 },
    { 48, 50, 25, 25, 0x03, 0x02, 34 },   { 64, 52, 32, 25, 0x03, 0x02, 34 },  { 48, 35, 24, 18, 0x03, 0x02, 34 },
    { 64, 51, 32, 26, 0x03, 0x02, 34 },   { 48, 35, 24, 18, 0x03, 0x02, 34 },  { 48, 53, 24, 28, 0x03, 0x02, 34 },
    { 64, 53, 33, 25, 0x03, 0x02, 34 },   { 64, 47, 31, 24, 0x03, 0x02, 34 },  { 64, 52, 32, 35, 0x03, 0x02, 34 },
    { 48, 48, 24, 23, 0x03, 0x02, 34 },   { 64, 87, 32, 26, 0x03, 0x02, 34 },  { 48, 30, 24, 14, 0x03, 0x02, 34 },
    { 80, 74, 40, 36, 0x01, 0x01, 50 },   { 80, 87, 6, 41, 0x01, 0x01, 42 },   { 80, 56, 19, 27, 0x01, 0x01, 40 },
    { 80, 65, 25, 33, 0x01, 0x01, 40 },   { 16, 38, 8, 12, 0x01, 0x01, 47 },   { 80, 78, 46, 33, 0x01, 0x01, 142 },
    { 80, 55, 32, 29, 0x01, 0x01, 155 },  { 80, 98, 67, 48, 0x01, 0x01, 51 },  { 80, 62, 47, 19, 0x01, 0x01, 55 },
    { 32, 123, 15, 83, 0x01, 0x01, 140 }, { 80, 60, 47, 14, 0x01, 0x01, 170 }, { 48, 77, 18, 59, 0x01, 0x01, 79 },
    { 80, 64, 35, 30, 0x01, 0x01, 33 },   { 64, 50, 29, 22, 0x01, 0x01, 40 },  { 80, 65, 39, 5, 0x01, 0x01, 37 },
    { 32, 61, 8, 56, 0x01, 0x01, 35 },    { 80, 83, 37, 42, 0x01, 0x01, 95 },  { 80, 27, 30, 21, 0x01, 0x01, 134 },
    { 80, 23, 122, -18, 0x01, 0x01, 53 }, { 80, 60, 27, 22, 0x01, 0x01, 83 },
};
static s32 D_801BF15C[5] = {
    0x50, 0x50, 0x8D, 0x50, 0x50,
};
static T_801BF170 D_801BF170[58] = {
    { 96, 85, 73, 67, 0x00, 0x00, 60 }, { 96, 85, 73, 74, 0x00, 0x00, 60 }, { 96, 85, 80, 67, 0x00, 0x00, 60 },
    { 96, 85, 73, 67, 0x00, 0x00, 60 }, { 96, 85, 80, 74, 0x00, 0x00, 60 }, { 32, 29, 17, 14, 0x02, 0x00, 50 },
    { 32, 27, 16, 13, 0x02, 0x00, 50 }, { 32, 30, 16, 15, 0x02, 0x00, 50 }, { 16, 32, 8, 20, 0x02, 0x00, 50 },
    { 16, 12, 8, 6, 0x02, 0x00, 50 },   { 32, 27, 16, 13, 0x02, 0x00, 50 }, { 16, 14, 8, 7, 0x02, 0x00, 50 },
    { 32, 19, 16, 9, 0x02, 0x00, 50 },  { 32, 26, 16, 16, 0x02, 0x00, 50 }, { 16, 32, 8, 22, 0x02, 0x00, 50 },
    { 32, 27, 16, 13, 0x02, 0x00, 50 }, { 16, 35, 9, 5, 0x02, 0x00, 45 },   { 32, 18, 14, 9, 0x02, 0x00, 45 },
    { 32, 38, 18, 19, 0x02, 0x00, 45 }, { 32, 21, 16, 9, 0x02, 0x00, 45 },  { 32, 34, 16, 17, 0x02, 0x00, 45 },
    { 48, 32, 19, 11, 0x02, 0x00, 45 }, { 32, 17, 16, 8, 0x02, 0x00, 45 },  { 32, 17, 16, 7, 0x02, 0x00, 45 },
    { 32, 21, 16, 11, 0x02, 0x00, 45 }, { 32, 18, 16, 8, 0x02, 0x00, 45 },  { 16, 24, 9, 15, 0x02, 0x00, 45 },
    { 16, 25, 7, 16, 0x02, 0x00, 45 },  { 32, 35, 16, 17, 0x02, 0x00, 45 }, { 16, 19, 5, 9, 0x02, 0x00, 80 },
    { 32, 28, 17, 7, 0x02, 0x00, 66 },  { 32, 16, 16, 8, 0x02, 0x00, 66 },  { 32, 24, 18, 11, 0x02, 0x00, 66 },
    { 32, 21, 16, 10, 0x02, 0x00, 66 }, { 16, 21, 8, 11, 0x02, 0x00, 66 },  { 16, 10, 8, 4, 0x02, 0x00, 66 },
    { 16, 7, 8, 3, 0x02, 0x00, 66 },    { 32, 23, 13, 11, 0x02, 0x00, 66 }, { 16, 16, 8, 8, 0x02, 0x00, 66 },
    { 16, 17, 8, 7, 0x02, 0x00, 50 },   { 16, 23, 9, 10, 0x02, 0x00, 66 },  { 16, 15, 8, 7, 0x02, 0x00, 66 },
    { 32, 15, 15, 7, 0x02, 0x00, 66 },  { 32, 17, 16, 8, 0x02, 0x00, 90 },  { 32, 16, 16, 8, 0x02, 0x00, 90 },
    { 16, 10, 8, 5, 0x02, 0x00, 90 },   { 16, 17, 8, 8, 0x02, 0x00, 90 },   { 32, 17, 17, 8, 0x02, 0x00, 90 },
    { 16, 11, 8, 5, 0x02, 0x00, 90 },   { 32, 17, 15, 9, 0x02, 0x00, 90 },  { 16, 12, 8, 6, 0x02, 0x00, 90 },
    { 16, 18, 9, 9, 0x02, 0x00, 90 },   { 32, 17, 17, 8, 0x02, 0x00, 90 },  { 32, 15, 16, 8, 0x02, 0x00, 90 },
    { 16, 18, 9, 13, 0x02, 0x00, 90 },  { 16, 16, 8, 7, 0x02, 0x00, 90 },   { 16, 30, 9, 8, 0x02, 0x00, 90 },
    { 16, 9, 9, 4, 0x02, 0x00, 90 },
};
static s32 D_801BF3B4[5] = {
    0x00, 0x01, 0x02, 0x03, 0x04,
};
static s32 D_801BF3C8[98] = {
    0x3A, 0x01, 0x02, 0x03, 0x04, 0x3A, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x3A, 0x3A, 0x3A, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x3A,
    0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x3A, 0x3A, 0x27, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A,
    0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A,
    0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A, 0x3A,
};

// mapId
// 0-4 is gameplay_dangeon_keep
// 5-0x3A is map_i_static
// 0x100-0x162 is map_grand_static
s32 func_80109A98(s32);

// Get ? Color
void func_801094A0(s32 arg0, Color_RGBA8* color) {
    *color = D_801BED40[arg0];
}

void MapData_GetMapTexDimGameplayDangeonKeep(s32 mapId, s32* width, s32* height) {
    *width = D_801BED4C[mapId].width;
    *height = D_801BED4C[mapId].height;
}

void func_801094F8(s32 mapId, s32* arg1, s32* arg2) {
    *arg1 = D_801BED4C[mapId].unk6;
    *arg2 = D_801BED4C[mapId].unk7;
}

void func_80109528(s32 mapId, s32* arg1) {
    *arg1 = D_801BED4C[mapId].unk8;
}

u8 func_8010954C(s32 arg0) {
    return D_801BED4C[arg0].unk9;
}

s16 MapData_GetMapScaleGameplayDangeonKeep(s32 mapId) {
    return D_801BED4C[mapId].scale;
}

TexturePtr func_8010958C(s32 arg0) {
    return D_801BED4C[arg0].lmapTex;
}

void MapData_GetMapTexDimGrandMap(s32 mapId, s32* arg1, s32* arg2) {
    *arg1 = D_801BED88[mapId - 0x100].unk0;
    *arg2 = D_801BED88[mapId - 0x100].unk1;
}

void func_801095DC(s32 mapId, s32* arg1, s32* arg2) {
    *arg1 = D_801BED88[mapId - 0x100].unk2;
    *arg2 = D_801BED88[mapId - 0x100].unk4;
}

void func_8010960C(s32 mapId, s32* arg1) {
    *arg1 = D_801BED88[mapId - 0x100].unk6;
}

u8 func_80109630(s32 mapId) {
    return D_801BED88[mapId - 0x100].unk7;
}

s16 func_80109650(s32 mapId) {
    return D_801BED88[mapId - 0x100].unk8;
}

s32 func_80109670(s32 mapId) {
    s32 cond = mapId - 0x100;
    s32 var_s1 = 0;
    s32 i;

    for (i = 1; i < cond + 1; i++) {
        var_s1 += func_801096D4((i - 1) + 0x100);
    }
    return var_s1;
}

s32 func_801096D4(s32 mapId) {
    return (D_801BED88[mapId - 0x100].unk0 * D_801BED88[mapId - 0x100].unk1) / 2;
}

s32 func_80109714(s32 mapId) {
    if ((mapId >= 0) && (mapId < 5)) {
        return MAPDATA_MID_GAMEPLAY_DANGEON_KEEP;
    }
    if ((mapId >= 0x100) && (mapId < 0x162)) {
        return MAPDATA_MID_GRAND_MAP_STATIC;
    }
    return MAPDATA_MID_MAP_I_STATIC;
}

void MapData_GetMapTexDim(s32 mapId, s32* width, s32* height) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            MapData_GetMapTexDimGameplayDangeonKeep(mapId, width, height);
            return;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            MapData_GetMapTexDimGrandMap(mapId, width, height);
            return;
        default:
            *width = *height = 0;
            return;
    }
}

void func_801097C8(s32 mapId, s32* arg1, s32* arg2) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            func_801094F8(mapId, arg1, arg2);
            return;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            func_801095DC(mapId, arg1, arg2);
            return;
        default:
            *arg1 = *arg2 = 0;
            return;
    }
}

void MapData_GetMapScale(s32 mapId, s32* scale) {
    switch (func_80109714(mapId)) {
        default:
            *scale = 0;
            return;
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            *scale = MapData_GetMapScaleGameplayDangeonKeep(mapId);
            return;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            *scale = func_80109650(mapId);
            return;
    }
}

void func_801098A0(s32 mapId, s32* arg1) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            func_80109528(mapId, arg1);
            return;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            func_8010960C(mapId, arg1);
            return;
        default:
            *arg1 = 0;
            return;
    }
}

// return some color index?
s32 func_80109908(s32 mapId) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            return func_8010954C(mapId);
        case MAPDATA_MID_GRAND_MAP_STATIC:
            return func_80109630(mapId);
        default:
            return 0;
    }
}

s32 func_80109964(s32 arg0) {
    return D_801BF15C[arg0];
}

void func_8010997C(s32 arg0, s32* arg1, s32* arg2) {
    *arg1 = D_801BF170[arg0].unk0;
    *arg2 = D_801BF170[arg0].unk1;
}

void func_801099AC(s32 arg0, s32* arg1, s32* arg2) {
    *arg1 = D_801BF170[arg0].unk2;
    *arg2 = D_801BF170[arg0].unk4;
}

void func_801099DC(s32 arg0, s32* arg1) {
    *arg1 = D_801BF170[arg0].unk6;
}

u8 func_80109A00(s32 arg0) {
    return D_801BF170[arg0].unk7;
}

s16 func_80109A20(s32 arg0) {
    return D_801BF170[arg0].unk8;
}

s32 func_80109A40(s32 arg0) {
    s32 temp_s2;
    s32 var_s0;
    s32 var_s1;

    var_s1 = 0;
    for (var_s0 = 1; var_s0 < arg0 + 1; var_s0++) {
        var_s1 += func_80109A98(var_s0 - 1);
    }

    return var_s1;
}

s32 func_80109A98(s32 arg0) {
    return (D_801BF170[arg0].unk0 * D_801BF170[arg0].unk1) / 2;
}

s32 func_80109AD8(s32 mapId) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            return D_801BF3B4[mapId];
        case MAPDATA_MID_GRAND_MAP_STATIC:
            return D_801BF3C8[mapId - 0x100];
        default:
            return 0;
    }
}

s32 func_80109B38(s32 mapId) {
    if (func_80109AD8(mapId) != 0x3A) {
        return 1;
    }
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            return 2;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            return 0;
        default:
            return 0;
    }
}

s32 func_80109BA0(s32 mapId) {
    s32 temp_v0 = func_80109AD8(mapId);

    if (temp_v0 != 0x3A) {
        return temp_v0;
    }
    if ((mapId >= 0x100) && (mapId < 0x162)) {
        return mapId - 0xC6;
    }
    return -1;
}

s32 func_80109BF4(s32 mapCompactId) {
    if (mapCompactId == -1) {
        return MAPDATA_CPID_2;
    }
    if (mapCompactId < 0x3A) {
        return MAPDATA_CPID_MAP_I_STATIC;
    }
    if (mapCompactId >= 0x3A) {
        return MAPDATA_CPID_GRAND_MAP_STATIC;
    }
    return MAPDATA_CPID_2;
}

s32 func_80109C38(s32 mapCompactId) {
    if (mapCompactId == -1) {
        return 0;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            return func_80109670(mapCompactId + 0xC6);
        case MAPDATA_CPID_MAP_I_STATIC:
            return func_80109A40(mapCompactId);
        case MAPDATA_CPID_2:
            return 0;
        default:
            return 0;
    }
}

s32 MapData_GetMapSize(s32 mapCompactId) {
    if (mapCompactId == -1) {
        return 0;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            return func_801096D4(mapCompactId + 0xC6);
        case MAPDATA_CPID_MAP_I_STATIC:
            return func_80109A98(mapCompactId);
        case MAPDATA_CPID_2:
            return 0;
        default:
            return 0;
    }
}

void func_80109D40(s32 mapCompactId, s32* arg1, s32* arg2) {
    if (mapCompactId == -1) {
        *arg1 = *arg2 = 0;
        return;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            // id base 0x100
            MapData_GetMapTexDimGrandMap(mapCompactId + 0xC6, arg1, arg2);
            return;
        case MAPDATA_CPID_MAP_I_STATIC:
            func_8010997C(mapCompactId, arg1, arg2);
            return;
        case MAPDATA_CPID_2:
        default:
            *arg1 = *arg2 = 0;
            return;
    }
}

void func_80109DD8(s32 mapCompactId, s32* arg1, s32* arg2) {
    s32 temp_v0;

    if (mapCompactId == -1) {
        *arg1 = *arg2 = 0;
        return;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            func_801095DC(mapCompactId + 0xC6, arg1, arg2);
            return;
        case MAPDATA_CPID_MAP_I_STATIC:
            func_801099AC(mapCompactId, arg1, arg2);
            return;
        case MAPDATA_CPID_2:
        default:
            *arg1 = *arg2 = 0;
            return;
    }
}

void func_80109E70(s32 mapCompactId, s32* arg1) {
    if (mapCompactId == -1) {
        *arg1 = 0;
        return;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            func_8010960C(mapCompactId + 0xC6, arg1);
            return;
        case MAPDATA_CPID_MAP_I_STATIC:
            func_801099DC(mapCompactId, arg1);
            return;
        case MAPDATA_CPID_2:
        default:
            *arg1 = 0;
            return;
    }
}

u8 func_80109EF8(s32 mapCompactId) {
    if (mapCompactId == -1) {
        return 0;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            return func_80109630(mapCompactId + 0xC6);
        case MAPDATA_CPID_MAP_I_STATIC:
            return func_80109A00(mapCompactId);
        case MAPDATA_CPID_2:
        default:
            return 0;
    }
}

s16 func_80109F78(s32 mapCompactId) {
    if (mapCompactId == -1) {
        return 0;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            return func_80109650(mapCompactId + 0xC6);
        case MAPDATA_CPID_MAP_I_STATIC:
            return func_80109A20(mapCompactId);
        case MAPDATA_CPID_2:
        default:
            return 0;
    }
}
