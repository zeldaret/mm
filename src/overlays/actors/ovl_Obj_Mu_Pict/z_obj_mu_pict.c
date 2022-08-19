/*
 * File: z_obj_mu_pict.c
 * Overlay: ovl_Obj_Mu_Pict
 * Description: Handles dialogue for checking the Garo/Gibdo poster in the Music Box House
 */

#include "z_obj_mu_pict.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8)

#define THIS ((ObjMuPict*)thisx)

void ObjMuPict_Init(Actor* thisx, PlayState* play);
void ObjMuPict_Destroy(Actor* thisx, PlayState* play);
void ObjMuPict_Update(Actor* thisx, PlayState* play);
void ObjMuPict_Draw(Actor* thisx, PlayState* play);

void func_80C06B5C(ObjMuPict* this);
void func_80C06B70(ObjMuPict* this, PlayState* play);
void func_80C06C54(ObjMuPict* this);
void func_80C06C68(ObjMuPict* this, PlayState* play);
void func_80C06CC4(ObjMuPict* this);
void func_80C06CD8(ObjMuPict* this, PlayState* play);
void func_80C06D90(ObjMuPict* this, PlayState* play);
void func_80C06DC8(ObjMuPict* this, PlayState* play);
void func_80C06E88(ObjMuPict* this, PlayState* play);

const ActorInit Obj_Mu_Pict_InitVars = {
    ACTOR_OBJ_MU_PICT,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjMuPict),
    (ActorFunc)ObjMuPict_Init,
    (ActorFunc)ObjMuPict_Destroy,
    (ActorFunc)ObjMuPict_Update,
    (ActorFunc)ObjMuPict_Draw,
};

void ObjMuPict_Init(Actor* thisx, PlayState* play) {
    ObjMuPict* this = THIS;

    if (!(gSaveContext.save.weekEventReg[75] & 0x20) && !(gSaveContext.save.weekEventReg[52] & 0x20)) {
        Actor_MarkForDeath(&this->actor);
    }

    func_80C06D90(this, play);
    this->unk14A = OBJMUPICT_GET_F000(&this->actor);
    this->actor.targetMode = 6;
    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 30.0f;
    this->unk148 = 0;
    func_80C06B5C(this);
}

void ObjMuPict_Destroy(Actor* thisx, PlayState* play) {
}

void func_80C06B5C(ObjMuPict* this) {
    this->actionFunc = func_80C06B70;
}

void func_80C06B70(ObjMuPict* this, PlayState* play) {
    s16 yawDiff = this->actor.yawTowardsPlayer - this->actor.world.rot.y;

    if (Actor_ProcessTalkRequest(&this->actor, &play->state)) {
        if (this->actor.cutscene < 0) {
            func_80C06DC8(this, play);
            func_80C06CC4(this);
        } else {
            if (ActorCutscene_GetCurrentIndex() == 0x7C) {
                ActorCutscene_Stop(0x7C);
            }
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            func_80C06DC8(this, play);
            func_80C06C54(this);
        }
    } else if (ABS_ALT(yawDiff) < 0x2AAA) {
        func_800B8614(&this->actor, play, 80.0f);
    }
}

void func_80C06C54(ObjMuPict* this) {
    this->actionFunc = func_80C06C68;
}

void func_80C06C68(ObjMuPict* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_Start(this->actor.cutscene, &this->actor);
        func_80C06CC4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80C06CC4(ObjMuPict* this) {
    this->actionFunc = func_80C06CD8;
}

void func_80C06CD8(ObjMuPict* this, PlayState* play) {
    switch (Message_GetState(&play->msgCtx)) {
        case TEXT_STATE_NONE:
        case TEXT_STATE_1:
        case TEXT_STATE_CLOSING:
        case TEXT_STATE_3:
        case TEXT_STATE_CHOICE:
            break;

        case TEXT_STATE_5:
            func_80C06E88(this, play);
            break;

        case TEXT_STATE_DONE:
            if (Message_ShouldAdvance(play)) {
                func_80C06B5C(this);
                if (this->actor.cutscene >= 0) {
                    ActorCutscene_Stop(this->actor.cutscene);
                }
            }
            break;
    }
    Math_SmoothStepToS(&this->actor.parent->world.rot.y, this->actor.parent->yawTowardsPlayer, 0xA, 0x71C, 0xB6);
    this->actor.parent->shape.rot.y = this->actor.parent->world.rot.y;
}

void func_80C06D90(ObjMuPict* this, PlayState* play) {
    Actor* actorPtr = play->actorCtx.actorLists[ACTORCAT_NPC].first;

    while (actorPtr != NULL) {
        if (actorPtr->id == ACTOR_EN_HGO) {
            this->actor.parent = actorPtr;
            return;
        }
        actorPtr = actorPtr->next;
    }
}

void func_80C06DC8(ObjMuPict* this, PlayState* play) {
    if (this->unk14A == 0) {
        if (this->unk148 == 0) {
            this->unk148 = 1;
            Message_StartTextbox(play, 0x159A, &this->actor);
            this->textId = 0x159A;
        } else {
            Message_StartTextbox(play, 0x159D, &this->actor);
            this->textId = 0x159D;
        }
    } else if (this->unk148 == 0) {
        this->unk148 = 1;
        Message_StartTextbox(play, 0x15A0, &this->actor);
        this->textId = 0x15A0;
    } else {
        Message_StartTextbox(play, 0x15A3, &this->actor);
        this->textId = 0x15A3;
    }
}

void func_80C06E88(ObjMuPict* this, PlayState* play) {
    if (Message_ShouldAdvance(play)) {
        switch (this->textId) {
            case 0x159A:
                Message_StartTextbox(play, 0x159B, &this->actor);
                this->textId = 0x159B;
                break;
            case 0x159B:
                Message_StartTextbox(play, 0x159C, &this->actor);
                this->textId = 0x159C;
                break;
            case 0x159D:
                Message_StartTextbox(play, 0x159E, &this->actor);
                this->textId = 0x159E;
                break;
            case 0x159E:
                Message_StartTextbox(play, 0x159F, &this->actor);
                this->textId = 0x159F;
                break;
            case 0x15A0:
                Message_StartTextbox(play, 0x15A1, &this->actor);
                this->textId = 0x15A1;
                break;
            case 0x15A1:
                Message_StartTextbox(play, 0x15A2, &this->actor);
                this->textId = 0x15A2;
                break;
            case 0x15A3:
                Message_StartTextbox(play, 0x15A4, &this->actor);
                this->textId = 0x15A4;
                break;
        }
    }
}

void ObjMuPict_Update(Actor* thisx, PlayState* play) {
    ObjMuPict* this = THIS;
    this->actionFunc(this, play);
}

void ObjMuPict_Draw(Actor* thisx, PlayState* play) {
}
