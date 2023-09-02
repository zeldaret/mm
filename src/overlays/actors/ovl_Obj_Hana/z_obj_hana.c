/*
 * File: z_obj_hana.c
 * Overlay: ovl_Obj_Hana
 * Description: Orange Graveyard Flower
 */

#include "z_obj_hana.h"
#include "objects/object_hana/object_hana.h"

#define FLAGS 0x00000000

#define THIS ((ObjHana*)thisx)

void ObjHana_Init(Actor* thisx, PlayState* play);
void ObjHana_Destroy(Actor* thisx, PlayState* play);
void ObjHana_Update(Actor* thisx, PlayState* play);
void ObjHana_Draw(Actor* thisx, PlayState* play);

ActorInit Obj_Hana_InitVars = {
    /**/ ACTOR_OBJ_HANA,
    /**/ ACTORCAT_PROP,
    /**/ FLAGS,
    /**/ OBJECT_HANA,
    /**/ sizeof(ObjHana),
    /**/ ObjHana_Init,
    /**/ ObjHana_Destroy,
    /**/ ObjHana_Update,
    /**/ ObjHana_Draw,
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 900, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_STOP),
};

void ObjHana_Init(Actor* thisx, PlayState* play) {
    ObjHana* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
}

void ObjHana_Destroy(Actor* thisx, PlayState* play) {
}

void ObjHana_Update(Actor* thisx, PlayState* play) {
}

void ObjHana_Draw(Actor* thisx, PlayState* play) {
    Gfx_DrawDListOpa(play, gGraveyardFlowersDL);
}
