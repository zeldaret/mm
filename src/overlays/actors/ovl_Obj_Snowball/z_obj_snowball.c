/*
 * File: z_obj_snowball.c
 * Overlay: ovl_Obj_Snowball
 * Description: Large Snowball
 */

#include "z_obj_snowball.h"
#include "objects/object_goroiwa/object_goroiwa.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS 0x00000000

#define THIS ((ObjSnowball*)thisx)

void ObjSnowball_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjSnowball_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80B02CD0(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B02D58(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B02DB0(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B02E54(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04338(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04350(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04540(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B0457C(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04608(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04648(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B046E4(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B047C0(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04B48(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04B60(ObjSnowball* this, GlobalContext* globalCtx);
void func_80B04D34(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Snowball_InitVars = {
    ACTOR_OBJ_SNOWBALL,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_GOROIWA,
    sizeof(ObjSnowball),
    (ActorFunc)ObjSnowball_Init,
    (ActorFunc)ObjSnowball_Destroy,
    (ActorFunc)ObjSnowball_Update,
    (ActorFunc)ObjSnowball_Draw,
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000000, 0x00, 0x00 },
            { 0x81837FBE, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_ON,
        },
        { 0, { { 0, 0, 0 }, 73 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

typedef struct {
    /* 0x00 */ s16 unk_00;
    /* 0x02 */ s16 unk_02;
    /* 0x04 */ ObjSnowballActionFunc unk_04;
} ObjSnowballStruct2;

static ObjSnowballStruct2 D_80B04F84[] = {
    { -1, 0, func_80B02D58 },
    { ACTOR_EN_JG, 0, func_80B02DB0 },
    { ACTOR_EN_WF, 1, func_80B02E54 },
    { ACTOR_EN_TITE, -4, func_80B02CD0 },
    { ACTOR_EN_KAME, 0, func_80B02CD0 },
    { -1, 0, NULL },
};

static Color_RGBA8 D_80B04FB4 = { 250, 250, 250, 255 };
static Color_RGBA8 D_80B04FB8 = { 180, 180, 180, 255 };
static Vec3f D_80B04FBC = { 0.0f, 0.3f, 0.0f };

static Gfx* D_80B04FC8[] = {
    object_goroiwa_DL_0072F0,
    object_goroiwa_DL_0077D0,
    object_goroiwa_DL_007C60,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 2000, ICHAIN_STOP),
};

void func_80B02CD0(ObjSnowball* this, GlobalContext* globalCtx) {
    ObjSnowballStruct2* ptr = &D_80B04F84[this->actor.home.rot.y];

    Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ptr->unk_00, this->actor.home.pos.x,
                                  this->actor.home.pos.y, this->actor.home.pos.z, this->actor.home.rot.x, 0,
                                  this->actor.home.rot.z, ptr->unk_02, -1, this->actor.unk20, NULL);
}

void func_80B02D58(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 temp_v0 = func_800A8150(OBJSNOWBALL_GET_3F(&this->actor));

    if (temp_v0 >= 0) {
        Item_DropCollectible(globalCtx, &this->actor.home.pos, (OBJSNOWBALL_GET_7F00(&this->actor) << 8) | temp_v0);
    }
}

void func_80B02DB0(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 pad;
    ObjSnowballStruct2* ptr = &D_80B04F84[this->actor.home.rot.y];

    Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ptr->unk_00, this->actor.home.pos.x,
                                  this->actor.home.pos.y, this->actor.home.pos.z, this->actor.home.rot.x, 0,
                                  this->actor.home.rot.z, this->actor.params | ptr->unk_02,
                                  ActorCutscene_GetAdditionalCutscene(this->actor.cutscene), this->actor.unk20, NULL);
}

void func_80B02E54(ObjSnowball* this, GlobalContext* globalCtx) {
    ObjSnowballStruct2* ptr = &D_80B04F84[this->actor.home.rot.y];

    Actor_SpawnAsChildAndCutscene(&globalCtx->actorCtx, globalCtx, ptr->unk_00, this->actor.home.pos.x,
                                  this->actor.home.pos.y, this->actor.home.pos.z, this->actor.home.rot.x, 0,
                                  this->actor.home.rot.z, this->actor.params | ptr->unk_02, -1, this->actor.unk20,
                                  NULL);
}

void func_80B02EE4(ObjSnowball* this, GlobalContext* globalCtx) {
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3s* hitPos = &this->collider.elements->info.bumper.hitPos;
    s32 i;

    for (i = 0; i < 4; i++) {
        sp94.x = ((Rand_ZeroOne() * 14.0f) - 7.0f) + hitPos->x;
        sp94.y = ((Rand_ZeroOne() * 14.0f) - 7.0f) + hitPos->y;
        sp94.z = ((Rand_ZeroOne() * 14.0f) - 7.0f) + hitPos->z;

        spA0.x = (Rand_ZeroOne() - 0.5f) * 1.6f;
        spA0.y = -0.8f;
        spA0.z = (Rand_ZeroOne() - 0.5f) * 1.6f;

        spAC.x = spA0.x * -0.06f;
        spAC.y = spA0.y * -0.06f;
        spAC.z = spA0.z * -0.06f;

        func_800B0E48(globalCtx, &sp94, &spA0, &spAC, &D_80B04FB4, &D_80B04FB8, (s32)(Rand_ZeroOne() * 30.0f) + 15,
                      (s32)(Rand_ZeroOne() * 40.0f) + 30);
    }
}

void func_80B030F8(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 pad;
    f32 temp_f28 = sqrtf(this->unk_20C);
    Vec3f spFC;
    Vec3f spF0;
    Vec3f spE4;
    s32 i;
    s32 phi_s6;
    Gfx* temp_s2;
    s16 scale;
    s32 temp_s1;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f26;
    s16 temp_s0;
    s32 temp_s7;
    f32 phi_f22;
    s32 gravity;
    s32 phi_s0;
    s32 phi_s4;

    for (i = 0, phi_s6 = 0; i < 25; i++, phi_s6 += 0xA3D) {
        temp_s7 = i & 7;
        if (temp_s7 < 4) {
            temp_s2 = D_80B04FC8[2];
            gravity = -280;
            phi_s4 = 0;
            phi_s0 = 0x40;
            phi_f22 = 1.0f;
        } else if (temp_s7 < 6) {
            temp_s2 = D_80B04FC8[1];
            gravity = -340;
            phi_s4 = 0;
            phi_f22 = 0.9f;
            if (Rand_ZeroOne() < 0.4f) {
                phi_s0 = 0x20;
            } else {
                phi_s0 = 0x40;
            }
        } else {
            temp_s2 = D_80B04FC8[0];
            gravity = -400;
            phi_s4 = 1;
            phi_f22 = 0.8f;
            if (Rand_Next() > 0) {
                phi_s0 = 0x21;
            } else {
                phi_s0 = 0x41;
            }
        }

        temp_f20 = (Rand_ZeroOne() * (40.0f * this->unk_20C)) + 20.0f;

        spFC.x = Math_SinS((s32)(Rand_ZeroOne() * 2621.44f) + phi_s6) * temp_f20;
        spFC.y = (Rand_ZeroOne() - 0.4f) * temp_f20 * 1.6666666f;
        spFC.z = Math_CosS((s32)(Rand_ZeroOne() * 2621.44f) + phi_s6) * temp_f20;

        spF0.x = spFC.x * 0.16f * phi_f22;
        spF0.y = (Rand_ZeroOne() * 16.0f) + 3.0f;
        spF0.z = spFC.z * 0.16f * phi_f22;

        spFC.x += this->actor.world.pos.x;
        spFC.y += this->actor.world.pos.y;
        spFC.z += this->actor.world.pos.z;

        scale = ((Rand_ZeroOne() * 15.0f) + 30.0f) * this->unk_20C;

        EffectSsKakera_Spawn(globalCtx, &spFC, &spF0, &spFC, gravity, phi_s0, 30, 0, 0, scale, phi_s4, 0, 50, -1,
                             OBJECT_GOROIWA, temp_s2);
        if ((this->unk_210 == 0) && (temp_s7 >= 3)) {
            spFC.x += (Rand_ZeroOne() * 120.0f) - 60.0f;
            spFC.y += Rand_ZeroOne() * 80.0f;
            spFC.z += (Rand_ZeroOne() * 120.0f) - 60.0f;

            temp_s0 = (s32)(Rand_ZeroOne() * 50.0f * temp_f28) + 40;
            temp_s1 = (s32)(Rand_ZeroOne() * 60.0f * temp_f28) + 50;
            func_800B0E48(globalCtx, &spFC, &gZeroVec3f, &D_80B04FBC, &D_80B04FB4, &D_80B04FB8, temp_s0, temp_s1);
        }
    }

    if (this->unk_210 != 0) {
        temp_f26 = this->unk_20C * 60.0f;

        for (i = 0, phi_s6 = 0; i < 16; i++, phi_s6 += 0x1000) {
            temp_s0 = (u32)Rand_Next() >> 0x10;
            temp_f20 = Math_SinS(temp_s0);
            temp_f22 = Math_CosS(temp_s0);

            spFC.x = Math_SinS(phi_s6);
            spFC.z = Math_CosS(phi_s6);

            spF0.x = 2.0f * spFC.x;
            spF0.y = (2.0f * Rand_ZeroOne()) + 1.0f;
            spF0.z = 2.0f * spFC.z;

            spFC.x *= temp_f22 * temp_f26;
            spFC.y = temp_f20 * temp_f26;
            spFC.z *= temp_f22 * temp_f26;

            spFC.x += this->actor.world.pos.x;
            spFC.y += this->actor.world.pos.y;
            spFC.z += this->actor.world.pos.z;

            spE4.x = spF0.x * -0.02f;
            spE4.y = spF0.y * -0.05f;
            spE4.z = spF0.z * -0.02f;

            EffectSsIceSmoke_Spawn(globalCtx, &spFC, &spF0, &spE4, ((s32)(Rand_ZeroOne() * 170.0f) + 150) * temp_f28);
        }
    }
}

void func_80B03688(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f spB8;
    Vec3f spAC;
    Vec3f spA0;
    s32 pad[2];
    f32 temp_f20;
    f32 temp_f22 = sqrtf(this->unk_20C);
    s16 temp_s3;
    s32 phi_s0;

    if (this->unk_210 == 0) {
        for (i = 0, phi_s0 = 0; i < 10; i++, phi_s0 += 0x1999) {
            temp_f20 = (Rand_ZeroOne() * (45.0f * this->unk_20C)) + 50.0f;

            spB8.x = Math_SinS((s32)(Rand_ZeroOne() * 6553.6f) + phi_s0) * temp_f20;
            spB8.y = Rand_ZeroOne() * 20.0f;
            spB8.z = Math_CosS((s32)(Rand_ZeroOne() * 6553.6f) + phi_s0) * temp_f20;

            spAC.x = spB8.x * 0.06f;
            spAC.y = 0.0f;
            spAC.z = spB8.z * 0.06f;

            spA0.x = spAC.x * -0.08f;
            spA0.y = 0.3f;
            spA0.z = spAC.z * -0.08f;

            spB8.x += this->actor.home.pos.x;
            spB8.y += this->actor.home.pos.y;
            spB8.z += this->actor.home.pos.z;

            temp_s3 = (s32)(Rand_ZeroOne() * 60.0f * temp_f22) + 70;

            func_800B0E48(globalCtx, &spB8, &spAC, &spA0, &D_80B04FB4, &D_80B04FB8, temp_s3,
                          (s32)(Rand_ZeroOne() * 70.0f * temp_f22) + 70);
        }
    } else {
        for (i = 0, phi_s0 = 0; i < 18; i++, phi_s0 += 0xE38) {
            temp_f20 = (Rand_ZeroOne() * (45.0f * this->unk_20C)) + 50.0f;

            spB8.x = Math_SinS((s32)(Rand_ZeroOne() * 3640.889f) + phi_s0);
            spB8.z = Math_CosS((s32)(Rand_ZeroOne() * 3640.889f) + phi_s0);

            spAC.x = spB8.x * 3.0f * temp_f22;
            spAC.y = 0.0f;
            spAC.z = spB8.z * 3.0f * temp_f22;

            spA0.x = spAC.x * -0.02f;
            spA0.y = 0.03f;
            spA0.z = spAC.z * -0.02f;

            spB8.x = (spB8.x * temp_f20) + this->actor.home.pos.x;
            spB8.y = (Rand_ZeroOne() * 20.0f) + this->actor.home.pos.y;
            spB8.z = (spB8.z * temp_f20) + this->actor.home.pos.z;

            EffectSsIceSmoke_Spawn(globalCtx, &spB8, &spAC, &spA0, (s32)(Rand_ZeroOne() * 140.0f * temp_f22) + 100);
        }
    }
}

void func_80B03A80(GlobalContext* globalCtx, f32 arg1, Vec3f* arg2) {
    f32 temp_f30 = sqrtf(arg1);
    Vec3f spD8;
    Vec3f spCC;
    s32 i;
    Gfx* temp_s1;
    f32 temp_f20;
    s16 phi_s2;
    s16 phi_s0;
    s16 phi_s3;
    s32 phi_s5;
    s32 tmp;
    s32 pad;

    for (i = 0, phi_s5 = 0; i < 13; i++, phi_s5 += 0x1999) {
        tmp = i & 3;

        temp_f20 = (Rand_ZeroOne() * (40.0f * arg1)) + 20.0f;

        spD8.x = Math_SinS((s32)(Rand_ZeroOne() * 6553.6f) + phi_s5) * temp_f20;
        spD8.y = Rand_ZeroOne() * temp_f20;
        spD8.z = Math_CosS((s32)(Rand_ZeroOne() * 6553.6f) + phi_s5) * temp_f20;

        spCC.x = spD8.x * 0.17f;
        spCC.y = (Rand_ZeroOne() * 14.0f) + 3.0f;
        spCC.z = spD8.z * 0.17f;

        spD8.x += arg2->x;
        spD8.y += arg2->y;
        spD8.z += arg2->z;

        if (tmp == 0) {
            temp_s1 = D_80B04FC8[0];
            phi_s2 = -400;
            phi_s3 = 1;
            if (Rand_Next() > 0) {
                phi_s0 = 0x21;
            } else {
                phi_s0 = 0x41;
            }
        } else if (tmp == 1) {
            temp_s1 = D_80B04FC8[1];
            phi_s2 = -340;
            phi_s3 = 1;
            if (Rand_Next() > 0) {
                phi_s0 = 0x21;
            } else {
                phi_s0 = 0x41;
            }
        } else {
            temp_s1 = D_80B04FC8[2];
            phi_s2 = -280;
            phi_s3 = 0;
            phi_s0 = 0x40;
        }

        EffectSsKakera_Spawn(globalCtx, &spD8, &spCC, &spD8, phi_s2, phi_s0, 30, 0, 0,
                             ((Rand_ZeroOne() * 15.0f) + 25.0f) * arg1, phi_s3, 0, 0x36, -1, OBJECT_GOROIWA, temp_s1);

        spD8.x += (Rand_ZeroOne() * 80.0f) - 40.0f;
        spD8.y += Rand_ZeroOne() * 55.0f;
        spD8.z += (Rand_ZeroOne() * 80.0f) - 40.0f;

        phi_s0 = (s32)(Rand_ZeroOne() * 60.0f * temp_f30) + 60;

        func_800B0E48(globalCtx, &spD8, &gZeroVec3f, &D_80B04FBC, &D_80B04FB4, &D_80B04FB8, phi_s0,
                      (s32)(Rand_ZeroOne() * 30.0f * temp_f30) + 60);
    }
}

void func_80B03E2C(ObjSnowball* this, GlobalContext* globalCtx) {
    ObjSnowballStruct* ptr;
    s32 i;

    this->unk_1A8[0].unk_1C.y = this->actor.yawTowardsPlayer - 0x4000;
    this->unk_1A8[0].unk_24 = Rand_ZeroOne() * -600.0f;
    this->unk_1A8[1].unk_1C.y = this->actor.yawTowardsPlayer + 0x4000;
    this->unk_1A8[1].unk_24 = Rand_ZeroOne() * 600.0f;

    for (i = 0; i < ARRAY_COUNT(this->unk_1A8); i++) {
        ptr = &this->unk_1A8[i];
        ptr->unk_00.x = this->actor.home.pos.x;
        ptr->unk_00.y = this->actor.home.pos.y + (61.0f * this->unk_20C);
        ptr->unk_00.z = this->actor.home.pos.z;

        ptr->unk_0C = Math_SinS(ptr->unk_1C.y) * (Rand_ZeroOne() + 5.0f);
        ptr->unk_10 = (Rand_ZeroOne() * 11.0f) + 20.0f;
        ptr->unk_14 = Math_CosS(ptr->unk_1C.y) * (Rand_ZeroOne() + 5.0f);

        ptr->unk_1C.x = 0;
        ptr->unk_1C.z = 0;

        ptr->unk_22 = (s32)(Rand_ZeroOne() * 400.0f) + 1100;
        ptr->unk_26 = Rand_ZeroOne() * -600.0f;
        ptr->unk_2D = 0;
        ptr->unk_2C = 0;
    }
}

void func_80B03FF8(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 rotY = this->actor.home.rot.y;
    ObjSnowballStruct2* sp18 = &D_80B04F84[rotY];

    if (sp18->unk_04 != NULL) {
        sp18->unk_04(this, globalCtx);
    }

    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_SNOWBALL_BROKEN);

    if (rotY == 5) {
        Flags_SetSwitch(globalCtx, OBJSNOWBALL_GET_3F(&this->actor));
    }
}

void ObjSnowball_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjSnowball* this = THIS;
    Sphere16* sphere;
    ColliderJntSphElementDim* elementDim;
    Vec3f sp48;
    s32 sp44;
    s32 sp40 = this->actor.home.rot.y;
    f32 phi_f20;
    s32 sp34;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    sp34 = sp40 == 1;
    if (sp34) {
        phi_f20 = 1.5f;
    } else {
        phi_f20 = 1.0f;
    }

    Actor_SetScale(&this->actor, 0.1f * phi_f20);

    this->actor.shape.rot.x = 0;
    this->actor.shape.rot.z = 0;
    this->actor.world.pos.y += 20.0f * phi_f20;
    this->actor.uncullZoneScale = 150.0f * phi_f20;
    this->actor.uncullZoneDownward = 300.0f * phi_f20;
    this->actor.shape.rot.y = (u32)Rand_Next() >> 0x10;
    this->unk_20C = phi_f20;

    if (sp34) {
        this->actor.textId = 0x238;
        this->actor.flags |= ACTOR_FLAG_1;
        this->actor.targetArrowOffset = 1400.0f / 3.0f;
        Actor_SetFocus(&this->actor, 24.0f);
        this->actor.targetMode = 3;
    }

    Collider_InitJntSph(globalCtx, &this->collider);
    Collider_SetJntSph(globalCtx, &this->collider, &this->actor, &sJntSphInit, this->colliderElements);
    this->actor.colChkInfo.mass = MASS_HEAVY;

    sphere = &this->collider.elements[0].dim.worldSphere;
    sphere->center.x = this->actor.world.pos.x;
    sphere->center.y = this->actor.world.pos.y;
    sphere->center.z = this->actor.world.pos.z;
    sphere->radius =
        (this->collider.elements[0].dim.scale * this->collider.elements[0].dim.modelSphere.radius) * phi_f20;

    sp48.x = this->actor.home.pos.x;
    sp48.y = this->actor.home.pos.y + 30.0f;
    sp48.z = this->actor.home.pos.z;

    this->actor.floorHeight =
        BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->actor.floorPoly, &sp44, &this->actor, &sp48);
    if (this->actor.floorHeight < (this->actor.home.pos.y - 10.0f)) {
        this->actor.floorPoly = NULL;
    } else {
        ActorShape_Init(&this->actor.shape, 0.0f, NULL, 13.0f);
    }

    func_80B04338(this, globalCtx);

    if ((sp40 == 5) && Flags_GetSwitch(globalCtx, OBJSNOWBALL_GET_3F(&this->actor))) {
        Actor_MarkForDeath(&this->actor);
    }
}

void ObjSnowball_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjSnowball* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider);
}

void func_80B04338(ObjSnowball* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B04350;
}

void func_80B04350(ObjSnowball* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 flag = (this->collider.base.acFlags & AC_HIT) != 0;

    if (flag) {
        this->collider.base.acFlags &= ~AC_HIT;
    }

    if (flag && (this->unk_211 == 0) &&
        (this->collider.elements->info.acHitInfo->toucher.dmgFlags &
         (0x80000000 | 0x4000 | 0x800 | 0x400 | 0x100 | 0x8))) {
        this->actor.flags |= ACTOR_FLAG_10;
        if (this->actor.home.rot.y == 1) {
            this->actor.flags &= ~(ACTOR_FLAG_1 | ACTOR_FLAG_8);
        }

        if (this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x4000) {
            this->unk_20A = 1;
        } else {
            if (this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x800) {
                this->unk_210 = 1;
            }
            this->unk_20A = 0;
        }

        if (this->actor.cutscene < 0) {
            func_80B03FF8(this, globalCtx);
            if (this->unk_20A == 0) {
                func_80B04608(this, globalCtx);
            } else {
                func_80B046E4(this, globalCtx);
            }
        } else {
            func_80B04540(this, globalCtx);
        }
        return;
    }

    if (flag &&
        !(this->collider.elements->info.acHitInfo->toucher.dmgFlags & (0x10000 | 0x2000 | 0x1000 | 0x800 | 0x20))) {
        if (this->unk_209 <= 0) {
            func_80B02EE4(this, globalCtx);
            if (this->collider.elements->info.acHitInfo->toucher.dmgFlags & 0x1000000) {
                this->unk_209 = 25;
            } else {
                this->unk_209 = 10;
            }
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_REFLECTION_SNOW);
        }
    }

    if (this->unk_209 > 0) {
        this->unk_209--;
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
}

void func_80B04540(ObjSnowball* this, GlobalContext* globalCtx) {
    ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    this->actionFunc = func_80B0457C;
}

void func_80B0457C(ObjSnowball* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        func_80B03FF8(this, globalCtx);
        this->unk_20B = 1;
        if (this->unk_20A == 0) {
            func_80B04608(this, globalCtx);
        } else {
            func_80B046E4(this, globalCtx);
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80B04608(ObjSnowball* this, GlobalContext* globalCtx) {
    func_80B030F8(this, globalCtx);
    this->actor.draw = NULL;
    this->unk_208 = 50;
    this->actor.floorPoly = NULL;
    this->actionFunc = func_80B04648;
}

void func_80B04648(ObjSnowball* this, GlobalContext* globalCtx) {
    this->unk_208--;
    if (this->unk_208 <= 0) {
        if (this->unk_20B != 0) {
            ActorCutscene_Stop(this->actor.cutscene);
        }

        if (this->actor.home.rot.y == 1) {
            func_80B04B48(this, globalCtx);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else if (this->unk_208 == 0x2D) {
        func_80B03688(this, globalCtx);
    }
}

void func_80B046E4(ObjSnowball* this, GlobalContext* globalCtx) {
    Vec3f sp44;
    s32 i;

    func_80B03E2C(this, globalCtx);

    for (i = 0; i < ARRAY_COUNT(this->unk_1A8); i++) {
        sp44.x = this->unk_1A8[i].unk_00.x;
        sp44.y = this->unk_1A8[i].unk_00.y - (60.0f * this->unk_20C);
        sp44.z = this->unk_1A8[i].unk_00.z;
        func_80B03A80(globalCtx, this->unk_20C, &sp44);
    }

    this->actor.draw = func_80B04D34;
    this->actor.floorPoly = NULL;
    this->unk_208 = 50;
    this->actionFunc = func_80B047C0;
}

void func_80B047C0(ObjSnowball* this, GlobalContext* globalCtx) {
    static Vec3f D_80B04FD8 = { 0.0f, 1.0f, 0.0f };
    static Vec3f D_80B04FE4 = { 0.0f, 0.0f, 1.0f };
    s32 pad;
    ObjSnowballStruct* ptr;
    Vec3f sp9C;
    s32 sp98;
    s32 i;
    Vec3f sp88;
    f32 sp84;
    f32 phi_f2;
    f32 sp7C;
    Vec3f sp70;

    for (i = 0; i < ARRAY_COUNT(this->unk_1A8); i++) {
        ptr = &this->unk_1A8[i];

        if (!(ptr->unk_2D & 1)) {
            ptr->unk_10 -= 6.0f;
            ptr->unk_10 *= 0.96f;
            if (ptr->unk_10 < -20.0f) {
                ptr->unk_10 = -20.0f;
            }

            ptr->unk_00.x += ptr->unk_0C;
            ptr->unk_00.y += ptr->unk_10;
            ptr->unk_00.z += ptr->unk_14;

            ptr->unk_1C.x += ptr->unk_22;
            ptr->unk_1C.y += ptr->unk_24;
            ptr->unk_1C.z += ptr->unk_26;

            sp9C.x = ptr->unk_00.x;
            sp9C.y = ptr->unk_00.y + 25.0f;
            sp9C.z = ptr->unk_00.z;

            ptr->unk_18 = BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &ptr->unk_28, &sp98, &this->actor, &sp9C);

            if (ptr->unk_10 <= 0.0f) {
                Matrix_InsertRotation(ptr->unk_1C.x, ptr->unk_1C.y, ptr->unk_1C.z, MTXMODE_NEW);
                Matrix_MultiplyVector3fByState(&D_80B04FE4, &sp88);

                sp84 = this->unk_20C * 60.0f * 0.9f;
                if (sp88.y > 0.0f) {
                    if (Math3D_AngleBetweenVectors(&D_80B04FD8, &sp88, &sp7C)) {
                        phi_f2 = 1.0f;
                    } else {
                        phi_f2 = 1.0f - SQ(sp7C);
                    }

                    if (phi_f2 <= 0.0f) {
                        sp84 = 0.0f;
                    } else {
                        sp84 *= sqrtf(phi_f2);
                    }
                }

                if (((ptr->unk_00.y - sp84) < ptr->unk_18) || (ptr->unk_18 < BGCHECK_Y_MIN + 10.0f)) {
                    ptr->unk_2D |= 1;
                    sp70.x = ptr->unk_00.x;
                    sp70.y = ptr->unk_00.y - sp84;
                    sp70.z = ptr->unk_00.z;
                    func_80B03A80(globalCtx, this->unk_20C, &sp70);
                }
            }
        }
    }

    this->unk_208--;

    if ((this->unk_208 <= 0) || ((this->unk_1A8[0].unk_2D & 1) && (this->unk_1A8[1].unk_2D & 1))) {
        if (this->unk_20B != 0) {
            ActorCutscene_Stop(this->actor.cutscene);
        }

        if (this->actor.home.rot.y == 1) {
            func_80B04B48(this, globalCtx);
        } else {
            Actor_MarkForDeath(&this->actor);
        }
    } else {
        for (i = 0; i < ARRAY_COUNT(this->unk_1A8); i++) {
            ptr = &this->unk_1A8[i];

            if (ptr->unk_2D & 1) {
                ptr->unk_2C = 0;
            } else if (ptr->unk_2C < 136) {
                ptr->unk_2C += 24;
            } else {
                ptr->unk_2C = 160;
            }
        }
    }
}

void func_80B04B48(ObjSnowball* this, GlobalContext* globalCtx) {
    this->actionFunc = func_80B04B60;
}

void func_80B04B60(ObjSnowball* this, GlobalContext* globalCtx) {
}

void ObjSnowball_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjSnowball* this = THIS;
    s32 sp24 = false;

    if (this->actor.home.rot.y == 1) {
        if (this->unk_211 != 0) {
            if (Actor_TextboxIsClosing(&this->actor, globalCtx)) {
                this->actor.flags &= ~ACTOR_FLAG_10;
                this->unk_211 = 0;
            }
        } else if (Actor_ProcessTalkRequest(&this->actor, &globalCtx->state)) {
            this->actor.flags |= ACTOR_FLAG_10;
            this->unk_211 = 1;
        } else if (this->actor.isTargeted) {
            sp24 = true;
        }
    }

    this->actionFunc(this, globalCtx);

    if (sp24 && (this->actionFunc == func_80B04350)) {
        func_800B8614(&this->actor, globalCtx, 100.0f);
    }

    if ((this->actor.floorPoly != NULL) && (this->actor.projectedPos.z < 920.0f)) {
        if (this->actor.projectedPos.z > 400.0f) {
            this->actor.shape.shadowAlpha = (920 - (s32)this->actor.projectedPos.z) >> 2;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        } else if (this->actor.projectedPos.z > -30.0f) {
            this->actor.shape.shadowAlpha = 130;
            this->actor.shape.shadowDraw = ActorShadow_DrawCircle;
        } else {
            this->actor.shape.shadowDraw = NULL;
        }
    } else {
        this->actor.shape.shadowDraw = NULL;
    }
}

void ObjSnowball_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjSnowball* this = THIS;

    Gfx_DrawDListOpa(globalCtx, object_goroiwa_DL_008B90);
}

void func_80B04D34(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjSnowball* this = THIS;
    ObjSnowballStruct* ptr;
    s32 i;
    MtxF sp88;
    Vec3s sp80;

    for (i = 0; i < ARRAY_COUNT(this->unk_1A8); i++) {
        ptr = &this->unk_1A8[i];

        if (!(ptr->unk_2D & 1)) {
            sp80.x = ptr->unk_1C.x;
            sp80.y = ptr->unk_1C.y;
            sp80.z = ptr->unk_1C.z;

            Matrix_SetStateRotationAndTranslation(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, &sp80);
            Matrix_Scale(this->actor.scale.x, this->actor.scale.y, this->actor.scale.z, MTXMODE_APPLY);
            Gfx_DrawDListOpa(globalCtx, object_goroiwa_DL_0082D0);

            if ((ptr->unk_28 != NULL) && (ptr->unk_2C > 0)) {
                OPEN_DISPS(globalCtx->state.gfxCtx);

                func_8012C448(globalCtx->state.gfxCtx);

                gDPSetCombineLERP(POLY_XLU_DISP++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, COMBINED, 0, 0,
                                  0, COMBINED);
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 0, 0, 0, ptr->unk_2C);

                func_800C0094(ptr->unk_28, ptr->unk_00.x, ptr->unk_18, ptr->unk_00.z, &sp88);
                Matrix_SetCurrentState(&sp88);
                Matrix_Scale(this->actor.scale.x * 7.5f, 1.0f, this->actor.scale.z * 7.5f, MTXMODE_APPLY);

                gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                          G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
                gSPDisplayList(POLY_XLU_DISP++, gCircleShadowDL);

                CLOSE_DISPS(globalCtx->state.gfxCtx);
            }
        }
    }
}
