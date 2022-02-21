/*
 * File: z_obj_dowsing.c
 * Overlay: ovl_Obj_Dowsing
 * Description:
 */

#include "z_obj_dowsing.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDowsing*)thisx)

void ObjDowsing_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjDowsing_Update(Actor* thisx, GlobalContext* globalCtx);

s32 ObjDowsing_GetFlag(ObjDowsing* this, GlobalContext* globalCtx);
s32 ObjDowsing_CheckValidSpawn(ObjDowsing* this, GlobalContext* globalCtx);

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
    s32 type = DOWSING_GET_TYPE(&this->actor);
    s32 flag = DOWSING_GET_FLAG(&this->actor);

    if (type == DOWSING_COLLECTIBLE) {
        return Flags_GetCollectible(globalCtx, flag);
    } else if (type == DOWSING_CHEST) {
        return Flags_GetTreasure(globalCtx, flag);
    } else if (type == DOWSING_SWITCH) {
        return Flags_GetSwitch(globalCtx, flag);
    } else {
        return 0;
    }
}

s32 ObjDowsing_CheckValidSpawn(ObjDowsing* this, GlobalContext* globalCtx) {
    if (ObjDowsing_GetFlag(this, globalCtx)) {
        Actor_MarkForDeath(&this->actor);
        return true;
    }
    return false;
}

void ObjDowsing_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjDowsing* this = THIS;

    ObjDowsing_CheckValidSpawn(this, globalCtx);
}

void ObjDowsing_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjDowsing_Update(Actor* thisx, GlobalContext* globalCtx) {
    ObjDowsing* this = THIS;

    if (!ObjDowsing_CheckValidSpawn(this, globalCtx)) {
        func_800B8C50(thisx, globalCtx);
    }
}
