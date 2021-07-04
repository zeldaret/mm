/*
 * File: z_obj_hana.c
 * Description: Orange Graveyard Flower
 */

#include "z_obj_hana.h"

#define FLAGS 0x00000000

#define THIS ((ObjHana*)thisx)

void ObjHana_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjHana_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Hana_InitVars = {
    ACTOR_OBJ_HANA,
    ACTORCAT_PROP,
    FLAGS,
    OBJECT_HANA,
    sizeof(ObjHana),
    (ActorFunc)ObjHana_Init,
    (ActorFunc)ObjHana_Destroy,
    (ActorFunc)ObjHana_Update,
    (ActorFunc)ObjHana_Draw,
};

extern Gfx D_06000500[];

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 10, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneForward, 900, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 40, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 40, ICHAIN_STOP),
};

void ObjHana_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjHana* this = THIS;

    Actor_ProcessInitChain(&this->actor, sInitChain);
}

void ObjHana_Destroy(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjHana_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjHana_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BDFC0(globalCtx, D_06000500);
}
