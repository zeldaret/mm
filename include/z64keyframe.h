#ifndef Z64_KEYFRAME_H
#define Z64_KEYFRAME_H

#include "ultra64.h"
#include "z64math.h"

struct PlayState;

#define KEYFRAME_OPA (0 << 0)
#define KEYFRAME_XLU (1 << 0)

struct SkeletonInfo;
struct SkeletonInfo2;

typedef s32 (*OverrideKeyframeDraw)(struct PlayState* play, struct SkeletonInfo2* skeleton, s32 limbIndex, Gfx** dList,
                                    u8* flags, void* arg, Vec3s* rot, Vec3f* pos);
typedef void (*PostKeyframeDraw)(struct PlayState* play, struct SkeletonInfo2* skeleton, s32 limbIndex, Gfx** dList,
                                 u8* flags, void* arg, Vec3s* rot, Vec3f* pos);

typedef s32 (*OverrideKeyframeDrawScaled)(struct PlayState* play, struct SkeletonInfo* skeleton, s32 limbIndex, Gfx** dList,
                                          u8* flags, void* arg, Vec3f* scale, Vec3s* rot, Vec3f* pos);
typedef void (*PostKeyframeDrawScaled)(struct PlayState* play, struct SkeletonInfo* skeleton, s32 limbIndex, Gfx** dList,
                                       u8* flags, void* arg, Vec3f* scale, Vec3s* rot, Vec3f* pos);

typedef s32 (*UnkKeyframeCallback)(struct PlayState* play, struct SkeletonInfo* skeletonInfo, s32* arg2, Gfx** dList, u8* arg4, void*);

// Keyframe limb?
typedef struct {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ u8 unk_4;
    /* 0x05 */ u8 flags;
    /* 0x06 */ Vec3s root;
} Struct_801BFA14_Arg1_Field4; // size = 0xC

// Other limb type?
typedef struct {
    /* 0x00 */ Gfx* dList;
    /* 0x04 */ u8 unk_4;
    /* 0x05 */ u8 flags;
    /* 0x06 */ u8 unk_6;         // transform limb draw index
} Struct_801BFA14_Arg1_Field4_2; // size = 0x8

typedef struct {
    /* 0x00 */ u8 limbCount;
    /* 0x01 */ u8 unk_1; // non-zero in object files, number of non-null-dlist limbs?
    /* 0x04 */ union {
        Struct_801BFA14_Arg1_Field4* unk_4; // arrays
        Struct_801BFA14_Arg1_Field4_2* unk_4_2;
    };
    /* 0x08 */ s16* unk_8;
    /* 0x0C */ s16* unk_C;
    /* 0x0C */ char unk_10[0x2];
    /* 0x12 */ s16 unk_12;
} Struct_801BFA14_Arg1;

typedef struct {
    /* 0x00 */ u16* unk_0;
    /* 0x04 */ s16* unk_4;
    /* 0x08 */ s16* unk_8;
    /* 0x0C */ s16* unk_C;
    /* 0x0C */ char unk_10[0x2];
    /* 0x12 */ s16 unk_12;
} SkeletonInfo_1C;

typedef struct {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s32 unk_14;
} FrameControl;

// FlexKeyframeSkeleton ?
typedef struct SkeletonInfo {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ Struct_801BFA14_Arg1* unk_18;    // array
    /* 0x1C */ SkeletonInfo_1C* unk_1C;
    /* 0x20 */ UnkKeyframeCallback* unk_20;     // pointer to array of functions
    /* 0x24 */ f32 unk_24;                      // duration? current time?
    /* 0x28 */ Vec3s* frameData;                // array of 3 Vec3s
    /* 0x2C */ s16* unk_2C;
} SkeletonInfo;

// KeyframeSkeleton ?
typedef struct SkeletonInfo2 {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ Struct_801BFA14_Arg1* unk_18;    // array
    /* 0x1C */ SkeletonInfo_1C* unk_1C;
    /* 0x20 */ f32 unk_20;                      // duration? current time?
    /* 0x24 */ Vec3s* frameData;
    /* 0x28 */ s16* unk_28;
    /* 0x2C */ Vec3s* unk_2C;
} SkeletonInfo2;

#endif
