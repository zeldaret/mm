#include "global.h"

// Checks whether or not a word can be registered in the dictionary
#ifdef NON_EQUIVALENT
s32 osVoiceCheckWord(u8* word) {
    s32 i;
    s32 errorCode = 0;
    u16 currentWord; // currentLetter? currentSyllable?
    u16 new_var;

    for (i = 0; word[i] != 0; i += 2) {
        new_var = word[i]; // Fake? But helps?
        currentWord = word[i + 1] + (new_var << 8);
        if (((currentWord != 0x815B) && (currentWord < 0x829F)) ||
            ((currentWord >= 0x82F2) && (currentWord < 0x8340)) || (currentWord == 0x837F) || (currentWord >= 0x8397)) {
            errorCode = 0xE;
        } else if ((i == 0) && ((currentWord == 0x815B) || (currentWord == 0x82F1) || (currentWord == 0x82C1) ||
                                (currentWord == 0x82EC) || (currentWord == 0x8393) || (currentWord == 0x8362) ||
                                (currentWord == 0x838E) || (currentWord == 0x8395) || (currentWord == 0x8396))) {
            errorCode = 0xE;
        } else if (((currentWord == 0x829F) || (currentWord == 0x8340)) && (currentWord != 0x82D3) &&
                   (currentWord != 0x8374) && (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82A1) || (currentWord == 0x8342)) && (currentWord != 0x82A4) &&
                   (currentWord != 0x82C4) && (currentWord != 0x82C5) && (currentWord != 0x82D3) &&
                   (currentWord != 0x8345) && (currentWord != 0x8365) && (currentWord != 0x8366) &&
                   (currentWord != 0x8374) && (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82A3) || (currentWord == 0x8344)) && (currentWord != 0x82C6) &&
                   (currentWord != 0x82C7) && (currentWord != 0x82D3) && (currentWord != 0x8367) &&
                   (currentWord != 0x8368) && (currentWord != 0x8374) && (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82A5) || (currentWord == 0x8346)) && (currentWord != 0x82A4) &&
                   (currentWord != 0x82B5) && (currentWord != 0x82B6) && (currentWord != 0x82BF) &&
                   (currentWord != 0x82C0) && (currentWord != 0x82C2) && (currentWord != 0x82D3) &&
                   (currentWord != 0x8345) && (currentWord != 0x8356) && (currentWord != 0x8357) &&
                   (currentWord != 0x8360) && (currentWord != 0x8361) && (currentWord != 0x8363) &&
                   (currentWord != 0x8374) && (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82A7) || (currentWord == 0x8348)) && (currentWord != 0x82A4) &&
                   (currentWord != 0x82D3) && (currentWord != 0x8345) && (currentWord != 0x8374) &&
                   (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82E1) || (currentWord == 0x82E3) || (currentWord == 0x82E5) ||
                    (currentWord == 0x8383) || (currentWord == 0x8385) || (currentWord == 0x8387)) &&
                   (currentWord != 0x82AB) && (currentWord != 0x82B5) && (currentWord != 0x82BF) &&
                   (currentWord != 0x82C9) && (currentWord != 0x82D0) && (currentWord != 0x82DD) &&
                   (currentWord != 0x82E8) && (currentWord != 0x82AC) && (currentWord != 0x82B6) &&
                   (currentWord != 0x82C0) && (currentWord != 0x82D1) && (currentWord != 0x82D2) &&
                   (currentWord != 0x834C) && (currentWord != 0x8356) && (currentWord != 0x8360) &&
                   (currentWord != 0x836A) && (currentWord != 0x8371) && (currentWord != 0x837E) &&
                   (currentWord != 0x838A) && (currentWord != 0x834D) && (currentWord != 0x8357) &&
                   (currentWord != 0x8361) && (currentWord != 0x8372) && (currentWord != 0x8373) &&
                   (currentWord != 0x8394)) {
            errorCode = 0xE;
        } else if ((currentWord == 0x815B) && ((currentWord == 0x82F1) || (currentWord == 0x82C1) ||
                                               (currentWord == 0x8393) || (currentWord == 0x8362))) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82F1) || (currentWord == 0x8393)) &&
                   ((currentWord == 0x82F1) || (currentWord == 0x8393))) {
            errorCode = 0xE;
        } else if (((currentWord == 0x82C1) || (currentWord == 0x8362)) &&
                   ((currentWord == 0x815B) || (currentWord == 0x82A0) || (currentWord == 0x82A2) ||
                    (currentWord == 0x82A4) || (currentWord == 0x82A6) || (currentWord == 0x82A8) ||
                    (currentWord == 0x82C8) || (currentWord == 0x82C9) || (currentWord == 0x82CA) ||
                    (currentWord == 0x82CB) || (currentWord == 0x82CC) || (currentWord == 0x82DC) ||
                    (currentWord == 0x82DD) || (currentWord == 0x82DE) || (currentWord == 0x82DF) ||
                    (currentWord == 0x82E0) || (currentWord == 0x82E2) || (currentWord == 0x82E4) ||
                    (currentWord == 0x82E6) || (currentWord == 0x82E7) || (currentWord == 0x82E8) ||
                    (currentWord == 0x82E9) || (currentWord == 0x82EA) || (currentWord == 0x82EB) ||
                    (currentWord == 0x82ED) || (currentWord == 0x82EE) || (currentWord == 0x82EF) ||
                    (currentWord == 0x82F0) || (currentWord == 0x82F1) || (currentWord == 0x829F) ||
                    (currentWord == 0x82A1) || (currentWord == 0x82A3) || (currentWord == 0x82A5) ||
                    (currentWord == 0x82A7) || (currentWord == 0x82E1) || (currentWord == 0x82E3) ||
                    (currentWord == 0x82E5) || (currentWord == 0x82C1) || (currentWord == 0x82EC) ||
                    (currentWord == 0x8341) || (currentWord == 0x8343) || (currentWord == 0x8345) ||
                    (currentWord == 0x8347) || (currentWord == 0x8349) || (currentWord == 0x8369) ||
                    (currentWord == 0x836A) || (currentWord == 0x836B) || (currentWord == 0x836C) ||
                    (currentWord == 0x836D) || (currentWord == 0x837D) || (currentWord == 0x837E) ||
                    (currentWord == 0x8380) || (currentWord == 0x8381) || (currentWord == 0x8382) ||
                    (currentWord == 0x8384) || (currentWord == 0x8386) || (currentWord == 0x8388) ||
                    (currentWord == 0x8389) || (currentWord == 0x838A) || (currentWord == 0x838B) ||
                    (currentWord == 0x838C) || (currentWord == 0x838D) || (currentWord == 0x838F) ||
                    (currentWord == 0x8390) || (currentWord == 0x8391) || (currentWord == 0x8392) ||
                    (currentWord == 0x8393) || (currentWord == 0x8340) || (currentWord == 0x8342) ||
                    (currentWord == 0x8344) || (currentWord == 0x8346) || (currentWord == 0x8348) ||
                    (currentWord == 0x8383) || (currentWord == 0x8385) || (currentWord == 0x8387) ||
                    (currentWord == 0x8362) || (currentWord == 0x838E))) {
            errorCode = 0xE;
        }

        if (errorCode != 0) {
            return errorCode;
        }
    }

    if ((currentWord == 0x82C1) || (currentWord == 0x8362)) {
        errorCode = 0xE;
    }

    return errorCode;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/boot/voicecheckword/osVoiceCheckWord.s")
#endif
