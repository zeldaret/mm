#include "global.h"

// padmgr functions
s32 func_80175008();
void func_8017506C(s32);

typedef struct {
    /* 0x00 */ u8* unk_00;
    /* 0x04 */ u8 unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ u16 unk_0C;
    /* 0x0E */ u16 unk_0E;
    /* 0x10 */ u16 unk_10;
    /* 0x12 */ u16 unk_12;
    /* 0x14 */ u16 unk_14;
} OSVoiceUnk; // size = 0x18

extern OSVoiceUnk D_801FD5A0;
extern OSVoiceHandle D_801FD5B8;

char D_801D8E50[] =
    "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU\0ZU\0SE\0ZE\0SO"
    "\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0"
    "PE\0HO\0BO\0PO\0MA\0MI\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke"
    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

char D_801D8F70[] = "aa\0AA\0ii\0II\0uu\0UU\0ee\0EE\0oo\0OO\0KA\0GA\0KI\0GI\0KU\0GU\0KE\0GE\0KO\0GO\0SA\0ZA\0SI\0ZI\0SU"
                    "\0ZU\0SE\0ZE\0SO\0ZO\0TA\0DA\0TI\0DI\0tu\0TU\0DU\0TE\0DE\0TO\0DO\0NA\0NI\0NU\0NE\0NO\0HA\0BA\0PA\0"
                    "HI\0BI\0PI\0HU\0BU\0PU\0HE\0BE\0PE\0HO\0BO\0PO\0MA\0MI\0  "
                    "\0MU\0ME\0MO\0ya\0YA\0yu\0YU\0yo\0YO\0RA\0RI\0RU\0RE\0RO\0wa\0WA\0WI\0WE\0WO\0NN\0VU\0ka\0ke\0\0\0"
                    "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0";

/*
char D_801E0EC0[] = "Error %d\n"
char D_801E0ECC[] = "NAI_VRS:osVoiceClearDictionary %d\n"
char D_801E0EF0[] = "NAI_VRS:dict error! (%d-%d %s)\n"
char D_801E0F10[] = "NAI_VRS:Ina_SetVruGain Error!\n"
char D_801E0F30[] = "NAI_VRS:mask on  %d\n"
char D_801E0F48[] = "NAI_VRS:mask off %d\n"
char D_801E0F60[] = "NAI_VRS:answer No.:%d Dist:%d Warn:%04X Level:%5d SN:%5d (Num:%d)\n"
char D_801E0FA4[] = "NAI_VRS:error !! (ANS_MAX:%d DIST:%d WARNING:%04X LEVEL:%5d SN:%5d)\n"
*/
#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/D_801E0EC0.s")

s32 func_801A51F0(s32 errorCode) {
    switch (errorCode) {
        case CONT_ERR_NO_CONTROLLER:
        case CONT_ERR_CONTRFAIL:
        case CONT_ERR_INVALID:
        case CONT_ERR_DEVICE:
        case CONT_ERR_VOICE_MEMORY:
        case CONT_ERR_VOICE_WORD:
        case CONT_ERR_VOICE_NO_RESPONSE:
            return -1;
        default:
            return 0;
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5228.s")

s32 func_801A5390(void) {
    s32 temp_t6;
    s32 sp18;

    temp_t6 = D_801FD5A0.unk_08;
    D_801FD5A0.unk_08 = 0;
    sp18 = func_80175008();
    osVoiceStartReadData(&D_801FD5B8);
    func_8017506C(sp18);
    return temp_t6;
}

s32 func_801A53DC(void) {
    return D_801FD5A0.unk_00;
}

void func_801A53E8(u16 arg0, u16 arg1, u16 arg2, u16 arg3, u16 arg4) {
    D_801FD5A0.unk_0C = arg0;
    D_801FD5A0.unk_0E = arg1;
    D_801FD5A0.unk_10 = arg2;
    D_801FD5A0.unk_12 = arg3;
    D_801FD5A0.unk_14 = arg4;
}

void func_801A541C(s32 analog, s32 digital) {
    s32 sp1C;
    s32 sp18;

    if (D_801FD5A0.unk_00 != 0) {
        sp18 = func_80175008();
        sp1C = osVoiceControlGain(&D_801FD5B8, analog, digital);
        func_8017506C(sp18);
        if (sp1C != 0) {
            func_801A51F0(sp1C);
        }
    }
}

s32 func_801A5488(u8* word) {
    s32 sp1C;
    s32 sp18;
    s32 temp_v0;

    sp18 = func_80175008();
    sp1C = osVoiceCheckWord(word);
    func_8017506C(sp18);
    return sp1C;
}

UNK_PTR func_801A54C4(void) {
    return &D_801FD608;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A54D0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5680.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5808.s")

void func_801A5A10(void) {
    D_801FD5A0.unk_00 = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/code_801A51F0/func_801A5A1C.s")
