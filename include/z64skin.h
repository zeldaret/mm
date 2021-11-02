#ifndef Z64_SKIN_H
#define Z64_SKIN_H

#include "z64animation.h"


typedef struct {
    /* 0x00 */ Vec3s jointPos; // Root is position in model space, children are relative to parent
    /* 0x06 */ u8 child;
    /* 0x07 */ u8 sibling;
    /* 0x08 */ s32 unk_8; // Type of data contained in segment
    /* 0x0C */ void* segment; // Segment address of data. Currently unclear what.
} SkinLimb; // size = 0x10


typedef struct {
    /* 0x000 */ u16 unk_0;
    /* 0x002 */ s16 unk_2;
    /* 0x004 */ s16 unk_4;
    /* 0x006 */ s8 unk_6;
    /* 0x007 */ s8 unk_7;
    /* 0x008 */ s8 unk_8;
    /* 0x009 */ u8 unk_9;
} Struct_800A57C0; // size = 0xA

typedef struct {
    /* 0x000 */ u8  unk_0;
    /* 0x002 */ s16 x;
    /* 0x004 */ s16 y;
    /* 0x006 */ s16 z;
    /* 0x008 */ u8  unk_8;
} Struct_800A598C_2; // size = 0xA

typedef struct {
    /* 0x000 */ u16 unk_0; // count of unk_8
    /* 0x002 */ u16 unk_2; // count of unk_C
    /* 0x004 */ u16 unk_4;
    /* 0x008 */ Struct_800A57C0* unk_8;
    /* 0x00C */ Struct_800A598C_2* unk_C;
} Struct_800A598C; // size = 0x10

typedef struct {
    /* 0x000 */ u16 vtxCount;
    /* 0x002 */ u16 unk_2;
    /* 0x004 */ Struct_800A598C* unk_4;
    /* 0x008 */ Gfx* dlist;
} Struct_800A5E28; // size = 0xC

typedef struct {
    /* 0x000 */ u8 index;
    /* 0x004 */ Vtx* buf[2];
} SkinAvb; // size = 0xC

typedef struct {
    /* 0x000 */ SkeletonHeader* skeletonHeader;
    /* 0x004 */ MtxF mtx;
    /* 0x044 */ s32 avbCount;
    /* 0x048 */ SkinAvb* avbTbl;
    /* 0x04C */ SkelAnime skelAnime;
} PSkinAwb; // size = 0x90

typedef void (*SkinPostLimbDraw)(struct Actor*, struct GlobalContext*, PSkinAwb*);
typedef s32 (*SkinOverrideLimbDraw)(struct Actor*, struct GlobalContext*, s32, PSkinAwb*);

void func_80137970(MtxF* mtx, Struct_800A57C0* arg1, Struct_800A598C* arg2, Vtx* arg3, Vec3f* arg4);
void func_80137B34(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3);
void func_80137EBC(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, s32 arg3, s32 arg4);
void func_80137F58(GraphicsContext* gfxCtx, PSkinAwb* skin, s32 limbIndex, Gfx* arg3, s32 arg4);
//void Skin_DrawImpl(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80138228(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, s32 arg4);
void func_80138258(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw arg4, s32 arg5);
void func_8013828C(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw arg4, s32 arg5, s32 arg6);
void func_801382C4(Actor* actor, GlobalContext* globalCtx, PSkinAwb* skin, SkinPostLimbDraw postLimbDraw, SkinOverrideLimbDraw arg4, s32 arg5, s32 arg6, s32 arg7);
void func_80138300(PSkinAwb* skin, s32 joint, Vec3f* arg2, Vec3f* arg3);
void func_8013835C(PSkinAwb* arg0, s32 arg1, s32 arg2, Vec3f* arg3);

void func_80138410(PSkinAwb* skin);
void func_80138424(GameState* gameState, PSkinAwb* skin, s32 limbIndex);
void Skin_Init(GameState* gameState, PSkinAwb* skin, SkeletonHeader* skeletonHeader, AnimationHeader* animationHeader);
void Skin_Free(GameState* gameState, PSkinAwb* skin);
s32 func_801387D4(PSkinAwb* skin, SkinLimb** skeleton, MtxF* mf, u8 parentIndex, u8 limbIndex);
s32 func_801388E4(PSkinAwb* skin, MtxF* arg1, Actor* actor, s32 arg3);

#endif
