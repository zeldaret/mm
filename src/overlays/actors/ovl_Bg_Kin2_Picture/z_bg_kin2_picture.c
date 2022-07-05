/*
 * File: z_bg_kin2_picture.c
 * Overlay: ovl_Bg_Kin2_Picture
 * Description: Ocean Spider House - Skullkid Painting
 */

// credits for documentation: Isghj, EllipticEllipsis

#include "z_bg_kin2_picture.h"
#include "assets/objects/object_kin2_obj/object_kin2_obj.h"

#define FLAGS 0x00000000

#define THIS ((BgKin2Picture*)thisx)

void BgKin2Picture_Init(Actor* thisx, PlayState* play);
void BgKin2Picture_Destroy(Actor* thisx, PlayState* play);
void BgKin2Picture_Update(Actor* thisx, PlayState* play);
void BgKin2Picture_Draw(Actor* thisx, PlayState* play);

void BgKin2Picture_Wait(BgKin2Picture* this, PlayState* play);
void BgKin2Picture_SetupPlayCutscene(BgKin2Picture* this);
void BgKin2Picture_PlayCutscene(BgKin2Picture* this, PlayState* play);
void BgKin2Picture_SetupDoNothing(BgKin2Picture* this);
void func_80B6F61C(BgKin2Picture* this);
void func_80B6F640(BgKin2Picture* this, PlayState* play);
void func_80B6F708(BgKin2Picture* this);
void func_80B6F72C(BgKin2Picture* this, PlayState* play);
void BgKin2Picture_SetupWait(BgKin2Picture* this);
void BgKin2Picture_DoNothing(BgKin2Picture* this, PlayState* play);

const ActorInit Bg_Kin2_Picture_InitVars = {
    ACTOR_BG_KIN2_PICTURE,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_KIN2_OBJ,
    sizeof(BgKin2Picture),
    (ActorFunc)BgKin2Picture_Init,
    (ActorFunc)BgKin2Picture_Destroy,
    (ActorFunc)BgKin2Picture_Update,
    (ActorFunc)BgKin2Picture_Draw,
};

static ColliderTrisElementInit sTrisElementsInit[] = {
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x000138B0, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -20.0f, 53.3f, 9.0f }, { -20.0f, 3.0f, 9.0f }, { 20.0f, 3.0f, 9.0f } } },
    },
    {
        {
            ELEMTYPE_UNK4,
            { 0x00000000, 0x00, 0x00 },
            { 0x000138B0, 0x00, 0x00 },
            TOUCH_NONE | TOUCH_SFX_NORMAL,
            BUMP_ON,
            OCELEM_NONE,
        },
        { { { -20.0f, 53.3f, 9.0f }, { 20.0f, 3.0f, 9.0f }, { 20.0f, 53.3f, 9.0f } } },
    },
};

static ColliderTrisInit sTrisInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_TRIS,
    },
    2,
    sTrisElementsInit,
};

static Vec3f D_80B6FA18 = { 0.0f, 23.0f, 0.0f };

static InitChainEntry sInitChain[] = {
    ICHAIN_F32_DIV1000(gravity, -2000, ICHAIN_CONTINUE),  ICHAIN_F32_DIV1000(terminalVelocity, -20000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE), ICHAIN_F32(uncullZoneScale, 100, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 100, ICHAIN_CONTINUE), ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

s32 func_80B6EFA0(PlayState* play, s32 arg1) {
    s32 phi_a2 = -1;

    if ((u8)arg1 & 3) {
        phi_a2 = (u8)(((arg1 & 0x3FC)) >> 2);
    }

    return (phi_a2 >= 0) && Flags_GetTreasure(play, phi_a2);
}

void func_80B6EFEC(BgKin2Picture* thisx, PlayState* play) {
    BgKin2Picture* this = thisx;
    s32 temp_a1;

    if (BG_KIN2_PICTURE_GET_100000(&this->dyna.actor) == 0) {
        temp_a1 = ((this->dyna.actor.params & 0x1F) * 4) | 0xFF03;
        if ((func_80B6EFA0(play, temp_a1) == 0) &&
            Actor_Spawn(&play->actorCtx, play, ACTOR_EN_SW, this->dyna.actor.home.pos.x, this->dyna.actor.home.pos.y + 23.0f,
                        this->dyna.actor.home.pos.z, 0, this->dyna.actor.home.rot.y, 0, temp_a1)) {
            play_sound(NA_SE_SY_TRE_BOX_APPEAR);
        }
    }
}

//dust function? Idea: BgKin2Picture_SpawnDust.
void func_80B6F098(BgKin2Picture* this, PlayState* play) {
    f32 temp_fs0;
    Vec3f temp;
    Vec3f pos;
    Vec3f velocity;
    Vec3f accel;
    s32 temp_s1;
    s32 scale; //rename.
    s16 scaleStep;
    s32 phi_s3;
    s32 i;

    Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x,
                                 this->dyna.actor.world.pos.y +
                                     (this->dyna.actor.shape.yOffset * this->dyna.actor.scale.y),
                                 this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);
    Matrix_MultVec3f(&D_80B6FA18, &temp);
    pos.y = temp.y - 7.0f;
    velocity.y = 0.0f;
    accel.y = 0.2f;

    for (i = 0, phi_s3 = 0; i < 20; i++, phi_s3 += 0xCCC) {
        scale = Rand_ZeroOne() * 3276.0f;
        temp_s1 = scale + phi_s3;
        temp_fs0 = (Rand_ZeroOne() * 14.0f) + 4.0f;
        pos.x = Math_SinS(temp_s1) * temp_fs0;
        pos.z = Math_CosS(temp_s1) * temp_fs0;
        velocity.x = (Rand_ZeroOne() - 0.5f) + (pos.x * (1.0f / 6.0f));
        velocity.z = (Rand_ZeroOne() - 0.5f) + (pos.z * (1.0f / 6.0f));
        pos.x += temp.x;
        pos.z += temp.z;
        accel.x = velocity.x * (-0.09f);
        accel.z = velocity.z * (-0.09f);
        scale = ((s32)(Rand_ZeroOne() * 10.0f)) + 0xA;
        scaleStep = ((s32)(Rand_ZeroOne() * 10.0f)) + 0xF;
        func_800B1210(play, &pos, &velocity, &accel, scale, scaleStep); //dust spawn function.
    }
}

void BgKin2Picture_Init(Actor* thisx, PlayState* play) {
    s32 pad;
    BgKin2Picture* this = THIS;
    s32 temp_a1;
    Vec3f vertices[3];
    s32 i;
    s32 j;
    ColliderTrisElementInit* element;

    Actor_ProcessInitChain(&this->dyna.actor, sInitChain);
    DynaPolyActor_Init(&this->dyna, 0);
    DynaPolyActor_LoadMesh(play, &this->dyna, &gOceanSpiderHouseSkullkidPaintingCol);
    func_800C62BC(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_InitTris(play, &this->colliderTris);
    Collider_SetTris(play, &this->colliderTris, &this->dyna.actor, &sTrisInit, &this->unk17C);
    Matrix_SetTranslateRotateYXZ(this->dyna.actor.world.pos.x, this->dyna.actor.world.pos.y,
                                 this->dyna.actor.world.pos.z, &this->dyna.actor.shape.rot);

    for (i = 0; i < ARRAY_COUNT(sTrisElementsInit); i++) {
        for (j = 0; j < ARRAY_COUNT(vertices); j++) {
            element = &sTrisInit.elements[i];
            Matrix_MultVec3f(&element->dim.vtx[j], &vertices[j]);
        }
        Collider_SetTrisVertices(&this->colliderTris, i, &vertices[0], &vertices[1], &vertices[2]);
    }

    Actor_SetFocus(&this->dyna.actor, 23.0f);
    temp_a1 = ((this->dyna.actor.params & 0x1F) << 2) | 0xFF03; //flags?

    if (BG_KIN2_PICTURE_GET_100000(&this->dyna.actor) || func_80B6EFA0(play, temp_a1)) {
        this->unk242 = -1;
    }

    BgKin2Picture_SetupWait(this);
}

void BgKin2Picture_Destroy(Actor* thisx, PlayState* play) {
    BgKin2Picture* this = THIS;

    DynaPoly_DeleteBgActor(play, &play->colCtx.dyna, this->dyna.bgId);
    Collider_DestroyTris(play, &this->colliderTris);
}

void BgKin2Picture_SetupWait(BgKin2Picture* this) {
    this->actionFunc = BgKin2Picture_Wait;
}

void BgKin2Picture_Wait(BgKin2Picture* this, PlayState* play) {
    if ((this->colliderTris.base.acFlags & AC_HIT) != 0) {
        this->colliderTris.base.acFlags &= ~AC_HIT;
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
        BgKin2Picture_SetupPlayCutscene(this);
    } else {
        if (this->unk242 >= 0) {
            if (this->unk242 == 0) {
                Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EN_STALGOLD_ROLL);
                if (Rand_ZeroOne() < 0.1f) {
                    this->unk242 = Rand_S16Offset(40, 80);
                } else {
                    this->unk242 = 8;
                }
            } else {
                this->unk242--;
            }
        }
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->colliderTris.base);
    }
}

void BgKin2Picture_SetupPlayCutscene(BgKin2Picture* this) {
    this->actionFunc = BgKin2Picture_PlayCutscene;
}

void BgKin2Picture_PlayCutscene(BgKin2Picture* this, PlayState* play) {
    if (ActorCutscene_GetCanPlayNext(this->dyna.actor.cutscene)) {
        ActorCutscene_StartAndSetUnkLinkFields(this->dyna.actor.cutscene, &this->dyna.actor);
        this->unk240 = 1;
        func_80B6F61C(this);
    } else {
        ActorCutscene_SetIntentToPlay(this->dyna.actor.cutscene);
    }
}

void func_80B6F61C(BgKin2Picture* this) {
    this->unk23A = 0xD;
    this->unk23C = 0;
    this->unk23E = 0;
    this->actionFunc = func_80B6F640;
}

void func_80B6F640(BgKin2Picture* this, PlayState* play) {
    Vec3f* new_var;
    Vec3f sp30;
    Vec3f sp24;
    this->unk23A += -1;
    if (this->unk23A <= 0) {
        Math_Vec3f_Copy(&this->dyna.actor.world.pos, &this->dyna.actor.home.pos);
        func_80B6F708(this);
        return;
    }
    this->unk23C += 0x7BAC;
    this->unk23E += 0x4E20;
    sp30.x = Math_CosS(this->unk23C);
    sp30.y = Math_CosS(this->unk23E) * 0.2f;
    sp30.z = 0.0f;
    Matrix_RotateYS(this->dyna.actor.shape.rot.y, 0);
    new_var = &sp30;
    Matrix_MultVec3f(new_var, &sp24);
    Math_Vec3f_Sum(&this->dyna.actor.home.pos, &sp24, &this->dyna.actor.world.pos);
}

void func_80B6F708(BgKin2Picture* this) {
    this->unk23B = 0;
    this->unk238 = 0;
    this->unk23A = 4;
    this->actionFunc = func_80B6F72C;
}



void func_80B6F72C(BgKin2Picture* this, PlayState* play) {
    if (this->unk23A > 0) {
        this->unk23A--;

        if (this->unk23A == 0) {
            func_80B6EFEC(this, play);
        }
    }

    Actor_MoveWithGravity(&this->dyna.actor);
    Actor_UpdateBgCheckInfo(play, &this->dyna.actor, 0.0f, 0.0f, 0.0f, 4U);

    if ((this->dyna.actor.bgCheckFlags & 1)) {
        Math_StepToS(&this->unk238, 0x7D0, 0x78);

        if (this->unk23B < 3) {
            this->unk23B++;

            if (this->dyna.actor.velocity.y <= 0.01f) {
                this->dyna.actor.velocity.y *= -0.7f;

                if (this->dyna.actor.velocity.y > 6.0f) {
                    this->dyna.actor.velocity.y = 6.0f;
                }

                if (this->unk23B < 3) {
                    Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_SMALL_WOODPLATE_BOUND_0);
                }
            }
        }
    }

    Actor_SetFocus(&this->dyna.actor, 23.0f);

    if (!(this->unk241) && (this->dyna.actor.shape.rot.x > 0x3300)) {
        func_80B6F098(this, play);
        this->unk241 = 1;
    }

    if (Math_ScaledStepToS(&this->dyna.actor.shape.rot.x, 0x4000, this->unk238) != 0) {
        this->dyna.actor.shape.yOffset = 40.0f;

        if (this->unk240) {
            ActorCutscene_Stop(this->dyna.actor.cutscene);
        }

        func_800C6314(play, &play->colCtx.dyna, this->dyna.bgId);
        Actor_PlaySfxAtPos(&this->dyna.actor, NA_SE_EV_WOODPLATE_BROKEN);
        BgKin2Picture_SetupDoNothing(this);
    } else {
        this->dyna.actor.shape.yOffset = Math_SinS(this->dyna.actor.shape.rot.x) * 40.0f;
    }
}

void BgKin2Picture_SetupDoNothing(BgKin2Picture* this) {
    this->actionFunc = BgKin2Picture_DoNothing;
}

void BgKin2Picture_DoNothing(BgKin2Picture* this, PlayState* play) {
}

void BgKin2Picture_Update(Actor* thisx, PlayState* play) {
    BgKin2Picture* this = THIS;
    this->actionFunc(this, play);
}

void BgKin2Picture_Draw(Actor* thisx, PlayState* play) {
    BgKin2Picture* this = THIS;
    Gfx_DrawDListOpa(play, gOceanSpiderHouseSkullkidPaintingDL);
}
