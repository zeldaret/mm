/*
 * File: z_obj_grass.c
 * Overlay: ovl_Obj_Grass
 * Description: "Master" instance of grass for unit spawned by Obj_Grass_Unit
 */

#include "z_obj_grass.h"
#include "overlays/actors/ovl_Obj_Grass_Carry/z_obj_grass_carry.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ObjGrass*)thisx)

void ObjGrass_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjGrass_Draw(Actor* thisx, GlobalContext* globalCtx);

ObjGrassStruct1* D_809AADA0[4];
f32 D_809AADB0[4];
ObjGrassStruct1_1* D_809AADC0[20];
f32 D_809AAE10[20];

#include "overlays/ovl_Obj_Grass/ovl_Obj_Grass.c"

const ActorInit Obj_Grass_InitVars = {
    ACTOR_OBJ_GRASS,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_FIELD_KEEP,
    sizeof(ObjGrass),
    (ActorFunc)ObjGrass_Init,
    (ActorFunc)ObjGrass_Destroy,
    (ActorFunc)ObjGrass_Update,
    (ActorFunc)ObjGrass_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_PLAYER | OC1_TYPE_2,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x0580C71C, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 6, 44, 0, { 0, 0, 0 } },
};

Vec3f D_809AAB4C[] = {
    { 0.0f, 0.707099974155f, 0.707099974155f },
    { 0.707099974155f, 0.707099974155f, 0.0f },
    { 0.0f, 0.707099974155f, -0.707099974155f },
    { -0.707099974155f, 0.707099974155f, 0.0f },
};

s16 D_809AAB7C[] = { 0x6C, 0x66, 0x60, 0x54, 0x42, 0x37, 0x2A, 0x26 };

s32 func_809A9110(GlobalContext* globalCtx, Vec3f* arg1) {
    f32 sp2C;
    Vec3f sp20;

    SkinMatrix_Vec3fMtxFMultXYZW(&globalCtx->viewProjectionMtxF, arg1, &sp20, &sp2C);

    if ((globalCtx->unk_187F0.z * -130.13191f) < sp20.z) {
        if (sp2C < 1.0f) {
            sp2C = 1.0f;
        }

        if (((fabsf(sp20.x) - (130.13191f * globalCtx->unk_187F0.x)) < sp2C) &&
            ((fabsf(sp20.y) - (130.13191f * globalCtx->unk_187F0.y)) < sp2C)) {
            return true;
        }
    }
    return false;
}

void func_809A91FC(MtxF* matrix) {
    s32 i;
    MtxF* temp = Matrix_GetCurrentState();
    f32* tmp = &temp->xx;
    f32* tmp2 = &matrix->xx;

    for (i = 0; i < 16; i++) {
        *tmp++ += *tmp2++;
    }
}

void func_809A92D0(ObjGrassStruct1_1* ptr, GlobalContext* globalCtx) {
    if (!(ptr->unk_0E & 0x10)) {
        Item_DropCollectibleRandom(globalCtx, NULL, &ptr->unk_00, ptr->unk_0E * 0x10);
    }
}

void func_809A9314(ObjGrassStruct1_1* ptr, GlobalContext* globalCtx) {
    Vec3f spBC;
    Vec3f spB0;
    s32 i;
    Vec3f* ptr2;

    for (i = 0; i < ARRAY_COUNT(D_809AAB4C); i++) {
        ptr2 = &D_809AAB4C[i];

        spB0.x = ptr->unk_00.x + (ptr2->x * 8.0f);
        spB0.y = (ptr->unk_00.y + (ptr2->y * 8.0f)) + 10.0f;
        spB0.z = ptr->unk_00.z + (ptr2->z * 8.0f);

        spBC.x = (Rand_ZeroOne() - 0.5f) * 8.0f;
        spBC.y = Rand_ZeroOne() * 10.0f;
        spBC.z = (Rand_ZeroOne() - 0.5f) * 8.0f;

        EffectSsKakera_Spawn(globalCtx, &spB0, &spBC, &spB0, -100, 64, 40, 3, 0,
                             D_809AAB7C[(s32)(Rand_ZeroOne() * 111.1f) & 7], 0, 0, 80, -1, 1, gKakeraLeafMiddle);

        spB0.x = ptr->unk_00.x + (ptr2->x * 16.0f);
        spB0.y = (ptr->unk_00.y + (ptr2->y * 16.0f)) + 10.0f;
        spB0.z = ptr->unk_00.z + (ptr2->z * 16.0f);

        spBC.x = (Rand_ZeroOne() - 0.5f) * 6.0f;
        spBC.y = Rand_ZeroOne() * 10.0f;
        spBC.z = (Rand_ZeroOne() - 0.5f) * 6.0f;

        EffectSsKakera_Spawn(globalCtx, &spB0, &spBC, &spB0, -100, 64, 40, 3, 0,
                             D_809AAB7C[(s32)(Rand_ZeroOne() * 111.1f) % 7], 0, 0, 80, -1, 1, gKakeraLeafTip);
    }
}

void ObjGrass_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjGrass* this = THIS;
    s32 i;

    Actor_SetScale(&this->actor, 0.4f);

    for (i = 0; i < ARRAY_COUNT(this->unk_2948); i++) {
        Collider_InitCylinder(globalCtx, &this->unk_2948[i].collider);
        Collider_SetCylinder(globalCtx, &this->unk_2948[i].collider, &this->actor, &sCylinderInit);
    }

    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    this->unk_3288 = (u32)Rand_Next() >> 0x10;
    this->unk_328A = (u32)Rand_Next() >> 0x10;
    this->unk_328C = (u32)Rand_Next() >> 0x10;
    this->unk_328E = (u32)Rand_Next() >> 0x10;
    this->unk_3290 = (u32)Rand_Next() >> 0x10;
}

void ObjGrass_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjGrass* this = THIS;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2948); i++) {
        Collider_DestroyCylinder(globalCtx, &this->unk_2948[i].collider);
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_3298); i++) {
        ObjGrassCarry** ptr = &this->unk_3298[i];

        if (*ptr != NULL) {
            (*ptr)->unk_190 = 0;
            *ptr = NULL;
        }
    }
}

void func_809A9790(ObjGrass* this, GlobalContext* globalCtx) {
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_2948); i++) {
        ObjGrassStruct1_1* ptr = this->unk_2948[i].unk_4C;

        if ((ptr != NULL) && (this->unk_2948[i].collider.base.acFlags & AC_HIT)) {
            func_809A9314(ptr, globalCtx);
            func_809A92D0(ptr, globalCtx);
            ptr->unk_0F |= 4;
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &ptr->unk_00, 20, NA_SE_EV_PLANT_BROKEN);
        }
    }
}

void func_809A983C(ObjGrass* this, GlobalContext* globalCtx) {
    Player* player = GET_PLAYER(globalCtx);
    s32 i;
    s32 j;
    s32 x;
    s32 y;
    f32 temp_f0;
    ObjGrassStruct1* ptr;
    ObjGrassStruct1_1* ptr2;
    ObjGrassStruct2* ptr3;
    s16 yaw;

    for (i = 0; i < ARRAY_COUNT(D_809AADC0); i++) {
        D_809AADC0[i] = NULL;
        D_809AAE10[i] = 422500.0f;
    }

    for (i = 0; i < ARRAY_COUNT(D_809AADA0); i++) {
        D_809AADA0[i] = NULL;
        D_809AADB0[i] = 422500.0f;
    }

    for (i = 0; i < this->unk_2944; i++) {
        ptr = &this->unk_144[i];

        for (j = 0; j < ptr->unk_FC; j++) {
            ptr->unk_0C[j].unk_0F &= (u16)~2;
        }
    }

    for (i = 0; i < this->unk_2944; i++) {
        ptr = &this->unk_144[i];
        temp_f0 = Math3D_Vec3fDistSq(&ptr->unk_00, &player->actor.world.pos);

        for (j = 0; j < ARRAY_COUNT(D_809AADB0); j++) {
            if (temp_f0 < D_809AADB0[j]) {
                break;
            }
        }

        if (j < ARRAY_COUNT(D_809AADB0)) {
            for (x = 2; x >= j; x--) {
                D_809AADB0[x + 1] = D_809AADB0[x];
                D_809AADA0[x + 1] = D_809AADA0[x];
            }

            D_809AADB0[j] = temp_f0;
            D_809AADA0[j] = ptr;
        }
    }

    this->unk_3294 = NULL;

    for (i = 0; i < ARRAY_COUNT(D_809AADA0); i++) {
        ptr = D_809AADA0[i];

        if (ptr != NULL) {
            for (j = 0; j < ptr->unk_FC; j++) {
                if (!(ptr->unk_0C[j].unk_0F & 4)) {
                    temp_f0 = Math3D_Vec3fDistSq(&ptr->unk_0C[j].unk_00, &player->actor.world.pos);

                    for (x = 0; x < ARRAY_COUNT(D_809AAE10); x++) {
                        if (temp_f0 < D_809AAE10[x]) {
                            break;
                        }
                    }

                    if (x < ARRAY_COUNT(D_809AAE10)) {
                        for (y = 18; y >= x; y--) {
                            D_809AAE10[y + 1] = D_809AAE10[y];
                            D_809AADC0[y + 1] = D_809AADC0[y];
                        }

                        D_809AAE10[x] = temp_f0;
                        D_809AADC0[x] = &ptr->unk_0C[j];

                        if (temp_f0 < 2500.0f) {
                            yaw = player->actor.shape.rot.y -
                                  Math_Vec3f_Yaw(&player->actor.world.pos, &ptr->unk_0C[j].unk_00);

                            if (ABS_ALT(yaw) < 0x2000) {
                                this->unk_3294 = &ptr->unk_0C[j];
                            }
                        }
                    }
                }
            }
        }
    }

    for (i = 0; i < ARRAY_COUNT(this->unk_2948); i++) {
        ptr3 = &this->unk_2948[i];

        ptr3->collider.base.acFlags &= (u16)~AC_HIT;
        ptr3->collider.base.ocFlags1 &= (u16)~OC1_HIT;

        ptr2 = D_809AADC0[i];
        if (ptr2 != NULL) {
            ptr3->collider.dim.pos.x = ptr2->unk_00.x;
            ptr3->collider.dim.pos.y = ptr2->unk_00.y;
            ptr3->collider.dim.pos.z = ptr2->unk_00.z;
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &ptr3->collider.base);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &ptr3->collider.base);
            ptr2->unk_0F |= 2;
            ptr3->unk_4C = ptr2;
        } else {
            ptr3->unk_4C = NULL;
        }
    }
}

void func_809A9DB8(ObjGrass* this) {
    s32 i;
    s32 pad;
    f32* ptr;
    f32 temp_f28;
    f32 spA4;
    f32 spA0;
    f32 temp_f22;
    f32 temp_f24;
    f32 sp94;
    f32 sp90;
    f32 temp_f26;
    f32 sp6C[8];
    f32 tempf1;
    f32 tempf2;
    f32 tempf3;
    f32 tempf4;
    f32 tempf5;
    f32 temp_f16;
    f32 temp_f20;

    this->unk_3288 += 70;
    this->unk_328A += 300;
    this->unk_328C += 700;
    this->unk_328E += 1300;
    this->unk_3290 += 8900;

    temp_f24 = Math_SinS(this->unk_3288);
    temp_f28 = Math_SinS(this->unk_328A);
    temp_f26 = Math_SinS(this->unk_328C);
    spA4 = Math_SinS(this->unk_328E) * 1.2f;
    spA0 = Math_SinS(this->unk_3290) * 1.5f;
    temp_f22 = Math_CosS(this->unk_3288);
    temp_f20 = Math_CosS(this->unk_328A);
    sp94 = Math_CosS(this->unk_328C);
    sp90 = Math_CosS(this->unk_328E) * 1.3f;
    temp_f16 = Math_CosS(this->unk_3290) * 1.7f;

    sp6C[0] = (temp_f24 - temp_f20) * temp_f26 * temp_f22 * temp_f24 * 0.0015f;
    sp6C[1] = (temp_f28 - sp94) * spA4 * temp_f20 * temp_f24 * 0.0015f;
    sp6C[2] = (temp_f26 - sp90) * sp94 * temp_f24 * temp_f22 * 0.0015f;
    sp6C[3] = (spA4 - temp_f20) * sp90 * temp_f28 * temp_f22 * 0.0015f;
    sp6C[4] = (temp_f24 - sp94) * temp_f24 * temp_f28 * spA0 * 0.0015f;
    sp6C[5] = (temp_f28 - sp90) * temp_f26 * spA4 * spA0 * 0.0015f;
    sp6C[6] = (temp_f26 - temp_f22) * temp_f22 * temp_f20 * temp_f16 * 0.0015f;
    sp6C[7] = (spA4 - temp_f20) * sp94 * sp90 * temp_f16 * 0.0015f;

    for (i = 0; i < ARRAY_COUNT(this->unk_2F88); i++) {
        ptr = &this->unk_2F88[i].mf[0][0];

        tempf1 = sp6C[(i + 0) & 7];
        tempf2 = sp6C[(i + 1) & 7];
        tempf3 = sp6C[(i + 2) & 7];
        tempf4 = sp6C[(i + 3) & 7];
        tempf5 = sp6C[(i + 4) & 7];

        ptr[0] = sp6C[1] * 0.2f;
        ptr[1] = tempf1;
        ptr[2] = tempf2;
        ptr[3] = 0.0f;

        ptr[4] = tempf3;
        ptr[5] = sp6C[0];
        ptr[6] = tempf3;
        ptr[7] = 0.0f;

        ptr[8] = tempf4;
        ptr[9] = tempf5;
        ptr[10] = sp6C[3] * 0.2f;
        ptr[11] = 0.0f;

        ptr[12] = 0.0f;
        ptr[13] = 0.0f;
        ptr[14] = 0.0f;
        ptr[15] = 0.0f;
    }
}

void ObjGrass_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjGrass* this = THIS;

    func_809A9790(this, globalCtx);
    func_809A983C(this, globalCtx);
    func_809A9DB8(this);
}

void func_809AA278(ObjGrass* this, GlobalContext* globalCtx) {
    ObjGrassStruct1* ptr;
    ObjGrassStruct1_1* ptr2;
    s32 i;
    s32 j;
    f32 distSq;
    f32 temp_f22;

    for (i = 0; i < this->unk_2944; i++) {
        ptr = &this->unk_144[i];

        temp_f22 = Math3D_Vec3fDistSq(&ptr->unk_00, &GET_ACTIVE_CAM(globalCtx)->eye);

        if ((temp_f22 < SQ(1280.0f)) && func_809A9110(globalCtx, &ptr->unk_00)) {
            ptr->unk_FE |= 1;

            for (j = 0; j < ptr->unk_FC; j++) {
                ptr2 = &ptr->unk_0C[j];

                if (ptr2->unk_0F & 4) {
                    ptr2->unk_10 = 255;
                    ptr2->unk_0F &= ~1;
                } else {
                    ptr2->unk_0F |= 1;
                    if (temp_f22 < SQ(980.0f)) {
                        ptr2->unk_10 = 255;
                    } else {
                        distSq = Math3D_Vec3fDistSq(&ptr2->unk_00, &GET_ACTIVE_CAM(globalCtx)->eye);
                        if ((distSq <= SQ(1080.0f)) || ((ptr2->unk_0F & 8) && (distSq < SQ(1180.0f)))) {
                            ptr2->unk_10 = 255;
                        } else if (distSq >= SQ(1180.0f)) {
                            ptr2->unk_10 = 0;
                        } else {
                            ptr2->unk_10 = (1180.0f - sqrtf(distSq)) * 2.55f;
                        }
                    }
                }
            }
        } else {
            ptr->unk_FE &= ~1;
        }
    }
}

void func_809AA54C(Actor* thisx, GlobalContext* globalCtx2) {
    ObjGrass* this = THIS;
    GlobalContext* globalCtx = globalCtx2;
    Lights* temp_s0;
    ObjGrassStruct1* ptr;
    s32 i;
    s32 j;
    Vec3s sp70 = { 0, 0, 0 };
    ObjGrassStruct1_1* ptr2;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 255, 255, 255, 255);
    gSPDisplayList(POLY_OPA_DISP++, gObjGrass_D_809AA9F0);

    for (i = 0; i < this->unk_2944; i++) {
        ptr = &this->unk_144[i];

        if (ptr->unk_FE & 1) {
            temp_s0 = LightContext_NewLights(&globalCtx->lightCtx, globalCtx->state.gfxCtx);
            Lights_BindAll(temp_s0, globalCtx->lightCtx.listHead, &ptr->unk_00, globalCtx);
            Lights_Draw(temp_s0, globalCtx->state.gfxCtx);

            for (j = 0; j < ptr->unk_FC; j++) {
                ptr2 = &ptr->unk_0C[j];

                if ((ptr2->unk_0F & 1) && (ptr2->unk_10 == 255)) {
                    sp70.y = ptr2->unk_0C;
                    Matrix_SetStateRotationAndTranslation(ptr2->unk_00.x, ptr2->unk_00.y, ptr2->unk_00.z, &sp70);
                    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
                    if (ptr2->unk_0F & 2) {
                        func_809A91FC(&this->unk_2F88[j]);
                    }

                    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gSPDisplayList(POLY_OPA_DISP++, gObjGrass_D_809AAAE0);
                }
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_809AA798(Actor* thisx, GlobalContext* globalCtx) {
    ObjGrass* this = THIS;
    ObjGrassStruct1* ptr;
    ObjGrassStruct1_1* ptr2;
    s32 i;
    s32 j;
    Vec3s sp6C = { 0, 0, 0 };

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C2DC(globalCtx->state.gfxCtx);

    gSPDisplayList(POLY_XLU_DISP++, gObjGrass_D_809AAA68);

    for (i = 0; i < this->unk_2944; i++) {
        ptr = &this->unk_144[i];

        if (ptr->unk_FE & 1) {
            for (j = 0; j < ptr->unk_FC; j++) {
                ptr2 = &ptr->unk_0C[j];

                if ((ptr2->unk_0F & 1) && (ptr2->unk_10 > 0) && (ptr2->unk_10 < 255)) {
                    sp6C.y = ptr2->unk_0C;
                    Matrix_SetStateRotationAndTranslation(ptr2->unk_00.x, ptr2->unk_00.y, ptr2->unk_00.z, &sp6C);
                    Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);

                    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                              G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, ptr2->unk_10);
                    gSPDisplayList(POLY_XLU_DISP++, gObjGrass_D_809AAAE0);
                }
            }
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void ObjGrass_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjGrass* this = THIS;

    func_809AA278(this, globalCtx);
    func_809AA54C(thisx, globalCtx);
    func_809AA798(thisx, globalCtx);
}
