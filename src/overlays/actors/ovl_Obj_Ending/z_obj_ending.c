/*
 * File: z_obj_ending.c
 * Overlay: ovl_Obj_Ending
 * Description: The stump and lighting at the end of the credits
 */

#include "z_obj_ending.h"
#include "objects/object_ending_obj/object_ending_obj.h"

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
    (ActorFunc)Actor_Noop,
    (ActorFunc)ObjEnding_Update,
    (ActorFunc)ObjEnding_Draw,
};

static ObjEndingModelInfo sModelInfo[] = {
    { { object_ending_obj_DL_003440, object_ending_obj_DL_0031A0 }, NULL },
    { { NULL, object_ending_obj_DL_0003D0 }, object_ending_obj_Matanimheader_001FF8 },
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
