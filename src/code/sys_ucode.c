/* 
 * File: sys_ucode.c
 * Description: Functions for obtaining locations and sizes of microcode
 */
#include "global.h"

extern u64 rspbootTextStart[];
extern u64 rspbootTextEnd[];

u64* initialgspUcodeText = gspF3DEX2_NoN_fifoTextStart;
u64* initialgspUcodeData = gspF3DEX2_NoN_fifoDataStart;

u64* SysUcode_GetUCodeBoot(void) {
    return rspbootTextStart;
}

size_t SysUcode_GetUCodeBootSize(void) {
    return (uintptr_t)rspbootTextEnd - (uintptr_t)rspbootTextStart;
}

u64* SysUcode_GetUCode(void) {
    return initialgspUcodeText;
}

u64* SysUcode_GetUCodeData(void) {
    return initialgspUcodeData;
}
