/*
 * File z_obj_moon_stone.c
 * Overlay: ovl_obj_moon_stone
 * Description: Moon's Tear
 */

#include "z_obj_moon_stone.h"

#define FLAGS 0x00100010

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

extern AnimatedMaterial D_06001C60;
extern Gfx D_06000D78[];
extern Gfx D_06000C80[];

void ObjMoonStone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMoonStone* this = THIS;

    Actor_SetScale(&this->actor, 0.3f);
    this->unk194 = (this->actor.params & 0xF000) >> 0xC;
    this->actor.targetMode = 0;
    this->actor.shape.yOffset = 25.0f;
    this->actor.focus.pos.y += 10.0f;
    if (this->unk194 == 0) {
        this->actor.colChkInfo.health = 0;
        this->actor.flags |= 9;
        func_80C0662C(this);
    } else {
        if ((gSaveContext.weekEventReg[74] & 0x40) == 0) {
            if ((gSaveContext.weekEventReg[74] & 0x80)) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, 0, 0, -1);
            }
            this->actor.flags &= ~1;
            func_80C0673C(this);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void ObjMoonStone_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80C0662C(ObjMoonStone* this) {
    this->actionFunc = func_80C06640;
}

void func_80C06640(ObjMoonStone* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;
    s16 sp1A = this->actor.yawTowardsPlayer - 0x8000;

    sp1A -= player->actor.shape.rot.y;
    if (func_800B84D0(&this->actor, globalCtx)) {
        this->actor.colChkInfo.health = 1;
        func_801518B0(globalCtx, 0x5E3U, &this->actor);
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
    if (func_800B867C(&this->actor, globalCtx) != 0) {
        this->actor.colChkInfo.health = 0;
        func_80C0662C(this);
    }
}

void func_80C0673C(ObjMoonStone* this) {
    if ((gSaveContext.weekEventReg[74] & 0x80) == 0) {
        this->actor.draw = NULL;
    }
    this->actionFunc = func_80C06768;
}

void func_80C06768(ObjMoonStone* this, GlobalContext* globalCtx) {
    if ((gSaveContext.weekEventReg[74] & 0x80)) {
        if (this->actor.draw == 0) {
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
            func_800B8A1C(&this->actor, globalCtx, 0x96, 100.0f, 30.0f);
        }
    }
}

void func_80C0685C(ObjMoonStone* this) {
    this->actionFunc = func_80C06870;
}

void func_80C06870(ObjMoonStone* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6 && func_80147624(globalCtx)) {
        gSaveContext.weekEventReg[74] |= 0x40;
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjMoonStone_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjMoonStone* this = THIS;
    Player* player = PLAYER;

    if ((player->stateFlags1 & 0x10000282) == 0) {
        this->actionFunc(this, globalCtx);
    }
}

void ObjMoonStone_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001C60));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000D78);
    SysMatrix_NormalizeXYZ(&globalCtx->mf_187FC);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06000C80);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
