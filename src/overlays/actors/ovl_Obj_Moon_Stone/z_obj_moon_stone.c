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

/*
const ActorInit Obj_Moon_Stone_InitVars = {
    ACTOR_OBJ_MOON_STONE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GI_RESERVE00,
    sizeof(ObjMoonStone),
    (ActorFunc)ObjMoonStone_Init,
    (ActorFunc)ObjMoonStone_Destroy,
    (ActorFunc)ObjMoonStone_Update,
    (ActorFunc)ObjMoonStone_Draw
};
*/

extern AnimatedMaterial D_06001C60;
extern Gfx D_06000D78[];
extern Gfx D_06000C80[];

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Init.asm")
void ObjMoonStone_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMoonStone* this = THIS;

    Actor_SetScale(this, 0.3f);
    this->unk194 = ((this->actor.params & 0xF000) >> 0xC);
    this->actor.targetMode = 0;
    this->actor.shape.yOffset = 25.0f;
    this->actor.focus.pos.y += 10.0f;
    if (this->unk194 == 0) {
        this->actor.colChkInfo.health = 0;
        this->actor.flags |= 9;
        func_80C0662C(this);
    } else {
        if ((gSaveContext.perm.weekEventReg[74] & 0x40) == 0) {
            if ((gSaveContext.perm.weekEventReg[74] & 0x80)) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                            this->actor.world.pos.z, 0, 0, 0, -1);
            }
            this->actor.flags &= ~1;
            func_80C0673C(this);
        } else {
            Actor_MarkForDeath(this);
        }
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Destroy.asm")
void ObjMoonStone_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0662C.asm")
void func_80C0662C(ObjMoonStone* this) {
    this->actionFunc = func_80C06640;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06640.asm")
void func_80C06640(ObjMoonStone* this, GlobalContext* globalCtx) {
    Actor* new_var; // could this bee the moon?
    s16 sp1A;
    s32 phi_v0;

    new_var = globalCtx->actorCtx.actorList[2].first;
    sp1A = this->actor.yawTowardsPlayer - 0x8000;
    sp1A = sp1A - new_var->shape.rot.y;
    if (func_800B84D0(this, globalCtx)) {
        this->actor.colChkInfo.health = 1;
        func_801518B0(globalCtx, 0x5E3U, this);
        func_80C066F8(this);

    } else {
        phi_v0 = ABS_ALT(sp1A);
        if (phi_v0 < 0x1555) {
            func_800B8614(this, globalCtx, 80.0f);
        }
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C066F8.asm")
void func_80C066F8(ObjMoonStone* this) {
    this->actionFunc = func_80C0670C;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0670C.asm")
void func_80C0670C(ObjMoonStone* this, GlobalContext* globalCtx) {
    if (func_800B867C(this, globalCtx) != 0) {
        this->actor.colChkInfo.health = 0;
        func_80C0662C(this);
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0673C.asm")
void func_80C0673C(ObjMoonStone* this) {
    if ((gSaveContext.perm.weekEventReg[74] & 0x80) == 0) {
        this->actor.draw = NULL;
    }
    this->actionFunc = func_80C06768;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06768.asm")
void func_80C06768(ObjMoonStone* this, GlobalContext* globalCtx) {
    if ((gSaveContext.perm.weekEventReg[74] & 0x80)) {
        if (this->actor.draw == 0) {
            this->actor.draw = ObjMoonStone_Draw;
            Actor_Spawn(&globalCtx->actorCtx, globalCtx, 1, this->actor.world.pos.x, this->actor.world.pos.y,
                        this->actor.world.pos.z, 0, 0, 0, -1);
        }
    }
    if (this->actor.draw) {
        if (Actor_HasParent(this, globalCtx)) {
            this->actor.parent = NULL;
            this->actor.draw = NULL;
            func_80C0685C(this);
            return;
        }
        if (this->actor.xzDistToPlayer < 25.0f) {
            func_800B8A1C(this, globalCtx, 0x96, 100.0f, 30.0f);
        }
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C0685C.asm")
void func_80C0685C(ObjMoonStone* this) {
    this->actionFunc = func_80C06870;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/func_80C06870.asm")
void func_80C06870(ObjMoonStone* this, GlobalContext* globalCtx) {
    if (func_80152498(&globalCtx->msgCtx) == 6) {
        if (func_80147624(globalCtx)) {
            gSaveContext.perm.weekEventReg[74] |= 0x40;
            Actor_MarkForDeath(this);
        }
    }
}

#pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Update.asm")
// void ObjMoonStone_Update(Actor* thisx, GlobalContext* globalCtx) {
//     ObjMoonStone* this = THIS;
//     if ((globalCtx->actorCtx.actorList[2].first->unkA6C & 0x10000282) == 0) {
//         this->actionFunc;
//     }
// }

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Moon_Stone_0x80C06510/ObjMoonStone_Draw.asm")
void ObjMoonStone_Draw(Actor* thisx, GlobalContext* globalCtx) {
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    AnimatedMat_Draw(globalCtx, Lib_SegmentedToVirtual(&D_06001C60));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000D78);
    SysMatrix_NormalizeXYZ(&globalCtx->unk187FC);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06000C80);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
