#ifndef Z_EN_SOB1_H
#define Z_EN_SOB1_H

#include <global.h>
#include "../ovl_En_GirlA/z_en_girla.h"

struct EnSob1;

typedef void (*EnSob1ActionFunc)(struct EnSob1*, GlobalContext*);
typedef void (*EnSob1BlinkFunc)(struct EnSob1*);

typedef struct ShopItem {
    /* 0x00 */ s16 shopItemId;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 z;
} ShopItem; // size = 0x8

typedef struct EnSob1UnkStruct {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
    /* 0x8 */ f32 unk8;
    /* 0xC */ f32 unkC;
} EnSob1UnkStruct; // size = 0x10

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

typedef struct EnSob1 {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnSob1ActionFunc actionFunc;
    /* 0x18C */ EnSob1ActionFunc prevActionFunc;
    /* 0x190 */ EnSob1ActionFunc actionFunc2;
    /* 0x194 */ ColliderCylinder collider;
    /* 0x1E0 */ Path* path;
    /* 0x1E4 */ s32 unk1E4;
    /* 0x1E8 */ s16 unk1E8;
    /* 0x1EA */ s8 objIndex;
    /* 0x1EB */ s8 unk1EB;
    /* 0x1EC */ s8 unk1EC;
    /* 0x1ED */ char unk1ED[0x1];
    /* 0x1EE */ s16 unk1EE;
    /* 0x1F0 */ s16 unk1F0;
    /* 0x1F2 */ Vec3s limbDrawTable[20];
    /* 0x26A */ Vec3s transitionDrawTable[20];
    /* 0x2E2 */ s16 eyeTextureIdx;
    /* 0x2E4 */ s16 blinkTimer;
    /* 0x2E6 */ char unk2E6[0x2];
    /* 0x2E8 */ EnSob1BlinkFunc blinkFunc;
    /* 0x2EC */ EnGirlA* items[3];
    /* 0x2F8 */ s32 stickAccumX;
    /* 0x2FC */ s32 stickAccumY;
    /* 0x300 */ f32 cursorX;
    /* 0x304 */ f32 cursorY;
    /* 0x308 */ f32 cursorZ;
    /* 0x30C */ s32 cursorColorR;
    /* 0x310 */ s32 cursorColorG;
    /* 0x314 */ s32 cursorColorB;
    /* 0x318 */ s32 cursorColorA;
    /* 0x31C */ f32 cursorAnimTween;
    /* 0x320 */ u8 cursorAnimState;
    /* 0x321 */ u8 drawCursor;
    /* 0x322 */ u8 cursorIdx;
    /* 0x323 */ char unk323[0x1];
    /* 0x324 */ StickDirectionPrompt stickRightPrompt;
    /* 0x35C */ StickDirectionPrompt stickLeftPrompt;
    /* 0x394 */ f32 arrowAnimTween;
    /* 0x398 */ f32 stickAnimTween;
    /* 0x39C */ u8 arrowAnimState;
    /* 0x39D */ u8 stickAnimState;
    /* 0x39E */ s16 cutsceneState;
    /* 0x3A0 */ s16 unk3A0;
    /* 0x3A2 */ s16 unk3A2;
    /* 0x3A4 */ s16 unk3A4;
    /* 0x3A6 */ s16 unk3A6;
    /* 0x3A8 */ char unk3A8[0x4];
    /* 0x3AC */ f32 shopItemSelectedTween;
    /* 0x3B0 */ char unk3B0[0x4];
    /* 0x3B4 */ u16 unk3B4;
    /* 0x3B6 */ u16 unk3B6;
    /* 0x3B8 */ u16 unk3B8;
    /* 0x3BA */ u8 unk3BA;
    /* 0x3BB */ char unk3BB[0x1];
    /* 0x3BC */ f32 unk3BC;
    /* 0x3C0 */ f32 unk3C0;
    /* 0x3C4 */ f32 unk3C4;
    /* 0x3C8 */ f32 unk3C8;
    /* 0x3CC */ s16 unk3CC;
    /* 0x3CE */ char unk3CE[0x2];
} EnSob1; // size = 0x3D0

extern const ActorInit En_Sob1_InitVars;

#endif // Z_EN_SOB1_H
