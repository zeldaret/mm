/*
 * File: z_obj_ghaka.c
 * Overlay: ovl_Obj_Ghaka
 * Description: Darmani's Gravestone
 */

#include "z_obj_ghaka.h"
#include "objects/object_ghaka/object_ghaka.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_8 | ACTOR_FLAG_20)

#define THIS ((ObjGhaka*)thisx)

void ObjGhaka_Init(Actor* thisx, PlayState* play);
void ObjGhaka_Destroy(Actor* thisx, PlayState* play);
void ObjGhaka_Update(Actor* thisx, PlayState* play);
void ObjGhaka_Draw(Actor* thisx, PlayState* play);

void func_80B3C260(ObjGhaka* this);
void func_80B3C29C(ObjGhaka* this);
void func_80B3C2B0(ObjGhaka* this);
void func_80B3C2C4(ObjGhaka* this, PlayState* play);
void func_80B3C39C(ObjGhaka* this, PlayState* play);
void func_80B3C4E0(ObjGhaka* this, PlayState* play);
void func_80B3C624(ObjGhaka* this, PlayState* play);

const ActorInit Obj_Ghaka_InitVars = {
    ACTOR_OBJ_GHAKA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GHAKA,
    sizeof(ObjGhaka),
    (ActorFunc)ObjGhaka_Init,
    (ActorFunc)ObjGhaka_Destroy,
    (ActorFunc)ObjGhaka_Update,
    (ActorFunc)ObjGhaka_Draw,
};

static Vec3f D_80B3C960 = { 0.0f, 0.0f, 0.0f };

static InitChainEntry D_80B3C96C[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

void func_80B3C260(ObjGhaka* this) {
    if (gSaveContext.save.weekEventReg[20] & 0x20) {
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + 100.0f;
    }
    this->actionFunc = func_80B3C39C;
}

void func_80B3C29C(ObjGhaka* this) {
    this->actionFunc = func_80B3C4E0;
}

void func_80B3C2B0(ObjGhaka* this) {
    this->actionFunc = func_80B3C624;
}

void func_80B3C2C4(ObjGhaka* this, PlayState* play) {
    if (!(gSaveContext.save.weekEventReg[20] & 0x20)) {
        Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0, 0, 0,
                                      this->dyna.actor.cutscene, this->dyna.actor.unk20, 0);
    } else {
        Actor_SpawnAsChildAndCutscene(&play->actorCtx, play, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0, 0, 1, -1,
                                      this->dyna.actor.unk20, 0);
    }
}

void func_80B3C39C(ObjGhaka* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    s16 distDiff = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;

    if (Actor_ProcessTalkRequest(&this->dyna.actor, &play->state)) {
        func_80B3C29C(this);
    } else if (this->dyna.actor.xzDistToPlayer < 100.0f || this->dyna.actor.isTargeted) {
        if (distDiff <= -0x5556 || distDiff >= 0x5556) {
            func_800B863C(&this->dyna.actor, play);
            if (player->transformation == PLAYER_FORM_GORON) {
                this->dyna.actor.textId = 0xCF3;
            } else {
                this->dyna.actor.textId = 0xCF2;
            }
        }
    }

    if (this->dyna.pushForce < 0.0f && !(gSaveContext.save.weekEventReg[20] & 0x20) &&
        player->transformation == PLAYER_FORM_GORON) {
        func_80B3C2B0(this);
    } else {
        player->stateFlags2 &= ~0x10;
        this->dyna.pushForce = 0.0f;
    }
}

void func_80B3C4E0(ObjGhaka* this, PlayState* play) {
    u8 talkState = Message_GetState(&play->msgCtx);

    if (talkState == TEXT_STATE_5) {
        if (Message_ShouldAdvance(play)) {
            play->msgCtx.msgMode = 0x43;
            play->msgCtx.stateTimer = 4;
            func_80B3C260(this);
        }
    } else if (talkState == TEXT_STATE_CHOICE) {
        if (Message_ShouldAdvance(play)) {
            switch (play->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->dyna.actor.textId = 0xCF5;
                    Message_StartTextbox(play, this->dyna.actor.textId, &this->dyna.actor);
                    break;

                case 1:
                    func_8019F208();
                    this->dyna.actor.textId = 0xCF7;
                    Message_StartTextbox(play, this->dyna.actor.textId, &this->dyna.actor);
                    break;

                case 2:
                    func_8019F230();
                    play->msgCtx.msgMode = 0x43;
                    play->msgCtx.stateTimer = 4;
                    func_80B3C260(this);
                    break;
            }
        }
    }
}

void func_80B3C624(ObjGhaka* this, PlayState* play) {
    Player* player = GET_PLAYER(play);
    u8 stepTemp = Math_StepToS(&this->unk_168, 0x64, 1);

    this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + this->unk_168;

    if (stepTemp) {
        player->stateFlags2 &= ~0x10;
        this->dyna.pushForce = 0.0f;
        func_80B3C2C4(this, play);
        gSaveContext.save.weekEventReg[20] |= 0x20;
        func_80B3C260(this);
        Audio_PlaySfxAtPos(&D_80B3C960, NA_SE_EV_BLOCK_BOUND);
    } else {
        Audio_PlaySfxAtPos(&D_80B3C960, NA_SE_EV_ROCK_SLIDE - SFX_FLAG);
    }
}

void ObjGhaka_Init(Actor* thisx, PlayState* play) {
    ObjGhaka* this = THIS;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    Actor_ProcessInitChain(&this->dyna.actor, D_80B3C96C);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    DynaPolyActor_Init(&this->dyna, 1);
    CollisionHeader_GetVirtual(&object_ghaka_Colheader_003CD0, &colHeader);
    this->dyna.bgId = DynaPoly_SetBgActor(play, &play->colCtx.dyna, &this->dyna.actor, colHeader);
    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x4);
    if (this->dyna.actor.floorPoly == 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
    if (gSaveContext.save.weekEventReg[20] & 0x20) {
        func_80B3C2C4(this, play);
    }
    func_80B3C260(this);
}

void ObjGhaka_Destroy(Actor* thisx, PlayState* play) {
    ObjGhaka* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
}

void ObjGhaka_Update(Actor* thisx, PlayState* play) {
    ObjGhaka* this = THIS;

    this->actionFunc(this, play);
    thisx->focus.pos.x = thisx->world.pos.x;
    thisx->focus.pos.y = thisx->world.pos.y + 60.0f;
    thisx->focus.pos.z = thisx->world.pos.z;
}

void ObjGhaka_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);
    func_8012C28C(play->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_ghaka_DL_001A20);
    func_8012C2DC(play->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_ghaka_DL_001980);
    CLOSE_DISPS(play->state.gfxCtx);
}
