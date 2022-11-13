#include "global.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#if 0

//fontWidth
extern f32 D_801D0470[159];

//rupeesTextLocalization
u8 D_801D06F0[4][8] = { { "rupee(s)" }, //EN
                        { "rubin(e)" }, //DE
                        { "rubis"    }, //FR
                        { "rupia(s)" }  //SPA 
                        };

// rupeesTextLength
u8 D_801D0710[4] = {8,8,5,8};

// sOwlWarpText
char D_801D0714[OWL_WARP_MAX][16] = {
    "Great Bay Coast",  // OWL_WARP_GREAT_BAY_COAST
    "Zora Cape",        // OWL_WARP_ZORA_CAPE
    "Snowhead",         // OWL_WARP_SNOWHEAD
    "Mountain Village", // OWL_WARP_MOUNTAIN_VILLAGE
    "Clock Town",       // OWL_WARP_CLOCK_TOWN
    "Milk Road",        // OWL_WARP_MILK_ROAD
    "Woodfall",         // OWL_WARP_WOODFALL
    "Southern Swamp",   // OWL_WARP_SOUTHERN_SWAMP
    "Ikana Canyon",     // OWL_WARP_IKANA_CANYON
    "Stone Tower",      // OWL_WARP_STONE_TOWER
    "Entrance",         // OWL_WARP_ENTRANCE
};

// sOwlWarpTextLength
s16 D_801D07C4[OWL_WARP_MAX] = {
    15, // OWL_WARP_GREAT_BAY_COAST
    9,  // OWL_WARP_ZORA_CAPE
    8,  // OWL_WARP_SNOWHEAD
    16, // OWL_WARP_MOUNTAIN_VILLAGE
    10, // OWL_WARP_CLOCK_TOWN
    9,  // OWL_WARP_MILK_ROAD
    8,  // OWL_WARP_WOODFALL
    14, // OWL_WARP_SOUTHERN_SWAMP
    12, // OWL_WARP_IKANA_CANYON
    11, // OWL_WARP_STONE_TOWER
    8,  // OWL_WARP_ENTRANCE
};

#endif

extern f32 D_801D0470[159];
extern u8 D_801D06F0[4][8];
extern u8 D_801D0710[4];
extern u8 D_801D0714[OWL_WARP_MAX][16];
extern s16 D_801D07C4[OWL_WARP_MAX];

void Message_FindMessageNES(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->messageEntryTableNes;
    const char* segment = msgEntry->segment;
    const char* foundSegment;
    const char* nextSegment;

    while (msgEntry->textId != 0xFFFF) {
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd = nextSegment - foundSegment;
            return;
        }
        msgEntry++;
    }

    msgEntry = msgCtx->messageEntryTableNes;
    foundSegment = msgEntry->segment;
    msgEntry++;
    nextSegment = msgEntry->segment;
    font->messageStart = foundSegment - segment;
    font->messageEnd = nextSegment - foundSegment;
}

void Message_LoadCharNES(PlayState* play, u8 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    Font_LoadCharNES(play, codePointIndex, temp1);
    msgCtx->decodedBuffer.schar[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->unk12098);
    *offset = temp1;
    *arg3 = temp2;
}

void Message_LoadPluralRupeesNES(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;

    msgCtx->decodedBuffer.schar[p] = 0x20;
    p++;
    Font_LoadCharNES(play, 'R', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'R';
    p++;
    Font_LoadCharNES(play, 'u', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'u';
    p++;
    Font_LoadCharNES(play, 'p', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'p';
    p++;
    Font_LoadCharNES(play, 'e', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'e';
    p++;
    Font_LoadCharNES(play, 'e', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'e';
    p++;
    Font_LoadCharNES(play, 's', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 's';

    f += 16.0f * msgCtx->unk12098 * 6.0f;
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadLocalizedRupeesNES(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u8 j;

    msgCtx->decodedBuffer.schar[p] = ' ';
    p++;

    for (j = 0; j < D_801D0710[gSaveContext.options.language - 1]; j++) {
        Font_LoadCharNES(play, D_801D06F0[gSaveContext.options.language - 1][j], o);
        msgCtx->decodedBuffer.schar[p] = D_801D06F0[gSaveContext.options.language - 1][j];
        o += FONT_CHAR_TEX_SIZE;
        p++;
    }

    p--;
    f += 16.0f * msgCtx->unk12098 * (D_801D0710[gSaveContext.options.language - 1] + 1);
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadRupeesNES(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3, s16 singular) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;

    msgCtx->decodedBuffer.schar[p] = ' ';
    p++;
    Font_LoadCharNES(play, 'R', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'R';
    p++;
    Font_LoadCharNES(play, 'u', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'u';
    p++;
    Font_LoadCharNES(play, 'p', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'p';
    p++;
    Font_LoadCharNES(play, 'e', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'e';
    p++;
    Font_LoadCharNES(play, 'e', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 'e';

    if (singular != 1) {
        p++;
        Font_LoadCharNES(play, 's', o);
        o += FONT_CHAR_TEX_SIZE;
        msgCtx->decodedBuffer.schar[p] = 's';
        f += 16.0f * msgCtx->unk12098 * 6.0f;
    } else {
        f += 16.0f * msgCtx->unk12098 * 5.0f;
    }

    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadTimeNES(PlayState* play, u8 arg1, s32* offset, f32* arg3, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u32 timeLeft;
    s16 digits[4];
    f32 timeLeftInMinutes;
    s16 i;

    if (arg1 == 0xCF) {
        // Calculates the time left before the moon crashes.
        timeLeft = TIME_UNTIL_MOON_CRASH;
    } else {
        // Calculates the time left before a new day.
        timeLeft = TIME_UNTIL_NEW_DAY;
    }

    timeLeftInMinutes = TIME_TO_MINUTES_F(timeLeft);

    digits[0] = 0;
    digits[1] = (timeLeftInMinutes / 60.0f);
    while (digits[1] >= 10) {
        digits[0]++;
        digits[1] -= 10;
    }

    digits[2] = 0;
    digits[3] = (s32)timeLeftInMinutes % 60;
    while (digits[3] >= 10) {
        digits[2]++;
        digits[3] -= 10;
    }

    for (i = 0; i < 4; i++) {
        Font_LoadCharNES(play, digits[i] + '0', o);
        o += FONT_CHAR_TEX_SIZE;
        msgCtx->decodedBuffer.schar[p] = digits[i] + '0';
        p++;
        if (i == 1) {
            Font_LoadCharNES(play, ':', o);
            o += FONT_CHAR_TEX_SIZE;
            msgCtx->decodedBuffer.schar[p] = ':';
            p++;
        }
    }

    f += 5.0f * (16.0f * msgCtx->unk12098);
    *decodedBufPos = p - 1;
    *offset = o;
    *arg3 = f;
}

void Message_LoadOwlWarpTextNES(PlayState* play, s32* offset, f32* arg2, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg2;
    s16 i;
    u8 currentChar;
    s16 owlWarpId;
    s16 stringLimit;

    if (func_8010A0A4(play) || (play->sceneId == SCENE_SECOM)) {
        owlWarpId = OWL_WARP_ENTRANCE;
    } else {
        owlWarpId = play->pauseCtx.cursorPoint[PAUSE_WORLD_MAP];
    }
    stringLimit = D_801D07C4[owlWarpId];

    for (i = 0; i < stringLimit; i++) {
        msgCtx->decodedBuffer.schar[p] = D_801D0714[owlWarpId][i];
        currentChar = msgCtx->decodedBuffer.schar[p];
        if (currentChar != ' ') {
            Font_LoadCharNES(play, D_801D0714[owlWarpId][i], o);
            o += FONT_CHAR_TEX_SIZE;
        }
        currentChar = msgCtx->decodedBuffer.schar[p];
        p++;
        f += (D_801D0470[currentChar - ' '] * msgCtx->unk12098);
    }

    p--;
    f += (stringLimit - 1) * (16.0f * msgCtx->unk12098);
    *decodedBufPos = p;
    *offset = o;
    *arg2 = f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_80159438.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_8015966C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/func_8015B198.s")
