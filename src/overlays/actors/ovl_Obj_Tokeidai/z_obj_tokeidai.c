/*
 * File: z_obj_tokeidai.c
 * Overlay: ovl_Obj_Tokeidai
 * Description: Clock Face
 */

#include "z_obj_tokeidai.h"

#define FLAGS 0x00000030

#define THIS ((ObjTokeidai*)thisx)

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjTokeidai_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AB319C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3240(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB32F0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3370(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB34CC(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3544(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3598(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB363C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB365C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3808(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3880(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB38B0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB39BC(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3A7C(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3B34(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3BD8(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3BE8(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3ED0(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4040(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4080(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB4160(ObjTokeidai* this, GlobalContext* globalCtx);
void func_80AB3BB0(ObjTokeidai* this);
void func_80AB4394(Actor* thisx, GlobalContext* globalCtx);
void func_80AB4664(Actor* thisx, GlobalContext* globalCtx);
void func_80AB4894(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Tokeidai_InitVars = {
    ACTOR_OBJ_TOKEIDAI,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_OBJECT_UNSET_TOKEIDAI,
    sizeof(ObjTokeidai),
    (ActorFunc)ObjTokeidai_Init,
    (ActorFunc)ObjTokeidai_Destroy,
    (ActorFunc)ObjTokeidai_Update,
    (ActorFunc)ObjTokeidai_Draw,
};

// static InitChainEntry sInitChain
static InitChainEntry D_80AB49E0[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 3300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 1100, ICHAIN_STOP),
};

extern UNK_TYPE D_06009A08;
extern UNK_TYPE D_0600B0C0;
extern UNK_TYPE D_0600B208;
extern UNK_TYPE D_0600BA78;
extern UNK_TYPE D_0600CF28;
extern UNK_TYPE D_0600D388;
extern UNK_TYPE D_0600D8E0;
extern UNK_TYPE D_0600D8E8;

s32 func_80AB2790() {
    if (gSaveContext.isNight) {
        return 0x8000;
    }
    return 0;
}

void func_80AB27B4(ObjTokeidai* this) {
    s32 temp;

    temp = (s32)(this->unk_170 * 0.010986328f) % 0x1E;
    this->unk_168 = temp;
    this->unk_14C = temp * 2184.5334f;
    this->unk_14E = 0x3C;
    this->unk_150 = 0;
}

void func_80AB2834(ObjTokeidai* this) {
    s32 temp;

    func_80AB27B4(this);
    temp = (s32)(this->unk_170 * 0.00036621094f);
    this->unk_16C = temp;
    this->unk_152 = temp * 2730.6667f;
    this->unk_154 = 0;
    this->unk_156 = 0;
    this->unk_15C = 0;
    this->unk_158 = func_80AB2790();
}

void func_80AB28C8(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = func_80AB4894;
    this->unk_144 = &D_0600BA78;
    func_80AB27B4(this);
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        func_80AB3BB0(this);
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->actionFunc = func_80AB3240;
        this->actor.world.pos.y += this->actor.scale.y * 1900.0f;
        this->actor.shape.yOffset = 1500.0f;
        gSaveContext.weekEventReg[8] |= 0x40;
    } else {
        this->actionFunc = func_80AB4080;
    }
}

void func_80AB29F8(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->actor.draw = func_80AB4394;
    func_80AB2834(this);
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        func_80AB3BB0(this);
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->actor.world.pos.y += (this->actor.scale.y * 5191.0f) - 50.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 1791.0f;
        this->unk_162 = -0x140;
        this->actor.shape.rot.x = -0x4000;
        this->actor.home.pos = this->actor.world.pos;
        this->actor.home.pos.y -= 1178.0f;
        this->actor.home.pos.z += 13.0f;
        this->actionFunc = func_80AB34CC;
    } else {
        this->actionFunc = func_80AB3ED0;
    }
}

void func_80AB2BBC(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    this->actor.draw = func_80AB4664;
    this->unk_144 = &D_0600B208;
    this->unk_148 = &D_0600B0C0;
    if (gSaveContext.isNight) {
        this->unk_16C = 100;
    } else {
        this->unk_16C = 0;
    }
    if ((globalCtx->sceneNum == SCENE_CLOCKTOWER && gSaveContext.sceneSetupIndex == 2 &&
         globalCtx->csCtx.unk_12 == 0) ||
        (globalCtx->sceneNum == SCENE_00KEIKOKU && gSaveContext.sceneSetupIndex == 2 && globalCtx->csCtx.unk_12 == 0)) {
        this->unk_16C = 0;
        func_80AB3BB0(this);
        if (this->actor.child == NULL) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == 3 || type == 6) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }
        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == 6) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else if ((gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) || gSaveContext.day % 5 >= 4) {
        this->unk_16C = 0;
        this->actor.world.pos.y += this->actor.scale.y * -2160.0f;
        this->actor.world.pos.x += Math_SinS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.world.pos.z += -Math_CosS(this->actor.world.rot.y) * this->actor.scale.z * 5400.0f;
        this->actor.shape.rot.x = -0x4000;
        this->actionFunc = func_80AB3598;
    } else {
        this->actionFunc = func_80AB4160;
    }
}

void ObjTokeidai_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;

    Actor_ProcessInitChain(&this->actor, D_80AB49E0);
    this->actionFunc = func_80AB3BD8;
    this->unk_144 = NULL;
    this->unk_148 = NULL;
    this->unk_160 = 0;
    this->unk_15E = 0;
    this->unk_162 = 0;
    this->unk_170 = gSaveContext.time;
    this->actor.home.rot.x = 0;
    switch (OBJ_TOKEIDAI_TYPE(&this->actor)) {
        case 4:
            Actor_SetScale(&this->actor, 0.15f);
            func_80AB28C8(this, globalCtx);
            break;
        case 0:
            func_80AB28C8(this, globalCtx);
            break;
        case 1:
            this->unk_144 = &D_0600D388;
            break;
        case 8:
            Actor_SetScale(&this->actor, 1.0f);
            this->unk_144 = &D_06009A08;
            this->actionFunc = func_80AB365C;
            break;
        case 5:
            Actor_SetScale(&this->actor, 0.15f);
            func_80AB29F8(this, globalCtx);
            break;
        case 2:
            func_80AB29F8(this, globalCtx);
            break;
        case 9:
            Actor_SetScale(&this->actor, 0.02f);
            this->actor.draw = func_80AB4394;
            func_80AB2834(this);
            this->actionFunc = func_80AB4040;
            break;
        case 10:
            Actor_SetScale(&this->actor, 0.01f);
            this->actor.draw = func_80AB4394;
            func_80AB2834(this);
            this->actionFunc = func_80AB4040;
            break;
        case 6:
            Actor_SetScale(&this->actor, 0.15f);
            func_80AB2BBC(this, globalCtx);
            break;
        case 3:
            func_80AB2BBC(this, globalCtx);
            break;
        case 11:
            this->unk_144 = &D_0600D8E8;
            this->unk_148 = &D_0600D8E0;
            this->actionFunc = func_80AB3BE8;
            break;
    }
}

void ObjTokeidai_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void func_80AB3010(ObjTokeidai* this, s32 arg1) {
    s32 temp;

    temp = (s32)(this->unk_170 * 0.010986328f) % 0x1E;
    if (temp != this->unk_168) {
        if ((this->unk_150 == 8) && (arg1 != 0)) {
            Audio_PlayActorSound2(&this->actor, NA_SE_EV_CLOCK_TOWER_SECOND_HAND);
        }
        if (this->unk_150 >= 9) {
            this->unk_14E += 0x3C;
            this->unk_14C += this->unk_14E;
        } else {
            if ((this->unk_150 & 3) == 0) {
                this->unk_14C += 0x5A;
            }
            if ((this->unk_150 & 3) == 1) {
                this->unk_14C -= 0x5A;
            }
        }
        this->unk_150++;
        if ((temp == 0xF && this->unk_14C < 0) || (temp != 0xF && this->unk_14C > (s16)(temp * 2184.5334f))) {
            this->unk_14C = temp * 2184.5334f;
            this->unk_168 = temp;
            this->unk_14E = 0x5A;
            this->unk_150 = 0;
        }
    }
}

void func_80AB319C(ObjTokeidai* this, GlobalContext* globalCtx) {
    if ((this->actor.bgCheckFlags & 1) != 0 || this->actor.world.pos.y < 0.0f) {
        this->actionFunc = func_80AB3BD8;
        return;
    }
    this->actor.shape.rot.x += 0x50;
    this->actor.shape.rot.z += 0x50;
    Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);
}

void func_80AB3240(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_800EE29C(globalCtx, 0x84) != 0) {
        if (globalCtx->csCtx.npcActions[func_800EE200(globalCtx, 0x84)]->unk0 == 2) {
            this->actionFunc = func_80AB319C;
            this->actor.speedXZ = this->actor.scale.y * 5.0f;
            this->actor.velocity.y = 0.0f;
            this->actor.minVelocityY = this->actor.scale.y * -50.0f;
            this->actor.gravity = this->actor.scale.y * -5.0f;
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB32F0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3370.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB34CC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3544.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3598.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB363C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB365C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB36C4.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3808.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3880.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB38B0.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB39BC.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3A7C.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3B34.s")

void func_80AB3BB0(ObjTokeidai* this) {
    this->actionFunc = func_80AB3B34;
    this->unk_154 = 0;
    this->unk_156 = 0;
    this->unk_15E = 0;
    this->unk_160 = 0;
    this->unk_162 = 0;
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3BD8.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3BE8.s")

s32 func_80AB3C50(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (gSaveContext.inventory.items[0] == 0xFF) {
        return 0;
    }
    if (gSaveContext.day % 5 == 3 && gSaveContext.time < CLOCK_TIME(6, 0)) {
        func_80AB3BB0(this);
        return 1;
    }
    return 0;
}

void func_80AB3CCC(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 temp;
    s32 temp_t1;
    s32 temp_t8;

    temp = (s32)(this->unk_170 * 0.00036621094f);
    if (temp != this->unk_16C) {
        if (this->unk_156 >= 0xD) {
            this->unk_154 += 0xA;
            this->unk_152 += this->unk_154;
        } else {
            if ((this->unk_156 & 3) == 0) {
                this->unk_152 += 0x3C;
            }
            if ((this->unk_156 & 3) == 1) {
                this->unk_152 -= 0x3C;
            }
        }
        this->unk_156++;
        if ((temp == 0xC && this->unk_152 < 0) || (temp != 0xC && this->unk_152 > (s16)(temp * 2730.6667f))) {
            this->unk_152 = temp * 2730.6667f;
            this->unk_16C = temp;
            this->unk_154 = 0;
            this->unk_156 = 0;
        }
    }
    if (this->unk_158 != func_80AB2790()) {
        if (this->unk_16C == 6) {
            this->unk_15C += 0x222;
            this->unk_158 += this->unk_15C;
            if (this->unk_158 >= 0x10001) {
                this->unk_158 = func_80AB2790();
                this->unk_15C = 0;
            }
        }
        if (this->unk_16C == 0x12) {
            this->unk_15C += 0x222;
            this->unk_158 += this->unk_15C;
            if (this->unk_158 >= 0x8001) {
                this->unk_158 = func_80AB2790();
                this->unk_15C = 0;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB3ED0.s")

void func_80AB4040(ObjTokeidai* this, GlobalContext* globalCtx) {
    this->unk_170 = gSaveContext.time;
    func_80AB3010(this, 1);
    func_80AB3CCC(this, globalCtx);
}

void func_80AB4080(ObjTokeidai* this, GlobalContext* globalCtx) {
    if (func_80AB3C50(this, globalCtx)) {
        this->actor.draw = func_80AB4894;
    } else {
        if (globalCtx->csCtx.state != 0) {
            this->actor.home.rot.x = 1;
            this->unk_170 += 3;
            this->actor.draw = func_80AB4894;
        } else {
            if ((globalCtx->actorCtx.unk5 & 2) == 0 && OBJ_TOKEIDAI_TYPE(&this->actor) == 4 &&
                ActorCutscene_GetCurrentIndex() == -1) {
                this->actor.draw = NULL;
            }
            this->unk_170 = gSaveContext.time;
            if (this->actor.home.rot.x != 0) {
                func_80AB27B4(this);
                this->actor.home.rot.x = 0;
            }
        }
        func_80AB3010(this, 0);
    }
}

void func_80AB4160(ObjTokeidai* this, GlobalContext* globalCtx) {
    s32 type;

    if (func_80AB3C50(this, globalCtx) != 0) {
        this->unk_16C = 0;
        if ((this->actor.child == NULL)) {
            type = OBJ_TOKEIDAI_TYPE(&this->actor);
            if (type == 3 || type == 6) {
                this->actor.child =
                    Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_HANABI, this->actor.world.pos.x,
                                this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, 0);
            }
        }
        if (this->actor.child != NULL) {
            if (OBJ_TOKEIDAI_TYPE(&this->actor) == 6) {
                this->actor.child->home.rot.x = 0x384;
            } else {
                this->actor.child->home.rot.x = 0x12C;
            }
        }
    } else {
        this->actor.shape.rot.y += -0x40;
        if (gSaveContext.isNight != 0) {
            if (this->unk_16C < 0x64) {
                this->unk_16C += +4;
            }
        } else if (this->unk_16C > 0) {
            this->unk_16C -= 4;
        }
    }
}

void ObjTokeidai_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjTokeidai* this = THIS;
    this->actionFunc(this, globalCtx);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/ObjTokeidai_Draw.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4394.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4664.s")

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Tokeidai/func_80AB4894.s")
