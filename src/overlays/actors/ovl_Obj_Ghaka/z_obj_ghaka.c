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


// s32 D_80B3C96C[] = { 0x801F0000, 0x3054001E, 0x00000000, 0x00000000, 0x00000000 };

static InitChainEntry D_80B3C96C[] = {
    ICHAIN_U8(targetMode, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 30, ICHAIN_STOP),
};

extern Gfx D_06001A20[];
extern Gfx D_06001980[];

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C260.asm")
void func_80B3C260(ObjGhaka* this) {
    if ((gSaveContext.perm.weekEventReg[20] & 0x20) != 0) {
        this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + 100.0f;
    }
    this->actionFunc = func_80B3C39C;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C29C.asm")
void func_80B3C29C(ObjGhaka* this) {
    this->actionFunc = func_80B3C4E0;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C2B0.asm")
void func_80B3C2B0(ObjGhaka* this) {
    this->actionFunc = func_80B3C624;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C2C4.asm")
void func_80B3C2C4(ObjGhaka* this, GlobalContext* globalCtx) {
    if ((gSaveContext.perm.weekEventReg[20] & 0x20) == 0) {
        Actor_SpawnWithParentAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0, 0, 0,
                                         this->dyna.actor.cutscene, this->dyna.actor.unk20, 0);
    } else {
        Actor_SpawnWithParentAndCutscene(&globalCtx->actorCtx, globalCtx, ACTOR_BG_GORON_OYU, 0.0f, 25.0f, 261.0f, 0, 0, 0, 1, -1,
                                         this->dyna.actor.unk20, 0);
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C39C.asm")
void func_80B3C39C(ObjGhaka* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    s16 temp_v1;

    temp_v1 = this->dyna.actor.yawTowardsPlayer - this->dyna.actor.shape.rot.y;
    if (func_800B84D0(&this->dyna.actor, globalCtx)) {
        func_80B3C29C(this);
    } else if (this->dyna.actor.xzDistToPlayer < 100.0f || this->dyna.actor.isTargeted) {
        if (temp_v1 <= -0x5556 || temp_v1 >= 0x5556) {
            func_800B863C(&this->dyna.actor, globalCtx);
            if (player->unk14B == 1) {
                this->dyna.actor.textId = 0xCF3;
            } else {
                this->dyna.actor.textId = 0xCF2;
            }
        }
    }
    if (this->dyna.unk148 < 0.0f) {
        if (!(gSaveContext.perm.weekEventReg[20] & 0x20) && player->unk14B == 1) {
            func_80B3C2B0(this);
            return;
        }
    }
    player->unkA70 &= ~0x10;
    this->dyna.unk148 = 0.0f;
}

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C4E0.asm")
void func_80B3C4E0(ObjGhaka* this, GlobalContext* globalCtx) {
    s32 temp_v0;

    temp_v0 = func_80152498(&globalCtx->msgCtx);
    if (temp_v0 == 5) {
        if (func_80147624(globalCtx)) {
            globalCtx->msgCtx.unk11F23 = 0x43;
            globalCtx->msgCtx.unk12024 = 4;
            func_80B3C260(this);
        }

    } else if ((temp_v0 & 0xFFFFFFFFu) == 4) {
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
                    globalCtx->msgCtx.unk11F23 = 0x43;
                    globalCtx->msgCtx.unk12024 = 4;
                    func_80B3C260(this);
        
            }
        }
    }
}


Vec3f D_80B3C960 = { 0.0f, 0.0f, 0.0f };
// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/func_80B3C624.asm")
void func_80B3C624(ObjGhaka* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    s32 stepTemp;

    stepTemp = Math_StepToS(&this->unk_168, 0x64, 1);
    this->dyna.actor.world.pos.z = this->dyna.actor.home.pos.z + this->unk_168;
    if (stepTemp & 0xFF) {
        player->unkA70 &= ~0x10;
        this->dyna.unk148 = 0.0f;
        func_80B3C2C4(this, globalCtx);
        gSaveContext.perm.weekEventReg[20] |= 0x20;
        func_80B3C260(this);
        func_8019F1C0(&D_80B3C960, 0x2835);
    } else {
        func_8019F1C0(&D_80B3C960, 0x200A);
    }
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Init.asm")
void ObjGhaka_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;
    s32 pad;
    CollisionHeader* sp2C;

    sp2C = NULL;
    Actor_ProcessInitChain(&this->dyna.actor, D_80B3C96C);
    Actor_SetScale(&this->dyna.actor, 0.1f);
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck_RelocateMeshHeader(&D_06003CD0, &sp2C);
    this->dyna.bgId = BgCheck_AddActorMesh(globalCtx, &globalCtx->colCtx.dyna, &this->dyna, sp2C);
    func_800B78B8(globalCtx, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4);
    if (this->dyna.actor.floorPoly == 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
    if ((gSaveContext.perm.weekEventReg[20] & 0x20) != 0) {
        func_80B3C2C4(this, globalCtx);
    }
    func_80B3C260(this);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Destroy.asm")
void ObjGhaka_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;
    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Update.asm")
void ObjGhaka_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjGhaka* this = THIS;

    this->actionFunc(this, globalCtx);
    thisx->focus.pos.x = thisx->world.pos.x;
    thisx->focus.pos.y = thisx->world.pos.y + 60.0f;
    thisx->focus.pos.z = thisx->world.pos.z;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Ghaka_0x80B3C260/ObjGhaka_Draw.asm")
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
