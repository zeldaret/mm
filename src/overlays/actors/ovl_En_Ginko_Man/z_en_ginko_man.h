#ifndef Z_EN_GINKO_MAN_H
#define Z_EN_GINKO_MAN_H

#include <global.h>

 typedef void (*EnGinkoManActionFunc)(struct EnGinkoMan*, GlobalContext*);

struct EnGinkoMan;

typedef struct EnGinkoMan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnGinkoManActionFunc actionFunc;
    /* 0x18C */ Vec3s limbDrawTbl[0x10];
    /* 0x1EC */ Vec3s transitionDrawTbl[0x10];
    /* 0x24C */ Vec3s limb15Rot;
    /* 0x252 */ Vec3s limb8Rot;
    /* 0x258 */ s16 curTextId;
    /* 0x25A */ s16 serviceFee;
    /* 0x25C */ s16 choiceDepositWithdrawl;
    /* 0x25E */ s16 newAccountFlag;
    /* 0x260 */ s16 stampChecked;
    /* 0x262 */ s16 previousBankValue;
    /* 0x264 */ s16 animTimer;
} EnGinkoMan; // size = 0x268

extern const ActorInit En_Ginko_Man_InitVars;

#define GINKOMAN_CHOICE_DEPOSIT   0
#define GINKOMAN_CHOICE_WITHDRAWL 1
#define GINKOMAN_CHOICE_CANCEL    2
#define GINKOMAN_CHOICE_RESET     0

#define GINKOMAN_CHOICE_YES  0
#define GINKOMAN_CHOICE_NO   1

extern SkeletonHeader*  D_0600C240;
extern AnimationHeader* D_060043F0;

extern AnimationHeader D_06004A7C; // these are segments found in our animation list
extern AnimationHeader D_06000AC4; // haven't figured out how to reference them from said list
extern AnimationHeader D_060008C0;

// values to get wallet capacity
extern u16 D_801C1E2C[]; // wallet capacities
extern u32 D_801C1DD0; // bit mask for wallet size in savecontext
extern u8 D_801C1E08; // bit shift on index to align

extern Gfx D_0600B1D8;

#endif // Z_EN_GINKO_MAN_H
