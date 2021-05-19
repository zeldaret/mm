#ifndef Z_EN_FG_H
#define Z_EN_FG_H

#include <global.h>

struct EnFg;

typedef void (*EnFgActionFunc)(struct EnFg*, GlobalContext*);

// Based on the envColor data. Related to params but mostly unused.
typedef enum {
    /* 00 */ FROG_YELLOW,   // Mountain Village
    /* 01 */ FROG_CYAN,     // Woodfall Temple
    /* 02 */ FROG_PINK,     // Great Bay Temple
    /* 03 */ FROG_BLUE,     // Southern Swamp
    /* 04 */ FROG_WHITE,    // Laundry Pool
    /* 05 */ FROG_BLACK,    // Extra frog??? Uncertain
} FrogType;

typedef struct {
    /* 0x00 */ AnimationHeader* animationSeg;
    /* 0x04 */ f32 playbackSpeed;
    /* 0x08 */ s16 frame;
    /* 0x0A */ s16 frameCount;
    /* 0x0C */ u8 mode;
    /* 0x0E */ s16 transitionRate;
} EnFgAnimation; // size = 0x10

typedef struct {
    /* 0x0000 */ u8 type;
    /* 0x0001 */ u8 timer;
    /* 0x0004 */ f32 xyScale;
    /* 0x0008 */ char unk_08[0xC];
    /* 0x0014 */ Vec3f pos;
    /* 0x0020 */ Vec3f unk_20; // Likely acceleration, set to 0 but unused
    /* 0x002C */ Vec3f velocity;
    /* 0x0038 */ char unk_38[0x4];
} EnFgEffectDust; // size = 0x3C

typedef struct EnFg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFgActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s limbDrawTbl[24];
    /* 0x268 */ Vec3s transitionDrawTbl[24];
    /* 0x2F8 */ s16 timer;
    /* 0x2FA */ s16 unk_2FA; // Scales y-velocity of actor
    /* 0x2FC */ EnFgEffectDust dustEffect[10];
} EnFg; // size = 0x554

#endif // Z_EN_FG_H
