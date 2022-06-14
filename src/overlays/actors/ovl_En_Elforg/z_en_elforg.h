#ifndef Z_EN_ELFORG_H
#define Z_EN_ELFORG_H

#include "global.h"

#define STRAY_FAIRY_TYPE(thisx) ((thisx)->params & 0xF)
#define STRAY_FAIRY_GET_PARAM_1C0(thisx) ((thisx)->params & 0x1C0)
#define STRAY_FAIRY_FLAG(thisx) (((thisx)->params & 0xFE00) >> 9)

#define STRAY_FAIRY_FLAG_MOVES_QUICKLY_TO_HOME (1 << 0)
#define STRAY_FAIRY_FLAG_SPARKLES_AND_SHRINKS (1 << 1)
#define STRAY_FAIRY_FLAG_CIRCLES_QUICKLY_IN_FOUNTAIN (1 << 2)
#define STRAY_FAIRY_FLAG_GREAT_FAIRYS_MASK_EQUIPPED (1 << 3)

typedef enum {
    STRAY_FAIRY_TYPE_FREE_FLOATING,            // The ones just floating around
    STRAY_FAIRY_TYPE_FAIRY_FOUNTAIN,           // The ones already present when you enter a Fairy Fountain
    STRAY_FAIRY_TYPE_BUBBLE,                   // The ones trapped in bubbles
    STRAY_FAIRY_TYPE_CLOCK_TOWN,               // The free-floating Stray Fairies in Clock Town
    STRAY_FAIRY_TYPE_ENEMY,                    // The ones trapped inside enemies
    STRAY_FAIRY_TYPE_COLLIDER,                 // Unused in retail. The fairy is hidden until the collider is hit
    STRAY_FAIRY_TYPE_CHEST,                    // The ones in treasure chests
    STRAY_FAIRY_TYPE_COLLECTIBLE,              // The ones in boxes, pots, beehives, etc.
    STRAY_FAIRY_TYPE_TURN_IN_TO_FAIRY_FOUNTAIN // The ones you "turn in" by walking into a Fairy Fountain
} StrayFairyType;

typedef enum {
    STRAY_FAIRY_AREA_CLOCK_TOWN,
    STRAY_FAIRY_AREA_WOODFALL,
    STRAY_FAIRY_AREA_SNOWHEAD,
    STRAY_FAIRY_AREA_GREAT_BAY,
    STRAY_FAIRY_AREA_STONE_TOWER,
    STRAY_FAIRY_AREA_MAX
} StrayFairyArea;

typedef enum {
    /*  0 */ STRAY_FAIRY_LIMB_NONE,
    /*  1 */ STRAY_FAIRY_LIMB_RIGHT_FACING_HEAD,
    /*  2 */ STRAY_FAIRY_LIMB_LEFT_WING,
    /*  3 */ STRAY_FAIRY_LIMB_RIGHT_WING,
    /*  4 */ STRAY_FAIRY_LIMB_GLOW,
    /*  5 */ STRAY_FAIRY_LIMB_TORSO,
    /*  6 */ STRAY_FAIRY_LIMB_RIGHT_ARM,
    /*  7 */ STRAY_FAIRY_LIMB_PELVIS_AND_LEGS,
    /*  8 */ STRAY_FAIRY_LIMB_LEFT_ARM,
    /*  9 */ STRAY_FAIRY_LIMB_LEFT_FACING_HEAD,
    /* 10 */ STRAY_FAIRY_LIMB_MAX,
} StrayFairyLimbs;

struct EnElforg;

typedef void (*EnElforgActionFunc)(struct EnElforg*, GlobalContext*);

typedef struct EnElforg {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[STRAY_FAIRY_LIMB_MAX];
    /* 0x1C4 */ ColliderCylinder collider;
    /* 0x210 */ Actor* enemy;
    /* 0x214 */ u16 flags;
    /* 0x216 */ s16 direction; // negative when facing right, positive when facing left
    /* 0x218 */ s16 area;
    /* 0x21C */ s32 timer;
    /* 0x220 */ s32 secondaryTimer;
    /* 0x224 */ f32 targetSpeedXZ;
    /* 0x228 */ f32 targetDistanceFromHome;
    /* 0x22C */ EnElforgActionFunc actionFunc;
} EnElforg; // size = 0x230

extern const ActorInit En_Elforg_InitVars;

#endif // Z_EN_ELFORG_H
