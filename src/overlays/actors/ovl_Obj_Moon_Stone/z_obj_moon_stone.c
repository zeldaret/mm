/*
 * File: z_obj_moon_stone.c
 * Overlay: ovl_Obj_Moon_Stone
 * Description: Moon's Tear
 */

#include "z_obj_moon_stone.h"
#include "objects/object_gi_reserve00/object_gi_reserve00.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_100000)

#define THIS ((ObjMoonStone*)thisx)

void ObjMoonStone_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMoonStone_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80C0662C(ObjMoonStone* this);
void func_80C06640(ObjMoonStone* this, GlobalContext* globalCtx);
void func_80C066F8(ObjMoonStone* this);
void func_80C0670C(ObjMoonStone* this, GlobalContext* globalCtx);
void func_80C0673C(ObjMoonStone* this);
void func_80C06768(ObjMoonStone* this, GlobalContext* globalCtx);
void func_80C0685C(ObjMoonStone* this);
void func_80C06870(ObjMoonStone* this, GlobalContext* globalCtx);

const ActorInit Obj_Moon_Stone_InitVars = {
    ACTOR_OBJ_MOON_STONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GI_RESERVE00,
    sizeof(ObjMoonStone),
    (ActorFunc)ObjMoonStone_Init,
    (ActorFunc)ObjMoonStone_Destroy,
    (ActorFunc)ObjMoonStone_Update,
    (ActorFunc)ObjMoonStone_Draw,
};

void ObjMoonStone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMoonStone* this = THIS;

    Actor_SetScale(&this->actor, 0.3f);
    this->unk194 = (this->actor.params & 0xF000) >> 0xC;
    this->actor.targetMode = 0;
    this->actor.shape.yOffset = 25.0f;
    this->actor.focus.pos.y += 10.0f;
    if (this->unk194 == 0) {
        this->actor.colChkInfo.health = 0;
        this->actor.flags |= (ACTOR_FLAG_1 | ACTOR_FLAG_8);
        func_80C0662C(this);
    } else if (!(gSaveContext.save.weekEventReg[74] & 0x40)) {
        if ((gSaveContext.save.weekEventReg[74] & 0x80)) {
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, -1);
        }
        this->actor.flags &= ~ACTOR_FLAG_1;
        func_80C0673C(this);
    } else {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMoonStone_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C0662C(ObjMoonStone* this) {
    this->actionFunc = func_80C06640;
}

void func_80C06640(ObjMoonStone* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s16 sp1A = this->actor.yawTowardsPlayer - 0x8000;

    sp1A -= player->actor.shape.rot.y;
    if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
        this->actor.colChkInfo.health = 1;
        Message_StartTextbox(globalCtx, 0x5E3U, &this->actor);
        func_80C066F8(this);
    } else {
        s32 phi_v0 = ABS_ALT(sp1A);
        if (phi_v0 < 0x1555) {
            func_800B8614(&this->actor, globalCtx, 80.0f);
        }
    }
}

void func_80C066F8(ObjMoonStone* this) {
    this->actionFunc = func_80C0670C;
}

void func_80C0670C(ObjMoonStone* this, GlobalContext* globalCtx) {
    if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
        this->actor.colChkInfo.health = 0;
        func_80C0662C(this);
    }
}

void func_80C0673C(ObjMoonStone* this) {
    if (!(gSaveContext.save.weekEventReg[74] & 0x80)) {
        this->actor.draw = NULL;
    }
    this->actionFunc = func_80C06768;
}

void func_80C06768(ObjMoonStone* this, GlobalContext* globalCtx) {
    if ((gSaveContext.save.weekEventReg[74] & 0x80)) {
        if (this->actor.draw == NULL) {
            this->actor.draw = ObjMoonStone_Draw;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, -1);
        }
    }
    if (this->actor.draw) {
        if (Actor_HasParent(&this->actor, globalCtx)) {
            this->actor.parent = NULL;
            this->actor.draw = NULL;
            func_80C0685C(this);
        } else if (this->actor.xzDistToPlayer < 25.0f) {
            Actor_PickUp(&this->actor, globalCtx, GI_MOON_TEAR, 100.0f, 30.0f);
        }
    }
}

void func_80C0685C(ObjMoonStone* this) {
    this->actionFunc = func_80C06870;
}

void func_80C06870(ObjMoonStone* this, GlobalContext* globalCtx) {
    if (Message_GetState(&globalCtx->msgCtx) == 6 && Message_ShouldAdvance(globalCtx)) {
        gSaveContext.save.weekEventReg[74] |= 0x40;
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMoonStone_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMoonStone* this = THIS;
    Player* player = GET_PLAYER(globalCtx);

    if (!(player->stateFlags1 & 0x10000282)) {
        this->actionFunc(this, globalCtx);
    }
}

void ObjMoonStone_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(object_gi_reserve00_Matanimheader_001C60));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_gi_reserve00_DL_000D78);
    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_gi_reserve00_DL_000C80);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
