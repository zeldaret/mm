#ifndef Z_EN_KNIGHT_H
#define Z_EN_KNIGHT_H

#include "global.h"

struct EnKnight;

typedef void (*EnKnightActionFunc)(struct EnKnight*, PlayState*);

typedef struct EnKnight {
    /* 0x000 */ Actor actor;
    /* 0x144 */ u16 unk_144;
    /* 0x146 */ s16 unk146;
    /* 0x148 */ u8 unk_148;
    /* 0x14A */ s16 unk14A[3];
    /* 0x150 */ char pad150[1];
    /* 0x151 */ u8 unk_151;
    /* 0x152 */ u8 unk152;
    /* 0x153 */ u8 unk_153;
    /* 0x154 */ u8 unk_154;
    /* 0x155 */ char pad155[1];
    /* 0x156 */ s16 unk156;
    /* 0x158 */ s16 unk158;
    /* 0x15A */ s16 unk15A;
    /* 0x15C */ s16 unk15C;
    /* 0x15E */ s16 unk15E;
    /* 0x160 */ s16 unk160;
    /* 0x162 */ u8 unk162;
    /* 0x164 */ Vec3f unk164;
    /* 0x170 */ s16 unk170;
    /* 0x172 */ s16 unk172;
    /* 0x174 */ s16 unk174;
    /* 0x176 */ s16 unk176;
    /* 0x178 */ s16 unk178;
    /* 0x17A */ s16 unk17A;
    /* 0x17C */ f32 unk17C;
    /* 0x180 */ f32 unk180;
    /* 0x184 */ s16 unk184;
    /* 0x186 */ s16 unk186;
    /* 0x188 */ s16 unk188;
    /* 0x18A */ s16 unk18A;
    /* 0x18C */ s16 unk18C;
    /* 0x18E */ s16 unk18E;
    /* 0x190 */ u8 unk190;
    /* 0x191 */ u8 unk191;
    /* 0x192 */ u8 unk192;
    /* 0x193 */ u8 unk193;
    /* 0x194 */ SkelAnime unk194;
    /* 0x1D8 */ f32 unk1D8;
    /* 0x1DC */ Vec3f unk1DC[15];
    /* 0x290 */ u8 unk290;
    /* 0x291 */ u8 unk291;
    /* 0x292 */ u8 unk292;
    /* 0x294 */ f32 unk294;
    /* 0x298 */ f32 unk298;
    /* 0x29C */ f32 unk29C;
    /* 0x2A0 */ u8 unk2A0;
    /* 0x2A1 */ u8 unk2A1;
    /* 0x2A2 */ s16 unk2A2;
    /* 0x2A4 */ f32 unk2A4;
    /* 0x2A8 */ f32 unk2A8;
    /* 0x2AC */ Vec3f unk2AC[2];
    /* 0x2C4 */ Vec3s unk2C4[29];
    /* 0x372 */ Vec3s unk372[29];
    /* 0x420 */ EnKnightActionFunc actionFunc;
    /* 0x424 */ EnKnightActionFunc unk424;
    /* 0x428 */ s16 unk428;
    /* 0x42C */ f32 unk42C;
    /* 0x430 */ f32 unk430;
    /* 0x434 */ Vec3f unk434;
    /* 0x440 */ Vec3f unk440;
    /* 0x44C */ u8 unk44C;
    /* 0x450 */ f32 unk450;
    /* 0x454 */ f32 unk454;
    /* 0x458 */ f32 unk458;
    /* 0x45C */ f32 unk45C;
    /* 0x460 */ f32 unk460;
    /* 0x464 */ f32 unk464;
    /* 0x468 */ f32 unk468;
    /* 0x46C */ f32 unk46C;
    /* 0x470 */ f32 unk470;
    /* 0x474 */ f32 unk474;
    /* 0x478 */ s16 unk478;
    /* 0x47C */ Vec3f unk47C;
    /* 0x488 */ ColliderCylinder unk488;
    /* 0x4D4 */ ColliderJntSph unk4D4;
    /* 0x4F4 */ ColliderJntSphElement unk4F4[1];
    /* 0x534 */ ColliderJntSph unk534;
    /* 0x554 */ ColliderJntSphElement unk554[1];
    /* 0x594 */ ColliderJntSph unk594;
    /* 0x5B4 */ ColliderJntSphElement unk5B4[2];
    /* 0x634 */ ColliderCylinder unk634;
    /* 0x680 */ u8 unk_680;
    /* 0x684 */ u32 unk684;
    /* 0x688 */ s16 unk688;
    /* 0x68A */ s16 unk_68A;
    /* 0x68C */ Vec3f unk68C;
    /* 0x698 */ Vec3f unk698;
    /* 0x6A4 */ f32 unk6A4;
    /* 0x6A8 */ char pad6A8[4];
    /* 0x6AC */ s16 unk6AC;
    /* 0x6B0 */ f32 unk6B0;
    /* 0x6B4 */ u16 unk6B4;
    /* 0x6B6 */ u16 unk6B6;
    /* 0x6B8 */ u16 unk6B8;
    /* 0x6BA */ char pad6BA[2];
    /* 0x6BC */ u16 unk6BC;
    /* 0x6BE */ u16 unk6BE;
    /* 0x6C0 */ u16 unk6C0;
    /* 0x6C2 */ u16 unk6C2;
    /* 0x6C4 */ u8 unk6C4;
    /* 0x6C8 */ Vec3f unk6C8;
} EnKnight; // size = 0x6D4

#endif // Z_EN_KNIGHT_H
