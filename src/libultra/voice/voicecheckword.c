/**
 * File: voicecheckwork.c
 *
 * Checks whether or not a word can be registered in the dictionary
 */
#include "PR/controller.h"

s32 osVoiceCheckWord(u8* word) {
    s32 i;
    s32 errorCode = 0;
    u16 curSyllable;
    u16 prevSyllable = '\0';

    for (i = 0; word[i] != 0; i += 2) {
        curSyllable = (word[i] << 8) + word[i + 1];
        if (((curSyllable != 'ー') && (curSyllable < 'ぁ')) || ((curSyllable > 'ん') && (curSyllable < 'ァ')) ||
            (curSyllable == 0x837F) || (curSyllable > 'ヶ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if ((i == 0) && ((curSyllable == 'ー') || (curSyllable == 'ん') || (curSyllable == 'っ') ||
                                (curSyllable == 'ゎ') || (curSyllable == 'ン') || (curSyllable == 'ッ') ||
                                (curSyllable == 'ヮ') || (curSyllable == 'ヵ') || (curSyllable == 'ヶ'))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ぁ') || (curSyllable == 'ァ')) && (prevSyllable != 'ふ') &&
                   (prevSyllable != 'フ') && (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ぃ') || (curSyllable == 'ィ')) && (prevSyllable != 'う') &&
                   (prevSyllable != 'て') && (prevSyllable != 'で') && (prevSyllable != 'ふ') &&
                   (prevSyllable != 'ウ') && (prevSyllable != 'テ') && (prevSyllable != 'デ') &&
                   (prevSyllable != 'フ') && (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ぅ') || (curSyllable == 'ゥ')) && (prevSyllable != 'と') &&
                   (prevSyllable != 'ど') && (prevSyllable != 'ふ') && (prevSyllable != 'ト') &&
                   (prevSyllable != 'ド') && (prevSyllable != 'フ') && (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ぇ') || (curSyllable == 'ェ')) && (prevSyllable != 'う') &&
                   (prevSyllable != 'し') && (prevSyllable != 'じ') && (prevSyllable != 'ち') &&
                   (prevSyllable != 'ぢ') && (prevSyllable != 'つ') && (prevSyllable != 'ふ') &&
                   (prevSyllable != 'ウ') && (prevSyllable != 'シ') && (prevSyllable != 'ジ') &&
                   (prevSyllable != 'チ') && (prevSyllable != 'ヂ') && (prevSyllable != 'ツ') &&
                   (prevSyllable != 'フ') && (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ぉ') || (curSyllable == 'ォ')) && (prevSyllable != 'う') &&
                   (prevSyllable != 'ふ') && (prevSyllable != 'ウ') && (prevSyllable != 'フ') &&
                   (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ゃ') || (curSyllable == 'ゅ') || (curSyllable == 'ょ') || (curSyllable == 'ャ') ||
                    (curSyllable == 'ュ') || (curSyllable == 'ョ')) &&
                   (prevSyllable != 'き') && (prevSyllable != 'し') && (prevSyllable != 'ち') &&
                   (prevSyllable != 'に') && (prevSyllable != 'ひ') && (prevSyllable != 'み') &&
                   (prevSyllable != 'り') && (prevSyllable != 'ぎ') && (prevSyllable != 'じ') &&
                   (prevSyllable != 'ぢ') && (prevSyllable != 'び') && (prevSyllable != 'ぴ') &&
                   (prevSyllable != 'キ') && (prevSyllable != 'シ') && (prevSyllable != 'チ') &&
                   (prevSyllable != 'ニ') && (prevSyllable != 'ヒ') && (prevSyllable != 'ミ') &&
                   (prevSyllable != 'リ') && (prevSyllable != 'ギ') && (prevSyllable != 'ジ') &&
                   (prevSyllable != 'ヂ') && (prevSyllable != 'ビ') && (prevSyllable != 'ピ') &&
                   (prevSyllable != 'ヴ')) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if ((curSyllable == 'ー') && ((prevSyllable == 'ん') || (prevSyllable == 'っ') ||
                                             (prevSyllable == 'ン') || (prevSyllable == 'ッ'))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((curSyllable == 'ん') || (curSyllable == 'ン')) &&
                   ((prevSyllable == 'ん') || (prevSyllable == 'ン'))) {
            errorCode = CONT_ERR_VOICE_WORD;
        } else if (((prevSyllable == 'っ') || (prevSyllable == 'ッ')) &&
                   ((curSyllable == 'ー') || (curSyllable == 'あ') || (curSyllable == 'い') || (curSyllable == 'う') ||
                    (curSyllable == 'え') || (curSyllable == 'お') || (curSyllable == 'な') || (curSyllable == 'に') ||
                    (curSyllable == 'ぬ') || (curSyllable == 'ね') || (curSyllable == 'の') || (curSyllable == 'ま') ||
                    (curSyllable == 'み') || (curSyllable == 'む') || (curSyllable == 'め') || (curSyllable == 'も') ||
                    (curSyllable == 'や') || (curSyllable == 'ゆ') || (curSyllable == 'よ') || (curSyllable == 'ら') ||
                    (curSyllable == 'り') || (curSyllable == 'る') || (curSyllable == 'れ') || (curSyllable == 'ろ') ||
                    (curSyllable == 'わ') || (curSyllable == 'ゐ') || (curSyllable == 'ゑ') || (curSyllable == 'を') ||
                    (curSyllable == 'ん') || (curSyllable == 'ぁ') || (curSyllable == 'ぃ') || (curSyllable == 'ぅ') ||
                    (curSyllable == 'ぇ') || (curSyllable == 'ぉ') || (curSyllable == 'ゃ') || (curSyllable == 'ゅ') ||
                    (curSyllable == 'ょ') || (curSyllable == 'っ') || (curSyllable == 'ゎ') || (curSyllable == 'ア') ||
                    (curSyllable == 'イ') || (curSyllable == 'ウ') || (curSyllable == 'エ') || (curSyllable == 'オ') ||
                    (curSyllable == 'ナ') || (curSyllable == 'ニ') || (curSyllable == 'ヌ') || (curSyllable == 'ネ') ||
                    (curSyllable == 'ノ') || (curSyllable == 'マ') || (curSyllable == 'ミ') || (curSyllable == 'ム') ||
                    (curSyllable == 'メ') || (curSyllable == 'モ') || (curSyllable == 'ヤ') || (curSyllable == 'ユ') ||
                    (curSyllable == 'ヨ') || (curSyllable == 'ラ') || (curSyllable == 'リ') || (curSyllable == 'ル') ||
                    (curSyllable == 'レ') || (curSyllable == 'ロ') || (curSyllable == 'ワ') || (curSyllable == 'ヰ') ||
                    (curSyllable == 'ヱ') || (curSyllable == 'ヲ') || (curSyllable == 'ン') || (curSyllable == 'ァ') ||
                    (curSyllable == 'ィ') || (curSyllable == 'ゥ') || (curSyllable == 'ェ') || (curSyllable == 'ォ') ||
                    (curSyllable == 'ャ') || (curSyllable == 'ュ') || (curSyllable == 'ョ') || (curSyllable == 'ッ') ||
                    (curSyllable == 'ヮ'))) {
            errorCode = CONT_ERR_VOICE_WORD;
        }

        if (errorCode != 0) {
            return errorCode;
        }

        prevSyllable = curSyllable;
    }

    if ((curSyllable == 'っ') || (curSyllable == 'ッ')) {
        errorCode = CONT_ERR_VOICE_WORD;
    }

    return errorCode;
}
