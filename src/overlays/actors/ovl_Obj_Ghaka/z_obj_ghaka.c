/*
 * File z_obj_ghaka.c
 * Overlay: ovl_obj_ghaka
 * Description: Darmani's Gravestone
 */

#include "z_obj_ghaka.h"

#define FLAGS 0x00000029

#define THIS ((ObjGhaka*)thisx)

void ObjGhaka_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGhaka_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B3C260(ObjGhaka* this);
void func_80B3C29C(ObjGhaka* this);
void func_80B3C2B0(ObjGhaka* this);
void func_80B3C2C4(ObjGhaka* this, GlobalContext* globalCtx);
void func_80B3C39C(ObjGhaka* this, GlobalContext* globalCtx);
void func_80B3C4E0(ObjGhaka* this, GlobalContext* globalCtx);
void func_80B3C624(ObjGhaka* this, GlobalContext* globalCtx);

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

extern Gfx D_06001A20[];
extern Gfx D_06001980[];
extern CollisionHeader D_06003CD0;

void func_80B3C260(ObjGhaka* this) {
    if (gSaveContext.weekEventReg[20] & 0x20) {
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

void func_80B3C2C4(ObjGhaka* this, GlobalContext* globalCtx) {
    if (!(gSaveContext.weekEventReg[20] & 0x20)) {
        Actor_SpawnWithParentAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0,
                                         0, 0, this->dyna.actor.cutscene, this->dyna.actor.unk20, 0);
    } else {
        Actor_SpawnWithParentAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0,
                                         0, 1, -1, this->dyna.actor.unk20, 0);
    }
}

void func_80B3C39C(ObjGhaka* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 distDiff = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;

    if (func_800B84D0(&this->dyna.actor, globalCtx)) {
        func_80B3C29C(this);
    } else if (this->dyna.actor.xzDistToPlayer < 100.0f || this->dyna.actor.isTargeted) {
        if (distDiff <= -0x5556 || distDiff >= 0x5556) {
            func_800B863C(&this->dyna.actor, globalCtx);
            if (player->transformation == PLAYER_FORM_GORON) {
                this->dyna.actor.textId = 0xCF3;
            } else {
                this->dyna.actor.textId = 0xCF2;
            }
        }
    }
    if (this->dyna.unk148 < 0.0f && !(gSaveContext.weekEventReg[20] & 0x20) &&
        player->transformation == PLAYER_FORM_GORON) {
        func_80B3C2B0(this);
    } else {
        player->stateFlags2 &= ~0x10;
        this->dyna.unk148 = 0.0f;
    }
}

void func_80B3C4E0(ObjGhaka* this, GlobalContext* globalCtx) {
    s32 temp_v0 = func_80152498(&globalCtx->msgCtx);

    if (temp_v0 == 5) {
        if (func_80147624(globalCtx)) {
            globalCtx->msgCtx.unk11F22 = 0x43;
            globalCtx->msgCtx.unk12023 = 4;
            func_80B3C260(this);
        }
        // Could be fake, but helps match
    } else if ((temp_v0 & 0xFFFFFFFF) == 4) {
        if (func_80147624(globalCtx)) {
            switch (globalCtx->msgCtx.choiceIndex) {
                case 0:
                    func_8019F208();
                    this->dyna.actor.textId = 0xCF5;
                    func_801518B0(globalCtx, this->dyna.actor.textId, &this->dyna.actor);
                    break;
                case 1:
                    func_8019F208();
                    this->dyna.actor.textId = 0xCF7;
                    func_801518B0(globalCtx, this->dyna.actor.textId, &this->dyna.actor);
                    break;
                case 2:
                    func_8019F230();
                    globalCtx->msgCtx.unk11F22 = 0x43;
                    globalCtx->msgCtx.unk12023 = 4;
                    func_80B3C260(this);
            }
        }
    }
}

void func_80B3C624(ObjGhaka* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    u8 stepTemp = Math_StepToS(&this->unk_168, 0x64, 1);

    this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + this->unk_168;

    if (stepTemp) {
        player->stateFlags2 &= ~0x10;
        this->dyna.unk148 = 0.0f;
        func_80B3C2C4(this, globalCtx);
        gSaveContext.weekEventReg[20] |= 0x20;
        func_80B3C260(this);
        func_8019F1C0(&D_80B3C960, NA_SE_EV_BLOCK_BOUND);
    } else {
        func_8019F1C0(&D_80B3C960, NA_SE_EV_ROCK_SLIDE - SFX_FLAG);
    }
}

void ObjGhaka_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;
    s32 pad;
    CollisionHeader* colHeader = NULL;

    Actor_ProcessInitChain(&this->dyna.actor, D_80B3C96C);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck_RelocateMeshHeader(&D_06003CD0, &colHeader);
    this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, colHeader);
    Actor_UpdateBgCheckInfo(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 0x4);
    if (this->dyna.actor.floorPoly == 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
    if (gSaveContext.weekEventReg[20] & 0x20) {
        func_80B3C2C4(this, globalCtx);
    }
    func_80B3C260(this);
}

void ObjGhaka_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjGhaka_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;

    this->actionFunc(this, globalCtx);
    thisx->focus.pos.x = thisx->world.pos.x;
    thisx->focus.pos.y = thisx->world.pos.y + 60.0f;
    thisx->focus.pos.z = thisx->world.pos.z;
}

void ObjGhaka_Draw(Actor* thisx, GlobalContext* globalCtx) {
    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06001A20);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06001980);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
