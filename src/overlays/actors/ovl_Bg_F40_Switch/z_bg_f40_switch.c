/*
 * File: z_bg_f40_switch.c
 * Overlay: ovl_Bg_F40_Switch
 * Description: Stone Tower FloorSwitch
 */
#include "z_bg_f40_switch.h"
#include "z64rumble.h"
#include "assets/objects/object_f40_switch/object_f40_switch.h"

#define FLAGS (ACTOR_FLAG_UPDATE_CULLING_DISABLED)

void BgF40Switch_Init(Actor* thisx, PlayState* play);
void BgF40Switch_Destroy(Actor* thisx, PlayState* play);
void BgF40Switch_Update(Actor* thisx, PlayState* play);
void BgF40Switch_Draw(Actor* thisx, PlayState* play);

void BgF40Switch_CheckAll(BgF40Switch* this, PlayState* play);
void BgF40Switch_Unpress(BgF40Switch* this, PlayState* play);
void BgF40Switch_IdlePressed(BgF40Switch* this, PlayState* play);
void BgF40Switch_Press(BgF40Switch* this, PlayState* play);
void BgF40Switch_WaitToPress(BgF40Switch* this, PlayState* play);
void BgF40Switch_IdleUnpressed(BgF40Switch* this, PlayState* play);

ActorProfile Bg_F40_Switch_Profile = {
    /**/ ACTOR_BG_F40_SWITCH,
    /**/ ACTORCAT_SWITCH,
    /**/ FLAGS,
    /**/ OBJECT_F40_SWITCH,
    /**/ sizeof(BgF40Switch),
    /**/ BgF40Switch_Init,
    /**/ BgF40Switch_Destroy,
    /**/ BgF40Switch_Update,
    /**/ BgF40Switch_Draw,
};

#if MM_VERSION >= N64_US
s32 sBgF40SwitchGlobalsInitialized = false;
u32 sBgF40SwitchLastUpdateFrame;
#endif

/*
 * Updates all instances of this actor in the current room, unless it's already been called this frame.
 */
#if MM_VERSION >= N64_US
void BgF40Switch_CheckAll(BgF40Switch* this, PlayState* play) {
    if (play->gameplayFrames != sBgF40SwitchLastUpdateFrame) {
        u32 pressedSwitchFlags[4] = { 0 };
        s32 pad;
        s32 switchFlag;
        s32 isPressed;
        Actor* actor;
        BgF40Switch* actorAsSwitch;
        u32 inCsMode = Player_InCsMode(play);

        for (actor = play->actorCtx.actorLists[ACTORCAT_SWITCH].first; actor != NULL; actor = actor->next) {
            if ((actor->id == ACTOR_BG_F40_SWITCH) && (actor->room == this->dyna.actor.room) &&
                (actor->update != NULL)) {
                actorAsSwitch = (BgF40Switch*)actor;
                actorAsSwitch->wasPressed = actorAsSwitch->isPressed;
                isPressed = DynaPolyActor_IsSwitchPressed(&actorAsSwitch->dyna);
                if (actorAsSwitch->isPressed && (actorAsSwitch->actionFunc == BgF40Switch_IdlePressed)) {
                    // Switch is fully pressed - if there's nothing keeping it pressed, wait a short time before
                    // reverting to unpressed state.
                    if (isPressed || inCsMode) {
                        actorAsSwitch->switchReleaseDelay = 6;
                    } else if (actorAsSwitch->switchReleaseDelay > 0) {
                        actorAsSwitch->switchReleaseDelay--;
                    } else {
                        actorAsSwitch->isPressed = isPressed;
                    }
                } else {
                    // No delay when pressing switch, or releasing from a not-fully-pressed state.
                    actorAsSwitch->isPressed = isPressed;
                }
                if (actorAsSwitch->isPressed) {
                    switchFlag = BGF40SWITCH_GET_SWITCH_FLAG(&actorAsSwitch->dyna.actor);
                    if ((switchFlag > SWITCH_FLAG_NONE) && (switchFlag < 0x80)) {
                        pressedSwitchFlags[(switchFlag & ~0x1F) >> 5] |= 1 << (switchFlag & 0x1F);
                        if (!actorAsSwitch->wasPressed && (actorAsSwitch->actionFunc == BgF40Switch_IdleUnpressed) &&
                            !Flags_GetSwitch(play, switchFlag)) {
                            actorAsSwitch->isInitiator = true;
                        }
                    }
                }
            }
        }
        for (actor = play->actorCtx.actorLists[ACTORCAT_SWITCH].first; actor != NULL; actor = actor->next) {
            if ((actor->id == ACTOR_BG_F40_SWITCH) && (actor->room == this->dyna.actor.room) &&
                (actor->update != NULL)) {
                switchFlag = BGF40SWITCH_GET_SWITCH_FLAG(actor);
                if ((switchFlag > SWITCH_FLAG_NONE) && (switchFlag < 0x80) && Flags_GetSwitch(play, switchFlag) &&
                    !(pressedSwitchFlags[(switchFlag & ~0x1F) >> 5] & (1 << (switchFlag & 0x1F)))) {
                    Flags_UnsetSwitch(play, switchFlag);
                }
            }
        }
        sBgF40SwitchLastUpdateFrame = play->gameplayFrames;
    }
}
#endif

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(cullingVolumeDistance, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(cullingVolumeDownward, 200, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 123, ICHAIN_STOP),
};

void BgF40Switch_Init(Actor* thisx, PlayState* play) {
    BgF40Switch* this = (BgF40Switch*)thisx;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->dyna.actor.scale.y = 0.165f;
    this->actionFunc = BgF40Switch_IdleUnpressed;
    this->dyna.actor.world.pos.y = this->dyna.actor.home.pos.y + 1.0f;
    DynaPolyActor_Init(&this->dyna, DYNA_TRANSFORM_POS);
    DynaPolyActor_LoadMesh(play, &this->dyna, &gStoneTowerFloorSwitchCol);
#if MM_VERSION >= N64_US
    if (!sBgF40SwitchGlobalsInitialized) {
        sBgF40SwitchLastUpdateFrame = play->gameplayFrames;
        sBgF40SwitchGlobalsInitialized = true;
    }
#endif
}

void BgF40Switch_Destroy(Actor* thisx, PlayState* play) {
    BgF40Switch* this = (BgF40Switch*)thisx;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void BgF40Switch_Unpress(BgF40Switch* this, PlayState* play) {
    this->dyna.actor.scale.y += 0.0495f;
    if (this->dyna.actor.scale.y >= 0.165f) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_SWITCH);
        this->actionFunc = BgF40Switch_IdleUnpressed;
        this->dyna.actor.scale.y = 0.165f;
    }
}

void BgF40Switch_IdlePressed(BgF40Switch* this, PlayState* play) {
#if MM_VERSION >= N64_US
    if (!this->isPressed) {
        this->actionFunc = BgF40Switch_Unpress;
    }
#else
    if (!DynaPolyActor_IsSwitchPressed(&this->dyna) && !Player_InCsMode(play)) {
        if (this->switchReleaseDelay <= 0) {
            this->actionFunc = BgF40Switch_Unpress;
            Flags_UnsetSwitch(play, BGF40SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
        } else {
            this->switchReleaseDelay--;
        }
    } else {
        this->switchReleaseDelay = 6;
    }
#endif
}

void BgF40Switch_Press(BgF40Switch* this, PlayState* play) {
    this->dyna.actor.scale.y -= 0.0495f;
    if (this->dyna.actor.scale.y <= 0.0165f) {
        Actor_PlaySfx(&this->dyna.actor, NA_SE_EV_IKANA_BLOCK_SWITCH);
        Rumble_Request(this->dyna.actor.xyzDistToPlayerSq, 120, 20, 10);
#if MM_VERSION >= N64_US
        if (this->isInitiator) {
            CutsceneManager_Stop(this->dyna.actor.csId);
            this->isInitiator = false;
        }
#else
        CutsceneManager_Stop(this->dyna.actor.csId);
#endif
        this->actionFunc = BgF40Switch_IdlePressed;
        this->dyna.actor.scale.y = 0.0165f;
        this->switchReleaseDelay = 6;
    }
}

void BgF40Switch_WaitToPress(BgF40Switch* this, PlayState* play) {
#if MM_VERSION >= N64_US
    if (!this->isInitiator || (this->dyna.actor.csId == CS_ID_NONE)) {
#else
    if (this->dyna.actor.csId == CS_ID_NONE) {
#endif
        this->actionFunc = BgF40Switch_Press;
#if MM_VERSION >= N64_US
        if (this->isInitiator) {
            Flags_SetSwitch(play, BGF40SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
        }
#else
        Flags_SetSwitch(play, BGF40SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
#endif
    } else if (CutsceneManager_IsNext(this->dyna.actor.csId)) {
        CutsceneManager_StartWithPlayerCs(this->dyna.actor.csId, &this->dyna.actor);
        this->actionFunc = BgF40Switch_Press;
#if MM_VERSION >= N64_US
        if (this->isInitiator) {
            Flags_SetSwitch(play, BGF40SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
        }
#else
        Flags_SetSwitch(play, BGF40SWITCH_GET_SWITCH_FLAG(&this->dyna.actor));
#endif
    } else {
        CutsceneManager_Queue(this->dyna.actor.csId);
    }
}

void BgF40Switch_IdleUnpressed(BgF40Switch* this, PlayState* play) {
#if MM_VERSION >= N64_US
    if (this->isPressed) {
        this->actionFunc = BgF40Switch_WaitToPress;
    }
#else
    if (DynaPolyActor_IsSwitchPressed(&this->dyna)) {
        this->actionFunc = BgF40Switch_WaitToPress;
    }
#endif
}

void BgF40Switch_Update(Actor* thisx, PlayState* play) {
    BgF40Switch* this = (BgF40Switch*)thisx;

#if MM_VERSION >= N64_US
    BgF40Switch_CheckAll(this, play);
#endif
    this->actionFunc(this, play);
}

void BgF40Switch_Draw(Actor* thisx, PlayState* play) {
    BgF40Switch* this = (BgF40Switch*)thisx;

    Gfx_DrawDListOpa(play, gStoneTowerFloorSwitchDL);
    Gfx_DrawDListOpa(play, gStoneTowerFloorSwitchOutlineDL);
}
