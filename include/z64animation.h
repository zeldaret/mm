#ifndef _Z64_ANIMATION_H
#define _Z64_ANIMATION_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>
#include <z64dma.h>
#include <z64math.h>

#define LINK_ANIMETION_OFFSET(addr, offset) \
    (((u32)&_link_animetionSegmentRomStart) + ((u32)addr & 0xFFFFFF) + ((u32)offset))
#define LIMB_DONE 0xFF
#define ANIMATION_ENTRY_MAX 50

#define ANIM_FLAG_UPDATEXZ 0x02
#define ANIM_FLAG_UPDATEY 0x10

struct GlobalContext;
struct Actor;
typedef struct SkelAnime SkelAnime;

typedef struct {
    /* 0x000 */ Vec3s translation;  // Translation relative to parent limb.  root limb is a tranlation for entire model.
    /* 0x006 */ u8 firstChildIndex; // The first child's index into the limb table.
    /* 0x007 */ u8 nextLimbIndex;   // The parent limb's next limb index into the limb table.
    /* 0x008 */ Gfx* displayLists[1]; // Display lists for the limb. Index 0 is the normal display list, index 1 is the
                                      // far model display list.
} StandardLimb; // Size = 0xC

// Model has limbs with only rigid meshes
typedef struct {
    /* 0x000 */ void** skeletonSeg; // Segment address of SkelLimbIndex.
    /* 0x004 */ u8 limbCount;          // Number of limbs in the model.
} SkeletonHeader; // size = 0x8

// Model has limbs with flexible meshes
typedef struct {
    /* 0x000 */ SkeletonHeader sh;
    /* 0x008 */ u8 dListCount;         // Number of display lists in the model.
} FlexSkeletonHeader; // size = 0xC

typedef s16 AnimationRotationValue;

typedef struct {
    /* 0x000 */ u16 x;
    /* 0x002 */ u16 y;
    /* 0x004 */ u16 z;
} JointIndex; // size = 0x06

typedef struct {
    /* 0x000 */ s16 frameCount;
    /* 0x002 */ s16 unk02;
} AnimationHeaderCommon; // size = 0x4

typedef struct {
    /* 0x00 */ AnimationHeaderCommon common;
    /* 0x04 */ s16* frameData;         // referenced as tbl
    /* 0x08 */ JointIndex* jointIndices; // referenced as ref_tbl
    /* 0x0C */ u16 staticIndexMax;
} AnimationHeader; // size = 0x10

typedef enum {
    ANIMATION_LINKANIMETION,
    ANIMATION_TYPE1,
    ANIMATION_TYPE2,
    ANIMATION_TYPE3,
    ANIMATION_TYPE4,
    ANIMATION_TYPE5
} AnimationType;

typedef struct {
    /* 0x000 */ DmaRequest req;
    /* 0x020 */ OSMesgQueue msgQueue;
    /* 0x038 */ OSMesg msg;
} AnimationEntryType0; // size = 0x3C

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 vecCount;
    /* 0x004 */ Vec3s* dst;
    /* 0x008 */ Vec3s* src;
} AnimationEntryType1; // size = 0xC

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 limbCount;
    /* 0x004 */ Vec3s* unk04;
    /* 0x008 */ Vec3s* unk08;
    /* 0x00C */ f32 unk0C;
} AnimationEntryType2; // size = 0x10

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 vecCount;
    /* 0x004 */ Vec3s* dst;
    /* 0x008 */ Vec3s* src;
    /* 0x00C */ u8* index;
} AnimationEntryType3; // size = 0x10

typedef struct {
    /* 0x000 */ u8 unk00;
    /* 0x001 */ u8 vecCount;
    /* 0x002 */ char unk02[0x2];
    /* 0x004 */ Vec3s* dst;
    /* 0x008 */ Vec3s* src;
    /* 0x00C */ u8* index;
} AnimationEntryType4; // size = 0x10

typedef struct {
    /* 0x000 */ struct Actor* actor;
    /* 0x004 */ SkelAnime* skelAnime;
    /* 0x008 */ f32 unk08;
} AnimationEntryType5; // size = 0xC

typedef struct {
    /* 0x000 */ u8 raw[0x3C];
} AnimationEntryRaw; // size = 0x3C

typedef union {
    AnimationEntryRaw raw;
    AnimationEntryType0 type0;
    AnimationEntryType1 type1;
    AnimationEntryType2 type2;
    AnimationEntryType3 type3;
    AnimationEntryType4 type4;
    AnimationEntryType5 type5;
} AnimationEntryType; // size = 0x3C

typedef struct {
    /* 0x000 */ u8 type;
    /* 0x001 */ u8 unk01;
    /* 0x004 */ AnimationEntryType types;
} AnimationEntry; // size = 0x40

typedef struct AnimationContext {
    /* 0x000 */ s16 animationCount;
    /* 0x002 */ char unk02[2];
    /* 0x004 */ AnimationEntry entries[ANIMATION_ENTRY_MAX];
} AnimationContext; // size = 0xC84

typedef struct {
    /* 0x00 */ AnimationHeaderCommon common;
    /* 0x04 */ u32 segment;
} LinkAnimationHeader; // size = 0x8

struct SkelAnime {
    /* 0x00 */ u8 limbCount; // joint_Num
                             /* modes 0 and 1 repeat the animation indefinitely
                              * modes 2 and 3 play the animaton once then stop
                              * modes >= 4 play the animation once, and always start at frame 0.
                              */
    /* 0x01 */ u8 mode;
    /* 0x02 */ u8 dListCount;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ void** skeleton;   // An array of pointers to limbs. Can be StandardLimb, LodLimb, or SkinLimb.
    /* 0x08 */
    union {
        AnimationHeader* animCurrentSeg;
        LinkAnimationHeader* linkAnimetionSeg;
        AnimationHeaderCommon* genericSeg;
    };
    /* 0x0C */ f32 initialFrame;
    /* 0x10 */ f32 animFrameCount;
    /* 0x14 */ f32 totalFrames;
    /* 0x18 */ f32 animCurrentFrame;
    /* 0x1C */ f32 animPlaybackSpeed;
    /* 0x20 */ Vec3s* limbDrawTbl;       // now_joint
    /* 0x24 */ Vec3s* transitionDrawTbl; // morf_joint
    /* 0x28 */ f32 transCurrentFrame;
    /* 0x2C */ f32 transitionStep;
    /* 0x30 */ s32 (*animUpdate)();
    /* 0x34 */ s8 initFlags;
    /* 0x35 */ u8 flags;
    /* 0x36 */ s16 prevFrameRot;
    /* 0x38 */ Vec3s prevFramePos;
    /* 0x3E */ Vec3s unk3E;
}; // size = 0x44

typedef s32 (*OverrideLimbDraw)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                struct Actor* actor);

typedef void (*PostLimbDraw)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                             struct Actor* actor);

typedef s32 (*OverrideLimbDraw2)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                 struct Actor* actor, Gfx** gfx);

typedef void (*PostLimbDraw2)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3s* rot,
                              struct Actor* actor, Gfx** gfx);

typedef s32 (*OverrideLimbDrawSV)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList, Vec3f* pos, Vec3s* rot,
                                  struct Actor* actor);

typedef void (*PostLimbDrawSV)(struct GlobalContext* globalCtx, s32 limbIndex, Gfx** dList1, Gfx** dList2, Vec3s* rot,
                               struct Actor* actor);

typedef void (*UnkActorDraw)(struct GlobalContext* globalCtx, s32 limbIndex, struct Actor* actor);

typedef void (*AnimationEntryCallback)(struct GlobalContext*, AnimationEntryType*);

extern u32 link_animetion_segment;

// fcurve_skelanime structs
typedef struct {
    /* 0x0000 */ u16 unk00; // appears to be flags
    /* 0x0002 */ s16 unk02;
    /* 0x0004 */ s16 unk04;
    /* 0x0006 */ s16 unk06;
    /* 0x0008 */ f32 unk08;
} TransformData; // size = 0xC

typedef struct {
    /* 0x0000 */ u8* refIndex;
    /* 0x0004 */ TransformData* transformData;
    /* 0x0008 */ s16* copyValues;
    /* 0x000C */ s16 unk0C;
    /* 0x000E */ s16 unk10;
} TransformUpdateIndex; // size 0x10

typedef struct {
    /* 0x0000 */ u8 firstChildIdx;
    /* 0x0001 */ u8 nextLimbIdx;
    /* 0x0004 */ Gfx* dList[2];
} SkelCurveLimb; // size >= 0x8

typedef struct {
    /* 0x0000 */ SkelCurveLimb** limbs;
    /* 0x0004 */ u8 limbCount;
} SkelCurveLimbList; // size = 0x8

typedef struct {
    /* 0x0000 */ Vec3s scale;
    /* 0x0006 */ Vec3s rot;
    /* 0x000C */ Vec3s pos;
} LimbTransform; // size = 0x12

typedef struct {
    /* 0x0000 */ u8 limbCount;
    /* 0x0004 */ SkelCurveLimb** limbList;
    /* 0x0008 */ TransformUpdateIndex* transUpdIdx;
    /* 0x000C */ f32 unk0C; // seems to be unused
    /* 0x0010 */ f32 animFinalFrame;
    /* 0x0014 */ f32 animSpeed;
    /* 0x0018 */ f32 animCurFrame;
    /* 0x001C */ LimbTransform* transforms;
} SkelAnimeCurve; // size = 0x20

typedef s32 (*OverrideCurveLimbDraw)(struct GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex,
                                     struct Actor* actor);
typedef void (*PostCurveLimbDraw)(struct GlobalContext* globalCtx, SkelAnimeCurve* skelCuve, s32 limbIndex,
                                  struct Actor* actor);

typedef struct struct_80B8E1A8 {
    /* 0x00 */ AnimationHeader* animationSeg;
    /* 0x04 */ f32 playbackSpeed;
    /* 0x08 */ u8 mode;
    /* 0x0C */ f32 transitionRate;
} struct_80B8E1A8; // size = 0x10

#endif
