#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"
#include "objects/object_nb/object_nb.h"

struct EnNb;

typedef void (*EnNbActionFunc)(struct EnNb*, PlayState*);
typedef s32 (*EnNbUnkFunc)(Actor*, PlayState*);

typedef enum EnNbAnimation {
    /* -1 */ EN_NB_ANIM_INVALID = -1,
    /*  0 */ EN_NB_ANIM_0,
    /*  1 */ EN_NB_ANIM_1,
    /*  2 */ EN_NB_ANIM_TALK_ONCE,
    /*  3 */ EN_NB_ANIM_TALK_LOOP,
    /*  4 */ EN_NB_ANIM_ANGRY,
    /*  5 */ EN_NB_ANIM_RELIEVED,
} EnNbAnimation;

typedef struct EnNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnNbActionFunc actionFunc;
    /* 0x18C */ EnNbActionFunc unk_18C;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ u8 schResultValue;
    /* 0x1E0 */ UNK_PTR unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ Actor* unk_1E8;
    /* 0x1EC */ char unk_1EC[0x04];
    /* 0x1F0 */ Vec3f headComputedPos;
    /* 0x1FC */ Vec3s headComputedRot;
    /* 0x202 */ Vec3s jointTable[NB_LIMB_MAX];
    /* 0x232 */ Vec3s morphTable[NB_LIMB_MAX];
    /* 0x262 */ u16 stateFlags;
    /* 0x264 */ u16 textId;
    /* 0x268 */ f32 animPlaySpeed;
    /* 0x26C */ f32 unk_26C; // Related to unk_270
    /* 0x270 */ f32 unk_270; // headDisplacement? controls how much the upper part of the head moves when she talks
    /* 0x274 */ f32 unk_274;
    /* 0x278 */ char unk_278[0x04];
    /* 0x27C */ s16 headRotZ; // Slightly rotates head when talking
    /* 0x27E */ s16 headRotY;
    /* 0x280 */ s16 timePathTimeSpeed;
    /* 0x282 */ s16 unk_282; // timer?
    /* 0x284 */ s16 unk_284; // storyState?
    /* 0x286 */ s16 unk_286; // another timer?
    /* 0x288 */ s16 unk_288;
    /* 0x28C */ EnNbUnkFunc unk_28C;
    /* 0x290 */ EnNbAnimation animIndex;
    /* 0x294 */ char unk_294[0x4];
    /* 0x294 */ TextState prevTalkState;
} EnNb; // size = 0x29C

#define EN_NB_FLAG_NONE (0)
#define EN_NB_FLAG_1    (1 << 0)
#define EN_NB_FLAG_2    (1 << 1)
#define EN_NB_FLAG_4    (1 << 2)
#define EN_NB_FLAG_8    (1 << 3)
#define EN_NB_FLAG_10   (1 << 4)
#define EN_NB_FLAG_20   (1 << 5)
#define EN_NB_FLAG_40   (1 << 6)
#define EN_NB_FLAG_80   (1 << 7)
#define EN_NB_FLAG_100  (1 << 8)
#define EN_NB_FLAG_200  (1 << 9)
#define EN_NB_FLAG_400  (1 << 10)

#endif // Z_EN_NB_H
