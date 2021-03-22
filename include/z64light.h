#ifndef _Z64LIGHT_H_
#define _Z64LIGHT_H_

#include <ultra64.h>
#include <PR/gbi.h>

typedef struct {
    /* 0x0 */ u8 col[3];
    /* 0x3 */ u8 unk3;
    /* 0x4 */ u8 colc[3];
    /* 0x7 */ u8 unk7;
    /* 0x8 */ s16 pos[3];
    /* 0xE */ u8 unkE;
    /* 0xF */ u8 unkF;
} PosLight; // size = 0x10

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x2 */ u16 params[6];
} LightInfo; // size = 0xE

typedef struct z_Light_t {
    /* 0x0 */ LightInfo* info;
    /* 0x4 */ struct z_Light_t* prev;
    /* 0x8 */ struct z_Light_t* next;
} z_Light; // size = 0xC

typedef struct {
    /* 0x0 */ z_Light* lightsHead;
    /* 0x4 */ u8 ambientRed;
    /* 0x5 */ u8 ambientGreen;
    /* 0x6 */ u8 ambientBlue;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ u8 unk9;
    /* 0xA */ s16 unkA;
    /* 0xC */ s16 unkC;
} LightingContext; // size = 0x10

typedef struct {
    /* 0x000 */ s32 numOccupied;
    /* 0x004 */ s32 nextFree;
    /* 0x008 */ z_Light lights[32];
} LightsList; // size = 0x188

typedef struct {
    /* 0x0 */ s8 dirX;
    /* 0x1 */ s8 dirY;
    /* 0x2 */ s8 dirZ;
    /* 0x3 */ u8 red;
    /* 0x4 */ u8 green;
    /* 0x5 */ u8 blue;
    /* 0x6 */ u16 pad[3];
} LightInfoDirectionalParams; // size = 0xC

typedef struct {
    /* 0x0 */ s16 posX;
    /* 0x2 */ s16 posY;
    /* 0x4 */ s16 posZ;
    /* 0x6 */ u8 color[3];
    /* 0x9 */ u8 unk9; // func_80102880 sets this only for type 2, func_80102A64 draws something if this is set
    /* 0xA */ s16 radius;
} LightInfoPositionalParams; // size = 0xC

typedef struct {
    /* 0x00 */ u8 enablePosLights;
    /* 0x01 */ u8 numLights;
    /* 0x02 */ UNK_TYPE1 pad2[6];
    /* 0x08 */ Lights7 lights;
} LightMapper; // size = 0x80

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightInfoDirectionalParams params;
} LightInfoDirectional; // size = 0xE

typedef struct {
    /* 0x0 */ u8 type;
    /* 0x2 */ LightInfoPositionalParams params;
} LightInfoPositional; // size = 0xE

#endif
