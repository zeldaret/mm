#include "global.h"
#include "z64shrink_window.h"
#include "z64view.h"
#include "message_data_static.h"
#include "overlays/kaleido_scope/ovl_kaleido_scope/z_kaleido_scope.h"

#if 0
#define DEFINE_PERSON(_enum, _photo, _description, _metEnum, metMessage, _metFlag) metMessage,
#define DEFINE_EVENT(_enum, _icon, _colorFlag, _description, completedMessage, _completedFlag) completedMessage,

u16 sBombersNotebookEventMessages[BOMBERS_NOTEBOOK_EVENT_MAX] = {
#include "tables/bombers_notebook/person_table.h"
#include "tables/bombers_notebook/event_table.h"
};

#undef DEFINE_PERSON
#undef DEFINE_EVENT

#define DEFINE_PERSON(_enum, _photo, _description, _metEnum, _metMessage, metFlag) metFlag,
#define DEFINE_EVENT(_enum, _icon, _colorFlag, _description, _completedMessage, completedFlag) completedFlag,

u16 gBombersNotebookWeekEventFlags[BOMBERS_NOTEBOOK_EVENT_MAX] = {
#include "tables/bombers_notebook/person_table.h"
#include "tables/bombers_notebook/event_table.h"
};

#undef DEFINE_PERSON
#undef DEFINE_EVENT

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

    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_A] = 189;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_DOWN] = 184;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_RIGHT] = 179;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_LEFT] = 174;
    msgCtx->ocarinaButtonsPosY[OCARINA_BTN_C_UP] = 169;
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

    if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_11)) {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A)) {
            Audio_PlaySfx(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        if (CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
            CHECK_BTN_ALL(controller->press.button, BTN_CUP)) {
            Audio_PlaySfx(NA_SE_SY_MESSAGE_PASS);
        }
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

s32 Message_ShouldAdvanceSilent(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Input* controller = CONTROLLER1(&play->state);

    if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_11)) {
        return CHECK_BTN_ALL(controller->press.button, BTN_A);
    } else {
        return CHECK_BTN_ALL(controller->press.button, BTN_A) || CHECK_BTN_ALL(controller->press.button, BTN_B) ||
               CHECK_BTN_ALL(controller->press.button, BTN_CUP);
    }
}

void Message_CloseTextbox(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    if (play->msgCtx.msgLength != 0) {
        msgCtx->stateTimer = 2;
        msgCtx->msgMode = 0x43;
        msgCtx->textboxEndType = TEXTBOX_ENDTYPE_00;
        Audio_PlaySfx(NA_SE_NONE);
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
            Audio_PlaySfx(NA_SE_SY_CURSOR);
        }
        return;
    } else if ((curInput->rel.stick_y < -29) && held == 0) {
        held = 1;
        msgCtx->choiceIndex++;
        if (msgCtx->choiceIndex > arg1) {
            msgCtx->choiceIndex = arg1;
        } else {
            Audio_PlaySfx(NA_SE_SY_CURSOR);
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

    msgCtx->textPosX = 0x30;
    if (arg2 == 1) {
        msgCtx->textPosY = msgCtx->unk11FFE[1 + msgCtx->choiceIndex];
    } else {
        msgCtx->textPosY = msgCtx->unk11FFE[msgCtx->choiceIndex];
    }
    func_80147818(play, puParm2, msgCtx->textPosX, msgCtx->textPosY);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80148D64.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149048.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801491DC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80149454.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801496C8.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_DrawTextChar.s")

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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_HandleOcarina.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014ADBC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_LoadItemIcon.s")

void Message_LoadChar(PlayState* play, u16 codePointIndex, s32* offset, f32* arg3, s16 decodedBufPos) {
    MessageContext* msgCtx = &play->msgCtx;
    s32 temp1 = *offset;
    f32 temp2 = *arg3;

    Font_LoadChar(play, codePointIndex, temp1);
    msgCtx->decodedBuffer.wchar[decodedBufPos] = codePointIndex;
    temp1 += FONT_CHAR_TEX_SIZE;
    temp2 += (16.0f * msgCtx->textCharScale);
    *offset = temp1;
    *arg3 = temp2;
}

// TODO: SJIS support
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
    Font_LoadChar(play, 0x815C, k); // 0x815C = ― in JISX0213
    k += FONT_CHAR_TEX_SIZE;
    msgCtx->decodedBuffer.wchar[t] = 0x815C;

    f += 16.0f * msgCtx->textCharScale * 3.0f;
    *decodedBufPos = t;
    *offset = k;
    *arg3 = f;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CDF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014CFDC.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D304.s")

extern u16 D_801D0188[OWL_WARP_MAX][9];
extern s16 D_801D0250[OWL_WARP_MAX];

void func_8014D62C(PlayState* play, s32* arg1, f32* arg2, s16* arg3) {
    MessageContext* msgCtx = &play->msgCtx;
    PauseContext* pauseCtx = &play->pauseCtx;
    s16 stringLimit;
    s16 temp_s1 = *arg3;
    s32 temp_s2 = *arg1;
    f32 sp3C = *arg2;
    s16 owlWarpId;
    s16 phi_s0;

    if (func_8010A0A4(play) || (play->sceneId == SCENE_SECOM)) {
        owlWarpId = OWL_WARP_ENTRANCE;
    } else {
        owlWarpId = pauseCtx->cursorPoint[PAUSE_WORLD_MAP];
    }
    stringLimit = D_801D0250[owlWarpId];

    for (phi_s0 = 0; phi_s0 < stringLimit; phi_s0++, temp_s1++, temp_s2 += 0x80) {
        msgCtx->decodedBuffer.wchar[temp_s1] = D_801D0188[owlWarpId][phi_s0];
        Font_LoadChar(play, D_801D0188[owlWarpId][phi_s0], temp_s2);
    }

    temp_s1--;
    sp3C += (stringLimit - 1) * (16.0f * msgCtx->textCharScale);

    *arg3 = temp_s1;
    *arg1 = temp_s2;
    *arg2 = sp3C;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8014D7B4.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150A84.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80150D08.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801514B0.s")

void Message_StartTextbox(PlayState* play, u16 textId, Actor* actor) {
    MessageContext* msgCtx = &play->msgCtx;

    msgCtx->ocarinaAction = 0xFFFF;
    func_80150D08(play, textId);
    msgCtx->talkActor = actor;
    msgCtx->msgMode = 1;
    msgCtx->stateTimer = 0;
    msgCtx->textDelayTimer = 0;
    play->msgCtx.ocarinaMode = 0;
}

void Message_ContinueTextbox(PlayState* play, u16 textId) {
    MessageContext* msgCtx = &play->msgCtx;
    InterfaceContext* interfaceCtx = &play->interfaceCtx;

    msgCtx->msgLength = 0;
    func_80150D08(play, textId);
    func_80150A84(play);
    msgCtx->msgMode = 5;
    msgCtx->stateTimer = 8;
    msgCtx->textDelayTimer = 0;

    if (interfaceCtx->unk_222 == 0) {
        if (textId != 0x1B93) {
            func_8011552C(play, DO_ACTION_NEXT);
        } else if (textId != 0xF8) {
            func_8011552C(play, DO_ACTION_DECIDE);
        }
    }
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget;

    if (play->pauseCtx.bombersNotebookOpen) {
        msgCtx->textboxXTarget = 0x22;
        msgCtx->textboxYTarget = 0x15E;
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
    msgCtx->textDelayTimer = 0;
    msgCtx->textboxColorAlphaCurrent = msgCtx->textboxColorAlphaTarget = msgCtx->textColorAlpha = 0;
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
        Interface_SetHudVisibility(HUD_VISIBILITY_NONE);
    }
}

void Message_BombersNotebookQueueEvent(PlayState* play, u8 event) {
    MessageContext* msgCtx = &play->msgCtx;

    if (CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
        if (!CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[event])) {
            msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount] = event;
            msgCtx->bombersNotebookEventQueueCount++;
        }
    } else if (event >= BOMBERS_NOTEBOOK_PERSON_MAX) {
        // Non MET events are processed even if the player does not have the notebook yet
        if (!CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags[event])) {
            msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount] = event;
            msgCtx->bombersNotebookEventQueueCount++;
        }
    }
}

u32 func_80151C9C(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;

    while (true) {
        if (msgCtx->bombersNotebookEventQueueCount == 0) {
            return false;
        }
        msgCtx->bombersNotebookEventQueueCount--;

        if (!CHECK_WEEKEVENTREG(gBombersNotebookWeekEventFlags
                                    [msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount]])) {
            SET_WEEKEVENTREG(gBombersNotebookWeekEventFlags
                                 [msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount]]);

            if ((sBombersNotebookEventMessages
                     [msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount]] != 0) &&
                CHECK_QUEST_ITEM(QUEST_BOMBERS_NOTEBOOK)) {
                Message_ContinueTextbox(
                    play, sBombersNotebookEventMessages
                              [msgCtx->bombersNotebookEventQueue[msgCtx->bombersNotebookEventQueueCount]]);
                Audio_PlaySfx(NA_SE_SY_SCHEDULE_WRITE);
                return true;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80151DA4.s")

void func_80152434(PlayState* play, u16 arg2) {
    play->msgCtx.blockSunsSong = false;
    func_80151DA4(play, arg2);
}

void func_80152464(PlayState* play, u16 arg1) {
    play->msgCtx.blockSunsSong = true;
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
        if (msgCtx->nextTextId != 0xFFFF) {
            return TEXT_STATE_1;
        }

        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_10) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_11)) {
            return TEXT_STATE_CHOICE;
        }
        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_40) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_42) ||
            (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_30)) {
            return TEXT_STATE_5;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_41) {
            return TEXT_STATE_16;
        }
        if ((msgCtx->textboxEndType >= TEXTBOX_ENDTYPE_50) && (msgCtx->textboxEndType <= TEXTBOX_ENDTYPE_57)) {
            return TEXT_STATE_3;
        }
        if ((msgCtx->textboxEndType == TEXTBOX_ENDTYPE_60) || (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_61)) {
            return TEXT_STATE_14;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_62) {
            return TEXT_STATE_15;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_63) {
            return TEXT_STATE_17;
        }
        if (msgCtx->textboxEndType == TEXTBOX_ENDTYPE_12) {
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
    if ((msgCtx->msgMode == 0x43) && (msgCtx->stateTimer == 1) && (msgCtx->bombersNotebookEventQueueCount == 0)) {
        return TEXT_STATE_CLOSING;
    }

    return TEXT_STATE_3;
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_8015268C.s")

void func_80152C64(View* view) {
    SET_FULLSCREEN_VIEWPORT(view);
    View_ApplyOrthoToOverlay(view);
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80152CAC.s")

// Spawn song effect?
void func_80152EC0(PlayState* play) {
    MessageContext* msgCtx = &play->msgCtx;
    Player* player = GET_PLAYER(play);

    if (1) {}
    if ((msgCtx->songPlayed < 0x17) && (msgCtx->songPlayed != 0xE) &&
        ((msgCtx->ocarinaAction < 0x43) || (msgCtx->ocarinaAction >= 0x47))) {
        msgCtx->ocarinaSongEffectActive = true;
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

void func_80153E7C(PlayState* play, Gfx** gfxP) {
    if ((gSaveContext.options.language == 0) && !play->msgCtx.textIsCredits) {
        func_8014ADBC(play, gfxP);
    } else if (play->msgCtx.textIsCredits) {
        Message_DrawTextCredits(play, gfxP);
    } else {
        func_8015966C(play, gfxP, 0);
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_80153EF0.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/func_801541D4.s")

void Message_Draw(PlayState* play) {
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

#pragma GLOBAL_ASM("asm/non_matchings/code/z_message/Message_Update.s")

void func_801586A4(PlayState* play) {
    play->msgCtx.messageEntryTableNes = D_801C6B98;
    play->msgCtx.messageTableStaff = D_801CFB08;
}

void Message_Init(PlayState* play) {
    Font* font;
    MessageContext* msgCtx = &play->msgCtx;

    func_801586A4(play);
    play->msgCtx.ocarinaMode = 0;
    msgCtx->msgMode = 0;
    msgCtx->msgLength = 0;
    msgCtx->currentTextId = 0;
    msgCtx->textboxEndType = 0;
    msgCtx->choiceIndex = 0;
    msgCtx->ocarinaAction = msgCtx->textUnskippable = 0;
    msgCtx->textColorAlpha = 0xFF;
    View_Init(&msgCtx->view, play->state.gfxCtx);
    msgCtx->textboxSegment = THA_AllocTailAlign16(&play->state.tha, 0x13C00);
    font = &play->msgCtx.font;
    Font_LoadOrderedFont(&play->msgCtx.font);
    font->unk_11D88 = 0;
    msgCtx->textIsCredits = msgCtx->messageHasSetSfx = false;
    msgCtx->textboxSkipped = 0;
    msgCtx->textFade = 0;
    msgCtx->ocarinaAvailableSongs = 0;
    msgCtx->textboxX = 0x34;
    msgCtx->textboxY = 0x24;
    msgCtx->ocarinaSongEffectActive = false;
    msgCtx->unk120BE = 0;
    msgCtx->unk120C0 = 0;
    msgCtx->unk120C2 = 0;
    msgCtx->unk120C4 = 0;
    msgCtx->unk120C8 = 0;
    msgCtx->unk120CA = 0;
    msgCtx->unk120CC = 0;
    msgCtx->unk120CE = 0;
    msgCtx->unk120D0 = 0;
    msgCtx->unk120D2 = 0;
    msgCtx->unk120D4 = 0;
    msgCtx->unk120D6 = 0;
}
