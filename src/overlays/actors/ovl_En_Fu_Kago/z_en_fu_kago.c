/*
 * File: z_en_fu_kago.c
 * Overlay: ovl_En_Fu_Kago
 * Description: Honey & Darling's Shop - Bomb Basket
 */

#include "z_en_fu_kago.h"
#include "overlays/actors/ovl_En_Bom/z_en_bom.h"
#include "overlays/actors/ovl_En_Fu/z_en_fu.h"
#include "objects/object_fu_mato/object_fu_mato.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnFuKago*)thisx)

void EnFuKago_Init(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Update(Actor* thisx, GlobalContext* globalCtx);
void EnFuKago_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80ACF994(EnFuKago* this);
void func_80ACF9A8(EnFuKago* this, GlobalContext* globalCtx);
void func_80ACF9DC(EnFuKago* this);
void func_80ACF9FC(EnFuKago* this, GlobalContext* globalCtx);
void func_80ACFA78(EnFuKago* this, GlobalContext* globalCtx);
void func_80AD0028(EnFuKago* this, GlobalContext* globalCtx);
void func_80AD0274(EnFuKago* this);
void func_80AD0288(EnFuKago* this, GlobalContext* globalCtx);

const ActorInit En_Fu_Kago_InitVars = {
    ACTOR_EN_FU_KAGO,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_FU_MATO,
    sizeof(EnFuKago),
    (ActorFunc)EnFuKago_Init,
    (ActorFunc)EnFuKago_Destroy,
    (ActorFunc)EnFuKago_Update,
    (ActorFunc)EnFuKago_Draw,
};

static ColliderSphereInit sSphereInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_NONE,
        OC1_ON | OC1_NO_PUSH | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_SPHERE,
    },
    {
        ELEMTYPE_UNK4,
        { 0xF7CFFFFF, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 0, { { 0, 0, 0 }, 200 }, 100 },
};

Gfx* D_80AD061C[] = {
    object_fu_mato_DL_0006A0, object_fu_mato_DL_000740, object_fu_mato_DL_0007E0,
    object_fu_mato_DL_000880, object_fu_mato_DL_000920, object_fu_mato_DL_0009C0,
};

Vec3f D_80AD0634[] = {
    { -1.0f, 0.5f, 1.73f }, { 1.0f, 0.5f, 1.73f },   { 2.0f, 0.5f, 0.0f },
    { 1.0f, 0.5f, -1.73f }, { -1.0f, 0.5f, -1.73f }, { -2.0f, 0.5f, 0.0f },
};

Vec3f D_80AD067C[] = {
    { -0.5f, 0.5f, 0.87f }, { 0.5f, 0.5f, 0.87f },   { 1.0f, 0.5f, 0.0f },
    { 0.5f, 0.5f, -0.87f }, { -0.5f, 0.5f, -0.87f }, { -1.0f, 0.5f, 0.0f },
};

Vec3f D_80AD06C4[] = {
    { -13.7f, 9.0f, 15.5f }, { 13.7f, 9.0f, 15.5f },   { 13.7f, 9.0f, 0.0f },
    { 13.7f, 9.0f, -15.5f }, { -13.7f, 9.0f, -15.5f }, { -13.7f, 9.0f, 0.0f },
};

void EnFuKago_Init(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFuKago* this = THIS;
    CollisionHeader* sp34 = NULL;
    Actor* npc = globalCtx->actorCtx.actorLists[ACTORCAT_NPC].first;

    DynaPolyActor_Init(&this->dyna, 1);
    CollisionHeader_GetVirtual(&object_fu_mato_Colheader_0015C0, &sp34);
    this->dyna.bgId = DynaPoly_SetBgActor(globalCtx, &globalCtx->colCtx.dyna, &this->dyna.actor, sp34);
    Actor_SetScale(&this->dyna.actor, 0.1f);

    while (npc != NULL) {
        if (npc->id == ACTOR_EN_FU) {
            this->dyna.actor.parent = npc;
            break;
        }
        npc = npc->next;
    }

    if (npc == NULL) {
        Actor_MarkForDeath(&this->dyna.actor);
        return;
    }

    Collider_InitSphere(globalCtx, &this->collider);
    Collider_SetSphere(globalCtx, &this->collider, &this->dyna.actor, &sSphereInit);
    this->collider.dim.worldSphere.radius = 10;
    this->unk_33A = 0;
    this->unk_33C = 0;
    this->dyna.actor.colChkInfo.health = 1;
    func_80ACF994(this);
}

void EnFuKago_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnFuKago* this = THIS;

    DynaPoly_DeleteBgActor(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

s32 func_80ACF8B8(EnFuKago* this, GlobalContext* globalCtx) {
    this->collider.dim.worldSphere.center.x = this->dyna.actor.world.pos.x;
    this->collider.dim.worldSphere.center.y = this->dyna.actor.world.pos.y + 10.0f;
    this->collider.dim.worldSphere.center.z = this->dyna.actor.world.pos.z;

    if (this->collider.base.ocFlags1 & OC1_HIT) {
        this->collider.base.ocFlags1 &= ~OC1_HIT;

        if (this->collider.base.oc->id == ACTOR_EN_BOM) {
            this->dyna.actor.child = this->collider.base.oc;
        } else if (this->collider.base.oc->id == ACTOR_PLAYER) {
            func_80ACFA78(this, globalCtx);
            return false;
        } else {
            return false;
        }

        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_SY_TRE_BOX_APPEAR);
        return true;
    } else {
        CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
    }
    return false;
}

void func_80ACF994(EnFuKago* this) {
    this->actionFunc = func_80ACF9A8;
}

void func_80ACF9A8(EnFuKago* this, GlobalContext* globalCtx) {
    if (func_80ACF8B8(this, globalCtx)) {
        func_80ACF9DC(this);
    }
}

void func_80ACF9DC(EnFuKago* this) {
    EnBom* bom = (EnBom*)this->dyna.actor.child;

    bom->timer = 20;
    this->actionFunc = func_80ACF9FC;
}

void func_80ACF9FC(EnFuKago* this, GlobalContext* globalCtx) {
    EnBom* bom = (EnBom*)this->dyna.actor.child;
    EnFu* fu = (EnFu*)this->dyna.actor.parent;

    if (this->dyna.actor.child->update == NULL) {
        this->dyna.actor.child = NULL;
        func_80ACF994(this);
    } else if (bom->timer == 1) {
        fu->unk_548++;
        func_80ACFA78(this, globalCtx);
    } else {
        this->dyna.actor.child->world.pos.x = this->dyna.actor.world.pos.x;
        this->dyna.actor.child->world.pos.z = this->dyna.actor.world.pos.z;
    }
}

void func_80ACFA78(EnFuKago* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp98;
    Vec3s sp90;
    Vec3s sp88 = { 0, 0, 0 };
    EnFuKagoStruct* ptr;
    s16 y;

    this->dyna.actor.colChkInfo.health = 0;
    sp98 = this->dyna.actor.world.pos;
    sp90 = this->dyna.actor.shape.rot;

    ptr = &this->unk_1B8[0];
    y = sp90.y;

    for (i = 0; i < ARRAY_COUNT(this->unk_1B8); i++) {
        ptr->unk_00 = sp98;
        ptr->unk_30 = sp88;

        ptr->unk_0C.x = (Math_CosS(y) * D_80AD0634[i].x) + (Math_SinS(y) * D_80AD0634[i].z);
        ptr->unk_0C.y = D_80AD0634[i].y + Rand_Centered();
        ptr->unk_0C.z = (Math_CosS(y) * D_80AD0634[i].z) - (Math_SinS(y) * D_80AD0634[i].x);

        ptr->unk_18.x = (Math_CosS(y) * D_80AD067C[i].x) + (Math_SinS(y) * D_80AD067C[i].z);
        ptr->unk_18.y = D_80AD067C[i].y;
        ptr->unk_18.z = (Math_CosS(y) * D_80AD067C[i].z) - (Math_SinS(y) * D_80AD067C[i].x);

        ptr->unk_36.x = (s16)Rand_Next() >> 5;
        ptr->unk_36.y = 0;
        ptr->unk_36.z = (s16)Rand_Next() >> 5;

        ptr->unk_24.x = D_80AD06C4[i].x;
        ptr->unk_24.y = D_80AD06C4[i].y;
        ptr->unk_24.z = D_80AD06C4[i].z;

        ptr->unk_3C = 0;

        ptr->unk_00.x += 18.0f * ptr->unk_0C.x;
        ptr->unk_00.y += 18.0f * ptr->unk_0C.y;
        ptr->unk_00.z += 18.0f * ptr->unk_0C.z;

        ptr++;
    }

    this->dyna.actor.freezeTimer = 2;
    EffectSsHahen_SpawnBurst(globalCtx, &this->dyna.actor.world.pos, 17.0f, 0, 15, 13, 20, -1, 10, NULL);

    this->unk_338 = 60;
    this->unk_33A = 1;

    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WOODBOX_BREAK);
    func_800C62BC(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
    this->actionFunc = func_80AD0028;
}

Vec3f D_80AD0714 = { 0.0f, 0.0f, 0.0f };

void func_80ACFDAC(EnFuKago* this, GlobalContext* globalCtx, EnFuKagoStruct* arg2) {
    Vec3f sp34;
    f32 temp_f0;

    if (arg2->unk_3C == 0) {
        if (arg2->unk_00.y < 15.0f) {
            sp34 = arg2->unk_00;
            sp34.y = 30.0f;
            EffectSsGSplash_Spawn(globalCtx, &sp34, NULL, NULL, 0, 800);
            EffectSsGRipple_Spawn(globalCtx, &sp34, 250, 650, 0);
            arg2->unk_3C = 1;
        }

        Math_SmoothStepToF(&arg2->unk_18.x, 0.0f, 0.1f, 0.1f, 0.1f);
        Math_SmoothStepToF(&arg2->unk_18.y, -1.0f, 0.1f, 0.1f, 0.1f);
        Math_SmoothStepToF(&arg2->unk_18.z, 0.0f, 0.1f, 0.1f, 0.1f);
        return;
    }

    temp_f0 = Math_Vec3f_DistXZ(&arg2->unk_00, &D_80AD0714);

    arg2->unk_18.y = ((15.0f - arg2->unk_00.y) * 0.1f) - (0.2f * arg2->unk_0C.y);
    arg2->unk_18.x = arg2->unk_0C.x * -0.1f;
    arg2->unk_18.z = arg2->unk_0C.z * -0.1f;

    if (temp_f0 < 190.0f) {
        arg2->unk_00.x *= 190.0f / temp_f0;
        arg2->unk_00.z *= 190.0f / temp_f0;
    }

    if (ABS_ALT(arg2->unk_36.x) > 100) {
        Math_SmoothStepToS(&arg2->unk_36.x, 0, 0xA, 0x64, 0xA);
    }

    if (ABS_ALT(arg2->unk_36.z) > 100) {
        Math_SmoothStepToS(&arg2->unk_36.z, 0, 0xA, 0x64, 0xA);
    }

    if ((globalCtx->gameplayFrames % 8) == 0) {
        sp34 = arg2->unk_00;
        sp34.y = 30.0f;
        EffectSsGRipple_Spawn(globalCtx, &sp34, 250, 650, 0);
    }
}

void func_80AD0028(EnFuKago* this, GlobalContext* globalCtx) {
    EnFuKagoStruct* ptr = this->unk_1B8;
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_1B8); i++) {
        func_80ACFDAC(this, globalCtx, ptr);

        ptr->unk_0C.x += ptr->unk_18.x;
        ptr->unk_0C.y += ptr->unk_18.y;
        ptr->unk_0C.z += ptr->unk_18.z;

        ptr->unk_00.x += ptr->unk_0C.x;
        ptr->unk_00.y += ptr->unk_0C.y;
        ptr->unk_00.z += ptr->unk_0C.z;

        ptr->unk_30.x += ptr->unk_36.x;
        ptr->unk_30.y += ptr->unk_36.y;
        ptr->unk_30.z += ptr->unk_36.z;

        ptr++;
    }

    if (this->unk_338 == 59) {
        this->unk_1B8[3].unk_0C.x *= -1.0f;
        this->unk_1B8[3].unk_0C.z *= -1.0f;

        this->unk_1B8[4].unk_0C.x *= -1.0f;
        this->unk_1B8[4].unk_0C.z *= -1.0f;
    } else if (this->unk_338 == 58) {
        Vec3f sp34 = this->unk_1B8[5].unk_0C;

        this->unk_1B8[5].unk_0C.x = sp34.z;
        this->unk_1B8[5].unk_0C.z = -sp34.x;

        sp34 = this->unk_1B8[2].unk_0C;
        this->unk_1B8[2].unk_0C.x = -sp34.z;
        this->unk_1B8[2].unk_0C.z = sp34.x;

        this->unk_1B8[5].unk_36.x *= -1;
        this->unk_1B8[5].unk_36.y *= -1;
        this->unk_1B8[5].unk_36.z *= -1;

        this->unk_1B8[2].unk_36.x *= -1;
        this->unk_1B8[2].unk_36.y *= -1;
        this->unk_1B8[2].unk_36.z *= -1;
    } else if (this->unk_338 == 0) {
        func_80AD0274(this);
    }
    this->unk_338--;
}

void func_80AD0274(EnFuKago* this) {
    this->actionFunc = func_80AD0288;
}

void func_80AD0288(EnFuKago* this, GlobalContext* globalCtx) {
    s32 pad;
    Vec3f* scale = &this->dyna.actor.scale;

    Math_SmoothStepToF(&scale->x, 0.0f, 0.1f, 0.005f, 0.005f);
    scale->z = scale->x;
    scale->y = scale->x;
    if (scale->x == 0.0f) {
        Actor_MarkForDeath(&this->dyna.actor);
    }
}

void EnFuKago_Update(Actor* thisx, GlobalContext* globalCtx) {
    EnFuKago* this = THIS;

    this->actionFunc(this, globalCtx);

    if (this->unk_33C == 1) {
        func_80AD0274(this);
    }
}

void func_80AD0340(EnFuKago* this, GlobalContext* globalCtx) {
    s32 pad[2];
    EnFuKagoStruct* ptr = &this->unk_1B8[0];
    s32 i;
    Vec3f* scale = &this->dyna.actor.scale;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);

    for (i = 0; i < ARRAY_COUNT(D_80AD061C); i++, ptr++) {
        Matrix_StatePush();
        Matrix_SetStateRotationAndTranslation(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, &this->dyna.actor.shape.rot);
        Matrix_InsertTranslation(ptr->unk_24.x, ptr->unk_24.y, ptr->unk_24.z, MTXMODE_APPLY);
        Matrix_InsertRotation(ptr->unk_30.x, ptr->unk_30.y, ptr->unk_30.z, MTXMODE_APPLY);
        Matrix_InsertTranslation(-ptr->unk_24.x, -ptr->unk_24.y, -ptr->unk_24.z, MTXMODE_APPLY);
        Matrix_Scale(scale->x, scale->y, scale->z, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, D_80AD061C[i]);

        Matrix_StatePop();
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnFuKago_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnFuKago* this = THIS;

    if (this->unk_33A == 0) {
        OPEN_DISPS(globalCtx->state.gfxCtx);

        func_8012C28C(globalCtx->state.gfxCtx);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_0006A0);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_000740);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_0007E0);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_000880);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_000920);
        gSPDisplayList(POLY_OPA_DISP++, object_fu_mato_DL_0009C0);

        CLOSE_DISPS(globalCtx->state.gfxCtx);
    } else {
        func_80AD0340(this, globalCtx);
    }
}
