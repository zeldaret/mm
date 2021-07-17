#ifndef Z_EN_CLEAR_TAG_H
#define Z_EN_CLEAR_TAG_H

#include <global.h>

struct EnClearTag;

typedef struct EnClearTagUnknownEffect {
    /* 0x00 */ u8 unk_00;
    /* 0x01 */ u8 unk_01;
    /* 0x02 */ char unk_02[0x2];
    /* 0x04 */ Vec3f pos;
    /* 0x10 */ Vec3f vel;
    /* 0x1C */ Vec3f accel;
    /* 0x28 */ f32 unk_28; // Vec3f?
    /* 0x2C */ f32 unk_2C;
    /* 0x30 */ f32 unk_30;
    /* 0x34 */ f32 unk_34;
    /* 0x38 */ f32 unk_38; // Vec3f?
    /* 0x3C */ f32 unk_3C;
    /* 0x40 */ f32 unk_40;
    /* 0x44 */ char unk_44[0x4];
    /* 0x48 */ s16 unk_48;
    /* 0x4A */ s16 unk_4A;
    /* 0x4C */ s16 unk_4C;
    /* 0x4E */ s16 unk_4E;
    /* 0x50 */ f32 unk_50;
    /* 0x54 */ f32 unk_54;
    /* 0x58 */ f32 unk_58;
    /* 0x5C */ f32 unk_5C;
    /* 0x60 */ f32 unk_60;
    /* 0x64 */ f32 unk_64;
    /* 0x68 */ f32 unk_68;
    /* 0x6C */ f32 unk_6C;
} EnClearTagUnknownEffect; // size = 0x70

typedef struct EnClearTag {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ EnClearTagUnknownEffect unk_0144[103];
    /* 0x2E54 */ char unk_2E54[0x2];
    /* 0x2E56 */ s16 unk_2E56;
    /* 0x2E58 */ char unk_2E58[0xE];
    /* 0x2E66 */ u8 unk_2E66;
    /* 0x2E67 */ u8 unk_2E67;
    /* 0x2E68 */ u8 unk_2E68;
    /* 0x2E69 */ char unk_2E69[0x1B];
} EnClearTag; // size = 0x2E84

extern const ActorInit En_Clear_Tag_InitVars;

#endif // Z_EN_CLEAR_TAG_H
