/*
 * File: z_arms_hook.c
 * Overlay: ovl_Arms_Hook
 * Description: Hookshot tip
 */

#include "z_arms_hook.h"
#include "objects/gameplay_keep/gameplay_keep.h"
#include "objects/object_link_child/object_link_child.h"

#define FLAGS (ACTOR_FLAG_10 | ACTOR_FLAG_20)

#define THIS ((ArmsHook*)thisx)

void ArmsHook_Init(Actor* thisx, PlayState* play);
void ArmsHook_Destroy(Actor* thisx, PlayState* play);
void ArmsHook_Update(Actor* thisx, PlayState* play);
void ArmsHook_Draw(Actor* thisx, PlayState* play);

void ArmsHook_Wait(ArmsHook* this, PlayState* play);
void ArmsHook_Shoot(ArmsHook* this, PlayState* play);

ActorInit Arms_Hook_InitVars = {
    /**/ ACTOR_ARMS_HOOK,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ArmsHook),
    /**/ ArmsHook_Init,
    /**/ ArmsHook_Destroy,
    /**/ ArmsHook_Update,
    /**/ ArmsHook_Draw,
};

static ColliderQuadInit D_808C1BC0 = {
    {
        COLTYPE_NONE,
        AT_ON | AT_TYPE_PLAYER,
        AC_NONE,
        OC1_NONE,
        OC2_TYPE_PLAYER,
        COLSHAPE_QUAD,
    },
    {
        ELEMTYPE_UNK2,
        { 0x00000080, 0x00, 0x02 },
        { 0xF7CFFFFF, 0x00, 0x00 },
        TOUCH_ON | TOUCH_NEAREST | TOUCH_SFX_NORMAL,
        BUMP_NONE,
        OCELEM_NONE,
    },
    { { { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f } } },
};

void ArmsHook_SetupAction(ArmsHook* this, ArmsHookActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArmsHook_Init(Actor* thisx, PlayState* play) {
    ArmsHook* this = THIS;

    Collider_InitQuad(play, &this->collider);
    Collider_SetQuad(play, &this->collider, &this->actor, &D_808C1BC0);
    ArmsHook_SetupAction(this, ArmsHook_Wait);
    this->unk1E0 = this->actor.world.pos;
}

void ArmsHook_Destroy(Actor* thisx, PlayState* play) {
    ArmsHook* this = THIS;

    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~ACTOR_FLAG_2000;
    }
    Collider_DestroyQuad(play, &this->collider);
}

void ArmsHook_Wait(ArmsHook* this, PlayState* play) {
    if (this->actor.parent == NULL) {
        ArmsHook_SetupAction(this, ArmsHook_Shoot);
        Actor_SetSpeeds(&this->actor, 20.0f);
        this->actor.parent = &GET_PLAYER(play)->actor;
        this->timer = 26;
    }
}

void func_808C1154(ArmsHook* this) {
    this->actor.child = this->actor.parent;
    this->actor.parent->parent = &this->actor;
}

s32 ArmsHook_AttachToPlayer(ArmsHook* this, Player* player) {
    player->actor.child = &this->actor;
    player->heldActor = &this->actor;
    if (this->actor.child != NULL) {
        player->actor.parent = this->actor.child = NULL;
        return 1;
    }
    return 0;
}

void ArmsHook_DetachHookFromActor(ArmsHook* this) {
    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~ACTOR_FLAG_2000;
        this->grabbed = NULL;
    }
}

s32 ArmsHook_CheckForCancel(ArmsHook* this) {
    Player* player = (Player*)this->actor.parent;

    if (Player_IsHoldingHookshot(player)) {
        if ((player->itemAction != player->heldItemAction) || (player->actor.flags & ACTOR_FLAG_TALK_REQUESTED) ||
            (player->stateFlags1 & (PLAYER_STATE1_80 | PLAYER_STATE1_4000000))) {
            this->timer = 0;
            ArmsHook_DetachHookFromActor(this);
            Math_Vec3f_Copy(&this->actor.world.pos, &player->rightHandWorld.pos);
            return 1;
        }
    }
    return 0;
}

void ArmsHook_AttachHookToActor(ArmsHook* this, Actor* actor) {
    actor->flags |= ACTOR_FLAG_2000;
    this->grabbed = actor;
    Math_Vec3f_Diff(&actor->world.pos, &this->actor.world.pos, &this->unk1FC);
}

void ArmsHook_Shoot(ArmsHook* this, PlayState* play) {
    Player* player = GET_PLAYER(play);

    if ((this->actor.parent == NULL) || !Player_IsHoldingHookshot(player)) {
        ArmsHook_DetachHookFromActor(this);
        Actor_Kill(&this->actor);
        return;
    }

    Actor_PlaySfx_FlaggedCentered1(&player->actor, NA_SE_IT_HOOKSHOT_CHAIN - SFX_FLAG);
    ArmsHook_CheckForCancel(this);

    if ((this->timer != 0) && (this->collider.base.atFlags & AT_HIT) &&
        (this->collider.info.atHitInfo->elemType != ELEMTYPE_UNK4)) {
        Actor* touchedActor = this->collider.base.at;

        if ((touchedActor->update != NULL) && (touchedActor->flags & (ACTOR_FLAG_200 | ACTOR_FLAG_400))) {
            if (this->collider.info.atHitInfo->bumperFlags & BUMP_HOOKABLE) {
                ArmsHook_AttachHookToActor(this, touchedActor);
                if (CHECK_FLAG_ALL(touchedActor->flags, ACTOR_FLAG_400)) {
                    func_808C1154(this);
                }
            }
        }
        this->timer = 0;
        Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_STICK_CRE);

        return;
    }

    if (DECR(this->timer) == 0) {
        Actor* grabbed = this->grabbed;
        Vec3f bodyDistDiffVec;
        Vec3f newPos;
        f32 bodyDistDiff;
        f32 phi_f16;
        s32 pad;

        if (grabbed != NULL) {
            if ((grabbed->update == NULL) || !CHECK_FLAG_ALL(grabbed->flags, ACTOR_FLAG_2000)) {
                grabbed = NULL;
                this->grabbed = NULL;
            } else if (this->actor.child != NULL) {
                f32 sp94 = Actor_WorldDistXYZToActor(&this->actor, grabbed);
                f32 sp90 = sqrtf(SQXYZ(this->unk1FC));

                Math_Vec3f_Diff(&grabbed->world.pos, &this->unk1FC, &this->actor.world.pos);
                if (50.0f < (sp94 - sp90)) {
                    ArmsHook_DetachHookFromActor(this);
                    grabbed = NULL;
                }
            }
        }

        {
            f32 velocity;

            bodyDistDiff =
                Math_Vec3f_DistXYZAndStoreDiff(&player->rightHandWorld.pos, &this->actor.world.pos, &bodyDistDiffVec);
            if (bodyDistDiff < 30.0f) {
                velocity = 0.0f;
                phi_f16 = 0.0f;
            } else {
                if (this->actor.child != NULL) {
                    velocity = 30.0f;
                } else if (grabbed != NULL) {
                    velocity = 50.0f;
                } else {
                    velocity = 200.0f;
                }
                phi_f16 = bodyDistDiff - velocity;
                if (bodyDistDiff <= velocity) {
                    phi_f16 = 0.0f;
                }
                velocity = phi_f16 / bodyDistDiff;
            }

            newPos.x = bodyDistDiffVec.x * velocity;
            newPos.y = bodyDistDiffVec.y * velocity;
            newPos.z = bodyDistDiffVec.z * velocity;
        }

        if (this->actor.child == NULL) {
            Math_Vec3f_Sum(&player->rightHandWorld.pos, &newPos, &this->actor.world.pos);
            if (grabbed != NULL) {
                Math_Vec3f_Sum(&this->actor.world.pos, &this->unk1FC, &grabbed->world.pos);
            }
        } else {
            Math_Vec3f_Diff(&bodyDistDiffVec, &newPos, &player->actor.velocity);
            player->actor.world.rot.x = Math_Atan2S_XY(sqrtf(SQXZ(bodyDistDiffVec)), -bodyDistDiffVec.y);
        }
        if (phi_f16 < 50.0f) {
            ArmsHook_DetachHookFromActor(this);
            if (phi_f16 == 0.0f) {
                ArmsHook_SetupAction(this, ArmsHook_Wait);
                if (ArmsHook_AttachToPlayer(this, player)) {
                    Math_Vec3f_Diff(&this->actor.world.pos, &player->actor.world.pos, &player->actor.velocity);
                    player->actor.velocity.y -= 20.0f;
                }
            }
        }
    } else {
        CollisionPoly* poly;
        s32 bgId;
        Vec3f posResult;
        Vec3f prevFrameDiff;
        Vec3f sp60;

        Actor_MoveWithGravity(&this->actor);
        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.prevPos, &prevFrameDiff);
        Math_Vec3f_Sum(&this->unk1E0, &prevFrameDiff, &this->unk1E0);
        this->actor.shape.rot.x = Math_Atan2S_XY(this->actor.speed, -this->actor.velocity.y);
        sp60.x = this->unk1EC.x - (this->unk1E0.x - this->unk1EC.x);
        sp60.y = this->unk1EC.y - (this->unk1E0.y - this->unk1EC.y);
        sp60.z = this->unk1EC.z - (this->unk1E0.z - this->unk1EC.z);
        if (BgCheck_EntityLineTest1(&play->colCtx, &sp60, &this->unk1E0, &posResult, &poly, true, true, true, true,
                                    &bgId) &&
            (!func_800B90AC(play, &this->actor, poly, bgId, &posResult) ||
             BgCheck_ProjectileLineTest(&play->colCtx, &sp60, &this->unk1E0, &posResult, &poly, true, true, true, true,
                                        &bgId))) {
            f32 nx = COLPOLY_GET_NORMAL(poly->normal.x);
            f32 nz = COLPOLY_GET_NORMAL(poly->normal.z);

            Math_Vec3f_Copy(&this->actor.world.pos, &posResult);
            this->actor.world.pos.x += 10.0f * nx;
            this->actor.world.pos.z += 10.0f * nz;
            this->timer = 1;
            if (SurfaceType_IsHookshotSurface(&play->colCtx, poly, bgId)) {
                DynaPolyActor* dynaPolyActor;

                if ((bgId != BGCHECK_SCENE) && (dynaPolyActor = DynaPoly_GetActor(&play->colCtx, bgId)) != NULL) {
                    ArmsHook_AttachHookToActor(this, &dynaPolyActor->actor);
                }
                func_808C1154(this);
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_STICK_OBJ);
            } else {
                CollisionCheck_SpawnShieldParticlesMetal(play, &this->actor.world.pos);
                Audio_PlaySfx_AtPos(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_REFLECT);
            }
        } else if (CHECK_BTN_ANY(CONTROLLER1(&play->state)->press.button,
                                 BTN_A | BTN_B | BTN_R | BTN_CUP | BTN_CLEFT | BTN_CRIGHT | BTN_CDOWN)) {
            s32 pad;

            this->timer = 1;
        }
    }
}

void ArmsHook_Update(Actor* thisx, PlayState* play) {
    ArmsHook* this = THIS;

    this->actionFunc(this, play);
    this->unk1EC = this->unk1E0;
}

Vec3f D_808C1C10 = { 0.0f, 0.0f, 0.0f };
Vec3f D_808C1C1C = { 0.0f, 0.0f, 900.0f };
Vec3f D_808C1C28 = { 0.0f, 500.0f, -3000.0f };
Vec3f D_808C1C34 = { 0.0f, -500.0f, -3000.0f };
Vec3f D_808C1C40 = { 0.0f, 500.0f, 0.0f };
Vec3f D_808C1C4C = { 0.0f, -500.0f, 0.0f };

void ArmsHook_Draw(Actor* thisx, PlayState* play) {
    ArmsHook* this = THIS;
    f32 f0;
    Player* player = GET_PLAYER(play);

    if ((player->actor.draw != NULL) && (player->rightHandType == PLAYER_MODELTYPE_RH_HOOKSHOT)) {
        Vec3f sp68;
        Vec3f sp5C;
        Vec3f sp50;
        f32 sp4C;
        f32 sp48;

        OPEN_DISPS(play->state.gfxCtx);

        if ((ArmsHook_Shoot != this->actionFunc) || (this->timer <= 0)) {
            Matrix_MultVec3f(&D_808C1C10, &this->unk1E0);
            Matrix_MultVec3f(&D_808C1C28, &sp5C);
            Matrix_MultVec3f(&D_808C1C34, &sp50);
            this->weaponInfo.active = false;
        } else {
            Matrix_MultVec3f(&D_808C1C1C, &this->unk1E0);
            Matrix_MultVec3f(&D_808C1C40, &sp5C);
            Matrix_MultVec3f(&D_808C1C4C, &sp50);
        }
        func_80126440(play, &this->collider, &this->weaponInfo, &sp5C, &sp50);
        Gfx_SetupDL25_Opa(play->state.gfxCtx);
        func_80122868(play, player);

        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, object_link_child_DL_01D960);
        Matrix_Translate(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z, MTXMODE_NEW);
        Math_Vec3f_Diff(&player->rightHandWorld.pos, &this->actor.world.pos, &sp68);
        sp48 = SQXZ(sp68);
        sp4C = sqrtf(SQXZ(sp68));
        Matrix_RotateYS(Math_Atan2S(sp68.x, sp68.z), MTXMODE_APPLY);
        Matrix_RotateXS(Math_Atan2S(-sp68.y, sp4C), MTXMODE_APPLY);
        f0 = sqrtf(SQ(sp68.y) + sp48);
        Matrix_Scale(0.015f, 0.015f, f0 * 0.01f, MTXMODE_APPLY);
        gSPMatrix(POLY_OPA_DISP++, Matrix_NewMtx(play->state.gfxCtx), G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
        gSPDisplayList(POLY_OPA_DISP++, gHookshotChainDL);
        func_801229A0(play, player);

        CLOSE_DISPS(play->state.gfxCtx);
    }
}
