#ifndef Z64CUTSCENE_H
#define Z64CUTSCENE_H

#include "ultra64.h"
#include "unk.h"

typedef struct {
    /* 0x0 */ s8    continueFlag;
    /* 0x1 */ s8    cameraRoll;
    /* 0x2 */ u16   nextPointFrame;
    /* 0x4 */ f32   viewAngle; // in degrees
    /* 0x8 */ Vec3s pos;
} CutsceneCameraPoint; // size = 0x10

typedef struct {
    /* 0x00 */ Vec3f at;
    /* 0x0C */ Vec3f eye;
    /* 0x18 */ s16 roll;
    /* 0x1A */ s16 fov;
} CutsceneCameraAngle; // size = 0x1C

typedef struct {
    /* 0x0 */ CutsceneCameraPoint* atPoints;
    /* 0x4 */ CutsceneCameraPoint* eyePoints;
    /* 0x8 */ s16 relativeToPlayer;
} CutsceneCameraMove; // size = 0xC

typedef struct {
    /* 0x00 */ u16 id; // "dousa"
    /* 0x02 */ u16 startFrame;
    /* 0x04 */ u16 endFrame;
    union {
        /* 0x06 */ Vec3s rot;
        /* 0x06 */ Vec3us urot;
    };
    /* 0x0C */ Vec3i startPos;
    /* 0x18 */ Vec3i endPos;
    /* 0x24 */ Vec3f normal;
} CsCmdActorCue; // size = 0x30

typedef struct {
    /* 0x0 */ u16 base;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
} CsCmdBase; // size = 0x8

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 hour;
    /* 0x7 */ u8 minute;
    /* 0x8 */ UNK_TYPE1 unk_08[0x04];
} CsCmdDayTime; // size = 0xC

typedef struct {
    /* 0x0 */ u16 setting;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
} CsCmdLightSetting; // size = 0x8

typedef struct {
    /* 0x0 */ u16 sequence;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
} CsCmdStartSeq; // size = 0x8

typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
    /* 0x8 */ u32 unk_08;
} CsCmdSequenceFade; // size = 0xC

typedef struct {
    /* 0x0 */ u16 base;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 type;
    /* 0x8 */ u16 textId1;
    /* 0xA */ u16 textId2;
} CsCmdText; // size = 0xC

typedef enum {
    /* -1 */ CS_TEXTBOX_TYPE_NONE = -1,
    /*  0 */ CS_TEXTBOX_TYPE_DEFAULT,
    /*  1 */ CS_TEXTBOX_TYPE_1,
    /*  2 */ CS_TEXT_OCARINA_ACTION,
    /*  3 */ CS_TEXTBOX_TYPE_3,
    /*  4 */ CS_TEXTBOX_TYPE_BOSSES_REMAINS,
    /*  5 */ CS_TEXTBOX_TYPE_ALL_NORMAL_MASKS
} CutsceneTextboxType;

typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 intensity;
    /* 0x7 */ u8 decayTimer;
    /* 0x8 */ u8 decayStep;
    /* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdRumble; // size = 0xC

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ Color_RGB8 color;
    /* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdFadeScreen; // size = 0xC

typedef enum {
    /* 0 */ CS_STATE_IDLE,
    /* 1 */ CS_STATE_START,
    /* 2 */ CS_STATE_RUN,
    /* 3 */ CS_STATE_STOP,
    /* 4 */ CS_STATE_RUN_UNSTOPPABLE
} CutsceneState;

typedef enum {
    /* 0x00A */ CS_CMD_TEXTBOX = 0xA,
    /* 0x05A */ CS_CMD_CAMERA = 0x5A,
    /* 0x064 */ CS_CMD_ACTOR_CUE_100 = 0x64,
    /* 0x065 */ CS_CMD_ACTOR_CUE_101,
    /* 0x066 */ CS_CMD_ACTOR_CUE_102,
    /* 0x067 */ CS_CMD_ACTOR_CUE_103,
    /* 0x068 */ CS_CMD_ACTOR_CUE_104,
    /* 0x069 */ CS_CMD_ACTOR_CUE_105,
    /* 0x06A */ CS_CMD_ACTOR_CUE_106,
    /* 0x06B */ CS_CMD_ACTOR_CUE_107,
    /* 0x06C */ CS_CMD_ACTOR_CUE_108,
    /* 0x06D */ CS_CMD_ACTOR_CUE_109,
    /* 0x06E */ CS_CMD_ACTOR_CUE_110,
    /* 0x06F */ CS_CMD_ACTOR_CUE_111,
    /* 0x070 */ CS_CMD_ACTOR_CUE_112,
    /* 0x071 */ CS_CMD_ACTOR_CUE_113,
    /* 0x072 */ CS_CMD_ACTOR_CUE_114,
    /* 0x073 */ CS_CMD_ACTOR_CUE_115,
    /* 0x074 */ CS_CMD_ACTOR_CUE_116,
    /* 0x075 */ CS_CMD_ACTOR_CUE_117,
    /* 0x076 */ CS_CMD_ACTOR_CUE_118,
    /* 0x077 */ CS_CMD_ACTOR_CUE_119,
    /* 0x078 */ CS_CMD_ACTOR_CUE_120,
    /* 0x079 */ CS_CMD_ACTOR_CUE_121,
    /* 0x07A */ CS_CMD_ACTOR_CUE_122,
    /* 0x07B */ CS_CMD_ACTOR_CUE_123,
    /* 0x07C */ CS_CMD_ACTOR_CUE_124,
    /* 0x07D */ CS_CMD_ACTOR_CUE_125,
    /* 0x07E */ CS_CMD_ACTOR_CUE_126,
    /* 0x07F */ CS_CMD_ACTOR_CUE_127,
    /* 0x080 */ CS_CMD_ACTOR_CUE_128,
    /* 0x081 */ CS_CMD_ACTOR_CUE_129,
    /* 0x082 */ CS_CMD_ACTOR_CUE_130,
    /* 0x083 */ CS_CMD_ACTOR_CUE_131,
    /* 0x084 */ CS_CMD_ACTOR_CUE_132,
    /* 0x085 */ CS_CMD_ACTOR_CUE_133,
    /* 0x086 */ CS_CMD_ACTOR_CUE_134,
    /* 0x087 */ CS_CMD_ACTOR_CUE_135,
    /* 0x088 */ CS_CMD_ACTOR_CUE_136,
    /* 0x089 */ CS_CMD_ACTOR_CUE_137,
    /* 0x08A */ CS_CMD_ACTOR_CUE_138,
    /* 0x08B */ CS_CMD_ACTOR_CUE_139,
    /* 0x08C */ CS_CMD_ACTOR_CUE_140,
    /* 0x08D */ CS_CMD_ACTOR_CUE_141,
    /* 0x08E */ CS_CMD_ACTOR_CUE_142,
    /* 0x08F */ CS_CMD_ACTOR_CUE_143,
    /* 0x090 */ CS_CMD_ACTOR_CUE_144,
    /* 0x091 */ CS_CMD_ACTOR_CUE_145,
    /* 0x092 */ CS_CMD_ACTOR_CUE_146,
    /* 0x093 */ CS_CMD_ACTOR_CUE_147,
    /* 0x094 */ CS_CMD_ACTOR_CUE_148,
    /* 0x095 */ CS_CMD_ACTOR_CUE_149,
    /* 0x096 */ CS_CMD_MISC,
    /* 0x097 */ CS_CMD_SET_LIGHTING,
    /* 0x098 */ CS_CMD_SCENE_TRANS_FX,
    /* 0x099 */ CS_CMD_MOTIONBLUR,
    /* 0x09A */ CS_CMD_GIVETATL,
    /* 0x09B */ CS_CMD_FADESCREEN,
    /* 0x09C */ CS_CMD_FADESEQ,
    /* 0x09D */ CS_CMD_SETTIME,
    /* 0x0C8 */ CS_CMD_SET_PLAYER_ACTION = 0xC8,
    /* 0x0C9 */ CS_CMD_ACTOR_CUE_201,
    /* 0x0FA */ CS_CMD_UNK_FA = 0xFA,
    /* 0x0FE */ CS_CMD_UNK_FE = 0xFE,
    /* 0x0FF */ CS_CMD_UNK_FF,
    /* 0x100 */ CS_CMD_UNK_100,
    /* 0x101 */ CS_CMD_UNK_101,
    /* 0x102 */ CS_CMD_UNK_102,
    /* 0x103 */ CS_CMD_UNK_103,
    /* 0x104 */ CS_CMD_UNK_104,
    /* 0x105 */ CS_CMD_UNK_105,
    /* 0x108 */ CS_CMD_UNK_108 = 0x108,
    /* 0x109 */ CS_CMD_UNK_109,
    /* 0x12C */ CS_CMD_PLAYSEQ = 0x12C,
    /* 0x12D */ CS_CMD_STOPSEQ,
    /* 0x12E */ CS_CMD_PLAYAMBIENCE,
    /* 0x12F */ CS_CMD_FADEAMBIENCE,
    /* 0x130 */ CS_CMD_130,
    /* 0x131 */ CS_CMD_131,
    /* 0x132 */ CS_CMD_132,
    /* 0x15E */ CS_CMD_TERMINATOR = 0x15E,
    /* 0x15F */ CS_CMD_CHOOSE_CREDITS_SCENES,
    /* 0x190 */ CS_CMD_RUMBLE = 0x190,
    /* 0x1C2 */ CS_CMD_ACTOR_CUE_450 = 0x1C2,
    /* 0x1C3 */ CS_CMD_ACTOR_CUE_451,
    /* 0x1C4 */ CS_CMD_ACTOR_CUE_452,
    /* 0x1C5 */ CS_CMD_ACTOR_CUE_453,
    /* 0x1C6 */ CS_CMD_ACTOR_CUE_454,
    /* 0x1C7 */ CS_CMD_ACTOR_CUE_455,
    /* 0x1C8 */ CS_CMD_ACTOR_CUE_456,
    /* 0x1C9 */ CS_CMD_ACTOR_CUE_457,
    /* 0x1CA */ CS_CMD_ACTOR_CUE_458,
    /* 0x1CB */ CS_CMD_ACTOR_CUE_459,
    /* 0x1CC */ CS_CMD_ACTOR_CUE_460,
    /* 0x1CD */ CS_CMD_ACTOR_CUE_461,
    /* 0x1CE */ CS_CMD_ACTOR_CUE_462,
    /* 0x1CF */ CS_CMD_ACTOR_CUE_463,
    /* 0x1D0 */ CS_CMD_ACTOR_CUE_464,
    /* 0x1D1 */ CS_CMD_ACTOR_CUE_465,
    /* 0x1D2 */ CS_CMD_ACTOR_CUE_466,
    /* 0x1D3 */ CS_CMD_ACTOR_CUE_467,
    /* 0x1D4 */ CS_CMD_ACTOR_CUE_468,
    /* 0x1D5 */ CS_CMD_ACTOR_CUE_469,
    /* 0x1D6 */ CS_CMD_ACTOR_CUE_470,
    /* 0x1D7 */ CS_CMD_ACTOR_CUE_471,
    /* 0x1D8 */ CS_CMD_ACTOR_CUE_472,
    /* 0x1D9 */ CS_CMD_ACTOR_CUE_473,
    /* 0x1DA */ CS_CMD_ACTOR_CUE_474,
    /* 0x1DB */ CS_CMD_ACTOR_CUE_475,
    /* 0x1DC */ CS_CMD_ACTOR_CUE_476,
    /* 0x1DD */ CS_CMD_ACTOR_CUE_477,
    /* 0x1DE */ CS_CMD_ACTOR_CUE_478,
    /* 0x1DF */ CS_CMD_ACTOR_CUE_479,
    /* 0x1E0 */ CS_CMD_ACTOR_CUE_480,
    /* 0x1E1 */ CS_CMD_ACTOR_CUE_481,
    /* 0x1E2 */ CS_CMD_ACTOR_CUE_482,
    /* 0x1E3 */ CS_CMD_ACTOR_CUE_483,
    /* 0x1E4 */ CS_CMD_ACTOR_CUE_484,
    /* 0x1E5 */ CS_CMD_ACTOR_CUE_485,
    /* 0x1E6 */ CS_CMD_ACTOR_CUE_486,
    /* 0x1E7 */ CS_CMD_ACTOR_CUE_487,
    /* 0x1E8 */ CS_CMD_ACTOR_CUE_488,
    /* 0x1E9 */ CS_CMD_ACTOR_CUE_489,
    /* 0x1EA */ CS_CMD_ACTOR_CUE_490,
    /* 0x1EB */ CS_CMD_ACTOR_CUE_491,
    /* 0x1EC */ CS_CMD_ACTOR_CUE_492,
    /* 0x1ED */ CS_CMD_ACTOR_CUE_493,
    /* 0x1EE */ CS_CMD_ACTOR_CUE_494,
    /* 0x1EF */ CS_CMD_ACTOR_CUE_495,
    /* 0x1F0 */ CS_CMD_ACTOR_CUE_496,
    /* 0x1F1 */ CS_CMD_ACTOR_CUE_497,
    /* 0x1F2 */ CS_CMD_ACTOR_CUE_498,
    /* 0x1F3 */ CS_CMD_ACTOR_CUE_499,
    /* 0x1F4 */ CS_CMD_ACTOR_CUE_500,
    /* 0x1F5 */ CS_CMD_ACTOR_CUE_501,
    /* 0x1F6 */ CS_CMD_ACTOR_CUE_502,
    /* 0x1F7 */ CS_CMD_ACTOR_CUE_503,
    /* 0x1F8 */ CS_CMD_ACTOR_CUE_504,
    /* 0x1F9 */ CS_CMD_ACTOR_CUE_505,
    /* 0x1FA */ CS_CMD_ACTOR_CUE_506,
    /* 0x1FB */ CS_CMD_ACTOR_CUE_507,
    /* 0x1FC */ CS_CMD_ACTOR_CUE_508,
    /* 0x1FD */ CS_CMD_ACTOR_CUE_509,
    /* 0x1FE */ CS_CMD_ACTOR_CUE_510,
    /* 0x1FF */ CS_CMD_ACTOR_CUE_511,
    /* 0x200 */ CS_CMD_ACTOR_CUE_512,
    /* 0x201 */ CS_CMD_ACTOR_CUE_513,
    /* 0x202 */ CS_CMD_ACTOR_CUE_514,
    /* 0x203 */ CS_CMD_ACTOR_CUE_515,
    /* 0x204 */ CS_CMD_ACTOR_CUE_516,
    /* 0x205 */ CS_CMD_ACTOR_CUE_517,
    /* 0x206 */ CS_CMD_ACTOR_CUE_518,
    /* 0x207 */ CS_CMD_ACTOR_CUE_519,
    /* 0x208 */ CS_CMD_ACTOR_CUE_520,
    /* 0x209 */ CS_CMD_ACTOR_CUE_521,
    /* 0x20A */ CS_CMD_ACTOR_CUE_522,
    /* 0x20B */ CS_CMD_ACTOR_CUE_523,
    /* 0x20C */ CS_CMD_ACTOR_CUE_524,
    /* 0x20D */ CS_CMD_ACTOR_CUE_525,
    /* 0x20E */ CS_CMD_ACTOR_CUE_526,
    /* 0x20F */ CS_CMD_ACTOR_CUE_527,
    /* 0x210 */ CS_CMD_ACTOR_CUE_528,
    /* 0x211 */ CS_CMD_ACTOR_CUE_529,
    /* 0x212 */ CS_CMD_ACTOR_CUE_530,
    /* 0x213 */ CS_CMD_ACTOR_CUE_531,
    /* 0x214 */ CS_CMD_ACTOR_CUE_532,
    /* 0x215 */ CS_CMD_ACTOR_CUE_533,
    /* 0x216 */ CS_CMD_ACTOR_CUE_534,
    /* 0x217 */ CS_CMD_ACTOR_CUE_535,
    /* 0x218 */ CS_CMD_ACTOR_CUE_536,
    /* 0x219 */ CS_CMD_ACTOR_CUE_537,
    /* 0x21A */ CS_CMD_ACTOR_CUE_538,
    /* 0x21B */ CS_CMD_ACTOR_CUE_539,
    /* 0x21C */ CS_CMD_ACTOR_CUE_540,
    /* 0x21D */ CS_CMD_ACTOR_CUE_541,
    /* 0x21E */ CS_CMD_ACTOR_CUE_542,
    /* 0x21F */ CS_CMD_ACTOR_CUE_543,
    /* 0x220 */ CS_CMD_ACTOR_CUE_544,
    /* 0x221 */ CS_CMD_ACTOR_CUE_545,
    /* 0x222 */ CS_CMD_ACTOR_CUE_546,
    /* 0x223 */ CS_CMD_ACTOR_CUE_547,
    /* 0x224 */ CS_CMD_ACTOR_CUE_548,
    /* 0x225 */ CS_CMD_ACTOR_CUE_549,
    /* 0x226 */ CS_CMD_ACTOR_CUE_550,
    /* 0x227 */ CS_CMD_ACTOR_CUE_551,
    /* 0x228 */ CS_CMD_ACTOR_CUE_552,
    /* 0x229 */ CS_CMD_ACTOR_CUE_553,
    /* 0x22A */ CS_CMD_ACTOR_CUE_554,
    /* 0x22B */ CS_CMD_ACTOR_CUE_555,
    /* 0x22C */ CS_CMD_ACTOR_CUE_556,
    /* 0x22D */ CS_CMD_ACTOR_CUE_557,
    /* 0x22E */ CS_CMD_ACTOR_CUE_558,
    /* 0x22F */ CS_CMD_ACTOR_CUE_559,
    /* 0x230 */ CS_CMD_ACTOR_CUE_560,
    /* 0x231 */ CS_CMD_ACTOR_CUE_561,
    /* 0x232 */ CS_CMD_ACTOR_CUE_562,
    /* 0x233 */ CS_CMD_ACTOR_CUE_563,
    /* 0x234 */ CS_CMD_ACTOR_CUE_564,
    /* 0x235 */ CS_CMD_ACTOR_CUE_565,
    /* 0x236 */ CS_CMD_ACTOR_CUE_566,
    /* 0x237 */ CS_CMD_ACTOR_CUE_567,
    /* 0x238 */ CS_CMD_ACTOR_CUE_568,
    /* 0x239 */ CS_CMD_ACTOR_CUE_569,
    /* 0x23A */ CS_CMD_ACTOR_CUE_570,
    /* 0x23B */ CS_CMD_ACTOR_CUE_571,
    /* 0x23C */ CS_CMD_ACTOR_CUE_572,
    /* 0x23D */ CS_CMD_ACTOR_CUE_573,
    /* 0x23E */ CS_CMD_ACTOR_CUE_574,
    /* 0x23F */ CS_CMD_ACTOR_CUE_575,
    /* 0x240 */ CS_CMD_ACTOR_CUE_576,
    /* 0x241 */ CS_CMD_ACTOR_CUE_577,
    /* 0x242 */ CS_CMD_ACTOR_CUE_578,
    /* 0x243 */ CS_CMD_ACTOR_CUE_579,
    /* 0x244 */ CS_CMD_ACTOR_CUE_580,
    /* 0x245 */ CS_CMD_ACTOR_CUE_581,
    /* 0x246 */ CS_CMD_ACTOR_CUE_582,
    /* 0x247 */ CS_CMD_ACTOR_CUE_583,
    /* 0x248 */ CS_CMD_ACTOR_CUE_584,
    /* 0x249 */ CS_CMD_ACTOR_CUE_585,
    /* 0x24A */ CS_CMD_ACTOR_CUE_586,
    /* 0x24B */ CS_CMD_ACTOR_CUE_587,
    /* 0x24C */ CS_CMD_ACTOR_CUE_588,
    /* 0x24D */ CS_CMD_ACTOR_CUE_589,
    /* 0x24E */ CS_CMD_ACTOR_CUE_590,
    /* 0x24F */ CS_CMD_ACTOR_CUE_591,
    /* 0x250 */ CS_CMD_ACTOR_CUE_592,
    /* 0x251 */ CS_CMD_ACTOR_CUE_593,
    /* 0x252 */ CS_CMD_ACTOR_CUE_594,
    /* 0x253 */ CS_CMD_ACTOR_CUE_595,
    /* 0x254 */ CS_CMD_ACTOR_CUE_596,
    /* 0x255 */ CS_CMD_ACTOR_CUE_597,
    /* 0x256 */ CS_CMD_ACTOR_CUE_598,
    /* 0x257 */ CS_CMD_ACTOR_CUE_599
} CutsceneCmd;

typedef enum {
    /* 0x00 */ CS_MISC_UNIMPLEMENTED_0,
    /* 0x01 */ CS_MISC_RAIN,
    /* 0x02 */ CS_MISC_LIGHTNING,
    /* 0x03 */ CS_MISC_LIFT_FOG,
    /* 0x04 */ CS_MISC_CLOUDY_SKY,
    /* 0x05 */ CS_MISC_STOP_CUTSCENE,
    /* 0x06 */ CS_MISC_UNIMPLEMENTED_6,
    /* 0x07 */ CS_MISC_SHOW_TITLE_CARD,
    /* 0x08 */ CS_MISC_MEDIUM_QUAKE_START,
    /* 0x09 */ CS_MISC_QUAKE_STOP,
    /* 0x0A */ CS_MISC_VISMONO_BLACK_AND_WHITE,
    /* 0x0B */ CS_MISC_VISMONO_SEPIA,
    /* 0x0C */ CS_MISC_HIDE_ROOM,
    /* 0x0D */ CS_MISC_RED_PULSATING_LIGHTS,
    /* 0x0E */ CS_MISC_HALT_ALL_ACTORS,
    /* 0x0F */ CS_MISC_RESUME_ALL_ACTORS,
    /* 0x10 */ CS_MISC_SANDSTORM_FILL,
    /* 0x11 */ CS_MISC_SUNSSONG_START,
    /* 0x12 */ CS_MISC_FREEZE_TIME,
    /* 0x13 */ CS_MISC_LONG_SCARECROW_SONG,
    /* 0x14 */ CS_MISC_SET_CSFLAG_3,
    /* 0x15 */ CS_MISC_SET_CSFLAG_4,
    /* 0x16 */ CS_MISC_PLAYER_FORM_DEKU,
    /* 0x17 */ CS_MISC_ENABLE_PLAYER_REFLECTION,
    /* 0x18 */ CS_MISC_DISABLE_PLAYER_REFLECTION,
    /* 0x19 */ CS_MISC_PLAYER_FORM_HUMAN,
    /* 0x1A */ CS_MISC_STRONG_QUAKE_START,
    /* 0x1B */ CS_MISC_1B,
    /* 0x1C */ CS_MISC_1C,
    /* 0x1D */ CS_MISC_PLAYER_FORM_RESTORED,
    /* 0x1E */ CS_MISC_1E,
    /* 0x1F */ CS_MISC_1F,
    /* 0x20 */ CS_MISC_UNIMPLEMENTED_20,
    /* 0x21 */ CS_MISC_SPECIAL_SAVE,
    /* 0x22 */ CS_MISC_SAVE,
    /* 0x23 */ CS_MISC_TIME_ADVANCE,
    /* 0x24 */ CS_MISC_WEAK_QUAKE_START,
    /* 0x25 */ CS_MISC_UNIMPLEMENTED_25,
    /* 0x26 */ CS_MISC_DAWN_OF_A_NEW_DAY,
    /* 0x27 */ CS_MISC_PLAYER_FORM_ZORA,
    /* 0x28 */ CS_MISC_FOREVER
} CutsceneMiscType;

typedef enum {
    /* 0x03 */ CS_FADE_OUT_FANFARE = 3, 
    /* 0x04 */ CS_FADE_OUT_BGM_MAIN
} CutsceneFadeOutSeqPlayer;

typedef enum {
    /* 0x01 */ CS_TRANS_GRAY_FILL_IN = 1, // has hardcoded sounds for some scenes
    /* 0x02 */ CS_TRANS_BLUE_FILL_IN,
    /* 0x03 */ CS_TRANS_RED_FILL_OUT,
    /* 0x04 */ CS_TRANS_GREEN_FILL_OUT,
    /* 0x05 */ CS_TRANS_GRAY_FILL_OUT,
    /* 0x06 */ CS_TRANS_BLUE_FILL_OUT,
    /* 0x07 */ CS_TRANS_RED_FILL_IN,
    /* 0x08 */ CS_TRANS_GREEN_FILL_IN,
    /* 0x09 */ CS_TRANS_TRIGGER_INSTANCE, // used with `TRANS_MODE_INSTANCE_WAIT`
    /* 0x0A */ CS_TRANS_BLACK_FILL_OUT,
    /* 0x0B */ CS_TRANS_BLACK_FILL_IN,
    /* 0x0C */ CS_TRANS_BLACK_C,
    /* 0x0D */ CS_TRANS_BLACK_D
} CutsceneTransitionType;

typedef union CutsceneData {
    s32 i;
    f32 f;
    s16 s[2];
    s8  b[4];
} CutsceneData;

typedef struct {
    /* 0x0 */ CutsceneData* script;
    /* 0x4 */ s16 nextEntrance;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7; // a weekEventReg bitpack?
} CutsceneEntry; // size = 0x8

typedef struct {
    /* 0x00 */ u8 sceneCsCount;
    /* 0x04 */ CutsceneData* script;
    /* 0x08 */ u8 state;
    /* 0x0C */ f32 timer;
    /* 0x10 */ u16 curFrame;
    /* 0x12 */ u16 currentCsIndex;
    /* 0x14 */ s32 subCamId;
    /* 0x18 */ u16 unk_18;
    /* 0x1A */ u8 unk_1A;
    /* 0x1B */ u8 unk_1B;
    /* 0x1C */ CutsceneCameraPoint* camAtPoints;
    /* 0x20 */ CutsceneCameraPoint* camEyePoints;
    /* 0x24 */ CsCmdActorCue* playerCue;
    /* 0x28 */ CsCmdActorCue* actorCues[10]; // "npcdemopnt"
    /* 0x50 */ CutsceneEntry* sceneCsList;
} CutsceneContext; // size = 0x54

#endif
