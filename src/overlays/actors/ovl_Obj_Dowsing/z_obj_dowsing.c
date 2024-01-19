/*
 * File: z_obj_dowsing.c
 * Overlay: ovl_Obj_Dowsing
 * Description: Rumbles controller if switch or collectible/chest flag is unset
 */

#include "z_obj_dowsing.h"

#define FLAGS (ACTOR_FLAG_10)

#define THIS ((ObjDowsing*)thisx)

void ObjDowsing_Init(Actor* thisx, PlayState* play);
void ObjDowsing_Destroy(Actor* thisx, PlayState* play);
void ObjDowsing_Update(Actor* thisx, PlayState* play);

s32 ObjDowsing_GetFlag(ObjDowsing* this, PlayState* play);
s32 ObjDowsing_CheckValidSpawn(ObjDowsing* this, PlayState* play);

ActorInit Obj_Dowsing_InitVars = {
    /**/ ACTOR_OBJ_DOWSING,
    /**/ ACTORCAT_ITEMACTION,
    /**/ FLAGS,
    /**/ GAMEPLAY_KEEP,
    /**/ sizeof(ObjDowsing),
    /**/ ObjDowsing_Init,
    /**/ ObjDowsing_Destroy,
    /**/ ObjDowsing_Update,
    /**/ NULL,
};

s32 ObjDowsing_GetFlag(ObjDowsing* this, PlayState* play) {
    s32 type = DOWSING_GET_TYPE(&this->actor);
    s32 flag = DOWSING_GET_FLAG(&this->actor);

    if (type == DOWSING_COLLECTIBLE) {
        return Flags_GetCollectible(play, flag);
    } else if (type == DOWSING_CHEST) {
        return Flags_GetTreasure(play, flag);
    } else if (type == DOWSING_SWITCH) {
        return Flags_GetSwitch(play, flag);
    } else {
        return 0;
    }
}

s32 ObjDowsing_CheckValidSpawn(ObjDowsing* this, PlayState* play) {
    if (ObjDowsing_GetFlag(this, play)) {
        Actor_Kill(&this->actor);
        return true;
    }
    return false;
}

void ObjDowsing_Init(Actor* thisx, PlayState* play) {
    ObjDowsing* this = THIS;

    ObjDowsing_CheckValidSpawn(this, play);
}

void ObjDowsing_Destroy(Actor* thisx, PlayState* play) {
}

void ObjDowsing_Update(Actor* thisx, PlayState* play) {
    ObjDowsing* this = THIS;

    if (!ObjDowsing_CheckValidSpawn(this, play)) {
        Actor_SetClosestSecretDistance(thisx, play);
    }
}
