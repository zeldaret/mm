#include "global.h"

typedef struct {
    /* 0x00 */ f32* posX;
    /* 0x04 */ f32* posY;
    /* 0x08 */ f32* posZ;
    /* 0x0C */ f32* freqScale;
    /* 0x10 */ f32* vol;
    /* 0x14 */ s8* reverbAdd;
    /* 0x18 */ f32 dist;
    /* 0x1C */ u32 priority; // lower is more prioritized
    /* 0x20 */ u16 sfxParams;
    /* 0x22 */ u16 sfxId;
    /* 0x25 */ u8 sfxUnk01;
    /* 0x24 */ u8 sfxImportance;
    /* 0x26 */ u8 state; // uses SfxState enum
    /* 0x27 */ u8 freshness;
    /* 0x28 */ u8 prev;
    /* 0x29 */ u8 next;
    /* 0x2A */ u8 channelIdx;
    /* 0x2B */ u8 unk_2F;
    /* 0x2C */ u8 token;
} SoundBankEntry; // size = 0x30

// gSoundBank
SoundBankEntry D_801FD710[9];
SoundBankEntry D_801FD8C0[12];
SoundBankEntry D_801FDB00[32];
SoundBankEntry D_801FE100[20];
SoundBankEntry D_801FE4C0[8];
SoundBankEntry D_801FE640[3];
SoundBankEntry D_801FE6D0[5];

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5BD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5C28.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5C8C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5CFC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5DDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A5F7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A6430.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A65C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A6D0C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7084.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7168.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7284.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A72CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7328.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7484.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A75E8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7720.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7794.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A7828.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A787C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A78E4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A5BD0/func_801A794C.s")
