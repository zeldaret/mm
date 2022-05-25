/*
 * File: z_obj_bean.c
 * Overlay: ovl_Obj_Bean
 * Description: Floating Bean Plant / Soft Soil
 */

#include "z_obj_bean.h"
#include "objects/object_mamenoki/object_mamenoki.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_400000)

#define THIS ((ObjBean*)thisx)

void ObjBean_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_Update(Actor* thisx, GlobalContext* globalCtx);

void func_80937C10(ObjBean* this);
void func_80937C24(ObjBean* this);
void func_80937CA0(ObjBean* this);
void func_80937CE4(ObjBean* this);
void func_80937D54(ObjBean* this);
void func_80937DD8(ObjBean* this);
void func_80937DEC(ObjBean* this, GlobalContext* globalCtx);
void func_80937FB0(ObjBean* this);
void func_80937FC8(ObjBean* this, GlobalContext* globalCtx);
void func_809381B0(ObjBean* this);
void func_809381C4(ObjBean* this, GlobalContext* globalCtx);
void func_80938284(ObjBean* this);
void func_80938298(ObjBean* this, GlobalContext* globalCtx);
void func_8093833C(ObjBean* this);
void func_80938358(ObjBean* this, GlobalContext* globalCtx);
void func_809383B4(ObjBean* this);
void func_809383D0(ObjBean* this, GlobalContext* globalCtx);
void func_80938408(ObjBean* this);
void func_80938444(ObjBean* this, GlobalContext* globalCtx);
void func_809384E8(ObjBean* this);
void func_80938504(ObjBean* this, GlobalContext* globalCtx);
void func_80938588(ObjBean* this);
void func_809385A8(ObjBean* this, GlobalContext* globalCtx);
void func_80938670(ObjBean* this);
void func_8093868C(ObjBean* this, GlobalContext* globalCtx);
void func_80938704(ObjBean* this);
void func_80938728(ObjBean* this, GlobalContext* globalCtx);
void func_8093876C(ObjBean* this);
void func_80938780(ObjBean* this, GlobalContext* globalCtx);
void func_80938804(ObjBean* this);
void func_80938834(ObjBean* this, GlobalContext* globalCtx);
void func_80938874(ObjBean* this);
void func_809388A8(ObjBean* this, GlobalContext* globalCtx);
void func_8093892C(ObjBean* this);
void func_80938958(ObjBean* this, GlobalContext* globalCtx);
void func_809389BC(ObjBean* this, GlobalContext* globalCtx);
void func_80938A14(ObjBean* this);
void func_80938A5C(ObjBean* this, GlobalContext* globalCtx);
void func_80938AA4(ObjBean* this);
void func_80938AD8(ObjBean* this, GlobalContext* globalCtx);
void func_80938C1C(Actor* thisx, GlobalContext* globalCtx);
void func_80938E00(Actor* thisx, GlobalContext* globalCtx);
void func_80938F50(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Bean_InitVars = {
    ACTOR_OBJ_BEAN,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_MAMENOKI,
    sizeof(ObjBean),
    (ActorFunc)ObjBean_Init,
    (ActorFunc)ObjBean_Destroy,
    (ActorFunc)ObjBean_Update,
    (ActorFunc)NULL,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_TYPE_PLAYER,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000000, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_ON,
    },
    { 64, 30, -31, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_OTHER,
        OC1_NONE,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 10, 10, 0, { 0, 0, 0 } },
};

static Vec2f D_80938FF8[4] = {
    { 3.0f, 0.3f },
    { 10.0f, 0.5f },
    { 30.0f, 0.5f },
    { 3.0f, 0.3f },
};

void func_80936CF0(ObjBean* this, GlobalContext* globalCtx) {
    Vec3f sp24;
    s32 sp20;

    sp24.x = this->dyna.actor.world.pos.x;
    sp24.y = this->dyna.actor.world.pos.y + 29.999998f;
    sp24.z = this->dyna.actor.world.pos.z;
    this->dyna.actor.floorHeight =
        BgCheck_EntityRaycastFloor5(&globalCtx->colCtx, &this->dyna.actor.floorPoly, &sp20, &this->dyna.actor, &sp24);
}

s32 func_80936D58(ObjBean* this, GlobalContext* globalCtx) {
    static Vec3f D_80939018 = { 0.0f, 30.0f, 0.0f };
    s32 pad;
    s32 spB8;
    Vec3f spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3f sp88;
    MtxF sp48;

    Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(this->dyna.actor.shape.rot.x, MTXMODE_APPLY);
    Matrix_InsertZRotation_s(this->dyna.actor.shape.rot.z, MTXMODE_APPLY);
    Matrix_MultiplyVector3fByState(&D_80939018, &spAC);
    Math_Vec3f_Sum(&this->dyna.actor.world.pos, &spAC, &spA0);
    Math_Vec3f_Diff(&this->dyna.actor.world.pos, &spAC, &sp94);

    if (BgCheck_EntityLineTest2(&globalCtx->colCtx, &spA0, &sp94, &sp88, &this->dyna.actor.floorPoly, true, true, true,
                                true, &spB8, &this->dyna.actor)) {
        this->dyna.actor.world.pos.x = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.x) * 1.9f) + sp88.x;
        this->dyna.actor.world.pos.y = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.y) * 1.9f) + sp88.y;
        this->dyna.actor.world.pos.z = (COLPOLY_GET_NORMAL(this->dyna.actor.floorPoly->normal.z) * 1.9f) + sp88.z;
        func_800C0094(this->dyna.actor.floorPoly, this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                      this->dyna.actor.world.pos.z, &sp48);
        Matrix_SetCurrentState(&sp48);
        Matrix_RotateY(this->dyna.actor.shape.rot.y, MTXMODE_APPLY);
        Matrix_CopyCurrentState(&sp48);
        func_8018219C(&sp48, &this->dyna.actor.shape.rot, 0);
        return true;
    }
    return false;
}

void func_80936F04(ObjBean* this) {
    this->unk_1AC = this->unk_1AE = this->unk_1B0 = 0;
    this->unk_1C8 = 0.0f;
}

void func_80936F24(ObjBean* this) {
    this->unk_1AC += 0xB6;
    this->unk_1AE += 0xFB;
    this->unk_1B0 += 0x64;
    Math_StepToF(&this->unk_1C8, 2.0f, 0.1f);
    this->unk_1CC = (Math_SinS(this->unk_1AC * 3) + Math_SinS(this->unk_1AE * 3)) * this->unk_1C8;
    this->unk_1D0 = (Math_CosS(this->unk_1AC * 4) + Math_CosS(this->unk_1AE * 4)) * this->unk_1C8;
    this->dyna.actor.scale.z =
        ((Math_SinS(this->unk_1B0 * 5) * 0.06f) + (Math_SinS(this->unk_1AE * 8) * 0.01f) + 1.07f) * 0.1f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z;
    this->dyna.actor.scale.y = ((Math_CosS(this->unk_1B0 * 10) * 0.2f) + 1.0f) * 0.1f;
    this->dyna.actor.shape.rot.y = (this->dyna.actor.home.rot.y + (s32)(Math_SinS(this->unk_1AC * 3) * 1000.0f)) +
                                   (s32)(Math_SinS(this->unk_1B0 * 2) * 2100.0f);
}

void func_80937130(ObjBean* this) {
    this->unk_1AC = this->unk_1AE = this->unk_1B0 = 0;
    Actor_SetScale(&this->dyna.actor, 0.0f);
}

void func_80937160(ObjBean* this) {
    this->unk_1AC += 0x384;
    if (this->unk_1AC > 0x5FFF) {
        this->unk_1AC = 0x5FFF;
    }

    this->unk_1AE += 0x258;
    if (this->unk_1AE > 0x4000) {
        this->unk_1AE = 0x4000;
    }

    this->dyna.actor.scale.y = Math_SinS(this->unk_1AC) * 0.16970563f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_SinS(this->unk_1AE) * 0.10700001f;
    Math_StepToF(&this->unk_1CC, 0.0f, 0.1f);
    Math_StepToF(&this->unk_1D0, 0.0f, 0.1f);
    Math_ScaledStepToS(&this->dyna.actor.shape.rot.y, this->dyna.actor.home.rot.y, 100);
}

void func_80937238(ObjBean* this) {
    this->dyna.actor.world.pos.x = this->unk_1BC.x + this->unk_1CC;
    this->dyna.actor.world.pos.y = this->unk_1BC.y;
    this->dyna.actor.world.pos.z = this->unk_1BC.z + this->unk_1D0;
}

void func_80937268(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1D8 = globalCtx->setupPathList[OBJBEAN_GET_3F00(&this->dyna.actor)].count - 1;
    this->unk_1DA = 0;
    this->unk_1DC = 1;
}

void func_809372A8(ObjBean* this) {
    Math_Vec3s_ToVec3f(&this->unk_1BC, this->unk_1D4);
}

void func_809372D0(ObjBean* this) {
    Actor* actor = &this->dyna.actor;
    Vec3f sp38;
    f32 sp34;
    f32 temp_f2;
    f32 temp_f12;

    Math_Vec3s_ToVec3f(&sp38, &this->unk_1D4[this->unk_1DC]);
    Math_Vec3f_Diff(&sp38, &this->unk_1BC, &actor->velocity);

    sp34 = Math3D_Vec3fMagnitude(&actor->velocity);
    temp_f2 = D_80938FF8[this->unk_1DE].x;
    temp_f12 = D_80938FF8[this->unk_1DE].z;
    if (sp34 < (actor->speedXZ * 8.0f)) {
        temp_f2 = ((temp_f2 - 2.0f) * 0.1f) + 2.0f;
        temp_f12 *= 0.4f;
    }

    Math_StepToF(&actor->speedXZ, temp_f2, temp_f12);

    if ((actor->speedXZ + 0.05f) < sp34) {
        Math_Vec3f_Scale(&actor->velocity, actor->speedXZ / sp34);
        this->unk_1BC.x += actor->velocity.x;
        this->unk_1BC.y += actor->velocity.y;
        this->unk_1BC.z += actor->velocity.z;
    } else {
        Math_Vec3f_Copy(&this->unk_1BC, &sp38);
        this->unk_1DA = this->unk_1DC;
        if (this->unk_1DA >= this->unk_1D8) {
            this->unk_1DC = 0;
        } else {
            this->unk_1DC++;
        }
        actor->speedXZ *= 0.5f;
    }
}

s32 func_80937468(ObjBean* this, GlobalContext* globalCtx) {
    Actor* bgActor = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;

    while (bgActor != NULL) {
        if ((bgActor->id == ACTOR_EN_HORSE) &&
            (Math3D_Vec3fDistSq(&bgActor->world.pos, &this->dyna.actor.world.pos) < SQ(100.0f))) {
            return true;
        }
        bgActor = bgActor->next;
    }

    return false;
}

ObjBean* func_809374F8(ObjBean* this, GlobalContext* globalCtx) {
    Actor* bgActor = globalCtx->actorCtx.actorLists[ACTORCAT_BG].first;
    s32 params = OBJBEAN_GET_3F80(&this->dyna.actor, 0);

    while (bgActor != NULL) {
        if (bgActor->id == ACTOR_OBJ_BEAN) {
            s32 params2 = OBJBEAN_GET_C000(bgActor);

            if (!params2 && (bgActor->room == this->dyna.actor.room) && !OBJBEAN_GET_80(bgActor) &&
                (params == OBJBEAN_GET_7F(bgActor, 0)) &&
                (Math3D_Vec3fDistSq(&bgActor->world.pos, &this->dyna.actor.world.pos) < SQ(10.0f))) {
                break;
            }
        }
        bgActor = bgActor->next;
    }

    return (ObjBean*)bgActor;
}

void func_809375C8(ObjBean* this, GlobalContext* globalCtx) {
    ObjBean* bean = func_809374F8(this, globalCtx);

    if (bean != NULL) {
        bean->unk_200 = 1;
    }
}

void func_809375F4(ObjBean* this, GlobalContext* globalCtx) {
    static Gfx* D_80939024[] = {
        gKakeraLeafMiddle,
        gKakeraLeafTip,
    };
    Vec3f spC4;
    Vec3f spB8;
    f32 temp_f20;
    s32 temp_s2;
    s16 temp_s1 = 0;
    s32 phi_s3;
    s32 phi_v0;
    s32 i;

    for (i = 0; i < 36; i++) {
        temp_s1 += 0x4E20;
        temp_f20 = Rand_ZeroOne() * 60.0f;

        spC4.x = (Math_SinS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.x;
        spC4.y = this->dyna.actor.world.pos.y;
        spC4.z = (Math_CosS(temp_s1) * temp_f20) + this->dyna.actor.world.pos.z;

        spB8.x = Math_SinS(temp_s1) * 3.5f;
        spB8.y = Rand_ZeroOne() * 13.0f;
        spB8.z = Math_CosS(temp_s1) * 3.5f;

        spB8.x += this->dyna.actor.world.pos.x - this->dyna.actor.prevPos.x;
        spB8.y += this->dyna.actor.world.pos.y - this->dyna.actor.prevPos.y;
        spB8.z += this->dyna.actor.world.pos.z - this->dyna.actor.prevPos.z;

        temp_s2 = (s32)(Rand_ZeroOne() * 180.0f) + 30;

        phi_v0 = 0x40;
        if (temp_s2 < 0x5A) {
            phi_s3 = -0x50;
            if (Rand_ZeroOne() < 0.1f) {
                phi_v0 = 0x60;
            } else {
                phi_v0 = 0x40;
            }
        } else {
            phi_s3 = -100;
            phi_v0 = 0x40;
        }
        EffectSsKakera_Spawn(globalCtx, &spC4, &spB8, &spC4, phi_s3, phi_v0, 40, 3, 0, temp_s2, 0, 0,
                             (temp_s2 >> 3) + 40, -1, GAMEPLAY_KEEP, D_80939024[i & 1]);
    }
}

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 2500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 200, ICHAIN_STOP),
};

void ObjBean_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjBean* this = THIS;
    s32 sp2C = OBJBEAN_GET_C000(&this->dyna.actor);

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    this->unk_1FE = 0;
    this->unk_1B8 = 0.1f;
    DynaPolyActor_Init(&this->dyna, 3);
    Collider_InitCylinder(globalCtx, &this->collider);

    if ((sp2C == ENOBJBEAN_GET_C000_1) || (sp2C == ENOBJBEAN_GET_C000_2)) {
        this->dyna.actor.update = func_80938C1C;
        this->dyna.actor.textId = 0xFD;
        if (sp2C == ENOBJBEAN_GET_C000_1) {
            Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit2);
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
        }
        this->dyna.actor.flags |= ACTOR_FLAG_10;
        func_80937C10(this);
        if (!func_80936D58(this, globalCtx)) {
            Actor_MarkForDeath(&this->dyna.actor);
        } else {
            func_800BC154(globalCtx, &globalCtx->actorCtx, &this->dyna.actor, 7);
            func_80937DD8(this);
        }
    } else {
        s32 params2 = OBJBEAN_GET_3F00(&this->dyna.actor);
        Path* path = &globalCtx->setupPathList[params2];

        this->unk_1DE = OBJBEAN_GET_3(&this->dyna.actor);
        this->dyna.actor.world.rot.z = 0;
        this->dyna.actor.home.rot.z = 0;
        this->dyna.actor.shape.rot.z = 0;
        this->unk_1FE |= 2;

        DynaPolyActor_LoadMesh(globalCtx, &this->dyna, &object_mamenoki_Colheader_0004BC);
        Collider_SetCylinder(globalCtx, &this->collider, &this->dyna.actor, &sCylinderInit1);
        Collider_UpdateCylinder(&this->dyna.actor, &this->collider);

        this->unk_1D4 = Lib_SegmentedToVirtual(path->points);

        func_80937268(this, globalCtx);
        func_809372A8(this);
        func_80937238(this);
        ActorShape_Init(&this->dyna.actor.shape, 0.0f, ActorShadow_DrawCircle, 8.8f);
        func_80936CF0(this, globalCtx);

        if (!OBJBEAN_GET_80(&this->dyna.actor) && Flags_GetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 0)) &&
            !Flags_GetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 1)) && func_800FE9B4(globalCtx)) {
            Flags_SetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 1));
        }

        if (OBJBEAN_GET_80(&this->dyna.actor) || Flags_GetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 1))) {
            func_80938804(this);
        } else {
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            func_80938704(this);
        }
    }
}

void ObjBean_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjBean* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80937B54(ObjBean* this) {
    Math_StepToS(&this->unk_1EE, this->unk_1F0, this->unk_1F2);
    Math_StepToS(&this->unk_1F4, this->unk_1F6, this->unk_1F8);
    this->unk_1FA += this->unk_1F4;
    this->unk_1FC = 6372.0f - (Math_SinS(this->unk_1FA) * this->unk_1EE);
    this->dyna.actor.scale.y = Math_SinS(this->unk_1FC) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(this->unk_1FC) * 0.12207746f;
}

void func_80937C10(ObjBean* this) {
    this->unk_1E8 = func_80937C24;
}

void func_80937C24(ObjBean* this) {
}

void func_80937C30(ObjBean* this) {
    this->unk_1E8 = func_80937CA0;
    this->unk_1EC = Rand_S16Offset(12, 40);
    this->unk_1F0 = Rand_S16Offset(200, 400);
    this->unk_1F2 = 20;
    this->unk_1F6 = Rand_S16Offset(100, 800);
    this->unk_1F8 = 20;
}

void func_80937CA0(ObjBean* this) {
    this->unk_1EC--;
    func_80937B54(this);
    if (this->unk_1EC < 0) {
        func_80937CE4(this);
    }
}

void func_80937CE4(ObjBean* this) {
    this->unk_1E8 = func_80937D54;
    this->unk_1EC = Rand_S16Offset(30, 4);
    this->unk_1F0 = Rand_S16Offset(2000, 1000);
    this->unk_1F2 = 200;
    this->unk_1F6 = Rand_S16Offset(14000, 6000);
    this->unk_1F8 = 4000;
}

void func_80937D54(ObjBean* this) {
    this->unk_1EC--;
    if (this->unk_1EC == 14) {
        this->unk_1F0 = Rand_S16Offset(200, 400);
        this->unk_1F6 = Rand_S16Offset(100, 500);
        this->unk_1F8 = 2000;
    }

    func_80937B54(this);

    if (this->unk_1EC < 0) {
        func_80937C30(this);
    }
}

void func_80937DD8(ObjBean* this) {
    this->actionFunc = func_80937DEC;
}

void func_80937DEC(ObjBean* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp20 = OBJBEAN_GET_C000(&this->dyna.actor);

    if (sp20 == ENOBJBEAN_GET_C000_1) {
        s32 pad2;

        if (func_809374F8(this, globalCtx) == NULL) {
            this->unk_1FF = false;
        } else {
            this->unk_1FF = true;
        }
    } else {
        this->unk_1FF = false;
    }

    if (this->unk_1FF && !Flags_GetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 1)) &&
        Flags_GetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 0)) && func_800FE9B4(globalCtx)) {
        Flags_SetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 1));
    }

    if (this->unk_1FF && Flags_GetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 1))) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    if (sp20 == ENOBJBEAN_GET_C000_2) {
        this->dyna.actor.draw = func_80938F50;
    } else {
        this->dyna.actor.draw = func_80938E00;
    }

    if (this->unk_1FF && Flags_GetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 0))) {
        this->unk_1FE |= 5;
        func_80937C30(this);
    } else {
        this->unk_1FE |= 1;
        func_80937C10(this);
    }

    if (Flags_GetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 0))) {
        this->unk_1E4 = 5;
    } else {
        this->unk_1E4 = 0;
    }

    func_80937FB0(this);
}

void func_80937FB0(ObjBean* this) {
    this->unk_1E0 = 0;
    this->actionFunc = func_80937FC8;
}

void func_80937FC8(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1E8(this);

    if (Actor_ProcessTalkRequest(&this->dyna.actor, &globalCtx->state)) {
        if (Player_GetExchangeItemId(globalCtx) == EXCH_ITEM_2E) {
            func_809383B4(this);
            Flags_SetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 0));
        }

        if (Flags_GetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 0))) {
            this->unk_1E4 = 5;
        } else {
            s32 pad;

            this->unk_1E4 = 0;
        }
    } else if (this->unk_1E4 == 1) {
        this->unk_1DF = 16;
        func_809381B0(this);
    } else if (((this->collider.base.acFlags & AC_HIT) && (this->collider.base.ac != NULL) &&
                (this->collider.base.ac->id == ACTOR_OBJ_AQUA)) ||
               ((this->unk_1FF != 0) && (this->unk_1FE & 4) && (this->dyna.actor.xzDistToPlayer < 300.0f) &&
                func_800FE9B4(globalCtx))) {
        func_809375C8(this, globalCtx);
        Flags_SetSwitch(globalCtx, OBJBEAN_GET_3F80(&this->dyna.actor, 1));
        this->unk_1E4 = 6;
        func_80938670(this);
    } else if (this->unk_1FF != 0) {
        if (this->unk_1FE & 4) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->dyna.actor.xzDistToPlayer < 150.0f) {
                CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
            }
        } else {
            func_800B85E0(&this->dyna.actor, globalCtx, 28.0f, 0x2E);
        }
    }
}

void func_809381B0(ObjBean* this) {
    this->actionFunc = func_809381C4;
}

void func_809381C4(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1E8(this);

    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        if (this->dyna.actor.cutscene >= 0) {
            func_800B7298(globalCtx, &this->dyna.actor, 1);
        }
        this->unk_1E4 = 2;
        func_80938284(this);
    } else if (this->unk_1E4 == 4) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        play_sound(NA_SE_SY_ERROR);
        this->unk_1E4 = 0;
        func_80937FB0(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80938284(ObjBean* this) {
    this->actionFunc = func_80938298;
}

void func_80938298(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1E8(this);

    if (this->unk_1E0 >= 3) {
        this->unk_1E4 = 3;
        Flags_SetSwitch(globalCtx, OBJBEAN_GET_7F(&this->dyna.actor, 0));
        this->unk_1E4 = 5;
        func_8093833C(this);
    } else if (this->unk_1E4 == 4) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        play_sound(NA_SE_SY_ERROR);
        this->unk_1E4 = 0;
        func_80937FB0(this);
    }
}

void func_8093833C(ObjBean* this) {
    this->actionFunc = func_80938358;
    this->unk_1B2 = 4;
}

void func_80938358(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1E8(this);

    if (this->unk_1B2 <= 0) {
        ActorCutscene_Stop(this->dyna.actor.cutscene);
        func_80937FB0(this);
    }
}

void func_809383B4(ObjBean* this) {
    this->unk_1B2 = 60;
    this->actionFunc = func_809383D0;
}

void func_809383D0(ObjBean* this, GlobalContext* globalCtx) {
    if (this->unk_1B2 <= 0) {
        this->unk_1FE |= 4;
        func_80938408(this);
    }
}

void func_80938408(ObjBean* this) {
    Actor_SetScale(&this->dyna.actor, 0.01f);
    this->actionFunc = func_80938444;
}

void func_80938444(ObjBean* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp20 = Math_StepToF(&this->dyna.actor.scale.y, 0.16672663f, 0.01f) & 1;

    sp20 &= Math_StepToF(&this->dyna.actor.scale.x, 0.03569199f, 0.00113f);

    this->dyna.actor.scale.z = this->dyna.actor.scale.x;
    if (sp20) {
        if (this->unk_1B2 <= 0) {
            func_809384E8(this);
        }
    } else {
        this->unk_1B2 = 1;
    }
    func_800B9010(&this->dyna.actor, NA_SE_PL_PLANT_GROW_UP - SFX_FLAG);
}

void func_809384E8(ObjBean* this) {
    this->unk_1AC = 0x33E9;
    this->actionFunc = func_80938504;
}

void func_80938504(ObjBean* this, GlobalContext* globalCtx) {
    this->unk_1AC -= 2400;
    this->dyna.actor.scale.y = Math_SinS(this->unk_1AC) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(this->unk_1AC) * 0.12207746f;
    if (this->unk_1AC < 6372) {
        func_80938588(this);
    }
}

void func_80938588(ObjBean* this) {
    this->unk_1AC = 0;
    this->unk_1AE = 3000;
    this->actionFunc = func_809385A8;
}

void func_809385A8(ObjBean* this, GlobalContext* globalCtx) {
    s32 pad;
    s16 sp22;

    this->unk_1AC += 16000;
    this->unk_1AE -= 200;
    sp22 = 6372.0f - (Math_SinS(this->unk_1AC) * this->unk_1AE);
    this->dyna.actor.scale.y = Math_SinS(sp22) * 0.17434467f;
    this->dyna.actor.scale.x = this->dyna.actor.scale.z = Math_CosS(sp22) * 0.12207746f;
    if (this->unk_1AE < 0) {
        func_80937C30(this);
        func_80937FB0(this);
    }
}

void func_80938670(ObjBean* this) {
    this->actionFunc = func_8093868C;
    this->unk_1B2 = 73;
}

void func_8093868C(ObjBean* this, GlobalContext* globalCtx) {
    if (this->unk_1B2 <= 0) {
        Actor_MarkForDeath(&this->dyna.actor);
    } else if (this->unk_1B2 <= 20) {
        this->dyna.actor.scale.x *= 0.89f;
        this->dyna.actor.scale.y *= 0.89f;
        this->dyna.actor.scale.z *= 0.89f;
        this->unk_1B8 *= 0.89f;
    }
}

void func_80938704(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = NULL;
    this->actionFunc = func_80938728;
}

void func_80938728(ObjBean* this, GlobalContext* globalCtx) {
    if (this->unk_200 != 0) {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        func_8093876C(this);
    }
}

void func_8093876C(ObjBean* this) {
    this->actionFunc = func_80938780;
}

void func_80938780(ObjBean* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        if (this->dyna.actor.cutscene >= 0) {
            func_800B7298(globalCtx, &this->dyna.actor, 1);
        }
        this->unk_1B4 = 36;
        func_80937130(this);
        func_80938AA4(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80938804(ObjBean* this) {
    this->dyna.actor.flags &= ~ACTOR_FLAG_10;
    this->dyna.actor.draw = func_80938E00;
    this->actionFunc = func_80938834;
}

void func_80938834(ObjBean* this, GlobalContext* globalCtx) {
    if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_80938874(this);
    }
    func_80936F24(this);
}

void func_80938874(ObjBean* this) {
    this->actionFunc = func_809388A8;
    this->dyna.actor.draw = func_80938E00;
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.speedXZ = 0.0f;
}

void func_809388A8(ObjBean* this, GlobalContext* globalCtx) {
    func_809372D0(this);
    if (this->unk_1DA == this->unk_1D8) {
        func_80937268(this, globalCtx);
        func_809372A8(this);
        func_8093892C(this);
    } else if (DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_800B9010(&this->dyna.actor, NA_SE_PL_PLANT_MOVE - SFX_FLAG);
    }
    func_80936F24(this);
}

void func_8093892C(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = func_80938E00;
    this->actionFunc = func_80938958;
}

void func_80938958(ObjBean* this, GlobalContext* globalCtx) {
    if (!DynaPolyActor_IsInRidingRotatingState(&this->dyna)) {
        func_80938804(this);
    }
    func_80936F24(this);
}

void func_80938998(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = NULL;
    this->actionFunc = func_809389BC;
}

void func_809389BC(ObjBean* this, GlobalContext* globalCtx) {
    if (!DynaPolyActor_IsInRidingMovingState(&this->dyna)) {
        func_80937268(this, globalCtx);
        func_809372A8(this);
        func_80937238(this);
        func_80938A14(this);
    }
}

void func_80938A14(ObjBean* this) {
    this->dyna.actor.draw = NULL;
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->unk_1B2 = 100;
    func_80937130(this);
    this->actionFunc = func_80938A5C;
}

void func_80938A5C(ObjBean* this, GlobalContext* globalCtx) {
    if (func_80937468(this, globalCtx)) {
        this->unk_1B2 = 100;
    } else if (this->unk_1B2 <= 0) {
        func_80938AA4(this);
    }
}

void func_80938AA4(ObjBean* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    this->dyna.actor.draw = func_80938E00;
    this->unk_1B2 = 30;
    this->actionFunc = func_80938AD8;
}

void func_80938AD8(ObjBean* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 sp30 = func_80937468(this, globalCtx);

    func_80937160(this);
    if (this->unk_1B2 == 25) {
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_PL_PLANT_GROW_BIG);
    }

    if (sp30 != 0) {
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    } else {
        func_800C6314(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    }

    if (this->dyna.actor.xzDistToPlayer < 74.0f) {
        Player* player = GET_PLAYER(globalCtx);
        f32 sp28 = 74.0f - this->dyna.actor.xzDistToPlayer;
        f32 sin;
        f32 cos;

        if (sp28 > 8.0f) {
            sp28 = 8.0f;
        }

        sin = Math_SinS(this->dyna.actor.yawTowardsPlayer) * sp28;
        cos = Math_CosS(this->dyna.actor.yawTowardsPlayer) * sp28;

        player->actor.world.pos.x += sin;
        player->actor.world.pos.z += cos;
    }

    if ((this->unk_1B2 <= 0) && (sp30 == 0)) {
        func_80936F04(this);
        func_80938804(this);
    }
}

void func_80938C1C(Actor* thisx, GlobalContext* globalCtx) {
    ObjBean* this = THIS;

    if (this->unk_1B2 > 0) {
        this->unk_1B2--;
    }

    if (this->unk_1DF > 0) {
        this->unk_1DF--;
        if (this->unk_1DF == 0) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        }
    }

    this->actionFunc(this, globalCtx);
}

void ObjBean_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjBean* this = THIS;

    if (this->unk_1B2 > 0) {
        this->unk_1B2--;
    }

    this->actionFunc(this, globalCtx);

    if (this->unk_1B4 > 0) {
        this->unk_1B4--;
        if (this->unk_1B4 == 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }
    }

    if (this->dyna.actor.draw != NULL) {
        func_80937238(this);
        if (this->dyna.actor.xzDistToPlayer < 150.0f) {
            this->collider.dim.radius = (this->dyna.actor.scale.x * 640.0f) + 0.5f;
            Collider_UpdateCylinder(&this->dyna.actor, &this->collider);
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
        func_80936CF0(this, globalCtx);
        this->dyna.actor.shape.shadowDraw = ActorShadow_DrawCircle;
        this->dyna.actor.shape.shadowScale = this->dyna.actor.scale.x * 88.0f;
        if (func_80937468(this, globalCtx)) {
            func_809375F4(this, globalCtx);
            func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
            func_80938998(this);
        }
    } else {
        this->dyna.actor.shape.shadowDraw = NULL;
    }
    Actor_SetFocus(&this->dyna.actor, 6.0f);
}

void func_80938E00(Actor* thisx, GlobalContext* globalCtx) {
    ObjBean* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

    if (this->unk_1FE & 4) {
        gSPDisplayList(POLY_OPA_DISP++, object_mamenoki_DL_000090);
    }

    if (this->unk_1FE & 2) {
        gSPDisplayList(POLY_OPA_DISP++, object_mamenoki_DL_0002D0);
    }

    if (this->unk_1FE & 1) {
        Matrix_SetStateRotationAndTranslation(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                              this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
        Matrix_Scale(this->unk_1B8, this->unk_1B8, this->unk_1B8, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_mamenoki_DL_000530);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80938F50(Actor* thisx, GlobalContext* globalCtx) {
    ObjBean* this = THIS;

    Gfx_DrawDListXlu(globalCtx, object_mamenoki_DL_002208);
}
