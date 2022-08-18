#include "global.h"
#include "z64map.h"

extern Color_RGBA8  D_801BED40[];
extern T_801BED4C   D_801BED4C[5];
extern T_801BF170   D_801BED88[];
extern s32          D_801BEFC8[];
extern s32          D_801BF15C[5];
extern T_801BF170   D_801BF170[];
extern s32          D_801BF3B4[];

s32 func_80109A98(s32);

// Get ? Color
void func_801094A0(s32 arg0, Color_RGBA8* color) {
    *color = D_801BED40[arg0];
}

void func_801094C8(s32 arg0, s32 *arg1, s32 *arg2) {
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

void func_801095AC(s32 arg0, s32 *arg1, s32 *arg2) {
    *arg1 = D_801BED88[arg0-0x100].unk0;
    *arg2 = D_801BED88[arg0-0x100].unk1;
}

void func_801095DC(s32 arg0, s32* arg1, s32* arg2) {
    *arg1 = D_801BED88[arg0-0x100].unk2;
    *arg2 = D_801BED88[arg0-0x100].unk4;
}

void func_8010960C(s32 arg0, s32* arg1) {
    *arg1 = D_801BED88[arg0-0x100].unk6;
}

u8 func_80109630(s32 arg0) {
    return D_801BED88[arg0-0x100].unk7;
}

s16 func_80109650(s32 arg0) {
    return D_801BED88[arg0-0x100].unk8;
}

s32 func_80109670(s32 arg0) {
    s32 cond = arg0 - 0x100;
    s32 var_s1 = 0;
    s32 i;

    for(i = 1; i < cond + 1; i++) {
        var_s1 += func_801096D4((i-1) + 0x100);
    }
    return var_s1;
}

s32 func_801096D4(s32 arg0) {
    return (D_801BED88[arg0 - 0x100].unk0 * D_801BED88[arg0 - 0x100].unk1) / 2;
}

s32 func_80109714(s32 arg0) {
    if ((arg0 >= 0) && (arg0 < 5)) {
        return 0;
    }
    if ((arg0 >= 0x100) && (arg0 < 0x162)) {
        return 1;
    }
    return 2;
}

void func_80109754(s32 arg0, s32 *arg1, s32 *arg2) {
    switch (func_80109714(arg0)) {
    case 0:
        func_801094C8(arg0, arg1, arg2);
        return;
    case 1:
        func_801095AC(arg0, arg1, arg2);
        return;
    default:
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
}

void func_801097C8(s32 arg0, s32* arg1, s32* arg2) {
    switch (func_80109714(arg0)) {
    case 0:
        func_801094F8(arg0, arg1, arg2);
        return;
    case 1:
        func_801095DC(arg0, arg1, arg2);
        return;
    default:
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
}

void func_8010983C(s32 arg0, s32 *arg1) {
    switch(func_80109714(arg0)){
        default:
            *arg1 = 0;
            return;
        case 0:
            *arg1 = func_8010956C(arg0);
            return;
        case 1:
            *arg1 = func_80109650(arg0);
            return;
    }
}

void func_801098A0(s32 arg0, s32* arg1) {
    switch (func_80109714(arg0)) {
    case 0:
        func_80109528(arg0, arg1);
        return;
    case 1:
        func_8010960C(arg0, arg1);
        return;
    default:
        *arg1 = 0;
        return;
    }
}

//return some color index?
u8 func_80109908(s32 arg0) {
    switch (func_80109714(arg0)) {
    case 0:
        return func_8010954C(arg0);
    case 1:
        return func_80109630(arg0);
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
    *arg1 =  D_801BF170[arg0].unk2;
    *arg2 =  D_801BF170[arg0].unk4;
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
    for (var_s0 = 1; var_s0 < arg0+1; var_s0++)
    {
        var_s1 += func_80109A98(var_s0 - 1);
    }

    return var_s1;
}

s32 func_80109A98(s32 arg0) {
    return (D_801BF170[arg0].unk0 * D_801BF170[arg0].unk1) / 2;
}

s32 func_80109AD8(s32 arg0) {
    switch (func_80109714(arg0)) {
    case 0:
        return D_801BF3B4[arg0];
    case 1:
        return D_801BEFC8[arg0];
    default:
        return 0;
    }
}

s32 func_80109B38(s32 arg0) {
    if (func_80109AD8(arg0) != 0x3A) {
        return 1;
    }
    switch (func_80109714(arg0)) {
    case 0:
        return 2;
    case 1:
        return 0;
    default:
        return 0;
    }
}

s32 func_80109BA0(s32 arg0) {
    s32 temp_v0 = func_80109AD8(arg0);

    if (temp_v0 != 0x3A) {
        return temp_v0;
    }
    if ((arg0 >= 0x100) && (arg0 < 0x162)) {
        return arg0 - 0xC6;
    }
    return -1;
}

s32 func_80109BF4(s32 arg0) {
    if (arg0 == -1) {
        return 2;
    }
    if (arg0 < 0x3A) {
        return MAPDATA_SOURCE_MAP_I_STATIC;
    }
    if (arg0 >= 0x3A) {
        return 0;
    }
    return 2;
}

s32 func_80109C38(s32 arg0) {
    if (arg0 == -1) {
        return 0;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        return func_80109670(arg0 + 0xC6);
    case MAPDATA_SOURCE_MAP_I_STATIC:
        return func_80109A40(arg0);
    case 2:
        return 0;
    default:
        return 0;
    }
}

s32 MapData_GetIMapSize(s32 arg0) {
    if (arg0 == -1) {
        return 0;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        return func_801096D4(arg0 + 0xC6);
    case MAPDATA_SOURCE_MAP_I_STATIC:
        return func_80109A98(arg0);
    case 2:
        return 0;
    default:
        return 0;
    }
}

void func_80109D40(s32 arg0, s32* arg1, s32* arg2) {
    if (arg0 == -1) {
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        func_801095AC(arg0 + 0xC6, arg1, arg2);
        return;
    case MAPDATA_SOURCE_MAP_I_STATIC:
        func_8010997C(arg0, arg1, arg2);
        return;
    case 2:
    default:
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
}

void func_80109DD8(s32 arg0, s32* arg1, s32* arg2) {
    s32 temp_v0;

    if (arg0 == -1) {
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        func_801095DC(arg0 + 0xC6, arg1, arg2);
        return;
    case MAPDATA_SOURCE_MAP_I_STATIC:
        func_801099AC(arg0, arg1, arg2);
        return;
    case 2:
    default:
        *arg2 = 0;
        *arg1 = 0;
        return;
    }
}

void func_80109E70(s32 arg0, s32* arg1) {
    if (arg0 == -1) {
        *arg1 = 0;
        return;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        func_8010960C(arg0 + 0xC6, arg1);
        return;
    case MAPDATA_SOURCE_MAP_I_STATIC:
        func_801099DC(arg0, arg1);
        return;
    case 2:
    default:
        *arg1 = 0;
        return;
    }
}

u8 func_80109EF8(s32 arg0) {
    if (arg0 == -1) {
        return 0;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        return func_80109630(arg0 + 0xC6);
    case MAPDATA_SOURCE_MAP_I_STATIC:
        return func_80109A00(arg0);
    case 2:
    default:
        return 0;
    }
}

s16 func_80109F78(s32 arg0) {
    if (arg0 == -1) {
        return 0;
    }
    switch (func_80109BF4(arg0)) {
    case 0:
        return func_80109650(arg0 + 0xC6);
    case MAPDATA_SOURCE_MAP_I_STATIC:
        return func_80109A20(arg0);
    case 2:
    default:
        return 0;
    }
}
