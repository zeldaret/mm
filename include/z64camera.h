#ifndef _Z64CAMERA_H_
#define _Z64CAMERA_H_

#include <ultra64.h>
// #include "global.h"

typedef struct {
    /* 0x0 */ s16 func;
    /* 0x2 */ UNK_TYPE1 pad2[0x6];
} CameraModeParams; // size = 0x8

typedef struct {
    /* 0x0 */ u32 validModes;
    /* 0x4 */ UNK_TYPE1 pad4[0x4];
    /* 0x8 */ CameraModeParams* modes;
} CameraStateParams; // size = 0xC

// typedef struct Camera Camera;

// typedef s32(*camera_update_func)(Camera* camera);

typedef struct Camera {
    /* 0x000 */ UNK_TYPE1 pad0[0x4];
    /* 0x004 */ Vec3f unk4;
    /* 0x010 */ UNK_TYPE1 pad10[0x8];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ s16 unk1C;
    /* 0x01E */ s16 unk1E;
    /* 0x020 */ Vec3f unk20;
    /* 0x02C */ UNK_TYPE1 pad2C[0x2];
    /* 0x02E */ s16 unk2E;
    /* 0x030 */ UNK_TYPE1 pad30[0x10];
    /* 0x040 */ s16 unk40;
    /* 0x042 */ s16 unk42;
    /* 0x044 */ UNK_TYPE1 pad44[0x8];
    /* 0x04C */ s16 unk4C;
    /* 0x04E */ UNK_TYPE1 pad4E[0x2];
    /* 0x050 */ Vec3f focalPoint;
    /* 0x05C */ Vec3f eye;
    /* 0x068 */ Vec3f upDir;
    /* 0x074 */ Vec3f unk74;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ f32 unk88;
    /* 0x08C */ struct GlobalContext* globalCtx;
    /* 0x090 */ struct ActorPlayer* player;
    /* 0x094 */ PosRot unk94;
    /* 0x0A8 */ struct Actor* unkA8;
    /* 0x0AC */ Vec3f unkAC;
    /* 0x0B8 */ UNK_TYPE1 padB8[0x8];
    /* 0x0C0 */ f32 unkC0;
    /* 0x0C4 */ f32 unkC4;
    /* 0x0C8 */ f32 unkC8;
    /* 0x0CC */ f32 unkCC;
    /* 0x0D0 */ f32 unkD0;
    /* 0x0D4 */ f32 unkD4;
    /* 0x0D8 */ UNK_TYPE1 padD8[0x4];
    /* 0x0DC */ f32 unkDC;
    /* 0x0E0 */ f32 unkE0;
    /* 0x0E4 */ UNK_TYPE1 padE4[0x18];
    /* 0x0FC */ f32 fov;
    /* 0x100 */ f32 unk100;
    /* 0x104 */ UNK_TYPE1 pad104[0x30];
    /* 0x134 */ Vec3s unk134;
    /* 0x13A */ UNK_TYPE1 pad13A[0x4];
    /* 0x13E */ u16 unk13E;
    /* 0x140 */ s16 unk140;
    /* 0x142 */ s16 state;
    /* 0x144 */ s16 mode;
    /* 0x146 */ UNK_TYPE1 pad146[0x2];
    /* 0x148 */ s16 unk148;
    /* 0x14A */ s16 unk14A;
    /* 0x14C */ s16 unk14C;
    /* 0x14E */ UNK_TYPE1 pad14E[0x6];
    /* 0x154 */ s16 unk154;
    /* 0x156 */ UNK_TYPE1 pad156[0x4];
    /* 0x15A */ s16 unk15A;
    /* 0x15C */ s16 unk15C;
    /* 0x15E */ s16 unk15E;
    /* 0x160 */ UNK_TYPE1 pad160[0x4];
    /* 0x164 */ s16 unk164;
    /* 0x166 */ s16 unk166;
    /* 0x168 */ UNK_TYPE1 pad168[0x10];
} Camera; // size = 0x178

#endif
