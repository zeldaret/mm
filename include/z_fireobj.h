#ifndef Z_FIREOBJ_H
#define Z_FIREOBJ_H

#include "ultra64.h"
#include "color.h"
#include "z64collision_check.h"
#include "z64light.h"
#include "z64math.h"

struct PlayState;
struct Actor;


typedef struct {
    /* 0x0 */ f32 size;
    /* 0x4 */ f32 dynamicSizeStep;
    /* 0x8 */ u8 state;
    /* 0x9 */ u8 sizeGrowsCos2;
    /* 0xA */ u8 colorsIndex;
    /* 0xB */ u8 flags;
    /* 0xC */ u8 lightParamsIndex;
} FireObjInitParams; // size = 0x10

typedef struct FireObjColors {
    /* 0x0 */ Color_RGBA8 primColor;
    /* 0x4 */ u8 lod;
    /* 0x5 */ Color_RGB8 envColor;
} FireObjColors; // size = 0x8

typedef struct FireObjLightParams {
    /* 0x0 */ s16 radius;
    /* 0x2 */ Color_RGB8 color;
    /* 0x5 */ Color_RGB8 maxColorAdj;
} FireObjLightParams; // size = 0x8

typedef struct FireObjLight {
    /* 0x00 */ LightNode* light;
    /* 0x04 */ LightInfo lightInfo;
    /* 0x12 */ u8 lightParamsIndex;
} FireObjLight; // size = 0x14

typedef struct FireObj {
    /* 0x00 */ Vec3f position;
    /* 0x0C */ f32 size;
    /* 0x10 */ f32 sizeInv;
    /* 0x14 */ f32 xScale;
    /* 0x18 */ f32 yScale;
    /* 0x1C */ f32 dynamicSize;
    /* 0x20 */ f32 dynamicSizeStep;
    /* 0x24 */ u8 state; // 0 - growing, 1 - shrinking, 2 - fully lit, 3 - not lit
    /* 0x25 */ u8 sizeGrowsCos2;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 colorsIndex;
    /* 0x28 */ u8 flags; // bit 0 - ?, bit 1 - ?
    /* 0x29 */ UNK_TYPE1 pad29[0x1];
    /* 0x2A */ s16 ignitionDelay;
    /* 0x2C */ ColliderCylinder collision;
    /* 0x78 */ FireObjLight light;
} FireObj; // size = 0x8B

typedef enum {
    FIRE_STATE_0,
    FIRE_STATE_1,
    FIRE_STATE_2,
    FIRE_STATE_3,
} FireState;


void FireObj_SetPosition(FireObj* fire, Vec3f* pos);
void FireObj_Draw(struct PlayState* play, FireObj* fire);
void FireObj_Init(struct PlayState* play, FireObj* fire, FireObjInitParams* init, struct Actor* actor);
void FireObj_Destroy(struct PlayState* play, FireObj* fire);
void FireObj_SetState2(FireObj* fire, f32 dynamicSizeStep, u8 newState);
void FireObj_Update(struct PlayState* play, FireObj* fire, struct Actor* actor);

#endif
