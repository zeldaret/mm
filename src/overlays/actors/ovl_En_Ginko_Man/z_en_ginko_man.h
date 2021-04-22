#ifndef Z_EN_GINKO_MAN_H
#define Z_EN_GINKO_MAN_H

#include <global.h>

 typedef void (*EnGinkoManActionFunc)(struct EnGinkoMan*, GlobalContext*);

struct EnGinkoMan;

typedef struct EnGinkoMan {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x124];
    /* 0x144 */ SkelAnime anime;
    /* 0x188 */ EnGinkoManActionFunc actionFunc;
    /* 0x18C */ Vec3s unk18C;
    /* 0x192 */ UNK_TYPE1 unk192[0x5A];
    /* 0x1EC */ Vec3s unk1EC;
    /* 0x1F2 */ UNK_TYPE1 unk1F2[0x5A];
    /* 0x24C */ Vec3s unk24C;
    /* 0x252 */ Vec3s unk252;
    /* 0x258 */ s16 lastText;
    /* 0x25A */ s16 unk25A;
    /* 0x25C */ s16 unk25C;
    /* 0x25E */ s16 unk25E;
    /* 0x260 */ s16 unk260;
    /* 0x262 */ s16 unk262; // padding
    /* 0x264 */ s16 unk264;
    /* 0x266 */ UNK_TYPE1 unk266[0x2];
} EnGinkoMan; // size = 0x268

extern const ActorInit En_Ginko_Man_InitVars;

extern SkeletonHeader* D_0600C240;
extern AnimationHeader* D_060043F0; // 0x60043F0;

extern AnimationHeader D_06004A7C;
extern AnimationHeader D_06000AC4;
extern AnimationHeader D_060008C0;

extern UNK_TYPE D_801C1DD0;
extern u8 D_801C1E08;

extern Gfx D_0600B1D8;

extern u16 D_801C1E2C;

#endif // Z_EN_GINKO_MAN_H
