#ifndef _Z64LIGHT_H_
#define _Z64LIGHT_H_

#include <ultra64.h>
#include <PR/gbi.h>
#include <color.h>

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

typedef union {
    LightPoint point;
    LightDirectional dir;
} LightParams; // size = 0xC

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightParams params;
} LightInfo; // size = 0xE

typedef struct {
    /* 0x00 */ u8 enablePosLights;
    /* 0x01 */ u8 numLights;
    /* 0x08 */ Lightsn l;
} Lights; // size = 0x80

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightPoint params;
} LightInfoPositional; // size = 0xE

typedef struct LightNode {
    /* 0x0 */ LightInfo* info;
    /* 0x4 */ struct LightNode* prev;
    /* 0x8 */ struct LightNode* next;
} LightNode; // size = 0xC

// TODO move LightsBuffer to .c file once .bss has been split
#define LIGHTS_BUFFER_SIZE 32

typedef struct {
    /* 0x000 */ s32 numOccupied;
    /* 0x004 */ s32 searchIndex;
    /* 0x008 */ LightNode lights[LIGHTS_BUFFER_SIZE];
} LightsBuffer; // size = 0x188

typedef struct {
    /* 0x0 */ LightNode* listHead;
    /* 0x4 */ Color_RGB8 ambient;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
} LightContext; // size = 0x10

typedef enum {
    /* 0x00 */ LIGHT_POINT_NOGLOW,
    /* 0x01 */ LIGHT_DIRECTIONAL,
    /* 0x02 */ LIGHT_POINT_GLOW
} LightType;

typedef struct GlobalContext GlobalContext;

typedef void (*LightsBindFunc)(Lights* lights, void* params, Vec3f* vec);
typedef void (*LightsPosBindFunc)(Lights* lights, void* params, GlobalContext* globalCtx);

#endif
