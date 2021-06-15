#ifndef Z_EN_OSSAN_H
#define Z_EN_OSSAN_H

#include <global.h>

#include "../ovl_En_GirlA/z_en_girla.h"

struct EnOssan;

typedef void (*EnOssanActionFunc)(struct EnOssan*, GlobalContext*);
typedef void (*EnOssanUnkFunc)(struct EnOssan*);

typedef struct ShopItem {
    /* 0x00 */ s16 shopItemId;
    /* 0x02 */ s16 x;
    /* 0x04 */ s16 y;
    /* 0x06 */ s16 z;
} ShopItem; // size = 0x8;

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

typedef struct EnOssan {
    /* 0x000 */ Actor actor;
    /* 0x144 */ SkelAnime skelAnime;
    /* 0x188 */ EnOssanActionFunc actionFunc;
    /* 0x18C */ EnOssanActionFunc tmpActionFunc; // Used to restore back to correct browsing function
    /* 0x190 */ ColliderCylinder collider;
    /* 0x1DC */ s16 delayTimer;
    /* 0x1DE */ s8 objIndex;
    /* 0x1E0 */ s16 eyeTextureIdx;
    /* 0x1E2 */ s16 blinkTimer;
    /* 0x1E4 */ EnOssanUnkFunc blinkFunc;
    /* 0x1E8 */ EnGirlA *items[8];
    /* 0x208 */ s32 stickAccumX;
    /* 0x20C */ s32 stickAccumY;
    /* 0x210 */ u8 moveHorizontal;
    /* 0x211 */ u8 moveVertical;
    /* 0x214 */ f32 cursorX;
    /* 0x218 */ f32 cursorY;
    /* 0x21C */ f32 cursorZ;
    /* 0x220 */ u32 cursorColorR;
    /* 0x224 */ u32 cursorColorG;
    /* 0x228 */ u32 cursorColorB;
    /* 0x22C */ u32 cursorColorA;
    /* 0x230 */ f32 cursorAnimTween;
    /* 0x234 */ u8 cursorAnimState;
    /* 0x235 */ u8 drawCursor;
    /* 0x236 */ u8 cursorIndex;
    /* 0x238 */ StickDirectionPrompt stickRightPrompt;
    /* 0x270 */ StickDirectionPrompt stickLeftPrompt;
    /* 0x2A8 */ f32 arrowAnimTween;
    /* 0x2AC */ f32 stickAnimTween;
    /* 0x2B0 */ u8 arrowAnimState;
    /* 0x2B1 */ u8 stickAnimState;
    /* 0x2B4 */ f32 shopItemSelectedTween;
    /* 0x2B8 */ s16 defaultCutscene;
    /* 0x2BA */ s16 lookToLeftShelfCutscene;
    /* 0x2BC */ s16 lookToRightShelfCutscene;
    /* 0x2BE */ s16 lookToShopKeeperCutscene;
    /* 0x2C0 */ s16 cutscene;
    /* 0x2C2 */ s16 cutSceneState;
    /* 0x2C4 */ u16 textId;
    /* 0x2C6 */ Vec3s unk2C6;
    /* 0x2CC */ Vec3s unk2CC;
    /* 0x2D2 */ s16 limbRotTableY[19];
    /* 0x2F8 */ s16 limbRotTableZ[19];
    /* 0x31E */ Vec3s limbDrawTbl[19];
    /* 0x390 */ Vec3s transitionDrawTbl[19];
    /* 0x402 */ s16 animationIdx;
    /* 0x404 */ s16 headRotZ;
    /* 0x406 */ s16 headRotX;
    /* 0x408 */ char pad408[0x2];
    /* 0x40A */ u16 welcomeFlags;
} EnOssan; // size = 0x40C

typedef enum {
    /* 0 */ CURIOSITY_SHOP_MAN,
    /* 1 */ PART_TIME_WORKER
} EnOssanWorker;

typedef enum {
    /* 0 */ ENOSSAN_HUMAN_WELCOME,
    /* 1 */ ENOSSAN_TALK_OPTION,
    /* 2 */ ENOSSAN_GORON_FIRST_TIME_WELCOME,
    /* 3 */ ENOSSAN_ZORA_FIRST_TIME_WELCOME,
    /* 4 */ ENOSSAN_DEKU_FIRST_TIME_WELCOME,
    /* 5 */ ENOSSAN_GORON_WELCOME,
    /* 6 */ ENOSSAN_ZORA_WELCOME,
    /* 7 */ ENOSSAN_DEKU_WELCOME,
} EnOssanWelcomeText;

typedef enum {
    /* 0 */ ENOSSAN_NEED_EMPTY_BOTTLE_TEXT,
    /* 1 */ ENOSSAN_NEED_RUPEES_TEXT,
    /* 2 */ ENOSSAN_NO_ROOM_TEXT,
    /* 3 */ ENOSSAN_SUCCESS_TEXT,
    /* 4 */ ENOSSAN_CANT_GET_NOW_TEXT
} EnOssanCanBuyResultsText;

extern const ActorInit En_Ossan_InitVars;

#endif // Z_EN_OSSAN_H
