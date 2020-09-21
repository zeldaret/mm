#include "global.h"
#include "z_arms_hook.h"

#define FLAGS 0x00000030

#define THIS ((ArmsHook*)thisx)

void ArmsHook_Init(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx);
void ArmsHook_Draw(Actor* thisx, GlobalContext* globalCtx);

void func_808C10F8(ArmsHook* this, GlobalContext* globalCtx);
void func_808C12A4(ArmsHook* this, GlobalContext* globalCtx);

/*
const ActorInit Arms_Hook_InitVars = {
    ACTOR_ARMS_HOOK,
    ACTORTYPE_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ArmsHook),
    (ActorFunc)ArmsHook_Init,
    (ActorFunc)ArmsHook_Destroy,
    (ActorFunc)ArmsHook_Update,
    (ActorFunc)ArmsHook_Draw
};
*/

extern ColQuadInit D_808C1BC0;

//ArmsHook_SetupAction
void func_808C1030(ArmsHook* this, ArmsHookActionFunc actionFunc) {
    this->actionFunc = actionFunc;
}

void ArmsHook_Init(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    Collision_InitQuadDefault(globalCtx, &this->collider);
    Collision_InitQuadWithData(globalCtx, &this->collider, &this->actor, &D_808C1BC0);
    func_808C1030(this, func_808C10F8);
    this->unk_1E0 = this->actor.currPosRot.pos;
}

void ArmsHook_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~0x2000;
    }
    Collision_FiniQuad(globalCtx, &this->collider);
}

void func_808C10F8(ArmsHook* this, GlobalContext* globalCtx) {
    if (this->actor.parent == NULL) {
        func_808C1030(this, func_808C12A4);
        func_800B6C04(&this->actor, 20.0f);
        this->actor.parent = &PLAYER->base;
        this->timer = 26; 
    }
}

void func_808C1154(ArmsHook* this) {
    this->actor.child = this->actor.parent;
    this->actor.parent->parent = &this->actor;
}

s32 func_808C1168(ArmsHook* this, ActorPlayer* player) {
    player->base.child = &this->actor;
    player->heldActor = &this->actor;
    if (this->actor.child != NULL) {
        player->base.parent = this->actor.child = NULL;
        return 1;
    }
    return 0;
}

void func_808C1198(ArmsHook* this) {
    if (this->grabbed != NULL) {
        this->grabbed->flags &= ~0x2000;
        this->grabbed = NULL;
    }
}

s32 func_808C11C0(ArmsHook* this) {
    ActorPlayer* player = (ActorPlayer*)this->actor.parent;
    if (func_801240C8(player)) {
        if ((player->heldItemActionParam != player->unk147) || ((player->base.flags & 0x100)) ||
            ((player->stateFlags1 & 0x4000080))) {
            this->timer = 0;
            func_808C1198(this);
            Math_Vec3f_Copy(&this->actor.currPosRot.pos, &player->unk368);
            return 1;
        }
    }
    return 0;
}

void func_808C125C(ArmsHook* this, Actor* actor) {
    actor->flags |= 0x2000;
    this->grabbed = actor;
    Math_Vec3f_Diff(&actor->currPosRot.pos, &this->actor.currPosRot.pos, &this->unk_1FC);
}

//GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C12A4.asm")
void func_808C12A4(ArmsHook* this, GlobalContext* globalCtx) {
    ActorPlayer* player = PLAYER;
    Actor* touchedActor;
    Actor* grabbed;
    Vec3f bodyDistDiffVec;
    Vec3f newPos;
    f32 bodyDistDiff;
    f32 phi_f16;
    DynaPolyActor* dynaPolyActor;
    f32 sp94;
    f32 sp90;
    s32 pad;
    CollisionPoly* poly;
    u32 dynaPolyID;
    Vec3f sp78;
    Vec3f prevFrameDiff;
    Vec3f sp60;
    f32 sp5C;
    f32 sp58;
    f32 velocity;
    s32 pad1;

    if ((this->actor.parent == NULL) || (!func_801240C8(player))) {
        func_808C1198(this);
        Actor_MarkForDeath(&this->actor);
        return;
    }

    func_8002F8F0(&player->base, 0x100B);
    func_808C11C0(this);

    if (this->timer != 0) {
        if ((this->collider.base.flagsAT & 2) && (this->collider.body.unk20->unk14 != 4)) {
            touchedActor = this->collider.base.collisionAT;
            if ((touchedActor->update != NULL) && (touchedActor->flags & 0x600)) {
                if (this->collider.body.unk20->unk16 & 4) {
                    func_808C125C(this, touchedActor);
                    if ((touchedActor->flags & 0x400) == 0x400) {
                        func_808C1154(this);
                    }
                }
            }
            this->timer = 0;
            //func_8019F1C0(this->actor.unkEC, 0x1814);
            return;
        }
    }
    
    if (DECR(this->timer) == 0) {
        grabbed = this->grabbed;
        if (grabbed != NULL) {
            if ((grabbed->update == NULL) || (grabbed->flags & 0x2000) != 0x2000) {
                grabbed = NULL;
                this->grabbed = NULL;
            } else {
                if (this->actor.child != NULL) {
                    sp94 = func_8002DB48(this, grabbed);
                    sp90 = sqrtf(SQ(this->unk_1FC.x) + SQ(this->unk_1FC.y) + SQ(this->unk_1FC.z));
                    Math_Vec3f_Diff(&grabbed->currPosRot.pos, &this->unk_1FC, &this->actor.currPosRot.pos);
                    if (50.0f < (sp94 - sp90)) {
                        ArmsHook_DetachHookFromActor(this);
                        grabbed = NULL;
                    }
                }
            }
        }

        bodyDistDiff = Math_Vec3f_DistXYZAndStoreDiff(&player->unk368, &this->actor.currPosRot.pos, &bodyDistDiffVec);
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

        if (this->actor.child == NULL) {
            if ((grabbed != NULL) && (grabbed->id == 213)) {
                Math_Vec3f_Diff(&grabbed->currPosRot.pos, &this->unk_1FC, &this->actor.currPosRot.pos);
                phi_f16 = 1.0f;
            } else {
                Math_Vec3f_Sum(&player->unk368, &newPos, &this->actor.currPosRot.pos);
                if (grabbed != NULL) {
                    Math_Vec3f_Sum(&this->actor.currPosRot.pos, &this->unk_1FC, &grabbed->currPosRot.pos);
                }
            }
        } else {
            Math_Vec3f_Diff(&bodyDistDiffVec, &newPos, &player->base.velocity);
            player->base.currPosRot.rot.x =
                atan2s(sqrtf(SQ(bodyDistDiffVec.x) + SQ(bodyDistDiffVec.z)), -bodyDistDiffVec.y);
        }

        if (phi_f16 < 50.0f) {
            ArmsHook_DetachHookFromActor(this);
            if (phi_f16 == 0.0f) {
                ArmsHook_SetupAction(this, func_808C10F8);
                if (ArmsHook_AttachToPlayer(this, player)) {
                    Math_Vec3f_Diff(&this->actor.currPosRot.pos, &player->base.currPosRot.pos, &player->base.velocity);
                    player->base.velocity.y -= 20.0f;
                    return;
                }
            }
        }
    } else {
        Actor_MoveForward(&this->actor);
        Math_Vec3f_Diff(&this->actor.currPosRot.pos, &this->actor.lastPos, &prevFrameDiff);
        Math_Vec3f_Sum(&this->unk_1E0, &prevFrameDiff, &this->unk_1E0);
        this->actor.shape.rot.x = atan2s(this->actor.speedXZ, -this->actor.velocity.y);
        sp60.x = this->unk_1E0.x - (this->unk_1EC.x - this->unk_1FC.x);
        sp60.y = this->unk_1E0.y - (this->unk_1EC.y - this->unk_1FC.y);
        sp60.z = this->unk_1E0.z - (this->unk_1EC.z - this->unk_1FC.z);
        if (func_8003DE84(&globalCtx->colCtx, &sp60, &this->unk_1EC, &sp78, &poly, 1, 1, 1, 1, &dynaPolyID) != 0) {
            if (func_8002F9EC(globalCtx, &this->actor, poly, dynaPolyID, &sp78) == 0) {
                sp5C = poly->norm.x * (1 / SHT_MAX);
                sp58 = poly->norm.z * (1 / SHT_MAX);
                Math_Vec3f_Copy(&this->actor.currPosRot.pos, &sp78);
                this->actor.currPosRot.pos.x += 10.0f * sp5C;
                this->actor.currPosRot.pos.z += 10.0f * sp58;
                this->timer = 0;
                if (func_80041FE8(&globalCtx->colCtx, poly, dynaPolyID) != 0) {
                    if (dynaPolyID != 0x32) {
                        dynaPolyActor = DynaPolyInfo_GetActor(&globalCtx->colCtx, dynaPolyID);
                        if (dynaPolyActor != NULL) {
                            ArmsHook_AttachHookToActor(this, &dynaPolyActor->actor);
                        }
                    }
                    func_80865044(this);

                    return;
                }
                func_80062D60(globalCtx, &this->actor.currPosRot.pos);

                return;
            }
        }
    }
}

void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk_1EC = this->unk_1E0;
}

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Draw.asm")
