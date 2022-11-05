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

extern f32 sFontWidths[];

#ifdef NON_MATCHING
// Message_DrawTextCredits // https://decomp.me/scratch/yc8Or
void Message_DrawTextCredits(PlayState* play, Gfx** gfxp) {
    MessageContext* msgCtx = &play->msgCtx;
    u16 lookAheadCharacter;
    u16 j;// var_a0;
    u16 i;// var_t0; // sp126
    u16 sfxHi;
    char character; //temp_v0;
    u16 charTexIndex; //sp120;
    Font* font = &play->msgCtx.font; // temp_a3 = &play->msgCtx.font; // sp50
    Gfx* gfx = *gfxp; // sp118;

    play->msgCtx.textPosX = play->msgCtx.unk11FF8;

    if (!play->msgCtx.textIsCredits) {
        msgCtx->textPosY = msgCtx->unk11FFA;
    } else {
        msgCtx->textPosY = 48;
    }

    if (msgCtx->textBoxType == 5) {
        msgCtx->unk12018 =msgCtx->unk1201A = msgCtx->unk1201C = 0;
    } else {
        msgCtx->unk12018 =msgCtx->unk1201A = msgCtx->unk1201C = 0xFF;
    }

    charTexIndex = 0;

    for (i = 0; i < msgCtx->textDrawPos; i++) {
        character = msgCtx->decodedBuffer.schar[i];

        switch (character) {
            case 0x1:
                msgCtx->textPosX = msgCtx->unk11FF8;
                if ((msgCtx->unk12022 == 1) || (msgCtx->unk12022 == 3)) {
                    msgCtx->textPosX += 0x20;
                }
                if ((msgCtx->unk12022 == 2) && (msgCtx->textPosY != msgCtx->unk11FFA)) {
                    msgCtx->textPosX += 0x20;
                }
                msgCtx->textPosY += msgCtx->unk11FFC;
                break;

            case 0x5:
                break;

            case 0x20:
                msgCtx->textPosX += 6;
                break;

            case 0x4:
                if (msgCtx->msgMode == 6) {
                    if (msgCtx->unk12094 == 0) {
                        play_sound(0);
                        msgCtx->msgMode = 0x41;
                        Font_LoadMessageBoxEndIcon(font, 0U);
                    } else {
                        msgCtx->msgMode = 4;
                        msgCtx->textUnskippable = 0;
                        msgCtx->msgBufPos++;
                    }
                }
                *gfxp = gfx;
                return;
            case 0x6:
                msgCtx->textPosX += msgCtx->decodedBuffer.schar[++i];
                break;

            case 0x7:
                msgCtx->textboxEndType = 0x20;
                if (msgCtx->msgMode == 6) {
                    play_sound(0U);
                    msgCtx->msgMode = 0x42;
                    Font_LoadMessageBoxEndIcon(font, 0U);
                }
                *gfxp = gfx;
                return;
            case 0x8:
                //if (msgCtx && msgCtx) {}

                if ((i + 1) == msgCtx->textDrawPos) {
                    if ((msgCtx->msgMode == 6) || ((msgCtx->msgMode >= 0xA) && (msgCtx->msgMode < 0x27))) {
                        j = i;
    //loop_32:
                        while (true) {
                            lookAheadCharacter = msgCtx->decodedBuffer.schar[j];
                            if (lookAheadCharacter == 6) {
                                j += 2;
                                //goto loop_32;
                                continue;
                            }
                            if ((lookAheadCharacter != 9) && (lookAheadCharacter != 0xA) && (lookAheadCharacter != 0xB) && (lookAheadCharacter != 0xC) && (lookAheadCharacter != 0xD) && (lookAheadCharacter != 4) && (lookAheadCharacter != 2)) {
                                j++;
                                //goto loop_32;
                                continue;
                            }
                            break;
                        }
                        i = j - 1;
                        msgCtx->textDrawPos = i + 1;
                    }
                }
                /* fallthrough */
            case 0x9:
                break;
            case 0xD:
                if ((i + 1) == msgCtx->textDrawPos) {
                    if (msgCtx->msgMode == 6) {
                        msgCtx->msgMode = 7;
                        Font_LoadMessageBoxEndIcon(font, 0U);
                    }
                    *gfxp = gfx;
                    return;
                }
                break;
            case 0xC:
                if (msgCtx->msgMode == 6) {
                    msgCtx->stateTimer = msgCtx->decodedBuffer.schar[++i];
                    msgCtx->msgMode = 8;
                }
                *gfxp = gfx;
                return;
            case 0x11:
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x50;
                    msgCtx->stateTimer = msgCtx->decodedBuffer.schar[++i] << 8;
                    msgCtx->stateTimer |= msgCtx->decodedBuffer.schar[++i];
                }
                *gfxp = gfx;
                return;
            case 0x12:
                if ((msgCtx->msgMode == 6) && (msgCtx->unk12092 == 0)) {
                    #if 0
                    temp_t7_2 = msgCtx + i;
                    msgCtx->unk12092 = 1;
                    sp48 = i;
                    play_sound((temp_t7_2->unk_11F26 | (temp_t7_2->unk_11F25 << 8)) & 0xFFFF);
                    var_a1 = sp48;
                    #endif
                    msgCtx->unk12092 = 1;
                    sfxHi = msgCtx->decodedBuffer.schar[1+i];
                    sfxHi <<= 8;
                    play_sound(sfxHi | msgCtx->decodedBuffer.schar[2+i]);
                }
                i += 2;
                break;
            case 0x13:
                break;
            case 0x15:
                if (msgCtx->msgMode == 6) {
                    play_sound(0U);
                }
                //temp_t7_3 = gfx;
                //gfx = temp_t7_3 + 8;
                //temp_t7_3->words.w1 = 0;
                //temp_t7_3->words.w0 = 0xE7000000;
                gDPPipeSync(gfx++);

                //temp_t9 = gfx;
                //gfx = temp_t9 + 8;
                //temp_t9->words.w0 = 0xFC119623;
                //temp_t9->words.w1 = 0xFF2FFFFF;
                gDPSetCombineMode(gfx++, G_CC_MODULATEIA_PRIM, G_CC_MODULATEIA_PRIM);

                //temp_v0_7 = gfx;
                //gfx = temp_v0_7 + 8;
                //temp_v0_7->words.w0 = 0xFA000000;
                //temp_v0_7->words.w1 = msgCtx->textColorAlpha & 0xFF;
                gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, msgCtx->textColorAlpha);

                //temp_v0_8 = gfx;
                //temp_t7_4 = temp_v0_8 + 8;
                //gfx = temp_t7_4;
                //temp_v0_8->words.w0 = 0xFD900000;
                //temp_v0_8->words.w1 = (u32)msgCtx->textboxSegment + 0x1000;
                //gDPSetTextureImage(gfx++, G_IM_FMT_I, G_IM_SIZ_16b, 1, (u32)msgCtx->textboxSegment + 0x1000);

                //gfx = temp_t7_4 + 8;
                //temp_t7_4->words.w1 = 0x07000000;
                //temp_t7_4->words.w0 = 0xF5900000;

                //temp_t7_5 = gfx;
                //gfx = temp_t7_5 + 8;
                //temp_t7_5->words.w1 = 0;
                //temp_t7_5->words.w0 = 0xE6000000;
                //temp_t6 = gfx;
                //gfx = temp_t6 + 8;
                //temp_t6->words.w0 = 0xF3000000;
                //temp_t6->words.w1 = 0x0747F156;
                //temp_t6_2 = gfx;
                //gfx = temp_t6_2 + 8;
                //temp_t6_2->words.w1 = 0;
                //temp_t6_2->words.w0 = 0xE7000000;
                //temp_t8 = gfx;
                //gfx = temp_t8 + 8;
                //temp_t8->words.w1 = 0;
                //temp_t8->words.w0 = 0xF5800C00;
                //temp_t7_6 = gfx;
                //gfx = temp_t7_6 + 8;
                //temp_t7_6->words.w0 = 0xF2000000;
                //temp_t7_6->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, ((u32) msgCtx->textboxSegment) + 0x1000, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                //temp_v0_9 = gfx;
                ////temp_t8_2 = temp_v0_9 + 8;
                //temp_t8_2 = temp_v0_9 + 1;
                //gfx = temp_t8_2;
                //temp_v0_9->words.w0 = ((((msgCtx->textPosX + 0x61) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF);
                //temp_v0_9->words.w1 = ((((msgCtx->textPosX + 1) * 4) & 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF);
                //gfx = temp_t8_2 + 8;
                //temp_t8_2->words.w0 = 0xE1000000;
                //temp_t8_2->words.w1 = 0;
                //temp_t7_7 = gfx;
                //gfx = temp_t7_7 + 8;
                //temp_t7_7->words.w0 = 0xF1000000;
                //temp_t7_7->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 1) << 2, (msgCtx->unk12012 + 1) << 2, (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 0x31) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);


                //temp_v0_10 = gfx;
                //temp_t8_3 = temp_v0_10 + 8;
                //gfx = temp_t8_3;
                //temp_v0_10->words.w0 = 0xFD900000;
                //temp_v0_10->words.w1 = (u32)msgCtx->textboxSegment + 0x1900;
                //gfx = temp_t8_3 + 8;
                //temp_t8_3->words.w1 = 0x07000000;
                //temp_t8_3->words.w0 = 0xF5900000;
                //temp_t8_4 = gfx;
                //gfx = temp_t8_4 + 8;
                //temp_t8_4->words.w1 = 0;
                //temp_t8_4->words.w0 = 0xE6000000;
                //temp_t7_8 = gfx;
                //gfx = temp_t7_8 + 8;
                //temp_t7_8->words.w0 = 0xF3000000;
                //temp_t7_8->words.w1 = 0x0747F156;
                //temp_t7_9 = gfx;
                //gfx = temp_t7_9 + 8;
                //temp_t7_9->words.w1 = 0;
                //temp_t7_9->words.w0 = 0xE7000000;
                //temp_t9_2 = gfx;
                //gfx = temp_t9_2 + 8;
                //temp_t9_2->words.w1 = 0;
                //temp_t9_2->words.w0 = 0xF5800C00;
                //temp_t8_5 = gfx;
                //gfx = temp_t8_5 + 8;
                //temp_t8_5->words.w0 = 0xF2000000;
                //temp_t8_5->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, ((u32) msgCtx->textboxSegment) + 0x1900, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);


                //temp_v0_11 = gfx;
                //temp_t9_3 = temp_v0_11 + 8;
                //gfx = temp_t9_3;
                //temp_v0_11->words.w0 = ((((msgCtx->textPosX + 0xC2) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x31) * 4) & 0xFFF);
                //temp_v0_11->words.w1 = ((((msgCtx->textPosX + 0x61) * 4) & 0xFFF) << 0xC) | (((msgCtx->unk12012 + 1) * 4) & 0xFFF);
                //gfx = temp_t9_3 + 8;
                //temp_t9_3->words.w0 = 0xE1000000;
                //temp_t9_3->words.w1 = 0;
                //temp_t8_6 = gfx;
                //gfx = temp_t8_6 + 8;
                //temp_t8_6->words.w0 = 0xF1000000;
                //temp_t8_6->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x61) << 2, (msgCtx->unk12012 + 1) << 2, (msgCtx->textPosX + 0xC2) << 2, (msgCtx->unk12012 + 0x31) << 2, 0, 0, 0, 0x0400, 0x0400);


                //temp_t8_7 = gfx;
                //gfx = temp_t8_7 + 8;
                //temp_t8_7->words.w1 = 0;
                //temp_t8_7->words.w0 = 0xE7000000;
                //temp_v0_12 = gfx;
                //gfx = temp_v0_12 + 8;
                //temp_v0_12->words.w0 = 0xFA000000;
                //temp_v0_12->words.w1 = (msgCtx->textColorAlpha & 0xFF) | 0xFF3C0000;
                gDPPipeSync(gfx++);
                gDPSetPrimColor(gfx++, 0, 0, 255, 60, 0, msgCtx->textColorAlpha);

                //temp_v0_13 = gfx;
                //temp_t9_4 = temp_v0_13 + 8;
                //gfx = temp_t9_4;
                //temp_v0_13->words.w0 = 0xFD900000;
                //temp_v0_13->words.w1 = (u32)msgCtx->textboxSegment + 0x1000;
                //gfx = temp_t9_4 + 8;
                //temp_t9_4->words.w1 = 0x07000000;
                //temp_t9_4->words.w0 = 0xF5900000;
                //temp_t9_5 = gfx;
                //gfx = temp_t9_5 + 8;
                //temp_t9_5->words.w1 = 0;
                //temp_t9_5->words.w0 = 0xE6000000;
                //temp_t8_8 = gfx;
                //gfx = temp_t8_8 + 8;
                //temp_t8_8->words.w0 = 0xF3000000;
                //temp_t8_8->words.w1 = 0x0747F156;
                //temp_t8_9 = gfx;
                //gfx = temp_t8_9 + 8;
                //temp_t8_9->words.w1 = 0;
                //temp_t8_9->words.w0 = 0xE7000000;
                //temp_t6_3 = gfx;
                //gfx = temp_t6_3 + 8;
                //temp_t6_3->words.w1 = 0;
                //temp_t6_3->words.w0 = 0xF5800C00;
                //temp_t9_6 = gfx;
                //gfx = temp_t9_6 + 8;
                //temp_t9_6->words.w0 = 0xF2000000;
                //temp_t9_6->words.w1 = 0x0017C0BC;
                gDPLoadTextureBlock_4b(gfx++, ((u32) msgCtx->textboxSegment) + 0x1000, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                //temp_v0_14 = gfx;
                //gfx = temp_v0_14 + 8;
                //temp_v0_14->words.w0 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF);
                //temp_v0_14->words.w1 = (((msgCtx->textPosX * 4) & 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF);
                //temp_t8_10 = gfx;
                //gfx = temp_t8_10 + 8;
                //temp_t8_10->words.w0 = 0xE1000000;
                //temp_t8_10->words.w1 = 0;
                //temp_t7_10 = gfx;
                //gfx = temp_t7_10 + 8;
                //temp_t7_10->words.w0 = 0xF1000000;
                //temp_t7_10->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, msgCtx->textPosX << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0x60) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);

                //temp_v0_15 = gfx;
                //temp_t8_11 = temp_v0_15 + 8;
                //gfx = temp_t8_11;
                //temp_v0_15->words.w0 = 0xFD900000;
                //temp_v0_15->words.w1 = (u32)msgCtx->textboxSegment + 0x1900;
                //gfx = temp_t8_11 + 8;
                //temp_t8_11->words.w1 = 0x07000000;
                //temp_t8_11->words.w0 = 0xF5900000;
                //temp_t8_12 = gfx;
                //gfx = temp_t8_12 + 8;
                //temp_t8_12->words.w1 = 0;
                //temp_t8_12->words.w0 = 0xE6000000;
                //temp_t7_11 = gfx;
                //gfx = temp_t7_11 + 8;
                //temp_t7_11->words.w0 = 0xF3000000;
                //temp_t7_11->words.w1 = 0x0747F156;
                //temp_t7_12 = gfx;
                //gfx = temp_t7_12 + 8;
                //temp_t7_12->words.w1 = 0;
                //temp_t7_12->words.w0 = 0xE7000000;
                //temp_t6_4 = gfx;
                //gfx = temp_t6_4 + 8;
                //temp_t6_4->words.w1 = 0;
                //temp_t6_4->words.w0 = 0xF5800C00;
                //temp_t8_13 = gfx;
                //gfx = temp_t8_13 + 8;
                //temp_t8_13->words.w0 = 0xF2000000;
                //temp_t8_13->words.w1 = 0x17C0BC;
                gDPLoadTextureBlock_4b(gfx++, ((u32) msgCtx->textboxSegment) + 0x1900, G_IM_FMT_I, 96, 48, 0, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);

                //temp_v0_16 = gfx;
                //gfx = temp_v0_16 + 8;
                //temp_v0_16->words.w0 = ((((msgCtx->textPosX + 0xC0) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((msgCtx->unk12012 + 0x30) * 4) & 0xFFF);
                //temp_v0_16->words.w1 = ((((msgCtx->textPosX + 0x60) * 4) & 0xFFF) << 0xC) | ((msgCtx->unk12012 * 4) & 0xFFF);
                //temp_t8_14 = gfx;
                //gfx = temp_t8_14 + 8;
                //temp_t8_14->words.w0 = 0xE1000000;
                //temp_t8_14->words.w1 = 0;
                //temp_t7_13 = gfx;
                //gfx = temp_t7_13 + 8;
                //temp_t7_13->words.w0 = 0xF1000000;
                //temp_t7_13->words.w1 = 0x04000400;
                gSPTextureRectangle(gfx++, (msgCtx->textPosX + 0x60) << 2, msgCtx->unk12012 << 2, (msgCtx->textPosX + 0xC0) << 2, (msgCtx->unk12012 + 0x30) << 2, G_TX_RENDERTILE, 0, 0, 0x0400, 0x0400);


                //temp_t7_14 = gfx;
                //gfx = temp_t7_14 + 8;
                //temp_t7_14->words.w1 = 0;
                //temp_t7_14->words.w0 = 0xE7000000;
                //temp_t9_7 = gfx;
                //gfx = temp_t9_7 + 8;
                //temp_t9_7->words.w0 = 0xFCFF97FF;
                //temp_t9_7->words.w1 = 0xFF2DFEFF;
                gDPPipeSync(gfx++);
                gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
                msgCtx->textPosX += 0x20;
                break;

            case 0x14:
                msgCtx->unk12026 = msgCtx->decodedBuffer.schar[++i];
                break;
            case 0x1A:
                msgCtx->textUnskippable = 1;
                break;
            case 0x1B:
                msgCtx->textboxEndType = 0x10;
                if (msgCtx->msgMode == 6) {
                    msgCtx->unk11F06 = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    msgCtx->choiceIndex = 0;
                    Font_LoadMessageBoxEndIcon(font, 2U);
                }
                break;
            case 0x1C:
                msgCtx->textboxEndType = 0x11;
                if (msgCtx->msgMode == 6) {
                    msgCtx->unk11F06 = msgCtx->currentTextId;
                    msgCtx->stateTimer = 4;
                    msgCtx->choiceIndex = 0;
                    Font_LoadMessageBoxEndIcon(font, 2U);
                }
                break;
            case 0x2:
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    if (msgCtx->textboxEndType == 0) {
                        play_sound(0x482E);
                        Font_LoadMessageBoxEndIcon(font, 1U);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                }
                *gfxp = gfx;
                return;
            case 0x10:
                if ((i + 1) == msgCtx->textDrawPos) {
                    func_8014AAD0(play);
                    *gfxp = gfx;
                    return;
                }
                break;
            case 0xE:
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x50;
                    msgCtx->stateTimer = (u8) msgCtx->decodedBuffer.schar[++i];
                    Font_LoadMessageBoxEndIcon(font, 1U);
                    if (play->csCtx.state == 0) {
                        func_8011552C(play, 3);
                    }
                }
                *gfxp = gfx;
                return;
            case 0xA:
                if (msgCtx->msgMode == 6) {
                    play_sound(0U);
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x30;
                }
                *gfxp = gfx;
                return;
            case 0xB:
                if (msgCtx->msgMode == 6) {
                    msgCtx->msgMode = 0x42;
                    msgCtx->textboxEndType = 0x40;
                    Font_LoadMessageBoxEndIcon(font, 0U);
                    play_sound(0x482E);
                }
                *gfxp = gfx;
                return;
            default:

                if ((msgCtx->msgMode == 6) && ((i + 1) == msgCtx->textDrawPos) && (msgCtx->textDelayTimer == msgCtx->unk12026)) {
                    //sp48 = (s32) character;
                    play_sound(0U);
                }
                //sp48 = (s32) character;
                func_8014995C(play, &font->charBuf[font->unk_11D88][charTexIndex], &gfx);
                charTexIndex += 0x80;
                // msgCtx->textPosX += (s32)(sFontWidths[character - ' '] * msgCtx->textCharScale);
                msgCtx->textPosX += (s32) (sFontWidths[character - ' '] * msgCtx->textCharScale);
                //continue;
                break;
        }
    }

    if (msgCtx->textDelayTimer == 0) {
        msgCtx->textDrawPos = i + 1;
        msgCtx->textDelayTimer = msgCtx->unk12026;
    } else {
        msgCtx->textDelayTimer--;
    }

    *gfxp = gfx;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/Message_DrawTextCredits.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message_staff/Message_DecodeCredits.s")
