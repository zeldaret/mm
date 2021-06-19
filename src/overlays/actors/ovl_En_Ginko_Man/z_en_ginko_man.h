#ifndef Z_EN_GINKO_MAN_H
#define Z_EN_GINKO_MAN_H

#include <global.h>

struct EnGinkoMan;

 typedef void (*EnGinkoManActionFunc)(struct EnGinkoMan*, GlobalContext*);

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
    /* 0x25E */ s16 isNewAccount;
    /* 0x260 */ s16 isStampChecked;
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

extern FlexSkeletonHeader object_ginko_skeleton[];
extern Gfx object_ginko_limb15_dlist[];

extern AnimationHeader object_ginko_floorsmacking_anim[];
extern AnimationHeader object_ginko_sitting_anim[];
extern AnimationHeader object_ginko_amazed_anim[];
extern AnimationHeader object_ginko_stamp_reach_anim[];
extern AnimationHeader object_ginko_advertising_anim[];

typedef enum {
    /* 0 */ GINKO_FLOORSMACKING,
    /* 1 */ GINKO_SITTING,
    /* 2 */ GINKO_REACHING,
    /* 3 */ GINKO_AMAZED,
    /* 4 */ GINKO_ADVERTISING,
} GinkoAnimationIndex;

// values to get wallet capacity
extern u16 D_801C1E2C[]; // wallet capacities

#endif // Z_EN_GINKO_MAN_H
