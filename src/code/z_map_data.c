#include "global.h"
#include "z64map.h"

static Color_RGBA8 D_801BED40[3] = {
    { 255, 255, 255, 255 },
    { 0, 255, 255, 160 },
    { 100, 255, 255, 255 },
};
static T_801BED4C D_801BED4C[5] = {
    { 0x050022C8, 0x60, 0x55, 0x30, 0x2A, 0x00, 0x00, 20 }, { 0x050042C8, 0x60, 0x55, 0x30, 0x3E, 0x00, 0x00, 20 },
    { 0x050052C8, 0x60, 0x55, 0x44, 0x2A, 0x00, 0x00, 20 }, { 0x050032C8, 0x60, 0x55, 0x30, 0x3E, 0x00, 0x00, 20 },
    { 0x050062C8, 0x60, 0x55, 0x44, 0x3E, 0x00, 0x00, 20 },
};
static T_801BF170 D_801BED88[98] = {
    { 0x60, 0x55, 48, 42, 0x00, 0x00, 20 },   { 0x60, 0x55, 48, 62, 0x00, 0x00, 20 },
    { 0x60, 0x55, 68, 42, 0x00, 0x00, 20 },   { 0x60, 0x55, 48, 62, 0x00, 0x00, 20 },
    { 0x60, 0x55, 68, 62, 0x00, 0x00, 20 },   { 0x50, 0x48, 40, 35, 0x01, 0x01, 52 },
    { 0x60, 0x55, 49, 43, 0x03, 0x02, 20 },   { 0x60, 0x55, 49, 43, 0x03, 0x02, 20 },
    { 0x60, 0x55, 49, 43, 0x03, 0x02, 20 },   { 0x60, 0x55, 49, 49, 0x03, 0x02, 20 },
    { 0x30, 0x2C, 25, 23, 0x03, 0x02, 20 },   { 0x60, 0x55, 49, 43, 0x03, 0x02, 20 },
    { 0x30, 0x2E, 25, 24, 0x03, 0x02, 20 },   { 0x40, 0x3D, 32, 31, 0x03, 0x02, 20 },
    { 0x60, 0x55, 49, 50, 0x03, 0x02, 20 },   { 0x60, 0x55, 49, 62, 0x03, 0x02, 20 },
    { 0x60, 0x55, 49, 43, 0x03, 0x02, 20 },   { 0x30, 0x50, 21, 41, 0x01, 0x01, 198 },
    { 0x20, 0x80, 17, 87, 0x01, 0x01, 138 },  { 0x50, 0x35, 40, 27, 0x01, 0x01, 54 },
    { 0x20, 0x51, 16, 15, 0x03, 0x02, 20 },   { 0x50, 0x2D, 35, 23, 0x03, 0x02, 20 },
    { 0x40, 0x57, 36, 44, 0x03, 0x02, 20 },   { 0x40, 0x33, 31, 23, 0x03, 0x02, 20 },
    { 0x50, 0x4F, 40, 40, 0x03, 0x02, 20 },   { 0x60, 0x4B, 36, 26, 0x03, 0x02, 20 },
    { 0x30, 0x29, 24, 20, 0x03, 0x02, 20 },   { 0x40, 0x2D, 31, 20, 0x03, 0x02, 20 },
    { 0x50, 0x34, 38, 28, 0x03, 0x02, 20 },   { 0x30, 0x2D, 23, 20, 0x03, 0x02, 20 },
    { 0x30, 0x3B, 25, 37, 0x03, 0x02, 20 },   { 0x30, 0x3C, 21, 38, 0x03, 0x02, 20 },
    { 0x30, 0x51, 24, 40, 0x03, 0x02, 20 },   { 0x30, 0x51, 24, 40, 0x03, 0x02, 20 },
    { 0x50, 0x59, 41, 26, 0x03, 0x02, 20 },   { 0x50, 0x35, 39, 26, 0x03, 0x02, 20 },
    { 0x40, 0x4E, 37, 36, 0x03, 0x02, 20 },   { 0x40, 0x44, 33, 33, 0x03, 0x02, 20 },
    { 0x30, 0x44, 23, 35, 0x03, 0x02, 20 },   { 0x30, 0x24, 25, 17, 0x03, 0x02, 20 },
    { 0x30, 0x19, 24, 12, 0x03, 0x02, 20 },   { 0x40, 0x4B, 24, 37, 0x03, 0x02, 20 },
    { 0x20, 0x35, 17, 26, 0x03, 0x02, 20 },   { 0x50, 0x3E, 35, 27, 0x01, 0x01, 105 },
    { 0x40, 0x4C, 31, 31, 0x01, 0x01, 133 },  { 0x60, 0x55, 47, 43, 0x03, 0x02, 20 },
    { 0x50, 0x47, 48, 33, 0x01, 0x01, 180 },  { 0x50, 0x57, 44, 44, 0x01, 0x01, 72 },
    { 0x40, 0x41, 31, 36, 0x01, 0x01, 57 },   { 0x30, 0x29, 28, 20, 0x01, 0x01, 60 },
    { 0x40, 0x4C, 17, 36, 0x01, 0x01, 58 },   { 0x50, 0x3C, 27, 22, 0x01, 0x01, 83 },
    { 0x50, 0x2F, 38, 23, 0x01, 0x01, 69 },   { 0x50, 0x3C, 40, 38, 0x01, 0x01, 29 },
    { 0x30, 0x13, 17, 8, 0x01, 0x01, 25 },    { 0x20, 0x63, 17, 16, 0x01, 0x01, 88 },
    { 0x30, 0x45, 19, 28, 0x01, 0x01, 76 },   { 0x30, 0x53, 34, 47, 0x01, 0x01, 104 },
    { 0x50, 0x36, 45, 27, 0x01, 0x01, 61 },   { 0x50, 0x5C, 35, 50, 0x01, 0x01, 60 },
    { 0x30, 0x4B, 24, 37, 0x03, 0x02, 20 },   { 0x40, 0x31, 32, 23, 0x03, 0x02, 20 },
    { 0x40, 0x31, 25, 24, 0x03, 0x02, 20 },   { 0x40, 0x34, 32, 24, 0x03, 0x02, 34 },
    { 0x40, 0x31, 31, 24, 0x03, 0x02, 34 },   { 0x20, 0x21, 18, 14, 0x03, 0x02, 34 },
    { 0x30, 0x32, 25, 25, 0x03, 0x02, 34 },   { 0x40, 0x34, 32, 25, 0x03, 0x02, 34 },
    { 0x30, 0x23, 24, 18, 0x03, 0x02, 34 },   { 0x40, 0x33, 32, 26, 0x03, 0x02, 34 },
    { 0x30, 0x23, 24, 18, 0x03, 0x02, 34 },   { 0x30, 0x35, 24, 28, 0x03, 0x02, 34 },
    { 0x40, 0x35, 33, 25, 0x03, 0x02, 34 },   { 0x40, 0x2F, 31, 24, 0x03, 0x02, 34 },
    { 0x40, 0x34, 32, 35, 0x03, 0x02, 34 },   { 0x30, 0x30, 24, 23, 0x03, 0x02, 34 },
    { 0x40, 0x57, 32, 26, 0x03, 0x02, 34 },   { 0x30, 0x1E, 24, 14, 0x03, 0x02, 34 },
    { 0x50, 0x4A, 40, 36, 0x01, 0x01, 50 },   { 0x50, 0x57, 6, 41, 0x01, 0x01, 42 },
    { 0x50, 0x38, 19, 27, 0x01, 0x01, 40 },   { 0x50, 0x41, 25, 33, 0x01, 0x01, 40 },
    { 0x10, 0x26, 8, 12, 0x01, 0x01, 47 },    { 0x50, 0x4E, 46, 33, 0x01, 0x01, 142 },
    { 0x50, 0x37, 32, 29, 0x01, 0x01, 155 },  { 0x50, 0x62, 67, 48, 0x01, 0x01, 51 },
    { 0x50, 0x3E, 47, 19, 0x01, 0x01, 55 },   { 0x20, 0x7B, 15, 83, 0x01, 0x01, 140 },
    { 0x50, 0x3C, 47, 14, 0x01, 0x01, 170 },  { 0x30, 0x4D, 18, 59, 0x01, 0x01, 79 },
    { 0x50, 0x40, 35, 30, 0x01, 0x01, 33 },   { 0x40, 0x32, 29, 22, 0x01, 0x01, 40 },
    { 0x50, 0x41, 39, 5, 0x01, 0x01, 37 },    { 0x20, 0x3D, 8, 56, 0x01, 0x01, 35 },
    { 0x50, 0x53, 37, 42, 0x01, 0x01, 95 },   { 0x50, 0x1B, 30, 21, 0x01, 0x01, 134 },
    { 0x50, 0x17, 122, -18, 0x01, 0x01, 53 }, { 0x50, 0x3C, 27, 22, 0x01, 0x01, 83 },
};
static s32 D_801BF15C[5] = {
    0x50, 0x50, 0x8D, 0x50, 0x50,
};
static T_801BF170 D_801BF170[58] = {
    { 0x60, 0x55, 73, 67, 0x00, 0x00, 60 }, { 0x60, 0x55, 73, 74, 0x00, 0x00, 60 },
    { 0x60, 0x55, 80, 67, 0x00, 0x00, 60 }, { 0x60, 0x55, 73, 67, 0x00, 0x00, 60 },
    { 0x60, 0x55, 80, 74, 0x00, 0x00, 60 }, { 0x20, 0x1D, 17, 14, 0x02, 0x00, 50 },
    { 0x20, 0x1B, 16, 13, 0x02, 0x00, 50 }, { 0x20, 0x1E, 16, 15, 0x02, 0x00, 50 },
    { 0x10, 0x20, 8, 20, 0x02, 0x00, 50 },  { 0x10, 0x0C, 8, 6, 0x02, 0x00, 50 },
    { 0x20, 0x1B, 16, 13, 0x02, 0x00, 50 }, { 0x10, 0x0E, 8, 7, 0x02, 0x00, 50 },
    { 0x20, 0x13, 16, 9, 0x02, 0x00, 50 },  { 0x20, 0x1A, 16, 16, 0x02, 0x00, 50 },
    { 0x10, 0x20, 8, 22, 0x02, 0x00, 50 },  { 0x20, 0x1B, 16, 13, 0x02, 0x00, 50 },
    { 0x10, 0x23, 9, 5, 0x02, 0x00, 45 },   { 0x20, 0x12, 14, 9, 0x02, 0x00, 45 },
    { 0x20, 0x26, 18, 19, 0x02, 0x00, 45 }, { 0x20, 0x15, 16, 9, 0x02, 0x00, 45 },
    { 0x20, 0x22, 16, 17, 0x02, 0x00, 45 }, { 0x30, 0x20, 19, 11, 0x02, 0x00, 45 },
    { 0x20, 0x11, 16, 8, 0x02, 0x00, 45 },  { 0x20, 0x11, 16, 7, 0x02, 0x00, 45 },
    { 0x20, 0x15, 16, 11, 0x02, 0x00, 45 }, { 0x20, 0x12, 16, 8, 0x02, 0x00, 45 },
    { 0x10, 0x18, 9, 15, 0x02, 0x00, 45 },  { 0x10, 0x19, 7, 16, 0x02, 0x00, 45 },
    { 0x20, 0x23, 16, 17, 0x02, 0x00, 45 }, { 0x10, 0x13, 5, 9, 0x02, 0x00, 80 },
    { 0x20, 0x1C, 17, 7, 0x02, 0x00, 66 },  { 0x20, 0x10, 16, 8, 0x02, 0x00, 66 },
    { 0x20, 0x18, 18, 11, 0x02, 0x00, 66 }, { 0x20, 0x15, 16, 10, 0x02, 0x00, 66 },
    { 0x10, 0x15, 8, 11, 0x02, 0x00, 66 },  { 0x10, 0x0A, 8, 4, 0x02, 0x00, 66 },
    { 0x10, 0x07, 8, 3, 0x02, 0x00, 66 },   { 0x20, 0x17, 13, 11, 0x02, 0x00, 66 },
    { 0x10, 0x10, 8, 8, 0x02, 0x00, 66 },   { 0x10, 0x11, 8, 7, 0x02, 0x00, 50 },
    { 0x10, 0x17, 9, 10, 0x02, 0x00, 66 },  { 0x10, 0x0F, 8, 7, 0x02, 0x00, 66 },
    { 0x20, 0x0F, 15, 7, 0x02, 0x00, 66 },  { 0x20, 0x11, 16, 8, 0x02, 0x00, 90 },
    { 0x20, 0x10, 16, 8, 0x02, 0x00, 90 },  { 0x10, 0x0A, 8, 5, 0x02, 0x00, 90 },
    { 0x10, 0x11, 8, 8, 0x02, 0x00, 90 },   { 0x20, 0x11, 17, 8, 0x02, 0x00, 90 },
    { 0x10, 0x0B, 8, 5, 0x02, 0x00, 90 },   { 0x20, 0x11, 15, 9, 0x02, 0x00, 90 },
    { 0x10, 0x0C, 8, 6, 0x02, 0x00, 90 },   { 0x10, 0x12, 9, 9, 0x02, 0x00, 90 },
    { 0x20, 0x11, 17, 8, 0x02, 0x00, 90 },  { 0x20, 0x0F, 16, 8, 0x02, 0x00, 90 },
    { 0x10, 0x12, 9, 13, 0x02, 0x00, 90 },  { 0x10, 0x10, 8, 7, 0x02, 0x00, 90 },
    { 0x10, 0x1E, 9, 8, 0x02, 0x00, 90 },   { 0x10, 0x09, 9, 4, 0x02, 0x00, 90 },
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

void func_801094C8(s32 arg0, s32* arg1, s32* arg2) {
    *arg1 = D_801BED4C[arg0].unk4;
    *arg2 = D_801BED4C[arg0].unk5;
}

void func_801094F8(s32 arg0, s32* arg1, s32* arg2) {
    *arg1 = D_801BED4C[arg0].unk6;
    *arg2 = D_801BED4C[arg0].unk7;
}

void func_80109528(s32 arg0, s32* arg1) {
    *arg1 = D_801BED4C[arg0].unk8;
}

u8 func_8010954C(s32 arg0) {
    return D_801BED4C[arg0].unk9;
}

s16 func_8010956C(s32 arg0) {
    return D_801BED4C[arg0].unkA;
}

TexturePtr func_8010958C(s32 arg0) {
    return D_801BED4C[arg0].lmapTex;
}

void func_801095AC(s32 mapId, s32* arg1, s32* arg2) {
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

void func_80109754(s32 mapId, s32* arg1, s32* arg2) {
    switch (func_80109714(mapId)) {
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            func_801094C8(mapId, arg1, arg2);
            return;
        case MAPDATA_MID_GRAND_MAP_STATIC:
            func_801095AC(mapId, arg1, arg2);
            return;
        default:
            *arg2 = 0;
            *arg1 = 0;
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
            *arg2 = 0;
            *arg1 = 0;
            return;
    }
}

void MapData_GetMapScale(s32 mapId, s32* scale) {
    switch (func_80109714(mapId)) {
        default:
            *scale = 0;
            return;
        case MAPDATA_MID_GAMEPLAY_DANGEON_KEEP:
            *scale = func_8010956C(mapId);
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
u8 func_80109908(s32 mapId) {
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
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
    switch (func_80109BF4(mapCompactId)) {
        case MAPDATA_CPID_GRAND_MAP_STATIC:
            // id base 0x100
            func_801095AC(mapCompactId + 0xC6, arg1, arg2);
            return;
        case MAPDATA_CPID_MAP_I_STATIC:
            func_8010997C(mapCompactId, arg1, arg2);
            return;
        case MAPDATA_CPID_2:
        default:
            *arg2 = 0;
            *arg1 = 0;
            return;
    }
}

void func_80109DD8(s32 mapCompactId, s32* arg1, s32* arg2) {
    s32 temp_v0;

    if (mapCompactId == -1) {
        *arg2 = 0;
        *arg1 = 0;
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
            *arg2 = 0;
            *arg1 = 0;
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
