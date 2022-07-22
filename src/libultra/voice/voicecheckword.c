#include "global.h"

// Checks whether or not a word can be registered in the dictionary
s32 osVoiceCheckWord(u8* word) {
    s32 i;
    s32 errorCode = 0;
    u16 currSyllable;
    u16 prevSyllable = 0;

    for (i = 0; word[i] != 0; i += 2) {
        currSyllable = (word[i] << 8) + word[i + 1];
        if (((currSyllable != 0x815B) && (currSyllable < 0x829F)) ||
            ((currSyllable >= 0x82F2) && (currSyllable < 0x8340)) || (currSyllable == 0x837F) ||
            (currSyllable >= 0x8397)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if ((i == 0) && ((currSyllable == 0x815B) || (currSyllable == 0x82F1) || (currSyllable == 0x82C1) ||
                                (currSyllable == 0x82EC) || (currSyllable == 0x8393) || (currSyllable == 0x8362) ||
                                (currSyllable == 0x838E) || (currSyllable == 0x8395) || (currSyllable == 0x8396))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x829F) || (currSyllable == 0x8340)) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82A1) || (currSyllable == 0x8342)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82C4) && (prevSyllable != 0x82C5) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8345) && (prevSyllable != 0x8365) && (prevSyllable != 0x8366) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82A3) || (currSyllable == 0x8344)) && (prevSyllable != 0x82C6) &&
                   (prevSyllable != 0x82C7) && (prevSyllable != 0x82D3) && (prevSyllable != 0x8367) &&
                   (prevSyllable != 0x8368) && (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82A5) || (currSyllable == 0x8346)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82B5) && (prevSyllable != 0x82B6) && (prevSyllable != 0x82BF) &&
                   (prevSyllable != 0x82C0) && (prevSyllable != 0x82C2) && (prevSyllable != 0x82D3) &&
                   (prevSyllable != 0x8345) && (prevSyllable != 0x8356) && (prevSyllable != 0x8357) &&
                   (prevSyllable != 0x8360) && (prevSyllable != 0x8361) && (prevSyllable != 0x8363) &&
                   (prevSyllable != 0x8374) && (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82A7) || (currSyllable == 0x8348)) && (prevSyllable != 0x82A4) &&
                   (prevSyllable != 0x82D3) && (prevSyllable != 0x8345) && (prevSyllable != 0x8374) &&
                   (prevSyllable != 0x8394)) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82E1) || (currSyllable == 0x82E3) || (currSyllable == 0x82E5) ||
                    (currSyllable == 0x8383) || (currSyllable == 0x8385) || (currSyllable == 0x8387)) &&
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
        } else if ((currSyllable == 0x815B) && ((prevSyllable == 0x82F1) || (prevSyllable == 0x82C1) ||
                                                (prevSyllable == 0x8393) || (prevSyllable == 0x8362))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((currSyllable == 0x82F1) || (currSyllable == 0x8393)) &&
                   ((prevSyllable == 0x82F1) || (prevSyllable == 0x8393))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((prevSyllable == 0x82C1) || (prevSyllable == 0x8362)) &&
                   ((currSyllable == 0x815B) || (currSyllable == 0x82A0) || (currSyllable == 0x82A2) ||
                    (currSyllable == 0x82A4) || (currSyllable == 0x82A6) || (currSyllable == 0x82A8) ||
                    (currSyllable == 0x82C8) || (currSyllable == 0x82C9) || (currSyllable == 0x82CA) ||
                    (currSyllable == 0x82CB) || (currSyllable == 0x82CC) || (currSyllable == 0x82DC) ||
                    (currSyllable == 0x82DD) || (currSyllable == 0x82DE) || (currSyllable == 0x82DF) ||
                    (currSyllable == 0x82E0) || (currSyllable == 0x82E2) || (currSyllable == 0x82E4) ||
                    (currSyllable == 0x82E6) || (currSyllable == 0x82E7) || (currSyllable == 0x82E8) ||
                    (currSyllable == 0x82E9) || (currSyllable == 0x82EA) || (currSyllable == 0x82EB) ||
                    (currSyllable == 0x82ED) || (currSyllable == 0x82EE) || (currSyllable == 0x82EF) ||
                    (currSyllable == 0x82F0) || (currSyllable == 0x82F1) || (currSyllable == 0x829F) ||
                    (currSyllable == 0x82A1) || (currSyllable == 0x82A3) || (currSyllable == 0x82A5) ||
                    (currSyllable == 0x82A7) || (currSyllable == 0x82E1) || (currSyllable == 0x82E3) ||
                    (currSyllable == 0x82E5) || (currSyllable == 0x82C1) || (currSyllable == 0x82EC) ||
                    (currSyllable == 0x8341) || (currSyllable == 0x8343) || (currSyllable == 0x8345) ||
                    (currSyllable == 0x8347) || (currSyllable == 0x8349) || (currSyllable == 0x8369) ||
                    (currSyllable == 0x836A) || (currSyllable == 0x836B) || (currSyllable == 0x836C) ||
                    (currSyllable == 0x836D) || (currSyllable == 0x837D) || (currSyllable == 0x837E) ||
                    (currSyllable == 0x8380) || (currSyllable == 0x8381) || (currSyllable == 0x8382) ||
                    (currSyllable == 0x8384) || (currSyllable == 0x8386) || (currSyllable == 0x8388) ||
                    (currSyllable == 0x8389) || (currSyllable == 0x838A) || (currSyllable == 0x838B) ||
                    (currSyllable == 0x838C) || (currSyllable == 0x838D) || (currSyllable == 0x838F) ||
                    (currSyllable == 0x8390) || (currSyllable == 0x8391) || (currSyllable == 0x8392) ||
                    (currSyllable == 0x8393) || (currSyllable == 0x8340) || (currSyllable == 0x8342) ||
                    (currSyllable == 0x8344) || (currSyllable == 0x8346) || (currSyllable == 0x8348) ||
                    (currSyllable == 0x8383) || (currSyllable == 0x8385) || (currSyllable == 0x8387) ||
                    (currSyllable == 0x8362) || (currSyllable == 0x838E))) {
            errorCode = CONT_ERR_VOICE_WORD;
        }

        if (errorCode != 0) {
            return errorCode;
        }

        prevSyllable = currSyllable;
    }

    if ((currSyllable == 0x82C1) || (currSyllable == 0x8362)) {
        errorCode = CONT_ERR_VOICE_WORD;
    }

    return errorCode;
}
