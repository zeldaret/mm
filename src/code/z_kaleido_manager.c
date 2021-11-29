#include "global.h"

#define KALEIDO_OVERLAY(name)                                                                                \
    {                                                                                                        \
        NULL, (u32)_ovl_##name##SegmentRomStart, (u32)_ovl_##name##SegmentRomEnd, _ovl_##name##SegmentStart, \
            _ovl_##name##SegmentEnd, 0, #name,                                                               \
    }

KaleidoMgrOverlay gKaleidoMgrOverlayTable[] = {
    KALEIDO_OVERLAY(kaleido_scope),
    KALEIDO_OVERLAY(player_actor),
};

void* sKaleidoAreaPtr = NULL;
KaleidoMgrOverlay* gKaleidoMgrCurOvl = NULL;
FaultAddrConvClient sKaleidoAreaFaultClient;

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/func_80163700.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/KaleidoManager_LoadOvl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/KaleidoManager_ClearOvl.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/KaleidoManager_Init.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/KaleidoManager_Destroy.s")

#pragma GLOBAL_ASM("asm/non_matchings/code/z_kaleido_manager/KaleidoManager_GetRamAddr.s")
