#include "global.h"

#define MSCRIPT_CONTINUE 0
#define MSCRIPT_STOP 1

/**
 * Branch forward if the provided weekEventReg flag is set
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) flag
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnWeekEventReg(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                  s32* endScript) {
    u8* script = *scriptPtr;
    u16 flag = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (CHECK_WEEKEVENTREG(flag)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the player is currently in goron form
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchIfGoron(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Player* player = GET_PLAYER(play);
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (player->transformation == PLAYER_FORM_GORON) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the player is currently in zora form
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchIfZora(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Player* player = GET_PLAYER(play);
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (player->transformation == PLAYER_FORM_ZORA) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the player is currently in deku form
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchIfDeku(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Player* player = GET_PLAYER(play);
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (player->transformation == PLAYER_FORM_DEKU) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the player is currently in human form
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchIfHuman(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Player* player = GET_PLAYER(play);
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (player->transformation == PLAYER_FORM_HUMAN) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward depending on the message choice index
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skipChoice1
 *  3:(s16) skipChoice2
 *  5:(s16) skipChoice3
 * Command size: 7
 */
s32 MsgEvent_BranchOnTextChoice(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = 0;

    switch (play->msgCtx.choiceIndex) {
        case 0:
            skip = MSCRIPT_GET_16(script, 1);
            break;

        case 1:
            skip = MSCRIPT_GET_16(script, 3);
            break;

        case 2:
            skip = MSCRIPT_GET_16(script, 5);
            break;

        default:
            break;
    }
    *scriptPtr += skip;

    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the actor has a parent, else get item
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) getItemId
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_OfferItem(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s32 getItemId = MSCRIPT_GET_16(script, 1);
    f32 xzRange = actor->xzDistToPlayer + 1.0f;
    f32 yRange = fabsf(actor->playerHeightRel) + 1.0f;
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (Actor_HasParent(actor, play)) {
        *scriptPtr += skip;
    } else {
        Actor_OfferGetItem(actor, play, getItemId, xzRange, yRange);
        return MSCRIPT_STOP;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if there is a talk request, else autotalk
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_Autotalk(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    f32 xzRange = actor->xzDistToPlayer + 1.0f;
    f32 yRange = fabsf(actor->playerHeightRel) + 1.0f;
    f32 xzDist;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (Actor_TalkOfferAccepted(actor, &play->state)) {
        *scriptPtr += skip;
    } else {
        actor->flags |= ACTOR_FLAG_10000;
        xzDist = actor->xzDistToPlayer;
        actor->xzDistToPlayer = 0.0f;
        Actor_OfferTalkExchange(actor, play, xzRange, yRange, PLAYER_IA_NONE);
        actor->xzDistToPlayer = xzDist;
        return MSCRIPT_STOP;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the player currently has more rupees
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) rupees
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnRupees(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 rupees = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (gSaveContext.save.saveInfo.playerData.rupees >= rupees) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the callback is null or returns non-zero
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchOnCallback(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                              s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if ((callback == NULL) || (callback(actor, play) != 0)) {
        *scriptPtr += skip;
    } else {
        return MSCRIPT_STOP;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward based on time of day
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skipDay1
 *  3:(s16) skipNight1
 *  5:(s16) skipDay2
 *  7:(s16) skipNight2
 *  9:(s16) skipDay3
 *  11:(s16) skipNight3
 * Command size: 13
 */
s32 MsgEvent_BranchOnDay(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = 0;

    switch (gSaveContext.save.day) {
        case 1:
            if (!gSaveContext.save.isNight) {
                skip = MSCRIPT_GET_16(script, 1);
            } else {
                skip = MSCRIPT_GET_16(script, 3);
            }
            break;

        case 2:
            if (!gSaveContext.save.isNight) {
                skip = MSCRIPT_GET_16(script, 5);
            } else {
                skip = MSCRIPT_GET_16(script, 7);
            }
            break;

        case 3:
            if (!gSaveContext.save.isNight) {
                skip = MSCRIPT_GET_16(script, 9);
            } else {
                skip = MSCRIPT_GET_16(script, 11);
            }
            break;

        default:
            break;
    }
    *scriptPtr += skip;
    return MSCRIPT_CONTINUE;
}

/**
 * Wait on choice text, skip forward when text closes.
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_AwaitTextJump(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) {
                return MSCRIPT_STOP;
            }
        case TEXT_STATE_CLOSING:
            skip = MSCRIPT_GET_16(script, 1);
            break;

        default:
            return MSCRIPT_STOP;
    }
    *scriptPtr += skip;
    return MSCRIPT_CONTINUE;
}

/**
 * Waits for text to advance
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_AwaitText(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) {
                return MSCRIPT_STOP;
            }
            break;

        case TEXT_STATE_CLOSING:
            break;

        default:
            return MSCRIPT_STOP;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Waits for text to end
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_AwaitTextEnd(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    s32 state = Message_GetState(&play->msgCtx);

    *endScript = false;

    switch (state) {
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) {
                break;
            }
        case TEXT_STATE_CLOSING:
            *endScript = true;
            break;

        default:
            return MSCRIPT_STOP;
    }
    return MSCRIPT_STOP;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) textId
 * Command size: 3
 */
s32 MsgEvent_BeginText(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;

    Message_StartTextbox(play, MSCRIPT_GET_16(script, 1), NULL);
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) textId
 * Command size: 3
 */
s32 MsgEvent_ContinueText(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;

    Message_ContinueTextbox(play, MSCRIPT_GET_16(script, 1));
    return MSCRIPT_CONTINUE;
}

/**
 * Script Terminator
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_Done(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    *endScript = true;
    return MSCRIPT_STOP;
}

/**
 * Sets weekEventReg flags
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) flag
 * Command size: 3
 */
s32 MsgEvent_SetWeekEventReg(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    u16 flag = MSCRIPT_GET_16(script, 1);

    SET_WEEKEVENTREG(flag);
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_CloseText(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Message_CloseTextbox(play);
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  0:(u16) flag
 * Command size: 3
 */
s32 MsgEvent_SetCollectible(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s32 flag = MSCRIPT_GET_16(script, 1);

    if (!Flags_GetCollectible(play, flag)) {
        Flags_SetCollectible(play, flag);
    }
    actor->parent = NULL;
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  0:(s16) rupees
 * Command size: 3
 */
s32 MsgEvent_ChangeRupees(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 rupees = MSCRIPT_GET_16(script, 1);

    Rupees_ChangeBy(rupees);
    return MSCRIPT_CONTINUE;
}

/**
 * Pause the message system
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_Pause(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    play->msgCtx.msgMode = 0x44;
    return MSCRIPT_CONTINUE;
}

/**
 * Unsets ACTOR_FLAG_10000 for the actor executing the script
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_UnsetAutotalk(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    actor->flags &= ~ACTOR_FLAG_10000;
    return MSCRIPT_CONTINUE;
}

/**
 * Sets player focus & talk actor to the child of the actor executing the script
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_FocusToChild(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    if (actor->child != NULL) {
        Actor_ChangeFocus(actor, play, actor->child);
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Sets player focus & talk actor to the actor executing the script
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_FocusToSelf(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    if (actor->child != NULL) {
        Actor_ChangeFocus(actor->child, play, actor);
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Unconditional branch by `skip`
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_Jump(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    *scriptPtr += skip;
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forwards if the specified quest item is obtained
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) questItem
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnQuestItem(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                               s32* endScript) {
    u8* script = *scriptPtr;
    u16 questItem = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (CHECK_QUEST_ITEM(questItem)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branch forwards if event_inf flag is set
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) event_inf flag
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnEventInf(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                              s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (MSCRIPT_GET_8(script, 2) & gSaveContext.eventInf[MSCRIPT_GET_8(script, 1)]) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Sets event_inf flag
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) event_inf flag
 * Command size: 3
 */
s32 MsgEvent_SetEventInf(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;

    gSaveContext.eventInf[MSCRIPT_GET_8(script, 1)] |= MSCRIPT_GET_8(script, 2);
    return MSCRIPT_CONTINUE;
}

/**
 * Unsets event_inf flag
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) event_inf flag
 * Command size: 3
 */
s32 MsgEvent_UnsetEventInf(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;

    gSaveContext.eventInf[MSCRIPT_GET_8(script, 1)] &= MSCRIPT_GET_8(script, 2) ^ 0xFF;
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) input player item-action
 *  3:(s16) skip if player item-action matches input player item-action
 *  5:(s16) skip if player item-action does not match input player item-action
 *  7:(s16) skip if player item-action is negative
 * Command size: 9
 */
s32 MsgEvent_BranchOnItemAction(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                s32* endScript) {
    u8* script = *scriptPtr;
    PlayerItemAction checkItemAction = MSCRIPT_GET_16(script, 1);
    s16 skip;
    PlayerItemAction curItemAction;

    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) {
                return MSCRIPT_STOP;
            }
        case TEXT_STATE_PAUSE_MENU:
            curItemAction = func_80123810(play);

            if (curItemAction == PLAYER_IA_NONE) {
                return MSCRIPT_STOP;
            } else if (curItemAction < 0) {
                skip = MSCRIPT_GET_16(script, 7);
            } else if (curItemAction == checkItemAction) {
                skip = MSCRIPT_GET_16(script, 3);
            } else {
                skip = MSCRIPT_GET_16(script, 5);
            }
            break;

        default:
            return MSCRIPT_STOP;
    }
    *scriptPtr += skip;
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if song is obtained
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) song
 *  3:(s16) skip
 * Command size: 9
 */
s32 MsgEvent_BranchOnSongObtained(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                  s32* endScript) {
    u8* script = *scriptPtr;
    u16 song = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (CHECK_QUEST_ITEM(QUEST_SONG_SONATA + song)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if the player's current mask matches
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) mask
 *  3:(s16) skip
 * Command size: 9
 */
s32 MsgEvent_BranchOnWornMask(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                              s32* endScript) {
    u8* script = *scriptPtr;
    s32 mask = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (Player_GetMask(play) == mask) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

#define MSCRIPT_GET_TIME(hour, minute, dest, temp) \
    (temp) = (hour)*60.0f;                         \
    (temp) += (minute);                            \
    (dest) = (temp) * (0x10000 / 60 / 24.0f);      \
    (dest) = ((dest)-0x10000 / 360 * 90)

#define MSCRIPT_TIME_NOW ((gSaveContext.save.time) - 0x10000 / 360 * 90)

/**
 * Branches forward if the current time is greater than the provided time
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u8)  hour
 *  1:(u8)  min
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnTimeGT(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 3);
    f32 f;
    u16 time;
    u16 now;

    MSCRIPT_GET_TIME(MSCRIPT_GET_8(script, 1), MSCRIPT_GET_8(script, 2), time, f);
    now = MSCRIPT_TIME_NOW;

    if (time < now) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if the current time is less or equal to the provided time
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u8)  hour
 *  1:(u8)  min
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnTimeLEQ(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 3);
    f32 f;
    u16 time;
    u16 now;

    MSCRIPT_GET_TIME(MSCRIPT_GET_8(script, 1), MSCRIPT_GET_8(script, 2), time, f);
    now = MSCRIPT_TIME_NOW;

    if (time >= now) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if switch flag is set
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) flag
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnSwitchFlag(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                s32* endScript) {
    u8* script = *scriptPtr;
    s16 flag = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (Flags_GetSwitch(play, flag)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Sets switch flag
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) flag
 * Command size: 3
 */
s32 MsgEvent_SetSwitchFlag(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 flag = MSCRIPT_GET_16(script, 1);

    Flags_SetSwitch(play, flag);
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if item is in inventory
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) item
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchOnItem(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    u16 item = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (INV_CONTENT(item) == item) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if current time is within the specified interval
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) startTime
 *  3:(u16) endTime
 *  5:(s16) skip
 * Command size: 7
 */
s32 MsgEvent_BranchOnTimeInterval(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                  s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 5);
    f32 f;
    u16 startTime;
    u16 endTime;
    u16 now;

    MSCRIPT_GET_TIME(MSCRIPT_GET_8(script, 1), MSCRIPT_GET_8(script, 2), startTime, f);
    MSCRIPT_GET_TIME(MSCRIPT_GET_8(script, 3), MSCRIPT_GET_8(script, 4), endTime, f);
    endTime--;
    now = MSCRIPT_TIME_NOW;

    if ((startTime >= now) || (now >= endTime)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if the current day matches
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) day
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_BranchIfDay(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 day = MSCRIPT_GET_16(script, 1);
    s16 skip = MSCRIPT_GET_16(script, 3);

    if (gSaveContext.save.day == day) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Branches forward if callback exists and returns non-zero
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchOnCallbackContinue(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                      s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if ((callback != NULL) && (callback(actor, play) != 0)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Skip forward if a powder keg is in inventory or if a powder keg actor exists
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_BranchIfHasPowderKeg(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                  s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if ((AMMO(ITEM_POWDER_KEG) != 0) || (play->actorCtx.flags & ACTORCTX_FLAG_0)) {
        *scriptPtr += skip;
    }
    return MSCRIPT_CONTINUE;
}

/**
 * Deletes the specified item
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) item
 * Command size: 3
 */
s32 MsgEvent_DeleteItem(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 item = MSCRIPT_GET_16(script, 1);

    Inventory_DeleteItem(item, SLOT(item));
    return MSCRIPT_CONTINUE;
}

/**
 * Runs the callback and selects a skip based on the result, default skip is the first one
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 *  3:(s16) skip
 *  5:(s16) skip
 * Command size: 7
 */
s32 MsgEvent_BranchOnCallbackMulti(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback,
                                   s32* endScript) {
    u8* script = *scriptPtr;
    s32 ret = 1;
    s16 skip;

    if (callback != NULL) {
        ret = callback(actor, play);
    }
    switch (ret) {
        case 3:
            skip = MSCRIPT_GET_16(script, 5);
            break;

        case 2:
            skip = MSCRIPT_GET_16(script, 3);
            break;

        case 1:
            skip = MSCRIPT_GET_16(script, 1);
            break;

        default:
            return MSCRIPT_STOP;
    }
    *scriptPtr += skip;
    return MSCRIPT_CONTINUE;
}

/**
 * Close the current textbox and set the player actor text id
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) textId
 * Command size: 3
 */
s32 MsgEvent_PlayerTalk(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Player* player = GET_PLAYER(play);
    u8* script = *scriptPtr;
    u16 textId = MSCRIPT_GET_16(script, 1);

    player->actor.textId = textId;
    Message_CloseTextbox(play);
    return MSCRIPT_CONTINUE;
}

/**
 * Queue a bomber's notebook event
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) event
 * Command size: 3
 */
s32 MsgEvent_NotebookEvent(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    u16 event = MSCRIPT_GET_16(script, 1);

    Message_BombersNotebookQueueEvent(play, event);
    return MSCRIPT_CONTINUE;
}

/**
 *
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_AwaitTextDone(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_CLOSING:
            break;

        case TEXT_STATE_CHOICE:
        case TEXT_STATE_EVENT:
            if (!Message_ShouldAdvance(play)) {
                return MSCRIPT_STOP;
            }

        case TEXT_STATE_DONE:
            if (!Message_ShouldAdvance(play)) {
                return MSCRIPT_STOP;
            }
            break;

        default:
            return MSCRIPT_STOP;
    }
    return MSCRIPT_CONTINUE;
}

/**
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_Jump3(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    *scriptPtr += skip;
    *scriptPtr += 3;
    return MSCRIPT_STOP;
}

/**
 * Plays Decide sfx
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_PlayDecide(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Audio_PlaySfx_MessageDecide();
    return MSCRIPT_CONTINUE;
}

/**
 * Plays Cancel sfx
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_PlayCancel(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Audio_PlaySfx_MessageCancel();
    return MSCRIPT_CONTINUE;
}

/**
 * Plays NA_SE_SY_ERROR sfx
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_PlayError(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Audio_PlaySfx(NA_SE_SY_ERROR);
    return MSCRIPT_CONTINUE;
}

MsgEventHandler sMsgEventCmdHandlers[] = {
    MsgEvent_BranchOnWeekEventReg,     // MSCRIPT_CMD_BRANCH_ON_WEEK_EVENT_REG
    MsgEvent_BranchIfGoron,            // MSCRIPT_CMD_BRANCH_IF_GORON
    MsgEvent_BranchIfZora,             // MSCRIPT_CMD_BRANCH_IF_ZORA
    MsgEvent_BranchIfDeku,             // MSCRIPT_CMD_BRANCH_IF_DEKU
    MsgEvent_BranchIfHuman,            // MSCRIPT_CMD_BRANCH_IF_HUMAN
    MsgEvent_BranchOnTextChoice,       // MSCRIPT_CMD_BRANCH_ON_TEXT_CHOICE
    MsgEvent_OfferItem,                // MSCRIPT_CMD_OFFER_ITEM
    MsgEvent_Autotalk,                 // MSCRIPT_CMD_AUTOTALK
    MsgEvent_BranchOnRupees,           // MSCRIPT_CMD_BRANCH_ON_RUPEES
    MsgEvent_BranchOnCallback,         // MSCRIPT_CMD_BRANCH_ON_CALLBACK
    MsgEvent_BranchOnDay,              // MSCRIPT_CMD_BRANCH_ON_DAY
    MsgEvent_AwaitTextJump,            // MSCRIPT_CMD_AWAIT_TEXT_JUMP
    MsgEvent_AwaitText,                // MSCRIPT_CMD_AWAIT_TEXT
    MsgEvent_AwaitTextEnd,             // MSCRIPT_CMD_AWAIT_TEXT_END
    MsgEvent_BeginText,                // MSCRIPT_CMD_BEGIN_TEXT
    MsgEvent_ContinueText,             // MSCRIPT_CMD_CONTINUE_TEXT
    MsgEvent_Done,                     // MSCRIPT_CMD_DONE
    MsgEvent_SetWeekEventReg,          // MSCRIPT_CMD_SET_WEEK_EVENT_REG
    MsgEvent_CloseText,                // MSCRIPT_CMD_CLOSE_TEXT
    MsgEvent_SetCollectible,           // MSCRIPT_CMD_SET_COLLECTIBLE
    MsgEvent_ChangeRupees,             // MSCRIPT_CMD_CHANGE_RUPEES
    MsgEvent_Pause,                    // MSCRIPT_CMD_PAUSE
    MsgEvent_UnsetAutotalk,            // MSCRIPT_CMD_UNSET_AUTOTALK
    MsgEvent_FocusToChild,             // MSCRIPT_CMD_FOCUS_TO_CHILD
    MsgEvent_FocusToSelf,              // MSCRIPT_CMD_FOCUS_TO_SELF
    MsgEvent_Jump,                     // MSCRIPT_CMD_JUMP
    MsgEvent_BranchOnQuestItem,        // MSCRIPT_CMD_BRANCH_ON_QUEST_ITEM
    MsgEvent_BranchOnEventInf,         // MSCRIPT_CMD_BRANCH_ON_EVENT_INF
    MsgEvent_SetEventInf,              // MSCRIPT_CMD_SET_EVENT_INF
    MsgEvent_UnsetEventInf,            // MSCRIPT_CMD_UNSET_EVENT_INF
    MsgEvent_BranchOnItemAction,       // MSCRIPT_CMD_BRANCH_ON_ITEMACTION
    MsgEvent_BranchOnSongObtained,     // MSCRIPT_CMD_BRANCH_ON_SONG_OBTAINED
    MsgEvent_BranchOnWornMask,         // MSCRIPT_CMD_BRANCH_ON_WORN_MASK
    MsgEvent_BranchOnTimeGT,           // MSCRIPT_CMD_BRANCH_ON_TIME_GT
    MsgEvent_BranchOnTimeLEQ,          // MSCRIPT_CMD_BRANCH_ON_TIME_LEQ
    MsgEvent_BranchOnSwitchFlag,       // MSCRIPT_CMD_BRANCH_ON_SWITCH_FLAG
    MsgEvent_SetSwitchFlag,            // MSCRIPT_CMD_SET_SWITCH_FLAG
    MsgEvent_BranchOnItem,             // MSCRIPT_CMD_BRANCH_ON_ITEM
    MsgEvent_BranchOnTimeInterval,     // MSCRIPT_CMD_BRANCH_ON_TIME_INTERVAL
    MsgEvent_BranchIfDay,              // MSCRIPT_CMD_BRANCH_IF_DAY
    MsgEvent_BranchOnCallbackContinue, // MSCRIPT_CMD_BRANCH_ON_CALLBACK_CONTINUE
    MsgEvent_BranchIfHasPowderKeg,     // MSCRIPT_CMD_BRANCH_IF_HAS_POWDER_KEG
    MsgEvent_DeleteItem,               // MSCRIPT_CMD_DELETE_ITEM
    MsgEvent_BranchOnCallbackMulti,    // MSCRIPT_CMD_BRANCH_ON_CALLBACK_MULTI
    MsgEvent_PlayerTalk,               // MSCRIPT_CMD_PLAYER_TALK
    MsgEvent_NotebookEvent,            // MSCRIPT_CMD_NOTEBOOK_EVENT
    MsgEvent_AwaitTextDone,            // MSCRIPT_CMD_AWAIT_TEXT_DONE
    MsgEvent_Jump3,                    // MSCRIPT_CMD_JUMP_3
    MsgEvent_PlayDecide,               // MSCRIPT_CMD_PLAY_DECIDE
    MsgEvent_PlayCancel,               // MSCRIPT_CMD_PLAY_CANCEL
    MsgEvent_PlayError,                // MSCRIPT_CMD_PLAY_ERROR
};

u8 sMsgEventCmdSizes[] = {
    MSCRIPT_BRANCH_ON_WEEK_EVENT_REG_SIZE,    // MSCRIPT_CMD_BRANCH_ON_WEEK_EVENT_REG
    MSCRIPT_BRANCH_IF_GORON_SIZE,             // MSCRIPT_CMD_BRANCH_IF_GORON
    MSCRIPT_BRANCH_IF_ZORA_SIZE,              // MSCRIPT_CMD_BRANCH_IF_ZORA
    MSCRIPT_BRANCH_IF_DEKU_SIZE,              // MSCRIPT_CMD_BRANCH_IF_DEKU
    MSCRIPT_BRANCH_IF_HUMAN_SIZE,             // MSCRIPT_CMD_BRANCH_IF_HUMAN
    MSCRIPT_BRANCH_ON_TEXT_CHOICE_SIZE,       // MSCRIPT_CMD_BRANCH_ON_TEXT_CHOICE
    MSCRIPT_OFFER_ITEM_SIZE,                  // MSCRIPT_CMD_OFFER_ITEM
    MSCRIPT_AUTOTALK_SIZE,                    // MSCRIPT_CMD_AUTOTALK
    MSCRIPT_BRANCH_ON_RUPEES_SIZE,            // MSCRIPT_CMD_BRANCH_ON_RUPEES
    MSCRIPT_BRANCH_ON_CALLBACK_SIZE,          // MSCRIPT_CMD_BRANCH_ON_CALLBACK
    MSCRIPT_BRANCH_ON_DAY_SIZE,               // MSCRIPT_CMD_BRANCH_ON_DAY,
    MSCRIPT_AWAIT_TEXT_JUMP_SIZE,             // MSCRIPT_CMD_AWAIT_TEXT_JUMP
    MSCRIPT_AWAIT_TEXT_SIZE,                  // MSCRIPT_CMD_AWAIT_TEXT
    MSCRIPT_AWAIT_TEXT_END_SIZE,              // MSCRIPT_CMD_AWAIT_TEXT_END
    MSCRIPT_BEGIN_TEXT_SIZE,                  // MSCRIPT_CMD_BEGIN_TEXT
    MSCRIPT_CONTINUE_TEXT_SIZE,               // MSCRIPT_CMD_CONTINUE_TEXT
    MSCRIPT_DONE_SIZE,                        // MSCRIPT_CMD_DONE
    MSCRIPT_SET_WEEK_EVENT_REG_SIZE,          // MSCRIPT_CMD_SET_WEEK_EVENT_REG
    MSCRIPT_CLOSE_TEXT_SIZE,                  // MSCRIPT_CMD_CLOSE_TEXT
    MSCRIPT_SET_COLLECTIBLE_SIZE,             // MSCRIPT_CMD_SET_COLLECTIBLE
    MSCRIPT_CHANGE_RUPEES_SIZE,               // MSCRIPT_CMD_CHANGE_RUPEES
    MSCRIPT_PAUSE_SIZE,                       // MSCRIPT_CMD_PAUSE
    MSCRIPT_UNSET_AUTOTALK_SIZE,              // MSCRIPT_CMD_UNSET_AUTOTALK
    MSCRIPT_FOCUS_TO_CHILD_SIZE,              // MSCRIPT_CMD_FOCUS_TO_CHILD
    MSCRIPT_FOCUS_TO_SELF_SIZE,               // MSCRIPT_CMD_FOCUS_TO_SELF
    MSCRIPT_JUMP_SIZE,                        // MSCRIPT_CMD_JUMP
    MSCRIPT_BRANCH_ON_QUEST_ITEM_SIZE,        // MSCRIPT_CMD_BRANCH_ON_QUEST_ITEM
    MSCRIPT_BRANCH_ON_EVENT_INF_SIZE,         // MSCRIPT_CMD_BRANCH_ON_EVENT_INF
    MSCRIPT_SET_EVENT_INF_SIZE,               // MSCRIPT_CMD_SET_EVENT_INF
    MSCRIPT_UNSET_EVENT_INF_SIZE,             // MSCRIPT_CMD_UNSET_EVENT_INF
    MSCRIPT_BRANCH_ON_ITEMACTION_SIZE,        // MSCRIPT_CMD_BRANCH_ON_ITEMACTION
    MSCRIPT_BRANCH_ON_SONG_OBTAINED_SIZE,     // MSCRIPT_CMD_BRANCH_ON_SONG_OBTAINED
    MSCRIPT_BRANCH_ON_WORN_MASK_SIZE,         // MSCRIPT_CMD_BRANCH_ON_WORN_MASK
    MSCRIPT_BRANCH_ON_TIME_GT_SIZE,           // MSCRIPT_CMD_BRANCH_ON_TIME_GT
    MSCRIPT_BRANCH_ON_TIME_LEQ_SIZE,          // MSCRIPT_CMD_BRANCH_ON_TIME_LEQ
    MSCRIPT_BRANCH_ON_SWITCH_FLAG_SIZE,       // MSCRIPT_CMD_BRANCH_ON_SWITCH_FLAG
    MSCRIPT_SET_SWITCH_FLAG_SIZE,             // MSCRIPT_CMD_SET_SWITCH_FLAG
    MSCRIPT_BRANCH_ON_ITEM_SIZE,              // MSCRIPT_CMD_BRANCH_ON_ITEM
    MSCRIPT_BRANCH_ON_TIME_INTERVAL_SIZE,     // MSCRIPT_CMD_BRANCH_ON_TIME_INTERVAL
    MSCRIPT_BRANCH_IF_DAY_SIZE,               // MSCRIPT_CMD_BRANCH_IF_DAY
    MSCRIPT_BRANCH_ON_CALLBACK_CONTINUE_SIZE, // MSCRIPT_CMD_BRANCH_ON_CALLBACK_CONTINUE
    MSCRIPT_BRANCH_IF_HAS_POWDER_KEG_SIZE,    // MSCRIPT_CMD_BRANCH_IF_HAS_POWDER_KEG
    MSCRIPT_DELETE_ITEM_SIZE,                 // MSCRIPT_CMD_DELETE_ITEM
    MSCRIPT_BRANCH_ON_CALLBACK_MULTI_SIZE,    // MSCRIPT_CMD_BRANCH_ON_CALLBACK_MULTI
    MSCRIPT_PLAYER_TALK_SIZE,                 // MSCRIPT_CMD_PLAYER_TALK
    MSCRIPT_NOTEBOOK_EVENT_SIZE,              // MSCRIPT_CMD_NOTEBOOK_EVENT
    MSCRIPT_AWAIT_TEXT_DONE_SIZE,             // MSCRIPT_CMD_AWAIT_TEXT_DONE
    MSCRIPT_JUMP_3_SIZE,                      // MSCRIPT_CMD_JUMP_3
    MSCRIPT_PLAY_DECIDE_SIZE,                 // MSCRIPT_CMD_PLAY_DECIDE
    MSCRIPT_PLAY_CANCEL_SIZE,                 // MSCRIPT_CMD_PLAY_CANCEL
    MSCRIPT_PLAY_ERROR_SIZE,                  // MSCRIPT_CMD_PLAY_ERROR
};

/**
 * Runs a message event script
 *
 * @param actor         The actor associated with the script
 * @param play          Play game state
 * @param script        The script to run
 * @param callback      Callback function used by various commands for different purposes
 * @param[in,out] pos   Position to resume the script from, the point at which the script stops executing is also
 *                       written out here
 * @return s32  Whether the script has reached an endpoint
 */
s32 MsgEvent_RunScript(Actor* actor, PlayState* play, MsgScript* script, MsgEventCallback callback, s32* pos) {
    u8* start;
    u8* cur;
    s32 scriptDone = false;
    s32 i;
    s32 cmdLen;
    u8 cmdId;
    s32 pad;

    start = script;
    script += *pos;

    if (sREG(95) != 0) {}

    cmdLen = 0;
    do {
        // Skip data from previous command
        script += cmdLen;

        // Get command id
        cmdId = *script;

        // Get command length
        if (cmdId < ARRAY_COUNTU(sMsgEventCmdSizes)) {
            cmdLen = sMsgEventCmdSizes[cmdId];
        } else {
            cmdLen = -1;
            //! @bug command handler still runs even if cmdId is invalid
        }

        // Debug loop?
        if (sREG(95) != 0) {
            for (i = 0; i < cmdLen; i++) {}
        }

        // Run command handler
    } while (sMsgEventCmdHandlers[cmdId](actor, play, &script, callback, &scriptDone) == MSCRIPT_CONTINUE);

    cur = script;
    if (!scriptDone) {
        *pos = cur - start;
    } else {
        *pos = 0;
    }
    return scriptDone;
}
