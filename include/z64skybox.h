#ifndef Z64SKYBOX_H
#define Z64SKYBOX_H

#include "PR/ultratypes.h"
#include "PR/gbi.h"
#include "color.h"

#include "z64dma.h"
#include "z64math.h"
#include "z64view.h"

struct GraphicsContext;
struct GameState;
struct PlayState;

typedef enum SkyboxId {
    /* 0 */ SKYBOX_NONE,
    /* 1 */ SKYBOX_NORMAL_SKY,
    /* 2 */ SKYBOX_2,
    /* 3 */ SKYBOX_3,
    /* 5 */ SKYBOX_CUTSCENE_MAP = 5
} SkyboxId;

typedef struct SkyboxContext {
    /* 0x000 */ View view;
    /* 0x168 */ void* staticSegments[4];
    /* 0x178 */ void* paletteStaticSegment;
    /* 0x17C */ Gfx (*dListBuf)[150];
    /* 0x180 */ Gfx* roomDL;
    /* 0x184 */ Vtx* roomVtx;
    /* 0x188 */ DmaRequest unk188;
    /* 0x1A8 */ DmaRequest unk1A8;
    /* 0x1C8 */ DmaRequest unk1C8;
    /* 0x1E8 */ OSMesgQueue loadQueue;
    /* 0x200 */ OSMesg loadMsg;
    /* 0x204 */ s16 skyboxShouldDraw;
    /* 0x208 */ Vec3f rot;
    /* 0x214 */ Vec3f eye;
    /* 0x220 */ s16 angle;
    /* 0x222 */ Color_RGB8 prim;
    /* 0x225 */ Color_RGB8 env;
} SkyboxContext; // size = 0x228

typedef struct struct_801C5F44 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
} struct_801C5F44; // size = 0x14

s32 func_80142440(SkyboxContext* skyboxCtx, Vtx* roomVtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void func_80143148(SkyboxContext* skyboxCtx, s32 arg1);
void Skybox_Setup(struct GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId);
void func_80143324(struct PlayState* play, SkyboxContext* skyboxCtx, s16 skyboxId);
void Skybox_Init(struct GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId);
Mtx* Skybox_UpdateMatrix(SkyboxContext* skyboxCtx, f32 x, f32 y, f32 z);
void Skybox_SetColors(SkyboxContext* skyboxCtx, u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB);
void Skybox_Draw(SkyboxContext* skyboxCtx, struct GraphicsContext* gfxCtx, s16 skyboxId, s16 blend, f32 x, f32 y, f32 z);
void Skybox_Update(SkyboxContext* skyboxCtx);

#endif
