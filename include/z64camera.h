#ifndef _Z64CAMERA_H_
#define _Z64CAMERA_H_

#include "ultra64.h"

#define MAIN_CAM 0

typedef enum {
    /* 0x00 */ CAM_FUNC_NONE,
    /* 0x01 */ CAM_FUNC_NORM0,
    /* 0x02 */ CAM_FUNC_NORM1,
    /* 0x03 */ CAM_FUNC_NORM2,
    /* 0x04 */ CAM_FUNC_NORM3,
    /* 0x05 */ CAM_FUNC_NORM4,
    /* 0x06 */ CAM_FUNC_PARA0,
    /* 0x07 */ CAM_FUNC_PARA1,
    /* 0x08 */ CAM_FUNC_PARA2,
    /* 0x09 */ CAM_FUNC_PARA3,
    /* 0x0A */ CAM_FUNC_PARA4,
    /* 0x0B */ CAM_FUNC_KEEP0,
    /* 0x0C */ CAM_FUNC_KEEP1,
    /* 0x0D */ CAM_FUNC_KEEP2,
    /* 0x0E */ CAM_FUNC_KEEP3,
    /* 0x0F */ CAM_FUNC_KEEP4,
    /* 0x10 */ CAM_FUNC_SUBJ0,
    /* 0x11 */ CAM_FUNC_SUBJ1,
    /* 0x12 */ CAM_FUNC_SUBJ2,
    /* 0x13 */ CAM_FUNC_SUBJ3,
    /* 0x14 */ CAM_FUNC_SUBJ4,
    /* 0x15 */ CAM_FUNC_JUMP0,
    /* 0x16 */ CAM_FUNC_JUMP1,
    /* 0x17 */ CAM_FUNC_JUMP2,
    /* 0x18 */ CAM_FUNC_JUMP3,
    /* 0x19 */ CAM_FUNC_JUMP4,
    /* 0x1A */ CAM_FUNC_BATT0,
    /* 0x1B */ CAM_FUNC_BATT1,
    /* 0x1C */ CAM_FUNC_BATT2,
    /* 0x1D */ CAM_FUNC_BATT3,
    /* 0x1E */ CAM_FUNC_BATT4,
    /* 0x1F */ CAM_FUNC_FIXD0,
    /* 0x20 */ CAM_FUNC_FIXD1,
    /* 0x21 */ CAM_FUNC_FIXD2,
    /* 0x22 */ CAM_FUNC_FIXD3,
    /* 0x23 */ CAM_FUNC_FIXD4,
    /* 0x24 */ CAM_FUNC_DATA0,
    /* 0x25 */ CAM_FUNC_DATA1,
    /* 0x26 */ CAM_FUNC_DATA2,
    /* 0x27 */ CAM_FUNC_DATA3,
    /* 0x28 */ CAM_FUNC_DATA4,
    /* 0x29 */ CAM_FUNC_UNIQ0,
    /* 0x2A */ CAM_FUNC_UNIQ1,
    /* 0x2B */ CAM_FUNC_UNIQ2,
    /* 0x2C */ CAM_FUNC_UNIQ3,
    /* 0x2D */ CAM_FUNC_UNIQ4,
    /* 0x2E */ CAM_FUNC_UNIQ5,
    /* 0x2F */ CAM_FUNC_UNIQ6,
    /* 0x30 */ CAM_FUNC_UNIQ7,
    /* 0x31 */ CAM_FUNC_UNIQ8,
    /* 0x32 */ CAM_FUNC_UNIQ9,
    /* 0x33 */ CAM_FUNC_DEMO0,
    /* 0x34 */ CAM_FUNC_DEMO1,
    /* 0x35 */ CAM_FUNC_DEMO2,
    /* 0x36 */ CAM_FUNC_DEMO3,
    /* 0x37 */ CAM_FUNC_DEMO4,
    /* 0x38 */ CAM_FUNC_DEMO5,
    /* 0x39 */ CAM_FUNC_DEMO6,
    /* 0x3A */ CAM_FUNC_DEMO7,
    /* 0x3B */ CAM_FUNC_DEMO8,
    /* 0x3C */ CAM_FUNC_DEMO9,
    /* 0x3D */ CAM_FUNC_SPEC0,
    /* 0x3E */ CAM_FUNC_SPEC1,
    /* 0x3F */ CAM_FUNC_SPEC2,
    /* 0x40 */ CAM_FUNC_SPEC3,
    /* 0x41 */ CAM_FUNC_SPEC4,
    /* 0x42 */ CAM_FUNC_SPEC5,
    /* 0x43 */ CAM_FUNC_SPEC6,
    /* 0x44 */ CAM_FUNC_SPEC7,
    /* 0x45 */ CAM_FUNC_SPEC8,
    /* 0x46 */ CAM_FUNC_SPEC9,
    /* 0x47 */ CAM_FUNC_MAX
} CameraFuncType;

typedef struct {
    /* 0x0 */ s16 val;
    /* 0x2 */ s16 param;
} CameraModeValue; // size = 0x4

typedef struct {
    /* 0x0 */ s16 funcIdx;
    /* 0x2 */ s16 valueCnt;
    /* 0x4 */ CameraModeValue* values;
} CameraMode; // size = 0x8

typedef struct {
    /* 0x0 */ union {
        u32 unk_00;
        struct {
            u32 unk_bit0 : 1;
            u32 unk_bit1 : 1;
            u32 validModes : 30;
        };
    };
    /* 0x4 */ u32 unk_04;
    /* 0x8 */ CameraMode* cameraModes;
} CameraSetting; // size = 0xC

typedef struct {
    /* 0x0000 */ struct Actor* doorActor;
    /* 0x0004 */ s16 camDataIdx;
    /* 0x0006 */ s16 timer1;
    /* 0x0008 */ s16 timer2;
    /* 0x000A */ s16 timer3;
} DoorParams; // size = 0xC

typedef struct {
    /* 0x0000 */ Vec3f pos;
    /* 0x000C */ Vec3f norm;
    /* 0x0018 */ CollisionPoly* poly;
    /* 0x001C */ VecSph sphNorm;
    /* 0x0024 */ s32 bgId;
} CamColChk; // size = 0x28

typedef struct Camera {
    /* 0x000 */ char paramData[0x50];
    /* 0x050 */ Vec3f focalPoint;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f upDir;
    /* 0x074 */ Vec3f eyeNext;
    /* 0x080 */ Vec3f skyboxOffset;
    /* 0x08C */ struct GlobalContext* globalCtx;
    /* 0x090 */ struct ActorPlayer* player;
    /* 0x094 */ PosRot playerPosRot;
    /* 0x0A8 */ struct Actor* target;
    /* 0x0AC */ PosRot targetPosRot;
    /* 0x0C0 */ f32 rUpdateRateInv;
    /* 0x0C4 */ f32 pitchUpdateRateInv;
    /* 0x0C8 */ f32 yawUpdateRateInv;
    /* 0x0CC */ f32 xzOffsetUpdateRate; // May be swapped with yOffset immediately below
    /* 0x0D0 */ f32 yOffsetUpdateRate;
    /* 0x0D4 */ f32 fovUpdateRate;
    /* 0x0D8 */ f32 xzSpeed;
    /* 0x0DC */ f32 dist;
    /* 0x0E0 */ f32 speedRatio;
    /* 0x0E4 */ Vec3f posOffset;
    /* 0x0F0 */ Vec3f playerPosDelta;
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 atLERPStepScale;
    /* 0x104 */ f32 playerGroundY;
    /* 0x108 */ Vec3f floorNorm;
    /* 0x114 */ f32 waterYPos;
    /* 0x118 */ s32 waterPrevCamIdx;
    /* 0x11C */ s32 waterPrevCamSetting;
    /* 0x120 */ s32 waterQuakeId;
    /* 0x124 */ void* data0;
    /* 0x128 */ void* data1;
    /* 0x12C */ s16 data2;
    /* 0x12E */ s16 data3;
    /* 0x130 */ s16 uid;
    /* 0x132 */ char unk_132[2];
    /* 0x134 */ Vec3s inputDir;
    /* 0x13A */ Vec3s camDir;
    /* 0x140 */ s16 status;
    /* 0x142 */ s16 setting;
    /* 0x144 */ s16 mode;
    /* 0x146 */ s16 bgCheckId;
    /* 0x148 */ s16 camDataIdx;
    /* 0x14A */ s16 unk_14A;
    /* 0x14C */ s16 flags;
    /* 0x14E */ s16 childCamIdx;
    /* 0x150 */ s16 unk_150;
    /* 0x152 */ s16 unk_152;
    /* 0x154 */ s16 prevSetting;
    /* 0x156 */ s16 nextCamDataIdx;
    /* 0x158 */ s16 nextBGCheckId;
    /* 0x15A */ s16 roll;
    /* 0x15C */ s16 paramFlags;
    /* 0x15E */ s16 animState;
    /* 0x160 */ s16 unk_160;
    /* 0x162 */ s16 timer;
    /* 0x164 */ s16 thisIdx;
    /* 0x166 */ s16 unk166;
    /* 0x168 */ UNK_TYPE1 pad168[0x10];
} Camera; // size = 0x178

#endif
