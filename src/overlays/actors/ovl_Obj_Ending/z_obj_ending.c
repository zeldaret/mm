#include "z_obj_ending.h"

#define FLAGS 0x00000030

#define THIS ((ObjEnding*)thisx)

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx);
void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx);

const ActorInit Obj_Ending_InitVars = {
    ACTOR_OBJ_ENDING,
    ACTORCAT_BG,
    FLAGS,
    OBJECT_ENDING_OBJ,
    sizeof(ObjEnding),
    (ActorFunc)ObjEnding_Init,
    (ActorFunc)func_800BDFB0,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw,
};

extern Gfx D_060003D0[];
extern Gfx D_060031A0[];
extern Gfx D_06003440[];
extern AnimatedMaterial D_06001FF8;

static ObjEndingModelInfo sModelInfo[] = {
    { { D_06003440, D_060031A0 }, NULL },
    { { NULL, D_060003D0 }, &D_06001FF8 },
};

static InitChainEntry sInitChain[] = {
    ICHAIN_VEC3F_DIV1000(scale, 100, ICHAIN_STOP),
};

void ObjEnding_Init(Actor* thisx, GlobalContext* globalCtx) {
    ObjEnding* this = THIS;
    AnimatedMaterial* animMat;

    Actor_ProcessInitChain(thisx, sInitChain);
    this->modelInfo = &sModelInfo[thisx->params];
    animMat = this->modelInfo->animMat;
    if (animMat != NULL) {
        this->animMat = (AnimatedMaterial*)Lib_SegmentedToVirtual(animMat);
    }
}

void ObjEnding_Update(Actor* thisx, GlobalContext* globalCtx) {
}

void ObjEnding_Draw(Actor* thisx, GlobalContext* globalCtx) {
    ObjEnding* this = THIS;
    Gfx* dl1;
    Gfx* dl2;

    if (this->animMat != NULL) {
        AnimatedMat_Draw(globalCtx, this->animMat);
    }
    dl1 = this->modelInfo->dLists[0];
    if (dl1 != NULL) {
        func_800BDFC0(globalCtx, dl1);
    }
    dl2 = this->modelInfo->dLists[1];
    if (dl2 != NULL) {
        func_800BE03C(globalCtx, dl2);
    }
}
