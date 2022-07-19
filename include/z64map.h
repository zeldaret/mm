#ifndef Z64_MAP_D_H
#define Z64_MAP_D_H
#include "ultra64.h"

/* z_map_data */

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 unk9;
    /* 0x0A */ s16 unkA;
} T_801BED4C; // size 0x0C?

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ s16 unk8;
} T_801BED88; // size 0x0A

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    u8 unk6;
    u8 unk7;
    s16 unk8;
} T_801BF170; // size 0x0A, ident to T_801BED88

/* z_map_disp */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x00 */ s16 unk2;
    /* 0x00 */ s16 unk4;
    /* 0x00 */ s16 unk6;
} T_801BEBB8_unk48;

typedef struct {
    /* 0x00 */ MinimapList* unk0; //unk0 -> sub1 -> s16[5]
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14; //unk4 same type as unk14
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s16 unk1C; //same as 0C
    /* 0x1E */ s16 unk1E; //same as 0E
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ char unk28[8];
    /* 0x30 */ s16 unk30; //scene minBounds.x
    /* 0x32 */ s16 unk32; //scene minBounds.z
    /* 0x34 */ s16 unk34; //scene boundsWidth.x
    /* 0x36 */ s16 unk36; //scene boundsWidth.z
    /* 0x38 */ s16 unk38; //scene boundsMidpoint.x
    /* 0x3A */ s16 unk3A; //scene boundsMidpoint.z
    /* 0x3C */ s16* unk3C;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ char unk42[2];
    /* 0x44 */ s16 unk44;
    /* 0x48 */ s16* unk48;
    /* 0x4C */ char unk4C[0x0C];
    /* 0x58 */ s16 unk58;
} T_801BEBB8;

typedef struct {
    /* 0x00 */ s16 unk0; //scene
    /* 0x02 */ s16 unk2;
} T_801BEC5C;

typedef struct{
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ UNK_TYPE2 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ UNK_TYPE2 unkA;
    /* 0x0C */ UNK_TYPE2 unkC;
    /* 0x0E */ u16 unkE;
} T_801F53B0;

/* z_map_data */
s32 func_801096D4(s32 arg0);
void func_8010983C(s32 arg0, s32 *arg1);
void func_801097C8(s32 arg0, s32* arg1, s32* arg2);
void func_80109754(s32 arg0, s32 *arg1, s32 *arg2);
#endif
