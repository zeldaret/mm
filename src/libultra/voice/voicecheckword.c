#include "global.h"

// Checks whether or not a word can be registered in the dictionary
s32 osVoiceCheckWord(u8* word) {
    s32 i;
    s32 errorCode = 0;
    u16 currentSyllable;
    u16 prevSyllable = 0;

    for (i = 0; word[i] != 0; i += 2) {
        currentSyllable = (word[i] << 8) + word[i + 1];
        if (((currentSyllable != 0x815B) && (currentSyllable < 0x829F)) ||
            ((currentSyllable >= 0x82F2) && (currentSyllable < 0x8340)) || (currentSyllable == 0x837F) ||
            (currentSyllable >= 0x8397)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if ((i == 0) &&
                   ((currentSyllable == 0x815B) || (currentSyllable == 0x82F1) || (currentSyllable == 0x82C1) ||
                    (currentSyllable == 0x82EC) || (currentSyllable == 0x8393) || (currentSyllable == 0x8362) ||
                    (currentSyllable == 0x838E) || (currentSyllable == 0x8395) || (currentSyllable == 0x8396))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x829F) || (currentSyllable == 0x8340)) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82A1) || (currentSyllable == 0x8342)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82C4) && (prevSyllable != 0x82C5) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8345) && (prevSyllable != 0x8365) && (prevSyllable != 0x8366) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82A3) || (currentSyllable == 0x8344)) && (prevSyllable != 0x82C6) &&
                   (prevSyllable != 0x82C7) && (prevSyllable != 0x82D3) && (prevSyllable != 0x8367) &&
                   (prevSyllable != 0x8368) && (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82A5) || (currentSyllable == 0x8346)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82B5) && (prevSyllable != 0x82B6) && (prevSyllable != 0x82BF) &&
                   (prevSyllable != 0x82C0) && (prevSyllable != 0x82C2) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8345) && (prevSyllable != 0x8356) && (prevSyllable != 0x8357) &&
                   (prevSyllable != 0x8360) && (prevSyllable != 0x8361) && (prevSyllable != 0x8363) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82A7) || (currentSyllable == 0x8348)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82D3) && (prevSyllable != 0x8345) && (prevSyllable != 0x8374) &&
                   (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82E1) || (currentSyllable == 0x82E3) || (currentSyllable == 0x82E5) ||
                    (currentSyllable == 0x8383) || (currentSyllable == 0x8385) || (currentSyllable == 0x8387)) &&
                   (prevSyllable != 0x82AB) && (prevSyllable != 0x82B5) && (prevSyllable != 0x82BF) &&
                   (prevSyllable != 0x82C9) && (prevSyllable != 0x82D0) && (prevSyllable != 0x82DD) &&
                   (prevSyllable != 0x82E8) && (prevSyllable != 0x82AC) && (prevSyllable != 0x82B6) &&
                   (prevSyllable != 0x82C0) && (prevSyllable != 0x82D1) && (prevSyllable != 0x82D2) &&
                   (prevSyllable != 0x834C) && (prevSyllable != 0x8356) && (prevSyllable != 0x8360) &&
                   (prevSyllable != 0x836A) && (prevSyllable != 0x8371) && (prevSyllable != 0x837E) &&
                   (prevSyllable != 0x838A) && (prevSyllable != 0x834D) && (prevSyllable != 0x8357) &&
                   (prevSyllable != 0x8361) && (prevSyllable != 0x8372) && (prevSyllable != 0x8373) &&
                   (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if ((currentSyllable == 0x815B) && ((prevSyllable == 0x82F1) || (prevSyllable == 0x82C1) ||
                                                   (prevSyllable == 0x8393) || (prevSyllable == 0x8362))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currentSyllable == 0x82F1) || (currentSyllable == 0x8393)) &&
                   ((prevSyllable == 0x82F1) || (prevSyllable == 0x8393))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((prevSyllable == 0x82C1) || (prevSyllable == 0x8362)) &&
                   ((currentSyllable == 0x815B) || (currentSyllable == 0x82A0) || (currentSyllable == 0x82A2) ||
                    (currentSyllable == 0x82A4) || (currentSyllable == 0x82A6) || (currentSyllable == 0x82A8) ||
                    (currentSyllable == 0x82C8) || (currentSyllable == 0x82C9) || (currentSyllable == 0x82CA) ||
                    (currentSyllable == 0x82CB) || (currentSyllable == 0x82CC) || (currentSyllable == 0x82DC) ||
                    (currentSyllable == 0x82DD) || (currentSyllable == 0x82DE) || (currentSyllable == 0x82DF) ||
                    (currentSyllable == 0x82E0) || (currentSyllable == 0x82E2) || (currentSyllable == 0x82E4) ||
                    (currentSyllable == 0x82E6) || (currentSyllable == 0x82E7) || (currentSyllable == 0x82E8) ||
                    (currentSyllable == 0x82E9) || (currentSyllable == 0x82EA) || (currentSyllable == 0x82EB) ||
                    (currentSyllable == 0x82ED) || (currentSyllable == 0x82EE) || (currentSyllable == 0x82EF) ||
                    (currentSyllable == 0x82F0) || (currentSyllable == 0x82F1) || (currentSyllable == 0x829F) ||
                    (currentSyllable == 0x82A1) || (currentSyllable == 0x82A3) || (currentSyllable == 0x82A5) ||
                    (currentSyllable == 0x82A7) || (currentSyllable == 0x82E1) || (currentSyllable == 0x82E3) ||
                    (currentSyllable == 0x82E5) || (currentSyllable == 0x82C1) || (currentSyllable == 0x82EC) ||
                    (currentSyllable == 0x8341) || (currentSyllable == 0x8343) || (currentSyllable == 0x8345) ||
                    (currentSyllable == 0x8347) || (currentSyllable == 0x8349) || (currentSyllable == 0x8369) ||
                    (currentSyllable == 0x836A) || (currentSyllable == 0x836B) || (currentSyllable == 0x836C) ||
                    (currentSyllable == 0x836D) || (currentSyllable == 0x837D) || (currentSyllable == 0x837E) ||
                    (currentSyllable == 0x8380) || (currentSyllable == 0x8381) || (currentSyllable == 0x8382) ||
                    (currentSyllable == 0x8384) || (currentSyllable == 0x8386) || (currentSyllable == 0x8388) ||
                    (currentSyllable == 0x8389) || (currentSyllable == 0x838A) || (currentSyllable == 0x838B) ||
                    (currentSyllable == 0x838C) || (currentSyllable == 0x838D) || (currentSyllable == 0x838F) ||
                    (currentSyllable == 0x8390) || (currentSyllable == 0x8391) || (currentSyllable == 0x8392) ||
                    (currentSyllable == 0x8393) || (currentSyllable == 0x8340) || (currentSyllable == 0x8342) ||
                    (currentSyllable == 0x8344) || (currentSyllable == 0x8346) || (currentSyllable == 0x8348) ||
                    (currentSyllable == 0x8383) || (currentSyllable == 0x8385) || (currentSyllable == 0x8387) ||
                    (currentSyllable == 0x8362) || (currentSyllable == 0x838E))) {
            errorCode = CONT_ERR_VOICE_WORD;
        }

        if (errorCode != 0) {
            return errorCode;
        }

        prevSyllable = currentSyllable;
    }

    if ((currentSyllable == 0x82C1) || (currentSyllable == 0x8362)) {
        errorCode = CONT_ERR_VOICE_WORD;
    }

    return errorCode;
}
