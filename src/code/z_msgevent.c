#include "global.h"

#define MSCRIPT_CONTINUE 0
#define MSCRIPT_STOP     1

/**
 * Branch forward if the provided week_event_reg flag is set
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) flag
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_Cmd00(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd01(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd02(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd03(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd04(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd05(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
    }
    *scriptPtr += skip;

    return MSCRIPT_CONTINUE;
}

/**
 * Branch forward if the actor has a parent, else get item?
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) getItemId
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_Cmd06(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
 * Branch forward by 1(s16) if there is a talk request, else get item?
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) skip
 * Command size: 3
 */
s32 MsgEvent_Cmd07(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
 * Branch forward if the player currently has more rupees than 1(u16)
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(s16) rupees
 *  3:(s16) skip
 * Command size: 5
 */
s32 MsgEvent_Cmd08(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd09(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (callback == NULL || callback(actor, play) != 0) {
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
s32 MsgEvent_Cmd10(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd11(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
 * Stop script if textbox active?
 *
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_Cmd12(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
 * End script when textbox is done?
 * 
 * Command structure:
 *  0:(u8)  cmd
 * Command size: 1
 */
s32 MsgEvent_Cmd13(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd14(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd15(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd16(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    *endScript = true;
    return MSCRIPT_STOP;
}

/**
 * Sets week_event_reg flags
 *
 * Command structure:
 *  0:(u8)  cmd
 *  1:(u16) flag
 * Command size: 3
 */
s32 MsgEvent_Cmd17(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd18(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd19(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd20(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd21(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd22(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd23(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd24(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd25(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd26(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd27(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd28(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd29(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd30(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd31(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd32(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd33(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd34(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd35(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd36(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd37(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd38(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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

    if (startTime >= now || now >= endTime) {
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
s32 MsgEvent_Cmd39(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd40(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (callback != NULL && callback(actor, play) != 0) {
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
s32 MsgEvent_Cmd41(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    u8* script = *scriptPtr;
    s16 skip = MSCRIPT_GET_16(script, 1);

    if (AMMO(ITEM_POWDER_KEG) != 0 || (play->actorCtx.flags & ACTORCTX_FLAG_0)) {
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
s32 MsgEvent_Cmd42(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd43(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd44(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd45(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd46(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd47(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd48(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd49(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
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
s32 MsgEvent_Cmd50(Actor* actor, PlayState* play, u8** scriptPtr, MsgEventCallback callback, s32* endScript) {
    Audio_PlaySfx(NA_SE_SY_ERROR);
    return MSCRIPT_CONTINUE;
}

MsgEventHandler sMsgEventCmdHandlers[51] = {
    MsgEvent_Cmd00, MsgEvent_Cmd01, MsgEvent_Cmd02, MsgEvent_Cmd03, MsgEvent_Cmd04, MsgEvent_Cmd05, MsgEvent_Cmd06,
    MsgEvent_Cmd07, MsgEvent_Cmd08, MsgEvent_Cmd09, MsgEvent_Cmd10, MsgEvent_Cmd11, MsgEvent_Cmd12, MsgEvent_Cmd13,
    MsgEvent_Cmd14, MsgEvent_Cmd15, MsgEvent_Cmd16, MsgEvent_Cmd17, MsgEvent_Cmd18, MsgEvent_Cmd19, MsgEvent_Cmd20,
    MsgEvent_Cmd21, MsgEvent_Cmd22, MsgEvent_Cmd23, MsgEvent_Cmd24, MsgEvent_Cmd25, MsgEvent_Cmd26, MsgEvent_Cmd27,
    MsgEvent_Cmd28, MsgEvent_Cmd29, MsgEvent_Cmd30, MsgEvent_Cmd31, MsgEvent_Cmd32, MsgEvent_Cmd33, MsgEvent_Cmd34,
    MsgEvent_Cmd35, MsgEvent_Cmd36, MsgEvent_Cmd37, MsgEvent_Cmd38, MsgEvent_Cmd39, MsgEvent_Cmd40, MsgEvent_Cmd41,
    MsgEvent_Cmd42, MsgEvent_Cmd43, MsgEvent_Cmd44, MsgEvent_Cmd45, MsgEvent_Cmd46, MsgEvent_Cmd47, MsgEvent_Cmd48,
    MsgEvent_Cmd49, MsgEvent_Cmd50,
};

u8 sMsgEventCmdLengths[51] = {
    MSCRIPT_BRANCH_ON_WEEK_EVENT_REG_LENGTH,
    3,
    3,
    3,
    3,
    7,
    5,
    3,
    5,
    3,
    13,
    3,
    1,
    1,
    3,
    3,
    1,
    3,
    1,
    3,
    3,
    1,
    1,
    1,
    1,
    3,
    5,
    5,
    3,
    3,
    9,
    5,
    5,
    5,
    5,
    5,
    3,
    5,
    7,
    5,
    3,
    3,
    3,
    7,
    3,
    3,
    1,
    3,
    1,
    1,
    1,
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
        if (cmdId < ARRAY_COUNTU(sMsgEventCmdLengths)) {
            cmdLen = sMsgEventCmdLengths[cmdId];
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
