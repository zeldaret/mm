#ifndef _Z64LIGHT_H_
#define _Z64LIGHT_H_

#include "ultra64.h"
#include "PR/gbi.h"
#include "color.h"

typedef struct {
    /* 0x00 */ u8 ambientColor[3];
    /* 0x03 */ s8 diffuseDir1[3];
    /* 0x06 */ u8 diffuseColor1[3];
    /* 0x09 */ s8 diffusePos2[3];
    /* 0x0C */ u8 diffuseColor[3];
    /* 0x0F */ u8 fogColor[3];
    /* 0x12 */ u16 fogNear;
    /* 0x14 */ u16 fogFar;
} LightSettings; // size = 0x16

typedef struct {
    /* 0x00 */ s16 ambientColor[3];
    /* 0x06 */ s16 diffuseColor1[3];
    /* 0x0C */ s16 diffuseColor2[3];
    /* 0x12 */ s16 fogColor[3];
    /* 0x18 */ s16 fogNear;
    /* 0x1A */ s16 fogFar;
} EnvLightSettings; // size = 0x1C

typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u8 color[3];
    /* 0x9 */ u8 drawGlow;
    /* 0xA */ s16 radius;
} LightPoint; // size = 0xC

typedef struct {
    /* 0x0 */ s8 x;
    /* 0x1 */ s8 y;
    /* 0x2 */ s8 z;
    /* 0x3 */ u8 color[3];
} LightDirectional; // size = 0x6

typedef union LightParams {
    LightPoint point;
    LightDirectional dir;
} LightParams; // size = 0xC

typedef struct LightInfo {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightParams params;
} LightInfo; // size = 0xE

typedef struct Lights {
    /* 0x00 */ u8 enablePosLights;
    /* 0x01 */ u8 numLights;
    /* 0x08 */ Lightsn l;
} Lights; // size = 0x80

typedef struct LightNode {
    /* 0x0 */ LightInfo* info;
    /* 0x4 */ struct LightNode* prev;
    /* 0x8 */ struct LightNode* next;
} LightNode; // size = 0xC

// TODO move LightsBuffer to .c file once .bss has been split
#define LIGHTS_BUFFER_SIZE 32

typedef struct LightsBuffer {
    /* 0x000 */ s32 numOccupied;
    /* 0x004 */ s32 searchIndex;
    /* 0x008 */ LightNode lights[LIGHTS_BUFFER_SIZE];
} LightsBuffer; // size = 0x188

typedef struct LightContext {
    /* 0x0 */ LightNode* listHead;
    /* 0x4 */ Color_RGB8 ambient;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
} LightContext; // size = 0x10

typedef enum LightType {
    /* 0x00 */ LIGHT_POINT_NOGLOW,
    /* 0x01 */ LIGHT_DIRECTIONAL,
    /* 0x02 */ LIGHT_POINT_GLOW
} LightType;

typedef void (*LightsBindFunc)(Lights* lights, LightParams* params, Vec3f* vec);
typedef void (*LightsPosBindFunc)(Lights* lights, LightParams* params, struct GlobalContext* globalCtx);

#endif
