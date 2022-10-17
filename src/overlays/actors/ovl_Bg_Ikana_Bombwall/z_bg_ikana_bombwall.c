/*
 * File: z_bg_ikana_bombwall.c
 * Overlay: ovl_Bg_Ikana_Bombwall
 * Description: Stone Tower Temple - Bombable Tan Floor Tile
 */

#include "z_bg_ikana_bombwall.h"
#include "objects/object_ikana_obj/object_ikana_obj.h"

#define FLAGS (ACTOR_FLAG_10000000)

#define THIS ((BgIkanaBombwall*)thisx)

void BgIkanaBombwall_Init(Actor* thisx, PlayState* play);
void BgIkanaBombwall_Destroy(Actor* thisx, PlayState* play);
void BgIkanaBombwall_Update(Actor* thisx, PlayState* play);
void BgIkanaBombwall_Draw(Actor* thisx, PlayState* play);

void func_80BD4F18(BgIkanaBombwall* this);
void func_80BD4F2C(BgIkanaBombwall* this, PlayState* play);
void func_80BD4F88(BgIkanaBombwall* this);
void func_80BD4F9C(BgIkanaBombwall* this, PlayState* play);
void func_80BD4FF8(BgIkanaBombwall* this);
void func_80BD503C(BgIkanaBombwall* this, PlayState* play);
void func_80BD5118(BgIkanaBombwall* this);
void func_80BD5134(BgIkanaBombwall* this, PlayState* play);

ActorInit Bg_Ikana_Bombwall_InitVars = {
    ACTOR_BG_IKANA_BOMBWALL,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_IKANA_OBJ,
    sizeof(BgIkanaBombwall),
    (ActorFunc)BgIkanaBombwall_Init,
    (ActorFunc)BgIkanaBombwall_Destroy,
    (ActorFunc)BgIkanaBombwall_Update,
    (ActorFunc)BgIkanaBombwall_Draw,
};

static ColliderCylinderInit sCylinderInit1 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000008, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 80, 80, 0, { 0, 0, 0 } },
};

static ColliderCylinderInit sCylinderInit2 = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0x00000000, 0x00, 0x00 },
        { 0x00000008, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 50, 20, 0, { 0, 0, 0 } },
};

s16 D_80BD52C8[] = {
    32,
    21,
    15,
    8,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 500, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 500, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 1000, ICHAIN_STOP),
};

Gfx* D_80BD52E0[] = {
    object_ikana_obj_DL_000378,
    object_ikana_obj_DL_000048,
};

#ifdef NON_MATCHING
void func_80BD4720(BgIkanaBombwall* this, PlayState* play) {
    s32 i;
    Vec3f spE0;
    Vec3f spD4;
    Vec3f spC8;
    Vec3f spBC;
    f32 temp_fs0;
    f32 phi_fs1;
    s16 phi_s0;
    s16 temp;
    s16 phi_t0;

    Matrix_Push();
    Matrix_RotateYS(this->dyna.actor.shape.rot.y, MTXMODE_NEW);
    temp_fs0 = 0.0f;
    phi_fs1 = 0.0f;

    for (i = 0; i < 30; i++) {
        temp_fs0 += 60.0f + (Rand_ZeroOne() * 20.0f);
        if (temp_fs0 > 75.0f) {
            temp_fs0 -= 150.0f;
        }
        spC8.x = temp_fs0;

        phi_fs1 += 5;
        spC8.y = phi_fs1;

        spC8.z = (Rand_ZeroOne() * 20.0f) - 10.0f;

        spBC.x = ((Rand_ZeroOne() - 0.5f) * 5.0f) + (temp_fs0 * 0.053333335f);
        spBC.y = (Rand_ZeroOne() * 7.0f) - 2.0f;
        spBC.z = (Rand_ZeroOne() * 4.0f) - 2.0f;

        Matrix_MultVec3f(&spC8, &spE0);
        Matrix_MultVec3f(&spBC, &spD4);

        spE0.x += this->dyna.actor.world.pos.x;
        spE0.y += this->dyna.actor.world.pos.y;
        spE0.z += this->dyna.actor.world.pos.z;

        if ((i & 3) == 0) {
            phi_s0 = 32;
            func_800BBFB0(play, &spE0, 50.0f, 2, 100, 120, 1);
        } else {
            phi_s0 = 64;
        }

        if (i & 1) {
            phi_s0 |= 1;
            phi_t0 = 1;
        } else {
            phi_t0 = 0;
        }

        if (D_80BD52C8[i & 3] >= 16) {
            temp = -550;
        } else {
            temp = -450;
        }

        EffectSsKakera_Spawn(play, &spE0, &spD4, &spE0, temp, phi_s0, 30, 0, 0, D_80BD52C8[i & 3], phi_t0, 0, 50, -1,
                             OBJECT_IKANA_OBJ, object_ikana_obj_DL_000288);
    }

    Matrix_Pop();
}
#else
void func_80BD4720(BgIkanaBombwall* this, PlayState* play);
#pragma GLOBAL_ASM("asm/non_matchings/overlays/ovl_Bg_Ikana_Bombwall/func_80BD4720.s")
#endif

void func_80BD4A14(BgIkanaBombwall* this, PlayState* play) {
    s32 i;
    Vec3f spD8;
    Vec3f spCC;
    f32 temp_fs0;
    f32 temp_fs1;
    f32 temp_fs3;
    s16 temp_v1;
    s16 phi_s2;
    s32 phi_t0;
    s16 phi_v0;
    s32 phi_v1;

    temp_fs3 = 0.0f;

    for (i = 0, phi_s2 = 0; i < 28; i++, phi_s2 += 0x924) {
        temp_fs3 += 20.0f + (Rand_ZeroOne() * 10.0f);
        if (temp_fs3 > 60.0f) {
            temp_fs3 -= 60.0f;
        }

        temp_fs0 = Math_SinS(phi_s2);
        temp_fs1 = Math_CosS(phi_s2);

        spD8.x = (temp_fs0 * temp_fs3) + this->dyna.actor.world.pos.x;
        spD8.y = this->dyna.actor.world.pos.y;
        spD8.z = (temp_fs1 * temp_fs3) + this->dyna.actor.world.pos.z;

        spCC.x = ((Rand_ZeroOne() - 0.5f) * 3.0f * temp_fs0) + ((temp_fs0 * temp_fs3) * 0.033333335f);
        spCC.y = (Rand_ZeroOne() * 18.0f) + 4.0f;
        spCC.z = ((Rand_ZeroOne() - 0.5f) * 3.0f * temp_fs1) + ((temp_fs1 * temp_fs3) * 0.033333335f);

        temp_v1 = (Rand_Next() & 3) + (i >> 1) + 6;

        if ((i & 3) == 0) {
            phi_v0 = 32;
        } else {
            phi_v0 = 64;
        }

        if (temp_v1 >= 15) {
            phi_v0 |= 1;
            phi_v1 = 1;
            phi_t0 = -550;
        } else {
            phi_v1 = 0;
            phi_t0 = -400;
        }

        EffectSsKakera_Spawn(play, &spD8, &spCC, &spD8, phi_t0, phi_v0, 30, 0, 0, temp_v1, phi_v1, 0, 50, -1,
                             OBJECT_IKANA_OBJ, object_ikana_obj_DL_000288);

        if ((i & 3) == 0) {
            spD8.y += 30.0f;
            func_800BBFB0(play, &spD8, 50.0f, 2, 70, 110, 1);
        }
    }
}

void BgIkanaBombwall_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgIkanaBombwall* this = THIS;
    s32 sp2C = BGIKANABOMBWALL_GET_100(&this->dyna.actor);
    s32 sp28;
    s32 sp24;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    Collider_InitCylinder(play, &this->collider);

    if (Flags_GetSwitch(play, BGIKANABOMBWALL_GET_SWITCHFLAG(&this->dyna.actor))) {
        Actor_Kill(&this->dyna.actor);
        return;
    }

    if (sp2C == 0) {
        sp28 = &object_ikana_obj_Colheader_000488;
        sp24 = &sCylinderInit1;
    } else {
        sp28 = &object_ikana_obj_Colheader_000128;
        sp24 = &sCylinderInit2;
    }

    DynaPolyActor_LoadMesh(play, &this->dyna, sp28);
    Collider_SetCylinder(play, &this->collider, &this->dyna.actor, sp24);
    Collider_UpdateCylinder(&this->dyna.actor, &this->collider);

    if (sp2C == 0) {
        func_80BD4F18(this);
    } else {
        func_80BD4F88(this);
    }
}

void BgIkanaBombwall_Destroy(Actor* thisx, PlayState* play) {
    BgIkanaBombwall* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyCylinder(play, &this->collider);
}

s32 func_80BD4E44(BgIkanaBombwall* this) {
    if (this->collider.base.acFlags & AC_HIT) {
        if ((this->collider.base.ac != NULL) &&
            (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &this->collider.base.ac->world.pos) < SQ(75.0f))) {
            return true;
        }
    }
    return false;
}

s32 func_80BD4EAC(BgIkanaBombwall* this) {
    if (this->collider.base.acFlags & AC_HIT) {
        if ((this->collider.base.ac != NULL) &&
            (Math3D_Vec3fDistSq(&this->dyna.actor.world.pos, &this->collider.base.ac->world.pos) < SQ(80.0f))) {
            return true;
        }
    }
    return false;
}

void func_80BD4F18(BgIkanaBombwall* this) {
    this->actionFunc = func_80BD4F2C;
}

void func_80BD4F2C(BgIkanaBombwall* this, PlayState* play) {
    if (func_80BD4E44(this)) {
        func_80BD4FF8(this);
    } else {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

void func_80BD4F88(BgIkanaBombwall* this) {
    this->actionFunc = func_80BD4F9C;
}

void func_80BD4F9C(BgIkanaBombwall* this, PlayState* play) {
    if (func_80BD4EAC(this)) {
        func_80BD4FF8(this);
    } else {
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
    }
}

void func_80BD4FF8(BgIkanaBombwall* this) {
    this->dyna.actor.flags |= ACTOR_FLAG_10;
    ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    this->actionFunc = func_80BD503C;
}

void func_80BD503C(BgIkanaBombwall* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        if (!BGIKANABOMBWALL_GET_100(&this->dyna.actor)) {
            func_80BD4720(this, play);
        } else {
            func_80BD4A14(this, play);
        }
        this->dyna.actor.draw = NULL;
        SoundSource_PlaySfxAtFixedWorldPos(play, &this->dyna.actor.world.pos, 60, NA_SE_EV_WALL_BROKEN);
        Flags_SetSwitch(play, BGIKANABOMBWALL_GET_SWITCHFLAG(&this->dyna.actor));
        if (!BGIKANABOMBWALL_GET_100(&this->dyna.actor)) {
            func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
        }
        func_80BD5118(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80BD5118(BgIkanaBombwall* this) {
    this->unk_1AC = 30;
    this->actionFunc = func_80BD5134;
}

void func_80BD5134(BgIkanaBombwall* this, PlayState* play) {
    if (!BGIKANABOMBWALL_GET_100(&this->dyna.actor)) {
        this->unk_1AC--;
        if (this->unk_1AC <= 0) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
            Actor_Kill(&this->dyna.actor);
        }
    } else if (this->dyna.actor.cutscene >= 0) {
        if (ActorCutscene_GetCurrentIndex() != this->dyna.actor.cutscene) {
            Actor_Kill(&this->dyna.actor);
        }
    } else {
        Actor_Kill(&this->dyna.actor);
    }
}

void BgIkanaBombwall_Update(Actor* thisx, PlayState* play) {
    BgIkanaBombwall* this = THIS;

    this->actionFunc(this, play);
}

void BgIkanaBombwall_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, D_80BD52E0[BGIKANABOMBWALL_GET_100(thisx)]);
}
