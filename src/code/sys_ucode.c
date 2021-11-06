#include "global.h"

u64* D_801D1E60 = D_801E2160;
u64* D_801D1E64 = D_801E3790;

u64* SysUcode_GetUCodeBoot(void) {
    return D_800969C0;
}

size_t SysUcode_GetUCodeBootSize(void) {
    return (uintptr_t)&D_80096B20 - (uintptr_t)D_800969C0;
}

u64* SysUcode_GetUCode(void) {
    return D_801D1E60;
}

u64* SysUcode_GetUCodeData(void) {
    return D_801D1E64;
}
