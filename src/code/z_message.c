#include "global.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#if 0

s16 D_801D02D8[15] = {
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE5, ACTOR_OCEFF_WIPE5, // Sonata of Awakening Effect, Sonata of Awakening Effect
    ACTOR_OCEFF_WIPE,  ACTOR_OCEFF_WIPE7, // Song of Time Effect, Song of Healing Effect
    ACTOR_OCEFF_WIPE2, ACTOR_OCEFF_WIPE6, // Epona's Song Effect, Song of Soaring Effect
    ACTOR_OCEFF_STORM, ACTOR_OCEFF_SPOT,  // Song of Storms Effect II [?], Sun's Song Effect
    ACTOR_OCEFF_WIPE, ACTOR_OCEFF_WIPE,   // Song of Time Effect, Song of Time Effect
    ACTOR_OCEFF_WIPE4                     // Scarecrow's Song Effect 
};
s32 D_801D02F8[15] = { 0,1,2,3,4,0,1,0,0,0,0,0,1,1,0 };

#endif

extern u16 D_801C6AB8[];
extern u16 D_801C6B28[];
extern s16 D_801D02D8[];
extern s32 D_801D02F8[];
extern s16 D_801F6B0C;
extern s16 D_801F6B0E;
extern s16 D_801F6B10;
extern s16 D_801F6B12;
extern s16 D_801F6B14;
extern s16 D_801F6B16;
extern s16 D_801F6B18;
extern s16 D_801F6B1A;
extern s16 D_801F6B1C;
extern s16 D_801F6B1E;
extern s16 D_801F6B20;
extern s16 D_801F6B22;
extern MessageTableEntry D_801C6B98[];
extern MessageTableEntry D_801CFB08[];

void func_80147520(void) {
    D_801CFC98 = 0xFF;
    D_801CFCA4[0] = D_801CFCA4[1] = D_801CFCA4[2] = D_801CFCA4[3] = D_801CFCA4[4] = D_801CFCA4[5] = D_801CFCA4[6] =
        D_801CFCA4[7] = D_801CFCA4[8] = 0;
}

void func_80147564(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->unk1204A[0] = 0xBD;
    msgCtx->unk1204A[1] = 0xB8;
    msgCtx->unk1204A[2] = 0xB3;
    msgCtx->unk1204A[3] = 0xAE;
    msgCtx->unk1204A[4] = 0xA9;
    func_80147520();
    D_801F6B0C = 0x50;
    D_801F6B10 = 0x96;
    D_801F6B0E = 0xFF;
    D_801F6B12 = 0xA;
    D_801F6B16 = 0xA;
    D_801F6B14 = 0xA;
    D_801F6B18 = 0xFF;
    D_801F6B1C = 0xFF;
    D_801F6B1A = 0x32;
    D_801F6B1E = 0xA;
    D_801F6B22 = 0xA;
    D_801F6B20 = 0xA;
}

s32 Message_ShouldAdvance(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->unk12020 == 0x10) || (msgCtx->unk12020 == 0x11)) {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
            CHECK_BTN_ALL(controller->press.button, BTN_CUP)) {
            play_sound(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

s32 Message_ShouldAdvanceSilent(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if (msgCtx->unk12020 == 0x10 || msgCtx->unk12020 == 0x11) {
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

void func_801477B4(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.msgLength != 0) {
        msgCtx->stateTimer = 2;
        msgCtx->msgMode = 0x43;
        msgCtx->unk12020 = 0;
        play_sound(NA_SE_PL_WALK_GROUND - SFX_FLAG);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147818.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80147F18.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148558.s")

#ifdef NON_MATCHING
void func_80148B98(PlayState* play, u8 arg1) {
    static s16 held = 0;
    MessageContext* msgCtx = &play->msgCtx;
    Input* curInput = CONTROLLER1(&play->state);

    if ((curInput->rel.stick_y > 29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex--;
        if (msgCtx->choiceIndex > 128) {
            msgCtx->choiceIndex = 0;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    } else if ((curInput->rel.stick_y < -29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex++;
        if (msgCtx->choiceIndex > arg1) {
            msgCtx->choiceIndex = arg1;
        } else {
            play_sound(NA_SE_SY_CURSOR);
        }
        return;
    } else {
        if (ABS_ALT(curInput->rel.stick_y) < 30) {
            held = 0;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148B98.s")
#endif

void func_80148CBC(PlayState* play, UNK_PTR puParm2, u8 arg2) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->unk11FF4 = 0x30;
    if (arg2 == 1) {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[1 + msgCtx->choiceIndex];
    } else {
        msgCtx->unk11FF6 = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    func_80147818(play, puParm2, msgCtx->unk11FF4, msgCtx->unk11FF6);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149048.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801491DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149454.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801496C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014995C.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149C18.s")

void Message_FindMessage(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    Font* font = &msgCtx->font;
    MessageTableEntry* msgEntry = msgCtx->messageEntryTable;
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

    msgEntry = msgCtx->messageEntryTable;
    foundSegment = msgEntry->segment;
    msgEntry++;
    nextSegment = msgEntry->segment;
    font->messageStart = foundSegment - segment;
    font->messageEnd = nextSegment - foundSegment;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149F74.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014AAD0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014ADBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014C70C.s")

void Message_LoadChar(PlayState* play, u16 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    Font_LoadChar(play, codePointIndex, temp1);
    msgCtx->decodedBuffer.wchar[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->unk12098);
    *offset = temp1;
    *arg3 = temp2;
}

// Message_LoadRupees JPN ?
void func_8014CCB4(PlayState* play, s16* decodedBufPos, s32* offset, f32* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    s16 t = *decodedBufPos;
    s32 k = *offset;
    f32 f = *arg3;

    Font_LoadChar(play, 0x838B, k); // 0x838B = ル in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x838B;
    t += 1;
    Font_LoadChar(play, 0x8373, k); // 0x8373 = ピ in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x8373;
    t += 1;
    Font_LoadChar(play, 0x815C, k); // Ox815C = ― in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x815C;

    f += 16.0f * msgCtx->unk12098 * 3.0f;
    *decodedBufPos = t;
    *offset = k;
    *arg3 = f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D304.s")

#ifdef NON_EQUIVALENT
extern u16* D_801D0188;
extern s16* D_801D0250;

void func_8014D62C(PlayState* play, s32* arg1, f32* arg2, s16* arg3) {
    f32 sp3C;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_s1_2;
    s16 temp_s6;
    s32 temp_s2;
    s32 temp_s2_2;
    u16* temp_v0;
    s16 phi_v0;
    s16 phi_s0;
    s16 phi_s1;
    s32 phi_s2;
    s16 phi_s1_2;
    s32 phi_s2_2;

    temp_s1 = *arg3;
    temp_s2 = *arg1;
    sp3C = *arg2;
    if ((func_8010A0A4(play) != 0) || (play->sceneNum == 0x4F)) {
        phi_v0 = 0xA;
    } else {
        phi_v0 = play->pauseCtx.unk_238[PAUSE_WORLD_MAP];
    }
    temp_s6 = *(&D_801D0250 + (phi_v0 * 2));
    phi_s0 = 0;
    phi_s1_2 = temp_s1;
    phi_s2_2 = temp_s2;
    if ((s32)temp_s6 > 0) {
        phi_s1 = temp_s1;
        phi_s2 = temp_s2;
        do {
            temp_v0 = (phi_v0 * 0x12) + &D_801D0188 + (phi_s0 * 2);
            (play + 0x4908 + (phi_s1 * 2))->decodedBuffer = (u16)*temp_v0;
            Font_LoadChar(play, *temp_v0, phi_s2);
            temp_s0 = phi_s0 + 1;
            temp_s1_2 = phi_s1 + 1;
            temp_s2_2 = phi_s2 + 0x80;
            phi_s0 = temp_s0;
            phi_s1 = temp_s1_2;
            phi_s2 = temp_s2_2;
            phi_s1_2 = temp_s1_2;
            phi_s2_2 = temp_s2_2;
        } while ((s32)temp_s0 < (s32)temp_s6);
    }
    *arg3 = phi_s1_2 - 1;
    *arg1 = phi_s2_2;
    *arg2 = sp3C + ((f32)(temp_s6 - 1) * (16.0f * play->msgCtx.unk12098));
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D62C.s")
#endif

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801514B0.s")

void Message_StartTextbox(PlayState* play, u16 textId, Actor* Actor) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaAction = 0xFFFF;
    func_80150D08(play, textId);
    msgCtx->unkActor = Actor;
    msgCtx->msgMode = 1;
    msgCtx->stateTimer = 0;
    msgCtx->unk12024 = 0;
    play->msgCtx.ocarinaMode = 0;
}

void func_80151938(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    msgCtx->msgLength = 0;
    func_80150D08(play, textId);
    func_80150A84(play);
    msgCtx->msgMode = 5;
    msgCtx->stateTimer = 8;
    msgCtx->unk12024 = 0;

    if (interfaceCtx->unk_222 == 0) {
        if (textId != 0x1B93) {
            func_8011552C(play, 0x10);
        } else if (textId != 0xF8) {
            func_8011552C(play, 6);
        }
    }
    msgCtx->unk1203C = msgCtx->unk1203A;

    if (play->pauseCtx.unk_1F0 != 0) {
        msgCtx->unk12004 = 0x22;
        msgCtx->unk12006 = 0x15E;
        func_80149C18(play);
        msgCtx->stateTimer = 1;
    }
}

void func_80151A68(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->msgLength = 0;
    func_80150D08(play, textId);
    func_80150A84(play);
    func_8015B198(play);
    msgCtx->msgMode = 0x45;
    msgCtx->unk12024 = 0;
    msgCtx->unk1203C = msgCtx->unk1203A = msgCtx->unk1201E = 0;
    msgCtx->stateTimer = 30;

    // Day/Dawn/Night.. Messages
    if ((msgCtx->currentTextId >= 0x1BB2) && (msgCtx->currentTextId <= 0x1BB6)) {
        XREG(74) = 0x6A;
        XREG(75) = 0;
        XREG(77) = 0x58;
        XREG(76) = 0x44;
    } else {
        XREG(74) = 0x42;
        XREG(75) = 0x1E;
        XREG(77) = 0x3C;
        XREG(76) = 0x1C;
        msgCtx->unk11F1A[0] = msgCtx->unk11F1A[1] = msgCtx->unk11F1A[2] = 0;
        Interface_ChangeAlpha(1);
    }
}

void func_80151BB4(PlayState* play, u8 arg1) {
    MessageContext* msgCtx = &play->msgCtx;
    u8 temp = arg1;

    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        if ((gSaveContext.save.weekEventReg[D_801C6B28[arg1] >> 8] & (u8)D_801C6B28[arg1]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    } else if (arg1 >= 20) {
        if ((gSaveContext.save.weekEventReg[D_801C6B28[arg1] >> 8] & (u8)D_801C6B28[arg1]) == 0) {
            msgCtx->unk120B2[msgCtx->unk120B1] = temp;
            msgCtx->unk120B1++;
        }
    }
}

u32 func_80151C9C(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    while (true) {
        if (msgCtx->unk120B1 == 0) {
            return false;
        }
        msgCtx->unk120B1--;

        if ((gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8] &
             (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]]) == 0) {
            gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8] =
                ((void)0, gSaveContext.save.weekEventReg[D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]] >> 8]) |
                (u8)D_801C6B28[msgCtx->unk120B2[msgCtx->unk120B1]];

            if ((D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]] != 0) && CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                func_80151938(play, D_801C6AB8[msgCtx->unk120B2[msgCtx->unk120B1]]);
                play_sound(NA_SE_SY_SCHEDULE_WRITE);
                return true;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151DA4.s")

void func_80152434(PlayState* play, u16 arg2) {
    play->msgCtx.unk12046 = 0;
    func_80151DA4(play, arg2);
}

void func_80152464(PlayState* play, u16 arg1) {
    play->msgCtx.unk12046 = 1;
    func_80151DA4(play, arg1);
}

/**
 * @return u8 A value of the TextState enum representing the current state of the on-screen message
 */
u8 Message_GetState(MessageContext* msgCtx) {
    if (msgCtx->msgLength == 0) {
        return TEXT_STATE_NONE;
    }

    if (msgCtx->msgMode == 0x42) {
        if (msgCtx->unk11F14 != 0xFFFF) {
            return TEXT_STATE_1;
        }

        if ((msgCtx->unk12020 == 0x10) || (msgCtx->unk12020 == 0x11)) {
            return TEXT_STATE_CHOICE;
        }
        if ((msgCtx->unk12020 == 0x40) || (msgCtx->unk12020 == 0x42) || (msgCtx->unk12020 == 0x30)) {
            return TEXT_STATE_5;
        }
        if (msgCtx->unk12020 == 0x41) {
            return TEXT_STATE_16;
        }
        if ((msgCtx->unk12020 >= 0x50) && (msgCtx->unk12020 < 0x58)) {
            return TEXT_STATE_3;
        }
        if ((msgCtx->unk12020 == 0x60) || (msgCtx->unk12020 == 0x61)) {
            return TEXT_STATE_14;
        }
        if (msgCtx->unk12020 == 0x62) {
            return TEXT_STATE_15;
        }
        if (msgCtx->unk12020 == 0x63) {
            return TEXT_STATE_17;
        }
        if (msgCtx->unk12020 == 0x12) {
            return TEXT_STATE_18;
        }
        return TEXT_STATE_DONE;
    }

    if (msgCtx->msgMode == 0x41) {
        return TEXT_STATE_10;
    }
    if (msgCtx->msgMode == 0x1B) {
        return TEXT_STATE_7;
    }
    if ((msgCtx->ocarinaMode == 3) || (msgCtx->msgMode == 0x37)) {
        return TEXT_STATE_8;
    }
    if (msgCtx->msgMode == 0x20) {
        return TEXT_STATE_9;
    }
    if ((msgCtx->msgMode == 0x21) || (msgCtx->msgMode == 0x3A)) {
        return TEXT_STATE_11;
    }
    if (msgCtx->msgMode == 0x3D) {
        return TEXT_STATE_12;
    }
    if (msgCtx->msgMode == 0x40) {
        return TEXT_STATE_13;
    }
    if ((msgCtx->msgMode == 0x43) && (msgCtx->stateTimer == 1) && (msgCtx->unk120B1 == 0)) {
        return TEXT_STATE_CLOSING;
    }

    return TEXT_STATE_3;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015268C.s")

void func_80152C64(View* view) {
    SET_FULLSCREEN_VIEWPORT(view);
    func_8013FBC8(view);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152CAC.s")

// Spawn song effect?
void func_80152EC0(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);

    if (1) {}
    if ((msgCtx->songPlayed < 0x17) && (msgCtx->songPlayed != 0xE) &&
        ((msgCtx->ocarinaAction < 0x43) || (msgCtx->ocarinaAction >= 0x47))) {
        msgCtx->unk120B0 = 1;
        if (msgCtx->songPlayed != 0x16) {
            Actor_Spawn(&play->actorCtx, play, D_801D02D8[msgCtx->songPlayed], player->actor.world.pos.x,
                        player->actor.world.pos.y, player->actor.world.pos.z, 0, 0, 0, D_801D02F8[msgCtx->songPlayed]);
            return;
        }
        Actor_Spawn(&play->actorCtx, play, ACTOR_OCEFF_WIPE4, player->actor.world.pos.x, player->actor.world.pos.y,
                    player->actor.world.pos.z, 0, 0, 0, 0);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152FB8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153750.s")

void func_80153E7C(PlayState* play, void* arg1) {
    if ((gSaveContext.options.language == 0) && (play->msgCtx.unk12090 == 0)) {
        func_8014ADBC(play, arg1);
        return;
    }
    if (play->msgCtx.unk12090 != 0) {
        func_8015E7EC(play, arg1);
        return;
    }
    func_8015966C(play, arg1, 0);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801541D4.s")

void func_80156758(PlayState* play) {
    Gfx* nextDisplayList;
    Gfx* polyOpa;
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);
    polyOpa = POLY_OPA_DISP;
    nextDisplayList = Graph_GfxPlusOne(polyOpa);
    gSPDisplayList(OVERLAY_DISP++, nextDisplayList);

    if ((play->msgCtx.currentTextId != 0x5E6) || !Play_InCsMode(play)) {
        func_801541D4(play, &nextDisplayList);
    }

    gSPEndDisplayList(nextDisplayList++);
    Graph_BranchDlist(polyOpa, nextDisplayList);
    POLY_OPA_DISP = nextDisplayList;
    CLOSE_DISPS(gfxCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015680C.s")

void func_801586A4(PlayState* play) {
    play->msgCtx.messageEntryTableNes = D_801C6B98;
    play->msgCtx.messageTableStaff = D_801CFB08;
}

void Message_Init(PlayState* play) {
    Font* font;
    MessageContext* messageCtx = &play->msgCtx;

    func_801586A4(play);
    play->msgCtx.ocarinaMode = 0;
    messageCtx->msgMode = 0;
    messageCtx->msgLength = 0;
    messageCtx->currentTextId = 0;
    messageCtx->unk12020 = 0;
    messageCtx->choiceIndex = 0;
    messageCtx->ocarinaAction = messageCtx->unk11FF2 = 0;
    messageCtx->unk1201E = 0xFF;
    View_Init(&messageCtx->view, play->state.gfxCtx);
    messageCtx->unk11EF8 = THA_AllocEndAlign16(&play->state.heap, 0x13C00);
    font = &play->msgCtx.font;
    Font_LoadOrderedFont(&play->msgCtx.font);
    font->unk_11D88 = 0;
    messageCtx->unk12090 = messageCtx->unk12092 = 0;
    messageCtx->unk12094 = 0;
    messageCtx->unk1209C = 0;
    messageCtx->unk120A0 = 0;
    messageCtx->unk12068 = 0x34;
    messageCtx->unk1206A = 0x24;
    messageCtx->unk120B0 = 0;
    messageCtx->unk120BE = 0;
    messageCtx->unk120C0 = 0;
    messageCtx->unk120C2 = 0;
    messageCtx->unk120C4 = 0;
    messageCtx->unk120C8 = 0;
    messageCtx->unk120CA = 0;
    messageCtx->unk120CC = 0;
    messageCtx->unk120CE = 0;
    messageCtx->unk120D0 = 0;
    messageCtx->unk120D2 = 0;
    messageCtx->unk120D4 = 0;
    messageCtx->unk120D6 = 0;
}
