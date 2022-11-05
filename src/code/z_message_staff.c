#include "global.h"
#include "message_data_static.h"

void Message_FindCreditsMessage(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->messageTableStaff;
    const char* segment = msgEntry->segment;
    const char* foundSegment;
    const char* nextSegment;

    while (msgEntry->textId != 0xFFFF) {
        if (msgEntry->textId == textId) {
            foundSegment = msgEntry->segment;
            font->charBuf[font->unk_11D88][0] = msgEntry->typePos;
            msgEntry++;
            nextSegment = msgEntry->segment;
            font->messageStart = foundSegment - segment;
            font->messageEnd = nextSegment - foundSegment;
            break;
        }
        msgEntry++;
    }
}

// clang-format off
f32 sCreditsFontWidths[144] = {
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
    10.0f,
    12.0f,
    12.0f,
    12.0f,
    12.0f,
    11.0f,
    8.0f,
    8.0f,
    8.0f,
    6.0f,
    6.0f,
    13.0f,
    13.0f,
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
    6.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
    9.0f,
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
    14.0f,
};
// clang-format on

#ifdef NON_MATCHING
// Message_DrawTextCredits // https://decomp.me/scratch/yc8Or
void Message_DrawTextCredits(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 lookAheadCharacter;
    u16 j;
    u16 i;
    u16 sfxHi;
    char character;
    u16 charTexIndex;
    Font* font = &msgCtx->font;
    Gfx* gfx = *gfxP;

    msgCtx->textPosX = msgCtx->unk11FF8;

    if (!msgCtx->textIsCredits) {
        msgCtx->textPosY = msgCtx->unk11FFA;
    } else {
        msgCtx->textPosY = 48;
    }

    if (msgCtx->textBoxType == 5) {
        msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 0;
    } else {
        msgCtx->textColorR = msgCtx->textColorG = msgCtx->textColorB = 255;
    }

    charTexIndex = 0;

    for (i = 0; i < msgCtx->textDrawPos; i++) {
        character = msgCtx->decodedBuffer.schar[i];

        switch (character) {
            case 0x1: // MESSAGE_NEWLINE
                msgCtx->textPosX = msgCtx->unk11FF8;
                if ((msgCtx->choiceNum == 1) || (msgCtx->choiceNum == 3)) {
                    msgCtx->textPosX += 32;
                }
                if ((msgCtx->choiceNum == 2) && (msgCtx->textPosY != msgCtx->unk11FFA)) {
                    msgCtx->textPosX += 32;
                }
                msgCtx->textPosY += msgCtx->unk11FFC;
                break;

            case 0x5: // Remnant of MESSAGE_COLOR
                break;

            case ' ':
                msgCtx->textPosX += 6;
                break;

            case 0x4: // MESSAGE_BOX_BREAK
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    if (!msgCtx->textboxSkipped) {
                        play_sound(0);
                        msgCtx->msgMode = MSGMODE_TEXT_AWAIT_NEXT;
                        Font_LoadMessageBoxEndIcon(font, 0);
                    } else {
                        msgCtx->msgMode = MSGMODE_TEXT_NEXT_MSG;
                        msgCtx->textUnskippable = false;
                        msgCtx->msgBufPos++;
                    }
                }
                *gfxP = gfx;
                return;

            case 0x6: // MESSAGE_SHIFT
                msgCtx->textPosX += msgCtx->decodedBuffer.schar[++i];
                break;

            case 0x7: // MESSAGE_TEXTID
                msgCtx->textboxEndType = TEXTBOX_ENDTYPE_20;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    play_sound(0);
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    Font_LoadMessageBoxEndIcon(font, 0);
                }
                *gfxP = gfx;
                return;

            case 0x8: // MESSAGE_QUICKTEXT_ENABLE
                if (((i + 1) == msgCtx->textDrawPos) &&
                    ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) ||
                     ((msgCtx->msgMode >= MSGMODE_OCARINA_STARTING) && (msgCtx->msgMode <= MSGMODE_26)))) {
                    j = i;
                    while (true) {
                        lookAheadCharacter = msgCtx->decodedBuffer.schar[j];
                        if (lookAheadCharacter == 6) {
                            j += 2;
                            continue;
                        }
                        if ((lookAheadCharacter != 9) && (lookAheadCharacter != 0xA) && (lookAheadCharacter != 0xB) &&
                            (lookAheadCharacter != 0xC) && (lookAheadCharacter != 0xD) && (lookAheadCharacter != 4) &&
                            (lookAheadCharacter != 2)) {
                            j++;
                            continue;
                        }
                        break;
                    }
                    i = j - 1;
                    msgCtx->textDrawPos = i + 1;
                }
                // fallthrough
            case 0x9: // MESSAGE_QUICKTEXT_DISABLE
                break;

            case 0xD: // MESSAGE_AWAIT_BUTTON_PRESS
                if ((i + 1) == msgCtx->textDrawPos) {
                    if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                        msgCtx->msgMode = MSGMODE_TEXT_AWAIT_INPUT;
                        Font_LoadMessageBoxEndIcon(font, 0);
                    }
                    *gfxP = gfx;
                    return;
                }
                break;

            case 0xC: // MESSAGE_BOX_BREAK_DELAYED
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->stateTimer = msgCtx->decodedBuffer.schar[++i];
                    msgCtx->msgMode = MSGMODE_TEXT_DELAYED_BREAK;
                }
                *gfxP = gfx;
                return;

            case 0x11: // MESSAGE_FADE2
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_50;
                    msgCtx->stateTimer = msgCtx->decodedBuffer.schar[++i] << 8;
                    msgCtx->stateTimer |= msgCtx->decodedBuffer.schar[++i];
                }
                *gfxP = gfx;
                return;

            case 0x12: // MESSAGE_SFX
                if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) && !msgCtx->messageHasSetSfx) {
                    msgCtx->messageHasSetSfx = true;
                    sfxHi = msgCtx->decodedBuffer.schar[i + 1];
                    sfxHi = sfxHi << 8;
                    play_sound(sfxHi | msgCtx->decodedBuffer.schar[i + 2]);
                }
                i += 2;
                break;

            case 0x13: // remnant of MESSAGE_ITEM_ICON
                break;

            case 0x15: // MESSAGE_BACKGROUND
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    play_sound(0);
                }
                // temp_t7_3 = gfx;
                // gfx = temp_t7_3 + 8;
                // temp_t7_3->words.w1 = 0;
                // temp_t7_3->words.w0 = 0xE7000000;
                gDPPipeSync(gfx++);

                // temp_t9 = gfx;
                // gfx = temp_t9 + 8;
                // temp_t9->words.w0 = 0xFC119623;
                // temp_t9->words.w1 = 0xFF2FFFFF;
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                // temp_v0_7 = gfx;
                // gfx = temp_v0_7 + 8;
                // temp_v0_7->words.w0 = 0xFA000000;
                // temp_v0_7->words.w1 = msgCtx->textColorAlpha & 0xFF;
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);

                // temp_v0_8 = gfx;
                // temp_t7_4 = temp_v0_8 + 8;
                // gfx = temp_t7_4;
                // temp_v0_8->words.w0 = 0xFD900000;
                // temp_v0_8->words.w1 = (u32)msgCtx->textboxSegment + 0x1000;
                // gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)msgCtx->textboxSegment + 0x1000);

                // gfx = temp_t7_4 + 8;
                // temp_t7_4->words.w1 = 0x07000000;
                // temp_t7_4->words.w0 = 0xF5900000;

                // temp_t7_5 = gfx;
                // gfx = temp_t7_5 + 8;
                // temp_t7_5->words.w1 = 0;
                // temp_t7_5->words.w0 = 0xE6000000;
                // temp_t6 = gfx;
                // gfx = temp_t6 + 8;
                // temp_t6->words.w0 = 0xF3000000;
                // temp_t6->words.w1 = 0x0747F156;
                // temp_t6_2 = gfx;
                // gfx = temp_t6_2 + 8;
                // temp_t6_2->words.w1 = 0;
                // temp_t6_2->words.w0 = 0xE7000000;
                // temp_t8 = gfx;
                // gfx = temp_t8 + 8;
                // temp_t8->words.w1 = 0;
                // temp_t8->words.w0 = 0xF5800C00;
                // temp_t7_6 = gfx;
                // gfx = temp_t7_6 + 8;
                // temp_t7_6->words.w0 = 0xF2000000;
                // temp_t7_6->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_9 = gfx;
                ////temp_t8_2 = temp_v0_9 + 8;
                // temp_t8_2 = temp_v0_9 + 1;
                // gfx = temp_t8_2;
                // temp_v0_9->words.w0 = ((((msgCtx->textPosX + 0x61) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF); temp_v0_9->words.w1 = ((((msgCtx->textPosX + 1) * 4) &
                // 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF); gfx = temp_t8_2 + 8; temp_t8_2->words.w0 =
                // 0xE1000000; temp_t8_2->words.w1 = 0; temp_t7_7 = gfx; gfx = temp_t7_7 + 8; temp_t7_7->words.w0 =
                // 0xF1000000; temp_t7_7->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 1) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);

                // temp_v0_10 = gfx;
                // temp_t8_3 = temp_v0_10 + 8;
                // gfx = temp_t8_3;
                // temp_v0_10->words.w0 = 0xFD900000;
                // temp_v0_10->words.w1 = (u32)msgCtx->textboxSegment + 0x1900;
                // gfx = temp_t8_3 + 8;
                // temp_t8_3->words.w1 = 0x07000000;
                // temp_t8_3->words.w0 = 0xF5900000;
                // temp_t8_4 = gfx;
                // gfx = temp_t8_4 + 8;
                // temp_t8_4->words.w1 = 0;
                // temp_t8_4->words.w0 = 0xE6000000;
                // temp_t7_8 = gfx;
                // gfx = temp_t7_8 + 8;
                // temp_t7_8->words.w0 = 0xF3000000;
                // temp_t7_8->words.w1 = 0x0747F156;
                // temp_t7_9 = gfx;
                // gfx = temp_t7_9 + 8;
                // temp_t7_9->words.w1 = 0;
                // temp_t7_9->words.w0 = 0xE7000000;
                // temp_t9_2 = gfx;
                // gfx = temp_t9_2 + 8;
                // temp_t9_2->words.w1 = 0;
                // temp_t9_2->words.w0 = 0xF5800C00;
                // temp_t8_5 = gfx;
                // gfx = temp_t8_5 + 8;
                // temp_t8_5->words.w0 = 0xF2000000;
                // temp_t8_5->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_11 = gfx;
                // temp_t9_3 = temp_v0_11 + 8;
                // gfx = temp_t9_3;
                // temp_v0_11->words.w0 = ((((msgCtx->textPosX + 0xC2) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF); temp_v0_11->words.w1 = ((((msgCtx->textPosX + 0x61) * 4) &
                // 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF); gfx = temp_t9_3 + 8; temp_t9_3->words.w0 =
                // 0xE1000000; temp_t9_3->words.w1 = 0; temp_t8_6 = gfx; gfx = temp_t8_6 + 8; temp_t8_6->words.w0 =
                // 0xF1000000; temp_t8_6->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0xC2) << 2, (msgCtx->unk12012 + 0x31) << 2, 0, 0, 0, 1 << 10,
                                    1 << 10);

                // temp_t8_7 = gfx;
                // gfx = temp_t8_7 + 8;
                // temp_t8_7->words.w1 = 0;
                // temp_t8_7->words.w0 = 0xE7000000;
                // temp_v0_12 = gfx;
                // gfx = temp_v0_12 + 8;
                // temp_v0_12->words.w0 = 0xFA000000;
                // temp_v0_12->words.w1 = (msgCtx->textColorAlpha & 0xFF) | 0xFF3C0000;
                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);

                // temp_v0_13 = gfx;
                // temp_t9_4 = temp_v0_13 + 8;
                // gfx = temp_t9_4;
                // temp_v0_13->words.w0 = 0xFD900000;
                // temp_v0_13->words.w1 = (u32)msgCtx->textboxSegment + 0x1000;
                // gfx = temp_t9_4 + 8;
                // temp_t9_4->words.w1 = 0x07000000;
                // temp_t9_4->words.w0 = 0xF5900000;
                // temp_t9_5 = gfx;
                // gfx = temp_t9_5 + 8;
                // temp_t9_5->words.w1 = 0;
                // temp_t9_5->words.w0 = 0xE6000000;
                // temp_t8_8 = gfx;
                // gfx = temp_t8_8 + 8;
                // temp_t8_8->words.w0 = 0xF3000000;
                // temp_t8_8->words.w1 = 0x0747F156;
                // temp_t8_9 = gfx;
                // gfx = temp_t8_9 + 8;
                // temp_t8_9->words.w1 = 0;
                // temp_t8_9->words.w0 = 0xE7000000;
                // temp_t6_3 = gfx;
                // gfx = temp_t6_3 + 8;
                // temp_t6_3->words.w1 = 0;
                // temp_t6_3->words.w0 = 0xF5800C00;
                // temp_t9_6 = gfx;
                // gfx = temp_t9_6 + 8;
                // temp_t9_6->words.w0 = 0xF2000000;
                // temp_t9_6->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_14 = gfx;
                // gfx = temp_v0_14 + 8;
                // temp_v0_14->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF); temp_v0_14->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF)
                // << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF); temp_t8_10 = gfx; gfx = temp_t8_10 + 8;
                // temp_t8_10->words.w0 = 0xE1000000; temp_t8_10->words.w1 = 0; temp_t7_10 = gfx; gfx = temp_t7_10 + 8;
                // temp_t7_10->words.w0 = 0xF1000000; temp_t7_10->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0x60) << 2,
                                    (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 1 << 10, 1 << 10);

                // temp_v0_15 = gfx;
                // temp_t8_11 = temp_v0_15 + 8;
                // gfx = temp_t8_11;
                // temp_v0_15->words.w0 = 0xFD900000;
                // temp_v0_15->words.w1 = (u32)msgCtx->textboxSegment + 0x1900;
                // gfx = temp_t8_11 + 8;
                // temp_t8_11->words.w1 = 0x07000000;
                // temp_t8_11->words.w0 = 0xF5900000;
                // temp_t8_12 = gfx;
                // gfx = temp_t8_12 + 8;
                // temp_t8_12->words.w1 = 0;
                // temp_t8_12->words.w0 = 0xE6000000;
                // temp_t7_11 = gfx;
                // gfx = temp_t7_11 + 8;
                // temp_t7_11->words.w0 = 0xF3000000;
                // temp_t7_11->words.w1 = 0x0747F156;
                // temp_t7_12 = gfx;
                // gfx = temp_t7_12 + 8;
                // temp_t7_12->words.w1 = 0;
                // temp_t7_12->words.w0 = 0xE7000000;
                // temp_t6_4 = gfx;
                // gfx = temp_t6_4 + 8;
                // temp_t6_4->words.w1 = 0;
                // temp_t6_4->words.w0 = 0xF5800C00;
                // temp_t8_13 = gfx;
                // gfx = temp_t8_13 + 8;
                // temp_t8_13->words.w0 = 0xF2000000;
                // temp_t8_13->words.w1 = 0x17C0BC;
                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);

                // temp_v0_16 = gfx;
                // gfx = temp_v0_16 + 8;
                // temp_v0_16->words.w0 = ((((msgCtx->textPosX + 0xC0) * 4) & 0xFFF) << 0xC) | 0xE4000000 |
                // (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF); temp_v0_16->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) &
                // 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF); temp_t8_14 = gfx; gfx = temp_t8_14 + 8;
                // temp_t8_14->words.w0 = 0xE1000000;
                // temp_t8_14->words.w1 = 0;
                // temp_t7_13 = gfx;
                // gfx = temp_t7_13 + 8;
                // temp_t7_13->words.w0 = 0xF1000000;
                // temp_t7_13->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, msgCtx->unk12012 << 2,
                                    (msgCtx->textPosX + 0xC0) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);

                // temp_t7_14 = gfx;
                // gfx = temp_t7_14 + 8;
                // temp_t7_14->words.w1 = 0;
                // temp_t7_14->words.w0 = 0xE7000000;
                // temp_t9_7 = gfx;
                // gfx = temp_t9_7 + 8;
                // temp_t9_7->words.w0 = 0xFCFF97FF;
                // temp_t9_7->words.w1 = 0xFF2DFEFF;
                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0,
                                  PRIMITIVE, 0);
                msgCtx->textPosX += 0x20;
                break;

            case 0x14: // MESSAGE_TEXT_SPEED
                msgCtx->textDelay = msgCtx->decodedBuffer.schar[++i];
                break;

            case 0x1A: // MESSAGE_UNSKIPPABLE
                msgCtx->textUnskippable = true;
                break;

            case 0x1B: // MESSAGE_TWO_CHOICE
                msgCtx->textboxEndType = TEXTBOX_ENDTYPE_10;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    msgCtx->choiceIndex = 0;
                    Font_LoadMessageBoxEndIcon(font, 2);
                }
                break;

            case 0x1C: // MESSAGE_THREE_CHOICE
                msgCtx->textboxEndType = TEXTBOX_ENDTYPE_11;
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->choiceTextId = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    msgCtx->choiceIndex = 0;
                    Font_LoadMessageBoxEndIcon(font, 2);
                }
                break;

            case 0x2: // MESSAGE_END
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_00) {
                        play_sound(NA_SE_SY_MESSAGE_END);
                        Font_LoadMessageBoxEndIcon(font, 1);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                }
                *gfxP = gfx;
                return;

            case 0x10: // MESSAGE_OCARINA
                if ((i + 1) == msgCtx->textDrawPos) {
                    Message_HandleOcarina(play);
                    *gfxP = gfx;
                    return;
                }
                break;

            case 0xE: // MESSAGE_FADE
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_50;
                    msgCtx->stateTimer = msgCtx->decodedBuffer.schar[++i];
                    Font_LoadMessageBoxEndIcon(font, 1);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxP = gfx;
                return;

            case 0xA: // MESSAGE_PERSISTENT
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    play_sound(0);
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_30;
                }
                *gfxP = gfx;
                return;

            case 0xB: // MESSAGE_EVENT
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    msgCtx->msgMode = MSGMODE_TEXT_DONE;
                    msgCtx->textboxEndType = TEXTBOX_ENDTYPE_40;
                    Font_LoadMessageBoxEndIcon(font, 0);
                    play_sound(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            default:
                if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) && ((i + 1) == msgCtx->textDrawPos) &&
                    (msgCtx->textDelayTimer == msgCtx->textDelay)) {
                    play_sound(0);
                }
                Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                charTexIndex += 0x80;

                msgCtx->textPosX += (s32)(sCreditsFontWidths[character - ' '] * msgCtx->textCharScale);
                break;
        }
    }

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos = i + 1;
        msgCtx->textDelayTimer = msgCtx->textDelay;
    } else {
        msgCtx->textDelayTimer--;
    }

    *gfxP = gfx;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/Message_DrawTextCredits.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/Message_DecodeCredits.s")
