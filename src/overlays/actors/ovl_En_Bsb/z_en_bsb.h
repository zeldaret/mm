#ifndef Z_EN_BSB_H
#define Z_EN_BSB_H

#include "global.h"

struct EnBsb;

typedef void (*EnBsbActionFunc)(struct EnBsb*, PlayState*);

typedef struct EnBsbUnkStruct {
    /* 0x00 */ u8 unk_00;
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f velocity;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ Vec3s rot;
    /* 0x30 */ f32 scale;
    /* 0x34 */ s16 unk_34;
} EnBsbUnkStruct; // size = 0x38

typedef struct EnBsb {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s unk_0188[21];
    /* 0x0206 */ Vec3s unk_0206[21];
    /* 0x0284 */ EnBsbActionFunc actionFunc;
    /* 0x0288 */ Path* unk_0288;
    /* 0x028C */ s32 unk_028C;
    /* 0x0290 */ u8 unk_0290;
    /* 0x0292 */ s16 unk_0292;
    /* 0x0294 */ s16 unk_0294;
    /* 0x0296 */ s16 unk_0296;
    /* 0x0298 */ Vec3f unk_0298;
    /* 0x02A4 */ s32 unk_02A4;
    /* 0x02A8 */ s32 unk_02A8;
    /* 0x02AC */ s16 unk_02AC;
    /* 0x02AE */ u8 unk_02AE;
    /* 0x02AF */ u8 unk_02AF;
    /* 0x02B0 */ s32 unk_02B0;
    /* 0x02B4 */ s16 unk_02B4;
    /* 0x02B6 */ s16 unk_02B6;
    /* 0x02B8 */ s16 unk_02B8;
    /* 0x02BA */ s16 unk_02BA;
    /* 0x02BC */ s16 unk_02BC;
    /* 0x02C0 */ f32 unk_02C0;
    /* 0x02C4 */ f32 unk_02C4;
    /* 0x02C8 */ s16 unk_02C8;
    /* 0x02CA */ s16 unk_02CA;
    /* 0x02CC */ s16 unk_02CC[5];
    /* 0x02D8 */ s32 unk_02D8;
    /* 0x02DC */ s32 unk_02DC;
    /* 0x02E0 */ Vec3f unk_02E0;
    /* 0x02EC */ Vec3f unk_02EC;
    /* 0x02F8 */ Vec3f unk_02F8;
    /* 0x0304 */ Vec3f unk_0304;
    /* 0x0310 */ Vec3s unk_0310;
    /* 0x0316 */ Vec3s unk_0316;
    /* 0x031C */ Vec3s unk_031C;
    /* 0x0322 */ s16 unk_0322;
    /* 0x0324 */ s16 unk_0324;
    /* 0x0328 */ f32 unk_0328;
    /* 0x032C */ f32 unk_032C;
    /* 0x0330 */ Vec3f unk_0330[17];
    /* 0x03FC */ s32 unk_03FC[17];
    /* 0x0440 */ s16 unk_0440;
    /* 0x0444 */ EnBsbUnkStruct unk_0444[50];
    /* 0x0F34 */ ColliderJntSph unk_0F34;
    /* 0x0F54 */ ColliderJntSphElement unk_0F54[7];
    /* 0x1114 */ u32 unk_1114;
    /* 0x1118 */ s16 unk_1118;
    /* 0x111A */ s16 unk_111A;
    /* 0x111C */ s16 unk_111C;
    /* 0x1120 */ f32 unk_1120;
    /* 0x1124 */ f32 unk_1124;
    /* 0x1128 */ Vec3f unk_1128;
    /* 0x1134 */ Vec3f unk_1134;
    /* 0x1140 */ Vec3f unk_1140;
    /* 0x114C */ Vec3f unk_114C;
} EnBsb; // size = 0x1158

#endif // Z_EN_BSB_H
