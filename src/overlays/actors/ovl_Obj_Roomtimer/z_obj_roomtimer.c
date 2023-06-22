/*
 * File: z_obj_roomtimer.c
 * Overlay: ovl_Obj_Roomtimer
 * Description:
 */

#include "z_obj_roomtimer.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjRoomtimer*)thisx)

void ObjRoomtimer_Init(Actor* thisx, PlayState* play);
void ObjRoomtimer_Destroy(Actor* thisx, PlayState* play);
void ObjRoomtimer_Update(Actor* thisx, PlayState* play);

void func_80973CD8(ObjRoomtimer* this, PlayState* play);
void func_80973D3C(ObjRoomtimer* this, PlayState* play);
void func_80973DE0(ObjRoomtimer* this, PlayState* play);

ActorInit Obj_Roomtimer_InitVars = {
    ACTOR_OBJ_ROOMTIMER,
    ACTORCAT_ENEMY,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjRoomtimer),
    (ActorFunc)ObjRoomtimer_Init,
    (ActorFunc)ObjRoomtimer_Destroy,
    (ActorFunc)ObjRoomtimer_Update,
    (ActorFunc)NULL,
};

void ObjRoomtimer_Init(Actor* thisx, PlayState* play) {
    ObjRoomtimer* this = THIS;

    this->switchFlag = ROOMTIMER_GET_SWITCHFLAG(thisx);
    this->actor.params &= 0x1FF;

    if (this->actor.params != 0x1FF) {
        this->actor.params = CLAMP_MAX(this->actor.params, 500);
    }
    this->actionFunc = func_80973CD8;
}

void ObjRoomtimer_Destroy(Actor* thisx, PlayState* play) {
    ObjRoomtimer* this = THIS;

    if ((this->actor.params != 0x1FF) && (gSaveContext.timerStates[TIMER_ID_MINIGAME_2] >= TIMER_STATE_START)) {
        gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_STOP;
    }
}

void func_80973CD8(ObjRoomtimer* this, PlayState* play) {
    if (this->actor.params != 0x1FF) {
        Interface_StartTimer(TIMER_ID_MINIGAME_2, this->actor.params);
    }

    func_800BC154(play, &play->actorCtx, &this->actor, ACTORCAT_PROP);
    this->actionFunc = func_80973D3C;
}

void func_80973D3C(ObjRoomtimer* this, PlayState* play) {
    if (Flags_GetClearTemp(play, this->actor.room)) {
        if (this->actor.params != 0x1FF) {
            gSaveContext.timerStates[TIMER_ID_MINIGAME_2] = TIMER_STATE_STOP;
        }
        CutsceneManager_Queue(this->actor.csId);
        this->actionFunc = func_80973DE0;
    } else if ((this->actor.params != 0x1FF) && (gSaveContext.timerStates[TIMER_ID_MINIGAME_2] == TIMER_STATE_OFF)) {
        Audio_PlaySfx(NA_SE_OC_ABYSS);
        func_80169EFC(&play->state);
        Actor_Kill(&this->actor);
    }
}

void func_80973DE0(ObjRoomtimer* this, PlayState* play) {
    if (CutsceneManager_IsNext(this->actor.csId)) {
        Flags_SetClear(play, this->actor.room);
        Flags_SetSwitch(play, this->switchFlag);
        if (CutsceneManager_GetLength(this->actor.csId) != -1) {
            CutsceneManager_StartWithPlayerCs(this->actor.csId, &this->actor);
        }
        Actor_Kill(&this->actor);
        return;
    }

    CutsceneManager_Queue(this->actor.csId);
}

void ObjRoomtimer_Update(Actor* thisx, PlayState* play) {
    ObjRoomtimer* this = THIS;

    this->actionFunc(this, play);
}
