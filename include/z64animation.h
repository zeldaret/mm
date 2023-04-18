#ifndef Z64ANIMATION_H
#define Z64ANIMATION_H

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "z64dma.h"
#include "z64math.h"

struct PlayState;
struct Actor;
struct SkelAnime;
struct PlayerAnimationFrame;

#define LINK_ANIMETION_OFFSET(addr, offset) \
    (SEGMENT_ROM_START(link_animetion) + ((uintptr_t)addr & 0xFFFFFF) + ((u32)offset))
#define LIMB_DONE 0xFF
#define ANIMATION_ENTRY_MAX 50

#define ANIM_FLAG_1         (1 << 0)
#define ANIM_FLAG_UPDATEY   (1 << 1)
#define ANIM_FLAG_4         (1 << 2)
#define ANIM_FLAG_NOMOVE    (1 << 4)

typedef enum AnimationMode {
    /* 0 */ ANIMMODE_LOOP,
    /* 1 */ ANIMMODE_LOOP_INTERP,
    /* 2 */ ANIMMODE_ONCE,
    /* 3 */ ANIMMODE_ONCE_INTERP,
    /* 4 */ ANIMMODE_LOOP_PARTIAL,
    /* 5 */ ANIMMODE_LOOP_PARTIAL_INTERP
} AnimationMode;

typedef enum {
    /* -1 */ ANIMTAPER_DECEL = -1,
    /*  0 */ ANIMTAPER_NONE,
    /*  1 */ ANIMTAPER_ACCEL
} AnimationTapers;

typedef struct {
    /* 0x0 */ Vec3s jointPos; // Root is position in model space, children are relative to parent
    /* 0x6 */ u8 child;       // The first child's index into the limb table.
    /* 0x7 */ u8 sibling;     // The parent limb's next limb index into the limb table.
    /* 0x8 */ Gfx* dList;     // Display lists for the limb. Index 0 is the normal display list, index 1 is the
                               // far model display list.
} StandardLimb; // size = 0xC

// Model has limbs with only rigid meshes
typedef struct {
    /* 0x0 */ Vec3s jointPos; // Root is position in model space, children are relative to parent
    /* 0x6 */ u8 child;
    /* 0x7 */ u8 sibling;
    /* 0x8 */ Gfx* dLists[2]; // Near and far
} LodLimb; // size = 0x10

// Model has limbs with only rigid meshes
typedef struct {
    /* 0x0 */ void** segment;
    /* 0x4 */ u8 limbCount;
} SkeletonHeader; // size = 0x8

// Model has limbs with flexible meshes
typedef struct {
    /* 0x0 */ SkeletonHeader sh;
    /* 0x8 */ u8 dListCount;
} FlexSkeletonHeader; // size = 0xC

// Index into the frame data table. 
typedef struct {
    /* 0x0 */ u16 x;
    /* 0x2 */ u16 y;
    /* 0x4 */ u16 z;
} JointIndex; // size = 0x6

typedef struct {
    /* 0x0 */ s16 frameCount;
} AnimationHeaderCommon; // size = 0x2

typedef struct {
    /* 0x0 */ AnimationHeaderCommon common;
    /* 0x4 */ s16* frameData; // referenced as tbl
    /* 0x8 */ JointIndex* jointIndices; // referenced as ref_tbl
    /* 0xC */ u16 staticIndexMax;
} AnimationHeader; // size = 0x10

typedef struct {
    /* 0x00 */ s16 xMax;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 yMax;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 zMax;
    /* 0x10 */ s16 z;
} JointKey; // size = 0x12

typedef struct {
    /* 0x0 */ s16 frameCount;
    /* 0x2 */ s16 limbCount;
    /* 0x4 */ s16* frameData;
    /* 0x8 */ JointKey* jointKey;
} LegacyAnimationHeader; // size = 0xC

typedef enum {
    ANIMATION_LINKANIMETION,
    ANIMENTRY_COPYALL,
    ANIMENTRY_INTERP,
    ANIMENTRY_COPYTRUE,
    ANIMENTRY_COPYFALSE,
    ANIMENTRY_MOVEACTOR
} AnimationType;

typedef struct {
    /* 0x00 */ DmaRequest req;
    /* 0x20 */ OSMesgQueue msgQueue;
    /* 0x38 */ OSMesg msg;
} AnimEntryLoadFrame; // size = 0x3C

typedef struct {
    /* 0x0 */ u8 queueFlag;
    /* 0x1 */ u8 vecCount;
    /* 0x4 */ Vec3s* dst;
    /* 0x8 */ Vec3s* src;
} AnimEntryCopyAll; // size = 0xC

typedef struct {
    /* 0x0 */ u8 queueFlag;
    /* 0x1 */ u8 vecCount;
    /* 0x4 */ Vec3s* base;
    /* 0x8 */ Vec3s* mod;
    /* 0xC */ f32 weight;
} AnimEntryInterp; // size = 0x10

typedef struct {
    /* 0x0 */ u8 queueFlag;
    /* 0x1 */ u8 vecCount;
    /* 0x4 */ Vec3s* dst;
    /* 0x8 */ Vec3s* src;
    /* 0xC */ u8* copyFlag;
} AnimEntryCopyTrue; // size = 0x10

typedef struct {
    /* 0x0 */ u8 queueFlag;
    /* 0x1 */ u8 vecCount;
    /* 0x4 */ Vec3s* dst;
    /* 0x8 */ Vec3s* src;
    /* 0xC */ u8* copyFlag;
} AnimEntryCopyFalse; // size = 0x10

typedef struct {
    /* 0x0 */ struct Actor* actor;
    /* 0x4 */ struct SkelAnime* skelAnime;
    /* 0x8 */ f32 unk08;
} AnimEntryMoveActor; // size = 0xC

typedef union {
    AnimEntryLoadFrame load;
    AnimEntryCopyAll copy;
    AnimEntryInterp interp;
    AnimEntryCopyTrue copy1;
    AnimEntryCopyFalse copy0;
    AnimEntryMoveActor move;
} AnimationEntryData; // size = 0x3C

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x04 */ AnimationEntryData data;
} AnimationEntry; // size = 0x40

typedef struct AnimationContext {
    /* 0x000 */ s16 animationCount;
    /* 0x004 */ AnimationEntry entries[ANIMATION_ENTRY_MAX];
} AnimationContext; // size = 0xC84

typedef struct {
    /* 0x0 */ AnimationHeaderCommon common;
    /* 0x4 */ union {
                void* segmentVoid;
                struct PlayerAnimationFrame* segment;
            };
} LinkAnimationHeader; // size = 0x8

typedef struct SkelAnime {
    /* 0x00 */ u8 limbCount;      // Number of limbs in the skeleton
    /* 0x01 */ u8 mode;           // 0: loop, 2: play once, 4: partial loop. +1 to interpolate between frames.
    /* 0x02 */ u8 dListCount;     // Number of display lists in a flexible skeleton
    /* 0x03 */ s8 taper;          // Tapering to use when morphing between animations. Only used by Door_Warp1.
    /* 0x04 */ void** skeleton;   // An array of pointers to limbs. Can be StandardLimb, LodLimb, or SkinLimb.
    /* 0x08 */ void* animation;   // Can be an AnimationHeader or LinkAnimationHeader.
    /* 0x0C */ f32 startFrame;    // In mode 4, start of partial loop.
    /* 0x10 */ f32 endFrame;      // In mode 2, Update returns true when curFrame is equal to this. In mode 4, end of partial loop.
    /* 0x14 */ f32 animLength;    // Total number of frames in the current animation's file.
    /* 0x18 */ f32 curFrame;      // Current frame in the animation
    /* 0x1C */ f32 playSpeed;     // Multiplied by R_UPDATE_RATE / 3 to get the animation's frame rate.
    /* 0x20 */ Vec3s* jointTable; // Current translation of model and rotations of all limbs
    /* 0x24 */ Vec3s* morphTable; // Table of values used to morph between animations
    /* 0x28 */ f32 morphWeight;   // Weight of the current animation morph as a fraction in [0,1]
    /* 0x2C */ f32 morphRate;     // Reciprocal of the number of frames in the morph
    /* 0x30 */ union {
                    s32 (*normal)(struct SkelAnime*);// Can be Loop, Partial loop, Play once, Morph, or Tapered morph
                    s32 (*link)(struct PlayState*, struct SkelAnime*); // Loop, Play once, and Morph
                } update;
    /* 0x34 */ s8 initFlags;      // Flags used when initializing Link's skeleton
    /* 0x35 */ u8 moveFlags;          // Flags used for animations that move the actor in worldspace.
    /* 0x36 */ s16 prevRot;       // Previous rotation in worldspace.
    /* 0x38 */ Vec3s prevTransl;  // Previous modelspace translation.
    /* 0x3E */ Vec3s baseTransl;  // Base modelspace translation.
} SkelAnime; // size = 0x44

typedef s32 (*OverrideLimbDrawOpa)(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                   struct Actor* thisx);

typedef void (*PostLimbDrawOpa)(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot,
                                struct Actor* thisx);

typedef s32 (*OverrideLimbDraw)(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                struct Actor* thisx, Gfx** gfx);

typedef void (*PostLimbDraw)(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3s* rot,
                             struct Actor* thisx, Gfx** gfx);

typedef s32 (*OverrideLimbDrawFlex)(struct PlayState* play, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                    struct Actor* thisx);

typedef void (*PostLimbDrawFlex)(struct PlayState* play, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot,
                                 struct Actor* thisx);

typedef void (*TransformLimbDrawOpa)(struct PlayState* play, s32 limbIndex, struct Actor* thisx);

typedef void (*TransformLimbDraw)(struct PlayState* play, s32 limbIndex, struct Actor* thisx, Gfx** gfx);

typedef void (*AnimationEntryCallback)(struct PlayState*, AnimationEntryData*);

extern u32 link_animetion_segment;

typedef struct {
    /* 0x00 */ AnimationHeader* animation;
    /* 0x04 */ f32 playSpeed;
    /* 0x08 */ f32 startFrame;
    /* 0x0C */ f32 frameCount;
    /* 0x10 */ u8 mode;
    /* 0x14 */ f32 morphFrames;
} AnimationInfo; // size = 0x18

typedef struct {
    /* 0x0 */ AnimationHeader* animation;
    /* 0x4 */ f32 playSpeed;
    /* 0x8 */ s16 startFrame;
    /* 0xA */ s16 frameCount;
    /* 0xC */ u8 mode;
    /* 0xE */ s16 morphFrames;
} AnimationInfoS; // size = 0x10

typedef struct AnimationSpeedInfo {
    /* 0x0 */ AnimationHeader* animation;
    /* 0x4 */ f32 playSpeed;
    /* 0x8 */ u8 mode;
    /* 0xC */ f32 morphFrames;
} AnimationSpeedInfo; // size = 0x10

struct SkeletonInfo;

typedef s32 (*UnkKeyframeCallback)(struct PlayState* play, struct SkeletonInfo* skeletonInfo, s32* arg2, Gfx** dList,
                                   u8* arg4, void* arg5);

// Keyframe limb?
typedef struct {
    /* 0x0 */ Gfx* dList;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 flags;
    /* 0x6 */ Vec3s root;
} Struct_801BFA14_Arg1_Field4; // size = 0xC

// Other limb type?
typedef struct {
    /* 0x0 */ Gfx* dList;
    /* 0x4 */ u8 unk_4;
    /* 0x5 */ u8 flags;
    /* 0x6 */ u8 unk_6;         // transform limb draw index
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
    /* 0x10 */ char unk_10[0x2];
    /* 0x12 */ s16 unk_12;
} Struct_801BFA14_Arg1; // size = 0x14

typedef struct {
    /* 0x00 */ u16* unk_0;
    /* 0x04 */ s16* unk_4;
    /* 0x08 */ s16* unk_8;
    /* 0x0C */ s16* unk_C;
    /* 0x10 */ char unk_10[0x2];
    /* 0x12 */ s16 unk_12;
} SkeletonInfo_1C; // size = 0x14

typedef struct {
    /* 0x00 */ f32 unk_0;
    /* 0x04 */ f32 unk_4;
    /* 0x08 */ f32 unk_8;
    /* 0x0C */ f32 unk_C;
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ s32 unk_14;
} FrameControl; // size = 0x18

// FlexKeyframeSkeleton ?
typedef struct SkeletonInfo {
    /* 0x00 */ FrameControl frameCtrl;
    /* 0x18 */ Struct_801BFA14_Arg1* unk_18;    // array
    /* 0x1C */ SkeletonInfo_1C* unk_1C;
    /* 0x20 */ UnkKeyframeCallback* unk_20;     // pointer to array of functions
    /* 0x24 */ f32 unk_24;                      // duration? current time?
    /* 0x28 */ Vec3s* frameData;                // array of 3 Vec3s
    /* 0x2C */ s16* unk_2C;
} SkeletonInfo; // size = 0x30

typedef s32 (*OverrideKeyframeDrawScaled)(struct PlayState* play, SkeletonInfo* skeletonInfo, s32 limbIndex, Gfx** dList,
                                          u8* flags, struct Actor* actor, Vec3f* scale, Vec3s* rot, Vec3f* pos);

typedef void (*PostKeyframeDrawScaled)(struct PlayState* play, SkeletonInfo* skeleton, s32 limbIndex, Gfx** dList,
                                       u8* flags, struct Actor* actor, Vec3f* scale, Vec3s* rot, Vec3f* pos);

#endif
