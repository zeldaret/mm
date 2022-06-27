/*
 * File: z_obj_wturn.c
 * Overlay: ovl_Obj_Wturn
 * Description: Stone Tower Temple Inverter
 */

#include "z_obj_wturn.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000 | ACTOR_FLAG_2000000)

#define THIS ((ObjWturn*)thisx)

void ObjWturn_Init(Actor* thisx, PlayState* play);
void ObjWturn_Update(Actor* thisx, PlayState* play);

void func_808A7954(ObjWturn* this);
void func_808A7968(ObjWturn* this, PlayState* play);
void func_808A7A24(ObjWturn* this);
void func_808A7A5C(ObjWturn* this, PlayState* play);
void func_808A7AAC(ObjWturn* this, PlayState* play);
void func_808A7BA0(ObjWturn* this, PlayState* play);
void func_808A7C04(ObjWturn* this, PlayState* play);
void func_808A7C78(ObjWturn* this, PlayState* play);

const ActorInit Obj_Wturn_InitVars = {
    ACTOR_OBJ_WTURN,       ACTORCAT_ITEMACTION,        FLAGS,
    GAMEPLAY_KEEP,         sizeof(ObjWturn),           (ActorFunc)ObjWturn_Init,
    (ActorFunc)Actor_Noop, (ActorFunc)ObjWturn_Update, (ActorFunc)NULL,
};

void ObjWturn_Init(Actor* thisx, PlayState* play) {
    ObjWturn* this = THIS;

    func_808A7954(this);
}

void func_808A7954(ObjWturn* this) {
    this->actionFunc = func_808A7968;
}

void func_808A7968(ObjWturn* this, PlayState* play) {
    if (play->msgCtx.ocarinaMode >= 28 && play->msgCtx.ocarinaMode < 39) {
        Flags_UnsetSwitch(play, this->actor.params);
        Actor_MarkForDeath(&this->actor);
    } else if ((Flags_GetSwitch(play, this->actor.params) && (play->sceneNum == SCENE_F40)) ||
               (!Flags_GetSwitch(play, this->actor.params) && (play->sceneNum == SCENE_F41))) {
        func_808A7A24(this);
    }
}

void func_808A7A24(ObjWturn* this) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_808A7A5C;
}

void func_808A7A5C(ObjWturn* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        func_808A7AAC(this, play);
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_808A7AAC(ObjWturn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    Vec3f eye;
    Vec3f at;

    ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
    func_8016566C(140);
    this->camId = ActorCutscene_GetCurrentCamera(this->actor.cutscene);
    func_800B7298(play, &this->actor, 21);
    at.x = player->actor.focus.pos.x;
    at.z = player->actor.focus.pos.z;
    at.y = player->actor.focus.pos.y;
    eye.x = (Math_SinS(this->actor.shape.rot.y) * 150.0f) + at.x;
    eye.z = (Math_CosS(this->actor.shape.rot.y) * 150.0f) + at.z;
    eye.y = at.y + 4.0f;
    Play_CameraSetAtEye(play, this->camId, &at, &eye);
    this->actionFunc = func_808A7BA0;
}

void func_808A7BA0(ObjWturn* this, PlayState* play) {
    if (Math_ScaledStepToS(&this->actor.shape.rot.z, -0x8000, 0x0200)) {
        func_808A7C04(this, play);
    }
    func_800B8FE8(&this->actor, NA_SE_EV_EARTHQUAKE - SFX_FLAG);
    Play_CameraSetRoll(play, this->camId, this->actor.shape.rot.z);
}

void func_808A7C04(ObjWturn* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    this->actor.world.pos.y += this->actor.playerHeightRel;
    player->actor.shape.shadowAlpha = 0;
    func_800B7298(play, &this->actor, 0x54);
    func_800B8E58(player, NA_SE_VO_NAVY_ENEMY);
    this->unk_14A = 0;
    func_80165690();
    this->actionFunc = func_808A7C78;
}

void func_808A7C78(ObjWturn* this, PlayState* play) {
    static Vec3f D_808A7DC0 = { 0.0f, -1.0f, 0.0f };
    Camera* camera = Play_GetCamera(play, this->camId);
    Player* player = GET_PLAYER(play);

    this->unk_14A++;
    player->actor.world.pos.y = this->actor.world.pos.y + this->unk_14A * 4.0f;
    Play_CameraSetAtEyeUp(play, this->camId, &player->actor.focus.pos, &camera->eye, &D_808A7DC0);
    if (this->unk_14A == 1) {
        play->unk_1887F = 0x40;
        gSaveContext.nextTransition = 3;
        gSaveContext.nextCutsceneIndex = 0;
        if (play->sceneNum == 0x58) {
            play->nextEntranceIndex = 0xAC00;
        } else {
            play->nextEntranceIndex = 0xAA10;
        }
        play->sceneLoadFlag = 0x14;
    }
}

void ObjWturn_Update(Actor* thisx, PlayState* play) {
    ObjWturn* this = THIS;

    this->actionFunc(this, play);
}
