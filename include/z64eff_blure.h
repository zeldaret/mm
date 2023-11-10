#ifndef Z64EFF_BLURE_H
#define Z64EFF_BLURE_H

#include "ultra64.h"

#include "color.h"
#include "z64math.h"

struct GraphicsContext;

typedef struct {
    /* 0x00 */ s32 state;
    /* 0x04 */ s32 timer;
    /* 0x08 */ Vec3s p1;
    /* 0x0E */ Vec3s p2;
    /* 0x14 */ u16 flags;
} EffectBlureElement; // size = 0x18

typedef struct {
    /* 0x000 */ char unk_00[0x184];
    /* 0x184 */ u8 p1StartColor[4];
    /* 0x188 */ u8 p2StartColor[4];
    /* 0x18C */ u8 p1EndColor[4];
    /* 0x190 */ u8 p2EndColor[4];
    /* 0x194 */ s32 elemDuration;
    /* 0x198 */ s32 unkFlag;
    /* 0x19C */ s32 calcMode;
} EffectBlureInit1; // size = 0x1A0

typedef struct {
    /* 0x00 */ s32 calcMode;
    /* 0x04 */ u16 flags;
    /* 0x06 */ s16 addAngleChange;
    /* 0x08 */ u8 p1StartColor[4];
    /* 0x0C */ u8 p2StartColor[4];
    /* 0x10 */ u8 p1EndColor[4];
    /* 0x14 */ u8 p2EndColor[4];
    /* 0x18 */ u8 elemDuration;
    /* 0x19 */ u8 unkFlag;
    /* 0x1A */ u8 drawMode; // 0: simple; 1: simple with alt colors; 2+: smooth
    /* 0x1B */ u8 mode4Param;
    /* 0x1C */ Color_RGBA8 altPrimColor; // used with drawMode 1
    /* 0x20 */ Color_RGBA8 altEnvColor; // used with drawMode 1
} EffectBlureInit2; // size = 0x24

typedef struct {
    /* 0x000 */ EffectBlureElement elements[16];
    /* 0x180 */ s32 calcMode;
    /* 0x184 */ f32 mode4Param;
    /* 0x188 */ u16 flags;
    /* 0x18A */ s16 addAngleChange;
    /* 0x18C */ s16 addAngle;
    /* 0x18E */ u8 p1StartColor[4];
    /* 0x192 */ u8 p2StartColor[4];
    /* 0x196 */ u8 p1EndColor[4];
    /* 0x19A */ u8 p2EndColor[4];
    /* 0x19E */ u8 numElements; // "now_edge_num"
    /* 0x19F */ u8 elemDuration;
    /* 0x1A0 */ u8 unkFlag;
    /* 0x1A1 */ u8 drawMode; // 0: simple; 1: simple with alt colors; 2+: smooth
    /* 0x1A2 */ Color_RGBA8 altPrimColor; // used with drawMode 1
    /* 0x1A6 */ Color_RGBA8 altEnvColor; // used with drawMode 1
} EffectBlure; // size = 0x1AC

void EffectBlure_AddVertex(EffectBlure* this, Vec3f* p1, Vec3f* p2);
void EffectBlure_AddSpace(EffectBlure* this);
void EffectBlure_Init1(void* thisx, void* initParamsx);
void EffectBlure_Init2(void* thisx, void* initParamsx);
void EffectBlure_Destroy(void* thisx);
s32 EffectBlure_Update(void* thisx);
void EffectBlure_Draw(void* thisx, struct GraphicsContext* gfxCtx);

#endif
