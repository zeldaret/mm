/*
 * File: z_obj_dowsing.c
 * Overlay: ovl_Obj_Dowsing
 * Description:
 */

#include "z_obj_dowsing.h"

#define FLAGS 0x00000010

#define THIS ((ObjDowsing*)thisx)

s32 ObjDowsing_GetFlag(ObjDowsing* this, GlobalContext* globalCtx);
s32 func_80B23DD0(ObjDowsing* this, GlobalContext* globalCtx);
void ObjDowsing_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Update(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Dowsing_InitVars = {
    ACTOR_OBJ_DOWSING,
    ACTORCAT_ITEMACTION,
    FLAGS,
    GAMEPLAY_KEEP,
    sizeof(ObjDowsing),
    (ActorFunc)ObjDowsing_Init,
    (ActorFunc)ObjDowsing_Destroy,
    (ActorFunc)ObjDowsing_Update,
    (ActorFunc)NULL,
};

s32 ObjDowsing_GetFlag(ObjDowsing* this, GlobalContext* globalCtx) {
    s32 type = this->actor.params >> 7;
    s32 flag = this->actor.params & 0x7F;

    if (type == 1) {
        return Actor_GetCollectibleFlag(globalCtx, flag);
    } else if (type == 2) {
        return Actor_GetChestFlag(globalCtx, flag);
    } else if (type == 3) {
        return Flags_GetSwitch(globalCtx, flag);
    } else {
        return 0;
    }
}

s32 func_80B23DD0(ObjDowsing* this, GlobalContext* globalCtx) {
    if (ObjDowsing_GetFlag(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return 1;
    }
    return 0;
}

void ObjDowsing_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDowsing* this = THIS;

    func_80B23DD0(this, globalCtx);
}

void ObjDowsing_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDowsing_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjDowsing* this = THIS;

    if (!func_80B23DD0(this, globalCtx)) {
        func_800B8C50(thisx, globalCtx);
    }
}
