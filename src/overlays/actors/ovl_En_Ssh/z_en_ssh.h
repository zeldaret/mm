#ifndef Z_EN_SSH_H
#define Z_EN_SSH_H

#include "global.h"

struct EnSsh;

typedef void (*EnSshActionFunc)(struct EnSsh*, GlobalContext*);

#define SSH_STATE_STUNNED (1 << 0)
#define SSH_STATE_GROUND_START (1 << 2)
#define SSH_STATE_ATTACKED (1 << 3)
#define SSH_STATE_SPIN (1 << 4)
#define SSH_STATE_FATHER (1 << 5)

typedef enum {
    SSH_ANIM_UNK0, // Unused animation. Possibly being knocked back?
    SSH_ANIM_UP,
    SSH_ANIM_WAIT,
    SSH_ANIM_LAND,
    SSH_ANIM_DROP,
    SSH_ANIM_UNK5, // Slower version of ANIM_DROP
    SSH_ANIM_UNK6  // Faster repeating version of ANIM_UNK0
} EnSshAnimation;

#define ENSSH_IS_CHILD(thisx) ((thisx)->params & 0xF)

typedef struct EnSsh {
    /* 0x0000 */ Actor actor;
    /* 0x0144 */ SkelAnime skelAnime;
    /* 0x0188 */ Vec3s jointTable[30];
    /* 0x023C */ Vec3s morphtable[30];
    /* 0x02F0 */ EnSshActionFunc actionFunc;
    /* 0x02F4 */ ColliderCylinder collider1[6];
    /* 0x04BC */ ColliderJntSph collider2;
    /* 0x04DC */ ColliderJntSphElement collider2Elements[1];
    /* 0x051C */ s16 initialYaw;
    /* 0x051E */ s16 maxTurnRate;
    /* 0x0520 */ s16 unkTimer;
    /* 0x0522 */ s16 spinTimer;
    /* 0x0524 */ s16 hitTimer;
    /* 0x0526 */ s16 invincibilityTimer;
    /* 0x0528 */ s16 sfxTimer;
    /* 0x052A */ s16 stunTimer;
    /* 0x052C */ s16 animTimer;
    /* 0x052E */ s16 swayTimer;
    /* 0x0530 */ s32 blureIdx;
    /* 0x0534 */ f32 colliderScale;
    /* 0x0538 */ f32 floorHeightOffset;
    /* 0x053C */ Vec3f ceilingPos;
    /* 0x0548 */ UNK_TYPE1 unk_548[0x78];
    /* 0x05C0 */ s16 swayAngle;
    /* 0x05C2 */ u16 stateFlags;
    /* 0x05C4 */ u8 hitCount;
    /* 0x05C6 */ s16 blinkState;
    /* 0x05C8 */ s16 blinkTimer;
} EnSsh; // size = 0x5CC

extern const ActorInit En_Ssh_InitVars;

#endif // Z_EN_SSH_H
