/*
 * File: z_obj_demo.c
 * Overlay: ovl_Obj_Demo
 * Description:
 */

#include "z_obj_demo.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDemo*)thisx)

void ObjDemo_Init(Actor* thisx, PlayState* play);
void ObjDemo_Update(Actor* thisx, PlayState* play);

void func_80983678(ObjDemo* this, PlayState* play);
void func_80983704(ObjDemo* this, PlayState* play);
void func_80983634(PlayState* play);

const ActorInit Obj_Demo_InitVars = {
    ACTOR_OBJ_DEMO,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjDemo),
    (ActorFunc)ObjDemo_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjDemo_Update,
    (ActorFunc)NULL,
};

void ObjDemo_Init(Actor* thisx, PlayState* play) {
    ObjDemo* this = THIS;

    thisx->params = OBJDEMO_GET_FF(thisx);
    if ((thisx->params != OBJDEMO_FF_FF) && (Flags_GetSwitch(play, thisx->params))) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    if (thisx->shape.rot.x < 0) {
        this->unk_148 = 1;
        thisx->shape.rot.x = -thisx->shape.rot.x;
    }
    if (thisx->shape.rot.x == 0) {
        this->xzRange = 80.0f;
    } else {
        this->xzRange = thisx->shape.rot.x * 4.0f;
        thisx->shape.rot.x = 0;
        thisx->world.rot.x = 0;
    }
    if (thisx->shape.rot.z == 0) {
        this->yRange = 60.0f;
    } else {
        this->yRange = thisx->shape.rot.z * 4.0f;
        thisx->shape.rot.z = 0;
        thisx->world.rot.z = 0;
    }
    func_80983634(play);
    this->actionFunc = func_80983678;
}

void func_80983634(PlayState* play) {
    if ((play->sceneNum == SCENE_CASTLE) && (func_801A8A50(0) == NA_BGM_IKANA_CASTLE)) {
        Audio_QueueSeqCmd(0x100100FF);
    }
}

void func_80983678(ObjDemo* this, PlayState* play) {
    func_80983634(play);
    if ((this->actor.xzDistToPlayer < this->xzRange) && (fabsf(this->actor.playerHeightRel) < this->yRange)) {
        if (this->unk_148 == 1) {
            ActorCutscene_Stop(0x7D);
        }
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
        this->actionFunc = func_80983704;
    }
}

void func_80983704(ObjDemo* this, PlayState* play) {
    if ((this->unk_148 == 1) && (ActorCutscene_GetCurrentIndex() == 0x7D)) {
        ActorCutscene_Stop(0x7D);
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    } else {
        if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
            if (this->unk_148 == 1) {
                ActorCutscene_Start(this->actor.cutscene, &this->actor);
                func_800E0348(play->cameraPtrs[CAM_ID_MAIN]);
            } else {
                ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
            }
            if (play->sceneNum == SCENE_CASTLE) {
                Audio_QueueSeqCmd(NA_BGM_IKANA_CASTLE | 0x8000);
            }
            this->actor.cutscene = ActorCutscene_GetAdditionalCutscene(this->actor.cutscene);
            if (this->actor.cutscene == -1) {
                if (this->actor.params != 0xFF) {
                    Flags_SetSwitch(play, this->actor.params);
                }
                Actor_MarkForDeath(&this->actor);
            }
        } else {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            func_80983634(play);
        }
    }
}

void ObjDemo_Update(Actor* thisx, PlayState* play) {
    ObjDemo* this = THIS;

    if ((this->actor.params != 0xFF) && Flags_GetSwitch(play, this->actor.params)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }
    this->actionFunc(this, play);
}
