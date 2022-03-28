/*
 * File: z_en_bombf.c
 * Overlay: ovl_En_Bombf
 * Description: Bomb flower
 */

#include "z_en_bombf.h"
#include "objects/object_bombf/object_bombf.h"

#define FLAGS (ACTOR_FLAG_1 | ACTOR_FLAG_10)

#define THIS ((EnBombf*)thisx)

void EnBombf_Init(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Destroy(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Update(Actor* thisx, GlobalContext* globalCtx);
void EnBombf_Draw(Actor* thisx, GlobalContext* globalCtx);

void EnBombf_SetupAction(EnBombf* this, EnBombfActionFunc actionFunc);
void func_808AEAB8(EnBombf* this, s16 arg1);
void func_808AEAE0(EnBombf* this, GlobalContext* globalCtx);
void func_808AEE3C(EnBombf* this, GlobalContext* globalCtx);
void func_808AEF68(EnBombf* this, GlobalContext* globalCtx);
void func_808AEFD4(EnBombf* this, GlobalContext* globalCtx);

const ActorInit En_Bombf_InitVars = {
    ACTOR_EN_BOMBF,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_BOMBF,
    sizeof(EnBombf),
    (ActorFunc)EnBombf_Init,
    (ActorFunc)EnBombf_Destroy,
    (ActorFunc)EnBombf_Update,
    (ActorFunc)EnBombf_Draw,
};

static ColliderCylinderInit sCylinderInit = {
    {
        COLTYPE_NONE,
        AT_NONE,
        AC_ON | AC_TYPE_PLAYER | AC_TYPE_OTHER,
        OC1_ON | OC1_TYPE_ALL,
        OC2_TYPE_2,
        COLSHAPE_CYLINDER,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000000, 0x00, 0x00 },
        { 0x00013A28, 0x00, 0x00 },
        TOUCH_NONE | TOUCH_SFX_NORMAL,
        BUMP_ON,
        OCELEM_ON,
    },
    { 9, 18, 10, { 0, 0, 0 } },
};

static ColliderJntSphElementInit sJntSphElementsInit[1] = {
    {
        {
            ELEMTYPE_UNK0,
            { 0x00000008, 0x00, 0x08 },
            { 0x00000000, 0x00, 0x00 },
            TOUCH_ON | TOUCH_SFX_NONE,
            BUMP_NONE,
            OCELEM_NONE,
        },
        { 0, { { 0, 0, 0 }, 0 }, 100 },
    },
};

static ColliderJntSphInit sJntSphInit = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_ALL,
        AC_NONE,
        OC1_NONE,
        OC2_NONE,
        COLSHAPE_JNTSPH,
    },
    1,
    sJntSphElementsInit,
};

void EnBombf_SetupAction(EnBombf* this, EnBombfActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void EnBombf_Init(Actor* thisx, GlobalContext* globalCtx2) {
    f32 yOffset = 0.0f;
    GlobalContext* globalCtx = globalCtx2;
    EnBombf* this = THIS;

    Actor_SetScale(thisx, 0.01f);
    this->unk_1F8 = 1;

    Collider_InitCylinder(globalCtx, &this->colliderCylinder);
    Collider_InitJntSph(globalCtx, &this->colliderJntSph);
    Collider_SetCylinder(globalCtx, &this->colliderCylinder, thisx, &sCylinderInit);
    Collider_SetJntSph(globalCtx, &this->colliderJntSph, thisx, &sJntSphInit, this->colliderJntSphElements);

    if (ENBOMBF_GET(thisx) == ENBOMBF_0) {
        yOffset = 1000.0f;
    }

    ActorShape_Init(&thisx->shape, yOffset, ActorShadow_DrawCircle, 12.0f);

    thisx->focus.pos = thisx->world.pos;
    thisx->colChkInfo.cylRadius = 10;
    thisx->colChkInfo.cylHeight = 10;
    thisx->targetMode = 0;

    if (ENBOMBF_GET(thisx) == ENBOMBF_0) {
        this->timer = 140;
        this->unk_1FE = 15;
        thisx->gravity = -1.5f;
        func_800BC154(globalCtx, &globalCtx->actorCtx, thisx, 3);
        thisx->colChkInfo.mass = 200;
        thisx->flags &= ~ACTOR_FLAG_1;
        EnBombf_SetupAction(this, func_808AEE3C);
    } else {
        thisx->colChkInfo.mass = MASS_IMMOVABLE;
        this->unk_1FC = 1;
        this->unk_204 = 1.0f;
        func_808AEAB8(this, ENBOMBF_GET(thisx));
    }

    thisx->uncullZoneScale += 31000.0f;
    thisx->uncullZoneForward += 31000.0f;
}

void EnBombf_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    EnBombf* this = THIS;

    Collider_DestroyCylinder(globalCtx, &this->colliderCylinder);
    Collider_DestroyJntSph(globalCtx, &this->colliderJntSph);
}

void func_808AEAB8(EnBombf* this, s16 arg1) {
    EnBombf_SetupAction(this, func_808AEAE0);
}

void func_808AEAE0(EnBombf* this, GlobalContext* globalCtx) {
    s32 pad;
    s32 pad2;
    EnBombf* bombf;
    Player* player = GET_PLAYER(globalCtx);
    s32 pad3;

    if (this->unk_204 >= 1.0f) {
        if (Actor_HasParent(&this->actor, globalCtx)) {
            bombf = (EnBombf*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOMBF, this->actor.world.pos.x,
                                          this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, ENBOMBF_0);
            if (bombf != NULL) {
                func_800B8C20(&this->actor, &bombf->actor, globalCtx);
                this->timer = 180;
                this->unk_204 = 0.0f;
                Actor_PlaySfxAtPos(&this->actor, NA_SE_PL_PULL_UP_ROCK);
                this->actor.flags &= ~ACTOR_FLAG_1;
            } else {
                player->actor.child = NULL;
                player->heldActor = NULL;
                player->interactRangeActor = NULL;
                this->actor.parent = NULL;
                player->stateFlags1 &= ~0x800;
            }
        } else if ((this->colliderCylinder.base.acFlags & AC_HIT) &&
                   ((this->colliderCylinder.info.acHitInfo->toucher.dmgFlags & 0x13828) ||
                    ((this->colliderCylinder.info.acHitInfo->toucher.dmgFlags & 0x200) &&
                     (player->transformation == PLAYER_FORM_GORON) && (player->actor.speedXZ > 15.0f)))) {
            this->colliderCylinder.base.acFlags &= ~AC_HIT;
            if (this->colliderCylinder.base.ac->category != ACTORCAT_BOSS) {
                bombf = (EnBombf*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOMBF, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, ENBOMBF_0);
                if (bombf != NULL) {
                    bombf->unk_1F8 = 1;
                    bombf->timer = 0;
                    this->timer = 180;
                    this->actor.flags &= ~ACTOR_FLAG_1;
                    this->unk_204 = 0.0f;
                }
            }
        } else {
            if (func_80123F48(globalCtx, &this->actor.world.pos, 30.0f, 50.0f)) {
                bombf = (EnBombf*)Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_BOMBF, this->actor.world.pos.x,
                                              this->actor.world.pos.y, this->actor.world.pos.z, 0, 0, 0, ENBOMBF_0);
                if (bombf != NULL) {
                    bombf->timer = 100;
                    this->timer = 180;
                    this->actor.flags &= ~ACTOR_FLAG_1;
                    this->unk_204 = 0.0f;
                }
            } else {
                if (!Actor_HasParent(&this->actor, globalCtx)) {
                    Actor_LiftActor(&this->actor, globalCtx);
                    return;
                }
                player->actor.child = NULL;
                player->heldActor = NULL;
                player->interactRangeActor = NULL;
                this->actor.parent = NULL;
                player->stateFlags1 &= ~0x800;
                this->actor.world.pos = this->actor.home.pos;
            }
        }
    } else {
        if (this->timer == 0) {
            this->unk_204 += 0.05f;
            if (this->unk_204 >= 1.0f) {
                this->actor.flags |= ACTOR_FLAG_1;
            }
        }

        if (Actor_HasParent(&this->actor, globalCtx)) {
            player->actor.child = NULL;
            player->heldActor = NULL;
            player->interactRangeActor = NULL;
            this->actor.parent = NULL;
            player->stateFlags1 &= ~0x800;
            this->actor.world.pos = this->actor.home.pos;
        }
    }
}

void func_808AEE3C(EnBombf* this, GlobalContext* globalCtx) {
    if (Actor_HasParent(&this->actor, globalCtx)) {
        this->unk_204 = 0.0f;
        EnBombf_SetupAction(this, func_808AEF68);
        this->actor.room = -1;
        return;
    }

    this->unk_204 = 1.0f;
    if (!(this->actor.bgCheckFlags & 1)) {
        Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 1.0f, 0.025f, 0.0f);
        return;
    }

    Math_SmoothStepToF(&this->actor.speedXZ, 0.0f, 1.0f, 1.5f, 0.0f);
    if (this->actor.bgCheckFlags & 2) {
        func_800B8EF4(globalCtx, &this->actor);
        if (this->actor.velocity.y < -6.0f) {
            this->actor.velocity.y *= -0.3f;
            this->actor.bgCheckFlags &= ~1;
        }
    } else if (this->timer >= 4) {
        Actor_LiftActor(&this->actor, globalCtx);
    }
}

void func_808AEF68(EnBombf* this, GlobalContext* globalCtx) {
    if (Actor_HasNoParent(&this->actor, globalCtx)) {
        EnBombf_SetupAction(this, func_808AEE3C);
        this->actor.bgCheckFlags &= ~1;
        func_808AEE3C(this, globalCtx);
    } else {
        this->actor.velocity.y = 0.0f;
    }
}

void func_808AEFD4(EnBombf* this, GlobalContext* globalCtx) {
    if (this->colliderJntSph.elements->dim.modelSphere.radius == 0) {
        this->actor.flags |= ACTOR_FLAG_20;
        func_8013ECE0(this->actor.xzDistToPlayer, 255, 20, 150);
    }

    this->colliderJntSph.elements->dim.modelSphere.radius = 100;
    this->colliderJntSph.elements->dim.worldSphere.radius = 100;

    if (ENBOMBF_GET(&this->actor) == ENBOMBF_1) {
        CollisionCheck_SetAT(globalCtx, &globalCtx->colChkCtx, &this->colliderJntSph.base);
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
        Player* player = GET_PLAYER(globalCtx);

        if ((player->stateFlags1 & 0x800) && (&this->actor == player->heldActor)) {
            player->actor.child = NULL;
            player->heldActor = NULL;
            player->interactRangeActor = NULL;
            player->stateFlags1 &= ~0x800;
        }
        Actor_MarkForDeath(&this->actor);
    }
}

void EnBombf_Update(Actor* thisx, GlobalContext* globalCtx) {
    Vec3f sp8C = { 0.0f, 0.0f, 0.0f };
    Vec3f sp80 = { 0.0f, 0.1f, 0.0f };
    Vec3f sp74 = { 0.0f, 0.0f, 0.0f };
    Vec3f sp68;
    Vec3f sp5C = { 0.0f, 0.6f, 0.0f };
    Color_RGBA8 sp58 = { 255, 255, 255, 255 };
    EnBombf* this = THIS;
    s32 pad;

    if ((this->unk_1F8 != 0) && (this->timer != 0)) {
        this->timer--;
    }

    if ((this->unk_1FC == 0) && !Actor_HasParent(&this->actor, globalCtx) &&
        ((this->actor.xzDistToPlayer >= 20.0f) || (fabsf(this->actor.playerHeightRel) >= 80.0f))) {
        this->unk_1FC = 1;
    }

    this->actionFunc(this, globalCtx);

    if (ENBOMBF_GET(&this->actor) == ENBOMBF_0) {
        Actor_MoveWithGravity(&this->actor);
    }

    if (this->actor.gravity != 0.0f) {
        DREG(6) = 1;
        Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 5.0f, 10.0f, 0.0f, 0x1F);
        DREG(6) = 0;
    }

    if (ENBOMBF_GET(&this->actor) == ENBOMBF_0) {
        if ((this->actor.velocity.y > 0.0f) && (this->actor.bgCheckFlags & 0x10)) {
            this->actor.velocity.y = -this->actor.velocity.y;
        }

        if ((this->actor.speedXZ != 0.0f) && (this->actor.bgCheckFlags & 8)) {
            s16 yDiff = BINANG_SUB(this->actor.wallYaw, this->actor.world.rot.y);

            if (ABS_ALT(yDiff) > 0x4000) {
                this->actor.world.rot.y =
                    BINANG_SUB(this->actor.wallYaw - this->actor.world.rot.y + this->actor.wallYaw, 0x8000);
            }
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMB_BOUND);
            Actor_MoveWithGravity(&this->actor);
            DREG(6) = 1;
            Actor_UpdateBgCheckInfo(globalCtx, &this->actor, 5.0f, 10.0f, 0.0f, 0x1F);
            DREG(6) = 0;
            this->actor.speedXZ *= 0.7f;
            this->actor.bgCheckFlags &= ~8;
        }

        if ((this->colliderCylinder.base.acFlags & AC_HIT) ||
            ((this->colliderCylinder.base.ocFlags1 & OC1_HIT) && (this->colliderCylinder.base.oc->category == 5))) {
            this->unk_1F8 = 1;
            this->timer = 0;
        } else if ((this->timer > 100) && func_80123F48(globalCtx, &this->actor.world.pos, 30.0f, 50.0f)) {
            this->timer = 100;
        }

        if (this->unk_1F8 != 0) {
            sp5C.y = 0.2f;
            sp68 = this->actor.world.pos;
            sp68.y += 25.0f;

            if (this->timer < 127) {
                if ((globalCtx->gameplayFrames % 2) == 0) {
                    EffectSsGSpk_SpawnFuse(globalCtx, &this->actor, &sp68, &sp8C, &sp74);
                }
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_IGNIT - SFX_FLAG);
                sp68.y += 3.0f;
                func_800B0DE0(globalCtx, &sp68, &sp8C, &sp5C, &sp58, &sp58, 0x32, 5);
            }

            if ((this->timer == 3) || (this->timer == 30) || (this->timer == 50) || (this->timer == 70)) {
                this->unk_1FE = this->unk_1FE >> 1;
            }

            if ((this->timer < 100) && (this->timer & (this->unk_1FE + 1))) {
                Math_SmoothStepToF(&this->unk_200, 150.0f, 1.0f, 150.0f / this->unk_1FE, 0.0f);
            } else {
                Math_SmoothStepToF(&this->unk_200, 0.0f, 1.0f, 150.0f / this->unk_1FE, 0.0f);
            }

            if (this->timer < 3) {
                Actor_SetScale(&this->actor, this->actor.scale.x + 0.002f);
            }

            if (this->timer == 0) {
                sp68 = this->actor.world.pos;
                sp68.y += 10.0f;

                if (Actor_HasParent(&this->actor, globalCtx)) {
                    sp68.y += 30.0f;
                }

                Actor_Spawn(&globalCtx->actorCtx, globalCtx, ACTOR_EN_CLEAR_TAG, sp68.x, sp68.y, sp68.z, 0, 0, 0,
                            CLEAR_TAG_SMALL_EXPLOSION);
                Actor_PlaySfxAtPos(&this->actor, NA_SE_IT_BOMB_EXPLOSION);

                globalCtx->envCtx.lightSettings.diffuseColor1[0] = globalCtx->envCtx.lightSettings.diffuseColor1[1] =
                    globalCtx->envCtx.lightSettings.diffuseColor1[2] = 250;
                globalCtx->envCtx.lightSettings.ambientColor[0] = globalCtx->envCtx.lightSettings.ambientColor[1] =
                    globalCtx->envCtx.lightSettings.ambientColor[2] = 250;

                func_800DFD04(&globalCtx->mainCamera, 2, 11, 8);

                this->actor.params = ENBOMBF_1;
                this->timer = 10;
                this->actor.flags |= ACTOR_FLAG_20;

                EnBombf_SetupAction(this, func_808AEFD4);
            }
        }
    }

    this->actor.focus.pos = this->actor.world.pos;
    this->actor.focus.pos.y += 10.0f;

    if (ENBOMBF_GET(&this->actor) <= ENBOMBF_0) {
        Collider_UpdateCylinder(&this->actor, &this->colliderCylinder);
        if ((this->unk_204 >= 1.0f) && (this->unk_1FC != 0)) {
            CollisionCheck_SetOC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
        }
        CollisionCheck_SetAC(globalCtx, &globalCtx->colChkCtx, &this->colliderCylinder.base);
    }

    if ((this->actor.scale.x >= 0.01f) && (ENBOMBF_GET(&this->actor) != ENBOMBF_1)) {
        if (this->actor.depthInWater >= 20.0f) {
            SoundSource_PlaySfxAtFixedWorldPos(globalCtx, &this->actor.world.pos, 30, NA_SE_IT_BOMB_UNEXPLOSION);
            Actor_MarkForDeath(&this->actor);
        } else if (this->actor.bgCheckFlags & 0x40) {
            this->actor.bgCheckFlags &= ~0x40;
            Actor_PlaySfxAtPos(&this->actor, NA_SE_EV_BOMB_DROP_WATER);
        }
    }
}

Gfx* func_808AF86C(GraphicsContext* gfxCtx, GlobalContext* globalCtx) {
    Gfx* head = GRAPH_ALLOC(gfxCtx, sizeof(Gfx) * 6);
    Gfx* gfx = head;

    Matrix_NormalizeXYZ(&globalCtx->billboardMtxF);

    gSPMatrix(gfx++, Matrix_NewMtx(gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    gSPEndDisplayList(gfx++);

    return head;
}

void EnBombf_Draw(Actor* thisx, GlobalContext* globalCtx) {
    s32 pad;
    EnBombf* this = THIS;

    OPEN_DISPS(globalCtx->state.gfxCtx);

    if (ENBOMBF_GET(&this->actor) <= ENBOMBF_0) {
        func_8012C28C(globalCtx->state.gfxCtx);

        if (ENBOMBF_GET(&this->actor) != ENBOMBF_0) {
            gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(POLY_OPA_DISP++, object_bombf_DL_000340);
            gSPDisplayList(POLY_OPA_DISP++, object_bombf_DL_000530);

            Matrix_InsertTranslation(0.0f, 1000.0f, 0.0f, MTXMODE_APPLY);
            Matrix_Scale(this->unk_204, this->unk_204, this->unk_204, MTXMODE_APPLY);
        }

        gDPSetPrimColor(POLY_OPA_DISP++, 0, 0, 200, 255, 200, 255);
        gDPPipeSync(POLY_OPA_DISP++);
        gDPSetEnvColor(POLY_OPA_DISP++, (s8)this->unk_200, 20, 10, 0);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(globalCtx->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);

        {
            Gfx* gfx = func_808AF86C(globalCtx->state.gfxCtx, globalCtx);

            gSPSegment(POLY_OPA_DISP++, 0x08, Lib_SegmentedToVirtual(gfx));
        }

        gSPDisplayList(POLY_OPA_DISP++, object_bombf_DL_000408);
    } else {
        Collider_UpdateSpheres(0, &this->colliderJntSph);
    }

    CLOSE_DISPS(globalCtx->state.gfxCtx);
}
