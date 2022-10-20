#include "global.h"
#include "initvars.h"
#include "overlays/fbdemos/ovl_fbdemo_triforce/z_fbdemo_triforce.h"
#include "overlays/fbdemos/ovl_fbdemo_wipe1/z_fbdemo_wipe1.h"
#include "overlays/fbdemos/ovl_fbdemo_wipe3/z_fbdemo_wipe3.h"
#include "overlays/fbdemos/ovl_fbdemo_wipe4/z_fbdemo_wipe4.h"
#include "overlays/fbdemos/ovl_fbdemo_wipe5/z_fbdemo_wipe5.h"

#define TRANSITION_OVERLAY(name, filename)                                                                       \
    {                                                                                                            \
        { 0, 0 }, SEGMENT_START(ovl_##filename), SEGMENT_END(ovl_##filename), SEGMENT_ROM_START(ovl_##filename), \
            SEGMENT_ROM_END(ovl_##filename), &name##_InitVars, sizeof(name)                                      \
    }

#define TRANSITION_OVERLAY_INTERNAL(name) \
    { { 0, 0 }, NULL, NULL, 0, 0, &name##_InitVars, sizeof(name) }

#define TRANSITION_OVERLAY_UNSET \
    { 0 }

TransitionOverlay gTransitionOverlayTable[] = {
    TRANSITION_OVERLAY_INTERNAL(TransitionFade),       TRANSITION_OVERLAY(TransitionTriforce, fbdemo_triforce),
    TRANSITION_OVERLAY(TransitionWipe1, fbdemo_wipe1), TRANSITION_OVERLAY(TransitionWipe3, fbdemo_wipe3),
    TRANSITION_OVERLAY(TransitionWipe4, fbdemo_wipe4), TRANSITION_OVERLAY_INTERNAL(TransitionCircle),
    TRANSITION_OVERLAY(TransitionWipe5, fbdemo_wipe5),
};

void Transition_Init(TransitionContext* transitionCtx) {
    TransitionOverlay* overlayEntry;
    ptrdiff_t relocOffset;
    TransitionInit* initInfo[1];

    overlayEntry = &gTransitionOverlayTable[transitionCtx->fbdemoType];
    TransitionOverlay_Load(overlayEntry);

    relocOffset = (uintptr_t)Lib_PhysicalToVirtual(overlayEntry->loadInfo.addr) - (uintptr_t)overlayEntry->vramStart;
    initInfo[0] = NULL;
    initInfo[0] = (overlayEntry->initInfo != NULL) ? (TransitionInit*)((uintptr_t)overlayEntry->initInfo + relocOffset)
                                                   : initInfo[0];

    transitionCtx->init = initInfo[0]->init;
    transitionCtx->destroy = initInfo[0]->destroy;
    transitionCtx->start = initInfo[0]->start;
    transitionCtx->isDone = initInfo[0]->isDone;
    transitionCtx->draw = initInfo[0]->draw;
    transitionCtx->update = initInfo[0]->update;
    transitionCtx->setType = initInfo[0]->setType;
    transitionCtx->setColor = initInfo[0]->setColor;
    transitionCtx->setEnvColor = initInfo[0]->setEnvColor;
}

void Transition_Destroy(TransitionContext* transitionCtx) {
    TransitionOverlay_Free(&gTransitionOverlayTable[transitionCtx->fbdemoType]);
}
