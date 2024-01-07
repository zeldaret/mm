#include "z64transition.h"

#include "segment_symbols.h"
#include "z64lib.h"

// InitVars and Linker symbol declarations (used in the table below)
#define DEFINE_TRANSITION(_enumValue, structName, _instanceName, name) \
    extern TransitionInit structName##_InitVars;                       \
    DECLARE_OVERLAY_SEGMENT(name)

#define DEFINE_TRANSITION_INTERNAL(_enumValue, structName, _instanceName) extern TransitionInit structName##_InitVars;

#include "tables/transition_table.h"

#undef DEFINE_TRANSITION
#undef DEFINE_TRANSITION_INTERNAL

#define DEFINE_TRANSITION(_enumValue, structName, _instanceName, name) \
    {                                                                  \
        { 0, 0 },                                                      \
        SEGMENT_START(ovl_##name),                                     \
        SEGMENT_END(ovl_##name),                                       \
        SEGMENT_ROM_START(ovl_##name),                                 \
        SEGMENT_ROM_END(ovl_##name),                                   \
        &structName##_InitVars,                                        \
        sizeof(structName),                                            \
    },

#define DEFINE_TRANSITION_INTERNAL(_enumValue, structName, _instanceName) \
    { { 0, 0 }, NULL, NULL, 0, 0, &structName##_InitVars, sizeof(structName) },

TransitionOverlay gTransitionOverlayTable[] = {
#include "tables/transition_table.h"
};

#undef DEFINE_TRANSITION
#undef DEFINE_TRANSITION_INTERNAL

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
