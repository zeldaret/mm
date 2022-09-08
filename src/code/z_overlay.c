#include "global.h"
#include "z64load.h"

u32 func_801651B0(TransitionOverlay *arg0, u32 arg1) {
    void* temp_v0 = Lib_PhysicalToVirtualNull(arg0->unk_0_4);

    if ((temp_v0 != NULL) && (arg1 >= arg0->unk_4) && (arg1 < arg0->unk_8)) {
        return ((u32)temp_v0 - arg0->unk_4) + arg1;
    }
    return arg1;
}

void func_80165224(TransitionOverlay *arg0, u32 *arg1, s32 arg2) {
    s32 i;
    
    for(i = 0; i < arg2; i++) {
        arg1[i] = func_801651B0(arg0, arg1[i]);
    }
}

s32 func_80165288(TransitionOverlay *overlay) {
    s32 temp;
    void* sp28;

    if (overlay->unk_C == 0) {
        return 3;
    }
    if (Lib_PhysicalToVirtualNull(overlay->unk_0_4) == NULL) {
        sp28 = ZeldaArena_Malloc(overlay->unk_8 - overlay->unk_4);

        if (sp28 == NULL) {
            return -1;
        }
        Load2_LoadOverlay(overlay->unk_C, overlay->unk_10, overlay->unk_4, overlay->unk_8, sp28);
        overlay->unk_0_4 = Lib_PhysicalToVirtual(sp28);
        overlay->unk_0_0 = 1;
        return 0;
    }
    temp = overlay->unk_0_0;
    if(temp != 0) {
        temp++;
        overlay->unk_0_0 = temp;
        if(temp == 0) {
            return 2;
        } else {
            return 1;
        }
    } else {
        return 2;
    }
}

s32 func_8016537C(TransitionOverlay *overlay) {
    s32 temp_v0_2;
    void *temp_v0;

    if (overlay->unk_C == 0) {
        return 3;
    }
    temp_v0 = Lib_PhysicalToVirtualNull(overlay->unk_0_4);
    if (temp_v0 != NULL) {
        temp_v0_2 = overlay->unk_0_0;
        if (temp_v0_2 != 0) {
            temp_v0_2--;
            overlay->unk_0_0 = temp_v0_2;
            if (temp_v0_2 == 0) {
                ZeldaArena_Free(temp_v0);
                overlay->unk_0_4 = Lib_PhysicalToVirtual(NULL);
                return 0;
            }
            return 1;
        }
        return 2;
    }
    return -1;
}

void func_80165438(TransitionOverlay *arg0) {
    arg0->unk_0 = 0;
}

void func_80165444(TransitionOverlay *arg0, u32 arg1, u32 arg2, u32 arg3, u32 arg4) {
    arg0->unk_4 = arg1;
    arg0->unk_8 = arg2;
    arg0->unk_C = arg3;
    arg0->unk_10 = arg4;
}
