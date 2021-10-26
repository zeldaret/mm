#include "global.h"

#define COLD_RESET 0
#define NMI 1

NmiBuff* gNMIBuffer;

void Nmi_Init(void) {
    gNMIBuffer = (NmiBuff*)osAppNmiBuffer;
    gNMIBuffer->resetting = false;

    if (osResetType == COLD_RESET) {
        gNMIBuffer->resetCount = 0;
        gNMIBuffer->duration = 0;
    } else {
        gNMIBuffer->resetCount++;
        gNMIBuffer->duration += gNMIBuffer->resetTime;
    }

    gNMIBuffer->resetTime = 0;
}

void Nmi_SetPrenmiStart(void) {
    gNMIBuffer->resetting = true;
    gNMIBuffer->resetTime = osGetTime();
}

u32 Nmi_GetPrenmiHasStarted(void) {
    return gNMIBuffer->resetting;
}
