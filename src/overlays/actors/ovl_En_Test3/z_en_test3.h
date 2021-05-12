#ifndef Z_EN_TEST3_H
#define Z_EN_TEST3_H

#include <global.h>

struct EnTest3;

typedef void (*EnTest3ActionFunc)(struct EnTest3*, struct GlobalContext*);

typedef struct {
    /* 0x0 */ u8 unk_00;
    /* 0x1 */ u8 unk_01;
    /* 0x2 */ u16 textId;
} TalkState; // size = 0x04

typedef struct {
    /* 0x0 */ u8 eyeTexId;
    /* 0x1 */ u8 mouthTexId;
} FaceAnimKeyFrame; // size = 0x02

typedef struct {
    /* 0x0 */ void (*init)(struct EnTest3*, struct GlobalContext*);
    /* 0x4 */ void (*action)(struct EnTest3*, struct GlobalContext*);
} KafeiActionSetupInfo; // size = 0x08

typedef struct {
    /* 0x0 */ s8 unk_00;
    /* 0x1 */ s8 unk_01_0 : 4;
    /* 0x1 */ s8 unk_01_1 : 4;
} struct_80A417E8_arg2; // size = 0x02

typedef struct {
    /* 0x0 */ u8 unk_00;
    /* 0x4 */ s32 unk_04;
    /* 0x8 */ s32 unk_08;
    /* 0xC */ s32 unk_0C;
} struct_80A417E8_arg3; // size = 0x10

typedef struct {
    /* 0x0 */ s32 (*unk_00)(struct EnTest3*, struct GlobalContext*, struct_80A417E8_arg2*, struct_80A417E8_arg3*);
    /* 0x4 */ s32 (*unk_04)(struct EnTest3*, struct GlobalContext*);
} struct_80A417E8; // size = 0x08

typedef s32 (*EnTest3_functions_80A4169C)(struct EnTest3*, struct GlobalContext*);

typedef struct EnTest3 {
    /* 0x000 */ Player actor;
    /* 0xD78 */ TalkState* talkState;
    /* 0xD7C */ PathInfo* path;
    /* 0xD80 */ s32 unk_D80;
    /* 0xD84 */ f32 unk_D84;
    /* 0xD88 */ s8 schedule;
    /* 0xD89 */ u8 actionId;
    /* 0xD8A */ s16 unk_D8A;
    /* 0xD8C */ u8 timer;
    /* 0xD8D */ s8 actorCutsceneId;
    /* 0xD8E */ s16 camId;
    /* 0xD90 */ Player* player;
    /* 0xD94 */ EnTest3ActionFunc action;
    /* 0xD98 */ Vec3f unk_D98;
    /* 0xDA4 */ f32 unk_DA4;
    /* 0xDA8 */ s32 unk_DA8;
    /* 0xDAC */ s32 unk_DAC;
    /* 0xDB0 */ s32 unk_DB0;
    /* 0xDB4 */ s32 unk_DB4;
} EnTest3; // size = 0xDB8

extern const ActorInit En_Test3_InitVars;

#endif // Z_EN_TEST3_H
