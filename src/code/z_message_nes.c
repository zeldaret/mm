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
char D_801D06F0[4][8] = {
    { "Rupee(s)" }, // EN
    { "Rubin(e)" }, // DE
    { "Rubis" },    // FR
    { "Rupia(s)" }, // SPA
};

// rupeesTextLength
u8 D_801D0710[4] = {
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
        // Calculates the time left before the moon crashes.
        // The day begins at CLOCK_TIME(6, 0) so it must be offset.
        timeLeft = (4 - CURRENT_DAY) * DAY_LENGTH - (u16)(((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0));
    } else {
        // Calculates the time left before a new day.
        // The day begins at CLOCK_TIME(6, 0) so it must be offset.
        timeLeft = DAY_LENGTH - (u16)(((void)0, gSaveContext.save.time) - CLOCK_TIME(6, 0));
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

#if 0
void Message_DrawTextNES(PlayState* play, Gfx** gfxP, s32 textDrawPos) {
    u16 sp13A;
    Gfx* gfx; // sp_134;
    s16 sp130;
    s16 sp12E;
    s16 sp12C;
    s16 sp12A;
    s32 sp54;
    s32 sp50;
    Font* font = &play->msgCtx.font;
    //Gfx* temp_t1;
    //Gfx* temp_t1_2;
    //Gfx* temp_t1_3;
    //Gfx* temp_t1_4;
    //Gfx* temp_t1_5;
    //Gfx* temp_t2;
    //Gfx* temp_t3;
    //Gfx* temp_t3_2;
    //Gfx* temp_t3_3;
    //Gfx* temp_t3_4;
    //Gfx* temp_t3_5;
    //Gfx* temp_t3_6;
    //Gfx* temp_t4;
    //Gfx* temp_t4_2;
    //Gfx* temp_t4_3;
    //Gfx* temp_t4_4;
    //Gfx* temp_t4_5;
    //Gfx* temp_t5;
    //Gfx* temp_t5_2;
    //Gfx* temp_t5_3;
    //Gfx* temp_t5_4;
    //Gfx* temp_t5_5;
    //Gfx* temp_t5_6;
    //Gfx* temp_t5_7;
    //Gfx* temp_t6;
    //Gfx* temp_t6_2;
    //Gfx* temp_t7;
    //Gfx* temp_t7_2;
    //Gfx* temp_t7_3;
    //Gfx* temp_t7_4;
    //Gfx* temp_t7_5;
    //Gfx* temp_t7_6;
    //Gfx* temp_t7_7;
    //Gfx* temp_t8;
    //Gfx* temp_t8_2;
    //Gfx* temp_t8_3;
    //Gfx* temp_t8_4;
    //Gfx* temp_t8_5;
    //Gfx* temp_t8_6;
    //Gfx* temp_t9;
    //Gfx* temp_t9_2;
    //Gfx* temp_t9_3;
    //Gfx* temp_t9_4;
    //Gfx* temp_v0_2;
    //Gfx* temp_v0_3;
    //Gfx* temp_v0_4;
    //Gfx* temp_v0_5;
    MessageContext* msgCtx;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v0_25;
    s16 temp_v0_26;
    s16 temp_v0_27;
    s16 temp_v0_28;
    s16 temp_v0_6;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s32 temp_s2;
    s32 temp_t2_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a1;
    u16 var_s3;
    u16 var_v1;
    u16 temp_v0_17;
    u16 temp_v0_22;
    u16 temp_v0_24;
    u16 temp_v0_29;
    u16 temp_v0_9;
    u8 var_t0;
    u8 temp_v0_10;
    u8 temp_v0_13;
    u8 temp_v0_18;
    u8 temp_v0_20;
    u8 temp_v0_21;
    u8 temp_v0_8;
    u8 temp_v1_8;
    Vec3s* temp_v0_11;
    Vec3s* temp_v0_12;
    Vec3s* temp_v0_14;
    Vec3s* temp_v0_15;
    Vec3s* temp_v0_16;

    temp_s2 = textDrawPos & 0xFFFF;
    msgCtx = &play->msgCtx;
    gfx = *gfxP;
    play->msgCtx.textPosX = play->msgCtx.unk11F1A[0] + play->msgCtx.unk11FF8;
    play->msgCtx.textPosY = play->msgCtx.unk11FFA;
    sp130 = 0;
    if (play->msgCtx.textIsCredits == 0) {
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

    for (var_s3 = temp_s2 & 0xFFFF; var_s3 < msgCtx->textDrawPos; var_s3++) {
        var_t0 = (u8) msgCtx->decodedBuffer.schar[var_s3];
            switch (var_t0) {                      /* switch 1 */
                case 0xC1:                          /* switch 1 */
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
                    gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);



                    //temp_v0_2 = gfx;
                    //gfx = temp_v0_2 + 8;
                    //temp_v0_2->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF);
                    //temp_v0_2->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF);
                    //temp_t7_2 = gfx;
                    //gfx = temp_t7_2 + 8;
                    //temp_t7_2->words.w0 = 0xE1000000;
                    //temp_t7_2->words.w1 = 0x00000000;
                    //temp_t3 = gfx;
                    //gfx = temp_t3 + 8;
                    //temp_t3->words.w0 = 0xF1000000;
                    //temp_t3->words.w1 = 0x04000400;
                    //temp_t5_2 = gfx;
                    //gfx = temp_t5_2 + 8;
                    //temp_t5_2->words.w0 = 0xFD900000;
                    //temp_t5_2->words.w1 = msgCtx->textboxSegment + 0x1900;
                    //temp_t3_2 = gfx;
                    //gfx = temp_t3_2 + 8;
                    //temp_t3_2->words.w1 = 0x07000000;
                    //temp_t3_2->words.w0 = 0xF5900000;
                    //temp_t5_3 = gfx;
                    //gfx = temp_t5_3 + 8;
                    //temp_t5_3->words.w1 = 0x00000000;
                    //temp_t5_3->words.w0 = 0xE6000000;
                    //temp_t8_3 = gfx;
                    //gfx = temp_t8_3 + 8;
                    //temp_t8_3->words.w1 = 0x0747F156;
                    //temp_t8_3->words.w0 = 0xF3000000;
                    //temp_t1_2 = gfx;
                    //gfx = temp_t1_2 + 8;
                    //temp_t1_2->words.w1 = 0x00000000;
                    //temp_t1_2->words.w0 = 0xE7000000;
                    //temp_t6 = gfx;
                    //gfx = temp_t6 + 8;
                    //temp_t6->words.w1 = 0x00000000;
                    //temp_t6->words.w0 = 0xF5800C00;
                    //temp_t9_2 = gfx;
                    //gfx = temp_t9_2 + 8;
                    //temp_t9_2->words.w1 = 0x0017C0BC;
                    //temp_t9_2->words.w0 = 0xF2000000;
                    gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, (msgCtx->unk12012 + 1) << 2, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);
                    gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);




                    //temp_v0_3 = gfx;
                    //gfx = temp_v0_3 + 8;
                    //temp_v0_3->words.w0 = ((((msgCtx->textPosX + 0xC1) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF);
                    //temp_v0_3->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF);
                    //temp_t9_3 = gfx;
                    //gfx = temp_t9_3 + 8;
                    //temp_t9_3->words.w0 = 0xE1000000;
                    //temp_t9_3->words.w1 = 0x00000000;
                    //temp_t5_4 = gfx;
                    //gfx = temp_t5_4 + 8;
                    //temp_t5_4->words.w0 = 0xF1000000;
                    //temp_t5_4->words.w1 = 0x04000400;
                    gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 1) << 2, (msgCtx->textPosX + 0xC1) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);



                    // temp_t7_3 = gfx;
                    // gfx = temp_t7_3 + 8;
                    // temp_t7_3->words.w1 = 0x00000000;
                    // temp_t7_3->words.w0 = 0xE7000000;
                    gDPPipeSync(gfx++);



                    //temp_t3_3 = gfx;
                    //gfx = temp_t3_3 + 8;
                    //temp_t3_3->words.w0 = 0xFA000000;
                    //temp_t3_3->words.w1 = (msgCtx->textColorAlpha & 0xFF) | 0xFF3C0000;
                    gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);

                    //temp_t7_4 = gfx;
                    //gfx = temp_t7_4 + 8;
                    //temp_t7_4->words.w0 = 0xFD900000;
                    //temp_t7_4->words.w1 = msgCtx->textboxSegment + 0x1000;
                    //temp_t5_5 = gfx;
                    //gfx = temp_t5_5 + 8;
                    //temp_t5_5->words.w1 = 0x07000000;
                    //temp_t5_5->words.w0 = 0xF5900000;
                    //temp_t7_5 = gfx;
                    //gfx = temp_t7_5 + 8;
                    //temp_t7_5->words.w1 = 0x00000000;
                    //temp_t7_5->words.w0 = 0xE6000000;
                    //temp_t3_4 = gfx;
                    //gfx = temp_t3_4 + 8;
                    //temp_t3_4->words.w1 = 0x0747F156;
                    //temp_t3_4->words.w0 = 0xF3000000;
                    //temp_t6_2 = gfx;
                    //gfx = temp_t6_2 + 8;
                    //temp_t6_2->words.w1 = 0x00000000;
                    //temp_t6_2->words.w0 = 0xE7000000;
                    //temp_t8_4 = gfx;
                    //gfx = temp_t8_4 + 8;
                    //temp_t8_4->words.w1 = 0x00000000;
                    //temp_t8_4->words.w0 = 0xF5800C00;
                    //temp_t1_3 = gfx;
                    //gfx = temp_t1_3 + 8;
                    //temp_t1_3->words.w1 = 0x0017C0BC;
                    //temp_t1_3->words.w0 = 0xF2000000;
                    gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);




                    //temp_v0_4 = gfx;
                    //gfx = temp_v0_4 + 8;
                    //temp_v0_4->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF);
                    //temp_v0_4->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF);
                    //temp_t9_4 = gfx;
                    //gfx = temp_t9_4 + 8;
                    //temp_t9_4->words.w0 = 0xE1000000;
                    //temp_t9_4->words.w1 = 0x00000000;
                    //temp_t5_6 = gfx;
                    //gfx = temp_t5_6 + 8;
                    //temp_t5_6->words.w0 = 0xF1000000;
                    //temp_t5_6->words.w1 = 0x04000400;
                    gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);



                    //temp_t4_4 = gfx;
                    //gfx = temp_t4_4 + 8;
                    //temp_t4_4->words.w0 = 0xFD900000;
                    //temp_t4_4->words.w1 = msgCtx->textboxSegment + 0x1900;
                    //temp_t5_7 = gfx;
                    //gfx = temp_t5_7 + 8;
                    //temp_t5_7->words.w1 = 0x07000000;
                    //temp_t5_7->words.w0 = 0xF5900000;
                    //temp_t4_5 = gfx;
                    //gfx = temp_t4_5 + 8;
                    //temp_t4_5->words.w1 = 0x00000000;
                    //temp_t4_5->words.w0 = 0xE6000000;
                    //temp_t3_5 = gfx;
                    //gfx = temp_t3_5 + 8;
                    //temp_t3_5->words.w1 = 0x0747F156;
                    //temp_t3_5->words.w0 = 0xF3000000;
                    //temp_t7_6 = gfx;
                    //gfx = temp_t7_6 + 8;
                    //temp_t7_6->words.w1 = 0x00000000;
                    //temp_t7_6->words.w0 = 0xE7000000;
                    //temp_t8_5 = gfx;
                    //gfx = temp_t8_5 + 8;
                    //temp_t8_5->words.w1 = 0x00000000;
                    //temp_t8_5->words.w0 = 0xF5800C00;
                    //temp_t1_4 = gfx;
                    //gfx = temp_t1_4 + 8;
                    //temp_t1_4->words.w1 = 0x0017C0BC;
                    //temp_t1_4->words.w0 = 0xF2000000;
                    gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);




                    //temp_v0_5 = gfx;
                    //gfx = temp_v0_5 + 8;
                    //temp_v0_5->words.w0 = ((((msgCtx->textPosX + 0xC0) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF);
                    //temp_v0_5->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF);
                    //temp_t3_6 = gfx;
                    //gfx = temp_t3_6 + 8;
                    //temp_t3_6->words.w0 = 0xE1000000;
                    //temp_t3_6->words.w1 = 0x00000000;
                    //temp_t7_7 = gfx;
                    //gfx = temp_t7_7 + 8;
                    //temp_t7_7->words.w0 = 0xF1000000;
                    //temp_t7_7->words.w1 = 0x04000400;
                    gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 * 4) << 2, (msgCtx->textPosX + 0xC0) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);


                    //temp_t8_6 = gfx;
                    //gfx = temp_t8_6 + 8;
                    //temp_t8_6->words.w1 = 0x00000000;
                    //temp_t8_6->words.w0 = 0xE7000000;
                    gDPPipeSync(gfx++);


                    //temp_t1_5 = gfx;
                    //gfx = temp_t1_5 + 8;
                    //temp_t1_5->words.w0 = 0xFCFF97FF;
                    //temp_t1_5->words.w1 = 0xFF2DFEFF;
                    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);



                    msgCtx->textPosX = msgCtx->textPosX + 0x20;
                    continue;

                case 0xC2:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x10;
                    
                    if (msgCtx->msgMode == 6) {
                        msgCtx->choiceTextId = msgCtx->currentTextId;
                        msgCtx->stateTimer = 4;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2U);
                        if (msgCtx->unk120D8 != 3) {
                            temp_v0_6 = msgCtx->textboxYTarget;
                            msgCtx->unk11FFE[0] = (s16) (temp_v0_6 + 0xE);
                            msgCtx->unk11FFE[1] = (s16) (temp_v0_6 + 0x1A);
                            msgCtx->unk11FFE[2] = (s16) (temp_v0_6 + 0x26);
                        }
                    }
                    continue;

                case 0xC3:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x11;
                    
                    if (msgCtx->msgMode == 6) {
                        msgCtx->choiceTextId = msgCtx->currentTextId;
                        msgCtx->stateTimer = 4;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2U);
                        if (msgCtx->unk120D8 != 3) {
                            msgCtx->unk11FFE[0] = (s16) (msgCtx->textboxYTarget + 0xE);
                            msgCtx->unk11FFE[1] = (s16) (msgCtx->textboxYTarget + 0x1A);
                            msgCtx->unk11FFE[2] = (s16) (msgCtx->textboxYTarget + 0x26);
                        }
                    }
                    continue;
                case 0xCC:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x60;
                    
                    if (msgCtx->msgMode == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    continue;
                case 0xD0:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x61;
                    
                    if (msgCtx->msgMode == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    continue;
                case 0xD1:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x62;
                    
                    if (msgCtx->msgMode == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    continue;
                case 0xD2:                          /* switch 1 */
                    
                    if (msgCtx->msgMode == 6) {
                        msgCtx->msgMode = 0x42;
                        msgCtx->textboxEndType = 0x41;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0U);
                        play_sound(0x482EU);
                    }
                    continue;
                case 0xD5:                          /* switch 1 */
                    msgCtx->textboxEndType = 0x63;
                    
                    if (msgCtx->msgMode == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    continue;
                case 0xE0:                          /* switch 1 */
                    if (msgCtx->msgMode == 6) {
                        msgCtx->msgMode = 0x42;
                        msgCtx->textboxEndType = 0x42;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        play_sound(0x482EU);
                    }
                    goto block_217;
                                      /* switch 2 */
                case 0x0:                           /* switch 2 */
                    
                    if ((play->pauseCtx.bombersNotebookOpen != 0) || (temp_v0_8 = msgCtx->textBoxType, (temp_v0_8 == 0xD))) {
                        msgCtx->textColorB = 0;
                        msgCtx->textColorG = msgCtx->textColorB;
                    } else if (temp_v0_8 == 5) {
                        msgCtx->textColorB = 0;
                        msgCtx->textColorG = msgCtx->textColorB;
                    } else {
                        msgCtx->textColorB = 0xFF;
                        msgCtx->textColorG = msgCtx->textColorB;
                    }
                    msgCtx->textColorR = msgCtx->textColorB;
                    temp_v0_9 = msgCtx->textDrawPos;
                    if (temp_v0_9 == (var_s3 + 1)) {
                        msgCtx->textDrawPos = temp_v0_9 + 1;
                    }
block_210:
                    continue;
                case 0x1:                           /* switch 2 */
                case 0x2:                           /* switch 2 */
                case 0x3:                           /* switch 2 */
                case 0x4:                           /* switch 2 */
                case 0x5:                           /* switch 2 */
                case 0x6:                           /* switch 2 */
                case 0x7:                           /* switch 2 */
                case 0x8:                           /* switch 2 */
                    temp_v0_10 = msgCtx->msgMode;
                    
                    if (((s32) temp_v0_10 >= 0x4A) && ((s32) temp_v0_10 < 0x50) && (var_t0 == 2)) {
                        msgCtx->textDrawPos = msgCtx->decodedTextLen;
                        if (msgCtx->unk120D6 != 0) {
                            msgCtx->unk120D4 = msgCtx->unk120D4 + 0x19;
                            if (msgCtx->unk120D4 >= 0x64) {
                                msgCtx->unk120D6 = 0;
                            }
                        } else {
                            msgCtx->unk120D4 = msgCtx->unk120D4 - 0x19;
                            if (msgCtx->unk120D4 < -0x63) {
                                msgCtx->unk120D6 = 1;
                            }
                        }
                        temp_v0_11 = &D_801D07DC[var_t0 - 1];
                        temp_a0 = temp_v0_11->x + msgCtx->unk120D4;
                        if (temp_a0 < 0) {
                            msgCtx->textColorR = 0;
                        } else {
                            msgCtx->textColorR = temp_a0;
                        }
                        temp_v1 = temp_v0_11->y;
                        temp_a0_2 = temp_v1 + msgCtx->unk120D4;
                        if (temp_a0_2 >= 0xFF) {
                            msgCtx->textColorG = temp_v1;
                        } else {
                            msgCtx->textColorG = temp_a0_2;
                        }
                        temp_v1_2 = temp_v0_11->z + msgCtx->unk120D4;
                        if (temp_v1_2 < 0) {
                            msgCtx->textColorB = 0;
                        } else {
                            msgCtx->textColorB = temp_v1_2;
                        }
                    } else if (play->pauseCtx.bombersNotebookOpen != 0) {
                        temp_v0_12 = &D_801D089C[var_t0];
                        msgCtx->textColorR = temp_v0_12->x;
                        msgCtx->textColorG = temp_v0_12->y;
                        msgCtx->textColorB = temp_v0_12->z;
                    } else {
                        temp_v0_13 = msgCtx->textBoxType;
                        if (temp_v0_13 == 1) {
                            temp_v0_14 =  &D_801D07DC[var_t0 - 1];
                            msgCtx->textColorR = temp_v0_14->x;
                            msgCtx->textColorG = temp_v0_14->y;
                            msgCtx->textColorB = temp_v0_14->z;
                        } else if (temp_v0_13 == 0xD) {
                            temp_v0_15 =  &D_801D086C[var_t0 - 1];
                            msgCtx->textColorR = temp_v0_15->x;
                            msgCtx->textColorG = temp_v0_15->y;
                            msgCtx->textColorB = temp_v0_15->z;
                        } else {
                            temp_v0_16 =  &D_801D080C[var_t0 - 1];
                            msgCtx->textColorR = temp_v0_16->x;
                            msgCtx->textColorG = temp_v0_16->y;
                            msgCtx->textColorB = temp_v0_16->z;
                        }
                    }
                    temp_v0_17 = msgCtx->textDrawPos;
                    if (temp_v0_17 == (var_s3 + 1)) {
                        msgCtx->textDrawPos = temp_v0_17 + 1;
                    }
                    continue;
                case 0x20:                          /* switch 2 */
                    msgCtx->textPosX = msgCtx->textPosX + 6;
                    continue;
                case 0x11:                          /* switch 2 */
                    msgCtx->textPosY = msgCtx->textPosY + msgCtx->unk11FFC;
                    /* fallthrough */
                case 0x13:                          /* switch 2 */
                    temp_v1_3 = sp130 + 1;
                    
                    msgCtx->textPosX = msgCtx->unk11F1A[temp_v1_3] + msgCtx->unk11FF8;
                    temp_v0_18 = msgCtx->choiceNum;
                    sp130 = temp_v1_3;
                    if (temp_v0_18 == 1) {
                        if (play->pauseCtx.bombersNotebookOpen == 0) {
                            msgCtx->textPosX = msgCtx->textPosX + 0x10;
                        } else {
                            msgCtx->textPosX = msgCtx->textPosX + 0x32;
                        }
                    } else if (temp_v0_18 == 2) {
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
                case 0x10:                          /* switch 2 */
                case 0x12:                          /* switch 2 */
                    if (msgCtx->msgMode == 6) {
                        if (msgCtx->textboxSkipped == 0) {
                            play_sound(0U);
                            msgCtx->msgMode = 0x41;
                            Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0U);
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

                case 0x17:                          /* switch 2 */
                    if ((msgCtx->textDrawPos == (var_s3 + 1)) && ((msgCtx->msgMode == 6) || (((s32) msgCtx->msgMode >= 0xA) && ((s32) msgCtx->msgMode < 0x27)))) {
                        var_v1 = var_s3;
                        while (true) {
                            temp_v0_20 = msgCtx->decodedBuffer.schar[var_v1];
                            if ((temp_v0_20 != 0x18) && (temp_v0_20 != 0x1A) && (temp_v0_20 != 0x19) && (temp_v0_20 != 0xE0) && (temp_v0_20 != 0x10) && (temp_v0_20 != 0x12)) {
                                var_v1++;
                                continue;
                            }
                            break;
                        }
                        temp_t2_2 = var_v1 - 1;
                        var_s3 = temp_t2_2 & 0xFFFF;
                        msgCtx->textDrawPos = temp_t2_2 + 1;
                    }
                    continue;
                case 0x18:                          /* switch 2 */
                    continue;
                case 0x1B:                          /* switch 2 */
                    temp_v1_4 = var_s3 + 1;
                    if (msgCtx->msgMode == 6) {
                        msgCtx->stateTimer = ((u8) msgCtx->decodedBuffer.schar[temp_v1_4 & 0xFFFF] << 8) | (u8) msgCtx->decodedBuffer.schar[(temp_v1_4 + 1) & 0xFFFF];
                        msgCtx->msgMode = 8;
                    }
                    *gfxP = gfx;
                    return;
                case 0x1C:                          /* switch 2 */
                    if (msgCtx->msgMode == 6) {
                        msgCtx->msgMode = 0x42;
                        temp_v1_5 = var_s3 + 1;
                        if (msgCtx->unk11F0C == 3) {
                            msgCtx->textboxEndType = 0x55;
                        } else {
                            msgCtx->textboxEndType = 0x50;
                        }
                        msgCtx->stateTimer = ((u8) msgCtx->decodedBuffer.schar[temp_v1_5 & 0xFFFF] << 8) | (u8) msgCtx->decodedBuffer.schar[(temp_v1_5 + 1) & 0xFFFF];
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                    *gfxP = gfx;
                    return;
                case 0x1D:                          /* switch 2 */
                    if (msgCtx->msgMode == 6) {
                        temp_v1_6 = var_s3 + 1;
                        msgCtx->msgMode = 0x42;
                        msgCtx->textboxEndType = 0x52;
                        msgCtx->stateTimer = ((u8) msgCtx->decodedBuffer.schar[temp_v1_6 & 0xFFFF] << 8) | (u8) msgCtx->decodedBuffer.schar[(temp_v1_6 + 1) & 0xFFFF];
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                    *gfxP = gfx;
                    return;
                case 0x1E:                          /* switch 2 */
                    temp_v1_7 = var_s3 + 1;
                    var_a1 = var_s3;
                    
                    if (msgCtx->textDrawPos == temp_v1_7) {
                        if (msgCtx->msgMode == 6) {
                            sp50 = var_s3;
                            sp54 = temp_v1_7;
                            play_sound(((msgCtx->decodedBuffer.schar[var_s3+1] << 8) | msgCtx->decodedBuffer.schar[var_s3+2]) & 0xFFFF);
                            var_a1 = sp50;
                        }
                    }
                    if (msgCtx->textDrawPos == temp_v1_7) {
                        msgCtx->textDrawPos = msgCtx->textDrawPos + 2;
                    }
                    var_s3 = (var_a1 + 2) & 0xFFFF;
                    continue;
                case 0x1F:                          /* switch 2 */
                    
                    if ((msgCtx->textDrawPos == (var_s3 + 1)) && (msgCtx->msgMode == 6)) {
                        msgCtx->msgMode = 9;
                        msgCtx->textDelayTimer = (msgCtx->decodedBuffer.schar[var_s3+1] << 8) | msgCtx->decodedBuffer.schar[var_s3+2];
                    }
                    var_s3 = (var_s3 + 2) & 0xFFFF;
                    continue;
                case 0xA:                           /* switch 2 */
                    var_s3 = (var_s3 + 1) & 0xFFFF;
                    temp_v0_21 = (u8) msgCtx->decodedBuffer.schar[var_s3];
                    
                    switch (temp_v0_21) {           /* switch 3 */
                        case 0x0:                   /* switch 3 */
                        case 0x1:                   /* switch 3 */
                        case 0x2:                   /* switch 3 */
                        case 0x3:                   /* switch 3 */
                        case 0x4:                   /* switch 3 */
                        case 0x5:                   /* switch 3 */
                        case 0x6:                   /* switch 3 */
                            msgCtx->textDelay = (u16) temp_v0_21;
                            temp_v0_22 = msgCtx->textDrawPos;
                            if (temp_v0_22 == (var_s3 + 1)) {
                                msgCtx->textDrawPos = temp_v0_22 + 1;
                            }
                            break;
                    }
                    continue;
                case 0x15:                          /* switch 2 */
                case 0xBF:                          /* switch 1 */
                    if (msgCtx->msgMode == 6) {
                        if (msgCtx->textBoxType == 3) {
                            Message_HandleOcarina(play);
                            goto block_217;
                        }
                        msgCtx->msgMode = 0x42;
                        if (msgCtx->textboxEndType == 0) {
                            sp54 = (s32) var_t0;
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
                        goto block_151;
                    }
block_151:
                    *gfxP = gfx;
                    return;
                case 0x1A:                          /* switch 2 */
                    if (msgCtx->msgMode == 6) {
                        play_sound(0U);
                        msgCtx->msgMode = 0x42;
                        msgCtx->textboxEndType = 0x30;
                    }
                    *gfxP = gfx;
                    return;
                case 0x19:                          /* switch 2 */
                    if (msgCtx->msgMode == 6) {
                        msgCtx->msgMode = 0x42;
                        msgCtx->textboxEndType = 0x40;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0U);
                        play_sound(0x482EU);
                    }
                    *gfxP = gfx;
                    return;
                default:                            /* switch 2 */
                //default:                            /* switch 1 */
                    
                    switch (var_t0) {               /* switch 4; irregular */
                        case 0x8169:                /* switch 4 */
                        case 0x8175:                /* switch 4 */
                            msgCtx->textPosX = msgCtx->textPosX - (s32) (6.0f * msgCtx->textCharScale);
                            break;
                        case 0x8145:                /* switch 4 */
                            msgCtx->textPosX = msgCtx->textPosX - (s32) (3.0f * msgCtx->textCharScale);
                            break;
                        case 0x8148:                /* switch 4 */
                        case 0x8149:                /* switch 4 */
                            msgCtx->textPosX = msgCtx->textPosX - (s32) (2.0f * msgCtx->textCharScale);
                            break;
                    }
                    if ((msgCtx->msgMode == 6) && (msgCtx->textDrawPos == (var_s3 + 1))) {
                        sp54 = (s32) var_t0;
                        play_sound(0U);
                    }
                    if (((s32) var_t0 >= 0xB0) && ((s32) var_t0 < 0xBC)) {
                        sp12E = msgCtx->textColorR;
                        sp12C = msgCtx->textColorG;
                        sp12A = msgCtx->textColorB;
                        msgCtx->textColorR = D_801D083C[D_801D08CC[var_t0 - 0xB0]].x;
                        msgCtx->textColorG = D_801D083C[D_801D08CC[var_t0 - 0xB0]].y;
                        msgCtx->textColorB = D_801D083C[D_801D08CC[var_t0 - 0xB0]].z;
                        sp54 = (s32) var_t0;
                        Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
                        var_t0 = (u8) sp54;
                        msgCtx->textColorR = sp12E;
                        msgCtx->textColorG = sp12C;
                        msgCtx->textColorB = sp12A;
                    } else {
                        if ((s32) msgCtx->msgMode >= 0x4D) {
                            temp_v0_24 = msgCtx->decodedTextLen;
                            if ((var_s3 < (temp_v0_24 - 6)) || (var_s3 >= (temp_v0_24 - 4))) {
                                sp54 = (s32) var_t0;
                                Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
                                goto block_181;
                            }
                        } else {
                            sp54 = (s32) var_t0;
                            Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][sp13A], &gfx);
block_181:
                            var_t0 = (u8) sp54;
                        }
                    }
                    sp13A += 0x80;
                    switch (var_t0) {               /* switch 5; irregular */
                        case 0x8144:                /* switch 5 */
                            msgCtx->textPosX = msgCtx->textPosX + (s32) (8.0f * msgCtx->textCharScale);
                            break;
                        case 0x816A:                /* switch 5 */
                        case 0x8176:                /* switch 5 */
                            msgCtx->textPosX = msgCtx->textPosX + (s32) (10.0f * msgCtx->textCharScale);
                            break;
                        case 0x8141:                /* switch 5 */
                        case 0x8142:                /* switch 5 */
                        case 0x8168:                /* switch 5 */
                            msgCtx->textPosX = msgCtx->textPosX + (s32) (12.0f * msgCtx->textCharScale);
                            break;
                        case 0x8194:                /* switch 5 */
                            msgCtx->textPosX = msgCtx->textPosX + (s32) (14.0f * msgCtx->textCharScale);
                            break;
                        case 0x8145:                /* switch 5 */
                            msgCtx->textPosX = msgCtx->textPosX + (s32) (15.0f * msgCtx->textCharScale);
                            break;
                        default:                    /* switch 5 */
                            temp_v1_8 = msgCtx->textboxEndType;
                            if (((temp_v1_8 == 0x62) && (temp_v0_25 = msgCtx->unk120C0, ((var_s3 < temp_v0_25) == 0)) && ((temp_v0_25 + 4) >= var_s3)) || ((temp_v1_8 == 0x63) && (temp_v0_26 = msgCtx->unk120C0, ((var_s3 < temp_v0_26) == 0)) && ((temp_v0_26 + 2) >= var_s3)) || ((temp_v1_8 == 0x60) && (temp_v0_27 = msgCtx->unk120C0, ((var_s3 < temp_v0_27) == 0)) && ((temp_v0_27 + 2) >= var_s3)) || ((temp_v1_8 == 0x61) && (temp_v0_28 = msgCtx->unk120C0, ((var_s3 < temp_v0_28) == 0)) && ((temp_v0_28 + 1) >= var_s3))) {
                                msgCtx->textPosX = msgCtx->textPosX + (s32) (16.0f * msgCtx->textCharScale);
                            } else {
                                msgCtx->textPosX = msgCtx->textPosX + (s32) (*(D_801D0470 + (var_t0) - ' ') * msgCtx->textCharScale);
                            }
                            break;
                    }
                    continue;
            }
    }

block_212:
    temp_v0_29 = msgCtx->textDelayTimer;
    if (temp_v0_29 == 0) {
        msgCtx->textDrawPos = var_s3 + 1;
        msgCtx->textDelayTimer = 0;
        if (msgCtx->msgMode == 9) {
            msgCtx->msgMode = 6;
        }
    } else {
        msgCtx->textDelayTimer = temp_v0_29 - 1;
    }
block_217:
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_nes/Message_DecodeNES.s")
