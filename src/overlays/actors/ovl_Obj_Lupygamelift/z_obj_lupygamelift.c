/*
 * File: z_obj_lupygamelift.c
 * Overlay: ovl_Obj_Lupygamelift
 * Description: Deku Scrub Playground - Rupee Elevator
 */

#include "z_obj_lupygamelift.h"
#include "objects/object_raillift/object_raillift.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjLupygamelift*)thisx)

void ObjLupygamelift_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjLupygamelift_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AF04BC(ObjLupygamelift* this);
void func_80AF04D8(ObjLupygamelift* this, GlobalContext* globalCtx);
void func_80AF0514(ObjLupygamelift* this);
void func_80AF0530(ObjLupygamelift* this, GlobalContext* globalCtx);

const ActorInit Obj_Lupygamelift_InitVars = {
    ACTOR_OBJ_LUPYGAMELIFT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_RAILLIFT,
    sizeof(ObjLupygamelift),
    (ActorFunc)ObjLupygamelift_Init,
    (ActorFunc)ObjLupygamelift_Destroy,
    (ActorFunc)ObjLupygamelift_Update,
    (ActorFunc)ObjLupygamelift_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 400, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjLupygamelift_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjLupygamelift* this = THIS;
    Path* path;
    s32 phi_v0;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->dyna.actor.scale.y = 0.15f;
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.world.rot.z = 0;
    this->unk_170 = 0;
    Actor_UpdateBgCheckInfo(globalCtx, thisx, 0.0f, 0.0f, 0.0f, 4);
    ActorShape_Init(&thisx->shape, 0.0f, ActorShadow_DrawSquare, 0.0f);
    DynaPolyActor_Init(&this->dyna, 1);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_raillift_Colheader_0048D0);
    this->unk_160 = thisx->home.rot.z * 0.1f;
    if (this->unk_160 < 0.0f) {
        this->unk_160 = -this->unk_160;
    }
    this->dyna.actor.home.rot.x = 0;
    this->dyna.actor.home.rot.y = 0;
    this->dyna.actor.home.rot.z = 0;
    path = &globalCtx->setupPathList[OBJLUPYGAMELIFT_GET_PATH(thisx)];
    this->unk_168 = OBJLUPYGAMELIFT_GET_7(thisx);
    this->unk_164 = path->count;
    if (this->unk_168 >= this->unk_164) {
        this->unk_168 = 0;
    }
    this->unk_16C = Lib_SegmentedToVirtual(path->points);
    Actor_SpawnAsChild(&globalCtx->actorCtx, &this->dyna.actor, globalCtx, 0x183, this->dyna.actor.world.pos.x,
                       this->dyna.actor.world.pos.y, this->dyna.actor.world.pos.z, this->dyna.actor.shape.rot.x,
                       this->dyna.actor.shape.rot.y, this->dyna.actor.shape.rot.z, 0);
    if (OBJLUPYGAMELIFT_GET_C(thisx) != 0) {
        phi_v0 = 1;
    } else {
        phi_v0 = 0;
    }
    Actor_Spawn(&globalCtx->actorCtx, globalCtx, 0x1D2, this->dyna.actor.home.pos.x, this->dyna.actor.home.pos.y,
                this->dyna.actor.home.pos.z, 0, 0, 0, phi_v0);
    func_80AF04BC(this);
}

void ObjLupygamelift_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjLupygamelift* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80AF0394(ObjLupygamelift* this) {
    static f32 D_80AF0750 = 100.0f;
    static f32 D_80AF0754 = 255.0f;
    static f32 D_80AF0758 = 5.0f;
    static f32 D_80AF075C = 10.0f;
    static f32 D_80AF0760 = -240.0f;
    static f32 D_80AF0764 = 30.0f;

    f32 new_var = D_80AF0754 - D_80AF0750;
    f32 new_var2 = D_80AF0764 - D_80AF0760;
    f32 new_var3 = D_80AF075C - D_80AF0758;
    f32 temp_fa0;
    f32 phi_fa1;

    temp_fa0 = this->dyna.actor.world.pos.y - D_80AF0760;
    if (temp_fa0 < 0.0f) {
        phi_fa1 = 0.0f;
    } else if (new_var2 < temp_fa0) {
        phi_fa1 = 1.0f;
    } else {
        phi_fa1 = temp_fa0 / new_var2;
    }
    this->dyna.actor.shape.shadowAlpha = D_80AF0754 - (phi_fa1 * new_var);
    this->dyna.actor.shape.shadowScale = D_80AF075C - (phi_fa1 * new_var3);
}

void func_80AF04BC(ObjLupygamelift* this) {
    this->unk_170 = 5;
    this->actionFunc = func_80AF04D8;
}

void func_80AF04D8(ObjLupygamelift* this, GlobalContext* globalCtx) {
    if (this->unk_170 == 0) {
        func_80AF0514(this);
    } else {
        this->unk_170--;
    }
}

void func_80AF0514(ObjLupygamelift* this) {
    this->actionFunc = func_80AF0530;
    this->dyna.actor.speedXZ = this->unk_160;
}

void func_80AF0530(ObjLupygamelift* this, GlobalContext* globalCtx) {
    f32 step;
    Vec3f target;

    target.x = (this->unk_16C[this->unk_168].x);
    target.y = (this->unk_16C[this->unk_168].y);
    target.z = (this->unk_16C[this->unk_168].z);
    step = Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &target, this->dyna.actor.speedXZ);
    if (step > 30.0f) {
        Math_SmoothStepToF(&this->dyna.actor.speedXZ, this->unk_160, 0.5f, 5.0f, 0.1f);
    } else if (step > 0.0f) {
        Math_SmoothStepToF(&this->dyna.actor.speedXZ, 5.0f, 0.5f, 5.0f, 1.0f);
    } else {
        if (this->unk_168 < (this->unk_164 - 1)) {
            this->unk_168++;
        } else {
            this->unk_168 = 0;
        }
    }
    if (this->dyna.actor.child->update == NULL) {
        this->dyna.actor.child = NULL;
    } else {
        this->dyna.actor.child->world.pos.x = this->dyna.actor.world.pos.x;
        this->dyna.actor.child->world.pos.y = this->dyna.actor.world.pos.y;
        this->dyna.actor.child->world.pos.z = this->dyna.actor.world.pos.z;
    }
    func_80AF0394(this);
}

void ObjLupygamelift_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjLupygamelift* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjLupygamelift_Draw(Actor* thisx, GlobalContext* globalCtx) {
    Gfx_DrawDListOpa(globalCtx, object_raillift_DL_0071B8);
}
