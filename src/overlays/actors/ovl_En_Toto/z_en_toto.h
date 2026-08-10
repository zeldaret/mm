#ifndef Z_EN_TOTO_H
#define Z_EN_TOTO_H

#include "global.h"
#include "face_change.h"
#include "assets/objects/object_zm/object_zm.h"

struct EnToto;

typedef void (*EnTotoActionFunc)(struct EnToto*, PlayState*);
typedef s32 (*EnTotoTalkFunc)(struct EnToto*, PlayState*);

#define ENTOTO_GET_ZORA_SPOKEN_FLAG(thisx) ((thisx)->params & 0x7F)
#define ENTOTO_GET_OTHER_SPOKEN_FLAG(thisx) (((thisx)->params >> 7) & 0x7F)
#define ENTOTO_GET_DEKU_SPOKEN_FLAG(thisx) ((thisx)->home.rot.x)

typedef struct EnTotoSpeakData {
    /* 0x0 */ u8 talkActionIndex;
    /* 0x1 */ u8 argument;              // Used for various functions, including as a timer
    /* 0x2 */ u16 textId;
} EnTotoSpeakData; // size = 0x4

typedef struct EnTotoSpotlight {
    /* 0x0 */ u16 promptTextId;
    /* 0x2 */ u16 wrongLightTextId;
    /* 0x4 */ u16 rightLightTextId;
    /* 0x6 */ Vec3s pos;
} EnTotoSpotlight; // size = 0xC

typedef struct EnToto {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ Vec3s jointTable[OBJECT_ZM_LIMB_MAX];
    /* 0x1F4 */ Vec3s morphTable[OBJECT_ZM_LIMB_MAX];
    /* 0x260 */ FaceChange faceChange;
    /* 0x264 */ ColliderCylinder collider;
    /* 0x2B0 */ u8 actionFuncIndex;
    /* 0x2B1 */ u8 timer;          // Used for various timers?
    /* 0x2B2 */ s8 csId;
    /* 0x2B3 */ u8 windFishFormsPlayed;
    /* 0x2B4 */ u8 animIndex;
    /* 0x2B5 */ u8 cueId;     /* Cue 4: Give Circus Leader's Mask // Cue 3: "Okay! That feels good!" // Cue 2: Turn around to look at Gorman // Cue 1: Turn back around to stage*/
    /* 0x2B6 */ u8 shouldCancelSoundCheck;
    /* 0x2B7 */ u8 shouldPlaySoundCheckCompleteCutscene;
    /* 0x2B8 */ EnTotoSpeakData* text;
    /* 0x2BC */ PlayerOverrideInputEntry overrideInputEntry;
    /* 0x2C4 */ Actor* spotlights;
    /* 0x2C8 */ s32 pad2C8;
} EnToto; // size = 0x2CC

#endif // Z_EN_TOTO_H
