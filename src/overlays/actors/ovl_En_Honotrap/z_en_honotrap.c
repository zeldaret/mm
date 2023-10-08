/*
 * File: z_en_honotrap.c
 * Overlay: ovl_En_Honotrap
 * Description: Eye switch that shoots fire
 */

#include "z_en_honotrap.h"
#include "assets/objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((EnHonotrap*)thisx)

void EnHonotrap_Init(Actor* thisx, PlayState* play);
void EnHonotrap_Destroy(Actor* thisx, PlayState* play);
void EnHonotrap_Update(Actor* thisx, PlayState* play);
void EnHonotrap_Draw(Actor* thisx, PlayState* play);

void func_8092E5A4(Vec3f* arg0, Vec3f* arg1);
void func_8092E638(EnHonotrap* this, PlayState* play);
void func_8092E840(EnHonotrap* this, PlayState* play);
void func_8092E988(EnHonotrap* this, PlayState* play);
void func_8092EBC0(EnHonotrap* this);
void func_8092EBDC(EnHonotrap* this, PlayState* play);
void func_8092EC9C(EnHonotrap* this);
void func_8092ECF0(EnHonotrap* this, PlayState* play);
void func_8092EDC0(EnHonotrap* this);
void func_8092EDD8(EnHonotrap* this, PlayState* play);
void func_8092EE08(EnHonotrap* this);
void func_8092EE1C(EnHonotrap* this, PlayState* play);
void func_8092EE68(EnHonotrap* this);
void func_8092EE90(EnHonotrap* this, PlayState* play);
void func_8092EF3C(EnHonotrap* this);
void func_8092EF98(EnHonotrap* this, PlayState* play);
void func_8092F05C(EnHonotrap* this);
void func_8092F074(EnHonotrap* this, PlayState* play);
void func_8092F0A4(EnHonotrap* this);
void func_8092F0B8(EnHonotrap* this, PlayState* play);
void func_8092F0F8(EnHonotrap* this);
void func_8092F10C(EnHonotrap* this, PlayState* play);
void func_8092F1A0(EnHonotrap* this);
void func_8092F208(EnHonotrap* this, PlayState* play);
void func_8092F34C(EnHonotrap* this);
void func_8092F3D8(EnHonotrap* this, PlayState* play);
void func_8092F5AC(EnHonotrap* this);
void func_8092F5EC(EnHonotrap* this, PlayState* play);
void func_8092F7A8(EnHonotrap* this);
void func_8092F7BC(EnHonotrap* this, PlayState* play);
void func_8092F854(EnHonotrap* this);
void func_8092F878(EnHonotrap* this, PlayState* play);
void func_8092FE44(Actor* thisx, PlayState* play);
void func_8092FEFC(Actor* thisx, PlayState* play);
void func_80930030(Actor* thisx, PlayState* play);
void func_80930190(Actor* thisx, PlayState* play);

extern Gfx D_050085F0;

#if 0
ActorInit En_Honotrap_InitVars = {
    ACTOR_EN_HONOTRAP,
    ACTORCAT_PROP,
    FLAGS,
    GAMEPLAY_DANGEON_KEEP,
    sizeof(EnHonotrap),
    (ActorFunc)EnHonotrap_Init,
    (ActorFunc)EnHonotrap_Destroy,
    (ActorFunc)EnHonotrap_Update,
    (ActorFunc)EnHonotrap_Draw,
};

// static ColliderTrisElementInit sTrisElementsInit[2] = {
static ColliderTrisElementInit D_80930424[2] = {
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { -23.0f, 0.0f, 8.5f }, { 0.0f, -23.0f, 8.5f } } },
    },
    {
        { ELEMTYPE_UNK4, { 0x00000000, 0x00, 0x00 }, { 0x00003820, 0x00, 0x00 }, TOUCH_NONE | TOUCH_SFX_NORMAL, BUMP_ON, OCELEM_NONE, },
        { { { 0.0f, 23.0f, 8.5f }, { 0.0f, -23.0f, 8.5f }, { 23.0f, 0.0f, 8.5f } } },
    },
};

// static ColliderTrisInit sTrisInit = {
static ColliderTrisInit D_8093049C = {
    { COLTYPE_NONE, AT_NONE, AC_ON | AC_TYPE_PLAYER, OC1_NONE, OC2_NONE, COLSHAPE_TRIS, },
    ARRAY_COUNT(sTrisElementsInit), D_80930424, // sTrisElementsInit,
};

// static ColliderCylinderInit sCylinderInit = {
static ColliderCylinderInit D_809304AC = {
    { COLTYPE_NONE, AT_ON | AT_TYPE_ENEMY, AC_ON | AC_TYPE_PLAYER, OC1_ON | OC1_TYPE_ALL, OC2_TYPE_2, COLSHAPE_CYLINDER, },
    { ELEMTYPE_UNK0, { 0xF7CFFFFF, 0x01, 0x04 }, { 0x00100000, 0x00, 0x00 }, TOUCH_ON | TOUCH_SFX_NONE, BUMP_ON, OCELEM_ON, },
    { 10, 25, 0, { 0, 0, 0 } },
};

// sColChkInfoInit
static CollisionCheckInfoInit D_809304D8 = { 0, 9, 23, 1 };

// static InitChainEntry sInitChain[] = {
static InitChainEntry D_809304E0[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_STOP),
};

#endif
extern Gfx* D_809303F0[4];
extern s32 D_80930400;
extern ColliderTrisElementInit D_80930424[2];
extern ColliderTrisInit D_8093049C;
extern ColliderCylinderInit D_809304AC;
extern CollisionCheckInfoInit D_809304D8;
extern InitChainEntry D_809304E0[];

void func_8092E510(EnHonotrap* this, PlayState* play) {
    s32 pad[3];

    Collider_UpdateCylinder(&this->actor, &this->collider.cyl);
    CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.tris.base);
    CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.tris.base);
    CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.tris.base);
    this->unk2C0 |= 1;
    this->unk2C0 |= 2;
    this->unk2C0 |= 4;
}

void func_8092E5A4(Vec3f* arg0, Vec3f* arg1) {
    f32 temp_fv0;
    f32 temp_fv1;

    temp_fv0 = Math3D_Vec3fMagnitude(arg1);
    if (temp_fv0 < 0.001f) {
        arg0->x = arg0->y = 0.0f;
        arg0->z = 1.0f;
        return;
    }
    temp_fv1 = 1.0f / temp_fv0;
    arg0->x = arg1->x * temp_fv1;
    arg0->y = arg1->y * temp_fv1;
    arg0->z = arg1->z * temp_fv1;
}

// EnHonotrap_InitEye
void func_8092E638(EnHonotrap* this, PlayState* play) {
    s32 i;
    s32 j;
    s32 k;
    f32 sin;
    f32 cos;
    Vec3f sp70[3];
    Vec3f* vtx;

    sin = Math_SinS(this->actor.home.rot.y);
    cos = Math_CosS(this->actor.home.rot.y);
    Actor_SetScale(&this->actor, 0.1f);

    if (D_80930400 != 0) {
        D_80930400 = 0;
        for (k = 0; k < 4; k++) {
            D_809303F0[k] = Lib_SegmentedToVirtual(D_809303F0[k]);
        }
    }

    Collider_InitTris(play, &this->collider.tris);
    Collider_SetTris(play, &this->collider.tris, &this->actor, &D_8093049C, this->collider.elements);

    for (i = 0; i < 2; i++) {
        for (j = 0, vtx = sp70; j < 3; j++, vtx++) {
            Vec3f* test = &D_8093049C.elements[i].dim.vtx[j];

            vtx->x = (test->z * sin) + (test->x * cos);
            vtx->y = test->y;
            vtx->z = (test->z * cos) - (test->x * sin);

            Math_Vec3f_Sum(vtx, &this->actor.world.pos, vtx);
        }
        Collider_SetTrisVertices(&this->collider.tris, i, &sp70[0], &sp70[1], &sp70[2]);
    }
    Actor_SetFocus(&this->actor, 0.0f);
    if (this->actor.params == 0) {
        func_8092EBC0(this);
    } else {
        func_8092EE68(this);
    }
}

// EnHonotrap_InitFlame
void func_8092E840(EnHonotrap* this, PlayState* play) {
    s32 pad[2];
    s32 params;

    params = this->actor.params;
    Actor_SetScale(&this->actor, 0.0001f);
    Collider_InitCylinder(play, &this->collider.cyl);
    Collider_SetCylinder(play, &this->collider.cyl, &this->actor, &D_809304AC);
    Collider_UpdateCylinder(&this->actor, &this->collider.cyl);
    this->actor.terminalVelocity = -1.0f;
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_809304D8);
    ActorShape_Init(&this->actor.shape, 0.0f, ActorShadow_DrawCircle, 30.0f);
    this->actor.shape.shadowAlpha = 0x80;
    this->unk228 = GET_PLAYER(play)->actor.world.pos;
    this->unk228.y += 10.0f;
    this->unk23A = Rand_ZeroOne() * 511.0f;
    Actor_PlaySfx(&this->actor, NA_SE_EV_FLAME_IGNITION);
    if (params == 2) {
        this->actor.room = -1;
        this->collider.cyl.dim.radius = 12;
        this->collider.cyl.dim.height = 30;
        this->actor.shape.yOffset = -1000.0f;
    }
    func_8092F0F8(this);
}

void func_8092E988(EnHonotrap* this, PlayState* play) {
    EnHonotrap23C* var_s2;
    s32 var_s0;
    s32 i;

    Actor_SetScale(&this->actor, 0.0001f);
    Collider_InitCylinder(play, &this->collider.cyl);
    Collider_SetCylinder(play, &this->collider.cyl, &this->actor, &D_809304AC);
    CollisionCheck_SetInfo(&this->actor.colChkInfo, NULL, &D_809304D8);

    var_s0 = Rand_ZeroOne() * 511.0f;
    var_s2 = &this->unk23C;
    for (i = 0; i < 6; i++) {
        var_s2->unkC[i].unk_10 = var_s0;
        var_s0 += (s32)Rand_ZeroFloat(300.0f) + 0x64;
        var_s0 &= 0x1FF;
    }

    Actor_PlaySfx(&this->actor, NA_SE_EV_FLAME_IGNITION);
    func_8092F854(this);
}

void EnHonotrap_Init(Actor* thisx, PlayState* play) {
    s32 params;
    EnHonotrap* this = (EnHonotrap*)thisx;

    params = this->actor.params;
    Actor_ProcessInitChain(&this->actor, D_809304E0);
    if ((params == 0) || (params == 3)) {
        func_8092E638(this, play);
    } else if (params == 4) {
        func_8092E988(this, play);
        this->actor.update = func_8092FEFC;
        this->actor.draw = func_80930190;
        this->actor.uncullZoneScale = 500.0f;
        this->actor.uncullZoneDownward = 500.0f;
    } else {
        func_8092E840(this, play);
        this->actor.update = func_8092FE44;
        this->actor.draw = func_80930030;
    }
}

void EnHonotrap_Destroy(Actor* thisx, PlayState* play) {
    s16 params;
    EnHonotrap* this = (EnHonotrap*)thisx;

    params = this->actor.params;
    if ((params == 0) || (params == 3)) {
        Collider_DestroyTris(play, &this->collider.tris);
    } else {
        Collider_DestroyCylinder(play, &this->collider.cyl);
    }
}

void func_8092EBC0(EnHonotrap* this) {
    this->actionFunc = func_8092EBDC;
    this->unk222 = 3;
}

void func_8092EBDC(EnHonotrap* this, PlayState* play) {
    f32 temp_fv0;
    s16 temp_v0;

    if (this->actor.child != NULL) {
        this->unk220 = 0xC8;
        return;
    }
    if ((this->unk220 <= 0) && (this->actor.xzDistToPlayer < 750.0f)) {
        temp_fv0 = this->actor.playerHeightRel;
        if ((temp_fv0 < 0.0f) && (temp_fv0 > -700.0f)) {
            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            if ((temp_v0 >= -0x3FFF) && (temp_v0 < 0x4000)) {
                func_8092EC9C(this);
            }
        }
    }
}

void func_8092EC9C(EnHonotrap* this) {
    this->actionFunc = func_8092ECF0;
    Actor_SetColorFilter(&this->actor, 0x4000, 255, 0, 40);
    this->unk220 = 30;
    Actor_PlaySfx(&this->actor, NA_SE_EV_RED_EYE);
}

void func_8092ECF0(EnHonotrap* this, PlayState* play) {
    this->unk222 -= 1;
    if (this->unk222 <= 0) {
        func_8092EDC0(this);
        Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HONOTRAP,
                           (Math_SinS(this->actor.shape.rot.y) * 12.0f) + this->actor.home.pos.x,
                           this->actor.home.pos.y - 10.0f,
                           (Math_CosS(this->actor.shape.rot.y) * 12.0f) + this->actor.home.pos.z,
                           this->actor.home.rot.x, this->actor.home.rot.y, this->actor.home.rot.z, 1);
    }
}

void func_8092EDC0(EnHonotrap* this) {
    this->actionFunc = func_8092EDD8;
    this->unk222 = 0;
}

void func_8092EDD8(EnHonotrap* this, PlayState* play) {
    if (this->unk220 <= 0) {
        func_8092EE08(this);
    }
}

void func_8092EE08(EnHonotrap* this) {
    this->actionFunc = func_8092EE1C;
}

void func_8092EE1C(EnHonotrap* this, PlayState* play) {
    this->unk222 += 1;
    if (this->unk222 >= 3) {
        func_8092EBC0(this);
        this->unk220 = 200;
    }
}

void func_8092EE68(EnHonotrap* this) {
    this->unk222 = 3;
    this->unk220 = 0x50;
    this->unk224 = 0;
    this->actionFunc = func_8092EE90;
}

void func_8092EE90(EnHonotrap* this, PlayState* play) {
    f32 temp_fv0;
    s16 temp_v0;

    if ((this->unk220 <= 0) && (this->actor.xzDistToPlayer < 120.0f)) {
        temp_fv0 = this->actor.playerHeightRel;
        if ((temp_fv0 < 0.0f) && (temp_fv0 > -700.0f)) {
            temp_v0 = this->actor.yawTowardsPlayer - this->actor.shape.rot.y;
            if ((temp_v0 >= -0x3FFF) && (temp_v0 < 0x4000)) {
                func_8092EF3C(this);
            }
        }
    }
}

void func_8092EF3C(EnHonotrap* this) {
    Actor_PlaySfx(&this->actor, 0x2881U);
    Actor_SetColorFilter(&this->actor, 0x4000U, 255, 0, 40);
    this->unk220 = 0x28;
    this->actionFunc = func_8092EF98;
}

void func_8092EF98(EnHonotrap* this, PlayState* play) {
    s32 pad;

    this->unk222 -= 1;
    if (this->unk222 <= 0) {
        Actor_SpawnAsChild(&play->actorCtx, &this->actor, play, ACTOR_EN_HONOTRAP,
                           (Math_SinS(this->actor.shape.rot.y) * 12.0f) + this->actor.home.pos.x,
                           this->actor.home.pos.y,
                           (Math_CosS(this->actor.shape.rot.y) * 12.0f) + this->actor.home.pos.z,
                           this->actor.home.rot.x, this->actor.home.rot.y, this->actor.home.rot.z, 4);
        func_8092F05C(this);
    }
}

void func_8092F05C(EnHonotrap* this) {
    this->actionFunc = func_8092F074;
    this->unk222 = 0;
}

void func_8092F074(EnHonotrap* this, PlayState* play) {
    if (this->unk220 <= 0) {
        func_8092F0A4(this);
    }
}

void func_8092F0A4(EnHonotrap* this) {
    this->actionFunc = func_8092F0B8;
}

void func_8092F0B8(EnHonotrap* this, PlayState* play) {
    this->unk222 += 1;
    if (this->unk222 >= 3) {
        func_8092EE68(this);
    }
}

void func_8092F0F8(EnHonotrap* this) {
    this->actionFunc = func_8092F10C;
}

void func_8092F10C(EnHonotrap* this, PlayState* play) {
    f32 temp_fv0;
    f32 var_fv0;
    s32 temp_v0;

    if (this->actor.params == 1) {
        var_fv0 = 0.004f;
    } else {
        var_fv0 = 0.0048f;
    }
    temp_v0 = Math_StepToF(&this->actor.scale.x, var_fv0, 0.0006f);
    temp_fv0 = this->actor.scale.x;
    this->actor.scale.y = temp_fv0;
    this->actor.scale.z = temp_fv0;
    if (temp_v0 != 0) {
        if (this->actor.params == 1) {
            func_8092F34C(this);
            return;
        }
        func_8092F1A0(this);
    }
}

void func_8092F1A0(EnHonotrap* this) {
    this->unk220 = 0x28;
    this->actor.velocity.y = 1.0f;
    this->actor.velocity.x = 2.0f * Math_SinS(this->actor.world.rot.y);
    this->actor.velocity.z = 2.0f * Math_CosS(this->actor.world.rot.y);
    this->actionFunc = func_8092F208;
}

void func_8092F208(EnHonotrap* this, PlayState* play) {
    if ((this->collider.tris.base.atFlags & 2) || (this->unk220 <= 0)) {
        if ((this->collider.tris.base.atFlags & 2) && !(this->collider.tris.base.atFlags & 4)) {
            func_800B8D98(play, &this->actor, 5.0f, this->actor.yawTowardsPlayer, 0.0f);
        }
        this->actor.velocity.z = 0.0f;
        this->actor.velocity.y = 0.0f;
        this->actor.velocity.x = 0.0f;
        func_8092F7A8(this);
        return;
    }
    if (this->actor.velocity.y > 0.0f) {
        this->actor.world.pos.x += this->actor.velocity.x;
        this->actor.world.pos.z += this->actor.velocity.z;
        Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 12.0f, 0.0f, 5U);
    }
    if (Math_StepToF(&this->actor.world.pos.y, this->actor.floorHeight + 1.0f, this->actor.velocity.y) == 0) {
        this->actor.velocity.y += 1.0f;
    } else {
        this->actor.velocity.y = 0.0f;
    }
    func_8092E510(this, play);
}

void func_8092F34C(EnHonotrap* this) {
    f32 temp_fv1;

    this->actionFunc = func_8092F3D8;
    temp_fv1 = 1.0f / (Actor_WorldDistXYZToPoint(&this->actor, &this->unk228) + 1.0f);
    this->actor.velocity.x = (this->unk228.x - this->actor.world.pos.x) * temp_fv1;
    this->actor.velocity.y = (this->unk228.y - this->actor.world.pos.y) * temp_fv1;
    this->actor.velocity.z = (this->unk228.z - this->actor.world.pos.z) * temp_fv1;
    this->unk220 = 160;
    this->unk234 = 0.0f;
}

#ifdef NON_MATCHING
void func_8092F3D8(EnHonotrap* this, PlayState* play) {
    s32 pad;
    Vec3f sp60;

    s32 temp_s1;
    Player* player;

    Vec3f sp4C;
    Vec3f sp40;
    Vec3f sp34;

    Math_StepToF(&this->unk234, 13.0f, 0.5f);
    sp60.x = fabsf(this->unk234 * this->actor.velocity.x);
    sp60.y = fabsf(this->unk234 * this->actor.velocity.y);
    sp60.z = fabsf(this->unk234 * this->actor.velocity.z);
    temp_s1 = 1;
    temp_s1 &= Math_StepToF(&this->actor.world.pos.x, this->unk228.x, sp60.x);
    temp_s1 &= Math_StepToF(&this->actor.world.pos.y, this->unk228.y, sp60.y);
    temp_s1 &= Math_StepToF(&this->actor.world.pos.z, this->unk228.z, sp60.z);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, 0x1DU);

    if (this->collider.tris.base.atFlags & 4) {
        player = GET_PLAYER(play);
        sp34.x = -player->shieldMf.xz;
        sp34.y = -player->shieldMf.yz;
        sp34.z = -player->shieldMf.zz;
        func_8092E5A4(&sp4C, &sp34);
        sp40 = this->actor.velocity;
        func_80179F64(&sp40, &sp4C, &this->actor.velocity);
        this->actor.speed = this->unk234 * 0.5f;
        this->actor.world.rot.y = Math_Atan2S_XY(this->actor.velocity.z, this->actor.velocity.x);
        func_8092F7A8(this);
        return;
    }
    if (this->collider.tris.base.atFlags & 2) {
        this->actor.speed = 0.0f;
        this->actor.velocity.y = 0.0f;
        func_8092F7A8(this);
        return;
    }
    if (this->unk220 <= 0) {
        func_8092F7A8(this);
        return;
    }
    func_8092E510(this, play);
    if (temp_s1 != 0) {
        func_8092F5AC(this);
    }
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_8092F3D8.s")
#endif

void func_8092F5AC(EnHonotrap* this) {
    this->actionFunc = func_8092F5EC;
    this->actor.speed = 0.0f;
    this->actor.velocity.x = this->actor.velocity.y = this->actor.velocity.z = 0.0f;
    this->unk220 = 100;
    this->actor.world.rot.x = this->actor.world.rot.y = this->actor.world.rot.z = 0;
}

void func_8092F5EC(EnHonotrap* this, PlayState* play) {
    s32 pad;

    Math_ScaledStepToS(&this->actor.world.rot.y, this->actor.yawTowardsPlayer, 0x300);
    Math_StepToF(&this->actor.speed, 3.0f, 0.1f);
    if (-this->actor.playerHeightRel < 10.0f) {
        this->actor.gravity = 0.08f;
    } else {
        this->actor.gravity = -0.08f;
    }
    Actor_UpdateVelocityWithGravity(&this->actor);
    if (this->actor.velocity.y > 1.0f) {
        this->actor.velocity.y = 1.0f;
    }
    this->actor.velocity.y *= 0.95f;
    Actor_UpdatePos(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, 0x1DU);

    if (this->collider.tris.base.atFlags & 4) {
        Player* player = GET_PLAYER(play);
        Vec3s sp30;

        Matrix_MtxFToYXZRot(&player->shieldMf, &sp30, 0);
        this->actor.world.rot.y = ((sp30.y * 2) - this->actor.world.rot.y) + 0x8000;
        func_8092F7A8(this);
    } else if (this->collider.tris.base.atFlags & 2) {
        this->actor.speed *= 0.1f;
        this->actor.velocity.y *= 0.1f;
        func_8092F7A8(this);
    } else if ((this->actor.bgCheckFlags & 8) || (this->unk220 <= 0)) {
        func_8092F7A8(this);
    } else {
        func_8092E510(this, play);
    }
}

void func_8092F7A8(EnHonotrap* this) {
    this->actionFunc = func_8092F7BC;
}

void func_8092F7BC(EnHonotrap* this, PlayState* play) {
    f32 temp_fv0;
    s32 sp28 = Math_StepToF(&this->actor.scale.x, 0.0001f, 0.00015f);
    temp_fv0 = this->actor.scale.x;
    this->actor.scale.y = temp_fv0;
    this->actor.scale.z = temp_fv0;
    Actor_MoveWithGravity(&this->actor);
    Actor_UpdateBgCheckInfo(play, &this->actor, 10.0f, 10.0f, 0.0f, 0x1DU);
    if (sp28 != 0) {
        Actor_Kill(&this->actor);
    }
}

void func_8092F854(EnHonotrap* this) {
    this->actionFunc = func_8092F878;
    this->unk220 = 0x50;
    this->unk23C.unk8 = 0.0f;
}

void func_8092F878(EnHonotrap* this, PlayState* play) {
    s32 var_v0;
    EnHonotrap23C* sp98;
    f32 var_fs0;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    s32 sp7C;
    s32 sp78;
    f32 var_fs0_2;
    Vec3f sp68;
    EnHonotrapArr* var_s0;

    sp98 = &this->unk23C;
    sp78 = 0;
    sp80 = fabsf(Math_CosS(Camera_GetCamDirPitch(play->cameraPtrs[play->activeCamId])));
    sp7C = (s32)(sp80 * -10.5f) - 10;
    Math_StepToF(&sp98->unk0, 1.0f, 0.05f);
    if (this->unk220 <= 40) {
        sp78 = Math_StepToF(&sp98->unk4, 1.0f, 0.05f);
    } else if (this->actor.parent == NULL) {
        this->unk220 = 40;
    }
    for (var_v0 = 0; var_v0 < 6; var_v0++) {
        sp98->unkC[var_v0].unk12 = 0;
    }

    sp88 = Math_SinS(this->actor.shape.rot.y) * 120.0f;
    sp84 = Math_CosS(this->actor.shape.rot.y) * 120.0f;

    sp98->unk8 += 0.050f * (1.0f - sp98->unk4);

    if (sp98->unk8 > 0.16666667f) {
        sp98->unk8 -= 0.16666667f;
    }
    var_fs0 = sp98->unk4 + sp98->unk8;

    for (var_v0 = 0; var_v0 < 6 && (var_fs0 <= sp98->unk0); var_v0++) {
        var_s0 = &sp98->unkC[var_v0];
        var_s0->unk12 = 1;

        var_s0->unk0.x = (f32)((sp88 * var_fs0) + this->actor.world.pos.x);
        var_s0->unk0.y = (f32)this->actor.world.pos.y;
        var_s0->unk0.z = (f32)((sp84 * var_fs0) + this->actor.world.pos.z);

        var_s0->unkC = Math_SinS((s16)(s32)(var_fs0 * 25486.223f)) * 1.6f;
        if (var_s0->unkC > 1.0f) {
            var_s0->unkC = 1.0f;
        } else if (var_s0->unkC < 0.0f) {
            var_s0->unkC = 0.0f;
        }

        var_fs0 += 0.16666667f;
        var_s0->unkC = (f32)(var_s0->unkC * (0.006f * (((1.0f - sp98->unk4) * 0.8f) + 0.2f)));
        var_s0->unk_10 = (s16)(var_s0->unk_10 + sp7C);
        var_s0->unk_10 = (s16)(var_s0->unk_10 & 0x1FF);
    }

    if ((sp78 != 0) || (this->unk220 <= 0)) {
        Actor_Kill(&this->actor);
        return;
    }
    temp_fs0 = sp98->unk0 * 120.0f;
    temp_fs1 = sp98->unk4 * 120.0f;
    Actor_OffsetOfPointInActorCoords(&this->actor, &sp68, &GET_PLAYER(play)->actor.world.pos);

    if (sp68.z < temp_fs1) {
        sp68.z = temp_fs1;
    } else if (temp_fs0 < sp68.z) {
        sp68.z = temp_fs0;
    }

    var_fs0_2 = Math_SinS((s16)(s32)(sp68.z * 212.3852f)) * 1.6f;
    if (var_fs0_2 > 1.0f) {
        var_fs0_2 = 1.0f;
    }
    sp80 *= ((1.0f - sp98->unk4) * 0.8f) + 0.2f;
    if (sp80 > 0.2f) {
        this->collider.cyl.dim.pos.x =
            (s16)(s32)((Math_SinS(this->actor.shape.rot.y) * sp68.z) + this->actor.world.pos.x);
        this->collider.cyl.dim.pos.y = (s16)(s32)(this->actor.world.pos.y - (24.0f * var_fs0_2));
        this->collider.cyl.dim.pos.z =
            (s16)(s32)((Math_CosS(this->actor.shape.rot.y) * sp68.z) + this->actor.world.pos.z);
        this->collider.cyl.dim.radius = (s16)(s32)(15.0f * var_fs0_2);
        this->collider.cyl.dim.height = (s16)(s32)(37.5f * var_fs0_2);
        CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.tris.base);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.tris.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.tris.base);
    }
}

extern Vec3f D_809304EC;
extern Vec3f D_809304F8;

void EnHonotrap_Update(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;

    if (this->unk220 > 0) {
        this->unk220 -= 1;
    }
    if ((this->actor.child != NULL) && (this->actor.child->update == NULL)) {
        this->actor.child = NULL;
    }
    this->actionFunc(this, play);
    if (this->collider.tris.base.acFlags & 2) {
        EffectSsBomb2_SpawnLayered(play, &this->actor.world.pos, &D_809304EC, &D_809304F8, 15, 8);
        Actor_Kill(&this->actor);
        return;
    }
    if (this->unk222 < 3) {
        this->collider.tris.base.acFlags &= ~AC_HIT;
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.tris.base);
    }
}

void func_8092FE44(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;

    if (this->unk220 > 0) {
        this->unk220--;
    }
    this->unk2C0 = 0;
    this->unk238 += 0x640;
    if (this->actor.params != 4) {
        this->actor.shape.yOffset = Math_SinS(this->unk238) * 1000.0f + 600.0f;
    }
    Actor_SetFocus(&this->actor, 5.0f);
    Actor_PlaySfx(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    this->actionFunc(this, play);
    this->unk23A -= 0x14;
    this->unk23A &= 0x1FF;
}

void func_8092FEFC(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;
    Actor* temp_v0;

    temp_v0 = this->actor.parent;
    if ((temp_v0 != NULL) && (temp_v0->update == NULL)) {
        this->actor.parent = NULL;
    }
    if (this->unk220 > 0) {
        this->unk220--;
    }
    this->unk238 += 0x640;
    Actor_PlaySfx(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    this->actionFunc(this, play);
}

void EnHonotrap_Draw(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, D_809303F0[this->unk222]);
    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, &D_050085F0);
    CLOSE_DISPS(play->state.gfxCtx);
}

void func_80930030(Actor* thisx, PlayState* play) {
    s32 pad;
    EnHonotrap* this = (EnHonotrap*)thisx;

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 32, 64, 1, 0, this->unk23A, 32, 128));
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 200, 0, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    Matrix_RotateYS(Camera_GetCamDirYaw(play->cameraPtrs[play->activeCamId]) + 0x8000, MTXMODE_APPLY);
    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);
    CLOSE_DISPS(play->state.gfxCtx);
}

#ifdef NON_MATCHING
void func_80930190(Actor* thisx, PlayState* play) {
    EnHonotrap* this = (EnHonotrap*)thisx;
    Vec3s spB8;
    EnHonotrapArr* temp_s0;
    EnHonotrap23C* var_s3;
    s32 i; // s4

    OPEN_DISPS(play->state.gfxCtx);
    Gfx_SetupDL25_Xlu(play->state.gfxCtx);
    gDPSetPrimColor(POLY_XLU_DISP++, 0x80, 0x80, 255, 200, 0, 255);
    gDPSetEnvColor(POLY_XLU_DISP++, 255, 0, 0, 0);
    Camera_GetCamDir(&spB8, play->cameraPtrs[play->activeCamId]);
    spB8.y += 0x8000;
    var_s3 = &this->unk23C;
    for (i = 0; i < 6; i++) {
        temp_s0 = &var_s3->unkC[i];
        if (temp_s0->unk12 != 0) {
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 0x20, 0x40, 1, 0, temp_s0->unk_10, 0x20, 0x80));
            Matrix_SetTranslateRotateYXZ(temp_s0->unk0.x, temp_s0->unk0.y - (4000.0f * temp_s0->unkC), temp_s0->unk0.z,
                                         &spB8);
            // temp_fa1 = temp_s0->unkC;
            Matrix_Scale(((fabsf(Math_SinS((s16)(spB8.y - this->actor.shape.rot.y) >> 1)) * 0.2f) + 1.7f) *
                             temp_s0->unkC,
                         temp_s0->unkC, 1.0f, MTXMODE_APPLY);
            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gEffFire1DL);
        }
    }
    CLOSE_DISPS(play->state.gfxCtx);
}
#else
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_En_Honotrap/func_80930190.s")
#endif
