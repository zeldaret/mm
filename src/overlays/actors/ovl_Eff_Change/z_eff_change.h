#ifndef Z_EFF_CHANGE_H
#define Z_EFF_CHANGE_H

#include "global.h"

struct EffChange;

typedef void (*EffChangeActionFunc)(struct EffChange*, PlayState*);

struct _struct_D_80A4C920_0x6 {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ u8 unk2;
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
};

typedef struct EffChange {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkeletonInfo skeletonInfo;
    /* 0x174 */ Vec3s unk174;
    /* 0x17A */ char pad17A[30];
    /* 0x198 */ Vec3s unk198;
    /* 0x19E */ char pad19E[30];
    /* 0x1BC */ s16 unk1BC;
    /* 0x1BE */ u8 unk1BE[4];
    /* 0x1C2 */ u8 unk1C2[4];
    /* 0x1C8 */ EffChangeActionFunc actionFunc;
} EffChange; // size = 0x1CC

extern const ActorInit Eff_Change_InitVars;

#endif // Z_EFF_CHANGE_H
