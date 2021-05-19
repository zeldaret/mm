#include <ultra64.h>
#include <global.h>

void CIC6105_Nop80081820(void) {
}

void CIC6105_Nop80081828(void) {
}

void CIC6105_PrintRomInfo(void) {
    FaultDrawer_DrawText(80, 200, "SP_STATUS %08x", (UNK_PTR)(*(u32*)0xA4040010));
    FaultDrawer_DrawText(40, 184, "ROM_F [Creator:%s]", &D_800994D0);
    FaultDrawer_DrawText(56, 192, "[Date:%s]", &D_800994DC);
}

void CIC6105_AddRomInfoFaultPage(void) {
    Fault_AddClient(&romInfoFaultClient, (fault_client_func)CIC6105_PrintRomInfo, 0, 0);
}

void CIC6105_RemoveRomInfoFaultPage(void) {
    Fault_RemoveClient(&romInfoFaultClient);
}

void func_800818F4(void) {
    D_8009BE30 = *(u32*)0xA02FB1F4;
    D_8009BE34 = *(u32*)0xA02FE1C0;
}
