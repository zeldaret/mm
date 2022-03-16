/*
 * File: z_en_wiz_fire.c
 * Overlay: ovl_En_Wiz_Fire
 * Description: Wizzrobe Fire/Ice Attack
 */

#include "z_en_wiz_fire.h"
#include "overlays/actors/ovl_En_Wiz/z_en_wiz.h"
#include "objects/object_wiz/object_wiz.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_8000000)

#define THIS ((EnWizFire*)thisx)

void EnWizFire_Init(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Update(Actor* thisx, GlobalContext* globalCtx);
void EnWizFire_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_80A4984C(EnWizFire* this, GlobalContext* globalCtx);
void func_80A49A44(EnWizFire* this, GlobalContext* globalCtx);
void func_80A49F38(EnWizFire* this, GlobalContext* globalCtx);
void func_80A49FD8(EnWizFire* this, GlobalContext* globalCtx);
void func_80A4A11C(EnWizFire* this, GlobalContext* globalCtx);
void func_80A4A608(EnWizFire* this, GlobalContext* globalCtx);
void func_80A4BAB4(Actor* thisx, GlobalContext* globalCtx);
void func_80A4BC74(EnWizFire* this, Vec3f* arg1, Vec3f* arg2);
void func_80A4BDDC(EnWizFire* this, GlobalContext* globalCtx);
void func_80A4BF78(EnWizFire* this, GlobalContext* globalCtx);

static s32 D_80A4C1C0 = 0;

const ActorInit En_Wiz_Fire_InitVars = {
    ACTOR_EN_WIZ_FIRE,
    ACTORCAT_ENEMY,
    FLAGS,
    OBJECT_WIZ,
    sizeof(EnWizFire),
    (ActorFunc)EnWizFire_Init,
    (ActorFunc)EnWizFire_Destroy,
    (ActorFunc)EnWizFire_Update,
    (ActorFunc)EnWizFire_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ENEMY,
        AC_ON | AC_TYPE_PLAYER,
        OC1_NONE,
        OC2_TYPE_1,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK0,
        { 0xF7CFFFFF, 0x09, 0x10 },
        { 0x01001202, 0x00, 0x00 },
        TOUCH_ON | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_NONE,
    },
    { 0, 0, 0, { 0, 0, 0 } },
};

void EnWizFire_Init(Actor* thisx, GlobalContext* globalCtx) {
    EnWizFire* this = THIS;

    Collider_InitAndSetCylinder(globalCtx, &this->collider, &this->actor, &sCylinderInit);
    this->unk_162 = this->actor.params;
    this->actor.targetMode = 3;
    this->unk_172 = 10;
    this->unk_1FC = 255.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;

    if (!func_8012405C(globalCtx)) {
        this->collider.info.toucher.dmgFlags = 0x20000000;
    }

    switch (this->unk_162) {
        case 4:
            this->unk_166 = 1;
            this->collider.info.toucher.damage = 8;
            this->collider.info.toucher.effect = 2;
            this->collider.info.bumper.dmgFlags = (0x1000000 | 0x800 | 0x200 | 0x2);
            this->unk_162 = 0;

        case 0:
            if (this->unk_162 == 4) {
                this->unk_162 = 0;
                this->collider.info.toucher.damage = 8;
            }

        case 1:
        case 3:
            this->actionFunc = func_80A4984C;
            break;

        case 2:
            this->actor.draw = func_80A4BAB4;
            this->unk_170 = Rand_S16Offset(0, 10000);
            this->unk_160 = 1;
            this->collider.info.toucher.damage = 2;
            this->actionFunc = func_80A49F38;
    }
}

void EnWizFire_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnWizFire* this = THIS;

    if (this->unk_162 == 0) {
        globalCtx->envCtx.lightSettings.fogColor[2] = 0;
        globalCtx->envCtx.lightSettings.fogColor[1] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.fogColor[0] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor2[2] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor2[1] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor2[0] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor1[2] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor1[1] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.diffuseColor1[0] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.ambientColor[2] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.ambientColor[1] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.ambientColor[0] = globalCtx->envCtx.lightSettings.fogColor[2];
        globalCtx->envCtx.lightSettings.fogNear = globalCtx->envCtx.lightSettings.fogColor[2];
    }
    Collider_DestroyCylinder(globalCtx, &this->collider);
}

void func_80A4984C(EnWizFire* this, GlobalContext* globalCtx) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_178); i++) {
        this->unk_178[i] = this->actor.world.pos;
    }

    this->unk_16E = 0;
    Matrix_StatePush();
    Matrix_RotateY(this->actor.world.rot.y, MTXMODE_NEW);
    Matrix_InsertXRotation_s(this->actor.world.rot.x, MTXMODE_APPLY);

    if (this->unk_162 != 0) {
        sp44.z = randPlusMinusPoint5Scaled(2.0f) + 8.0f;
    } else {
        sp44.z = 12.0f;
    }

    Matrix_MultiplyVector3fByState(&sp44, &this->actor.velocity);
    Matrix_StatePop();
    this->actor.world.rot.x = this->actor.world.rot.y = this->actor.world.rot.z = 0;
    this->unk_168 = 50;
    if (this->unk_162 != 0) {
        this->actor.velocity.y = 10.0f;
        this->actor.gravity = -1.0f;
        this->unk_150 = 0.01f;
    } else {
        this->unk_150 = 0.02f;
        this->unk_168 = 100;
    }
    this->unk_160 = 0;
    this->actionFunc = func_80A49A44;
}

void func_80A49A44(EnWizFire* this, GlobalContext* globalCtx) {
    Vec3f sp54 = { 0.0f, 0.0f, 0.0f };

    this->actor.world.rot.z += 5000;

    if (this->unk_162 != 0) {
        this->unk_150 = 0.01f;
    } else {
        this->unk_150 = 0.02f;
    }

    if ((this->unk_168 == 0) && (this->unk_14C < 0.001f)) {
        Math_Vec3f_Copy(&this->actor.velocity, &gZeroVec3f);
        this->unk_160 = 3;
        this->unk_16A = 0;
        this->actionFunc = func_80A4A608;
        return;
    }

    if (this->unk_168 == 0) {
        this->unk_150 = 0.0f;
    }

    Math_ApproachF(&this->unk_14C, this->unk_150, 0.2f, 0.01f);

    if (this->unk_172 == 0) {
        if ((this->actor.bgCheckFlags & 8) && (this->unk_162 == 0) && (this->unk_168 != 0) &&
            (this->actor.bgCheckFlags & 8)) {
            D_80A4C1C0 = 0;
            this->unk_168 = 0;
            this->unk_150 = 0.0f;
        }
    }

    if ((this->actor.bgCheckFlags & 1) && (this->unk_16A == 0)) {
        s32 i;
        s16 phi_s0;
        s32 temp;

        if (this->unk_162 == 1) {
            this->unk_16A = 10;

            Matrix_StatePush();
            Matrix_RotateY((s16)randPlusMinusPoint5Scaled(0x100) + this->actor.world.rot.y, MTXMODE_NEW);
            sp54.z = randPlusMinusPoint5Scaled(2.0f) + 8.0f;
            Matrix_MultiplyVector3fByState(&sp54, &this->actor.velocity);
            Matrix_StatePop();

            this->actor.velocity.y = 6.0f;
            this->actor.gravity = -0.7f;

            if (this->unk_164 == 0) {
                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WIZ_FIRE, this->actor.world.pos.x,
                            this->actor.world.pos.y - 10.0f, this->actor.world.pos.z, 0, 0, 0, 2);
                this->unk_164 = 1;
            }

            this->unk_168 = 0;
            this->unk_14C = 0.0f;
            Math_Vec3f_Copy(&this->actor.velocity, &gZeroVec3f);
            this->unk_160 = 3;
            this->unk_16A = 0;
            this->actionFunc = func_80A4A608;
            return;
        }

        if ((this->unk_162 == 0) && (this->unk_168 != 0)) {
            if (this->actor.floorBgId == BGCHECK_SCENE) {
                this->unk_16A = 100;
                if (this->unk_166 == 0) {
                    phi_s0 = 0;

                    for (i = 0; i < 5; i++) {
                        Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_WIZ_FIRE, this->actor.world.pos.x,
                                    this->actor.world.pos.y, this->actor.world.pos.z, 0, phi_s0, 0, 1);
                        phi_s0 += BINANG_ADD((s32)randPlusMinusPoint5Scaled(0x1000), 0x3333);
                    }

                    Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);
                    this->unk_16A = Rand_S16Offset(70, 30);
                    if (this->unk_16A != 0) {
                        Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_EXP - SFX_FLAG);
                    }
                } else if (this->unk_16A != 0) {
                    Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
                }
                Math_Vec3f_Copy(&this->actor.velocity, &gZeroVec3f);
                this->unk_168 = 0;
                this->unk_160 = 2;
                this->unk_14C = 0.0f;
                this->actionFunc = func_80A4A11C;
            }
            return;
        }
    }

    if ((this->unk_162 != 3) && (this->unk_168 != 0)) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->collider.info.acHitInfo->toucher.dmgFlags == 0x1000) {
                this->unk_168 = 0;
                this->unk_148 = 1;
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }

        if (func_8012405C(globalCtx) && (this->collider.base.atFlags & AT_BOUNCED)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_MG);
            this->collider.base.atFlags &= ~(AT_TYPE_ENEMY | AT_BOUNCED | AT_HIT);
            this->collider.base.atFlags |= AT_TYPE_PLAYER;
            this->collider.info.toucher.dmgFlags = 0x20;
            this->collider.info.toucher.damage = 2;
            this->unk_168 = 100;
            this->unk_162 = 3;
            this->actor.velocity.x *= -1.0f;
            this->actor.velocity.y *= -0.5f;
            this->actor.velocity.z *= -1.0f;

            if ((this->actor.parent != NULL) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
                (this->actor.parent->update != NULL)) {
                ((EnWiz*)this->actor.parent)->unk_3BA = 0;
            }
        }
    }
}

void func_80A49F38(EnWizFire* this, GlobalContext* globalCtx) {
    this->unk_150 = 0.02f;
    this->unk_168 = Rand_S16Offset(50, 50);
    this->unk_154 = randPlusMinusPoint5Scaled(1.0f) * 0.007f;
    this->unk_158 = randPlusMinusPoint5Scaled(1.0f) * 0.005f;
    this->unk_15C = randPlusMinusPoint5Scaled(1.0f) * 0.007f;
    this->actionFunc = func_80A49FD8;
}

void func_80A49FD8(EnWizFire* this, GlobalContext* globalCtx) {
    if (this->unk_168 > 10) {
        Math_ApproachF(&this->unk_14C, this->unk_150, 0.3f, 0.01f);
    } else {
        Math_ApproachF(&this->unk_14C, 2.0f * this->unk_150, 0.2f, 0.002f);
        Math_ApproachZeroF(&this->unk_1FC, 1.0f, 35.0f);
        if ((this->unk_168 == 0) && (this->unk_1FC < 2.0f)) {
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    if (this->collider.base.acFlags & AC_HIT) {
        if (this->unk_168 != 0) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->unk_168 > 10) {
                this->unk_168 -= 10;
            }

            if (this->collider.info.acHitInfo->toucher.dmgFlags == 0x1000) {
                this->unk_168 = 0;
                this->unk_148 = 1;
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }
    }

    if (this->unk_168 != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    }
}

void func_80A4A11C(EnWizFire* this, GlobalContext* globalCtx) {
    s32 pad;

    if ((this->actor.parent != NULL) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
        (this->actor.parent->update != NULL) && (this->actor.parent->colChkInfo.health == 0)) {
        this->unk_16A = 0;
        this->unk_174 = 1;
    }

    this->unk_16E++;

    if (this->unk_16E > 10) {
        this->unk_16E = 10;
    }

    if (this->unk_16A != 0) {
        Math_ApproachF(&this->unk_200, 60.0f, 0.5f, 10.0f);
        if (this->unk_166 == 1) {
            Vec3f sp40 = { 0.0f, 0.0f, 0.0f };
            Vec3f sp34;

            sp40.x = randPlusMinusPoint5Scaled(3.0f) / 10.0f;
            sp40.y = 0.23f;
            sp40.z = randPlusMinusPoint5Scaled(3.0f) / 10.0f;

            Math_Vec3f_Copy(&sp34, &this->actor.world.pos);
            sp34.x += randPlusMinusPoint5Scaled(150.0f);
            sp34.z += randPlusMinusPoint5Scaled(150.0f);

            Math_ApproachF(&this->unk_1F0, 0.022f, 0.3f, 0.01f);
            this->collider.dim.radius = this->unk_1F0 * 4300.0f;
            this->collider.dim.height = 30;
            this->collider.dim.yShift = 15;
            func_80A4BC74(this, &sp34, &sp40);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            return;
        }

        Math_ApproachF(&this->unk_1F0, 0.02f, 0.3f, 0.002f);
        Math_ApproachF(&this->unk_1F8, 0.02f, 0.3f, 0.002f);
        Math_ApproachF(&this->unk_1F4, 0.02f, 0.3f, 0.2f);
        this->collider.dim.radius = this->unk_1F0 * 4000.0f;
        this->collider.dim.height = this->unk_1F4 * 1850.0f;
        this->collider.dim.yShift = -15;

        if (this->collider.dim.height < 2) {
            this->collider.dim.height = 2;
        }

        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            if ((D_80A4C1C0 == 0) && (this->collider.info.acHitInfo->toucher.dmgFlags == 0x1000)) {
                D_80A4C1C0 = 1;
                this->unk_148 = 1;
                this->unk_16A = 0;
                SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }
        this->actor.world.pos.y = this->actor.floorHeight + 10.0f;
        Actor_SetFocus(&this->actor, 0.0f);
        return;
    }

    Math_ApproachZeroF(&this->unk_200, 0.2f, 3.0f);

    if (this->unk_166 == 1) {
        Math_ApproachZeroF(&this->unk_1F0, 0.046f, 0.001f);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);

        if (this->unk_164 == 0) {
            if ((this->actor.parent != NULL) && (this->actor.parent->id == ACTOR_EN_WIZ) && (this->unk_1F0 < 0.05f)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                this->collider.dim.yShift = -15;
                this->unk_164 = 1;
                wiz->unk_3BA = 0;
            }
        }

        if ((this->unk_164 != 0) && (this->unk_1F0 < 0.05f)) {
            Math_ApproachZeroF(&this->unk_1FC, 1.0f, 5.0f);
        }

        if ((this->unk_1F0 < 0.001f) && (this->unk_204 < 0.001f)) {
            D_80A4C1C0 = 0;
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    Math_ApproachZeroF(&this->unk_1F4, 0.1f, 0.01f);

    if (this->unk_1F4 < 0.01f) {
        Math_ApproachZeroF(&this->unk_1FC, 1.0f, 10.0f);
        if ((this->unk_1FC < 10.0f) && (this->unk_204 < 0.001f)) {
            D_80A4C1C0 = 0;
            if ((this->actor.parent != NULL) && (this->unk_162 == 0) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
                (this->actor.parent->update != NULL)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                wiz->unk_3BA = 0;
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80A4A608(EnWizFire* this, GlobalContext* globalCtx) {
    if (this->unk_16A == 0) {
        this->unk_16A = 2;
        this->unk_16E++;
        if (this->unk_16E >= 6) {
            if ((this->actor.parent != NULL) && (this->unk_162 == 0) && (this->actor.parent->id == ACTOR_EN_WIZ)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                D_80A4C1C0 = 0;
                if (wiz->actor.update != NULL) {
                    wiz->unk_3BA = 0;
                }
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnWizFire_Update(Actor* thisx, GlobalContext* globalCtx2) {
    static Color_RGB8 D_80A4C234[] = {
        { 100, 40, 40 }, { 180, 0x78, 80 }, { 155, 80, 80 },   { 125, 20, 0 },
        { 0, 0, 0 },     { 200, 250, 250 }, { 100, 250, 250 }, { 225, 255, 235 },
    };
    static Color_RGBA8 D_80A4C24C = { 250, 250, 250, 255 };
    static Color_RGBA8 D_80A4C250 = { 180, 180, 180, 255 };
    GlobalContext* globalCtx = globalCtx2;
    EnWizFire* this = THIS;
    Player* player = GET_PLAYER(globalCtx);
    s32 j;
    s16 temp_s0;
    s16 idx;

    Actor_SetScale(&this->actor, this->unk_14C);
    func_80A4BDDC(this, globalCtx);
    this->unk_204 = this->unk_200 / 60.0f;

    if (this->unk_162 == 0) {
        Actor* wiz = this->actor.parent;

        if ((wiz != NULL) && (wiz->id == ACTOR_EN_WIZ) && (wiz->update != NULL) && (((EnWiz*)wiz)->unk_74A != 2)) {
            f32 phi_f0;

            idx = this->unk_166 * 4;

            phi_f0 = 970.0f;
            if (this->unk_166 == 0) {
                phi_f0 = 968.0f;
            }

            globalCtx->envCtx.lightSettings.fogNear = (phi_f0 - (s16)globalCtx->envCtx.unk_C4.fogNear) * this->unk_204;

            globalCtx->envCtx.lightSettings.ambientColor[0] =
                ((f32)D_80A4C234[idx].r - globalCtx->envCtx.unk_C4.ambientColor[0]) * this->unk_204;
            globalCtx->envCtx.lightSettings.ambientColor[1] =
                ((f32)D_80A4C234[idx].g - globalCtx->envCtx.unk_C4.ambientColor[1]) * this->unk_204;
            globalCtx->envCtx.lightSettings.ambientColor[2] =
                ((f32)D_80A4C234[idx].b - globalCtx->envCtx.unk_C4.ambientColor[2]) * this->unk_204;

            idx++;
            globalCtx->envCtx.lightSettings.diffuseColor1[0] =
                ((f32)D_80A4C234[idx].r - globalCtx->envCtx.unk_C4.diffuseColor1[0]) * this->unk_204;
            globalCtx->envCtx.lightSettings.diffuseColor1[1] =
                ((f32)D_80A4C234[idx].g - globalCtx->envCtx.unk_C4.diffuseColor1[1]) * this->unk_204;
            globalCtx->envCtx.lightSettings.diffuseColor1[2] =
                ((f32)D_80A4C234[idx].b - globalCtx->envCtx.unk_C4.diffuseColor1[2]) * this->unk_204;

            idx++;
            globalCtx->envCtx.lightSettings.diffuseColor2[0] =
                ((f32)D_80A4C234[idx].r - globalCtx->envCtx.unk_C4.diffuseColor[0]) * this->unk_204;
            globalCtx->envCtx.lightSettings.diffuseColor2[1] =
                ((f32)D_80A4C234[idx].g - globalCtx->envCtx.unk_C4.diffuseColor[1]) * this->unk_204;
            globalCtx->envCtx.lightSettings.diffuseColor2[2] =
                ((f32)D_80A4C234[idx].b - globalCtx->envCtx.unk_C4.diffuseColor[2]) * this->unk_204;

            idx++;
            globalCtx->envCtx.lightSettings.fogColor[0] =
                ((f32)D_80A4C234[idx].r - globalCtx->envCtx.unk_C4.fogColor[0]) * this->unk_204;
            globalCtx->envCtx.lightSettings.fogColor[1] =
                ((f32)D_80A4C234[idx].g - globalCtx->envCtx.unk_C4.fogColor[1]) * this->unk_204;
            globalCtx->envCtx.lightSettings.fogColor[2] =
                ((f32)D_80A4C234[idx].b - globalCtx->envCtx.unk_C4.fogColor[2]) * this->unk_204;
        }
    }

    this->unk_170++;

    this->actionFunc(this, globalCtx);

    this->actor.shape.yOffset = 10.0f;
    Actor_UpdatePos(&this->actor);

    this->unk_178[0] = this->actor.world.pos;

    for (j = 8; j >= 0; j--) {
        this->unk_178[j + 1] = this->unk_178[j];
    }

    this->actor.velocity.y += this->actor.gravity;

    if (this->unk_172 != 0) {
        this->unk_172--;
    }

    if (this->unk_168 != 0) {
        this->unk_168--;
    }

    if (this->unk_16C != 0) {
        this->unk_16C--;
    }

    if (this->unk_16A != 0) {
        this->unk_16A--;
    }

    Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 20.0f, 5.0f, 10, 0x1D);

    if (((this->unk_148 != 0) || (D_80A4C1C0 != 0)) && (this->unk_16C == 0)) {
        Vec3f sp70;
        Vec3f sp64;
        Vec3f sp58;
        f32 sp54;
        s32 i;

        sp70.x = 0.0f;
        sp70.y = 1.0f;
        sp70.z = 0.0f;
        sp64.x = 0.0f;
        sp64.y = 1.0f;
        sp64.z = 0.0f;

        sp54 = Rand_S16Offset(20, 10);
        if (this->unk_162 == 0) {
            sp54 = Rand_S16Offset(40, 20);
        }

        this->unk_16C = Rand_S16Offset(2, 2);

        for (i = 0; i < 2; i++) {
            temp_s0 = Rand_S16Offset(20, 20);
            sp58.x = ((f32)((Rand_ZeroOne() < 0.5f) ? -1 : 1) * temp_s0) + this->actor.world.pos.x;
            sp58.y = (Rand_ZeroOne() * 20.0f) + this->actor.floorHeight;
            temp_s0 = Rand_S16Offset(20, 20);
            sp58.z = ((f32)((Rand_ZeroOne() < .5f) ? -1 : 1) * temp_s0) + this->actor.world.pos.z;
            func_800B0DE0(globalCtx, &sp58, &sp64, &sp70, &D_80A4C24C, &D_80A4C250, Rand_S16Offset(350, 100), sp54);
        }
    }

    if (this->unk_160 < 2) {
        this->collider.dim.radius = (this->unk_14C * 15.0f) + 25.0f;
        this->collider.dim.height = (this->unk_14C * 15.0f) + 25.0f;
        this->collider.dim.yShift = (this->unk_14C * -0.75f) - 5.0f;
    }

    if (this->unk_162 == 2) {
        this->collider.dim.radius = 10;
        this->collider.dim.height = this->unk_14C * 5000.0f;
        this->collider.dim.yShift = 0;
    }

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        if (this->unk_162 == 0) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EN_WIZ_LAUGH2);
            if (player->invincibilityTimer > 0) {
                player->invincibilityTimer += 40;
                if (this->unk_166 != 0) {
                    player->invincibilityTimer += 50;
                    this->unk_174 = 1;
                }
            }
        }
    }

    if ((player->stateFlags2 & 0x4000) && (player->unk_AE8 < 90)) {
        player->unk_AE8 = 90;
    }

    if ((this->unk_148 == 0) && (D_80A4C1C0 == 0) && ((this->unk_162 != 0) || (this->unk_1FC > 200.0f))) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        if (player->invincibilityTimer == 0) {
            CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->collider.base);
        }
    }
}

void func_80A4B0C8(EnWizFire* this, GlobalContext* globalCtx) {
    s32 pad;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->unk_162 == 0) && (this->unk_160 == 2)) {
        func_8012C28C(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_Scale(this->unk_1F0, this->unk_1F0, this->unk_1F0, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s8)this->unk_1FC);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 40, 30, 80);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_005190);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 215, 215, 215, (s8)this->unk_1FC);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 128);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, -globalCtx->state.frames & 0x7F,
                                    -globalCtx->state.frames & 0x7F, 0x20, 0x40, 1, globalCtx->state.frames & 0xFF,
                                    globalCtx->state.frames & 0xFF, 0x10, 0x10));

        Matrix_RotateY(0, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_005750);
    }

    func_80A4BF78(this, globalCtx);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A4B33C(EnWizFire* this, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if ((this->unk_162 == 0) && (this->unk_160 == 2)) {
        func_8012C28C(globalCtx->state.gfxCtx);
        func_8012C2DC(globalCtx->state.gfxCtx);
        Matrix_StatePush();
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_Scale(this->unk_1F0, this->unk_1F0, this->unk_1F0, MTXMODE_APPLY);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, -globalCtx->state.frames % 128, 0, 0x20, 0x20, 1,
                                    (globalCtx->state.frames * 2) % 128, 0, 0x20, 0x20));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 100, 40, 0, (s8)this->unk_1FC);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 245, 255, 128);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_003120);

        Matrix_StatePop();
        Matrix_StatePush();
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, globalCtx->state.frames % 128,
                                    (-globalCtx->state.frames * 6) % 256, 0x20, 0x40, 1,
                                    (globalCtx->state.frames * 2) % 128, (-globalCtx->state.frames * 6) % 256, 0x20,
                                    0x40));
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 80, 0, 0, (s8)this->unk_1FC);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 100);

        Matrix_Scale(this->unk_1F8, this->unk_1F8, this->unk_1F8, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_003640);

        Matrix_StatePop();
        Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z,
                                 MTXMODE_NEW);
        Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (-globalCtx->state.frames * 3) % 128, 0, 0x20, 0x20, 1,
                                    0, (-globalCtx->state.frames * 10) % 256, 0x20, 0x40));
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 100, 50, 0, 255);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 200, 235, 240, 128);

        Matrix_Scale(this->unk_1F4, this->unk_1F4, this->unk_1F4, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_003FC0);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void EnWizFire_Draw(Actor* thisx, GlobalContext* globalCtx2) {
    GlobalContext* globalCtx = globalCtx2;
    EnWizFire* this = THIS;
    s32 i;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);
    Matrix_StatePush();

    for (i = 9; i >= this->unk_16E; i--) {
        f32 temp_f20 = this->actor.scale.x - (i * -0.0019f);

        if (temp_f20 > 0.0f) {
            if (this->unk_166 == 0) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255 - (i * 25), 0, 255 - (i * 25));
                gDPSetEnvColor(POLY_XLU_DISP++, 255 - (i * 25), 0, 0, 0);
            } else {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255 - (i * 7), 255 - (i * 3), 255 - (i * 3), 255 - (i * 25));
                gDPSetEnvColor(POLY_XLU_DISP++, 220, 255, 235, 0);
            }

            Matrix_InsertTranslation(this->unk_178[i].x, this->unk_178[i].y + this->actor.shape.yOffset,
                                     this->unk_178[i].z, MTXMODE_NEW);
            Matrix_Scale(temp_f20, temp_f20, temp_f20, MTXMODE_APPLY);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_InsertZRotation_s(this->actor.world.rot.z, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_002B40);
        }
    }

    Matrix_StatePop();

    CLOSE_DISPS(globalCtx->state.gfxCtx);

    if (this->unk_166 == 0) {
        func_80A4B33C(this, globalCtx);
    } else {
        func_80A4B0C8(this, globalCtx);
    }
}

void func_80A4BAB4(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnWizFire* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    Matrix_InsertTranslation(this->actor.world.pos.x, this->actor.floorHeight + 20.0f, this->actor.world.pos.z,
                             MTXMODE_NEW);
    Matrix_Scale(this->unk_14C + this->unk_154, this->unk_14C + this->unk_158, this->unk_14C + this->unk_15C,
                 MTXMODE_APPLY);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, 0, 0, 0x20, 0x20, 1, this->unk_170 & 0x7F,
                                (-this->unk_170 * 10) & 0x7F, 0x20, 0x20));
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 100, 50, 0, (s8)this->unk_1FC);
    gDPSetEnvColor(POLY_XLU_DISP++, 200, 235, 245, 255);

    Matrix_InsertMatrix(&globalCtx->billboardMtxF, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_002630);

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}

void func_80A4BC74(EnWizFire* this, Vec3f* arg1, Vec3f* arg2) {
    s16 i;
    EnWizFireStruct* ptr = this->unk_254;

    for (i = 0; i < ARRAY_COUNT(this->unk_254); i++, ptr++) {
        if (ptr->unk_00 == 0) {
            ptr->unk_00 = 1;
            Math_Vec3f_Copy(&ptr->unk_1C, &gZeroVec3f);
            ptr->unk_01 = Rand_ZeroFloat(100.0f);
            ptr->unk_10 = *arg1;
            ptr->unk_28 = *arg2;
            ptr->unk_0C = (Rand_ZeroFloat(5.0f) + 20.0f) * 0.001f;
            ptr->unk_08 = 0;
            ptr->unk_06 = 0;
            break;
        }
    }
}

void func_80A4BDDC(EnWizFire* this, GlobalContext* globalCtx) {
    s32 i;
    EnWizFireStruct* ptr = &this->unk_254[0];

    for (i = 0; i < ARRAY_COUNT(this->unk_254); i++, ptr++) {
        if (ptr->unk_00 != 0) {
            ptr->unk_01++;

            ptr->unk_10.x += ptr->unk_1C.x;
            ptr->unk_10.y += ptr->unk_1C.y;
            ptr->unk_10.z += ptr->unk_1C.z;

            ptr->unk_1C.x += ptr->unk_28.x;
            ptr->unk_1C.y += ptr->unk_28.y;
            ptr->unk_1C.z += ptr->unk_28.z;

            if (ptr->unk_08 == 0) {
                ptr->unk_06 += 10;
                if (ptr->unk_06 >= 100) {
                    ptr->unk_08 = 1;
                }
            } else {
                ptr->unk_06 -= 8;
                if (ptr->unk_06 <= 0) {
                    ptr->unk_06 = 0;
                    ptr->unk_00 = 0;
                }
            }
        }
    }
}

void func_80A4BF78(EnWizFire* this, GlobalContext* globalCtx) {
    s16 i;
    u8 flag;
    EnWizFireStruct* ptr = &this->unk_254[0];
    GraphicsContext* gfxCtx = globalCtx->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(globalCtx->state.gfxCtx);
    func_8012C2DC(globalCtx->state.gfxCtx);

    flag = false;
    for (i = 0; i < ARRAY_COUNT(this->unk_254); i++, ptr++) {
        if (ptr->unk_00 != 0) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_000E70);
                flag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, ptr->unk_06);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(globalCtx->state.gfxCtx, 0, (ptr->unk_01 * 3) & 0x7F,
                                        (ptr->unk_01 * 0xF) & 0xFF, 0x20, 0x40, 1, 0, 0, 0x20, 0x20));

            Matrix_InsertTranslation(ptr->unk_10.x, ptr->unk_10.y, ptr->unk_10.z, MTXMODE_NEW);
            Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);
            Matrix_Scale(ptr->unk_0C, ptr->unk_0C, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetRenderMode(POLY_XLU_DISP++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BACK | G_FOG);
            gSPDisplayList(POLY_XLU_DISP++, object_wiz_DL_000FD8);
        }
    }

    CLOSE_DISPS(gfxCtx);
}
