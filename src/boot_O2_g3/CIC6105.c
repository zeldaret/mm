#include "global.h"

UNK_TYPE4 D_8009BE30;
UNK_TYPE4 D_8009BE34;
FaultClient romInfoFaultClient;

void CIC6105_Nop80081820(void) {
}

void CIC6105_Nop80081828(void) {
}

void CIC6105_PrintRomInfo(void) {
    FaultDrawer_DrawText(80, 200, "SP_STATUS %08x", HW_REG(SP_STATUS_REG, u32));
    FaultDrawer_DrawText(40, 184, "ROM_F [Creator:%s]", gBuildTeam);
    FaultDrawer_DrawText(56, 192, "[Date:%s]", gBuildDate);
}

void CIC6105_AddRomInfoFaultPage(void) {
    Fault_AddClient(&romInfoFaultClient, CIC6105_PrintRomInfo, 0, 0);
}

void CIC6105_RemoveRomInfoFaultPage(void) {
    Fault_RemoveClient(&romInfoFaultClient);
}

void func_800818F4(void) {
    D_8009BE30 = *(u32*)0xA02FB1F4;
    D_8009BE34 = *(u32*)0xA02FE1C0;
}
