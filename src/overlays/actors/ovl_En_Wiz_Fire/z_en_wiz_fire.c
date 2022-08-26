/*
 * File: z_en_wiz_fire.c
 * Overlay: ovl_En_Wiz_Fire
 * Description: Wizrobe Fire/Ice Attack
 */

#include "z_en_wiz_fire.h"
#include "overlays/actors/ovl_En_Wiz/z_en_wiz.h"
#include "objects/object_wiz/object_wiz.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_4 | ACTOR_FLAG_10 | ACTOR_FLAG_8000000)

#define THIS ((EnWizFire*)thisx)

void EnWizFire_Init(Actor* thisx, PlayState* play);
void EnWizFire_Destroy(Actor* thisx, PlayState* play);
void EnWizFire_Update(Actor* thisx, PlayState* play);
void EnWizFire_Draw(Actor* thisx, PlayState* play);

void func_80A4984C(EnWizFire* this, PlayState* play);
void func_80A49A44(EnWizFire* this, PlayState* play);
void func_80A49F38(EnWizFire* this, PlayState* play);
void func_80A49FD8(EnWizFire* this, PlayState* play);
void func_80A4A11C(EnWizFire* this, PlayState* play);
void func_80A4A608(EnWizFire* this, PlayState* play);
void EnWizFire_DrawSmallFlame(Actor* thisx, PlayState* play);
void EnWizFire_InitializeEffect(EnWizFire* this, Vec3f* pos, Vec3f* accel);
void EnWizFire_UpdateEffects(EnWizFire* this, PlayState* play);
void EnWizFire_DrawEffects(EnWizFire* this, PlayState* play);

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

void EnWizFire_Init(Actor* thisx, PlayState* play) {
    EnWizFire* this = THIS;

    Collider_InitAndSetCylinder(play, &this->collider, &this->actor, &sCylinderInit);
    this->type = EN_WIZ_FIRE_GET_TYPE(&this->actor);
    this->actor.targetMode = 3;
    this->unk_172 = 10;
    this->alpha = 255.0f;
    this->actor.flags &= ~ACTOR_FLAG_1;

    if (!Player_HasMirrorShieldEquipped(play)) {
        this->collider.info.toucher.dmgFlags = 0x20000000;
    }

    switch (this->type) {
        case 4:
            this->unk_166 = 1;
            this->collider.info.toucher.damage = 8;
            this->collider.info.toucher.effect = 2;
            this->collider.info.bumper.dmgFlags = (0x1000000 | 0x800 | 0x200 | 0x2);
            this->type = 0;

        case 0:
            if (this->type == 4) {
                this->type = 0;
                this->collider.info.toucher.damage = 8;
            }

        case 1:
        case 3:
            this->actionFunc = func_80A4984C;
            break;

        case 2:
            this->actor.draw = EnWizFire_DrawSmallFlame;
            this->smallFlameScroll = Rand_S16Offset(0, 10000);
            this->unk_160 = 1;
            this->collider.info.toucher.damage = 2;
            this->actionFunc = func_80A49F38;
    }
}

void EnWizFire_Destroy(Actor* thisx, PlayState* play) {
    EnWizFire* this = THIS;

    if (this->type == 0) {
        play->envCtx.lightSettings.fogColor[2] = 0;
        play->envCtx.lightSettings.fogColor[1] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.fogColor[0] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor2[2] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor2[1] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor2[0] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor1[2] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor1[1] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.diffuseColor1[0] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.ambientColor[2] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.ambientColor[1] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.ambientColor[0] = play->envCtx.lightSettings.fogColor[2];
        play->envCtx.lightSettings.fogNear = play->envCtx.lightSettings.fogColor[2];
    }
    Collider_DestroyCylinder(play, &this->collider);
}

void func_80A4984C(EnWizFire* this, PlayState* play) {
    Vec3f sp44 = { 0.0f, 0.0f, 0.0f };
    s32 i;

    for (i = 0; i < ARRAY_COUNT(this->unk_178); i++) {
        this->unk_178[i] = this->actor.world.pos;
    }

    this->unk_16E = 0;
    Matrix_Push();
    Matrix_RotateYS(this->actor.world.rot.y, MTXMODE_NEW);
    Matrix_RotateXS(this->actor.world.rot.x, MTXMODE_APPLY);

    if (this->type != 0) {
        sp44.z = randPlusMinusPoint5Scaled(2.0f) + 8.0f;
    } else {
        sp44.z = 12.0f;
    }

    Matrix_MultVec3f(&sp44, &this->actor.velocity);
    Matrix_Pop();
    this->actor.world.rot.x = this->actor.world.rot.y = this->actor.world.rot.z = 0;
    this->unk_168 = 50;
    if (this->type != 0) {
        this->actor.velocity.y = 10.0f;
        this->actor.gravity = -1.0f;
        this->targetScale = 0.01f;
    } else {
        this->targetScale = 0.02f;
        this->unk_168 = 100;
    }
    this->unk_160 = 0;
    this->actionFunc = func_80A49A44;
}

void func_80A49A44(EnWizFire* this, PlayState* play) {
    Vec3f sp54 = { 0.0f, 0.0f, 0.0f };

    this->actor.world.rot.z += 5000;

    if (this->type != 0) {
        this->targetScale = 0.01f;
    } else {
        this->targetScale = 0.02f;
    }

    if ((this->unk_168 == 0) && (this->scale < 0.001f)) {
        Math_Vec3f_Copy(&this->actor.velocity, &gZeroVec3f);
        this->unk_160 = 3;
        this->unk_16A = 0;
        this->actionFunc = func_80A4A608;
        return;
    }

    if (this->unk_168 == 0) {
        this->targetScale = 0.0f;
    }

    Math_ApproachF(&this->scale, this->targetScale, 0.2f, 0.01f);

    if (this->unk_172 == 0) {
        if ((this->actor.bgCheckFlags & 8) && (this->type == 0) && (this->unk_168 != 0) &&
            (this->actor.bgCheckFlags & 8)) {
            D_80A4C1C0 = 0;
            this->unk_168 = 0;
            this->targetScale = 0.0f;
        }
    }

    if ((this->actor.bgCheckFlags & 1) && (this->unk_16A == 0)) {
        s32 i;
        s16 phi_s0;
        s32 temp;

        if (this->type == 1) {
            this->unk_16A = 10;

            Matrix_Push();
            Matrix_RotateYS((s16)randPlusMinusPoint5Scaled(0x100) + this->actor.world.rot.y, MTXMODE_NEW);
            sp54.z = randPlusMinusPoint5Scaled(2.0f) + 8.0f;
            Matrix_MultVec3f(&sp54, &this->actor.velocity);
            Matrix_Pop();

            this->actor.velocity.y = 6.0f;
            this->actor.gravity = -0.7f;

            if (this->unk_164 == 0) {
                Actor_Spawn(&play->actorCtx, play, ACTOR_EN_WIZ_FIRE, this->actor.world.pos.x,
                            this->actor.world.pos.y - 10.0f, this->actor.world.pos.z, 0, 0, 0, 2);
                this->unk_164 = 1;
            }

            this->unk_168 = 0;
            this->scale = 0.0f;
            Math_Vec3f_Copy(&this->actor.velocity, &gZeroVec3f);
            this->unk_160 = 3;
            this->unk_16A = 0;
            this->actionFunc = func_80A4A608;
            return;
        }

        if ((this->type == 0) && (this->unk_168 != 0)) {
            if (this->actor.floorBgId == BGCHECK_SCENE) {
                this->unk_16A = 100;
                if (this->unk_166 == 0) {
                    phi_s0 = 0;

                    for (i = 0; i < 5; i++) {
                        Actor_Spawn(&play->actorCtx, play, ACTOR_EN_WIZ_FIRE, this->actor.world.pos.x,
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
                this->scale = 0.0f;
                this->actionFunc = func_80A4A11C;
            }
            return;
        }
    }

    if ((this->type != 3) && (this->unk_168 != 0)) {
        if (this->collider.base.acFlags & AC_HIT) {
            this->collider.base.acFlags &= ~AC_HIT;
            if (this->collider.info.acHitInfo->toucher.dmgFlags == 0x1000) {
                this->unk_168 = 0;
                this->unk_148 = 1;
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }

        if (Player_HasMirrorShieldEquipped(play) && (this->collider.base.atFlags & AT_BOUNCED)) {
            Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_SHIELD_REFLECT_MG);
            this->collider.base.atFlags &= ~(AT_TYPE_ENEMY | AT_BOUNCED | AT_HIT);
            this->collider.base.atFlags |= AT_TYPE_PLAYER;
            this->collider.info.toucher.dmgFlags = 0x20;
            this->collider.info.toucher.damage = 2;
            this->unk_168 = 100;
            this->type = 3;
            this->actor.velocity.x *= -1.0f;
            this->actor.velocity.y *= -0.5f;
            this->actor.velocity.z *= -1.0f;

            if ((this->actor.parent != NULL) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
                (this->actor.parent->update != NULL)) {
                ((EnWiz*)this->actor.parent)->hasActiveProjectile = false;
            }
        }
    }
}

void func_80A49F38(EnWizFire* this, PlayState* play) {
    this->targetScale = 0.02f;
    this->unk_168 = Rand_S16Offset(50, 50);
    this->scaleMod.x = randPlusMinusPoint5Scaled(1.0f) * 0.007f;
    this->scaleMod.y = randPlusMinusPoint5Scaled(1.0f) * 0.005f;
    this->scaleMod.z = randPlusMinusPoint5Scaled(1.0f) * 0.007f;
    this->actionFunc = func_80A49FD8;
}

void func_80A49FD8(EnWizFire* this, PlayState* play) {
    if (this->unk_168 > 10) {
        Math_ApproachF(&this->scale, this->targetScale, 0.3f, 0.01f);
    } else {
        Math_ApproachF(&this->scale, 2.0f * this->targetScale, 0.2f, 0.002f);
        Math_ApproachZeroF(&this->alpha, 1.0f, 35.0f);
        if ((this->unk_168 == 0) && (this->alpha < 2.0f)) {
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
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }
    }

    if (this->unk_168 != 0) {
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BURN_OUT - SFX_FLAG);
    }
}

void func_80A4A11C(EnWizFire* this, PlayState* play) {
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

            Math_ApproachF(&this->poolScale, 0.022f, 0.3f, 0.01f);
            this->collider.dim.radius = this->poolScale * 4300.0f;
            this->collider.dim.height = 30;
            this->collider.dim.yShift = 15;
            EnWizFire_InitializeEffect(this, &sp34, &sp40);
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);
            return;
        }

        Math_ApproachF(&this->poolScale, 0.02f, 0.3f, 0.002f);
        Math_ApproachF(&this->fireSmokeScale, 0.02f, 0.3f, 0.002f);
        Math_ApproachF(&this->bigFlameScale, 0.02f, 0.3f, 0.2f);
        this->collider.dim.radius = this->poolScale * 4000.0f;
        this->collider.dim.height = this->bigFlameScale * 1850.0f;
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
                SoundSource_PlaySfxAtFixedWorldPos(play, &this->actor.world.pos, 50, NA_SE_EV_ICE_MELT);
            }
        }
        this->actor.world.pos.y = this->actor.floorHeight + 10.0f;
        Actor_SetFocus(&this->actor, 0.0f);
        return;
    }

    Math_ApproachZeroF(&this->unk_200, 0.2f, 3.0f);

    if (this->unk_166 == 1) {
        Math_ApproachZeroF(&this->poolScale, 0.046f, 0.001f);
        Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_ICE_FREEZE - SFX_FLAG);

        if (this->unk_164 == 0) {
            if ((this->actor.parent != NULL) && (this->actor.parent->id == ACTOR_EN_WIZ) && (this->poolScale < 0.05f)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                this->collider.dim.yShift = -15;
                this->unk_164 = 1;
                wiz->hasActiveProjectile = false;
            }
        }

        if ((this->unk_164 != 0) && (this->poolScale < 0.05f)) {
            Math_ApproachZeroF(&this->alpha, 1.0f, 5.0f);
        }

        if ((this->poolScale < 0.001f) && (this->lightSettingsScale < 0.001f)) {
            D_80A4C1C0 = 0;
            Actor_MarkForDeath(&this->actor);
        }
        return;
    }

    Math_ApproachZeroF(&this->bigFlameScale, 0.1f, 0.01f);

    if (this->bigFlameScale < 0.01f) {
        Math_ApproachZeroF(&this->alpha, 1.0f, 10.0f);
        if ((this->alpha < 10.0f) && (this->lightSettingsScale < 0.001f)) {
            D_80A4C1C0 = 0;
            if ((this->actor.parent != NULL) && (this->type == 0) && (this->actor.parent->id == ACTOR_EN_WIZ) &&
                (this->actor.parent->update != NULL)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                wiz->hasActiveProjectile = false;
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void func_80A4A608(EnWizFire* this, PlayState* play) {
    if (this->unk_16A == 0) {
        this->unk_16A = 2;
        this->unk_16E++;
        if (this->unk_16E >= 6) {
            if ((this->actor.parent != NULL) && (this->type == 0) && (this->actor.parent->id == ACTOR_EN_WIZ)) {
                EnWiz* wiz = (EnWiz*)this->actor.parent;

                D_80A4C1C0 = 0;
                if (wiz->actor.update != NULL) {
                    wiz->hasActiveProjectile = false;
                }
            }
            Actor_MarkForDeath(&this->actor);
        }
    }
}

void EnWizFire_Update(Actor* thisx, PlayState* play2) {
    static Color_RGB8 D_80A4C234[] = {
        { 100, 40, 40 }, { 180, 0x78, 80 }, { 155, 80, 80 },   { 125, 20, 0 },
        { 0, 0, 0 },     { 200, 250, 250 }, { 100, 250, 250 }, { 225, 255, 235 },
    };
    static Color_RGBA8 D_80A4C24C = { 250, 250, 250, 255 };
    static Color_RGBA8 D_80A4C250 = { 180, 180, 180, 255 };
    PlayState* play = play2;
    EnWizFire* this = THIS;
    Player* player = GET_PLAYER(play);
    s32 j;
    s16 temp_s0;
    s16 idx;

    Actor_SetScale(&this->actor, this->scale);
    EnWizFire_UpdateEffects(this, play);
    this->lightSettingsScale = this->unk_200 / 60.0f;

    if (this->type == 0) {
        Actor* wiz = this->actor.parent;

        if ((wiz != NULL) && (wiz->id == ACTOR_EN_WIZ) && (wiz->update != NULL) && (((EnWiz*)wiz)->type != 2)) {
            f32 phi_f0;

            idx = this->unk_166 * 4;

            phi_f0 = 970.0f;
            if (this->unk_166 == 0) {
                phi_f0 = 968.0f;
            }

            play->envCtx.lightSettings.fogNear = (phi_f0 - (s16)play->envCtx.unk_C4.fogNear) * this->lightSettingsScale;

            play->envCtx.lightSettings.ambientColor[0] =
                ((f32)D_80A4C234[idx].r - play->envCtx.unk_C4.ambientColor[0]) * this->lightSettingsScale;
            play->envCtx.lightSettings.ambientColor[1] =
                ((f32)D_80A4C234[idx].g - play->envCtx.unk_C4.ambientColor[1]) * this->lightSettingsScale;
            play->envCtx.lightSettings.ambientColor[2] =
                ((f32)D_80A4C234[idx].b - play->envCtx.unk_C4.ambientColor[2]) * this->lightSettingsScale;

            idx++;
            play->envCtx.lightSettings.diffuseColor1[0] =
                ((f32)D_80A4C234[idx].r - play->envCtx.unk_C4.diffuseColor1[0]) * this->lightSettingsScale;
            play->envCtx.lightSettings.diffuseColor1[1] =
                ((f32)D_80A4C234[idx].g - play->envCtx.unk_C4.diffuseColor1[1]) * this->lightSettingsScale;
            play->envCtx.lightSettings.diffuseColor1[2] =
                ((f32)D_80A4C234[idx].b - play->envCtx.unk_C4.diffuseColor1[2]) * this->lightSettingsScale;

            idx++;
            play->envCtx.lightSettings.diffuseColor2[0] =
                ((f32)D_80A4C234[idx].r - play->envCtx.unk_C4.diffuseColor[0]) * this->lightSettingsScale;
            play->envCtx.lightSettings.diffuseColor2[1] =
                ((f32)D_80A4C234[idx].g - play->envCtx.unk_C4.diffuseColor[1]) * this->lightSettingsScale;
            play->envCtx.lightSettings.diffuseColor2[2] =
                ((f32)D_80A4C234[idx].b - play->envCtx.unk_C4.diffuseColor[2]) * this->lightSettingsScale;

            idx++;
            play->envCtx.lightSettings.fogColor[0] =
                ((f32)D_80A4C234[idx].r - play->envCtx.unk_C4.fogColor[0]) * this->lightSettingsScale;
            play->envCtx.lightSettings.fogColor[1] =
                ((f32)D_80A4C234[idx].g - play->envCtx.unk_C4.fogColor[1]) * this->lightSettingsScale;
            play->envCtx.lightSettings.fogColor[2] =
                ((f32)D_80A4C234[idx].b - play->envCtx.unk_C4.fogColor[2]) * this->lightSettingsScale;
        }
    }

    this->smallFlameScroll++;

    this->actionFunc(this, play);

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

    Actor_UpdateBgCheckInfo(play, &this->actor, 20.0f, 5.0f, 10, 0x1D);

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
        if (this->type == 0) {
            sp54 = Rand_S16Offset(40, 20);
        }

        this->unk_16C = Rand_S16Offset(2, 2);

        for (i = 0; i < 2; i++) {
            temp_s0 = Rand_S16Offset(20, 20);
            sp58.x = ((f32)((Rand_ZeroOne() < 0.5f) ? -1 : 1) * temp_s0) + this->actor.world.pos.x;
            sp58.y = (Rand_ZeroOne() * 20.0f) + this->actor.floorHeight;
            temp_s0 = Rand_S16Offset(20, 20);
            sp58.z = ((f32)((Rand_ZeroOne() < .5f) ? -1 : 1) * temp_s0) + this->actor.world.pos.z;
            func_800B0DE0(play, &sp58, &sp64, &sp70, &D_80A4C24C, &D_80A4C250, Rand_S16Offset(350, 100), sp54);
        }
    }

    if (this->unk_160 < 2) {
        this->collider.dim.radius = (this->scale * 15.0f) + 25.0f;
        this->collider.dim.height = (this->scale * 15.0f) + 25.0f;
        this->collider.dim.yShift = (this->scale * -0.75f) - 5.0f;
    }

    if (this->type == 2) {
        this->collider.dim.radius = 10;
        this->collider.dim.height = this->scale * 5000.0f;
        this->collider.dim.yShift = 0;
    }

    if (this->collider.base.atFlags & AT_HIT) {
        this->collider.base.atFlags &= ~AT_HIT;
        if (this->type == 0) {
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

    if ((this->unk_148 == 0) && (D_80A4C1C0 == 0) && ((this->type != 0) || (this->alpha > 200.0f))) {
        Collider_UpdateCylinder(&this->actor, &this->collider);
        CollisionCheck_SetAC(play, &play->colChkCtx, &this->collider.base);
        if (player->invincibilityTimer == 0) {
            CollisionCheck_SetAT(play, &play->colChkCtx, &this->collider.base);
        }
    }
}

void EnWizFire_DrawIcePool(EnWizFire* this, PlayState* play) {
    s32 pad;

    OPEN_DISPS(play->state.gfxCtx);

    if ((this->type == 0) && (this->unk_160 == 2)) {
        func_8012C28C(play->state.gfxCtx);
        func_8012C2DC(play->state.gfxCtx);
        Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(this->poolScale, this->poolScale, this->poolScale, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255, 255, (s8)this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 40, 30, 80);
        gSPDisplayList(POLY_XLU_DISP++, gWizrobeIcePoolDL);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 215, 215, 215, (s8)this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 255, 255, 128);
        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, -play->state.frames & 0x7F, -play->state.frames & 0x7F, 32,
                                    64, 1, play->state.frames & 0xFF, play->state.frames & 0xFF, 16, 16));

        Matrix_RotateYS(0, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gWizrobeIcePoolShineDL);
    }

    EnWizFire_DrawEffects(this, play);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnWizFire_DrawFirePoolAndFlame(EnWizFire* this, PlayState* play2) {
    PlayState* play = play2;

    OPEN_DISPS(play->state.gfxCtx);

    if ((this->type == 0) && (this->unk_160 == 2)) {
        func_8012C28C(play->state.gfxCtx);
        func_8012C2DC(play->state.gfxCtx);
        Matrix_Push();
        Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_Scale(this->poolScale, this->poolScale, this->poolScale, MTXMODE_APPLY);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, -play->state.frames % 128, 0, 0x20, 0x20, 1,
                                    (play->state.frames * 2) % 128, 0, 0x20, 0x20));
        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 100, 40, 0, (s8)this->alpha);
        gDPSetEnvColor(POLY_XLU_DISP++, 255, 245, 255, 128);
        gSPDisplayList(POLY_XLU_DISP++, gWizrobeFirePoolDL);

        Matrix_Pop();
        Matrix_Push();
        Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, play->state.frames % 128, (-play->state.frames * 6) % 256,
                                    0x20, 0x40, 1, (play->state.frames * 2) % 128, (-play->state.frames * 6) % 256,
                                    0x20, 0x40));
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 80, 0, 0, (s8)this->alpha);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 0, 0, 0, 100);

        Matrix_Scale(this->fireSmokeScale, this->fireSmokeScale, this->fireSmokeScale, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gWizrobeFireSmokeDL);

        Matrix_Pop();
        Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight, this->actor.world.pos.z, MTXMODE_NEW);
        Matrix_ReplaceRotation(&play->billboardMtxF);

        gSPSegment(POLY_XLU_DISP++, 0x08,
                   Gfx_TwoTexScroll(play->state.gfxCtx, 0, (-play->state.frames * 3) % 128, 0, 0x20, 0x20, 1, 0,
                                    (-play->state.frames * 10) % 256, 0x20, 0x40));
        gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 100, 50, 0, 255);
        gDPPipeSync(POLY_XLU_DISP++);
        gDPSetEnvColor(POLY_XLU_DISP++, 200, 235, 240, 128);

        Matrix_Scale(this->bigFlameScale, this->bigFlameScale, this->bigFlameScale, MTXMODE_APPLY);

        gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_XLU_DISP++, gWizrobeBigFlameDL);
    }

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnWizFire_Draw(Actor* thisx, PlayState* play2) {
    PlayState* play = play2;
    EnWizFire* this = THIS;
    s32 i;

    OPEN_DISPS(play->state.gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);
    Matrix_Push();

    for (i = 9; i >= this->unk_16E; i--) {
        f32 scale = this->actor.scale.x - (i * -0.0019f);

        if (scale > 0.0f) {
            if (this->unk_166 == 0) {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255, 255 - (i * 25), 0, 255 - (i * 25));
                gDPSetEnvColor(POLY_XLU_DISP++, 255 - (i * 25), 0, 0, 0);
            } else {
                gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 255 - (i * 7), 255 - (i * 3), 255 - (i * 3), 255 - (i * 25));
                gDPSetEnvColor(POLY_XLU_DISP++, 220, 255, 235, 0);
            }

            Matrix_Translate(this->unk_178[i].x, this->unk_178[i].y + this->actor.shape.yOffset, this->unk_178[i].z,
                             MTXMODE_NEW);
            Matrix_Scale(scale, scale, scale, MTXMODE_APPLY);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_RotateZS(this->actor.world.rot.z, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_XLU_DISP++, gWizrobeMagicProjectileDL);
        }
    }

    Matrix_Pop();

    CLOSE_DISPS(play->state.gfxCtx);

    if (this->unk_166 == 0) {
        EnWizFire_DrawFirePoolAndFlame(this, play);
    } else {
        EnWizFire_DrawIcePool(this, play);
    }
}

void EnWizFire_DrawSmallFlame(Actor* thisx, PlayState* play) {
    s32 pad;
    EnWizFire* this = THIS;

    OPEN_DISPS(play->state.gfxCtx);

    Matrix_Translate(this->actor.world.pos.x, this->actor.floorHeight + 20.0f, this->actor.world.pos.z, MTXMODE_NEW);
    Matrix_Scale(this->scale + this->scaleMod.x, this->scale + this->scaleMod.y, this->scale + this->scaleMod.z,
                 MTXMODE_APPLY);

    gSPSegment(POLY_XLU_DISP++, 0x08,
               Gfx_TwoTexScroll(play->state.gfxCtx, 0, 0, 0, 32, 32, 1, this->smallFlameScroll & 0x7F,
                                (-this->smallFlameScroll * 10) & 0x7F, 32, 32));
    gDPSetPrimColor(POLY_XLU_DISP++, 0, 0x80, 100, 50, 0, (s8)this->alpha);
    gDPSetEnvColor(POLY_XLU_DISP++, 200, 235, 245, 255);

    Matrix_Mult(&play->billboardMtxF, MTXMODE_APPLY);

    gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPDisplayList(POLY_XLU_DISP++, gWizrobeSmallFlameDL);

    CLOSE_DISPS(play->state.gfxCtx);
}

void EnWizFire_InitializeEffect(EnWizFire* this, Vec3f* pos, Vec3f* accel) {
    s16 i;
    EnWizFireEffect* effect = &this->effects[0];

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (!effect->isEnabled) {
            effect->isEnabled = true;
            Math_Vec3f_Copy(&effect->velocity, &gZeroVec3f);
            effect->smokeScroll = Rand_ZeroFloat(100.0f);
            effect->pos = *pos;
            effect->accel = *accel;
            effect->scale = (Rand_ZeroFloat(5.0f) + 20.0f) * 0.001f;
            effect->shouldDecreaseAlpha = 0;
            effect->alpha = 0;
            break;
        }
    }
}

void EnWizFire_UpdateEffects(EnWizFire* this, PlayState* play) {
    s32 i;
    EnWizFireEffect* effect = &this->effects[0];

    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->isEnabled) {
            effect->smokeScroll++;

            effect->pos.x += effect->velocity.x;
            effect->pos.y += effect->velocity.y;
            effect->pos.z += effect->velocity.z;

            effect->velocity.x += effect->accel.x;
            effect->velocity.y += effect->accel.y;
            effect->velocity.z += effect->accel.z;

            if (!effect->shouldDecreaseAlpha) {
                effect->alpha += 10;
                if (effect->alpha >= 100) {
                    effect->shouldDecreaseAlpha = true;
                }
            } else {
                effect->alpha -= 8;
                if (effect->alpha <= 0) {
                    effect->alpha = 0;
                    effect->isEnabled = false;
                }
            }
        }
    }
}

void EnWizFire_DrawEffects(EnWizFire* this, PlayState* play) {
    s16 i;
    u8 flag;
    EnWizFireEffect* effect = &this->effects[0];
    GraphicsContext* gfxCtx = play->state.gfxCtx;

    OPEN_DISPS(gfxCtx);

    func_8012C28C(play->state.gfxCtx);
    func_8012C2DC(play->state.gfxCtx);

    flag = false;
    for (i = 0; i < ARRAY_COUNT(this->effects); i++, effect++) {
        if (effect->isEnabled) {
            if (!flag) {
                gSPDisplayList(POLY_XLU_DISP++, gWizrobeIceSmokeMaterialDL);
                flag++;
            }

            gDPSetPrimColor(POLY_XLU_DISP++, 0, 0, 195, 225, 235, effect->alpha);
            gSPSegment(POLY_XLU_DISP++, 0x08,
                       Gfx_TwoTexScroll(play->state.gfxCtx, 0, (effect->smokeScroll * 3) & 0x7F,
                                        (effect->smokeScroll * 0xF) & 0xFF, 32, 64, 1, 0, 0, 32, 32));

            Matrix_Translate(effect->pos.x, effect->pos.y, effect->pos.z, MTXMODE_NEW);
            Matrix_ReplaceRotation(&play->billboardMtxF);
            Matrix_Scale(effect->scale, effect->scale, 1.0f, MTXMODE_APPLY);

            gSPMatrix(POLY_XLU_DISP++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gDPSetRenderMode(POLY_XLU_DISP++, G_RM_PASS, G_RM_AA_ZB_XLU_SURF2);
            gSPClearGeometryMode(POLY_XLU_DISP++, G_CULL_BACK | G_FOG);
            gSPDisplayList(POLY_XLU_DISP++, gWizrobeIceSmokeModelDL);
        }
    }

    CLOSE_DISPS(gfxCtx);
}
