#ifndef Z64INTERFACE_H
#define Z64INTERFACE_H

#include "ultra64.h"
#include "z64view.h"

typedef enum {
    /*  0 */ MINIGAME_STATE_NONE,
    /*  1 */ MINIGAME_STATE_COUNTDOWN_SETUP_3,
    /*  2 */ MINIGAME_STATE_COUNTDOWN_3,
    /*  3 */ MINIGAME_STATE_COUNTDOWN_SETUP_2,
    /*  4 */ MINIGAME_STATE_COUNTDOWN_2,
    /*  5 */ MINIGAME_STATE_COUNTDOWN_SETUP_1,
    /*  6 */ MINIGAME_STATE_COUNTDOWN_1,
    /*  7 */ MINIGAME_STATE_COUNTDOWN_SETUP_GO,
    /*  8 */ MINIGAME_STATE_COUNTDOWN_GO,
    /* 20 */ MINIGAME_STATE_NO_COUNTDOWN_SETUP = 20,
    /* 21 */ MINIGAME_STATE_NO_COUNTDOWN,
    /* 30 */ MINIGAME_STATE_PLAYING = 30
} MinigameState;

typedef enum {
    /* 0 */ PERFECT_LETTERS_TYPE_OFF,
    /* 1 */ PERFECT_LETTERS_TYPE_1,
    /* 2 */ PERFECT_LETTERS_TYPE_2,
    /* 3 */ PERFECT_LETTERS_TYPE_3
} PerfectLettersType;

typedef enum {
    /* 0 */ PERFECT_LETTERS_STATE_OFF,
    /* 1 */ PERFECT_LETTERS_STATE_INIT,
    /* 2 */ PERFECT_LETTERS_STATE_ENTER,
    /* 3 */ PERFECT_LETTERS_STATE_STATIONARY, // Display for type 1
    /* 4 */ PERFECT_LETTERS_STATE_SPREAD, // Exit for type 1
    /* 5 */ PERFECT_LETTERS_STATE_DISPLAY,
    /* 6 */ PERFECT_LETTERS_STATE_EXIT
} PerfectLettersState;

#define PERFECT_LETTERS_NUM_LETTERS 8
#define PERFECT_LETTERS_ANGLE_PER_LETTER (0x10000 / PERFECT_LETTERS_NUM_LETTERS)

typedef struct {
    /* 0x000 */ View view;
    /* 0x168 */ Vtx* actionVtx;
    /* 0x16C */ Vtx* beatingHeartVtx;
    /* 0x170 */ u8* parameterSegment;
    /* 0x174 */ u8* doActionSegment;
    /* 0x178 */ u8* iconItemSegment;
    /* 0x17C */ u8* mapSegment;
    /* 0x180 */ u8* unk_180;
    /* 0x184 */ DmaRequest dmaRequest_184;
    /* 0x1A4 */ DmaRequest dmaRequest_1A4;
    /* 0x1C4 */ DmaRequest dmaRequest_1C4;
    /* 0x1E4 */ OSMesgQueue loadQueue;
    /* 0x1FC */ OSMesg loadMsg;
    /* 0x200 */ Viewport viewport;
    /* 0x210 */ s16 unk_210;
    /* 0x212 */ u16 unk_212;
    /* 0x214 */ u16 unk_214;
    /* 0x218 */ f32 unk_218;
    /* 0x21C */ s16 unk_21C;
    /* 0x21E */ s16 bButtonDoAction;
    /* 0x220 */ s16 unk_220;
    /* 0x222 */ s16 unk_222;
    /* 0x224 */ s16 unk_224;
    /* 0x226 */ s16 lifeColorChange;
    /* 0x228 */ s16 lifeColorChangeDirection;
    /* 0x22A */ s16 beatingHeartPrim[3];
    /* 0x230 */ s16 beatingHeartEnv[3];
    /* 0x236 */ s16 heartsPrimR[2];
    /* 0x23A */ s16 heartsPrimG[2];
    /* 0x23E */ s16 heartsPrimB[2];
    /* 0x242 */ s16 heartsEnvR[2];
    /* 0x246 */ s16 heartsEnvG[2];
    /* 0x24A */ s16 heartsEnvB[2];
    /* 0x24E */ s16 health;
    /* 0x250 */ s16 unkTimer;
    /* 0x252 */ s16 lifeSizeChange;
    /* 0x254 */ s16 lifeSizeChangeDirection; // 1 means shrinking, 0 growing
    /* 0x256 */ s16 unk_256;
    /* 0x258 */ s16 magicConsumptionTimer; // For certain magic states, 1 unit of magic is consumed every time the timer reaches 0
    /* 0x25A */ u8 numHorseBoosts;
    /* 0x25C */ u16 minigamePoints; // Points to add to the minigame score. Reset to 0 every frame.
    /* 0x25E */ u16 minigameHiddenPoints; // Points to add to the secondary set of minigame points not displayed. Reset to 0 every frame.
    /* 0x260 */ u16 minigameAmmo;
    /* 0x262 */ u16 minigameUnusedPoints; // Associated with other minigame points, unused
    /* 0x264 */ s16 unk_264;
    /* 0x266 */ s16 aAlpha;
    /* 0x268 */ s16 bAlpha;
    /* 0x26A */ s16 cLeftAlpha;
    /* 0x26C */ s16 cDownAlpha;
    /* 0x26E */ s16 cRightAlpha;
    /* 0x270 */ s16 healthAlpha;
    /* 0x272 */ s16 magicAlpha;
    /* 0x274 */ s16 minimapAlpha;
    /* 0x276 */ s16 startAlpha;
    /* 0x278 */ s16 unk_278;
    /* 0x27A */ s16 dungeonOrBossAreaMapIndex;
    /* 0x27C */ s16 mapRoomNum;
    /* 0x27E */ u8 unk_27E;
    /* 0x27F */ u8 unk_27F;
    /* 0x280 */ u8 minigameState;
    /* 0x282 */ s16 minigameCountdownAlpha;
    /* 0x284 */ s16 minigameCountdownScale;
    /* 0x286 */ s16 perfectLettersOn;
    /* 0x288 */ s16 perfectLettersType;
    /* 0x28A */ s16 perfectLettersState[PERFECT_LETTERS_NUM_LETTERS];
    /* 0x29A */ u16 perfectLettersAngles[PERFECT_LETTERS_NUM_LETTERS]; // Angle that follows the projectory of an ellipse
    /* 0x2AA */ s16 perfectLettersOffsetX[PERFECT_LETTERS_NUM_LETTERS];
    /* 0x2BC */ f32 perfectLettersSemiAxisX[PERFECT_LETTERS_NUM_LETTERS];
    /* 0x2DC */ f32 perfectLettersSemiAxisY[PERFECT_LETTERS_NUM_LETTERS];
    /* 0x2FC */ s16 perfectLettersPrimColor[4];
    /* 0x304 */ s16 perfectLettersCount;
    /* 0x306 */ s16 perfectLettersUnused;
    /* 0x308 */ s16 perfectLettersColorIndex;
    /* 0x30A */ s16 perfectLettersColorTimer;
    /* 0x30C */ s16 perfectLettersTimer;
    struct {
        /* 0x30E */ u8 unk_30E; // "h_gauge"
        /* 0x30F */ u8 bButton;
        /* 0x310 */ u8 aButton;
        /* 0x311 */ u8 tradeItems;
        /* 0x312 */ u8 unk_312;
        /* 0x313 */ u8 unk_313;
        /* 0x314 */ u8 unk_314;
        /* 0x315 */ u8 songOfSoaring;
        /* 0x316 */ u8 songOfStorms;
        /* 0x317 */ u8 unk_317;
        /* 0x318 */ u8 pictographBox;
        /* 0x319 */ u8 all;     // "another"; enables all item restrictions
    } restrictions; // size = 0xC
    /* 0x31A */ u8 storyState;
    /* 0x31B */ u8 storyType;
    /* 0x31C */ u8 unk_31C;
    /* 0x320 */ OSMesgQueue unk_320;
    /* 0x338 */ OSMesg unk_338;
    /* 0x33C */ void* unk_33C;
    /* 0x340 */ u32 unk_340;
    /* 0x344 */ u32 unk_344;
} InterfaceContext; // size = 0x348

#endif
