#ifndef _Z64CUTSCENE_H_
#define _Z64CUTSCENE_H_

#include <ultra64.h>
#include <unk.h>

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
    /* 0x00 */ u16 unk0; // action; // "dousa"
    /* 0x02 */ u16 startFrame;
    /* 0x04 */ u16 endFrame;
    /* 0x06 */ UNK_TYPE1 pad6[0x2A];
} CsCmdActorAction; // size = 0x30

typedef struct {
    /* 0x0 */ u16 base;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
} CsCmdBase; // size = 0x6

typedef struct {
    /* 0x0 */ u16 unk0;
    /* 0x2 */ u16 startFrame;
    /* 0x4 */ u16 endFrame;
    /* 0x6 */ u8 hour;
    /* 0x7 */ u8 minute;
} CsCmdDayTime; // size = 0x8

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
} CsCmdMusicFade; // size = 0x6

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

typedef union CutsceneData {
    s32 i;
    f32 f;
    s16 s[2];
    s8  b[4];
} CutsceneData;

#endif
