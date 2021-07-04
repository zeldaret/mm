/*
 * File: z_bg_ctower_rot.c
 * Overlay: ovl_Bg_CtowerRot
 * Description: Twisting path along with the Doors to Clocktower
 */

#include "z_bg_ctower_rot.h"

#define FLAGS 0x00000030

#define THIS ((BgCtowerRot*)thisx)

void BgCtowerRot_Init(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Destroy(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Update(Actor* thisx, GlobalContext* globalCtx);
void BgCtowerRot_Draw(Actor* thisx, GlobalContext* globalCtx);

void BgCtowerRot_CorridorRotate(BgCtowerRot* this, GlobalContext* globalCtx);
void BgCtowerRot_DoorDoNothing(BgCtowerRot* this, GlobalContext* globalCtx);
void BgCtowerRot_DoorIdle(BgCtowerRot* this, GlobalContext* globalCtx);
void BgCtowerRot_SetupDoorClose(BgCtowerRot* this, GlobalContext* globalCtx);

const ActorInit Bg_Ctower_Rot_InitVars = {
    ACTOR_BG_CTOWER_ROT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_CTOWER_ROT,
    sizeof(BgCtowerRot),
    (ActorFunc)BgCtowerRot_Init,
    (ActorFunc)BgCtowerRot_Destroy,
    (ActorFunc)BgCtowerRot_Update,
    (ActorFunc)BgCtowerRot_Draw,
};

extern Gfx D_060129D0[];

extern Gfx D_06012DA0[];

extern CollisionHeader D_060142E8;

extern Gfx D_06017220[];

extern CollisionHeader D_06017410;

extern Gfx D_060174E0[];

extern CollisionHeader D_06017650;

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static Gfx* bgCtowerRotDlists[] = { D_06012DA0, D_06017220, D_060174E0 };

void BgCtowerRot_Init(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerRot* this = THIS;
    s32 pad;
    Player* player;
    Vec3f offset;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    BcCheck3_BgActorInit(&this->dyna, 1);
    if (this->dyna.actor.params == CORRIDOR) {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_060142E8);
        this->actionFunc = BgCtowerRot_CorridorRotate;
        return;
    }
    player = PLAYER;
    if (this->dyna.actor.params == MAIN_DOOR) {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06017410);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y + 0x4000;
    } else {
        BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06017650);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y - 0x4000;
    }
    Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &offset, &player->actor.world.pos);
    if (offset.z < 0.0f) {
        this->dyna.actor.world.pos.x = this->dyna.actor.home.pos.x + (Math_SinS(this->dyna.actor.world.rot.y) * 80.0f);
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + (Math_CosS(this->dyna.actor.world.rot.y) * 80.0f);
        this->timer = 80.0f;
        this->actionFunc = BgCtowerRot_DoorIdle;
    } else {
        this->actionFunc = BgCtowerRot_DoorDoNothing;
    }
}

void BgCtowerRot_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerRot* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void BgCtowerRot_CorridorRotate(BgCtowerRot* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f offset;
    f32 rotZ;
    f32 offsetDiffZ;
    f32 rotZtmp;

    Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &offset, &player->actor.world.pos);
    if (offset.z > 1100.0f) {
        rotZ = 0.0f;
    } else {
        offsetDiffZ = 1100.0f - offset.z;
        rotZtmp = (offsetDiffZ > 1000.0f)
                      ? 1000.0f
                      : offsetDiffZ; // Removing rotZtmp just causes regalloc issues and a missing instruction
        rotZ = rotZtmp;
    }
    func_800DFAC8(globalCtx->cameraPtrs[0], 0x11);
    this->dyna.actor.shape.rot.z = rotZ * 16.384f;
    if (globalCtx->csCtx.frames == 0x84) {
        play_sound(NA_SE_SY_SPIRAL_DASH);
    }
}

void BgCtowerRot_DoorDoNothing(BgCtowerRot* this, GlobalContext* globalCtx) {
}

void BgCtowerRot_DoorClose(BgCtowerRot* this, GlobalContext* globalCtx) {
    if (!Math_SmoothStepToF(&this->timer, 0.0f, 0.1f, 15.0f, 0.1f)) {
        if (this->dyna.actor.params == MAIN_DOOR) {
            Audio_PlayActorSound2(&this->dyna.actor, NA_SE_EV_STONEDOOR_STOP);
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
        this->actionFunc = BgCtowerRot_DoorDoNothing;
    } else if (this->dyna.actor.params == 1) {
        func_800B9010(&this->dyna.actor, NA_SE_EV_STONE_STATUE_OPEN - SFX_FLAG);
    }
    this->dyna.actor.world.pos.x =
        this->dyna.actor.home.pos.x + (Math_SinS(this->dyna.actor.world.rot.y) * this->timer);
    this->dyna.actor.world.pos.z =
        this->dyna.actor.home.pos.z + (Math_CosS(this->dyna.actor.world.rot.y) * this->timer);
}

void BgCtowerRot_DoorIdle(BgCtowerRot* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    Vec3f offset;

    Actor_CalcOffsetOrientedToDrawRotation(&this->dyna.actor, &offset, &player->actor.world.pos);
    if (offset.z > 30.0f) {
        this->unk160 = 0.0f;
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        this->actionFunc = BgCtowerRot_SetupDoorClose;
    }
}

void BgCtowerRot_SetupDoorClose(BgCtowerRot* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        if (this->dyna.actor.params == MAIN_DOOR) {
            ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        }
        this->actionFunc = BgCtowerRot_DoorClose;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void BgCtowerRot_Update(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerRot* this = THIS;

    this->actionFunc(this, globalCtx);
}

void BgCtowerRot_Draw(Actor* thisx, GlobalContext* globalCtx) {
    BgCtowerRot* this = THIS;

    func_800BDFC0(globalCtx, bgCtowerRotDlists[this->dyna.actor.params]);
    if (this->dyna.actor.params == CORRIDOR) {
        func_800BE03C(globalCtx, D_060129D0);
    }
}
