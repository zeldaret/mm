/*
 * File: z_obj_vspinyroll.c
 * Overlay: ovl_Obj_Vspinyroll
 * Description: Vertical Spiked rollers
 */

#include "z_obj_vspinyroll.h"
#include "objects/object_spinyroll/object_spinyroll.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjVspinyroll*)thisx)

void ObjVspinyroll_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjVspinyroll_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A3CEC4(ObjVspinyroll* this);
void func_80A3CEE0(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3CF4C(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3CFAC(ObjVspinyroll* this);
void func_80A3CFE0(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3D024(ObjVspinyroll* this);
void func_80A3D038(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3D0E8(ObjVspinyroll* this);
void func_80A3D0FC(ObjVspinyroll* this, GlobalContext* globalCtx);
void func_80A3D2C0(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Vspinyroll_InitVars = {
    ACTOR_OBJ_VSPINYROLL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SPINYROLL,
    sizeof(ObjVspinyroll),
    (ActorFunc)ObjVspinyroll_Init,
    (ActorFunc)ObjVspinyroll_Destroy,
    (ActorFunc)ObjVspinyroll_Update,
    (ActorFunc)ObjVspinyroll_Draw,
};

f32 D_80A3D450[] = { 1.0f, 2.0f };

f32 D_80A3D458[] = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f };

s16 D_80A3D478[] = { 1, 10, 20, 30, 40, 50, 60, 70 };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x20000000, 0x00, 0x04 },
        { 0x01C37BB6, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 30, 120, 0, { 0, 0, 0 } },
};

f32 D_80A3D4B4[] = { 1.0f, 1.0f, -1.0f, -1.0f };

f32 D_80A3D4C4[] = { 29.0f, -29.0f, 29.0f, -29.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_STOP),
};

s16 D_80A3D4DC[] = { 0xFA0, -0xFA0 };

void func_80A3C4E0(Vec3f* arg0, Vec3f* arg1, s16 arg2) {
    f32 sp1C = Math_SinS(arg2);
    f32 temp_f0 = Math_CosS(arg2);

    arg0->x = (arg1->z * sp1C) + (arg1->x * temp_f0);
    arg0->y = arg1->y;
    arg0->z = (arg1->z * temp_f0) - (arg1->x * sp1C);
}

void func_80A3C560(ObjVspinyroll* this) {
    f32 magnitude;
    Vec3f* sp20 = &this->unk_39C[this->unk_398 ^ 1];

    Math_Vec3f_Diff(sp20, &this->dyna.actor.world.pos, &this->unk_3B4);
    magnitude = Math3D_Vec3fMagnitude(&this->unk_3B4);
    if (magnitude < 0.01f) {
        Math_Vec3f_Diff(sp20, &this->unk_39C[this->unk_398], &this->unk_3B4);
        magnitude = Math3D_Vec3fMagnitude(&this->unk_3B4);
        if (magnitude < 0.01f) {
            Math_Vec3f_Copy(&this->unk_3B4, &gZeroVec3f);
            return;
        }
    }
    Math_Vec3f_Scale(&this->unk_3B4, 1.0f / magnitude);
}

void func_80A3C658(ObjVspinyroll* this) {
    this->dyna.actor.world.rot.y = Math_Vec3f_Yaw(&this->dyna.actor.world.pos, &this->unk_39C[this->unk_398 ^ 1]);
}

void func_80A3C6A0(ObjVspinyroll* this) {
    this->unk_398 = 0;
    func_80A3C658(this);
    func_80A3C560(this);
}

void func_80A3C6CC(ObjVspinyroll* this) {
    this->unk_398 ^= 1;
    func_80A3C658(this);
    func_80A3C560(this);
}

s32 func_80A3C700(ObjVspinyroll* this) {
    s32 pad;
    s32 sp30 = this->unk_398 ^ 1;
    Vec3f sp24;

    Math_StepToF(&this->dyna.actor.speedXZ, this->unk_394, this->unk_394 * 0.2f);

    this->dyna.actor.world.pos.x += this->dyna.actor.speedXZ * this->unk_3B4.x;
    this->dyna.actor.world.pos.y += this->dyna.actor.speedXZ * this->unk_3B4.y;
    this->dyna.actor.world.pos.z += this->dyna.actor.speedXZ * this->unk_3B4.z;

    Math_Vec3f_Diff(&this->unk_39C[sp30], &this->dyna.actor.world.pos, &sp24);
    return Math3D_LengthSquared(&sp24) < (SQ(this->dyna.actor.speedXZ) + 0.05f);
}

void func_80A3C7E8(ObjVspinyroll* this) {
    f32 phi_f2;
    s32 i;
    s32 j;
    f32 tempf;
    s32 index = D_80A3D450[OBJVSPINYROLL_GET_4000(&this->dyna.actor)] * 120.0f * (1.0f / 58.0f);

    index += 2;
    this->unk_38C = index * 4;

    tempf = ((D_80A3D450[OBJVSPINYROLL_GET_4000(&this->dyna.actor)] * 120.0f) - 2.0f) / (index - 1);
    phi_f2 = 1.0f;

    for (i = 0, j = 0; i < this->unk_38C; i++) {
        this->unk_1A8[i].unk_00.x = D_80A3D4C4[j];
        this->unk_1A8[i].unk_00.y = phi_f2;
        this->unk_1A8[i].unk_00.z = D_80A3D4B4[j];

        j++;
        if (j >= 4) {
            j = 0;
            phi_f2 += tempf;
        }
    }
}

#ifdef NON_MATCHING
s32 func_80A3C8D8(ObjVspinyroll* this, GlobalContext* globalCtx, Vec3f* arg2, s32 arg3) {
    s32 pad;
    ObjVspinyrollStruct2* ptr = &this->unk_1A8[0];
    s32 pad2;
    s32 i;
    Vec3f spE4;
    Vec3f spD8;
    Vec3f spCC;
    Vec3f spC0;
    Vec3f spB4;
    Vec3f spA8;
    f32 temp_f20 = FLT_MAX;
    f32 temp_f0;
    s32 sp9C;

    spE4.z = 0.0f;
    sp9C = false;
    this->unk_388 = NULL;

    for (i = 0; i < this->unk_38C; i++, ptr++) {
        spE4.x = ptr->unk_00.x;
        spE4.y = ptr->unk_00.y;
        func_80A3C4E0(&spD8, &spE4, this->dyna.actor.world.rot.y);

        spD8.x += this->dyna.actor.world.pos.x;
        spD8.y += this->dyna.actor.world.pos.y;
        spD8.z += this->dyna.actor.world.pos.z;

        Math_Vec3f_Copy(&spCC, &spD8);

        spCC.x += 30.0f * this->unk_3B4.x;
        spCC.z += 30.0f * this->unk_3B4.z;

        if (BgCheck_EntityLineTest3(&globalCtx->colCtx, &spD8, &spCC, &spC0, &this->unk_1A8[i].collisionPoly, true,
                                    false, false, true, &this->unk_1A8[i].bgId, &this->dyna.actor, 0.0f)) {
            if ((arg3 != 0) && (this->dyna.actor.flags & ACTOR_FLAG_40)) {
                spA8.x = ptr->unk_00.x * 0.2f;
                spA8.y = ptr->unk_00.y;
                spA8.z = 20.0f;

                func_80A3C4E0(&spB4, &spA8, this->dyna.actor.world.rot.y);

                spB4.x += this->dyna.actor.world.pos.x;
                spB4.y += this->dyna.actor.world.pos.y;
                spB4.z += this->dyna.actor.world.pos.z;

                EffectSsHitMark_SpawnFixedScale(globalCtx, 3, &spB4);
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_IT_SHIELD_REFLECT_SW);
            }

            temp_f0 = Math3D_Vec3fDistSq(&spD8, &spC0);
            if (temp_f0 < temp_f20) {
                temp_f20 = temp_f0;
                sp9C = true;
                Math_Vec3f_Diff(&spC0, &spCC, arg2);
                this->unk_388 = ptr;
            }
        }
    }

    return sp9C;
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Vspinyroll/func_80A3C8D8.s")
#endif

s32 func_80A3CB94(ObjVspinyroll* this, GlobalContext* globalCtx, s32 arg2) {
    Vec3f sp1C;

    if (func_80A3C8D8(this, globalCtx, &sp1C, arg2)) {
        this->dyna.actor.world.pos.x += sp1C.x;
        this->dyna.actor.world.pos.z += sp1C.z;
        return true;
    }
    return false;
}

DynaPolyActor* func_80A3CBF0(ObjVspinyroll* this, GlobalContext* globalCtx) {
    if (this->unk_388 != NULL) {
        return DynaPoly_GetActor(&globalCtx->colCtx, this->unk_388->bgId);
    }
    return NULL;
}

s32 func_80A3CC30(ObjVspinyroll* this, GlobalContext* globalCtx) {
    DynaPolyActor* actor = func_80A3CBF0(this, globalCtx);

    if ((actor != NULL) && (Math3D_Vec3fDistSq(&actor->actor.world.pos, &actor->actor.prevPos) > 0.0001f)) {
        return true;
    }
    return false;
}

void func_80A3CC84(f32 arg0) {
    MtxF* matrix = Matrix_GetCurrentState();

    matrix->wy += arg0;
}

void ObjVspinyroll_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjVspinyroll* this = THIS;
    s32 params = OBJVSPINYROLL_GET_4000(&this->dyna.actor);
    f32 sp40 = D_80A3D450[params];
    s32 pad2;
    Path* path;
    Vec3s* points;
    Vec3s* point1;
    Vec3s* point2;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);

    this->dyna.actor.world.rot.x = 0;
    this->dyna.actor.world.rot.z = 0;
    this->dyna.actor.shape.rot.x = 0;
    this->dyna.actor.shape.rot.z = 0;
    this->dyna.actor.scale.y = 0.1f * sp40;
    this->dyna.actor.scale.z = 0.1f;
    this->dyna.actor.uncullZoneScale = 300.0f * sp40;
    this->dyna.actor.scale.x = 0.1f;

    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_spinyroll_Colheader_000F80);

    Collider_InitCylinder(globalCtx, &this->collider);
    Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit);

    if (params == OBJVSPINYROLL_4000_1) {
        this->dyna.actor.draw = func_80A3D2C0;
        this->collider.dim.height = 240;
    }

    if (OBJVSPINYROLL_GET_7F(&this->dyna.actor) == OBJVSPINYROLL_7F_7F) {
        func_80A3CEC4(this);
        return;
    }

    this->dyna.actor.world.rot.y = 0;
    func_80A3C7E8(this);
    this->unk_394 = D_80A3D458[OBJVSPINYROLL_GET_380(thisx)];

    path = &globalCtx->setupPathList[OBJVSPINYROLL_GET_7F(&this->dyna.actor)];
    points = Lib_SegmentedToVirtual(path->points);
    point1 = &points[0];
    point2 = &points[1];

    Math_Vec3s_ToVec3f(&this->unk_39C[0], point1);
    Math_Vec3s_ToVec3f(&this->unk_39C[1], point2);

    Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->unk_39C[0]);

    func_80A3C6A0(this);
    this->dyna.actor.shape.rot.y = this->dyna.actor.world.rot.y;
    func_80A3CFAC(this);
}

void ObjVspinyroll_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjVspinyroll* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A3CEC4(ObjVspinyroll* this) {
    this->dyna.actor.speedXZ = 0.0f;
    this->actionFunc = func_80A3CEE0;
}

void func_80A3CEE0(ObjVspinyroll* this, GlobalContext* globalCtx) {
    this->unk_3C0 += 0x6E;
    if (this->unk_3C0 > 0xFA0) {
        this->unk_3C0 = 0xFA0;
    }
}

void func_80A3CF10(ObjVspinyroll* this) {
    this->actionFunc = func_80A3CF4C;
    this->unk_3C8 = D_80A3D478[OBJVSPINYROLL_GET_1C00(&this->dyna.actor)];
    this->dyna.actor.speedXZ = 0.0f;
}

void func_80A3CF4C(ObjVspinyroll* this, GlobalContext* globalCtx) {
    if (Math_ScaledStepToS(&this->unk_3C0, 0, this->unk_3C4) && (this->unk_3C8 > 0)) {
        this->unk_3C8--;
        if (this->unk_3C8 <= 0) {
            func_80A3CFAC(this);
        }
    }
}

void func_80A3CFAC(ObjVspinyroll* this) {
    this->actionFunc = func_80A3CFE0;
    this->unk_3C2 = D_80A3D4DC[this->unk_398];
    this->dyna.actor.speedXZ = 0.0f;
}

void func_80A3CFE0(ObjVspinyroll* this, GlobalContext* globalCtx) {
    if (Math_ScaledStepToS(&this->unk_3C0, this->unk_3C2, 0x6E)) {
        func_80A3D024(this);
    }
}

void func_80A3D024(ObjVspinyroll* this) {
    this->actionFunc = func_80A3D038;
}

void func_80A3D038(ObjVspinyroll* this, GlobalContext* globalCtx) {
    s32 sp24 = func_80A3C700(this);

    if (func_80A3CB94(this, globalCtx, 1)) {
        this->unk_3C4 = 0x7D0;
        if (func_80A3CBF0(this, globalCtx) != NULL) {
            func_80A3D0E8(this);
        } else {
            func_80A3C6CC(this);
            func_80A3CF10(this);
        }
    } else if (sp24 != 0) {
        func_80A3C6CC(this);
        this->unk_3C4 = 120;
        func_80A3CF10(this);
    }
}

void func_80A3D0E8(ObjVspinyroll* this) {
    this->actionFunc = func_80A3D0FC;
}

void func_80A3D0FC(ObjVspinyroll* this, GlobalContext* globalCtx) {
    s32 sp24 = true;

    Math_ScaledStepToS(&this->unk_3C0, 0, this->unk_3C4);
    if (func_80A3CB94(this, globalCtx, 0) && func_80A3CC30(this, globalCtx)) {
        sp24 = false;
    }

    if (sp24) {
        func_80A3C6CC(this);
        func_80A3CF10(this);
    }
}

void ObjVspinyroll_Update(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    ObjVspinyroll* this = THIS;

    this->actionFunc(this, globalCtx);

    this->unk_3C6 += this->unk_3C0;

    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
    CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void ObjVspinyroll_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjVspinyroll* this = THIS;

    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + 60.0f,
                             this->dyna.actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->dyna.actor.shape.rot.z + 0x4000, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x + this->unk_3C6, MTXMODE_APPLY);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);
    Gfx_DrawDListOpa(globalCtx, object_spinyroll_DL_000460);
}

void func_80A3D2C0(Actor* thisx, GlobalContext* globalCtx) {
    ObjVspinyroll* this = THIS;
    Vec3s sp3C;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    sp3C.x = this->dyna.actor.shape.rot.x + this->unk_3C6;
    sp3C.y = this->dyna.actor.shape.rot.y;
    sp3C.z = this->dyna.actor.shape.rot.z + 0x4000;

    func_8012C28C(globalCtx->state.gfxCtx);
    Matrix_InsertTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y + 60.0f,
                             this->dyna.actor.world.pos.z, MTXMODE_NEW);
    Matrix_RotateY(sp3C.y, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(sp3C.z, MTXMODE_APPLY);
    Matrix_InsertXRotation_s(sp3C.x, MTXMODE_APPLY);
    Matrix_Scale(0.1f, 0.1f, 0.1f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_spinyroll_DL_000460);

    func_80A3CC84(120.0f);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, object_spinyroll_DL_000460);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
