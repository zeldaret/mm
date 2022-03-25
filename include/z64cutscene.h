#ifndef Z64CUTSCENE_H
#define Z64CUTSCENE_H

#include "ultra64.h"
#include "unk.h"

typedef struct {
    /* 0x00 */ s8    continueFlag;
    /* 0x01 */ s8    cameraRoll;
    /* 0x02 */ u16   nextPointFrame;
    /* 0x04 */ f32   viewAngle; // in degrees
    /* 0x08 */ Vec3s pos;
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
    /* 0x00 */ u16 action; // "dousa"
    /* 0x02 */ u16 startFrame;
    /* 0x04 */ u16 endFrame;
    union {
        /* 0x06 */ Vec3s rot;
        /* 0x06 */ Vec3us urot;
    };
    /* 0x0C */ Vec3i startPos;
    /* 0x18 */ Vec3i endPos;
    /* 0x24 */ Vec3f normal;
} CsCmdActorAction; // size = 0x30

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
} CsCmdEnvLighting; // size = 0x8

typedef struct {
    /* 0x0 */ u16 sequence;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
} CsCmdSequenceChange; // size = 0x8

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
} CsCmdTextbox; // size = 0xC

typedef enum {
    /*      0 */ CS_TEXTBOX_TYPE_DEFAULT,
    /*      1 */ CS_TEXTBOX_TYPE_1,
    /*      2 */ CS_TEXTBOX_TYPE_LEARN_SONG,
    /*      3 */ CS_TEXTBOX_TYPE_3,
    /*      4 */ CS_TEXTBOX_TYPE_BOSSES_REMAINS,
    /*      5 */ CS_TEXTBOX_TYPE_ALL_NORMAL_MASKS,
    /* 0xFFFF */ CS_TEXTBOX_TYPE_NONE = 0xFFFF
} CutsceneTextboxType;

typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
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
    /* 0 */ CS_STATE_0,
    /* 1 */ CS_STATE_1,
    /* 2 */ CS_STATE_2,
    /* 3 */ CS_STATE_3,
    /* 4 */ CS_STATE_4
} CutsceneState;

typedef enum {
    /* 0x00A */ CS_CMD_TEXTBOX = 0xA,
    /* 0x05A */ CS_CMD_CAMERA = 0x5A,
    /* 0x096 */ CS_CMD_MISC = 0x96,
    /* 0x097 */ CS_CMD_SET_LIGHTING,
    /* 0x098 */ CS_CMD_SCENE_TRANS_FX,
    /* 0x099 */ CS_CMD_MOTIONBLUR,
    /* 0x09A */ CS_CMD_GIVETATL,
    /* 0x09B */ CS_CMD_FADESCREEN,
    /* 0x09C */ CS_CMD_FADESEQ,
    /* 0x09D */ CS_CMD_SETTIME,
    /* 0x0C8 */ CS_CMD_SET_PLAYER_ACTION = 0xC8,
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
    /* 0x12D */ CS_CMD_UNK_12D,
    /* 0x130 */ CS_CMD_130 = 0x130,
    /* 0x131 */ CS_CMD_131,
    /* 0x132 */ CS_CMD_132,
    /* 0x133 */ CS_CMD_STOPSEQ,
    /* 0x134 */ CS_CMD_PLAYAMBIENCE,
    /* 0x135 */ CS_CMD_FADEAMBIENCE,
    /* 0x15E */ CS_CMD_TERMINATOR = 0x15E,
    /* 0x15F */ CS_CMD_CHOOSE_CREDITS_SCENES,
    /* 0x190 */ CS_CMD_RUMBLE = 0x190
} CutsceneCmd;

typedef union CutsceneData {
    s32 i;
    f32 f;
    s16 s[2];
    s8  b[4];
} CutsceneData;

typedef struct {
    /* 0x0 */ CutsceneData* segmentedData;
    /* 0x4 */ s16 nextEntranceIndex;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7; // a weekEventReg bitpack?
} CutsceneEntry; // size = 0x8

typedef struct {
    /* 0x00 */ u8                   sceneCsCount;
    /* 0x04 */ CutsceneData*        csData;
    /* 0x08 */ u8                   state;
    /* 0x0C */ f32                  unk_0C;
    /* 0x10 */ u16                  frames;
    /* 0x12 */ u16                  currentCsIndex;
    /* 0x14 */ s32                  csCamId;
    /* 0x18 */ u16                  unk_18;
    /* 0x1A */ u8                   unk_1A;
    /* 0x1B */ u8                   unk_1B;
    /* 0x1C */ CutsceneCameraPoint* atPoints;
    /* 0x20 */ CutsceneCameraPoint* eyePoints;
    /* 0x24 */ CsCmdActorAction*    playerAction;
    /* 0x28 */ CsCmdActorAction*    actorActions[10]; // "npcdemopnt"
    /* 0x50 */ CutsceneEntry*       sceneCsList;
} CutsceneContext; // size = 0x54

#endif
