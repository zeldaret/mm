#ifndef Z64QUAKE_H
#define Z64QUAKE_H

#include "z64math.h"

struct PlayState;
struct Camera;

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 rollOffset;
    /* 0x1A */ s16 zoom;
    /* 0x1C */ f32 max; // Set to scaled max data of struct (mag for Vec3f), never used
} QuakeCamCalc; // size = 0x20

#define QUAKE_SPEED (1 << 0)
#define QUAKE_VERTICAL_MAG (1 << 1)
#define QUAKE_HORIZONTAL_MAG (1 << 2)
#define QUAKE_ZOOM (1 << 3)
#define QUAKE_ROLL_OFFSET (1 << 4)
#define QUAKE_SHAKE_PLANE_OFFSET_X (1 << 5)
#define QUAKE_SHAKE_PLANE_OFFSET_Y (1 << 6)
#define QUAKE_SHAKE_PLANE_OFFSET_Z (1 << 7)
#define QUAKE_COUNTDOWN (1 << 8)
#define QUAKE_IS_SHAKE_PERPENDICULAR (1 << 9)

typedef enum {
    /* 1 */ QUAKE_TYPE_1 = 1,
    /* 2 */ QUAKE_TYPE_2,
    /* 3 */ QUAKE_TYPE_3,
    /* 4 */ QUAKE_TYPE_4,
    /* 5 */ QUAKE_TYPE_5,
    /* 6 */ QUAKE_TYPE_6
} QuakeType;

u32 Quake_SetValue(s16 quakeIndex, s16 valueType, s16 value);
u32 Quake_SetSpeed(s16 quakeIndex, s16 speed);
u32 Quake_SetCountdown(s16 quakeIndex, s16 countdown);
s16 Quake_GetCountdown(s16 quakeIndex);
u32 Quake_SetQuakeValues(s16 quakeIndex, s16 verticalMag, s16 horizontalMag, s16 zoom, s16 rollOffset);
u32 Quake_SetQuakeValues2(s16 quakeIndex, s16 isShakePerpendicular, Vec3s shakePlaneOffset);
s16 Quake_Add(Camera* camera, u32 type);
s16 Quake_Calc(Camera* camera, QuakeCamCalc* camData);
u32 Quake_Remove(s16 index);
s32 Quake_NumActiveQuakes(void);
void Quake_Init(void);

#define DISTORTION_TYPE_0 (1 << 0)
#define DISTORTION_TYPE_2 (1 << 2)
#define DISTORTION_TYPE_3 (1 << 3)
#define DISTORTION_TYPE_4 (1 << 4)
#define DISTORTION_TYPE_5 (1 << 5)
#define DISTORTION_TYPE_6 (1 << 6)
#define DISTORTION_TYPE_7 (1 << 7)
#define DISTORTION_TYPE_8 (1 << 8)
#define DISTORTION_TYPE_9 (1 << 9)
#define DISTORTION_TYPE_A (1 << 10)
#define DISTORTION_TYPE_B (1 << 11)

void Distortion_SetCountdown(s16 countdown);
s16 Distortion_GetCountdown(void);
s16 Distortion_GetType(void);
void Distortion_SetType(s32 type);
void Distortion_ClearType(s32 type);
void Distortion_Init(PlayState* play);
void Distortion_Update(void);

#endif
