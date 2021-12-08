/*
 * File: z_obj_roomtimer.c
 * Overlay: ovl_Obj_Roomtimer
 * Description:
 */

#include "z_obj_roomtimer.h"

#define FLAGS 0x00000010

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

    this->flag = (this->actor.params >> 9) & 0x7F;
    this->actor.params &= 0x1FF;

    if (this->actor.params != 0x1FF) {
        this->actor.params = CLAMP_MAX(this->actor.params, 0x1F4);
    }
    this->actionFunc = func_80973CD8;
}

void ObjRoomtimer_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    if (thisx->params != 0x1FF && gSaveContext.unk_3DD0[4] > 0) {
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
    if (Actor_GetRoomClearedTemp(globalCtx, this->actor.room)) {
        if (this->actor.params != 0x1FF) {
            gSaveContext.unk_3DD0[4] = 5;
        }
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = func_80973DE0;
    } else if (this->actor.params != 0x1FF && gSaveContext.unk_3DD0[4] == 0) {
        play_sound(NA_SE_OC_ABYSS);
        func_80169EFC(globalCtx);
        Actor_MarkForDeath(&this->actor);
    }
}

void func_80973DE0(ObjRoomtimer* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        Actor_SetRoomCleared(globalCtx, this->actor.room);
        Actor_SetSwitchFlag(globalCtx, this->flag);
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
