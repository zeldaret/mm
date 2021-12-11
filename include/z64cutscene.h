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
    /* 0x24 */ Vec3i normal;
} CsCmdActorAction; // size = 0x30

typedef struct {
    /* 0x0 */ u16 base;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ UNK_TYPE1 unk_06[0x02];
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
} CsCmdEnvLighting; // size = 0x6

typedef struct {
    /* 0x0 */ u16 sequence;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
} CsCmdMusicChange; // size = 0x6

typedef struct {
    /* 0x0 */ u16 type;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 unk_06;
    /* 0x8 */ u32 unk_08;
} CsCmdMusicFade; // size = 0xC

typedef struct {
    /* 0x0 */ u16 base;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u16 type;
    /* 0x8 */ u16 textId1;
    /* 0xA */ u16 textId2;
} CsCmdTextbox; // size = 0xC

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdUnk190; // size = 0xC

typedef struct {
    /* 0x0 */ UNK_TYPE4 unk0;
    /* 0x4 */ UNK_TYPE4 unk4;
} CsCmdUnk5A; // size = 0x8

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 unk6;
    /* 0x7 */ u8 unk7;
    /* 0x8 */ u8 unk8;
    /* 0x9 */ UNK_TYPE1 pad9[0x3];
} CsCmdUnk9B; // size = 0xC

typedef enum {
    /* 0 */ CS_STATE_IDLE,
    /* 1 */ CS_STATE_SKIPPABLE_INIT,
    /* 2 */ CS_STATE_SKIPPABLE_EXEC,
    /* 3 */ CS_STATE_UNSKIPPABLE_INIT,
    /* 4 */ CS_STATE_UNSKIPPABLE_EXEC
} CutsceneState;

typedef enum {
    ///* 0x000 */ CS_CMD_00,
    /* 0x00A */ CS_CMD_TEXTBOX = 0xA,
    /* 0x05A */ CS_CMD_5A = 0x5A,
    /* 0x096 */ CS_CMD_MISC = 0x96,
    /* 0x097 */ CS_CMD_SET_LIGHTING,
    /* 0x098 */ CS_CMD_SCENE_TRANS_FX,
    /* 0x099 */ CS_CMD_99,
    /* 0x09A */ CS_CMD_GIVETATL,
    /* 0x09B */ CS_CMD_9B,
    /* 0x09C */ CS_CMD_FADESEQ,
    /* 0x09D */ CS_CMD_SETTIME,
    /* 0x0C8 */ CS_CMD_SET_PLAYER_ACTION = 0xC8,
    /* 0x12C */ CS_CMD_PLAYSEQ = 0x12C,
    /* 0x130 */ CS_CMD_130 = 0x130,
    /* 0x131 */ CS_CMD_131 = 0x131,
    /* 0x132 */ CS_CMD_132 = 0x132,
    /* 0x133 */ CS_CMD_STOPSEQ,
    /* 0x134 */ CS_CMD_PLAYAMBIENCE,
    /* 0x135 */ CS_CMD_FADEAMBIENCE,
    /* 0x15E */ CS_CMD_15E = 0x15E,
    /* 0x15F */ CS_CMD_15F,
    /* 0x190 */ CS_CMD_190 = 0x190,
} CutsceneCmd;

typedef union CutsceneData {
    s32 i;
    f32 f;
    s16 s[2];
    s8  b[4];
} CutsceneData;

#endif
