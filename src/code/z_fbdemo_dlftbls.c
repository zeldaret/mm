#include "global.h"

extern TransitionOverlay D_801D0BB0[];

void func_80163C90(TransitionContext *transitionCtx) {
    TransitionOverlay *sp24;
    intptr_t temp2;
    TransitionInit* sp1C[1];
     
    sp24 = &D_801D0BB0[transitionCtx->fbdemoType];
    func_80165288(sp24);
    
    temp2 = (uintptr_t)Lib_PhysicalToVirtualNull(sp24->unk_0_4) - sp24->unk_4;
    sp1C[0] = NULL;
    sp1C[0] = (sp24->unk_14 != NULL) ? (TransitionInit*)((uintptr_t)sp24->unk_14 + temp2) : sp1C[0];

    transitionCtx->init = sp1C[0]->init;
    transitionCtx->destroy = sp1C[0]->destroy;
    transitionCtx->start = sp1C[0]->start;
    transitionCtx->isDone = sp1C[0]->isDone;
    transitionCtx->draw = sp1C[0]->draw;
    transitionCtx->update = sp1C[0]->update;
    transitionCtx->setType = sp1C[0]->setType;
    transitionCtx->setColor = sp1C[0]->setColor;
    transitionCtx->setUnkColor = sp1C[0]->setEnvColor;
}

void func_80163D80(TransitionContext *transitionCtx) {
    func_8016537C(&D_801D0BB0[transitionCtx->fbdemoType]);
}
