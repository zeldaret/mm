#ifndef Z_DM_HINA_H
#define Z_DM_HINA_H

#include "global.h"

struct DmHina;

typedef void (*DmHinaActionFunc)(struct DmHina*, PlayState*);

typedef struct DmHina {
    /* 0x000 */ Actor actor;
    /* 0x144 */ DmHinaActionFunc actionFunc;
    /* 0x148 */ f32 maskScale;
    /* 0x14C */ f32 scale; // used to scale the remains size, light orb size/color and env lights
    /* 0x150 */ f32 drawOrbEffect;
    /* 0x154 */ f32 oscilationFactor;
    /* 0x158 */ f32 blueWarpPosY;
    /* 0x15C */ f32 yDimScaleFactor; // Scale factor used in y-dimension
    /* 0x160 */ Vec3f subCamEye;
    /* 0x16C */ Vec3f subCamAt;
    /* 0x178 */ UNK_TYPE1 unused[2];
    /* 0x17A */ s16 subCamId;
    /* 0x17C */ s16 timer;
    /* 0x17E */ u8 csState;
    /* 0x17F */ u8 lightOrbAlpha;
    /* 0x180 */ u8 isVisible;
} DmHina; // size = 0x184

#endif // Z_DM_HINA_H
