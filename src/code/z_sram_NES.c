#include "global.h"
#include "overlays/gamestates/ovl_file_choose/z_file_choose.h"

#define CHECK_NEWF(newf)                                                                                 \
    ((newf)[0] != 'Z' || (newf)[1] != 'E' || (newf)[2] != 'L' || (newf)[3] != 'D' || (newf)[4] != 'A' || \
     (newf)[5] != '3')

#define CHECK2_NEWF(newf)                                                                                 \
    ((newf)[0] == 'Z' && (newf)[1] == 'E' && (newf)[2] == 'L' && (newf)[3] == 'D' && (newf)[4] == 'A' && \
     (newf)[5] == '3')


s32 D_801C5FC0 = 0xC00;
s32 D_801C5FC4 = 0;
s32 D_801C5FC8 = 0;
s32 D_801C5FCC = 0x40000000;

s32 D_801C5FD0[448] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0xC04,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x100000,
    0,
    0,
    0x40000002,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x4000000,
    0,
    0,
    0,
    2,
    0,
    0,
    0,
    0x4000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0xF,
    0,
    0,
    0,
    0x70B000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0,
    0x1A00020,
    0,
    0,
    0,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0x1000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2,
    0,
    0,
    0,
    0x40000000,
    0,
    0,
    0,
    0,
    0x10,
    0,
    0,
    0,
    3,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0x100400,
    0,
    0,
    0x22,
    0x400,
    0,
    0,
    0x80,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2,
    0,
    0,
    0,
    0x80000002,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80000000,
    0xC00,
    0,
    0,
    0x40000000,
    0x102,
    0,
    0,
    0x400,
    0,
    0,
    0,
    2,
    0,
    0,
    0,
    0x40000000,
    0x70,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x40000000,
    0,
    0,
    0,
    0x40000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x100000,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x400,
    0,
    0,
    0,
    0x400,
    0,
    0,
    0,
    0x100000,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0x100,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0x80,
    0,
    0,
    0,
    0x80,
    0,
    0,
    0,
    0x80000000,
    0,
    0,
    0,
    0x400,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    2,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x400,
    0x100000,
    0,
    0,
    0x400,
    0,
    0,
    1,
    0,
};

u16 D_801C66D0[100] = {
    0xFFFC,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0,
    0,
    0,
    0xC000,
    0xC00,
    0,
    0xC0,
    0,
    0x300,
    0x3000,
    0xC000,
    0xC00,
    0,
    0,
    0,
    0,
    0,
    0,
    0xC00C,
    0xC00C,
    0xC008,
    3,
    0x3000,
    0,
    0,
    0,
    0xFF00,
    0xC3F,
    0x3F,
    0,
    0,
    0xCFFF,
    0,
    0,
    0xC00,
    0xC00,
    0,
    0xC0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0x3C,
    0x20,
    0,
    0x300C,
    0x3000,
    0,
    0xC,
    0xC0,
    0,
    0xFF0,
    0x300,
    0,
    0,
    0xC00,
    0,
    0,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xFFFF,
    0xC0,
    0,
    0xC000,
    0,
    3,
    0,
    0xC000,
    0,
    0xC0,
    0x300,
    0,
    0,
    0,
    0xC000,
    0xFFF0,
    0,
    0,
    0x300,
    0,
    0xC000,
    0xF0,
    0,
    0,
    0,
    0,
    0,
    0,
};

s32 D_801C6798[] = {
    0x00000020,
    0x00001470,
    0x000028C0,
    0x00003D10,
    0x00005160,
    0x000065B0,
};
u8 D_801C67B0[24] = {
    0xFF,
    1,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    6,
    7,
    8,
    9,
    0xA,
    0xFF,
    0xC,
    0xD,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
    0xFF,
};

s32 D_801C67C8[1] = {0};
s32 D_801C67CC[7] = {0x40, 0x80, 0xC0, 0x100, 0x180, 0x200, 0x280};

s32 D_801C67E8[] = {
    0x00000300,
    0x00000380,
};

s32 D_801C67F0[1] = {0x40};
s32 D_801C67F4[9] = {0x40, 0x40, 0x40, 0x80, 0x80, 0x80, 0x80, 1, 1};
s32 D_801C6818[8] = {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80};

s32 D_801C6838[] = {
0x00000001,
0x00000001,
};
s32 D_801C6840[4] = {0x100, 0x180, 0x200, 0x280};
s32 D_801C6850[8] = {0x80, 0x80, 0x80, 0x80, 0x300, 0x380, 1, 1};
s32 D_801C6870[8] = {0x100C, 0x100C, 0x100C, 0x100C, 0x3CA0, 0x3CA0, 0x3CA0, 0x3CA0};
u8 D_801C6890[8] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80};
s32 D_801C6898[] = {
    0x00000000,
    0x00000000,
    0x3E3E3E3E,
    0x3E3E3E3E,
    0x00300030,
    0x00300000,
    0x00000000,
    0x00000000,
    0xFF000000,
    0xFF000008,
};

//s32 D_801C68C0 = 0x4DFFFFFF;

s32 D_801C68C0[] = {
    0x4DFFFFFF,
    0x4DFFFFFF,
    0x4DFFFFFF,
    0xFDFFFFFF,
    0x00FFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0xFFFFFFFF,
    0x00110000,
};


Inventory gSaveDefaultInventory = {
    {
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
    },
    {
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
        0xFF,
    },
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    0x120000,
    0,
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {
        {0x15, 0x12, 0x17},
        {0x14, 0x3E, 0x3E},
        {0x3E, 0x3E, 0x15},
        {0x12, 0x17, 0x14},
        {0x3E, 0x3E, 0x3E},
        {0x3E, 0x15, 0x12},
        {0x17, 0x14, 0x3E},
        {0x3E, 0x3E, 0x3E},
    },
};
u16 gSaveDefaultChecksum = 0;



s32 D_801C6970[] = {
    0x5A454C44,
    0x41330000,
    0x15121714,
    0x3E3E3E3E,
    0x00800080,
    0x00300032,
    0x00640000,
    0x01000000,
    0xFF000000,
    0xFF000008,
};

s32 D_801C6998[] = {
    0x4D011300,
    0x4D013300,
    0x4D013400,
    0x09093200,
    0x00011300,
    0x000A2307,
    0x000C2907,
    0x00011D07,
    0x00110000,
};


Inventory D_801C69BC = {
    {
        0,
        1,
        2,
        3,
        4,
        0x28,
        6,
        7,
        8,
        9,
        0xA,
        0x2D,
        0xC,
        0xD,
        0xE,
        0xF,
        0x10,
        0x2F,
        0x12,
        0x13,
        0x14,
        0x15,
        0xFF,
        0xFF,
    },
    {
        0x3E,
        0x38,
        0x47,
        0x45,
        0x40,
        0x32,
        0x3A,
        0x46,
        0x39,
        0x42,
        0x48,
        0x33,
        0x3C,
        0x3D,
        0x37,
        0x3F,
        0x36,
        0x34,
        0x43,
        0x41,
        0x3B,
        0x44,
        0x49,
        0x35,
    },
    {
        1,
        0x1E,
        1,
        1,
        1,
        1,
        0x1E,
        0x1E,
        0x1E,
        0x1E,
        1,
        1,
        1,
        1,
        0x1E,
        1,
        1,
        1,
        1,
        1,
        1,
        1,
        0,
        0,
    },
    0x120009,
    0x105F7C0,
    {7, 7, 7, 7, 7, 7, 7, 7, 7, 7},
    {8, 8, 8, 8, 8, 8, 8, 8, 8, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {
        {0x15, 0x12, 0x17},
        {0x14, 0x3E, 0x3E},
        {0x3E, 0x3E, 0x15},
        {0x12, 0x17, 0x14},
        {0x3E, 0x3E, 0x3E},
        {0x3E, 0x15, 0x12},
        {0x17, 0x14, 0x3E},
        {0x3E, 0x3E, 0x3E},
    },
};
u16 D_801C6A44 = 0;
u8 D_801C6A48[8] = {0x35, 0x33, 0x34, 0x32, 0x35, 0, 0, 0};
u8 D_801C6A50[8] = {0x2F, 0x23, 0x29, 0x1D, 0x2F, 0, 0, 0};
s32 D_801C6A58[6] = {0x68B06A60, 0xB2309A80, 0xD8903E40, 0x864084A0, 0x2040AA30, 0};

u16 D_801F6AF0;
u8 D_801F6AF2;

void func_80143A10(u8 owlId) {
    gSaveContext.save.playerData.owlActivationFlags = ((void)0, gSaveContext.save.playerData.owlActivationFlags) | (u16)gBitFlags[owlId];
    if (gSaveContext.save.playerData.unk_20 == 0xFF) {
        gSaveContext.save.playerData.unk_20 = owlId;
    }
}

void func_80143A54(void) {
    gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF) | 0x130000;
    gSaveContext.save.roomInf[127][3] = (gSaveContext.save.roomInf[127][3] & 0xFFFF0000) | 0xA;
    gSaveContext.save.roomInf[127][4] = 0x1770;
    gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF0000) | 0x27;
    gSaveContext.save.roomInf[127][6] = (gSaveContext.save.roomInf[127][6] & 0xFFFF) | 0xA0000;
    gSaveContext.save.roomInf[123][0] = 0x1D4C;
    gSaveContext.save.roomInf[123][1] = 0x1D4C;
    gSaveContext.save.roomInf[123][2] = 0x1DB0;
}

void func_80143AC4(void) {
    gSaveContext.save.weekEventReg[55] &= 0xFD;
    gSaveContext.save.weekEventReg[90] &= 0xFE;
    gSaveContext.save.weekEventReg[89] &= 0xBF;
    gSaveContext.save.weekEventReg[89] &= 0xF7;
    gSaveContext.save.weekEventReg[85] &= 0x7F;
}

#if 0
void func_80143B0C(GameState* gameState) {
    SaveContext* temp_s0_5;
    s16 temp_s0;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_s1;
    s32 temp_s1_2;
    s32 temp_s1_3;
    u16 temp_a0;
    u16 temp_a3;
    u16 temp_t8;
    u32 temp_a2_2;
    u32 temp_a2_3;
    u32 temp_a2_4;
    u32 temp_a2_5;
    u32 temp_s0_2;
    u32 temp_s0_3;
    u32 temp_t4_2;
    u32 temp_t6_2;
    u32 temp_v0_10;
    u32 temp_v0_2;
    u32 temp_v0_3;
    u32 temp_v0_4;
    u32* temp_a2;
    u32* temp_v1;
    u32* temp_v1_2;
    u8 temp_a1_3;
    u8 temp_a1_4;
    u8 temp_t0;
    u8 temp_t1;
    u8 temp_t4;
    u8 temp_t6;
    u8 temp_t8_2;
    u8 temp_v0_5;
    u8 temp_v0_6;
    u8 temp_v0_7;
    u8 temp_v0_8;
    u8 temp_v0_9;
    u8 temp_v1_3;
    u8 temp_v1_4;
    u8 temp_v1_5;
    u8 temp_v1_6;
    u8 temp_v1_7;
    u8 temp_v1_8;
    void* temp_s0_4;
    void* temp_v0;
    void* temp_v0_11;
    void* temp_v0_12;
    ?* phi_a0;
    u32* phi_v1;
    u32* phi_a2;
    u32* phi_v1_2;
    u32* phi_a2_2;
    SaveContext* phi_s0;
    u32 phi_v1_3;
    s32 phi_s1;
    s32 phi_a1;
    SaveContext* phi_s0_2;
    u8* phi_a0_2;
    s32 phi_a1_2;
    void* phi_s0_3;
    s32 phi_s1_2;
    u8 phi_v0;
    u8 phi_v0_2;
    u8 phi_v0_3;
    u8 phi_v0_4;
    u8 phi_v0_5;
    u32 phi_v0_6;
    s32 phi_a1_3;
    u32 phi_a2_3;
    s32 phi_a1_4;
    u32 phi_a2_4;
    s32 phi_s1_3;
    u8 phi_v0_7;
    u8 phi_v1_4;
    u8 phi_v0_8;
    SaveContext* phi_s0_4;
    u16* phi_a3;
    u8 phi_a0_3;
    u8 phi_a0_4;
    u8 phi_v0_9;

    gSaveContext.save.daySpeed = 0;
    temp_t8 = gSaveContext.save.playerData.deaths + 1;
    gSaveContext.save.daysElapsed = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = 0x3FFF;
    gSaveContext.save.playerData.deaths = temp_t8;
    if ((temp_t8 & 0xFFFF) >= 0x3E8) {
        gSaveContext.save.playerData.deaths = 0x3E7;
    }
    temp_s0 = convert_scene_number_among_shared_scenes(gameState->unk_A4);
    func_80169D40((GlobalContext* ) gameState);
    temp_v0 = (temp_s0 * 0x10) + &D_801C5FC0;
    gameState->unk_1E68 = (s32) (gameState->unk_1E68 & temp_v0->unk_8);
    gameState->unk_1E58 = (s32) (gameState->unk_1E58 & temp_v0->unk_0);
    gameState->unk_1E5C = (s32) (gameState->unk_1E5C & temp_v0->unk_4);
    gameState->unk_1E6C = 0;
    gameState->unk_1E74 = (s32) (gameState->unk_1E74 & temp_v0->unk_C);
    gSaveContext.cycleSceneFlags[0][1] = (u32) (D_801C5FC0 & gSaveContext.cycleSceneFlags[0][1]);
    gSaveContext.cycleSceneFlags[0][2] = (u32) (D_801C5FC4 & gSaveContext.cycleSceneFlags[0][2]);
    *gSaveContext.cycleSceneFlags = (s32) (D_801C5FC8 & *gSaveContext.cycleSceneFlags);
    gSaveContext.cycleSceneFlags[0][4] = (u32) (D_801C5FCC & gSaveContext.cycleSceneFlags[0][4]);
    gSaveContext.cycleSceneFlags[0][3] = 0U;
    gSaveContext.save.roomInf[0][5] = 0U;
    gSaveContext.save.roomInf[0][6] = 0U;
    phi_a0 = &D_801C5FD0;
    phi_v1 = &gSaveContext.save.daySpeed;
    phi_a2 = &gSaveContext.save.daysElapsed;
    do {
        phi_v1->unk_3F6C = (s32) (phi_a0->unk_0 & phi_v1->unk_3F6C);
        phi_v1->unk_3F70 = (s32) (phi_a0->unk_4 & phi_v1->unk_3F70);
        phi_v1->unk_3F74 = 0;
        phi_v1->unk_3F68 = (s32) (phi_a0->unk_8 & phi_v1->unk_3F68);
        phi_v1->unk_3F78 = (s32) (phi_a0->unk_C & phi_v1->unk_3F78);
        phi_a2->unk_10C = 0;
        phi_a2->unk_110 = 0;
        phi_v1->unk_3F80 = (s32) (phi_a0->unk_10 & phi_v1->unk_3F80);
        phi_v1->unk_3F84 = (s32) (phi_a0->unk_14 & phi_v1->unk_3F84);
        phi_v1->unk_3F88 = 0;
        phi_v1->unk_3F7C = (s32) (phi_a0->unk_18 & phi_v1->unk_3F7C);
        temp_a2 = phi_a2 + 0x38;
        phi_v1->unk_3F8C = (s32) (phi_a0->unk_1C & phi_v1->unk_3F8C);
        temp_a2->unk_F4 = 0;
        temp_a2->unk_F0 = 0;
        temp_v1 = phi_v1 + 0x28;
        phi_a0 += 0x20;
        phi_v1 = temp_v1;
        phi_a2 = temp_a2;
        phi_v1_2 = temp_v1;
        phi_a2_2 = temp_a2;
    } while (temp_a2 != &gSaveContext.save.roomInf[104][1]);
    if ((u32) temp_a2 < (u32) &gSaveContext.save.roomInf[111][1]) {
        do {
            temp_a2_2 = phi_a2_2 + 0x1C;
            temp_v1_2 = phi_v1_2 + 0x14;
            temp_v1_2->unk_3F54 = 0;
            temp_v1_2->unk_3F58 = 0;
            temp_v1_2->unk_3F5C = 0;
            temp_v1_2->unk_3F60 = 0;
            temp_v1_2->unk_3F64 = 0;
            phi_v1_2 = temp_v1_2;
            phi_a2_2 = (u32* ) temp_a2_2;
        } while (temp_a2_2 < (u32) &gSaveContext.save.roomInf[111][1]);
    }
    phi_s0 = &gSaveContext;
    do {
        temp_s0_2 = phi_s0 + 1;
        temp_s0_2->unk_48C9 = 0;
        phi_s0 = (SaveContext* ) temp_s0_2;
    } while (temp_s0_2 < (u32) (&gSaveContext + 0x1B));
    if ((gSaveContext.unk_F4C & 0x20) != 0) {
        func_801149A0(0x35, (s16) gItemSlots[0x35]);
    }
    phi_a1 = 0;
    phi_a1_2 = 0;
    phi_a1_3 = 0;
    phi_a1_4 = 0;
    phi_a3 = &D_801C66D0;
    do {
        phi_v1_3 = (u32) *phi_a3;
        phi_s1 = 0;
loop_13:
        if ((phi_v1_3 & 3) == 0) {
            gSaveContext.save.weekEventReg[phi_a1] &= *(&D_801C6890 + phi_s1) ^ 0xFF;
        }
        temp_v0_2 = (phi_v1_3 >> 2) & 0xFFFF;
        if ((temp_v0_2 & 3) == 0) {
            gSaveContext.save.weekEventReg[phi_a1] &= (&D_801C6890 + phi_s1)->unk_1 ^ 0xFF;
        }
        temp_v0_3 = (temp_v0_2 >> 2) & 0xFFFF;
        if ((temp_v0_3 & 3) == 0) {
            gSaveContext.save.weekEventReg[phi_a1] &= (&D_801C6890 + phi_s1)->unk_2 ^ 0xFF;
        }
        temp_v0_4 = (temp_v0_3 >> 2) & 0xFFFF;
        if ((temp_v0_4 & 3) == 0) {
            gSaveContext.save.weekEventReg[phi_a1] &= (&D_801C6890 + phi_s1)->unk_3 ^ 0xFF;
        }
        temp_s1 = phi_s1 + 4;
        phi_v1_3 = (temp_v0_4 >> 2) & 0xFFFF;
        phi_s1 = temp_s1;
        if (temp_s1 != 8) {
            goto loop_13;
        }
        temp_a1 = phi_a1 + 1;
        phi_a1 = temp_a1;
        phi_a3 += 2;
    } while (temp_a1 < 0x64);
    phi_s0_2 = &gSaveContext;
    do {
        temp_s0_3 = phi_s0_2 + 1;
        temp_s0_3->unk_100B = 0;
        phi_s0_2 = (SaveContext* ) temp_s0_3;
    } while (temp_s0_3 < (u32) &gSaveContext.save.cutscene);
    temp_t4 = gSaveContext.unk_1013 & 0xFE;
    temp_t6 = temp_t4 & 0xFD;
    gSaveContext.unk_1013 = temp_t4;
    temp_t8_2 = temp_t6 & 0xFB;
    gSaveContext.unk_1013 = temp_t6;
    temp_t0 = temp_t8_2 & 0xF7;
    gSaveContext.unk_1013 = temp_t8_2;
    gSaveContext.unk_1013 = temp_t0;
    temp_t1 = temp_t0 & 0xEF;
    gSaveContext.unk_1013 = temp_t1;
    if (gSaveContext.save.playerData.rupees != 0) {
        gSaveContext.unk_1013 = (u8) (temp_t1 | 1);
    }
    temp_v0_5 = gSaveContext.save.inventory.items[gItemSlots[6]];
    phi_a0_2 = &D_801C67B0;
    if ((temp_v0_5 == 6) && (gSaveContext.save.inventory.ammo[gItemSlots[temp_v0_5 & 0xFF]] != 0)) {
        gSaveContext.unk_1013 = (u8) (gSaveContext.unk_1013 | 2);
    }
    temp_v0_6 = gSaveContext.save.inventory.items[gItemSlots[9]];
    phi_s0_3 = &gSaveContext + 0x12;
    if ((temp_v0_6 == 9) && (gSaveContext.save.inventory.ammo[gItemSlots[temp_v0_6 & 0xFF]] != 0)) {
        gSaveContext.unk_1013 = (u8) (gSaveContext.unk_1013 | 4);
    }
    temp_v0_7 = gSaveContext.save.inventory.items[gItemSlots[8]];
    if ((temp_v0_7 == 8) && (gSaveContext.save.inventory.ammo[gItemSlots[temp_v0_7 & 0xFF]] != 0)) {
        gSaveContext.unk_1013 = (u8) (gSaveContext.unk_1013 | 8);
    }
    temp_v0_8 = gSaveContext.save.inventory.items[gItemSlots[1]];
    if ((temp_v0_8 == 1) && (gSaveContext.save.inventory.ammo[gItemSlots[temp_v0_8 & 0xFF]] != 0)) {
        gSaveContext.unk_1013 = (u8) (gSaveContext.unk_1013 | 0x10);
    }
    do {
        if (*phi_a0_2 != 0xFF) {
            temp_v0_9 = gSaveContext.save.inventory.items[phi_a1_2];
            if ((temp_v0_9 != 0xFF) && (phi_a1_2 != 0xD)) {
                gSaveContext.save.inventory.ammo[gItemSlots[temp_v0_9 & 0xFF]] = 0;
            }
        }
        temp_a1_2 = phi_a1_2 + 1;
        phi_a0_2 += 1;
        phi_a1_2 = temp_a1_2;
    } while (temp_a1_2 < 0x18);
    do {
        temp_a1_3 = phi_s0_3->unk_70;
        if ((s32) temp_a1_3 >= 0x13) {
            phi_s1_2 = 1;
            if ((s32) temp_a1_3 < 0x28) {
                do {
                    if (phi_s1_2 == 0) {
                        temp_v1_3 = gSaveContext.save.playerForm;
                        phi_a0_3 = temp_v1_3;
                        if (temp_v1_3 == 4) {
                            phi_a0_3 = 0U;
                        }
                        phi_v0 = (&gSaveContext + (phi_a0_3 * 4) + phi_s1_2)->unk_4C;
                    } else {
                        phi_v0 = gSaveContext.save.equips.buttonItems[0][phi_s1_2];
                    }
                    if ((phi_v0 & 0xFF) == phi_s0_3->unk_70) {
                        if (phi_s1_2 == 0) {
                            temp_v1_4 = gSaveContext.save.playerForm;
                            phi_v0_2 = temp_v1_4;
                            if (temp_v1_4 == 4) {
                                phi_v0_2 = 0U;
                            }
                            (&gSaveContext + (phi_v0_2 * 4) + phi_s1_2)->unk_4C = 0x12U;
                        } else {
                            gSaveContext.save.equips.buttonItems[0][phi_s1_2] = 0x12;
                        }
                        func_80112B40((GlobalContext* ) gameState, phi_s1_2 & 0xFF);
                    }
                    temp_s1_2 = phi_s1_2 + 1;
                    phi_s1_2 = temp_s1_2;
                } while (temp_s1_2 != 4);
                phi_s0_3->unk_70 = 0x12U;
            }
        }
        temp_s0_4 = phi_s0_3 + 1;
        phi_s0_3 = temp_s0_4;
    } while ((u32) temp_s0_4 < (u32) &gSaveContext.save.day);
    gSaveContext.save.inventory.questItems &= -1 - *(gBitFlags + 0x64);
    if ((s32) gSaveContext.save.playerData.health < 0x30) {
        gSaveContext.save.playerData.health = 0x30;
    }
    temp_a0 = gSaveContext.save.equips.equipment;
    temp_a1_4 = *gEquipShifts;
    if (((s32) (temp_a0 & *gEquipMasks) >> temp_a1_4) < 3) {
        temp_a3 = *gEquipNegMasks;
        temp_v1_5 = gSaveContext.save.playerForm;
        gSaveContext.save.equips.equipment = (1 << temp_a1_4) | (temp_a0 & temp_a3);
        if (temp_v1_5 == 4) {
            phi_v0_3 = 0U;
        } else {
            phi_v0_3 = temp_v1_5;
        }
        if (phi_v0_3 == 0) {
            temp_a2_3 = gSaveContext.save.roomInf[126][5];
            if (((u32) ((u32) (temp_a2_3 & 0xFF000000) >> 0x18) >= 0x4FU) || ((u32) ((u32) (temp_a2_3 & 0xFF0000) >> 0x10) >= 0x4FU)) {
                phi_v0_5 = temp_v1_5;
                if (temp_v1_5 == 4) {
                    phi_v0_5 = 0U;
                }
                gSaveContext.save.equips.buttonItems[phi_v0_5] = 0x4F;
                gSaveContext.save.equips.equipment = (3 << temp_a1_4) | (gSaveContext.save.equips.equipment & temp_a3);
            } else {
                phi_v0_4 = temp_v1_5;
                if (temp_v1_5 == 4) {
                    phi_v0_4 = 0U;
                }
                gSaveContext.save.equips.buttonItems[phi_v0_4] = 0x4D;
            }
        } else {
            temp_a2_4 = gSaveContext.save.roomInf[126][5];
            if (((u32) ((u32) (temp_a2_4 & 0xFF000000) >> 0x18) >= 0x4FU) || ((u32) ((u32) (temp_a2_4 & 0xFF0000) >> 0x10) >= 0x4FU)) {
                gSaveContext.save.equips.buttonItems = 0x4F;
                gSaveContext.save.equips.equipment = (3 << temp_a1_4) | (gSaveContext.save.equips.equipment & temp_a3);
            } else {
                gSaveContext.save.equips.buttonItems = 0x4D;
            }
        }
    }
    temp_a2_5 = gSaveContext.save.roomInf[126][5];
    temp_v0_10 = (u32) (temp_a2_5 & 0xFF000000) >> 0x18;
    phi_v0_6 = temp_v0_10;
    if ((temp_v0_10 == 0x10U) || (((u32) (temp_a2_5 & 0xFF0000) >> 0x10) == 0x10U)) {
        gSaveContext.save.inventory.items[gItemSlots[0x10]] = 0x10;
        phi_v0_6 = (u32) (gSaveContext.save.roomInf[126][5] & 0xFF000000) >> 0x18;
    }
    phi_a2_3 = gSaveContext.save.roomInf[126][5];
    if (phi_v0_6 == 0x12U) {
loop_85:
        temp_v0_11 = &gSaveContext + gItemSlots[0x12] + phi_a1_3;
        if (temp_v0_11->unk_70 == 0xFF) {
            temp_v0_11->unk_70 = 0x12U;
            phi_a2_3 = gSaveContext.save.roomInf[126][5];
        } else {
            temp_a1_5 = phi_a1_3 + 1;
            phi_a1_3 = temp_a1_5;
            if (temp_a1_5 != 6) {
                goto loop_85;
            }
        }
    }
    phi_a2_4 = phi_a2_3;
    if (((u32) (phi_a2_3 & 0xFF0000) >> 0x10) == 0x12U) {
loop_90:
        temp_v0_12 = &gSaveContext + gItemSlots[0x12] + phi_a1_4;
        if (temp_v0_12->unk_70 == 0xFF) {
            temp_v0_12->unk_70 = 0x12U;
            phi_a2_4 = gSaveContext.save.roomInf[126][5];
        } else {
            temp_a1_6 = phi_a1_4 + 1;
            phi_a1_4 = temp_a1_6;
            if (temp_a1_6 != 6) {
                goto loop_90;
            }
        }
    }
    temp_t6_2 = phi_a2_4 & 0xFFFFFF;
    gSaveContext.save.roomInf[126][5] = temp_t6_2;
    gSaveContext.save.roomInf[126][5] = temp_t6_2 & 0xFF00FFFF;
    func_801149A0(5, 5);
    func_801149A0(0xB, 0xB);
    func_801149A0(0x11, 0x11);
    phi_s1_3 = 1;
    do {
        if (phi_s1_3 == 0) {
            temp_v1_6 = gSaveContext.save.playerForm;
            phi_a0_4 = temp_v1_6;
            if (temp_v1_6 == 4) {
                phi_a0_4 = 0U;
            }
            phi_v0_7 = (&gSaveContext + (phi_a0_4 * 4) + phi_s1_3)->unk_4C;
        } else {
            phi_v0_7 = gSaveContext.save.equips.buttonItems[0][phi_s1_3];
        }
        if ((phi_v0_7 & 0xFF) >= 0x28) {
            if (phi_s1_3 == 0) {
                temp_v1_7 = gSaveContext.save.playerForm;
                phi_v0_9 = temp_v1_7;
                if (temp_v1_7 == 4) {
                    phi_v0_9 = 0U;
                }
                phi_v1_4 = (&gSaveContext + (phi_v0_9 * 4) + phi_s1_3)->unk_4C;
            } else {
                phi_v1_4 = gSaveContext.save.equips.buttonItems[0][phi_s1_3];
            }
            if ((phi_v1_4 & 0xFF) < 0x31) {
                if (phi_s1_3 == 0) {
                    temp_v1_8 = gSaveContext.save.playerForm;
                    phi_v0_8 = temp_v1_8;
                    if (temp_v1_8 == 4) {
                        phi_v0_8 = 0U;
                    }
                    (&gSaveContext + (phi_v0_8 * 4) + phi_s1_3)->unk_4C = 0xFFU;
                } else {
                    gSaveContext.save.equips.buttonItems[0][phi_s1_3] = 0xFF;
                }
                func_80112B40((GlobalContext* ) gameState, phi_s1_3 & 0xFF);
            }
        }
        temp_s1_3 = phi_s1_3 + 1;
        phi_s1_3 = temp_s1_3;
    } while (temp_s1_3 != 4);
    gSaveContext.save.roomInf[126][1] = 0;
    temp_t4_2 = gSaveContext.save.roomInf[126][0] & 0xFFFF;
    gSaveContext.save.roomInf[126][0] = temp_t4_2;
    gSaveContext.save.roomInf[126][0] = temp_t4_2 & 0xFFFF0000;
    gSaveContext.save.roomInf[124][0] = 0;
    gSaveContext.save.roomInf[124][1] = 0;
    gSaveContext.save.roomInf[124][2] = 0;
    gSaveContext.save.roomInf[124][3] = 0;
    gSaveContext.save.roomInf[124][4] = 0;
    gSaveContext.save.roomInf[124][5] = 0;
    gSaveContext.save.roomInf[124][6] = 0;
    func_80143A54();
    phi_s0_4 = &gSaveContext;
    do {
        temp_s0_5 = phi_s0_4 + 4;
        temp_s0_5->unk_BF = (s8) (phi_s0_4->unk_C3 & 0xFE);
        temp_s0_5->unk_BE = (s8) (phi_s0_4->unk_C2 & 0xFE);
        temp_s0_5->unk_BD = (s8) (phi_s0_4->unk_C1 & 0xFE);
        temp_s0_5->unk_C7 = 0;
        temp_s0_5->unk_D1 = 0;
        temp_s0_5->unk_C8 = 0;
        temp_s0_5->unk_D2 = 0;
        temp_s0_5->unk_C9 = 0;
        temp_s0_5->unk_D3 = 0;
        temp_s0_5->save.inventory.questItems = phi_s0_4->save.inventory.dungeonItems & 0xFE;
        temp_s0_5->unk_C6 = 0;
        temp_s0_5->unk_D0 = 0;
        phi_s0_4 = temp_s0_5;
    } while (temp_s0_5 != &gSaveContext.save.cutscene);
    gSaveContext.save.playerData.rupees = 0;
    gSaveContext.save.unk_F65 = 0;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
    gSaveContext.rupeeAccumulator = 0;
    func_800F3B2C(gameState);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80143B0C.s")
#endif

void Sram_IncrementDay(void) {
    if (CURRENT_DAY < 4) {
        gSaveContext.save.day++;
        gSaveContext.save.daysElapsed++;
    }

    gSaveContext.save.bombersCaughtNum = 0;
    gSaveContext.save.bombersCaughtOrder[0] = 0;
    gSaveContext.save.bombersCaughtOrder[1] = 0;
    gSaveContext.save.bombersCaughtOrder[2] = 0;
    gSaveContext.save.bombersCaughtOrder[3] = 0;
    gSaveContext.save.bombersCaughtOrder[4] = 0;
    gSaveContext.save.weekEventReg[0x49] &= (u8)~0x10;
    gSaveContext.save.weekEventReg[0x55] &= (u8)~0x02;
}

u16 Sram_CalcChecksum(void* data, size_t count) {
    u8* dataPtr = data;
    u16 chkSum = 0;

    while (count-- > 0) {
        chkSum += *dataPtr;
        dataPtr++;
    }
    return chkSum;
}

void func_80144628(void) {
    gSaveContext.save.entranceIndex = 0x1C00;
    gSaveContext.save.equippedMask = 0;
    gSaveContext.save.firstCycleFlag = 0;
    gSaveContext.save.unk_06 = 0;
    gSaveContext.save.linkAge = 0;
    gSaveContext.save.isNight = false;
    gSaveContext.save.daySpeed = 0;
    gSaveContext.save.snowheadCleared = 0;
    gSaveContext.save.hasTatl = false;
    gSaveContext.save.isOwlSave = false;

    // Instead of bloating all save context accesses with an extra sub-struct, the size of the would-be sub-struct
    // is calculated manually
    bzero(&gSaveContext.save.playerData, sizeof(Save) - OFFSETOF(Save, playerData));
}

void Sram_GenerateRandomSaveFields(void) {
    s32 randBombers;
    s16 sp2A;
    s16 phi_v1_2;
    s16 i;
    s16 j;
    s32 k;
    s16 randSpiderHouse;

    func_80143A54();

    gSaveContext.save.lotteryCodes[0][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[0][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[1][2] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][0] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][1] = Rand_S16Offset(0, 10);
    gSaveContext.save.lotteryCodes[2][2] = Rand_S16Offset(0, 10);

    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {

        }
    }

    i = 0;
    sp2A = Rand_S16Offset(0, 16) & 3;
    k = 6;
    while (i != k) {
        randSpiderHouse = Rand_S16Offset(0, 16) & 3;
        if (sp2A != randSpiderHouse) {
            gSaveContext.save.spiderHouseMaskOrder[i] = randSpiderHouse;
            i++;
            sp2A = randSpiderHouse;
        }
    }

    do {
        randBombers = Rand_S16Offset(0, 6);
    } while (randBombers <= 0 || randBombers >= 6);

    gSaveContext.save.bomberCode[0] = randBombers;

    i = 1;
    while (i != 5) {
        k = false;

        do {
            randBombers = Rand_S16Offset(0, 6);
        } while (randBombers <= 0 || randBombers >= 6);

        sp2A = 0;
        do {
            if (randBombers == gSaveContext.save.bomberCode[sp2A]) {
                k = true;
            }
            sp2A++;
        }while (sp2A < i);

        if (k == false) {
            gSaveContext.save.bomberCode[i] = randBombers;
            i++;
        }
    }
}

void func_80144890(void) {
    gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
    gSaveContext.save.daysElapsed = 0;
    gSaveContext.save.day = 0;
    gSaveContext.save.time = CLOCK_TIME(6, 0)-1;
    func_80144628();

    Lib_MemCpy(&gSaveContext.save.playerData, &D_801C6898, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &D_801C68C0, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &gSaveDefaultInventory, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &gSaveDefaultChecksum, sizeof(gSaveContext.save.checksum));

    gSaveContext.save.horseData.scene = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.angle = -0x7554;

    gSaveContext.nextCutsceneIndex = 0;
    gSaveContext.save.playerData.magicLevel = 0;
    Sram_GenerateRandomSaveFields();
}

void Sram_InitDebugSave(void) {
    func_80144628();

    Lib_MemCpy(&gSaveContext.save.playerData, &D_801C6970, sizeof(SavePlayerData));
    Lib_MemCpy(&gSaveContext.save.equips, &D_801C6998, sizeof(ItemEquips));
    Lib_MemCpy(&gSaveContext.save.inventory, &D_801C69BC, sizeof(Inventory));
    Lib_MemCpy(&gSaveContext.save.checksum, &D_801C6A44, sizeof(gSaveContext.save.checksum));

    if (gSaveContext.save.playerForm != PLAYER_FORM_HUMAN) {
        gSaveContext.save.equips.buttonItems[0][2] = D_801C6A48[((void)0, gSaveContext.save.playerForm & 0xFF)];
        gSaveContext.save.equips.cButtonSlots[0][2] = D_801C6A50[((void)0, gSaveContext.save.playerForm & 0xFF)];
    }

    gSaveContext.save.hasTatl = true;

    gSaveContext.save.horseData.scene = SCENE_F01;
    gSaveContext.save.horseData.pos.x = -1420;
    gSaveContext.save.horseData.pos.y = 257;
    gSaveContext.save.horseData.pos.z = -1285;
    gSaveContext.save.horseData.angle = -0x7554;

    gSaveContext.save.entranceIndex = 0x1C00;
    gSaveContext.save.firstCycleFlag = 1;

    gSaveContext.save.weekEventReg[0x0F] |= 0x20;
    gSaveContext.save.weekEventReg[0x3B] |= 0x04;
    gSaveContext.save.weekEventReg[0x1F] |= 0x04;

    gSaveContext.cycleSceneFlags[99][1] = 1;
    gSaveContext.save.roomInf[99][1] = 1;
    gSaveContext.save.playerData.magicLevel = 0;

    Sram_GenerateRandomSaveFields();
}

void func_80144A94(SramContext* sramCtx) {
    s32 i;
    s32 cutscene = gSaveContext.save.cutscene;

    bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));

    if (func_80185968(*sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]) !=
        0) {
        func_80185968(*sramCtx->saveBuf, D_801C67CC[gSaveContext.fileNum * 2], D_801C67F4[gSaveContext.fileNum * 2]);
    }
    Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));
    if (CHECK_NEWF(gSaveContext.save.playerData.newf)) {
        func_80185968(*sramCtx->saveBuf, D_801C67CC[gSaveContext.fileNum * 2], D_801C67F4[gSaveContext.fileNum * 2]);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }
    gSaveContext.save.cutscene = cutscene;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
        gSaveContext.eventInf[i] = 0;
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.cycleSceneFlags[i][0] = gSaveContext.save.roomInf[i][0];
        gSaveContext.cycleSceneFlags[i][1] = gSaveContext.save.roomInf[i][1];
        gSaveContext.cycleSceneFlags[i][2] = gSaveContext.save.roomInf[i][2];
        gSaveContext.cycleSceneFlags[i][3] = gSaveContext.save.roomInf[i][3];
        gSaveContext.cycleSceneFlags[i][4] = gSaveContext.save.roomInf[i][4];
    }

    for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3DD0); i++) {
        gSaveContext.unk_3DD0[i] = 0;
        gSaveContext.unk_3DE0[i] = 0;
        gSaveContext.unk_3E18[i] = 0;
        gSaveContext.unk_3E50[i] = 0;
        gSaveContext.unk_3E88[i] = 0;
        gSaveContext.unk_3EC0[i] = 0;
    }

    D_801BDAA0 = 1;
    D_801BDA9C = 0;
    gSaveContext.powderKegTimer = 0;
    gSaveContext.unk_1014 = 0;
    gSaveContext.jinxTimer = 0;
}

#ifdef NON_EQUIVALENT
void func_80144E78(GameState* gameState, SramContext* sramCtx) {
    s32 i;
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    s32 phi_t1 = 0;
    s32 pad1[3];

    if (gSaveContext.unk_3F3F) {
        bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));

        if (gSaveContext.fileNum == 0xFF) {
            func_80185968(*sramCtx->saveBuf, D_801C67C8[0], D_801C67F0[0]);
        } else if (fileChooseCtx->unk_2446A[gSaveContext.fileNum] != 0) {
            phi_t1 = gSaveContext.fileNum + 2;

            if (func_80185968(*sramCtx->saveBuf, D_801C67C8[phi_t1 * 2], D_801C67F0[phi_t1 * 2]) != 0) {
                func_80185968(*sramCtx->saveBuf, D_801C67C8[phi_t1 * 2 + 1], D_801C67F0[phi_t1 * 2 + 1]);
            }
        } else {
            phi_t1 = gSaveContext.fileNum;

            if (func_80185968(*sramCtx->saveBuf, D_801C67C8[phi_t1 * 2], D_801C67F0[phi_t1 * 2]) != 0) {
                func_80185968(*sramCtx->saveBuf, D_801C67C8[phi_t1 * 2 + 1], D_801C67F0[phi_t1 * 2 + 1]);
            }
        }

        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[phi_t1 * 2]);

        if (CHECK_NEWF(gSaveContext.save.playerData.newf)) {
            func_80185968(*sramCtx->saveBuf, D_801C67CC[phi_t1 * 2], D_801C67F4[phi_t1 * 2]);
            Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, D_801C6870[phi_t1 * 2]);
        }
    }

    gSaveContext.save.playerData.magicLevel = 0;

    if (!gSaveContext.save.isOwlSave) {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.eventInf); i++) {
            gSaveContext.eventInf[i] = 0;
        }

        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.cycleSceneFlags[i][0] = gSaveContext.save.roomInf[i][0];
            gSaveContext.cycleSceneFlags[i][1] = gSaveContext.save.roomInf[i][1];
            gSaveContext.cycleSceneFlags[i][2] = gSaveContext.save.roomInf[i][2];
            gSaveContext.cycleSceneFlags[i][3] = gSaveContext.save.roomInf[i][3];
            gSaveContext.cycleSceneFlags[i][4] = gSaveContext.save.roomInf[i][4];
        }

        for (i = 0; i < ARRAY_COUNT(gSaveContext.unk_3DD0); i++) {
            gSaveContext.unk_3DD0[i] = 0;
            gSaveContext.unk_3DE0[i] = 0;
            gSaveContext.unk_3E18[i] = 0;
            gSaveContext.unk_3E50[i] = 0;
            gSaveContext.unk_3E88[i] = 0;
            gSaveContext.unk_3EC0[i] = 0;
        }

        if (gSaveContext.save.firstCycleFlag != 0) {
            gSaveContext.save.entranceIndex = 0xD800;
            gSaveContext.save.day = 0;
            gSaveContext.save.time = 0x3FFF;
        } else {
            gSaveContext.save.entranceIndex = 0x1C00;
            gSaveContext.nextCutsceneIndex = 0;
            gSaveContext.save.playerForm = PLAYER_FORM_HUMAN;
        }
    } else {
        gSaveContext.save.entranceIndex = D_801C6A58[gSaveContext.save.owlSaveLocation];
        if (D_801C6A58[gSaveContext.save.owlSaveLocation] == 0x84A0 && (gSaveContext.save.weekEventReg[20] & 0x02)) {
            gSaveContext.save.entranceIndex = 0xCA0;
        } else if (D_801C6A58[gSaveContext.save.owlSaveLocation] == 0x9A80 && (gSaveContext.save.weekEventReg[33] & 0x80)) {
            gSaveContext.save.entranceIndex = 0xAE80;
        }

        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.cycleSceneFlags[i][0] = gSaveContext.save.roomInf[i][0];
            gSaveContext.cycleSceneFlags[i][1] = gSaveContext.save.roomInf[i][1];
            gSaveContext.cycleSceneFlags[i][2] = gSaveContext.save.roomInf[i][2];
            gSaveContext.cycleSceneFlags[i][3] = gSaveContext.save.roomInf[i][3];
            gSaveContext.cycleSceneFlags[i][4] = gSaveContext.save.roomInf[i][4];
        }

        if (gSaveContext.save.unk_F65) {
            Lib_MemCpy(D_801D88A0, gSaveContext.save.scarecrowsSong, sizeof(gSaveContext.save.scarecrowsSong));

            for (i = 0; i != ARRAY_COUNT(gSaveContext.save.scarecrowsSong); i++) {
            }
        }

        func_80170D2C(sramCtx, gSaveContext.fileNum);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80144E78.s")
#endif

void func_8014546C(SramContext* sramCtx) {
    s32 i;

    if (gSaveContext.save.isOwlSave) {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
            gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
            gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
            gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
            gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, OFFSETOF(SaveContext, fileNum));

        Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, OFFSETOF(SaveContext, fileNum));
    } else {
        for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
            gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
            gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
            gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
            gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
            gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
        }

        gSaveContext.save.checksum = 0;
        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));

        if (gSaveContext.unk_3F3F) {
            Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, sizeof(Save));
            Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));
        }
    }
}

/**
 * Save permanent scene flags, calculate checksum, copy save context to the save buffer
 */
void func_80145698(SramContext* sramCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(gSaveContext.cycleSceneFlags); i++) {
        gSaveContext.save.roomInf[i][0] = gSaveContext.cycleSceneFlags[i][0];
        gSaveContext.save.roomInf[i][1] = gSaveContext.cycleSceneFlags[i][1];
        gSaveContext.save.roomInf[i][2] = gSaveContext.cycleSceneFlags[i][2];
        gSaveContext.save.roomInf[i][3] = gSaveContext.cycleSceneFlags[i][3];
        gSaveContext.save.roomInf[i][4] = gSaveContext.cycleSceneFlags[i][4];
    }

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));
    if (gSaveContext.unk_3F3F != 0) {
        Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, sizeof(Save));
        Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));
    }
}

#if 0
void func_801457CC(GameState* gameState, SramContext* sramCtx) {
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    u16 sp7A;
    u16 sp76;
    s16 sp74;
    u16 sp6E;
    s32 sp64;
    s32* sp60;
    s32* sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    void* sp40;
    s16 temp_s3_3;
    s32 temp_v1_2;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 temp_v1_9;
    s32* temp_a3;
    s32* temp_s3_2;
    s32* temp_s4_2;
    s32* temp_t0;
    u16 temp_s2;
    u16 temp_s2_2;
    u16 temp_s2_3;
    u16 temp_s2_4;
    u16 temp_s7;
    u16 temp_s7_2;
    u16 temp_s7_3;
    u16 temp_s7_4;
    u16 temp_t7;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u32* temp_fp;
    u32* temp_fp_2;
    u32* temp_fp_3;
    u8 temp_v0;
    u8 temp_v1;
    u8 temp_v1_5;
    void* temp_s3;
    void* temp_s4;
    void* temp_t2;
    void* temp_t2_2;
    void* temp_t6;
    void* temp_t6_2;
    void* temp_t8;
    void* temp_t8_2;
    void* temp_t8_3;
    s32 phi_v1;
    s32 phi_s3;
    s32 phi_s2;
    s32 phi_s2_2;
    s32 phi_v1_2;
    s32 phi_v1_3;
    s32 phi_v0;
    s32 phi_v1_4;
    s8 phi_a0;
    u16 phi_v1_5;
    u16 phi_s2_3;
    u16 phi_v1_6;
    s32 phi_s2_4;
    s32 phi_v1_7;
    s32 phi_v1_8;
    s32 phi_v0_2;
    s32 phi_v1_9;
    s8 phi_a0_2;
    u16 phi_v1_10;
    u32* phi_fp;
    u16 phi_s2_5;
    u16 phi_v1_11;
    s8 phi_a0_3;
    s8 phi_a0_4;

    temp_v0 = gSaveContext.unk_3F3F;
    phi_v1 = 0;
    phi_v1_2 = 0;
    phi_v1_3 = 0;
    phi_v1_4 = 0;
    phi_v1_7 = 0;
    phi_v1_8 = 0;
    phi_v1_9 = 0;
    if (temp_v0 != 0) {
        sp74 = 0;
        sp76 = 0;
        D_801F6AF0 = gSaveContext.save.time;
        D_801F6AF2 = temp_v0;
        phi_s3 = 0;
        do {
            sp50 = phi_v1;
            sp6E = 0;
            bzero((void* ) sramCtx->saveBuf, 0x4000);
            temp_a3 = &D_801C67C8[phi_s3];
            temp_t0 = &D_801C67F0[phi_s3];
            sp5C = temp_t0;
            sp60 = temp_a3;
            sp64 = phi_s3 * 4;
            phi_s2 = 0;
            phi_s2_2 = 0;
            phi_s2_4 = 0;
            if (func_80185968((void* ) sramCtx->saveBuf, *temp_a3, *temp_t0) != 0) {
                sp6E = 1;
                sp50 = phi_v1;
                if (func_80185968((void* ) sramCtx->saveBuf, D_801C67CC[phi_s3], D_801C67F4[phi_s3]) != 0) {
                    phi_s2 = 1;
                }
            }
            sp58 = phi_s3;
            if (phi_v1 < 2) {
                //temp_t2 = gamestate + sp76;
                //temp_t2->unk_24468 = 0;
                fileChooseCtx->unk_24468[sp76] = 0;
                //sp40 = temp_t2 + 0x20000;
                sp54 = sp58 * 4;
                if (phi_s2 != 0) {
                    bzero((void* ) sramCtx->saveBuf, 0x4000);
                    Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, *(D_801C6870 + sp64));
                } else {
                    //temp_fp = sp64 + D_801C6870;
                    Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                    temp_s2 = gSaveContext.save.checksum;
                    gSaveContext.save.checksum = 0;
                    temp_v0_2 = Sram_CalcChecksum((void* ) &gSaveContext, D_801C6870[sp64]);
                    //temp_v1 = (u8) gSaveContext.save.playerData.newf;
                    gSaveContext.save.checksum = temp_s2;
                    if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s2 != (temp_v0_2 & 0xFFFF))) {
                        sp6E = 1;
                        if ((gSaveContext.save.playerData.newf[0] == 0x5A) && (gSaveContext.save.playerData.newf[1] == 0x45)) {

                        }
                        if (func_80185968((void* ) sramCtx->saveBuf, D_801C67C8[sp54 + 1], D_801C67F0[sp54 + 1]) != 0) {
                            phi_s2_2 = 1;
                        }
                        Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                        temp_s7 = gSaveContext.save.checksum;
                        gSaveContext.save.checksum = 0;
                        if ((phi_s2_2 != 0) || CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s7 != Sram_CalcChecksum((void* ) &gSaveContext, D_801C6870[sp64]))) {
                            bzero((void* ) sramCtx->saveBuf, 0x4000);
                            Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, 0x100CU);
                            sp6E = 0x3E7;
                        }
                    }
                }

                gSaveContext.save.checksum = 0;
                gSaveContext.save.checksum = Sram_CalcChecksum((void* ) &gSaveContext, *(D_801C6870 + sp54));
                do {
                    temp_v1_2 = (phi_v1_2 + 1) & 0xFFFF;
                    //(gamestate + (sp76 * 6) + phi_v1_2)->unk_243F4 = (u8) gSaveContext.save.playerData.newf[phi_v1_2];
                    fileChooseCtx->newf[sp76][phi_v1_2] = gSaveContext.save.playerData.newf[phi_v1_2];
                    phi_v1_2 = temp_v1_2;
                    phi_v1_5 = (u16) temp_v1_2;
                } while (temp_v1_2 < 6);
                //temp_t8 = gamestate + (sp76 * 6);
                // if ((temp_t8->unk_243F4 == 0x5A) && (temp_t8->unk_243F5 == 0x45) && (temp_t8->unk_243F6 == 0x4C) && (temp_t8->unk_243F7 == 0x44) && (temp_t8->unk_243F8 == 0x41) && (temp_t8->unk_243F9 == 0x33)) {
                if (CHECK2_NEWF(gSaveContext.save.playerData.newf)) {
                    //temp_t8_2 = gamestate + (sp76 * 2);
                    //temp_t8_2->unk_2440C = (u16) gSaveContext.save.playerData.deaths;
                    fileChooseCtx->unk_2440C[sp76] = gSaveContext.save.playerData.deaths;
                    phi_a0_3 = 0;
                    do {
                        temp_v1_3 = (phi_v1_3 + 1) & 0xFFFF;
                        //(gamestate + (sp76 * 8) + phi_v1_3)->unk_24414 = (u8) gSaveContext.save.playerData.playerName[phi_v1_3];
                        fileChooseCtx->unk_24414[sp76][phi_v1_3] = gSaveContext.save.playerData.playerName[phi_v1_3];
                        phi_v1_3 = temp_v1_3;
                    } while (temp_v1_3 < 8);
                    //temp_t8_2->unk_24434 = (s16) gSaveContext.save.playerData.healthCapacity;
                    //temp_t8_2->unk_2443C = (s16) gSaveContext.save.playerData.health;
                    //sp40->unk_4454 = (s8) gSaveContext.unk_D3;
                    //(gamestate + (sp76 * 4))->unk_24444 = (u32) gSaveContext.save.inventory.questItems;
                    //temp_t8_2->unk_24458 = (u16) gSaveContext.save.time;
                    //temp_t8_2->unk_24460 = (s16) gSaveContext.save.day;
                    //sp40->unk_4468 = (u8) gSaveContext.save.isOwlSave;
                    //temp_t8_2->unk_2446C = (s16) gSaveContext.save.playerData.rupees;
                    //sp40->unk_4474 = (s8) ((u32) (gSaveContext.save.inventory.upgrades & *(gUpgradeMasks + 0x10)) >> gUpgradeShifts[4]);

                    fileChooseCtx->unk_24438[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.healthCapacity;
                    fileChooseCtx->unk_24440[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.health;
                    fileChooseCtx->unk_24456[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.dungeonKeys[9];
                    fileChooseCtx->unk_2444C[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.questItems;
                    fileChooseCtx->unk_2445C[fileChooseCtx->unk_244A6] = gSaveContext.save.time;
                    fileChooseCtx->unk_24464[fileChooseCtx->unk_244A6] = gSaveContext.save.day;
                    fileChooseCtx->unk_2446A[fileChooseCtx->unk_244A6] = gSaveContext.save.isOwlSave;
                    fileChooseCtx->unk_24470[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.rupees;
                    fileChooseCtx->unk_24476[fileChooseCtx->unk_244A6] =
                        (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

                    phi_v0 = 0;
                    do {
                        temp_v1_4 = (phi_v1_4 + 1) & 0xFFFF;
                        phi_v1_4 = temp_v1_4;
                        phi_a0 = phi_a0_3;
                        phi_v1_5 = (u16) temp_v1_4;
                        if (gSaveContext.save.inventory.masks[phi_v0] != 0xFF) {
                            phi_a0 = (phi_a0_3 + 1) & 0xFFFF;
                        }
                        phi_v0 = temp_v1_4;
                        phi_a0_3 = phi_a0;
                    } while (temp_v1_4 < 0x18);
                    //sp40->unk_4478 = phi_a0;
                    fileChooseCtx->unk_24478[0] = phi_a0;
                    //sp40->unk_447C = (s8) ((u32) (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                    fileChooseCtx->unk_2447C[0] = (s8) ((u32) (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                }
                if (sp6E == 1) {
                    Lib_MemCpy(sramCtx->saveBuf + 0x2000, (void* ) &gSaveContext, 0x100CU);
                    func_80146EBC(sramCtx, *sp60, *(D_801C6818 + sp64));
                } else if (sp6E == 0) {
                    temp_s7_2 = gSaveContext.save.checksum;
                    sp7A = phi_v1_5;
                    phi_v1_6 = phi_v1_5;
                    if (func_80185968((void* ) sramCtx->saveBuf, *(D_801C67CC + sp54), *(D_801C67F4 + sp54)) != 0) {
                        phi_s2_3 = 1U;
                    } else {
                        Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, 0x100CU);
                        temp_s2_2 = gSaveContext.save.checksum;
                        gSaveContext.save.checksum = 0;
                        phi_s2_3 = temp_s2_2;
                        phi_v1_6 = Sram_CalcChecksum((void* ) &gSaveContext, 0x100CU) & 0xFFFF;
                    }
                    //if (((u8) gSaveContext.save.playerData.newf != 0x5A) || (gSaveContext.unk_25 != 0x45) || (gSaveContext.unk_26 != 0x4C) || (gSaveContext.unk_27 != 0x44) || (gSaveContext.unk_28 != 0x41) || (gSaveContext.unk_29 != 0x33) || (phi_s2_3 != phi_v1_6) || (phi_s2_3 != temp_s7_2)) {
                    if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (phi_s2_3 != phi_v1_6) || (phi_s2_3 != temp_s7_2)) {
                        func_80185968((void* ) sramCtx->saveBuf, *sp60, *sp5C);
                        Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, 0x100CU);
                        Lib_MemCpy(sramCtx->saveBuf + 0x2000, (void* ) &gSaveContext, 0x100CU);
                        func_80146EBC(sramCtx, *sp60, *(D_801C6818 + sp64));
                    }
                }
            } else if (phi_v1 < 4) {
                //temp_t8_3 = gamestate + sp76;
                //temp_t8_3->unk_24468 = 0;
                fileChooseCtx->unk_24468[sp76] = 0;
                //temp_t2_2 = gamestate + (phi_v1 * 6);
                sp54 = sp58 * 4;
                //sp40 = temp_t8_3 + 0x20000;
                //if ((temp_t2_2->unk_243E8 == 0x5A) && (temp_t2_2->unk_243E9 == 0x45) && (temp_t2_2->unk_243EA == 0x4C) && (temp_t2_2->unk_243EB == 0x44) && (temp_t2_2->unk_243EC == 0x41) && (temp_t2_2->unk_243ED == 0x33)) {
                if (CHECK2_NEWF(gSaveContext.save.playerData.newf)) {
                    if (phi_s2 != 0) {
                        bzero((void* ) sramCtx->saveBuf, 0x4000);
                        //temp_fp_2 = sp64 + D_801C6870;
                        Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                        //phi_fp = temp_fp_2;
                    } else {
                        //temp_fp_3 = sp64 + D_801C6870;
                        Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                        temp_s2_3 = gSaveContext.save.checksum;
                        gSaveContext.save.checksum = 0;
                        temp_v0_3 = Sram_CalcChecksum((void* ) &gSaveContext, D_801C6870[sp64]);
                        //temp_v1_5 = (u8) gSaveContext.save.playerData.newf;
                        gSaveContext.save.checksum = temp_s2_3;
                        //phi_fp = temp_fp_3;
                        if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s2_3 != (temp_v0_3 & 0xFFFF))) {
                            sp6E = 1;
                            if ((gSaveContext.save.playerData.newf[0] == 0x5A) && (gSaveContext.save.playerData.newf[1] == 0x45)) {

                            }
                            if (func_80185968((void* ) sramCtx->saveBuf, D_801C67C8[sp54+1], D_801C67F0[sp54+1]) != 0) {
                                phi_s2_4 = 1;
                            }
                            Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                            temp_s7_3 = gSaveContext.save.checksum;
                            gSaveContext.save.checksum = 0;
                            if ((phi_s2_4 != 0) || CHECK_NEWF(gSaveContext.save.playerData.newf) || (temp_s7_3 != Sram_CalcChecksum((void* ) &gSaveContext, D_801C6870[sp64]))) {
                                bzero((void* ) sramCtx->saveBuf, 0x4000);
                                Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                                sp6E = 0x3E7;
                            }
                        }
                    }
                    gSaveContext.save.checksum = 0;
                    gSaveContext.save.checksum = Sram_CalcChecksum((void* ) &gSaveContext, *(D_801C6870 + sp54));
                    do {
                        temp_v1_6 = (phi_v1_7 + 1) & 0xFFFF;
                        //(gamestate + (sp76 * 6) + phi_v1_7)->unk_243F4 = (u8) gSaveContext.save.playerData.newf[phi_v1_7];
                        fileChooseCtx->newf[sp76][phi_v1_7] = gSaveContext.save.playerData.newf[phi_v1_7];
                        phi_v1_7 = temp_v1_6;
                        phi_v1_10 = (u16) temp_v1_6;
                    } while (temp_v1_6 < 6);
                    //temp_t6 = gamestate + (sp76 * 6);
                    //if ((temp_t6->unk_243F4 == 0x5A) && (temp_t6->unk_243F5 == 0x45) && (temp_t6->unk_243F6 == 0x4C) && (temp_t6->unk_243F7 == 0x44) && (temp_t6->unk_243F8 == 0x41) && (temp_t6->unk_243F9 == 0x33)) {
                    if (CHECK2_NEWF(gSaveContext.save.playerData.newf)) {
                        //temp_t6_2 = gamestate + (sp76 * 2);
                        //temp_t6_2->unk_2440C = (u16) gSaveContext.save.playerData.deaths;
                        fileChooseCtx->unk_2440C[sp76] = gSaveContext.save.playerData.deaths;
                        phi_a0_4 = 0;
                        do {
                            temp_v1_7 = (phi_v1_8 + 1) & 0xFFFF;
                            //(gamestate + (sp76 * 8) + phi_v1_8)->unk_24414 = (u8) gSaveContext.save.playerData.playerName[phi_v1_8];
                            fileChooseCtx->unk_24414[sp76][phi_v1_8] = gSaveContext.save.playerData.playerName[phi_v1_8];
                            phi_v1_8 = temp_v1_7;
                        } while (temp_v1_7 < 8);
                        //temp_t6_2->unk_24434 = (s16) gSaveContext.save.playerData.healthCapacity;
                        //temp_t6_2->unk_2443C = (s16) gSaveContext.save.playerData.health;
                        //sp40->unk_4454 = (s8) gSaveContext.unk_D3;
                        //(gamestate + (sp76 * 4))->unk_24444 = (u32) gSaveContext.save.inventory.questItems;
                        //temp_t6_2->unk_24458 = (u16) gSaveContext.save.time;
                        //temp_t6_2->unk_24460 = (s16) gSaveContext.save.day;
                        //sp40->unk_4468 = (u8) gSaveContext.save.isOwlSave;
                        //temp_t6_2->unk_2446C = (s16) gSaveContext.save.playerData.rupees;
                        //sp40->unk_4474 = (s8) ((u32) (gSaveContext.save.inventory.upgrades & *(gUpgradeMasks + 0x10)) >> gUpgradeShifts[4]);

                        fileChooseCtx->unk_24438[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.healthCapacity;
                        fileChooseCtx->unk_24440[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.health;
                        fileChooseCtx->unk_24456[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.dungeonKeys[9];
                        fileChooseCtx->unk_2444C[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.questItems;
                        fileChooseCtx->unk_2445C[fileChooseCtx->unk_244A6] = gSaveContext.save.time;
                        fileChooseCtx->unk_24464[fileChooseCtx->unk_244A6] = gSaveContext.save.day;
                        fileChooseCtx->unk_2446A[fileChooseCtx->unk_244A6] = gSaveContext.save.isOwlSave;
                        fileChooseCtx->unk_24470[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.rupees;
                        fileChooseCtx->unk_24476[fileChooseCtx->unk_244A6] =
                            (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

                        phi_v0_2 = 0;
                        do {
                            temp_v1_8 = (phi_v1_9 + 1) & 0xFFFF;
                            phi_v1_9 = temp_v1_8;
                            phi_a0_2 = phi_a0_4;
                            phi_v1_10 = (u16) temp_v1_8;
                            if (gSaveContext.save.inventory.masks[phi_v0_2] != 0xFF) {
                                phi_a0_2 = (phi_a0_4 + 1) & 0xFFFF;
                            }
                            phi_v0_2 = temp_v1_8;
                            phi_a0_4 = phi_a0_2;
                        } while (temp_v1_8 < 0x18);
                        //sp40->unk_4478 = phi_a0_2;
                        fileChooseCtx->unk_24478[0] = phi_a0_2;
                        //sp40->unk_447C = (s8) ((u32) (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                        fileChooseCtx->unk_2447C[0] = (s8) ((u32) (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C);
                    }

                    if (sp6E == 1) {
                        func_80146EBC(sramCtx, *sp60, *sp5C);
                        func_80146EBC(sramCtx, D_801C67C8[sp54+1], D_801C67F0[sp54+1]);
                    } else if (sp6E == 0) {
                        temp_s7_4 = gSaveContext.save.checksum;
                        sp7A = phi_v1_10;
                        phi_v1_11 = phi_v1_10;
                        if (func_80185968(*sramCtx->saveBuf, D_801C67C8[sp54+1], D_801C67F0[sp54+1]) != 0) {
                            phi_s2_5 = 1U;
                        } else {
                            Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                            temp_s2_4 = gSaveContext.save.checksum;
                            gSaveContext.save.checksum = 0;
                            phi_s2_5 = temp_s2_4;
                            phi_v1_11 = Sram_CalcChecksum((void* ) &gSaveContext, D_801C6870[sp64]) & 0xFFFF;
                        }
                        //if (((u8) gSaveContext.save.playerData.newf != 0x5A) || (gSaveContext.unk_25 != 0x45) || (gSaveContext.unk_26 != 0x4C) || (gSaveContext.unk_27 != 0x44) || (gSaveContext.unk_28 != 0x41) || (gSaveContext.unk_29 != 0x33) || (phi_s2_5 != phi_v1_11) || (phi_s2_5 != temp_s7_4)) {
                        if (CHECK_NEWF(gSaveContext.save.playerData.newf) || (phi_s2_5 != phi_v1_11) || (phi_s2_5 != temp_s7_4)) {
                            func_80185968((void* ) sramCtx->saveBuf, *sp60, *sp5C);
                            Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, D_801C6870[sp64]);
                            func_80146EBC(sramCtx, *sp60, *sp5C);
                            func_80146EBC(sramCtx, D_801C67C8[sp54+1], D_801C67F0[sp54+1]);
                        }
                    }
                } else {
                    bzero((void* ) sramCtx->saveBuf, 0x4000);
                    Lib_MemCpy((void* ) &gSaveContext, (void* ) sramCtx->saveBuf, *(D_801C6870 + sp64));
                    func_80146EBC(sramCtx, *sp60, *sp5C);
                    func_80146EBC(sramCtx, D_801C67C8[sp58+1], D_801C67F0[sp58+1]);
                }
            } else {
                if (phi_s2 != 0) {
                    gSaveContext.optionId = 0xA51D;
                    gSaveContext.language = 1;
                    gSaveContext.audioSetting = 0;
                    gSaveContext.languageSetting = 0;
                    goto block_122;
                }
                Lib_MemCpy((void* ) &gSaveContext.optionId, (void* ) sramCtx->saveBuf, 6U);
                if (gSaveContext.optionId != 0xA51D) {
                    gSaveContext.optionId = 0xA51D;
                    gSaveContext.language = 1;
                    gSaveContext.audioSetting = 0;
                    gSaveContext.languageSetting = 0;
block_122:
                    gSaveContext.zTargetSetting = 0;
                }
                func_801A3D98(gSaveContext.audioSetting);
            }
            temp_t7 = sp76 + 1;
            temp_v1_9 = temp_t7 & 0xFFFF;
            temp_s3_3 = (sp58 + 2) & 0xFFFF;
            sp76 = temp_t7;
            phi_v1 = temp_v1_9;
            phi_s3 = (s32) temp_s3_3;
        } while (temp_v1_9 < 5);
        sp74 = temp_s3_3;
        gSaveContext.save.time = D_801F6AF0;
        gSaveContext.unk_3F3F = D_801F6AF2;
    }
    gSaveContext.language = 1;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_801457CC.s")
#endif

void func_80146580(GameState* gameState, SramContext* sramCtx, s32 fileNum) {
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    s32 pad;

    if (gSaveContext.unk_3F3F) {
        if (fileChooseCtx->unk_2446A[fileNum]) {
            func_80147314(sramCtx, fileNum);
            fileChooseCtx->unk_2446A[fileNum] = 0;
        }
        bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, sizeof(Save));
    }
    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}


#ifdef NON_MATCHING
// v0/v1
void func_80146628(GameState* gameState, SramContext* sramCtx) {
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    u16 i;
    s16 maskCount;

    if (gSaveContext.unk_3F3F) {
        if (fileChooseCtx->unk_2446A[fileChooseCtx->unk_2448E]) {
            func_80147414(sramCtx, fileChooseCtx->unk_2448E, fileChooseCtx->unk_244A6);
            fileChooseCtx->unk_24410[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.deaths;

            for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.playerName); i++) {
                fileChooseCtx->unk_24424[fileChooseCtx->unk_244A6][i] = gSaveContext.save.playerData.playerName[i];
            }

            fileChooseCtx->unk_24438[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.healthCapacity;
            fileChooseCtx->unk_24440[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.health;
            fileChooseCtx->unk_24456[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.dungeonKeys[9];
            fileChooseCtx->unk_2444C[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.questItems;
            fileChooseCtx->unk_2445C[fileChooseCtx->unk_244A6] = gSaveContext.save.time;
            fileChooseCtx->unk_24464[fileChooseCtx->unk_244A6] = gSaveContext.save.day;
            fileChooseCtx->unk_2446A[fileChooseCtx->unk_244A6] = gSaveContext.save.isOwlSave;
            fileChooseCtx->unk_24470[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.rupees;
            fileChooseCtx->unk_24476[fileChooseCtx->unk_244A6] =
                (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

            for (maskCount = i = 0; i < ARRAY_COUNT(gSaveContext.save.inventory.masks); i++) {
                if (gSaveContext.save.inventory.masks[(s32)i] != 0xFF) {
                    maskCount++;
                }
            }

            fileChooseCtx->unk_2447A[fileChooseCtx->unk_244A6] = maskCount;
            fileChooseCtx->unk_2447E[fileChooseCtx->unk_244A6] =
                (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
        }

        // clear buffer
        bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));
        // read to buffer
        func_80185968(*sramCtx->saveBuf, D_801C67C8[fileChooseCtx->unk_2448E * 2],
                      D_801C67F0[fileChooseCtx->unk_2448E * 2]);

        if (1) {}
        func_80185968(&(*sramCtx->saveBuf)[0x2000], D_801C67CC[fileChooseCtx->unk_2448E * 2],
                      D_801C67F4[fileChooseCtx->unk_2448E * 2]);
        if (1) {}

        // copy buffer to save context
        Lib_MemCpy(&gSaveContext.save, sramCtx->saveBuf, sizeof(Save));

        fileChooseCtx->unk_2440C[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.deaths;

        for (i = 0; i < ARRAY_COUNT(gSaveContext.save.playerData.playerName); i++) {
            fileChooseCtx->unk_24414[fileChooseCtx->unk_244A6][i] = gSaveContext.save.playerData.playerName[i];
        }

        fileChooseCtx->healthCapacity[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.healthCapacity;
        fileChooseCtx->health[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.health;
        fileChooseCtx->unk_24454[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.dungeonKeys[9];
        fileChooseCtx->unk_24444[fileChooseCtx->unk_244A6] = gSaveContext.save.inventory.questItems;
        fileChooseCtx->unk_24458[fileChooseCtx->unk_244A6] = gSaveContext.save.time;
        fileChooseCtx->unk_24460[fileChooseCtx->unk_244A6] = gSaveContext.save.day;
        fileChooseCtx->unk_24468[fileChooseCtx->unk_244A6] = gSaveContext.save.isOwlSave;
        fileChooseCtx->rupees[fileChooseCtx->unk_244A6] = gSaveContext.save.playerData.rupees;
        fileChooseCtx->unk_24474[fileChooseCtx->unk_244A6] =
            (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

        for (maskCount = i = 0; i < ARRAY_COUNT(gSaveContext.save.inventory.masks); i++) {
            if (gSaveContext.save.inventory.masks[(s32)i] != 0xFF) {
                maskCount++;
            }
        }

        fileChooseCtx->unk_24478[fileChooseCtx->unk_244A6] = maskCount;
        fileChooseCtx->unk_2447C[fileChooseCtx->unk_244A6] =
            (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
    }

    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_sram_NES/func_80146628.s")
#endif

void func_80146AA0(GameState* gameState, SramContext* sramCtx) {
    s32 phi_v0;
    u16 phi_v1;
    FileChooseContext* fileChooseCtx = (FileChooseContext*)gameState;
    s16 phi_a0;

    if (gSaveContext.unk_3F3F) {
        func_80144890();
        if (fileChooseCtx->unk_24480 == 0) {
            gSaveContext.save.cutscene = 0xFFF0;
        }

        for (phi_v0 = 0; phi_v0 != ARRAY_COUNT(gSaveContext.save.playerData.playerName); phi_v0++) {
            gSaveContext.save.playerData.playerName[phi_v0] =
                fileChooseCtx->unk_24414[fileChooseCtx->unk_24480][phi_v0];
        }

        gSaveContext.save.playerData.newf[0] = 'Z';
        gSaveContext.save.playerData.newf[1] = 'E';
        gSaveContext.save.playerData.newf[2] = 'L';
        gSaveContext.save.playerData.newf[3] = 'D';
        gSaveContext.save.playerData.newf[4] = 'A';
        gSaveContext.save.playerData.newf[5] = '3';

        gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, sizeof(Save));

        Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, sizeof(Save));
        Lib_MemCpy(&(*sramCtx->saveBuf)[0x2000], &gSaveContext, sizeof(Save));

        for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.save.playerData.newf); phi_v1++) {
            fileChooseCtx->newf[fileChooseCtx->unk_24480][phi_v1] = gSaveContext.save.playerData.newf[phi_v1];
        }

        fileChooseCtx->unk_2440C[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.deaths;

        for (phi_v1 = 0; phi_v1 < ARRAY_COUNT(gSaveContext.save.playerData.playerName); phi_v1++) {
            fileChooseCtx->unk_24414[fileChooseCtx->unk_24480][phi_v1] =
                gSaveContext.save.playerData.playerName[phi_v1];
        }

        fileChooseCtx->healthCapacity[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.healthCapacity;
        fileChooseCtx->health[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.health;
        fileChooseCtx->unk_24454[fileChooseCtx->unk_24480] = gSaveContext.save.inventory.dungeonKeys[9];
        fileChooseCtx->unk_24444[fileChooseCtx->unk_24480] = gSaveContext.save.inventory.questItems;
        fileChooseCtx->unk_24458[fileChooseCtx->unk_24480] = gSaveContext.save.time;
        fileChooseCtx->unk_24460[fileChooseCtx->unk_24480] = gSaveContext.save.day;
        fileChooseCtx->unk_24468[fileChooseCtx->unk_24480] = gSaveContext.save.isOwlSave;
        fileChooseCtx->rupees[fileChooseCtx->unk_24480] = gSaveContext.save.playerData.rupees;
        fileChooseCtx->unk_24474[fileChooseCtx->unk_24480] =
            (gSaveContext.save.inventory.upgrades & gUpgradeMasks[4]) >> gUpgradeShifts[4];

        for (phi_v1 = 0, phi_a0 = 0; phi_v1 < 24; phi_v1++) {
            if (gSaveContext.save.inventory.masks[(s32)phi_v1] != 0xFF) {
                phi_a0++;
            }
        }

        fileChooseCtx->unk_24478[fileChooseCtx->unk_24480] = phi_a0;
        fileChooseCtx->unk_2447C[fileChooseCtx->unk_24480] =
            (gSaveContext.save.inventory.questItems & 0xF0000000) >> 0x1C;
    }
    gSaveContext.save.time = D_801F6AF0;
    gSaveContext.unk_3F3F = D_801F6AF2;
}

void func_80146DF8(SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F) {
        gSaveContext.language = 1;
        Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext.optionId, 6);
    }
}

void func_80146E40(GameState* gameState, SramContext* sramCtx) {
    if (&gSaveContext.save) {}

    func_801A3D98(gSaveContext.audioSetting);
}

// Sram_Init
void Sram_Alloc(GameState* gamestate, SramContext* sramCtx) {
    if (gSaveContext.unk_3F3F != 0) {
        sramCtx->saveBuf = THA_AllocEndAlign16(&gamestate->heap, 0x4000);
        sramCtx->status = 0;
    }
}

/**
 * Synchronous flash write
 */
void func_80146EBC(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    func_80185F64(*sramCtx->saveBuf, curPage, numPages);
}


void func_80146EE8(GameState* gameState) {
    s32 pad;
    GlobalContext* globalCtx = (GlobalContext*)gameState;
    SramContext* sramCtx = &globalCtx->sramCtx;

    gSaveContext.save.firstCycleFlag = 1;
    gSaveContext.save.isOwlSave = false;
    func_80145698(sramCtx);
    func_80185F64(*sramCtx->saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C6818[gSaveContext.fileNum * 2]);
}

/**
 * Save the game
 */
void func_80146F5C(GameState* gameState) {
    s32 cutscene;
    s32 day;
    u16 time;
    GlobalContext* globalCtx = (GlobalContext*)gameState;

    cutscene = gSaveContext.save.cutscene;
    time = gSaveContext.save.time;
    day = gSaveContext.save.day;
    gSaveContext.save.weekEventReg[0x54] &= (u8)0xDF;

    func_80143B0C(gameState);
    func_8014546C(&globalCtx->sramCtx);

    gSaveContext.save.day = day;
    gSaveContext.save.time = time;
    gSaveContext.save.cutscene = cutscene;
    func_80185F64(globalCtx->sramCtx.saveBuf, D_801C67C8[gSaveContext.fileNum * 2], D_801C67F0[gSaveContext.fileNum * 2]);
}

void func_80147008(SramContext* sramCtx, u32 curPage, u32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    sramCtx->status = 1;
}

void func_80147020(SramContext* sramCtx) {
    // async flash write
    func_80185DDC(*sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);

    sramCtx->unk_18 = osGetTime();
    sramCtx->status = 2;
}

void func_80147068(SramContext* sramCtx) {
    if (sramCtx->status == 2) {
        if (func_80185EC4() != 0) { // if task running
            if (func_80185F04() == 0) { // wait for task done
                // task success
                sramCtx->status = 4;
            } else {
                // task failure
                sramCtx->status = 4;
            }
        }
    } else if (((osGetTime() - sramCtx->unk_18) * 0x40) / 3000 / 10000 >= 200) {
        sramCtx->status = 0;
    }
}

void func_80147138(SramContext* sramCtx, s32 curPage, s32 numPages) {
    sramCtx->curPage = curPage;
    sramCtx->numPages = numPages;
    sramCtx->status = 6;
}

void func_80147150(SramContext* sramCtx) {
    func_80185DDC(*sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);

    sramCtx->unk_18 = osGetTime();
    sramCtx->status = 7;
}

void func_80147198(SramContext* sramCtx) {
    if (sramCtx->status == 7) {
        if (func_80185EC4() != 0) { // Is task running
            if (func_80185F04() == 0) { // Wait for task done
                func_80185DDC(*sramCtx->saveBuf, sramCtx->curPage + 0x80, sramCtx->numPages);
                sramCtx->status = 8;
            } else {
                func_80185DDC(*sramCtx->saveBuf, sramCtx->curPage + 0x80, sramCtx->numPages);
                sramCtx->status = 8;
            }
        }
    } else if (sramCtx->status == 8) {
        if (func_80185EC4() != 0) { // Is task running
            if (func_80185F04() == 0) { // Wait for task done
                sramCtx->status = 4;
            } else {
                sramCtx->status = 4;
            }
        }
    } else if (((osGetTime() - sramCtx->unk_18) * 0x40) / 3000 / 10000 >= 200) {
        sramCtx->status = 0;
        bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));
        gSaveContext.save.isOwlSave = 0;
        gSaveContext.save.checksum = 0;
        // flash read to buffer then copy to save context
        func_80185968(*sramCtx->saveBuf, sramCtx->curPage, sramCtx->numPages);
        Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, OFFSETOF(SaveContext, fileNum));
    }
}

void func_80147314(SramContext* sramCtx, s32 fileNum) {
    s32 pad;

    gSaveContext.save.isOwlSave = false;

    gSaveContext.save.playerData.newf[0] = '\0';
    gSaveContext.save.playerData.newf[1] = '\0';
    gSaveContext.save.playerData.newf[2] = '\0';
    gSaveContext.save.playerData.newf[3] = '\0';
    gSaveContext.save.playerData.newf[4] = '\0';
    gSaveContext.save.playerData.newf[5] = '\0';

    gSaveContext.save.checksum = 0;
    gSaveContext.save.checksum = Sram_CalcChecksum(&gSaveContext, 0x3CA0);

    Lib_MemCpy(*sramCtx->saveBuf, &gSaveContext, 0x3CA0);
    func_80146EBC(sramCtx, D_801C6840[fileNum*2], D_801C6850[fileNum*2]);
    func_80146EBC(sramCtx, D_801C6840[fileNum*2+1], D_801C6850[fileNum*2]);

    gSaveContext.save.isOwlSave = true;

    gSaveContext.save.playerData.newf[0] = 'Z';
    gSaveContext.save.playerData.newf[1] = 'E';
    gSaveContext.save.playerData.newf[2] = 'L';
    gSaveContext.save.playerData.newf[3] = 'D';
    gSaveContext.save.playerData.newf[4] = 'A';
    gSaveContext.save.playerData.newf[5] = '3';
}

void func_80147414(SramContext* sramCtx, s32 fileNum, s32 arg2) {
    s32 pad;

    // Clear save buffer
    bzero(*sramCtx->saveBuf, sizeof(*sramCtx->saveBuf));

    // Read save file
    if (func_80185968(*sramCtx->saveBuf, D_801C6840[fileNum*2], D_801C6850[fileNum*2]) != 0) {
        // If failed, read backup save file
        func_80185968(*sramCtx->saveBuf, D_801C6840[fileNum*2+1], D_801C6850[fileNum*2+1]);
    }

    // Copy buffer to save context
    Lib_MemCpy(&gSaveContext, sramCtx->saveBuf, 0x3CA0);

    func_80146EBC(sramCtx, D_801C6840[arg2*2], D_801C6850[arg2*2]);
    func_80146EBC(sramCtx, D_801C6840[arg2*2+1], D_801C6850[arg2*2]);
}

void Sram_nop8014750C(s32 arg0) {
}
