/*
 * File: z_en_time_tag.c
 * Overlay: ovl_En_Time_Tag
 * Description:
 */

#include "z_en_time_tag.h"
#include "overlays/actors/ovl_En_Elf/z_en_elf.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnTimeTag*)thisx)

void EnTimeTag_Init(Actor* thisx, PlayState* play);
void EnTimeTag_Destroy(Actor* thisx, PlayState* play);
void EnTimeTag_Update(Actor* thisx, PlayState* play);

void func_80AC9FD4(EnTimeTag* this, PlayState* play);
void func_80AC9FE4(EnTimeTag* this, PlayState* play);
void func_80ACA0A8(EnTimeTag* this, PlayState* play);
void func_80ACA12C(EnTimeTag* this, PlayState* play);
void func_80ACA184(EnTimeTag* this, PlayState* play);
void func_80ACA268(EnTimeTag* this, PlayState* play);
void func_80ACA348(EnTimeTag* this, PlayState* play);
void func_80ACA3C0(EnTimeTag* this, PlayState* play);
void func_80ACA418(EnTimeTag* this, PlayState* play);
void func_80ACA5F8(EnTimeTag* this, PlayState* play);
void func_80ACA714(EnTimeTag* this, PlayState* play);
void func_80ACA724(EnTimeTag* this, PlayState* play);
void func_80ACA7C4(EnTimeTag* this, PlayState* play);
void func_80ACA840(EnTimeTag* this, PlayState* play);

const ActorInit En_Time_Tag_InitVars = {
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

    this->actionFunc = func_80ACA840;

    switch (ENTIMETAG_GET_E000(&this->actor)) {
        case 4:
            if ((gSaveContext.save.weekEventReg[8] & 0x40) || (CURRENT_DAY != 3)) {
                Actor_MarkForDeath(&this->actor);
                return;
            }
            this->actor.home.rot.x = 0;
            this->actor.home.rot.y = 0;
            break;

        case 2:
            this->actionFunc = func_80ACA0A8;
            this->actor.flags |= ACTOR_FLAG_2000000;
            break;

        case 1:
            this->actionFunc = func_80ACA268;
            this->actor.flags |= ACTOR_FLAG_2000000;
            if (CHECK_QUEST_ITEM(QUEST_SONG_SOARING)) {
                this->actor.textId = 0xC02;
                return;
            }
            this->actor.textId = 0;
            break;

        case 3:
            this->actionFunc = func_80ACA5F8;
            this->actor.textId = 0;
            this->actor.home.rot.x = 0;
            break;
    }
}

void EnTimeTag_Destroy(Actor* thisx, PlayState* play) {
}

void func_80AC9FD4(EnTimeTag* this, PlayState* play) {
}

void func_80AC9FE4(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->actionFunc = func_80AC9FD4;
        gSaveContext.unk_3DD0[3] = 0;
        if (CHECK_QUEST_ITEM(QUEST_REMAINS_ODOWLA) && CHECK_QUEST_ITEM(QUEST_REMAINS_GOHT) &&
            CHECK_QUEST_ITEM(QUEST_REMAINS_GYORG) && CHECK_QUEST_ITEM(QUEST_REMAINS_TWINMOLD)) {
            gSaveContext.save.weekEventReg[25] |= 2;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80ACA0A8(EnTimeTag* this, PlayState* play) {
    EnTimeTag* this2 = this;

    if ((play->msgCtx.ocarinaMode == 3) && (play->msgCtx.unk1202E == 4)) {
        if (this->actor.cutscene != -1) {
            this->actionFunc = func_80AC9FE4;
            ActorCutscene_SetIntentToPlay(this2->actor.cutscene);
            gSaveContext.unk_3DD0[3] = 0;
        }
        play->msgCtx.ocarinaMode = 4;
    }
}

void func_80ACA12C(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCurrentIndex() != this->actor.cutscene) {
        this->actionFunc = func_80ACA268;
        this->actor.textId = 0xC02;
        Item_Give(play, ITEM_SONG_SOARING);
    }
}

void func_80ACA184(EnTimeTag* this, PlayState* play) {
    if (ActorCutscene_GetCurrentIndex() == 0x7C) {
        ActorCutscene_Stop(0x7C);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        this->actionFunc = func_80ACA12C;
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80ACA208(EnTimeTag* this, PlayState* play) {
    if ((Message_GetState(&play->msgCtx) == TEXT_STATE_5) && Message_ShouldAdvance(play)) {
        func_801477B4(play);
        this->actionFunc = func_80ACA268;
    }
}

void func_80ACA268(EnTimeTag* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->actor.textId == 0) {
            this->actionFunc = func_80ACA184;
        } else {
            this->actionFunc = func_80ACA208;
        }
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play) &&
               (Flags_GetSwitch(play, ENTIMETAG_GET_SWITCHFLAG(&this->actor)) ||
                CHECK_QUEST_ITEM(QUEST_SONG_SOARING))) {
        this->actor.flags |= ACTOR_FLAG_1;
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void func_80ACA348(EnTimeTag* this, PlayState* play) {
    if (this->actor.home.rot.x > 0) {
        this->actor.home.rot.x--;
        return;
    }

    if (this->actor.home.rot.z != 0) {
        func_80151938(play, 0x1230);
    } else {
        func_80151938(play, 0x122D);
    }

    this->actionFunc = func_80ACA418;
}

void func_80ACA3C0(EnTimeTag* this, PlayState* play) {
    if ((play->msgCtx.unk11F00->state == 0) && (play->msgCtx.msgMode == 0x1B)) {
        this->actor.home.rot.x = 5;
        this->actionFunc = func_80ACA348;
        play->msgCtx.msgLength = 0;
        play->msgCtx.msgMode = 0;
    }
}

void func_80ACA418(EnTimeTag* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_5:
            if (Message_ShouldAdvance(play)) {
                switch (play->msgCtx.currentTextId) {
                    case 0x101C:
                    case 0x101D:
                    case 0x101E:
                    case 0x122D:
                        func_80151938(play, play->msgCtx.currentTextId + 1);
                        break;

                    case 0x101F:
                    case 0x122A:
                    case 0x1230:
                        func_801477B4(play);
                        this->actionFunc = func_80ACA5F8;
                        if (ActorCutscene_GetCurrentIndex() == this->actor.cutscene) {
                            ActorCutscene_Stop(this->actor.cutscene);
                        }
                        break;

                    case 0x122B:
                        func_80152434(play, 0x3F);
                        this->actionFunc = func_80ACA3C0;
                        this->actor.home.rot.z = 0;
                        break;

                    case 0x122E:
                        func_80152434(play, 0x40);
                        this->actionFunc = func_80ACA3C0;
                        this->actor.home.rot.z = 1;
                        break;
                }
            }
            break;

        case TEXT_STATE_CLOSING:
            this->actionFunc = func_80ACA5F8;
            break;
    }

    if (this->actor.home.rot.x != 0) {
        if (this->actor.cutscene == -1) {
            this->actor.home.rot.x = 0;
        } else if (ActorCutscene_GetCurrentIndex() == 0x7C) {
            ActorCutscene_Stop(0x7C);
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        } else if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            this->actor.home.rot.x = 0;
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        }
    }
}

void func_80ACA5F8(EnTimeTag* this, PlayState* play) {
    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (gSaveContext.save.playerForm == PLAYER_FORM_ZORA) {
            if (ENTIMETAG_GET_SWITCHFLAG(&this->actor) == 1) {
                Message_StartTextbox(play, 0x101C, &this->actor);
            } else {
                Message_StartTextbox(play, 0x122B, &this->actor);
            }
            this->actor.home.rot.x = 1;
        } else {
            Message_StartTextbox(play, 0x122A, &this->actor);
            if (0) {}
            ((EnElf*)GET_PLAYER(play)->tatlActor)->unk_264 |= 4;
            Actor_ChangeFocus(&this->actor, play, GET_PLAYER(play)->tatlActor);
            this->actor.home.rot.x = 0;
        }
        this->actionFunc = func_80ACA418;
    } else if ((this->actor.xzDistToPlayer < 100.0f) && Player_IsFacingActor(&this->actor, 0x3000, play)) {
        func_800B8614(&this->actor, play, 110.0f);
    }
}

void func_80ACA714(EnTimeTag* this, PlayState* play) {
}

void func_80ACA724(EnTimeTag* this, PlayState* play) {
    if (Message_GetState(&play->msgCtx) == TEXT_STATE_5) {
        play->nextEntranceIndex = play->setupExitList[ENTIMETAG_GET_1F(&this->actor)];
        play->transitionTrigger = TRANS_TRIGGER_START;
        if (!ENTIMETAG_GET_E000(&this->actor)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_OC_DOOR_OPEN);
        }
        this->actionFunc = func_80ACA714;
    }
}

void func_80ACA7C4(EnTimeTag* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[63] & 1) && !(gSaveContext.save.weekEventReg[63] & 2)) {
        func_800B7298(play, &this->actor, 7);
        Message_StartTextbox(play, ENTIMETAG_GET_1FE0(&this->actor) + 0x1883, NULL);
        this->actionFunc = func_80ACA724;
    }
}

void func_80ACA840(EnTimeTag* this, PlayState* play) {
    s16 temp_ft4;
    s16 temp_hi;

    if ((play->sceneNum != SCENE_YADOYA) || (INV_CONTENT(ITEM_ROOM_KEY) != ITEM_ROOM_KEY)) {
        temp_ft4 = gSaveContext.save.time * (24.0f / 0x10000); // TIME_TO_HOURS_F
        temp_hi = (s32)TIME_TO_MINUTES_F(gSaveContext.save.time) % 60;
        if (gSaveContext.save.weekEventReg[63] & 1) {
            if (gSaveContext.save.weekEventReg[63] & 2) {
                this->actionFunc = func_80ACA7C4;
            } else if ((temp_ft4 == this->actor.home.rot.x) && (temp_hi == this->actor.home.rot.y)) {
                gSaveContext.save.weekEventReg[63] |= 2;
            }
        } else if ((temp_ft4 == this->actor.home.rot.x) && (temp_hi == this->actor.home.rot.y) &&
                   !Play_InCsMode(play)) {
            func_800B7298(play, &this->actor, 7);
            Message_StartTextbox(play, ENTIMETAG_GET_1FE0(&this->actor) + 0x1883, NULL);
            this->actionFunc = func_80ACA724;
        }
    }
}

void EnTimeTag_Update(Actor* thisx, PlayState* play) {
    EnTimeTag* this = THIS;

    this->actionFunc(this, play);
}
