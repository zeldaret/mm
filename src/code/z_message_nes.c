#include "global.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

// clang-format off
// fontWidth
f32 D_801D0470[160] = {
    8.0f,
    8.0f,
    6.0f,
    9.0f,
    9.0f,
    14.0f,
    12.0f,
    3.0f,
    7.0f,
    7.0f,
    7.0f,
    9.0f,
    4.0f,
    6.0f,
    4.0f,
    9.0f,
    10.0f,
    5.0f,
    9.0f,
    9.0f,
    10.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    6.0f,
    6.0f,
    9.0f,
    11.0f,
    9.0f,
    11.0f,
    13.0f,
    12.0f,
    9.0f,
    11.0f,
    11.0f,
    8.0f,
    8.0f,
    12.0f,
    10.0f,
    4.0f,
    8.0f,
    10.0f,
    8.0f,
    13.0f,
    11.0f,
    13.0f,
    9.0f,
    13.0f,
    10.0f,
    10.0f,
    9.0f,
    10.0f,
    11.0f,
    15.0f,
    11.0f,
    10.0f,
    10.0f,
    7.0f,
    10.0f,
    7.0f,
    10.0f,
    9.0f,
    5.0f,
    8.0f,
    9.0f,
    8.0f,
    9.0f,
    9.0f,
    6.0f,
    9.0f,
    8.0f,
    4.0f,
    6.0f,
    8.0f,
    4.0f,
    12.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    7.0f,
    8.0f,
    7.0f,
    8.0f,
    9.0f,
    12.0f,
    8.0f,
    9.0f,
    8.0f,
    7.0f,
    5.0f,
    7.0f,
    10.0f,
    6.0f,
    12.0f,
    12.0f,
    12.0f,
    12.0f,
    11.0f,
    8.0f,
    8.0f,
    8.0f,
    8.0f,
    6.0f,
    6.0f,
    6.0f,
    6.0f,
    10.0f,
    13.0f,
    13.0f,
    13.0f,
    13.0f,
    10.0f,
    10.0f,
    10.0f,
    10.0f,
    9.0f,
    8.0f,
    8.0f,
    8.0f,
    8.0f,
    8.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    4.0f,
    4.0f,
    4.0f,
    4.0f,
    8.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    8.0f,
    8.0f,
    8.0f,
    8.0f,
    8.0f,
    11.0f,
    6.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
    14.0f,
};
// clang-format on

// rupeesTextLocalization
char D_801D06F0[LANGUAGE_MAX - 1][8] = {
    { "Rupee(s)" }, // EN
    { "Rubin(e)" }, // DE
    { "Rubis" },    // FR
    { "Rupia(s)" }, // SPA
};

// rupeesTextLength
u8 D_801D0710[LANGUAGE_MAX - 1] = {
    sizeof("Rupee(s)") - 1,
    sizeof("Rubin(e)") - 1,
    sizeof("Rubis") - 1,
    sizeof("Rupia(s)") - 1,
};

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
    sizeof("Great Bay Coast") - 1,  // OWL_WARP_GREAT_BAY_COAST
    sizeof("Zora Cape") - 1,        // OWL_WARP_ZORA_CAPE
    sizeof("Snowhead") - 1,         // OWL_WARP_SNOWHEAD
    sizeof("Mountain Village") - 1, // OWL_WARP_MOUNTAIN_VILLAGE
    sizeof("Clock Town") - 1,       // OWL_WARP_CLOCK_TOWN
    sizeof("Milk Road") - 1,        // OWL_WARP_MILK_ROAD
    sizeof("Woodfall") - 1,         // OWL_WARP_WOODFALL
    sizeof("Southern Swamp") - 1,   // OWL_WARP_SOUTHERN_SWAMP
    sizeof("Ikana Canyon") - 1,     // OWL_WARP_IKANA_CANYON
    sizeof("Stone Tower") - 1,      // OWL_WARP_STONE_TOWER
    sizeof("Entrance") - 1,         // OWL_WARP_ENTRANCE
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

    f += 16.0f * msgCtx->textCharScale * 6.0f;
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
    f += 16.0f * msgCtx->textCharScale * (D_801D0710[gSaveContext.options.language - 1] + 1);
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
        f += (D_801D0470[currentChar - ' '] * msgCtx->textCharScale);
    }

    p--;
    f += (stringLimit - 1) * (16.0f * msgCtx->textCharScale);
    *decodedBufPos = p;
    *offset = o;
    *arg2 = f;
}

void func_80159438(OSTime time, s16* digits) {
    OSTime t = time;

    digits[0] = t / 36000;
    t -= (digits[0] * 36000);

    digits[1] = t / 6000;
    t -= (digits[1] * 6000);

    digits[2] = '\'';

    digits[3] = t / 1000;
    t -= digits[3] * 1000;

    digits[4] = t / 100;
    t -= digits[4] * 100;

    digits[5] = '"';

    digits[6] = t / 10;
    t -= digits[6] * 10;

    digits[7] = t;

    digits[0] += '0';
    digits[1] += '0';
    digits[3] += '0';
    digits[4] += '0';
    digits[6] += '0';
    digits[7] += '0';
}

// Probably color structs instead of Vec3s... whoops
Vec3s D_801D07DC[] = {
    { 255, 120, 0 },  { 70, 255, 80 },   { 80, 110, 255 },  { 255, 255, 30 },
    { 90, 180, 255 }, { 210, 100, 255 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Vec3s D_801D080C[] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Vec3s D_801D083C[] = {
    { 255, 60, 60 },  { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 180, 180, 200 }, { 255, 130, 30 },
};

Vec3s D_801D086C[] = {
    { 195, 0, 0 },    { 70, 255, 80 },   { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

Vec3s D_801D089C[] = {
    { 255, 60, 60 },  { 110, 170, 255 }, { 80, 90, 255 },   { 255, 255, 50 },
    { 80, 150, 255 }, { 255, 150, 180 }, { 170, 170, 170 }, { 255, 130, 30 },
};

u8 D_801D08CC[] = {
    0x02, 0x01, 0x03, 0x06, 0x06, 0x06, 0x03, 0x03, 0x03, 0x03, 0x01, 0x06,
};

#ifdef NON_EQUIVALENT
void Message_DrawTextNES(PlayState* play, Gfx** gfxP, u16 textDrawPos) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 sp13A;
    Font* font = &play->msgCtx.font;
    Gfx* gfx; // sp_134;
    s16 sp130;
    s16 sp12E;
    s16 sp12C;
    s16 sp12A;
    u8 var_t0; // sp54
    u16 i;
    u16 var_v1;
    u8 temp_v0_20;
    u8 temp_v0_21;

    gfx = *gfxP;
    msgCtx->textPosX = msgCtx->unk11F1A[0] + msgCtx->unk11FF8;
    msgCtx->textPosY = msgCtx->unk11FFA;
    sp130 = 0;

    if (msgCtx->textIsCredits == 0) {
        msgCtx->textPosY = msgCtx->unk11FFA;
    } else {
        msgCtx->textPosY = 0x30;
    }

    if (msgCtx->itemId != 0xFE) {
        Message_DrawItemIcon(play, &gfx);
    }

    msgCtx->textColorR = msgCtx->unk120C8;
    msgCtx->textColorG = msgCtx->unk120CA;
    msgCtx->textColorB = msgCtx->unk120CC;
    sp13A = 0;

    for (i = textDrawPos; i < msgCtx->textDrawPos; i++) {
        var_t0 = (u8)msgCtx->decodedBuffer.schar[i];
        switch (var_t0) { /* switch 1 */
            case 0x0:     /* switch 2 */
                if ((play->pauseCtx.bombersNotebookOpen) || (msgCtx->textBoxType == 0xD)) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else if (msgCtx->textBoxType == 5) {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
                } else {
                    msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 255;
                }

                if (msgCtx->textDrawPos == (i + 1)) {
                    msgCtx->textDrawPos++;
                }
                continue;

            case 0x1: /* switch 2 */
            case 0x2: /* switch 2 */
            case 0x3: /* switch 2 */
            case 0x4: /* switch 2 */
            case 0x5: /* switch 2 */
            case 0x6: /* switch 2 */
            case 0x7: /* switch 2 */
            case 0x8: /* switch 2 */
                if ((msgCtx->msgMode >= 0x4A) && (msgCtx->msgMode < 0x50) && (var_t0 == 2)) {
                    msgCtx->textDrawPos = msgCtx->decodedTextLen;
                    if (msgCtx->unk120D6 != 0) {
                        msgCtx->unk120D4 += 25;
                        if (msgCtx->unk120D4 >= 100) {
                            msgCtx->unk120D6 = 0;
                        }
                    } else {
                        msgCtx->unk120D4 -= 25;
                        if (msgCtx->unk120D4 <= -100) {
                            msgCtx->unk120D6 = 1;
                        }
                    }

                    msgCtx->textColorR = CLAMP_MIN(D_801D07DC[var_t0 - 1 + 1].x + msgCtx->unk120D4, 0);

                    if (D_801D07DC[var_t0 - 1 + 1].y + msgCtx->unk120D4 >= 0xFF) {
                        msgCtx->textColorG = D_801D07DC[var_t0 - 1 + 1].y;
                    } else {
                        msgCtx->textColorG = D_801D07DC[var_t0 - 1 + 1].y + msgCtx->unk120D4;
                    }

                    msgCtx->textColorB = CLAMP_MIN(D_801D07DC[var_t0 - 1 + 1].z + msgCtx->unk120D4, 0);
                } else if (play->pauseCtx.bombersNotebookOpen) {
                    msgCtx->textColorR = D_801D089C[(s16)(var_t0 - 1)].x;
                    msgCtx->textColorG = D_801D089C[(s16)(var_t0 - 1)].y;
                    msgCtx->textColorB = D_801D089C[(s16)(var_t0 - 1)].z;
                } else if (msgCtx->textBoxType == 1) {
                    msgCtx->textColorR = D_801D07DC[(s16)(var_t0 - 1)].x;
                    msgCtx->textColorG = D_801D07DC[(s16)(var_t0 - 1)].y;
                    msgCtx->textColorB = D_801D07DC[(s16)(var_t0 - 1)].z;
                } else if (msgCtx->textBoxType == 0xD) {
                    msgCtx->textColorR = D_801D086C[(s16)(var_t0 - 1)].x;
                    msgCtx->textColorG = D_801D086C[(s16)(var_t0 - 1)].y;
                    msgCtx->textColorB = D_801D086C[(s16)(var_t0 - 1)].z;
                } else {
                    msgCtx->textColorR = D_801D080C[(s16)(var_t0 - 1)].x;
                    msgCtx->textColorG = D_801D080C[(s16)(var_t0 - 1)].y;
                    msgCtx->textColorB = D_801D080C[(s16)(var_t0 - 1)].z;
                }

                if (msgCtx->textDrawPos == (i + 1)) {
                    msgCtx->textDrawPos++;
                }

                continue;

            case 0x20: /* switch 2 */
                msgCtx->textPosX += 6;
                continue;
            case 0x11: /* switch 2 */
                msgCtx->textPosY = msgCtx->textPosY + msgCtx->unk11FFC;
                /* fallthrough */
            case 0x13: /* switch 2 */
                sp130++;

                msgCtx->textPosX = msgCtx->unk11F1A[sp130] + msgCtx->unk11FF8;
                if (msgCtx->choiceNum == 1) {
                    if (play->pauseCtx.bombersNotebookOpen == 0) {
                        msgCtx->textPosX += 0x10;
                    } else {
                        msgCtx->textPosX += 0x32;
                    }
                } else if (msgCtx->choiceNum == 2) {
                    if (msgCtx->unk120D8 != 3) {
                        if (play->pauseCtx.bombersNotebookOpen == 0) {
                            msgCtx->textPosX += 0xA;
                        } else {
                            msgCtx->textPosX += 0x39;
                        }
                    } else if (sp130 >= 2) {
                        if (play->pauseCtx.bombersNotebookOpen == 0) {
                            msgCtx->textPosX += 0xA;
                        } else {
                            msgCtx->textPosX += 0x39;
                        }
                    }
                }
                continue;

            case 0x10: /* switch 2 */
            case 0x12: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    if (msgCtx->textboxSkipped == 0) {
                        play_sound(0);
                        msgCtx->msgMode = 0x41;
                        Font_LoadMessageBoxEndIcon(font, 0);
                    } else {
                        msgCtx->msgMode = 4;
                        msgCtx->textUnskippable = 0;
                        msgCtx->msgBufPos = msgCtx->msgBufPos + 1;
                    }
                    msgCtx->unk120CE = msgCtx->textColorR;
                    msgCtx->unk120D0 = msgCtx->textColorG;
                    msgCtx->unk120D2 = msgCtx->textColorB;
                }
                *gfxP = gfx;
                return;

            case 0x17: /* switch 2 */
                if (msgCtx->textDrawPos == (i + 1)) {
                    var_v1 = i;
                    if ((msgCtx->msgMode == 6) || ((msgCtx->msgMode >= 0xA) && (msgCtx->msgMode < 0x27))) {
                        while (true) {
                            // temp_v0_20 = msgCtx->decodedBuffer.schar[var_v1];
                            if ((msgCtx->decodedBuffer.schar[var_v1] != 0x18) &&
                                (msgCtx->decodedBuffer.schar[var_v1] != 0x1A) &&
                                (msgCtx->decodedBuffer.schar[var_v1] != 0x19) &&
                                (msgCtx->decodedBuffer.schar[var_v1] != 0xE0) &&
                                (msgCtx->decodedBuffer.schar[var_v1] != 0x10) &&
                                (msgCtx->decodedBuffer.schar[var_v1] != 0x12)) {
                                var_v1++;
                                continue;
                            }
                            break;
                        }

                        i = var_v1 - 1;
                        msgCtx->textDrawPos = i + 1;
                    }
                }
                continue;

            case 0x18: /* switch 2 */
                continue;

            case 0x1B: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    msgCtx->stateTimer = (msgCtx->decodedBuffer.schar[++i] << 8) | msgCtx->decodedBuffer.schar[++i];
                    msgCtx->msgMode = 8;
                }
                *gfxP = gfx;
                return;

            case 0x1C: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    if (msgCtx->unk11F0C == 3) {
                        msgCtx->textboxEndType = 0x55;
                    } else {
                        msgCtx->textboxEndType = 0x50;
                    }
                    msgCtx->stateTimer =
                        ((u8)msgCtx->decodedBuffer.schar[++i] << 8) | (u8)msgCtx->decodedBuffer.schar[++i];
                    Font_LoadMessageBoxEndIcon(font, 1);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1D: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x52;
                    msgCtx->stateTimer =
                        ((u8)msgCtx->decodedBuffer.schar[++i] << 8) | (u8)msgCtx->decodedBuffer.schar[++i];
                    Font_LoadMessageBoxEndIcon(font, 1);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1E: /* switch 2 */
                if ((i + 1) == msgCtx->textDrawPos) {
                    if (msgCtx->msgMode == 6) {
                        play_sound((msgCtx->decodedBuffer.schar[i + 1] << 8) | msgCtx->decodedBuffer.schar[i + 2]);
                    }
                }
                if ((i + 1) == msgCtx->textDrawPos) {
                    msgCtx->textDrawPos = msgCtx->textDrawPos + 2;
                }
                i += 2;
                continue;

            case 0x1F: /* switch 2 */

                if ((msgCtx->textDrawPos == (i + 1)) && (msgCtx->msgMode == 6)) {
                    msgCtx->msgMode = 9;
                    msgCtx->textDelayTimer =
                        (msgCtx->decodedBuffer.schar[i + 1] << 8) | msgCtx->decodedBuffer.schar[i + 2];
                }
                i += 2;
                continue;

            case 0xA: /* switch 2 */
                i++;
                temp_v0_21 = (u8)msgCtx->decodedBuffer.schar[i];

                switch (temp_v0_21) { /* switch 3 */
                    case 0x0:         /* switch 3 */
                    case 0x1:         /* switch 3 */
                    case 0x2:         /* switch 3 */
                    case 0x3:         /* switch 3 */
                    case 0x4:         /* switch 3 */
                    case 0x5:         /* switch 3 */
                    case 0x6:         /* switch 3 */
                        msgCtx->textDelay = (u16)temp_v0_21;
                        if (msgCtx->textDrawPos == (i + 1)) {
                            msgCtx->textDrawPos++;
                        }
                        break;
                }
                continue;

            case 0xC1: /* switch 1 */
                msgCtx->textPosX = 0x2D;

                if (msgCtx->msgMode == 6) {
                    play_sound(0);
                }
                // temp_t1 = gfx;
                // gfx = temp_t1 + 8;
                // temp_t1->words.w1 = 0x00000000;
                // temp_t1->words.w0 = 0xE7000000;
                // temp_t4 = gfx;
                // gfx = temp_t4 + 8;
                // temp_t4->words.w0 = 0xFC119623;
                // temp_t4->words.w1 = 0xFF2FFFFF;
                // temp_t8 = gfx;
                // gfx = temp_t8 + 8;
                // temp_t8->words.w0 = 0xFA000000;
                // temp_t8->words.w1 = msgCtx->textColorAlpha & 0xFF;
                // temp_t4_2 = gfx;
                // gfx = temp_t4_2 + 8;
                // temp_t4_2->words.w0 = 0xFD900000;
                // temp_t4_2->words.w1 = msgCtx->textboxSegment + 0x1000;
                // temp_t9 = gfx;
                // gfx = temp_t9 + 8;
                // temp_t9->words.w1 = 0x07000000;
                // temp_t9->words.w0 = 0xF5900000;
                // temp_t4_3 = gfx;
                // gfx = temp_t4_3 + 8;
                // temp_t4_3->words.w1 = 0x00000000;
                // temp_t4_3->words.w0 = 0xE6000000;
                // temp_t7 = gfx;
                // gfx = temp_t7 + 8;
                // temp_t7->words.w1 = 0x0747F156;
                // temp_t7->words.w0 = 0xF3000000;
                // temp_t2 = gfx;
                // gfx = temp_t2 + 8;
                // temp_t2->words.w1 = 0x00000000;
                // temp_t2->words.w0 = 0xE7000000;
                // temp_t5 = gfx;
                // gfx = temp_t5 + 8;
                // temp_t5->words.w1 = 0x00000000;
                // temp_t5->words.w0 = 0xF5800C00;
                // temp_t8_2 = gfx;
                // gfx = temp_t8_2 + 8;
                // temp_t8_2->words.w1 = 0x0017C0BC;
                // temp_t8_2->words.w0 = 0xF2000000;

                gDPPipeSync(gfx++);
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gfx++, 0, 0, 0x00, 0x00, 0x00, msgCtx->textColorAlpha);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_2 = gfx;
                // gfx = temp_v0_2 + 8;
                // temp_v0_2->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF); temp_v0_2->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF) <<
                // 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF); temp_t7_2 = gfx; gfx = temp_t7_2 + 8;
                // temp_t7_2->words.w0 = 0xE1000000;
                // temp_t7_2->words.w1 = 0x00000000;
                // temp_t3 = gfx;
                // gfx = temp_t3 + 8;
                // temp_t3->words.w0 = 0xF1000000;
                // temp_t3->words.w1 = 0x04000400;
                // temp_t5_2 = gfx;
                // gfx = temp_t5_2 + 8;
                // temp_t5_2->words.w0 = 0xFD900000;
                // temp_t5_2->words.w1 = msgCtx->textboxSegment + 0x1900;
                // temp_t3_2 = gfx;
                // gfx = temp_t3_2 + 8;
                // temp_t3_2->words.w1 = 0x07000000;
                // temp_t3_2->words.w0 = 0xF5900000;
                // temp_t5_3 = gfx;
                // gfx = temp_t5_3 + 8;
                // temp_t5_3->words.w1 = 0x00000000;
                // temp_t5_3->words.w0 = 0xE6000000;
                // temp_t8_3 = gfx;
                // gfx = temp_t8_3 + 8;
                // temp_t8_3->words.w1 = 0x0747F156;
                // temp_t8_3->words.w0 = 0xF3000000;
                // temp_t1_2 = gfx;
                // gfx = temp_t1_2 + 8;
                // temp_t1_2->words.w1 = 0x00000000;
                // temp_t1_2->words.w0 = 0xE7000000;
                // temp_t6 = gfx;
                // gfx = temp_t6 + 8;
                // temp_t6->words.w1 = 0x00000000;
                // temp_t6->words.w0 = 0xF5800C00;
                // temp_t9_2 = gfx;
                // gfx = temp_t9_2 + 8;
                // temp_t9_2->words.w1 = 0x0017C0BC;
                // temp_t9_2->words.w0 = 0xF2000000;
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 0x0400, 0x0400);
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_3 = gfx;
                // gfx = temp_v0_3 + 8;
                // temp_v0_3->words.w0 = ((((msgCtx->textPosX + 0xC1) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF); temp_v0_3->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) &
                // 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF); temp_t9_3 = gfx; gfx = temp_t9_3 + 8;
                // temp_t9_3->words.w0 = 0xE1000000;
                // temp_t9_3->words.w1 = 0x00000000;
                // temp_t5_4 = gfx;
                // gfx = temp_t5_4 + 8;
                // temp_t5_4->words.w0 = 0xF1000000;
                // temp_t5_4->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0xC1) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 0x0400, 0x0400);

                // temp_t7_3 = gfx;
                // gfx = temp_t7_3 + 8;
                // temp_t7_3->words.w1 = 0x00000000;
                // temp_t7_3->words.w0 = 0xE7000000;
                gDPPipeSync(gfx++);

                // temp_t3_3 = gfx;
                // gfx = temp_t3_3 + 8;
                // temp_t3_3->words.w0 = 0xFA000000;
                // temp_t3_3->words.w1 = (msgCtx->textColorAlpha & 0xFF) | 0xFF3C0000;
                gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);

                // temp_t7_4 = gfx;
                // gfx = temp_t7_4 + 8;
                // temp_t7_4->words.w0 = 0xFD900000;
                // temp_t7_4->words.w1 = msgCtx->textboxSegment + 0x1000;
                // temp_t5_5 = gfx;
                // gfx = temp_t5_5 + 8;
                // temp_t5_5->words.w1 = 0x07000000;
                // temp_t5_5->words.w0 = 0xF5900000;
                // temp_t7_5 = gfx;
                // gfx = temp_t7_5 + 8;
                // temp_t7_5->words.w1 = 0x00000000;
                // temp_t7_5->words.w0 = 0xE6000000;
                // temp_t3_4 = gfx;
                // gfx = temp_t3_4 + 8;
                // temp_t3_4->words.w1 = 0x0747F156;
                // temp_t3_4->words.w0 = 0xF3000000;
                // temp_t6_2 = gfx;
                // gfx = temp_t6_2 + 8;
                // temp_t6_2->words.w1 = 0x00000000;
                // temp_t6_2->words.w0 = 0xE7000000;
                // temp_t8_4 = gfx;
                // gfx = temp_t8_4 + 8;
                // temp_t8_4->words.w1 = 0x00000000;
                // temp_t8_4->words.w0 = 0xF5800C00;
                // temp_t1_3 = gfx;
                // gfx = temp_t1_3 + 8;
                // temp_t1_3->words.w1 = 0x0017C0BC;
                // temp_t1_3->words.w0 = 0xF2000000;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_4 = gfx;
                // gfx = temp_v0_4 + 8;
                // temp_v0_4->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF); temp_v0_4->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF) <<
                // 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF); temp_t9_4 = gfx; gfx = temp_t9_4 + 8; temp_t9_4->words.w0 =
                // 0xE1000000; temp_t9_4->words.w1 = 0x00000000; temp_t5_6 = gfx; gfx = temp_t5_6 + 8;
                // temp_t5_6->words.w0 = 0xF1000000;
                // temp_t5_6->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0x60) << 2,
                                    (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

                // temp_t4_4 = gfx;
                // gfx = temp_t4_4 + 8;
                // temp_t4_4->words.w0 = 0xFD900000;
                // temp_t4_4->words.w1 = msgCtx->textboxSegment + 0x1900;
                // temp_t5_7 = gfx;
                // gfx = temp_t5_7 + 8;
                // temp_t5_7->words.w1 = 0x07000000;
                // temp_t5_7->words.w0 = 0xF5900000;
                // temp_t4_5 = gfx;
                // gfx = temp_t4_5 + 8;
                // temp_t4_5->words.w1 = 0x00000000;
                // temp_t4_5->words.w0 = 0xE6000000;
                // temp_t3_5 = gfx;
                // gfx = temp_t3_5 + 8;
                // temp_t3_5->words.w1 = 0x0747F156;
                // temp_t3_5->words.w0 = 0xF3000000;
                // temp_t7_6 = gfx;
                // gfx = temp_t7_6 + 8;
                // temp_t7_6->words.w1 = 0x00000000;
                // temp_t7_6->words.w0 = 0xE7000000;
                // temp_t8_5 = gfx;
                // gfx = temp_t8_5 + 8;
                // temp_t8_5->words.w1 = 0x00000000;
                // temp_t8_5->words.w0 = 0xF5800C00;
                // temp_t1_4 = gfx;
                // gfx = temp_t1_4 + 8;
                // temp_t1_4->words.w1 = 0x0017C0BC;
                // temp_t1_4->words.w0 = 0xF2000000;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_5 = gfx;
                // gfx = temp_v0_5 + 8;
                // temp_v0_5->words.w0 = ((((msgCtx->textPosX + 0xC0) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF); temp_v0_5->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) &
                // 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF); temp_t3_6 = gfx; gfx = temp_t3_6 + 8;
                // temp_t3_6->words.w0 = 0xE1000000;
                // temp_t3_6->words.w1 = 0x00000000;
                // temp_t7_7 = gfx;
                // gfx = temp_t7_7 + 8;
                // temp_t7_7->words.w0 = 0xF1000000;
                // temp_t7_7->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 * 4) << 2,
                                    (msgCtx->textPosX + 0xC0) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0,
                                    0, 0x0400, 0x0400);

                // temp_t8_6 = gfx;
                // gfx = temp_t8_6 + 8;
                // temp_t8_6->words.w1 = 0x00000000;
                // temp_t8_6->words.w0 = 0xE7000000;
                gDPPipeSync(gfx++);

                // temp_t1_5 = gfx;
                // gfx = temp_t1_5 + 8;
                // temp_t1_5->words.w0 = 0xFCFF97FF;
                // temp_t1_5->words.w1 = 0xFF2DFEFF;
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                                  PRIMITIVE, 0);

                msgCtx->textPosX += 0x20;
                continue;

            case 0xC2: /* switch 1 */
                msgCtx->textboxEndType = 0x10;

                if (msgCtx->msgMode == 6) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(font, 2U);
                    if (msgCtx->unk120D8 != 3) {
                        msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 0xE);
                        msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x1A);
                        msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x26);
                    }
                }
                continue;

            case 0xC3: /* switch 1 */
                msgCtx->textboxEndType = 0x11;

                if (msgCtx->msgMode == 6) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    Font_LoadMessageBoxEndIcon(font, 2U);
                    if (msgCtx->unk120D8 != 3) {
                        msgCtx->unk11FFE[0] = (s16)(msgCtx->textboxYTarget + 0xE);
                        msgCtx->unk11FFE[1] = (s16)(msgCtx->textboxYTarget + 0x1A);
                        msgCtx->unk11FFE[2] = (s16)(msgCtx->textboxYTarget + 0x26);
                    }
                }
                continue;
            case 0xCC: /* switch 1 */
                msgCtx->textboxEndType = 0x60;

                if (msgCtx->msgMode == 6) {
                    Font_LoadMessageBoxEndIcon(font, 1U);
                }
                continue;

            case 0xD0: /* switch 1 */
                msgCtx->textboxEndType = 0x61;

                if (msgCtx->msgMode == 6) {
                    Font_LoadMessageBoxEndIcon(font, 1U);
                }
                continue;

            case 0xD1: /* switch 1 */
                msgCtx->textboxEndType = 0x62;

                if (msgCtx->msgMode == 6) {
                    Font_LoadMessageBoxEndIcon(font, 1U);
                }
                continue;

            case 0xD2: /* switch 1 */

                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x41;
                    Font_LoadMessageBoxEndIcon(font, 0U);
                    play_sound(0x482EU);
                }
                continue;

            case 0xD5: /* switch 1 */
                msgCtx->textboxEndType = 0x63;

                if (msgCtx->msgMode == 6) {
                    Font_LoadMessageBoxEndIcon(font, 1U);
                }
                continue;

            case 0x15: /* switch 2 */
            case 0xBF: /* switch 1 */
                if (msgCtx->msgMode == 6) {
                    if (msgCtx->textBoxType == 3) {
                        Message_HandleOcarina(play);
                        *gfxP = gfx;
                        return;
                    }

                    msgCtx->msgMode = 0x42;
                    if (msgCtx->textboxEndType == 0) {
                        play_sound(0x482EU);
                        if (var_t0 == 0xBF) {
                            Font_LoadMessageBoxEndIcon(font, 1U);
                        } else {
                            Font_LoadMessageBoxEndIcon(font, 0U);
                        }
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    } else {
                        play_sound(0U);
                    }
                }
                *gfxP = gfx;
                return;

            case 0x1A: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    play_sound(0U);
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x30;
                }
                *gfxP = gfx;
                return;

            case 0x19: /* switch 2 */
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x40;
                    Font_LoadMessageBoxEndIcon(font, 0U);
                    play_sound(0x482EU);
                }
                *gfxP = gfx;
                return;

            case 0xE0: /* switch 1 */
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x42;
                    Font_LoadMessageBoxEndIcon(font, 1U);
                    play_sound(0x482EU);
                }
                *gfxP = gfx;
                return;
                /* switch 2 */

            default: /* switch 2 */
                     // default:                            /* switch 1 */

                switch (var_t0) { /* switch 4; irregular */
                    case 0x8169:  /* switch 4 */
                    case 0x8175:  /* switch 4 */
                        msgCtx->textPosX -= (s32)(6.0f * msgCtx->textCharScale);
                        break;
                    case 0x8145: /* switch 4 */
                        msgCtx->textPosX -= (s32)(3.0f * msgCtx->textCharScale);
                        break;
                    case 0x8148: /* switch 4 */
                    case 0x8149: /* switch 4 */
                        msgCtx->textPosX -= (s32)(2.0f * msgCtx->textCharScale);
                        break;
                }
                if ((msgCtx->msgMode == 6) && (msgCtx->textDrawPos == (i + 1))) {
                    play_sound(0U);
                }
                if (((s32)var_t0 >= 0xB0) && ((s32)var_t0 < 0xBC)) {
                    sp12E = msgCtx->textColorR;
                    sp12C = msgCtx->textColorG;
                    sp12A = msgCtx->textColorB;
                    msgCtx->textColorR = D_801D083C[D_801D08CC[var_t0 - 0xB0]].x;
                    msgCtx->textColorG = D_801D083C[D_801D08CC[var_t0 - 0xB0]].y;
                    msgCtx->textColorB = D_801D083C[D_801D08CC[var_t0 - 0xB0]].z;
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
                    msgCtx->textColorR = sp12E;
                    msgCtx->textColorG = sp12C;
                    msgCtx->textColorB = sp12A;
                } else if (msgCtx->msgMode >= 0x4D) {
                    if ((i < (msgCtx->decodedTextLen - 6)) || (i >= (msgCtx->decodedTextLen - 4))) {
                        Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
                    }
                } else {
                    Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
                }
                sp13A += 0x80;
                switch (var_t0) { /* switch 5; irregular */
                    case 0x8144:  /* switch 5 */
                        msgCtx->textPosX += (s32)(8.0f * msgCtx->textCharScale);
                        break;
                    case 0x816A: /* switch 5 */
                    case 0x8176: /* switch 5 */
                        msgCtx->textPosX += (s32)(10.0f * msgCtx->textCharScale);
                        break;
                    case 0x8141: /* switch 5 */
                    case 0x8142: /* switch 5 */
                    case 0x8168: /* switch 5 */
                        msgCtx->textPosX += (s32)(12.0f * msgCtx->textCharScale);
                        break;
                    case 0x8194: /* switch 5 */
                        msgCtx->textPosX += (s32)(14.0f * msgCtx->textCharScale);
                        break;
                    case 0x8145: /* switch 5 */
                        msgCtx->textPosX += (s32)(15.0f * msgCtx->textCharScale);
                        break;
                    default: /* switch 5 */
                        if (((msgCtx->textboxEndType == 0x62) && ((i < msgCtx->unk120C0) == 0) &&
                             ((msgCtx->unk120C0 + 4) >= i)) ||
                            ((msgCtx->textboxEndType == 0x63) && ((i < msgCtx->unk120C0) == 0) &&
                             ((msgCtx->unk120C0 + 2) >= i)) ||
                            ((msgCtx->textboxEndType == 0x60) && ((i < msgCtx->unk120C0) == 0) &&
                             ((msgCtx->unk120C0 + 2) >= i)) ||
                            ((msgCtx->textboxEndType == 0x61) && ((i < msgCtx->unk120C0) == 0) &&
                             ((msgCtx->unk120C0 + 1) >= i))) {
                            msgCtx->textPosX += (s32)(16.0f * msgCtx->textCharScale);
                        } else {
                            msgCtx->textPosX += (s32)(D_801D0470[var_t0 - ' '] * msgCtx->textCharScale);
                        }
                        break;
                }
                continue;
        }
    }

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos = i + 1;
        msgCtx->textDelayTimer = 0;
        if (msgCtx->msgMode == 9) {
            msgCtx->msgMode = 6;
        }
    } else {
        msgCtx->textDelayTimer--;
    }

    *gfxP = gfx;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/Message_DrawTextNES.s")
#endif

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

char D_801D08E8[][6] = {
    "RED",
    "BLUE",
    "YELLOW",
    "GREEN",
};

u8 D_801D0900[] = {
    sizeof("RED") - 1,
    sizeof("BLUE") - 1,
    sizeof("YELLOW") - 1,
    sizeof("GREEN") - 1,
};

#ifdef NON_EQUIVALENT
void Message_DecodeNES(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font; // spE0
    Player* player;             // spDC
    s16 decodedBufPos;          // spDA
    s16 var_s0_2;
    f32 var_fs0;
    s16 var_s0_3;
    s16 spD0;
    s16 digits[4]; // spC8/CA/CC/CE
    s16 spC6;
    s32 loadChar;
    s32 charTexIdx; // spBC
    s16 index;
    s16 value;
    s16 spA8[8];
    f32 spA4;
    f32 timeInSeconds;
    s16 playerNameLen; // s0
    s16 i;             // s1
    s16 var_v1_3;
    u8 curChar; // sp78
    u8 curChar2;
    u8 temp_s2_2;
    u8 var_s2_9;

    player = GET_PLAYER(play);
    decodedBufPos = 0;
    spC6 = 0;
    charTexIdx = 0;
    spD0 = 0;
    msgCtx->textDelayTimer = 0;
    msgCtx->textDelay = msgCtx->textDelayTimer;
    msgCtx->textFade = 0;
    spA4 = 0.0f;
    font->unk_11D88 = (font->unk_11D88 ^ 1) & 1;
    Message_SetupLoadItemIcon(play);

    while (true) {
        curChar = msgCtx->decodedBuffer.schar[decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos];

        if ((curChar == 0x10) || (curChar == 0x12) || (curChar == 0x1B) || (curChar == 0x1C) || (curChar == 0x1D) ||
            (curChar == 0x19) || (curChar == 0xE0) || (curChar == 0xBF) || (curChar == 0x15)) {
            msgCtx->msgMode = 6;
            msgCtx->textDrawPos = 1;
            if (msgCtx->textBoxType == 3) {
                msgCtx->unk11FFA = msgCtx->textboxY + 2;
            } else {
                msgCtx->unk11FFA = msgCtx->textboxY + 8;
            }
            msgCtx->unk11F1A[spC6] = 0;
            if (msgCtx->unk11F18 != 0) {
                msgCtx->unk11F1A[spC6] = (s16)((s16)(s32)((msgCtx->textCharScale * 16.0f * 16.0f) - spA4) / 2);
            }
            spA4 = 0.0f;
            if (curChar == 0x12) {
                if ((msgCtx->textBoxType != 3) && (msgCtx->textBoxType != 4)) {
                    if (spD0 < 2) {
                        msgCtx->unk11FFA = XREG(10) + msgCtx->textboxY;
                    } else if (spD0 == 2) {
                        msgCtx->unk11FFA = XREG(11) + msgCtx->textboxY;
                    } else if (spD0 == (s16)3U) {
                        msgCtx->unk11FFA = XREG(12) + msgCtx->textboxY;
                    }
                }
            } else {
                if ((msgCtx->textBoxType != 3) && (msgCtx->textBoxType != 4)) {
                    if (spD0 == 0) {
                        msgCtx->unk11FFA = XREG(10) + msgCtx->textboxY + XREG(13);
                    } else if (spD0 == 1) {
                        msgCtx->unk11FFA = XREG(11) + msgCtx->textboxY + XREG(13);
                    } else if (spD0 == 2) {
                        msgCtx->unk11FFA = XREG(12) + msgCtx->textboxY + XREG(13);
                    }
                }
            }
            if ((curChar == 0x1B) || (curChar == 0x1C) || (curChar == 0x1D)) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 1];
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 2];
                msgCtx->msgBufPos += 3;
            }
            msgCtx->decodedTextLen = decodedBufPos;
            msgCtx->unk120D8 = spD0;
            if (msgCtx->textboxSkipped || (msgCtx->textBoxType == 1) || (msgCtx->textBoxType == 3) ||
                (msgCtx->textBoxType == 6) || (msgCtx->textBoxType == 8) || (msgCtx->textBoxType == 9) ||
                (msgCtx->textBoxType == 0xB) || (msgCtx->unk11F0C == 3)) {
                msgCtx->textDrawPos = msgCtx->decodedTextLen;
            }
            msgCtx->unk120C8 = msgCtx->unk120CE;
            msgCtx->unk120CA = msgCtx->unk120D0;
            msgCtx->unk120CC = msgCtx->unk120D2;
            break;
        }

        if (curChar == 0x1A) {
            break;
        }
        if (curChar == 0x16) {
            // Substitute the player name control character for the file's player name.
            for (playerNameLen = ARRAY_COUNT(gSaveContext.save.playerData.playerName); playerNameLen > 0;
                 playerNameLen--) {
                if (gSaveContext.save.playerData.playerName[playerNameLen - 1] != 0x3E) {
                    break;
                }
            }

            for (i = 0; i < playerNameLen; i++) {
                curChar2 = (u8)gSaveContext.save.playerData.playerName[i];
                if (curChar2 == 0x3E) {
                    curChar2 = ' ';
                } else if (curChar2 == 0x40) {
                    curChar2 = '.';
                } else if (curChar2 == 0x3F) {
                    curChar2 = '-';
                } else if (curChar2 < 0xA) {
                    curChar2 += '0';
                } else if (curChar2 < 0x24) {
                    curChar2 += '7';
                } else if (curChar2 < 0x3E) {
                    curChar2 += '=';
                }
                if (curChar2 != ' ') {
                    Font_LoadCharNES(play, curChar2, charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                }
                msgCtx->decodedBuffer.schar[decodedBufPos] = curChar2;
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if (curChar == 0xC1) {
            spC6 = 2;
            spD0 = 2;
            DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1000, _message_texture_staticSegmentRomStart, 0x900);
            DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1900, _message_texture_staticSegmentRomStart + 0x900, 0x900);
            msgCtx->unk12012 = msgCtx->textboxY + 8;
            msgCtx->unk11F18 = 1;
            msgCtx->unk12010 = XREG(47);
        } else if (curChar == 0xC2) {
            msgCtx->unk11F18 = 0;
            msgCtx->choiceNum = 2;
        } else if (curChar == 0xC3) {
            msgCtx->unk11F18 = 0;
            msgCtx->choiceNum = 3;
            msgCtx->unk11FF8 = msgCtx->unk11FF8 + 0x16;
        } else if (curChar == 0xC4) {
            func_80159438(gSaveContext.timerCurTimes[curChar - 0xC4], spA8);

            loadChar = false;
            for (i = 0; i < 5; i++) {
                if ((i == 1) || (spA8[i + 3] != 0x30)) {
                    loadChar = true;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, spA8[i + 4], &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xC5) || (curChar == 0xC6) || (curChar == 0xC7) || (curChar == 0xC8) ||
                   (curChar == 0xC9)) {
            func_80159438(gSaveContext.timerCurTimes[curChar - 0xC4], spA8);

            loadChar = false;
            for (i = 0; i < 8; i++) {
                switch (i) {
                    case 2:
                    case 5:
                        break;
                    default:
                        if (spA8[i] != 0x30) {
                            case 4:
                                loadChar = true;
                        }
                        break;
                }
                if (loadChar) {
                    Message_LoadCharNES(play, spA8[i], &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0xCA) {
            digits[0] = 0;
            timeInSeconds = TIME_TO_MINUTES_F(gSaveContext.save.time);

            digits[1] = timeInSeconds / 60.0f;
            while (digits[1] >= 10) {
                digits[0]++;
                digits[1] -= 10;
            }

            digits[2] = 0;
            digits[3] = (s32)timeInSeconds % 60;
            while (digits[3] >= 10) {
                digits[2]++;
                digits[3] -= 10;
            }

            for (i = 0; i < 4; i++) {
                Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                if (i == 1) {
                    Font_LoadCharNES(play, 0x22, charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x22;
                    decodedBufPos++;
                } else if (i == 3) {
                    Font_LoadCharNES(play, 0x27, charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x27;
                }
            }
            spA4 += 6.0f * (16.0f * msgCtx->textCharScale);
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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
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
            msgCtx->unk120C4 = charTexIdx;
            digits[0] = digits[1] = digits[2] = 0;
            for (i = 0; i < 3; i++) {
                Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            Message_LoadLocalizedRupeesNES(play, &decodedBufPos, &charTexIdx, &spA4);
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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            Message_LoadRupeesNES(play, &decodedBufPos, &charTexIdx, &spA4, msgCtx->bankRupeesSelected);
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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            Message_LoadRupeesNES(play, &decodedBufPos, &charTexIdx, &spA4, msgCtx->bankRupees);
        } else if (curChar == 0xCF) {
            Message_LoadTimeNES(play, curChar & 0xFF, &charTexIdx, &spA4, &decodedBufPos);
        } else if (curChar == 0xC) {
            digits[0] = digits[1] = 0;
            digits[2] = gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex];

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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }

            if ((gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 1) ||
                (gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 0x15)) {
                Message_LoadCharNES(play, 0x73, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x74, &charTexIdx, &spA4, ++decodedBufPos);
            } else if ((gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 2) ||
                       (gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 0x16)) {
                Message_LoadCharNES(play, 0x6E, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x64, &charTexIdx, &spA4, ++decodedBufPos);
            } else if ((gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 3) ||
                       (gSaveContext.save.inventory.strayFairies[(void)0, gSaveContext.dungeonIndex] == 0x17)) {
                Message_LoadCharNES(play, 0x72, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x64, &charTexIdx, &spA4, ++decodedBufPos);
            } else {
                Message_LoadCharNES(play, 0x74, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x68, &charTexIdx, &spA4, ++decodedBufPos);
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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }

            if ((Inventory_GetSkullTokenCount(play->sceneId) == 1) ||
                (Inventory_GetSkullTokenCount(play->sceneId) == 21)) {
                Message_LoadCharNES(play, 0x73, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x74, &charTexIdx, &spA4, ++decodedBufPos);
            } else if ((Inventory_GetSkullTokenCount(play->sceneId) == 2) ||
                       (Inventory_GetSkullTokenCount(play->sceneId) == 22)) {
                Message_LoadCharNES(play, 0x6E, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x64, &charTexIdx, &spA4, ++decodedBufPos);
            } else if ((Inventory_GetSkullTokenCount(play->sceneId) == 3) ||
                       (Inventory_GetSkullTokenCount(play->sceneId) == 23)) {
                Message_LoadCharNES(play, 0x72, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x64, &charTexIdx, &spA4, ++decodedBufPos);
            } else {
                Message_LoadCharNES(play, 0x74, &charTexIdx, &spA4, decodedBufPos);
                Message_LoadCharNES(play, 0x68, &charTexIdx, &spA4, ++decodedBufPos);
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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
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
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
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
            msgCtx->unk120C4 = charTexIdx;
            digits[0] = digits[1] = digits[2] = 0;
            for (i = 0; i < 2; i++) {
                Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            Message_LoadPluralRupeesNES(play, &decodedBufPos, &charTexIdx, &spA4);
        } else if (curChar == 0xD1) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 0;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIdx;

            for (i = 0; i < 5; i++) {
                msgCtx->unk12054[i] = 1;
                Message_LoadCharNES(play, 0x31U, &charTexIdx, &spA4, decodedBufPos);
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if (curChar == 0xD3) {
            if (gSaveContext.save.timeSpeedOffset == 0x12) {
                var_s2_9 = 0;
            } else if (gSaveContext.save.timeSpeedOffset == 0) {
                var_s2_9 = 1;
            } else {
                var_s2_9 = 2;
            }

            for (i = 0; i < 4; i++) {
                msgCtx->decodedBuffer.schar[decodedBufPos] = D_801D08D8[var_s2_9][i];
                Font_LoadCharNES(play, D_801D08D8[var_s2_9][i], charTexIdx);
                decodedBufPos++;
                charTexIdx += FONT_CHAR_TEX_SIZE;
            }
            decodedBufPos--;
            spA4 += 3.0f * (16.0f * msgCtx->textCharScale);
            msgCtx->choiceIndex = var_s2_9;
        } else if (curChar == 0xD4) {
            Message_LoadOwlWarpTextNES(play, &charTexIdx, &spA4, &decodedBufPos);
        } else if (curChar == 0xD5) {
            decodedBufPos++;
            msgCtx->unk120BE = spC6;
            msgCtx->unk120C0 = decodedBufPos;
            msgCtx->unk120C2 = 0;
            msgCtx->bankRupeesSelected = 0;
            msgCtx->unk120C4 = charTexIdx;
            for (i = 0; i < 3; i++) {
                msgCtx->unk12054[i] = 1;
                Font_LoadCharNES(play, 0x31U, charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = 0x31;
                decodedBufPos++;
                spA4 += 16.0f * msgCtx->textCharScale;
            }
            decodedBufPos--;
        } else if (curChar == 0xD6) {
            for (i = 0; i < 6; i++) {
                msgCtx->decodedBuffer.schar[decodedBufPos] = (s8)D_801D08E4[gSaveContext.save.spiderHouseMaskOrder[i]];
                Message_LoadCharNES(play, (i + 0x31) & 0xFF, &charTexIdx, &spA4, ++decodedBufPos);
                decodedBufPos++;
            }
            msgCtx->decodedBuffer.schar[decodedBufPos] = 0;
        } else if ((curChar >= 0xD7) && (curChar < 0xDB)) {
            digits[0] = digits[1] = 0;
            digits[2] = 15 - gSaveContext.save.inventory.strayFairies[curChar - 0xD7];

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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xDC) || (curChar == 0xDD)) {
            if (curChar == 0xDC) {
                digits[0] = gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][0];
                digits[1] = gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][1];
                digits[2] = gSaveContext.save.lotteryCodes[CURRENT_DAY - 1][2];
            } else {
                // temp_v0_14 = gSaveContext.save.lotteryCodeGuess;
                digits[0] = (u32)(((void)0, gSaveContext.save.lotteryCodeGuess) & 0xF00) >> 8;
                digits[1] = (u32)(((void)0, gSaveContext.save.lotteryCodeGuess) & 0xF0) >> 4;
                digits[2] = ((void)0, gSaveContext.save.lotteryCodeGuess) & 0xF;
            }

            for (i = 0; i < 3; i++) {
                Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            Message_LoadPluralRupeesNES(play, &decodedBufPos, &charTexIdx, &spA4);
        } else if (curChar == 0xDF) {
            for (i = 0; i < 5; i++) {
                digits[i] = gSaveContext.save.bomberCode[i];
                Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                spA4 += 16.0f * msgCtx->textCharScale;
            }
            decodedBufPos--;
        } else if ((curChar >= 0xE1) && (curChar < 0xE7)) {
            index = curChar - 0xE1;
            msgCtx->decodedBuffer.schar[decodedBufPos] = D_801D08E4[gSaveContext.save.spiderHouseMaskOrder[index]];
            temp_s2_2 = D_801D0900[gSaveContext.save.spiderHouseMaskOrder[index]];
            decodedBufPos++;

            for (var_s0_2 = 0; var_s0_2 < temp_s2_2; var_s0_2++) {
                Message_LoadCharNES(play, D_801D08E8[gSaveContext.save.spiderHouseMaskOrder[index]][var_s0_2],
                                    &charTexIdx, &spA4, decodedBufPos);
                decodedBufPos++;
            }

            msgCtx->decodedBuffer.schar[decodedBufPos] = 0;
        } else if (curChar == 0xE7) {
            digits[0] = 0;

            digits[1] = (s32)(
                ((f32)((-(((s32)gSaveContext.save.day % 5) << 0x10) - ((gSaveContext.save.time - 0x4000) & 0xFFFF)) +
                       0x40000) *
                 0.021972656f) /
                60.0f);

            while (digits[1] >= 10) {
                digits[0]++;
                digits[1] -= 10;
            }

            loadChar = false;
            for (i = 0; i < 2; i++) {
                if ((i == 1) || (digits[i] != 0)) {
                    loadChar = 1;
                }
                if (loadChar != 0) {
                    Message_LoadCharNES(play, digits[i] + '0', &charTexIdx, &spA4, decodedBufPos);
                    decodedBufPos++;
                }
            }
            msgCtx->decodedBuffer.schar[decodedBufPos] = 0x20;
            Message_LoadCharNES(play, 0x68, &charTexIdx, &spA4, ++decodedBufPos);
            Message_LoadCharNES(play, 0x6F, &charTexIdx, &spA4, ++decodedBufPos);
            Message_LoadCharNES(play, 0x75, &charTexIdx, &spA4, ++decodedBufPos);
            Message_LoadCharNES(play, 0x72, &charTexIdx, &spA4, ++decodedBufPos);
            if ((digits[0] != 0) || (digits[1] != 1)) {
                Message_LoadCharNES(play, 0x73, &charTexIdx, &spA4, ++decodedBufPos);
            }
        } else if (curChar == 0xE8) {
            Message_LoadTimeNES(play, curChar & 0xFF, &charTexIdx, &spA4, &decodedBufPos);

        } else if ((curChar == 0xF0) || (curChar == 0xF1) || (curChar == 0xF2) || (curChar == 0xF8)) {
            if (curChar == 0xF8) {
                value = gSaveContext.save.unk_EE8;
            } else {
                value = (&gSaveContext.save.bankRupees)[curChar - 0xF0];
            }
            if (curChar == 0xF2) {
                if (((gSaveContext.save.linkAge != 0) ? 5 : 17) == 5) {
                    value &= 0x7F;
                } else {
                    value = ((s16)((u32)((&gSaveContext.save.bankRupees)[font->msgBuf.schar[msgCtx->msgBufPos]] &
                                         0xFF000000) >>
                                   0x18) &
                             0x7F);
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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
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
                func_80159438(gSaveContext.save.unk_EE0, spA8);
            } else if (curChar == 0xF9) {
                func_80159438(gSaveContext.save.horseBackBalloonHighScore, spA8);
            } else {
                func_80159438(gSaveContext.save.dekuPlaygroundHighScores[curChar - 0xFA], spA8);
            }

            loadChar = false;
            for (i = 0; i < 8; i++) {
                switch (i) {
                    case 2:
                    case 5:
                        break;
                    default:
                        if (spA8[i] != 0) {
                            case 4:
                                loadChar = 1;
                        }
                        break;
                }
                if (loadChar) {
                    Font_LoadCharNES(play, spA8[i + 1], charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = spA8[i];
                    decodedBufPos++;
                } else {
                    var_fs0 -= 1.0f;
                }
            }
            decodedBufPos--;
            spA4 += var_fs0 * (16.0f * msgCtx->textCharScale);
        } else if ((curChar == 0xF3) || (curChar == 0xF4) || (curChar == 0xF5)) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = (&gSaveContext.save.unk_EE8)[curChar - 0xF3];

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
                Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                if (i == 1) {
                    Font_LoadCharNES(play, '"', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                    decodedBufPos++;
                } else if (i == 3) {
                    Font_LoadCharNES(play, 0x27, charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = 0x27;
                }
            }
            spA4 += 4.0f * (16.0f * msgCtx->textCharScale);
        } else if (curChar == 0xF6) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = gSaveContext.save.shootingGalleryHighScores;

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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if ((curChar == 0xFD) || (curChar == 0xFE) || (curChar == 0xFF)) {
            index = curChar - 0xFD;

            for (var_s0_3 = 8; var_s0_3 > 0; var_s0_3--) {
                if (gSaveContext.save.inventory.dekuPlaygroundPlayerName[index][var_s0_3 - 1] == 0x3E) {
                    break;
                }
            }

            for (i = 0; i < var_s0_3; i++) {
                msgCtx->decodedBuffer.schar[decodedBufPos + i] = 0xFD;

                for (var_v1_3 = 0; var_v1_3 < 0x80; var_v1_3 += 4) {
                    font->charBuf[font->unk_11D88][charTexIdx + var_v1_3 + 0] =
                        font->fontBuf[gSaveContext.save.inventory.dekuPlaygroundPlayerName[index][i] + var_v1_3 + 0];
                    font->charBuf[font->unk_11D88][charTexIdx + var_v1_3 + 1] =
                        font->fontBuf[gSaveContext.save.inventory.dekuPlaygroundPlayerName[index][i] + var_v1_3 + 1];
                    font->charBuf[font->unk_11D88][charTexIdx + var_v1_3 + 2] =
                        font->fontBuf[gSaveContext.save.inventory.dekuPlaygroundPlayerName[index][i] + var_v1_3 + 2];
                    font->charBuf[font->unk_11D88][charTexIdx + var_v1_3 + 3] =
                        font->fontBuf[gSaveContext.save.inventory.dekuPlaygroundPlayerName[index][i] + var_v1_3 + 3];
                }
                charTexIdx += FONT_CHAR_TEX_SIZE;
            }
            decodedBufPos = (decodedBufPos + var_s0_3) - 1;
            spA4 += (f32)var_s0_3 * (16.0f * msgCtx->textCharScale);
        } else if (curChar == 0xB) {
            digits[0] = digits[1] = digits[2] = 0;
            digits[3] = (s16)((u32)(gSaveContext.save.unk_EE8 & 0xFFFF0000) >> 0x10);

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
                    Font_LoadCharNES(play, digits[i] + '0', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    spA4 += 16.0f * msgCtx->textCharScale;
                }
            }
            decodedBufPos--;
        } else if (curChar == 0x14) {
            decodedBufPos--;
            for (i = 0; i < font->msgBuf.schar[msgCtx->msgBufPos + 1]; i++) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = 0x20;
                spA4 += 6.0f;
            }
            msgCtx->msgBufPos++;
        } else if ((curChar == 0x13) || (curChar == 0x11)) {
            msgCtx->unk11F1A[spC6] = 0;
            if (msgCtx->unk11F18 != 0) {
                msgCtx->unk11F1A[spC6] = (s16)(s32)(((msgCtx->textCharScale * 16.0f * 16.0f) - spA4) * 0.5f);
            }
            spC6++;
            spA4 = 0.0f;
            if (curChar == 0x11) {
                spD0++;
            }
        } else if ((curChar == 0x17) || (curChar == 0x18) || (curChar == 0x1A)) {

        } else if (curChar == 0xA) {
            decodedBufPos++;
        } else if (curChar == 0x1C) {
            msgCtx->textFade = true;
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
        } else if (curChar == 0x1E) {
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            if (msgCtx->textboxSkipped || (msgCtx->textBoxType == 1) || (msgCtx->textBoxType == 3) ||
                (msgCtx->textBoxType == 6) || (msgCtx->textBoxType == 8) || (msgCtx->textBoxType == 9) ||
                (msgCtx->textBoxType == 0xB) || (msgCtx->unk11F0C == 3)) {
                play_sound((msgCtx->decodedBuffer.schar[decodedBufPos - 1] << 8) |
                           msgCtx->decodedBuffer.schar[decodedBufPos]);
            }
        } else if (curChar == 0x1F) {
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
        } else if ((curChar != 0x20) && ((s32)curChar >= 9)) {
            Font_LoadCharNES(play, curChar, charTexIdx);
            charTexIdx += FONT_CHAR_TEX_SIZE;
            D_801D0470[curChar - ' '] * msgCtx->textCharScale;
            spA4 += D_801D0470[curChar - ' '] * msgCtx->textCharScale;
        } else if (curChar == 0x20) {
            spA4 += 6.0f;
        }
        decodedBufPos++;
        msgCtx->msgBufPos++;
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/Message_DecodeNES.s")
#endif