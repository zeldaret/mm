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

f32 sCreditsFontWidths[144] = {
    8.0f,  8.0f,  6.0f,  9.0f,  9.0f,  14.0f, 12.0f, 3.0f,  7.0f,  7.0f,  7.0f,  9.0f,  4.0f,  6.0f,  4.0f,  9.0f,
    10.0f, 5.0f,  9.0f,  9.0f,  10.0f, 9.0f,  9.0f,  9.0f,  9.0f,  9.0f,  6.0f,  6.0f,  9.0f,  11.0f, 9.0f,  11.0f,
    13.0f, 12.0f, 9.0f,  11.0f, 11.0f, 8.0f,  8.0f,  12.0f, 10.0f, 4.0f,  8.0f,  10.0f, 8.0f,  13.0f, 11.0f, 13.0f,
    9.0f,  13.0f, 10.0f, 10.0f, 9.0f,  10.0f, 11.0f, 15.0f, 11.0f, 10.0f, 10.0f, 7.0f,  10.0f, 7.0f,  10.0f, 9.0f,
    5.0f,  8.0f,  9.0f,  8.0f,  9.0f,  9.0f,  6.0f,  9.0f,  8.0f,  4.0f,  6.0f,  8.0f,  4.0f,  12.0f, 9.0f,  9.0f,
    9.0f,  9.0f,  7.0f,  8.0f,  7.0f,  8.0f,  9.0f,  12.0f, 8.0f,  9.0f,  8.0f,  7.0f,  5.0f,  7.0f,  10.0f, 10.0f,
    12.0f, 12.0f, 12.0f, 12.0f, 11.0f, 8.0f,  8.0f,  8.0f,  6.0f,  6.0f,  13.0f, 13.0f, 10.0f, 10.0f, 10.0f, 9.0f,
    8.0f,  8.0f,  8.0f,  8.0f,  8.0f,  9.0f,  9.0f,  9.0f,  9.0f,  6.0f,  9.0f,  9.0f,  9.0f,  9.0f,  9.0f,  14.0f,
    14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f, 14.0f,
};

void Message_DrawTextCredits(PlayState* play, Gfx** gfxP) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 pad;
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

    if (msgCtx->textBoxType == TEXTBOX_TYPE_5) {
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
                        Audio_PlaySfx(NA_SE_NONE);
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
                    Audio_PlaySfx(NA_SE_NONE);
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
                        character = msgCtx->decodedBuffer.schar[j];
                        if (character == 6) {
                            j += 2;
                            continue;
                        }
                        if ((character != 9) && (character != 0xA) && (character != 0xB) && (character != 0xC) &&
                            (character != 0xD) && (character != 4) && (character != 2)) {
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
                    Audio_PlaySfx(sfxHi | msgCtx->decodedBuffer.schar[i + 2]);
                }
                i += 2;
                break;

            case 0x13: // remnant of MESSAGE_ITEM_ICON
                break;

            case 0x15: // MESSAGE_BACKGROUND
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Audio_PlaySfx(NA_SE_NONE);
                }
                gDPPipeSync(gfx++);
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);

                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1000, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 1) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0,
                                    0, 1 << 10, 1 << 10);

                gDPLoadTextureBlock_4b(gfx++, msgCtx->textboxSegment + 0x1900, G_IM_FMT_I, 96, 48, 0,
                                       G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
                                       G_TX_NOLOD, G_TX_NOLOD);
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 1) << 2,
                                    (msgCtx->textPosX + 0xC2) << 2, (msgCtx->unk12012 + 0x31) << 2, 0, 0, 0, 1 << 10,
                                    1 << 10);

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
                        Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                        Font_LoadMessageBoxEndIcon(font, 1);
                        if (play->csCtx.state == CS_STATE_IDLE) {
                            func_8011552C(play, DO_ACTION_RETURN);
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
                    if (play->csCtx.state == CS_STATE_IDLE) {
                        func_8011552C(play, DO_ACTION_RETURN);
                    }
                }
                *gfxP = gfx;
                return;

            case 0xA: // MESSAGE_PERSISTENT
                if (msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) {
                    Audio_PlaySfx(NA_SE_NONE);
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
                    Audio_PlaySfx(NA_SE_SY_MESSAGE_END);
                }
                *gfxP = gfx;
                return;

            default:
                if ((msgCtx->msgMode == MSGMODE_TEXT_DISPLAYING) && ((i + 1) == msgCtx->textDrawPos) &&
                    (msgCtx->textDelayTimer == msgCtx->textDelay)) {
                    Audio_PlaySfx(NA_SE_NONE);
                }
                Message_DrawTextChar(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                charTexIndex += FONT_CHAR_TEX_SIZE;

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

void Message_DecodeCredits(PlayState* play) {
    u16 curChar;
    s16 loadChar;
    s16 i;
    s16 playerNameLen;
    s16 decodedBufPos = 0;
    s16 charOffset;
    f32 timeInSeconds;
    s16 numLines = 0;
    s16 value;
    s16 digits[4];
    s32 charTexIdx = 0;
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &play->msgCtx.font;

    msgCtx->nextTextId = 0xFFFF;

    while (true) {
        curChar = font->msgBuf.schar[msgCtx->msgBufPos];
        msgCtx->decodedBuffer.schar[decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos];

        if ((curChar == 4) || (curChar == 7) || (curChar == 0xC) || (curChar == 0xB) || (curChar == 2)) {
            // Textbox decoding ends with any of the above text control characters
            msgCtx->msgMode = MSGMODE_TEXT_DISPLAYING;
            msgCtx->textDrawPos = 1;
            msgCtx->unk11FFA = msgCtx->textboxY + 8;

            if (msgCtx->textBoxType != TEXTBOX_TYPE_4) {
                if (numLines == 0) {
                    msgCtx->unk11FFA = msgCtx->textboxY + 26;
                } else if (numLines == 1) {
                    msgCtx->unk11FFA = msgCtx->textboxY + 20;
                } else if (numLines == 2) {
                    msgCtx->unk11FFA = msgCtx->textboxY + 16;
                }
            }

            if (curChar == 7) {
                value = font->msgBuf.schar[msgCtx->msgBufPos + 1];
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 1];
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 2];
                value <<= 8;
                msgCtx->nextTextId = msgCtx->decodedBuffer.schar[decodedBufPos] | value;
            }

            if (curChar == 0xC) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 1];
                msgCtx->msgBufPos += 2;
            }

            msgCtx->decodedTextLen = decodedBufPos;

            if (msgCtx->textboxSkipped) {
                msgCtx->textDrawPos = msgCtx->decodedTextLen;
            }
            break;
        } else if (curChar == 0xF) {
            // Substitute the player name control character for the file's player name.
            for (playerNameLen = ARRAY_COUNT(gSaveContext.save.saveInfo.playerData.playerName); playerNameLen > 0;
                 playerNameLen--) {
                if (gSaveContext.save.saveInfo.playerData.playerName[playerNameLen - 1] != 0x3E) {
                    break;
                }
            }

            for (i = 0; i < playerNameLen; i++) {
                curChar = gSaveContext.save.saveInfo.playerData.playerName[i];
                if (curChar == 62) {
                    curChar = ' ';
                } else if (curChar == 64) {
                    curChar = '.';
                } else if (curChar == 63) {
                    curChar = '-';
                } else if (curChar < 10) {
                    charOffset = curChar;
                    curChar = '0' + charOffset;
                } else if (curChar < 36) {
                    charOffset = curChar;
                    curChar = 'A' - 10 + charOffset;
                } else if (curChar < 62) {
                    charOffset = curChar;
                    curChar = 'a' - 36 + charOffset;
                }

                if (curChar != ' ') {
                    Font_LoadCharNES(play, curChar - ' ', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                }
                msgCtx->decodedBuffer.schar[decodedBufPos] = curChar;
                decodedBufPos++;
            }
            decodedBufPos--;
        } else if ((curChar == 0x16) || (curChar == 0x17)) {
            digits[0] = digits[1] = digits[2] = 0;
            if (curChar == 0x17) {
                digits[3] = gSaveContext.timerCurTimes[TIMER_ID_MINIGAME_2];
            } else {
                digits[3] = gSaveContext.timerCurTimes[TIMER_ID_GORON_RACE_UNUSED];
            }

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
                Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                charTexIdx += FONT_CHAR_TEX_SIZE;
                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                decodedBufPos++;
                if (i == 1) {
                    Font_LoadCharNES(play, '"' - ' ', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                    decodedBufPos++;
                } else if (i == 3) {
                    Font_LoadCharNES(play, '"' - ' ', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                }
            }

        } else if (curChar == 0x18) {
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
                    Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    decodedBufPos++;
                }
            }
            decodedBufPos--;
        } else if (curChar != 0x19) {
            if (curChar == 0x1D) {
                digits[0] = 0;
                digits[1] = gSaveContext.minigameScore;

                while (digits[1] >= 10) {
                    digits[0]++;
                    digits[1] -= 10;
                }

                for (i = 0; i < 2; i++) {
                    if ((i == 1) || (digits[i] != 0)) {
                        Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                        charTexIdx += FONT_CHAR_TEX_SIZE;
                        msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                        decodedBufPos++;
                    }
                }
                decodedBufPos--;
            } else if (curChar == 0x1E) {
                value = HIGH_SCORE((u8)font->msgBuf.schar[++msgCtx->msgBufPos]);
                if ((font->msgBuf.schar[msgCtx->msgBufPos] & 0xFF) == HS_FISHING) {
                    if (LINK_AGE_IN_YEARS == YEARS_CHILD) {
                        value &= 0x7F;
                    } else {
                        value =
                            (s16)((HIGH_SCORE((u8)font->msgBuf.schar[msgCtx->msgBufPos]) & 0xFF000000) >> 0x18) & 0x7F;
                    }
                    value = SQ((f32)value) * 0.0036f + 0.5f;
                }
                switch (font->msgBuf.schar[msgCtx->msgBufPos] & 0xFF) {
                    case 0:
                    case 1:
                    case 2:
                        digits[0] = digits[1] = digits[2] = 0;
                        digits[3] = value;

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
                                Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                                msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                                charTexIdx += FONT_CHAR_TEX_SIZE;
                                decodedBufPos++;
                            }
                        }
                        decodedBufPos--;
                        break;

                    case 3:
                    case 4:
                    case 6:
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
                            Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                            charTexIdx += FONT_CHAR_TEX_SIZE;
                            msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                            decodedBufPos++;
                            if (i == 1) {
                                Font_LoadCharNES(play, '"' - ' ', charTexIdx);
                                charTexIdx += FONT_CHAR_TEX_SIZE;
                                msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                                decodedBufPos++;
                            } else if (i == 3) {
                                Font_LoadCharNES(play, '"' - ' ', charTexIdx);
                                charTexIdx += FONT_CHAR_TEX_SIZE;
                                msgCtx->decodedBuffer.schar[decodedBufPos] = '"';
                            }
                        }
                        break;

                    default:
                        break;
                }
            } else if (curChar == 0x1F) {
                digits[0] = 0;
                timeInSeconds = TIME_TO_MINUTES_F(CURRENT_TIME);

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
                    Font_LoadCharNES(play, digits[i] + '0' - ' ', charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                    msgCtx->decodedBuffer.schar[decodedBufPos] = digits[i] + '0';
                    decodedBufPos++;
                    if (i == 1) {
                        Font_LoadCharNES(play, ':' - ' ', charTexIdx);
                        charTexIdx += FONT_CHAR_TEX_SIZE;
                        msgCtx->decodedBuffer.schar[decodedBufPos] = ':';
                        decodedBufPos++;
                    }
                }

                decodedBufPos--;
            } else if (curChar == 0x13) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[msgCtx->msgBufPos + 1];
                Message_LoadItemIcon(play, font->msgBuf.schar[msgCtx->msgBufPos + 1], msgCtx->textboxY + 10);
            } else if (curChar == 0x15) {
                DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1000,
                                    (uintptr_t)SEGMENT_ROM_START(message_texture_static) + 0x900, 0x900);
                DmaMgr_SendRequest0(msgCtx->textboxSegment + 0x1900,
                                    (uintptr_t)SEGMENT_ROM_START(message_texture_static) + 0x900, 0x900);
                msgCtx->msgBufPos += 3;
                msgCtx->unk12012 = msgCtx->textboxY + 8;
                numLines = 2;
            } else if (curChar == 5) {
                msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
            } else if (curChar == 1) {
                numLines++;
            } else if ((curChar != 8) && (curChar != 9) && (curChar != 0xD) && (curChar != 0x10) && (curChar != 0xA) &&
                       (curChar != 0x1A)) {
                if (curChar == 0xE) {
                    msgCtx->textFade = true;
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
                } else if (curChar == 0x11) {
                    msgCtx->textFade = true;
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
                } else if ((curChar == 6) || (curChar == 0x14)) {
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos] & 0xFF;
                } else if (curChar == 0x12) {
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
                    msgCtx->decodedBuffer.schar[++decodedBufPos] = font->msgBuf.schar[++msgCtx->msgBufPos];
                } else if (curChar == 0x1B) {
                    msgCtx->choiceNum = 2;
                } else if (curChar == 0x1C) {
                    msgCtx->choiceNum = 3;
                } else if (curChar != ' ') {
                    Font_LoadCharNES(play, curChar, charTexIdx);
                    charTexIdx += FONT_CHAR_TEX_SIZE;
                }
            }
        }

        decodedBufPos++;
        msgCtx->msgBufPos++;
    }
}
