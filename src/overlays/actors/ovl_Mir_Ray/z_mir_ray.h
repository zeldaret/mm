#ifndef Z_MIR_RAY_H
#define Z_MIR_RAY_H

#include "global.h"

struct MirRay;

#define MIRRAY_LOCATION(thisx) ((thisx)->params)

// Locations of light beams in sMirRayData
typedef enum {
    /* 0 */ MIRRAY_SPIRIT_BOMBCHUIWAROOM_DOWNLIGHT,
    /* 1 */ MIRRAY_SPIRIT_SUNBLOCKROOM_DOWNLIGHT,
    /* 2 */ MIRRAY_SPIRIT_SINGLECOBRAROOM_DOWNLIGHT,
    /* 3 */ MIRRAY_SPIRIT_ARMOSROOM_DOWNLIGHT,
    /* 4 */ MIRRAY_SPIRIT_TOPROOM_DOWNLIGHT,
    /* 5 */ MIRRAY_SPIRIT_TOPROOM_CEILINGMIRROR,
    /* 6 */ MIRRAY_SPIRIT_SINGLECOBRAROOM_COBRA,
    /* 7 */ MIRRAY_SPIRIT_TOPROOM_COBRA1,
    /* 8 */ MIRRAY_SPIRIT_TOPROOM_COBRA2,
    /* 9 */ MIRRAY_GANONSCASTLE_SPIRITTRIAL_DOWNLIGHT,
    /* 10 */ MIRRAY_MAX,
} MirRayBeamLocations;

typedef struct MirRay {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderJntSph collider1;
    /* 0x0164 */ ColliderJntSphElement collider1Elements[1];
    /* 0x01A4 */ ColliderQuad collider2;
    /* 0x0224 */ f32 reflectIntensity; // Reflection occurs if it is positive, brightness depends on it
    /* 0x0228 */ Vec3f shieldCorners[6];
    /* 0x0270 */ f32 reflectRange;
    /* 0x0274 */ Vec3f sourcePt;
    /* 0x0280 */ Vec3f poolPt;
    /* 0x028C */ s16 sourceEndRad;
    /* 0x028E */ s16 poolEndRad;
    /* 0x0290 */ s16 lightPointRad;
    /* 0x0294 */ LightNode* lightNode;
    /* 0x0298 */ LightInfo lightInfo;
    /* 0x02A6 */ u8 unLit; // Conditioned on. set in Cobra?
} MirRay; // size = 0x2A8

extern const ActorInit Mir_Ray_InitVars;

#endif // Z_MIR_RAY_H
