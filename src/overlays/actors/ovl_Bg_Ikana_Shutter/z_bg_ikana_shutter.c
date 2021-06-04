#include "z_bg_ikana_shutter.h"

#define FLAGS 0x00000010

#define THIS ((BgIkanaShutter*)thisx)

void BgIkanaShutter_Init(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Update(Actor* thisx, GlobalContext* globalCtx);
void BgIkanaShutter_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BD5828(BgIkanaShutter* this);
void func_80BD5844(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD5878(BgIkanaShutter* this);
void func_80BD5894(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD58F0(BgIkanaShutter* this);
void func_80BD5910(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD599C(BgIkanaShutter* this);
void func_80BD59C4(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD59F8(BgIkanaShutter* this);
void func_80BD5A18(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD5AE8(BgIkanaShutter* this);
void func_80BD5B04(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD5B44(BgIkanaShutter* this);
void func_80BD5B60(BgIkanaShutter* this, GlobalContext* globalCtx);
void func_80BD5BC4(BgIkanaShutter* this);
void func_80BD5BD8(BgIkanaShutter* this, GlobalContext* globalCtx);
void BgIkanaShutter_SetupDoNothing(BgIkanaShutter* this);
void BgIkanaShutter_DoNothing(BgIkanaShutter* this, GlobalContext* globalCtx);

const ActorInit Bg_Ikana_Shutter_InitVars = {
    ACTOR_BG_IKANA_SHUTTER,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaShutter),
    (ActorFunc)BgIkanaShutter_Init,
    (ActorFunc)BgIkanaShutter_Destroy,
    (ActorFunc)BgIkanaShutter_Update,
    (ActorFunc)BgIkanaShutter_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern CollisionHeader D_06000F28;
extern Gfx D_06000CE8[];

s32 BgIkanaShutter_AllSwitchesPressed(BgIkanaShutter* this, GlobalContext* globalCtx) {
    return Flags_GetSwitch(globalCtx, this->dyna.actor.params & 0x7F) &&
           Flags_GetSwitch(globalCtx, (this->dyna.actor.params & 0x7F) + 1) &&
           Flags_GetSwitch(globalCtx, (this->dyna.actor.params & 0x7F) + 2) &&
           Flags_GetSwitch(globalCtx, (this->dyna.actor.params & 0x7F) + 3);
}

void BgIkanaShutter_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaShutter* this = THIS;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000F28);
    if (!((this->dyna.actor.params >> 8) & 1)) {
        if (BgIkanaShutter_AllSwitchesPressed(this, globalCtx)) {
            func_80BD599C(this);
            return;
        }
        func_80BD5828(this);
        return;
    }
    if (Actor_GetRoomCleared(globalCtx, this->dyna.actor.room)) {
        BgIkanaShutter_SetupDoNothing(this);
        return;
    }
    func_80BD5AE8(this);
}

void BgIkanaShutter_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaShutter* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80BD5828(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5844;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80BD5844(BgIkanaShutter* this, GlobalContext* globalCtx) {
    if (BgIkanaShutter_AllSwitchesPressed(this, globalCtx)) {
        func_80BD5878(this);
    }
}

void func_80BD5878(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5894;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80BD5894(BgIkanaShutter* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        func_80BD58F0(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

void func_80BD58F0(BgIkanaShutter* this) {
    this->dyna.actor.velocity.y = 0.6f;
    this->actionFunc = func_80BD5910;
}

void func_80BD5910(BgIkanaShutter* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->dyna.actor.velocity.y, 4.0f, 0.5f);
    if (Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + 220.0f, 0.5f,
                           this->dyna.actor.velocity.y, 1.0f) < 0.5f) {
        func_80BD599C(this);
    }
}

void func_80BD599C(BgIkanaShutter* this) {
    this->actionFunc = func_80BD59C4;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 220.0f;
}

void func_80BD59C4(BgIkanaShutter* this, GlobalContext* globalCtx) {
    if (BgIkanaShutter_AllSwitchesPressed(this, globalCtx) == 0) {
        func_80BD59F8(this);
    }
}

void func_80BD59F8(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5A18;
    this->dyna.actor.velocity.y = -23.0f;
}

void func_80BD5A18(BgIkanaShutter* this, GlobalContext* globalCtx) {
    s32 pad[2];
    s16 quake;

    this->dyna.actor.velocity.y += -5.0f;
    this->dyna.actor.velocity.y *= 0.978f;
    this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
    if (this->dyna.actor.world.pos.y <= this->dyna.actor.home.pos.y) {
        quake = Quake_Add(ACTIVE_CAM, 3);
        Quake_SetSpeed(quake, 0x5420);
        Quake_SetQuakeValues(quake, 4, 0, 0, 0);
        Quake_SetCountdown(quake, 12);
        func_80BD5828(this);
    }
}

void func_80BD5AE8(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5B04;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80BD5B04(BgIkanaShutter* this, GlobalContext* globalCtx) {
    if (Actor_GetRoomClearedTemp(globalCtx, this->dyna.actor.room)) {
        func_80BD5B44(this);
    }
}

void func_80BD5B44(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5B60;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y;
}

void func_80BD5B60(BgIkanaShutter* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        Actor_SetRoomCleared(globalCtx, this->dyna.actor.room);
        func_80BD5BC4(this);
        return;
    }
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
}

void func_80BD5BC4(BgIkanaShutter* this) {
    this->actionFunc = func_80BD5BD8;
}

void func_80BD5BD8(BgIkanaShutter* this, GlobalContext* globalCtx) {
    Math_StepToF(&this->dyna.actor.velocity.y, 4.0f, 0.5f);
    if (Math_SmoothStepToF(&this->dyna.actor.world.pos.y, this->dyna.actor.home.pos.y + -220.0f, 0.5f,
                           this->dyna.actor.velocity.y, 1.0f) < 0.5f) {
        BgIkanaShutter_SetupDoNothing(this);
    }
}

void BgIkanaShutter_SetupDoNothing(BgIkanaShutter* this) {
    this->actionFunc = BgIkanaShutter_DoNothing;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + -220.0f;
}

void BgIkanaShutter_DoNothing(BgIkanaShutter* this, GlobalContext* globalCtx) {
}

void BgIkanaShutter_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgIkanaShutter* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgIkanaShutter_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000CE8);
}
