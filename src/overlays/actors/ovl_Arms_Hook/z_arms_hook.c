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

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/func_808C12A4.asm")

void ArmsHook_Update(Actor* thisx, GlobalContext* globalCtx) {
    ArmsHook* this = THIS;

    this->actionFunc(this, globalCtx);
    this->unk_1EC = this->unk_1E0;
}

GLOBAL_ASM("asm/non_matchings/ovl_Arms_Hook_0x808C1030/ArmsHook_Draw.asm")
