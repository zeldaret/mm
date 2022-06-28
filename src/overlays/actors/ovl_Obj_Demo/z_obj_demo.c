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
    s16 temp_v0;

    thisx->params &= 0xFF;
    if ((thisx->params != 0xFF) && (Flags_GetSwitch(play, thisx->params))) {
        Actor_MarkForDeath(&this->actor);
    } else {
        if (thisx->shape.rot.x < 0) {
            this->unk_148 = 1;
            thisx->shape.rot.x = -thisx->shape.rot.x;
        }
        if (thisx->shape.rot.x == 0) {
            this->unk_14C = 80.0f;
        } else {
            this->unk_14C = thisx->shape.rot.x * 4.0f;
            thisx->shape.rot.x = 0;
            thisx->world.rot.x = 0;
        }
        temp_v0 = thisx->shape.rot.z;
        if (temp_v0 == 0) {
            this->unk_150 = 60.0f;
        } else {
            thisx->shape.rot.z = 0;
            thisx->world.rot.z = 0;
            this->unk_150 = temp_v0 * 4.0f;
        }
        func_80983634(play);
        this->actionFunc = func_80983678;
    }
}

void func_80983634(PlayState* play) {
    if ((play->sceneNum == SCENE_CASTLE) && (func_801A8A50(0) == NA_BGM_IKANA_CASTLE)) {
        Audio_QueueSeqCmd(0x100100FF);
    }
}

void func_80983678(ObjDemo* this, PlayState* play) {
    func_80983634(play);
    if ((this->actor.xzDistToPlayer < this->unk_14C) && (fabsf(this->actor.playerHeightRel) < this->unk_150)) {
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
        return;
    }
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene) != 0) {
        if (this->unk_148 == 1) {
            ActorCutscene_Start(this->actor.cutscene, &this->actor);
            func_800E0348(play->cameraPtrs[0]);
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

void ObjDemo_Update(Actor* thisx, PlayState* play) {
    ObjDemo* this = THIS;

    if ((this->actor.params != 0xFF) && (Flags_GetSwitch(play, this->actor.params) != 0)) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actionFunc(this, play);
    }
}
