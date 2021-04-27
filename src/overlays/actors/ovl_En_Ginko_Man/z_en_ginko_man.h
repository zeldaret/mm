#ifndef Z_EN_GINKO_MAN_H
#define Z_EN_GINKO_MAN_H

#include <global.h>

 typedef void (*EnGinkoManActionFunc)(struct EnGinkoMan*, GlobalContext*);

struct EnGinkoMan;

typedef struct EnGinkoMan {
    /* 0x000 */ Actor actor;
    ///* 0x144 */ char unk_144[0x124];
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnGinkoManActionFunc actionFunc;
    /* 0x18C */ Vec3s limbDrawTbl[0x10];
    ///* 0x192 */ UNK_TYPE1 unk192[0x5A];
    /* 0x1EC */ Vec3s transitionDrawTbl[0x10];
    ///* 0x1F2 */ UNK_TYPE1 unk1F2[0x5A];
    /* 0x24C */ Vec3s limb15Rot;
    /* 0x252 */ Vec3s limb8Rot;
    /* 0x258 */ s16 lastText;
    /* 0x25A */ s16 unk25A; // copied from save context
    /* 0x25C */ s16 unk25C; // copied from msgCtx -> unk12022
    /* 0x25E */ s16 unk25E; // think this: double dialogue for opening acount with smol deposit
    /* 0x260 */ s16 unk260; // busy with dialogue?
    /* 0x262 */ s16 previousBankValue;
    /* 0x264 */ s16 unk264; // animation timer of some sort
    /* 0x266 */ UNK_TYPE1 unk266[0x2];
} EnGinkoMan; // size = 0x268

extern const ActorInit En_Ginko_Man_InitVars;

extern SkeletonHeader* D_0600C240;
extern AnimationHeader* D_060043F0; // 0x60043F0;

extern AnimationHeader D_06004A7C;
extern AnimationHeader D_06000AC4;
extern AnimationHeader D_060008C0;

extern u32 D_801C1DD0;
extern u8 D_801C1E08;

extern Gfx D_0600B1D8;

extern u16 D_801C1E2C[];

#endif // Z_EN_GINKO_MAN_H
