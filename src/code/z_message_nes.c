#include "global.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

f32 sNESFontWidths[160] = {
    8.0f,  8.0f,  6.0f,  9.0f,  9.0f,  14.0f, 12.0f, 3.0f,  7.0f,  7.0f,  7.0f,  9.0f,  4.0f,  6.0f,  4.0f,  9.0f,
    10.0f, 5.0f,  9.0f,  9.0f,  10.0f, 9.0f,  9.0f,  9.0f,  9.0f,  9.0f,  6.0f,  6.0f,  9.0f,  11.0f, 9.0f,  11.0f,
    13.0f, 12.0f, 9.0f,  11.0f, 11.0f, 8.0f,  8.0f,  12.0f, 10.0f, 4.0f,  8.0f,  10.0f, 8.0f,  13.0f, 11.0f, 13.0f,
    9.0f,  13.0f, 10.0f, 10.0f, 9.0f,  10.0f, 11.0f, 15.0f, 11.0f, 10.0f, 10.0f, 7.0f,  10.0f, 7.0f,  10.0f, 9.0f,
    5.0f,  8.0f,  9.0f,  8.0f,  9.0f,  9.0f,  6.0f,  9.0f,  8.0f,  4.0f,  6.0f,  8.0f,  4.0f,  12.0f, 9.0f,  9.0f,
    9.0f,  9.0f,  7.0f,  8.0f,  7.0f,  8.0f,  9.0f,  12.0f, 8.0f,  9.0f,  8.0f,  7.0f,  5.0f,  7.0f,  10.0f, 6.0f,
    12.0f, 12.0f, 12.0f, 12.0f, 11.0f, 8.0f,  8.0f,  8.0f,  8.0f,  6.0f,  6.0f,  6.0f,  6.0f,  10.0f, 13.0f, 13.0f,
    13.0f, 13.0f, 10.0f, 10.0f, 10.0f, 10.0f, 9.0f,  8.0f,  8.0f,  8.0f,  8.0f,  8.0f,  9.0f,  9.0f,  9.0f,  9.0f,
    4.0f,  4.0f,  4.0f,  4.0f,  8.0f,  9.0f,  9.0f,  9.0f,  9.0f,  8.0f,  8.0f,  8.0f,  8.0f,  8.0f,  11.0f, 6.0f,
    14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f,
};

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
    temp2 += (16.0f * msgCtx->textCharScale);
    *offset = temp1;
    *arg3 = temp2;
}

void Message_LoadPluralRupeesNES(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
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
    p++;
    Font_LoadCharNES(play, 's', o);
    o += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.schar[p] = 's';

    f += 16.0f * msgCtx->textCharScale * 6.0f;
    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

#define RUPEES_STR_EN "Rupee(s)"
#define RUPEES_STR_DE "Rubin(e)"
#define RUPEES_STR_FR "Rubis"
#define RUPEES_STR_SPA "Rupia(s)"

char sRupeesTextLocalization[LANGUAGE_MAX - 1][8] = {
    RUPEES_STR_EN,  // EN
    RUPEES_STR_DE,  // DE
    RUPEES_STR_FR,  // FR
    RUPEES_STR_SPA, // SPA
};

u8 sRupeesTextLength[LANGUAGE_MAX - 1] = {
    sizeof(RUPEES_STR_EN) - 1,
    sizeof(RUPEES_STR_DE) - 1,
    sizeof(RUPEES_STR_FR) - 1,
    sizeof(RUPEES_STR_SPA) - 1,
};

void Message_LoadLocalizedRupeesNES(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u8 j;

    msgCtx->decodedBuffer.schar[p] = ' ';
    p++;

    for (j = 0; j < sRupeesTextLength[gSaveContext.options.language - 1]; j++) {
        Font_LoadCharNES(play, sRupeesTextLocalization[gSaveContext.options.language - 1][j], o);
        msgCtx->decodedBuffer.schar[p] = sRupeesTextLocalization[gSaveContext.options.language - 1][j];
        o += FONT_CHAR_TEX_SIZE;
        p++;
    }

    p--;
    f += 16.0f * msgCtx->textCharScale * (sRupeesTextLength[gSaveContext.options.language - 1] + 1);
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
        f += 16.0f * msgCtx->textCharScale * 6.0f;
    } else {
        f += 16.0f * msgCtx->textCharScale * 5.0f;
    }

    *decodedBufPos = p;
    *offset = o;
    *arg3 = f;
}

void Message_LoadTimeNES(PlayState* play, u8 curChar, s32* offset, f32* arg3, s16* decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 p = *decodedBufPos;
    s32 o = *offset;
    f32 f = *arg3;
    u32 timeLeft;
    s16 digits[4];
    f32 timeLeftInMinutes;
    s16 i;

    if (curChar == 0xCF) {
        timeLeft = TIME_UNTIL_MOON_CRASH;
    } else {
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

    f += 5.0f * (16.0f * msgCtx->textCharScale);
    *decodedBufPos = p - 1;
    *offset = o;
    *arg3 = f;
}

#define GREAT_BAY_COAST_STR "Great Bay Coast"
#define ZORA_CAPE_STR "Zora Cape"
#define SNOWHEAD_STR "Snowhead"
#define MOUNTAIN_VILLAGE_STR "Mountain Village"
#define CLOCK_TOWN_STR "Clock Town"
#define MILK_ROAD_STR "Milk Road"
#define WOODFALL_STR "Woodfall"
#define SOUTHERN_SWAMP_STR "Southern Swamp"
#define IKANA_CANYON_STR "Ikana Canyon"
#define STONE_TOWER_STR "Stone Tower"
#define ENTRANCE_STR "Entrance"

char sOwlWarpTextENG[OWL_WARP_MAX][16] = {
    GREAT_BAY_COAST_STR,  // OWL_WARP_GREAT_BAY_COAST
    ZORA_CAPE_STR,        // OWL_WARP_ZORA_CAPE
    SNOWHEAD_STR,         // OWL_WARP_SNOWHEAD
    MOUNTAIN_VILLAGE_STR, // OWL_WARP_MOUNTAIN_VILLAGE
    CLOCK_TOWN_STR,       // OWL_WARP_CLOCK_TOWN
    MILK_ROAD_STR,        // OWL_WARP_MILK_ROAD
    WOODFALL_STR,         // OWL_WARP_WOODFALL
    SOUTHERN_SWAMP_STR,   // OWL_WARP_SOUTHERN_SWAMP
    IKANA_CANYON_STR,     // OWL_WARP_IKANA_CANYON
    STONE_TOWER_STR,      // OWL_WARP_STONE_TOWER
    ENTRANCE_STR,         // OWL_WARP_ENTRANCE
};

s16 sOwlWarpTextLengthENG[OWL_WARP_MAX] = {
    sizeof(GREAT_BAY_COAST_STR) - 1,  // OWL_WARP_GREAT_BAY_COAST
    sizeof(ZORA_CAPE_STR) - 1,        // OWL_WARP_ZORA_CAPE
    sizeof(SNOWHEAD_STR) - 1,         // OWL_WARP_SNOWHEAD
    sizeof(MOUNTAIN_VILLAGE_STR) - 1, // OWL_WARP_MOUNTAIN_VILLAGE
    sizeof(CLOCK_TOWN_STR) - 1,       // OWL_WARP_CLOCK_TOWN
    sizeof(MILK_ROAD_STR) - 1,        // OWL_WARP_MILK_ROAD
    sizeof(WOODFALL_STR) - 1,         // OWL_WARP_WOODFALL
    sizeof(SOUTHERN_SWAMP_STR) - 1,   // OWL_WARP_SOUTHERN_SWAMP
    sizeof(IKANA_CANYON_STR) - 1,     // OWL_WARP_IKANA_CANYON
    sizeof(STONE_TOWER_STR) - 1,      // OWL_WARP_STONE_TOWER
    sizeof(ENTRANCE_STR) - 1,         // OWL_WARP_ENTRANCE
};

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
    stringLimit = sOwlWarpTextLengthENG[owlWarpId];

    for (i = 0; i < stringLimit; i++) {
        msgCtx->decodedBuffer.schar[p] = sOwlWarpTextENG[owlWarpId][i];
        currentChar = msgCtx->decodedBuffer.schar[p];
        if (currentChar != ' ') {
            Font_LoadCharNES(play, sOwlWarpTextENG[owlWarpId][i], o);
            o += FONT_CHAR_TEX_SIZE;
        }
        currentChar = msgCtx->decodedBuffer.schar[p];
        p++;
        f += (sNESFontWidths[currentChar - ' '] * msgCtx->textCharScale);
    }

    p--;
    f += (stringLimit - 1) * (16.0f * msgCtx->textCharScale);
    *decodedBufPos = p;
    *offset = o;
    *arg2 = f;
}

void Message_GetTimerDigitsNES(OSTime time, s16* digits) {
    OSTime t = time;

    // 6 minutes
    digits[0] = t / SECONDS_TO_TIMER(360);
    t -= (digits[0] * SECONDS_TO_TIMER(360));

    // minutes
    digits[1] = t / SECONDS_TO_TIMER(60);
    t -= (digits[1] * SECONDS_TO_TIMER(60));

    digits[2] = '\'';

    // 10 seconds
    digits[3] = t / SECONDS_TO_TIMER(10);
    t -= digits[3] * SECONDS_TO_TIMER(10);

    // seconds
    digits[4] = t / SECONDS_TO_TIMER(1);
    t -= digits[4] * SECONDS_TO_TIMER(1);

    digits[5] = '"';

    // 100 milliseconds
    digits[6] = t / SECONDS_TO_TIMER_PRECISE(0, 10);
    t -= digits[6] * SECONDS_TO_TIMER_PRECISE(0, 10);

    // 10 milliseconds
    digits[7] = t;

    digits[0] += '0';
    digits[1] += '0';
    digits[3] += '0';
    digits[4] += '0';
    digits[6] += '0';
    digits[7] += '0';
}

Color_RGB16 D_801D07DC[] = {
    { 255, 120, 0 },  { 70, 255, 80 },   { 80, 110, 255 },  { 255, 255, 30 },
    { 90, 180, 255 }, { 210, 100, 255 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Color_RGB16 D_801D080C[] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Color_RGB16 D_801D083C[] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 180, 180, 200 }, { 255, 130, 30 },
};

Color_RGB16 D_801D086C[] = {
    { 195, 0, 0 },    { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Color_RGB16 D_801D089C[] = {
    { 255, 60, 60 },  { 110, 170, 255 }, { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

u8 D_801D08CC[] = {
    0x02, 0x01, 0x03, 0x06, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x01, 0x06,
};

void Message_DrawTextNES(PlayState* play, Gfx** gfxP, u16 textDrawPos) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 i;
    u16 j;
    Font* font = &msgCtx->font;
    u16 charTexIndex;
    u16 stateTimerHi;
    Gfx* gfx = *gfxP;
    u16 character;
    s16 sp130;
    s16 sp12E;
    s16 sp12C;
    s16 sp12A;

    msgCtx->textPosX = msgCtx->unk11F1A[0] + msgCtx->unk11FF8;
    msgCtx->textPosY = msgCtx->unk11FFA;

    sp130 = 0;
    if (!msgCtx->textIsCredits) {
        msgCtx->textPosY = msgCtx->unk11FFA;
    } else {
        msgCtx->textPosY = 48;
    }

    if (msgCtx->itemId != 0xFE) {
        Message_DrawItemIcon(play, &gfx);
    }

    msgCtx->textColorR = msgCtx->unk120C8;
    msgCtx->textColorG = msgCtx->unk120CA;
    msgCtx->textColorB = msgCtx->unk120CC;

    charTexIndex = 0;

    for (i = textDrawPos; i < msgCtx->textDrawPos; i++) {
        character = msgCtx->decodedBuffer.schar[i];

        switch (character) {
            case 0x0:
                if (play->pauseCtx.bombersNotebookOpen || (msgCtx->textBoxType == TEXTBOX_TYPE_D)) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else if (msgCtx->textBoxType == TEXTBOX_TYPE_5) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 255;
                }

                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                break;

            case 0x1:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x5:
            case 0x6:
            case 0x7:
            case 0x8:
                if ((msgCtx->msgMode >= MSGMODE_NEW_CYCLE_0) && (msgCtx->msgMode <= MSGMODE_OWL_SAVE_2) &&
                    (character == 0x2)) {
                    msgCtx->textDrawPos = msgCtx->decodedTextLen;
                    if (msgCtx->unk120D6) {
                        msgCtx->unk120D4 += 25;
                        if (msgCtx->unk120D4 >= 100) {
                            msgCtx->unk120D6 = false;
                        }
                    } else {
                        msgCtx->unk120D4 -= 25;
                        if (msgCtx->unk120D4 <= -100) {
                            msgCtx->unk120D6 = true;
                        }
                    }

                    if (D_801D07DC[(s16)(character - 1)].r + msgCtx->unk120D4 < 0) {
                        msgCtx->textColorR = 0;
                    } else {
                        msgCtx->textColorR = D_801D07DC[(s16)(character - 1)].r + msgCtx->unk120D4;
                    }

                    if (D_801D07DC[(s16)(character - 1)].g + msgCtx->unk120D4 >= 255) {
                        msgCtx->textColorG = D_801D07DC[(s16)(character - 1)].g;
                    } else {
                        msgCtx->textColorG = D_801D07DC[(s16)(character - 1)].g + msgCtx->unk120D4;
                    }

                    if (D_801D07DC[(s16)(character - 1)].b + msgCtx->unk120D4 < 0) {
                        msgCtx->textColorB = 0;
                    } else {
                        msgCtx->textColorB = D_801D07DC[(s16)(character - 1)].b + msgCtx->unk120D4;
                    }

                } else if (play->pauseCtx.bombersNotebookOpen) {
                    msgCtx->textColorR = D_801D089C[(s16)(character - 1)].r;
                    msgCtx->textColorG = D_801D089C[(s16)(character - 1)].g;
                    msgCtx->textColorB = D_801D089C[(s16)(character - 1)].b;
                } else if (msgCtx->textBoxType == TEXTBOX_TYPE_1) {
                    msgCtx->textColorR = D_801D07DC[(s16)(character - 1)].r;
                    msgCtx->textColorG = D_801D07DC[(s16)(character - 1)].g;
                    msgCtx->textColorB = D_801D07DC[(s16)(character - 1)].b;
                } else if (msgCtx->textBoxType == TEXTBOX_TYPE_D) {
                    msgCtx->textColorR = D_801D086C[(s16)(character - 1)].r;
                    msgCtx->textColorG = D_801D086C[(s16)(character - 1)].g;
                    msgCtx->textColorB = D_801D086C[(s16)(character - 1)].b;
                } else {
                    msgCtx->textColorR = D_801D080C[(s16)(character - 1)].r;
                    msgCtx->textColorG = D_801D080C[(s16)(character - 1)].g;
                    msgCtx->textColorB = D_801D080C[(s16)(character - 1)].b;
                }

                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos++;
                }
                break;

            case 0x20: // ` `
                msgCtx->textPosX += 6;
                break;

            case 0x11:
                msgCtx->textPosY += msgCtx->unk11FFC;
                // fallthrough
            case 0x13:
                sp130++;

                msgCtx->textPosX = msgCtx->unk11F1A[sp130] + msgCtx->unk11FF8;
                if (msgCtx->choiceNum == 1) {
                    if (!play->pauseCtx.bombersNotebookOpen) {
                        msgCtx->textPosX += 16;
                    } else {
                        msgCtx->textPosX += 50;
                    }
                } else if (msgCtx->choiceNum == 2) {
                    if (msgCtx->unk120D8 != 3) {
                        if (!play->pauseCtx.bombersNotebookOpen) {
                            msgCtx->textPosX += 10;
                        } else {
                            msgCtx->textPosX += 57;
                        }
                    } else if (sp130 >= 2) {
                        if (!play->pauseCtx.bombersNotebookOpen) {
                            msgCtx->textPosX += 10;
                        } else {
                            msgCtx->textPosX += 57;
                        }
                    }
                }
                continue;

            case 0x10:
            case 0x12:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    if (!msgCtx->textboxSkipped) {
                        Audio_PlaySfx(NA_SE_NONE);
                        msgCtx->msgMode = MSGMODE_TEXT_AWAIT_NEXT;
                        Font_LoadMessageBoxEndIcon(font, 0);
                    } else {
                        msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
                        msgCtx->textUnskippable = false;
                        msgCtx->msgBufPos++;
                    }
                    msgCtx->unk120CE = msgCtx->textColorR;
                    msgCtx->unk120D0 = msgCtx->textColorG;
                    msgCtx->unk120D2 = msgCtx->textColorB;
                }
                *gfxP = gfx;
                return;

            case 0x17: // MESSAGE_QUICKTEXT_ENABLE
                if ((i + 1) == msgCtx->textDrawPos) {
                    if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) ||
                        ((msgCtx->msgMode >= MSGMODE_OCARINA_STARTING) && (msgCtx->msgMode <= MSGMODE_26))) {
                        j = i;
                        while (true) {
                            if ((msgCtx->decodedBuffer.schar[j] != 0x18) && (msgCtx->decodedBuffer.schar[j] != 0x1A) &&
                                (msgCtx->decodedBuffer.schar[j] != 0x19) && (msgCtx->decodedBuffer.schar[j] != 0xE0) &&
                                (msgCtx->decodedBuffer.schar[j] != 0x10) && (msgCtx->decodedBuffer.schar[j] != 0x12)) {
                                j++;
                                continue;
                            }
                            break;
                        }
                        i = j - 1;
                        msgCtx->textDrawPos = i + 1;
                    }
                }
                break;

            case 0x18: // MESSAGE_QUICKTEXT_DISABLE
                break;

            case 0x1B: // MESSAGE_BOX_BREAK_DELAYED
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    stateTimerHi = msgCtx->decodedBuffer.schar[++i] << 8;
                    stateTimerHi |= msgCtx->decodedBuffer.schar[++i];
                    msgCtx->stateTimer = stateTimerHi;
                    msgCtx->msgMode = MSGMODE_TEXT_DELAYED_BREAK;
                }
                *gfxP = gfx;
                return;

            case 0x1C:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    if (msgCtx->unk11F0C == 3) {
                        msgCtx->textboxEndType = 0x55;
                    } else {
                        msgCtx->textboxEndType = 0x50;
                    }
                    stateTimerHi = msgCtx->decodedBuffer.schar[++i] << 8;
                    stateTimerHi |= msgCtx->decodedBuffer.schar[++i];
                    msgCtx->stateTimer = stateTimerHi;
                    Font_LoadMessageBoxEndIcon(font, 1);
                    if (play->csCtx.state == CS_STATE_IDLE) {
                        func_8011552C(play, DO_ACTION_RETURN);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1D:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x52;
                    stateTimerHi = msgCtx->decodedBuffer.schar[++i] << 8;
                    stateTimerHi |= msgCtx->decodedBuffer.schar[++i];
                    msgCtx->stateTimer = stateTimerHi;
                    Font_LoadMessageBoxEndIcon(font, 1);
                    if (play->csCtx.state == CS_STATE_IDLE) {
                        func_8011552C(play, DO_ACTION_RETURN);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1E: // MESSAGE_SFX
                if (((i + 1) == msgCtx->textDrawPos) && (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING)) {
                    stateTimerHi = msgCtx->decodedBuffer.schar[i + 1] << 8;
                    stateTimerHi |= msgCtx->decodedBuffer.schar[i + 2];
                    Audio_PlaySfx(stateTimerHi);
                }
                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos += 2;
                }
                i += 2;
                break;

            case 0x1F:
                if (((i + 1) == msgCtx->textDrawPos) && (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING)) {
                    msgCtx->msgMode = MSGMODE_9;
                    stateTimerHi = msgCtx->decodedBuffer.schar[i + 1] << 8;
                    stateTimerHi |= msgCtx->decodedBuffer.schar[i + 2];
                    msgCtx->textDelayTimer = stateTimerHi;
                }
                i += 2;
                break;

            case 0xA:
                i++;
                character = msgCtx->decodedBuffer.schar[i];
                switch (character) {
                    case 0x0:
                    case 0x1:
                    case 0x2:
                    case 0x3:
                    case 0x4:
                    case 0x5:
                    case 0x6:
                        msgCtx->textDelay = character - 0x0;
                        if ((i + 1) == msgCtx->textDrawPos) {
                            msgCtx->textDrawPos++;
                        }
                        break;
                }
                break;

            case 0xC1: // MESSAGE_BACKGROUND
                msgCtx->textPosX = 0x2D;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Audio_PlaySfx(NA_SE_NONE);
                }

                gDPPipeSync(gfx++);
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0xC1) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);

                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0x60) << 2,
                                    (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, msgCtx->unk12012 << 2,
                                    (msgCtx->textPosX + 0xC0) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);

                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                                  PRIMITIVE, 0);

                msgCtx->textPosX += 32;
                break;

            case 0xC2:
                msgCtx->textboxEndType = 0x10;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(font, 2);
                    if (msgCtx->unk120D8 != 3) {
                        msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 0xE);
                        msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x1A);
                        msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x26);
                    }
                }
                break;

            case 0xC3:
                msgCtx->textboxEndType = 0x11;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(font, 2);
                    if (msgCtx->unk120D8 != 3) {
                        msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 0xE);
                        msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x1A);
                        msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x26);
                    }
                }
                break;

            case 0xCC:
                msgCtx->textboxEndType = 0x60;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(font, 1);
                }
                break;

            case 0xD0:
                msgCtx->textboxEndType = 0x61;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(font, 1);
                }
                break;

            case 0xD1:
                msgCtx->textboxEndType = 0x62;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(font, 1);
                }
                break;

            case 0xD2:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x41;
                    Font_LoadMessageBoxEndIcon(font, 0);
                    Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                }
                break;

            case 0xD5:
                msgCtx->textboxEndType = 0x63;

                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Font_LoadMessageBoxEndIcon(font, 1);
                }
                break;

            case 0x15:
            case 0xBF:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    if (msgCtx->textBoxType == TEXTBOX_TYPE_3) {
                        Message_HandleOcarina(play);
                        *gfxP = gfx;
                        return;
                    }

                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    if (msgCtx->textboxEndType == 0) {
                        Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                        if (character == 0xBF) {
                            Font_LoadMessageBoxEndIcon(font, 1);
                        } else {
                            Font_LoadMessageBoxEndIcon(font, 0);
                        }
                        if (play->csCtx.state == CS_STATE_IDLE) {
                            func_8011552C(play, DO_ACTION_RETURN);
                        }
                    } else {
                        Audio_PlaySfx(NA_SE_NONE);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1A:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Audio_PlaySfx(NA_SE_NONE);
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x30;
                }
                *gfxP = gfx;
                return;

            case 0x19:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x40;
                    Font_LoadMessageBoxEndIcon(font, 0);
                    Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            case 0xE0:
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = 0x42;
                    Font_LoadMessageBoxEndIcon(font, 1);
                    Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            default:
                switch (character) {
                    case 0x8169:
                    case 0x8175:
                        msgCtx->textPosX -= TRUNCF_BINANG(6.0f * msgCtx->textCharScale);
                        break;

                    case 0x8145:
                        msgCtx->textPosX -= TRUNCF_BINANG(3.0f * msgCtx->textCharScale);
                        break;

                    case 0x8148:
                    case 0x8149:
                        msgCtx->textPosX -= TRUNCF_BINANG(2.0f * msgCtx->textCharScale);
                        break;

                    default:
                        break;
                }
                if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) && ((i + 1) == msgCtx->textDrawPos)) {
                    Audio_PlaySfx(NA_SE_NONE);
                }
                if ((character >= 0xB0) && (character <= 0xBB)) {
                    sp12E = msgCtx->textColorR;
                    sp12C = msgCtx->textColorG;
                    sp12A = msgCtx->textColorB;
                    msgCtx->textColorR = D_801D083C[(s16)D_801D08CC[character - 0xB0]].r;
                    msgCtx->textColorG = D_801D083C[(s16)D_801D08CC[character - 0xB0]].g;
                    msgCtx->textColorB = D_801D083C[(s16)D_801D08CC[character - 0xB0]].b;
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                    msgCtx->textColorR = sp12E;
                    msgCtx->textColorG = sp12C;
                    msgCtx->textColorB = sp12A;
                } else if (msgCtx->msgMode >= MSGMODE_OWL_SAVE_0) {
                    if ((i < (msgCtx->decodedTextLen - 6)) || (i >= (msgCtx->decodedTextLen - 4))) {
                        Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                    }
                } else {
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                }
                charTexIndex += FONT_CHAR_TEX_SIZE;

                //! @TODO: u8 character but > 0x255 cases
                switch (character) {
                    case 0x8144:
                        msgCtx->textPosX += TRUNCF_BINANG(8.0f * msgCtx->textCharScale);
                        break;

                    case 0x816A:
                    case 0x8176:
                        msgCtx->textPosX += TRUNCF_BINANG(10.0f * msgCtx->textCharScale);
                        break;

                    case 0x8141:
                    case 0x8142:
                    case 0x8168:
                        msgCtx->textPosX += TRUNCF_BINANG(12.0f * msgCtx->textCharScale);
                        break;

                    case 0x8194:
                        msgCtx->textPosX += TRUNCF_BINANG(14.0f * msgCtx->textCharScale);
                        break;

                    case 0x8145:
                        msgCtx->textPosX += TRUNCF_BINANG(15.0f * msgCtx->textCharScale);
                        break;

                    default:
                        if (((msgCtx->textboxEndType == 0x62) && (i >= msgCtx->unk120C0) &&
                             ((msgCtx->unk120C0 + 4) >= i)) ||
                            ((msgCtx->textboxEndType == 0x63) && (i >= msgCtx->unk120C0) &&
                             ((msgCtx->unk120C0 + 2) >= i)) ||
                            ((msgCtx->textboxEndType == 0x60) && (i >= msgCtx->unk120C0) &&
                             ((msgCtx->unk120C0 + 2) >= i)) ||
                            ((msgCtx->textboxEndType == 0x61) && (i >= msgCtx->unk120C0) &&
                             ((msgCtx->unk120C0 + 1) >= i))) {
                            msgCtx->textPosX += (s32)(16.0f * msgCtx->textCharScale);
                        } else {
                            msgCtx->textPosX += (s32)(sNESFontWidths[character - ' '] * msgCtx->textCharScale);
                        }
                        break;
                }
                break;
        }
    }

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos = i + 1;
        msgCtx->textDelayTimer = 0;
        if (msgCtx->msgMode == MSGMODE_9) {
            msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
        }
    } else {
        msgCtx->textDelayTimer--;
    }

    *gfxP = gfx;
}

char D_801D08D8[][4] = {
    "Fast",
    "----",
    "Slow",
};

u8 D_801D08E4[] = {
    0x01,
    0x03,
    0x04,
    0x02,
};

#define RED_STR "RED"
#define BLUE_STR "BLUE"
#define YELLOW_STR "YELLOW"
#define GREEN_STR "GREEN"

char sMaskCodeTextENG[][6] = {
    RED_STR,
    BLUE_STR,
    YELLOW_STR,
    GREEN_STR,
};

u8 sMaskCodeTextLengthENG[] = {
    sizeof(RED_STR) - 1,
    sizeof(BLUE_STR) - 1,
    sizeof(YELLOW_STR) - 1,
    sizeof(GREEN_STR) - 1,
};

void Message_DecodeNES(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    Player* player = GET_PLAYER(play);
    s16 decodedBufPos = 0;
    s16 value;
    u32 timeToMoonCrash;
    s16 i;
    s16 numLines;
    s16 digits[4];
    s16 spC6 = 0;
    u16 sfxHi;
    f32 var_fs0;
    s32 charTexIndex = 0;
    s16 loadChar;
    s16 index;
    s16 spA8[8];
    f32 spA4;
    u8* fontBuf;
    s16 playerNameLen;
    s16 var_v1_3;
    u8 curChar;

    numLines = 0;
    msgCtx->textDelayTimer = 0;
    msgCtx->textDelay = msgCtx->textDelayTimer;
    msgCtx->textFade = false;
    spA4 = 0.0f;
    font->unk_11D88 = (font->unk_11D88 ^ 1) & 1;
    Message_SetupLoadItemIcon(play);

    while (true) {
        curChar = font->msgBuf.schar[msgCtx->msgBufPos];
        msgCtx->decodedBuffer.schar[decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos];

        if ((curChar == 0x10) || (curChar == 0x12) || (curChar == 0x1B) || (curChar == 0x1C) || (curChar == 0x1D) ||
            (curChar == 0x19) || (curChar == 0xE0) || (curChar == 0xBF) || (curChar == 0x15) || (curChar == 0x1A)) {
            msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
            msgCtx->textDrawPos = 1;
            if (msgCtx->textBoxType == TEXTBOX_TYPE_3) {
                msgCtx->unk11FFA = msgCtx->textboxY + 2;
            } else {
                msgCtx->unk11FFA = msgCtx->textboxY + 8;
            }
            msgCtx->unk11F1A[spC6] = 0;
            if (msgCtx->unk11F18 != 0) {
                msgCtx->unk11F1A[spC6] = TRUNCF_BINANG((msgCtx->textCharScale * 16.0f * 16.0f) - spA4) / 2;
            }

            spA4 = 0.0f;

            if (curChar == 0x12) {
                if ((msgCtx->textBoxType != TEXTBOX_TYPE_3) && (msgCtx->textBoxType != TEXTBOX_TYPE_4)) {
                    if (numLines < 2) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(10);
                    } else if (numLines == 2) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(11);
                    } else if (numLines == 3) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(12);
                    }
                }
            } else {
                if ((msgCtx->textBoxType != TEXTBOX_TYPE_3) && (msgCtx->textBoxType != TEXTBOX_TYPE_4)) {
                    if (numLines == 0) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(13) + XREG(10);
                    } else if (numLines == 1) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(13) + XREG(11);
                    } else if (numLines == 2) {
                        msgCtx->unk11FFA = msgCtx->textboxY + XREG(13) + XREG(12);
                    }
                }
            }

            {
                s8 requiredScopeTemp;

                if ((curChar == 0x1B) || (curChar == 0x1C) || (curChar == 0x1D)) {
                    //! FAKE: & 0xFFFF to fix regalloc
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[(msgCtx->msgBufPos & 0xFFFF) + 1];
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 2];
                    msgCtx->msgBufPos += 3;
                }
            }

            msgCtx->decodedTextLen = decodedBufPos;
            msgCtx->unk120D8 = numLines;
            if (msgCtx->textboxSkipped || (msgCtx->textBoxType == TEXTBOX_TYPE_1) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_3) || (msgCtx->textBoxType == TEXTBOX_TYPE_6) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_8) || (msgCtx->textBoxType == TEXTBOX_TYPE_9) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_B) || (msgCtx->unk11F0C == 3)) {
                msgCtx->textDrawPos = msgCtx->decodedTextLen;
            }
            msgCtx->unk120C8 = msgCtx->unk120CE;
            msgCtx->unk120CA = msgCtx->unk120D0;
            msgCtx->unk120CC = msgCtx->unk120D2;
            break;
        } else if (curChar == 0x16) {
            // Substitute the player name control character for the file's player name.
            for (playerNameLen = ARRAY_COUNT(gSaveContext.save.saveInfo.playerData.playerName); playerNameLen > 0;
                 playerNameLen--) {
                if (gSaveContext.save.saveInfo.playerData.playerName[playerNameLen - 1] != 0x3E) {
                    break;
                }
            }

            for (i = 0; i < playerNameLen; i++) {
                curChar = gSaveContext.save.saveInfo.playerData.playerName[i];
                if (curChar == 0x3E) {
                    curChar = ' ';
                } else if (curChar == 0x40) {
                    curChar = '.';
                } else if (curChar == 0x3F) {
                    curChar = '-';
                } else if (curChar < 0xA) {
                    curChar += 0;
                    curChar = '0' + curChar;
                } else if (curChar < 0x24) {
                    curChar += 0;
                    curChar = 'A' - 10 + curChar;
                } else if (curChar < 0x3E) {
                    curChar += 0;
                    curChar = 'a' - 36 + curChar;
                }
                if (curChar != ' ') {
                    Font_LoadCharNES(play, curChar, charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                }
                msgCtx->decodedBuffer.schar[decodedBufPos] = curChar;
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if (curChar == 0xC1) {
            DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1000, SEGMENT_ROM_START(message_texture_static), 0x900);
            DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1900, SEGMENT_ROM_START(message_texture_static) + 0x900,
                                0x900);
            numLines = 2;
            spC6 = 2;
            msgCtx->unk12012 = msgCtx->textboxY + 8;
            msgCtx->unk11F18 = 1;
            msgCtx->unk12010 = XREG(47);
        } else if (curChar == 0xC2) {
            msgCtx->unk11F18 = 0;
            msgCtx->choiceNum = 2;
        } else if (curChar == 0xC3) {
            msgCtx->unk11F18 = 0;
            msgCtx->choiceNum = 3;
            msgCtx->unk11FF8 += 0x16;
        } else if (curChar == 0xC4) {
            Message_GetTimerDigitsNES(((void)0, gSaveContext.timerCurTimes[curChar - 0xC4]), spA8);

            loadChar = false;
            for (i = 0; i < 5; i++) {
                if ((i == 1) || (spA8[i + 3] != '0')) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, spA8[i + 3], &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xC5) || (curChar == 0xC6) || (curChar == 0xC7) || (curChar == 0xC8) ||
                   (curChar == 0xC9)) {
            Message_GetTimerDigitsNES(((void)0, gSaveContext.timerCurTimes[curChar - 0xC4]), spA8);

            loadChar = false;
            for (i = 0; i < 8; i++) {
                if ((i == 4) || ((i != 2) && (i != 5) && (spA8[i] != '0'))) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, spA8[i], &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0xCA) {
            digits[0] = 0;
            digits[1] = TIME_TO_MINUTES_F(CURRENT_TIME) / 60.0f;
            while (digits[1] >= 10) {
                digits[0]++;
                digits[1] -= 10;
            }

            digits[2] = 0;
            digits[3] = (s32)TIME_TO_MINUTES_F(CURRENT_TIME) % 60;
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            for (i = 0; i < 4; i++) {
                Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                if (i == 1) {
                    Font_LoadCharNES(play, '"', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x22;
                    decodedBufPos++;
                } else if (i == 3) {
                    Font_LoadCharNES(play, 0x27, charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x27;
                }
            }
            spA4 += 6 * (16.0f * msgCtx->textCharScale);
        } else if (curChar == 0xCB) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = Flags_GetAllTreasure(play);

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0xCC) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 2;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIndex;
            digits[0] = digits[1] = digits[2] = 0;

            for (i = 0; i < 3; i++) {
                Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            Message_LoadLocalizedRupeesNES(play, &decodedBufPos, &charTexIndex, &spA4);
        } else if (curChar == 0xCD) {
            digits[0] = digits[1] = 0;
            digits[2] = msgCtx->bankRupeesSelected;

            while (digits[2] >= 100) {
                digits[0]++;
                digits[2] -= 100;
            }

            while (digits[2] >= 10) {
                digits[1]++;
                digits[2] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 3; i++) {
                if ((i == 2) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            Message_LoadRupeesNES(play, &decodedBufPos, &charTexIndex, &spA4, msgCtx->bankRupeesSelected);
        } else if (curChar == 0xCE) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = msgCtx->bankRupees;

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            Message_LoadRupeesNES(play, &decodedBufPos, &charTexIndex, &spA4, msgCtx->bankRupees);
        } else if (curChar == 0xCF) {
            Message_LoadTimeNES(play, curChar, &charTexIndex, &spA4, &decodedBufPos);
        } else if (curChar == 0xC) {
            digits[0] = digits[1] = 0;
            digits[2] = gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex];

            while (digits[2] >= 100) {
                digits[0]++;
                digits[2] -= 100;
            }
            while (digits[2] >= 10) {
                digits[1]++;
                digits[2] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 3; i++) {
                if ((i == 2) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }

            if ((gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 1) ||
                (gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 21)) {
                Message_LoadCharNES(play, 's', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 't', &charTexIndex, &spA4, decodedBufPos);
            } else if ((gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 2) ||
                       (gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 22)) {
                Message_LoadCharNES(play, 'n', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'd', &charTexIndex, &spA4, decodedBufPos);
            } else if ((gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 3) ||
                       (gSaveContext.save.saveInfo.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 23)) {
                Message_LoadCharNES(play, 'r', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'd', &charTexIndex, &spA4, decodedBufPos);
            } else {
                Message_LoadCharNES(play, 't', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'h', &charTexIndex, &spA4, decodedBufPos);
            }
        } else if (curChar == 0xD) {
            digits[0] = digits[1] = 0;
            digits[2] = Inventory_GetSkullTokenCount(play->sceneId);

            while (digits[2] >= 100) {
                digits[0]++;
                digits[2] -= 100;
            }
            while (digits[2] >= 10) {
                digits[1]++;
                digits[2] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 3; i++) {
                if ((i == 2) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }

            if ((Inventory_GetSkullTokenCount(play->sceneId) == 1) ||
                (Inventory_GetSkullTokenCount(play->sceneId) == 21)) {
                Message_LoadCharNES(play, 's', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 't', &charTexIndex, &spA4, decodedBufPos);
            } else if ((Inventory_GetSkullTokenCount(play->sceneId) == 2) ||
                       (Inventory_GetSkullTokenCount(play->sceneId) == 22)) {
                Message_LoadCharNES(play, 'n', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'd', &charTexIndex, &spA4, decodedBufPos);
            } else if ((Inventory_GetSkullTokenCount(play->sceneId) == 3) ||
                       (Inventory_GetSkullTokenCount(play->sceneId) == 23)) {
                Message_LoadCharNES(play, 'r', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'd', &charTexIndex, &spA4, decodedBufPos);
            } else {
                Message_LoadCharNES(play, 't', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
                Message_LoadCharNES(play, 'h', &charTexIndex, &spA4, decodedBufPos);
            }
        } else if (curChar == 0xE) {
            digits[0] = 0;
            digits[1] = gSaveContext.minigameScore;

            while (digits[1] >= 10) {
                digits[0]++;
                digits[1] -= 10;
            }

            for (i = 0; i < 2; i++) {
                if ((i == 1) || (digits[i] != 0)) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }

            decodedBufPos--;
        } else if (curChar == 0xF) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = gSaveContext.minigameScore;

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0xD0) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 0;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIndex;
            digits[0] = digits[1] = digits[2] = 0;
            for (i = 0; i < 2; i++) {
                Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            Message_LoadPluralRupeesNES(play, &decodedBufPos, &charTexIndex, &spA4);
        } else if (curChar == 0xD1) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 0;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIndex;

            for (i = 0; i < 5; i++) {
                msgCtx->unk12054[i] = 1;
                Message_LoadCharNES(play, '1', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if (curChar == 0xD3) {
            if (((void)0, gSaveContext.save.timeSpeedOffset) == 18) {
                index = 0;
            } else if (((void)0, gSaveContext.save.timeSpeedOffset) == 0) {
                index = 1;
            } else {
                index = 2;
            }

            for (i = 0; i < 4; i++, decodedBufPos++) {
                msgCtx->decodedBuffer.schar[decodedBufPos] = D_801D08D8[index][i];
                Font_LoadCharNES(play, D_801D08D8[index][i], charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
            }
            decodedBufPos--;
            spA4 += 3.0f * (16.0f * msgCtx->textCharScale);
            msgCtx->choiceIndex = index;
        } else if (curChar == 0xD4) {
            Message_LoadOwlWarpTextNES(play, &charTexIndex, &spA4, &decodedBufPos);
        } else if (curChar == 0xD5) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 0;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIndex;

            for (i = 0; i < 3; i++) {
                msgCtx->unk12054[i] = 1;
                Font_LoadCharNES(play, '1', charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = '1';
                spA4 += 16.0f * msgCtx->textCharScale;
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if (curChar == 0xD6) {
            for (i = 0; i < 6; i++) {
                msgCtx->decodedBuffer.schar[decodedBufPos] =
                    D_801D08E4[((void)0, gSaveContext.save.saveInfo.spiderHouseMaskOrder[i])];
                decodedBufPos++;
                Message_LoadCharNES(play, i + '1', &charTexIndex, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            msgCtx->decodedBuffer.schar[decodedBufPos] = 0;
        } else if ((curChar >= 0xD7) && (curChar < 0xDB)) {
            digits[0] = digits[1] = 0;
            digits[2] = STRAY_FAIRY_SCATTERED_TOTAL - gSaveContext.save.saveInfo.inventory.strayFairies[curChar - 0xD7];

            while (digits[2] >= 100) {
                digits[0]++;
                digits[2] -= 100;
            }
            while (digits[2] >= 10) {
                digits[1]++;
                digits[2] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 3; i++) {
                if ((i == 2) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
        } else if (curChar == 0xDB) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = gSaveContext.minigameScore;

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xDC) || (curChar == 0xDD)) {
            if (curChar == 0xDC) {
                digits[0] = gSaveContext.save.saveInfo.lotteryCodes[CURRENT_DAY - 1][0];
                digits[1] = gSaveContext.save.saveInfo.lotteryCodes[CURRENT_DAY - 1][1];
                digits[2] = gSaveContext.save.saveInfo.lotteryCodes[CURRENT_DAY - 1][2];
            } else {
                digits[0] = (HS_GET_LOTTERY_CODE_GUESS() & 0xF00) >> 8;
                digits[1] = (HS_GET_LOTTERY_CODE_GUESS() & 0xF0) >> 4;
                digits[2] = HS_GET_LOTTERY_CODE_GUESS() & 0xF;
            }

            for (i = 0; i < 3; i++) {
                Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                spA4 += 16.0f * msgCtx->textCharScale;
            }
            decodedBufPos--;
        } else if (curChar == 0xDE) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = gItemPrices[GET_CUR_FORM_BTN_ITEM(player->heldItemButton)];

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            Message_LoadPluralRupeesNES(play, &decodedBufPos, &charTexIndex, &spA4);
        } else if (curChar == 0xDF) {
            for (i = 0; i < 5; i++) {
                digits[i] = gSaveContext.save.saveInfo.bomberCode[i];
                Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                spA4 += 16.0f * msgCtx->textCharScale;
            }
            decodedBufPos--;
        } else if ((curChar >= 0xE1) && (curChar < 0xE7)) {
            msgCtx->decodedBuffer.schar[decodedBufPos++] =
                D_801D08E4[((void)0, gSaveContext.save.saveInfo.spiderHouseMaskOrder[(s16)(curChar - 0xE1)])];
            index = sMaskCodeTextLengthENG[((void)0,
                                            gSaveContext.save.saveInfo.spiderHouseMaskOrder[(s16)(curChar - 0xE1)])];
            for (playerNameLen = 0; playerNameLen < index; playerNameLen++, decodedBufPos++) {
                Message_LoadCharNES(
                    play,
                    sMaskCodeTextENG[((void)0, gSaveContext.save.saveInfo.spiderHouseMaskOrder[(s16)(curChar - 0xE1)])]
                                    [playerNameLen],
                    &charTexIndex, &spA4, decodedBufPos);
            }

            msgCtx->decodedBuffer.schar[decodedBufPos] = 0;
        } else if (curChar == 0xE7) {
            timeToMoonCrash = TIME_UNTIL_MOON_CRASH;
            digits[0] = 0;
            digits[1] = TIME_TO_HOURS_F_ALT(timeToMoonCrash);

            while (digits[1] >= 10) {
                digits[0]++;
                digits[1] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 2; i++) {
                if ((i == 1) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIndex, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            msgCtx->decodedBuffer.schar[decodedBufPos] = ' ';
            decodedBufPos++;
            Message_LoadCharNES(play, 'h', &charTexIndex, &spA4, decodedBufPos);
            decodedBufPos++;
            Message_LoadCharNES(play, 'o', &charTexIndex, &spA4, decodedBufPos);
            decodedBufPos++;
            Message_LoadCharNES(play, 'u', &charTexIndex, &spA4, decodedBufPos);
            decodedBufPos++;
            Message_LoadCharNES(play, 'r', &charTexIndex, &spA4, decodedBufPos);
            if ((digits[0] != 0) || (digits[1] != 1)) {
                decodedBufPos++;
                Message_LoadCharNES(play, 's', &charTexIndex, &spA4, decodedBufPos);
            }
        } else if (curChar == 0xE8) {
            Message_LoadTimeNES(play, curChar, &charTexIndex, &spA4, &decodedBufPos);

        } else if ((curChar == 0xF0) || (curChar == 0xF1) || (curChar == 0xF2) || (curChar == 0xF8)) {
            if (curChar == 0xF8) {
                value = (s32)HS_GET_HIGH_SCORE_3_LOWER();
            } else {
                value = HIGH_SCORE(curChar - 0xF0);
            }
            if (curChar == 0xF2) {
                if (LINK_AGE_IN_YEARS == YEARS_CHILD) {
                    value &= 0x7F;
                } else {
                    value = (s16)((HIGH_SCORE((u8)font->msgBuf.schar[msgCtx->msgBufPos]) & 0xFF000000) >> 0x18) & 0x7F;
                }
            }
            digits[3] = value;
            digits[0] = digits[1] = digits[2] = 0;

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xF7) || (curChar == 0xF9) || (curChar == 0xFA) || (curChar == 0xFB) ||
                   (curChar == 0xFC)) {
            var_fs0 = 8.0f;
            if (curChar == 0xF7) {
                Message_GetTimerDigitsNES(GET_HIGH_SCORE(HS_UNK_1), spA8);
            } else if (curChar == 0xF9) {
                Message_GetTimerDigitsNES(GET_HIGH_SCORE(HS_HORSE_BACK_BALLOON), spA8);
            } else {
                Message_GetTimerDigitsNES(
                    ((void)0, gSaveContext.save.saveInfo.dekuPlaygroundHighScores[curChar - 0xFA]), spA8);
            }

            loadChar = false;
            for (i = 0; i < 8; i++) {
                if ((i == 4) || ((i != 2) && (i != 5) && (spA8[i] != '\0'))) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, spA8[i], charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = spA8[i];
                    decodedBufPos++;
                } else {
                    var_fs0 -= 1.0f;
                }
            }
            spA4 += var_fs0 * (16.0f * msgCtx->textCharScale);
            decodedBufPos--;
        } else if ((curChar == 0xF3) || (curChar == 0xF4) || (curChar == 0xF5)) {
            value = HIGH_SCORE(curChar - 0xF3 + HS_BOAT_ARCHERY);
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = value;

            while (digits[3] >= 60) {
                digits[1]++;
                if (digits[1] >= 10) {
                    digits[0]++;
                    digits[1] -= 10;
                }
                digits[3] -= 60;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            for (i = 0; i < 4; i++) {
                Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                charTexIndex += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                if (i == 1) {
                    Font_LoadCharNES(play, '"', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                    decodedBufPos++;
                } else if (i == 3) {
                    Font_LoadCharNES(play, 0x27, charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x27;
                }
            }
            spA4 += 4.0f * (16.0f * msgCtx->textCharScale);
        } else if (curChar == 0xF6) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = HS_GET_TOWN_SHOOTING_GALLERY_HIGH_SCORE();

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xFD) || (curChar == 0xFE) || (curChar == 0xFF)) {
            index = curChar - 0xFD;
            for (playerNameLen = 8; playerNameLen > 0; playerNameLen--) {
                if (((void)0,
                     gSaveContext.save.saveInfo.inventory.dekuPlaygroundPlayerName[index][playerNameLen - 1]) != 0x3E) {
                    break;
                }
            }

            for (i = 0; i < playerNameLen; i++) {
                curChar = ((void)0, gSaveContext.save.saveInfo.inventory.dekuPlaygroundPlayerName[index][i]);
                msgCtx->decodedBuffer.schar[decodedBufPos + i] = 0xFD;
                fontBuf = &font->fontBuf[(curChar & 0xFFFF) * FONT_CHAR_TEX_SIZE];

                for (var_v1_3 = 0; var_v1_3 < FONT_CHAR_TEX_SIZE; var_v1_3 += 4) {
                    font->charBuf[font->unk_11D88][charTexIndex + var_v1_3 + 0] = fontBuf[var_v1_3 + 0];
                    font->charBuf[font->unk_11D88][charTexIndex + var_v1_3 + 1] = fontBuf[var_v1_3 + 1];
                    font->charBuf[font->unk_11D88][charTexIndex + var_v1_3 + 2] = fontBuf[var_v1_3 + 2];
                    font->charBuf[font->unk_11D88][charTexIndex + var_v1_3 + 3] = fontBuf[var_v1_3 + 3];
                }
                charTexIndex += FONT_CHAR_TEX_SIZE;
            }
            decodedBufPos += playerNameLen - 1;
            spA4 += playerNameLen * (16.0f * msgCtx->textCharScale);
        } else if (curChar == 0xB) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = HS_GET_BOAT_ARCHERY_HIGH_SCORE();

            while (digits[3] >= 1000) {
                digits[0]++;
                digits[3] -= 1000;
            }
            while (digits[3] >= 100) {
                digits[1]++;
                digits[3] -= 100;
            }
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 4; i++) {
                if ((i == 3) || (digits[i] != 0)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, digits[i] + '0', charTexIndex);
                    charTexIndex += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0x14) {
            decodedBufPos--;
            for (i = 0; i < font->msgBuf.schar[msgCtx->msgBufPos + 1]; i++) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = ' ';
                spA4 += 6.0f;
            }
            msgCtx->msgBufPos++;
        } else if ((curChar == 0x13) || (curChar == 0x11)) {
            msgCtx->unk11F1A[spC6] = 0;
            if (msgCtx->unk11F18 != 0) {
                msgCtx->unk11F1A[spC6] = ((msgCtx->textCharScale * 16.0f * 16.0f) - spA4) * 0.5f;
            }
            spC6++;
            spA4 = 0.0f;
            if (curChar == 0x11) {
                numLines++;
            }
        } else if ((curChar == 0x17) || (curChar == 0x18) || (curChar == 0x1A)) {
            // pass
        } else if (curChar == 0xA) {
            decodedBufPos++;
        } else if (curChar == 0x1C) {
            msgCtx->textFade = true;
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos] & 0xFF;
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos] & 0xFF;
        } else if (curChar == 0x1E) {
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            if (msgCtx->textboxSkipped || (msgCtx->textBoxType == TEXTBOX_TYPE_1) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_3) || (msgCtx->textBoxType == TEXTBOX_TYPE_6) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_8) || (msgCtx->textBoxType == TEXTBOX_TYPE_9) ||
                (msgCtx->textBoxType == TEXTBOX_TYPE_B) || (msgCtx->unk11F0C == 3)) {
                sfxHi = msgCtx->decodedBuffer.schar[decodedBufPos - 1] << 8;
                sfxHi |= msgCtx->decodedBuffer.schar[decodedBufPos];
                Audio_PlaySfx(sfxHi);
            }
        } else if (curChar == 0x1F) {
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
        } else if ((curChar != 0x20) && (curChar >= 9)) {
            Font_LoadCharNES(play, curChar, charTexIndex);
            charTexIndex += FONT_CHAR_TEX_SIZE;
            spA4 += sNESFontWidths[curChar - ' '] * msgCtx->textCharScale;
        } else if (curChar == 0x20) {
            spA4 += 6.0f;
        }
        decodedBufPos++;
        msgCtx->msgBufPos++;
    }
}
