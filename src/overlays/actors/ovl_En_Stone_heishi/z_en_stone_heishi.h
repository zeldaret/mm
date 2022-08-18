#ifndef Z_EN_STONE_HEISHI_H
#define Z_EN_STONE_HEISHI_H

#include "global.h"

struct EnStoneheishi;

typedef void (*EnStoneheishiActionFunc)(struct EnStoneheishi*, PlayState*);

typedef struct EnStoneheishi {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;                   /* inferred */
    /* 0x188 */ Vec3s unk188;                       /* inferred */
    /* 0x18E */ char pad18E[0x60];                  /* maybe part of unk188[0x11]? */
    /* 0x1EE */ Vec3s unk1EE;                       /* inferred */
    /* 0x1F4 */ char pad1F4[0x60];                  /* maybe part of unk1EE[0x11]? */
    /* 0x254 */ EnStoneheishiActionFunc actionFunc;
    /* 0x258 */ s16 unk258;                         /* inferred */
    /* 0x25A */ s16 unk25A;                         /* inferred */
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;                         /* inferred */
    /* 0x260 */ s16 unk260;                         /* inferred */
    /* 0x262 */ char pad262[2];
    /* 0x264 */ s32 animMode;                         /* inferred */
    /* 0x268 */ s16 unk268;                         /* inferred */
    /* 0x26A */ s16 unk26A;                         /* inferred */
    /* 0x26C */ f32 endFrame;                         /* inferred */
    /* 0x270 */ s16 unk270;                         /* inferred */
    /* 0x272 */ s16 unk272;                         /* inferred */
    /* 0x274 */ s16 unk274;                         /* inferred */
    /* 0x276 */ u8 unk276;
    /* 0x277 */ u8 unk277;                          /* inferred */
    /* 0x278 */ ColliderCylinder unk278;            /* inferred */
} EnStoneheishi; // size = 0x2C4

extern const ActorInit En_Stone_heishi_InitVars;

#endif // Z_EN_STONE_HEISHI_H
