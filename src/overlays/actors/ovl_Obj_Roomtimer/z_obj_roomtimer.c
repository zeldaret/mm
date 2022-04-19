/*
 * File: z_obj_roomtimer.c
 * Overlay: ovl_Obj_Roomtimer
 * Description:
 */

#include "z_obj_roomtimer.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjRoomtimer*)thisx)

void ObjRoomtimer_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRoomtimer_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80973CD8(ObjRoomtimer* this, GlobalContext* globalCtx);
void func_80973D3C(ObjRoomtimer* this, GlobalContext* globalCtx);
void func_80973DE0(ObjRoomtimer* this, GlobalContext* globalCtx);

const ActorInit Obj_Roomtimer_InitVars = {
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

void ObjRoomtimer_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjRoomtimer* this = THIS;

    this->switchFlag = ROOMTIMER_GET_SWITCHFLAG(thisx);
    this->actor.params &= 0x1FF;

    if (this->actor.params != 0x1FF) {
        this->actor.params = CLAMP_MAX(this->actor.params, 500);
    }
    this->actionFunc = func_80973CD8;
}

void ObjRoomtimer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjRoomtimer* this = THIS;

    if (this->actor.params != 0x1FF && gSaveContext.unk_3DD0[4] > 0) {
        gSaveContext.unk_3DD0[4] = 5;
    }
}

void func_80973CD8(ObjRoomtimer* this, GlobalContext* globalCtx) {
    if (this->actor.params != 0x1FF) {
        func_8010E9F0(4, this->actor.params);
    }

    func_800BC154(globalCtx, &globalCtx->actorCtx, &this->actor, ACTORCAT_PROP);
    this->actionFunc = func_80973D3C;
}

void func_80973D3C(ObjRoomtimer* this, GlobalContext* globalCtx) {
    if (Flags_GetClearTemp(globalCtx, this->actor.room)) {
        if (this->actor.params != 0x1FF) {
            gSaveContext.unk_3DD0[4] = 5;
        }
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = func_80973DE0;
    } else if (this->actor.params != 0x1FF && gSaveContext.unk_3DD0[4] == 0) {
        play_sound(NA_SE_OC_ABYSS);
        func_80169EFC(&globalCtx->state);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80973DE0(ObjRoomtimer* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        Flags_SetClear(globalCtx, this->actor.room);
        Flags_SetSwitch(globalCtx, this->switchFlag);
        if (ActorCutscene_GetLength(this->actor.cutscene) != -1) {
            ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        }
        Actor_MarkForDeath(&this->actor);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void ObjRoomtimer_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjRoomtimer* this = THIS;

    this->actionFunc(this, globalCtx);
}
