#include "z_obj_visiblock.h"

#define FLAGS 0x00000080

#define THIS ((ObjVisiblock*)thisx)

void ObjVisiblock_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Destroy(Actor* thisx, GlobalContext* globalCtx);
void ObjVisiblock_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Visiblock_InitVars = {
    ACTOR_OBJ_VISIBLOCK,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_VISIBLOCK,
    sizeof(ObjVisiblock),
    (ActorFunc)ObjVisiblock_Init,
    (ActorFunc)ObjVisiblock_Destroy,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjVisiblock_Draw
};

static InitChainEntry D_80ADEB50[] = {
    ICHAIN_F32(uncullZoneForward, 4000, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneScale, 200, ICHAIN_CONTINUE),
    ICHAIN_F32(uncullZoneDownward, 150, ICHAIN_CONTINUE),
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

extern CollisionHeader D_06000AD0;
extern UNK_TYPE D_06000140;

void ObjVisiblock_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjVisiblock* this = THIS;

    Actor_ProcessInitChain(this, D_80ADEB50);
    BcCheck3_BgActorInit(&this->dyna, 0);
    BgCheck3_LoadMesh(globalCtx, &this->dyna, &D_06000AD0);
}

void ObjVisiblock_Destroy(Actor* thisx, GlobalContext* globalCtx) {
    ObjVisiblock* this = THIS;

    BgCheck_RemoveActorMesh(globalCtx, &globalCtx->colCtx.dyna, this->dyna.bgId);
}

void ObjVisiblock_Draw(Actor* thisx, GlobalContext* globalCtx) {
    func_800BE03C(globalCtx, &D_06000140);
}
