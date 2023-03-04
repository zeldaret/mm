#include "prevent_bss_reordering.h"
#include "CIC6105.h"
#include "ultra64.h"
#include "build.h"
#include "global.h"
#include "unk.h"

UNK_TYPE4 D_8009BE30;
UNK_TYPE4 D_8009BE34;
FaultClient sRomInfoFaultClient;

void CIC6105_Nop80081820(void) {
}

void CIC6105_Nop80081828(void) {
}

void CIC6105_PrintRomInfo(void) {
    FaultDrawer_DrawText(80, 200, "SP_STATUS %08x", IO_READ(SP_STATUS_REG));
    FaultDrawer_DrawText(40, 184, "ROM_F [Creator:%s]", gBuildTeam);
    FaultDrawer_DrawText(56, 192, "[Date:%s]", gBuildDate);
}

void CIC6105_AddRomInfoFaultPage(void) {
    Fault_AddClient(&sRomInfoFaultClient, CIC6105_PrintRomInfo, 0, 0);
}

void CIC6105_RemoveRomInfoFaultPage(void) {
    Fault_RemoveClient(&sRomInfoFaultClient);
}

void func_800818F4(void) {
    D_8009BE30 = IO_READ(CIC_ADDRESS_1);
    D_8009BE34 = IO_READ(CIC_ADDRESS_2);
}
