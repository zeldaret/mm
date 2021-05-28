#include "z_obj_bell.h"

#define FLAGS 0x00000030

#define THIS ((ObjBell*)thisx)

void ObjBell_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBell_Draw(Actor* thisx, GlobalContext* globalCtx);

s32 func_80A356D8(ObjBell* this);
s32 func_80A357A8(ObjBell* this, GlobalContext* globalCtx);

/*
const ActorInit Obj_Bell_InitVars = {
    ACTOR_OBJ_BELL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_F52_OBJ,
    sizeof(ObjBell),
    (ActorFunc)ObjBell_Init,
    (ActorFunc)ObjBell_Destroy,
    (ActorFunc)ObjBell_Update,
    (ActorFunc)ObjBell_Draw,
};
*/

// s32 D_80A35E90[] = { 0x09110039, 0x10040000, 0x02000000, 0x20000000, 0x00040000, 0x00000000,
//                      0x00000000, 0x01000100, 0x00000000, 0x03C00000, 0x00460064 };

ColliderSphereInit D_80A35E90 = {
    {
        COLTYPE_METAL,
        AT_ON | AT_TYPE_ENEMY,
        AC_NONE,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK2,
        { 0x20000000, 0x00, 0x04 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 0, { { 0, 960, 0 }, 70 }, 100 },
};

// s32 D_80A35EBC[] = { 0x09000900, 0x10040000, 0x02000000, 0x00000000, 0x00000000, 0xF7CFFFFF,
//                      0x00000000, 0x00010000, 0x00000000, 0x044C0000, 0x004A0064 };

ColliderSphereInit D_80A35EBC = {
    {
        COLTYPE_METAL,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 0, { { 0, 1100, 0 }, 74 }, 100 },
};

CollisionCheckInfoInit2 D_80A35EE8 = {
    0, 0, 0, 0, MASS_IMMOVABLE,
};

// Damage Table
DamageTable D_80A35EF4[] = { 0x010101E1, 0x01010101, 0xF1010101, 0x0101F101, 0x01010101, 0x01010101,
                             0x01010101, 0x010101E1, 0x00000000, 0x00000000, 0x00000000 };

extern CollisionHeader D_06001BA8;
extern Gfx D_06000840[];
extern Gfx D_06000570[];

extern Gfx D_06000698[];
extern Gfx D_060008D0[];
extern Gfx D_06000960[];
extern Gfx D_060007A8[];

// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A35510.asm")
s32 func_80A35510(ObjBell* this, s32 arg1) {
    Vec3f bumperPos;
    Vec3f newVec;
    f32 phi_f0;
    s32 phi_a3;

    if (((arg1 == 0) && (this->unk_21C < 1000.0f)) || ((arg1 == 1) && (this->unk_21C < 4000.0f)) || (arg1 == 2)) {
        phi_a3 = 1;
    } else {
        phi_a3 = 0;
    }
    if (arg1 != 0) {
        if (arg1 != 1) {
            if (arg1 != 2) {
            } else {
            block_19:
                this->unk_21C += 9000.0f;
            }
        } else {
            if (this->unk_21C > 3000.0f) {
                phi_f0 = 750.0f;
            } else {
                phi_f0 = 3000.0f;
            }
            this->unk_21C += phi_f0;
            goto block_19;
        }
    } else {
        if (this->unk_21C > 1000.0f) {
            phi_f0 = 250.0f;
        } else {
            phi_f0 = 1000.0f;
        }
        this->unk_21C += phi_f0;
        goto block_19;
    }
    this->unk_20C = CLAMP(this->unk_20C, 0.0f, 18000.0f);
    if (phi_a3 == 1) {
        Math_Vec3s_ToVec3f(&bumperPos, &this->collider2.info.bumper.hitPos);
        Math_Vec3f_Copy(&newVec, &this->dyna.actor.world);
        this->dyna.actor.world.rot.y = Math_Vec3f_Yaw(&bumperPos, &newVec);
        if (this->unk_20C <= 0x4000 && this->unk_20C >= -0x4000) {
            this->unk_20C -= 0x4000;
        } else {
            this->unk_20C += 0x4000;
        }
    }
    return phi_a3;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A356D8.asm")
s32 func_80A356D8(ObjBell* this) {
    f32 temp_f2;
    s16 new_var;

    this->unk_212 = this->dyna.actor.world.rot.y;
    if (this->unk_20C >= 0x4000 || this->unk_20C < -0x3FFF) {
        this->unk_212 -= 0x8000;
    }
    temp_f2 = Math_SinS(this->unk_20C) * this->unk_21C;
    this->dyna.actor.world.rot.x = this->dyna.actor.home.rot.x;
    new_var = temp_f2;
    this->unk_220 = temp_f2;
    this->dyna.actor.world.rot.x += new_var;
    Math_ApproachF(&this->unk_21C, 0.0f, 0.03f, 70.0f);
    if (this->unk_21C > 0.0f) {
        this->unk_20C -= 0x800;
    }
    return 0;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A357A8.asm")
s32 func_80A357A8(ObjBell* this, GlobalContext* globalCtx) {
    f32 temp_f0;
    s16 temp_v1;

    if ((this->collider1.base.ocFlags1 & 2)) {
        this->collider1.base.ocFlags1 &= 0xFFFD;
        temp_v1 = this->dyna.actor.yawTowardsPlayer - this->unk_212;
        temp_f0 = this->unk_21C / 18000.0f;
        if (ABS_ALT(temp_v1) < 0x3FFC) {
            if (this->unk_214 == 0) {
                if (temp_f0 > 0.18f) {
                    func_800B8D98(globalCtx, this, 8.0f * temp_f0, this->dyna.actor.yawTowardsPlayer, 11.0f * temp_f0);
                    this->unk_214 = 0x1E;
                }
            }
        }
    }
    if ((this->collider2.base.acFlags & 2)) {
        this->collider2.base.acFlags &= 0xFFFD;
        this->unk_20E = 0xA;
        switch (this->dyna.actor.colChkInfo.damageEffect) {
            case 0xF:
                Audio_PlayActorSound2(this, 0x28F3);
                func_80A35510(this, 1);
                break;
            case 0xE:
                Audio_PlayActorSound2(this, 0x28F3);
                func_80A35510(this, 2);
                break;
            default:
                func_80A35510(this, 0);
                break;
        }
    }
    return 0;
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A358FC.asm")
void func_80A358FC(ObjBell* this, GlobalContext* globalCtx) {
    s16 phi_v1;

    this->collider1.dim.worldSphere.radius = (this->collider1.dim.modelSphere.radius * this->collider1.dim.scale);
    this->collider2.dim.worldSphere.radius = (this->collider2.dim.modelSphere.radius * this->collider2.dim.scale);
    if (this->unk_20E == 0) {
        phi_v1 = 0;
    } else {
        this->unk_20E--;
        phi_v1 = this->unk_20E;
    }
    if (phi_v1 == 0) {
        CollisionCheck_SetAC(globalCtx, &globalCtx->colCheckCtx, &this->collider2);
    }
    CollisionCheck_SetOC(globalCtx, &globalCtx->colCheckCtx, &this->collider1);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A359B4.asm")
void func_80A359B4(Actor* thisx, GlobalContext* globalCtx) {
    SysMatrix_InsertTranslation(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, 0);
    Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1U);
    SysMatrix_InsertTranslation(0.0f, 2600.0f, 0.0f, 1);
    Matrix_RotateY(thisx->world.rot.y, 1U);
    SysMatrix_InsertXRotation_s(thisx->world.rot.x, 1);
    Matrix_RotateY(-thisx->world.rot.y, 1U);
    SysMatrix_InsertTranslation(0.0f, -2600.0f, 0.0f, 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000698);
    gSPDisplayList(POLY_OPA_DISP++, D_060008D0);
    gSPDisplayList(POLY_OPA_DISP++, D_06000960);
    gSPDisplayList(POLY_OPA_DISP++, D_060007A8);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A35B18.asm")
void func_80A35B18(Actor* thisx, GlobalContext* globalCtx) {
    SysMatrix_InsertTranslation(thisx->world.pos.x, thisx->world.pos.y, thisx->world.pos.z, NULL);
    Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1);
    Matrix_RotateY(thisx->shape.rot.y, 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C28C(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, D_06000570);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/func_80A35BD4.asm")
void func_80A35BD4(Actor* thisx, GlobalContext* globalCtx) {

    SysMatrix_InsertTranslation(thisx->world.pos.x, thisx->world.pos.y - 4.0f, thisx->world.pos.z, 0);
    Matrix_Scale(thisx->scale.x, thisx->scale.y, thisx->scale.z, 1);

    OPEN_DISPS(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, D_06000840);
    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/ObjBell_Init.asm")
void ObjBell_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjBell* this = THIS;

    BcCheck3_BgActorInit(&this->dyna.actor, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna.actor, &D_06001BA8);
    Actor_SetScale(this, 0.08f);
    Collider_InitAndSetSphere(globalCtx, &this->collider1, this, &D_80A35E90);
    Collider_InitAndSetSphere(globalCtx, &this->collider2, this, &D_80A35EBC);
    CollisionCheck_SetInfo2(&this->dyna.actor.colChkInfo, &D_80A35EF4, &D_80A35EE8);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/ObjBell_Destroy.asm")
void ObjBell_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjBell* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroySphere(globalCtx, &this->collider1);
    Collider_DestroySphere(globalCtx, &this->collider2);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/ObjBell_Update.asm")
void ObjBell_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjBell* this = THIS;

    if (this->unk_214 != 0) {
        this->unk_214--;
    }
    func_80A357A8(this, globalCtx);
    func_80A356D8(this);
    func_80A358FC(this, globalCtx);
}

// matches
// #pragma GLOBAL_ASM("./asm/non_matchings/overlays/ovl_Obj_Bell_0x80A35510/ObjBell_Draw.asm")
void ObjBell_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBell* this = THIS;
    Vec3f sp30;
    Vec3f sp24;

    func_80A35B18(this, globalCtx);
    func_80A35BD4(this, globalCtx);
    func_80A359B4(this, globalCtx);
    Math_Vec3s_ToVec3f(&sp30, &this->collider1.dim);
    SysMatrix_MultiplyVector3fByState(&sp30, &sp24);
    Math_Vec3f_ToVec3s(&this->collider1.dim.worldSphere, &sp24);
    Math_Vec3s_ToVec3f(&sp30, &this->collider2.dim);
    SysMatrix_MultiplyVector3fByState(&sp30, &sp24);
    Math_Vec3f_ToVec3s(&this->collider2.dim.worldSphere, &sp24);
}
