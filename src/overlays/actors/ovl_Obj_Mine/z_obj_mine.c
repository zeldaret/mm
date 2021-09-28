/*
 * File: z_obj_mine.c
 * Overlay: ovl_Obj_Mine
 * Description: Spike metal Mine
 */

#include "z_obj_mine.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"

#define FLAGS 0x00000000

#define THIS ((ObjMine*)thisx)

void ObjMine_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjMine_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A82F84(ObjMine* this);
void func_80A82F98(ObjMine* this, GlobalContext* globalCtx);
void func_80A82FA8(ObjMine* this);
void func_80A82FC8(ObjMine* this, GlobalContext* globalCtx);
void func_80A83258(ObjMine* this, GlobalContext* globalCtx);
void func_80A832BC(ObjMine* this);
void func_80A832D0(ObjMine* this, GlobalContext* globalCtx);
void func_80A83A74(ObjMine* this);
void func_80A83A88(ObjMine* this, GlobalContext* globalCtx);
void func_80A83B14(ObjMine* this);
void func_80A83B28(ObjMine* this, GlobalContext* globalCtx);
void func_80A83CEC(ObjMine* this);
void func_80A83D00(ObjMine* this, GlobalContext* globalCtx);
void func_80A83E7C(Actor* thisx, GlobalContext* globalCtx);
void func_80A83FBC(Actor* thisx, GlobalContext* globalCtx);
void func_80A84088(Actor* thisx, GlobalContext* globalCtx);
void func_80A84338(Actor* thisx, GlobalContext* globalCtx);

extern Gfx D_06000030[];
extern Gfx D_06002068[];
extern Gfx D_06002188[];

static s32 D_80A849D0[0xC0];

const ActorInit Obj_Mine_InitVars = {
    ACTOR_OBJ_MINE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_NY,
    sizeof(ObjMine),
    (ActorFunc)ObjMine_Init,
    (ActorFunc)ObjMine_Destroy,
    (ActorFunc)ObjMine_Update,
    (ActorFunc)ObjMine_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK2,
            { 0x00000000, 0x00, 0x00 },
            { 0x01CBFFBE, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 30 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_1,
        OC2_TYPE_1,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

static f32 D_80A845A4[] = {
    1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f,
};

static Vec3f D_80A845C4 = { 1.0f, 0.0f, 0.0f };

static Vec3f D_80A845D0[] = {
    { 0.0f, 1.0f, 0.0f },
    { 0.0f, 0.0f, 1.0f },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 1300, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 150, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_STOP),
};

void func_80A811D0(ObjMine* this, s32 arg1) {
    Math_Vec3s_ToVec3f(&this->actor.world.pos, &this->unk_1B4[arg1]);
}

s32 func_80A8120C(Vec3f* arg0, Vec3f* arg1) {
    f32 temp_f0 = Math3D_Vec3fMagnitude(arg0);

    if (temp_f0 < 0.001f) {
        return false;
    }

    arg1->x = arg0->x * (1.0f / temp_f0);
    arg1->y = arg0->y * (1.0f / temp_f0);
    arg1->z = arg0->z * (1.0f / temp_f0);
    return true;
}

s32 func_80A81288(Vec3f* arg0, Vec3f* arg1, f32* arg2, f32* arg3) {
    f32 temp_f0 = Math3D_Vec3fMagnitude(arg0);

    if (temp_f0 < 0.001f) {
        return false;
    }

    arg1->x = arg0->x * (1.0f / temp_f0);
    arg1->y = arg0->y * (1.0f / temp_f0);
    arg1->z = arg0->z * (1.0f / temp_f0);
    *arg2 = temp_f0;
    *arg3 = 1.0f / temp_f0;

    return true;
}

void func_80A8131C(ObjMine* this, GlobalContext* globalCtx) {
    EnBom* bomb = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, this->actor.world.pos.x,
                                      this->actor.world.pos.y - 15.0f, this->actor.world.pos.z, 0, 0, 0, 0);

    if (bomb != NULL) {
        bomb->timer = 0;
    }
}

void func_80A81384(ObjMine* this, GlobalContext* globalCtx) {
    f32 x = this->collider.elements[0].dim.worldSphere.center.x;
    f32 y = this->collider.elements[0].dim.worldSphere.center.y - 15.0f;
    f32 z = this->collider.elements[0].dim.worldSphere.center.z;

    EnBom* bom = (EnBom*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOM, x, y, z, 0, 0, 0, 0);

    if (bom != NULL) {
        bom->timer = 0;
    }
}

s32 func_80A8140C(ObjMine* this) {
    if (this->collider.base.ocFlags2 & OC2_HIT_PLAYER) {
        return true;
    }

    if ((this->collider.base.ocFlags1 & OC2_UNK1)) {
        Actor* mine = this->collider.base.oc;

        if ((mine->id == ACTOR_OBJ_MINE) && (mine->room == this->actor.room)) {
            return true;
        }
    }

    return false;
}

void func_80A8146C(ObjMine* this, s16* arg1, s16* arg2) {
    s32 pad2[3];
    Vec3f sp40;
    s16 sp3E;
    s16 pad;
    Actor* temp_s0 = this->collider.base.ac;

    Math_Vec3s_ToVec3f(&sp40, &this->collider.elements[0].dim.worldSphere.center);
    sp3E = Math_Vec3f_Yaw(&temp_s0->world.pos, &sp40);

    if (this->collider.elements[0].info.acHitInfo->toucher.dmgFlags & 0x13820) {
        *arg1 = temp_s0->shape.rot.y;
        *arg2 = temp_s0->shape.rot.y - sp3E;
    } else {
        Vec3f sp2C;
        Vec3s* hitPos = &this->collider.elements[0].info.bumper.hitPos;

        Math_Vec3s_ToVec3f(&sp2C, hitPos);
        *arg1 = Actor_YawBetweenActors(temp_s0, &this->actor);
        *arg2 = Math_Vec3f_Yaw(&temp_s0->world.pos, &sp2C) - sp3E;
    }
}

#ifdef NON_MATCHING
// stack, 1 var needs to go without changing code gen
void func_80A81544(ObjMine* this, Vec3f* arg1) {
    ColliderJntSphElement* element = &this->collider.elements[0];
    Vec3s* sphere = &element->dim.worldSphere.center;
    Actor* temp_v1 = this->collider.base.ac;

    if ((element->info.acHitInfo->toucher.dmgFlags & 0x13820)) {
        SysMatrix_StatePush();
        Matrix_RotateY(temp_v1->shape.rot.y, MTXMODE_NEW);
        SysMatrix_InsertXRotation_s(temp_v1->shape.rot.x, MTXMODE_APPLY);
        SysMatrix_GetStateTranslationAndScaledZ(1.0f, arg1);
        SysMatrix_StatePop();
    } else {
        Vec3f sp20;

        sp20.x = sphere->x - temp_v1->world.pos.x;
        sp20.y = sphere->y - temp_v1->world.pos.y;
        sp20.z = sphere->z - temp_v1->world.pos.z;
        if (!func_80A8120C(&sp20, arg1)) {
            Math_Vec3f_Copy(arg1, D_80A845D0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81544.s")
#endif

void func_80A81640(ObjMine* this) {
}

void func_80A8164C(Vec3f* arg0) {
    MtxF* matrix = SysMatrix_GetCurrentState();

    matrix->mf[3][0] = arg0->x;
    matrix->mf[3][1] = arg0->y;
    matrix->mf[3][2] = arg0->z;
}

void func_80A81684(ObjMineUnkStruct* arg0) {
    MtxF* matrix = SysMatrix_GetCurrentState();

    matrix->mf[0][0] = arg0->unk_00.x;
    matrix->mf[0][1] = arg0->unk_00.y;
    matrix->mf[0][2] = arg0->unk_00.z;
    matrix->mf[0][3] = 0.0f;

    matrix->mf[1][0] = arg0->unk_0C.x;
    matrix->mf[1][1] = arg0->unk_0C.y;
    matrix->mf[1][2] = arg0->unk_0C.z;
    matrix->mf[1][3] = 0.0f;

    matrix->mf[2][0] = arg0->unk_18.x;
    matrix->mf[2][1] = arg0->unk_18.y;
    matrix->mf[2][2] = arg0->unk_18.z;
    matrix->mf[2][3] = 0.0f;

    matrix->mf[3][0] = 0.0f;
    matrix->mf[3][1] = 0.0f;
    matrix->mf[3][2] = 0.0f;
    matrix->mf[3][3] = 1.0f;
}

s32 func_80A81714(Vec3f* arg0, Vec3f* arg1, f32 arg2) {
    Vec3f sp3C;
    Vec3f sp30;
    Vec3f sp24;
    f32 sp20 = Math3D_Parallel(arg0, arg1);

    if (cos_rad(arg2) <= sp20) {
        Math_Vec3f_Copy(arg0, arg1);
        return true;
    }

    SysMatrix_StatePush();
    Math_Vec3f_Copy(&sp30, arg0);
    Math3D_CrossProduct(arg0, arg1, &sp3C);
    if (func_80A8120C(&sp3C, &sp24)) {
        SysMatrix_InsertRotationAroundUnitVector_s(arg2 * 10430.378f, &sp24, MTXMODE_NEW);
        SysMatrix_MultiplyVector3fByState(&sp30, arg0);
    } else {
        SysMatrix_SetStateXRotation(arg2);
        SysMatrix_MultiplyVector3fByState(&sp30, arg0);
    }

    SysMatrix_StatePop();
    return false;
}

void func_80A81818(ObjMine* this) {
    this->collider.elements->dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider.elements->dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider.elements->dim.worldSphere.center.z = this->actor.world.pos.z;
}

void func_80A81868(ObjMine* this, s32 arg1) {
    s32 i;
    ObjMineUnkStruct* ptr = &this->unk_1B8;
    ObjMineUnkStruct3* unkStruct;
    f32 arg = arg1;
    f32 temp_f12 = this->actor.home.rot.z * 5.0f;

    ptr->unk_00.x = 1.0f;
    ptr->unk_0C.y = 1.0f;
    ptr->unk_18.z = 1.0f;
    ptr->unk_24.y = 1.0f;

    if (arg1 > 0) {
        ptr->unk_40 = -sqrtf(0.001984f / arg);
        ptr->unk_44 = (0.00031746097f * arg) + 0.95f;
    }

    ptr->unk_58 = 0.0002f;

    for (i = 0, unkStruct = &ptr->unk_60[0]; i < arg1; i++, unkStruct++) {
        unkStruct->unk_00 = 0x4000;
    }

    if (temp_f12 < 0.0f) {
        ptr->unk_5C = -1.0f;
    } else if (temp_f12 <= 21.0f) {
        ptr->unk_5C = 0.0f;
    } else {
        ptr->unk_5C = SQ(temp_f12 - 20.0f);
    }
}

void func_80A819A4(ObjMine* this, s32 arg1) {
    SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void func_80A81A00(ObjMine* this) {
    ObjMineUnkStruct* ptr = &this->unk_1B8;
    Vec3f sp28;

    sp28.x = -ptr->unk_30;
    sp28.y = 1.0f;
    sp28.z = -ptr->unk_34;

    func_80A8120C(&sp28, &ptr->unk_0C);
    Math3D_CrossProduct(&D_80A845C4, &ptr->unk_0C, &sp28);
    func_80A8120C(&sp28, &ptr->unk_18);
    Math3D_CrossProduct(&ptr->unk_0C, &ptr->unk_18, &sp28);
    func_80A8120C(&sp28, &ptr->unk_00);
}

void func_80A81AA4(ObjMine* this) {
    s32 params = this->actor.params & 0x3F;
    f32 temp_f0 = -((params * 12.0f) + 10.0f);

    this->actor.world.pos.x = (this->unk_1B8.unk_0C.x * temp_f0) + this->actor.home.pos.x;
    this->actor.world.pos.y = (this->unk_1B8.unk_0C.y * temp_f0) + this->actor.home.pos.y;
    this->actor.world.pos.z = (this->unk_1B8.unk_0C.z * temp_f0) + this->actor.home.pos.z;
}

void func_80A81B14(ObjMine* this) {
    s32 params = this->actor.params & 0x3F;
    f32 temp_f0 = 1.0f / ((params * 12.0f) + 10.0f);
    f32 x = this->actor.world.pos.x - this->actor.home.pos.x;
    f32 z = this->actor.world.pos.z - this->actor.home.pos.z;

    this->unk_1B8.unk_30 = x * temp_f0;
    this->unk_1B8.unk_34 = z * temp_f0;
}

void func_80A81B7C(ObjMine* this, s32 arg1) {
    ObjMineUnkStruct* ptr = &this->unk_1B8;
    ObjMineUnkStruct2* unkStruct;
    s32 i;
    f32 sp58 = this->actor.home.rot.z * 5.0f;
    f32 temp_f24;
    f32 temp_f26;

    ptr->unk_00.x = 0.9f;
    ptr->unk_18.y = 0.003f;

    *(s16*)((u8*)ptr + 0x20) = (u32)Rand_Next() >> 0x13;
    ptr->unk_24.x = -0.0002f;
    ptr->unk_30 = -0.0002f;

    temp_f26 = ptr->unk_18.y * 6.0f;
    temp_f24 = this->actor.home.pos.y;

    unkStruct = (ObjMineUnkStruct2*)&ptr->unk_44;
    for (i = 0; i < arg1; i++, unkStruct++) {
        temp_f24 += 12.0f;
        unkStruct->unk_00.x = 1.0f;
        unkStruct->unk_0C.y = 1.0f;
        unkStruct->unk_18.z = 1.0f;
        unkStruct->unk_24.x = this->actor.home.pos.x;
        unkStruct->unk_24.y = temp_f24;
        unkStruct->unk_24.z = this->actor.home.pos.z;
        unkStruct->unk_30.x = (Rand_ZeroOne() - 0.5f) * temp_f26;
        unkStruct->unk_30.y = (Rand_ZeroOne() - 0.5f) * temp_f26;
        unkStruct->unk_30.z = (Rand_ZeroOne() - 0.5f) * temp_f26;
    }

    ptr->unk_24.y = temp_f24;
    ptr->unk_24.z = temp_f24 * 0.97f;
    temp_f24 = temp_f24 - 18.0f;

    if (ptr->unk_24.z < temp_f24) {
        ptr->unk_24.z = temp_f24;
    }

    if (sp58 < 0.0f) {
        ptr->unk_34 = -1.0f;
    } else if (sp58 <= 37.0f) {
        ptr->unk_34 = 0.0f;
    } else {
        ptr->unk_34 = SQ(sp58 - 36.0f);
    }
}

void func_80A81D70(ObjMine* this, s32 arg1) {
    SysMatrix_InsertTranslation(this->actor.home.pos.x, this->actor.home.pos.y + (arg1 * 12.0f) + 10.0f,
                                this->actor.home.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    Collider_UpdateSpheres(0, &this->collider);
}

void func_80A81DEC(ObjMine* this) {
    s32 pad[2];
    s32 temp_v0 = this->actor.params & 0x3F;
    NextUnkStruct* temp_v1 = &((NextUnkStruct*)&this->unk_1B8)[temp_v0];

    if (temp_v0 == 0) {
        this->actor.world.pos.y = (this->actor.home.pos.y + 12.0f) + 10.0f;
    } else {
        Vec3f sp1C;

        Math_Vec3f_ScaleAndStore(&temp_v1->unk_08, 10.0f, &sp1C);
        Math_Vec3f_Sum(&temp_v1->unk_20, &sp1C, &this->actor.world.pos);
    }
}

void func_80A81E7C(ObjMine* this, GlobalContext* globalCtx) {
    ObjMineUnkStruct* temp_v1 = &this->unk_1B8;
    s32 pad;
    Vec3f sp7C;
    Vec3f sp70;
    Vec3f sp64;
    Vec3f sp58;
    Vec3f sp4C;
    CollisionPoly* sp48;
    u32 sp44;
    f32 sp40;
    f32 sp3C;

    *(s8*)(&temp_v1->unk_40) = 0;
    if (temp_v1->unk_34 > -0.000001f) {
        if (temp_v1->unk_34 <= Math3D_XZDistanceSquared(this->actor.home.pos.x, this->actor.home.pos.z,
                                                        this->actor.world.pos.x, this->actor.world.pos.z)) {
            sp58.x = this->actor.world.pos.x - this->actor.home.pos.x;
            sp58.y = 0.0f;
            sp58.z = this->actor.world.pos.z - this->actor.home.pos.z;
            if (func_80A81288(&sp58, &sp4C, &sp40, &sp3C)) {
                sp70.x = this->actor.world.pos.x + (sp4C.x * 36.0f);
                sp70.y = this->actor.world.pos.y;
                sp70.z = this->actor.world.pos.z + (sp4C.z * 36.0f);
                sp7C.x = this->actor.home.pos.x;
                sp7C.y = this->actor.world.pos.y;
                sp7C.z = this->actor.home.pos.z;
                if (func_800C55C4(&globalCtx->colCtx, &sp7C, &sp70, &sp64, &sp48, 1, 0, 0, 1, &sp44)) {
                    *(s8*)(&temp_v1->unk_40) = 1;
                    temp_v1->unk_38 = sp4C.x * -0.2f;
                    temp_v1->unk_3C = sp4C.z * -0.2f;
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A81FFC.s")

void func_80A828A8(ObjMine* this) {
    s32 pad;
    Vec3f spE0;
    Vec3f spD4;
    Vec3f spC8;
    s32 spC4 = this->actor.params & 0x3F;
    s32 i = 0;
    s32 phi_s5;
    Vec3f* phi_s3 = NULL;
    ObjMineUnkStruct* sp70 = &this->unk_1B8;
    Vec3f spA8;
    Vec3f sp9C;
    Vec3f sp90;
    Vec3f sp84;
    ObjMineUnkStruct2* temp_s0 = (ObjMineUnkStruct2*)&sp70->unk_44;
    f32 sp7C;
    f32 sp78;

    sp84.x = this->actor.home.pos.x;
    sp84.y = this->actor.home.pos.y + 6.0f;
    sp84.z = this->actor.home.pos.z;

    for (; i < spC4; i++, temp_s0++) {
        phi_s5 = false;
        temp_s0->unk_30.x += temp_s0->unk_3C.x;
        temp_s0->unk_30.y += temp_s0->unk_3C.y;
        temp_s0->unk_30.z += temp_s0->unk_3C.z;
        Math_Vec3f_Scale(&temp_s0->unk_30, sp70->unk_00.x);
        Math_Vec3f_Copy(&sp90, &temp_s0->unk_24);
        temp_s0->unk_24.x += temp_s0->unk_30.x;
        temp_s0->unk_24.y += temp_s0->unk_30.y;
        temp_s0->unk_24.z += temp_s0->unk_30.z;

        if ((temp_s0->unk_24.y <= this->actor.home.pos.y) && (temp_s0->unk_30.y < 0.0f)) {
            temp_s0->unk_30.y *= 0.1f;
        }

        Math_Vec3f_Diff(&temp_s0->unk_24, &sp84, &spA8);

        if (func_80A81288(&spA8, &sp9C, &sp7C, &sp78) && (sp7C > 4.0f)) {
            Math_Vec3f_Copy(&spD4, &temp_s0->unk_0C);
            func_80A81714(&spD4, &sp9C, 0.10471976f);

            Math3D_CrossProduct((phi_s3 == NULL) ? &D_80A845C4 : phi_s3, &spD4, &spA8);

            if (func_80A8120C(&spA8, &spE0)) {
                Math3D_CrossProduct(&spD4, &spE0, &spA8);
                if (func_80A8120C(&spA8, &spC8)) {
                    phi_s5 = true;
                }
            }
        }

        if (phi_s5) {
            Math_Vec3f_Copy(&temp_s0->unk_00, &spC8);
            Math_Vec3f_Copy(&temp_s0->unk_0C, &spD4);
            Math_Vec3f_Copy(&temp_s0->unk_18, &spE0);
        } else {
            sp7C = 4.0f;
        }

        if (sp7C >= 6.0f) {
            temp_s0->unk_24.x = (temp_s0->unk_0C.x * 6.0f) + sp84.x;
            temp_s0->unk_24.y = (temp_s0->unk_0C.y * 6.0f) + sp84.y;
            temp_s0->unk_24.z = (temp_s0->unk_0C.z * 6.0f) + sp84.z;
        } else {
            temp_s0->unk_24.x = (temp_s0->unk_0C.x * sp7C) + sp84.x;
            temp_s0->unk_24.y = (temp_s0->unk_0C.y * sp7C) + sp84.y;
            temp_s0->unk_24.z = (temp_s0->unk_0C.z * sp7C) + sp84.z;
        }

        sp84.x = temp_s0->unk_24.x + (temp_s0->unk_0C.x * 6.0f);
        sp84.y = temp_s0->unk_24.y + (temp_s0->unk_0C.y * 6.0f);
        sp84.z = temp_s0->unk_24.z + (temp_s0->unk_0C.z * 6.0f);

        phi_s3 = &temp_s0->unk_00;
    }
}

void func_80A81FFC(ObjMine* this);

void func_80A82C28(ObjMine* this, GlobalContext* globalCtx) {
    func_80A81E7C(this, globalCtx);
    func_80A81FFC(this);
    func_80A828A8(this);
}

void ObjMine_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;
    s32 pad;
    s32 sp44 = this->actor.params & 0xFF;
    Path* path;
    s32 sp3C;
    s32 sp38 = (this->actor.params >> 0xC) & 3;
    s32 sp34;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    this->actor.shape.rot.z = 0;
    this->actor.world.rot.z = 0;
    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);

    if (sp38 == 0) {
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 45.0f);
        this->actor.shape.shadowAlpha = 140;
        this->unk_1A8 = D_80A845A4[(this->actor.params >> 8) & 7];
        if (sp44 == 0xFF) {
            func_80A82F84(this);
        } else {
            path = &globalCtx->setupPathList[sp44];
            this->unk_1B0 = 0;
            this->unk_1AC = path->count - 1;
            this->unk_1B4 = (Vec3s*)Lib_SegmentedToVirtual(path->points);
            func_80A811D0(this, this->unk_1B0);
            func_80A82FA8(this);
        }
        SysMatrix_SetStateRotationAndTranslation(this->actor.world.pos.x, this->actor.world.pos.y,
                                                 this->actor.world.pos.z, &this->actor.shape.rot);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
        Collider_UpdateSpheres(0, &this->collider);
        this->actor.floorHeight =
            func_800C411C(&globalCtx->colCtx, &this->actor.floorPoly, &sp3C, &this->actor, &this->actor.world.pos);
    } else {
        sp34 = this->actor.params & 0x3F;
        this->actor.update = func_80A83E7C;
        this->actor.uncullZoneScale = (sp34 * 21.0f) + 150.0f;
        this->actor.uncullZoneDownward = (sp34 * 21.0f) + 150.0f;
        ActorShape_Init(&this->actor.shape, 0.0f, func_800B3FC0, 45.0f);
        this->actor.shape.shadowAlpha = 0x8C;

        if (sp38 == 1) {
            this->actor.draw = func_80A84088;
            func_80A81868(this, sp34);
            this->actor.world.pos.y = (-10.0f - (sp34 * 12.0f)) + this->actor.home.pos.y;
            func_80A819A4(this, sp34);
            func_800B4AEC(globalCtx, &this->actor, 0.0f);
            if (sp34 == 0) {
                func_80A83A74(this);
            } else {
                func_80A832BC(this);
            }
        } else {
            this->actor.draw = func_80A84338;
            func_80A81B7C(this, sp34);
            this->actor.world.pos.y = (sp34 * 12.0f) + 10.0f + this->actor.home.pos.y;
            func_80A81D70(this, sp34);
            if (sp34 == 0) {
                func_80A83CEC(this);
            } else {
                func_80A83B14(this);
            }
        }
    }
}

void ObjMine_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80A82F84(ObjMine* this) {
    this->actionFunc = func_80A82F98;
}

void func_80A82F98(ObjMine* this, GlobalContext* globalCtx) {
}

void func_80A82FA8(ObjMine* this) {
    this->actor.flags |= 0x10;
    this->actionFunc = func_80A82FC8;
}

#ifdef NON_MATCHING
// stack
void func_80A82FC8(ObjMine* this, GlobalContext* globalCtx) {
    f32 phi_f0;
    Vec3f spA0;
    f32 sp9C;
    s32 pad;
    f32 phi_f12;
    s32 sp90;
    Vec3f sp84;
    Vec3f sp78;
    MtxF sp38;

    Math_Vec3s_ToVec3f(&spA0, &this->unk_1B4[this->unk_1B0 + 1]);
    Math_Vec3f_Diff(&spA0, &this->actor.world.pos, &this->actor.velocity);

    sp9C = Math3D_Vec3fMagnitude(&this->actor.velocity);
    if ((sp9C < (this->unk_1A8 * 8.0f)) && (this->unk_1A8 > 2.0f)) {
        phi_f0 = ((this->unk_1A8 - 2.0f) * 0.1f) + 2.0f;
        phi_f12 = this->unk_1A8 * 0.03f;
    } else {
        phi_f0 = this->unk_1A8;
        phi_f12 = this->unk_1A8 * 0.16f;
    }

    Math_StepToF(&this->actor.speedXZ, phi_f0, phi_f12);

    if ((this->actor.speedXZ + 0.05f) < sp9C) {
        Math_Vec3f_Scale(&this->actor.velocity, this->actor.speedXZ / sp9C);
        this->actor.world.pos.x += this->actor.velocity.x;
        this->actor.world.pos.y += this->actor.velocity.y;
        this->actor.world.pos.z += this->actor.velocity.z;
    } else {
        this->actor.speedXZ *= 0.4f;
        this->unk_1B0++;
        if (this->unk_1B0 >= this->unk_1AC) {
            this->unk_1B0 = 0;
        }
        func_80A811D0(this, this->unk_1B0);
    }

    this->actor.floorHeight =
        func_800C411C(&globalCtx->colCtx, &this->actor.floorPoly, &sp90, &this->actor, &this->actor.world.pos);

    if (this->actor.flags & 0x40) {
        Math3D_CrossProduct(&D_80A845D0[0], &this->actor.velocity, &sp78);
        if (func_80A8120C(&sp78, &sp84)) {
            SysMatrix_InsertRotationAroundUnitVector_f(this->actor.speedXZ * 0.03125f, &sp84, MTXMODE_NEW);
            Matrix_RotateY(this->actor.shape.rot.y, MTXMODE_APPLY);
            SysMatrix_InsertXRotation_s(this->actor.shape.rot.x, MTXMODE_APPLY);
            SysMatrix_InsertZRotation_s(this->actor.shape.rot.z, MTXMODE_APPLY);
            SysMatrix_CopyCurrentState(&sp38);
            func_8018219C(&sp38, &this->actor.shape.rot, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Obj_Mine/func_80A82FC8.s")
#endif

void func_80A83214(ObjMine* this) {
    this->actor.flags |= 0x10;
    this->actor.draw = func_80A83FBC;
    this->actor.shape.shadowDraw = NULL;
    this->actor.scale.x = 0.02f;
    this->actor.scale.y = 0.02f;
    this->actor.scale.z = 0.02f;
    this->actionFunc = func_80A83258;
}

void func_80A83258(ObjMine* this, GlobalContext* globalCtx) {
    this->actor.scale.x *= 1.8f;
    if (this->actor.scale.x > 0.17495999f) {
        Actor_MarkForDeath(&this->actor);
    } else {
        this->actor.scale.y = this->actor.scale.x;
        this->actor.scale.z = this->actor.scale.x;
    }
}

void func_80A832BC(ObjMine* this) {
    this->actionFunc = func_80A832D0;
}

void func_80A832D0(ObjMine* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 spA0 = this->actor.params & 0x3F;
    ObjMineUnkStruct* unkStruct = &this->unk_1B8;

    Math_Vec3f_Copy(&unkStruct->unk_24, &unkStruct->unk_0C);
    if (func_80A8140C(this)) {
        func_80A81384(this, globalCtx);
        func_80A81640(this);
        func_80A83214(this);
    } else {
        ObjMineUnkStruct3* temp;
        s32 i;
        f32 sp90;
        f32 sp8C;
        f32 sp88;
        s16 sp86;
        s16 sp84;
        s32 pad2;
        s32 pad3;

        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            unkStruct->unk_48 = 0.04f;
            func_80A8146C(this, &unkStruct->unk_4C, &sp84);
            sp8C = Math_SinS(sp84) * 150.0f;
            sp88 = sp8C;
            sp8C = -(sp8C / spA0);

            for (i = 0, temp = &unkStruct->unk_60[0]; i < spA0; i++, temp++) {
                temp->unk_02 += (s16)sp88;
                temp->unk_02 = CLAMP(temp->unk_02, -800, 800);
                sp88 -= sp8C;
            }
        }

        if (unkStruct->unk_48 > 0.0001f) {
            sp90 = Math_SinS(unkStruct->unk_4C) * unkStruct->unk_48;
            sp8C = Math_CosS(unkStruct->unk_4C) * unkStruct->unk_48;
            unkStruct->unk_38 += sp90;
            unkStruct->unk_3C += sp8C;
            Math_StepToF(&unkStruct->unk_48, 0.0f, 0.02f);
        }

        if ((u32)Rand_Next() >> 0x1B == 0) {
            unkStruct->unk_50 = Rand_ZeroOne() * unkStruct->unk_58;
            unkStruct->unk_54 = (u32)Rand_Next() >> 0x10;
        }

        sp90 = Math_SinS(unkStruct->unk_54) * unkStruct->unk_50;
        sp8C = Math_CosS(unkStruct->unk_54) * unkStruct->unk_50;
        unkStruct->unk_38 += sp90;
        unkStruct->unk_3C += sp8C;

        unkStruct->unk_38 += unkStruct->unk_30 * unkStruct->unk_40;
        unkStruct->unk_3C += unkStruct->unk_34 * unkStruct->unk_40;

        unkStruct->unk_38 *= unkStruct->unk_44;
        unkStruct->unk_3C *= unkStruct->unk_44;

        unkStruct->unk_30 += unkStruct->unk_38;
        unkStruct->unk_34 += unkStruct->unk_3C;

        unkStruct->unk_30 = CLAMP(unkStruct->unk_30, -5.0f, 5.0f);
        unkStruct->unk_34 = CLAMP(unkStruct->unk_34, -5.0f, 5.0f);

        func_80A81A00(this);
        func_80A81AA4(this);

        if ((unkStruct->unk_5C > -0.000001f) &&
            (unkStruct->unk_5C <= Math3D_XZDistanceSquared(this->actor.world.pos.x, this->actor.world.pos.z,
                                                           this->actor.home.pos.x, this->actor.home.pos.z))) {
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 20.0f, 0.0f, 1);

            if (this->actor.bgCheckFlags & 8) {
                if (this->actor.wallPoly != NULL) {
                    Vec3f sp70;
                    Vec3f sp64;
                    Vec3f sp58;
                    Vec3f sp4C;
                    f32 sp48;
                    f32 sp44;

                    sp4C.x = unkStruct->unk_38;
                    sp4C.y = 0.0f;
                    sp4C.z = unkStruct->unk_3C;
                    if (func_80A81288(&sp4C, &sp70, &sp48, &sp44)) {
                        sp58.x = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.x);
                        sp58.y = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.y);
                        sp58.z = COLPOLY_GET_NORMAL(this->actor.wallPoly->normal.z);
                        func_80179F64(&sp70, &sp58, &sp64);
                        sp48 *= 0.5f;
                        unkStruct->unk_38 = sp64.x * sp48;
                        unkStruct->unk_3C = sp64.z * sp48;
                    } else {
                        unkStruct->unk_38 *= -0.1f;
                        unkStruct->unk_3C *= -0.1f;
                    }
                    func_80A81B14(this);
                    func_80A81A00(this);
                    func_80A81AA4(this);
                }
            }
        }

        for (i = 0, temp = &unkStruct->unk_60[0]; i < spA0; i++, temp++) {
            sp86 = temp->unk_00 - 0x4000;
            sp88 = ((Rand_ZeroOne() * 30.0f) - 15.0f) + (temp->unk_02 + (sp86 * -0.05f));
            sp88 *= 0.995f;
            temp->unk_02 = sp88;
            temp->unk_00 += temp->unk_02;
        }

        func_800B4AEC(globalCtx, &this->actor, 0.0f);
        func_80A81818(this);
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A83A74(ObjMine* this) {
    this->actionFunc = func_80A83A88;
}

void func_80A83A88(ObjMine* this, GlobalContext* globalCtx) {
    if (func_80A8140C(this)) {
        func_80A81384(this, globalCtx);
        func_80A81640(this);
        func_80A83214(this);
    } else {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void func_80A83B14(ObjMine* this) {
    this->actionFunc = func_80A83B28;
}

void func_80A83B28(ObjMine* this, GlobalContext* globalCtx) {
    ObjMineUnkStruct* ptr;
    s16 rand;

    if (func_80A8140C(this)) {
        func_80A81384(this, globalCtx);
        func_80A81640(this);
        func_80A83214(this);
        return;
    }

    ptr = &this->unk_1B8;
    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        func_80A81544(this, (Vec3f*)&ptr->unk_00.y);
        ptr->unk_0C.y = 7.0f;
        Math_Vec3f_Scale((Vec3f*)&ptr->unk_00.y, 7.0f);
    }

    if (ptr->unk_0C.y > 0.0001f) {
        ptr->unk_0C.y = Math_Vec3f_StepTo((Vec3f*)&ptr->unk_00.y, &D_801D15B0, 2.8f);
    }

    ptr->unk_00.x = 0.9f;
    ptr->unk_24.x = -0.0002f;
    ptr->unk_30 = -0.0002f;
    ptr->unk_18.y = 0.003f;
    if (!((u32)Rand_Next() >> 0x1B)) {
        rand = (u32)Rand_Next() >> 0x10;
        ptr->unk_0C.z = Math_SinS(rand) * 1.8f * ptr->unk_18.y;
        ptr->unk_18.x = Math_CosS(rand) * 0.2f * ptr->unk_18.y;
        *(s16*)((u8*)ptr + 0x20) = (u32)Rand_Next() >> 0x13;
    }

    func_80A82C28(this, globalCtx);
    func_80A81DEC(this);
    func_80A81818(this);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80A83CEC(ObjMine* this) {
    this->actionFunc = func_80A83D00;
}

void func_80A83D00(ObjMine* this, GlobalContext* globalCtx) {
    if (func_80A8140C(this)) {
        func_80A81384(this, globalCtx);
        func_80A81640(this);
        func_80A83214(this);
    } else {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
}

void ObjMine_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjMine* this = THIS;

    if ((this->collider.base.ocFlags2 & OC2_HIT_PLAYER) || (this->collider.base.acFlags & AC_HIT)) {
        func_80A8131C(this, globalCtx);
        func_80A83214(this);
    }

    this->actionFunc(this, globalCtx);

    if (this->actor.update != NULL) {
        this->collider.base.ocFlags1 &= ~OC1_HIT;
        this->collider.base.acFlags &= ~AC_HIT;
        this->collider.base.ocFlags2 &= ~OC2_HIT_PLAYER;
        if ((this->actor.flags & 0x40) && (this->actionFunc != func_80A83258)) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80A83E7C(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;

    this->actionFunc(this, globalCtx);
}

void ObjMine_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjMine* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->actionFunc == func_80A82FC8) {
        Collider_UpdateSpheres(0, &this->collider);
    }

    func_800B8050(&this->actor, globalCtx, 1);
    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPSetRenderMode(POLY_OPA_DISP++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(POLY_OPA_DISP++, 0, 0, 0, 255);
    gSPDisplayList(POLY_OPA_DISP++, D_06002068);
    gSPDisplayList(POLY_OPA_DISP++, D_06002188);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A83FBC(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_800B8118(&this->actor, globalCtx, 1);
    func_8012C2DC(globalCtx->state.gfxCtx);

    gDPSetRenderMode(POLY_XLU_DISP++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
    gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 75);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06002068);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A84088(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;
    s32 temp_s5 = this->actor.params & 0x3F;
    ObjMineUnkStruct3* temp;
    ObjMineUnkStruct* ptr = &this->unk_1B8;
    s32 pad;
    s32 i;
    Vec3f sp94;
    Vec3f sp88;
    Gfx* gfx;

    func_800B8050(&this->actor, globalCtx, 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, D_06000030);

    func_80A81684(ptr);
    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
    if (temp_s5 != 0) {
        Math_Vec3f_ScaleAndStore(&ptr->unk_0C, -6.0f, &sp88);
        sp94.x = this->actor.home.pos.x - sp88.x;
        sp94.y = (this->actor.home.pos.y - 6.0f) - sp88.y;
        sp94.z = this->actor.home.pos.z - sp88.z;
        Math_Vec3f_ScaleAndStore(&ptr->unk_0C, -12.0f, &sp88);

        for (i = 0, temp = &ptr->unk_60[0]; i < temp_s5; i++, temp++) {
            Matrix_RotateY(temp->unk_00, MTXMODE_APPLY);
            sp94.x += sp88.x;
            sp94.y += sp88.y;
            sp94.z += sp88.z;
            func_80A8164C(&sp94);

            gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(gfx++, D_06000030);
        }
    }

    SysMatrix_InsertXRotation_s(0x2000, MTXMODE_APPLY);
    func_80A8164C(&this->actor.world.pos);

    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gSPDisplayList(gfx++, D_06002068);
    gSPDisplayList(gfx++, D_06002188);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A84338(Actor* thisx, GlobalContext* globalCtx) {
    ObjMine* this = THIS;
    s32 temp_s7 = this->actor.params & 0x3F;
    s32 i;
    Gfx* gfx;
    ObjMineUnkStruct2* temp;
    s32 pad[2];

    func_800B8050(&this->actor, globalCtx, 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    gfx = POLY_OPA_DISP;

    gSPDisplayList(gfx++, &sSetupDL[6 * 25]);
    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(gfx++, D_06000030);

    for (i = 0, temp = (ObjMineUnkStruct2*)((u8*)this + 0x1FC); i < temp_s7; i++, temp++) {
        func_80A81684((ObjMineUnkStruct*)temp);
        Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, 1);
        if ((i & 1) == 0) {
            Matrix_RotateY(0x4000, 1);
        }
        func_80A8164C(&temp->unk_24);

        gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(gfx++, D_06000030);
    }

    SysMatrix_InsertXRotation_s(0x2000, 1);
    func_80A8164C(&this->actor.world.pos);

    gSPMatrix(gfx++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gDPPipeSync(gfx++);
    gDPSetRenderMode(gfx++, G_RM_PASS, G_RM_AA_ZB_OPA_SURF2);
    gDPSetEnvColor(gfx++, 0, 0, 0, 255);
    gSPDisplayList(gfx++, D_06002068);
    gSPDisplayList(gfx++, D_06002188);

    POLY_OPA_DISP = gfx;

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
