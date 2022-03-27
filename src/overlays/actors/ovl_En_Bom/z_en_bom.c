/*
 * File: z_en_bom.c
 * Overlay: ovl_En_Bom
 * Description: Bomb / Powder Keg
 */

#include "z_en_bom.h"
#include "objects/gameplay_keep/gameplay_keep.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((EnBom*)thisx)

void EnBom_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBom_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80871058(EnBom* this, GlobalContext* globalCtx);
void func_808714D4(EnBom* this, GlobalContext* globalCtx);
void func_80872648(GlobalContext* globalCtx, Vec3f* arg1);
void func_808726DC(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, s32 arg4);
void func_80872BC0(GlobalContext* globalCtx, s32 arg1);

typedef struct {
    /* 0x00 */ Vec3f unk_00;
    /* 0x0C */ Vec3f unk_0C;
    /* 0x18 */ s16 unk_18;
    /* 0x1A */ s16 unk_1A;
} EnBomStruct; // size = 0x1C

static EnBomStruct D_80874650[16];

const ActorInit En_Bom_InitVars = {
    ACTOR_EN_BOM,
    ACTORCAT_EXPLOSIVES,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(EnBom),
    (ActorFunc)EnBom_Init,
    (ActorFunc)EnBom_Destroy,
    (ActorFunc)EnBom_Update,
    (ActorFunc)EnBom_Draw,
};

static f32 enBomScales[] = { 0.01f, 0.03f };

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_HIT0,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x00013828, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 6, 11, 14, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit1[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000008, 0x00, 0x02 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit1 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ALL,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit1,
};

static ColliderJntSphElementInit sJntSphElementsInit2[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x80000008, 0x00, 0x04 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit2 = {
    {
        COLTYPE_HIT0,
        AT_ON | AT_TYPE_ALL,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit2,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F(scale, 0, ICHAIN_CONTINUE),
    ICHAIN_F32(targetArrowOffset, 2000, ICHAIN_CONTINUE),
    ICHAIN_F32_DIV1000(gravity, -4000, ICHAIN_STOP),
};

void EnBom_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnBom* this = THIS;
    s32 params;

    Actor_ProcessInitChain(&this->actor, sInitChain);
    ActorShape_Init(&this->actor.shape, 700.0f, ActorShadow_DrawCircle, 16.0f);
    this->actor.colChkInfo.mass = 200;
    this->actor.colChkInfo.cylRadius = 5;
    this->actor.colChkInfo.cylHeight = 10;

    this->flashSpeedScale = 7;
    this->isPowderKeg = ENBOM_GETX_1(&this->actor);
    if (this->isPowderKeg) {
        globalCtx->actorCtx.unk5 |= 1;
        this->timer = gSaveContext.powderKegTimer;
    } else {
        this->timer = 70;
    }

    Collider_InitCylinder(globalCtx, &this->collider1);
    Collider_InitJntSph(globalCtx, &this->collider2);
    Collider_SetCylinder(globalCtx, &this->collider1, &this->actor, &sCylinderInit);

    if (!this->isPowderKeg) {
        Collider_SetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit1, &this->collider3);
        this->collider1.dim.radius = 6;
        this->collider1.dim.height = 11;
    } else {
        Collider_SetJntSph(globalCtx, &this->collider2, &this->actor, &sJntSphInit2, &this->collider3);
        this->collider1.dim.radius = 20;
        this->collider1.dim.height = 36;
        func_80872648(globalCtx, &this->actor.world.pos);
    }

    this->collider3.info.toucher.damage += ENBOM_GETZ_FF00(thisx);
    this->actor.shape.rot.z &= 0xFF;
    if (ENBOM_GETZ_80(&this->actor)) {
        this->actor.shape.rot.z |= 0xFF00;
    }

    this->collider2.elements[0].dim.worldSphere.center.x = this->actor.world.pos.x;
    this->collider2.elements[0].dim.worldSphere.center.y = this->actor.world.pos.y;
    this->collider2.elements[0].dim.worldSphere.center.z = this->actor.world.pos.z;

    this->actor.flags |= ACTOR_FLAG_100000;

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actionFunc = func_808714D4;
        this->actor.room = -1;
        Actor_SetScale(&this->actor, enBomScales[this->isPowderKeg]);
    } else {
        this->actionFunc = func_80871058;
        gSaveContext.powderKegTimer = 0;
    }
}

void EnBom_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBom* this = THIS;

    Collider_DestroyJntSph(globalCtx, &this->collider2);
    Collider_DestroyCylinder(globalCtx, &this->collider1);
    if (this->isPowderKeg) {
        globalCtx->actorCtx.unk5 &= ~1;
    }
}

void func_80871058(EnBom* this, GlobalContext* globalCtx) {
    static Vec3f D_80872E68[] = {
        { 2.0f, -6.0f, -0.3f },
        { 1.5f, -5.0f, -0.6f },
        { 0.2f, -6.0f, -0.1f },
    };

    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->actionFunc = func_808714D4;
        this->actor.room = -1;
        return;
    }

    if ((this->actor.velocity.y > 0.0f) && (this->actor.bgCheckFlags & 0x10)) {
        this->actor.velocity.y = -this->actor.velocity.y;
    }

    if ((this->actor.speedXZ != 0.0f) && (this->actor.bgCheckFlags & 8)) {
        s16 yDiff = BINANG_SUB(this->actor.wallYaw, this->actor.world.rot.y);

        if (ABS_ALT(yDiff) > 0x4000) {
            this->actor.world.rot.y =
                BINANG_SUB(this->actor.wallYaw - this->actor.world.rot.y + this->actor.wallYaw, 0x8000);
        }

        Actor_PlaySfxAtPos(&this->actor, this->isPowderKeg ? NA_SE_EV_PUT_DOWN_WOODBOX : NA_SE_EV_BOMB_BOUND);
        Actor_MoveWithGravity(&this->actor);
        this->actor.speedXZ *= 0.7f;
        this->actor.bgCheckFlags &= ~8;
    }

    if (!(this->actor.bgCheckFlags & 1)) {
        Math_StepToF(&this->actor.speedXZ, 0.0f, 0.08f);
    } else {
        Vec3f* sp58;
        u32 sp54 = func_800C99D4(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId);
        Vec3f sp48;
        s16 sp46;
        f32 sp40;
        f32 sp3C;
        f32 sp38;

        sp58 = &D_80872E68[this->isPowderKeg];

        if (sp54 == 5) {
            sp58 = &D_80872E68[2];
        }

        if ((sp54 == 4) || (sp54 == 14) || (sp54 == 15)) {
            s16 sp36;

            Math_ApproachF(&this->actor.shape.yOffset, 0.0f, 0.1f, 50.0f);
            sp36 = this->actor.shape.shadowAlpha;
            Math_ApproachS(&sp36, 0, 1, 20);
            this->actor.shape.shadowAlpha = sp36;
        } else {
            Math_ApproachF(&this->actor.shape.yOffset, 700.0f, 1.0f, 700.0f);
        }

        sp40 = Math_SinS(this->actor.world.rot.y) * this->actor.speedXZ;
        sp3C = Math_CosS(this->actor.world.rot.y) * this->actor.speedXZ;
        func_800B75A0(this->actor.floorPoly, &sp48, &sp46);

        sp40 += 3.0f * sp48.x;
        sp3C += 3.0f * sp48.z;
        sp38 = sqrtf(SQ(sp40) + SQ(sp3C));

        if ((sp38 < this->actor.speedXZ) ||
            (SurfaceType_GetSlope(&globalCtx->colCtx, this->actor.floorPoly, this->actor.floorBgId) == 1)) {
            if (sp38 > 16.0f) {
                this->actor.speedXZ = 16.0f;
            } else {
                this->actor.speedXZ = sp38;
            }
            this->actor.world.rot.y = Math_FAtan2F(sp3C, sp40);
        }

        if (!Math_StepToF(&this->actor.speedXZ, 0.0f, sp58->x)) {
            s16 temp = this->actor.world.rot.y;
            s32 pad;

            if (ABS_ALT(BINANG_SUB(this->actor.world.rot.y, this->actor.shape.rot.y)) > 0x4000) {
                temp = BINANG_ROT180(temp);
            }
            Math_ScaledStepToS(&this->actor.shape.rot.y, temp, this->actor.speedXZ * 100.0f);
            this->unk_1FA += (s16)(this->actor.speedXZ * 800.0f);
        }

        if (this->actor.bgCheckFlags & 2) {
            Actor_PlaySfxAtPos(&this->actor, this->isPowderKeg ? NA_SE_EV_TRE_BOX_BOUND : NA_SE_EV_BOMB_BOUND);
            if (this->actor.velocity.y < sp58->y) {
                if ((sp54 == 4) || (sp54 == 14) || (sp54 == 15)) {
                    this->actor.velocity.y = 0.0f;
                } else {
                    this->actor.velocity.y = this->actor.velocity.y * sp58->z;
                }
                this->actor.bgCheckFlags &= ~1;
            }
        } else if (this->timer >= 4) {
            Actor_LiftActor(&this->actor, globalCtx);
        }
    }

    Actor_MoveWithGravity(&this->actor);
}

void func_808714D4(EnBom* this, GlobalContext* globalCtx) {
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        this->actionFunc = func_80871058;
        this->actor.room = globalCtx->roomCtx.currRoom.num;
        this->actor.flags &= ~ACTOR_FLAG_100000;
        this->actor.bgCheckFlags &= ~1;
        Math_Vec3s_ToVec3f(&this->actor.prevPos, &this->actor.home.rot);
        if (this->isPowderKeg) {
            gSaveContext.powderKegTimer = 0;
        }
        func_80871058(this, globalCtx);
    } else {
        Math_Vec3f_ToVec3s(&this->actor.home.rot, &this->actor.parent->world.pos);
        if (this->isPowderKeg) {
            gSaveContext.powderKegTimer = this->timer;
        }
    }
    Math_ScaledStepToS(&this->unk_1FA, 0, 2000);
}

void func_808715B8(EnBom* this, GlobalContext* globalCtx) {
    static s16 D_80872E8C[] = { 100, 200 };
    static Color_RGBA8 D_80872E90 = { 185, 140, 70, 255 };
    static Color_RGBA8 D_80872E94 = { 255, 255, 255, 255 };
    s32 i;
    s32 temp_s0;
    f32 temp_f20;
    s32 pad;
    f32 spCC;
    Vec3f spC0;
    Vec3f spB4;
    CollisionPoly* spB0;
    s32 spAC;
    Vec3f spA0;
    Vec3f sp94;
    Vec3f sp88;
    Color_RGBA8 sp84;
    Color_RGBA8 sp80;

    if (this->collider2.elements->dim.modelSphere.radius == 0) {
        this->actor.flags |= ACTOR_FLAG_20;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
    }

    this->collider2.elements->dim.worldSphere.radius = D_80872E8C[this->isPowderKeg];
    if (this->timer == 7) {
        this->collider2.base.atFlags &= ~OC1_TYPE_1;
    }

    if (this->actor.params == ENBOM_1) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider2.base);
    }

    if (globalCtx->envCtx.lightSettings.diffuseColor1[0] != 0) {
        globalCtx->envCtx.lightSettings.diffuseColor1[0] -= 25;
    }

    if (globalCtx->envCtx.lightSettings.diffuseColor1[1] != 0) {
        globalCtx->envCtx.lightSettings.diffuseColor1[1] -= 25;
    }

    if (globalCtx->envCtx.lightSettings.diffuseColor1[2] != 0) {
        globalCtx->envCtx.lightSettings.diffuseColor1[2] -= 25;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[0] != 0) {
        globalCtx->envCtx.lightSettings.ambientColor[0] -= 25;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[1] != 0) {
        globalCtx->envCtx.lightSettings.ambientColor[1] -= 25;
    }

    if (globalCtx->envCtx.lightSettings.ambientColor[2] != 0) {
        globalCtx->envCtx.lightSettings.ambientColor[2] -= 25;
    }

    if (this->timer == 0) {
        func_80123590(globalCtx, &this->actor);
        Actor_MarkForDeath(&this->actor);
    }

    if ((this->timer & 1) == 0) {
        spCC = Rand_ZeroFloat(M_PI);

        for (i = 0; i < 15; i++) {
            Matrix_InsertYRotation_f(((2.0f * (i * M_PI)) / 15.0f) + spCC, MTXMODE_NEW);
            Matrix_GetStateTranslationAndScaledZ((10 - this->timer) * 300.0f * 0.1f, &spC0);
            spB4.x = this->actor.world.pos.x + spC0.x;
            spB4.y = this->actor.world.pos.y + 500.0f;
            spB4.z = this->actor.world.pos.z + spC0.z;
            if (BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &spB0, &spAC, &spB4) != BGCHECK_Y_MIN) {
                temp_s0 = func_800C99D4(&globalCtx->colCtx, spB0, spAC);
                temp_f20 = BgCheck_EntityRaycastFloor1(&globalCtx->colCtx, &spB0, &spB4);

                if ((temp_s0 == 4) || (temp_s0 == 15) || (temp_s0 == 14)) {
                    if (temp_s0 == 4) {
                        sp84 = D_80872E90;
                        sp80 = D_80872E90;
                    } else {
                        sp84 = D_80872E94;
                        sp80 = D_80872E94;
                    }
                    Matrix_GetStateTranslationAndScaledZ(5.0f, &sp94);
                    sp88.x = sp88.z = 0.0f;
                    sp94.y = 2.0f;
                    sp88.y = 0.2f;

                    spA0.x = spB4.x;
                    spA0.y = temp_f20;
                    spA0.z = spB4.z;

                    temp_f20 = Rand_ZeroFloat(250.0f);
                    func_800B0F18(globalCtx, &spA0, &sp94, &sp88, &sp84, &sp80, temp_f20 + 950.0f, 10,
                                  Rand_ZeroFloat(5.0f) + 14.0f);
                }
            }
        }
    }
}

static s16 D_80872E98[] = { 3, 5 };
static s16 D_80872E9C[] = { 10, 15 };

void EnBom_Update(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f spA4 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp98 = { 0.0f, 0.1f, 0.0f };
    Vec3f sp8C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp80;
    Vec3f sp74 = { 0.0f, 0.6f, 0.0f };
    Color_RGBA8 sp70 = { 255, 255, 255, 255 };
    EnBom* this = THIS;
    s32 pad;
    Player* player = GET_PLAYER(globalCtx);

    if (player->stateFlags1 & 2) {
        return;
    }

    if (Player_GetMask(globalCtx) == PLAYER_MASK_GIANT) {
        Actor_MarkForDeath(thisx);
        return;
    }

    if (this->unk_1FC != 0) {
        this->unk_1FC--;
        Math_ApproachZeroF(&thisx->speedXZ, 1.0f, 1.0f);
        Actor_MoveWithGravity(thisx);
        Actor_UpdateBgCheckInfo(globalCtx, thisx, 35.0f, 10.0f, 36.0f, 4);
        if (this->unk_1FC == 0) {
            if (this->isPowderKeg) {
                gSaveContext.powderKegTimer = 0;
            }
            Actor_MarkForDeath(thisx);
        }
    } else {
        thisx->gravity = -1.2f;
        if (this->timer != 0) {
            if (!this->isPowderKeg || (func_808715B8 == this->actionFunc) || !Play_InCsMode(globalCtx)) {
                this->timer--;
            }
        }

        if ((!this->isPowderKeg && (this->timer == 67)) || (this->isPowderKeg && (this->timer <= 2400))) {
            Actor_PlaySfxAtPos(thisx, NA_SE_PL_TAKE_OUT_SHIELD);
            Actor_SetScale(thisx, enBomScales[this->isPowderKeg]);
        }

        if ((thisx->xzDistToPlayer >= 20.0f) || (fabsf(thisx->playerHeightRel) >= 80.0f)) {
            this->unk_1F8 = 1;
        }

        this->actionFunc(this, globalCtx);

        Actor_UpdateBgCheckInfo(globalCtx, thisx, 35.0f, 10.0f, 36.0f, 0x1F);
        if (thisx->params == ENBOM_0) {
            static Vec3us D_80872ED4[] = {
                { 40, 20, 100 },
                { 300, 60, 600 },
            };
            Vec3us* sp60 = &D_80872ED4[this->isPowderKeg];

            sp74.y = 0.2f;
            Math_Vec3f_Copy(&sp80, &thisx->home.pos);
            if ((globalCtx->gameplayFrames % 2) == 0) {
                EffectSsGSpk_SpawnFuse(globalCtx, thisx, &sp80, &spA4, &sp8C);
            }
            if (this->isPowderKeg) {
                func_801A0810(&thisx->projectedPos, NA_SE_IT_BIG_BOMB_IGNIT - SFX_FLAG,
                              (this->flashSpeedScale == 7)   ? 0
                              : (this->flashSpeedScale == 3) ? 1
                                                             : 2);
            } else {
                Actor_PlaySfxAtPos(thisx, NA_SE_IT_BOMB_IGNIT - SFX_FLAG);
            }

            sp80.y += 3.0f;
            func_800B0DE0(globalCtx, &sp80, &spA4, &sp74, &sp70, &sp70, 50, 5);

            if ((this->collider1.base.acFlags & AC_HIT) ||
                ((this->collider1.base.ocFlags1 & OC1_HIT) && ((this->collider1.base.oc->category == ACTORCAT_ENEMY) ||
                                                               (this->collider1.base.oc->category == ACTORCAT_BOSS)))) {
                this->timer = 0;
                thisx->shape.rot.z = 0;
            } else if ((this->timer > 100) && (func_80123F48(globalCtx, &thisx->world.pos, 30.0f, 50.0f))) {
                this->timer = 100;
            }

            sp74.y = 0.2f;
            sp80 = thisx->world.pos;
            sp80.y += 10.0f;

            if ((this->timer == sp60->x) || (this->timer == sp60->y) || (this->timer == 3)) {
                thisx->shape.rot.z = 0;
                this->flashSpeedScale >>= 1;
            }

            if ((this->timer < sp60->z) && (this->timer & (this->flashSpeedScale + 1))) {
                Math_ApproachF(&this->unk_1F4, 140.0f, 1.0f, 140.0f / this->flashSpeedScale);
            } else {
                Math_ApproachZeroF(&this->unk_1F4, 1.0f, 140.0f / this->flashSpeedScale);
            }

            if (this->timer < 3) {
                Actor_SetScale(thisx, thisx->scale.x + 0.002f);
            }

            if (this->timer == 0) {
                sp80 = thisx->world.pos;
                sp80.y += 10.0f;
                if (Actor_HasParent(thisx, globalCtx)) {
                    sp80.y += 30.0f;
                }
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp80.x, sp80.y - 10.0f, sp80.z, 0, 0,
                            0, this->isPowderKeg);
                func_800BC848(thisx, globalCtx, D_80872E98[this->isPowderKeg], D_80872E9C[this->isPowderKeg]);
                globalCtx->envCtx.lightSettings.diffuseColor1[0] = globalCtx->envCtx.lightSettings.diffuseColor1[1] =
                    globalCtx->envCtx.lightSettings.diffuseColor1[2] = 250;
                globalCtx->envCtx.lightSettings.ambientColor[0] = globalCtx->envCtx.lightSettings.ambientColor[1] =
                    globalCtx->envCtx.lightSettings.ambientColor[2] = 250;
                func_800DFD04(&globalCtx->mainCamera, 2, 11, 8);
                thisx->params = ENBOM_1;
                this->timer = 10;
                thisx->flags |= (0x100000 | 0x20);
                this->actionFunc = func_808715B8;
                if (this->isPowderKeg) {
                    gSaveContext.powderKegTimer = 0;
                    Actor_PlaySfxAtPos(thisx, NA_SE_IT_BIG_BOMB_EXPLOSION);
                } else {
                    Actor_PlaySfxAtPos(thisx, NA_SE_IT_BOMB_EXPLOSION);
                }
            }
        }

        Actor_SetFocus(thisx, 20.0f);

        if (thisx->params <= ENBOM_0) {
            Collider_UpdateCylinder(thisx, &this->collider1);
            if (!Actor_HasParent(thisx, globalCtx) && (this->unk_1F8 != 0)) {
                CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
            }
            CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider1.base);
        }

        if ((enBomScales[this->isPowderKeg] <= thisx->scale.x) && (thisx->params != ENBOM_1)) {
            if (thisx->depthInWater >= 20.0f) {
                Vec3f sp54;

                sp54.x = thisx->world.pos.x;
                sp54.y = thisx->world.pos.y + thisx->depthInWater;
                sp54.z = thisx->world.pos.z;
                EffectSsGRipple_Spawn(globalCtx, &sp54, 70, 500, 0);
                EffectSsGRipple_Spawn(globalCtx, &sp54, 70, 500, 10);
                sp54.y += 10.0f;
                EffectSsGSplash_Spawn(globalCtx, &sp54, NULL, NULL, 1, 500);
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp54.x, sp54.y, sp54.z, 0, 0, 1, 200);
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &thisx->world.pos, 30, NA_SE_IT_BOMB_UNEXPLOSION);
                this->unk_1F4 = 0.0f;
                thisx->velocity.y = (KREG(83) * 0.1f) + -2.0f;
                thisx->gravity = (KREG(84) * 0.1f) + -0.5f;
                this->unk_1FC = KREG(81) + 10;
            } else if (thisx->bgCheckFlags & 0x40) {
                thisx->bgCheckFlags &= ~0x40;
                Actor_PlaySfxAtPos(thisx, NA_SE_EV_BOMB_DROP_WATER);
            }
        }
    }
}

static Vec3f D_80872EE0 = { 0.0f, 800.0f, 0.0f };
static Vec3f D_80872EEC = { -750.0f, 0.0f, 0.0f };
static Vec3f D_80872EF8 = { -800.0f, 0.0f, 0.0f };
static Vec3f D_80872F04 = { 0.0f, 0.0f, 0.0f };

#include "overlays/ovl_En_Bom/ovl_En_Bom.c"

void EnBom_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBom* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (this->actor.params == ENBOM_0) {
        func_8012C28C(globalCtx->state.gfxCtx);

        Collider_UpdateSpheres(0, &this->collider2);

        if (!this->isPowderKeg) {
            func_800B8050(&this->actor, globalCtx, 0);
            Matrix_MultiplyVector3fByState(&D_80872EE0, &this->actor.home.pos);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_015FA0);

            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_InsertXRotation_s(0x4000, MTXMODE_APPLY);

            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPPipeSync(POLY_OPA_DISP++);
            gDPSetEnvColor(POLY_OPA_DISP++, (s8)this->unk_1F4, 0, 40, 255);
            gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, (s8)this->unk_1F4, 0, 40, 255);
            gSPDisplayList(POLY_OPA_DISP++, gameplay_keep_DL_015DB0);
        } else {
            Vec3f sp58;
            Vec3f sp4C;

            if (this->unk_1FA != 0) {
                s16 sp4A = this->actor.world.rot.y - this->actor.shape.rot.y;
                f32 sp44 = (1000.0f / Math_CosS(ABS_ALT((s16)(this->unk_1FA % 10922)) - 0x1555)) + -1000.0f;

                Matrix_RotateY(sp4A, MTXMODE_APPLY);
                Matrix_InsertTranslation(0.0f, sp44, 0.0f, MTXMODE_APPLY);
                Matrix_InsertXRotation_s(this->unk_1FA, MTXMODE_APPLY);
                Matrix_RotateY(-sp4A, MTXMODE_APPLY);
            }

            Matrix_MultiplyVector3fByState(&D_80872EEC, &this->actor.home.pos);
            Matrix_MultiplyVector3fByState(&D_80872EF8, &sp58);
            Matrix_MultiplyVector3fByState(&D_80872F04, &sp4C);

            gDPSetEnvColor(POLY_OPA_DISP++, 255, 255, 255, 255);
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, ovl_En_Bom_DL_80873CA0);
            gSPDisplayList(POLY_OPA_DISP++, ovl_En_Bom_DL_808742F8);

            func_808726DC(globalCtx, &this->actor.home.pos, &sp58, &sp4C, this->timer);
            func_80872BC0(globalCtx, this->timer);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80872648(GlobalContext* globalCtx, Vec3f* arg1) {
    EnBomStruct* ptr = &D_80874650[0];
    s32 i;

    for (i = 0; i < ARRAY_COUNT(D_80874650); i++, ptr++) {
        Math_Vec3f_Copy(&ptr->unk_00, arg1);
        Math_Vec3f_Copy(&ptr->unk_0C, &gZeroVec3f);
        ptr->unk_18 = 0;
        ptr->unk_1A = 0x4000;
    }
}

void func_808726DC(GlobalContext* globalCtx, Vec3f* arg1, Vec3f* arg2, Vec3f* arg3, s32 arg4) {
    s32 i;
    f32 temp_f20;
    Vec3f spCC;
    Vec3f spC0;
    EnBomStruct* ptr = &D_80874650[0];
    EnBomStruct* ptr2 = &D_80874650[1];
    f32 temp_f26 = Math_Vec3f_DistXYZ(arg3, arg1);
    s32 spB0;
    f32 temp_f2;
    f32 sqrt;

    Math_Vec3f_Copy(&ptr->unk_00, arg1);
    Math_Vec3f_Diff(arg2, arg1, &spCC);

    ptr->unk_18 = Math_FAtan2F(spCC.z, spCC.x);
    sqrt = sqrtf(SQ(spCC.x) + SQ(spCC.z));
    ptr->unk_1A = Math_FAtan2F(sqrt, spCC.y);

    spB0 = (arg4 / 240) + 1;

    for (i = 0; i < spB0; i++, ptr++, ptr2++, arg4 -= 240) {
        f32 phi_f22;
        CollisionPoly* spA0;
        s32 sp9C;
        Vec3f sp90;

        if (arg4 >= 240) {
            phi_f22 = 8.0f;
        } else {
            phi_f22 = (arg4 % 240) * (1.0f / 240) * 8.0f;
        }

        Math_Vec3f_Sum(&ptr2->unk_00, &ptr2->unk_0C, &ptr2->unk_00);
        temp_f20 = Math_Vec3f_DistXYZAndStoreDiff(arg3, &ptr2->unk_00, &spCC);
        if (temp_f20 < temp_f26) {
            if (temp_f20 == 0.0f) {
                spCC.x = 0.0f;
                spCC.y = temp_f26;
                spCC.z = 0.0f;
            } else {
                temp_f20 = temp_f26 / temp_f20;
                spCC.x *= temp_f20;
                spCC.y *= temp_f20;
                spCC.z *= temp_f20;
            }
            Math_Vec3f_Sum(arg3, &spCC, &ptr2->unk_00);
        }

        if (Math_Vec3f_DistXYZAndStoreDiff(&ptr->unk_00, &ptr2->unk_00, &spCC) == 0.0f) {
            spCC.x = 0.0f;
            spCC.y = phi_f22;
            spCC.z = 0.0f;
        }

        ptr2->unk_18 = Math_FAtan2F(spCC.z, spCC.x);
        sqrt = sqrtf(SQ(spCC.x) + SQ(spCC.z));
        ptr2->unk_1A = Math_FAtan2F(sqrt, spCC.y);

        ptr2->unk_18 = (s16)CLAMP(BINANG_SUB(ptr2->unk_18, ptr->unk_18), -8000, 8000) + ptr->unk_18;
        ptr2->unk_1A = (s16)CLAMP(BINANG_SUB(ptr2->unk_1A, ptr->unk_1A), -8000, 8000) + ptr->unk_1A;

        temp_f20 = Math_CosS(ptr2->unk_1A) * phi_f22;
        spC0.x = Math_SinS(ptr2->unk_18) * temp_f20;
        spC0.z = Math_CosS(ptr2->unk_18) * temp_f20;
        spC0.y = Math_SinS(ptr2->unk_1A) * phi_f22;

        Math_Vec3f_Sum(&ptr->unk_00, &spC0, &ptr2->unk_00);
        Math_Vec3f_Copy(&sp90, &ptr2->unk_00);

        sp90.y += 50.0f;

        temp_f2 = BgCheck_EntityRaycastFloor3(&globalCtx->colCtx, &spA0, &sp9C, &sp90) - ptr2->unk_00.y;
        if (temp_f2 >= 0.0f) {
            spC0.y += temp_f2;
            if (phi_f22 < spC0.y) {
                spC0.y = phi_f22;
                temp_f2 = 0.0f;
            } else {
                temp_f2 = sqrtf(SQ(phi_f22) - SQ(spC0.y));
            }

            if (temp_f20 == 0.0f) {
                spC0.x = temp_f2;
            } else {
                temp_f2 /= temp_f20;
                spC0.x *= temp_f2;
                spC0.z *= temp_f2;
            }

            Math_Vec3f_Sum(&ptr->unk_00, &spC0, &ptr2->unk_00);
            Math_Vec3f_Copy(&ptr2->unk_0C, &gZeroVec3f);
        }

        ptr2->unk_0C.y += -1.0f;
        if (ptr2->unk_0C.y < -10.0f) {
            ptr2->unk_0C.y = -10.0f;
        }
    }

    Math_Vec3f_Copy(arg1, &ptr->unk_00);
}

void func_80872BC0(GlobalContext* globalCtx, s32 arg1) {
    s32 temp_s5;
    s32 i;
    EnBomStruct* ptr = &D_80874650[0];
    EnBomStruct* ptr2;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(ptr->unk_00.x, ptr->unk_00.y, ptr->unk_00.z, MTXMODE_NEW);
    Matrix_InsertRotation(ptr->unk_1A, ptr->unk_18, 0, MTXMODE_APPLY);
    Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

    gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_OPA_DISP++, ovl_En_Bom_DL_80872F98);

    temp_s5 = (arg1 / 240) + 1;
    ptr2 = &D_80874650[1];

    for (i = 1; i < temp_s5; i++, ptr2++) {
        Matrix_InsertTranslation(ptr2->unk_00.x, ptr2->unk_00.y, ptr2->unk_00.z, MTXMODE_NEW);
        Matrix_InsertRotation(ptr2->unk_1A, ptr2->unk_18, 0, MTXMODE_APPLY);
        Matrix_Scale(0.01f, 0.01f, 0.01f, MTXMODE_APPLY);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        if ((i % 2) == 0) {
            gSPDisplayList(POLY_OPA_DISP++, ovl_En_Bom_DL_80873020);
        } else {
            gSPDisplayList(POLY_OPA_DISP++, ovl_En_Bom_DL_80873040);
        }
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
