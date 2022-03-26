#ifndef Z64RUMBLE_H
#define Z64RUMBLE_H

#include "PR/ultratypes.h"
#include "io/controller.h"

typedef struct UnkRumbleStruct {
    /* 0x000 */ u8 rumbleEnabled[MAXCONTROLLERS];
    /* 0x004 */ u8 unk_04[0x40];
    /* 0x044 */ u8 unk_44[0x40];
    /* 0x084 */ u8 unk_84[0x40];
    /* 0x0C4 */ u8 unk_C4[0x40];
    /* 0x104 */ u8 unk_104; // state?
    /* 0x105 */ u8 unk_105; // seems to be a boolean value
    /* 0x106 */ u16 unk_106;
    /* 0x108 */ u16 unk_108;
    /* 0x10A */ u8 unk_10A;
    /* 0x10B */ u8 unk_10B;
    /* 0x10C */ u8 unk_10C;
    /* 0x10D */ u8 unk_10D;
} UnkRumbleStruct; // size = 0x10E

void func_8013EC44(f32 arg0, u8 arg1, u8 arg2, u8 arg3);
void func_8013ECE0(f32 xyzDistToPlayerSq, u8 arg1, u8 arg2, u8 arg3);
void Rumble_Init(void);
void Rumble_Destroy(void);
s32 Rumble_ControllerOneHasRumblePak(void);
void func_8013EE24(void);
void func_8013EE38(void);
void func_8013EE48(s32 arg0);

void func_80182CE0(UnkRumbleStruct* arg0);
void func_80183020(UnkRumbleStruct* arg0);
void func_80183058(UnkRumbleStruct* arg0);

#endif
