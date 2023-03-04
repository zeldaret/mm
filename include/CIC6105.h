#ifndef CIC6105_H
#define CIC6105_H

// IPL3 puts values in those addresses as part of the anti-piracy checks
#define CIC_ADDRESS_1 0x2FB1F4
#define CIC_ADDRESS_2 0x2FE1C0


void CIC6105_Nop80081820(void);
void CIC6105_Nop80081828(void);
void CIC6105_PrintRomInfo(void);
void CIC6105_AddRomInfoFaultPage(void);
void CIC6105_RemoveRomInfoFaultPage(void);
void func_800818F4(void);

#endif
