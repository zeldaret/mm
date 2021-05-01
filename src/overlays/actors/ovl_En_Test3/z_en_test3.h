#ifndef Z_EN_TEST3_H
#define Z_EN_TEST3_H

#include <global.h>

struct EnTest3;

typedef void (*EnTest3ActionFunc)(struct EnTest3*, struct GlobalContext*);

typedef struct {
    /* 0x0 */ u8 unk_00;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u16 textId;
} TalkState;

typedef struct {
    /* 0x0 */ u8 unk_00;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ s16 unk_02;
    /* 0x4 */ Vec3s* pos;
} PathInfo;

typedef struct {
    /* 0x0 */ u8 eyeTexId;
    /* 0x1 */ u8 mouthTexId;
} FaceAnimKeyFrame;

typedef struct EnTest3 {
    /* 0x000 */ Player actor;
    /* 0xD78 */ TalkState* talkState;
    /* 0xD7C */ PathInfo* path;
    /* 0xD80 */ s32 unk_D80; // schedule/time related
    /* 0xD84 */ f32 unk_D84; // path related
    /* 0xD88 */ s8 schedule;
    /* 0xD89 */ u8 actionId;
    /* 0xD8A */ s16 unk_D8A;
    /* 0xD8C */ u8 timer;
    /* 0xD8D */ s8 eventId;
    /* 0xD8E */ s16 camId;
    /* 0xD90 */ Player* player;
    /* 0xD94 */ EnTest3ActionFunc actionFunc;
    /* 0xD98 */ Vec3f unk_D98; // nurb spline stuff
    /* 0xDA4 */ f32 unk_DA4;
    /* 0xDA8 */ s32 unk_DA8;
    /* 0xDAC */ s32 unk_DAC;
    /* 0xDB0 */ s32 unk_DB0;
    /* 0xDB4 */ s32 unk_DB4;
} EnTest3; // size = 0xDB8

extern const ActorInit En_Test3_InitVars;

#endif // Z_EN_TEST3_H
