/*
 * File: z_en_time_tag.c
 * Overlay: ovl_En_Time_Tag
 * Description: Song of Soaring engraving; Rooftop Oath to Order event; Mikau's and Lulu's diary; Kick out of scene
 * event
 */

#include "z_en_time_tag.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnTimeTag*)thisx)

void EnTimeTag_Init(Actor* thisx, PlayState* play);
void EnTimeTag_Destroy(Actor* thisx, PlayState* play);
void EnTimeTag_Update(Actor* thisx, PlayState* play);

void EnTimeTag_RooftopOath_DoNothing(EnTimeTag* this, PlayState* play);
void EnTimeTag_RooftopOath_Cutscene(EnTimeTag* this, PlayState* play);
void EnTimeTag_RooftopOath_Wait(EnTimeTag* this, PlayState* play);

void EnTimeTag_SoaringEngraving_GetSong(EnTimeTag* this, PlayState* play);
void EnTimeTag_SoaringEngraving_StartCutscene(EnTimeTag* this, PlayState* play);
void EnTimeTag_SoaringEngraving_Wait(EnTimeTag* this, PlayState* play);

void EnTimeTag_Diary_AfterOcarina(EnTimeTag* this, PlayState* play);
void EnTimeTag_Diary_TeachEvanSongSnippets(EnTimeTag* this, PlayState* play);
void EnTimeTag_Diary_Cutscene(EnTimeTag* this, PlayState* play);
void EnTimeTag_Diary_Wait(EnTimeTag* this, PlayState* play);

void EnTimeTag_KickOut_DoNothing(EnTimeTag* this, PlayState* play);
void EnTimeTag_KickOut_Transition(EnTimeTag* this, PlayState* play);
void EnTimeTag_KickOut_WaitForEvent(EnTimeTag* this, PlayState* play);
void EnTimeTag_KickOut_WaitForTime(EnTimeTag* this, PlayState* play);

ActorInit En_Time_Tag_InitVars = {
    ACTOR_EN_TIME_TAG,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnTimeTag),
    (ActorFunc)EnTimeTag_Init,
    (ActorFunc)EnTimeTag_Destroy,
    (ActorFunc)EnTimeTag_Update,
    (ActorFunc)NULL,
};

void EnTimeTag_Init(Actor* thisx, PlayState* play) {
    EnTimeTag* this = THIS;

    this->actionFunc = EnTimeTag_KickOut_WaitForTime;

    switch (ENTIMETAG_GET_TYPE(&this->actor)) {
        case TIMETAG_KICKOUT_FINAL_HOURS:
            if ((gSaveContext.save.weekEventReg[8] & 0x40) || (CURRENT_DAY != 3)) {
                // Not final hours
                Actor_Kill(&this->actor);
                return;
            }
            // Overwrite kickout time to midnight
            ENTIMETEG_GET_KICKOUT_HOUR(&this->actor) = 0;
            ENTIMETEG_GET_KICKOUT_MINUTE(&this->actor) = 0;
            break;

        case TIMETAG_ROOFTOP_OATH:
            this->actionFunc = EnTimeTag_RooftopOath_Wait;
            this->actor.flags |= ACTOR_FLAG_2000000;
            break;

        case TIMETAG_SOARING_ENGRAVING:
            this->actionFunc = EnTimeTag_SoaringEngraving_Wait;
            this->actor.flags |= ACTOR_FLAG_2000000;
            if (CHECK_QUEST_ITEM(QUEST_SONG_SOARING)) {
                this->actor.textId = 0xC02;
            } else {
                this->actor.textId = 0;
            }
            break;

        case TIMETAG_DIARY:
            this->actionFunc = EnTimeTag_Diary_Wait;
            this->actor.textId = 0;
            ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 0;
            break;
    }
}

void EnTimeTag_Destroy(Actor* thisx, PlayState* play) {
}

void EnTimeTag_RooftopOath_DoNothing(EnTimeTag* this, PlayState* play) {
}

void EnTimeTag_RooftopOath_Cutscene(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);

        this->actionFunc = EnTimeTag_RooftopOath_DoNothing;
        gSaveContext.timerStates[TIMER_ID_MOON_CRASH] = TIMER_STATE_OFF;

        if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOLWA) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) &&
            CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
            gSaveContext.save.weekEventReg[25] |= 2;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnTimeTag_RooftopOath_Wait(EnTimeTag* this, PlayState* play) {
    EnTimeTag* this2 = this;

    if ((play->msgCtx.ocarinaMode == 3) && (play->msgCtx.lastPlayedSong == OCARINA_SONG_OATH)) {
        if (this->actor.cutscene != -1) {
            this->actionFunc = EnTimeTag_RooftopOath_Cutscene;
            ActorCutscene_SetIntentToPlay(this2->actor.cutscene);
            gSaveContext.timerStates[TIMER_ID_MOON_CRASH] = TIMER_STATE_OFF;
        }
        play->msgCtx.ocarinaMode = 4;
    }
}

void EnTimeTag_SoaringEngraving_GetSong(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        this->actionFunc = EnTimeTag_SoaringEngraving_Wait;
        this->actor.textId = 0xC02;
        Item_Give(play, ITEM_SONG_SOARING);
    }
}

void EnTimeTag_SoaringEngraving_StartCutscene(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actionFunc = EnTimeTag_SoaringEngraving_GetSong;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void EnTimeTag_SoaringEngraving_RepeatedInteraction(EnTimeTag* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        Message_CloseTextbox(play);
        this->actionFunc = EnTimeTag_SoaringEngraving_Wait;
    }
}

void EnTimeTag_SoaringEngraving_Wait(EnTimeTag* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->actor.textId == 0) {
            this->actionFunc = EnTimeTag_SoaringEngraving_StartCutscene;
        } else {
            this->actionFunc = EnTimeTag_SoaringEngraving_RepeatedInteraction;
        }
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play) &&
               (Flags_GetSwitch(play, ENTIMETAG_GET_SOARING_SWITCHFLAG(&this->actor)) ||
                CHECK_QUEST_ITEM(QUEST_SONG_SOARING))) {
        this->actor.flags |= ACTOR_FLAG_1;
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void EnTimeTag_Diary_AfterOcarina(EnTimeTag* this, PlayState* play) {
    if (ENTIMETAG_GET_DIARY_TIMER(&this->actor) > 0) {
        ENTIMETAG_GET_DIARY_TIMER(&this->actor)--;
        return;
    }

    if (ENTIMETAG_GET_DIARY_SONG(&this->actor) != TIMETAG_DIARY_SONG_EVAN_PART1) {
        // TIMETAG_DIARY_SONG_EVAN_PART2
        Message_ContinueTextbox(play, 0x1230);
    } else {
        // TIMETAG_DIARY_SONG_EVAN_PART1
        Message_ContinueTextbox(play, 0x122D);
    }

    this->actionFunc = EnTimeTag_Diary_Cutscene;
}

void EnTimeTag_Diary_TeachEvanSongSnippets(EnTimeTag* this, PlayState* play) {
    if ((play->msgCtx.ocarinaStaff->state == 0) && (play->msgCtx.msgMode == 0x1B)) {
        ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 5;
        this->actionFunc = EnTimeTag_Diary_AfterOcarina;
        play->msgCtx.msgLength = 0;
        play->msgCtx.msgMode = 0;
    }
}

void EnTimeTag_Diary_Cutscene(EnTimeTag* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x101C: // Lulu diary part 1
                    case 0x101D: // Lulu diary part 2
                    case 0x101E: // Lulu diary part 3
                    case 0x122D: // Mikau diary part 2
                        Message_ContinueTextbox(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x101F: // Lulu diary part 4
                    case 0x122A: // Can not read Zora script
                    case 0x1230: // Mikau diary part 4
                        Message_CloseTextbox(play);
                        this->actionFunc = EnTimeTag_Diary_Wait;
                        if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                            ActorCutscene_Stop(this->actor.cutscene);
                        }
                        break;

                    case 0x122B: // Mikau diary part 1
                        // Display ocarina Staff
                        func_80152434(play, 0x3F);
                        this->actionFunc = EnTimeTag_Diary_TeachEvanSongSnippets;
                        ENTIMETAG_GET_DIARY_SONG(&this->actor) = TIMETAG_DIARY_SONG_EVAN_PART1;
                        break;

                    case 0x122E: // Mikau diary part 3
                        // Display ocarina Staff
                        func_80152434(play, 0x40);
                        this->actionFunc = EnTimeTag_Diary_TeachEvanSongSnippets;
                        ENTIMETAG_GET_DIARY_SONG(&this->actor) = TIMETAG_DIARY_SONG_EVAN_PART2;
                        break;
                }
            }
            break;

        case TEXT_STATE_CLOSING:
            this->actionFunc = EnTimeTag_Diary_Wait;
            break;
    }

    if (ENTIMETAG_GET_DIARY_TIMER(&this->actor) != 0) {
        if (this->actor.cutscene == -1) {
            ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 0;
        } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 0;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void EnTimeTag_Diary_Wait(EnTimeTag* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            if (ENTIMETAG_GET_DIARY_TYPE(&this->actor) == TIMETAG_DIARY_LULU) {
                Message_StartTextbox(play, 0x101C, &this->actor);
            } else {
                // TIMETAG_DIARY_MIKAU
                Message_StartTextbox(play, 0x122B, &this->actor);
            }
            ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 1;
        } else {
            // unable to read Zora script
            Message_StartTextbox(play, 0x122A, &this->actor);

            //! FAKE:
            if (0) {}

            ((EnElf*)GET_PLAYER(play)->tatlActor)->unk_264 |= 4;
            Actor_ChangeFocus(&this->actor, play, GET_PLAYER(play)->tatlActor);
            ENTIMETAG_GET_DIARY_TIMER(&this->actor) = 0;
        }
        this->actionFunc = EnTimeTag_Diary_Cutscene;
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play)) {
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void EnTimeTag_KickOut_DoNothing(EnTimeTag* this, PlayState* play) {
}

void EnTimeTag_KickOut_Transition(EnTimeTag* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_5) {
        play->nextEntrance = play->setupExitList[ENTIMETAG_GET_KICKOUT_EXIT_INDEX(&this->actor)];
        play->transitionTrigger = TRANS_TRIGGER_START;
        if (ENTIMETAG_GET_TYPE(&this->actor) == TIMETAG_KICKOUT_DOOR) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_OC_DOOR_OPEN);
        }
        this->actionFunc = EnTimeTag_KickOut_DoNothing;
    }
}

/**
 * Setup a request to kick out, but wait for an event to complete first
 */
void EnTimeTag_KickOut_WaitForEvent(EnTimeTag* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[63] & 1) && !(gSaveContext.save.weekEventReg[63] & 2)) {
        func_800B7298(play, &this->actor, 7);
        Message_StartTextbox(play, 0x1883 + ENTIMETAG_GET_KICKOUT_TEXT_TYPE(&this->actor), NULL);
        this->actionFunc = EnTimeTag_KickOut_Transition;
    }
}

void EnTimeTag_KickOut_WaitForTime(EnTimeTag* this, PlayState* play) {
    s16 hour;
    s16 minute;

    if ((play->sceneId == SCENE_YADOYA) && (INV_CONTENT(ITEM_ROOM_KEY) == ITEM_ROOM_KEY)) {
        // Having the room key allows you to stay in stock-pot inn
        return;
    }

    hour = TIME_TO_HOURS_F(gSaveContext.save.time);
    minute = (s32)TIME_TO_MINUTES_F(gSaveContext.save.time) % 60;

    if (gSaveContext.save.weekEventReg[63] & 1) {
        if (gSaveContext.save.weekEventReg[63] & 2) {
            this->actionFunc = EnTimeTag_KickOut_WaitForEvent;
        } else if ((hour == ENTIMETEG_GET_KICKOUT_HOUR(&this->actor)) &&
                   (minute == ENTIMETEG_GET_KICKOUT_MINUTE(&this->actor))) {
            gSaveContext.save.weekEventReg[63] |= 2;
        }
    } else if ((hour == ENTIMETEG_GET_KICKOUT_HOUR(&this->actor)) &&
               (minute == ENTIMETEG_GET_KICKOUT_MINUTE(&this->actor)) && !Play_InCsMode(play)) {
        func_800B7298(play, &this->actor, 7);
        Message_StartTextbox(play, 0x1883 + ENTIMETAG_GET_KICKOUT_TEXT_TYPE(&this->actor), NULL);
        this->actionFunc = EnTimeTag_KickOut_Transition;
    }
}

void EnTimeTag_Update(Actor* thisx, PlayState* play) {
    EnTimeTag* this = THIS;

    this->actionFunc(this, play);
}
