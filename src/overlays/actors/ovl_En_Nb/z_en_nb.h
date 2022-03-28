#ifndef Z_EN_NB_H
#define Z_EN_NB_H

#include "global.h"
#include "objects/object_nb/object_nb.h"

struct EnNb;

typedef void (*EnNbActionFunc)(struct EnNb*, GlobalContext*);
typedef s32 (*EnNbActionFunc2)(struct EnNb*, GlobalContext*);

typedef struct EnNb {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnNbActionFunc actionFunc;
    /* 0x18C */ EnNbActionFunc unk_18C;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ u8 unk_1DC;
    /* 0x1DD */ char unk_1DD[0x3];
    /* 0x1E0 */ UNK_PTR unk_1E0;
    /* 0x1E4 */ s32 unk_1E4;
    /* 0x1E8 */ Actor* unk_1E8;
    /* 0x1EC */ char unk_1EC[0x04];
    /* 0x1F0 */ Vec3f unk_1F0;
    /* 0x1FC */ Vec3s unk_1FC;
    /* 0x202 */ Vec3s jointTable[OBJECT_NB_LIMB_MAX];
    /* 0x232 */ Vec3s morphTable[OBJECT_NB_LIMB_MAX];
    /* 0x262 */ u16 unk_262; // bitpack
    /* 0x264 */ u16 textId;
    /* 0x266 */ char unk_266[0x02];
    /* 0x268 */ f32 unk_268; // playSpeedBackup?
    /* 0x26C */ f32 unk_26C; // Related to unk_270
    /* 0x270 */ f32 unk_270; // headDisplacement? controls how much the upper part of the head moves when she talks
    /* 0x274 */ f32 unk_274;
    /* 0x278 */ char unk_278[0x04];
    /* 0x27C */ s16 headRot; // Slightly rotates head when talking
    /* 0x27E */ s16 unk_27E;
    /* 0x280 */ s16 unk_280; // Time related
    /* 0x282 */ s16 unk_282; // timer?
    /* 0x284 */ s16 unk_284; // storyState?
    /* 0x286 */ s16 unk_286; // another timer?
    /* 0x288 */ s16 unk_288;
    /* 0x28A */ char unk_28A[0x02];
    /* 0x28C */ EnNbActionFunc2 unk_28C;
    /* 0x290 */ s32 unk_290; // animIndex?
    /* 0x294 */ char unk_294[0x4];
    /* 0x294 */ s32 unk_298;
} EnNb; // size = 0x29C

extern const ActorInit En_Nb_InitVars;

#endif // Z_EN_NB_H
