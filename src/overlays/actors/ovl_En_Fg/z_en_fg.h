#ifndef Z_EN_FG_H
#define Z_EN_FG_H

#include <global.h>

struct EnFg;

typedef void (*EnFgActionFunc)(struct EnFg*, GlobalContext*);

// Based on the envColor data. Related to params but mostly unused.
typedef enum {
    /* 0x00 */ FG_YELLOW,
    /* 0x01 */ FG_CYAN,
    /* 0x02 */ FG_PINK,
    /* 0x03 */ FG_BLUE,
    /* 0x04 */ FG_WHITE,
    /* 0x05 */ FG_BLACK, // All frogs are blackened when hit by an explosion
} FrogType;

typedef enum {
    /* 0x00 */ FG_DMGEFFECT_NONE,
    /* 0x01 */ FG_DMGEFFECT_EXPLOSION, // Bomb or bombchu, not powderkeg
    /* 0x02 */ FG_DMGEFFECT_DEKUSTICK,
    /* 0x03 */ FG_DMGEFFECT_HOOKSHOT,
    /* 0x04 */ FG_DMGEFFECT_ARROW,
    /* 0x05 */ FG_DMGEFFECT_ICEARROW,
} FrogDamageEffect;

typedef struct {
    /* 0x0000 */ u8 type;
    /* 0x0001 */ u8 timer;
    /* 0x0004 */ f32 xyScale;
    /* 0x0008 */ UNK_TYPE1 unk_08[0xC];
    /* 0x0014 */ Vec3f pos;
    /* 0x0020 */ Vec3f unk_20; // Likely acceleration, set to 0 but unused
    /* 0x002C */ Vec3f velocity;
    /* 0x0038 */ UNK_TYPE1 unk_38[0x4];
} EnFgEffectDust; // size = 0x3C

typedef struct EnFg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnFgActionFunc actionFunc;
    /* 0x148 */ SkelAnime skelAnime;
    /* 0x18C */ ColliderCylinder collider;
    /* 0x1D8 */ Vec3s limbDrawTbl[24];
    /* 0x268 */ Vec3s transitionDrawTbl[24];
    /* 0x2F8 */ s16 timer;
    /* 0x2FA */ s16 bounceCounter;
    /* 0x2FC */ EnFgEffectDust dustEffect[10];
} EnFg; // size = 0x554

#endif // Z_EN_FG_H
