#include "z_obj_ending.h"

#define FLAGS 0x00000030

#define THIS ((ObjEnding*)thisx)

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx);

/*
const ActorInit Obj_Ending_InitVars = {
    ACTOR_OBJ_ENDING,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ENDING_OBJ,
    sizeof(ObjEnding),
    (ActorFunc)ObjEnding_Init,
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw,
};
*/

extern InitChainEntry D_80C25CF8[];
/*
static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};
*/

extern unkStruct D_80C25CE0[];
/*
static unkStruct D_80C25CE0[2] = {
    {0x06003440, 0x060031A0, 0x00000000},
    {0x00000000, 0x060003D0, 0x06001FF8}
};
*/

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjEnding* this = THIS;
    AnimatedMaterial* texture;

    Actor_ProcessInitChain(&this->actor, D_80C25CF8);
    this->unk144 = &D_80C25CE0[this->actor.params];
    if (false) {}
    texture = this->unk144->texture;

    if (texture != NULL) {
        this->texture = Lib_SegmentedToVirtual(texture);
    }
}

void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjEnding* this = THIS;
    Gfx* dl;
    Gfx* tempunk4;

    if (this->texture != NULL) {
        AnimatedMat_Draw(globalCtx, this->texture);
    }
    tempunk4 = this->unk144->unk0;
    if (tempunk4 != 0) {
        func_800BDFC0(globalCtx, tempunk4);
    }
    dl = this->unk144->dl;
    if (dl != NULL) {
        func_800BE03C(globalCtx, dl);
    }
}
