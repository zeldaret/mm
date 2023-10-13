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
    SKYBOX_NONE,
    SKYBOX_NORMAL_SKY,
    SKYBOX_2,
    SKYBOX_3,
    SKYBOX_CUTSCENE_MAP = 5
} SkyboxId;

typedef struct SkyboxContext {
    View view;
    void* staticSegments[4];
    void* paletteStaticSegment;
    Gfx (*dListBuf)[150];
    Gfx* roomDL;
    Vtx* roomVtx;
    DmaRequest unk188;
    DmaRequest unk1A8;
    DmaRequest unk1C8;
    OSMesgQueue loadQueue;
    OSMesg loadMsg;
    s16 skyboxShouldDraw;
    Vec3f rot;
    Vec3f eye;
    s16 angle;
    Color_RGB8 prim;
    Color_RGB8 env;
} SkyboxContext;

typedef struct SkyboxVertexData {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} SkyboxVertexData;


s32 Skybox_LoadTexturesAndPalette(SkyboxContext* skyboxCtx, Vtx* roomVtx, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8);
void Skybox_GenerateVertices(SkyboxContext* skyboxCtx, s32 arg1);
void Skybox_Setup(struct GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId);
void Skybox_ManageResources(struct PlayState* play, SkyboxContext* skyboxCtx, s16 skyboxId);
void Skybox_Init(struct GameState* gameState, SkyboxContext* skyboxCtx, s16 skyboxId);
Mtx* Skybox_UpdateMatrix(SkyboxContext* skyboxCtx, f32 x, f32 y, f32 z);
void Skybox_SetColors(SkyboxContext* skyboxCtx, u8 primR, u8 primG, u8 primB, u8 envR, u8 envG, u8 envB);
void Skybox_Draw(SkyboxContext* skyboxCtx, struct GraphicsContext* gfxCtx, s16 skyboxId, s16 blend, f32 x, f32 y, f32 z);
void Skybox_Update(SkyboxContext* skyboxCtx);

#endif
