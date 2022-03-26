/*
 * File: z_obj_bigicicle.c
 * Overlay: ovl_Obj_Bigicicle
 * Description: Large icicles
 */

#include "z_obj_bigicicle.h"
#include "overlays/actors/ovl_Obj_Ice_Poly/z_obj_ice_poly.h"
#include "objects/object_bigicicle/object_bigicicle.h"

#define FLAGS 0x00000000

#define THIS ((ObjBigicicle*)thisx)

void ObjBigicicle_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjBigicicle_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80AE8FD4(ObjBigicicle* this, GlobalContext* globalCtx);
void func_80AE9090(ObjBigicicle* this, GlobalContext* globalCtx);
void func_80AE9180(ObjBigicicle* this, GlobalContext* globalCtx);
void func_80AE9258(ObjBigicicle* this, GlobalContext* globalCtx);
void func_80AE939C(ObjBigicicle* this, GlobalContext* globalCtx);

const ActorInit Obj_Bigicicle_InitVars = {
    ACTOR_OBJ_BIGICICLE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BIGICICLE,
    sizeof(ObjBigicicle),
    (ActorFunc)ObjBigicicle_Init,
    (ActorFunc)ObjBigicicle_Destroy,
    (ActorFunc)ObjBigicicle_Update,
    (ActorFunc)ObjBigicicle_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00003820, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 23, 68, -40, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_HARD,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 31, 90, -150, { 0, 0, 0 } },
};

AnimatedMaterial* D_80AE9878 = object_bigicicle_Matanimheader_001678;

Vec3f D_80AE987C = { 0.0f, -1.0f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(gravity, -2, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 5600, ICHAIN_STOP),
};

s32 D_80AE9890 = false;

Color_RGBA8 D_80AE9894 = { 250, 250, 250, 255 };
Color_RGBA8 D_80AE9898 = { 180, 180, 180, 255 };

Gfx* D_80AE989C[] = { object_bigicicle_DL_001D10, object_bigicicle_DL_002530, object_bigicicle_DL_002C20 };

Gfx* D_80AE98A8[] = {
    object_bigicicle_DL_000B20,
    object_bigicicle_DL_000D60,
    object_bigicicle_DL_000F40,
};

void ObjBigicicle_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjBigicicle* this = THIS;
    f32 sp30;
    s32 sp28;

    Actor_ProcessInitChain(&this->actor, sInitChain);

    sp28 = OBJBIGICLE_GET_FF00(&this->actor);
    if ((sp28 == 0) || (sp28 == 0xFF)) {
        sp28 = 0x3C;
    }
    Actor_SetScale(&this->actor, sp28 * 0.001f);

    this->actor.params &= 0xFF;
    this->actor.colChkInfo.mass = MASS_IMMOVABLE;
    sp30 = sp28 * (1.0f / 60.0f);

    Collider_InitAndSetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit1);
    this->collider1.dim.radius = this->collider1.dim.radius * sp30;
    this->collider1.dim.height = this->collider1.dim.height * sp30;
    this->collider1.dim.yShift = this->collider1.dim.yShift * sp30;

    Collider_InitAndSetCylinder(globalCtx, &this->collider2, &this->actor, &sCylinderInit2);
    this->collider2.dim.radius = this->collider2.dim.radius * sp30;
    this->collider2.dim.height = this->collider2.dim.height * sp30;
    this->collider2.dim.yShift = this->collider2.dim.yShift * sp30;

    if (Flags_GetSwitch(globalCtx, this->actor.params)) {
        Actor_MarkForDeath(&this->actor);
        return;
    }

    this->unk_148 = this->actor.shape.rot.x;
    this->actor.shape.rot.x = 0x4000;

    Collider_UpdateCylinder(&this->actor, &this->collider1);
    Collider_UpdateCylinder(&this->actor, &this->collider2);

    if (!D_80AE9890) {
        D_80AE9878 = Lib_SegmentedToVirtual(D_80AE9878);
        D_80AE9890 = true;
    }

    this->unk_149 = 0;
    this->actionFunc = func_80AE8FD4;
}

void ObjBigicicle_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjBigicicle* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->collider1);
    Collider_DestroyCylinder(globalCtx, &this->collider2);
}

void func_80AE8DE4(ObjBigicicle* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp98;
    Vec3f sp8C;
    f32 temp_f20 = this->actor.scale.x * (50.0f / 3.0f);

    for (i = 0; i < 10; i++) {
        sp98.x = (randPlusMinusPoint5Scaled(4.0f) * temp_f20) + this->actor.world.pos.x;
        sp98.y = ((Rand_ZeroFloat(20.0f) - 35.0f) * temp_f20) + this->actor.world.pos.y;
        sp98.z = (randPlusMinusPoint5Scaled(4.0f) * temp_f20) + this->actor.world.pos.z;

        sp8C.x = randPlusMinusPoint5Scaled(13.0f);
        sp8C.y = Rand_ZeroFloat(2.0f);
        sp8C.z = randPlusMinusPoint5Scaled(13.0f);

        EffectSsHahen_Spawn(globalCtx, &sp98, &sp8C, &D_80AE987C, 2, (Rand_ZeroFloat(20.0f) + 30.0f) * temp_f20,
                            OBJECT_BIGICICLE, 0x28, object_bigicicle_DL_0009B0);
    }

    sp98.x = this->actor.world.pos.x;
    sp98.y = this->actor.world.pos.y - (25.0f * temp_f20);
    sp98.z = this->actor.world.pos.z;

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &sp98, 40, NA_SE_EV_ICE_PIECE);
}

void func_80AE8FD4(ObjBigicicle* this, GlobalContext* globalCtx) {
    if ((this->collider1.base.acFlags & AC_HIT) ||
        ((this->collider2.base.acFlags & AC_HIT) && (this->collider2.info.acHitInfo->toucher.dmgFlags & 0x3820))) {
        if ((this->unk_148 == 0) || (this->unk_149 == 1)) {
            ActorCutscene_SetIntentToPlay(this->actor.cutscene);
            this->actionFunc = func_80AE9090;
            return;
        }

        func_80AE8DE4(this, globalCtx);
        this->unk_149++;
        this->unk_14A = 50;
        this->actionFunc = func_80AE9180;
    }
}

void func_80AE9090(ObjBigicicle* this, GlobalContext* globalCtx) {
    if (ActorCutscene_GetCanPlayNext(this->actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->actor.cutscene, &this->actor);
        this->unk_149++;
        func_80AE8DE4(this, globalCtx);
        if (this->unk_149 == 2) {
            f32 temp_f0 = this->actor.scale.y * 2100.0f;

            this->actor.flags |= ACTOR_FLAG_10;
            this->actor.shape.yOffset = 2100.0f;
            this->actor.world.pos.y -= temp_f0;
            this->collider1.dim.yShift += (s16)temp_f0;
            this->collider2.dim.yShift += (s16)temp_f0;
            this->actionFunc = func_80AE9258;
        } else {
            this->unk_14A = 50;
            this->actionFunc = func_80AE9180;
        }
    } else {
        ActorCutscene_SetIntentToPlay(this->actor.cutscene);
    }
}

void func_80AE9180(ObjBigicicle* this, GlobalContext* globalCtx) {
    this->unk_14A--;

    if (this->unk_14A > 0) {
        this->unk_14A--;
        this->actor.shape.rot.x = BINANG_ADD((s32)(randPlusMinusPoint5Scaled(1408.0f) * 0.02f * this->unk_14A), 0x4000);
        this->actor.shape.rot.z = randPlusMinusPoint5Scaled(1408.0f) * 0.02f * this->unk_14A;
    } else {
        this->actor.shape.rot.x = 0x4000;
        this->actor.shape.rot.z = 0;
        ActorCutscene_Stop(this->actor.cutscene);
        this->actionFunc = func_80AE8FD4;
    }
}

void func_80AE9258(ObjBigicicle* this, GlobalContext* globalCtx) {
    Actor* itemAction;
    f32 temp_f0;
    ObjIcePoly* icePoly;

    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 0.0f, 0.0f, 0.0f, 4);

    itemAction = globalCtx->actorCtx.actorLists[ACTORCAT_ITEMACTION].first;

    while (itemAction != NULL) {
        if (itemAction->id == ACTOR_OBJ_ICE_POLY) {
            icePoly = (ObjIcePoly*)itemAction;
            temp_f0 = this->actor.world.pos.y - icePoly->actor.world.pos.y;
            if ((temp_f0 < icePoly->colliders1[0].dim.height) && (temp_f0 > 0.0f) &&
                (Actor_XZDistanceBetweenActors(&this->actor, &icePoly->actor) < icePoly->colliders1[0].dim.radius)) {
                Flags_SetSwitch(globalCtx, this->actor.params);
                this->actionFunc = func_80AE939C;
                return;
            }
        }
        itemAction = itemAction->next;
    }

    if (this->actor.bgCheckFlags & 1) {
        this->actionFunc = func_80AE939C;
    } else {
        Collider_UpdateCylinder(&this->actor, &this->collider1);
        Collider_UpdateCylinder(&this->actor, &this->collider2);
    }
}

void func_80AE939C(ObjBigicicle* this, GlobalContext* globalCtx) {
    s32 i;
    Vec3f sp98;
    Vec3f sp8C;
    f32 temp_f20 = this->actor.scale.x * (50.0f / 3.0f);

    for (i = 0; i < 20; i++) {
        sp8C.x = randPlusMinusPoint5Scaled(15.0f);
        sp8C.y = Rand_ZeroFloat(7.0f) + 3.0f;
        sp8C.z = randPlusMinusPoint5Scaled(15.0f);

        sp98.x = this->actor.world.pos.x + (sp8C.x * 5.0f * temp_f20);
        sp98.y = this->actor.world.pos.y + (sp8C.y * 7.0f * temp_f20);
        sp98.z = this->actor.world.pos.z + (sp8C.z * 5.0f * temp_f20);

        EffectSsHahen_Spawn(globalCtx, &sp98, &sp8C, &D_80AE987C, 2, (Rand_ZeroFloat(30.0f) + 40.0f) * temp_f20,
                            OBJECT_BIGICICLE, 30, object_bigicicle_DL_0009B0);
    }

    SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 40, NA_SE_EV_GLASSBROKEN_IMPACT);
    ActorCutscene_Stop(this->actor.cutscene);
    Actor_MarkForDeath(&this->actor);
}

void ObjBigicicle_Update(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    ObjBigicicle* this = THIS;
    Vec3f sp44;

    this->actionFunc(this, globalCtx);

    if (Rand_ZeroOne() < 0.05f) {
        sp44.x = (((215.0f + Rand_ZeroFloat(65.0f)) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1)) * this->actor.scale.x) +
                 this->actor.world.pos.x;
        sp44.y = ((((Rand_ZeroFloat(1400.0f) + -150.0f) - 2100.0f) + this->actor.shape.yOffset) * this->actor.scale.y) +
                 this->actor.world.pos.y;
        sp44.z = (((215.0f + Rand_ZeroFloat(65.0f)) * ((Rand_ZeroOne() < 0.5f) ? -1 : 1)) * this->actor.scale.z) +
                 this->actor.world.pos.z;

        EffectSsKiraKira_SpawnDispersed(globalCtx, &sp44, &gZeroVec3f, &gZeroVec3f, &D_80AE9894, &D_80AE9898, 2000, 5);
    }

    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
    CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
}

void ObjBigicicle_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjBigicicle* this = THIS;

    Gfx_DrawDListXlu(globalCtx, D_80AE989C[this->unk_149]);
    Gfx_DrawDListXlu(globalCtx, D_80AE98A8[this->unk_149]);
    AnimatedMat_Draw(globalCtx, D_80AE9878);
    Gfx_DrawDListXlu(globalCtx, object_bigicicle_DL_0014F0);
}
