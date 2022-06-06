/*
 * File: z_obj_boat.c
 * Overlay: ovl_Obj_Boat
 * Description: Pirate Boat
 */

#include "z_obj_boat.h"
#include "objects/object_kaizoku_obj/object_kaizoku_obj.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoat*)thisx)

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx);

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0);
void func_80B9B428(ObjBoat* this, GlobalContext* globalCtx);
void func_80B9B124(ObjBoat* this);

const ActorInit Obj_Boat_InitVars = {
    ACTOR_OBJ_BOAT,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_KAIZOKU_OBJ,
    sizeof(ObjBoat),
    (ActorFunc)ObjBoat_Init,
    (ActorFunc)ObjBoat_Destroy,
    (ActorFunc)ObjBoat_Update,
    (ActorFunc)ObjBoat_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0) {
    s16 yaw;
    Vec3s* temp = &this->unk164[(s32)this->unk15C];

    Math_Vec3s_ToVec3f(arg0, &temp[this->unk15D]);
    yaw = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, arg0);

    return ((this->unk15D > 0) ? yaw : (yaw + 0x8000));
}

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    Path* path;
    ObjBoat* this = THIS;
    Vec3f sp24;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 3);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_kaizoku_obj_Colheader_009A88);
    if (this->dyna.actor.params < 0) {
        this->dyna.actor.update = (void (*)(Actor*, GlobalContext*))func_80B9B428;
    } else {
        path = &globalCtx->setupPathList[(this->dyna.actor.params >> 7) & 0x1F];
        this->unk163 = path->count - 1;
        this->unk164 = Lib_SegmentedToVirtual(path->points);
        this->unk15D = 1;
        this->dyna.actor.world.pos.x = this->unk164[this->unk15C].x;
        this->dyna.actor.world.pos.z = this->unk164[this->unk15C].z;
        this->dyna.actor.shape.rot.y = func_80B9AF50(this, &sp24);
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        this->unk15D = -this->unk15D;
    }
}

void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoat* this = THIS;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80B9B124(ObjBoat* this) {
    this->unk160 += 0x3E8;
    this->dyna.actor.world.pos.y = Math_SinS(this->unk160) + this->dyna.actor.home.pos.y;
    this->dyna.actor.shape.rot.x = (s16)(s32)(Math_SinS(this->unk160) * 100.0f);
    this->dyna.actor.shape.rot.z = (s16)(s32)(Math_SinS((s16)(this->unk160 * 2)) * 50.0f);
}

void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjBoat* this = THIS;
    Player* player;
    s32 currentAction;
    f32 sp3C;
    s16 sp3A;
    Vec3f sp2C;

    player = GET_PLAYER(globalCtx);
    currentAction = DynaPolyActor_IsInRidingMovingState(&this->dyna);
    sp3C = 0.0f;
    sp3A = this->dyna.actor.shape.rot.y;
    if ((currentAction) || ((DynaPolyActor_IsInRidingFallingState(&this->dyna)))) {
        if ((this->unk15F == 0) &&
            (((this->dyna.actor.params & 0x4000)) || ((currentAction != 0) && (this->unk15C == this->unk15E)))) {
            this->unk15D = -this->unk15D;
            if (this->unk15D > 0) {
                this->unk15E = this->unk163;
            } else {
                this->unk15E = 0;
            }
            this->unk15F = 0x3C;
        }
    } else if (this->dyna.actor.speedXZ == 0.0f) {
        if (this->unk15F != 0) {
            this->unk15F--;
        }
    }
    if (this->unk15C != this->unk15E) {
        sp3A = func_80B9AF50(this, &sp2C);
        if (Math_Vec3f_DistXZ(&this->dyna.actor.world.pos, &sp2C) < 200.0f) {
            this->unk15C += this->unk15D;
            if (this->unk15C == this->unk15E) {
                if ((this->dyna.actor.params & 0x4000)) {
                    this->unk15C = 0;
                } else if (this->dyna.actor.speedXZ == 0.0f) {
                    this->unk15C = 0;
                    this->unk15D = -1;
                }
            }
        } else {
            sp3C = this->unk15D * ((this->dyna.actor.params & 0x4000) ? 5.0f : 3.0f);
        }
    }
    if (player->csMode != 0x1A) {
        Math_ScaledStepToS(&this->dyna.actor.shape.rot.y, sp3A, (s16)(s32)(fabsf(this->dyna.actor.speedXZ) * 40.0f));
        this->dyna.actor.world.rot.y = this->dyna.actor.shape.rot.y;
        Math_StepToF(&this->dyna.actor.speedXZ, sp3C, 0.05f);
        Actor_MoveWithGravity(&this->dyna.actor);
        if (this->dyna.actor.speedXZ != 0.0f) {
            func_800B9010(&this->dyna.actor, 0x2154U);
        }
    }
    func_80B9B124(this);
}

void func_80B9B428(ObjBoat* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    s32 pad;

    if (Cutscene_CheckActorAction(globalCtx, 0x1FFU) != 0) {
        CsCmdActorAction* var_a3 = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 0x1FFU)];
        if (this->unk15F != var_a3->action) {
            this->dyna.actor.shape.rot.x = var_a3->urot.x;
            if (var_a3->action != 1) {
                Path* var_v0_2 = &globalCtx->setupPathList[(this->dyna.actor.params >> 7) & 0x1F];
                if (var_a3->action == 3) {
                    var_v0_2 = &globalCtx->setupPathList[var_v0_2->unk1];
                }
                this->unk163 = var_v0_2->count;
                this->unk164 = Lib_SegmentedToVirtual(var_v0_2->points);
                Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, this->unk164);
                this->dyna.actor.speedXZ = var_a3->urot.z * 0.005493164f;
                this->unk164++;
                this->unk15C = 1;
            }
            this->unk15F = var_a3->action;
        } else {
            if (var_a3->action != 1) {
                Vec3f sp34;
                f32 temp;
                Math_Vec3s_ToVec3f(&sp34, this->unk164);
                temp = Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &sp34, this->dyna.actor.speedXZ);
                if ((this->unk15C < this->unk163) && (temp < this->dyna.actor.speedXZ)) {
                    this->unk164++;
                    this->unk15C++;
                }
            }
            if (var_a3->action != 3) {
                func_80B9B124(this);
                if (var_a3->action == 2) {
                    func_800B9010(&this->dyna.actor, 0x2154U);
                }
            } else {
                this->dyna.actor.shape.rot.y += 0x7D0;
                this->dyna.actor.shape.rot.x += 0x3E8;
                this->dyna.actor.shape.rot.z += 0x1F4;
            }
        }
    }
}

void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoat* this = THIS;

    Gfx_DrawDListOpa(globalCtx, (Gfx*)&object_kaizoku_obj_DL_007630);
}
