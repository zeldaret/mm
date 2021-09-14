#ifndef _Z64_SELECT_H_
#define _Z64_SELECT_H_

#include "global.h"

struct SelectContext;

void Select_Init(GameState* thisx);
void Select_Destroy(GameState* thisx);

typedef void (*Select_LoadFunc)(struct SelectContext*, u32, s32);

typedef struct {
    /* 0x00 */ char* name;
    /* 0x04 */ Select_LoadFunc loadFunc;
    /* 0x08 */ s32 entranceIndex;
} SceneSelectEntry; // size = 0xC

typedef struct SelectContext {
    /* 0x000 */ GameState state;
    /* 0x0A8 */ View view;
    /* 0x210 */ s32 count;
    /* 0x214 */ SceneSelectEntry* scenes;
    /* 0x218 */ s32 currentScene;
    /* 0x21C */ s32 unk_21C; // Changed by L button
    /* 0x220 */ s32 unk_220[7];
    /* 0x23C */ char unk_23C[0xC];
    /* 0x248 */ s32 opt;
    /* 0x24C */ s32 cursorPos;
    /* 0x250 */ char unk_250[0xC];
    /* 0x25C */ s32 unk_25C; // accumulator?
    /* 0x260 */ s32 cursorVelocity;
    /* 0x264 */ s32 unk_264; // timer1
    /* 0x268 */ s32 unk_268; // timer2
    /* 0x26C */ s32 unk_26C; // bool?
    /* 0x270 */ s32 unk_270; // bool?
    /* 0x274 */ s32 unk_274; // set but unused
    /* 0x278 */ char unk_278[0x08];
} SelectContext; // size = 0x280

#endif
