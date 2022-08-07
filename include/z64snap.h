#ifndef Z64_SNAP_H
#define Z64_SNAP_H

#include "PR/ultratypes.h"
#include "z64actor.h"

typedef s32 (*PictoValidationFunc)(struct PlayState*, Actor*);

typedef struct {
    /* 0x000 */ Actor actor;
    /* 0x144 */ PictoValidationFunc validationFunc;
} PictoActor;

// Picto box flags

typedef enum {
    // Used externally, set and read by actors
    /* 0x00 */ PICTOGRAPH_0,
    /* 0x01 */ PICTOGRAPH_IN_SWAMP,
    /* 0x02 */ PICTOGRAPH_MONKEY,
    /* 0x03 */ PICTOGRAPH_BIG_OCTO,
    /* 0x04 */ PICTOGRAPH_LULU_HEAD,
    /* 0x05 */ PICTOGRAPH_LULU_RIGHT_ARM,
    /* 0x06 */ PICTOGRAPH_LULU_LEFT_ARM, // Need all three of these to qualify as a good picture
    /* 0x07 */ PICTOGRAPH_SCARECROW,
    /* 0x08 */ PICTOGRAPH_TINGLE,
    /* 0x09 */ PICTOGRAPH_PIRATE_GOOD,
    /* 0x0A */ PICTOGRAPH_DEKU_KING,
    /* 0x0B */ PICTOGRAPH_PIRATE_TOO_FAR, // overlaps with PICTOGRAPH_PIRATE_GOOD, but that is checked first

    // Used internally, test for failures of position, angle etc.
    /* 0x3B */ PICTOGRAPH_BEHIND_COLLISION = 0x3B,
    /* 0x3C */ PICTOGRAPH_BEHIND_BG,
    /* 0x3D */ PICTOGRAPH_NOT_IN_VIEW,
    /* 0x3E */ PICTOGRAPH_BAD_ANGLE,
    /* 0x3F */ PICTOGRAPH_BAD_DISTANCE
} PictographFlag;

// The following macros are subject to renaming once the capture system is better understood
#define PICTO_RESOLUTION_HORIZONTAL 150
#define PICTO_RESOLUTION_VERTICAL 105
#define PICTO_CAPTURE_REGION_TOPLEFT_X ((SCREEN_WIDTH - PICTO_RESOLUTION_HORIZONTAL) / 2)
#define PICTO_CAPTURE_REGION_TOPLEFT_Y ((SCREEN_HEIGHT - PICTO_RESOLUTION_VERTICAL) / 2)

s32 Snap_RecordPictographedActors(PlayState* play);
void Snap_SetFlag(s32 flag);
void Snap_UnsetFlag(s32 flag);
u32 Snap_CheckFlag(s32 flag);
s16 Snap_AbsS(s16 val);
s32 Snap_ValidatePictograph(PlayState* play, Actor* actor, s32 flag, Vec3f* pos, Vec3s* rot, f32 distanceMin, f32 distanceMax, s16 angleRange);

#endif
