#ifndef Z_EN_TRT_H
#define Z_EN_TRT_H

#include <global.h>
#include "overlays/actors/ovl_En_GirlA/z_en_girla.h"

struct EnTrt;

typedef void (*EnTrtActionFunc)(struct EnTrt*, GlobalContext*);
typedef void (*EnTrtBlinkFunc)(struct EnTrt*);

typedef struct ShopItem {
    /* 0x00 */ s16 shopItemId;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 z;
} ShopItem; // size = 0x8

typedef struct {
    /* 0x00 */ u32 stickColorR;
    /* 0x04 */ u32 stickColorG;
    /* 0x08 */ u32 stickColorB;
    /* 0x0C */ u32 stickColorA;
    /* 0x10 */ f32 stickTexX;
    /* 0x14 */ f32 stickTexY;
    /* 0x18 */ u32 arrowColorR;
    /* 0x1C */ u32 arrowColorG;
    /* 0x20 */ u32 arrowColorB;
    /* 0x24 */ u32 arrowColorA;
    /* 0x28 */ f32 arrowTexX;
    /* 0x2C */ f32 arrowTexY;
    /* 0x30 */ f32 texZ; // Used for both stickTexZ and arrowTexZ
    /* 0x34 */ s32 isEnabled;
} StickDirectionPrompt; // size = 0x38

typedef struct EnTrt {
    /* 0x000 */ Actor actor;
    /* 0x144 */ EnTrtActionFunc actionFunc;
    /* 0x148 */ EnTrtActionFunc tmpActionFunc;
    /* 0x14C */ SkelAnime skelAnime;
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ char unk1DC[0x154];
    /* 0x330 */ s16 delayTimer;
    /* 0x332 */ s16 sleepSoundTimer;
    /* 0x334 */ s16 cutsceneState;
    /* 0x336 */ char unk336[0x2];
    /* 0x338 */ s32 stickAccumX;
    /* 0x33C */ s32 stickAccumY;
    /* 0x340 */ EnGirlA* items[3];
    /* 0x34C */ u8 cursorIdx;
    /* 0x34D */ char unk34D[0x3];
    /* 0x350 */ StickDirectionPrompt stickLeftPrompt;
    /* 0x388 */ StickDirectionPrompt stickRightPrompt;
    /* 0x3C0 */ f32 shopItemSelectedTween;
    /* 0x3C4 */ f32 cursorAnimTween;
    /* 0x3C8 */ u8 cursorAnimState;
    /* 0x3C9 */ char unk3C9[0x3];
    /* 0x3CC */ f32 arrowAnimTween;
    /* 0x3D0 */ f32 stickAnimTween;
    /* 0x3D4 */ u8 arrowAnimState;
    /* 0x3D5 */ u8 stickAnimState;
    /* 0x3D6 */ s16 blinkTimer;
    /* 0x3D8 */ s16 eyeTextureIdx;
    /* 0x3DA */ char unk3DA[0x2];
    /* 0x3DC */ EnTrtBlinkFunc blinkFunc;
    /* 0x3E0 */ s16 cutscene;
    /* 0x3E2 */ s16 tmpGetMushroomCutscene;
    /* 0x3E4 */ f32 cursorX;
    /* 0x3E8 */ f32 cursorY;
    /* 0x3EC */ f32 cursorZ;
    /* 0x3F0 */ s32 cursorColorR;
    /* 0x3F4 */ s32 cursorColorG;
    /* 0x3F8 */ s32 cursorColorB;
    /* 0x3FC */ s32 cursorColorA;
    /* 0x400 */ u8 drawCursor;
    /* 0x401 */ char unk401[0x1];
    /* 0x402 */ s16 timer;
    /* 0x404 */ s16 animationState;
    /* 0x406 */ u16 textId;
    /* 0x408 */ u16 tmpTextId;
    /* 0x40A */ u16 talkOptionTextId;
    /* 0x40C */ s16 lookForwardCutscene;
    /* 0x40E */ s16 lookToShelfCutscene;
    /* 0x410 */ s16 lookToShopkeeperCutscene;
    /* 0x412 */ s16 getMushroomCutscene;
    /* 0x414 */ char unk414[0x2];
    /* 0x416 */ Vec3s headRot;
    /* 0x41C */ Vec3f headPos;
    /* 0x428 */ s16 headPitch;
    /* 0x42A */ s16 headYaw;
    /* 0x42C */ u16 flags;
    /* 0x42E */ char unk42E[0x2];
} EnTrt; // size = 0x430

extern const ActorInit En_Trt_InitVars;

#endif // Z_EN_TRT_H
