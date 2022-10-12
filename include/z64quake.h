#ifndef Z64QUAKE_H
#define Z64QUAKE_H

#include "z64math.h"

struct PlayState;
struct Camera;

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 upRollOffset;
    /* 0x1A */ s16 fovOffset;
    /* 0x1C */ f32 maxOffset; // Set to scaled max data of struct (mag for Vec3f), never used
} ShakeInfo; // size = 0x20



typedef enum {
    /* 0 */ QUAKE_TYPE_NONE,
    /* 1 */ QUAKE_TYPE_1, // Periodic, sustaining, random X perturbations
    /* 2 */ QUAKE_TYPE_2, // Aperiodic, sustaining, random X perturbations
    /* 3 */ QUAKE_TYPE_3, // Periodic, decaying
    /* 4 */ QUAKE_TYPE_4, // Aperiodic, decaying, random X perturbations
    /* 5 */ QUAKE_TYPE_5, // Periodic, sustaining
    /* 6 */ QUAKE_TYPE_6 // See below
} QuakeType;

s16 Quake_Request(Camera* camera, u32 type);

u32 Quake_SetSpeed(s16 index, s16 speed);
u32 Quake_SetPerturbations(s16 index, s16 y, s16 x, s16 fov, s16 roll);
u32 Quake_SetDuration(s16 index, s16 duration);
u32 Quake_SetOrientation(s16 index, s16 isRelativeToScreen, Vec3s orientation);

s16 Quake_GetTimeLeft(s16 index);
s32 Quake_NumActiveQuakes(void);
u32 Quake_RemoveRequest(s16 index);

void Quake_Init(void);
s16 Quake_Update(Camera* camera, ShakeInfo* camShake);

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

void Distortion_SetCountdown(s16 timer);
s16 Distortion_GetCountdown(void);
s16 Distortion_GetType(void);
void Distortion_SetType(s32 type);
void Distortion_ClearType(s32 type);
void Distortion_Init(PlayState* play);
void Distortion_Update(void);

#endif
