#include "z_obj_raillift.h"

#define FLAGS 0x00000010

#define THIS ((ObjRaillift*)thisx)

void ObjRaillift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjRaillift_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A1A360(Actor* thisx, GlobalContext* globalCtx);
void func_80A1A330(Actor* thisx, GlobalContext* globalCtx);

void func_80A19B98(ObjRaillift* this, GlobalContext* globalCtx);
void func_80A19F18(ObjRaillift* this, GlobalContext* globalCtx);
void func_80A19910(ObjRaillift* this, s32 arg1);
void func_80A19F78(ObjRaillift* this, GlobalContext* globalCtx);
void func_80A19E84(ObjRaillift* this, GlobalContext* globalCtx);
void func_80A19EE0(ObjRaillift* this, GlobalContext* globalCtx);
void func_80A19BA8(ObjRaillift* this, GlobalContext* globalCtx);

extern CollisionHeader D_06004FF8;
extern CollisionHeader D_060048D0;
extern Gfx D_06004BF0[];
extern Gfx D_06000208[];
extern Gfx D_060071B8[];

const ActorInit Obj_Raillift_InitVars = {
    ACTOR_OBJ_RAILLIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjRaillift),
    (ActorFunc)ObjRaillift_Init,
    (ActorFunc)ObjRaillift_Destroy,
    (ActorFunc)ObjRaillift_Update,
    (ActorFunc)ObjRaillift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

static CollisionHeader* D_80A1A3C0[] = { &D_06004FF8, &D_060048D0 };


void func_80A19910(ObjRaillift* this, s32 idx) {
    Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, &this->unk170[idx]);
}

void ObjRaillift_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;
    s32 pad;
    Path* path;
    s32 sp48 = (thisx->params >> 0xF) & 1;
    s32 sp44 = 0;

    Actor_ProcessInitChain(thisx, sInitChain);

    thisx->shape.rot.x = 0;
    thisx->world.rot.x = 0;
    thisx->shape.rot.z = 0;
    thisx->world.rot.z = 0;
    BcCheck3_BgActorInit(&this->dyna, 1);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, D_80A1A3C0[sp48]);
    this->unk160 = thisx->home.rot.z * 0.1f;
    if (this->unk160 < 0.0f) {
        this->unk160 = -this->unk160;
        sp44 = 1;
    }
    if (sp48 == 1) {
        Actor_SpawnWithParent(&globalCtx->actorCtx, thisx, globalCtx, ACTOR_OBJ_ETCETERA, thisx->world.pos.x,
                              thisx->world.pos.y, thisx->world.pos.z, thisx->shape.rot.x, thisx->shape.rot.y,
                              thisx->shape.rot.z, 0);
        if (sp44 != 0) {
            thisx->draw = func_80A1A360;
        } else {
            thisx->draw = func_80A1A330;
        }
    }
    if (this->unk160 < 0.01f) {
        this->actionFunc = func_80A19B98;
    } else {
        path = &globalCtx->setupPathList[thisx->params & 0x7F];
        this->unk168 = (thisx->params >> 7) & 0x1F;
        this->unk164 = path->count - 1;
        this->unk16C = 1;
        this->unk170 = (Vec3s*)Lib_SegmentedToVirtual(path->points);
        func_80A19910(this, this->unk168);
        if (((thisx->params >> 0xD) & 1) && !Flags_GetSwitch(globalCtx, thisx->home.rot.x & 0x7F)) {
            this->actionFunc = func_80A19F18;
        } else {
            this->actionFunc = func_80A19BA8;
        }
    }
}

void ObjRaillift_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80A19B98(ObjRaillift* this, GlobalContext* globalCtx) {
}

void func_80A19BA8(ObjRaillift* this, GlobalContext* globalCtx) {
    int new_var;
    Vec3f sp48;
    f32 speed;
    f32 target;
    f32 step;
    s32 flag;
    Vec3s* temp_v0;
    Vec3s* temp_v1_2;
    s32 pad;

    if (((&this->dyna.actor)->params >> 0xD) & 1) {
        if (Flags_GetSwitch(globalCtx, (&this->dyna.actor)->home.rot.x & 0x7F) == 0) {
            this->actionFunc = func_80A19F18;
            return;
        }

        if ((((&this->dyna.actor)->params >> 0xF) & 1) == 1) {
            func_800B9010(&this->dyna.actor, NA_SE_EV_PLATE_LIFT_LEVEL - SFX_FLAG);
        }
    }

    Math_Vec3s_ToVec3f(&sp48, &(&this->unk170[this->unk168])[this->unk16C]);
    Math_Vec3f_Diff(&sp48, &this->dyna.actor.world.pos, &this->dyna.actor.velocity);
    speed = Math3D_Vec3fMagnitude(&this->dyna.actor.velocity);
    if ((speed < (this->unk160 * 8.0f)) && (this->unk160 > 2.0f)) {
        target = ((this->unk160 - 2.0f) * 0.1f) + 2.0f;
        step = this->unk160 * 0.03f;
    } else {
        target = this->unk160;
        step = this->unk160 * 0.16f;
    }

    Math_StepToF(&this->dyna.actor.speedXZ, target, step);
    if ((this->dyna.actor.speedXZ + 0.05f) < speed) {
        Math_Vec3f_Scale(&this->dyna.actor.velocity, this->dyna.actor.speedXZ / speed);
        this->dyna.actor.world.pos.x += this->dyna.actor.velocity.x;
        this->dyna.actor.world.pos.y += this->dyna.actor.velocity.y;
        this->dyna.actor.world.pos.z += this->dyna.actor.velocity.z;
    } else {
        this->unk168 += this->unk16C;
        if (1) {}
        this->dyna.actor.speedXZ *= 0.4f;
        new_var = (this->dyna.actor.params >> 0xC) & 1;
        flag = 1;
        if (((this->unk168 >= this->unk164) && (this->unk16C > 0)) || ((this->unk168 <= 0) && (this->unk16C < 0))) {
            if (!new_var) {
                this->unk16C = -this->unk16C;
                this->unk186 = 10;
                this->actionFunc = func_80A19EE0;
            } else {
                temp_v1_2 = &this->unk170[this->unk164];
                this->unk168 = (this->unk16C > 0) ? (0) : (this->unk164);
                temp_v0 = &this->unk170[0];
                if (((temp_v0->x != temp_v1_2->x) || (temp_v0->y != temp_v1_2->y)) || (temp_v0->z != (temp_v1_2->z))) {
                    this->actionFunc = func_80A19E84;
                    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
                    flag = 0;
                }
            }
        }

        if (flag != 0) {
            func_80A19910(this, this->unk168);
        }
    }
}

void func_80A19E84(ObjRaillift* this, GlobalContext* globalCtx) {
    if (!func_800CAF70(&this->dyna)) {
        func_80A19910(this, this->unk168);
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
        this->actionFunc = func_80A19BA8;
    }
}

void func_80A19EE0(ObjRaillift* this, GlobalContext* globalCtx) {
    this->unk186--;
    if (this->unk186 <= 0) {
        this->actionFunc = func_80A19BA8;
        this->dyna.actor.speedXZ = 0.0f;
    }
}

void func_80A19F18(ObjRaillift* this, GlobalContext* globalCtx) {
    if (Flags_GetSwitch(globalCtx, (&this->dyna.actor)->home.rot.x & 0x7F)) {
        this->dyna.actor.speedXZ = 0.0f;
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        this->actionFunc = func_80A19F78;
    }
}

void func_80A19F78(ObjRaillift* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk188 = 0x32;
        this->actionFunc = func_80A19BA8;
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void ObjRaillift_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjRaillift* this = THIS;
    f32 target;
    f32 step;

    this->actionFunc(this, globalCtx);
    Actor_SetHeight(&this->dyna.actor, 10.0f);
    if (this->unk188 > 0) {
        this->unk188--;
        if (this->unk188 == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }
    if ((thisx->params >> 0xE) & 1) {
        this->unk178 = this->unk174;
        if (func_800CAF70(&this->dyna)) {
            this->unk174 = 1;
        } else {
            this->unk174 = 0;
        }
        if ((this->unk174 != this->unk178) && (this->unk180 < 1.0f)) {
            this->unk184 = -0x8000;
            this->unk180 = 6.0f;
        }
        this->unk184 += 0xCE4;
        Math_StepToF(&this->unk180, 0.0f, 0.12f);
        if (this->unk174 != 0) {
            step = Math_CosS(fabsf(this->unk17C) * 2048.0f) + 0.02f;
        } else {
            step = Math_SinS(fabsf(this->unk17C) * 2048.0f) + 0.02f;
        }
        if (this->unk174 != 0) {
            target = -8.0f;
        } else {
            target = 0.0f;
        }
        Math_StepToF(&this->unk17C, target, step);
        this->dyna.actor.shape.yOffset = ((Math_SinS(this->unk184) * this->unk180) + this->unk17C) * 10.0f;
        dummy_label_653499:;
    }
    if ((((thisx->params >> 0xF) & 1) == 1) && this->dyna.actor.child != NULL) {
        if (this->dyna.actor.child->update == NULL) {
            this->dyna.actor.child = NULL;
        } else {
            this->dyna.actor.child->world.pos.x = this->dyna.actor.world.pos.x;
            this->dyna.actor.child->world.pos.y =
                this->dyna.actor.world.pos.y + (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y);
            this->dyna.actor.child->world.pos.z = this->dyna.actor.world.pos.z;
        }
    }
}

void ObjRaillift_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08,
               Gfx_TwoTexScrollEnvColor(globalCtx->state.gfxCtx, 0, globalCtx->gameplayFrames, 0, 32, 32, 1, 0, 0,
                                        32, 32, 0, 0, 0, 160));
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06004BF0);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A1A330(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000208);
}

void func_80A1A360(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_060071B8);
}
