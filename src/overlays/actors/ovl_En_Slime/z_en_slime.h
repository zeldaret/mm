#ifndef Z_EN_SLIME_H
#define Z_EN_SLIME_H

#include "global.h"
#include "objects/object_slime/object_slime.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define EN_SLIME_LIMBPOS_COUNT 5

struct EnSlime;

typedef void (*EnSlimeActionFunc)(struct EnSlime*, PlayState*);

typedef struct EnSlime {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnSlimeActionFunc actionFunc;
    /* 0x148 */ u8 alpha;
    /* 0x149 */ u8 unk149; //Index into cycling asset load, probably texture, like a blink.
    /* 0x14A */ u8 damageEffectType;
    /* 0x14B */ char pad14B[1];
    /* 0x14C */ s16 timer; //? Used for different things? Like for respawn countdown, or just general behavior changes?
    /* 0x14E */ s16 idleRotY;
    /* 0x150 */ s16 respawnRotY;
    /* 0x152 */ s16 respawnTime;
    /* 0x154 */ Vec3f unk154;
    /* 0x160 */ void* dropObjectTex;
    /* 0x164 */ f32 effectAlpha;
    /* 0x168 */ f32 effectScale;
    /* 0x16C */ f32 frozenSteamScale;
    /* 0x170 */ f32 distLimit;
    /* 0x174 */ Vec3f respawnScale;
    /* 0x180 */ Vec3f limbPos[EN_SLIME_LIMBPOS_COUNT];
    /* 0x1BC */ ColliderCylinder collider;
} EnSlime; /* size = 0x208 */

typedef enum EnSlimeType {
    /* 0x0 */ EN_SLIME_TYPE_BLUE,
    /* 0x1 */ EN_SLIME_TYPE_GREEN,
    /* 0x2 */ EN_SLIME_TYPE_YELLOW,
    /* 0x3 */ EN_SLIME_TYPE_RED,
} EnSlimeType;

extern const ActorInit En_Slime_InitVars;

#endif // Z_EN_SLIME_H
