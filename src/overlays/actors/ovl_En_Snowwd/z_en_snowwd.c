/*
 * File: z_en_snowwd.c
 * Overlay: ovl_En_Snowwd
 * Description: Snow-Covered Tree
 */

#include "z_en_snowwd.h"
#include "objects/object_snowwd/object_snowwd.h"

#define FLAGS 0x00000000

#define THIS ((EnSnowwd*)thisx)

void EnSnowwd_Init(Actor* thisx, PlayState* play);
void EnSnowwd_Destroy(Actor* thisx, PlayState* play);
void EnSnowwd_Update(Actor* thisx, PlayState* play);
void EnSnowwd_Draw(Actor* thisx, PlayState* play);

void func_80AF76F0(EnSnowwd* this, PlayState* play);

ActorInit En_Snowwd_InitVars = {
    ACTOR_EN_SNOWWD,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_SNOWWD,
    sizeof(EnSnowwd),
    (ActorFunc)EnSnowwd_Init,
    (ActorFunc)EnSnowwd_Destroy,
    (ActorFunc)EnSnowwd_Update,
    (ActorFunc)EnSnowwd_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_TREE,
        AT_NONE,
        AC_ON | AC_HARD | AC_TYPE_PLAYER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK5,
        { 0x00000000, 0x00, 0x00 },
        { 0x0100020A, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 18, 60, 0, { 0, 0, 0 } },
};

Vec3f D_80AF7ABC = { 0.0f, 0.0f, 0.0f };

Vec3f D_80AF7AC8 = { 0.0f, -4.0f, 0.0f };

Color_RGBA8 D_80AF7AD4 = { 255, 255, 255, 255 };

Color_RGBA8 D_80AF7AD8 = { 200, 200, 220, 0 };

void EnSnowwd_Init(Actor* thisx, PlayState* play) {
    EnSnowwd* this = THIS;

    this->actor.home.rot.z = 0;
    this->actor.home.rot.y = 0;
    this->unk190 = 0;
    this->actor.uncullZoneForward = 4000.0f;
    this->actor.uncullZoneScale = 2000.0f;
    this->actor.uncullZoneDownward = 2400.0f;
    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    Actor_SetScale(&this->actor, 1.0f);
    this->actionFunc = func_80AF76F0;
}

void EnSnowwd_Destroy(Actor* thisx, PlayState* play) {
    EnSnowwd* this = THIS;

    Collider_DestroyCylinder(play, &this->collider);
}

void func_80AF76F0(EnSnowwd* this, PlayState* play) {
    s32 pad;
    Actor* thisx = &this->actor;
    f32 sp54;
    Vec3f sp48;

    if (this->collider.base.acFlags & AC_HIT) {
        this->collider.base.acFlags &= ~AC_HIT;
        Actor_PlaySfx(thisx, NA_SE_IT_REFLECTION_WOOD);
    }
    if (thisx->home.rot.y != 0) {
        this->unk190 = 0x15;
        thisx->home.rot.y = 0;
        if (thisx->home.rot.z == 0) {
            if (SNOWWD_GET_PARAM_F80(&this->actor) < 0x10) {
                sp48 = thisx->world.pos;
                sp48.y += 200.0f;
                Item_DropCollectibleRandom(play, NULL, &sp48, SNOWWD_GET_PARAM_F80(&this->actor) * 0x10);
            }
            thisx->home.rot.z = 1;
        }
    }
    if (thisx->xzDistToPlayer < 600.0f) {
        Collider_UpdateCylinder(thisx, &this->collider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        CollisionCheck_SetOC(play, &play->colChkCtx, &this->collider.base);
    }
    if (this->unk190 > 0) {
        this->unk190--;
        sp54 = Math_SinS((s16)((this->unk190 ^ 0xFFFF) * 0x3332)) * 250.0f;
        thisx->shape.rot.x = (s16)(Math_CosS(thisx->yawTowardsPlayer - thisx->shape.rot.y) * sp54);
        thisx->shape.rot.z = (s16)(Math_SinS(thisx->yawTowardsPlayer - thisx->shape.rot.y) * sp54);
        sp48 = thisx->world.pos;
        sp48.x += Rand_CenteredFloat(80.0f);
        sp48.y += 100.0f + Rand_ZeroFloat(30.0f);
        sp48.z += Rand_CenteredFloat(80.0f);
        func_800B0EB0(play, &sp48, &D_80AF7AC8, &D_80AF7ABC, &D_80AF7AD4, &D_80AF7AD8, 200, 10, 20);
    }
}

void EnSnowwd_Update(Actor* thisx, PlayState* play) {
    EnSnowwd* this = THIS;

    this->actionFunc(this, play);
}

void EnSnowwd_Draw(Actor* thisx, PlayState* play) {
    OPEN_DISPS(play->state.gfxCtx);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    Gfx_SetupDL25_Opa(play->state.gfxCtx);
    gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(object_snowwd_Tex_001AA0));
    gSPDisplayList(POLY_OPA_DISP++, object_snowwd_DL_000198);

    CLOSE_DISPS(play->state.gfxCtx);
}
