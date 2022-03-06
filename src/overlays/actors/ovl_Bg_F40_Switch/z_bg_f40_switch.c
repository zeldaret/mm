/*
 * File: z_bg_f40_switch.c
 * Overlay: ovl_Bg_F40_Switch
 * Description: Stone Tower Switch
 */

#include "z_bg_f40_switch.h"
#include "objects/object_f40_switch/object_f40_switch.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((BgF40Switch*)thisx)

void BgF40Switch_Init(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Update(Actor* thisx, GlobalContext* globalCtx);
void BgF40Switch_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80BC47B0(BgF40Switch* this, GlobalContext* globalCtx);
void BgF40Switch_Unpress(BgF40Switch* this, GlobalContext* globalCtx);
void BgF40Switch_IdlePressed(BgF40Switch* this, GlobalContext* globalCtx);
void BgF40Switch_Press(BgF40Switch* this, GlobalContext* globalCtx);
void BgF40Switch_WaitToPress(BgF40Switch* this, GlobalContext* globalCtx);
void BgF40Switch_IdleUnpressed(BgF40Switch* this, GlobalContext* globalCtx);

const ActorInit Bg_F40_Switch_InitVars = {
    ACTOR_BG_F40_SWITCH,
    ACTORCAT_SWITCH,
    FLAGS,
    OBJECT_F40_SWITCH,
    sizeof(BgF40Switch),
    (ActorFunc)BgF40Switch_Init,
    (ActorFunc)BgF40Switch_Destroy,
    (ActorFunc)BgF40Switch_Update,
    (ActorFunc)BgF40Switch_Draw,
};

s32 sBgF40SwitchGlobalsInitialized = false;
u32 sBgF40SwitchLastUpdateFrame;

/*
 * Updates all instances of this actor in the current room, unless it's already been called this frame.
 */
void func_80BC47B0(BgF40Switch* this, GlobalContext* globalCtx) {
    if (globalCtx->gameplayFrames != sBgF40SwitchLastUpdateFrame) {
        u32 pressedSwitchFlags[4] = { 0 };
        u32 pad;
        s32 switchFlag;
        s32 isPressed;
        Actor* actor;
        BgF40Switch* actorAsSwitch;
        u32 unk40 = func_801233E4(globalCtx);

        for (actor = globalCtx->actorCtx.actorList[ACTORCAT_SWITCH].first; actor != NULL; actor = actor->next) {
            if (actor->id == ACTOR_BG_F40_SWITCH && actor->room == this->actor.actor.room && actor->update != NULL) {
                actorAsSwitch = (BgF40Switch*)actor;
                actorAsSwitch->wasPressed = actorAsSwitch->isPressed;
                isPressed = DynaPolyActor_IsInSwitchPressedState(&actorAsSwitch->actor);
                if (actorAsSwitch->isPressed && actorAsSwitch->actionFunc == BgF40Switch_IdlePressed) {
                    // Switch is fully pressed - if there's nothing keeping it pressed, wait a short time before
                    // reverting to unpressed state.
                    if (isPressed || unk40) {
                        actorAsSwitch->switchReleaseDelay = 6;
                    } else {
                        if (actorAsSwitch->switchReleaseDelay > 0) {
                            actorAsSwitch->switchReleaseDelay--;
                        } else {
                            actorAsSwitch->isPressed = isPressed;
                        }
                    }
                } else {
                    // No delay when pressing switch, or releasing from a not-fully-pressed state.
                    actorAsSwitch->isPressed = isPressed;
                }
                if (actorAsSwitch->isPressed) {
                    switchFlag = BGF40SWITCH_GET_SWITCHFLAG(actorAsSwitch);
                    if (switchFlag >= 0 && switchFlag < 0x80) {
                        pressedSwitchFlags[(switchFlag & ~0x1F) >> 5] |= 1 << (switchFlag & 0x1F);
                        if (!actorAsSwitch->wasPressed &&
                            actorAsSwitch->actionFunc == BgF40Switch_IdleUnpressed &&
                            !Flags_GetSwitch(globalCtx, switchFlag)) {
                            actorAsSwitch->isInitiator = true;
                        }
                    }
                }
            }
        }
        for (actor = globalCtx->actorCtx.actorList[ACTORCAT_SWITCH].first; actor != NULL; actor = actor->next) {
            if (actor->id == ACTOR_BG_F40_SWITCH && actor->room == this->actor.actor.room && actor->update != 0) {
                switchFlag = BGF40SWITCH_GET_SWITCHFLAG((BgF40Switch*)actor);
                if (switchFlag >= 0 && switchFlag < 0x80 && Flags_GetSwitch(globalCtx, switchFlag) &&
                    !(pressedSwitchFlags[(switchFlag & ~0x1F) >> 5] & (1 << (switchFlag & 0x1F)))) {
                    Actor_UnsetSwitchFlag(globalCtx, switchFlag);
                }
            }
        }
        sBgF40SwitchLastUpdateFrame = globalCtx->gameplayFrames;
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 123, ICHAIN_STOP),
};

void BgF40Switch_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Switch* this = THIS;

    Actor_ProcessInitChain(&this->actor.actor, sInitChain);
    this->actor.actor.scale.y = 0.165f;
    this->actionFunc = BgF40Switch_IdleUnpressed;
    this->actor.actor.world.pos.y = this->actor.actor.home.pos.y + 1.0f;
    DynaPolyActor_Init(&this->actor, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->actor, &object_f40_switch_Colheader_000118);
    if (!sBgF40SwitchGlobalsInitialized) {
        sBgF40SwitchLastUpdateFrame = globalCtx->gameplayFrames;
        sBgF40SwitchGlobalsInitialized = true;
    }
}

void BgF40Switch_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Switch* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->actor.bgId);
}

void BgF40Switch_Unpress(BgF40Switch* this, GlobalContext* globalCtx) {
    this->actor.actor.scale.y += 0.0495f;
    if (this->actor.actor.scale.y >= 0.165f) {
        Audio_PlayActorSound2(&this->actor.actor, NA_SE_EV_IKANA_BLOCK_SWITCH);
        this->actionFunc = BgF40Switch_IdleUnpressed;
        this->actor.actor.scale.y = 0.165f;
    }
}

void BgF40Switch_IdlePressed(BgF40Switch* this, GlobalContext* globalCtx) {
    if (!this->isPressed) {
        this->actionFunc = BgF40Switch_Unpress;
    }
}

void BgF40Switch_Press(BgF40Switch* this, GlobalContext* globalCtx) {
    this->actor.actor.scale.y -= 0.0495f;
    if (this->actor.actor.scale.y <= 0.0165f) {
        Audio_PlayActorSound2(&this->actor.actor, NA_SE_EV_IKANA_BLOCK_SWITCH);
        func_8013ECE0(this->actor.actor.xyzDistToPlayerSq, 120, 20, 10);
        if (this->isInitiator) {
            ActorCutscene_Stop(this->actor.actor.cutscene);
            this->isInitiator = false;
        }
        this->actionFunc = BgF40Switch_IdlePressed;
        this->actor.actor.scale.y = 0.0165f;
        this->switchReleaseDelay = 6;
    }
}

void BgF40Switch_WaitToPress(BgF40Switch* this, GlobalContext* globalCtx) {
    if (!this->isInitiator || this->actor.actor.cutscene == -1) {
        this->actionFunc = BgF40Switch_Press;
        if (this->isInitiator) {
            Actor_SetSwitchFlag(globalCtx, BGF40SWITCH_GET_SWITCHFLAG(this));
        }
    } else if (ActorCutscene_GetCanPlayNext(this->actor.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.actor.cutscene, &this->actor.actor);
        this->actionFunc = BgF40Switch_Press;
        if (this->isInitiator) {
            Actor_SetSwitchFlag(globalCtx, BGF40SWITCH_GET_SWITCHFLAG(this));
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.actor.cutscene);
    }
}

void BgF40Switch_IdleUnpressed(BgF40Switch* this, GlobalContext* globalCtx) {
    if (this->isPressed) {
        this->actionFunc = BgF40Switch_WaitToPress;
    }
}

void BgF40Switch_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Switch* this = THIS;

    func_80BC47B0(this, globalCtx);
    this->actionFunc(this, globalCtx);
}

void BgF40Switch_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgF40Switch* this = THIS;

    func_800BDFC0(globalCtx, object_f40_switch_DL_000438);
    func_800BDFC0(globalCtx, object_f40_switch_DL_000390);
}
