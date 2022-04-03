#ifndef Z_OBJ_DORA_H
#define Z_OBJ_DORA_H

#include "global.h"

struct ObjDora;

typedef void (*ObjDoraActionFunc)(struct ObjDora*, GlobalContext*);

typedef enum {
    /* 0x0 */ DORA_HIT_NONE,
    /* 0x1 */ DORA_HIT_LIGHT,
    /* 0x2 */ DORA_HIT_STRONG
} ObjDoraHitStrength;

typedef enum {
    /* 0x0 */ DORA_DMGEFF_NONE,
    /* 0xE */ DORA_DMGEFF_STRONG = 0xE,
    /* 0xF */ DORA_DMGEFF_LIGHT
} ObjDoraDamageEffect;

typedef struct ObjDora {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ ColliderTris colliderTris;
    /* 0x0164 */ ColliderTrisElement colliderTrisElements[6];
    /* 0x038C */ ObjDoraActionFunc actionFunc;
    /* 0x0390 */ Vec3f gongForce;
    /* 0x039C */ Vec2s gongAngle;
    /* 0x03A0 */ s16 lastGongHitType;
    /* 0x03A2 */ Vec2s gongRotation;
    /* 0x03A6 */ s16 rupeeDropTimer;
    /* 0x03A8 */ s16 collisionCooldownTimer;
    /* 0x03AA */ s16 unk3AA; // Set but not used
} ObjDora; // size = 0x3AC

extern const ActorInit Obj_Dora_InitVars;

#endif // Z_OBJ_DORA_H
