#include "z_arms_hook.h"

#define FLAGS 0x00000030

#define THIS ((ArmsHook*)thisx)

void ArmsHook_Init(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Draw(Actor* thisx, GlobalContext* globalCtx);

void ArmsHook_Wait(ArmsHook* this, GlobalContext* globalCtx);
void ArmsHook_Shoot(ArmsHook* this, GlobalContext* globalCtx);

const ActorInit Arms_Hook_InitVars = {
    ACTOR_ARMS_HOOK,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArmsHook),
    (ActorFunc)ArmsHook_Init,
    (ActorFunc)ArmsHook_Destroy,
    (ActorFunc)ArmsHook_Update,
    (ActorFunc)ArmsHook_Draw,
};

ColliderQuadInit D_808C1BC0 = {
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

Vec3f D_808C1C10 = { 0.0f, 0.0f, 0.0f };
Vec3f D_808C1C1C = { 0.0f, 0.0f, 900.0f };
Vec3f D_808C1C28 = { 0.0f, 500.0f, -3000.0f };
Vec3f D_808C1C34 = { 0.0f, -500.0f, -3000.0f };
Vec3f D_808C1C40 = { 0.0f, 500.0f, 0.0f };
Vec3f D_808C1C4C = { 0.0f, -500.0f, 0.0f };

extern Gfx D_0601D960[];

void ArmsHook_SetupAction(ArmsHook* this, ArmsHookActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArmsHook_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    Collider_InitQuad(globalCtx, &this->collider);
    Collider_SetQuad(globalCtx, &this->collider, &this->actor, &D_808C1BC0);
    ArmsHook_SetupAction(this, ArmsHook_Wait);
    this->unk1E0 = this->actor.world.pos;
}

void ArmsHook_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~0x2000;
    }
    Collider_DestroyQuad(globalCtx, &this->collider);
}

void ArmsHook_Wait(ArmsHook* this, GlobalContext* globalCtx) {
    if (this->actor.parent == NULL) {
        ArmsHook_SetupAction(this, ArmsHook_Shoot);
        func_800B6C04(&this->actor, 20.0f);
        this->actor.parent = &PLAYER->actor;
        this->timer = 26;
    }
}

void func_808C1154(ArmsHook* this) {
    this->actor.child = this->actor.parent;
    this->actor.parent->parent = &this->actor;
}

s32 ArmsHook_AttachToPlayer(ArmsHook* this, Player* player) {
    player->actor.child = &this->actor;
    player->leftHandActor = &this->actor;
    if (this->actor.child != NULL) {
        player->actor.parent = this->actor.child = NULL;
        return 1;
    }
    return 0;
}

void ArmsHook_DetachHookFromActor(ArmsHook* this) {
    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~0x2000;
        this->grabbed = NULL;
    }
}

s32 ArmsHook_CheckForCancel(ArmsHook* this) {
    Player* player = (Player*)this->actor.parent;
    if (func_801240C8(player)) {
        if ((player->heldItemActionParam != player->itemActionParam) || ((player->actor.flags & 0x100)) ||
            ((player->stateFlags1 & 0x4000080))) {
            this->timer = 0;
            ArmsHook_DetachHookFromActor(this);
            Math_Vec3f_Copy(&this->actor.world.pos, &player->rightHandWorld.pos);
            return 1;
        }
    }
    return 0;
}

void ArmsHook_AttachHookToActor(ArmsHook* this, Actor* actor) {
    actor->flags |= 0x2000;
    this->grabbed = actor;
    Math_Vec3f_Diff(&actor->world.pos, &this->actor.world.pos, &this->unk1FC);
}

void ArmsHook_Shoot(ArmsHook* this, GlobalContext* globalCtx) {
    Player* player = PLAYER;

    if ((this->actor.parent == NULL) || (!func_801240C8(player))) {
        ArmsHook_DetachHookFromActor(this);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    func_800B8F98(&player->actor, NA_SE_IT_HOOKSHOT_CHAIN - SFX_FLAG);
    ArmsHook_CheckForCancel(this);

    if (this->timer != 0 && (this->collider.base.atFlags & AT_HIT) &&
        (this->collider.info.atHitInfo->elemType != ELEMTYPE_UNK4)) {
        Actor* touchedActor = this->collider.base.at;
        if ((touchedActor->update != NULL) && (touchedActor->flags & 0x600)) {
            if (this->collider.info.atHitInfo->bumperFlags & BUMP_HOOKABLE) {
                ArmsHook_AttachHookToActor(this, touchedActor);
                if ((touchedActor->flags & 0x400) == 0x400) {
                    func_808C1154(this);
                }
            }
        }
        this->timer = 0;
        func_8019F1C0(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_STICK_CRE);

        return;
    }

    if (DECR(this->timer) == 0) {
        Actor* grabbed;
        Vec3f bodyDistDiffVec;
        Vec3f newPos;
        f32 bodyDistDiff;
        f32 phi_f16;
        s32 pad;

        grabbed = this->grabbed;
        if (grabbed != NULL) {
            if ((grabbed->update == NULL) || (grabbed->flags & 0x2000) != 0x2000) {
                grabbed = NULL;
                this->grabbed = NULL;
            } else {
                if (this->actor.child != NULL) {
                    f32 sp94 = Actor_DistanceBetweenActors(&this->actor, grabbed);
                    f32 sp90 = sqrtf(SQ(this->unk1FC.x) + SQ(this->unk1FC.y) + SQ(this->unk1FC.z));
                    Math_Vec3f_Diff(&grabbed->world.pos, &this->unk1FC, &this->actor.world.pos);
                    if (50.0f < (sp94 - sp90)) {
                        ArmsHook_DetachHookFromActor(this);
                        grabbed = NULL;
                    }
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
                } else {
                    if (grabbed != NULL) {
                        velocity = 50.0f;
                    } else {
                        velocity = 200.0f;
                    }
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
            player->actor.world.rot.x =
                Math_FAtan2F(sqrtf(SQ(bodyDistDiffVec.x) + SQ(bodyDistDiffVec.z)), -bodyDistDiffVec.y);
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
        u32 bgId;
        Vec3f sp78;
        Vec3f prevFrameDiff;
        Vec3f sp60;

        Actor_SetVelocityAndMoveYRotationAndGravity(&this->actor);
        Math_Vec3f_Diff(&this->actor.world.pos, &this->actor.prevPos, &prevFrameDiff);
        Math_Vec3f_Sum(&this->unk1E0, &prevFrameDiff, &this->unk1E0);
        this->actor.shape.rot.x = Math_FAtan2F(this->actor.speedXZ, -this->actor.velocity.y);
        sp60.x = this->unk1EC.x - (this->unk1E0.x - this->unk1EC.x);
        sp60.y = this->unk1EC.y - (this->unk1E0.y - this->unk1EC.y);
        sp60.z = this->unk1EC.z - (this->unk1E0.z - this->unk1EC.z);
        if (func_800C55C4(&globalCtx->colCtx, &sp60, &this->unk1E0, &sp78, &poly, 1, 1, 1, 1, &bgId) != 0 &&
            (func_800B90AC(globalCtx, &this->actor, poly, bgId, &sp78) == 0 ||
             func_800C576C(&globalCtx->colCtx, &sp60, &this->unk1E0, &sp78, &poly, 1, 1, 1, 1, &bgId) != 0)) {
            f32 sp5C = poly->normal.x * (1 / SHT_MAX);
            f32 sp58 = poly->normal.z * (1 / SHT_MAX);

            Math_Vec3f_Copy(&this->actor.world.pos, &sp78);
            this->actor.world.pos.x += 10.0f * sp5C;
            this->actor.world.pos.z += 10.0f * sp58;
            this->timer = 1;
            if (func_800C9CEC(&globalCtx->colCtx, poly, bgId)) {
                {
                    DynaPolyActor* dynaPolyActor;
                    if (bgId != 0x32 && (dynaPolyActor = BgCheck_GetActorOfMesh(&globalCtx->colCtx, bgId)) != NULL) {
                        ArmsHook_AttachHookToActor(this, &dynaPolyActor->actor);
                    }
                }
                func_808C1154(this);
                func_8019F1C0(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_STICK_OBJ);
            } else {
                CollisionCheck_SpawnShieldParticlesMetal(globalCtx, &this->actor.world.pos);
                func_8019F1C0(&this->actor.projectedPos, NA_SE_IT_HOOKSHOT_REFLECT);
            }
        } else {
            if (CHECK_BTN_ANY(globalCtx->state.input[0].press.button,
                              BTN_A | BTN_B | BTN_R | BTN_CUP | BTN_CLEFT | BTN_CRIGHT | BTN_CDOWN)) {
                s32 pad;
                this->timer = 1;
            }
        }
    }
}

void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk1EC = this->unk1E0;
}

void ArmsHook_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;
    s32 pad;
    Player* player = PLAYER;
    Vec3f sp68;
    Vec3f sp5C;
    Vec3f sp50;
    f32 sp4C;
    f32 sp48;

    if (player->actor.draw != NULL && player->rightHandType == 0xB) {
        // OPEN_DISP macro
        {
            GraphicsContext* sp44 = globalCtx->state.gfxCtx;
            f32 f0;

            if ((ArmsHook_Shoot != this->actionFunc) || (this->timer <= 0)) {
                SysMatrix_MultiplyVector3fByState(&D_808C1C10, &this->unk1E0);
                SysMatrix_MultiplyVector3fByState(&D_808C1C28, &sp5C);
                SysMatrix_MultiplyVector3fByState(&D_808C1C34, &sp50);
                this->unk1C4 = 0;
            } else {
                SysMatrix_MultiplyVector3fByState(&D_808C1C1C, &this->unk1E0);
                SysMatrix_MultiplyVector3fByState(&D_808C1C40, &sp5C);
                SysMatrix_MultiplyVector3fByState(&D_808C1C4C, &sp50);
            }
            func_80126440(globalCtx, &this->collider.base, &this->unk1C4, &sp5C, &sp50);
            func_8012C28C(globalCtx->state.gfxCtx);
            func_80122868(globalCtx, player);

            gSPMatrix(sp44->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(sp44->polyOpa.p++, D_0601D960);
            SysMatrix_InsertTranslation(this->actor.world.pos.x, this->actor.world.pos.y, this->actor.world.pos.z,
                                        MTXMODE_NEW);
            Math_Vec3f_Diff(&player->rightHandWorld.pos, &this->actor.world.pos, &sp68);
            sp48 = SQ(sp68.x) + SQ(sp68.z);
            sp4C = sqrtf(sp48);
            Matrix_RotateY(Math_Atan2S(sp68.x, sp68.z), MTXMODE_APPLY);
            SysMatrix_InsertXRotation_s(Math_Atan2S(-sp68.y, sp4C), MTXMODE_APPLY);
            f0 = sqrtf(SQ(sp68.y) + sp48);
            Matrix_Scale(0.015f, 0.015f, f0 * 0.01f, MTXMODE_APPLY);
            gSPMatrix(sp44->polyOpa.p++, Matrix_NewMtx(globalCtx->state.gfxCtx),
                      G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
            gSPDisplayList(sp44->polyOpa.p++, D_040008D0);
            func_801229A0(globalCtx, player);
        }
    }
}
