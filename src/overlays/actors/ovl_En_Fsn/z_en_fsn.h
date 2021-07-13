#ifndef Z_EN_FSN_H
#define Z_EN_FSN_H

#include <global.h>
#include "overlays/actors/ovl_En_GirlA/z_en_girla.h"

#define ENFSN_IS_BACKROOM(thisx) ((thisx)->params & 1)
#define ENFSN_IS_SHOP(thisx) (!((thisx)->params & 1))

#define ENFSN_SHOULD_HAGGLE(this) ((this)->flags & 0x80)
#define ENFSN_IS_ANGRY(this) ((this)->flags & 0x100)
#define ENFSN_SHOULD_CALM_DOWN(this) ((this)->flags & 0x200)
#define ENFSN_SHOULD_OFFER_FINAL_PRICE(this) ((this)->flags & 0x40)

#define ENFSN_SET_SHOULD_HAGGLE(this) ((this)->flags |= 0x80)
#define ENFSN_SET_IS_ANGRY(this) ((this)->flags |= 0x100)
#define ENFSN_SET_SHOULD_CALM_DOWN(this) ((this)->flags |= 0x200)
#define ENFSN_SET_SHOULD_OFFER_FINAL_PRICE(this) ((this)->flags |= 0x40)

#define ENFSN_UNSET_SHOULD_HAGGLE(this) ((this)->flags &= ~0x80)
#define ENFSN_UNSET_IS_ANGRY(this) ((this)->flags &= ~0x100)
#define ENFSN_UNSET_SHOULD_CALM_DOWN(this) ((this)->flags &= ~0x200)
#define ENFSN_UNSET_SHOULD_OFFER_FINAL_PRICE(this) ((this)->flags &= ~0x40)

struct EnFsn;

typedef void (*EnFsnActionFunc)(struct EnFsn*, GlobalContext*);

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

typedef struct EnFsn {
    /* 0x000 */ Actor actor;
    /* 0x144 */ UNK_TYPE1 pad144[0x4C];
    /* 0x190 */ SkelAnime skelAnime;
    /* 0x1D4 */ EnFsnActionFunc actionFunc;
    /* 0x1D8 */ EnFsnActionFunc tmpActionFunc; // Used to return to correct browsing function
    /* 0x1DC */ ColliderCylinder collider;
    /* 0x228 */ s16 limbRotYTable[19];
    /* 0x24E */ s16 limbRotZTable[19];
    /* 0x274 */ Vec3s unk274;
    /* 0x27A */ Vec3s unk27A;
    /* 0x280 */ Vec3s limbDrawTable[19];
    /* 0x2F2 */ Vec3s transitionDrawTable[19];
    /* 0x364 */ s16 eyeTextureIdx;
    /* 0x366 */ s16 blinkTimer;
    /* 0x368 */ s16 cutsceneState;
    /* 0x36A */ s16 cutscene;
    /* 0x36C */ s16 lookToShopkeeperCutscene;
    /* 0x36E */ s16 lookToShelfCutscene;
    /* 0x370 */ s16 lookToShopkeeperFromShelfCutscene;
    /* 0x372 */ s16 lookToShopkeeperBuyingCutscene;
    /* 0x374 */ s16 price;
    /* 0x376 */ u16 textId;
    /* 0x378 */ u8 isSelling;
    /* 0x379 */ u8 cursorIdx;
    /* 0x37C */ s32 getItemId;
    /* 0x380 */ s16 stolenItem1;
    /* 0x382 */ s16 stolenItem2;
    /* 0x384 */ s16 itemIds[3];
    /* 0x38A */ s16 totalSellingItems;
    /* 0x38C */ s16 numSellingItems;
    /* 0x390 */ EnGirlA* items[3];
    /* 0x39C */ s16 delayTimer;
    /* 0x3A0 */ s32 stickAccumX;
    /* 0x3A4 */ s32 stickAccumY;
    /* 0x3A8 */ f32 cursorX;
    /* 0x3AC */ f32 cursorY;
    /* 0x3B0 */ f32 cursorZ;
    /* 0x3B4 */ s32 cursorColorR;
    /* 0x3B8 */ s32 cursorColorG;
    /* 0x3BC */ s32 cursorColorB;
    /* 0x3C0 */ s32 cursorColorA;
    /* 0x3C4 */ f32 cursorAnimTween;
    /* 0x3C8 */ u8 cursorAnimState;
    /* 0x3C9 */ u8 drawCursor;
    /* 0x3CC */ StickDirectionPrompt stickLeftPrompt;
    /* 0x404 */ StickDirectionPrompt stickRightPrompt;
    /* 0x43C */ f32 arrowAnimTween;
    /* 0x440 */ f32 stickAnimTween;
    /* 0x444 */ u8 arrowAnimState;
    /* 0x445 */ u8 stickAnimState;
    /* 0x448 */ f32 shopItemSelectedTween;
    /* 0x44C */ s16 animationIdx;
    /* 0x44E */ u16 flags;
} EnFsn; // size = 0x450

extern const ActorInit En_Fsn_InitVars;

#endif // Z_EN_FSN_H
