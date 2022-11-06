extern ? D_801D03F0;

void Message_DrawTextNES(PlayState* play, Gfx** gfxP, s32 textDrawPos) {
    u16 sp13A;
    Gfx* sp134;
    s16 sp130;
    s16 sp12E;
    s16 sp12C;
    s16 sp12A;
    Font* sp5C;
    s32 sp54;
    s32 sp50;
    Font* temp_a3;
    Font* temp_a3_2;
    Font* temp_a3_3;
    Font* temp_a3_4;
    Font* var_v0;
    Gfx* temp_t1;
    Gfx* temp_t1_2;
    Gfx* temp_t1_3;
    Gfx* temp_t1_4;
    Gfx* temp_t1_5;
    Gfx* temp_t2;
    Gfx* temp_t3;
    Gfx* temp_t3_2;
    Gfx* temp_t3_3;
    Gfx* temp_t3_4;
    Gfx* temp_t3_5;
    Gfx* temp_t3_6;
    Gfx* temp_t4;
    Gfx* temp_t4_2;
    Gfx* temp_t4_3;
    Gfx* temp_t4_4;
    Gfx* temp_t4_5;
    Gfx* temp_t5;
    Gfx* temp_t5_2;
    Gfx* temp_t5_3;
    Gfx* temp_t5_4;
    Gfx* temp_t5_5;
    Gfx* temp_t5_6;
    Gfx* temp_t5_7;
    Gfx* temp_t6;
    Gfx* temp_t6_2;
    Gfx* temp_t7;
    Gfx* temp_t7_2;
    Gfx* temp_t7_3;
    Gfx* temp_t7_4;
    Gfx* temp_t7_5;
    Gfx* temp_t7_6;
    Gfx* temp_t7_7;
    Gfx* temp_t8;
    Gfx* temp_t8_2;
    Gfx* temp_t8_3;
    Gfx* temp_t8_4;
    Gfx* temp_t8_5;
    Gfx* temp_t8_6;
    Gfx* temp_t9;
    Gfx* temp_t9_2;
    Gfx* temp_t9_3;
    Gfx* temp_t9_4;
    Gfx* temp_v0_2;
    Gfx* temp_v0_3;
    Gfx* temp_v0_4;
    Gfx* temp_v0_5;
    MessageContext* temp_s1;
    s16 temp_a0;
    s16 temp_a0_2;
    s16 temp_v0_25;
    s16 temp_v0_26;
    s16 temp_v0_27;
    s16 temp_v0_28;
    s16 temp_v0_6;
    s16 temp_v0_7;
    s16 temp_v1;
    s16 temp_v1_2;
    s16 temp_v1_3;
    s16 var_t4;
    s32 temp_s2;
    s32 temp_t2_2;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a1;
    s32 var_s3;
    s32 var_v1;
    u16 temp_v0_17;
    u16 temp_v0_22;
    u16 temp_v0_24;
    u16 temp_v0_29;
    u16 temp_v0_9;
    u16 var_v0_2;
    u8 temp_v0;
    u8 temp_v0_10;
    u8 temp_v0_13;
    u8 temp_v0_18;
    u8 temp_v0_19;
    u8 temp_v0_20;
    u8 temp_v0_21;
    u8 temp_v0_8;
    u8 temp_v1_8;
    u8 var_t0;
    void* temp_t1_6;
    void* temp_t3_7;
    void* temp_v0_11;
    void* temp_v0_12;
    void* temp_v0_14;
    void* temp_v0_15;
    void* temp_v0_16;
    void* temp_v0_23;
    void* var_at;
    void* var_at_2;
    void* var_s0;
    void* var_s2;

    temp_s2 = textDrawPos & 0xFFFF;
    var_v0 = play + 0x10000;
    temp_s1 = &play->msgCtx;
    sp134 = *gfxP;
    var_s0 = temp_s1 + 0x10000;
    play->msgCtx.textPosX = play->msgCtx.unk11F1A[0] + play->msgCtx.unk11FF8;
    play->msgCtx.textPosY = play->msgCtx.unk11FFA;
    sp130 = 0;
    if (play->msgCtx.textIsCredits == 0) {
        var_s0 = temp_s1 + 0x10000;
        temp_s1->textPosY = temp_s1->unk11FFA;
    } else {
        temp_s1->textPosY = 0x30;
    }
    if (var_s0->unk_1F16 != 0xFE) {
        sp5C = var_v0;
        Message_DrawItemIcon(play, &sp134);
        var_v0 = sp5C;
    }
    temp_s1->textColorR = var_s0->unk_20C8;
    temp_s1->textColorG = var_s0->unk_20CA;
    temp_s1->textColorB = var_s0->unk_20CC;
    sp13A = 0;
    var_s3 = temp_s2 & 0xFFFF;
    if (temp_s2 < (s32) var_s0->unk_1FEE) {
        sp5C = var_v0;
loop_7:
        temp_v0 = (u8) temp_s1->decodedBuffer.schar[var_s3];
        var_t0 = temp_v0;
        if ((s32) temp_v0 >= 0x21) {
            switch (temp_v0) {                      /* switch 1 */
                case 0xC1:                          /* switch 1 */
                    temp_s1->textPosX = 0x2D;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        play_sound(0U);
                    }
                    temp_t1 = sp134;
                    sp134 = temp_t1 + 8;
                    temp_t1->words.w1 = 0;
                    temp_t1->words.w0 = 0xE7000000;
                    temp_t4 = sp134;
                    sp134 = temp_t4 + 8;
                    temp_t4->words.w0 = 0xFC119623;
                    temp_t4->words.w1 = 0xFF2FFFFF;
                    temp_t8 = sp134;
                    sp134 = temp_t8 + 8;
                    temp_t8->words.w0 = 0xFA000000;
                    temp_t8->words.w1 = var_s0->unk_201E & 0xFF;
                    temp_t4_2 = sp134;
                    sp134 = temp_t4_2 + 8;
                    temp_t4_2->words.w0 = 0xFD900000;
                    temp_t4_2->words.w1 = var_s0->unk_1EF8 + 0x1000;
                    temp_t9 = sp134;
                    sp134 = temp_t9 + 8;
                    temp_t9->words.w1 = 0x07000000;
                    temp_t9->words.w0 = 0xF5900000;
                    temp_t4_3 = sp134;
                    sp134 = temp_t4_3 + 8;
                    temp_t4_3->words.w1 = 0;
                    temp_t4_3->words.w0 = 0xE6000000;
                    temp_t7 = sp134;
                    sp134 = temp_t7 + 8;
                    temp_t7->words.w1 = 0x0747F156;
                    temp_t7->words.w0 = 0xF3000000;
                    temp_t2 = sp134;
                    sp134 = temp_t2 + 8;
                    temp_t2->words.w1 = 0;
                    temp_t2->words.w0 = 0xE7000000;
                    temp_t5 = sp134;
                    sp134 = temp_t5 + 8;
                    temp_t5->words.w1 = 0;
                    temp_t5->words.w0 = 0xF5800C00;
                    temp_t8_2 = sp134;
                    sp134 = temp_t8_2 + 8;
                    temp_t8_2->words.w1 = 0x17C0BC;
                    temp_t8_2->words.w0 = 0xF2000000;
                    temp_v0_2 = sp134;
                    sp134 = temp_v0_2 + 8;
                    temp_v0_2->words.w0 = ((((var_s0->unk_1FF4 + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((var_s0->unk_2012 + 0x31) * 4) & 0xFFF);
                    temp_v0_2->words.w1 = (((var_s0->unk_1FF4 * 4) & 0xFFF) << 0xC) | (((var_s0->unk_2012 + 1) * 4) & 0xFFF);
                    temp_t7_2 = sp134;
                    sp134 = temp_t7_2 + 8;
                    temp_t7_2->words.w0 = 0xE1000000;
                    temp_t7_2->words.w1 = 0;
                    temp_t3 = sp134;
                    sp134 = temp_t3 + 8;
                    temp_t3->words.w0 = 0xF1000000;
                    temp_t3->words.w1 = 0x04000400;
                    temp_t5_2 = sp134;
                    sp134 = temp_t5_2 + 8;
                    temp_t5_2->words.w0 = 0xFD900000;
                    temp_t5_2->words.w1 = var_s0->unk_1EF8 + 0x1900;
                    temp_t3_2 = sp134;
                    sp134 = temp_t3_2 + 8;
                    temp_t3_2->words.w1 = 0x07000000;
                    temp_t3_2->words.w0 = 0xF5900000;
                    temp_t5_3 = sp134;
                    sp134 = temp_t5_3 + 8;
                    temp_t5_3->words.w1 = 0;
                    temp_t5_3->words.w0 = 0xE6000000;
                    temp_t8_3 = sp134;
                    sp134 = temp_t8_3 + 8;
                    temp_t8_3->words.w1 = 0x0747F156;
                    temp_t8_3->words.w0 = 0xF3000000;
                    temp_t1_2 = sp134;
                    sp134 = temp_t1_2 + 8;
                    temp_t1_2->words.w1 = 0;
                    temp_t1_2->words.w0 = 0xE7000000;
                    temp_t6 = sp134;
                    sp134 = temp_t6 + 8;
                    temp_t6->words.w1 = 0;
                    temp_t6->words.w0 = 0xF5800C00;
                    temp_t9_2 = sp134;
                    sp134 = temp_t9_2 + 8;
                    temp_t9_2->words.w1 = 0x17C0BC;
                    temp_t9_2->words.w0 = 0xF2000000;
                    temp_v0_3 = sp134;
                    sp134 = temp_v0_3 + 8;
                    temp_v0_3->words.w0 = ((((var_s0->unk_1FF4 + 0xC1) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((var_s0->unk_2012 + 0x31) * 4) & 0xFFF);
                    temp_v0_3->words.w1 = ((((var_s0->unk_1FF4 + 0x60) * 4) & 0xFFF) << 0xC) | (((var_s0->unk_2012 + 1) * 4) & 0xFFF);
                    temp_t9_3 = sp134;
                    sp134 = temp_t9_3 + 8;
                    temp_t9_3->words.w0 = 0xE1000000;
                    temp_t9_3->words.w1 = 0;
                    temp_t5_4 = sp134;
                    sp134 = temp_t5_4 + 8;
                    temp_t5_4->words.w0 = 0xF1000000;
                    temp_t5_4->words.w1 = 0x04000400;
                    temp_t7_3 = sp134;
                    sp134 = temp_t7_3 + 8;
                    temp_t7_3->words.w1 = 0;
                    temp_t7_3->words.w0 = 0xE7000000;
                    temp_t3_3 = sp134;
                    sp134 = temp_t3_3 + 8;
                    temp_t3_3->words.w0 = 0xFA000000;
                    temp_t3_3->words.w1 = (var_s0->unk_201E & 0xFF) | 0xFF3C0000;
                    temp_t7_4 = sp134;
                    sp134 = temp_t7_4 + 8;
                    temp_t7_4->words.w0 = 0xFD900000;
                    temp_t7_4->words.w1 = var_s0->unk_1EF8 + 0x1000;
                    temp_t5_5 = sp134;
                    sp134 = temp_t5_5 + 8;
                    temp_t5_5->words.w1 = 0x07000000;
                    temp_t5_5->words.w0 = 0xF5900000;
                    temp_t7_5 = sp134;
                    sp134 = temp_t7_5 + 8;
                    temp_t7_5->words.w1 = 0;
                    temp_t7_5->words.w0 = 0xE6000000;
                    temp_t3_4 = sp134;
                    sp134 = temp_t3_4 + 8;
                    temp_t3_4->words.w1 = 0x0747F156;
                    temp_t3_4->words.w0 = 0xF3000000;
                    temp_t6_2 = sp134;
                    sp134 = temp_t6_2 + 8;
                    temp_t6_2->words.w1 = 0;
                    temp_t6_2->words.w0 = 0xE7000000;
                    temp_t8_4 = sp134;
                    sp134 = temp_t8_4 + 8;
                    temp_t8_4->words.w1 = 0;
                    temp_t8_4->words.w0 = 0xF5800C00;
                    temp_t1_3 = sp134;
                    sp134 = temp_t1_3 + 8;
                    temp_t1_3->words.w1 = 0x17C0BC;
                    temp_t1_3->words.w0 = 0xF2000000;
                    temp_v0_4 = sp134;
                    sp134 = temp_v0_4 + 8;
                    temp_v0_4->words.w0 = ((((var_s0->unk_1FF4 + 0x60) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((var_s0->unk_2012 + 0x30) * 4) & 0xFFF);
                    temp_v0_4->words.w1 = (((var_s0->unk_1FF4 * 4) & 0xFFF) << 0xC) | ((var_s0->unk_2012 * 4) & 0xFFF);
                    temp_t9_4 = sp134;
                    sp134 = temp_t9_4 + 8;
                    temp_t9_4->words.w0 = 0xE1000000;
                    temp_t9_4->words.w1 = 0;
                    temp_t5_6 = sp134;
                    sp134 = temp_t5_6 + 8;
                    temp_t5_6->words.w0 = 0xF1000000;
                    temp_t5_6->words.w1 = 0x04000400;
                    temp_t4_4 = sp134;
                    sp134 = temp_t4_4 + 8;
                    temp_t4_4->words.w0 = 0xFD900000;
                    temp_t4_4->words.w1 = var_s0->unk_1EF8 + 0x1900;
                    temp_t5_7 = sp134;
                    sp134 = temp_t5_7 + 8;
                    temp_t5_7->words.w1 = 0x07000000;
                    temp_t5_7->words.w0 = 0xF5900000;
                    temp_t4_5 = sp134;
                    sp134 = temp_t4_5 + 8;
                    temp_t4_5->words.w1 = 0;
                    temp_t4_5->words.w0 = 0xE6000000;
                    temp_t3_5 = sp134;
                    sp134 = temp_t3_5 + 8;
                    temp_t3_5->words.w1 = 0x0747F156;
                    temp_t3_5->words.w0 = 0xF3000000;
                    temp_t7_6 = sp134;
                    sp134 = temp_t7_6 + 8;
                    temp_t7_6->words.w1 = 0;
                    temp_t7_6->words.w0 = 0xE7000000;
                    temp_t8_5 = sp134;
                    sp134 = temp_t8_5 + 8;
                    temp_t8_5->words.w1 = 0;
                    temp_t8_5->words.w0 = 0xF5800C00;
                    temp_t1_4 = sp134;
                    sp134 = temp_t1_4 + 8;
                    temp_t1_4->words.w1 = 0x17C0BC;
                    temp_t1_4->words.w0 = 0xF2000000;
                    temp_v0_5 = sp134;
                    sp134 = temp_v0_5 + 8;
                    temp_v0_5->words.w0 = ((((var_s0->unk_1FF4 + 0xC0) * 4) & 0xFFF) << 0xC) | 0xE4000000 | (((var_s0->unk_2012 + 0x30) * 4) & 0xFFF);
                    temp_v0_5->words.w1 = ((((var_s0->unk_1FF4 + 0x60) * 4) & 0xFFF) << 0xC) | ((var_s0->unk_2012 * 4) & 0xFFF);
                    temp_t3_6 = sp134;
                    sp134 = temp_t3_6 + 8;
                    temp_t3_6->words.w0 = 0xE1000000;
                    temp_t3_6->words.w1 = 0;
                    temp_t7_7 = sp134;
                    sp134 = temp_t7_7 + 8;
                    temp_t7_7->words.w0 = 0xF1000000;
                    temp_t7_7->words.w1 = 0x04000400;
                    temp_t8_6 = sp134;
                    sp134 = temp_t8_6 + 8;
                    temp_t8_6->words.w1 = 0;
                    temp_t8_6->words.w0 = 0xE7000000;
                    temp_t1_5 = sp134;
                    sp134 = temp_t1_5 + 8;
                    temp_t1_5->words.w0 = 0xFCFF97FF;
                    temp_t1_5->words.w1 = 0xFF2DFEFF;
                    temp_s1->textPosX = var_s0->unk_1FF4 + 0x20;
                    goto block_210;
                case 0xC2:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x10;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->choiceTextId = var_s0->unk_1F04;
                        temp_s1->stateTimer = 4;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2U);
                        if (var_s0->unk_20D8 != 3) {
                            temp_v0_6 = var_s0->unk_2006;
                            var_s0->unk_1FFE = (s16) (temp_v0_6 + 0xE);
                            var_s0->unk_2000 = (s16) (temp_v0_6 + 0x1A);
                            var_s0->unk_2002 = (s16) (temp_v0_6 + 0x26);
                        }
                    }
                    goto block_210;
                case 0xC3:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x11;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->choiceTextId = var_s0->unk_1F04;
                        temp_s1->stateTimer = 4;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 2U);
                        if (var_s0->unk_20D8 != 3) {
                            temp_v0_7 = var_s0->unk_2006;
                            var_s0->unk_1FFE = (s16) (temp_v0_7 + 0xE);
                            var_s0->unk_2000 = (s16) (temp_v0_7 + 0x1A);
                            var_s0->unk_2002 = (s16) (temp_v0_7 + 0x26);
                        }
                    }
                    goto block_210;
                case 0xCC:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x60;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    goto block_210;
                case 0xD0:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x61;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    goto block_210;
                case 0xD1:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x62;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    goto block_210;
                case 0xD2:                          /* switch 1 */
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->msgMode = 0x42;
                        temp_s1->textboxEndType = 0x41;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0U);
                        play_sound(0x482EU);
                    }
                    goto block_210;
                case 0xD5:                          /* switch 1 */
                    temp_s1->textboxEndType = 0x63;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1F22 == 6) {
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                    }
                    goto block_210;
                case 0xE0:                          /* switch 1 */
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->msgMode = 0x42;
                        temp_s1->textboxEndType = 0x42;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        play_sound(0x482EU);
                    }
                    goto block_217;
            }
        } else {
            switch (var_t0) {                       /* switch 2 */
                case 0x0:                           /* switch 2 */
                    var_s2 = temp_s1 + 0x10000;
                    if ((sp5C->charBuf[1][0x3320] != 0) || (temp_v0_8 = var_s0->unk_1F0A, (temp_v0_8 == 0xD))) {
                        temp_s1->textColorB = 0;
                        temp_s1->textColorG = var_s0->unk_201C;
                        var_at = temp_s1 + 0x10000;
                    } else if (temp_v0_8 == 5) {
                        temp_s1->textColorB = 0;
                        temp_s1->textColorG = var_s0->unk_201C;
                        var_at = temp_s1 + 0x10000;
                    } else {
                        temp_s1->textColorB = 0xFF;
                        temp_s1->textColorG = var_s0->unk_201C;
                        var_at = temp_s1 + 0x10000;
                    }
                    var_at->unk_2018 = var_s0->unk_201C;
                    temp_v0_9 = var_s0->unk_1FEE;
                    if (temp_v0_9 == (var_s3 + 1)) {
                        temp_s1->textDrawPos = temp_v0_9 + 1;
                    }
block_210:
                    var_v0_2 = var_s2->unk_1FEE;
block_211:
                    var_s3 = (var_s3 + 1) & 0xFFFF;
                    if (var_s3 >= (s32) var_v0_2) {
                        goto block_212;
                    }
                    goto loop_7;
                case 0x1:                           /* switch 2 */
                case 0x2:                           /* switch 2 */
                case 0x3:                           /* switch 2 */
                case 0x4:                           /* switch 2 */
                case 0x5:                           /* switch 2 */
                case 0x6:                           /* switch 2 */
                case 0x7:                           /* switch 2 */
                case 0x8:                           /* switch 2 */
                    temp_v0_10 = var_s0->unk_1F22;
                    var_s2 = temp_s1 + 0x10000;
                    if (((s32) temp_v0_10 >= 0x4A) && ((s32) temp_v0_10 < 0x50) && (var_t0 == 2)) {
                        temp_s1->textDrawPos = var_s0->unk_1FF0;
                        if (var_s0->unk_20D6 != 0) {
                            temp_s1->unk120D4 = var_s0->unk_20D4 + 0x19;
                            if (var_s0->unk_20D4 >= 0x64) {
                                temp_s1->unk120D6 = 0;
                            }
                        } else {
                            temp_s1->unk120D4 = var_s0->unk_20D4 - 0x19;
                            if (var_s0->unk_20D4 < -0x63) {
                                temp_s1->unk120D6 = 1;
                            }
                        }
                        temp_v0_11 = ((s16) (var_t0 - 1) * 6U) + D_801D07DC;
                        temp_a0 = temp_v0_11->unk_0 + var_s0->unk_20D4;
                        if (temp_a0 < 0) {
                            temp_s1->textColorR = 0;
                        } else {
                            temp_s1->textColorR = temp_a0;
                        }
                        temp_v1 = temp_v0_11->unk_2;
                        temp_a0_2 = temp_v1 + var_s0->unk_20D4;
                        if (temp_a0_2 >= 0xFF) {
                            temp_s1->textColorG = temp_v1;
                        } else {
                            temp_s1->textColorG = temp_a0_2;
                        }
                        temp_v1_2 = temp_v0_11->unk_4 + var_s0->unk_20D4;
                        if (temp_v1_2 < 0) {
                            temp_s1->textColorB = 0;
                        } else {
                            temp_s1->textColorB = temp_v1_2;
                        }
                    } else if (sp5C->charBuf[1][0x3320] != 0) {
                        temp_v0_12 = ((s16) (var_t0 - 1) * 6U) + D_801D089C;
                        temp_s1->textColorR = temp_v0_12->unk_0;
                        temp_s1->textColorG = temp_v0_12->unk_2;
                        temp_s1->textColorB = temp_v0_12->unk_4;
                    } else {
                        temp_v0_13 = var_s0->unk_1F0A;
                        if (temp_v0_13 == 1) {
                            temp_v0_14 = ((s16) (var_t0 - 1) * 6U) + D_801D07DC;
                            temp_s1->textColorR = temp_v0_14->unk_0;
                            temp_s1->textColorG = temp_v0_14->unk_2;
                            temp_s1->textColorB = temp_v0_14->unk_4;
                        } else if (temp_v0_13 == 0xD) {
                            temp_v0_15 = ((s16) (var_t0 - 1) * 6U) + D_801D086C;
                            temp_s1->textColorR = temp_v0_15->unk_0;
                            temp_s1->textColorG = temp_v0_15->unk_2;
                            temp_s1->textColorB = temp_v0_15->unk_4;
                        } else {
                            temp_v0_16 = ((s16) (var_t0 - 1) * 6U) + D_801D080C;
                            temp_s1->textColorR = temp_v0_16->unk_0;
                            temp_s1->textColorG = temp_v0_16->unk_2;
                            temp_s1->textColorB = temp_v0_16->unk_4;
                        }
                    }
                    temp_v0_17 = var_s0->unk_1FEE;
                    if (temp_v0_17 == (var_s3 + 1)) {
                        temp_s1->textDrawPos = temp_v0_17 + 1;
                    }
                    goto block_210;
                case 0x20:                          /* switch 2 */
                    temp_s1->textPosX = var_s0->unk_1FF4 + 6;
                    var_v0_2 = temp_s1->textDrawPos;
                    goto block_211;
                case 0x11:                          /* switch 2 */
                    temp_s1->textPosY = var_s0->unk_1FF6 + var_s0->unk_1FFC;
                    /* fallthrough */
                case 0x13:                          /* switch 2 */
                    temp_v1_3 = sp130 + 1;
                    var_s2 = temp_s1 + 0x10000;
                    temp_s1->textPosX = temp_s1->unk11F1A[temp_v1_3] + var_s0->unk_1FF8;
                    temp_v0_18 = var_s0->unk_2022;
                    sp130 = temp_v1_3;
                    if (temp_v0_18 == 1) {
                        if (sp5C->charBuf[1][0x3320] == 0) {
                            temp_s1->textPosX = var_s0->unk_1FF4 + 0x10;
                        } else {
                            temp_s1->textPosX = var_s0->unk_1FF4 + 0x32;
                        }
                    } else if (temp_v0_18 == 2) {
                        if (var_s0->unk_20D8 != 3) {
                            if (sp5C->charBuf[1][0x3320] == 0) {
                                var_at_2 = temp_s1 + 0x10000;
                                var_t4 = var_s0->unk_1FF4 + 0xA;
                                goto block_64;
                            }
                            temp_s1->textPosX = var_s0->unk_1FF4 + 0x39;
                        } else if (sp130 >= 2) {
                            if (sp5C->charBuf[1][0x3320] == 0) {
                                temp_s1->textPosX = var_s0->unk_1FF4 + 0xA;
                            } else {
                                var_at_2 = temp_s1 + 0x10000;
                                var_t4 = var_s0->unk_1FF4 + 0x39;
block_64:
                                var_at_2->unk_1FF4 = var_t4;
                            }
                        }
                    }
                    goto block_210;
                case 0x10:                          /* switch 2 */
                case 0x12:                          /* switch 2 */
                    if (var_s0->unk_1F22 == 6) {
                        if (var_s0->unk_2094 == 0) {
                            sp5C = &play->msgCtx.font;
                            play_sound(0U);
                            temp_s1->msgMode = 0x41;
                            Font_LoadMessageBoxEndIcon(sp5C, 0U);
                        } else {
                            temp_s1->msgMode = 4;
                            temp_s1->textUnskippable = 0;
                            temp_s1->msgBufPos = var_s0->unk_1FEC + 1;
                        }
                        temp_s1->unk120CE = var_s0->unk_2018;
                        temp_s1->unk120D0 = var_s0->unk_201A;
                        temp_s1->unk120D2 = var_s0->unk_201C;
                    }
                    *gfxP = sp134;
                    return;
                case 0x17:                          /* switch 2 */
                    var_s2 = temp_s1 + 0x10000;
                    if ((var_s0->unk_1FEE == (var_s3 + 1)) && ((temp_v0_19 = var_s0->unk_1F22, var_v1 = var_s3 & 0xFFFF, (temp_v0_19 == 6)) || (((s32) temp_v0_19 >= 0xA) && ((s32) temp_v0_19 < 0x27)))) {
loop_76:
                        temp_v0_20 = (u8) temp_s1->decodedBuffer.schar[var_v1];
                        if ((temp_v0_20 != 0x18) && (temp_v0_20 != 0x1A) && (temp_v0_20 != 0x19) && (temp_v0_20 != 0xE0) && (temp_v0_20 != 0x10) && (temp_v0_20 != 0x12)) {
                            var_v1 = (var_v1 + 1) & 0xFFFF;
                            goto loop_76;
                        }
                        temp_t2_2 = var_v1 - 1;
                        var_s3 = temp_t2_2 & 0xFFFF;
                        temp_s1->textDrawPos = temp_t2_2 + 1;
                    }
                    goto block_210;
                case 0x18:                          /* switch 2 */
                    var_v0_2 = temp_s1->textDrawPos;
                    goto block_211;
                case 0x1B:                          /* switch 2 */
                    temp_v1_4 = var_s3 + 1;
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->stateTimer = ((u8) temp_s1->decodedBuffer.schar[temp_v1_4 & 0xFFFF] << 8) | (u8) temp_s1->decodedBuffer.schar[(temp_v1_4 + 1) & 0xFFFF];
                        temp_s1->msgMode = 8;
                    }
                    *gfxP = sp134;
                    return;
                case 0x1C:                          /* switch 2 */
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->msgMode = 0x42;
                        temp_v1_5 = var_s3 + 1;
                        if (var_s0->unk_1F0C == 3) {
                            temp_s1->textboxEndType = 0x55;
                        } else {
                            temp_s1->textboxEndType = 0x50;
                        }
                        temp_s1->stateTimer = ((u8) temp_s1->decodedBuffer.schar[temp_v1_5 & 0xFFFF] << 8) | (u8) temp_s1->decodedBuffer.schar[(temp_v1_5 + 1) & 0xFFFF];
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                    *gfxP = sp134;
                    return;
                case 0x1D:                          /* switch 2 */
                    if (var_s0->unk_1F22 == 6) {
                        temp_v1_6 = var_s3 + 1;
                        temp_s1->msgMode = 0x42;
                        temp_s1->textboxEndType = 0x52;
                        temp_s1->stateTimer = ((u8) temp_s1->decodedBuffer.schar[temp_v1_6 & 0xFFFF] << 8) | (u8) temp_s1->decodedBuffer.schar[(temp_v1_6 + 1) & 0xFFFF];
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 1U);
                        if (play->csCtx.state == 0) {
                            func_8011552C(play, 3);
                        }
                    }
                    *gfxP = sp134;
                    return;
                case 0x1E:                          /* switch 2 */
                    temp_v1_7 = var_s3 + 1;
                    var_a1 = var_s3;
                    var_s2 = temp_s1 + 0x10000;
                    if (var_s0->unk_1FEE == temp_v1_7) {
                        temp_t3_7 = temp_s1 + var_s3;
                        if (var_s0->unk_1F22 == 6) {
                            sp50 = var_s3;
                            sp54 = temp_v1_7;
                            play_sound(((temp_t3_7->unk_11F25 << 8) | temp_t3_7->unk_11F26) & 0xFFFF);
                            var_a1 = sp50;
                        }
                    }
                    if (var_s0->unk_1FEE == temp_v1_7) {
                        temp_s1->textDrawPos = var_s0->unk_1FEE + 2;
                    }
                    var_s3 = (var_a1 + 2) & 0xFFFF;
                    goto block_210;
                case 0x1F:                          /* switch 2 */
                    var_s2 = temp_s1 + 0x10000;
                    if ((var_s0->unk_1FEE == (var_s3 + 1)) && (var_s0->unk_1F22 == 6)) {
                        temp_t1_6 = temp_s1 + var_s3;
                        temp_s1->msgMode = 9;
                        temp_s1->textDelayTimer = (temp_t1_6->unk_11F25 << 8) | temp_t1_6->unk_11F26;
                    }
                    var_s3 = (var_s3 + 2) & 0xFFFF;
                    goto block_210;
                case 0xA:                           /* switch 2 */
                    var_s3 = (var_s3 + 1) & 0xFFFF;
                    temp_v0_21 = (u8) temp_s1->decodedBuffer.schar[var_s3];
                    var_s2 = temp_s1 + 0x10000;
                    switch (temp_v0_21) {           /* switch 3 */
                        case 0x0:                   /* switch 3 */
                        case 0x1:                   /* switch 3 */
                        case 0x2:                   /* switch 3 */
                        case 0x3:                   /* switch 3 */
                        case 0x4:                   /* switch 3 */
                        case 0x5:                   /* switch 3 */
                        case 0x6:                   /* switch 3 */
                            temp_s1->textDelay = (u16) temp_v0_21;
                            temp_v0_22 = var_s0->unk_1FEE;
                            if (temp_v0_22 == (var_s3 + 1)) {
                                temp_s1->textDrawPos = temp_v0_22 + 1;
                            }
                            break;
                    }
                    goto block_210;
                case 0x15:                          /* switch 2 */
                case 0xBF:                          /* switch 1 */
                    if (var_s0->unk_1F22 == 6) {
                        if (var_s0->unk_1F0A == 3) {
                            Message_HandleOcarina(play);
                            goto block_217;
                        }
                        temp_s1->msgMode = 0x42;
                        temp_a3 = &play->msgCtx.font;
                        if (var_s0->unk_2020 == 0) {
                            sp5C = temp_a3;
                            sp54 = (s32) var_t0;
                            play_sound(0x482EU);
                            if (var_t0 == 0xBF) {
                                Font_LoadMessageBoxEndIcon(temp_a3, 1U);
                            } else {
                                Font_LoadMessageBoxEndIcon(temp_a3, 0U);
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
                    *gfxP = sp134;
                    return;
                case 0x1A:                          /* switch 2 */
                    if (var_s0->unk_1F22 == 6) {
                        play_sound(0U);
                        temp_s1->msgMode = 0x42;
                        temp_s1->textboxEndType = 0x30;
                    }
                    *gfxP = sp134;
                    return;
                case 0x19:                          /* switch 2 */
                    if (var_s0->unk_1F22 == 6) {
                        temp_s1->msgMode = 0x42;
                        temp_s1->textboxEndType = 0x40;
                        Font_LoadMessageBoxEndIcon(&play->msgCtx.font, 0U);
                        play_sound(0x482EU);
                    }
                    *gfxP = sp134;
                    return;
                default:                            /* switch 2 */
                default:                            /* switch 1 */
                    var_s2 = temp_s1 + 0x10000;
                    switch (var_t0) {               /* switch 4; irregular */
                        case 0x8169:                /* switch 4 */
                        case 0x8175:                /* switch 4 */
                            temp_s1->textPosX = var_s0->unk_1FF4 - (s32) (6.0f * var_s0->unk_2098);
                            break;
                        case 0x8145:                /* switch 4 */
                            temp_s1->textPosX = var_s0->unk_1FF4 - (s32) (3.0f * var_s0->unk_2098);
                            break;
                        case 0x8148:                /* switch 4 */
                        case 0x8149:                /* switch 4 */
                            temp_s1->textPosX = var_s0->unk_1FF4 - (s32) (2.0f * var_s0->unk_2098);
                            break;
                    }
                    if ((var_s0->unk_1F22 == 6) && (var_s0->unk_1FEE == (var_s3 + 1))) {
                        sp54 = (s32) var_t0;
                        play_sound(0U);
                    }
                    if (((s32) var_t0 >= 0xB0) && ((s32) var_t0 < 0xBC)) {
                        temp_v0_23 = var_t0 + D_801D08CC;
                        sp12E = var_s0->unk_2018;
                        sp12C = var_s0->unk_201A;
                        temp_a3_2 = &play->msgCtx.font;
                        sp12A = var_s0->unk_201C;
                        temp_s1->textColorR = *(D_801D083C + (temp_v0_23->unk_-B0 * 6U));
                        temp_s1->textColorG = (D_801D083C + (temp_v0_23->unk_-B0 * 6U))->unk_2;
                        temp_s1->textColorB = (D_801D083C + (temp_v0_23->unk_-B0 * 6U))->unk_4;
                        sp54 = (s32) var_t0;
                        Message_DrawTextChar(play, temp_a3_2 + (temp_a3_2->unk_11D88 * 0x3C00) + sp13A, &sp134);
                        var_t0 = (u8) sp54;
                        temp_s1->textColorR = sp12E;
                        temp_s1->textColorG = sp12C;
                        temp_s1->textColorB = sp12A;
                    } else {
                        temp_a3_3 = &play->msgCtx.font;
                        if ((s32) var_s0->unk_1F22 >= 0x4D) {
                            temp_v0_24 = var_s0->unk_1FF0;
                            if ((var_s3 < (temp_v0_24 - 6)) || (var_s3 >= (temp_v0_24 - 4))) {
                                temp_a3_4 = &play->msgCtx.font;
                                sp54 = (s32) var_t0;
                                Message_DrawTextChar(play, temp_a3_4 + (temp_a3_4->unk_11D88 * 0x3C00) + sp13A, &sp134);
                                goto block_181;
                            }
                        } else {
                            sp54 = (s32) var_t0;
                            Message_DrawTextChar(play, temp_a3_3 + (temp_a3_3->unk_11D88 * 0x3C00) + sp13A, &sp134);
block_181:
                            var_t0 = (u8) sp54;
                        }
                    }
                    sp13A += 0x80;
                    switch (var_t0) {               /* switch 5; irregular */
                        case 0x8144:                /* switch 5 */
                            temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (8.0f * var_s0->unk_2098);
                            break;
                        case 0x816A:                /* switch 5 */
                        case 0x8176:                /* switch 5 */
                            temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (10.0f * var_s0->unk_2098);
                            break;
                        case 0x8141:                /* switch 5 */
                        case 0x8142:                /* switch 5 */
                        case 0x8168:                /* switch 5 */
                            temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (12.0f * var_s0->unk_2098);
                            break;
                        case 0x8194:                /* switch 5 */
                            temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (14.0f * var_s0->unk_2098);
                            break;
                        case 0x8145:                /* switch 5 */
                            temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (15.0f * var_s0->unk_2098);
                            break;
                        default:                    /* switch 5 */
                            temp_v1_8 = var_s0->unk_2020;
                            if (((temp_v1_8 == 0x62) && (temp_v0_25 = var_s0->unk_20C0, ((var_s3 < temp_v0_25) == 0)) && ((temp_v0_25 + 4) >= var_s3)) || ((temp_v1_8 == 0x63) && (temp_v0_26 = var_s0->unk_20C0, ((var_s3 < temp_v0_26) == 0)) && ((temp_v0_26 + 2) >= var_s3)) || ((temp_v1_8 == 0x60) && (temp_v0_27 = var_s0->unk_20C0, ((var_s3 < temp_v0_27) == 0)) && ((temp_v0_27 + 2) >= var_s3)) || ((temp_v1_8 == 0x61) && (temp_v0_28 = var_s0->unk_20C0, ((var_s3 < temp_v0_28) == 0)) && ((temp_v0_28 + 1) >= var_s3))) {
                                temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (16.0f * var_s0->unk_2098);
                            } else {
                                temp_s1->textPosX = var_s0->unk_1FF4 + (s32) (*(&D_801D03F0 + (var_t0 * 4)) * var_s0->unk_2098);
                            }
                            break;
                    }
                    goto block_210;
            }
        }
    } else {
block_212:
        temp_v0_29 = var_s0->unk_2024;
        if (temp_v0_29 == 0) {
            temp_s1->textDrawPos = var_s3 + 1;
            temp_s1->textDelayTimer = 0;
            if (var_s0->unk_1F22 == 9) {
                temp_s1->msgMode = 6;
            }
        } else {
            temp_s1->textDelayTimer = temp_v0_29 - 1;
        }
block_217:
        *gfxP = sp134;
    }
}
