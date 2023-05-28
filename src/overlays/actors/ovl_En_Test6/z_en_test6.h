#ifndef Z_EN_TEST6_H
#define Z_EN_TEST6_H

#include "global.h"

struct EnTest6;

typedef void (*EnTest6ActionFunc)(struct EnTest6*, PlayState*);

#define SOTCS_GET_OCARINA_MODE(thisx) ((thisx)->params)

// Double Sot Cs:
// Cues from `SPOT00CutsceneData_009710`

// Reset Sot Cs:
// Cues from `SPOT00CutsceneData_0091A0` (Reset cycle: keep current playerForm)
// Cues from `SPOT00CutsceneData_009450` (Reset cycle: return to human playerForm)

// CueIds are a mix of cues externally from data above and internally based on a certain state

typedef enum SoTCsCueId {
    /* 0x00 */ SOTCS_CUEID_NONE,
    /* 0x01 */ SOTCS_CUEID_DOUBLE_1, // frames 11-44, 82-98, 99-100
    /* 0x02 */ SOTCS_CUEID_DOUBLE_0, // frames 10-11
    /* 0x03 */ SOTCS_CUEID_DOUBLE_2, // frames 44-59
    /* 0x04 */ SOTCS_CUEID_DOUBLE_3, // frames 59-69
    /* 0x05 */ SOTCS_CUEID_DOUBLE_4, // frames 69-82
    /* 0x06 */ SOTCS_CUEID_RESET_0,  // frames 0-5
    /* 0x07 */ SOTCS_CUEID_RESET_1,  // frames 5-800
    /* 0x08 */ SOTCS_CUEID_RESET_2,  // frames 800-1044
    /* 0x09 */ SOTCS_CUEID_DOUBLE_5, // frames 98-99
    /* 0x5A */ SOTCS_CUEID_INV_INIT = 90, // frame 0
    /* 0x5B */ SOTCS_CUEID_INV_SETUP_CLOCKS, // frames x-90
    /* 0x5D */ SOTCS_CUEID_INV_UNUSED = 93,
    /* 0x5F */ SOTCS_CUEID_INV_CLOCKS = 95,
    /* 0x63 */ SOTCS_CUEID_INV_END = 99
} SoTCsCueId;

typedef struct {
    /* 0x0 */ LightNode* node;
    /* 0x4 */ LightInfo info;
} SoTCsLight; // size = 0x14

#define SOTCS_INV_NUM_CLOCKS 6
#define SOTCS_DOUBLE_NUM_CLOCKS 51
#define SOTCS_RESET_NUM_CLOCKS 128
#define SOTCS_NUM_PARTICLES 64

typedef struct EnTest6 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTest6ActionFunc actionFunc;
    /* 0x148 */ Gfx* gfx;
    /* 0x14C */ f32 speed; // Used for clock distance and lights
    /* 0x150 */ f32 clockDist; // Radius from player
    /* 0x154 */ f32 clockSpeed;
    /* 0x158 */ f32 clockDistSpeed; // Radial Speed
    /* 0x15C */ f32 invSotEnvLerp;
    /* 0x160 */ f32 doubleSotEnvLerp;
    /* 0x164 */ SoTCsLight lights[2];
    /* 0x18C */ CutsceneCamera csCamInfo;
    /* 0x20C */ Vec3f clockPos[SOTCS_INV_NUM_CLOCKS];
    /* 0x254 */ Vec3f (*particles)[SOTCS_NUM_PARTICLES];
    /* 0x258 */ Vec3f subCamAt;
    /* 0x264 */ Vec3f subCamEye;
    /* 0x270 */ f32 subCamFov;
    /* 0x274 */ s16 cueId;
    /* 0x276 */ s16 drawType;
    /* 0x278 */ s16 clockYaw;
    /* 0x27A */ s16 timer;
    /* 0x27C */ s16 clockAngle;
    /* 0x27E */ s16 clockRingRotZ;
    /* 0x280 */ s16 clockColorGray;
    /* 0x282 */ s16 alpha;
    /* 0x284 */ s16 subCamId;
    /* 0x286 */ s16 screenFillAlpha; // As a ratio, 20 is an alpha of 255
} EnTest6; // size = 0x288

#endif // Z_EN_TEST6_H
