#ifndef Z_EN_WALLMAS_H
#define Z_EN_WALLMAS_H

#include "global.h"
#include "objects/object_wallmaster/object_wallmaster.h"

#define WALLMASTER_GET_TYPE(thisx) ((thisx)->params)
#define WALLMASTER_GET_SWITCH_FLAG(thisx) (((thisx)->params >> 8) & 0xFF)
#define WALLMASTER_IS_FROZEN(thisx) ((thisx)->params & 0x80)

/**
 * This type determines under what conditions the Wallmaster will drop from the ceiling.
 * - WALLMASTER_TYPE_TIMER_ONLY: These Wallmasters don't check for anything to determine
 *   whether or not to drop; they just set a 130-frame timer and drop once it reaches 0.
 * - WALLMASTER_TYPE_PROXIMITY: These Wallmasters ensure that the player in within a certain
 *   distance of their current position (as dictated by detectionRadius); once the player
 *   enters that range, they set a 130-frame timer and drop once it reaches 0.
 * - WALLMASTER_TYPE_FLAG: These Wallmasters wait for a certain switch flag to be activated,
 *   as specified in their params. Once this switch is activated, they set an 81-frame timer
 *   and drop once it reaches 0.
 * 
 * While in the "waiting to drop" state, all Wallmaster variations can be forced to reset the
 * timer to 130 frames if the player enters certain states (e.g., if the player is no longer
 * touching the ground). Additionally, WALLMASTER_TYPE_PROXIMITY-type Wallmasters will reset
 * the timer to 130 frames if the player strays too far from the Wallmaster's current position.
 */
typedef enum {
    /* 0x00 */ WALLMASTER_TYPE_TIMER_ONLY,
    /* 0x01 */ WALLMASTER_TYPE_PROXIMITY,
    /* 0x02 */ WALLMASTER_TYPE_FLAG
} WallmasterType;

struct EnWallmas;

typedef void (*EnWallmasActionFunc)(struct EnWallmas*, GlobalContext*);

typedef struct EnWallmas {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnWallmasActionFunc actionFunc;
    /* 0x18C */ u8 drawDmgEffType;
    /* 0x18E */ s16 timer;
    /* 0x190 */ s16 switchFlag;
    /* 0x192 */ Vec3s jointTable[WALLMASTER_LIMB_MAX];
    /* 0x228 */ Vec3s morphTable[WALLMASTER_LIMB_MAX];
    /* 0x2C0 */ f32 yTarget;
    /* 0x2C4 */ f32 detectionRadius;
    /* 0x2C8 */ f32 drawDmgEffAlpha;
    /* 0x2CC */ f32 drawDmgEffScale;
    /* 0x2D0 */ f32 drawDmgEffFrozenSteamScale;
    /* 0x2D4 */ Vec3f limbPos[11];
    /* 0x358 */ ColliderCylinder collider;
} EnWallmas; // size = 0x3A4

extern const ActorInit En_Wallmas_InitVars;

#endif // Z_EN_WALLMAS_H
