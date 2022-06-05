/*
 * File: z_obj_boat.c
 * Overlay: ovl_Obj_Boat
 * Description: Pirate Boat
 */

#include "z_obj_boat.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjBoat*)thisx)

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx);

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0);               /* extern */
void func_80B9B428(ObjBoat* this, GlobalContext* globalCtx); /* extern */
void func_80B9B124(ObjBoat* arg0);

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

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_80B9B680[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 1000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 1000, ICHAIN_STOP),
};

extern InitChainEntry D_80B9B680[];

extern Gfx D_06007630;
extern CollisionHeader D_06009A88;

s16 func_80B9AF50(ObjBoat* this, Vec3f* arg0) {
    s16 yaw;
    Vec3s* temp = &this->unk164[(s32)this->unk15C];

    Math_Vec3s_ToVec3f(arg0, &temp[this->unk15D]);
    yaw = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, arg0);

    return ((this->unk15D > 0) ? yaw : (yaw + 0x8000));
}

void ObjBoat_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad[2];
    ObjBoat* this = (ObjBoat*)thisx;
    Path* path;
    Vec3f sp24;

    Actor_ProcessInitChain(&this->dyna.actor, D_80B9B680);
    DynaPolyActor_Init(&this->dyna, 3);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &D_06009A88);
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
    ObjBoat* this = (ObjBoat*)thisx;
    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void func_80B9B124(ObjBoat* arg0) {
    arg0->unk160 += 0x3E8;
    arg0->dyna.actor.world.pos.y = Math_SinS(arg0->unk160) + arg0->dyna.actor.home.pos.y;
    arg0->dyna.actor.shape.rot.x = (s16)(s32)(Math_SinS(arg0->unk160) * 100.0f);
    arg0->dyna.actor.shape.rot.z = (s16)(s32)(Math_SinS((s16)(arg0->unk160 * 2)) * 50.0f);
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boat/ObjBoat_Update.s")
/*
void ObjBoat_Update(Actor* thisx, GlobalContext* globalCtx) {
    Actor* sp44;
    s32 sp40;
    f32 sp3C;
    s16 sp3A;
    Vec3f sp2C;
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_t3;
    u8 temp_v0_2;
    s32 phi_v1;
    f32 phi_fv0;
    ObjBoat* this = (ObjBoat*)thisx;

    sp44 = globalCtx->actorCtx.actorLists[2].first;
    temp_v0 = DynaPolyActor_IsInRidingMovingState((DynaPolyActor*)this);
    temp_v1 = temp_v0;
    sp3C = 0.0f;
    sp3A = this->dyna.shape.rot.y;
    phi_v1 = temp_v1;
    if ((temp_v0 != 0) ||
        (sp40 = temp_v0, phi_v1 = sp40, (DynaPolyActor_IsInRidingFallingState((DynaPolyActor*)this) != 0))) {
        if ((this->unk15F == 0) &&
            (((this->dyna.params & 0x4000) != 0) || ((phi_v1 != 0) && (this->unk15E == this->unk15C)))) {
            this->unk15D = -this->unk15D;
            if (this->unk15D > 0) {
                this->unk15E = (u8)this->unk163;
            } else {
                this->unk15E = 0;
            }
            this->unk15F = 0x3C;
        }
    } else if (this->dyna.speedXZ == 0.0f) {
        temp_v0_2 = this->unk15F;
        if (temp_v0_2 != 0) {
            this->unk15F = temp_v0_2 - 1;
        }
    }
    if (this->unk15E != this->unk15C) {
        sp3A = func_80B9AF50(&this->dyna, &sp2C);
        if (Math_Vec3f_DistXZ(&this->dyna.world.pos, &sp2C) < 200.0f) {
            temp_t3 = this->unk15C + this->unk15D;
            this->unk15C = temp_t3;
            if (this->unk15E == (temp_t3 & 0xFF)) {
                if ((this->dyna.params & 0x4000) != 0) {
                    this->unk15C = 0;
                } else if (this->dyna.speedXZ == 0.0f) {
                    this->unk15C = 0;
                    this->unk15D = -1;
                }
            }
        } else {
            if ((this->dyna.params & 0x4000) != 0) {
                phi_fv0 = 5.0f;
            } else {
                phi_fv0 = 3.0f;
            }
            sp3C = phi_fv0 * (f32)this->unk15D;
        }
    }
    if (sp44->unk394 != 0x1A) {
        Math_ScaledStepToS(&this->dyna.shape.rot.y, sp3A, (s16)(s32)(fabsf(this->actor.speedXZ) * 40.0f));
        this->dyna.world.rot.y = this->dyna.shape.rot.y;
        Math_StepToF(&this->dyna.speedXZ, sp3C, 0.05f);
        Actor_MoveWithGravity(&this->dyna);
        if (this->dyna.speedXZ != 0.0f) {
            func_800B9010(&this->dyna, 0x2154U);
        }
    }
    func_80B9B124(this);
}
*/
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boat/func_80B9B428.s")
/*
void func_80B9B428(ObjBoat *this, GlobalContext *globalCtx) {
    CsCmdActorAction *sp44;
    Vec3f sp34;
    CsCmdActorAction *temp_a3;
    Path *temp_a0;
    Path *temp_v0_2;
    Vec3s *temp_v0_3;
    f32 temp_ft1;
    u16 temp_t7;
    u16 temp_v0;
    u16 temp_v1;
    u8 temp_v0_4;
    Path *phi_v0;
    f32 phi_ft1;
    u8 phi_v0_2;
    u16 phi_v1;
    CsCmdActorAction *phi_a3;

    if (Cutscene_CheckActorAction(globalCtx, 0x1FFU) != 0) {
        temp_a3 = globalCtx->csCtx.actorActions[Cutscene_GetActorActionIndex(globalCtx, 0x1FFU)];

        phi_v1 = temp_a3->action;
        phi_a3 = temp_a3;
        if (temp_v1 != this->unk15F) {
            this->dyna.actor.shape.rot.x = (s16) (u16) temp_a3->rot.x;
            temp_v0 = temp_a3->action;
            phi_v0_2 = (u8) temp_v0;
            if (temp_v0 != 1) {
                temp_a0 = globalCtx->setupPathList;
                temp_v0_2 = &temp_a0[((s16) this->dyna.actor.params >> 7) & 0x1F];
                phi_v0 = temp_v0_2;
                if (temp_v0 == 3) {
                    phi_v0 = &temp_a0[temp_v0_2->unk1];
                }
                this->unk163 = (s8) phi_v0->count;
                sp44 = temp_a3;
                temp_v0_3 = Lib_SegmentedToVirtual(phi_v0->points);
                this->unk164 = temp_v0_3;
                Math_Vec3s_ToVec3f(&this->dyna.actor.world.pos, temp_v0_3);
                temp_t7 = (u16) temp_a3->rot.z;
                temp_ft1 = (f32) temp_t7;
                phi_ft1 = temp_ft1;
                if ((s32) temp_t7 < 0) {
                    phi_ft1 = temp_ft1 + 4294967296.0f;
                }
                this->unk164 = 6; //+=
                this->unk15C = 1; //+=
                this->dyna.actor.speedXZ = phi_ft1 * 0.005493164f;
                phi_v0_2 = (u8) temp_a3->action;
            }
            this->unk15F = phi_v0_2;
            return;
        }
        if (temp_v1 != 1) {
            sp44 = temp_a3;
            Math_Vec3s_ToVec3f(&sp34, (Vec3s *) this->unk164);
            temp_v0_4 = this->unk15C;
            phi_a3 = sp44;
            if (((s32) temp_v0_4 < (s32) (u8) this->unk163) && (Math_Vec3f_StepTo(&this->dyna.actor.world.pos, &sp34,
this->dyna.actor.speedXZ) < this->dyna.actor.speedXZ)) { this->unk15C = temp_v0_4 + 1; this->unk164 = 6;
            }
            phi_v1 = sp44->action;
        }
        if (phi_v1 != 3) {
            sp44 = phi_a3;
            func_80B9B124(this);
            if (phi_a3->action == 2) {
                func_800B9010(&this->dyna.actor, 0x2154U);
            }
        } else {
            this->dyna.actor.shape.rot.y += 0x7D0;
            this->dyna.actor.shape.rot.x += 0x3E8;
            this->dyna.actor.shape.rot.z += 0x1F4;
        }
    }
}
*/
//#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Boat/ObjBoat_Draw.s")

void ObjBoat_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBoat* this = (ObjBoat*)thisx;
    Gfx_DrawDListOpa(globalCtx, (Gfx*)&D_06007630);
}
