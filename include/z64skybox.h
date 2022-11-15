#ifndef Z64_SKYBOX_H
#define Z64_SKYBOX_H

#include "PR/ultratypes.h"
#include "PR/gbi.h"

#include "z64dma.h"
#include "z64math.h"
#include "z64view.h"

typedef enum SkyboxId {
    /* 0x00 */ SKYBOX_NONE,
    /* 0x01 */ SKYBOX_NORMAL_SKY,
    /* 0x02 */ SKYBOX_2,
    /* 0x03 */ SKYBOX_3,
    /* 0x05 */ SKYBOX_CUTSCENE_MAP = 5
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
    /* 0x200 */ OSMesg loadMsg[1];
    /* 0x204 */ s16 skyboxShouldDraw;
    /* 0x208 */ f32 rotX;
    /* 0x20C */ f32 rotY;
    /* 0x210 */ f32 rotZ;
    /* 0x214 */ Vec3f eye;
    /* 0x220 */ s16 angle;
    /* 0x222 */ u8 primR;
    /* 0x223 */ u8 primG;
    /* 0x224 */ u8 primB;
    /* 0x225 */ u8 envR;
    /* 0x226 */ u8 envG;
    /* 0x227 */ u8 envB;
} SkyboxContext; // size = 0x228

#endif
